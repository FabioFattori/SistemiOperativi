#!/bin/bash
for name in /usr/include/* ; do
	if [[ -d ${name} && -r ${name} && ${name} -nt /usr/include/stdio.h ]] ; then
		echo /usr/include/${name}
	fi
done

echo "<--->";
echo "now with the [ operator";
echo "<--->";

for name in /usr/include/* ; do
	if [ -d ${name} ] ;then
	   	if [ -r ${name} ]; then 
	   		if [ ${name} -nt /usr/include/stdio.h ]; then
	   			echo /usr/include/${name};
	   		fi
		fi
	fi
done

echo "<--->";
echo "now with the test operator";
echo "<--->";

for name in /usr/include/* ; do
	if test -d ${name}; then
	   	if test -r ${name}; then 
	   		if test ${name} -nt /usr/include/stdio.h; then
	   			echo /usr/include/${name};
	   		fi
		fi
	fi
done
