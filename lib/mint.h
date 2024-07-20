class mint
{
    const static ll mod = 998244353;
    void norm() { x = (x%mod+mod)%mod; }
public:
    ll x;
    mint() : x(0) {}
    mint(ll x) : x(x) { norm(); }
    friend mint operator^(mint lhs, ll rhs)
    {
        mint res = 1;
        for(;rhs;rhs>>=1)
        {
            if(rhs&1) res *= lhs;
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
