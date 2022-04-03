#ifndef SCAN_ENGINE_H
#define SCAN_ENGINE_H

/*
  Engine for detected different types of scans:

*/
#define MAX_PER_DS          30

struct data_set{
  unsigned long ds_times[MAX_PER_DS];
};
// scan-engine-data-set-collection
struct se_dsc{
  
};

#endif /* SCAN_ENGINE_H */