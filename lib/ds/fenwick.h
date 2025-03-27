template <typename T>
class fenwick
{
public:
    fenwick(ranges::range auto&& rg) : data(ranges::size(rg)+1)
    {
        vector<T> p(data.size());
        inclusive_scan(rg.begin(), rg.end(), p.begin()+1);
        for(int i=1;i<(int)p.size();i++) data[i] = p[i]-p[i-lowbit(i)];
    }
    fenwick(int n, const T& init={}) : fenwick(vector(n, init)) {}
    auto prefix(int p) const
    {
        T sum{};
        for(int i=p+1;i;i-=lowbit(i)) sum += data[i];
        return sum;
    }
    auto suffix(int p) const { return prefix(size()-1)-prefix(p); }
    auto operator()(int l, int r) const { return prefix(r)-prefix(l-1); }
    auto operator()(int l) const { return (*this)(l, l); }
    void add(int p, const T& x)
    {
        for(int i=p+1;i<=size();i+=lowbit(i))
            data[i] += x;
    }
    void clear() { ranges::fill(data, T()); }
    int size() const { return data.size()-1; }
private:
    static constexpr auto lowbit(auto x) { return x&-x; }
    vector<T> data;
};
