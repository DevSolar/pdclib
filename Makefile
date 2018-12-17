# This is a list of all non-source files that are part of the distribution.
AUXFILES := Makefile Readme.txt

# Directories belonging to the project
PROJDIRS := functions include platform/example
# Directory where binaries should be written
BUILDDIR := .
# All source files of the project
SRCFILES := $(shell find -L $(PROJDIRS) -type f -name "*.c")
# All header files of the project
HDRFILES := $(shell find -L $(PROJDIRS) -type f -name "*.h")
# All object files in the library
OBJFILES := $(patsubst %.c,$(BUILDDIR)/%.o,$(SRCFILES))
# All test drivers (.t)
TSTFILES := $(patsubst %.c,$(BUILDDIR)/%_t,$(SRCFILES))
# All regression test drivers (.r)
REGFILES := $(patsubst %.c,$(BUILDDIR)/%_r,$(SRCFILES))
# All library dependency files (.d)
DEPFILES := $(patsubst %.c,$(BUILDDIR)/%.d,$(SRCFILES))
# All test driver dependency files (_t.d)
TSTDEPFILES := $(patsubst %,$(BUILDDIR)/%.d,$(TSTFILES))
# All regression test driver dependency files (_r.d)
REGDEPFILES := $(patsubst %,$(BUILDDIR)/%.d,$(REGFILES))
# All files belonging to the source distribution
ALLFILES := $(SRCFILES) $(HDRFILES) $(AUXFILES)

WARNINGS := -Wall -Wextra -pedantic -Wno-unused-parameter -Wshadow -Wpointer-arith -Wcast-align -Wwrite-strings -Wmissing-prototypes -Wmissing-declarations -Wredundant-decls -Wnested-externs -Winline -Wno-long-long -Wuninitialized -Wstrict-prototypes -Wdeclaration-after-statement
CFLAGS := -DUSE_DL_PREFIX -DDLMALLOC_EXPORT= -fno-builtin -g -std=c99 -I./testing -I./platform/example/include $(WARNINGS) $(USERFLAGS)

.PHONY: all clean srcdist tests testdrivers regtests regtestdrivers todos fixmes help

all: $(BUILDDIR)/pdclib.a testdrivers regtestdrivers
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
	@echo
	@echo "========"
	@echo "FIXME's:"
	@echo "========"
	@echo
	@$(MAKE) fixmes
	@echo
	@echo "======="
	@echo "TODO's:"
	@echo "======="
	@echo
	@$(MAKE) todos | head
	@echo "..."

$(BUILDDIR)/pdclib.a: $(OBJFILES)
	@echo " AR	$@"
	@ar rc $(BUILDDIR)/pdclib.a $?
	@echo

tests: testdrivers
	-@rc=0; count=0; failed=""; for file in $(TSTFILES); do echo " TST	$$file"; $$file; test=$$?; if [ $$test != 0 ]; then rc=`expr $$rc + $$test`; failed="$$failed $$file"; fi; count=`expr $$count + 1`; done; echo; echo "Tests executed (linking PDCLib): $$count  Tests failed: $$rc"; echo; for file in $$failed; do echo "Failed: $$file"; done; echo

testdrivers: $(TSTFILES)
	@echo

regtests: regtestdrivers
	-@rc=0; count=0; failed=""; for file in $(REGFILES); do echo " RTST	$$file"; $$file; test=$$?; if [ $$test != 0 ]; then rc=`expr $$rc + $$test`; failed="$$failed $$file"; fi; count=`expr $$count + 1`; done; echo; echo "Tests executed (linking system libc): $$count  Tests failed: $$rc"; echo; for file in $$failed; do echo "Failed: $$file"; done; echo

regtestdrivers: $(REGFILES)
	@echo

-include $(DEPFILES) $(TSTDEPFILES) $(REGDEPFILES)

clean:
	-@$(RM) $(wildcard $(OBJFILES) $(DEPFILES) $(TSTFILES) $(TSTDEPFILES) $(REGFILES) $(REGDEPFILES) $(BUILDDIR)/pdclib.a pdclib.tgz scanf_testdata_*)

srcdist:
	@tar czf pdclib.tgz $(ALLFILES)

todos:
	-@for file in $(ALLFILES:Makefile=); do grep -H TODO $$file; done; true

fixmes:
	-@for file in $(ALLFILES:Makefile=); do grep -H FIXME $$file; done; true

help:
	@echo "Available make targets:"
	@echo
	@echo "all              - build pdclib.a"
	@echo "clean            - remove all object files, dependency files and test drivers"
	@echo "srcdist          - build pdclib.tgz (source tarball)"
	@echo "tests            - build and run test drivers (link pdclib.a)"
	@echo "  testdrivers    - build but do not run test drivers"
	@echo "regtests         - build and run regression test drivers (link system clib)"
	@echo "  regtestdrivers - build but do not run regression test drivers"
	@echo "todos            - list all TODO comments in the sources"
	@echo "fixmes           - list all FIXME comments in the sources"
	@echo "%.o              - build an individual object file"
	@echo "%.t              - build an individual test driver"
	@echo "%.r              - build an individual regression test driver"
	@echo "help             - print this list"
	@echo
	@echo "Any additional compiler flags you want to use can be passed as USERFLAGS"
	@echo "(Usage: USERFLAGS=\"flags\" make [...])."
	@echo
	@echo "If you want to build out-of-source, you can specify BUILDDIR"
	@echo "(Usage: make [...] BUILDDIR=/path/to/binaries/)."

$(BUILDDIR)/platform/example/functions/_dlmalloc/malloc.o: platform/example/functions/_dlmalloc/malloc.c Makefile
	@echo " CC	$(patsubst functions/%,%,$@)"
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -Wno-cast-align -MMD -MP -I./include -c $< -o $@

$(BUILDDIR)/%.o: %.c Makefile
	@echo " CC	$(patsubst functions/%,%,$@)"
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -MMD -MP -I./include -c $< -o $@

$(BUILDDIR)/%_t: %.c Makefile $(BUILDDIR)/pdclib.a
	@echo " CC	$(patsubst functions/%,%,$@)"
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -MMD -MP -DTEST -I./include $< $(BUILDDIR)/pdclib.a -o $@

$(BUILDDIR)/%_r: %.c Makefile
	@echo " CC	$(patsubst functions/%,%,$@)"
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -Wno-deprecated-declarations -Wno-format -MMD -MP -DTEST -DREGTEST $< -o $@
