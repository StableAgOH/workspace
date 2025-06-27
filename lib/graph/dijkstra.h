template <typename W>
class dijkstra
{
    vector<vector<pair<int, W>>> g;
public:
    struct result
    {
        vector<W> dis;
        vector<vector<int>> pre;
        explicit result(int n, int start, W inf) : dis(n, inf), pre(n) { dis[start] = 0; }
    };
    explicit dijkstra(int n) : g(n) {}
    void add_arc(int u, int v, W w) { g[u].emplace_back(v, w); }
    void add_edge(int u, int v, W w) { add_arc(u, v, w), add_arc(v, u, w); }
    auto operator[](size_t p) const { return g[p]; }
    auto operator()(int start, const W inf = numeric_limits<W>::max()/2) const
    {
        result res(g.size(), start, inf);
        priority_queue<pair<W, int>, vector<pair<W, int>>, greater<>> pq;
        pq.emplace(0, start);
        while(!pq.empty())
        {
            auto [d,u] = pq.top();
            pq.pop();
            if(d>res.dis[u]) continue;
            for(auto [v,w] : g[u])
            {
                if(d+w<res.dis[v])
                {
                    res.dis[v] = d+w;
                    res.pre[v] = {u};
                    pq.emplace(res.dis[v], v);
                }
                else if(d+w==res.dis[v]) res.pre[v].push_back(u);
            }
        }
        return res;
    }
};
