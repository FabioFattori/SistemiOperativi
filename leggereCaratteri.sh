#!/bin/bash

exec {FD}< /usr/include/stdio.h;
if [ $? == 0 ]; then 
	nCar=0;
	while read -u ${FD} -N 1 -r A; do 
		((nCar=${nCar}+1))
	done 
	exec {FD}>&-
	echo ${nCar};
fi


