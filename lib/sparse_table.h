#include <bits/stdc++.h>
using namespace std;
template <typename T, auto O, size_t L=(size_t)ceil(log2(1e7))>
class sparse_table
{
private:
    array<vector<T>, L> f;
public:
    sparse_table(const ranges::range auto& r)
    {
        for(auto i : r) f[0].emplace_back(i);
        int n = f[0].size();
        for(int i=1;(1<<i)<=n;i++)
            for(int j=0;j+(1<<i)-1<n;j++)
                f[i].emplace_back(O(f[i-1][j], f[i-1][j+(1<<(i-1))]));
    }
    T operator()(int l,int r)
    {
        int k = log2(r-l+1);
        return O(f[k][l], f[k][r-(1<<k)+1]);
    }
};
#define functor(name, op) auto name = [](const auto& x, const auto& y) { return op(x,y); };
