lib_LTLIBRARIES = libwin.la
libwin_la_SOURCES = \
    libwin.c libwin.h \
    io/io.c io/io.h \
    syscalls/syscalls.h syscalls/syscalls_stubs.c
libwin_la_LDFLAGS = -version-info 0:0:0 -no-undefined
libwin_la_LIBADD = -lws2_32
