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
	{"regex", 'r', "regex", 0,
		"Regex pattern for extracting version number from input"},
	{"check-version", 'c', "version", 0, "The version to compare to"},
    {"mode", 129, "MODE", 0, "One of comparison operators lt, le, eq, ge (default), gt"},
    {"quiet", 'q', 0, 0, "Don't print anything on stdout"},
	{ 0 }
};

enum return_code { RET_PASSED, RET_FAILED, RET_ERROR };

int main(int argc, char **argv)
{
	struct arguments args;
	struct version *check_version, *found_version;
	int result = 0;
	char compstr[3];

	/* Parse our arguments; every option seen by parse_opt will
	   be reflected in arguments. */
	if (parse_args(argc, argv, options, args_doc, doc, &args) != 0)
		return RET_ERROR;

	check_version = make_version(args.check_version, 0);

	found_version = extract_version(stdin, args.regex);
	if (found_version == NULL) {
		fprintf(stderr, "Failed to extract version from stdin\n");
		free(check_version);
		return RET_FAILED;
	}

	switch (args.mode) {
		case COMP_GE:
			result = versioncmp(found_version, check_version) >= 0;
			strcpy(compstr, ">=");
			break;
		case COMP_LE:
			result = versioncmp(found_version, check_version) <= 0;
			strcpy(compstr, "<=");
			break;
		case COMP_LT:
			result = versioncmp(found_version, check_version) < 0;
			strcpy(compstr, "<");
			break;
		case COMP_GT:
			result = versioncmp(found_version, check_version) > 0;
			strcpy(compstr, ">");
			break;
		case COMP_EQ:
			result = versioncmp(found_version, check_version) == 0;
			strcpy(compstr, "==");
			break;
	}

	if (!args.quiet)
		printf("Result: %s %s %s: %s\n",
			found_version->string,
			compstr,
			check_version->string,
			result ? "true" : "false");

	free_version(check_version);
	free_version(found_version);
	return result ? RET_PASSED : RET_FAILED;
}
