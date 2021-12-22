#ifndef __COLORS_H
#define __COLORS_H

#define __END_COLOR_STREAM          "\033[0m"
#define __TCP_COLOR_NS              "\033[32m"
#define __TCP_SYN                   "\033[35m"
#define __TCP_PSH                   "\033[34m"
#define __TCP_ACK                   "\033[33m"
#define __TCP_RST                   "\033[31m"
#define __TCP_URG                   "\033[36m"
#define __TCP_FIN                   "\033[37m" 
#define __ARP_BOTH                  "\033[3;33m"
#define __FRAGMENTED                "\033[4m"
#define __REG_ICMP_v4_v6            "\033[35m"
#define __UDP_REG                   "\033[96m"
#define __STP                       "\033[94m"

#define BLOCKED_IP_FOUND            __TCP_RST
#endif /* __COLORS_H */