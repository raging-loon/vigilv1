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

#ifndef PACKET_PARSER_H
#define PACKET_PARSER_H
#include <stdbool.h>
#include "engine/rule/rule.h"

bool str_match_parser(const struct rule_data *, const struct rule *);

// not necessarily a packet parser but belongs here
bool is_blocked_ipv4(const char *);

bool none(const struct rule_data * , const struct rule *);

bool pcre_match(const struct rule_data *, const struct rule *);

#endif /* PACKET_PARSER_H */