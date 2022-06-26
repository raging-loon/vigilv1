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
#ifndef ICMPDSCT_H
#define ICMPDSCT_H
#include "../filter/parsing/rule.h"
void ip6_icmp_decode(const unsigned char *, const char *,const char *);
 
void ip4_icmp_decode(const unsigned char * const,struct rule_data *);


#endif /* ICMPDSCT_H */