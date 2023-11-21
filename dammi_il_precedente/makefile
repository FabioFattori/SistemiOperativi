CFLAGS=-ansi -Wpedantic -Wall -Werror
LFLAGS=

all: main.exe

main.exe: main.o dammi_il_precedente.o
	gcc ${LFLAGS} -o main.exe main.o dammi_il_precedente.o -lm
	
main.o: main.c dammi_il_precedente.h
	gcc -c ${CFLAGS} main.c
dammi_il_precedente.o: dammi_il_precedente.c
	gcc -c ${CFLAGS} dammi_il_precedente.c

.PHONY: clean

clean: rm -f dammi_il_precedente.o main.o main.exe *~core
