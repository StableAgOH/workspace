template <typename T>
class mo
{
    struct Q { int l, r; size_t id; uint64_t h; };
    const int K;
    vector<Q> qs;
    uint64_t hilbert(int x, int y) const
    {
        uint64_t d = 0;
        for(int s=1<<(K-1);s>0;s>>=1)
        {
            bool rx=x&s, ry=y&s;
            d += (uint64_t)s*s*((3*rx)^ry);
            if(ry) continue;
            if(rx) x=(1<<K)-1-x, y=(1<<K)-1-y;
            swap(x, y);
        }
        return d;
    }
public:
    explicit mo(size_t n) : K(bit_width(n)) {}
    void add_query(size_t l, size_t r) { qs.emplace_back(l, r, qs.size(), hilbert(l, r)); }
    auto operator()(auto&& al, auto&& ar, auto&& dl, auto&& dr, auto&& get)
    {
        ranges::sort(qs, {}, &Q::h);
        vector<T> ans(qs.size());
        int l=0, r=-1;
        for(const auto& q : qs)
        {
            while(l>q.l) al(--l);
            while(r<q.r) ar(++r);
            while(l<q.l) dl(l++);
            while(r>q.r) dr(r--);
            ans[q.id] = get(l, r);
        }
        return ans;
    }
};
