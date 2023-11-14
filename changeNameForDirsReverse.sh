#!/bin/bash

# set up the dir 

if [[ ! -d changeNameDir ]] ; then mkdir changeNameDir ; fi

cd changeNameDir;

rm -d *;

for (( i=0;${i}<10;i=${i}+1 )); do mkdir "1.${i}"; done

# solve the problem 

for dirName in `ls`; do
    newDigit=${dirName#*.};
    newDigit=$(( 9 - ${newDigit} ));
    mv ${dirName} "2.${newDigit}";
done 