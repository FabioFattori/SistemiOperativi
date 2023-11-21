#!/bin/bash

RIGA='1 * 2';

while [[ -n ${RIGA} ]]; do
	toSub="${RIGA%% *}"
	echo "${toSub}";
	
	if [[ "${RIGA}" == "${toSub}" ]]; then
	 	RIGA=
	else 
		RIGA="${RIGA#* }";
	fi
done
