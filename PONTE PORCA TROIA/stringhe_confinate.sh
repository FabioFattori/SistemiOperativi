#!/bin/bash

exec {FD}<cadutevic2.txt;

while read -r -u ${FD} row; do
	row=${row#${row%% *} }
	row=${row#${row%% \"*\"} }
	row=${row%% \"*\"}
	echo ${row}
done
