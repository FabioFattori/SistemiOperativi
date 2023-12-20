#!/bin/bash

exec {fd}<cadutevicApici.txt

while read -r -u ${fd} row; do
	row=${row#${row%% *} };
	row=${row#${row%% \"*\"} };
	row=${row%% \"*\"}
	echo ${row}
done
