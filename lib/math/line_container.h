template <typename T>
class line_container
{
public:
    struct line
    {
        mutable T k, m;
        mutable long double p;
        int id;
        auto operator()(T x) const { return k*x+m; }
        bool operator<(const line& o) const { return k<o.k; }
        bool operator<(long double x) const { return p<x; }
    };
    void add_line(T k, T m)
    {
        auto z=ls.emplace(k, m, 0, cnt++), y=z++, x=y;
        while(isect(y, z)) z = ls.erase(z);
        if(x!=ls.begin()&&isect(--x, y)) isect(x, y=ls.erase(y));
        while((y=x)!=ls.begin()&&(--x)->p>=y->p) isect(x, ls.erase(y));
    }
    auto get_line(T x) { return *ls.lower_bound(x); }
    auto operator()(T x) { return get_line(x)(x); }
private:
    int cnt = 0;
    multiset<line, less<>> ls;
    bool isect(decltype(ls.begin()) x, decltype(ls.begin()) y)
    {
        if(y==ls.end()) return x->p=1e100, false;
        if(x->k==y->k) x->p = x->m>y->m?1e100:-1e100;
        else x->p = (long double)(y->m-x->m)/(x->k-y->k);
        return x->p>=y->p;
    }
};
