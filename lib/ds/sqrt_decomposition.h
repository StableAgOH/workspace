template <typename T, auto Op, auto InvOp>
class sqrt_decomposition
{
    static_assert(convertible_to<invoke_result_t<decltype(Op), T, T>, T>);
    static_assert(convertible_to<invoke_result_t<decltype(InvOp), T, T>, T>);
    size_t n, bs;
    vector<size_t> id;
    vector<T> data, block;
public:
    sqrt_decomposition(ranges::range auto&& rg) :
        n(ranges::size(rg)), bs(sqrt(n)), id(n), data(ranges::begin(rg), ranges::end(rg))
    {
        for(size_t i=0;i<n;i++) id[i] = i/bs;
        block.resize(id[n-1]+1);
        for(size_t i=0;i<n;i++) block[id[i]] = i%bs==0?data[i]:Op(block[id[i]], data[i]);
    }
    sqrt_decomposition(size_t n, const T& init={}) : sqrt_decomposition(vector(n, init)) {}
    void set(size_t p, const T& x)
    {
        block[id[p]] = InvOp(block[id[p]], data[p]);
        data[p] = x;
        block[id[p]] = Op(block[id[p]], data[p]);
    }
    void transform(size_t p, auto&& f) { set(p, f((*this)[p])); }
    auto operator[](size_t p) const { return data[p]; }
    auto operator()(size_t l, size_t r) const
    {
        if(id[l]==id[r]) return reduce(data.begin()+l+1, data.begin()+r+1, data[l], Op);
        auto res = reduce(data.begin()+l+1, data.begin()+bs*(id[l]+1), data[l], Op);
        res = reduce(data.begin()+bs*id[r], data.begin()+r+1, res, Op);
        return reduce(block.begin()+id[l]+1, block.begin()+id[r], res, Op);
    }
};
