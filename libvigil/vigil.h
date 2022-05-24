#ifndef VIGIL_H
#define VIGIL_H
#include <stdint.h>
#include <regex.h>
/* RULE STRUCTURES  */
// rule_data is created when a frame is decoded into a packet usually
// this contains everything needed for rulemgr
struct rule_data{
  unsigned char * pkt;                          // packet bytes
  char * src_ip_addr;                           // pointer to src address
  char * dest_ip_addr;                          // pointer to dest address
  uint32_t srcip;                               // may delete
  uint32_t destip;                              // may delete
  int flow;                                     // direction of traffic
  unsigned int src_port;                        // source port
  unsigned int dest_port;                       // destination port
  int __protocol;                               // protocol, see R_ICMP, R_UDP, etc
  int pkt_len;                                  // length of entire packet
  unsigned int dsize;                           // size of packet data(e.g. size of http request)
  const struct ip_hdr * ip_header;              // ip header
  const struct __tcp * tcp_header;              // tcp header
  const struct __icmp4 * icmp_header;           // icmp header
  unsigned char tcp_flags[8];                   // TCP flags in single character for such as
                                                //  "S" for SYN and "A" for ACK
  int is_established;                           // whether or not the tcp session is established
  
};
// Traffic flows
#define FLOW_OUTWARD                            69
#define FLOW_INWARD                             70
#define FLOW_EITHER                             71

// This describes the actual rule that is parsed
struct rule{
  uint32_t src, dest;                           // src/dest in the form of bytes
  int dest_port, src_port;                      // src and dest ports
  
  int flow;                                     // designated flow of traffic
  /*    Traffic flow symbols
      * -> to
      * <> Either
      
    Examples
      $externalnet -> $homenet 
      This means anything from the outside coming in. 
      Flow will be set to FLOW_INWARD

      $homenet -> $externalnet
      This means anything from the inside going out
      Flow will be set to FLOW_OUTWARD

      $externalnet <> $homenet
                 or
      $homenet <> $externalnet
      This means either, in to out or out to in
      Flow will be set to FLOW_EITHER 
  */
  unsigned int offset;                          // How far into the packet to start searching
  int dsize;                                    // size of packet
  int d_operator;                               // internal operator for dsize, will be an opcode
  char rulename[24];                            // *optional* rulename
  char rule_taret[255];                         // actual taret of the rule
  int protocol;                                 // protocol of the rule, equivalent to rule_data's __protocol
  int port;                                     // optional port
  // TODO: ADD PORT RANGES
  bool noencrypt;                               // This is set to ignore encrypted traffic that is detected
                                                // through watching for TLS/SSL handshakes
  int severity;                                 // severity of rule, maybe removed
  char message[128];                            // what to print or send when the rule is matched
  regex_t pcre;                                 // Compiled regex
  char pcrestr[128];                            // Regex string
  bool uses_pcre; 
  char raw_target[128];                         // unitialized target characters
  int is_established;                           // only applicable for TCP sessions
  int depth;                                    // where to stop looking in the packet
  struct r_tcp_data tcp_data;
  struct r_raw_ip_data ip_data;
  struct r_icmp_dataset icmp_data;
  bool(*pkt_parser)(const struct rule_data *, const struct rule *);
  void(*action)(const struct rule_data *, const struct rule *, int);
};

// Data sets for struct rule
// ICMP Data
struct r_icmp_dataset{
  bool typeset, codeset, seqset, idset;
  uint8_t type;
  uint8_t code;
  uint16_t seq;
  uint16_t id;
};
// TCP Data
struct r_tcp_data{
  bool flagset, ackset, seqset;
  unsigned char flags[8];
  uint16_t ack;
  uint32_t seq;
  uint16_t res1;                                // Reserved bits
};
// RAW IP Data
struct r_raw_ip_data{
  bool tosset, ttlset, protoset;
  uint8_t tos;
  uint8_t ttl;
  uint8_t proto;                                // Protocol number
};

struct spi_member{
  // fill in
};




#endif /* VIGIL_H */