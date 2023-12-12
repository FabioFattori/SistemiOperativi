#!/bin/bash

if [ $# != 1 ] ; then echo "name for the script required"; exit 1; fi
if [ -f $1 ] ; then echo "script already exits" ; exit 2 ;fi

touch $1 && chmod 770 $1 && echo "#!/bin/bash" >> $1 && echo "file created";