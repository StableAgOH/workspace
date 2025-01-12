template <typename T, T E1, typename M, M E2>
requires requires(T x, M f)
{
    requires default_initializable<M>; // identity
    { f(x) } -> same_as<T>; // mapping
    { f*f } -> same_as<M>; // composition
}
class lazy_segtree
{
    using crfp = const T& (*)(const T&, const T&);
    using op_t = function<T(T,T)>;
    static constexpr auto lowbit(auto x) { return x&-x; }
    op_t op;
    size_t n, sz, lg;
    vector<T> data;
    vector<M> lazy;
    void update(size_t p) { data[p] = op(data[p<<1], data[p<<1|1]); }
    void all_apply(size_t p, const M& f)
    {
        data[p] = f(data[p]);
        if(p<sz) lazy[p] = f*lazy[p];
    }
    void push(size_t p)
    {
        all_apply(p<<1, lazy[p]);
        all_apply(p<<1|1, lazy[p]);
        lazy[p] = {};
    }
public:
    template <typename F>
    requires same_as<invoke_result_t<F,T,T>, T>
    lazy_segtree(ranges::range auto&& rg, F&& op) : op(forward<F>(op))
    {
        n = ranges::size(rg);
        sz = bit_ceil(n);
        lg = countr_zero(sz);
        data.resize(2*sz, E1);
        lazy.resize(sz);
        ranges::copy(rg, data.begin()+sz);
        for(size_t i=sz-1;i>=1;i--) update(i);
    }
    template <ranges::range R>
    lazy_segtree(R&& rg, crfp op) : lazy_segtree(forward<R>(rg), op_t(op)) {}
    template <typename F>
    requires same_as<invoke_result_t<F,T,T>, T>
    lazy_segtree(size_t n, F&& op) : lazy_segtree(vector(n, E1), forward<F>(op)) {}
    lazy_segtree(size_t n, crfp op) : lazy_segtree(vector(n, E1), op_t(op)) {}
    auto operator()() const { return data[1]; }
    auto operator()(size_t p) const
    {
        p += sz;
        for(size_t i=lg;i>=1;i--) push(p>>i);
        return data[p];
    }
    auto operator()(size_t l, size_t r)
    {
        l += sz;
        r += sz+1;
        for(size_t i=lg;i>=1;i--)
        {
            if(((l>>i)<<i)!=l) push(l>>i);
            if(((r>>i)<<i)!=r) push((r-1)>>i);
        }
        auto resl=data[0], resr=data[0];
        while(l<r)
        {
            if(l&1) resl = op(resl, data[l++]);
            if(r&1) resr = op(data[--r], resr);
            l >>= 1;
            r >>= 1;
        }
        return op(resl, resr);
    }
    void set(size_t p, const T& x)
    {
        p += sz;
        for(size_t i=lg;i>=1;i--) push(p>>i);
        data[p] = x;
        for(size_t i=1;i<=lg;i++) update(p>>i);
    }
    void apply(size_t p, const M& f)
    {
        p += sz;
        for(size_t i=lg;i>=1;i--) push(p>>i);
        data[p] = f(data[p]);
        for(size_t i=1;i<=lg;i++) update(p>>i);
    }
    void apply(size_t l, size_t r, const M& f)
    {
        l += sz;
        r += sz+1;
        for(size_t i=lg;i>=1;i--)
        {
            if(((l>>i)<<i)!=l) push(l>>i);
            if(((r>>i)<<i)!=r) push((r-1)>>i);
        }
        [&](size_t l, size_t r)
        {
            while(l<r)
            {
                if(l&1) all_apply(l++, f);
                if(r&1) all_apply(--r, f);
                l >>= 1;
                r >>= 1;
            }
        }(l, r);
        for(size_t i=1;i<=lg;i++)
        {
            if(((l>>i)<<i)!=l) update(l>>i);
            if(((r>>i)<<i)!=r) update((r-1)>>i);
        }
    }
    template <predicate<T> F>
    size_t min_left(size_t r, F&& pred) const
    {
        if(!r) return 0;
        r += sz;
        for(size_t i=lg;i>=1;i--) push((r-1)>>i);
        T sum = data[0];
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
                    if(pred(op(data[r], sum)))
                    {
                        sum = op(data[r], sum);
                        r--;
                    }
                }
                return r+1-sz;
            }
            sum = op(data[r], sum);
        }
        while(lowbit(r)!=r);
        return 0;
    }
    template <predicate<T> F>
    size_t max_right(size_t l, F&& pred) const
    {
        if(l==n) return n;
        l += sz;
        for(size_t i=lg;i>=1;i--) push(l>>i);
        T sum = data[0];
        do
        {
            while(l%2==0) l >>= 1;
            if(!pred(op(sum, data[l])))
            {
                while(l<sz)
                {
                    push(l);
                    l <<= 1;
                    if(pred(op(sum, data[l])))
                    {
                        sum = op(sum, data[l]);
                        l++;
                    }
                }
                return l-sz;
            }
            sum = op(sum, data[l]);
            l++;
        }
        while(lowbit(l)!=l);
        return n;
    }
};
