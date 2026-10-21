#include "syscalls.h"
#include <errno.h>

#warning "Linux syscall stubs are not implemented"

static long sys_linux_unimplemented(void) {
    errno = ENOSYS;
    return -1;
}

#define LIA_DEFINE_STUB(name) \
    long sys_##name(void) { return sys_linux_unimplemented(); }
LIA_UNIMPLEMENTED_SYSCALLS(LIA_DEFINE_STUB)
#undef LIA_DEFINE_STUB
