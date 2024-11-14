#include <bits/stdc++.h>
using namespace std;
template <typename T, typename O=plus<T>>
class fenwick
{
    static constexpr auto lowbit(auto x) { return x&-x; }
    int n;
    vector<T> c;
public:
    fenwick(int n) : n(n), c(n+1) {}
    fenwick(const ranges::range auto& r) : fenwick(a.size())
    {
        vector<T> p(n+1);
        partial_sum(r.begin(), r.end(), p.begin()+1);
        for(int i=1;i<=n;i++) c[i] = p[i]-p[i-lowbit(i)];
    }
    fenwick(int n, const T& x) : fenwick(vector(n,x)) {}
    void clear() { ranges::fill(c, T()); }
    int size() { return n; }
    void add(int p, const T& x)
    {
        for(int i=p+1;i<=n;i+=lowbit(i))
            c[i] = O()(c[i], x);
    }
    auto prefix_sum(int p) const
    {
        T sum{};
        for(int i=p+1;i;i-=lowbit(i))
            sum = O()(sum, c[i]);
        return sum;
    }
    auto operator()(int l) const { return operator()(l,l); }
    auto operator()(int l, int r) const { return prefix_sum(r)-prefix_sum(l-1); }
};
