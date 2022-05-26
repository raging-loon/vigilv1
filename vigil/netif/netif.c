#include "netif.h"
#include <ifaddrs.h>
#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../capture/pktmgr.h"
#include <sys/socket.h>
#include <dirent.h>
#include <signal.h>
#include "../backtrace/backtrace.h"
#include "../globals.h"
#include <arpa/inet.h>
#include <linux/if_ether.h>
#include <netdb.h>
#include <netinet/in.h>
v_netif * net_interfaces;
int iface_detected = 0;
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
      if(dir->d_name[0] == '.')
        continue;
      
      strcpy(iface->if_name,dir->d_name);
      printf("Found %s\n",iface->if_name);
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
    // printf("%s %s\n",name, net_interfaces[i].if_name);
    if(strcmp(net_interfaces[i].if_name,name) == 0)
      return i;
  }
  return -1;
}
void start_interface_cap(const char * iface){
  pthread_t pthrd;
  add_thread(&pthrd);
  // sigset_t set;
  // sigemptyset(&set);
  // sigaddset(&set,SIGSEGV);
  // pthread_sigmask(SIG_BLOCK,&set,NULL);
  pthread_create(&pthrd,NULL,(void*)&start_interface_cap_ex,(void*)iface);
  pthread_join(pthrd,NULL);
}

void start_interface_cap_ex(void * __iface){
  char * iface = (char *)__iface;
  int loc;

  if((loc = iface_exists(iface)) == -1){
    printf("Interface %s does not exist\n",iface);
    return;
  }
  v_netif * v_iface = &net_interfaces[loc];
  

  v_iface->fd = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
  if(v_iface->fd < 0){
    perror("Socket error");
    return;
  }
  setsockopt(v_iface->fd, SOL_SOCKET, 25, iface, strlen(iface) + 1);
    
  
  v_iface->thrd_id = pthread_self();
  
  int len;
  int saddr_sz;
  struct sockaddr saddr;
  
  char buffer[2048] = {0};
  signal(SIGSEGV,crash_handler);

  while(1){
    len == recvfrom(v_iface->fd,buffer, sizeof(buffer), 0, &saddr,(socklen_t *)&saddr_sz);
    if(len < 0) break;
    pktmgr(v_iface->if_name,len,buffer);
    memset(&buffer,0,sizeof(buffer));
  }
  // free(buffer);
}