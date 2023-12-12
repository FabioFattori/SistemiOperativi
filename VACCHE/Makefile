CFLAGS=-ansi -Wpedantic -Wall -D_REENTRANT -D_THREAD_SAFE -D_DEFAULT_SOURCE -D_POSIX_C_SOURCE=200112L
LIBRARIES=-lpthread
DBGPTHREADFUNCTION_SOURCE_DIR=/home/studente/Desktop/SistemiOperativi/
LFLAGS=

all: vacche.exe

vacche.exe: vacche.o DBGpthread.o
	gcc ${LFLAGS} -o vacche.exe vacche.o DBGpthread.o -lm ${LIBRARIES}
	
vacche.o: vacche.c ${DBGPTHREADFUNCTION_SOURCE_DIR}DBGpthread.h ${DBGPTHREADFUNCTION_SOURCE_DIR}printerror.h
	gcc -c ${CFLAGS} vacche.c

DBGpthread.o: ${DBGPTHREADFUNCTION_SOURCE_DIR}DBGpthread.c ${DBGPTHREADFUNCTION_SOURCE_DIR}printerror.h
	gcc  -c ${DBGPTHREADFUNCTION_SOURCE_DIR}DBGpthread.c -I${DBGPTHREADFUNCTION_SOURCE_DIR}

.PHONY: clean

clean: rm -f main.o DBGpthread.o main.exe *~core
