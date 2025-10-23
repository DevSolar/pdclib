SUPPORTED:=x86_64-linux-gcc x86_64-win32-gcc aarch64-linux-clang m68k-amigaos-vbcc

ifeq ($(filter $(PLATFORM),$(SUPPORTED)),)
    $(info Please set PLATFORM to one of the supported target platforms.)
    $(info Supported are:)
    $(foreach dir,$(patsubst platform/%,%,$(SUPPORTED)),$(info - $(dir)))
ifeq ($(PLATFORM),)
    $(error No platform)
else
    $(error Unsupported platform '$(PLATFORM)')
endif
endif

OBJ:=$(foreach file,$(filter-out src/_excluded/%,$(wildcard src/**/*.c)),$(patsubst %.c,bin/obj/%.o,$(notdir $(file))))
TST:=$(foreach file,$(wildcard src/**/*.c),$(patsubst %.c,bin/tst/%,$(notdir $(file))))
RTST:=$(foreach file,$(wildcard src/**/*.c),$(patsubst %.c,bin/rtst/%,$(notdir $(file))))
TOOLS:=$(patsubst tools/%.c,bin/tools/%,$(wildcard tools/*.c))

DIRS:=bin/obj bin/tst bin/rtst bin/tools

.PHONY: all clean tests regtests

include platform/$(PLATFORM)/settings.mk

all: regtests tests $(TOOLS)

clean:
	@$(RM) bin

$(DIRS):
	@$(MKDIR) $@

pdclib: bin/$(ARTARGET)

tests: $(TST)
	@$(foreach driver,$(TST),echo $(driver)...; $(driver);)

regtests: $(RTST)
	@$(foreach driver,$(RTST),echo $(driver)...; $(driver);)

bin/$(ARTARGET): $(OBJ)
	@$(AR) $(ARFLAGS) $@ $^

bin/obj/%.o: src/*/%.c Makefile platform/$(PLATFORM)/settings.mk | bin/obj
	@$(CC) $(CFLAGS) -Iinclude -Iplatform/$(PLATFORM)/include -c $< -o $@

bin/tools/%: tools/%.c Makefile platform/$(PLATFORM)/settings.mk | bin/tools
	@$(CC) $(CFLAGS) $< -o $@

bin/tst/%: src/*/%.c Makefile platform/$(PLATFORM)/settings.mk | bin/tst
	@$(CC) $(CFLAGS) -Iinclude -Iplatform/$(PLATFORM)/include -Itest_support -DTEST $< -o $@

bin/rtst/%: src/*/%.c Makefile platform/$(PLATFORM)/settings.mk | bin/rtst
	@$(CC) $(CFLAGS) -Itest_support -DTEST -DREGTEST $< -o $@
