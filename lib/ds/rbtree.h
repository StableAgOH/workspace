#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
template <typename T>
using rbtree_base = tree<pair<T,int>, null_type, less<>, rb_tree_tag, tree_order_statistics_node_update>;
template <typename T>
class rbtree : public rbtree_base<T>
{
    int cnt = 0;
public:
    auto insert(const T& x) { rbtree_base<T>::insert({x, cnt++}); }
    auto erase(const T& x)
    {
        auto it = lower_bound(x);
        if(it->first==x) rbtree_base<T>::erase(it);
    }
    auto order_of_key(const T& x) const { return rbtree_base<T>::order_of_key({x, INT_MIN}); }
    auto find_by_order(int rk) const { return rbtree_base<T>::find_by_order(rk); }
    auto lower_bound(const T& x) const { return rbtree_base<T>::lower_bound({x, INT_MIN}); }
    auto upper_bound(const T& x) const { return rbtree_base<T>::upper_bound({x, INT_MAX}); }
};
