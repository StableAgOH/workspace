template <typename Q>
class mo
{
    size_t n;
    vector<Q> q;
public:
    mo(size_t n) : n(n) {}
    void add_query(Q&& q) { this->q.push_back(q); }
    auto operator()(auto&& push_front, auto&& pop_front, auto&& push_back, auto&& pop_back, auto&& calc)
    {
        vector<invoke_result_t<decltype(calc), Q>> ans(q.size());
        int siz = n/sqrt(q.size());
        vector<int> pos(n+1);
        for(size_t i=1;i<=n;i++) pos[i] = i/siz;
        vector<int> o(q.size());
        iota(o.begin(), o.end(), 0);
        sort(o.begin(), o.end(), [&](int i, int j) {
            if(pos[get<0>(q[i])]!=pos[get<0>(q[j])]) return get<0>(q[i])<get<0>(q[j]);
            if((pos[get<0>(q[i])]&1)) return get<1>(q[i])<get<1>(q[j]);
            return get<1>(q[i])>get<1>(q[j]);
        });
        int cl=0, cr=-1;
        for(auto i : o)
        {
            int l=get<0>(q[i]), r=get<1>(q[i]);
            while(cl>l) push_front(--cl);
            while(cr<r) push_back(++cr);
            while(cl<l) pop_front(cl++);
            while(cr>r) pop_back(cr--);
            ans[i] = calc(q[i]);
        }
        return ans;
    }
};
