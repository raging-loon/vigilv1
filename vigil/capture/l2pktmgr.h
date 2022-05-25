#ifndef L2_PKT_MGR
#define L2_PKT_MGR
#include <pcap.h>

/********************************
 *       Layer 2 Protocols      *
 *                              * 
 * - ARP                        *
 * - STP                        *
 ********************************/  

void arpdecode(const unsigned char*, const int len);


void loopback_ctp_decode(const unsigned char *);


#endif /* L2_PKT_MGR */