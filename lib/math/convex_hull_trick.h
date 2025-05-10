/**
 * @tparam Extremum 求 min 传 false，求 max 传 true
 * @tparam AddOrd 插入斜率单调递减传 false，插入单调递增传 true
 * @tparam QryOrd 查询 x 值单调递减传 false，查询单调递增传 true
 */
template <typename T, bool Extremum, bool AddOrd, bool QryOrd>
class convex_hull_trick
{
public:
    struct line
    {
        T k, b;
        int id;
        auto operator()(T x) const { return k*x+b; }
        auto isect(const line& o) const { return (long double)(o.b-b)/(k-o.k); }
    };
    void add_line(T k, T b)
    {
        line l(k, b, cnt++);
        if(!ls.empty()&&ls.back().k==l.k)
        {
            if(cmp1(l.b, ls.back().b)) ls.back() = l;
            return;
        }
        while(ls.size()>1&&cmp2(ls[ls.size()-2].isect(l), ls[ls.size()-2].isect(ls.back()))) ls.pop_back();
        ls.push_back(l);
    }
    auto get_line(T x)
    {
        if constexpr(Extremum^AddOrd^QryOrd)
        {
            while(ls.size()>1&&cmp1(ls[1](x), ls.front()(x))) ls.pop_front();
            return ls.front();
        }
        else
        {
            while(ls.size()>1&&cmp1(ls[ls.size()-2](x), ls.back()(x))) ls.pop_back();
            return ls.back();
        }
    }
    auto operator()(T x) { return get_line(x)(x); }
private:
    static constexpr conditional_t<Extremum, greater<>, less<>> cmp1{};
    static constexpr conditional_t<Extremum^AddOrd, greater<>, less<>> cmp2{};
    int cnt = 0;
    deque<line> ls;
};
