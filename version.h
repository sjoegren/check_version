#ifndef _MATCHING_H
#define _MATCHING_H

#define VERSION_NUM_PARTS   3

struct version {
	char *string;
	unsigned int parts[VERSION_NUM_PARTS];
};

struct version *extract_version(FILE *, const char *);
struct version *make_version(const char *, size_t);
void free_version(struct version *);
void print_version(struct version *);
int versioncmp(const struct version *, const struct version *);

#endif
