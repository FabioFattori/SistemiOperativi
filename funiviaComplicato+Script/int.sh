#!/bin/bash


for file in `find /usr/include/linux/ -name "*.h" -print`;do
	grep int ${file} | cut -b -3
done
