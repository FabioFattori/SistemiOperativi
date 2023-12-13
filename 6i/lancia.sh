#!/bin/bash
i=1;

for file in `ls -S1 /usr/include/*.h`;do
if [[ ${i} == 1 ]]; then
	f1=${file};
	elif [[ ${i} == 2 ]];then
	f2=${file};
	elif [[ ${i} == 3 ]];then
	f3=${file};
	elif [[ ${i} == 4 ]];then
	f4=${file};
	elif [[ ${i} == 5 ]];then
	f5=${file};
	elif [[ ${i} == 6 ]];then
	f6=${file};
	elif [[ ${i} == 7 ]];then
	f7=${file};
	fi
	i=$((${i}+1));
	if [[ ${i} == 8 ]]; then 
	
	./contaseparatamente.sh ${f1} ${f2} ${f3} ${f4} ${f5} ${f6} ${f7} 1>&2;
	exit 0;
	fi
done

 
