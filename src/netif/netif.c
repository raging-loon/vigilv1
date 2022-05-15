#include "netif.h"
#include <ifaddrs.h>
#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netdb.h>
v_netif * net_interfaces;


void detect_interfaces(){
  struct ifaddrs * ifaces;
  if(getifaddrs(&ifaces) == -1){
    perror("Failed in getifaddrs in netif.c");
    return;
  }
  net_interfaces = (v_netif *)malloc(sizeof(v_netif));
  int iface_detected = 0;


  struct ifaddrs * n_addr_ptr = ifaces;
  while(n_addr_ptr){
    int addr_family = n_addr_ptr->ifa_addr->sa_family;

    if(addr_family == AF_INET || addr_family == AF_INET6){
      if(iface_detected != 0){
        
        net_interfaces = (v_netif *)realloc(net_interfaces,sizeof(net_interfaces) * iface_detected);
      }
      v_netif * current_iface = (v_netif*)&net_interfaces[iface_detected];
      
      current_iface->a_family = addr_family;
      strcpy(&current_iface->if_name,n_addr_ptr->ifa_name);
      getnameinfo(n_addr_ptr->ifa_addr,
                  addr_family == AF_INET ? sizeof(struct sockaddr_in) : sizeof(struct sockaddr_in6),
                  current_iface->address,
                  sizeof(current_iface->address),
                  0,0, NI_NUMERICHOST
                  );
      
      iface_detected++;
    }
    n_addr_ptr = n_addr_ptr->ifa_next;
    
  }
  freeifaddrs(ifaces);
}

void free_iface(){
  free(net_interfaces);
}