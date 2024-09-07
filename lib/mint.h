ll mod = 998244353;
class mint
{
    ll x;
    void norm() { x = (x%mod+mod)%mod; }
public:
    mint() : mint(0) {}
    mint(ll x) : x(x) { norm(); }
    auto val() const { return x; }
    friend mint operator^(mint lhs, mint rhs)
    {
        mint res = 1;
        for(;rhs.x;rhs.x>>=1)
        {
            if(rhs.x&1) res *= lhs;
            lhs *= lhs;
        }
        return res;
    }
    mint operator~() { return (*this)^(mod-2); }
    friend bool operator<(mint lhs, mint rhs) { return lhs.x<rhs.x; }
    friend bool operator==(mint lhs, mint rhs) { return lhs.x==rhs.x; }
    friend mint operator+=(mint& lhs, mint rhs) { return lhs = lhs.x+rhs.x; }
    friend mint operator+(mint lhs, mint rhs) { return lhs += rhs; }
    friend mint operator-=(mint& lhs, mint rhs) { return lhs = lhs.x-rhs.x; }
    friend mint operator-(mint lhs, mint rhs) { return lhs -= rhs; }
    friend mint operator*=(mint& lhs, mint rhs) { return lhs = lhs.x*rhs.x; }
    friend mint operator*(mint lhs, mint rhs) { return lhs *= rhs; }
    friend mint operator/=(mint& lhs, mint rhs) { return lhs *= (~rhs); }
    friend mint operator/(mint lhs, mint rhs) { return lhs /= rhs; }
    friend istream& operator>>(istream& is, mint& rhs) { is>>rhs.x; rhs.norm(); return is; }
    friend ostream& operator<<(ostream& os, mint rhs) { return os<<rhs.x; }
};
template <>
struct std::formatter<mint> : std::formatter<ll>
{
    auto format(mint m, format_context& ctx) const
    {
        return std::formatter<ll>::format(m.val(), ctx);
    }
};
