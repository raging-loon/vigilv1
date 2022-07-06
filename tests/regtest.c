#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_PORTS     128

void get_port_ranges(char *, int * , int *);
void handle_port_range(char *, int *, int *);
int main(){
  char port_range[] = "1,3,14-20";
  int len = 0;
  int * port_ranges = (int *)malloc(sizeof(int) * MAX_PORTS);
  get_port_ranges(port_range,port_ranges,&len);
  // printf();
  for(int i = 0; i < len; i++){
    printf("%d ",port_ranges[i]);
  }
  printf("\n");
  free(port_ranges);
}

void get_port_ranges(char * line, int * arr, int *len){
  char * tok = strtok(line,",");
  while(tok != NULL){
    if(strchr(tok,'-') == NULL){
      int num;
      if(atoi(tok) > 0){
        arr[(*len)++] = atoi(tok);
      }
    } else {
     handle_port_range(tok,arr,len); 
    }

    tok = strtok(NULL,",");  
  }
  
}

void handle_port_range(char * line, int * arr, int * len){
  int start, end;
  char temp_arr[strlen(line) + 1];
  strcpy(temp_arr, line);
  char * tok = strtok(line,"-");
  start = atoi(tok);
  if((tok = strtok(NULL,"-")) != NULL){
    end = atoi(tok);
  } else {
    printf("Failed\n");
  }
  printf("%d %d\n",start,end);
  for(int i = start; i < end + 1; i++){
    arr[(*len)++] = i;
  }
}


