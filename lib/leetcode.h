#include <bits/stdc++.h>
#include "local.h"
using namespace std;
struct ListNode
{
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}
    ~ListNode() { delete next; }
    friend istream& operator>>(istream& is, ListNode*& l)
    {
        assert(is.get()=='[');
        if(cin.peek()==']') return is;
        auto head=new ListNode(), p=head;
        while(true)
        {
            p->next = new ListNode();
            is>>p->next->val;
            p = p->next;
            if(is.get()==']') break;
        }
        l = head->next;
        return is;
    }
    friend ostream& operator<<(ostream& os, ListNode* l)
    {
        os<<'[';
        for(;l;l=l->next) os<<l->val<<",]"[l->next==nullptr];
        return os;
    }
};
struct TreeNode
{
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
    ~TreeNode() { delete left; delete right; }
};
istream& operator>>(istream& is, ranges::range auto& r)
{
    assert(is.get()=='[');
    if(cin.peek()==']') return is;
    ranges::range_value_t<decltype(r)> x;
    while(true)
    {
        is>>x;
        r.push_back(x);
        if(is.get()==']') break;
    }
    return is;
}
template <typename C, typename T>
basic_ostream<C,T>& operator<<(basic_ostream<C,T>& os, const ranges::range auto& r)
{
    os<<'[';
    for(auto it=ranges::begin(r);it!=ranges::end(r);)
        os<<*it++<<",]"[it==ranges::end(r)];
    return os;
}
template <typename T, typename F, typename... Args>
void execute(T (F::*solve)(Args...))
{
    while(true)
    {
        tuple<decay_t<Args>...> rargs;
        apply([&](auto&&... rarg) { (..., (cin>>rarg, cin.get())); }, rargs);
        auto args = tuple_cat(tuple(F()), rargs);
        if constexpr(same_as<T, void>) apply(solve, args);
        else cout<<apply(solve, args)<<'\n';
        if(cin.peek()==EOF||cin.peek()=='\n') break;
    }
}
#ifndef DEBUG
#define ENABLE_OUT freopen("out.txt", "w", stdout);
#else
#define ENABLE_OUT
#endif
#define LEETCODE_MAIN(solve)            \
    int main()                          \
    {                                   \
        freopen("in.txt", "r", stdin);  \
        ENABLE_OUT                      \
        ios::sync_with_stdio(false);    \
        cin.tie(nullptr);               \
        execute(&Solution::solve);      \
        return 0;                       \
    }
