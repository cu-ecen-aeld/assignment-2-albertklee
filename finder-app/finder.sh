#!/usr/bin/env bash

[ $# -ne 2 ] && { echo "Error: requires filesdir and searchstr arguments" ; exit 1 ; }

filesdir="$1"
searchstr="$2"

[ ! -d "$filesdir" ] && { echo "Error: $filesdir not a directory" ; exit 1 ; }

x=$( find "$filesdir" -type f | wc -l )
y=$( find "$filesdir" -type f -exec grep "$searchstr" {} + | wc -l )

echo The number of files are $x and the number of matching lines are $y
