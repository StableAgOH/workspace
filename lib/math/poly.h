template <int P> struct proth;
template <> struct proth<998244353> { static constexpr int G = 3; };
template <> struct proth<1004535809> { static constexpr int G = 3; };
template <> struct proth<469762049> { static constexpr int G = 3; };
template <typename T=static_mint<998244353>>
class poly : public vector<T>
{
    static inline const auto P = T::mod();
    static constexpr T G=proth<P>::G, I2=T(2).inv();
    static void ntt(vector<T>& a, int f)
    {
        int n = a.size();
        for(int i=1,j=0;i<n;i++)
        {
            int k = n>>1;
            for(;j&k;k>>=1) j ^= k;
            if(i<(j^=k)) swap(a[i], a[j]);
        }
        for(int k=1;k<n;k<<=1)
        {
            auto wn = G.pow((P-1)/(k<<1)*f);
            for(int i=0;i<n;i+=k<<1)
            {
                T w = 1;
                for(int j=0;j<k;j++,w*=wn)
                {
                    auto u=a[i+j], v=a[i+j+k]*w;
                    a[i+j]=u+v, a[i+j+k]=u-v;
                }
            }
        }
        if(f==-1)
        {
            auto in = T(n).inv();
            for(auto& x : a) x *= in;
        }
    }
    static poly simple_conv(const poly& a, const poly& b)
    {
        if(a.empty()||b.empty()) return {};
        poly c(a.size()+b.size()-1);
        for(size_t i=0;i<a.size();i++)
            for(size_t j=0;j<b.size();j++)
                c[i+j] += a[i]*b[j];
        return c;
    }
public:
    using vector<T>::vector;
    friend auto operator+(poly a, const poly& b)
    {
        a.resize(max(a.size(), b.size()));
        for(size_t i=0;i<b.size();i++) a[i] += b[i];
        return a;
    }
    friend auto operator-(poly a, const poly& b)
    {
        a.resize(max(a.size(), b.size()));
        for(size_t i=0;i<b.size();i++) a[i] -= b[i];
        return a;
    }
    friend poly operator*(poly a, T x)
    {
        for(size_t i=0;i<a.size();i++) a[i] *= x;
        return a;
    }
    friend poly operator*(poly a, poly b) requires requires { proth<P>::G; }
    {
        if(min(a.size(), b.size())<64) return simple_conv(a, b);
        auto m=a.size()+b.size()-1, n=bit_ceil(m);
        a.resize(n), b.resize(n);
        ntt(a, 1); ntt(b, 1);
        for(size_t i=0;i<n;i++) a[i] *= b[i];
        ntt(a, -1); a.resize(m);
        return a;
    }
    friend poly operator*(poly a, poly b) requires (!requires { proth<P>::G; })
    {
        if(min(a.size(), b.size())<64) return simple_conv(a, b);
        static constexpr int P1=998244353, P2=1004535809, P3=469762049;
        using M1 = static_mint<P1>;
        using M2 = static_mint<P2>;
        using M3 = static_mint<P3>;
        static constexpr static_mint<P2> i12 = M2(P1).inv();
        static constexpr static_mint<P3> i13=M3(P1).inv(), i23=M3(P2).inv();
        poly<M1> a1(a.size()), b1(b.size());
        poly<M2> a2(a.size()), b2(b.size());
        poly<M3> a3(a.size()), b3(b.size());
        for(size_t i=0;i<a.size();i++) a1[i]=int(a[i]), a2[i]=int(a[i]), a3[i]=int(a[i]);
        for(size_t i=0;i<b.size();i++) b1[i]=int(b[i]), b2[i]=int(b[i]), b3[i]=int(b[i]);
        a1=a1*b1, a2=a2*b2, a3=a3*b3;
        poly res(a1.size());
        T m1=P1, m12=m1*P2;
        for(size_t i=0;i<res.size();i++)
        {
            int v1=int(a1[i]), v2=int((a2[i]-v1)*i12), v3=int(((a3[i]-v1)*i13-v2)*i23);
            res[i] = T(v1)+T(v2)*m1+T(v3)*m12;
        }
        return res;
    }

    auto cut(this auto self, int n) { self.resize(n); return self; }
    poly deriv()
    {
        if(this->empty()) return {};
        poly res(this->size()-1);
        for(size_t i=1;i<this->size();i++) res[i-1] = (*this)[i]*i;
        return res;
    }
    poly integ()
    {
        if(this->empty()) return {};
        poly res(this->size()+1);
        for(size_t i=0;i<this->size();i++) res[i+1] = (*this)[i]/(i+1);
        return res;
    }
    poly inv(size_t n)
    {
        if(n==1) return {this->front().inv()};
        auto b = inv((n+1)/2);
        return (b+b-cut(n)*b*b).cut(n);
    }
    poly sqrt(size_t n)
    {
        if(n==1) return {1};
        auto b = sqrt((n+1)/2);
        return ((b+cut(n)*b.inv(n))*I2).cut(n);
    }
    auto ln(size_t n)
    {
        return (deriv()*inv(n)).integ().cut(n);
    }
    poly exp(size_t n)
    {
        if(n==1) return {1}; 
        auto b=exp((n+1)/2), fac=poly{1}+cut(n)-b.ln(n);
        return (b*fac).cut(n);
    }
    auto pow(long long k, size_t n)
    {
        return (ln(n)*k).exp(n);
    }
    friend pair<poly, poly> div_mod(poly a, poly b)
    {
        int n=a.size(), m=b.size();
        if(n<m) return {{0}, a};
        auto ra=a, rb=b;
        ranges::reverse(ra); ranges::reverse(rb);
        auto q = (ra*rb.inv(n-m+1)).cut(n-m+1);
        ranges::reverse(q);
        auto r = a-b*q;
        r.resize(max(1, m-1));
        return {q, r};
    }
    friend T bostan_mori(poly p, poly q, size_t n)
    {
        for(;n;n>>=1)
        {
            auto nq = q;
            for(size_t i=1;i<nq.size();i+=2) nq[i] = -nq[i];
            auto u=p*nq, v=q*nq;
            p.resize((u.size()+!(n&1))/2);
            for(size_t i=0;i<p.size();i++) p[i] = u[(i<<1)+(n&1)];
            q.resize((v.size()+1)/2);
            for(size_t i=0;i<q.size();i++) q[i] = v[i<<1];
        }
        return p.empty()?0:p[0]/q[0];
    }
};
