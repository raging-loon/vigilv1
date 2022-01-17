#ifndef FLAGS_H
#define FLAGS_H

/* TCP FLAGS */ 
#define NE_TCP_END_CONNECT_FA           0x6001
#define NE_TCP_CONNECT_INIT             0x6002
#define NE_TCP_CONNECT_P2               0x6003
#define NE_TCP_CONNECT_P3               0x6004
#define NE_TCP_END_CONNECT_FORCE        0xbeef
#define NE_TCP_SEND_DATA                0x6005
#define NE_TCP_RST                      0x6006
#define NE_TCP_NO_FLAGS                 0x6007
#define NE_TCP_EXCESS_FLAGS             0x6008
/* IPv4 FLAGS*/ 
#define IPv4_IS_FRAGMENT                0x8007

/* ICMP FLAGS */ 
#define ICMPv4_EXCESS_LENGTH            0x3003


/* DETECTION FLAGS */
#define VULN_SCAN                       0x1001
#define EXPLOIT_KIT                     0x1002
#endif /* FLAGS_H */ 