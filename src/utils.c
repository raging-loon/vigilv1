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

#include "utils.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include <uchar.h>
#include <time.h>
static __thread char buffer[128];

char * mac_ntoa( uint8_t * hwaddr){
  // printf("mac_ntoa\n");
  // char *__hwaddr;
  unsigned char * __hwaddr = (unsigned char *)hwaddr;
  snprintf(buffer, sizeof(buffer), "%02x:%02x:%02x:%02x:%02x:%02x",
      __hwaddr[0], __hwaddr[1], __hwaddr[2], __hwaddr[3], __hwaddr[4], __hwaddr[5]
  );
  return buffer;

}
char * uc_mac_ntoa(unsigned char * __hwaddr){
  snprintf(buffer, sizeof(buffer), "%02x:%02x:%02x:%02x:%02x:%02x",  __hwaddr[0], __hwaddr[1], __hwaddr[2], __hwaddr[3], __hwaddr[4], __hwaddr[5]
  );
  return buffer;
}
char * u8_ipv4_ntoa(uint8_t * ip_addr){

  unsigned char * __ip_addr = (unsigned char *)ip_addr;
  snprintf(buffer,sizeof(buffer),"%d.%d.%d.%d",
    __ip_addr[0],__ip_addr[1],__ip_addr[2],__ip_addr[3]
  );
  return buffer;
}
char * ipv4_ntoa( uint32_t * ip_addr){
  // char buffer[18];
  unsigned char * __ip_addr = (unsigned char *)ip_addr;
  snprintf(buffer,sizeof(buffer),"%d.%d.%d.%d",
    __ip_addr[0],__ip_addr[1],__ip_addr[2],__ip_addr[3]
  );
  return buffer;
  
}


unsigned char * inet6_ntoa(uint8_t * ip_bits){
  unsigned char *bytes;
  memset(buffer,0,128);
  memset(&bytes, 0, sizeof(bytes));
  bytes = (unsigned char *)ip_bits;
  snprintf(buffer, sizeof(buffer),"%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x",
    ip_bits[0],ip_bits[1],ip_bits[2],ip_bits[3],
    ip_bits[4],ip_bits[5],ip_bits[6], ip_bits[7],
    ip_bits[8], ip_bits[9], ip_bits[10], ip_bits[11],
    ip_bits[12] ,ip_bits[13], ip_bits[14], ip_bits[15]
  );
  return buffer;
}


char * get_formated_time(){
  char * time__;
  time_t t = time(NULL);
  struct tm __time = *localtime(&t);
  sprintf(time__,"%d-%02d-%02d %02d:%02d:%02d",
          __time.tm_year + 1900,
          __time.tm_mon + 1,
          __time.tm_mday,
          __time.tm_hour,
          __time.tm_min,
          __time.tm_sec);
  return time__;
}