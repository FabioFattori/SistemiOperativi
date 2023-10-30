#!/bin/bash

somma=0;

for((i=1;${i}<=$#;i=${i}+1)); do
	((somma=${somma}+${!i}*${!i}-${!i}));
done 
echo ${somma}
