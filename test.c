#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
  char ipv6addr[] = "fe80:0000:0000:0000:0218:0aff:fe87:2ca5";
  char shortaddr[strlen(ipv6addr)];
  char * hextet;
  hextet = strtok(ipv6addr,":");
  int hextets_scanned = 0;
  while(hextet != NULL){
    int num_zeroes = 0;
    
    for(int i = 0; i < strlen(hextet); i++){
      if(hextet[i] == '0')
        num_zeroes++;
      else 
        break;
    }

    if(num_zeroes == 4){
      strcat(shortaddr,"0");
    } else{
      strncat(shortaddr,hextet,num_zeroes +1);
    }


    if(hextets_scanned != 7)
      strcat(shortaddr,":");
    else
      break;
    
    hextets_scanned++;
    hextet = strtok(NULL,":");
  }
  printf("%s\n",shortaddr);
}