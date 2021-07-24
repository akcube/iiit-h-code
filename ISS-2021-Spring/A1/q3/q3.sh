#!/bin/bash

# echo "1. Words - start with ‘s’ and is not follow by ‘a’"
cat $1 | grep -ohP "\bs(?!a)\w*\b" | cat | tr '\n' ',' | rev | cut -c 2- | rev
# echo "2. Word starts with ‘w’ and is followed by ‘h’"
cat $1 | grep -oh "\bwh\w*\b" | cat | tr '\n' ',' | rev | cut -c 2- | rev
# echo "3. Word starts with ‘t’ and is followed by ‘h’"
cat $1 | grep -oh "\bth\w*\b" | cat | tr '\n' ',' | rev | cut -c 2- | rev
# echo "4. Word starts with ‘a’ and is not followed by ‘n’"
cat $1 | grep -ohP "\ba(?!n)\w*\b" | cat | tr '\n' ',' | rev | cut -c 2- | rev