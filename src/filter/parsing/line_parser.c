#include "line_parser.h"
#include "rule.h"
#include "../actions/alerts.h"
#include "packet_parser.h"
#include "rule_parser.h"
#include "token.h"
#include "../../../globals.h"
#include "../../utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/* alert stdout any TCP (name:"ioc-root-uid"; msg:"IOC Root UID returned"; type:str_match; target:"uid=0(root)";); */
static char * substr(char * str, int left, int right){
  char * sub = (char *)malloc(sizeof(char) * (right - left + 2));
  for(int i = left; i <= right; i++){
    sub[i - left] = str[i];
  }
  sub[right - left + 1] = '\0';
  return sub;
}
static bool delimit(char c){
  return c == ' ';
}


static bool isdigit(const char * pos_num){
  for(int i = 0; i < strlen(pos_num); i++){
    if(pos_num[i] != '0' && pos_num[i] != '1' && pos_num[i] != '2' &&
       pos_num[i] != '3' && pos_num[i] != '4' && pos_num[i] != '4' &&
       pos_num[i] != '5' && pos_num[i] != '6' && pos_num[i] != '7' &&
       pos_num[i] != '8' && pos_num[i] != '9') 
      return false;
  }
  return true;
}


static void assign_port_number(const char * sub, struct rule * r){
  if(isdigit(sub))
    r->port = atoi(sub);
  else if(strcmp(sub,"any") == 0)
    r->port = -1;
  
}

static void assign_protocol(const char * sub, struct rule * r){
  if(strcmp(sub,"ANY") == 0)
    r->protocol = R_ALL;
  else if(strcmp(sub,"ICMP") == 0)
    r->protocol = R_ICMP;

  else if(strcmp(sub,"TCP") == 0)
    r->protocol = R_TCP;
  else if(strcmp(sub,"UDP") == 0)
    r->protocol = R_UDP;
}

static void get_ruletype(const char * __line, struct rule * __rule){
  if(strncmp(__line,"str_match",9) == 0){
    __rule->pkt_parser = str_match_parser;
    return;
  }

  else {
    printf("Unknown rule type: %s\n",__line);
    exit(EXIT_FAILURE);
  }
  
}
static int numeric_check(char * sub,int min, int max){
  if(isdigit(sub)){
    int tval = atoi(sub);
    if(tval >= min && tval <= max)
      return tval;
  }
  return -1;
}
// semicolon strip
static void sc_strip(char * sub){
  sub[strcspn(sub,";")] = 0;
}



static void void_rule(struct rule * r){
  memset(&r->icmp_data, NULL,sizeof(r->icmp_data));
  memset(&r->ip_data,   NULL,sizeof(r->ip_data));
  memset(&r->tcp_data,  NULL,sizeof(r->tcp_data));
}





void line_parser(const char * line){
  struct rule * rdata = &rules[++num_rules];
  rdata->port = -1;
  rdata->protocol = -1;
  void_rule(rdata);
  int chars_parsed = 0;
  char * parser;
  char * content;
  bool data = false;
  int left = 0, right = 0;
  int len = strlen(line);
  bool parsing_msg_str = false;
  bool parsing_target_str = false;
  while(right <= len && left <= right){
    if(!delimit(line[right])) {
      right++;
    
    }
    if(delimit(line[right]) && right == left){
      if(line[right] == ':'){
        printf("Found operator");
      }
      right++;
      left = right;
    
    
    } else if(delimit(line[right]) && left != right || (right == len && left != right)){
      char * sub = substr(line, left, right -1);
      // printf("%s\n",sub);
      entry:
      
      if(data == false){

        if(strcmp(sub,NKEY_ALERT) == 0)
            ;
        else if(strcmp(sub,"stdout") == 0 && !parsing_msg_str && !parsing_target_str)
          rdata->action = stdout_alert;
        else if((strcmp(sub,"ICMP") == 0 || strcmp(sub,"ANY") == 0 || 
                 strcmp(sub,"TCP") == 0 || strcmp(sub,"UDP") == 0) && !parsing_target_str && !parsing_msg_str)
          assign_protocol(sub,rdata);
        else if((isdigit(sub) || strcmp(sub,"any") == 0) && !parsing_msg_str && !parsing_target_str)
          assign_port_number(sub,rdata);
        else if(sub[0] == '('){
          data = true;
          continue;
        }


      } else {
          char * keysub;
          if(sub[0] == '(') 
            keysub = sub + 1;
          else 
            keysub = sub;


          if(parsing_msg_str){

            if(keysub[strlen(keysub)- 1] == ';'){
              strncat(rdata->message,keysub,strlen(keysub) -2);
              parsing_msg_str = false;
              continue;
            }
            strcat(rdata->message,keysub);
            strcat(rdata->message," ");

          } else if(parsing_target_str){
              if(strstr(keysub,"\";") != NULL){
                strncat(rdata->rule_target,keysub,strlen(keysub) - 3);
                parsing_target_str = false;
                continue;
              }
              strcat(rdata->rule_target,keysub);
              strcat(rdata->rule_target,"\x20");

          } else {

            if(strncmp(keysub,"name:\"",6) == 0){
              strncpy(rdata->rulename,keysub + 6,strlen(keysub) - 8);
            }
            else if(strncmp(keysub,"msg:\"",5) == 0){
              parsing_msg_str = true;
              char * partial_msg = keysub + 5;
              strcat(rdata->message, partial_msg);
              strcat(rdata->message,"\x20");
            } 
            else if(strncmp(keysub,"type:",5) == 0){
              char rtype[10];
              strncpy(rtype,keysub + 5, strlen(keysub) -6);

              get_ruletype(rtype,rdata);
            }
            else if(strncmp(keysub,"target:\"",8) == 0){
              char * partial_target = keysub + 8;
              if(strstr(partial_target,"\";") != NULL){
                strncpy(rdata->rule_target, keysub + 8,strlen(keysub) - 11);
              } else {
                parsing_target_str = true;
                strcat(rdata->rule_target, partial_target);
                strcat(rdata->rule_target,"\x20");
              }
            
            }
          else if(strncmp(keysub,"sev:",4) == 0){
            // remove semicolon
            keysub[strcspn(keysub,";")] == 0x00;
            if(isdigit(keysub + 4)){
              int r_sev = atoi(keysub + 4);
              if(r_sev > 0 && r_sev <= 10){
                rdata->severity = r_sev;
              } else {
                printf("Rule severity should be > 0 and <= 10\n");
                exit(-1);
              }
            } else {
              printf("Rule severity should be a numeric value\n");
              exit(-1);
            }
          }
          else if(strncmp(keysub,"itype:",6) == 0){
            sc_strip(keysub);
            if(rdata->protocol == R_ICMP){
              int itype = numeric_check(keysub + 6,0,255);
              if(itype == -1){
                printf("Invalid icmp type value\n");
                exit(-1);
              } else {
                rdata->icmp_data.type = itype;
                rdata->icmp_data.typeset = true;
              }

            } else {
              printf("%s: itype only applies to rules with ICMP as protocol\n",rdata->rulename);
              exit(-1);
            }
          }

          else if(strncmp(keysub,"icode:",6) == 0){
            sc_strip(keysub);
            if(rdata->protocol == R_ICMP){
              int icode = numeric_check(keysub + 6,0,255);
              if(icode == -1){
                printf("Invalide icmp code value\n");
                exit(-1);
              } 
              rdata->icmp_data.code = icode;
              rdata->icmp_data.codeset = true;
            } else {
              printf("icode only applies to rules with ICMP as protocol\n");
            }
          }

          else if(strncmp(keysub,"icmp_id:",8) == 0){
            sc_strip(keysub);
            if(rdata->protocol = R_ICMP){
              int iid = numeric_check(keysub + 8,0,65535);
              if(icode == -1){
                printf("Invalid icmp id value\n");
                exit(-1);
              }
              rdata->icmp_data.id = iid;
              rdata->icmp_data.idset = true;
            }
          } else {
            printf("icmp_id only applies to rules with ICMP as protocol\n");
            exit(-1);
          }

        }

    
      }

      left = right;
      if(sub[strlen(sub) - 1] == ')') return;
    }


  }
}
