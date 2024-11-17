template <typename T>
class xor_hasher_weight
{
    mt19937 rnd;
    map<T,int> w;
public:
    xor_hasher_weight() : rnd(mt19937(random_device()())) {}
    xor_hasher_weight(initializer_list<T> il) : xor_hasher_weight() { for(auto i : il) assign(i); }
    xor_hasher_weight(ranges::range auto&& r) : xor_hasher_weight() { for(auto i : r) assign(i); }
    void assign(const T& x) { if(!w.contains(x)) w[x] = rnd(); }
    int operator()(T x) const { return w.at(x); }
};
template <typename T>
class xor_hasher
{
    vector<int> p;
    xor_hasher_weight<T> w;
public:
    xor_hasher(ranges::range auto&& r, const xor_hasher_weight<T>& w) : p(ranges::size(r)), w(w)
    {
        for(size_t i=0;i<p.size();i++) p[i] = (i?p[i-1]:0)^w(r[i]);
    }
    int operator()(size_t l, size_t r) const { return p[r]^(l?p[l-1]:0); }
};
