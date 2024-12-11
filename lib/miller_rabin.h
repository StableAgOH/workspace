ll qpow(__int128 a,ll k,ll p)
{
    ll res = 1;
    for(;k;k>>=1,a=a*a%p) if(k&1) res=res*a%p;
    return res;
}
bool miller_rabin(ll x)
{
    if(x<3||x%2==0) return x==2;
    auto t = countr_zero((unsigned)x-1);
    auto u = (x-1)>>t;
    for(auto a : {2, 325, 9375, 28178, 450775, 9780504, 1795265022})
    {
        __int128 v = qpow(a, u, x);
        if(v<=1) continue;
        for(int s=0;s<t;s++)
        {
            if(v==x-1) goto nxt;
            v = v*v%x;
        }
        return false;
    nxt:;
    }
    return true;
}
