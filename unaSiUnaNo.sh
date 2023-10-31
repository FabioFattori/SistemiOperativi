#!/bin/bash
File=$1;

i=0
checkEnter=0;
nRigheStampate=0;

while read line; do
    if [ ${checkEnter} == 1 ]; then
        echo $line ;
        nRigheStampate=$((nRigheStampate+1));
        checkEnter=$((checkEnter-2));
    fi
    i=$((i+1));
    checkEnter=$((checkEnter+1));
done < ${File}

echo "---------------------"

echo "nRighe totali: " $i
echo "nRighe stampate: " $nRigheStampate