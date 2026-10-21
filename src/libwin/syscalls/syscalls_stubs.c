#include "syscalls.h"
#include <errno.h>

#warning "Windows syscall stubs are not implemented"

ssize_t sys_write(int fd, const void *buf, size_t count) {
    (void)fd;
    (void)buf;
    (void)count;
    errno = ENOSYS;
    return -1;
}

ssize_t sys_read(int fd, void *buf, size_t count) {
    (void)fd;
    (void)buf;
    (void)count;
    errno = ENOSYS;
    return -1;
}

int sys_open(const char *pathname, int flags, mode_t mode) {
    (void)pathname;
    (void)flags;
    (void)mode;
    errno = ENOSYS;
    return -1;
}

int sys_close(int fd) {
    (void)fd;
    errno = ENOSYS;
    return -1;
}

void sys_exit(int status) {
    (void)status;
    errno = ENOSYS;
}

pid_t sys_fork(void) {
    errno = ENOSYS;
    return (pid_t)-1;
}

int sys_kill(pid_t pid, int sig) {
    (void)pid;
    (void)sig;
    errno = ENOSYS;
    return -1;
}

int sys_execve(const char *filename, char *const argv[], char *const envp[]) {
    (void)filename;
    (void)argv;
    (void)envp;
    errno = ENOSYS;
    return -1;
}
