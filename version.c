#define _GNU_SOURCE		/* For getline() */

#include <assert.h>
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
		FILE *input, const char *regex, const struct version *check_version)
{
	char *lineptr;
	regex_t preg;
	int re_errcode;
	char errbuf[RE_ERROR_MAXLEN];
	ssize_t read;
	size_t size;
	size_t nmatch = 2;
	char match = 0;
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

	for (int i = 0; i < nmatch; ++i) {
		PRINT_DEBUG((stderr, "%i, %i\n", pmatch[i].rm_so, pmatch[i].rm_eo));
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

	// TODO: compare numbers

	free(lineptr);
	return found_version;
}

/*
 * Create a new `struct version`.
 * str:	pointer to string to copy into the returned struct.
 * n:	for a non-zero value, copy at most n bytes from str.
 * returns: pointer to created struct.
 */
struct version * make_version(const char *str, size_t n)
{
	struct version *v;
	int tokens = 3, p = 0;
	char *token;

	if ((v = malloc(sizeof(struct version))) == NULL) {
		perror("make_version");
		exit(1);
	}
	v->string = n ? strndup(str, n) : strdup(str);

	PRINT_DEBUG((stderr, "string: %s\n", v->string));
	token = strtok(v->string, ".");
	PRINT_DEBUG((stderr, "first  token: %s\n", token));

	while (token != NULL && tokens-- > 0) {
		PRINT_DEBUG((stderr, "Got token: %s\n", token));
		errno = 0;
		v->parts[p++] = (unsigned) strtoul(token, NULL, 10);
		if (errno)
			break;
		token = strtok(NULL, ".");
	}
	free(token);
	return v;
}

void free_version(struct version *v)
{
	free(v->string);
}

void print_version(struct version *v)
{
	printf("%s parts=[%u, %u, %u]\n",
			v->string, v->parts[0], v->parts[1], v->parts[2]);
}
