#!/bin/bash

DATE=$(awk 'NF>1{print $NF}' $1)
NAME=$(sed -e 's/[0-9]*\/[0-9]*\/[0-9]*$//' $1)
FILE="q2_output.txt"

BD=${DATE:0:2}
BM=${DATE:3:2}
BY=${DATE:6:4}

CD=$(date '+%d')
CM=$(date '+%m')
CY=$(date '+%Y')

if [[ BD -gt CD ]] 
then
	CM="$(($CM-1))";
fi

if [[ BM -gt CM ]]
then
	CY="$(($CY-1))"
fi

AGE="$(($CY-$BY))"

echo -n $NAME "" > $FILE
echo $AGE >> $FILE