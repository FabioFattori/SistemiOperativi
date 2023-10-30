#!/bin/bash
toStamp="";
i=0;
for ((i=2;${i}<=$#;i=${i}+2)); do
	toStamp="${toStamp}${!i}";
done
echo ${toStamp};

toStamp="";

for ((i=1;${i}<=$#;i=${i}+2)); do
	toStamp="${toStamp}${!i}";
done
echo ${toStamp};
