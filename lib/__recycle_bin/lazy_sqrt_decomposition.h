template <typename T, typename Lazy>
requires requires(T a, T b, Lazy c, Lazy d)
{
    {a+b} -> same_as<T>;
    {a+c} -> same_as<T>;
    c += d;
    {Lazy::e()} -> same_as<Lazy>;
}
class lazy_sqrt_decomposition
{
    size_t n, sz;
    vector<size_t> id;
    vector<T> data, block;
    vector<Lazy> lazy;
    void apply_node(size_t p, const Lazy& lz)
    {
        data[p] = data[p]+lz;
        block[id[p]] = block[id[p]]+lz;
    }
    void apply_block(size_t p, const Lazy& lz)
    {
        block[p] = block[p]+lz;
        lazy[p] += lz;
    }
public:
    lazy_sqrt_decomposition(ranges::range auto&& rg) : n(ranges::size(rg)), sz(sqrt(n)), id(n),
        data(ranges::begin(rg), ranges::end(rg)), block((n-1)/sz+1), lazy(block.size(), Lazy::e())
    {
        for(size_t i=0;i<n;i++) id[i] = i/sz;
        for(size_t i=0;i<n;i++) block[id[i]] = i%sz==0?data[i]:block[id[i]]+data[i];
    }
    lazy_sqrt_decomposition(size_t n, const T& init={}) : lazy_sqrt_decomposition(vector(n, init)) {}
    auto operator[](size_t p) const { return data[p]+lazy[id[p]]; }
    auto operator()(size_t l, size_t r) const
    {
        T res;
        if(id[l]==id[r])
        {
            for(size_t i=l;i<=r;i++) res = i==l?(*this)[l]:res+(*this)[i];
            return res;
        }
        else
        {
            if(l%sz==0) res = block[id[l]];
            else for(size_t i=l;i<sz*(id[l]+1);i++) res = i==l?(*this)[l]:res+(*this)[i];
            for(size_t i=id[l]+1;i<id[r];i++) res = res+block[i];
            if((r+1)%sz==0) res = res+block[id[r]];
            else for(size_t i=sz*id[r];i<=r;i++) res = res+(*this)[i];
        }
        return res;
    }
    void apply(size_t l, size_t r, const Lazy& lz)
    {
        if(id[l]==id[r])
        {
            for(size_t i=l;i<=r;i++) apply_node(i, lz);
            return;
        }
        if(l%sz==0) apply_block(id[l], lz);
        else for(size_t i=l;i<sz*(id[l]+1);i++) apply_node(i, lz);
        for(size_t i=id[l]+1;i<id[r];i++) apply_block(i, lz);
        if((r+1)%sz==0) apply_block(id[r], lz);
        else for(size_t i=sz*id[r];i<=r;i++) apply_node(i, lz);
    }
};
