DEPS:=$(patsubst %.o,%.d,$(OBJ))
TDEPS:=$(patsubst %,%.d,$(TST))

CC:=gcc
CFLAGS:=-g -O2 -std=c99 -MMD -MP -Wall -Wextra
RM:=rm -rf
MKDIR:=mkdir -p
AR:=ar
ARFLAGS:=rc
ARTARGET:=pdclib.a

-include $(DEPS) $(TDEPS)
