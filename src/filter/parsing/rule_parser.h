#ifndef RULE_PARSER_H
#define RULE_PARSER_H
#include "rule.h"
// find paths for rules in the config file
void rule_library_parser(const char *);
// find rules in the rule file
void rule_parser(const char *);
void deny_conf_parser(char *);
void host_mon_parser();
// void test_main();
static void get_protocol(const char *, struct rule * );
#endif /* RULE_PARSER_H */ 