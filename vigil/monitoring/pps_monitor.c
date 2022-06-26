/*     
    This file is part of Vigil.

    Vigil is free software: you can redistribute it and/or modify it under the terms of the 
    GNU General Public License as published by the Free Software Foundation, either version 3 
    of the License, or (at your option) any later version.

    Vigil is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; 
    without  even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
    See the GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along with Vigil. 
    If not, see <https://www.gnu.org/licenses/>. 

*/
#include "monitoring.h"
#include <pcap.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#define MAX_PPS_ENTRY      1024
#define MAX_PPS_LOG_ENTRY  600
void pps_monitor(){
  // static unsigned long last_pkt_time;
  // static unsigned long  *pkt_times = (unsigned long *)malloc(256);
  static unsigned long pkt_times[MAX_PPS_ENTRY];
  static unsigned int arr_num;
  static int current_log_num;
  static int lines_written;

  if(current_log_num == 0){
    lines_written = 0;
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
    closedir(dr);

    printf("Found %d log files\n",current_log_num);
    
    
    current_log_num++;
    arr_num = 0;
    return;
  }


  if(arr_num == MAX_PPS_ENTRY){
    FILE * output;
    char filename[64];
    
    if(lines_written >= MAX_PPS_LOG_ENTRY){
      sprintf(filename,"/usr/share/vigil/stats/pps/pps.log.%d.txt",++current_log_num);  

      output = fopen(filename,"w");
    } else {
      sprintf(filename,"/usr/share/vigil/stats/pps/pps.log.%d.txt",current_log_num);
      output = fopen(filename,"a");
    }


    // printf("%d\n",lines_written);
    // printf("Dumping to %s\n",filename); // for debugging
    unsigned long  *num_arr = (unsigned long *)malloc(256*sizeof(unsigned long));
    unsigned int   *nums    =  (unsigned int *)malloc(128*sizeof(unsigned int));
    int sec_loc = -1;
    long last_seen = 0;
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
      // fprintf(stdout,"%lu,%d\n",num_arr[i],nums[i]);
    }
    free(num_arr);
    free(nums);
    memset(&pkt_times,0,sizeof(pkt_times));
    
    if(lines_written >= MAX_PPS_LOG_ENTRY){
      lines_written = 0;
      current_log_num++;
    }
    else lines_written += sec_loc;
    arr_num = 0;
    fclose(output);
  }
  // printf("Before memory corruption\n");
  pkt_times[arr_num++] = (unsigned long)time(NULL);


}