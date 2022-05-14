#include "netif.h"
#include <ifaddrs.h>
#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>

v_netif * net_interfaces;


void detect_interfaces(){
  net_interfaces = (v_netif *)malloc(sizeof(v_netif));
  


  struct ifaddrs * ifaces;
  if(getifaddrs(&ifaces) == -1){
    perror("Failed in getifaddrs in netif.c");
    return;
  }

  while(ifaces){
    int addr_family = ifaces->ifa_addr->sa_family;

    if(addr_family == AF_INET || addr_family == AF_INET6){
      
    }
  }
}