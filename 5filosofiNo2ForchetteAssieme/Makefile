CFLAGSCONSTRERROR=-ansi -Wpedantic -Wall -D_REENTRANT -D_THREAD_SAFE -D_POSIX_C_SOURCE=200112L
CFLAGS=-ansi -Wpedantic -Wall -D_REENTRANT -D_THREAD_SAFE 

LIBRARIES=-lpthread

all: 	 5filosofiNo2ForchetteAssieme.exe

5filosofiNo2ForchetteAssieme.exe:  5filosofiNo2ForchetteAssieme.o DBGpthread.o 
	gcc -o 5filosofiNo2ForchetteAssieme.exe 5filosofiNo2ForchetteAssieme.o DBGpthread.o ${LIBRARIES}

5filosofiNo2ForchetteAssieme.o: 5filosofiNo2ForchetteAssieme.c DBGpthread.h printerror.h
	gcc -c ${CFLAGS} 5filosofiNo2ForchetteAssieme.c 

DBGpthread.o: DBGpthread.c printerror.h
	gcc ${CFLAGSCONSTRERROR} -c DBGpthread.c 


.PHONY:	clean

clean:
	-rm -f 5filosofiNo2ForchetteAssieme.o DBGpthread.o 5filosofiNo2ForchetteAssieme.exe


