#include "utils.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
char * mac_ntoa(const unsigned char * hwaddr, char * buffer, int buffer_size){
  snprintf(buffer, buffer_size, "%.2x:%.2x:%.2x:%.2x:%.2x:%.2x",
      hwaddr[0], hwaddr[1], hwaddr[2], hwaddr[3], hwaddr[4], hwaddr[5]
  );
  return buffer;


}
