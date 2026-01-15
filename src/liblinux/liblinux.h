#ifndef liblinux_h
#define liblinux_h
#include <stdio.h>
#include <sys/socket.h>
void liblinux_init(void);
void network_client_linux(void);
void network_server_linux(void);

#endif