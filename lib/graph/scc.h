class scc
{
public:
    template <typename T>
    scc(const graph<T>& g) : n(g.size()), cnt(0), id(n)
    {
        int timestamp = 0;
        vector<int> low(n), dfn(n, -1);
        stack<int> st;
        auto dfs = [&](auto&& dfs, int u) -> void
        {
            low[u] = dfn[u] = timestamp++;
            st.push(u);
            for(auto& e : g[u])
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
                    dfn[v] = n;
                    id[v] = cnt;
                    if(v==u) break;
                }
                cnt++;
            }
        };
        for(int i=0;i<n;i++) if(dfn[i]==-1) dfs(dfs, i);
        for(auto& x : id) x = cnt-1-x;
    }
    auto operator[](int u) const { return id[u]; }
    auto size() const { return cnt; }
    auto groups() const
    {
        vector<vector<int>> groups(cnt);
        for(int i=0;i<n;i++) groups[id[i]].push_back(i);
        return groups;
    }
private:
    int n, cnt;
    vector<int> id;
};
