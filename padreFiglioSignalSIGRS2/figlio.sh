#!/bin/bash

echo "sono il figlio di ${PPID} e aspetto!"
sleep 5

kill -s SIGUSR2 ${PPID}
