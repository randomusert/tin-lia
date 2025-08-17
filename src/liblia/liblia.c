#include "liblia.h"
#include "../liblinux/liblinux.h"
#include "../libwin/libwin.h"

void liblia_init(void) {
    // Initialization code for the library can be added here.
    // For now, we just print a message to indicate that the library has been initialized.
    #if defined(__linux__)
    liblinux_init();
    #elif defined(__WIN32)
    libwin_init();
    #endif
    
    printf("liblia initialized.\n");
}