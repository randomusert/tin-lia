AC_INIT([tin-lia], [0.1])
AM_INIT_AUTOMAKE([foreign subdir-objects dist-zip])
AC_CONFIG_HEADERS([config.h])

AC_ARG_WITH([platform],
  [AS_HELP_STRING([--with-platform=PLATFORM],
                  [choose platform: linux or win (default: linux)])],
  [
    if test "$withval" = "yes" || test "$withval" = "no"; then
      with_platform=linux
    else
      with_platform="$withval"
    fi
  ],
  [with_platform=linux])

case "$with_platform" in
  linux)
    CC=gcc
    platform_linux=yes
    platform_win=no
    ;;
  win)
    AC_CHECK_PROG([HAVE_MINGW], [x86_64-w64-mingw32-gcc], [yes], [no])
    if test "$HAVE_MINGW" = "no"; then
      AC_MSG_ERROR([MinGW cross-compiler not found: please install mingw-w64])
    fi
    CC=x86_64-w64-mingw32-gcc
    host_alias=x86_64-w64-mingw32
    platform_linux=no
    platform_win=yes
    ;;
  *)
    AC_MSG_ERROR([Invalid platform: $with_platform. Use linux or win.])
    ;;
esac

AC_SUBST([CC])

AC_PROG_CC
LT_INIT
AC_PROG_RANLIB

AM_CONDITIONAL([BUILD_LINUX], [test "$platform_linux" = "yes"])
AM_CONDITIONAL([BUILD_WIN], [test "$platform_win" = "yes"])


AC_CONFIG_FILES([
  Makefile
  src/Makefile
  src/liblia/Makefile
  src/liblinux/Makefile
  src/libwin/Makefile
])
AC_OUTPUT
