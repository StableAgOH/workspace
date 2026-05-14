// https://judge.yosupo.jp/submission/360243
vector<int> dep(n+1), in(n+1), asc(n+1), top(n+1);
vector<pair<int, int>> ord;
auto lowbit = [](auto x) { return x&-x; };
auto dfs = [&](auto&& self, int u, int p) -> void
{
    ord.emplace_back(u, p);
    in[u] = ord.size();
    for(auto v : g[u])
    {
        if(v==p) continue;
        dep[v] = dep[u]+1;
        self(self, v, u);
        top[in[v]] = u;
        if(lowbit(in[u])<lowbit(in[v])) in[u] = in[v];
    }
};
dfs(dfs, s, 0);
for(auto [u, p] : ord) asc[u] = asc[p]|lowbit(in[u]);
auto lca = [&](int u, int v)
{
    if(unsigned j = in[u]^in[v])
    {
        j = asc[u]&asc[v]&-bit_floor(j);
        if(auto k=bit_floor(asc[u]^j)) u = top[(in[u]&-k)|k];
        if(auto k=bit_floor(asc[v]^j)) v = top[(in[v]&-k)|k];
    }
    return dep[u]<dep[v]?u:v;
};
