#ifndef _MATCHING_H
#define _MATCHING_H

struct version {
	char *string;
	unsigned int parts[3];
};

enum _MATCH_RETURN_CODES {
	MATCH_SUCCESS,
	MATCH_FAILURE,
	MATCH_RE_ERROR,
};

struct version *extract_version(FILE *, const char *, const struct version *);
struct version *make_version(const char *, size_t);
void free_version(struct version *);
void print_version(struct version *);

#endif
