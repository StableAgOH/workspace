template <typename T, auto F>
struct fft_base
{
    using value_type = T;
    static inline vector<T> r1{1}, r2{1};
    static auto len(size_t x, size_t y) { return x+y-1; }
    void operator()(vector<T>& a, int f)
    {
        int n = a.size();
        auto& r = f==1?r1:r2;
        if((int)r.size()<n)
        {
            int old = r.size();
            r.resize(n);
            for(int i=old;i<n;i<<=1)
            {
                T w=F(f, i), wk=1;
                for(int j=0;j<i;j++,wk*=w) r[i+j] = wk;
            }
        }
        if(f==1)
        {
            for(int k=n>>1;k>=1;k>>=1)
            {
                for(int i=0;i<n;i+=k<<1)
                {
                    for(int j=0;j<k;j++)
                    {
                        auto u=a[i+j], v=a[i+j+k];
                        a[i+j]=u+v, a[i+j+k]=(u-v)*r[k+j];
                    }
                }
            }
        }
        else
        {
            for(int k=1;k<n;k<<=1)
            {
                for(int i=0;i<n;i+=k<<1)
                {
                    for(int j=0;j<k;j++)
                    {
                        auto u=a[i+j], v=a[i+j+k]*r[k+j];
                        a[i+j]=u+v, a[i+j+k]=u-v;
                    }
                }
            }
            auto inv = T(1)/T(n);
            for(int i=0;i<n;i++) a[i] *= inv;
        }
    }
};
using fft = fft_base<complex<double>, [](int f, int k) { return polar(1.0, f*numbers::pi/k); }>;
using ntt = fft_base<mint, [](int f, int k) { return mint(3).pow(f*(mint::mod()-1)/(k<<1)); }>;
template <auto F>
struct fwt_base
{
    static auto len(size_t x, size_t y) { return max(x, y); }
    template <typename T>
    void operator()(vector<T>& a, int f)
    {
        int n = a.size();
        for(int k=1;k<n;k<<=1)
            for(int i=0;i<n;i+=k<<1)
                for(int j=0;j<k;j++)
                    F(a[i+j], a[i+j+k], f);
    }
};
using fwt_and = fwt_base<[](auto& u, auto& v, int f) { u += f*v; }>;
using fwt_or = fwt_base<[](auto& u, auto& v, int f) { v += f*u; }>;
using fwt_xor = fwt_base<[](auto& u, auto& v, int f) {
    tie(u, v) = pair(u+v, u-v);
    if(f==-1) u/=2, v/=2;
}>;
template <typename T, typename Conv>
auto convolve(const vector<T>& a, const vector<T>& b, Conv conv)
{
    auto m = bit_ceil(Conv::len(a.size(), b.size()));
    using U = conditional_t<
        requires { typename Conv::value_type; },
        typename Conv::value_type,
        T
    >;
    vector<U> c1(m), c2(m);
    ranges::copy(a, c1.begin());
    ranges::copy(b, c2.begin());
    conv(c1, 1);
    conv(c2, 1);
    for(size_t i=0;i<m;i++) c1[i] *= c2[i];
    conv(c1, -1);
    if constexpr(same_as<Conv, fft>)
    {
        vector<T> ret(a.size()+b.size()-1);
        for(size_t i=0;i<ret.size();i++) ret[i] = round(c1[i].real());
        return ret;
    }
    else return c1;
}
