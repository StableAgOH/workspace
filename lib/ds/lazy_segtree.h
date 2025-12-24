template <typename T, typename Op, typename E1,
    typename Lazy, typename Cp, typename Ap, typename E2>
requires convertible_to<invoke_result_t<Op, T, T>, T> &&
    convertible_to<invoke_result_t<E1>, T> &&
    invocable<Cp, Lazy&, Lazy> &&
    invocable<Ap, T&, Lazy> &&
    convertible_to<invoke_result_t<E2>, Lazy>
class lazy_segtree
{
    static constexpr auto lowbit(size_t x) { return x&-x; }
    Op op; E1 e1; Cp cp; Ap ap; E2 e2;
    size_t n, sz, lg;
    vector<T> data;
    vector<Lazy> lazy;
    void update(size_t p) { data[p] = op(data[p<<1], data[p<<1|1]); }
    void all_apply(size_t p, const Lazy& lz)
    {
        ap(data[p], lz);
        if(p<sz) cp(lazy[p], lz);
    }
    void push(size_t p)
    {
        all_apply(p<<1, lazy[p]);
        all_apply(p<<1|1, lazy[p]);
        lazy[p] = lazy[0];
    }
public:
    lazy_segtree(ranges::range auto&& rg, Op op, E1 e1, Cp cp, Ap ap, E2 e2) :
        op(op), e1(e1), cp(cp), ap(ap), e2(e2),
        n(ranges::size(rg)), sz(bit_ceil(n)), lg(countr_zero(sz)), data(sz<<1, e1()), lazy(sz, e2())
    {
        ranges::copy(rg, data.begin()+sz);
        for(auto i=sz-1;i>=1;i--) update(i);
    }
    lazy_segtree(size_t n, Op op, E1 e1, Cp cp, Ap ap, E2 e2, const T& init={}) :
        lazy_segtree(vector(n, init), op, e1, cp, ap, e2) {}
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
            if(l&1) resl = op(resl, data[l++]);
            if(r&1) resr = op(data[--r], resr);
        }
        return op(resl, resr);
    }
    void transform(size_t p, invocable<T&> auto&& f)
    {
        p += sz;
        for(auto i=lg;i>=1;i--) push(p>>i);
        f(data[p]);
        for(size_t i=1;i<=lg;i++) update(p>>i);
    }
    void set(size_t p, const T& x) { transform(p, [&](T& y) { y = x; }); }
    void try_change(size_t p, const T& x) { transform(p, [&](T& y) { y = op(y, x); }); }
    void apply(size_t p, const Lazy& lz)
    {
        p += sz;
        for(auto i=lg;i>=1;i--) push(p>>i);
        apply(data[p], lz);
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
    auto min_left(size_t r, predicate<T> auto&& pred) const
    {
        if(!r) return 0;
        r += sz;
        for(auto i=lg;i>=1;i--) push((r-1)>>i);
        auto sum = data[0];
        do
        {
            r--;
            while(r>1&&(r&1)) r >>= 1;
            if(!pred(op(data[r], sum)))
            {
                while(r<sz)
                {
                    push(r);
                    r = r<<1|1;
                    if(auto x=op(data[r], sum);pred(x)) { sum = x; r--; }
                }
                return r+1-sz;
            }
            sum = op(data[r], sum);
        }
        while(lowbit(r)!=r);
        return 0;
    }
    auto max_right(size_t l, predicate<T> auto&& pred) const
    {
        if(l==n) return n;
        l += sz;
        for(auto i=lg;i>=1;i--) push(l>>i);
        auto sum = data[0];
        do
        {
            while(!(l&1)) l >>= 1;
            if(!pred(op(sum, data[l])))
            {
                while(l<sz)
                {
                    push(l);
                    l <<= 1;
                    if(auto x=op(sum, data[l]);pred(x)) { sum = x; l++; }
                }
                return l-sz;
            }
            sum = op(sum, data[l++]);
        }
        while(lowbit(l)!=l);
        return n;
    }
};
template <ranges::range R, typename Op, typename E1, typename Compose, typename Apply, typename E2>
lazy_segtree(R, Op, E1, Compose, Apply, E2) -> lazy_segtree<ranges::range_value_t<R>, Op, E1, 
    invoke_result_t<E2>, Compose, Apply, E2>;
