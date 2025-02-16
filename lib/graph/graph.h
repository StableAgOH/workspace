template <typename T=int>
class graph
{
public:
    struct edge
    {
        int idx, from, to;
        T cost;
        edge() = default;
        edge(int idx, int to, T cost=1) : idx(idx), to(to), cost(cost) {}
        operator int() const { return to; }
    };
    explicit graph(int n) : idx(0), adj(n) {}
    auto& operator[](int u) const { return adj[u]; }
    int size() const { return adj.size(); }
    void add_arc(int from, int to, T cost=1) { adj[from].emplace_back(idx++, to, cost); }
    void add_edge(int from, int to, T cost=1) { add_arc(from, to, cost); add_arc(to, from, cost); }
    template <typename F>
    void for_each(int u, F&& callback) const { for(const auto& e : adj[u]) callback(e); }
private:
    int idx;
    vector<vector<edge>> adj;
};
