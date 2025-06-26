template <typename T, auto Op>
requires convertible_to<invoke_result_t<decltype(Op), T, T>, T>
class segtree
{
    static constexpr auto lowbit(size_t x) { return x&-x; }
    size_t n, sz;
    vector<T> data;
    void update(size_t p) { data[p] = Op(data[p<<1], data[p<<1|1]); }
public:
    segtree(ranges::range auto&& rg, const T& e) : n(ranges::size(rg)), sz(bit_ceil(n)), data(sz<<1, e)
    {
        ranges::copy(rg, data.begin()+sz);
        for(auto i=sz-1;i>=1;i--) update(i);
    }
    segtree(size_t n, const T& e, const T& init={}) : segtree(vector(n, init), e) {}
    auto operator()() const { return data[1]; }
    auto operator[](size_t p) const { return data[p+sz]; }
    auto operator()(size_t l, size_t r) const
    {
        auto resl=data[0], resr=data[0];
        for(l+=sz,r+=sz+1;l<r;l>>=1,r>>=1)
        {
            if(l&1) resl = Op(resl, data[l++]);
            if(r&1) resr = Op(data[--r], resr);
        }
        return Op(resl, resr);
    }
    void transform(size_t p, invocable<T&> auto&& f) { for(f(data[p+=sz]);p>1;p>>=1) update(p>>1); }
    void set(size_t p, const T& x) { transform(p, [&](T& v) { v = x; }); }
    size_t min_left(size_t r, predicate<T> auto&& pred) const
    {
        if(!r) return 0;
        r += sz;
        auto sum = data[0];
        do
        {
            r--;
            while(r>1&&(r&1)) r >>= 1;
            if(!pred(Op(data[r], sum)))
            {
                while(r<sz)
                {
                    r = r<<1|1;
                    if(auto x=Op(data[r], sum);pred(x)) { sum = x; r--; }
                }
                return r+1-sz;
            }
            sum = Op(data[r], sum);
        }
        while(lowbit(r)!=r);
        return 0;
    }
    size_t max_right(size_t l, predicate<T> auto&& pred) const
    {
        if(l==n) return n;
        l += sz;
        auto sum = data[0];
        do
        {
            while(!(l&1)) l >>= 1;
            if(!pred(Op(sum, data[l])))
            {
                while(l<sz)
                {
                    l <<= 1;
                    if(auto x=Op(sum, data[l]);pred(x)) { sum = x; l++; }
                }
                return l-sz;
            }
            sum = Op(sum, data[l++]);
        }
        while(lowbit(l)!=l);
        return n;
    }
};
