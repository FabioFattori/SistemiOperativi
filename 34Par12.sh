#!/bin/bash

for fileName in `find /usr/include/ -type f` ; do
    head -n 3 ${fileName} | cut -b -3;
done