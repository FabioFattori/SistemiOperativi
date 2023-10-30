#!/bin/bash
NOMIFILES=`ls`
for x in ${NOMIFILES}; do
	for y in ${NOMIFILES}; do
		for z in ${NOMIFILES}; do
			echo "(${x};${y};${z})";
		done 
	done 
done
