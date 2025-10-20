CC:=vc
DEPS:=$(patsubst %.o,%.deps,$(SRC))

CC:=vc
CFLAGS:=+aos68k -g -O2 -c99 -deps -deps-for-libs -warn=-1
RM:=Delete ALL QUIET
MKDIR:=mkdir NOICON
AR:=lha
ARFLAGS:=-q a $@ $(^D) $^
ARTARGET:=pdclib.lha

-include $(DEPS)
