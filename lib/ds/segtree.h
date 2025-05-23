template <typename T>
requires requires(T a, T b)
{
    {a+b} -> same_as<T>;
    {T::e()} -> same_as<T>;
}
class segtree
{
    static constexpr auto lowbit(auto x) { return x&-x; }
    size_t n, sz;
    vector<T> data;
    void update(size_t p) { data[p] = data[p<<1]+data[p<<1|1]; }
public:
    segtree(ranges::range auto&& rg) : n(ranges::size(rg)), sz(bit_ceil(n)), data(sz<<1, T::e())
    {
        ranges::copy(rg, data.begin()+sz);
        for(auto i=sz-1;i>=1;i--) update(i);
    }
    segtree(size_t n, const T& init={}) : segtree(vector(n, init)) {}
    auto operator()() const { return data[1]; }
    auto operator[](size_t p) const { return data[p+sz]; }
    auto operator()(size_t l, size_t r) const
    {
        auto resl=data[0], resr=data[0];
        for(l+=sz,r+=sz+1;l<r;l>>=1,r>>=1)
        {
            if(l&1) resl = resl+data[l++];
            if(r&1) resr = data[--r]+resr;
        }
        return resl+resr;
    }
    auto size() const { return n; }
    void set(size_t p, const T& x) { for(data[p+=sz]=x;p>1;p>>=1) update(p>>1); }
    template <predicate<T> Pred>
    size_t min_left(size_t r, Pred&& pred) const
    {
        if(!r) return 0;
        r += sz;
        auto sum = data[0];
        do
        {
            r--;
            while(r>1&&(r&1)) r >>= 1;
            if(!pred(data[r]+sum))
            {
                while(r<sz)
                {
                    r = r<<1|1;
                    if(auto x=data[r]+sum;pred(x)) { sum = x; r--; }
                }
                return r+1-sz;
            }
            sum = data[r]+sum;
        }
        while(lowbit(r)!=r);
        return 0;
    }
    template <predicate<T> Pred>
    size_t max_right(size_t l, Pred&& pred) const
    {
        if(l==n) return n;
        l += sz;
        auto sum = data[0];
        do
        {
            while(!(l&1)) l >>= 1;
            if(!pred(sum+data[l]))
            {
                while(l<sz)
                {
                    l <<= 1;
                    if(auto x=sum+data[l];pred(x)) { sum = x; l++; }
                }
                return l-sz;
            }
            sum = sum+data[l++];
        }
        while(lowbit(l)!=l);
        return n;
    }
};
