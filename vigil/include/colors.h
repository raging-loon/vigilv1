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