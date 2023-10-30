#!/bin/bash

/*da errore */
for (( i=0; ls ./ ; i=i+1 )) ; do 
	echo "${i}" ; 
done

i=0;
for name in `ls ./` ; do
	i=$((i+1));
	echo ${i};
done 
