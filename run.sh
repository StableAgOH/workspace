#!/bin/bash
cases=${1:-1}
echo "$cases cases"
for ((i = 1; i <= $cases; i++)); do
    echo "Testing case $i..."
    ./temp $i
    diff --ignore-all-space testcases/$i.out testcases/$i.ans
done
