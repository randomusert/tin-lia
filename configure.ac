AC_INIT([tin-lia], [0.1])


AM_INIT_AUTOMAKE([foreign subdir-objects])
AC_PROG_CC
AC_PROG_RANLIB

AC_CONFIG_HEADERS([config.h])

# Custom option: --with-platform={linux,win}
AC_ARG_WITH([platform],
  [AS_HELP_STRING([--with-platform],
                  [choose platform: linux or win])],
  [with_platform=$withval],
  [with_platform=linux]) # default

case "$with_platform" in
  linux)
    AM_CONDITIONAL([BUILD_LINUX], [true])
    AM_CONDITIONAL([BUILD_WIN], [false])
    ;;
  win)
    AM_CONDITIONAL([BUILD_LINUX], [false])
    AM_CONDITIONAL([BUILD_WIN], [true])
    ;;
  *)
    AC_MSG_ERROR([Invalid platform: $with_platform. Use linux or win.])
    ;;
esac

AC_CONFIG_FILES([
  Makefile
  src/Makefile
  src/liblia/Makefile
  src/liblinux/Makefile
  src/libwin/Makefile
])
AC_OUTPUT
