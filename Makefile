#
# To make a release with version number; make VERSION=...
#
PROG = check_version
CFLAGS = -Wall -Wpedantic
CC = gcc

SOURCES = $(wildcard *.c)
OBJECTS = $(SOURCES:.c=.o)

ifdef VERSION
CFLAGS += -DPROGRAM_VERSION='"$(PROG) $(VERSION)"'
endif

ifdef DEBUG
CFLAGS += -g -DDEBUG
endif

.PHONY: clean
clean:
	$(RM) $(OBJECTS) $(PROG)
	$(RM) core*

.DEFAULT_GOAL = $(PROG)

$(PROG): $(OBJECTS)
	$(CC) $(CFLAGS) $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $<
