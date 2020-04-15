# Temporary for testing during development.

SRCFILES:=$(wildcard *.c)
TSTFILES:=$(patsubst %.c,%_t,$(SRCFILES))

all: $(TSTFILES)
	for testdriver in ./$(TSTFILES); do $$testdriver; done

clean:
	$(RM) $(TSTFILES)

%_t: %.c Makefile
	$(CC) $(CFLAGS) -std=c99 -DTEST -g -I ../../platform/example/include/pdclib/ -I ../../test_support/ $< -o $@
