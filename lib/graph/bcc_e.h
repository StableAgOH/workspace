class bcc_e
{
public:
    template <typename T>
    bcc_e(const graph<T>& g) : n(g.size()), cnt(0), id(n)
    {
        int timestamp = 0;
        vector<int> low(n), dfn(n, -1);
        stack<int> st;
        auto dfs = [&](auto&& dfs, int u, int i) -> void
        {
            low[u] = dfn[u] = timestamp++;
            st.push(u);
            for(auto& e : g[u])
            {
                if(e.idx==(i^1)) return;
                if(dfn[e.to]==-1)
                {
                    dfs(dfs, e.to, e.idx);
                    low[u] = min(low[u], low[e.to]);
                    if(low[e.to]>dfn[u]) m_cuts.push_back(minmax(e.idx, e.idx^1));
                }
                else low[u] = min(low[u], dfn[e.to]);
            }
            if(low[u]==dfn[u])
            {
                while(true)
                {
                    int v = st.top();
                    st.pop();
                    dfn[v] = n;
                    id[v] = cnt;
                    if(v==u) break;
                }
                cnt++;
            }
        };
        for(int i=0;i<n;i++) if(dfn[i]==-1) dfs(dfs, i, -1);
        for(auto& x : id) x = cnt-1-x;
    }
    auto operator[](int u) const { return id[u]; }
    auto size() const { return cnt; }
    auto& cuts() const { return m_cuts; }
    auto groups() const
    {
        vector<vector<int>> groups(cnt);
        for(int i=0;i<n;i++) groups[id[i]].push_back(i);
        return groups;
    }
private:
    int n, cnt;
    vector<int> id;
    vector<pair<int,int>> m_cuts;
};
