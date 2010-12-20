# $Id$

# This is where you chose which platform to compile for (see 'make links' / './platform')
PLATFORM := example

# This is a list of all non-source files that are part of the distribution.
AUXFILES := Makefile Readme.txt

# Directories belonging to the project
PROJDIRS := functions includes internals
# All source files of the project
SRCFILES := $(shell find $(PROJDIRS) -mindepth 1 -maxdepth 3 -name "*.c")
# All header files of the project
HDRFILES := $(shell find $(PROJDIRS) -mindepth 1 -maxdepth 3 -name "*.h")
# All .c files in functions/_PDCLIB that do not have a regression test driver
INTFILES := _Exit atomax digits open print scan remove rename seed stdinit strtox_main strtox_prelim filemode eol errno seek prepread prepwrite allocpages tmpfilename closeall
# All object files in the library
OBJFILES := $(patsubst %.c,%.o,$(SRCFILES))
# All test drivers (.t)
TSTFILES := $(patsubst %.c,%_t,$(SRCFILES))
# All regression test drivers (.r)
REGFILES := $(filter-out $(patsubst %,functions/_PDCLIB/%_r,$(INTFILES)),$(patsubst %.c,%_r,$(SRCFILES)))
# All library dependency files (.d)
DEPFILES := $(patsubst %.c,%.d,$(SRCFILES))
# All test driver dependency files (_t.d)
TSTDEPFILES := $(patsubst %,%.d,$(TSTFILES))
# All regression test driver dependency files (_r.d)
REGDEPFILES := $(patsubst %,%.d,$(REGFILES))
# All files belonging to the source distribution
ALLFILES := $(SRCFILES) $(HDRFILES) $(AUXFILES)

WARNINGS := -Wall -Wextra -pedantic -Wno-unused-parameter -Wshadow -Wpointer-arith -Wcast-align -Wwrite-strings -Wmissing-prototypes -Wmissing-declarations -Wredundant-decls -Wnested-externs -Winline -Wno-long-long -fno-builtin 
CFLAGS := -g -std=c99 -I./internals -I./testing $(WARNINGS) $(USERFLAGS)

.PHONY: all clean srcdist bindist test tests testdrivers regtests regtestdrivers todos fixmes find links unlink help

all: pdclib.a testdrivers regtestdrivers
	@echo
	@echo "========================"
	@echo "Executing library tests:"
	@echo "========================"
	@echo
	@$(MAKE) tests | grep -v "^ TST" | grep -v "^Failed"
	@echo
	@echo "==========================="
	@echo "Executing regression tests:"
	@echo "==========================="
	@echo
	@$(MAKE) regtests | grep -v "^ RTST" | grep -v "^Failed"

pdclib.a: $(OBJFILES)
	@echo " AR	$@"
	@ar rc pdclib.a $?
	@echo

test: functions/$(FILE)
	functions/$(FILE)

tests: testdrivers
	-@rc=0; count=0; failed=""; for file in $(TSTFILES); do echo " TST	$$file"; ./$$file; test=$$?; if [ $$test != 0 ]; then rc=`expr $$rc + $$test`; failed="$$failed $$file"; fi; count=`expr $$count + 1`; done; echo; echo "Tests executed (linking PDCLib): $$count  Tests failed: $$rc"; echo; for file in $$failed; do echo "Failed: $$file"; done; echo

testdrivers: $(TSTFILES)
	@echo

regtests: regtestdrivers
	-@rc=0; count=0; failed=""; for file in $(REGFILES); do echo " RTST	$$file"; ./$$file; test=$$?; if [ $$test != 0 ]; then rc=`expr $$rc + $$test`; failed="$$failed $$file"; fi; count=`expr $$count + 1`; done; echo; echo "Tests executed (linking system libc): $$count  Tests failed: $$rc"; echo; for file in $$failed; do echo "Failed: $$file"; done; echo

regtestdrivers: $(REGFILES)
	@echo

-include $(DEPFILES) $(TSTDEPFILES) $(REGDEPFILES)

clean:
	@for file in $(OBJFILES) $(DEPFILES) $(TSTFILES) $(TSTDEPFILES) $(REGFILES) $(REGDEPFILES) pdclib.a pdclib.tgz scanf_testdata_*; do if [ -f $$file ]; then rm $$file; fi; done

srcdist:
	@tar czf pdclib.tgz $(ALLFILES)

todos:
	-@for file in $(ALLFILES); do grep -H TODO $$file; done; true

fixmes:
	-@for file in $(ALLFILES); do grep -H FIXME $$file; done; true

find:
	@find functions/ includes/ internals/ platform/ -name "*\.[ch]" -type f | xargs grep $$FIND

links:
	@echo "Linking platform/$(PLATFORM)..."
	@for file in $$(find platform/$(PLATFORM) -mindepth 2 -type f ! -path *.svn* -printf "%P\n"); do ln -s $$(dirname $$file | sed "s@[^/]*@..@g")/platform/$(PLATFORM)/$$file $$file; done

unlink:
	@echo "Unlinking platform files..."
	@for dir in $(PROJDIRS); do find $$dir -type l -exec rm {} +; done

help:
	@echo "Available make targets:"
	@echo
	@echo "all              - build pdclib.a"
	@echo "clean            - remove all object files, dependency files and test drivers"
	@echo "srcdist          - build pdclib.tgz (source tarball)"
	@echo "test             - test a single testdriver (Usage: FILE=\"test.[rt]\" make test)"
	@echo "tests            - build and run test drivers (link pdclib.a)"
	@echo "  testdrivers    - build but do not run test drivers"
	@echo "regtests         - build and run regression test drivers (link system clib)"
	@echo "  regtestdrivers - build but do not run regression test drivers"
	@echo "todos            - list all TODO comments in the sources"
	@echo "fixmes           - list all FIXME comments in the sources"
	@echo "find             - find a phrase in the sources (Usage: FIND=\"phrase\" make find)"
	@echo "links            - link platform files (development only)"
	@echo "unlink           - remove links to platform files (development only)"
	@echo "%.o              - build an individual object file"
	@echo "%.t              - build an individual test driver"
	@echo "%.r              - build an individual regression test driver"
	@echo "help             - print this list"
	@echo
	@echo "Any additional compiler flags you want to use can be passed as USERFLAGS"
	@echo "(Usage: USERFLAGS=\"flags\" make [...])."

%.o: %.c Makefile
	@echo " CC	$(patsubst functions/%,%,$@)"
	@$(CC) $(CFLAGS) -MMD -MP -I./includes -c $< -o $@

%_t: %.c Makefile pdclib.a
	@echo " CC	$(patsubst functions/%,%,$@)"
	@$(CC) $(CFLAGS) -MMD -MP -DTEST -I./includes $< pdclib.a -o $@

%_r: %.c Makefile
	@echo " CC	$(patsubst functions/%,%,$@)"
	@$(CC) $(CFLAGS) -MMD -MP -DTEST -DREGTEST $< -o $@

