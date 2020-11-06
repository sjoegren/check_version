#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_INIT([check_version], m4_esyscmd([./version.sh]), [https://github.com/akselsjogren/check_version])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_SRCDIR([src/args.h])

# Checks for programs.
AC_PROG_CC

# Checks for libraries.

# Checks for header files.
AC_CHECK_HEADERS([argp.h], [], [AC_MSG_ERROR([missing required header])])

# Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_SIZE_T
AC_TYPE_SSIZE_T

# Checks for library functions.
AC_FUNC_MALLOC
AC_CHECK_FUNCS([getline regcomp strdup strndup strtoul],
			   [],
			   [AC_MSG_ERROR([function is required to build the package.])])

AC_CONFIG_FILES([Makefile
                 src/Makefile])

AM_INIT_AUTOMAKE([foreign -Wall -Werror])

AC_OUTPUT
