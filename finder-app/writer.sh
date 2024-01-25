#!/usr/bin/env bash

[ $# -ne 2 ] && { echo "Error: need writefile and writestr arguments" ; exit 1 ; }

writefile="$1"
writestr="$2"

mkdir -p $( dirname "$writefile" )
echo "$writestr" > "$writefile"
