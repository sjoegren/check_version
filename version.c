#define _GNU_SOURCE		/* For getline() */

#include <ctype.h>
#include <errno.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include "common.h"
#include "version.h"

#define INITIAL_MATCHES_ALLOC_SIZE	4
#define RE_ERROR_MAXLEN				500

struct version * extract_version(
		FILE *input,
		const char *regex,
		const struct version *check_version)
{
	char *lineptr = NULL;
	regex_t preg;
	int re_errcode;
	char match = 0, errbuf[RE_ERROR_MAXLEN];
	ssize_t read;
	size_t size = 0, nmatch = 2;
	regmatch_t pmatch[nmatch];
	struct version *found_version;

	if ((re_errcode = regcomp(&preg, regex, REG_EXTENDED | REG_ICASE)) != 0) {
		regerror(re_errcode, &preg, errbuf, RE_ERROR_MAXLEN);
		fprintf(stderr, "Regex error: %s\n", errbuf);
		return NULL;
	}

	while ((read = getline(&lineptr, &size, input)) != -1) {
		if (regexec(&preg, lineptr, nmatch, pmatch, 0) == 0) {
			match = 1;
			PRINT_DEBUG((stderr, "Matched line: %s read=%zi size=%zu\n",
						lineptr, read, size));
			break;
		}
	}

	regfree(&preg);

	if (!match) {
		fprintf(stderr, "No match found for pattern: '%s'\n", regex);
		free(lineptr);
		return NULL;
	}

	if (pmatch[1].rm_so == -1) {
		fprintf(stderr, "No subgroup match found.\n");
		free(lineptr);
		return NULL;
	}

	found_version = make_version(
		lineptr + pmatch[1].rm_so,			// start of substring
		pmatch[1].rm_eo - pmatch[1].rm_so	// substring length
	);

	free(lineptr);
	return found_version;
}

/*
 * Create a new `struct version`.
 * str:	pointer to string to copy into the returned struct.
 * n:	for a non-zero value, copy at most n bytes from str.
 * returns: pointer to created struct. Caller can use free_version() to free
 * the returned pointer..
 */
struct version * make_version(const char *str, size_t n)
{
	struct version *v;
	int tokens = VERSION_NUM_PARTS, p = 0;
	char *token, *tempstr;

	if ((v = malloc(sizeof(struct version))) == NULL) {
		perror("make_version");
		exit(1);
	}
	v->string = n ? strndup(str, n) : strdup(str);

    tempstr = strdup(v->string);
	token = strtok(tempstr, ".");

	while (token != NULL && tokens-- > 0) {
		PRINT_DEBUG((stderr, "string: %s, token %d: %s\n", v->string, p, token));
		errno = 0;
		v->parts[p++] = (unsigned) strtoul(token, NULL, 10);
		if (errno)
			break;
		token = strtok(NULL, ".");
	}
	/* Set remaining parts to 0 */
	while (tokens-- > 0)
		v->parts[p++] = 0;

	free(tempstr);
	return v;
}

/*
 * Compare two versions by their integer parts.
 * Returns: -1, 0, or 1.
 */
int versioncmp(const struct version *a, const struct version *b)
{
    for (int i = 0; i < VERSION_NUM_PARTS; ++i) {
		PRINT_DEBUG((stderr, "versioncmp(%s, %s), part %d\n", a->string, b->string, i));
        if (a->parts[i] > b->parts[i])
            return 1;
        if (a->parts[i] < b->parts[i])
            return -1;
    }
    return 0;
}

void free_version(struct version *v)
{
	free(v->string);
    free(v);
}

void print_version(struct version *v)
{
	printf("%s parts=[%u, %u, %u]\n",
			v->string, v->parts[0], v->parts[1], v->parts[2]);
}
