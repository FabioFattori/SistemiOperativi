CFLAGS=-ansi -Wpedantic -Wall -D_REENTRANT -D_THREAD_SAFE -D_POSIX_C_SOURCE=200112L

LIBRARIES=-lpthread

all: 	 staffettasemplice_ConTurno.exe

staffettasemplice_ConTurno.exe:  staffettasemplice_ConTurno.o DBGpthread.o 
			gcc ${CFLAGS} -o staffettasemplice_ConTurno.exe staffettasemplice_ConTurno.o DBGpthread.o ${LIBRARIES}

staffettasemplice_ConTurno.o: staffettasemplice_ConTurno.c DBGpthread.h printerror.h
			gcc -c ${CFLAGS} staffettasemplice_ConTurno.c

DBGpthread.o: DBGpthread.c printerror.h
			gcc ${CFLAGS} -c DBGpthread.c  


.PHONY:	clean

clean:
	-rm -f staffettasemplice_ConTurno.o DBGpthread.o staffettasemplice_ConTurno.exe


