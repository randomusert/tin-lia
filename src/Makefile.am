SUBDIRS = liblia

if BUILD_LINUX
SUBDIRS += liblinux
endif

if BUILD_WIN
SUBDIRS += libwin
endif

bin_PROGRAMS = tin-lia
tin_lia_SOURCES = main.c

tin_lia_LDADD = liblia/liblia.a

if BUILD_LINUX
tin_lia_LDADD += liblinux/liblinux.a
endif

if BUILD_WIN
tin_lia_LDADD += libwin/libwin.a
endif
