class mint
{
    const static int mod = 998244353;
    long long x;
    void norm() { x = (x%mod+mod)%mod; }
public:
    mint() : x(0) {}
    mint(long long x) : x(x) { norm(); }
    friend mint operator^(mint lhs, long long rhs)
    {
        mint res = 1;
        for(;rhs;rhs>>=1,lhs=lhs*lhs) if(rhs&1) res = res*lhs;
        return res;
    }
    mint operator~() { return (*this)^(mod-2); }
    friend mint operator+(mint lhs, mint rhs) { return lhs.x+rhs.x; }
    friend mint operator-(mint lhs, mint rhs) { return lhs.x-rhs.x; }
    friend mint operator*(mint lhs, mint rhs) { return lhs.x*rhs.x; }
    friend mint operator/(mint lhs, mint rhs) { return lhs*(~rhs); }
    friend istream& operator>>(istream& is, mint& rhs) { is>>rhs.x; rhs.norm(); return is; }
    friend ostream& operator<<(ostream& os, mint rhs) { return os<<rhs.x; }
};
