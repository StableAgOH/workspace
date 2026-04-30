template <integral T=long long>
class flow_graph
{
    static constexpr T INF = numeric_limits<T>::max()/2;
    struct edge { size_t to, rev; T cap, cost; };
    vector<vector<edge>> adj;
    vector<T> dis;
    vector<size_t> ptr;
    vector<bool> vis;
    bool bfs(size_t s, size_t t)
    {
        ranges::fill(dis, -1);
        dis[s] = 0;
        queue<size_t> q({s});
        while(!q.empty())
        {
            auto v = q.front();
            q.pop();
            for(const auto& e : adj[v])
                if(e.cap>0&&dis[e.to]==-1)
                    dis[e.to] = dis[v]+1, q.push(e.to);
        }
        return dis[t]!=-1;
    }
    T dfs(size_t v, size_t t, T x)
    {
        if(x==0||v==t) return x;
        T flow = 0;
        for(auto& i=ptr[v];i<adj[v].size();i++)
        {
            auto& e = adj[v][i];
            if(dis[v]+1!=dis[e.to]||e.cap==0) continue;
            if(T d=dfs(e.to, t, min(x, e.cap));d>0)
            {
                e.cap -= d;
                adj[e.to][e.rev].cap += d;
                flow += d;
                x -= d;
                if(x==0) break;
            }
        }
        if(flow==0) dis[v] = -1;
        return flow;
    }
    bool spfa(size_t s, size_t t)
    {
        ranges::fill(dis, INF);
        dis[s] = 0;
        ranges::fill(vis, false);
        vis[s] = true;
        queue<size_t> q({s});
        while(!q.empty())
        {
            auto v = q.front();
            q.pop();
            vis[v] = false;
            for(auto& e : adj[v])
            {
                if(e.cap>0&&dis[e.to]>dis[v]+e.cost)
                {
                    dis[e.to] = dis[v]+e.cost;
                    if(!vis[e.to]) q.push(e.to), vis[e.to]=true;
                }
            }
        }
        return dis[t]!=INF;
    }
    T mcmf_dfs(size_t v, size_t t, T x, T& tot)
    {
        if(v==t) return x;
        vis[v] = true;
        T flow = 0;
        for(auto& i=ptr[v];i<adj[v].size();i++)
        {
            auto& e = adj[v][i];
            if(!vis[e.to]&&e.cap>0&&dis[e.to]==dis[v]+e.cost)
            {
                if(T d=mcmf_dfs(e.to, t, min(x, e.cap), tot);d>0)
                {
                    e.cap -= d;
                    adj[e.to][e.rev].cap += d;
                    tot += d*e.cost;
                    flow += d;
                    x -= d;
                    if(x==0) break;
                }
            }
        }
        if(flow==0) dis[v] = INF;
        vis[v] = false;
        return flow;
    }
public:
    flow_graph(size_t n) : adj(n), dis(n), ptr(n), vis(n) {}
    void add_edge(size_t u, size_t v, T cap, T cost=0)
    {
        adj[u].emplace_back(v, adj[v].size(), cap, cost);
        adj[v].emplace_back(u, adj[u].size()-1, 0, -cost);
    }
    auto max_flow(size_t s, size_t t)
    {
        T res = 0;
        while(bfs(s, t))
        {
            ranges::fill(ptr, 0);
            while(T x=dfs(s, t, INF)) res += x;
        }
        return res;
    }
    template <bool Slope=false>
    auto mcmf(size_t s, size_t t)
    {
        T flow=0, cost=0;
        vector<pair<T, T>> res = {{0, 0}};
        while(spfa(s, t))
        {
            ranges::fill(ptr, 0);
            if(T d=mcmf_dfs(s, t, INF, cost);d>0)
            {
                flow += d;
                if constexpr(Slope) res.emplace_back(flow, cost);
            }
        }
        if constexpr(Slope) return tuple(flow, cost, res);
        else return pair(flow, cost);
    }
};
