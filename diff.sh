#!/bin/bash
set -e
clang++ temp.cpp -o temp -O2 -std=c++20
clang++ test.cpp -o test -O2 -std=c++20
for ((i = 1; ; i++)); do
    echo "No.$i"
    python3 data.py >in.in
    ./temp
    ./test <in.in >out2.out
    diff -w out.out out2.out
    sleep 0.5
done
