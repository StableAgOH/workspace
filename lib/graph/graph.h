template <typename T=int>
class graph
{
public:
    struct edge { int to, id; T weight; };
    explicit graph(int n) : adj(n) {}
    auto& operator[](int u) const { return adj[u]; }
    int node_cnt() const { return adj.size(); }
    int edge_cnt() const { return ecnt; }
    void add_arc(int u, int v, T weight=1) { adj[u].emplace_back(v, ecnt++, weight); }
    void add_edge(int u, int v, T weight=1) { add_arc(u, v, weight); add_arc(v, u, weight); }
private:
    int ecnt = 0;
    vector<vector<edge>> adj;
};
