template <typename T>
class modular
{
    static constexpr long long norm(long long v)
    {
        if(v<-mod()||v>=mod()) v %= mod();
        if(v<0) v += mod();
        return v;
    }
    int x;
public:
    static constexpr auto mod() { return T::value; }
    constexpr modular(long long v=0) : x(norm(v)) {}
    constexpr explicit operator int() const { return x; }
    constexpr modular inv() const
    {
        int a=x, b=mod();
        long long u=1, v=0;
        while(b)
        {
            int t = a/b;
            a = exchange(b, a%b);
            u = exchange(v, u-t*v);
        }
        return u;
    }
    constexpr modular pow(long long p) const
    {
        if(p<0) return inv().pow(-p);
        modular a=*this, r=1;
        for(;p;p>>=1,a*=a) if(p&1) r *= a;
        return r;
    }
    constexpr auto operator<=>(const modular&) const = default;
    constexpr auto operator-() const { return modular(x?mod()-x:0); }
    constexpr auto& operator+=(modular o) { if((x+=o.x)>=mod()) x -= mod(); return *this; }
    constexpr auto& operator-=(modular o) { if((x-=o.x)<0) x += mod(); return *this; }
    constexpr auto& operator*=(modular o) { x = norm(1LL*x*o.x); return *this; }
    constexpr auto& operator/=(modular o) { return *this *= o.inv(); }
    friend auto operator+(modular x, modular y) { return x += y; }
    friend auto operator-(modular x, modular y) { return x -= y; }
    friend auto operator*(modular x, modular y) { return x *= y; }
    friend auto operator/(modular x, modular y) { return x /= y; }
    friend auto& operator>>(istream& is, modular& a) { long long v; is>>v; a=v; return is; }
    friend auto& operator<<(ostream& os, modular a) { return os<<a.x; }
};
template <int P>
using static_mint = modular<integral_constant<int, P>>;
struct dynamic_mod { static inline int value; };
using dynamic_mint = modular<dynamic_mod>;
