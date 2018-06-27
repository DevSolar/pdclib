TARGET := get-uctypes
# All source files of the project
SRCFILES := $(wildcard *.c)
# All header files of the project
HDRFILES := $(wildcard *.h)
# All object files in the project
OBJFILES := $(patsubst %.c,%.o,$(SRCFILES))
# All dependency files (.d)
DEPFILES := $(patsubst %.c,%.d,$(SRCFILES))
# All test driver dependency files (_t.d)

WARNINGS := -Wall -Wextra -pedantic -Wno-unused-parameter -Wshadow -Wpointer-arith -Wcast-align -Wwrite-strings -Wmissing-prototypes -Wmissing-declarations -Wredundant-decls -Wnested-externs -Winline -Wno-long-long -Wuninitialized -Wstrict-prototypes -Wdeclaration-after-statement -Werror
CFLAGS := -g -std=c99 $(WARNINGS) $(USERFLAGS)

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJFILES)
	@echo " CC	$@"
	@$(CC) $^ -o $@
	@echo

-include $(DEPFILES)

clean:
	-@$(RM) $(wildcard $(OBJFILES) $(DEPFILES) $(TARGET))

%.o: %.c Makefile
	@echo " CC	$@"
	@$(CC) $(CFLAGS) -MMD -MP -c $< -o $@
