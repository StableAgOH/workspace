template <typename T>
class fenwick
{
private:
    int n;
    vector<T> c;
    int lowbit(int x) { return x&-x; }
public:
    fenwick(const int n) : n(n) { c.resize(n+1); }
    void add(int p, const T& x) { for(auto i=p;i<=n;i+=lowbit(i)) c[p] += x; }
    T query(int p)
    {
        T sum = T();
        for(auto i=p;i;i-=lowbit(i)) sum += c[i];
        return sum;
    }
    T query(int l, int r) { return query(r)-query(l-1); }
};
