template <typename T>
class xor_hasher_weight
{
    mt19937 rnd;
    map<T, int> w;
public:
    xor_hasher_weight() : rnd(chrono::steady_clock::now().time_since_epoch().count()) {}
    xor_hasher_weight(ranges::range auto&& r) : xor_hasher_weight() { for(auto i : r) add(i); }
    xor_hasher_weight(initializer_list<T> il) : xor_hasher_weight() { for(auto i : il) add(i); }
    void add(const T& x) { if(!w.contains(x)) w[x] = rnd(); }
    int operator()(const T& x) const { return w.at(x); }
};
template <typename T>
class xor_hasher
{
    vector<int> p;
    xor_hasher_weight<T> w;
public:
    xor_hasher(ranges::range auto&& r, const xor_hasher_weight<T>& w) : p(ranges::size(r)+1), w(w)
    {
        auto it = ranges::begin(r);
        for(size_t i=1;i<p.size();i++) p[i] = p[i-1]^w(*it++);
    }
    auto& weight_function() { return w; }
    int operator()(size_t l, size_t r) const { return p[r+1]^p[l]; }
};
