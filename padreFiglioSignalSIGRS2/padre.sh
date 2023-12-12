#!/bin/bash
trap "echo \"ho ricevo il segnale SIGUSR2 VADO A FARE IN CULO cit il padre $$\"; exit 0" SIGUSR2;

./figlio.sh