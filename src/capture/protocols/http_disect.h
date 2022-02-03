#ifndef HTTP_DISECT_H
#define HTTP_DISECT_H
#include "../../filter/parsing/rule.h"

void http_disect(const unsigned char *, const struct rule_data *);


void * full_http_disect(const unsigned char *, const struct rule_data *);


#endif /* HTTP_DISECT_H */ 