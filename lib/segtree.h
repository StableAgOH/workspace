template <typename T>
class segtree
{
    using crfp = const T& (*)(const T&, const T&);
    using op_t = function<T(T,T)>;
    static constexpr auto lowbit(auto x) { return x&-x; }
    op_t op;
    size_t n, sz;
    vector<T> data; // data[0] is e, data[1] is the root
    void update(size_t p) { data[p] = op(data[p<<1], data[p<<1|1]); }
public:
    segtree() = default;
    template <typename F>
    requires same_as<invoke_result_t<F,T,T>, T>
    segtree(ranges::range auto&& rg, F&& op, const T& e={}) : op(forward<F>(op))
    {
        n = ranges::size(rg);
        sz = bit_ceil(n);
        data.resize(2*sz, e);
        ranges::copy(rg, data.begin()+sz);
        for(size_t i=sz-1;i>=1;i--) update(i);
    }
    template <ranges::range R>
    segtree(R&& rg, crfp op, const T& e={}) : segtree(forward<R>(rg), op_t(op), e) {}
    template <typename F>
    requires same_as<invoke_result_t<F,T,T>, T>
    segtree(size_t n, F&& op, const T& e={}) : segtree(vector(n,e), forward<F>(op), e) {}
    segtree(size_t n, crfp op, const T& e={}) : segtree(vector(n,e), op_t(op), e) {}
    auto operator()() const { return data[1]; }
    auto operator()(size_t p) const { return data[p+sz]; }
    auto operator()(size_t l, size_t r) const
    {
        auto resl=data[0], resr=data[0];
        for(l+=sz,r+=sz+1;l<r;l>>=1,r>>=1)
        {
            if(l&1) resl = op(resl, data[l++]);
            if(r&1) resr = op(data[--r], resr);
        }
        return op(resl, resr);
    }
    void set(size_t p, const T& x) { for(data[p+=sz]=x;p>1;p>>=1) update(p>>1); }
    template <predicate<T> F>
    size_t min_left(size_t r, F&& f) const
    {
        if(!r) return 0;
        r += sz;
        T sum = data[0];
        do
        {
            r--;
            while(r>1&&(r&1)) r >>= 1;
            if(!f(op(data[r], sum)))
            {
                while(r<sz)
                {
                    r = r<<1|1;
                    if(f(op(data[r], sum)))
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
    size_t max_right(size_t l, F&& f) const
    {
        if(l==n) return n;
        l += sz;
        T sum = data[0];
        do
        {
            while(l%2==0) l >>= 1;
            if(!f(op(sum, data[l])))
            {
                while(l<sz)
                {
                    l <<= 1;
                    if(f(op(sum, data[l])))
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
template <ranges::range R, typename F> segtree(R,F) -> segtree<ranges::range_value_t<R>>;
