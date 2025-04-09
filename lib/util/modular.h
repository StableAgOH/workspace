template <typename T>
class modular
{
public:
    modular() : x() {}
    modular(const auto& x) : x(norm(x)) {}
    explicit operator auto() const { return x; }
    auto pow(integral auto rhs) const
    {
        modular a=*this, res=1;
        for(;rhs;rhs>>=1,a*=a) if(rhs&1) res *= a;
        return res;
    }
    auto operator~() const { return pow(mod()-2); }
    auto operator<=>(const modular& rhs) const = default;
    auto operator-() const { return modular(-x); }
    auto& operator+=(const modular& rhs) { if((x+=rhs.x)>=mod()) x -= mod(); return *this; }
    auto& operator-=(const modular& rhs) { if((x-=rhs.x)<0) x += mod(); return *this; }
    auto& operator*=(const modular& rhs) { return *this = (long long)x*rhs.x; }
    auto& operator/=(const modular& rhs) { return *this *= (~rhs); }
    friend auto operator+(modular lhs, const modular& rhs) { return lhs += rhs; }
    friend auto operator-(modular lhs, const modular& rhs) { return lhs -= rhs; }
    friend auto operator*(modular lhs, const modular& rhs) { return lhs *= rhs; }
    friend auto operator/(modular lhs, const modular& rhs) { return lhs /= rhs; }
    friend auto& operator>>(istream& is, modular& rhs) { is>>rhs.x; rhs.x = norm(rhs.x); return is; }
    friend auto& operator<<(ostream& os, const modular& rhs) { return os<<rhs.x; }
private:
    static constexpr auto mod() { return T::value; }
    static constexpr auto norm(integral auto x)
    {
        if(!(-mod()<=x&&x<mod())) x %= mod();
        if(x<0) x += mod();
        return x;
    }
    int x;
};
template <int MOD>
using static_mint = modular<integral_constant<int, MOD>>;
struct dynamic_mod { static int value; };
int dynamic_mod::value;
using dynamic_mint = modular<dynamic_mod>;
