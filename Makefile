CC = gcc
CFLAGS = -Wall -Werror
EXE = mbox-parser

SRC = $(wildcard src/*.c)
OBJ = $(SRC:%.c=%.o)
DEP = $(OBJ:%.o=%.d)

LIBS = $(addprefix -l,)

PREFIX = /usr/local

.PHONY: all
all: debug

.PHONY: debug
debug: CFLAGS += -g
debug: $(EXE)

.PHONY: remake
remake: clean debug
.NOTPARALLEL: remake

.PHONY: release
release: CFLAGS += -O3 -DNDEBUG
release: clean $(EXE)
.NOTPARALLEL: release

.PHONY: clean
clean:
	@rm -f $(OBJ) $(DEP) $(EXE)

.PHONY: install
install: all
	@install $(EXE) $(PREFIX)/bin

.PHONY: uninstall
uninstall:
	@-rm $(PREFIX)/bin/$(EXE)

$(EXE): $(OBJ)
	@$(CC) -o $@ $^ $(LIBS)

-include $(DEP)

%.o: %.c
	@echo Compiling $<...
	@$(CC) $(CFLAGS) -c -o $@ $<
