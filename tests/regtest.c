#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
struct data{
  unsigned int data1 : 16;
  unsigned int data2 : 16;
  unsigned int data3 : 32;
};

int main(){
  struct data * d = (struct data *)malloc(sizeof(struct data));
  d->data1 = 0x6261;
  d->data2 = 0x6463;
  d->data3 = 0x90676665;
  printf("%s\n",d);

  
}