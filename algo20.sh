#!/bin/bash

if test -e /usr/include/stdio.h; then
	grep '*' /usr/include/stdio.h;
else 
	echo "il file non esiste";
fi

