#!/bin/bash

echo "press Ctrl + C to stop";
echo "reading from input ... "

while read row; do
	echo "nCaratteri => ${#row}";		
done
