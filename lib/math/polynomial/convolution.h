struct fft
{
    void operator()(valarray<complex<double>>& a, bool inv)
    {
        int n = a.size();
        valarray<int> pos(n);
        for(int i=0;i<n;i++)
        {
            pos[i] = pos[i>>1]>>1;
            if(i&1) pos[i] |= n>>1;
        }
        for(int i=0;i<n;i++) if(i<pos[i]) swap(a[i], a[pos[i]]);
        for(int i=1;i<n;i<<=1)
        {
            auto w = polar(1.0, (inv?-1:1)*numbers::pi/i);
            for(int j=0;j<n;j+=i<<1)
            {
                complex wk = 1.0;
                for(int k=0;k<i;k++)
                {
                    auto u=a[j+k], v=wk*a[j+k+i];
                    a[j+k] = u+v;
                    a[j+k+i] = u-v;
                    wk *= w;
                }
            }
        }
        if(inv) a /= n;
    }
};
struct fwt_and
{
    template <typename T>
    void operator()(valarray<T> a, bool inv)
    {
        int n = a.size();
        for(int len=2;len<=n;len<<=1)
        {
            int k = len>>1;
            for(int i=0;i<n;i+=len)
                for(int j=0;j<k;j++)
                    a[i+j+k] += a[i+j]*(inv?-1:1);
        }
    }
};
using fwt_or = fwt_and;
struct fwt_xor
{
    template <typename T>
    void operator()(valarray<T>& a, bool inv)
    {
        int n = a.size();
        for(int len=1;len<n;len<<=1)
        {
            for(int i=0;i<n;i+=2*len)
            {
                for(int j=0;j<len;j++)
                {
                    auto u=a[i+j], v=a[i+j+len];
                    a[i+j] = u+v;
                    a[i+j+len] = u-v;
                }
            }
        }
        if(inv) for(int i=0;i<n;i++) a[i] /= n;
    }
};
template <typename T, typename Conv=fft>
polynomial<T> convolution(const polynomial<T>& lhs, const polynomial<T>& rhs, Conv conv={})
{
    auto apply_convolution = [&](auto& p, auto& q)
    {
        conv(p, false);
        conv(q, false);
        p *= q;
        conv(p, true);
    };
    if constexpr(same_as<Conv, fft>)
    {
        int m = bit_ceil(unsigned(lhs.degree()+rhs.degree()+1));
        valarray<complex<double>> c1(m), c2(m);
        for(int i=0;i<=lhs.degree();i++) c1[i] = lhs[i];
        for(int i=0;i<=rhs.degree();i++) c2[i] = rhs[i];
        apply_convolution(c1, c2);
        polynomial<T> ret(lhs.degree()+rhs.degree());
        for(int i=0;i<=ret.degree();i++) ret[i] = round(c1[i].real());
        return ret;
    }
    else
    {
        int m = bit_ceil(unsigned(max(lhs.degree(), rhs.degree())+1));
        valarray<T> c1(m), c2(m);
        for(int i=0;i<=lhs.degree();i++) c1[i] = lhs[i];
        for(int i=0;i<=rhs.degree();i++) c2[i] = rhs[i];
        apply_convolution(c1, c2);
        return c1;
    }
}
