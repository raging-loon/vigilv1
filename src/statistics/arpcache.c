#include <stdint.h>
#include "arpcache.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../../globals.h"
#include "../utils.h"



void compare_entries(char * ip, char * mac){
  for(int i = 0; i < arp_entries + 1; i++){
    if(compare_ip_entry((char*)&arpcache[i].ip_addr,ip)){
      if(compare_mac_entry((char*)&arpcache[i].mac_addr,mac)){
        // do nothing its fine
      } else {
        printf("Arp entry changed for ip address %s: was %s is now %s",
                ip, arpcache[i].mac_addr, mac);
      }
    }
  }
}

void add_entry(char *ip, char  *mac){
  struct arp_entry * entry = &arpcache[++arp_entries];
  // for(int i = 0; i < 4; i++) entry->ip_addr[i] = ip[i];  
  // for(int i = 0; i < 6; i++) entry->mac_addr[i] = mac[i];
  strcpy(entry->ip_addr,ip);
  strcpy(entry->mac_addr,mac);
} 


int entry_exists(char *ip,char *mac){
  for(int i = 0; i < arp_entries + 1; i++ ){
    if(compare_ip_entry((char*)&arpcache[i].ip_addr, ip) == 0 &&
       compare_mac_entry((char*)&arpcache[i].mac_addr, mac) == 0) return i;
  }
  return -1;
}


int compare_ip_entry(char * ip1,char * ip2){
  return strcmp(ip1,ip2);

}
int compare_mac_entry(char * mac1,char * mac2){
  return strcmp(mac1, mac2);
  


}



void load_csv_arp_cache(){
  FILE * fp = fopen("/usr/share/npsi/arpcache.csv","r");
  if(fp == NULL){
    printf("Could not load arp cache from database, file nonexistant\n");
    goto close;
  }
  char * line = NULL;
  size_t pos, len = 0;
  while((pos = getline(&line,&len,fp)) != -1){
    if(strstr(line,"\x00") == 0)
      break;
    
    printf("%s\n",line);
    char __ipaddress[16];
    char __macaddress[18];
    
    line[strcspn(line,"\n")] = 0;
    char * ip_addr = strtok(line,",");
    strcpy(__ipaddress,ip_addr);
    ip_addr = strtok(NULL,",");
    strcpy(__macaddress,ip_addr);
    printf("%s -> %s\n",__ipaddress,__macaddress);

  }
  if(line) free(line);
  goto close;
close:
  fclose(fp);
}