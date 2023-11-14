#!/bin/bash

Files=`find  /Users/fabiofattori/Desktop -name "*.h" -mindepth 2 -print`

if [[ -z ${Files} ]]; then echo "no .h files found"; exit 1; fi

for file in ${Files}; do mostRecentFile=${file}; done

for file in ${Files}; do
    # check if file is the most recent between the two
    if [[ ${mostRecentFile} -ot ${file} ]]; then 
        mostRecentFile=${file};
    fi
done

echo "the most recent file is => ${mostRecentFile}";