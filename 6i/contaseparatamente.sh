#!/bin/bash

TOTPARI=0;
TOTDISPARI=0;

i=1;

for file in $@; do
	resto=$((${i} % 2));
	lines=`wc ${file} --lines`;
	lines=${lines%% *}
	if [[ ${resto} == 0 ]];then
		TOTPARI=$((${lines}+${TOTPARI}));
	else
		TOTDISPARI=$((${lines}+${TOTDISPARI}));
	fi
	i=$((${i} +1));
done

echo "pari => ${TOTPARI};";
echo "dispari => ${TOTDISPARI}" 1>&2;
