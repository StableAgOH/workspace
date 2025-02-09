struct csr
{
    vector<int> start, elist;
    csr(int n, const vector<pair<int,int>>& edges) : start(n+1), elist(edges.size())
    {
        for(auto e : edges) start[e.first+1]++;
        inclusive_scan(start.begin()+1, start.end(), start.begin()+1);
        auto counter = start;
        for (auto e : edges) elist[counter[e.first]++] = e.second;
    }
};
class scc_graph
{
    int n;
    vector<pair<int,int>> edges;
public:
    explicit scc_graph(int n) : n(n) {}
    void add_edge(int from, int to) { edges.emplace_back(from, to); }
    pair<int, vector<int>> scc_ids() const
    {
        csr g(n, edges);
        int timestamp=0, cnt=0;
        vector<int> low(n), dfn(n,-1), ids(n);
        stack<int> st;
        auto dfs = [&](auto&& dfs, int u) -> void
        {
            low[u] = dfn[u] = timestamp++;
            st.push(u);
            for(int i=g.start[u];i<g.start[u+1];i++)
            {
                auto v = g.elist[i];
                if(dfn[v]==-1)
                {
                    dfs(dfs, v);
                    low[u] = min(low[u], low[v]);
                }
                else low[u] = min(low[u], dfn[v]);
            }
            if(low[u]==dfn[u])
            {
                int v;
                do
                {
                    v = st.top();
                    st.pop();
                    dfn[v] = n;
                    ids[v] = cnt;
                }
                while(v!=u);
                cnt++;
            }
        };
        for(int i=0;i<n;i++) if(dfn[i]==-1) dfs(dfs, i);
        for(auto& x : ids) x = cnt-1-x;
        return {cnt, ids};
    }
    vector<vector<int>> scc() const
    {
        auto [cnt, ids] = scc_ids();
        vector<int> counts(cnt);
        for(auto x : ids) counts[x]++;
        vector<vector<int>> groups(cnt);
        for(int i=0;i<n;i++) groups[ids[i]].push_back(i);
        return groups;
    }
};
class two_sat
{
    int n;
    scc_graph scc;
public:
    explicit two_sat(int n) : n(n), scc(2*n) {}
    void add_clause(int i, bool f, int j, bool g)
    {
        scc.add_edge(2*i+!f, 2*j+g);
        scc.add_edge(2*j+!g, 2*i+f);
    }
    optional<vector<bool>> operator()() const
    {
        auto ids = scc.scc_ids().second;
        for(int i=0;i<n;i++) if(ids[2*i]==ids[2*i+1]) return nullopt;
        vector<bool> ans(n);
        for(int i=0;i<n;i++) ans[i] = ids[2*i]<ids[2*i+1];
        return ans;
    }
};
