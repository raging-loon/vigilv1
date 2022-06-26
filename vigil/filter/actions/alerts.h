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


#ifndef ALERTS_H
#define ALERTS_H
#include "../parsing/rule.h"
#include <unistd.h>

typedef struct{
  // pid_t pid;
  // uint type;
  long type;
  char data[256];
} ipc_queue_mem;

#define GAM_IPC             0x34
#define GAM_STDOUT          0x35
#define GAM_LOG             0x36


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
// void ipc_shmem_alert(const struct rule_data *, const struct rule *, int);
// write to sqlite db
// void sqlite_alert(const struct rule_data *, const struct rule *, int);

#endif /* ALERTS_H */