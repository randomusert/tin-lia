#include "server.h"

#if defined(_WIN32) || defined(_WIN64)
    #include "../../libwin/libwin.h"
#elif defined(__linux__)
    #include "../../liblinux/liblinux.h"
#else
    #error "Unsupported platform"
#endif

void servercmd(void) {
    #if defined(_WIN32) || defined(_WIN64)
        network_server_win();
    #elif defined(__linux__)
        network_server_linux();
    #else
        #error "Unsupported platform"
    #endif
}