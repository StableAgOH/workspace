class ntt
{
    using T = mint998244353;
    inline static vector<T> r{1}, ir{1};
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
                    auto u=a[i+j], v=a[i+j+k]*ir[k+j];
                    a[i+j]=u+v, a[i+j+k]=u-v;
                }
            }
        }
        auto inv = ~T(n);
        for(auto& x : a) x *= inv;
    }
public:
    static auto convolve(const vector<T>& a, const vector<T>& b)
    {
        auto m = bit_ceil(a.size()+b.size()-1);
        if(r.size()<m)
        {
            auto old = r.size();
            r.resize(m), ir.resize(m);
            for(auto i=old;i<m;i<<=1)
            {
                T w=T(3).pow((T::mod()-1)/(i<<1)), iw=~w, wk=1, iwk=1;
                for(size_t j=0;j<i;j++,wk*=w,iwk*=iw) 
                {
                    r[i+j] = wk;
                    ir[i+j] = iwk;
                }
            }
        }
        vector<T> c1(m), c2(m);
        ranges::copy(a, c1.begin());
        ranges::copy(b, c2.begin());
        dft(c1), dft(c2);
        for(size_t i=0;i<m;i++) c1[i] *= c2[i];
        idft(c1);
        return c1;
    }
};
