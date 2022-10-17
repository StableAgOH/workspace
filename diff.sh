set -e
g++ temp.cpp -o temp -DLOCAL -O2 -Wno-unused-result -std=c++20
g++ test.cpp -o test -Wno-unused-result
for ((i = 1; ; i++)); do
    echo "No.$i"
    python3 data.py >in.in
    ./temp
    ./test <in.in >out2.out
    diff out.out out2.out
    sleep 0.5
done
