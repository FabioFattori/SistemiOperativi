#!/bin/bash

for file in `find  /usr/include/linux/ -maxdepth 1 -name "*f*.h" -print`; do
	nRows=`wc --lines ${file}`;
	nRows=${nRows%% *};
	if [[ ${nRows} -ge 10 && ${nRows} -le 100 ]]; then
		tail -n 1 ${file} | wc -c 
	fi
done
