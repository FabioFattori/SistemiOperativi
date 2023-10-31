#!/bin/bash

File=$1;
cut -b 3-5,10-15 ${File} | sed 's/ //g' | sed 's/*//g' | sed 's/\t//g' | wc -c;
