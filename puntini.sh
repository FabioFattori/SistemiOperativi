#!/bin/bash

if [ $# != 1 ]; then echo "pirla mi serve l'intero";exit 1; fi

for (( i=0; i < $1 ; i=i+1)) ; do
	echo -n ".$$";
	sleep 1;
done 
