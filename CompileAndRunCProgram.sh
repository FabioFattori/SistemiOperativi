#!/bin/bash

if [[ $# != 1 ]]; then echo "C file needed"; exit 1; fi
if [[ ! -f $1 ]]; then echo "$1 doesn't exits"; exit 2; fi

fileC=$1;
fileWithOutputExtension=${fileC//".c"/".o"};
exetutable=${fileC//".c"/".exe"};

gcc -c -ansi -Wpedantic -Wall $1 && gcc -o ${exetutable} ${fileWithOutputExtension} && ./${exetutable}
