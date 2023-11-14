#!/bin/bash


hasDoneFirstProva=0;

while read -r nome2 cognome2 code2 vote2; do
	
	if [[ ${vote2} < 18 ]]; then 
		
		
		while read -r nome1 cognome1 code1 vote1 ; do
			if [[ ${code2} == ${code1} ]]; then
				echo "entro per ${nome1}"
				hasDoneFirstProva=1;
			fi
			
		done < risProvaPratica1.txt
		
		
		if [[ ${hasDoneFirstProva} == 0 ]]; then 
			echo "${code2} ${nome2} ${cognome2} ${vote2}";
		fi
		
	fi
	
	hasDoneFirstProva=0;
done < risProvaPratica2.txt

exit 0;
