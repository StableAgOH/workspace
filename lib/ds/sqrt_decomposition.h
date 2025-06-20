template <typename T, auto Op>
requires same_as<invoke_result_t<decltype(Op), T, T>, T>
class sqrt_decomposition
{
    size_t n, sz;
    vector<size_t> id;
    vector<T> data, block;
public:
    sqrt_decomposition(ranges::range auto&& rg) : n(ranges::size(rg)), sz(sqrt(n)), id(n),
        data(ranges::begin(rg), ranges::end(rg)), block((n-1)/sz+1)
    {
        for(size_t i=0; i<n; i++) id[i] = i/sz;
        for(size_t i=0; i<n; i++) block[id[i]] = i%sz==0?data[i]:Op(block[id[i]], data[i]);
    }
    sqrt_decomposition(size_t n, const T& init={}) : sqrt_decomposition(vector(n, init)) {}
    auto operator[](size_t p) const { return data[p]; }
    auto operator()(size_t l, size_t r) const
    {
        if(id[l]==id[r]) return reduce(data.begin()+l+1, data.begin()+r+1, data[l], Op);
        auto res = l%sz==0?block[id[l]]:reduce(data.begin()+l+1, data.begin()+sz*(id[l]+1), data[l], Op);
        res = reduce(block.begin()+id[l]+1, block.begin()+id[r], res, Op);
        return (r+1)%sz==0?Op(res, block[id[r]]):reduce(data.begin()+sz*id[r], data.begin()+r+1, res, Op);
    }
    void apply(size_t p, const T& x)
    {
        data[p] = Op(data[p], x);
        block[id[p]] = Op(block[id[p]], x);
    }
};
