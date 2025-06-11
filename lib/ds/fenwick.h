template <typename T>
class fenwick
{
    static constexpr auto lowbit(size_t x) { return x&-x; }
    vector<T> data;
public:
    fenwick(ranges::range auto&& rg) : data(ranges::begin(rg), ranges::end(rg))
    {
        for(size_t i=1;i<=data.size();i++)
        {
            auto j = i+lowbit(i);
            if(j<=data.size()) data[j-1] += data[i-1];
        }
    }
    fenwick(size_t n, const T& init={}) : fenwick(vector(n, init)) {}
    void add(size_t p, const T& x) { for(auto i=p+1;i<=data.size();i+=lowbit(i)) data[i-1] += x; }
    template <typename U=T>
    auto operator()(size_t l, size_t r, U init={}) const
    {
        for(auto i=r+1;i;i-=lowbit(i)) init += data[i-1];
        for(auto i=l;i;i-=lowbit(i)) init -= data[i-1];
        return init;
    }
    auto operator[](size_t p) const { return (*this)(p, p); }
    void clear() { data.assign(data.size(), {}); }
    auto size() const { return data.size(); }
};
