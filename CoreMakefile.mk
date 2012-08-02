TARGETS = pdclib

ifndef PDCLIB_PLATFORM_EXT
endif

ifndef PDCLIB_MALLOC
    $(error malloc to use unspecified. Set PDCLIB_MALLOC.)
endif

ifeq ($(PDCLIB_MALLOC),solar)
    pdclib_SOURCEDIRS += opt/malloc-solar
else
ifeq ($(PDCLIB_MALLOC),ptmalloc3)
    pdclib_SOURCEDIRS += opt/ptmalloc3
else
    $(error Bad malloc specified. Supported: solar, ptmalloc3)
endif
endif

# No: -Wcast-align; spurious for uses of char* to do pointer arithmetic
# No: -Winline; generates spirous errors on -Os builds
WARNINGS := -Wall -Wextra -pedantic -Wno-unused-parameter -Wshadow -Wpointer-arith -Wwrite-strings -Wmissing-prototypes -Wmissing-declarations -Wredundant-decls -Wnested-externs -Wno-long-long -Wuninitialized -Wstrict-prototypes

pdclib_COMFLAGS += -ffreestanding $(WARNINGS)
pdclib_CFLAGS   += -std=c11
pdclib_SOURCEDIRS 	+= 	functions/_PDCLIB functions/ctype functions/inttypes  \
					 	functions/locale functions/stdio functions/stdlib	  \
					 	functions/string/
pdclib_OUT_TYPE   	+= archive
pdclib_INCLUDE_DIRS	+= $(pdclib_SOURCE_DIR)/includes $(pdclib_SOURCE_DIR)/internals

ifdef PDCLIB_OPT_NOTHREAD
	pdclib_SOURCEDIRS   += opt/nothread
	pdclib_INCLUDE_DIRS += $(pdclib_SOURCE_DIR)/opt/nothread
endif