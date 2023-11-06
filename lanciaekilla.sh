#!/bin/bash

PIDs=`./lanciaeprendipid.sh`

for Pid in ${PIDS} ; do 
	kill -9 ${Pid}
done	
