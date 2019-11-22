PROG = tests
CFLAGS = -I.. -Wall -Wpedantic
CC = gcc

SOURCES = $(wildcard *.c ../*.c)
HEADERS = $(wildcard *.h ../*.h)
OBJECTS = $(SOURCES:.c=.o)

.PHONY: clean
clean:
	$(RM) $(OBJECTS) $(PROG)
	$(RM) core*

.DEFAULT_GOAL = $(PROG)

$(PROG): $(OBJECTS)
	$(CC) $(CFLAGS) $^ -o $@

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $<
