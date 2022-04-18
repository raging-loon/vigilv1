#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(int argc, char **argv){
  FILE *cpuinfo = fopen("/proc/cpuinfo", "rb");
  char *arg = 0;
  size_t size = 0;
  int numcpus = 0;
  char to_print[512];
  memset(&to_print,0,sizeof(to_print));
  while(getdelim(&arg, &size, '\n', cpuinfo) != -1){
     if(strncmp("model name",arg,10) == 0){
       int loc = 0;
       for(int i = 0;i < strlen(arg); i++){
         if(arg[i] == ':'){
           loc = i;
           break;
         }
       }
       // printf("%s",arg + loc + 2);
       strcat(to_print,arg + loc + 2);
       numcpus++;
     }
  }
  printf("Found %d cpus:\n%s",numcpus,to_print);
  free(arg);
  fclose(cpuinfo);
  return 0;
}