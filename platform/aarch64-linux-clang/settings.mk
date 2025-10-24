DEPS:=$(patsubst %.o,%.d,$(OBJ))
TDEPS:=$(patsubst %,%.d,$(TST))

CC:=clang
CFLAGS:=-g -O2 -std=c99 -MMD -MP -Weverything -Wno-reserved-macro-identifier
RM:=rm -rf
MKDIR:=mkdir -p
AR:=ar
ARFLAGS:=rc
ARTARGET:=pdclib.a

-include $(DEPS) $(TDEPS)
