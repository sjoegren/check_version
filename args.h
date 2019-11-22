#ifndef _ARGS_H
#define _ARGS_H

#include <argp.h>

#define MAX_NUM_ARGS 2
/* Used by main to communicate with parse_opt. */
struct arguments
{
	//char *args[MAX_NUM_ARGS];                /* pattern [file] */
	/* int ignore_case, count, line_numbers; */
    char *regex, *check_version;
};

int parse_args(int argc, char **argv,
		const struct argp_option *options,
		const char *args_doc, const char *doc,
		struct arguments *args);

#endif
