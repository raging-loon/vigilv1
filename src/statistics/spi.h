#ifndef SPI_H
#define SPI_H

#include <stdint.h>
#include "watchlist.h"

struct w_tcp_session{
  unsigned int start;
  unsigned int end;
  unsigned int length;
  int progress;
  uint16_t end_flags;
};





struct tcp_watchdog{
  struct watchlist_member * w;
  unsigned int twh_completed;
  struct w_tcp_session tcp_sessions[50];

};


#endif /* SPI_H */


