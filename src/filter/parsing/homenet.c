#include "homenet.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

uint32_t homenet_toi(const char * ip_addr){
  char num_str[9];
  
  char * octet = strtok(ip_addr,".");
  while(octet != NULL){
    sprintf(num_str + strlen(num_str),"%x",atoi(octet));
    octet = strtok(NULL,".");
  }
  return (uint32_t)strtol(num_str,NULL,16);
}
