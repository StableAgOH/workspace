template <typename T>
class difference_constraint
{
    int n;
    vector<tuple<int, int, T>> edges;
    void add_arc(int u, int v, T w) { edges.emplace_back(u, v, w); }
public:
    difference_constraint(int n) : n(n) { for(int i=0;i<n;i++) add_arc(n, i, 0); }
    void add_leq(int u, int v, T w) { add_arc(v, u, w); }
    void add_geq(int u, int v, T w) { add_arc(u, v, -w); }
    void add_eq(int u, int v, T w) { add_leq(u, v, w); add_geq(u, v, w); }
    auto operator()()
    {
        vector<T> dis(n+1, numeric_limits<T>::max()/2);
        dis[n] = 0;
        bool relax;
        for(int i=0;i<=n;i++)
        {
            relax = false;
            for(auto [u,v,w] : edges)
            {
                if(dis[u]+w<dis[v])
                {
                    dis[v] = dis[u]+w;
                    relax = true;
                }
            }
            if(!relax) break;
        }
        return relax?vector<T>{}:dis;
    }
};
