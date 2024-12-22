template <typename T>
class sparse_table
{
    using op_t = function<T(T,T)>;
    using minmaxfp = const T& (*)(const T&, const T&);
    op_t op;
    vector<vector<T>> f;
public:
    template <typename F>
    sparse_table(ranges::range auto&& rg, F&& op) : op(forward<op_t>(op))
    {
        f.emplace_back(ranges::begin(rg), ranges::end(rg));
        int n = f.front().size();
        for(int i=1;(1<<i)<n;i++)
        {
            f.emplace_back(n);
            for(int j=1<<i;j<n;j+=1<<(i+1))
            {
                f[i][j-1] = f[0][j-1];
                for(int k=j-2;k>=j-(1<<i);k--) f[i][k] = this->op(f[0][k], f[i][k+1]);
                f[i][j] = f[0][j];
                for(int k=j+1;k<min(n,j+(1<<i));k++) f[i][k] = this->op(f[i][k-1], f[0][k]);
            }
        }
    }
    template <ranges::range R>
    sparse_table(R&& rg, minmaxfp op) : sparse_table(forward<R>(rg), op_t(op)) {}
    T operator()(int l, int r) const
    {
        if(l==r) return f[0][l];
        int p = bit_width(unsigned(l^r))-1;
        return op(f[p][l], f[p][r]);
    }
};
template <ranges::range R, typename F> sparse_table(R,F) -> sparse_table<ranges::range_value_t<R>>;
