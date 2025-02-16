template <typename T>
class polynomial
{
private:
    size_t n;
    valarray<T> coef;
    static auto fft(const vector<complex<double>>& p, int flag=1)
    {
        assert(has_single_bit(p.size()));
        auto n = p.size();
        vector<size_t> pos(n);
        for(size_t i=0;i<n;i++)
        {
            pos[i] = pos[i>>1]>>1;
            if(i&1) pos[i] |= n>>1;
        }
        vector<complex<double>> a(n);
        for(size_t i=0;i<n;i++) a[pos[i]] = p[i];
        for(size_t i=1;i<n;i<<=1)
        {
            complex w(cos(numbers::pi/i), sin(flag*numbers::pi/i));
            for(size_t j=0;j<n;j+=i<<1)
            {
                complex wk = 1.0;
                for(size_t k=0;k<i;k++)
                {
                    auto x=a[j+k], y=wk*a[j+k+i];
                    a[j+k] = x+y;
                    a[j+k+i] = x-y;
                    wk *= w;
                }
            }
        }
        if(flag==-1) for(auto& i : a) i /= n;
        return a;
    }
public:
    polynomial() : n(0), coef(1) {}
    polynomial(size_t n) : n(n), coef(n+1) {}
    polynomial(initializer_list<T> l) : n(l.size()-1), coef(l) {}
    auto degree() const { return n; }
    auto operator[](int i) const { return coef[i]; }
    auto& operator[](int i) { return coef[i]; }
    auto& operator+=(const polynomial& rhs)
    {
        n = max(n, rhs.n);
        coef.resize(n+1);
        coef += rhs.coef;
        return *this;
    }
    auto operator+(const polynomial& rhs) const { return polynomial(*this) += rhs; }
    auto& operator-=(const polynomial& rhs)
    {
        n = max(n, rhs.n);
        coef.resize(n+1);
        coef -= rhs.coef;
        return *this;
    }
    auto operator-(const polynomial& rhs) const { return polynomial(*this) += rhs; }
    auto& operator*=(const polynomial& rhs)
    {
        auto m = bit_ceil(n+rhs.n+1);
        vector<complex<double>> c1(m), c2(m);
        for(size_t i=0;i<=n;i++) c1[i] = coef[i];
        for(size_t i=0;i<=rhs.n;i++) c2[i] = rhs.coef[i];
        auto m1=fft(c1), m2=fft(c2);
        for(size_t i=0;i<m;i++) m1[i] *= m2[i];
        auto c = fft(m1, -1);
        n += rhs.n;
        coef.resize(n+1);
        for(size_t i=0;i<=n;i++) coef[i] = round(c[i].real());
        return *this;
    }
    auto operator*(const polynomial& rhs) const { return polynomial(*this) *= rhs; }
    friend istream& operator>>(istream& lhs, polynomial& rhs)
    {
        for(size_t i=0;i<=rhs.n;i++) lhs>>rhs[i];
        return lhs;
    }
    friend ostream& operator<<(ostream& lhs, const polynomial& rhs)
    {
        for(size_t i=0;i<=rhs.n;i++) lhs<<rhs[i]<<" ";
        return lhs;
    }
};
