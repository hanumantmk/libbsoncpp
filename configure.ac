#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.61])
AC_INIT([libmongocpp], [1.0], [jason.carey@mongodb.com])
AC_CONFIG_HEADERS([config.h])

LT_PREREQ([2.2])
LT_INIT

AM_INIT_AUTOMAKE([1.10])

AC_PROG_CXX()

AX_CXX_COMPILE_STDCXX_11()

# Checks for libraries.

# Checks for header files.
AC_CHECK_HEADERS([unistd.h sys/types.h error.h])

# Checks for library functions.
PKG_CHECK_MODULES(BSON, libbson-1.0 > 0.4.0)

# Checks for library functions.
PKG_CHECK_MODULES(MONGOC, libmongoc-1.0 > 0.90.0)

AC_CONFIG_FILES([
    Makefile
])

AC_OUTPUT
