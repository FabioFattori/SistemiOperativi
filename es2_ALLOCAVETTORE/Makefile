CFLAGS=-ansi -Wpedantic -Wall -Werror
LFLAGS=

all: 	main.exe

main.exe: 	main.o 
			gcc ${LFLAGS} -o main.exe main.o -lm

main.o: main.c macro.h
		gcc -c ${CFLAGS} main.c

.PHONY: clean

clean:
		rm -f main.exe main.o *~ core
