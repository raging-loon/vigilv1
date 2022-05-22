#include "netif.h"
#include <ifaddrs.h>
#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <dirent.h>
#include <arpa/inet.h>
#include <netdb.h>
v_netif * net_interfaces;
int iface_detected;
void detect_interfaces(){
  net_interfaces = (v_netif *)malloc(sizeof(v_netif));
  iface_detected = 0;
  struct dirent * dir;
  DIR * dr = opendir("/sys/class/net/");
  
  if(dr == NULL){
    perror("Failed");
    exit(-1);
  } else {
    while((dir = readdir(dr)) != NULL){
      if(iface_detected != 0){
        net_interfaces = (v_netif *)realloc(net_interfaces,sizeof(net_interfaces) * iface_detected);
      }
      
      v_netif * iface = &net_interfaces[iface_detected];
      if(strcmp(dir->d_name,".") ==0 || strcmp(dir->d_name,"..") == 0)
        continue;
      strcpy(iface->if_name,dir->d_name);
      iface_detected++;
    }
  }
  
  closedir(dr); 
}

void free_iface(){
  free(net_interfaces);
}

int iface_exists(const char * name){
  for(int i = 0; i < iface_detected; i++){
    if(strcmp(net_interfaces[i].if_name,name) == 0)
      return i;
  }
  return -1;
}