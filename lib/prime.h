template <int Mx>
class prime_minf_tag
{
protected:
    void upd_p(int i) { minf[i] = i; }
    void upd_c(int i, int j) { minf[i*j] = j; }
    prime_minf_tag() = default;
public:
    array<int, Mx+1> minf = {};
#ifdef __cpp_lib_generator
    template <integral T>
    generator<T> factorization_logn(T x) const { for(;x>1;x/=minf[x]) co_yield minf[x]; }
#else
    auto factorization_logn(integral auto x) const
    {
        vector<int> res;
        for(;x>1;x/=minf[x]) res.push_back(minf[x]);
        return res;
    }
#endif
};
template <int Mx>
class prime_phi_tag
{
protected:
    prime_phi_tag() = default;
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
    void upd_p(int i)
    {
        primes.push_back(i);
        (..., Tags<Mx>::upd_p(i));
    }
    void upd_c(int i, int j)
    {
        not_prime[i*j] = true;
        (..., Tags<Mx>::upd_c(i,j));
    }
public:
    vector<int> primes;
    prime()
    {
        for(int i=2;i<=Mx;i++)
        {
            if(!not_prime[i]) upd_p(i);
            for(auto j : primes)
            {
                if(i*j>Mx) break;
                upd_c(i,j);
                if(i%j==0) break;
            }
        }
    }
    bool is_prime(integral auto x) const
    {
        if(x<=1) return false;
        if(x<=Mx) return !not_prime[x];
        auto s = sqrt(x);
        for(auto i : primes)
        {
            if(i>s) break;
            if(x%i==0) return false;
        }
        return true;
    }
#ifdef __cpp_lib_generator
    template <integral T>
    generator<T> factorization_sqrtn(T x) const
    {
        for(auto i : primes)
        {
            if(i>sqrt(x)) break;
            for(;x%i==0;x/=i) co_yield i;
        }
        if(x>1) co_yield x;
    }
#else
    auto factorization_sqrtn(integral auto x) const
    {
        vector<int> res;
        for(auto i : primes)
        {
            if(i>sqrt(x)) break;
            for(;x%i==0;x/=i) res.push_back(i);
        }
        if(x>1) res.push_back(x);
        return res;
    }
#endif
};
auto factorize(auto&& factorization_result)
{
    using T = decay_t<decltype(*factorization_result.begin())>;
    map<T,int> cnt;
    for(auto i : factorization_result) cnt[i]++;
    vector pf(cnt.begin(), cnt.end());
    vector<T> fac;
    auto dfs = [&](this auto dfs, size_t p, T mul)
    {
        if(p==pf.size())
        {
            fac.push_back(mul);
            return;
        }
        for(auto i : views::iota(0))
        {
            dfs(p+1, mul);
            if(i==pf[p].second) break;
            mul *= pf[p].first;
        }
    };
    dfs(0, 1);
    return fac;
};
