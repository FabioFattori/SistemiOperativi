#!/bin/bash

while read row ; do
    toPrint=${row//"*"/"\*"};
    toPrint=${toPrint//"?"/"\?"};
    toPrint=${toPrint//"["/"\["};
    toPrint=${toPrint//"]"/"\]"};
    echo ${toPrint}

done