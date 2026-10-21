#ifndef SYSCALLS_H
#define SYSCALLS_H
#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif
#include <unistd.h>
#include <sys/syscall.h>
#include <stdint.h>
#include <sys/types.h>

ssize_t sys_write(int fd, const void *buf, size_t count);
ssize_t sys_read(int fd, void *buf, size_t count);
int sys_open(const char *pathname, int flags, mode_t mode);
int sys_close(int fd);
void sys_exit(int status);
pid_t sys_fork(void);
int sys_kill(pid_t pid, int sig);
int sys_execve(const char *filename, char *const argv[], char *const envp[]);

#include "syscalls_stubs.h"

#endif // SYSCALLS_H