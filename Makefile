# This is a list of all non-source files that are part of the distribution.
AUXFILES := Makefile Readme.txt

SRCFILES := $(shell find . -name "*.c" -mindepth 1 -maxdepth 3)
HDRFILES := $(shell find . -name "*.h" -mindepth 1 -maxdepth 3)
OBJFILES := $(patsubst %.c,%.o,$(SRCFILES))
DEPFILES := $(patsubst %.c,%.d,$(SRCFILES))
ALLFILES := $(SRCFILES) $(HDRFILES) $(AUXFILES)

CPPFLAGS  := -MMD -MP
CFLAGS    := -g -std=c99 -I./internals/

.PHONY: all clean dist

all: $(OBJFILES)
	ar r pdclib.a $(OBJFILES)

-include $(DEPFILES)

clean:
	-@for file in $(OBJFILES) $(DEPFILES) pdclib.a; do if [ -f $$file ]; then rm $$file; fi; done

dist:
	@tar czf pdclib.tgz $(ALLFILES)

%.o: %.c Makefile
	$(CC) $(MODE) -c $(CPPFLAGS) $(CFLAGS) $< -o $@

