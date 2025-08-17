#ifndef CLIENT_H
#define CLIENT_H
#if defined(_WIN32) || defined(_WIN64)
    #include "../../libwin/libwin.h"
#elif defined(__linux__)
    #include "../../liblinux/liblinux.h"
#else
    #error "Unsupported platform"
#endif
void clientcmd(void);
#endif // CLIENT_H