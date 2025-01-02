template <int BASE=31, int MOD=998244353>
class string_hasher
{
    int n;
    vector<int> p, h;
public:
    string_hasher(const string& s) : n(s.length()), p(n+1, 1), h(n+1)
    {
        for(int i=1;i<=n;i++)
        {
            p[i] = ll(p[i-1])*BASE%MOD;
            h[i] = (ll(h[i-1])*BASE+s[i-1])%MOD;
        }
    }
    operator int() const { return (*this)(0, n-1); }
    auto operator()(int l, int r) const { return (h[r+1]-h[l]*p[r-l+1]%MOD+MOD)%MOD; }
    auto size() const { return n; }
};
