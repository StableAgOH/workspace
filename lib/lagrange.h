template <typename T>
class lagrange
{
private:
    using vec = vector<T>;
    int n;
    vec x,y;
    void mul(vec& f, int p, const T& t)
    {
        for(int i=p;i>0;i--) f[i] = f[i-1]+t*f[i];
        f[0] *= t;
    }
    void div(vec f, vec& r, const T& t)
    {
        for(int i=f.size()-1;i>0;i--) f[i-1] -= t*f[i];
        copy(f.begin()+1, f.end(), r.begin());
    }
public:
    lagrange(const vec& x, const vec& y)
    {
        assert(x.size()==y.size());
        this->n = x.size();
        this->x = x;
        this->y = y;
    }
    T get(const T& x0)
    {
        T y0 = 0;
        for(int i=0;i<n;i++)
        {
            T a=1, b=1;
            for(int j=0;j<n;j++)
            {
                if(i==j) continue;
                a *= (x0-x[j]);
                b *= (x[i]-x[j]);
            }
            y0 += a/b*y[i];
        }
        return y0;
    }
    /// @return a[0] + a[1]x + a[2]x^2 + ...
    vec get_coefficients()
    {
        vec a(n), b(n+1), c(n);
        b[0]=-x[0], b[1]=1;
        for(int i=2;i<=n;i++) mul(b,i,-x[i-1]);
        for(int i=0;i<n;i++)
        {
            T p = 1;
            for(int j=0;j<n;j++) if(i!=j) p *= (x[i]-x[j]);
            T q = y[i]/p;
            div(b,c,-x[i]);
            for(int j=0;j<n;j++) a[j] += q*c[j];
        }
        return a;
    }
};
