#include <string.h>
#include <stdio.h>
int main(){
  const unsigned char * addr = "\x00\x68\x65\x6c\x6c\x6f\x34\x45\x67";
  const unsigned char * target = "hello";
  const int len = 10;
  char hex_version[len * 2];
  char hex_target[10];
  for(int i = 0; i < len; i++){
    // printf("%X",addr[i]);
    sprintf((hex_version + i * 2),"%02x", addr[i]);
  }
  for(int i = 0; i < 5; i++){
    sprintf(hex_target + i * 2, "%02x", target[i]);
  }
  printf("HEX PKT=%s\nHEX TARGET=%s\n",hex_version,hex_target);
  if(strstr(hex_version,hex_target) != NULL){
    printf("FOUND MATCH\n");
  }
}