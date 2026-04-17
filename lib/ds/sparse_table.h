template <typename T, auto Op>
requires convertible_to<invoke_result_t<decltype(Op), T, T>, T>
class sparse_table
{
    vector<vector<T>> d;
public:
    explicit sparse_table(ranges::range auto&& rg)
    {
        int n = ranges::size(rg);
        d.emplace_back(ranges::begin(rg), ranges::end(rg));
        for(int i=1;(1<<i)<n;i++)
        {
            d.emplace_back(n-(1<<i)+1);
            for(int j=0;j+(1<<i)-1<n;j++)
                d[i][j] = Op(d[i-1][j], d[i-1][j+(1<<(i-1))]);
        }
    }
    T operator()(size_t l, size_t r) const
    {
        auto k = bit_width(r-l+1)-1;
        return Op(d[k][l], d[k][r-(1<<k)+1]);
    }
};
