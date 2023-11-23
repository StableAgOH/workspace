#include <bits/stdc++.h>
using namespace std;
template <typename T, typename O=plus<T>>
class fenwick
{
private:
    O op;
    int n;
    vector<T> pre;
    int lowbit(int x) const { return x&-x; }
public:
    fenwick(int n) : n(n) { pre.resize(n+1); }
    fenwick(const ranges::range auto& r)
    {
        n = ranges::size(r);
        pre.resize(n+1);
        int p = 0;
        for(auto i : r) add(p++, i);
    }
    void add(int p, const T& x)
    {
        for(int i=p+1;i<=n;i+=lowbit(i)) pre[i] = op(pre[i], x);
    }
    auto operator()(int p) const
    {
        T sum = T();
        for(int i=p+1;i;i-=lowbit(i)) sum += pre[i];
        return sum;
    }
    auto operator()(int l, int r) const
    {
        return operator()(r)-operator()(l-1);
    }
};
