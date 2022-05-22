#ifndef __NET_BIOS_H
#define __NET_BIOS_H
#include <stdint.h>
struct netbios_session_status{
  uint8_t msg_type;
  uint8_t length[3];
};



#endif /* __NET_BIOS_H */