CFLAGS=-ansi -Wpedantic -Wall -D_REENTRANT -D_THREAD_SAFE -D_DEFAULT_SOURCE -D_POSIX_C_SOURCE=200112L
LIBRARIES=-lpthread
LFLAGS=

all: main.exe

main.exe: main.o DBGpthread.o
	gcc ${LFLAGS} -o main.exe main.o DBGpthread.o -lm ${LIBRARIES}
	
main.o: main.c DBGpthread.h printerror.h
	gcc -c ${CFLAGS} main.c

DBGpthread.o: DBGpthread.c printerror.h
	gcc  -c DBGpthread.c 

.PHONY: clean

clean: rm -f main.o DBGpthread.o main.exe *~core
