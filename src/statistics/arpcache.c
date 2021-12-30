#include <stdint.h>
#include "arpcache.h"
#include <stdio.h>
#include "../../globals.h"
#include "../utils.h"



void compare_entries(uint8_t ip, uint8_t mac){
  for(int i = 0; i < arp_entries + 1; i++){
    if(compare_ip_entry((uint8_t*)&arpcache[i].ip_addr,&ip)){
      if(compare_mac_entry((uint8_t*)&arpcache[i].mac_addr,&mac)){
        // do nothing its fine
      } else {
        printf("Arp entry changed for ip address %s: was %s is now %s",
                u8_ipv4_ntoa(&ip),
                mac_ntoa((uint8_t*)&arpcache[i].mac_addr),
                mac_ntoa(&mac));
      }
    }
  }
}

void add_entry(uint8_t *ip, uint8_t  *mac){
  struct arp_entry * entry = &arpcache[++arp_entries];
  for(int i = 0; i < 4; i++) entry->ip_addr[i] = ip[i];  
  for(int i = 0; i < 6; i++) entry->mac_addr[i] = mac[i];
} 


int entry_exists(uint8_t *ip,uint8_t *mac){
  for(int i = 0; i < arp_entries + 1; i++ ){
    if(compare_ip_entry((uint8_t*)&arpcache[i].ip_addr, ip) == -1 &&
       compare_mac_entry((uint8_t*)&arpcache[i].mac_addr, mac) == -1) return i;
  }
  return -1;
}


int compare_ip_entry(uint8_t * ip1,uint8_t * ip2){
  for(int i = 0; i < 4; i++){
    if(ip1[i] != ip2[i]) return -1;
  }
  return 1;
}
int compare_mac_entry(uint8_t * mac1,uint8_t * mac2){
  for(int i = 0; i < 6; i++){
    if(mac1[i] != mac2[i]) return -1;
  }
  return 1;

}