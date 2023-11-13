#!/bin/bash


for path in `./separa.sh` ; do
    echo ${path}
    path=${path#"/"}
    while [[ ${path} != "" ]] ; do
        printed=${path%%/*};
        if [[ ${printed} == ${path} ]]; then
            # sono arrivato alla fine del path
            echo ${path}
            path="";
        else 
            # non sono alla fine 
            echo ${printed}
            path=${path#"${printed}/"}
        fi
    done
done