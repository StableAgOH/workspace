class bcc_v
{
    vector<vector<int>> g;
public:
    struct result
    {
        vector<int> cuts;
        vector<vector<int>> groups;
    };
    explicit bcc_v(int n) : g(n) {}
    void add_edge(int u, int v) { g[u].push_back(v), g[v].push_back(u); }
    auto operator()() const
    {
        result res;
        int timestamp = 0;
        vector<int> low(g.size()), dfn(g.size(), -1);
        stack<int> st;
        auto dfs = [&](auto&& dfs, int u, int root) -> void
        {
            low[u] = dfn[u] = timestamp++;
            st.push(u);
            if(u==root&&g[u].empty()) res.groups.emplace_back(1, u);
            int s = 0;
            for(auto v : g[u])
            {
                if(dfn[v]==-1)
                {
                    dfs(dfs, v, root);
                    low[u] = min(low[u], low[v]);
                    if(low[v]>=dfn[u])
                    {
                        if(++s+(u!=root)==2) res.cuts.push_back(u);
                        res.groups.emplace_back();
                        int w;
                        do
                        {
                            res.groups.back().push_back(w=st.top());
                            st.pop();
                        }
                        while(w!=v);
                        res.groups.back().push_back(u);
                    }
                }
                else low[u] = min(low[u], dfn[v]);
            }
        };
        for(size_t i=0;i<g.size();i++) if(dfn[i]==-1) dfs(dfs, i, i);
        return res;
    }
    auto get_bctree() const
    {
        auto res = (*this)();
        vector<vector<int>> h(g.size()+res.groups.size());
        for(int i=0,j=g.size();i<(int)res.groups.size();i++,j++)
            for(auto v : res.groups[i])
                h[j].push_back(v), h[v].push_back(j);
        return h;
    }
};
