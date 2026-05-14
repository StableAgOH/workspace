vector<int> dep(n+1);
vector<array<int, 20>> f(n+1);
auto dfs = [&](auto&& self, int u, int p) -> void
{
    dep[u] = dep[p]+1;
    f[u][0] = p;
    for(int i=1;i<20;i++) f[u][i] = f[f[u][i-1]][i-1];
    for(auto v : g[u])
        if(v!=p) self(self, v, u);
};
dfs(dfs, 1, 0);
auto lca = [&](int u, int v)
{
    if(dep[u]<dep[v]) swap(u, v);
    for(int i=19;i>=0;i--)
        if(dep[f[u][i]]>=dep[v])
            u = f[u][i];
    if(u==v) return u;
    for(int i=19;i>=0;i--)
    {
        if(f[u][i]==f[v][i]) continue;
        u=f[u][i], v=f[v][i];
    }
    return f[u][0];
};
