template <typename T, auto Op>
requires convertible_to<invoke_result_t<decltype(Op), T, T>, T>
class sparse_table
{
public:
    sparse_table(span<T> s)
    {
        int n = s.size();
        data.emplace_back(s.begin(), s.end());
        for(int i=1;(1<<i)<n;i++)
        {
            data.emplace_back(n);
            for(int m=1<<i;m<n;m+=1<<(i+1))
            {
                data[i][m-1] = s[m-1];
                for(int j=m-2;j>=m-(1<<i);j--) data[i][j] = Op(s[j], data[i][j+1]);
                data[i][m] = s[m];
                for(int j=m+1;j<min(n,m+(1<<i));j++) data[i][j] = Op(data[i][j-1], s[j]);
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
