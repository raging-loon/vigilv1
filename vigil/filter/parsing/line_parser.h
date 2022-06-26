/*     
    This file is part of Vigil.

    Vigil is free software: you can redistribute it and/or modify it under the terms of the 
    GNU General Public License as published by the Free Software Foundation, either version 3 
    of the License, or (at your option) any later version.

    Foobar is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; 
    without  even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
    See the GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along with Foobar. 
    If not, see <https://www.gnu.org/licenses/>. 

*/


#ifndef LINE_PARSER_H
#define LINE_PARSER_H
#include <stdbool.h>
#include "rule.h"
void line_parser(const char *);

bool str_isdigit(const char * );

void set_alert_method(struct rule *);
#endif /* LINE_PARSER_H */ 