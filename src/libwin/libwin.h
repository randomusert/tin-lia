#ifndef LIBWIN_H
#define LIBWIN_H
#include <stdio.h>
#include <winsock2.h>
#include <ws2tcpip.h>


// use winsocks for networking
void network_client_win(void);
void network_server_win(void);
#endif