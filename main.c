#include <argp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "args.h"
#include "common.h"
#include "version.h"

#ifndef PROGRAM_VERSION
#define PROGRAM_VERSION	"check_version dev"
#endif

const char *argp_program_version = PROGRAM_VERSION;
const char *argp_program_bug_address = "<github.com/akselsjogren>";

/* Program documentation. */
static char doc[] =
"Check how a program version compares to a version string.";

/* A description of the arguments we accept. */
static char args_doc[] = "--regex PATTERN --check-version VERSION";

/* Program options */
static struct argp_option options[] = {
	{"regex", 'r', "pattern", 0, "Regex pattern for extracting version number from input" },
	{"check-version", 'c', "VERSION", 0, "The version to compare to"},
	{ 0 }
};

enum RETURN { SUCCESS, FAILED, ERROR };


int main(int argc, char **argv)
{
	struct arguments args;
	struct version *check_version, *found_version;

	/* Parse our arguments; every option seen by parse_opt will
	   be reflected in arguments. */
	if (parse_args(argc, argv, options, args_doc, doc, &args) != 0)
		exit(ERROR);

	/* PRINT_DEBUG((stderr, "pattern: '%s', file: '%s', case: %d, count: %d, lineno: %d\n", */
	/* 		args.args[0], args.args[1], args.ignore_case, args.count, args.line_numbers)); */
	PRINT_DEBUG((stderr, "regex: '%s', check-version: '%s'\n", args.regex, args.check_version));

	check_version = make_version(args.check_version, 0);

	found_version = extract_version(stdin, args.regex, check_version);
	if (found_version == NULL) {
		fprintf(stderr, "Failed to extract version from stdin\n");
		free(check_version);
		return ERROR;
	}

	print_version(check_version);
	print_version(found_version);

	free_version(check_version);
	free_version(found_version);
	return 0;
}
