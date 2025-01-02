template <int BASE, int MOD>
struct string_hasher
{
    static constexpr int base=BASE, mod=MOD;
    int n;
    vector<int> p, h;
    string_hasher(const string& s) : n(s.length()), p(n+1, 1), h(n+1)
    {
        for(int i=1;i<=n;i++)
        {
            p[i] = ll(p[i-1])*base%mod;
            h[i] = (ll(h[i-1])*base+s[i-1])%mod;
        }
    }
    operator int() const { return h.back(); }
    int operator()(int l, int r) const { return (h[r+1]-ll(h[l])*p[r-l+1]%mod+mod)%mod; }
    auto size() const { return n; }
};
using preset_string_hasher1 = string_hasher<131, 998244353>;
using preset_string_hasher2 = string_hasher<131, 1000000007>;
using preset_string_hasher3 = string_hasher<131, 1000000009>;
