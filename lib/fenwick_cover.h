template <typename T, typename O>
class fenwick_cover
{
    static constexpr auto lowbit(auto x) { return x&-x; }
    int n;
    vector<T> a, c;
public:
    fenwick_cover(int n) : n(n), a(n), c(n+1) {}
    fenwick_cover(int n, const T& x) : n(n), a(n,x), c(n+1,x) {}
    fenwick_cover(const vector<T>& v) : fenwick_cover(v.size())
    {
        ranges::copy(v, a.begin());
        for(int i=1;i<=n;i++)
        {
            c[i] = O()(c[i], a[i-1]);
            int j = i+lowbit(i);
            if(j<=n) c[j] = O()(c[j], c[i]);
        }
    }
    int size() { return n; }
    void update(int p, const T& x)
    {
        a[p] = x;
        for(int i=p+1;i<=n;i+=lowbit(i))
        {
            c[i] = a[i-1];
            for(int j=1;j<lowbit(i);j<<=1) c[i] = O()(c[i], c[i-j]);
        }
    }
    auto operator()(int l) const { return operator()(l,l); }
    auto operator()(int l, int r) const
    {
        l++;
        r++;
        T ans = a[r-1];
        while(r>=l)
        {
            ans = O()(ans, a[r-1]);
            r--;
            for(;r-lowbit(r)>=l;r-=lowbit(r)) ans = O()(ans, c[r]);
        }
        return ans;
    }
};
