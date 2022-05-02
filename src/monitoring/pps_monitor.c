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
#define MAX_PPS_ENTRY       2048
void pps_monitor(){
  // static unsigned long last_pkt_time;
  // static unsigned long  *pkt_times = (unsigned long *)malloc(256);
  static unsigned long pkt_times[MAX_PPS_ENTRY];
  static unsigned int arr_num;
  static int current_log_num;

  if(current_log_num == 0){
    printf("Scanning for previous log files...\n");
    struct dirent * dir;
    DIR * dr = opendir("/usr/share/vigil/stats/pps/");
    if(dr == NULL){
      perror("Failed");
      current_log_num = 0;
    } else {
      while((dir = readdir(dr)) != NULL) current_log_num++;
      current_log_num -= 2; // account for . and ..
    }
    printf("Found %d log files\n",current_log_num++);
    return;
  }


  pkt_times[arr_num++] = (unsigned long)time(NULL);
  if(arr_num == MAX_PPS_ENTRY){
    int linecount = 0;
    if(current_log_num == 0){
        char temp_file_name[64];
      sprintf(temp_file_name,"/usr/share/vigil/stats/pps/pps.log.%d.txt",current_log_num);    
      int linecount = 0;
      char ch;
      FILE * fp = fopen(temp_file_name,"r");
      if(fp == NULL){
        linecount = MAX_PPS_ENTRY;
        goto end;
      }
      while((ch = fgetc(fp)) != EOF){
        if(ch == '\n') linecount++;
      }
      fclose(fp);
      end:;
    }
    
  
    FILE * output;
    char filename[64];
    
    if(linecount >= MAX_PPS_ENTRY){
      sprintf(filename,"/usr/share/vigil/stats/pps/pps.log.%d.txt",++current_log_num);  
      output = fopen(filename,"w");
    } else {
      sprintf(filename,"/usr/share/vigil/stats/pps/pps.log.%d.txt",current_log_num);
      output = fopen(filename,"a");
    }


    
    printf("Dumping to %s\n",filename);
    unsigned long num_arr[24 * current_log_num];
    unsigned int nums[24 * current_log_num];
    int sec_loc = -1;
    unsigned long last_seen = 0;
    for(int i = 0; i < MAX_PPS_ENTRY; i++ ){
      if(last_seen == pkt_times[i]){
        nums[sec_loc]++;
      } else {
        // printf("Here\n");
        last_seen = pkt_times[i];
        num_arr[++sec_loc] = last_seen;
        nums[sec_loc] = 1;   
        nums[sec_loc]++;
      
      }
    }
    for(int i = 0; i < sec_loc; i++){
      fprintf(output,"%lu,%d\n",num_arr[i], nums[i]);
      
    }
    memset(&pkt_times,0,sizeof(pkt_times));
    arr_num = 0;
    fclose(output);
  }

}