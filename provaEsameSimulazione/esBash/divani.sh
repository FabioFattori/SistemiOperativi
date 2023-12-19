#!/bin/bash

if (( $# != 2 )) ; then 
	echo "errore: servono 2 argomenti: larghezza_minima  altezza_massima"
	exit 1
fi

LARGMIN=$1
ALTMAX=$2

# ORA nelle due variabili ci sono i parametri
# passati a riga di comando.
# Da qui in poi aggiungete quello che serve.
# Leggete il contenuto del file ./divani.txt
# ed usatelo opportunamente.

exec {FD}<"divani.txt";

while read -r -u ${FD} nome larghezza altezza profondita; do
	if [[ ${larghezza} -ge ${LARGMIN} && ${altezza} -le ${ALTMAX} ]]; then
		echo "${nome} ${larghezza} ${altezza} ${profondita}";
	fi
done


