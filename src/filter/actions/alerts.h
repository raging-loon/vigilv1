#ifndef ALERTS_H
#define ALERTS_H
#include "../parsing/rule.h"


void format_msg(const struct rule_data*, const struct rule *, char * restrict);

// print to screen
void stdout_alert(const struct rule_data*, const struct rule *, int);
// write to log
void log_alert(const struct rule_data*,const struct rule*, int);
// write to socket fd
void raw_socket_alert(const struct rule_data *, const struct rule *, int);
// write to ipc pipe
void ipc_msg_alrt(const struct rule_data *, const struct rule *, int);
// write to shared memory
void ipc_shmem_alert(const struct rule_data *, const struct rule *, int);
// write to sqlite db
// void sqlite_alert(const struct rule_data *, const struct rule *, int);

#endif /* ALERTS_H */