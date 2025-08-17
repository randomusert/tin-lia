#include "client.h"

#if defined(_WIN32) || defined(_WIN64)
    #include "../../libwin/libwin.h"
#elif defined(__linux__)
    #include "../../liblinux/liblinux.h"
#else
    #error "Unsupported platform"
#endif


void clientcmd(void) {
    #if defined(_WIN32) || defined(_WIN64)
        network_client_win();
    #elif defined(__linux__)
        network_client_linux();
    #else
        #error "Unsupported platform"
    #endif
}