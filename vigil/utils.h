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
#ifndef UTILS_H
#define UTILS_H
#include <stdint.h>
#include <stdbool.h>

/* x = src
   y = dest
   x and y are interchangeable
   z = target
*/
//! @brief Test if the destination or the source port are a particular value
#define IS_PORT_DEST_SRC(X,Y,Z)(X == Z || Y == Z)
//! @brief Test if the character is in the ASCII range
#define IS_PRINTABLE_ASCII(X)(X > 32 || X < 127)

//! @brief same as ether_ntoa_r in glibc
unsigned char * mac_ntoa(const uint8_t * );

unsigned char * uc_mac_ntoa(unsigned char *);
//! @brief inet_ntoa but for raw bytes instead of a socket
unsigned char * ipv4_ntoa( uint32_t );
unsigned char * u8_ipv4_ntoa(uint8_t * );
//! @brief see ipv4_ntoa but for ipv6
unsigned char * inet6_ntoa(uint8_t * );
//! @brief return a character array with the current time
char * get_formated_time();
//! @brief find the first occurence of a character within a string
int strloc(const char *  haystack,const char needle);
//! @brief Copy the current time in the to character array fiven as an argument
void cb_get_formatted_time(char * );

void fail(const char * , const char *);
bool char_is_printable(const char );
bool test_string_arr_print(const char * );

void hw_addr_to_bytes(const char *, uint8_t *);

int get_num_files(const char *);
bool is_loopback(uint8_t *);
#endif /* UTILS_H */