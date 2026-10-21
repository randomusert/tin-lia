# libwin

## syscall coverage

The Windows platform library exposes basic placeholders for the syscall APIs
declared in `syscalls.h`. These functions return `-1` and set `errno` to
`ENOSYS`, except `sys_exit`, which returns after setting `errno`. They do not
invoke Windows system calls. Building the library emits a warning until these
stubs are replaced with Windows implementations.
