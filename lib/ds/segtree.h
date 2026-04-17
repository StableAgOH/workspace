template <typename T, auto Op>
requires convertible_to<invoke_result_t<decltype(Op), T, T>, T>
class segtree
{
    size_t n, sz;
    vector<T> d;
    void pull(size_t p) { d[p] = Op(d[p<<1], d[p<<1|1]); }
public:
    segtree(size_t n, const T& e={}) : n(n), sz(bit_ceil(n)), d(sz<<1, e) {}
    segtree(ranges::range auto&& rg, const T& e={}) : segtree(ranges::size(rg), e)
    {
        ranges::copy(rg, d.begin()+sz);
        for(size_t i=sz-1;i>=1;i--) pull(i);
    }
    T operator()() const { return d[1]; }
    T operator[](size_t p) const { return d[p+sz]; }
    T operator()(size_t l, size_t r) const
    {
        T resl=d[0], resr=d[0];
        for(l+=sz,r+=sz+1;l<r;l>>=1,r>>=1)
        {
            if(l&1) resl = Op(resl, d[l++]);
            if(r&1) resr = Op(d[--r], resr);
        }
        return Op(resl, resr);
    }
    void transform(size_t p, invocable<T&> auto&& f)
    {
        for(f(d[p+=sz]);p>1;p>>=1)
            pull(p>>1);
    }
    void set(size_t p, const T& x) { transform(p, [&](T& y) { y = x; }); }
    void compose(size_t p, const T& x) { transform(p, [&](T& y) { y = Op(y, x); }); }
    size_t min_left(size_t r, predicate<T> auto&& pred) const
    {
        r += sz+1;
        T sum = d[0];
        do
        {
            r--;
            while(r>1&&(r&1)) r >>= 1;
            if(!pred(Op(d[r], sum)))
            {
                while(r<sz)
                {
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
    size_t max_right(size_t l, predicate<T> auto&& pred) const
    {
        if(l==n) return n-1;
        l += sz;
        T sum = d[0];
        do
        {
            while(!(l&1)) l >>= 1;
            if(!pred(Op(sum, d[l])))
            {
                while(l<sz)
                {
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
