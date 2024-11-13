template <typename T>
class modular
{
    static constexpr auto mod() { return T::value; }
    static constexpr auto norm(integral auto x)
    {
        if(!(-mod()<=x&&x<mod())) x %= mod();
        if(x<0) x += mod();
        return x;
    }
    int x;
public:
    modular() : x() {}
    modular(const auto& x) : x(norm(x)) {}
    explicit operator auto() const { return x; }
    auto operator()() const { return x; }
    auto pow(integral auto rhs) const
    {
        modular a=*this, res=1;
        for(;rhs;rhs>>=1,a*=a) if(rhs&1) res *= a;
        return res;
    }
    auto operator~() const { return pow(mod()-2); }
    auto operator<=>(const modular& rhs) const = default;
    auto operator-() const { return modular(-x); }
    auto operator++() { return *this += 1; }
    auto operator--() { return *this -= 1; }
    auto operator++(int) { auto res = *this; return ++*this, res; }
    auto operator--(int) { auto res = *this; return --*this, res; }
    auto& operator+=(const modular& rhs) { if((x+=rhs.x)>=mod()) x -= mod(); return *this; }
    auto& operator-=(const modular& rhs) { if((x-=rhs.x)<0) x += mod(); return *this; }
    auto& operator*=(const modular& rhs) { return *this = (ll)x*rhs.x; }
    auto& operator/=(const modular& rhs) { return *this *= (~rhs); }
    friend auto operator+(modular lhs, const modular& rhs) { return lhs += rhs; }
    friend auto operator-(modular lhs, const modular& rhs) { return lhs -= rhs; }
    friend auto operator*(modular lhs, const modular& rhs) { return lhs *= rhs; }
    friend auto operator/(modular lhs, const modular& rhs) { return lhs /= rhs; }
    friend auto& operator>>(istream& is, modular& rhs) { is>>rhs.x; rhs.x = norm(rhs.x); return is; }
    friend auto& operator<<(ostream& os, const modular& rhs) { return os<<rhs.x; }
};
template <typename T>
struct std::formatter<modular<T>> : formatter<string>
{
    auto format(const modular<T>& m, format_context& ctx) const
    {
        return format_to(ctx.out(), "{}", m());
    }
};
// #define DYNAMIC_MOD
#ifdef DYNAMIC_MOD
struct mod { static int value; };
int mod::value = 1e9+7;
using mint = modular<mod>;
#else
constexpr int mod = 1e9+7;
using mint = modular<integral_constant<int, mod>>;
#endif
