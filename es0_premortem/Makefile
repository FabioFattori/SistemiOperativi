# Makefile per premortem.c

# a causa dell'uso di pthread occorrerebbe compilare
# col flag -D_REENTRANT oppure con  -D_THREAD_SAFE
# Li metto entrambi.
# Per evidenziare che servono, ho inserito i flag anche direttamente nel codice
# Inoltre, per usare la funzione usleep bisogna definire il simbolo _DEFAULT_SOURCE

CFLAGS=-ansi -Wpedantic -Wall -D_REENTRANT -D_THREAD_SAFE -D_DEFAULT_SOURCE -D_POSIX_C_SOURCE=200112L
LIBRARIES=-lpthread

all: 	es0_premortem.exe 

es0_premortem.exe: es0_premortem.o
	gcc -o es0_premortem.exe es0_premortem.o ${LIBRARIES}

es0_premortem.o: es0_premortem.c
	gcc -c ${CFLAGS} es0_premortem.c


.PHONY:	clean

clean:
	rm -f es0_premortem.o es0_premortem.exe 

