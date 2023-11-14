#!/bin/bash

if [[ $# != 1 ]]; then echo "int param required"; fi
if [[ $1 -le 0 ]]; then echo $1; exit 0; fi

./discendenti.sh $(($1 - 1)) ; 
echo $1;
wait $!;

exit 0;
