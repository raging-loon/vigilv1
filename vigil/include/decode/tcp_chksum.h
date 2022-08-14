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
#ifndef TCP_CHKSUM_H
#define TCP_CHKSUM_H
#include "nethdr/tcp.h"
#include "nethdr/ip_hdr.h"
#include <stdbool.h>
bool tcp_check_sum_passed(struct ip_hdr *, struct __tcp *tcp_hdr);


#endif /* TCP_CHKSUM_H */