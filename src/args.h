#ifndef _ARGS_H
#define _ARGS_H

#include <argp.h>

enum comp_mode { COMP_LT, COMP_LE, COMP_EQ, COMP_GE, COMP_GT };

/* Used by main to communicate with parse_opt. */
struct arguments
{
    char *regex, *check_version;
    int quiet;
	enum comp_mode mode;
};

error_t parse_args(
    int,
    char **,
    const struct argp_option *,
    const char *,
    const char *,
    struct arguments *
);

#endif
