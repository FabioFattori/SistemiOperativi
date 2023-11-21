CFLAGS=-ansi -Wpedantic -Wall -Werror
LFLAGS=

all: casuale.exe

casuale.exe: casuale.o
	gcc ${LFLAGS} -o casuale.exe casuale.o -lm

casuale.o: casuale.c
	gcc -c ${CFLAGS} casuale.c 
	
.PHONY: clean

clean: rm -f casuale.exe casuale.o *~ core 
