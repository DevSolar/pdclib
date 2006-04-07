# $Id$

# This is a list of all non-source files that are part of the distribution.
AUXFILES := Makefile Readme.txt

PROJDIRS := functions includes internals
SRCFILES := $(shell find $(PROJDIRS) -mindepth 1 -maxdepth 3 -name "*.c")
HDRFILES := $(shell find $(PROJDIRS) -mindepth 1 -maxdepth 3 -name "*.h")
INTFILES := atomax digits lengthmods seed strtox_main strtox_prelim rename remove _Exit
OBJFILES := $(patsubst %.c,%.o,$(SRCFILES))
TSTFILES := $(patsubst %.c,%.t,$(SRCFILES))
REGFILES := $(filter-out $(patsubst %,functions/_PDCLIB/%.r,$(INTFILES)),$(patsubst %.c,%.r,$(SRCFILES)))
DEPFILES := $(patsubst %.c,%.d,$(SRCFILES))
ALLFILES := $(SRCFILES) $(HDRFILES) $(AUXFILES)

CFLAGS := -Wall -pedantic -Wshadow -Wpointer-arith -Wcast-align -Wwrite-strings -Wmissing-prototypes -Wmissing-declarations -Wredundant-decls -Wnested-externs -Winline -Wno-long-long -Wconversion -Wstrict-prototypes

.PHONY: clean dist test testdrivers regtest

all: pdclib.a

pdclib.a: $(OBJFILES)
	@ar r pdclib.a $?

test: testdrivers
	-@rc=0; count=0; for file in $(TSTFILES); do ./$$file; rc=`expr $$rc + $$?`; count=`expr $$count + 1`; done; echo; echo "Tests executed (linking PDCLib): $$count  Tests failed: $$rc"

testdrivers: $(TSTFILES)

regtest: regtestdrivers
	-@rc=0; count=0; for file in $(REGFILES); do ./$$file; rc=`expr $$rc + $$?`; count=`expr $$count + 1`; done; echo; echo "Tests executed (linking system libc): $$count  Tests failed: $$rc"

regtestdrivers: $(REGFILES)

-include $(DEPFILES)

clean:
	@for file in $(OBJFILES) $(DEPFILES) $(TSTFILES) $(REGFILES) pdclib.a pdclib.tgz; do if [ -f $$file ]; then rm $$file; fi; done

dist:
	@tar czf pdclib.tgz $(ALLFILES)

todolist:
	-@for file in $(ALLFILES); do grep -H TODO $$file; done; true

fixmelist:
	-@for file in $(ALLFILES); do grep -H FIXME $$file; done; true

%.o: %.c Makefile
	@$(CC) $(CFLAGS) -Wall -DNDEBUG -MMD -MP -MT "$*.d $*.t" -g -std=c99 -I./includes -I./internals -c $< -o $@

%.t: %.c Makefile pdclib.a
	@$(CC) $(CFLAGS) -DTEST -std=c99 -I./includes -I./internals $< pdclib.a -o $@

%.r: %.c Makefile
	@$(CC) $(CFLAGS) -DTEST -DREGTEST -std=c99 -I./internals $< -o $@
