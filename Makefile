# This is a list of all non-source files that are part of the distribution.
AUXFILES := Makefile Readme.txt

PROJDIRS := functions includes internals
SRCFILES := $(shell find $(PROJDIRS) -mindepth 1 -maxdepth 3 -name "*.c")
HDRFILES := $(shell find $(PROJDIRS) -mindepth 1 -maxdepth 3 -name "*.h")
INTFILES := $(patsubst %.c,%.r,$(shell find functions/_PDCLIB -name "*.c"))
OBJFILES := $(patsubst %.c,%.o,$(SRCFILES))
TSTFILES := $(patsubst %.c,%.t,$(SRCFILES))
REGFILES := $(filter-out $(INTFILES),$(patsubst %.c,%.r,$(SRCFILES)))
DEPFILES := $(patsubst %.c,%.d,$(SRCFILES))
ALLFILES := $(SRCFILES) $(HDRFILES) $(AUXFILES)

.PHONY: clean dist test regtest

all: pdclib.a

pdclib.a: $(OBJFILES)
	@ar r pdclib.a $?

test: $(TSTFILES)
	-@rc=0; for file in $(TSTFILES); do ./$$file; rc=`expr $$rc + $$?`; done; echo; echo "Tests failed: $$rc"

regtest: $(REGFILES)
	-@rc=0; for file in $(REGFILES); do ./$$file; rc=`expr $$rc + $$?`; done; echo; echo "Regression tests failed: $$rc"

-include $(DEPFILES)

clean:
	-@for file in $(OBJFILES) $(DEPFILES) $(TSTFILES) $(REGFILES) pdclib.a pdclib.tgz; do if [ -f $$file ]; then rm $$file; fi; done

dist:
	@tar czf pdclib.tgz $(ALLFILES)

%.o: %.c Makefile
	@$(CC) -Wall -DNDEBUG -MMD -MP -MT "$*.d $*.t" -g -std=c99 -I./includes -I./internals -c $< -o $@

%.t: %.c Makefile pdclib.a
	@$(CC) -Wall -DTEST -std=c99 -I./includes -I./internals $< pdclib.a -o $@

%.r: %.c Makefile
	@$(CC) -Wall -DTEST -DREGTEST -std=c99 -I./internals $< -o $@
