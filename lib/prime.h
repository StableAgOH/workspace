class prime_minf_tag
{
protected:
    prime_minf_tag(int n) : minf(n+1) {}
    void upd_p(int i) { minf[i] = i; }
    void upd_c(int i, int j) { minf[i*j] = j; }
public:
    vector<int> minf;
    auto factorization_logn(integral auto x) const
    {
        vector<int> res;
        for(;x>1;x/=minf[x]) res.push_back(minf[x]);
        return res;
    }
};
class prime_phi_tag
{
protected:
    prime_phi_tag(int n) : phi(n+1) { phi[1] = 1; }
    void upd_p(int i) { phi[i] = i-1; }
    void upd_c(int i, int j) { phi[i*j] = i%j?phi[i]*(j-1):phi[i]*j; }
public:
    vector<int> phi;
};
template <typename... Tags>
class prime : public Tags...
{
    void upd_p([[maybe_unused]] int i)
    {
        primes.push_back(i);
        (..., Tags::upd_p(i));
    }
    void upd_c([[maybe_unused]] int i, [[maybe_unused]] int j)
    {
        is_prime[i*j] = false;
        (..., Tags::upd_c(i,j));
    }
public:
    vector<bool> is_prime;
    vector<int> primes;
    prime() = delete;
    prime(int n) : Tags(n)..., is_prime(n+1, true)
    {
        for(int i=2;i<=n;i++)
        {
            if(is_prime[i]) upd_p(i);
            for(auto j : primes)
            {
                if(i*j>n) break;
                upd_c(i,j);
                if(i%j==0) break;
            }
        }
    }
    auto factorization_sqrtn(integral auto x) const
    {
        vector<decltype(x)> res;
        for(auto i : primes)
        {
            if(decltype(x)(i)*i>x) break;
            for(;x%i==0;x/=i) res.push_back(i);
        }
        if(x>1) res.push_back(x);
        return res;
    }
};

prime<prime_minf_tag> pri(/* maxz */);
auto factorize = [&](auto z)
{
    map<int,int> cnt;
    for(auto i : pri.factorization_logn(z)) cnt[i]++;
    vector pf(cnt.begin(), cnt.end());
    decltype(z) mul = 1;
    vector fac = {mul};
    auto dfs = [&](this auto dfs, int p)
    {
        if(p==pf.size()) return;
        dfs(p+1);
        auto [a,b] = pf[p];
        for(int i=0;i<b;i++)
        {
            mul *= a;
            fac.push_back(mul);
            dfs(p+1);
        }
        for(int i=0;i<b;i++) mul /= a;
    };
    dfs(0);
    return fac;
};
