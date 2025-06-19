class bcc_e
{
    int idx = 0;
    vector<vector<pair<int, int>>> g;
public:
    struct result
    {
        int cnt = 0;
        vector<int> id;
        vector<pair<int, int>> cuts;
        explicit result(int n) : id(n) {}
        auto groups() const
        {
            vector<vector<int>> groups(cnt);
            for(size_t i=0; i<id.size(); i++) groups[id[i]].push_back(i);
            return groups;
        }
    };
    explicit bcc_e(int n) : g(n) {}
    void add_edge(int u, int v) { g[u].emplace_back(v, idx++); g[v].emplace_back(u, idx++); }
    auto operator()() const
    {
        result res(g.size());
        int timestamp = 0;
        vector<int> low(g.size()), dfn(g.size(), -1);
        stack<int> st;
        auto dfs = [&](auto&& dfs, int u, int i) -> void
        {
            low[u] = dfn[u] = timestamp++;
            st.push(u);
            for(auto [v, idx] : g[u])
            {
                if(idx==(i^1)) continue;
                if(dfn[v]==-1)
                {
                    dfs(dfs, v, idx);
                    low[u] = min(low[u], low[v]);
                    if(low[v]>dfn[u]) res.cuts.push_back(minmax(idx, idx^1));
                }
                else low[u] = min(low[u], dfn[v]);
            }
            if(low[u]==dfn[u])
            {
                while(true)
                {
                    int v = st.top();
                    st.pop();
                    dfn[v] = g.size();
                    res.id[v] = res.cnt;
                    if(v==u) break;
                }
                res.cnt++;
            }
        };
        for(size_t i=0; i<g.size(); i++) if(dfn[i]==-1) dfs(dfs, i, -1);
        for(auto& x : res.id) x = res.cnt-1-x;
        return res;
    }
};
