#ifndef __LLDP_H
#define __LLDP_H
#include <stdint.h>
struct chassis_subtype{
  uint16_t tlv_info;
  uint16_t chassis_id_subtype
  uint8_t chassis_id[6];
};



struct lldp_type_1{
  struct chassis_subtype chassis_info;
  
};




#endif __LLDP_H