#ifndef TCP_CHKSUM_H
#define TCP_CHKSUM_H
#include "../../packets/tcp.h"
#include "../../packets/ip_hdr.h"
#include <stdbool.h>
bool tcp_check_sum_passed(struct ip_hdr *, unsigned short *tcp_hdr);


#endif /* TCP_CHKSUM_H */