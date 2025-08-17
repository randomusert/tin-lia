#include "liblia/liblia.h"

#ifdef WIN32
#include "libwin/libwin.h"
#elif defined(__linux__)
#include "liblinux/liblinux.h"
#endif

int main(void) {
    // Platform-specific initialization
#ifdef WIN32
    printf("Initializing Windows library...\n");
#elif defined(__linux__)
    liblinux_init();
#endif

    // Common library init
    liblia_init();

    return 0;
}
