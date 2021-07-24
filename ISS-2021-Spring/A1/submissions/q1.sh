#!/bin/bash

FILE=$1
OUTPUTFILE="q1_output.txt"

touch $OUTPUTFILE
> $OUTPUTFILE

while read -r line || [ -n "$line" ]; 
do
	for word in $line;
	do
		if [ ${#word} -le 4 ]
		then
			echo $word >> $OUTPUTFILE;
		else
			echo -n ${word:0:4} >> $OUTPUTFILE;
			for i in $(seq 6 ${#word});
			do
				echo -n "#" >> $OUTPUTFILE;
			done;
			echo "#" >> $OUTPUTFILE;
		fi
	done;
done < $FILE 