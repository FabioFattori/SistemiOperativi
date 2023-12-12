#!/bin/bash
### Nei commenti che seguono vedete dei suggerimenti sull'algoritmo da
### seguire per produrre l'output corretto.
###

# I voti della seconda prova li devo mettere tutti nello standard output


# Poi devo mettere nello standard output i voti della prima prova
# ottenuti dagli studenti che non hanno un voto nella seconda prova
exec {FD}<esame1.txt;

cat esame2.txt;


while read -r -u ${FD} cod voto ; do
	output=`grep "${cod}" esame2.txt`;
	if [[ $output == "" ]]; then
		echo "voto di ${cod} => ${voto}";
	fi
done


