#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(){
  char * pkt = "User-Agent: Mozilla/5.00 (Nikto/2.1.5) (Evasions:None) (Test:Port Check)";
//
  regex_t rgx;
  char re[128];
  strcpy(re,"User-Agent:.*\(.*Nikto.*\).*\(Evasions:.*\)");
  if(regcomp(&rgx,re,0) != 0){
    printf("Failed to compile\n");
  }
  if(regexec(&rgx,pkt,0,NULL,0) == REG_NOMATCH)
    printf("Failure\n");
  else
    printf("Success\n");
}

