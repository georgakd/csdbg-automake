#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ(2.59)
AC_INIT([csdbg], [1.29], [kalamara@users.sourceforge.net])
AM_INIT_AUTOMAKE([subdir-objects])
AC_CONFIG_SRCDIR([src])
AC_CONFIG_MACRO_DIR([m4])
#AC_CONFIG_HEADER([config.h])

# Checks for programs.
AC_PROG_CXX
AC_PROG_CC

#libtoolize
LT_INIT

AC_LANG_CPLUSPLUS
# Checks for libraries.
AC_CHECK_LIB([bfd], [bfd_init])
AC_CHECK_LIB([dl], [dlsym])
AC_CHECK_LIB([pthread], [pthread_create])

# Checks for header files.
AC_HEADER_STDC
AC_CHECK_HEADERS([stdio.h stdlib.h string.h stdarg.h ctype.h]) 

# Checks for typedefs, structures, and compiler characteristics.
AC_C_CONST
AC_HEADER_STDBOOL

# Checks for library functions.
AC_FUNC_MALLOC
AC_FUNC_VPRINTF
AC_CHECK_FUNCS([atexit memset strstr])

#enable-debug
AC_ARG_ENABLE([debug],
[  --disable-debug         Debugging code],
[case "${enableval}" in
  yes) debug=true ;;
  *)  debug=false ;;
esac],[debug=true])
AM_CONDITIONAL([DEBUG], [test x$debug = xtrue])

#enable-color-term
AC_ARG_ENABLE([color-term],
[  --enable-color-term=yes Include support for color terminals (VT100)],
[case "${enableval}" in
  yes) color=true ;;
  *)  color=false ;;
esac],[color=false])
AM_CONDITIONAL([COLOR], [test x$color = xtrue])

#enable-highlight
AC_ARG_ENABLE([highlight],
[  --enable-highlight=yes  Trace C++ syntax highlighting],
[case "${enableval}" in
  yes) highlight=true ;;
  *)  highlight=false ;;
esac],[highlight=false])
AM_CONDITIONAL([HIGHLIGHT], [test x$highlight = xtrue])

#disable-streambuf
AC_ARG_ENABLE([streambuf],
[  --disable-streambuf     Buffered output streams],
[case "${enableval}" in
  yes) streambuf=true ;;
  *)  streambuf=false ;;
esac],[streambuf=true])
AM_CONDITIONAL([STREAMBUF], [test x$streambuf = xtrue])

#disable-plugin
AC_ARG_ENABLE([plugin],
[  --disable-plugin       Instrumentation plugins],
[case "${enableval}" in
  yes) plugin=true ;;
  *)  plugin=false ;;
esac],[plugin=true])
AM_CONDITIONAL([PLUGIN], [test x$plugin = xtrue])

#disable-filter
AC_ARG_ENABLE([filter],
[  --disable-filter       Instrumentation filters],
[case "${enableval}" in
  yes) filter=true ;;
  *)  filter=false ;;
esac],[filter=true])
AM_CONDITIONAL([FILTER], [test x$filter = xtrue])

AC_CONFIG_FILES([Makefile])

AC_OUTPUT
