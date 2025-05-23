template <typename T>
requires requires(T a, T b) { {a+b} -> same_as<T>; }
class sqrt_decomposition
{
    size_t n, sz;
    vector<size_t> id;
    vector<T> data, block;
public:
    sqrt_decomposition(ranges::range auto&& rg) : n(rg.size()), sz(sqrt(n)), id(n),
        data(ranges::begin(rg), ranges::end(rg)), block((n-1)/sz+1)
    {
        for(size_t i=0;i<n;i++) id[i] = i/sz;
        for(size_t i=0;i<n;i++) block[id[i]] = i%sz==0?data[i]:block[id[i]]+data[i];
    }
    sqrt_decomposition(size_t n, const T& init={}) : sqrt_decomposition(vector(n, init)) {}
    auto operator[](size_t p) const { return data[p]; }
    auto operator()(size_t l, size_t r) const
    {
        if(id[l]==id[r]) return reduce(data.begin()+l+1, data.begin()+r+1, data[l]);
        auto res = l%sz==0?block[id[l]]:reduce(data.begin()+l+1, data.begin()+sz*(id[l]+1), data[l]);
        res = reduce(block.begin()+id[l]+1, block.begin()+id[r], res);
        return reduce(data.begin()+sz*id[r], data.begin()+r+1, res);
    }
    void set(size_t p, const T& x)
    {
        auto q = id[p];
        if constexpr(requires(T a, T b) { {a-b} -> same_as<T>; })
        {
            block[q] = block[q]-data[p]+x;
            data[p] = x;
        }
        else
        {
            data[p] = x;
            for(auto i=q*sz;i<min(n, (q+1)*sz);i++) block[q] = i%sz==0?data[i]:block[q]+data[i];
        }
    }
    void set(size_t p, const T& x, auto&& f)
    {
        static_assert(convertible_to<invoke_result_t<decltype(f), T>, T>);
        data[p] = x;
        block[id[p]] = f(block[id[p]]);
    }
};
