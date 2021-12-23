#ifndef NSH_SERVER_H
#define NSH_SERVER_H
#include <sys/socket.h>
#include <stdbool.h>
#define NSH_RPC_PORT            111
#define NSH_LOOPBACK            "127.0.0.1"

typedef struct{
  int file_desc;
  struct sockaddr_in * __socket;
} connect_t;

void start_nsh_server();

// thread
static void *actually_start_nsh_server();


static bool nsh_do_login(int);
#endif /* NSH_SERVER_H */ 