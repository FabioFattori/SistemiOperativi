#!/bin/bash

# set up the dir 

if [[ ! -d changeNameDir ]] ; then mkdir changeNameDir ; fi

cd changeNameDir;

rm -d *;

for (( i=0;${i}<10;i=${i}+1 )); do mkdir "1.${i}"; done

# resolve the problem


for dirName in `ls`; do 
	mv ${dirName} "2.${dirName#*.}"
done
