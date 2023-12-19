CFLAGS=-ansi -Wpedantic -Wall -D_REENTRANT -D_THREAD_SAFE -D_POSIX_C_SOURCE=200112L

LIBRARIES=-lpthread

all: 	prod_ConsA+B.exe

prod_ConsA+B.exe: prod_ConsA+B.o DBGpthread.o
	gcc ${CFLAGS} -o prod_ConsA+B.exe prod_ConsA+B.o DBGpthread.o ${LIBRARIES}

prod_ConsA+B.o: prod_ConsA+B.c DBGpthread.h printerror.h
	gcc ${CFLAGS} -c prod_ConsA+B.c 

DBGpthread.o: DBGpthread.c printerror.h
	gcc ${CFLAGS} -c DBGpthread.c 

.PHONY:	clean

clean:
	-rm -f prod_ConsA+B.o DBGpthread.o prod_ConsA+B.exe


