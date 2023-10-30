#!/bin/bash

exec {rows}< /usr/include/stdio.h;
if [ $? == 0 ]; then 
	while read -u ${rows} parola1 parola2 parola3 parola4 ; do 
		echo "${parola3}";
	done 
fi
exec {rows}>&-



