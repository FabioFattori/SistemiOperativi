#!/bin/bash
if (( $# != 1 )) ; then echo "serve nomefile" ; exit 1 ; fi
if [[ ! -r $1 ]] ; then echo "il file $1 non esiste"; exit 2; fi

OUT="";

exec {FD}< $1;

if [ $? == 0 ]; then
	
	while read -u ${FD} parola1 parola2 parola3 parola4 ; do
		OUT="${OUT} ${parola2}";
	done
	
fi
	
echo ${OUT};
