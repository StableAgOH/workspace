template <int Mx>
class prime_minf_tag
{
protected:
    void upd_p(int i) { minf[i] = i; }
    void upd_c(int i, int j) { minf[i*j] = j; }
public:
    array<int, Mx+1> minf = {};
    auto factorization_logn(integral auto x) const
    {
        vector<int> res;
        for(;x>1;x/=minf[x]) res.push_back(minf[x]);
        return res;
    }
};
template <int Mx>
class prime_phi_tag
{
protected:
    void upd_p(int i) { phi[i] = i-1; }
    void upd_c(int i, int j) { phi[i*j] = i%j?phi[i]*(j-1):phi[i]*j; }
public:
    array<int, Mx+1> phi = {0,1};
};
template <int Mx, template <int> typename... Tags>
class prime : public Tags<Mx>...
{
    static_assert(Mx>0);
    bitset<Mx+1> not_prime;
public:
    vector<int> primes;
    prime()
    {
        for(int i=2;i<=Mx;i++)
        {
            if(!not_prime[i])
            {
                primes.push_back(i);
                (..., Tags<Mx>::upd_p(i));
            }
            for(auto j : primes)
            {
                if(i*j>Mx) break;
                not_prime[i*j] = true;
                (..., Tags<Mx>::upd_c(i,j));
                if(i%j==0) break;
            }
        }
    }
    bool is_prime(integral auto x) const
    {
        if(x<=1) return false;
        if(x<=Mx) return !not_prime[x];
        for(auto i : primes)
        {
            if(ll(i)*i>x) break;
            if(x%i==0) return false;
        }
        return true;
    }
    auto factorization_sqrtn(integral auto x) const
    {
        vector<int> res;
        for(auto i : primes)
        {
            if(ll(i)*i>x) break;
            for(;x%i==0;x/=i) res.push_back(i);
        }
        if(x>1) res.push_back(x);
        return res;
    }
};
template <ranges::range R>
auto factorize(R&& factorization_result)
{
    using T = ranges::range_value_t<R>;
    map<T, int> cnt;
    for(auto i : factorization_result) cnt[i]++;
    vector pf(cnt.begin(), cnt.end());
    vector<T> fac;
    auto dfs = [&](auto&& self, size_t p, T mul) -> void
    {
        if(p==pf.size())
        {
            fac.push_back(mul);
            return;
        }
        for(auto i : views::iota(0))
        {
            self(self, p+1, mul);
            if(i==pf[p].second) break;
            mul *= pf[p].first;
        }
    };
    dfs(dfs, 0, 1);
    return fac;
};
