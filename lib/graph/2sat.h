class two_sat : public scc
{
    int n;
public:
    explicit two_sat(int n) : scc(2*n), n(n) {}
    void add_disjunction(int x, bool i, int y, bool j)
    {
        add_arc(2*x+!i, 2*y+j);
        add_arc(2*y+!j, 2*x+i);
    }
    auto get_scc_result() const { return scc::operator()(); }
    auto operator()() const
    {
        auto s = get_scc_result();
        for(int i=0; i<n; i++) if(s.id[2*i]==s.id[2*i+1]) return vector<bool>{};
        vector<bool> ans(n);
        for(int i=0; i<n; i++) ans[i] = s.id[2*i]<s.id[2*i+1];
        return ans;
    }
};
