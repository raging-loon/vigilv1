#ifndef __SUSP_H
#define __SUSP_H
#include "../filter/parsing/rule.h"
/* suspicious transmission table */ 
struct sus_trans_table{ 
  struct rule_data info;
  unsigned int time;
};


#endif /* __SUSP_H */