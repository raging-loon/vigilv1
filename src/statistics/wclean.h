#ifndef W_CLEAN_H
#define W_CLEAN_H
#include "watchlist.h"

#define CLEAN_DELAY   86400


int ready_for_clean(const struct watchlist_member *);

void clean(struct watchlist_member *);

void scan_for_clean();

void is_ready_for_clean();

#endif /* W_CLEAN_H */ 