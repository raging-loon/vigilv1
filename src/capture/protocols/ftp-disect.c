#include "ftp-disect.h"
#include <string.h>
#include "../../statistics/watchlist.h"
#include "../../../globals.h"
#include <stdio.h>
void ftp_disect(const char * pkt, const struct rule_data * rdata){
  if(strstr(pkt,"Login incorrect") != NULL || strstr(pkt,"login incorrect") != NULL){
    struct watchlist_member * w  = &watchlist[member_exists(rdata->dest_ip_addr)];
    w->failed_ftp_login_attempts++;
    if(w->failed_ftp_login_attempts >= 5){
      printf("Possible FTP brute force attempt:"
            " %s(suspect) -> %s. %d failed logins\n",
            rdata->dest_ip_addr,rdata->src_ip_addr,w->failed_ftp_login_attempts);
    }
  }
}