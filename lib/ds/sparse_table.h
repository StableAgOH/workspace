template <typename T, auto Op>
requires same_as<invoke_result_t<decltype(Op), T, T>, T>
class sparse_table
{
    vector<vector<T>> data;
public:
    sparse_table(ranges::range auto&& rg)
    {
        int n = ranges::size(rg);
        data.emplace_back(ranges::begin(rg), ranges::end(rg));
        for(int i=1; (1<<i)<n; i++)
        {
            data.emplace_back(n);
            for(int m=1<<i; m<n; m+=1<<(i+1))
            {
                data[i][m-1] = data[0][m-1];
                for(int j=m-2; j>=m-(1<<i); j--) data[i][j] = Op(data[0][j], data[i][j+1]);
                data[i][m] = data[0][m];
                for(int j=m+1; j<min(n, m+(1<<i)); j++) data[i][j] = Op(data[i][j-1], data[0][j]);
            }
        }
    }
    auto operator()(size_t l, size_t r) const
    {
        int p = max(0, (int)bit_width(l^r)-1);
        return Op(data[p][l], data[p][r]);
    }
};
