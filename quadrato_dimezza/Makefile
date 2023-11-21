CFLAGS=-ansi -Wpedantic -Wall -Werror
LFLAGS=

all: 	main.exe

main.exe: 	main.o dimezza.o quadrato.o
			gcc ${LFLAGS} -o main.exe main.o dimezza.o quadrato.o -lm

main.o: 	main.c dimezza.h quadrato.h
			gcc -c ${CFLAGS} main.c

dimezza.o: 	dimezza.c
			gcc -c ${CFLAGS} dimezza.c

quadrato.o: quadrato.c
			gcc -c ${CFLAGS} quadrato.c

.PHONY: 	clean

clean:
			rm -f main.exe main.o dimezza.o quadrato.o *~ core
