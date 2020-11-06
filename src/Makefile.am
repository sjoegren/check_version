bin_PROGRAMS = check_version
check_PROGRAMS = test_check_version
TESTS = test_check_version

check_version_SOURCES = args.c args.h common.h main.c version.c version.h
check_version_CFLAGS = -ggdb -D_DEFAULT_SOURCE -D_POSIX_C_SOURCE=200809L -std=c11 -Wall -Wpedantic

test_check_version_SOURCES = test_check_version.c common.h version.c version.h
test_check_version_CFLAGS = $(check_version_CFLAGS)
