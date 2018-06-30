TARGET := get-uctypes
# All source files of the project
SRCFILES := $(wildcard *.c)
# All header files of the project
HDRFILES := $(wildcard *.h)
# All object files in the project
OBJFILES := $(patsubst %.c,%.o,$(SRCFILES))
# All test drivers (_t)
TSTFILES := $(patsubst %.c,%_t,$(SRCFILES))
# All dependency files (.d)
DEPFILES := $(patsubst %.c,%.d,$(SRCFILES))
# All test driver dependency files (_t.d)
TSTDEPFILES := $(patsubst %,%.d,$(TSTFILES))
# All test driver dependency files (_t.d)

WARNINGS := -Wall -Wextra -pedantic -Wno-unused-parameter -Wshadow -Wpointer-arith -Wcast-align -Wwrite-strings -Wmissing-prototypes -Wmissing-declarations -Wredundant-decls -Wnested-externs -Winline -Wno-long-long -Wuninitialized -Wstrict-prototypes -Wdeclaration-after-statement
CFLAGS := -g -std=c99 $(WARNINGS) $(USERFLAGS) -I.

.PHONY: all clean tests

all: $(TARGET)

$(TARGET): $(OBJFILES)
	@echo " CC      $@"
	@$(CC) $^ -o $@
	@echo

tests: testdrivers
	-@rc=0; count=0; failed=""; for file in $(TSTFILES); do echo " TST     $$file"; ./$$file; test=$$?; if [ $$test != 0 ]; then rc=`expr $$rc + $$test`; failed="$$failed $$file"; fi; count=`expr $$count + 1`; done; echo; echo "Tests executed: $$count  Tests failed: $$rc"; echo; for file in $$failed; do echo "Failed: $$file"; done; echo

testdrivers: $(TSTFILES)
	@echo

-include $(DEPFILES) $(TSTDEPFILES)

clean:
	-@$(RM) $(wildcard $(OBJFILES) $(DEPFILES) $(TSTFILES) $(TSTDEPFILES) $(TARGET) aux.a)

%.o: %.c Makefile
	@echo " CC      $@"
	@$(CC) $(CFLAGS) -MMD -MP -c $< -o $@

%_t: %.c Makefile aux.a
	@echo " CC      $@"
	@$(CC) $(CFLAGS) -MMD -MP -DTEST $< aux.a -o $@

aux.a: $(OBJFILES)
	@ar rc $@ $^
