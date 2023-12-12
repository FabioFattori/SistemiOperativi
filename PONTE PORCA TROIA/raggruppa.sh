#!/bin/bash

if [[ -e tmp.txt ]];then rm tmp.txt;  fi

touch tmp.txt;

exec {FD}<cadutevic.txt;

while read -r -u ${FD} year luogo motivo danni; do

	OUT=`grep ${motivo} tmp.txt`;
	
	if [[ $OUT == "" ]]; then 
		# new motivo trovato
	
		echo "${motivo} 0" >> tmp.txt;
	else 
		OUT=${OUT#${motivo} };
		NEWOUT=$((OUT+1));
		sed -i "/${motivo}/d" tmp.txt
		echo "${motivo} ${NEWOUT}" >> tmp.txt
	fi
	
done
	
cat tmp.txt
