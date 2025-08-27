AC_INIT([tin-lia], [0.1])
AM_INIT_AUTOMAKE([foreign subdir-objects dist-zip])
AC_CONFIG_HEADERS([config.h])


AC_PROG_RANLIB


AC_ARG_WITH([platform],
  [AS_HELP_STRING([--with-platform],
                  [choose platform: linux or win])],
  [with_platform=$withval],
  [with_platform=linux]) # default

# Choose compiler before running AC_PROG_CC
case "$with_platform" in
  linux)
    CC=gcc
    AM_CONDITIONAL([BUILD_LINUX], [true])
    AM_CONDITIONAL([BUILD_WIN], [false])
    ;;
  win)
    AC_CHECK_PROG([HAVE_MINGW], [x86_64-w64-mingw32-gcc], [yes], [no])
    if test "$HAVE_MINGW" = "no"; then
      AC_MSG_ERROR([MinGW cross-compiler not found: please install mingw-w64])
    fi
    CC=x86_64-w64-mingw32-gcc
    AM_CONDITIONAL([BUILD_LINUX], [false])
    AM_CONDITIONAL([BUILD_WIN], [true])
    ;;
  *)
    AC_MSG_ERROR([Invalid platform: $with_platform. Use linux or win.])
    ;;
esac

# NOW run compiler detection
AC_PROG_CC



AC_CONFIG_FILES([
  Makefile
  src/Makefile
  src/liblia/Makefile
  src/liblinux/Makefile
  src/libwin/Makefile
])
AC_OUTPUT
