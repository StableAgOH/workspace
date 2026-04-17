template <typename T, auto Op>
requires convertible_to<invoke_result_t<decltype(Op), T, T>, T>
class disjoint_sparse_table
{
    vector<vector<T>> d;
public:
    explicit disjoint_sparse_table(ranges::range auto&& rg)
    {
        int n = ranges::size(rg);
        d.emplace_back(ranges::begin(rg), ranges::end(rg));
        for(int i=1;(1<<i)<n;i++)
        {
            d.emplace_back(n);
            for(int m=1<<i;m<n;m+=1<<(i+1))
            {
                d[i][m-1] = d[0][m-1];
                for(int j=m-2;j>=m-(1<<i);j--) d[i][j] = Op(d[0][j], d[i][j+1]);
                d[i][m] = d[0][m];
                for(int j=m+1;j<min(n, m+(1<<i));j++) d[i][j] = Op(d[i][j-1], d[0][j]);
            }
        }
    }
    T operator()(size_t l, size_t r) const
    {
        auto k = max(0, int(bit_width(l^r))-1);
        return Op(d[k][l], d[k][r]);
    }
};
