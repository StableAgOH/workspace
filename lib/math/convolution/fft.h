class fft
{
    using T = complex<double>;
    inline static vector<T> r{1};
    static void dft(vector<T>& a)
    {
        int n = a.size();
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
    static void idft(vector<T>& a)
    {
        int n = a.size();
        for(int k=1;k<n;k<<=1)
        {
            for(int i=0;i<n;i+=k<<1)
            {
                for(int j=0;j<k;j++)
                {
                    auto u=a[i+j], v=a[i+j+k]*conj(r[k+j]);
                    a[i+j]=u+v, a[i+j+k]=u-v;
                }
            }
        }
        for(auto& x : a) x /= n;
    }
public:
    template <typename U>
    static auto convolve(const vector<U>& a, const vector<U>& b)
    {
        auto m = bit_ceil(a.size()+b.size()-1);
        if(r.size()<m)
        {
            auto old = r.size();
            r.resize(m);
            for(auto i=old;i<m;i<<=1)
            {
                T w=polar(1.0, numbers::pi/i), wk=1;
                for(size_t j=0;j<i;j++,wk*=w) r[i+j] = wk;
            }
        }
        vector<T> c(m);
        for(size_t i=0;i<a.size();i++) c[i].real(a[i]);
        for(size_t i=0;i<b.size();i++) c[i].imag(b[i]);
        dft(c);
        for(size_t i=0;i<m;i++) c[i] *= c[i];
        idft(c);
        vector<U> r(a.size()+b.size()-1);
        for(size_t i=0;i<r.size();i++) r[i] = round(c[i].imag()/2);
        return r;
    }
};
