#!/bin/bash

if [ $1 -gt 0 ]; then
	./lanciaricorsivo.sh $(( $1 - 1 )) &
	echo "new progress PID => "$!
	wait $!
fi
