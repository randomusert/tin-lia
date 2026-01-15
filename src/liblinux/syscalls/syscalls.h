#ifndef SYSCALLS_H
#define SYSCALLS_H
#include <unistd.h>
#include <sys/syscall.h>
#include <stdint.h>
#include <sys/types.h>

// Define syscall numbers for x86_64 if not defined
#define SYS_write 1
#define SYS_read 0
#define SYS_open 2
#define SYS_close 3
#define SYS_exit 60
#define SYS_fork 57
#define SYS_kill 62
#define SYS_execve 59


ssize_t sys_write(int fd, const void *buf, size_t count);
ssize_t sys_read(int fd, void *buf, size_t count);
int sys_open(const char *pathname, int flags, mode_t mode);
int sys_close(int fd);
void sys_exit(int status);
pid_t sys_fork(void);
int sys_kill(pid_t pid, int sig);
int sys_execve(const char *filename, char *const argv[], char *const envp[]);


#endif // SYSCALLS_H