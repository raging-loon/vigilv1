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