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
    auto begin() { return pre.begin(); }
    auto end() { return pre.end(); }
};
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
    class iterator
    {
    private:
        const fenwick<T,O>& fen;
        int p;
    public:
        iterator(const fenwick<T,O>& fen, int p) : fen(fen), p(p) {}
        auto operator*() { return fen(p); }
        auto& operator++() { p++; return *this; }
        auto operator++(int) { return iterator(fen, p++); }
        auto operator!=(const iterator& rhs)
        {
            return !(addressof(fen)==addressof(rhs.fen)&&p==rhs.p);
        }
    };
    auto begin() { return iterator(*this, 0); }
    auto end() { return iterator(*this, n); }
};
