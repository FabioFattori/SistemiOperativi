#!/bin/bash
exec {FD}< mioFIle.txt

if [ $? == 0 ]; then
	while read -u ${FD} parola1; do
		if [[ ${parola1} != "" ]] ; then 
			echo "${parola1}";
		fi
	done
fi
