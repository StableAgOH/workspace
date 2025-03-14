struct fft
{
    template <typename T>
    using vtype = valarray<complex<double>>;
    static auto vd(size_t ld, size_t rd) { return ld+rd; }
    void operator()(valarray<complex<double>>& a, int f)
    {
        int n = a.size();
        valarray<int> pos(n);
        for(int i=0;i<n;i++) pos[i] = pos[i>>1]>>1|(i&1?n>>1:0);
        for(int i=0;i<n;i++) if(i<pos[i]) swap(a[i], a[pos[i]]);
        for(int i=1;i<n;i<<=1)
        {
            auto w = polar(1.0, f*numbers::pi/i);
            for(int j=0;j<n;j+=i<<1)
            {
                complex wk = 1.0;
                for(int k=0;k<i;k++,wk*=w)
                {
                    auto u=a[j+k], v=a[i+j+k]*wk;
                    a[j+k] = u+v, a[i+j+k] = u-v;
                }
            }
        }
        if(f==-1) a /= n;
    }
};
template <auto F>
struct fwt
{
    template <typename T>
    using vtype = valarray<T>;
    static auto vd(size_t ld, size_t rd) { return max(ld, rd); }
    template <typename T>
    void operator()(valarray<T>& a, int f)
    {
        int n = a.size();
        for(int k=1;k<n;k<<=1)
            for(int i=0;i<n;i+=k<<1)
                for(int j=0;j<k;j++)
                    F(a[i+j], a[i+j+k], f);
    }
};
using fwt_and = fwt<[](auto& u, auto& v, int f) { u += f*v; }>;
using fwt_or = fwt<[](auto& u, auto& v, int f) { v += f*u; }>;
using fwt_xor = fwt<[](auto& u, auto& v, int f) {
    tie(u,v) = pair(u+v, u-v);
    if(f==-1) u/=2, v/=2;
}>;
template <typename T, typename Conv=fft>
polynomial<T> convolution(const polynomial<T>& lhs, const polynomial<T>& rhs, Conv conv={})
{
    int m = bit_ceil(Conv::vd(lhs.degree(), rhs.degree())+1);
    typename Conv::vtype<T> c1(m), c2(m);
    for(size_t i=0;i<=lhs.degree();i++) c1[i] = lhs[i];
    for(size_t i=0;i<=rhs.degree();i++) c2[i] = rhs[i];
    conv(c1, 1), conv(c2, 1), c1 *= c2, conv(c1, -1);
    if constexpr(same_as<Conv, fft>)
    {
        polynomial<T> ret(lhs.degree()+rhs.degree());
        for(size_t i=0;i<=ret.degree();i++) ret[i] = round(c1[i].real());
        return ret;
    }
    else return c1;
}
