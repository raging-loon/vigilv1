/*
 * Copyright 2021-2022 Conner Macolley
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
 */


#ifndef TCPMGR_H
#define TCPMGR_H
#include <pcap.h>
#include "../filter/parsing/rule.h"

#define PSH_ACK_SET(X,Y) (X && Y)
#define FIN_ACK_SET(X,Y) (X && Y)
#define SYN_ACK_SET(X,Y) (X && Y)
#define RST_ACK_SET(X,Y) (X && Y)
void ip6_tcp_decode();

void ip4_tcp_decode(const unsigned char *,struct rule_data *,const struct pcap_pkthdr *);


#endif /* TCPMGR_H */