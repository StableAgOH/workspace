struct hld
{
    vector<int> dep, par, siz, son, top, bot, dfn;
    explicit hld(int n) : dep(n), par(n), siz(n, 1), son(n, -1), top(n), bot(n), dfn(n) {}
    auto is_ancestor(int u, int v) { return dfn[u]<=dfn[v]&&dfn[v]<dfn[u]+siz[u]; }
    auto lca(int u, int v)
    {
        while(top[u]!=top[v])
        {
            if(dep[top[u]]<dep[top[v]]) swap(u, v);
            u = par[top[u]];
        }
        return (dep[u]<dep[v])?u:v;
    }
    auto dis(int u, int v) { return dep[u]+dep[v]-2*dep[lca(u, v)]; }
    template <typename F>
    void path(int u, int v, F cb)
    {
        while(top[u]!=top[v])
        {
            if(dep[top[u]]<dep[top[v]]) swap(u, v);
            cb(top[u], u);
            u = par[top[u]];
        }
        if(dep[u]>dep[v]) swap(u, v);
        cb(u, v);
    }
};
class hld_builder
{
    vector<vector<int>> g;
public:
    explicit hld_builder(int n) : g(n) {}
    auto& add_edge(int u, int v)
    {
        g[u].push_back(v);
        g[v].push_back(u);
        return *this;
    }
    auto build(int rt=0)
    {
        hld h(g.size());
        auto dfs1 = [&](auto&& dfs1, int u, int p) -> void
        {
            h.dep[u] = (p==-1)?0:h.dep[p]+1;
            h.par[u] = p;
            for(auto v : g[u])
            {
                if(v==p) continue;
                dfs1(dfs1, v, u);
                h.siz[u] += h.siz[v];
                if(h.son[u]==-1||h.siz[v]>h.siz[h.son[u]]) h.son[u] = v;
            }
        };
        dfs1(dfs1, rt, -1);
        int timestamp = 0;
        auto dfs2 = [&](auto&& dfs2, int u, int t) -> void
        {
            h.top[u] = t;
            h.dfn[u] = timestamp++;
            if(h.son[u]!=-1)
            {
                dfs2(dfs2, h.son[u], t);
                h.bot[u] = h.bot[h.son[u]];
            }
            else h.bot[u] = u;
            for(auto v : g[u])
            {
                if(v==h.par[u]||v==h.son[u]) continue;
                dfs2(dfs2, v, v);
            }
        };
        dfs2(dfs2, rt, rt);
        return h;
    }
};
