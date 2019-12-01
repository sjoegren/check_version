#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../common.h"
#include "../version.h"

static int test_make_version(int *, int *);
static int test_versioncmp(int *, int *);

int main(int argc, char **argv)
{
	int total_tests = 0, tests = 0, total_passed = 0, passed = 0;

	test_make_version(&tests, &passed);
	total_tests += tests;
	total_passed += passed;

    tests = 0;
    passed = 0;
	test_versioncmp(&tests, &passed);
	total_tests += tests;
	total_passed += passed;

	printf("Ran %d tests, %d passed, %d failed\n",
			total_tests, total_passed, total_tests - total_passed);

	return total_tests == total_passed ? 0 : 1;
}

static int test_make_version(int *ntests, int *passed)
{
	struct version *v;

	/* make_version() stores version string */
	(*ntests)++;
	v = make_version("1.2.3", 0);
	if (strcmp(v->string, "1.2.3") == 0)
		(*passed)++;
	else
		printf("tc %-50s: failed\n", "make_version stores version string");
	free_version(v);

	/* make_version() stores first n bytes */
	(*ntests)++;
	v = make_version("123.456.78", 5);
	if (strcmp(v->string, "123.4") == 0)
		(*passed)++;
	else
		printf("test %-50s: failed\n", "make_version stores n bytes version string");
	free_version(v);

	/* make_version major,minor,micro */
	(*ntests)++;
	v = make_version("1.23.456", 0);
	unsigned int expected[VERSION_NUM_PARTS] = {1u, 23u, 456u};
	if (memcmp(v->parts, expected, sizeof(expected)) == 0)
		(*passed)++;
	else
		printf("test %-50s: failed\n", "make_version major,minor,micro");
	free_version(v);

	/* make_version major,minor */
	(*ntests)++;
	v = make_version("10.5", 0);
	unsigned int expected2[VERSION_NUM_PARTS] = {10u, 5u, 0u};
	if (memcmp(v->parts, expected2, sizeof(expected2)) == 0)
		(*passed)++;
	else
		printf("test %-50s: failed\n", "make_version major,minor");
	free_version(v);

	/* make_version major */
	(*ntests)++;
	v = make_version("42", 0);
	unsigned int expected3[VERSION_NUM_PARTS] = {42, 0, 0};
	if (memcmp(v->parts, expected3, sizeof(expected3)) == 0)
		(*passed)++;
	else
		printf("test %-50s: failed\n", "make_version major");
	free_version(v);

	/* make_version extra tokens in input */
	(*ntests)++;
	v = make_version("4.8.15.16.23.42", 0);
	unsigned int expected4[VERSION_NUM_PARTS] = {4, 8, 15};
	if (memcmp(v->parts, expected4, sizeof(expected4)) == 0)
		(*passed)++;
	else
		printf("test %-50s: failed\n", "make_version extra tokens in input");
	free_version(v);

	return *passed == *ntests ? 1 : 0;
}

int test_versioncmp(int *ntests, int *passed)
{
	struct version *a, *b;

	/* versioncmp 1.0.0 == 1*/
	(*ntests)++;
	a = make_version("1.0.0", 10);
	b = make_version("1", 10);
    if (versioncmp(a, b) == 0)
        (*passed)++;
    else
		printf("test %-50s: failed\n", "versioncmp 1.0.0 == 1");
	free_version(a);
	free_version(b);

	/* versioncmp 1.0.0 > 0.9.1 */
	(*ntests)++;
	a = make_version("1.0.0", 10);
	b = make_version("0.9.1", 10);
    if (versioncmp(a, b) == 1)
        (*passed)++;
    else
		printf("test %-50s: failed\n", "versioncmp 1.0.0 > 0.9.1");
	free_version(a);
	free_version(b);

	/* versioncmp 9.123.4567 < 10.0.1 */
	(*ntests)++;
	a = make_version("9.123.4567", 0);
	b = make_version("10.0.1", 0);
    if (versioncmp(a, b) == -1)
        (*passed)++;
    else
		printf("test %-50s: failed\n", "versioncmp 9.123.4567 < 10.0.1");
	free_version(a);
	free_version(b);

	/* versioncmp same version object equals */
	(*ntests)++;
	a = make_version("5.1", 0);
    if (versioncmp(a, a) == 0)
        (*passed)++;
    else
		printf("test %-50s: failed\n", "versioncmp 9.123.4567 < 10.0.1");
	free_version(a);

	return *passed == *ntests ? 1 : 0;
}
