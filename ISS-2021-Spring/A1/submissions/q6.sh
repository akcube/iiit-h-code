usage() { echo "Usage: $0 -C [insert|search|delete|edit|display] followed by input flags" 1>&2;}

FILE=./contacts.csv
if !(test -f "$FILE"); then
    touch contacts.csv
    echo "fname,lname,mobile,office" > contacts.csv
fi

MODE=""
FNAME=""
LNAME=""
MOBILE=""
OFFICE=""
SEARCHKEY=""
COL=""

ASC="1"

while getopts ":C:f:l:n:o:k:c:v:ad" opt; do
    case $opt in
        C) MODE=$OPTARG;;
        f) FNAME=$OPTARG;;
        l) LNAME=$OPTARG;;
        n) MOBILE=$OPTARG;;
        o) OFFICE=$OPTARG;;
		k) SEARCHKEY=$OPTARG;;
		c) COL=$OPTARG;;
		v) SEARCHKEY=$OPTARG;;
		d) ASC="0";;
        \?) usage;;
		:) usage;;
    esac
done
shift $((OPTIND -1))

if [[ $MODE == "insert" ]]; then
	echo "$FNAME,$LNAME,$MOBILE,$OFFICE" >> contacts.csv

elif [[ $MODE == "edit" ]]; then
	sed -i "s/^$SEARCHKEY,.*$/$FNAME,$LNAME,$MOBILE,$OFFICE/" $FILE;

elif [[ $MODE == "display" ]]; then
	if [[ $ASC == "1" ]]; then
		tail -n +2 $FILE | sort
	elif [[ $ASC == "0" ]]; then
		tail -n +2 $FILE | sort -r
	fi

elif [[ $MODE == "search" ]]; then
	if [[ $COL == "fname" ]]; then
		grep -P "^$SEARCHKEY,.*$" $FILE
	elif [[ $COL == "lname" ]]; then
		grep -P "^.*,$SEARCHKEY,.*$" $FILE
	elif [[ $COL == "mobile" ]]; then
		grep -P "^.*,.*,$SEARCHKEY,.*$" $FILE
	elif [[ $COL == "office" ]]; then
		grep -P "^.*,.*,.*,$SEARCHKEY$" $FILE
	fi

elif [[ $MODE == "delete" ]]; then
	if [[ $COL == "fname" ]]; then
		sed -i "/^$SEARCHKEY,.*$/d" $FILE
	elif [[ $COL == "lname" ]]; then
		sed -i "/^.*,$SEARCHKEY,.*$/d" $FILE
	elif [[ $COL == "mobile" ]]; then
		sed -i "/^.*,.*,$SEARCHKEY,.*$/d" $FILE
	elif [[ $COL == "office" ]]; then
		sed -i "/^.*,.*,.*,$SEARCHKEY$/d" $FILE
	fi
fi
