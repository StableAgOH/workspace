#!/bin/bash
set -e
g++ temp.cpp -o temp -DLOCAL -O2 -Wno-unused-result -std=c++20
g++ test.cpp -o test -Wno-unused-result
for ((i = 1; ; i++)); do
    echo "No.$i"
    python3 data.py >testcases/233.in
    ./temp 233
    ./test <testcases/233.in >testcases/233.ans
    diff testcases/233.out testcases/233.ans
    sleep 0.5
done
