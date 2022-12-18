class prime_tag_base
{
protected:
    int n;
};
class prime_tag : public virtual prime_tag_base
{
protected:
    typedef int prime_t;
    virtual void update_prime(const prime_t i) = 0;
    virtual void update_composite(const prime_t i, const prime_t j) = 0;
    prime_tag(const int n) { this->n = n; }
};
template <int I>
class prime_null_tag : public prime_tag
{
protected:
    void update_prime(const prime_t i) {}
    void update_composite(const prime_t i, const prime_t j) {}
    prime_null_tag(const int n) : prime_tag(n) {}
};
class prime_minf_tag : public prime_tag
{
protected:
    prime_minf_tag(const int n) : prime_tag(n) { minf.resize(n+1); }
    void update_prime(const prime_t i) { minf[i] = i; }
    void update_composite(const prime_t i, const prime_t j) { minf[i*j] = j; }
public:
    vector<prime_t> minf;
    auto divide_uniqvec_logn(prime_t x) const
    {
        assert(x<=this->n);
        vector<prime_t> res;
        while(x>1)
        {
            if(res.empty()||minf[x]!=res.back()) res.push_back(minf[x]);
            x /= minf[x];
        }
        return res;
    }
    auto divide_map_logn(prime_t x) const
    {
        assert(x<=this->n);
        map<prime_t, int> mp;
        while(x>1)
        {
            mp[minf[x]]++;
            x /= minf[x];
        }
        return mp;
    }
};
class prime_phi_tag : public prime_tag
{
protected:
    prime_phi_tag(const int n) : prime_tag(n) { phi.resize(n+1); }
    void update_prime(const prime_t i) { phi[i] = i-1; }
    void update_composite(const prime_t i, const prime_t j)
    {
        if(i%j==0) phi[i*j] = phi[i]*j;
        else phi[i*j] = phi[i]*(j-1);
    }
public:
    vector<prime_t> phi;
};
template <typename T1=prime_null_tag<0>, typename T2=prime_null_tag<1>>
requires derived_from<T1, prime_tag> && derived_from<T2, prime_tag>
class prime : public T1, public T2
{
private:
    typedef prime_tag::prime_t prime_t;
    vector<bool> vis;
    void update_prime(const prime_t i)
    {
        T1::update_prime(i);
        T2::update_prime(i);
    }
    void update_composite(const prime_t i, const prime_t j)
    {
        T1::update_composite(i, j);
        T2::update_composite(i, j);
    }
public:
    vector<prime_t> pri;
    prime() = delete;
    prime(const int n) : T1(n), T2(n)
    {
        vis.resize(n+1);
        for(prime_t i=2;i<=n;i++)
        {
            if(!vis[i])
            {
                pri.push_back(i);
                update_prime(i);
            }
            for(prime_t j : pri)
            {
                if(i*j>n) break;
                vis[i*j] = true;
                update_composite(i, j);
                if(i%j==0) break;
            }
        }
    }
    template <integral T>
    auto divide_uniqvec_sqrtn(T x) const
    {
        assert(sqrt(x)<=this->n);
        vector<T> res;
        for(auto i : pri)
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
        assert(sqrt(x)<=this->n);
        map<T, int> mp;
        for(auto i : pri)
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

// 枚举 z 的所有因子（除了 1）
prime<prime_minf_tag> pri(1e7);
auto mp = pri.divide_map_logn(z);
auto pf = vector(mp.begin(), mp.end());
decltype(z) mul = 1;
vector<decltype(z)> fac;
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
//* result: fac