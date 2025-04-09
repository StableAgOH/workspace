template <typename T, auto Op>
requires convertible_to<invoke_result_t<decltype(Op), T, T>, T>
class segtree
{
public:
    segtree() = default;
    segtree(ranges::range auto&& rg, const T& e={}) : 
        n(ranges::size(rg)), sz(bit_ceil(unsigned(n))), data(sz<<1, e)
    {
        ranges::copy(rg, data.begin()+sz);
        for(int i=sz-1;i>=1;i--) update(i);
    }
    segtree(int n, const T& e={}) : segtree(vector(n, e), e) {}
    auto operator()() const { return data[1]; }
    auto operator()(int p) const { return data[p+sz]; }
    auto operator()(int l, int r) const
    {
        auto resl=data[0], resr=data[0];
        for(l+=sz,r+=sz+1;l<r;l>>=1,r>>=1)
        {
            if(l&1) resl = Op(resl, data[l++]);
            if(r&1) resr = Op(data[--r], resr);
        }
        return Op(resl, resr);
    }
    void set(int p, const T& x) { for(data[p+=sz]=x;p>1;p>>=1) update(p>>1); }
    void transform(int p, auto&& f) { set(p, f((*this)(p))); }
    template <predicate<T> Pred>
    int min_left(int r, Pred&& pred) const
    {
        if(!r) return 0;
        r += sz;
        T sum = data[0];
        do
        {
            r--;
            while(r>1&&(r&1)) r >>= 1;
            if(!pred(Op(data[r], sum)))
            {
                while(r<sz)
                {
                    r = r<<1|1;
                    if(pred(Op(data[r], sum)))
                    {
                        sum = Op(data[r], sum);
                        r--;
                    }
                }
                return r+1-sz;
            }
            sum = Op(data[r], sum);
        }
        while(lowbit(r)!=r);
        return 0;
    }
    template <predicate<T> Pred>
    int max_right(int l, Pred&& pred) const
    {
        if(l==n) return n;
        l += sz;
        T sum = data[0];
        do
        {
            while(l%2==0) l >>= 1;
            if(!pred(Op(sum, data[l])))
            {
                while(l<sz)
                {
                    l <<= 1;
                    if(pred(Op(sum, data[l])))
                    {
                        sum = Op(sum, data[l]);
                        l++;
                    }
                }
                return l-sz;
            }
            sum = Op(sum, data[l]);
            l++;
        }
        while(lowbit(l)!=l);
        return n;
    }
private:
    static constexpr auto lowbit(auto x) { return x&-x; }
    int n, sz;
    vector<T> data;
    void update(int p) { data[p] = Op(data[p<<1], data[p<<1|1]); }
};
