DIR=${PWD}
OLDPWD=${PWD}

if [[ "$#" -ge 1 ]]; then
	DIR=$1;
fi

cd $DIR
echo "Directories:"
find . -not -path '*/\.*' -type d -exec sh -c "ct=\$(find '{}' -not -path '*/\.*' -type f | wc -l); echo \"\$ct {}, \$ct file(s)\"" \; | sort -nr -k 1 | sed -e 's/^[0-9]*\s*//' | sed -e 's/.*\///' | grep -v "^\."

echo ""
echo "Files:"
find . -not -path '*/\.*' -type d -exec ls -l {} \; | grep "^-.*" | grep -vP "^total \d*$" | sort -rg -k 5 | awk '{print $9}'

cd $OLDPWD