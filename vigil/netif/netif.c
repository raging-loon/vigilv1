#include "netif.h"
#include <ifaddrs.h>
#include <sys/types.h>
#include <stdlib.h>

#include <stdio.h>
#include <string.h>
#include "../capture/pktmgr.h"
#include "../utils.h"
#include <sys/socket.h>
#include <dirent.h>
#include <signal.h>
#include "../backtrace/backtrace.h"
#include "../globals.h"
#include <arpa/inet.h>
#include <linux/netlink.h>
#include <linux/if_ether.h>
#include <sys/ioctl.h>
#include <linux/if.h>
#include <netdb.h>
#include <linux/if_packet.h>
#include <netinet/in.h>
#define NI_NUMERICHOST 1
#define SO_BINDTODEVICE 25
v_netif * net_interfaces;
int iface_detected = 0;
void detect_interfaces(){
  int num_dirs = num_f_in_dir("/sys/class/net/");
  if(num_dirs == -1){
    perror("failed to open directory");
    exit(-1);
  }
  net_interfaces = (v_netif *)malloc(sizeof(v_netif) * num_dirs);
  iface_detected = 0;
  struct dirent * dir;
  DIR * dr = opendir("/sys/class/net/");
  
  if(dr == NULL){
    perror("Failed");
    exit(-1);
  } else {
    while((dir = readdir(dr)) != NULL){
      
      v_netif * iface = &net_interfaces[iface_detected];
      if(dir->d_name[0] == '.')
        continue;
      
      strcpy(iface->if_name,dir->d_name);
      iface->addr_set = 0;
      printf("Found %s\n",iface->if_name);
      iface_detected++;
    }
  }
  
  closedir(dr); 
  gather_iface_addrs();
  gather_iface_hw_addrs();
  print_iface_summary();
}

// TODO: Account for IPv6 networks
void gather_iface_addrs(){
  struct ifaddrs * addrs;
  if(getifaddrs(&addrs) == -1){
    perror("getifaddrs");
    return;
  }
  struct ifaddrs * addr_ptr = addrs;
  while(addr_ptr){
    if(addr_ptr->ifa_addr->sa_family == AF_INET || addr_ptr->ifa_addr->sa_family == AF_INET6){
      int loc;

      if((loc = iface_exists(addr_ptr->ifa_name)) != -1){
        v_netif * iface = &net_interfaces[loc];
        if(iface->addr_set == 0){
          const int f_size = addr_ptr->ifa_addr->sa_family == 
                              AF_INET ? sizeof(struct sockaddr_in) :
                                        sizeof(struct sockaddr_in6);
          // vscode will give a syntax error for NI_NUMERICHOST, but there is none
          char t_addr[100];
          getnameinfo(addr_ptr->ifa_addr,f_size,t_addr, sizeof(t_addr),0, 0,NI_NUMERICHOST);

          strcpy(iface->address,t_addr);
          printf("%s -> %s\n", iface->if_name,t_addr);
          iface->addr_set = 1;
        }
      }
    }
    addr_ptr = addr_ptr->ifa_next;
  }
  freeifaddrs(addrs);
}

void gather_iface_hw_addrs(){
  for(int i = 0; i < iface_detected; i++){
    v_netif * net_if = &net_interfaces[i];
    char filename[64 + 256];
    char * temp_mac_addr = NULL;
    size_t len;
    sprintf(filename,"/sys/class/net/%s/address",net_if->if_name);
    FILE * fp = fopen(filename,"r");
    if(fp == NULL){
      printf("Failed to get address of %s\n",net_if->if_name);
      exit(EXIT_FAILURE);
    }
    getline(&temp_mac_addr,&len,fp);
    hw_addr_to_bytes(temp_mac_addr,net_if->mac_addr);

  }
}
void free_iface(){
  free(net_interfaces);
  // for(int i = 0; i < iface_detected; i++)
  //   free(&net_interfaces[i]);
  
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
  struct ifreq ifr;
  memset(&ifr, 0, sizeof(ifr));
  strncpy(ifr.ifr_name,iface,strlen(iface) + 1);
  
  v_iface->fd = socket(PF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
  // v_iface->fd = socket(PF_RAW, SOCK_RAW, RAWPROTO_SNOOP);
  if(v_iface->fd < 0){
    perror("Socket error");
    return;
  }
  if((ioctl(v_iface->fd,SIOCGIFINDEX, &ifr)) == -1){
    perror("ioctl");
    return;
  }

  if(setsockopt(v_iface->fd, SOL_SOCKET, SO_BINDTODEVICE, (void*)&ifr, sizeof(ifr)) < 0){
    perror("setsockopt");
    return;
  }
    
  
  v_iface->thrd_id = pthread_self();
  
  int len;
  int saddr_sz;
  struct sockaddr saddr;
  
  unsigned char buffer[1600] = {0};
  signal(SIGSEGV,crash_handler);

  while(1){
    len = recvfrom(v_iface->fd,&buffer, 1600, 0, &saddr,(socklen_t *)&saddr_sz);
    // printf("%d\n",len);
    pktmgr(v_iface->if_name,len,&buffer);
    memset(&buffer,0,sizeof(buffer));
    continue;
  }

  // free(buffer);
}

bool interface_operational(const char * iface){
  char filename[40 + 1];
  sprintf(filename,"/sys/class/net/%s/operstate",iface);
  FILE * fp = fopen(filename,"r");
  if(fp == NULL){
    printf("Failed to detect interface operational state\n");
    fclose(fp);

    return false;
  }
  char * state = NULL;
  size_t len = 0;
  getline(&state,&len,fp);
  fclose(fp);

  if(strcmp(state,"up") == 0)
    return true;
  return false;
}  


void print_iface_summary(){
  for(int i = 0; i < iface_detected; i++){
    v_netif * net_if = &net_interfaces[i];
    printf("%s: %s %s",net_if->if_name,net_if->address,mac_ntoa(net_if->mac_addr));
  }
}


int num_f_in_dir(const char * directory){
  struct dirent * dir;
  DIR * dr = opendir(directory);
  if(dr == NULL) return -1;

  int num_files = 0;
  while((dir = readdir(dr)) != NULL) num_files++;

  return num_files - 2;
  
}