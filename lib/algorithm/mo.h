template <typename T>
class mo
{
    int n;
    vector<pair<int, int>> q;
public:
    mo(int n) : n(n) {}
    void add_query(int l, int r) { q.emplace_back(l, r); }
    template <typename C>
    auto operator()(C&& calculator)
    {
        vector<T> ans(q.size());
        int siz = n/sqrt(q.size())+1;
        vector<int> pos(n+1);
        for(int i=1;i<=n;i++) pos[i] = i/siz;
        vector<int> o(q.size());
        iota(o.begin(), o.end(), 0);
        sort(o.begin(), o.end(), [&](int i, int j) {
            if(pos[q[i].first]!=pos[q[j].first]) return q[i].first<q[j].first;
            if((pos[q[i].first]&1)) return q[i].second<q[j].second;
            return q[i].second>q[j].second;
        });
        int cl=0, cr=-1;
        for(auto i : o)
        {
            auto [l,r] = q[i];
            while(cl>l) calculator.push_front(--cl);
            while(cr<r) calculator.push_back(++cr);
            while(cl<l) calculator.pop_front(cl++);
            while(cr>r) calculator.pop_back(cr--);
            ans[i] = calculator(l, r);
        }
        return ans;
    }
};
