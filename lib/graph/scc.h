class scc
{
public:
    template <typename T>
    scc(const graph<T>& g) : cnt(0), id(g.node_cnt())
    {
        int timestamp = 0;
        vector<int> low(g.node_cnt()), dfn(g.node_cnt(), -1);
        stack<int> st;
        auto dfs = [&](auto&& dfs, int u) -> void
        {
            low[u] = dfn[u] = timestamp++;
            st.push(u);
            for(auto& e : g[u])
            {
                if(dfn[e.to]==-1)
                {
                    dfs(dfs, e.to);
                    low[u] = min(low[u], low[e.to]);
                }
                else low[u] = min(low[u], dfn[e.to]);
            }
            if(low[u]==dfn[u])
            {
                while(true)
                {
                    int v = st.top();
                    st.pop();
                    dfn[v] = g.node_cnt();
                    id[v] = cnt;
                    if(v==u) break;
                }
                cnt++;
            }
        };
        for(int i=0;i<g.node_cnt();i++) if(dfn[i]==-1) dfs(dfs, i);
        for(auto& x : id) x = cnt-1-x;
    }
    auto operator[](int u) const { return id[u]; }
    auto size() const { return cnt; }
    auto groups() const
    {
        vector<vector<int>> groups(cnt);
        for(size_t i=0;i<id.size();i++) groups[id[i]].push_back(i);
        return groups;
    }
private:
    int cnt;
    vector<int> id;
};
