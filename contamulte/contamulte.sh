#!/bin/bash

if [[ -f "tmp.txt" ]];then rm "tmp.txt"; fi

touch tmp.txt

while read arg nome codice data; do
	OUT=`grep ${codice} tmp.txt`;
	
	if [[ $OUT == "" ]]; then 
		# new codice trovato
	
		echo "${codice} 1" >> tmp.txt;
	else 
		OUT=${OUT#${codice} };
		NEWOUT=$((OUT+1));
		sed -i "/${codice}/d" tmp.txt
		echo "${codice} ${NEWOUT}" >> tmp.txt
	fi
done

cat tmp.txt
