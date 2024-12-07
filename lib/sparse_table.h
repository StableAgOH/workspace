template <typename T, auto Op>
class sparse_table
{
    vector<vector<T>> f;
public:
    sparse_table(ranges::range auto&& r)
    {
        int n = ranges::size(r);
        f.emplace_back(ranges::begin(r), ranges::end(r));
        for(int i=1;(1<<i)<n;i++)
        {
            f.emplace_back(n);
            for(int j=1<<i;j<n;j+=1<<(i+1))
            {
                f[i][j-1] = f[0][j-1];
                for(int k=j-2;k>=j-(1<<i);k--) f[i][k] = Op(f[0][k], f[i][k+1]);
                f[i][j] = f[0][j];
                for(int k=j+1;k<min(n,j+(1<<i));k++) f[i][k] = Op(f[i][k-1], f[0][k]);
            }
        }
    }
    T operator()(int l,int r)
    {
        if(l==r) return f[0][l];
        int p = bit_width(unsigned(l^r))-1;
        return Op(f[p][l], f[p][r]);
    }
};
