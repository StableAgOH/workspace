template <typename T, auto Op, typename L, auto Cp, auto Ap>
requires convertible_to<invoke_result_t<decltype(Op), T, T>, T> &&
    invocable<decltype(Cp), L&, L> &&
    invocable<decltype(Ap), T&, L>
class lazy_segtree
{
    size_t n, sz, lg;
    vector<T> d;
    vector<L> z;
    void pull(size_t p) { d[p] = Op(d[p<<1], d[p<<1|1]); }
    void all_apply(size_t p, const L& lz)
    {
        Ap(d[p], lz);
        if(p<sz) Cp(z[p], lz);
    }
    void push(size_t p)
    {
        all_apply(p<<1, z[p]);
        all_apply(p<<1|1, z[p]);
        z[p] = z[0];
    }
public:
    lazy_segtree(size_t n, const T& e1={}, const L& e2={}) : n(n),
        sz(bit_ceil(n)), lg(countr_zero(sz)), d(sz<<1, e1), z(sz, e2) {}
    lazy_segtree(ranges::range auto&& rg, const T& e1={}, const L& e2={})
        : lazy_segtree(ranges::size(rg), e1, e2)
    {
        ranges::copy(rg, d.begin()+sz);
        for(auto i=sz-1;i>=1;i--) pull(i);
    }
    T operator()() const { return d[1]; }
    T operator[](size_t p) const { return d[p+sz]; }
    T operator()(size_t l, size_t r)
    {
        l+=sz, r+=sz;
        for(int i=lg;i>=1;i--)
        {
            if(((l>>i)<<i)!=l) push(l>>i);
            if(((r>>i)<<i)!=r) push((r-1)>>i);
        }
        T resl=d[0], resr=d[0];
        for(;l<r;l>>=1,r>>=1)
        {
            if(l&1) resl = Op(resl, d[l++]);
            if(r&1) resr = Op(d[--r], resr);
        }
        return Op(resl, resr);
    }
    void transform(size_t p, invocable<T&> auto&& f)
    {
        p += sz;
        for(auto i=lg;i>=1;i--) push(p>>i);
        f(d[p]);
        for(auto i=1;i<=lg;i++) pull(p>>i);
    }
    void set(size_t p, const T& x) { transform(p, [&](T& y) { y = x; }); }
    void compose(size_t p, const T& x) { transform(p, [&](T& y) { y = Op(y, x); }); }
    void apply(size_t p, const L& lz)
    {
        p += sz;
        for(auto i=lg;i>=1;i--) push(p>>i);
        Ap(d[p], lz);
        for(auto i=1;i<=lg;i++) pull(p>>i);
    }
    void apply(size_t l, size_t r, const L& lz)
    {
        l+=sz, r+=sz;
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
        for(auto i=1;i<=lg;i++)
        {
            if(((l>>i)<<i)!=l) pull(l>>i);
            if(((r>>i)<<i)!=r) pull((r-1)>>i);
        }
    }
    size_t min_left(size_t r, predicate<T> auto&& pred)
    {
        r += sz+1;
        for(auto i=lg;i>=1;i--) push((r-1)>>i);
        T sum = d[0];
        do
        {
            r--;
            while(r>1&&(r&1)) r >>= 1;
            if(!pred(Op(d[r], sum)))
            {
                while(r<sz)
                {
                    push(r);
                    r = r<<1|1;
                    if(T x=Op(d[r], sum);pred(x)) { sum = x; r--; }
                }
                return r+1-sz;
            }
            sum = Op(d[r], sum);
        }
        while((r&-r)!=r);
        return 0;
    }
    size_t max_right(size_t l, predicate<T> auto&& pred)
    {
        if(l==n) return n-1;
        l += sz;
        for(auto i=lg;i>=1;i--) push(l>>i);
        T sum = d[0];
        do
        {
            while(!(l&1)) l >>= 1;
            if(!pred(Op(sum, d[l])))
            {
                while(l<sz)
                {
                    push(l);
                    l <<= 1;
                    if(T x=Op(sum, d[l]);pred(x)) { sum = x; l++; }
                }
                return l-sz-1;
            }
            sum = Op(sum, d[l++]);
        }
        while((l&-l)!=l);
        return n-1;
    }
};
