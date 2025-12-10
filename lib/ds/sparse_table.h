template <typename T, auto Op>
requires convertible_to<invoke_result_t<decltype(Op), T, T>, T>
class sparse_table
{
    vector<vector<T>> data;
public:
    explicit sparse_table(ranges::range auto&& rg)
    {
        int n = ranges::size(rg);
        data.emplace_back(ranges::begin(rg), ranges::end(rg));
        for(int i=1;(1<<i)<n;i++)
        {
            data.emplace_back(n-(1<<i)+1);
            for(int j=0;j+(1<<i)-1<n;j++)
                data[i][j] = Op(data[i-1][j], data[i-1][j+(1<<(i-1))]);
        }
    }
    auto operator()(size_t l, size_t r) const
    {
        auto k = bit_width(r-l+1)-1;
        return Op(data[k][l], data[k][r-(1<<k)+1]);
    }
};
