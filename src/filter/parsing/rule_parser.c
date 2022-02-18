/*
 * Copyright 2021 Conner Macolley
 *
 *    Licensed under the Apache License, Version 2.0 (the "License");
 *    you may not use this file except in compliance with the License.
 *    You may obtain a copy of the License at
 *
 *        http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Unless required by applicable law or agreed to in writing, software
 *    distributed under the License is distributed on an "AS IS" BASIS,
 *    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *    See the License for the specific language governing permissions and
 *    limitations under the License.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "rule_parser.h"
#include "rule.h"
#include "packet_parser.h"
#include "../actions/alerts.h"
#include "../../../globals.h"
#include "../../debug.h"
#include "line_parser.h"
#include "homenet.h"
#include "../../utils.h"
static bool is_rule(const char *);
static bool is_comment(const char * line);
static void rstrip(char * );
static void syntax_error(const char * line, int line_no);
static void get_action(const char * , struct rule *);


/*
  *-*-*-*- rule_parser.c -*-*-*-*
  @purpose Parse <i>stuff</i>

  void rule_library_parser(const char * alt_file);
    ==> Parse the configuration file located in /noraa.conf(github) or /etc/noraa/noraa.conf(live system)
    Global variables in /globals.c are declared here.
    Rules are parsed here, any line starting with a '$' is treated like a file containing rules.
    They are passed to rule_parser
  void rule_parser(const char * __filename);
    ==> parse the rules containted in a rule file
    Calls line_parser to actually parse them
  
  void line_parser(const char * line);
    ==> Parse the individual rules in a file
    The format for these rules is as follows:
    "alert alert_type port protocol (name:"name"; msg:"msg"; type:type; target:"target";)"
      - alert_type is the type of alert to be called by the rule, the function pointer is assigned using 
        the get_action function
      - port is the port number this rule is applied to
        @TODO: add more flexibility and support here
      - protocol is the layer 4 protocol that this rule should be applied to.
      - name is the name of the rule.
      - msg is the message to be printed to the screen and in logs
      - type is the function pointer that is assigned using the get_ruletype function
    After the line has been successfuly parsed, they rule is built and added to the "rules" struct
    located in /src/globals.c

  void deny_conf_parser(char * file);
    ==> Parse the blacklist
    Entries should be listed as follows:
      protocol:address
      i.e: ipv4:10.0.0.1
    The ipv4 addresses will be added to the blocked_ipv4_addrs struct in /src/globals.
    @TODO: add support for MAC and IPv6 addresses
    
*/

 


// also the main config parser
void rule_library_parser(const char * alt_file){
  // alt_file will be determined elsewhere
  FILE * fp = fopen(alt_file,"r");
  if(fp == NULL){
    printf("Error opening configuration file: %s\n",alt_file);
    exit(EXIT_FAILURE);
  }
  size_t pos;
  size_t len = 0;
  char * line = NULL;
  
  while((pos = getline(&line,&len,fp)) != -1){
    
    line[strcspn(line,"\n")] = 0;
    // printf("%s\n",line);
    if(is_comment(line) == true) continue;
  
    else if(strncmp(line,"strict_icmp_timestamp_req=",26) == 0){
      if(strcmp(line + 26,"YES") == 0) strict_icmp_timestamp_req = true;
      else strict_icmp_timestamp_req = false;
    }
    else if(strncmp(line,"strict_nmap_host_alive_check=",29) == 0){
      if(strcmp(line + 29, "YES") == 0) strict_nmap_host_alive_check = true;
      else strict_nmap_host_alive_check = false;
    }
    else if(strncmp(line,"clean_delay_in_packets=",23) == 0){
      
      if(strlen(line) < 24){
        printf("Clean delay needs a value\n");
        exit(EXIT_FAILURE);
      } 
      clean_delay_pkts = atoi(line + 23);
      
    }
    else if(strncmp(line,"clean_delay_in_mseconds=",24) == 0){
      if(strlen(line) == 24){
        printf("Clean delay needs a value\n");
        exit(EXIT_FAILURE);
      }
      clean_delay = atoi(line + 24);
    }

    else if(strncmp(line,"use_sqlite=",11) == 0){
      if(strcmp(line + 11,"YES") == 0) use_sqlite = true;
      else use_sqlite = false;
    }
    else if(strncmp(line,"sqlite_database_path=",21) == 0){
      strcpy(sqlite_db_path,line + 21);
      livedebug("sqlite_database_path: %s",sqlite_db_path);
    }
    else if(strncmp(line,"in_adapter=",11) == 0){
      strcpy(input_adapter,line + 11);
      livedebug("rule_parser.c: rule_library_parser: in_adapter: %s",input_adapter);
      
    }
    else if(strncmp(line,"out_adapter=",12) == 0){
      strcpy(output_adapter,line + 12);
      livedebug("rule_parser.c: rule_library_parser: out_adapter: %s",output_adapter);
      
    }
    else if(strncmp(line,"mode=",5) == 0){
      livedebug("mode: %s",line + 5);
      printf("Running in ");
      if(strncmp(line+5,"2",1) == 0){
        NORAA_MODE = IPS_ACTIVE;
        printf("IPS mode as per config\n");
      } else {
        // default to ids mode to minimize disruption if there was an mistake in the config

        NORAA_MODE = IDS_PASSIVE;
        printf("IDS mode as per config\n");
      }

    }
    else if(strncmp(line,"localip=",8) == 0){
      strcpy(local_ip,line + 8);
      livedebug("local_ip as per config: %s",&local_ip);
    }
    else if(strncmp(line,"defgw=",6) == 0){
      strcpy(def_gw,line + 6);
    }
    else if(strncmp(line,"use_spi=",8)  == 0){
      if(strcmp(line + 6,"YES") == 0) use_spi = true;
      else use_spi = false;
    }
    else if(strncmp(line,"HOME_NET=",9) == 0){
      // line[strcspn(line,"\n")] = 0x00;
      rstrip(line);
      homenet =  homenet_toi(line + 9);
    }
    else if(strncmp(line,"HOME_NET_MASK=",14) == 0){
      rstrip(line);
      homenetmask = homenet_toi(line + 14);
    }
    else if(is_rule(line)){
      // printf("Parsing: %s\n",line);
      rule_parser(line);
    }
    memset(line,0,sizeof(line)); 
  }
  if(NORAA_MODE == 0xffff){
    NORAA_MODE = IDS_PASSIVE;
  }
}
static bool is_rule(const char * line){
  return line[0] == '$' ? true : false;
}

static bool is_comment(const char * line){
  return strstr(line,"#") != NULL ? true : false;
}

static void rstrip(char * line){
  line[strcspn(line,"\n")] = 0;
}

static void syntax_error(const char * line, int line_no){
  printf("Syntax error at line %d: %s\n",line_no,line);
  exit(EXIT_FAILURE);
}

void rule_parser(const char * __filename){
  // + 1 for the $ at the beggining
  // also for the " " at the beggining when filename is given over network
  const char * filename = __filename + 1;
  FILE * fp = fopen(filename,"r");
  if(fp == NULL){
    printf("Error opening rule file: %s. Refusing to continue\n",filename);

    exit(EXIT_FAILURE);
  }
  printf("Parsing file %s\n",filename);
  size_t pos;
  size_t len = 0;
  char * line = NULL;
  
  while((pos = getline(&line,&len,fp)) != -1){
    if(is_comment(line))
      continue;
    rstrip(line);

    if(strcmp("\x00",line) == 0) continue;
    if(strstr(line,"alert") != NULL){
      line_parser(line);
    } 
  }
  if(debug_mode) printf("Finished parsing %s\n",filename);
}

void deny_conf_parser(char * file){
  FILE * fp = fopen(file,"r");
  if(fp == NULL){
    printf("Error opening %s for expl/implicit deny parsing\n",file);
    exit(EXIT_FAILURE);
  }
  char * line = NULL;
  size_t pos, len = 0;
  while((pos = getline(&line,&len,fp)) != -1){
    rstrip(line);
    if(is_comment(line)) continue;
    
    if(strcmp("\x00",line) == 0) continue;
    if(strstr(line,"ipv4")){
      struct blocked_ipv4 * temp = &blocked_ipv4_addrs[++blk_ipv4_len];
      char * ipv4_addr = line + 5;
      // printf("%s\n",ipv4_addr);
      strcpy(temp->ipv4_addr ,ipv4_addr);
    } 
  }
  
  if(line) free(line);
  
  /*
  for(int i = 0; i < blk_ipv4_len+1; i++){
    printf("Blocked IP address: %s\n",blocked_ipv4_addrs[i].ipv4_addr);
  }
  */
}


void host_mon_parser(){
  FILE * fp = fopen(default_host_conf,"r");
  if(fp == NULL){
    printf("Failed to open %s\n",default_host_conf);
    exit(EXIT_FAILURE);
  }
  fclose(fp);
}
