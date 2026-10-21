lib_LTLIBRARIES = liblia.la
liblia_la_SOURCES = \
    liblia.c liblia.h \
    commands/client.c commands/client.h \
    commands/server.c commands/server.h \
    commands/test.c commands/testcmd.h
liblia_la_LDFLAGS = -version-info 0:0:0 -no-undefined

if BUILD_LINUX
liblia_la_LIBADD = ../liblinux/liblinux.la
endif

if BUILD_WIN
liblia_la_LIBADD = ../libwin/libwin.la
endif
