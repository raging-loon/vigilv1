#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void rm_leading_zeroes_ipv6(const char *, char *);
int main(){
  // should turn into fe80::128:0:0:2ca5
  char ipv6addr[] =  "fe80:0000:0000:0000:0218:0000:0000:2ca5";
  char shortaddr[strlen(ipv6addr)];
  rm_leading_zeroes_ipv6((const char *)&ipv6addr,(char *)&shortaddr);
  printf("%s\n",shortaddr);
}

void rm_leading_zeroes_ipv6(const char * ipv6addr, char * dest){
  char * hextet = strtok(ipv6addr,":");
  int hextets_scanned = 0;
  while(hextet != NULL){
    int num_zeroes = 0;
    for(int i = 0; i < strlen(hextet); i++){
      if(hextet[i] == '0')
        num_zeroes++;
      else 
        break;
    }
    if(num_zeroes == 4)
      strcat(dest,"0");
    else
      strcat(dest,hextet + num_zeroes );

    if(hextets_scanned != 7)
      strcat(dest,":");
    else 
      break;

    hextets_scanned++;
    hextet = strtok(NULL,":");
  }
}

void combine_semicolons_ipv6(const char * ipv6addr, char * dest){
  
}