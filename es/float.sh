#!/bin/bash

listFloats=0.0
for i in $(seq 0 100)
do
    aux=$[($RANDOM % 15555)]
	printf -v aux "%.1f" ${aux}
	#In the first iteration it just set the variable, in the others it append
	if [ ${i} -eq 0 ]
	then
		listFloats=${aux}
##		printf ${aux} > randomFloats.txt
##		printf ' ' >> randomFloats.txt
	else
		listFloats="${listFloats} ${aux}"
##		printf ${aux} >> randomFloats.txt
##		printf ' ' >> randomFloats.txt

	fi
done

printf "%s\n" ${listFloats}
