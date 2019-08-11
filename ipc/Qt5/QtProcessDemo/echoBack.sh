#!/bin/bash

echo "script back: started"
while read var
do
	if [ "xbreak" = "x$var" ]
	then
		break
	fi
	echo "script back:" "$var"
done
echo "script back: finnished"
