class prime_tag
{
protected:
    int n;
    virtual void update_prime(int i) = 0;
    virtual void update_composite(int i, int j) = 0;
    prime_tag(int n) : n(n) {}
};
class prime_minf_tag : public virtual prime_tag
{
protected:
    prime_minf_tag(int n) : prime_tag(n) { minf.resize(n+1); }
    void update_prime(int i) { minf[i] = i; }
    void update_composite(int i, int j) { minf[i*j] = j; }
public:
    vector<int> minf;
    auto divide_uniqvec_logn(int x) const
    {
        assert(x<=this->n);
        vector<int> res;
        while(x>1)
        {
            if(res.empty()||minf[x]!=res.back()) res.push_back(minf[x]);
            x /= minf[x];
        }
        return res;
    }
    auto divide_map_logn(int x) const
    {
        assert(x<=this->n);
        map<int, int> mp;
        while(x>1)
        {
            mp[minf[x]]++;
            x /= minf[x];
        }
        return mp;
    }
};
class prime_phi_tag : public virtual prime_tag
{
protected:
    prime_phi_tag(int n) : prime_tag(n) { phi.resize(n+1); }
    void update_prime(int i) { phi[i] = i-1; }
    void update_composite(int i, int j)
    {
        if(i%j==0) phi[i*j] = phi[i]*j;
        else phi[i*j] = phi[i]*(j-1);
    }
public:
    vector<int> phi;
};
template <derived_from<prime_tag>... Tags>
class prime : virtual prime_tag, public Tags...
{
private:
    void update_prime(int i) { (..., Tags::update_prime(i)); }
    void update_composite(int i, int j) { (..., Tags::update_composite(i, j)); }
public:
    vector<bool> is_prime;
    vector<int> primes;
    prime() = delete;
    prime(int n) : prime_tag(n), Tags(n)...
    {
        assert(n<=1e8);
        is_prime.resize(n+1);
        for(int i=2;i<=n;i++)
        {
            if(!is_prime[i])
            {
                primes.push_back(i);
                update_prime(i);
            }
            for(auto j : primes)
            {
                if(i*j>n) break;
                is_prime[i*j] = true;
                update_composite(i, j);
                if(i%j==0) break;
            }
        }
    }
    template <integral T>
    auto divide_uniqvec_sqrtn(T x) const
    {
        vector<T> res;
        for(auto i : primes)
        {
            if(i>x) break;
            if(x%i==0) res.push_back(i);
            while(x%i==0) x /= i;
        }
        if(x>1) res.push_back(x);
        return res;
    }
    template <integral T>
    auto divide_map_sqrtn(T x) const
    {
        map<T, int> mp;
        for(auto i : primes)
        {
            if(i>x) break;
            while(x%i==0)
            {
                mp[i]++;
                x /= i;
            }
        }
        if(x>1) mp[x]++;
        return mp;
    }
};

// 枚举 z 的所有因子
const int N = 1e5;
prime<prime_minf_tag> pri(N);
auto f = [&](auto z)
{
    auto mp = pri.divide_map_logn(z);
    auto pf = vector(mp.begin(), mp.end());
    decltype(z) mul = 1;
    vector<decltype(z)> fac = {1};
    function<void(size_t)> dfs = [&](size_t p)
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