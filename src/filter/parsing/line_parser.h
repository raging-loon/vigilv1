#ifndef LINE_PARSER_H
#define LINE_PARSER_H
#include <stdbool.h>
#include "rule.h"
void line_parser(const char *);

bool isdigit(const char * );
void set_alert_method(struct rule *);
#endif /* LINE_PARSER_H */ 