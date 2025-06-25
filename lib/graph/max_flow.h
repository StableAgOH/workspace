template <typename T>
class max_flow
{
    struct edge
    {
        int to, rev;
        T cap, flow;
    };
    vector<vector<edge>> adj;
public:
    explicit max_flow(int n) : adj(n) {}
    void add_edge(int u, int v, T cap)
    {
        adj[u].emplace_back(v, adj[v].size(), cap, 0);
        adj[v].emplace_back(u, adj[u].size()-1, 0, 0);
    }
    auto flow(int s, int t, T limit=numeric_limits<T>::max())
    {
        vector<int> level(adj.size()), iter(adj.size());
        auto bfs = [&]()
        {
            ranges::fill(level, -1);
            level[s] = 0;
            queue<int> q;
            q.push(s);
            while(!q.empty())
            {
                int u = q.front();
                q.pop();
                for(const auto& e : adj[u])
                {
                    if(e.cap==0||level[e.to]>=0) continue;
                    level[e.to] = level[u]+1;
                    if(e.to==t) return;
                    q.push(e.to);
                }
            }
        };
        auto dfs = [&](auto&& self, int u, T up)
        {
            if(u==s) return up;
            T res = 0;
            for(int& i=iter[u];i<(int)adj[u].size();i++)
            {
                auto& e = adj[u][i];
                if(level[u]<=level[e.to]||adj[e.to][e.rev].cap==0) continue;
                T d = self(self, e.to, min(up-res, adj[e.to][e.rev].cap));
                if(d<=0) continue;
                e.cap += d;
                adj[e.to][e.rev].cap -= d;
                res += d;
                if(res==up) return res;
            }
            level[u] = adj.size();
            return res;
        };
        T flow = 0;
        while(flow<limit)
        {
            bfs();
            if(level[t]==-1) break;
            ranges::fill(iter, 0);
            T f = dfs(dfs, t, limit-flow);
            if(f==0) break;
            flow += f;
        }
        return flow;
    }
    auto min_cut(int s)
    {
        vector<bool> cut(adj.size());
        queue<int> q;
        q.push(s);
        while(!q.empty())
        {
            int u = q.front();
            q.pop();
            cut[u] = true;
            for(const auto& e : adj[u])
            {
                if(e.cap==0||cut[e.to]) continue;
                cut[e.to] = true;
                q.push(e.to);
            }
        }
        return cut;
    }
};
