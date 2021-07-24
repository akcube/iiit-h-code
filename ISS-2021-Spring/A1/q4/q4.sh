#!/bin/bash

STOPWORDS=$2
FILE="temp_$1"
OUTPUTFILE="Output.txt"

cat $1 > $FILE

touch $OUTPUTFILE
> $OUTPUTFILE

calc(){ 
	VAL=$(awk "BEGIN { print $* }"); 
	printf "%.2f\n" "$VAL" >> $OUTPUTFILE
}

while read -r line || [ -n "$line" ]; 
do
	for word in $line;
	do
		sed -i  "s/\<$word\>[,.?!;\s]*//g" $FILE;
	done;
done < $STOPWORDS

while read -r line || [ -n "$line" ];
do
	echo -n $line >> $OUTPUTFILE
	echo -n ", " >> $OUTPUTFILE
	FREQ=$(echo $line | grep -oh "\b$3\b" | cat | wc -l);
	WORDS=$(echo $line | wc -w);
	calc "$FREQ / $WORDS";
done < $FILE
rm -f $FILE