#include <stdio.h>
#include <stdlib.h>

unsigned char *packet = "HEAD / HTTP/1.1\r\nHost: scanme.nmap.org\r\nUser-Agent: curl/7.68.0\r\nAccept: */*\r\n";

// 48454144202f20485454502f312e310d0a486f73743a207363616e6d652e6e6d61702e6f72670d0a557365722d4167656e743a206375726c2f372e36382e300d0a4163636570743a202a2f2a0d0a
int main(){
  unsigned int pkt_len = 86;
  unsigned int offset = 15;
  char temp_pkt[(pkt_len * 2) + 2];
  int chars_filled = 0;
  for(int i = offset; i < pkt_len; i++){
    sprintf(temp_pkt + chars_filled++ * 2, "%02x",packet[i]);
    // printf("%c\n",packet[i]);
  }
  printf("%s\n",temp_pkt);
}