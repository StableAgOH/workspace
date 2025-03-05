class bcc_v
{
public:
    template <typename T>
    bcc_v(const graph<T>& g) : n(g.size())
    {
        int timestamp = 0;
        vector<int> low(g.size()), dfn(g.size(), -1);
        stack<int> st;
        auto dfs = [&](auto&& dfs, int u, int root) -> void
        {
            low[u] = dfn[u] = timestamp++;
            st.push(u);
            if(u==root&&g[u].empty()) m_groups.emplace_back(1,u);
            int s = 0;
            for(auto& e : g[u])
            {
                if(dfn[e.to]==-1)
                {
                    dfs(dfs, e.to, root);
                    low[u] = min(low[u], low[e.to]);
                    if(low[e.to]>=dfn[u])
                    {
                        if(++s+(u!=root)==2) m_cuts.push_back(u);
                        m_groups.emplace_back();
                        int w;
                        do
                        {
                            w = st.top();
                            st.pop();
                            m_groups.back().push_back(w);
                        }
                        while(w!=e.to);
                        m_groups.back().push_back(u);
                    }
                }
                else low[u] = min(low[u], dfn[e.to]);
            }
        };
        for(int i=0;i<g.size();i++) if(dfn[i]==-1) dfs(dfs, i, i);
    }
    int size() const { return m_groups.size(); }
    auto& cuts() const { return m_cuts; }
    auto& groups() const { return m_groups; }
    auto bctree() const
    {
        graph<> t(n+size());
        int cnt = n;
        for(auto& group : m_groups)
        {
            for(auto v : group) t.add_edge(cnt, v);
            cnt++;
        }
        return t;
    }
private:
    int n;
    vector<int> m_cuts;
    vector<vector<int>> m_groups;
};
