#!/bin/bash

if [[ -e tmp.txt ]]; then rm tmp.txt; fi

touch tmp.txt;
exec {fd}<cadutevic.txt

while read -r -u ${fd} anno luogo motivo danno ;do
	OUT=`grep ${motivo} tmp.txt`;
	if [[ ${OUT} == "" ]];then
		# new motivo founded
		echo "${motivo} 1" >> tmp.txt 
	else 
		# old motivo founded
		OUT=${OUT#"${motivo}"};
		OUT=$((${OUT}+1));
		sed -i "/${motivo}/d" tmp.txt;
		echo "${motivo} ${OUT}" >> tmp.txt
	fi
done

cat tmp.txt
