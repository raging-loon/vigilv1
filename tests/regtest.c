#include <stdio.h>
#include <stdlib.h>
#include <string.h>
char * strsplit(char *, char* dlmt);
int main(){

  char array[] = {"close@plt 2910 291b\n"};
  array[strcspn(array,'\n')] = 0;
  char * splar = strsplit(array," ");
  for(int i = 0; i < 100; i++){
    if(strcmp(splar[i],"\x00") == 0){
      break;
    }
    printf("%s\n",splar[i]);
  }
  free(splar);
}


char * strsplit(char * str, char *dlmt){
  char * arr = (char *)malloc(sizeof(str) * 10);
  char * token = strtok(str,dlmt);
  int numtok = 0;
  while(token != NULL){
    strcpy(arr[numtok++],token);
    token = strtok(NULL,dlmt);
  }
  return arr;
}