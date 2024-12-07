/**
 * @brief ST 表，支持所有“可重复贡献问题”。参见：https://oi-wiki.org/ds/sparse-table/
 * 
 * 构造（以在 a 上建立一个求 max 的 ST 表为例）：
 * @code{.cpp} sparse_table<int, [](int x,int y) { return max(x,y); }> st(a); @endcode
 * 
 * @tparam T 元素类型
 * @tparam Op 可重复贡献二元操作（max、min、gcd、lcm、bit_and、bit_or 等），建议使用 lambda 表达式
 */
template <typename T, auto Op>
class sparse_table
{
    vector<vector<T>> f;
public:
    /**
     * @param r 要建立 ST 表的序列
     */
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
    /**
     * @brief 查询 0-indexed 闭区间 [l,r] 的结果
     */
    T operator()(int l,int r)
    {
        if(l==r) return f[0][l];
        int p = bit_width(unsigned(l^r))-1;
        return Op(f[p][l], f[p][r]);
    }
};
