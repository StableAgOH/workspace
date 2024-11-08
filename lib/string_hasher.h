class string_hasher
{
private:
    int mod;
    vector<ll> w, h;
public:
    string_hasher(string_view s, int p=23333, int mod=998244353) : mod(mod), w(1,1), h(1)
    {
        for(size_t i=1;i<=s.length();i++)
        {
            w.push_back(w[i-1]*p%mod);
            h.push_back((h[i-1]*p+s[i-1])%mod);
        }
    }
    auto operator()(int l,int r) { return (h[r]-h[l-1]*w[r-l+1]%mod+mod)%mod; }
};
