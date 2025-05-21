class hld
{
    vector<vector<int>> g;
public:
    struct result
    {
        vector<int> dep, par, siz, son, top, bot, dfn;
        explicit result(int n) : dep(n), par(n), siz(n, 1), son(n, -1), top(n), bot(n), dfn(n) {}
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
    explicit hld(int n) : g(n) {}
    void add_edge(int u, int v) { g[u].push_back(v), g[v].push_back(u); }
    auto operator()(int rt=0) const
    {
        result res(g.size());
        auto dfs1 = [&](auto&& dfs1, int u, int p) -> void
        {
            res.dep[u] = p==-1?0:res.dep[p]+1;
            res.par[u] = p;
            for(auto v : g[u])
            {
                if(v==p) continue;
                dfs1(dfs1, v, u);
                res.siz[u] += res.siz[v];
                if(res.son[u]==-1||res.siz[v]>res.siz[res.son[u]]) res.son[u] = v;
            }
        };
        dfs1(dfs1, rt, -1);
        int timestamp = 0;
        auto dfs2 = [&](auto&& dfs2, int u, int t) -> void
        {
            res.top[u] = t;
            res.dfn[u] = timestamp++;
            if(res.son[u]!=-1)
            {
                dfs2(dfs2, res.son[u], t);
                res.bot[u] = res.bot[res.son[u]];
            }
            else res.bot[u] = u;
            for(auto v : g[u])
            {
                if(v==res.par[u]||v==res.son[u]) continue;
                dfs2(dfs2, v, v);
            }
        };
        dfs2(dfs2, rt, rt);
        return res;
    }
};
