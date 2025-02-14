class two_sat
{
public:
    explicit two_sat(int n) : n(n), g(2*n) {}
    auto& get_graph() const { return g; }
    void add_disjunction(int x, bool i, int y, bool j)
    {
        g.add_edge(2*x+!i, 2*y+j);
        g.add_edge(2*y+!j, 2*x+i);
    }
    vector<bool> operator()() const
    {
        scc s(g);
        for(int i=0;i<n;i++) if(s[2*i]==s[2*i+1]) return {};
        vector<bool> ans(n);
        for(int i=0;i<n;i++) ans[i] = s[2*i]<s[2*i+1];
        return ans;
    }
private:
    int n;
    graph<> g;
};
