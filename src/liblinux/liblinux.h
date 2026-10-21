#ifndef liblinux_h
#define liblinux_h
#include <stdio.h>
#include <sys/socket.h>
void liblinux_init(void);
int network_client_linux(void);
int network_server_linux(void);

#endif