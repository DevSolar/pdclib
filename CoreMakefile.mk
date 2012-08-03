TARGETS = pdclib

ifndef PDCLIB_PLATFORM_EXT
endif

ifndef PDCLIB_MALLOC
    $(error malloc to use unspecified. Set PDCLIB_MALLOC.)
endif

ifeq ($(PDCLIB_MALLOC),solar)
    pdclib_SOURCEDIRS += opt/malloc-solar
else
ifeq ($(PDCLIB_MALLOC),dlmalloc)
    pdclib_SOURCEDIRS += opt/dlmalloc
else
    $(error Bad malloc specified. Supported: solar, ptmalloc3)
endif
endif

# No: -Wcast-align;      spurious for uses of char* to do pointer arithmetic
# No: -Winline;          generates spirous errors on -Os builds
# No: -Wredundant-decls; redefinition of functions is legal and sometimes required
#         (especially applicable to PDCLib sources)
# -Wno-unused-parameter; unused parameters are common in some interfaces
WARNINGS := -Wall -Wextra -pedantic -Wshadow -Wpointer-arith -Wwrite-strings -Wmissing-prototypes -Wmissing-declarations -Wnested-externs -Wno-long-long -Wuninitialized -Wstrict-prototypes -Wno-unused-parameter

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

ifdef PDCLIB_OPT_NOTIME
	pdclib_SOURCEDIRS += opt/notime
endif