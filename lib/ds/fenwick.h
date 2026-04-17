template <typename T>
class fenwick
{
    static constexpr auto lowbit(size_t x) { return x&-x; }
    vector<T> d;
public:
    fenwick(ranges::range auto&& rg) : d(ranges::begin(rg), ranges::end(rg))
    {
        for(size_t i=1;i<=d.size();i++)
        {
            auto j = i+lowbit(i);
            if(j<=d.size()) d[j-1] += d[i-1];
        }
    }
    fenwick(size_t n, const T& init={}) : fenwick(vector(n, init)) {}
    void add(size_t p, const T& x)
    {
        for(size_t i=p+1;i<=d.size();i+=lowbit(i))
            d[i-1] += x;
    }
    T prefix(size_t p) const
    {
        T sum{};
        for(size_t i=p+1;i;i-=lowbit(i)) sum += d[i-1];
        return sum;
    }
    T operator()(size_t l, size_t r) const { return prefix(r)-prefix(l-1); }
    T operator[](size_t p) const { return (*this)(p, p); }
};
