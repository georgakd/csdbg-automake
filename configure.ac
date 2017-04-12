#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ(2.59)
AC_INIT([csdbg], [1.29], [kalamara@users.sourceforge.net])
AM_INIT_AUTOMAKE([subdir-objects])
AC_CONFIG_SRCDIR([src])
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

AC_CONFIG_FILES([Makefile])
AC_OUTPUT