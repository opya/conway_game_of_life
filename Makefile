CFLAGS = -Wall -Werror -g -pedantic

all:
	clang ${CFLAGS} cgol.c -o cgol
