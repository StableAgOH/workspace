#include <bits/stdc++.h>
using namespace std;
template <typename T, typename O=plus<T>>
class prefix_sum
{
private:
    O op;
    vector<T> pre;
public:
    prefix_sum(const ranges::range auto& r)
    {
        pre.reserve(ranges::size(r));
        T sum = T();
        for(auto& i : r) pre.push_back(sum = op(sum, i));
    }
    T operator()(int p) { return p>=0?pre[p]:T(); }
    T operator()(int l,int r) { return operator()(r)-operator()(l-1); }
};
