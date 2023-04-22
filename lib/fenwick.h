template <typename T>
class fenwick
{
private:
    size_t n;
    vector<T> pre;
    size_t lowbit(size_t x) { return x&-x; }
public:
    fenwick(const size_t n) : n(n) { pre.resize(n+1); }
    void add(size_t p, const T& x) { for(auto i=p;i<=n;i+=lowbit(i)) pre[p] += x; }
    T query(size_t p)
    {
        assert(p<=n);
        T sum = T();
        for(auto i=p;i;i-=lowbit(i)) sum += pre[i];
        return sum;
    }
    T query(size_t l, size_t r)
    {
        assert(l<=r&&r<=n);
        return query(r)-query(l-1);
    }
};
