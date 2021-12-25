#ifndef NSH_CMD_H
#define NSH_CMD_H

void send_blacklist(int );
void add_to_blacklist(int, const char *);

void get_loaded_rules(int);
void load_new_rule(int,const char *);
void get_rule_matches(int);
#endif /* NSH_CMD_H */