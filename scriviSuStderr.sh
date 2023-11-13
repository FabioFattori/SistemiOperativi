#!/bin/bash

while read row; do
    toPrintStderr="${row%% *}" 

    if [ ${toPrintStderr} == "exit0" ] ; then exit 0 ; fi

    echo "${toPrintStderr}" 1>&2 
    echo "evviva instead of word"
done 