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
    sparse_table(ranges::range auto&& rg, function<T(T,T)> op) : op(op) { build(rg); }
    sparse_table(ranges::range auto&& rg, CR (*op)(CR,CR)) : op(op) { build(rg); }
    T operator()(int l,int32_t r)
    {
        if(l==r) return f[0][l];
        int p = bit_width(unsigned(l^r))-1;
        return op(f[p][l], f[p][r]);
    }
};
