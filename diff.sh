#!/bin/bash

exit_if_not_zero() {
    if [ $? ]; then
        echo $1 >&2
        exit $?
    fi
}

program1=${1:-"temp.cpp"}
program2=${2:-"test.cpp"}

echo "[INFO] Compiling $program1"
g++ $program1 -o temp -O2 -std=c++20
exit_if_not_zero "[CE] $program1"

echo "[INFO] Compiling $program2"
g++ $program2 -o test -O2 -std=c++20
exit_if_not_zero "[CE] $program2"

for ((i = 1; ; i++)); do
    echo "[INFO] Testcase No.$i"

    python3 data.py >in.txt
    exit_if_not_zero "[RE] data.py"

    ./temp <in.txt >out.txt
    exit_if_not_zero "[RE] $program1"

    ./test <in.txt >out2.txt
    exit_if_not_zero "[RE] $program2"

    diff -w out.txt out2.txt
    exit_if_not_zero "[ERROR] Two results do not match"

    sleep 0.5
done
