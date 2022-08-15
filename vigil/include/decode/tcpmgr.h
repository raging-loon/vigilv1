/*     
    This file is part of Vigil.

    Vigil is free software: you can redistribute it and/or modify it under the terms of the 
    GNU General Public License as published by the Free Software Foundation, either version 3 
    of the License, or (at your option) any later version.

    Vigil is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; 
    without  even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
    See the GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along with Vigil. 
    If not, see <https://www.gnu.org/licenses/>. 

*/
#ifndef TCPMGR_H
#define TCPMGR_H
#include <pcap.h>
#include "engine/rule/rule.h"

#define PSH_ACK_SET(X,Y) (X && Y)
#define FIN_ACK_SET(X,Y) (X && Y)
#define SYN_ACK_SET(X,Y) (X && Y)
#define RST_ACK_SET(X,Y) (X && Y)
void ip6_tcp_decode(const unsigned char * pkt, struct rule_data * rdata, const int len);

void ip4_tcp_decode(const unsigned char * pkt, struct rule_data * rdata, const int len);


#endif /* TCPMGR_H */