#ifndef VWEBSERV_H
#define VWEBSERV_H


void start_web_server();
void * start_web_server_thrd();


#ifdef FUNCTIONALITY_TEST

int main(int argc, char ** argv);
#endif

#endif /* VWEBSERV_H */