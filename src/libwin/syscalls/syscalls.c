#include "syscalls.h"

ssize_t sys_write_win(int fd, const void *buf, size_t count) {
    WriteFile((HANDLE)_get_osfhandle(fd), buf, count, NULL, NULL);
}
ssize_t sys_read_win(int fd, void *buf, size_t count) {
    ReadFile((HANDLE)_get_osfhandle(fd), buf, count, NULL, NULL);
}

int s