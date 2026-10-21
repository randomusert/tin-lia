#include "io.h"
#include <stdio.h>
#include <fcntl.h>

// Map linux file syscalls to this function
// This is part of the impl for the liblinux.
void fileOpen(char file[], int flags, mode_t mode) {
    open(file, flags, mode);
}