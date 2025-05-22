template <typename T, typename Lazy, auto Op, auto Compose, auto Apply>
class lazy_segtree
{
    static_assert(convertible_to<invoke_result_t<decltype(Op), T, T>, T>);
    static_assert(invocable<decltype(Compose), Lazy&, Lazy>);
    static_assert(invocable<decltype(Apply), T&, Lazy>);
    static constexpr auto lowbit(auto x) { return x&-x; }
    size_t n, sz, lg;
    vector<T> data;
    vector<Lazy> lazy;
    void update(size_t p) { data[p] = Op(data[p<<1], data[p<<1|1]); }
    void all_apply(size_t p, const Lazy& lz)
    {
        Apply(data[p], lz);
        if(p<sz) Compose(lazy[p], lz);
    }
    void push(size_t p)
    {
        all_apply(p<<1, lazy[p]);
        all_apply(p<<1|1, lazy[p]);
        lazy[p] = lazy[0];
    }
public:
    lazy_segtree(ranges::range auto&& rg, T e1={}, Lazy e2={}) :
        n(ranges::size(rg)), sz(bit_ceil(n)), lg(countr_zero(sz)), data(2*sz, e1), lazy(sz, e2)
    {
        ranges::copy(rg, data.begin()+sz);
        for(auto i=sz-1;i>=1;i--) update(i);
    }
    lazy_segtree(size_t n, T e1={}, Lazy e2={}) : lazy_segtree(vector(n, e1), e1, e2) {}
    auto operator()() const { return data[1]; }
    auto operator[](size_t p)
    {
        p += sz;
        for(auto i=lg;i>=1;i--) push(p>>i);
        return data[p];
    }
    auto operator()(size_t l, size_t r)
    {
        l+=sz, r+=sz+1;
        for(auto i=lg;i>=1;i--)
        {
            if(((l>>i)<<i)!=l) push(l>>i);
            if(((r>>i)<<i)!=r) push((r-1)>>i);
        }
        auto resl=data[0], resr=data[0];
        for(;l<r;l>>=1,r>>=1)
        {
            if(l&1) resl = Op(resl, data[l++]);
            if(r&1) resr = Op(data[--r], resr);
        }
        return Op(resl, resr);
    }
    auto size() const { return n; }
    void set(size_t p, const T& x)
    {
        p += sz;
        for(auto i=lg;i>=1;i--) push(p>>i);
        data[p] = x;
        for(size_t i=1;i<=lg;i++) update(p>>i);
    }
    void apply(size_t p, const Lazy& lz)
    {
        p += sz;
        for(auto i=lg;i>=1;i--) push(p>>i);
        data[p] = Apply(data[p], lz);
        for(size_t i=1;i<=lg;i++) update(p>>i);
    }
    void apply(size_t l, size_t r, const Lazy& lz)
    {
        l+=sz, r+=sz+1;
        for(auto i=lg;i>=1;i--)
        {
            if(((l>>i)<<i)!=l) push(l>>i);
            if(((r>>i)<<i)!=r) push((r-1)>>i);
        }
        for(auto i=l,j=r;i<j;i>>=1,j>>=1)
        {
            if(i&1) all_apply(i++, lz);
            if(j&1) all_apply(--j, lz);
        }
        for(size_t i=1;i<=lg;i++)
        {
            if(((l>>i)<<i)!=l) update(l>>i);
            if(((r>>i)<<i)!=r) update((r-1)>>i);
        }
    }
    template <predicate<T> Pred>
    size_t min_left(size_t r, Pred&& pred) const
    {
        if(!r) return 0;
        r += sz;
        for(auto i=lg;i>=1;i--) push((r-1)>>i);
        auto sum = data[0];
        do
        {
            r--;
            while(r>1&&(r&1)) r >>= 1;
            if(!pred(Op(data[r], sum)))
            {
                while(r<sz)
                {
                    push(r);
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
    template <predicate<T> Pred>
    size_t max_right(size_t l, Pred&& pred) const
    {
        if(l==n) return n;
        l += sz;
        for(auto i=lg;i>=1;i--) push(l>>i);
        auto sum = data[0];
        do
        {
            while(!(l&1)) l >>= 1;
            if(!pred(Op(sum, data[l])))
            {
                while(l<sz)
                {
                    push(l);
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
