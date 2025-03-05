template <typename T=int>
class graph
{
public:
    struct edge
    {
        int idx, to;
        T weight;
        edge(int idx, int to, T weight=1) : idx(idx), to(to), weight(weight) {}
        operator int() const { return to; }
    };
    explicit graph(int n) : adj(n) {}
    auto& operator[](int u) const { return adj[u]; }
    int size() const { return adj.size(); }
    void add_arc(int from, int to, T weight=1) { adj[from].emplace_back(idx++, to, weight); }
    void add_edge(int from, int to, T weight=1) { add_arc(from, to, weight); add_arc(to, from, weight); }
private:
    int idx = 0;
    vector<vector<edge>> adj;
};
