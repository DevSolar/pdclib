# This is a list of all non-source files that are part of the distribution.
AUXFILES := Makefile Readme.txt

SRCFILES := $(shell find . -name "*.c" -mindepth 1 -maxdepth 3)
HDRFILES := $(shell find . -name "*.h" -mindepth 1 -maxdepth 3)
OBJFILES := $(patsubst %.c,%.o,$(SRCFILES))
TSTFILES := $(patsubst %.c,%.t,$(SRCFILES))
DEPFILES := $(patsubst %.c,%.d,$(SRCFILES))
ALLFILES := $(SRCFILES) $(HDRFILES) $(AUXFILES)

.PHONY: all clean dist

all: $(OBJFILES)
	ar r pdclib.a $?

test: $(TSTFILES)
	-@rc=0; for file in $(TSTFILES); do ./$$file; rc=`expr $$rc + $$?`; done; echo; echo "Tests failed: $$rc"

-include $(DEPFILES)

clean:
	-@for file in $(OBJFILES) $(DEPFILES) $(TSTFILES) pdclib.a; do if [ -f $$file ]; then rm $$file; fi; done

dist:
	@tar czf pdclib.tgz $(ALLFILES)

%.o: %.c Makefile
	@$(CC) -Wall -DNDEBUG -MMD -MP -MT "$*.d $*.t" -g -std=c99 -I./internals -c $< -o $@

%.t: %.c Makefile
	@$(CC) -Wall -DTEST -std=c99 -I./internals/ $< -o $@
