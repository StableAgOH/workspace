template <auto F>
class fwt_base
{
    template <typename T>
    static void transform(vector<T>& a, int f)
    {
        int n = a.size();
        for(int k=1;k<n;k<<=1)
            for(int i=0;i<n;i+=k<<1)
                for(int j=0;j<k;j++)
                    F(a[i+j], a[i+j+k], f);
    }
public:
    template <typename T>
    static auto convolve(vector<T> a, vector<T> b)
    {
        auto m = max(a.size(), b.size());
        a.resize(m), b.resize(m);
        transform(a, 1);
        transform(b, 1);
        for(size_t i=0;i<m;i++) a[i] *= b[i];
        transform(a, -1);
        return a;
    }
};
using fwt_and = fwt_base<[](auto& u, auto& v, int f) { u += f*v; }>;
using fwt_or = fwt_base<[](auto& u, auto& v, int f) { v += f*u; }>;
using fwt_xor = fwt_base<[](auto& u, auto& v, int f) {
    tie(u, v) = pair(u+v, u-v);
    if(f==-1) u/=2, v/=2;
}>;
