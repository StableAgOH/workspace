template <integral T>
struct basis
{
    vector<T> base;
    basis() = default;
    basis(ranges::range auto&& rg) { for(auto i : rg) insert(i); }
    void insert(T x)
    {
        for(auto i : base) x = min(x, x^i);
        for(auto& i : base) i = min(i, i^x);
        if(x) base.push_back(x);
    }
    bool can_construct(T x)
    {
        for(auto i : base) x = min(x, x^i);
        return !x;
    }
    T get_max()
    {
        T ret = 0;
        for(auto i : base) ret = max(ret, ret^i);
        return ret;
    }
    T get_min() { return base.back(); }
};
