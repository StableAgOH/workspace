template <typename T>
class fenwick
{
    static constexpr auto lowbit(auto x) { return x&-x; }
    vector<T> data;
public:
    fenwick(ranges::range auto&& rg) : data(ranges::size(rg)+1)
    {
        vector<T> p(data.size());
        inclusive_scan(rg.begin(), rg.end(), p.begin()+1);
        for(size_t i=1;i<p.size();i++) data[i] = p[i]-p[i-lowbit(i)];
    }
    fenwick(size_t n, const T& init={}) : fenwick(vector(n, init)) {}
    auto prefix(size_t p) const
    {
        T sum{};
        for(size_t i=p+1;i;i-=lowbit(i)) sum += data[i];
        return sum;
    }
    auto suffix(size_t p) const { return prefix(size()-1)-prefix(p); }
    auto operator()(size_t l, size_t r) const { return prefix(r)-prefix(l-1); }
    auto operator()(size_t l) const { return (*this)(l, l); }
    void add(size_t p, const T& x) { for(size_t i=p+1;i<=size();i+=lowbit(i)) data[i] += x; }
    void clear() { ranges::fill(data, T()); }
    auto size() const { return data.size()-1; }
};
