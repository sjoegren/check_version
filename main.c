#include <argp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "args.h"
#include "common.h"
#include "version.h"

const char *argp_program_version = ARGP_PROGRAM_VERSION;
const char *argp_program_bug_address = ARGP_PROGRAM_BUG_ADDRESS;

/* Program documentation. */
static char doc[] = "\n"
"Check how a program version compares to a version string.\n"
"Example: Check if git version is at least 2.0:\n\n"
"  git --version | check_version -r 'version ([0-9]+\\.[0-9]+\\.[0-9]+)' -c 2.0";

/* A description of the arguments we accept. */
static char args_doc[] = "-r regex -c version";

/* Program options */
static struct argp_option options[] = {
	{"regex",           'r', "regex",   0,
		"Regex pattern for extracting version number from input"},
	{"check-version",   'c', "version", 0, "The version to compare to"},
    {"quiet",           'q', 0,         0, "Don't print anything on stdout"},
	{ 0 }
};

enum RETURN { SUCCESS, FAILED, ERROR };


int main(int argc, char **argv)
{
	struct arguments args;
	struct version *check_version, *found_version;
    int result, retval;

	/* Parse our arguments; every option seen by parse_opt will
	   be reflected in arguments. */
	if (parse_args(argc, argv, options, args_doc, doc, &args) != 0)
		exit(ERROR);

	check_version = make_version(args.check_version, 0);

	found_version = extract_version(stdin, args.regex, check_version);
	if (found_version == NULL) {
		fprintf(stderr, "Failed to extract version from stdin\n");
		free(check_version);
		return ERROR;
	}

    if ((result = versioncmp(found_version, check_version)) >= 0) {
		if (!args.quiet)
			printf("Result: %s >= %s: true\n",
				found_version->string, check_version->string);
        retval = MATCH_SUCCESS;
    }
    else {
		if (!args.quiet)
			printf("Result: %s >= %s: false\n",
				found_version->string, check_version->string);
        retval = MATCH_FAILURE;
    }

	free_version(check_version);
	free_version(found_version);
	return retval;
}
