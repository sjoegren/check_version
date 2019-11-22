#
# To make a release with version number; make VERSION=...
#
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

ifdef VERSION
CFLAGS += -DPROGRAM_VERSION='"$(PROG) $(VERSION)"'
endif

ifdef DEBUG
CFLAGS += -g -Og -DDEBUG
endif

.PHONY: clean
clean:
	$(RM) $(OBJECTS) $(PROG)
	$(RM) core*
	$(RM) $(TEST_OBJECTS) $(TEST_PROG)

.DEFAULT_GOAL = $(PROG)

$(PROG): $(OBJECTS)
	$(CC) $(CFLAGS) $^ -o $@

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: test
test: $(TEST_PROG)
	$(TEST_PROG)

$(TEST_PROG): $(filter-out main.o, $(OBJECTS)) $(TEST_OBJECTS)
	$(CC) $(CFLAGS) $^ -o $@
