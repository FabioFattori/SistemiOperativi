#!/bin/bash

pathCopy=${PATH}
endOfCicle="";

while (( ${#endOfCicle} != ${#pathCopy} )) ; do 
    toPrint=${pathCopy%%:*};
    echo ${toPrint};
    if [[ "${pathCopy}" ==  "${pathCopy#"${toPrint}:"}" ]]; then
        # sono arrivato alla fine di PATH
        pathCopy=${pathCopy#"${toPrint}"};
    else 
        # non sono arrivato alla fine 
        pathCopy=${pathCopy#"${toPrint}:"};
    fi
done