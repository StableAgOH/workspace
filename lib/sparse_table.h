template <typename T>
class sparse_table
{
    using crfp = const T& (*)(const T&, const T&);
    using op_t = function<T(T,T)>;
    op_t op;
    vector<vector<T>> f;
public:
    template <ranges::range R, typename F>
    sparse_table(R&& rg, F&& op) : op(forward<F>(op))
    {
        f.emplace_back(ranges::begin(rg), ranges::end(rg));
        size_t n = f.front().size();
        for(size_t i=1;(1u<<i)<n;i++)
        {
            f.emplace_back(n);
            for(size_t j=1<<i;j<n;j+=1<<(i+1))
            {
                f[i][j-1] = f[0][j-1];
                for(size_t k=j-1;k-->j-(1<<i);) f[i][k] = this->op(f[0][k], f[i][k+1]);
                f[i][j] = f[0][j];
                for(size_t k=j+1;k<min(n,j+(1<<i));k++) f[i][k] = this->op(f[i][k-1], f[0][k]);
            }
        }
    }
    template <ranges::range R>
    sparse_table(R&& rg, crfp op) : sparse_table(forward<R>(rg), op_t(op)) {}
    T operator()(size_t l, size_t r) const
    {
        int p = max(0, (int)bit_width(l^r)-1); // In gcc 12, bit_width return decltype(l^r)
        return op(f[p][l], f[p][r]);
    }
};
template <ranges::range R, typename F> sparse_table(R,F) -> sparse_table<ranges::range_value_t<R>>;
