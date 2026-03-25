template <typename T>
T crt(const vector<T>& a, const vector<T>& m)
{
    auto exgcd = [](auto&& self, T a, T b, T &x, T &y)
    {
        if(!b) return x=1, y=0, a;
        T d = self(self, b, a%b, y, x);
        y -= a/b*x;
        return d;
    };
    T ans=(a[0]%m[0]+m[0])%m[0], M=m[0];
    for(size_t i=1;i<a.size();i++)
    {
        T b=(a[i]-ans%m[i]+m[i])%m[i], x, y;
        T g = exgcd(exgcd, M, m[i], x, y);
        if(b%g) return -1;
        T mod = m[i]/g;
        x = __int128(x)*(b/g)%mod;
        ans += x*M;
        M *= mod;
        ans = (ans%M+M)%M;
    }
    return ans;
}
