template <typename T>
class modular
{
    int x;
public:
    static constexpr int mod() { return T::value; }
    modular(long long v=0) : x(v%mod()) { if(x<0) x += mod(); }
    explicit operator auto() const { return x; }
    modular inv() const
    {
        int a=x, b=mod(), u=1, v=0;
        while(b)
        {
            int t = a/b;
            a = exchange(b, a%b);
            u = exchange(v, u-t*v);
        }
        return u;
    }
    modular pow(long long p) const
    {
        if(p<0) return inv().pow(-p);
        modular a=*this, r=1;
        for(;p;p>>=1,a*=a) if(p&1) r *= a;
        return r;
    }
    auto operator<=>(const modular& rhs) const = default;
    auto operator-() const { return modular(-x); }
    auto& operator+=(modular r) { if((x+=r.x)>=mod()) x -= mod(); return *this; }
    auto& operator-=(modular r) { if((x-=r.x)<0) x += mod(); return *this; }
    auto& operator*=(modular r) { x = 1LL*x*r.x%mod(); return *this; }
    auto& operator/=(modular r) { return *this *= r.inv(); }
    friend auto operator+(modular l, modular r) { return l += r; }
    friend auto operator-(modular l, modular r) { return l -= r; }
    friend auto operator*(modular l, modular r) { return l *= r; }
    friend auto operator/(modular l, modular r) { return l /= r; }
    friend auto& operator>>(istream& is, modular& a) { long long v; is>>v; a=v; return is; }
    friend auto& operator<<(ostream& os, modular a) { return os<<a.x; }
};
template <int M>
using static_mint = modular<integral_constant<int, M>>;
struct dynamic_mod { static int value; }; 
int dynamic_mod::value;
using dynamic_mint = modular<dynamic_mod>;
