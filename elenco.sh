#!/bin/bash

LungNomiDirectory=0;
nFile=0;

for name in  `ls ./` ; do
	echo ${name};
	if [[ -d ${name} ]] ; then
		((LungNomiDirectory=${LungNomiDirectory}+${#name}))
	else 
		nFile=$((nFile+1))
	
	fi 

done

echo "nFile => " ${nFile};
echo "LungNomiDirectory => " ${LungNomiDirectory};
