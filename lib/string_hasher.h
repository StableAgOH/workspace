class string_hasher
{
private:
    int mod;
    vector<ll> ppow, hpre;
public:
    string_hasher(const string& s, int p=114514, int mod=998244353) : mod(mod)
    {
        ppow.push_back(1);
        hpre.push_back(0);
        for(size_t i=1;i<=s.length();i++)
        {
            ppow.push_back(ppow[i-1]*p%mod);
            hpre.push_back(hpre[i-1]*p%mod+s[i-1]%mod);
        }
    }
    int get(int l,int r)
    {
        assert(l<=r);
        return (hpre[r]-hpre[l-1]*ppow[r-l+1]%mod+mod)%mod;
    }
};
