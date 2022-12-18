#!/bin/bash

exit_if_not_zero() {
    if [ $? ]; then
        echo $1 >&2
        exit $?
    fi
}

echo "[INFO] Compiling temp.cpp"
clang++ temp.cpp -o temp -O2 -std=c++20
exit_if_not_zero "[CE] temp.cpp"

echo "[INFO] Compiling test.cpp"
clang++ test.cpp -o test -O2 -std=c++20
exit_if_not_zero "[CE] test.cpp"

for ((i = 1; ; i++)); do
    echo "[INFO] Testcase No.$i"

    python3 data.py >in.in
    exit_if_not_zero "[RE] data.py"

    ./temp
    exit_if_not_zero "[RE] temp.cpp"

    ./test <in.in >out2.out
    exit_if_not_zero "[RE] test.cpp"

    diff -w out.out out2.out
    exit_if_not_zero "[ERROR] Two results do not match"

    sleep 0.5
done
