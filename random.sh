#!/bin/bash

nCount=0;

RANDOM=$1;

toTest=$((RANDOM%10));

while [ ${toTest} != 2 ] ; do

echo ${toTest};

nCount=$((nCount+1));

toTest=$((RANDOM%10));

done

echo '---------------------';

echo ${nCount};
