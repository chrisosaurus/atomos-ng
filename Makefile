.POSIX:

include config.mk

all: atomos-ng

# compile and link main executable
atomos-ng:
	@echo compiling main CC -o $@
	@${CC} atomos-ng.c -o $@ ${LDFLAGS}

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

