# $Id$

# This is where you chose which platform to compile for (see 'make links' / './platform')
PLATFORM := example_cygwin

# This is a list of all non-source files that are part of the distribution.
AUXFILES := Makefile Readme.txt

# Directories belonging to the project
PROJDIRS := functions includes internals
# All source files of the project
SRCFILES := $(shell find $(PROJDIRS) -mindepth 1 -maxdepth 3 -name "*.c")
# All header files of the project
HDRFILES := $(shell find $(PROJDIRS) -mindepth 1 -maxdepth 3 -name "*.h")
# All .c files in functions/_PDCLIB that do not have a regression test driver
INTFILES := _Exit atomax digits open print scan remove rename seed stdinit strtox_main strtox_prelim cleanstream fflush filemode eol errno seek prepread prepwrite allocpages
# All object files in the library
OBJFILES := $(patsubst %.c,%.o,$(SRCFILES))
# All test drivers (.t)
TSTFILES := $(patsubst %.c,%.t,$(SRCFILES))
# All regression test drivers (.r)
REGFILES := $(filter-out $(patsubst %,functions/_PDCLIB/%.r,$(INTFILES)),$(patsubst %.c,%.r,$(SRCFILES)))
# All dependency files (.d)
DEPFILES := $(patsubst %.c,%.d,$(SRCFILES))
# All files belonging to the source distribution
ALLFILES := $(SRCFILES) $(HDRFILES) $(AUXFILES)

# All files in platform/$(PLATFORM)/functions/_PDCLIB (for development only)
PATCHFILES1 := $(shell ls platform/$(PLATFORM)/functions/_PDCLIB/*.c)
# All files in platform/$(PLATFORM)/functions/stdlib (for development only)
PATCHFILES2 := $(shell ls platform/$(PLATFORM)/functions/stdlib/*.c)
# All files in platform/$(PLATFORM)/functions/stdio (for development only)
PATCHFILES3 := $(shell ls platform/$(PLATFORM)/functions/stdio/*.c)

WARNINGS := -Wall -Wextra -pedantic -Wno-unused-parameter -Wshadow -Wpointer-arith -Wcast-align -Wwrite-strings -Wmissing-prototypes -Wmissing-declarations -Wredundant-decls -Wnested-externs -Winline -Wno-long-long -fno-builtin 
CFLAGS := -g -std=gnu99 -I./internals $(WARNINGS) $(USERFLAGS)

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

-include $(DEPFILES)

clean:
	@for file in $(OBJFILES) $(DEPFILES) $(TSTFILES) $(REGFILES) pdclib.a pdclib.tgz; do if [ -f $$file ]; then rm $$file; fi; done

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
	@cd internals && ln -s ../platform/$(PLATFORM)/internals/_PDCLIB_config.h
	@cd includes && ln -s ../platform/$(PLATFORM)/includes/float.h
	@cd functions/_PDCLIB && for file in $(PATCHFILES1); do basfile=`basename $$file`; if [ ! -f $$basfile ]; then ln -s `ls ../../$$file` .; fi; done
	@cd functions/stdlib && for file in $(PATCHFILES2); do basfile=`basename $$file`; if [ ! -f $$basfile ]; then ln -s `ls ../../$$file` .; fi; done
	@cd functions/stdio && for file in $(PATCHFILES3); do basfile=`basename $$file`; if [ ! -f $$basfile ]; then ln -s `ls ../../$$file` .; fi; done

unlink:
	@echo "Unlinking platform files..."
	@if [ -f internals/_PDCLIB_config.h ]; then rm internals/_PDCLIB_config.h; fi
	@if [ -f includes/float.h ]; then rm includes/float.h; fi
	@cd functions/_PDCLIB && for file in $(PATCHFILES1); do basfile=`basename $$file`; if [ -f $$basfile ]; then rm $$basfile; fi; done
	@cd functions/stdlib && for file in $(PATCHFILES2); do basfile=`basename $$file`; if [ -f $$basfile ]; then rm $$basfile; fi; done
	@cd functions/stdio && for file in $(PATCHFILES3); do basfile=`basename $$file`; if [ -f $$basfile ]; then rm $$basfile; fi; done

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
	@$(CC) $(CFLAGS) -MMD -MP -MT "$*.d $*.t" -I./includes -c $< -o $@

%.t: %.c Makefile pdclib.a
	@echo " CC	$(patsubst functions/%,%,$@)"
	@$(CC) $(CFLAGS) -DTEST -I./includes $< pdclib.a -o $@

%.r: %.c Makefile
	@echo " CC	$(patsubst functions/%,%,$@)"
	@$(CC) $(CFLAGS) -Wno-format -DTEST -DREGTEST $< -o $@

