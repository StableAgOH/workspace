#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T>
class rbtree
{
    int id = 0;
    tree<pair<T, int>, null_type, less<>, rb_tree_tag, tree_order_statistics_node_update> t;
public:
    auto begin() { return t.begin(); }
    auto end() { return t.end(); }
    auto size() { return t.size(); }
    auto empty() { return t.empty(); }
    auto insert(const T& x) { t.insert({x, id++}); }
    auto erase(const T& x) { t.erase(t.lower_bound({x, INT_MIN})); }
    auto order_of_key(const T& x) { return t.order_of_key({x, INT_MIN})+1; }
    auto find_by_order(int rk) { return t.find_by_order(rk-1); }
    auto prev(const T& x)
    {
        auto it = t.lower_bound({x, INT_MIN});
        return it==t.begin()?t.end():--it;
    }
    auto next(const T& x) { return t.upper_bound({x, INT_MAX}); }
};
