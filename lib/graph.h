using edge_t = int;
class graph_tag
{
protected:
    int n;
    vector<vector<pair<int,edge_t>>> G;
    graph_tag(int n) : n(n) { G.resize(n+1); }
public:
    void add_edge(int u,int v,edge_t w=1) { G[u].emplace_back(v,w); }
    void add_biedge(int u,int v,edge_t w=1) { add_edge(u,v,w); add_edge(v,u,w); }
};
class graph_dijkstra_tag : public virtual graph_tag
{
protected:
    graph_dijkstra_tag(int n) : graph_tag(n) {}
public:
    auto dijkstra(int s, ll inf=numeric_limits<ll>::max()/2)
    {
        using pi = pair<ll,int>;
        vector<bool> vis(n+1);
        vector<ll> dis(n+1, inf);
        priority_queue<pi, vector<pi>, greater<>> pq;
        dis[s] = 0;
        pq.emplace(0,s);
        while(!pq.empty())
        {
            auto [d,u] = pq.top();
            pq.pop();
            if(vis[u]) continue;
            vis[u] = true;
            for(auto [v,w] : G[u])
            {
                auto t = dis[u]+w;
                if(t<dis[v]) pq.emplace(dis[v]=t, v);
            }
        }
        return dis;
    }
};
class graph_prim_tag : public virtual graph_tag
{
protected:
    graph_prim_tag(int n) : graph_tag(n) {}
public:
    auto prim(edge_t inf=numeric_limits<edge_t>::max()/2) const
    {
        ll ans = 0;
        vector<tuple<int,int,edge_t>> tree;
        using pi = pair<edge_t,int>;
        vector<bool> vis(n+1);
        vector<edge_t> dis(n+1, inf);
        priority_queue<pi, vector<pi>, greater<>> pq;
        dis[1] = 0;
        pq.emplace(0,1);
        int cnt = 0;
        while(!pq.empty()&&cnt<n)
        {
            auto [d,u] = pq.top();
            pq.pop();
            if(vis[u]) continue;
            vis[u] = true;
            ans += d;
            cnt++;
            for(auto [v,w] : G[u]) if(w<dis[v]) pq.emplace(dis[v]=w, v);
        }
        return pair(ans, cnt==n);
    }
};
template <derived_from<graph_tag>... Tags>
class graph : public virtual graph_tag, public Tags...
{
public:
    graph(int n) : graph_tag(n), Tags(n)... {}
};
