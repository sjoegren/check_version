PROG = check_version
CFLAGS = -Wall -Wpedantic
CC = gcc

SOURCES = $(wildcard *.c)
HEADERS = $(wildcard *.h)
OBJECTS = $(SOURCES:.c=.o)

TEST_DIR = tests
TEST_PROG = $(TEST_DIR)/runtests
TEST_SOURCES = $(wildcard $(TEST_DIR)/*.c)
TEST_OBJECTS = $(TEST_SOURCES:.c=.o)

VERSION = $(subst v,,$(shell git describe))
RELEASE_DIST = $(PROG)-$(VERSION).tar.gz
BUILD_OPTS = -DPROGRAM_VERSION='"$(VERSION)"'

.PHONY: debug
debug: CFLAGS += -g -Og
debug: BUILD_OPTS = -DDEBUG
debug: $(PROG)

.PHONY: release
release: $(PROG) $(RELEASE_DIST)

$(RELEASE_DIST): $(PROG) LICENSE
	tar -cvzf $@ $^

.PHONY: clean
clean:
	$(RM) $(OBJECTS) $(PROG)
	$(RM) $(TEST_OBJECTS) $(TEST_PROG)
	$(RM) $(PROG)-*.tar.gz

.DEFAULT_GOAL = $(PROG)

$(PROG): $(OBJECTS)
	$(CC) $(CFLAGS) $^ -o $@

%.o: %.c $(HEADERS)
	$(CC) $(BUILD_OPTS) $(CFLAGS) -c $< -o $@

.PHONY: test
test: $(TEST_PROG)
	$(TEST_PROG)

$(TEST_PROG): $(filter-out main.o, $(OBJECTS)) $(TEST_OBJECTS)
	$(CC) $(CFLAGS) $^ -o $@
