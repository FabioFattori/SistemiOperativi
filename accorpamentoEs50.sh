#!/bin/bash

(
 sed -n 3,5p /usr/include/stdio.h ;
 tail -n 4 /usr/include/stdio.h | cut -c 1	
 ) | (
  read Riga1 ; read Riga2 ; echo ${Riga2} ; echo ${Riga1};
  read input ; &> /dev/null;
  while read row; do
	echo "nCaratteri => ${#row}";		
  done
 )
