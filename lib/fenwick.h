template <typename T>
class fenwick
{
    static constexpr auto lowbit(auto x) { return x&-x; }
    size_t n;
    vector<T> data;
public:
    fenwick(ranges::range auto&& rg) : n(ranges::size(rg)), data(n+1)
    {
        vector<T> p(n+1);
        inclusive_scan(rg.begin(), rg.end(), p.begin()+1);
        for(size_t i=1;i<=n;i++) data[i] = p[i]-p[i-lowbit(i)];
    }
    fenwick(size_t n, const T& init={}) : fenwick(vector(n, init)) {}
    auto prefix_sum(size_t p) const
    {
        T sum{};
        for(size_t i=p+1;i;i-=lowbit(i)) sum += data[i];
        return sum;
    }
    auto operator()(size_t l) const { return (*this)(l,l); }
    auto operator()(size_t l, size_t r) const { return prefix_sum(r)-prefix_sum(l-1); }
    void add(size_t p, const T& x) { for(size_t i=p+1;i<=n;i+=lowbit(i)) data[i] += x; }
    void clear() { ranges::fill(data, T()); }
    auto size() const { return n; }
};
