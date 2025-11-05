template <int B=131, int M=998244353>
class rolling_hasher
{
    int n;
    vector<int> p, h;
public:
    class result
    {
        int n, p, h;
    public:
        result(int n, int p, int h) : n(n), p(p), h(h) {}
        operator int() const { return h; }
        auto operator+(const result& oth) const { return result(n+oth.n, ll(p)*oth.p%M, (ll(h)*oth.p+oth.h)%M); }
        auto operator+=(const result& oth) { return *this = *this+oth; }
    };
    template <typename Iter>
    rolling_hasher(Iter first, Iter last) : n(distance(first, last)), p(n+1, 1), h(n+1)
    {
        for(int i=1;i<=n;i++)
        {
            p[i] = (ll(p[i-1])*B)%M;
            h[i] = (ll(h[i-1])*B+(*first++))%M;
        }
    }
    operator int() const { return h.back(); }
    auto operator()(int l, int r) const { return result(r-l+1, p[r-l+1], (h[r+1]-ll(h[l])*p[r-l+1]%M+M)%M); }
};
