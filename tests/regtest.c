#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(){
  char * pkt = "GET %2f%64e%66%61%75lt.%61spx HTTP/1.1\r\nHost: localhost\r\nUser-Agent: Mozilla/5.00 (Nikto/2.1.5) (Evasions:1) (Test:multiple_index)\r\nConnection: Keep-Alive";

  regex_t rgx;
  char re[128];
  strcpy(re,"User-Agent:.*\(.*Nikto.*\).*\(Evasions:.*\).*");
  if(regcomp(&rgx,re,0) != 0){
    printf("Failed to compile\n");
  }
  if(regexec(&rgx,pkt,0,NULL,0) == REG_NOMATCH)
    printf("Failure\n");
  else
    printf("Success\n");
}

