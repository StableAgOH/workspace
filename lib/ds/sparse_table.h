template <typename T, auto Op>
requires requires(T x, T y) { { Op(x, y) } -> convertible_to<T>; }
class sparse_table
{
public:
    sparse_table(ranges::range auto&& rg)
    {
        int n = ranges::size(rg);
        data.emplace_back(ranges::begin(rg), ranges::end(rg));
        for(int i=1;(1<<i)<n;i++)
        {
            data.emplace_back(n);
            for(int m=1<<i;m<n;m+=1<<(i+1))
            {
                data[i][m-1] = data[0][m-1];
                for(int j=m-2;j>=m-(1<<i);j--)
                    data[i][j] = Op(data[0][j], data[i][j+1]);
                data[i][m] = data[0][m];
                for(int j=m+1;j<min(n, m+(1<<i));j++)
                    data[i][j] = Op(data[i][j-1], data[0][j]);
            }
        }
    }
    auto operator()(int l, int r) const
    {
        int p = max<int>(0, bit_width(unsigned(l^r))-1);
        return Op(data[p][l], data[p][r]);
    }
private:
    vector<vector<T>> data;
};
