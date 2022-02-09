#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
  char * ipv6addr = "fe80:0000:0000:0000:0218:0aff:fe87:2ca5";
  char shortaddr[strlen(ipv6addr)];
  char * hextet;
  hextet = strtok(ipv6addr,":");
  while(hextet != NULL){
    printf("%s\n",hextet);
    
  }

}