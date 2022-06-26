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
#ifndef TLSDATA_H
#define TLSDATA_H
#include <stdint.h>
struct tlsd{
  uint8_t content_type;
  unsigned int version: 16;
  uint16_t len;
};

struct tls_handshake{
  uint8_t handshake_type;
  unsigned int length : 24;
  uint16_t version;
  unsigned int random_data[32];
  uint8_t ses_id_len;
  uint16_t cipher_suites_length;
};



#endif /* TLSDATA_H */