#!/bin/bash

if [ $# != 1 ] ; then echo "serve la stringa di input";exit 1; fi

toReverse=$1;

reversed="";

for (( i=0 ; i < ${#toReverse} ; i=i+1)) ; do
	currentChar=${toReverse:$i:1};
	reversed="${currentChar}${reversed}";
done

echo ${reversed};
