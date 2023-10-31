#!/bin/bash
exec {Verdetti}<verdetti.txt
exec {Processi}<processi.txt
exec {Denunce}<denunce.txt

while read -r -u ${Verdetti} ProcessCode Desc \
   && read -r -u ${Processi} idDenuncia processCodeInFile \
   && read -r -u ${Denunce} nome cognome idDenunciaInFile descDenuncia; 
   do
  	: do 
  	if [[ ${ProcessCode} == ${processCodeInFile} ]] ; then
  	
  		if [[ ${idDenuncia} == ${idDenunciaInFile} ]] ; then
  			echo "${nome} ${cognome} => verdetto: ${Desc} </> descrizione Denuncia: ${descDenuncia}"	
  		fi
  	fi
done


