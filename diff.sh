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
clang++ $program1 -o temp -O2 -std=c++20
exit_if_not_zero "[CE] $program1"

echo "[INFO] Compiling $program2"
clang++ $program2 -o test -O2 -std=c++20
exit_if_not_zero "[CE] $program2"

for ((i = 1; ; i++)); do
    echo "[INFO] Testcase No.$i"

    python3 data.py >in.in
    exit_if_not_zero "[RE] data.py"

    ./temp <in.in >out.out
    exit_if_not_zero "[RE] $program1"

    ./test <in.in >out2.out
    exit_if_not_zero "[RE] $program2"

    diff -w out.out out2.out
    exit_if_not_zero "[ERROR] Two results do not match"

    sleep 0.5
done
