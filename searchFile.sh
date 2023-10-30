#!/bin/bash

for car in {c,d,e,f,g} ; do 
	for nomeFile in /usr/include/?${car}*;do
		if [[ -e ${nomeFile} && ( ${#nomeFile} -lt 18 || ${#nomeFile} -gt 23 ) ]];then
			echo ${nomeFile};
		fi
	done
done
