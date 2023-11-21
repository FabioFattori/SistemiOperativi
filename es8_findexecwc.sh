#!/bin/bash

for name in `./es7_find2livelli.sh `; do
	wc ${name} --lines
done
