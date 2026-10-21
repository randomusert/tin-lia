SUBDIRS =

if BUILD_LINUX
SUBDIRS += liblinux
endif

if BUILD_WIN
SUBDIRS += libwin
endif

SUBDIRS += liblia

bin_PROGRAMS = tin-lia
tin_lia_SOURCES = main.c

tin_lia_LDADD = liblia/liblia.la

if BUILD_LINUX
tin_lia_LDADD += liblinux/liblinux.la
endif

if BUILD_WIN
tin_lia_LDADD += libwin/libwin.la
endif
