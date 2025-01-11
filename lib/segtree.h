template <typename T>
class segtree
{
    using crfp = const T& (*)(const T&, const T&);
    using op_t = function<T(T,T)>;
    size_t n, sz;
    vector<T> data; // data[0] is e, data[1] is the root
    op_t op;
    void update(size_t p) { data[p] = op(data[p<<1], data[p<<1|1]); }
public:
    segtree() = default;
    template <ranges::range R, typename F>
    segtree(R&& rg, F&& op, const T& e) :
        n(ranges::size(rg)), sz(bit_ceil(n)), data(2*sz, e), op(forward<F>(op))
    {
        ranges::copy(rg, data.begin()+sz);
        for(size_t i=sz-1;i>=1;i--) update(i);
    }
    template <ranges::range R>
    segtree(R&& rg, crfp op, const T& e) : segtree(forward<R>(rg), op_t(op), e) {}
    template <typename F>
    segtree(size_t n, F&& op, const T& e) : segtree(vector(n,e), forward<F>(op), e) {}
    segtree(size_t n, crfp op, const T& e) : segtree(vector(n,e), op_t(op), e) {}
    void set(size_t p, const T& x) { for(data[p+=sz]=x;p>1;p>>=1) update(p>>1); }
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
};
