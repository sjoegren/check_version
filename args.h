#ifndef _ARGS_H
#define _ARGS_H

#include <argp.h>

#define MAX_NUM_ARGS 2
/* Used by main to communicate with parse_opt. */
struct arguments
{
    char *regex, *check_version;
    int quiet;
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
