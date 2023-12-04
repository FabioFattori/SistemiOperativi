#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Usage: $0 <project_name>"
    exit 1
fi
if [ -d $1 ]; then
    echo "Error: $1 already exists"
    exit 2
fi

mkdir $1
cd $1;
touch main.c && touch Makefile
echo "#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char const *argv[])
{
    /* code */
    return 0;
}" >> main.c

echo "CFLAGS=-ansi -Wpedantic -Wall -D_REENTRANT -D_THREAD_SAFE -D_DEFAULT_SOURCE -D_POSIX_C_SOURCE=200112L
LIBRARIES=-lpthread
LFLAGS=

all: main.exe

main.exe: main.o
	gcc \${LFLAGS} -o main.exe main.o -lm \${LIBRARIES}
	
main.o: main.c
	gcc -c \${CFLAGS} main.c


.PHONY: clean

clean: rm -f main.o main.exe *~core" >> Makefile;

cd ..
echo "Project created!";
exit 0;
