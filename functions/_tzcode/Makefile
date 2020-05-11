# Temporary for testing during development.

SRCFILES:=$(wildcard *.c)
TSTFILES:=$(patsubst %.c,%_t,$(SRCFILES))

CFLAGS_GENERAL:=-std=c99 -g -I ../../platform/example/include/pdclib/

all: $(TSTFILES)
	for testdriver in $(TSTFILES); do ./$$testdriver; done

clean:
	$(RM) $(TSTFILES)

%.o: %.c
	$(CC) $(CFLAGS) $(CFLAGS_GENERAL) -c $< -o $@

%_t: %.c Makefile
	$(CC) $(CFLAGS) $(CFLAGS_GENERAL) -DTEST -I ../../test_support/ $< -o $@
