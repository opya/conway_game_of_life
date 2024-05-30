CFLAGS = -Wall -Werror -g

all:
	clang ${CFLAGS} cgol.c -o cgol
