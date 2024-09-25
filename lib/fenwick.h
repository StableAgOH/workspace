template <typename T, typename O=plus<T>>
class fenwick
{
private:
    O op;
    int n;
    vector<T> c;
    int lowbit(int x) const { return x&-x; }
public:
    fenwick(int n) : n(n) { c.resize(n+1); }
    fenwick(const ranges::range auto& r) : fenwick(ranges::size(r))
    {
        vector<T> pre(n+1);
        partial_sum(r.begin(), r.end(), pre.begin()+1);
        for(int i=1;i<=n;i++) c[i] = pre[i]-pre[i-lowbit(i)];
    }
    void clear() { ranges::fill(c, T()); }
    void add(int p, const T& x)
    {
        for(int i=p;i<=n;i+=lowbit(i)) c[i] = op(c[i], x);
    }
    auto operator()(int p) const
    {
        T sum{};
        for(int i=p;i;i-=lowbit(i)) sum += c[i];
        return sum;
    }
    auto operator()(int l, int r) const
    {
        return (*this)(r)-(*this)(l-1);
    }
};
