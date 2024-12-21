template <typename T>
class sparse_table
{
    using CR = const T&;
    function<T(T,T)> op;
    vector<vector<T>> f;
    void build(ranges::range auto&& rg)
    {
        int n = ranges::size(rg);
        f.emplace_back(ranges::begin(rg), ranges::end(rg));
        for(int i=1;(1<<i)<n;i++)
        {
            f.emplace_back(n);
            for(int j=1<<i;j<n;j+=1<<(i+1))
            {
                f[i][j-1] = f[0][j-1];
                for(int k=j-2;k>=j-(1<<i);k--) f[i][k] = op(f[0][k], f[i][k+1]);
                f[i][j] = f[0][j];
                for(int k=j+1;k<min(n,j+(1<<i));k++) f[i][k] = op(f[i][k-1], f[0][k]);
            }
        }
    }
public:
    sparse_table(ranges::range auto&& rg, CR (*op)(CR, CR)) : op(op) { build(rg); }
    template <typename F> sparse_table(ranges::range auto&& rg, F&& op) : op(op) { build(rg); }
    T operator()(int l, int r) const
    {
        if(l==r) return f[0][l];
        int p = bit_width(unsigned(l^r))-1;
        return op(f[p][l], f[p][r]);
    }
};
template <ranges::range R, typename T=ranges::range_value_t<R>>
sparse_table(R, const T& (*op)(const T&, const T&)) -> sparse_table<T>;
template <ranges::range R, typename T=ranges::range_value_t<R>, typename F>
sparse_table(R, F) -> sparse_table<T>;
