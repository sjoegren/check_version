/*
 * Parsing arguments with <argp.h>.
 */

#include "args.h"

static error_t parse_opt (int key, char *arg, struct argp_state *state);

/* Parse a single option. */
static error_t parse_opt (int key, char *arg, struct argp_state *state)
{
	/* Get the input argument from argp_parse, which we
	   know is a pointer to our arguments structure. */
	struct arguments *args = state->input;

	switch (key)
	{
		case 'r':
            args->regex = arg;
			break;

		case 'c':
            args->check_version = arg;
			break;

		case 'q':
            args->quiet = 1;
			break;

		case ARGP_KEY_ARG:
            return ARGP_ERR_UNKNOWN;
			break;

        case ARGP_KEY_END:
            if (!args->regex || !args->check_version) {
                /* Missing mandatory args. */
                argp_error(state, "--regex and --check-version are required\n");
            }
            break;

		default:
			return ARGP_ERR_UNKNOWN;
	}
	return 0;
}

/*
 * Parse options and arguments from command line.
 */
error_t parse_args(
        int argc, char **argv,
        const struct argp_option *options,
        const char *args_doc,
        const char *doc,
        struct arguments *args)
{
	/* Our argp parser. */
	struct argp argp = { options, parse_opt, args_doc, doc };

	/* Default values. */
	args->regex = NULL;
	args->check_version = NULL;
	args->quiet = 0;

	/* Parse our arguments; every option seen by parse_opt will
	   be reflected in arguments. */
	return argp_parse(&argp, argc, argv, 0, 0, args);
}
