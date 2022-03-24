#ifndef TCP_CHKSUM_H
#define TCP_CHKSUM_H
#include "../../packets/tcp.h"

#include <stdbool.h>
bool tcp_check_sum_passed(struct __tcp *, int size);


#endif /* TCP_CHKSUM_H */