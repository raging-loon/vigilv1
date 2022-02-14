/*!
 * @file colors.h
 * @author Conner Macolley
 * @brief Define ASCII escape sequence for printing in color
 * @section LICENSE
 * 
 *
 * Copyright 2021 Conner Macolley
 *
 *    Licensed under the Apache License, Version 2.0 (the "License");
 *    you may not use this file except in compliance with the License.
 *    You may obtain a copy of the License at
 *
 *        http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Unless required by applicable law or agreed to in writing, software
 *    distributed under the License is distributed on an "AS IS" BASIS,
 *    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *    See the License for the specific language governing permissions and
 *    limitations under the License.
 *
 *  @section DESCRIPTION
 *  Define ASCII escape sequence for printing in color
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