CFLAGS=-ansi -Wpedantic -Wall -Werror
LFLAGS=

all: 	main.exe

main.exe: 	main.o 
			gcc ${LFLAGS} -o main.exe main.o -lm

main.o: main.c
		gcc -c ${CFLAGS} -D'allocaVettore(PTR)=do { PTR=(int32_t*)malloc(10*sizeof(int32_t));if(PTR!=NULL) { int j; for(j=0;j<10;j++) {PTR[j]=-1000+j; } } } while(0)'  main.c

.PHONY: clean

clean:
		rm -f main.exe main.o *~ core
