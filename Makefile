.POSIX:

include config.mk

# search src/ and libs/ for c files
SRC =
OBJ = ${SRC:.c=.o}

# tests live in t/
TESTS = $(shell find t -name '*.c' )
# output location for tests
TESTOUT = bin
TESTO = $(patsubst %.c, $(TESTOUT)/%, $(TESTS))

# only defined when `make debug`
EXTRAFLAGS =

# default to compiling without debug symbols
all: atomos-ng

# compile each component, linking is handled by `icarus` rule
%.o: %.c
	@echo COMPILING CC $< to obj
	@${CC} -g -c ${CFLAGS} $< ${EXTRAFLAGS} -o $@

# compile and link main executable
atomos-ng:
	@echo compiling main CC -o $@
	@${CC} atomos-ng.c -o $@ ${LDFLAGS} ${EXTRAFLAGS} ${OBJ}

# clean up everything managed by make
clean:
	@echo cleaning objects and temporary files
	@find . -iname '*.o' -delete
	@echo cleaning executables
	@rm -f atomos-ng

run: atomos-ng
	`which time` -f "total wall clock time: %e (s)"  ./$<
	@echo
	make -s clean

.PHONY: all clean atomos-ng run

