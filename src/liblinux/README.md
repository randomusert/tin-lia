# lib linux
this is the linux/unix platform library implementing from the standard c library.

## syscall coverage

`syscalls.h` contains typed wrappers for `read`, `write`, `open`, `close`,
`exit`, `fork`, `kill`, and `execve`. `syscalls_stubs.h` lists the other 377
syscall names present in the x86-64 Linux syscall header on the development
host. Each corresponding `sys_*` function is an explicit placeholder that
returns `-1` and sets `errno` to `ENOSYS`; it does not invoke the kernel.
Building the Linux library emits a warning until these stubs are replaced with
typed implementations.

## building
this library gets built by the root makefile.