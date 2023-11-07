#!/bin/bash

if [ $# != 2 ]; then echo "ho bisogno di due parametri per funzionare ;("; exit 2 ;fi
if [ ! -d $1  ]; then echo "il path non esiste"; exit 3 ; fi

find "$1" -name "$2" -print; 
