# This is a list of all non-source files that are part of the distribution.
AUXFILES := Makefile Readme.txt

SRCFILES := $(shell find . -name "*.c" -mindepth 1 -maxdepth 3)
HDRFILES := $(shell find . -name "*.h" -mindepth 1 -maxdepth 3)
OBJFILES := $(patsubst %.c,%.o,$(SRCFILES))
TSTFILES := $(patsubst %.c,%.t,$(SRCFILES))
DEPFILES := $(patsubst %.c,%.d,$(SRCFILES))
ALLFILES := $(SRCFILES) $(HDRFILES) $(AUXFILES)

CPPFLAGS  := -MMD -MP
CFLAGS    := -g -std=c99 -I./internals/

.PHONY: all clean dist

all: $(OBJFILES)
	ar r pdclib.a $(OBJFILES)

test: $(TSTFILES)
	-@rc=0; for file in $(TSTFILES); do ./$$file; rc=`expr $$rc + $$?`; done; echo; echo "Tests failed: $$rc"

-include $(DEPFILES)

clean:
	-@for file in $(OBJFILES) $(DEPFILES) pdclib.a; do if [ -f $$file ]; then rm $$file; fi; done

dist:
	@tar czf pdclib.tgz $(ALLFILES)

%.o: %.c Makefile
	$(CC) -DNDEBUG -c $(CPPFLAGS) $(CFLAGS) $< -o $@

%.t: %.c Makefile
	$(CC) -DTEST $(CFLAGS) $< -o $@

