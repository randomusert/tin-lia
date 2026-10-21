#ifndef LIA_SYSCALLS_STUBS_H
#define LIA_SYSCALLS_STUBS_H

/*
 * These are the x86-64 Linux syscall names not yet covered by a typed
 * wrapper in syscalls.h. The no-argument signatures are placeholders only.
 */
#define LIA_UNIMPLEMENTED_SYSCALLS(X) \
    X(stat) X(fstat) X(lstat) X(poll) X(lseek) X(mmap) X(mprotect) \
    X(munmap) X(brk) X(rt_sigaction) X(rt_sigprocmask) X(rt_sigreturn) \
    X(ioctl) X(pread64) X(pwrite64) X(readv) X(writev) X(access) X(pipe) \
    X(select) X(sched_yield) X(mremap) X(msync) X(mincore) X(madvise) \
    X(shmget) X(shmat) X(shmctl) X(dup) X(dup2) X(pause) X(nanosleep) \
    X(getitimer) X(alarm) X(setitimer) X(getpid) X(sendfile) X(socket) \
    X(connect) X(accept) X(sendto) X(recvfrom) X(sendmsg) X(recvmsg) \
    X(shutdown) X(bind) X(listen) X(getsockname) X(getpeername) \
    X(socketpair) X(setsockopt) X(getsockopt) X(clone) X(vfork) X(wait4) \
    X(uname) X(semget) X(semop) X(semctl) X(shmdt) X(msgget) X(msgsnd) \
    X(msgrcv) X(msgctl) X(fcntl) X(flock) X(fsync) X(fdatasync) \
    X(truncate) X(ftruncate) X(getdents) X(getcwd) X(chdir) X(fchdir) \
    X(rename) X(mkdir) X(rmdir) X(creat) X(link) X(unlink) X(symlink) \
    X(readlink) X(chmod) X(fchmod) X(chown) X(fchown) X(lchown) X(umask) \
    X(gettimeofday) X(getrlimit) X(getrusage) X(sysinfo) X(times) X(ptrace) \
    X(getuid) X(syslog) X(getgid) X(setuid) X(setgid) X(geteuid) \
    X(getegid) X(setpgid) X(getppid) X(getpgrp) X(setsid) X(setreuid) \
    X(setregid) X(getgroups) X(setgroups) X(setresuid) X(getresuid) \
    X(setresgid) X(getresgid) X(getpgid) X(setfsuid) X(setfsgid) X(getsid) \
    X(capget) X(capset) X(rt_sigpending) X(rt_sigtimedwait) \
    X(rt_sigqueueinfo) X(rt_sigsuspend) X(sigaltstack) X(utime) X(mknod) \
    X(uselib) X(personality) X(ustat) X(statfs) X(fstatfs) X(sysfs) \
    X(getpriority) X(setpriority) X(sched_setparam) X(sched_getparam) \
    X(sched_setscheduler) X(sched_getscheduler) X(sched_get_priority_max) \
    X(sched_get_priority_min) X(sched_rr_get_interval) X(mlock) X(munlock) \
    X(mlockall) X(munlockall) X(vhangup) X(modify_ldt) X(pivot_root) \
    X(_sysctl) X(prctl) X(arch_prctl) X(adjtimex) X(setrlimit) X(chroot) \
    X(sync) X(acct) X(settimeofday) X(mount) X(umount2) X(swapon) \
    X(swapoff) X(reboot) X(sethostname) X(setdomainname) X(iopl) X(ioperm) \
    X(create_module) X(init_module) X(delete_module) X(get_kernel_syms) \
    X(query_module) X(quotactl) X(nfsservctl) X(getpmsg) X(putpmsg) \
    X(afs_syscall) X(tuxcall) X(security) X(gettid) X(readahead) \
    X(setxattr) X(lsetxattr) X(fsetxattr) X(getxattr) X(lgetxattr) \
    X(fgetxattr) X(listxattr) X(llistxattr) X(flistxattr) X(removexattr) \
    X(lremovexattr) X(fremovexattr) X(tkill) X(time) X(futex) \
    X(sched_setaffinity) X(sched_getaffinity) X(set_thread_area) \
    X(io_setup) X(io_destroy) X(io_getevents) X(io_submit) X(io_cancel) \
    X(get_thread_area) X(lookup_dcookie) X(epoll_create) X(epoll_ctl_old) \
    X(epoll_wait_old) X(remap_file_pages) X(getdents64) X(set_tid_address) \
    X(restart_syscall) X(semtimedop) X(fadvise64) X(timer_create) \
    X(timer_settime) X(timer_gettime) X(timer_getoverrun) X(timer_delete) \
    X(clock_settime) X(clock_gettime) X(clock_getres) X(clock_nanosleep) \
    X(exit_group) X(epoll_wait) X(epoll_ctl) X(tgkill) X(utimes) X(vserver) \
    X(mbind) X(set_mempolicy) X(get_mempolicy) X(mq_open) X(mq_unlink) \
    X(mq_timedsend) X(mq_timedreceive) X(mq_notify) X(mq_getsetattr) \
    X(kexec_load) X(waitid) X(add_key) X(request_key) X(keyctl) \
    X(ioprio_set) X(ioprio_get) X(inotify_init) X(inotify_add_watch) \
    X(inotify_rm_watch) X(migrate_pages) X(openat) X(mkdirat) X(mknodat) \
    X(fchownat) X(futimesat) X(newfstatat) X(unlinkat) X(renameat) \
    X(linkat) X(symlinkat) X(readlinkat) X(fchmodat) X(faccessat) \
    X(pselect6) X(ppoll) X(unshare) X(set_robust_list) X(get_robust_list) \
    X(splice) X(tee) X(sync_file_range) X(vmsplice) X(move_pages) \
    X(utimensat) X(epoll_pwait) X(signalfd) X(timerfd_create) X(eventfd) \
    X(fallocate) X(timerfd_settime) X(timerfd_gettime) X(accept4) \
    X(signalfd4) X(eventfd2) X(epoll_create1) X(dup3) X(pipe2) \
    X(inotify_init1) X(preadv) X(pwritev) X(rt_tgsigqueueinfo) \
    X(perf_event_open) X(recvmmsg) X(fanotify_init) X(fanotify_mark) \
    X(prlimit64) X(name_to_handle_at) X(open_by_handle_at) X(clock_adjtime) \
    X(syncfs) X(sendmmsg) X(setns) X(getcpu) X(process_vm_readv) \
    X(process_vm_writev) X(kcmp) X(finit_module) X(sched_setattr) \
    X(sched_getattr) X(renameat2) X(seccomp) X(getrandom) X(memfd_create) \
    X(kexec_file_load) X(bpf) X(execveat) X(userfaultfd) X(membarrier) \
    X(mlock2) X(copy_file_range) X(preadv2) X(pwritev2) X(pkey_mprotect) \
    X(pkey_alloc) X(pkey_free) X(statx) X(io_pgetevents) X(rseq) \
    X(uretprobe) X(uprobe) X(pidfd_send_signal) X(io_uring_setup) \
    X(io_uring_enter) X(io_uring_register) X(open_tree) X(move_mount) \
    X(fsopen) X(fsconfig) X(fsmount) X(fspick) X(pidfd_open) X(clone3) \
    X(close_range) X(openat2) X(pidfd_getfd) X(faccessat2) \
    X(process_madvise) X(epoll_pwait2) X(mount_setattr) X(quotactl_fd) \
    X(landlock_create_ruleset) X(landlock_add_rule) X(landlock_restrict_self) \
    X(memfd_secret) X(process_mrelease) X(futex_waitv) \
    X(set_mempolicy_home_node) X(cachestat) X(fchmodat2) X(map_shadow_stack) \
    X(futex_wake) X(futex_wait) X(futex_requeue) X(statmount) X(listmount) \
    X(lsm_get_self_attr) X(lsm_set_self_attr) X(lsm_list_modules) X(mseal) \
    X(setxattrat) X(getxattrat) X(listxattrat) X(removexattrat) \
    X(open_tree_attr) X(file_getattr) X(file_setattr) X(listns) \
    X(rseq_slice_yield)

#define LIA_DECLARE_STUB(name) long sys_##name(void);
LIA_UNIMPLEMENTED_SYSCALLS(LIA_DECLARE_STUB)
#undef LIA_DECLARE_STUB

#endif
