#!/bin/bash

newestFile="";

for file in `find /usr/include/linux/ -mindepth 2 -name "*.h"`;do
	if [[ ${newestFile} == "" ]]; then
		newestFile=${file}
	elif [[ ${newestFile} -ot ${file} ]]; then
		newestFile=${file}
	fi
done

echo ${newestFile};
