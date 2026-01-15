#include "syscalls.h"

ssize_t sys_write(int fd, const void *buf, size_t count) {
    return syscall(SYS_write, fd, buf, count);
}

ssize_t sys_read(int fd, void *buf, size_t count) {
    return syscall(SYS_read, fd, buf, count);
}
int sys_open(const char *pathname, int flags, mode_t mode) {
    return syscall(SYS_open, pathname, flags, mode);
}

int sys_close(int fd) {
    return syscall(SYS_close, fd);
}
void sys_exit(int status) {
    syscall(SYS_exit, status);
}

pid_t sys_fork(void) {
    return syscall(SYS_fork);
}
int sys_kill(pid_t pid, int sig) {
    return syscall(SYS_kill, pid, sig);
}
int sys_execve(const char *filename, char *const argv[], char *const envp[]) {
    return syscall(SYS_execve, filename, argv, envp);
}
