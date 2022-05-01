/*
* Copyright 2021-2022 Conner Macolley
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
#include "monitoring.h"
#include <pcap.h>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#define MAX_PPS_ENTRY       128
void pps_monitor(unsigned char * user, const struct pcap_pkthdr * pkt_hdr, const unsigned char * pkt){
  // static unsigned long last_pkt_time;
  // static unsigned long  *pkt_times = (unsigned long *)malloc(256);
  static unsigned long pkt_times[MAX_PPS_ENTRY];
  static unsigned int arr_num = 0;
  pkt_times[arr_num++] = (unsigned long)time(NULL);
  if(arr_num == MAX_PPS_ENTRY){
    struct dirent * dir;
    int f_num = 0;
    DIR * dr = opendir("/usr/share/vigil/stats/pps/");
    if(dr == NULL){
      // add alert here
      return;
    }
    while((dir = readdir(dr)) != NULL){
      f_num++;
    }
    f_num -= 2; // account for "." and ".."
    // 20 = name of file, 27 = director name
    char filename[20 + 27];
    sprintf(filename,"/usr/share/vigil/stats/pps/pps.log.%d.txt",f_num); 

    FILE * fp = fopen(filename,"a");
    if(fp == NULL){
      perror("Error opening file");
      return;
    }
    printf("Dumping to %s\n",filename);
    unsigned int inbtwn_times[128];
    unsigned int subtime = 0;
    for(int i = arr_num; i != 0; ){
      inbtwn_times[subtime++] = pkt_times[i] - pkt_times[i--];
      if(i == 0) break;
    }
    for(int i = 0; i < subtime; i++){
      fprintf(fp,"%lu,%d",pkt_times[i],inbtwn_times[i]);
    }
    memset(&pkt_times,0,sizeof(pkt_times));
    arr_num = 0;
  }

}