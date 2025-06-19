class scc
{
    vector<vector<int>> g;
public:
    struct result
    {
        int cnt = 0;
        vector<int> id;
        explicit result(int n) : id(n) {}
        auto groups() const
        {
            vector<vector<int>> groups(cnt);
            for(size_t i=0; i<id.size(); i++) groups[id[i]].push_back(i);
            return groups;
        }
    };
    explicit scc(int n) : g(n) {}
    void add_arc(int u, int v) { g[u].push_back(v); }
    auto operator()() const
    {
        result res(g.size());
        int timestamp = 0;
        vector<int> low(g.size()), dfn(g.size(), -1);
        stack<int> st;
        auto dfs = [&](auto&& dfs, int u) -> void
        {
            low[u] = dfn[u] = timestamp++;
            st.push(u);
            for(auto v : g[u])
            {
                if(dfn[v]==-1)
                {
                    dfs(dfs, v);
                    low[u] = min(low[u], low[v]);
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
        for(size_t i=0; i<g.size(); i++) if(dfn[i]==-1) dfs(dfs, i);
        for(auto& x : res.id) x = res.cnt-1-x;
        return res;
    }
};
