template <typename W=int>
class seggraph
{
    size_t n, sz;
    array<size_t, 2> base;
    vector<vector<pair<size_t, W>>> adj;
    auto collect(size_t l, size_t r, size_t offset)
    {
        vector<size_t> ns;
        for (l+=sz,r+=sz;l<=r;l>>=1,r>>=1)
        {
            if(l&1) ns.push_back(offset+(l++));
            if(!(r&1)) ns.push_back(offset+(r--));
        }
        return ns;
    }
public:
    using range = pair<size_t, size_t>;
    explicit seggraph(size_t n) : n(n), sz(bit_ceil(n)), base({2*sz-1, 4*sz-1}), adj(base[1]+n)
    {
        for(size_t i=1;i<sz;i++)
        {
            adj[i].emplace_back(i<<1, 0);
            adj[i].emplace_back(i<<1|1, 0);
            adj[base[0]+(i<<1)].emplace_back(base[0]+i, 0);
            adj[base[0]+(i<<1|1)].emplace_back(base[0]+i, 0);
        }
        for(size_t i=0;i<n;i++)
        {
            auto o = id(i);
            adj[i+sz].emplace_back(o, 0);
            adj[o].emplace_back(base[0]+i+sz, 0);
        }
    }
    auto id(size_t u) const { return base[1]+u; }
    void add_arc(size_t u, size_t v, W w=1) { adj[id(u)].emplace_back(id(v), w); }
    void add_arc(size_t u, range r, W w=1)
    {
        auto ns = collect(r.first, r.second, 0);
        auto x = id(u);
        for(auto y : ns) adj[x].emplace_back(y, w);
    }
    void add_arc(range r, size_t v, W w=1)
    {
        auto ns = collect(r.first, r.second, base[0]);
        auto x = id(v);
        for(auto y : ns) adj[y].emplace_back(x, w);
    }
    void add_arc(range r, range s, W w=1)
    {
        auto vs1=collect(r.first, r.second, 0), vs2=collect(s.first, s.second, base[0]);
        adj.emplace_back();
        for(auto x : vs1) adj[x].emplace_back(adj.size()-1, 0);
        for(auto y : vs2) adj[adj.size()-1].emplace_back(y, w);
    }
    auto& graph() const { return adj; }
};
