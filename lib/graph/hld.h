class hld
{
    vector<vector<int>> g;
public:
    struct result
    {
        vector<int> dep, par, siz, son, top, dfn;
        explicit result(int n) : dep(n), par(n), siz(n, 1), son(n, -1), top(n), dfn(n) {}
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
        void path(int u, int v, invocable<int, int> auto&& cb)
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
        template <bool ExcludeLCA=false>
        void dfn_path(int u, int v, invocable<int, int> auto&& cb)
        {
            while(top[u]!=top[v])
            {
                if(dep[top[u]]<dep[top[v]]) swap(u, v);
                cb(dfn[top[u]], dfn[u]);
                u = par[top[u]];
            }
            if(dep[u]>dep[v]) swap(u, v);
            cb(dfn[u]+ExcludeLCA, dfn[v]);
        }
    };
    explicit hld(int n) : g(n) {}
    void add_edge(int u, int v) { g[u].push_back(v), g[v].push_back(u); }
    auto operator[](size_t p) const { return g[p]; }
    auto operator()(int rt=0) const
    {
        result res(g.size());
        auto dfs1 = [&](auto&& self, int u, int p) -> void
        {
            res.dep[u] = p==-1?0:res.dep[p]+1;
            res.par[u] = p;
            for(auto v : g[u])
            {
                if(v==p) continue;
                self(self, v, u);
                res.siz[u] += res.siz[v];
                if(res.son[u]==-1||res.siz[v]>res.siz[res.son[u]]) res.son[u] = v;
            }
        };
        dfs1(dfs1, rt, -1);
        int ts = 0;
        auto dfs2 = [&](auto&& self, int u, int t) -> void
        {
            res.top[u] = t;
            res.dfn[u] = ts++;
            if(res.son[u]!=-1) self(self, res.son[u], t);
            for(auto v : g[u])
                if(v!=res.par[u]&&v!=res.son[u])
                    self(self, v, v);
        };
        dfs2(dfs2, rt, rt);
        return res;
    }
};
