#include <bits/stdc++.h>
#include <experimental/iterator>
#include "local.h"
using namespace std;
struct ListNode
{
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}
    friend istream& operator>>(istream& is, ListNode*& l)
    {
        assert(is.get()=='[');
        if(is.peek()==']') return is.ignore(1);
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
    friend istream& operator>>(istream& is, TreeNode*& t)
    {
        assert(is.get()=='[');
        if(is.peek()==']') return is.ignore(1);
        auto p = new TreeNode();
        queue<TreeNode*> q;
        q.push(p);
        bool right = true;
        while(!q.empty())
        {
            if(is.peek()!='n')
            {
                int x;
                is>>x;
                auto n = new TreeNode(x);
                if(right) q.front()->right = n;
                else q.front()->left = n;
                q.push(n);
            }
            else is.ignore(4);
            if(is.get()==']') break;
            if(right) q.pop();
            right ^= 1;
        }
        t = p->right;
        return is;
    }
    friend ostream& operator<<(ostream& os, TreeNode* t)
    {
        os<<"[";
        queue<TreeNode*> q;
        if(t)
        {
            q.push(t);
            os<<t->val;
        }
        while(!q.empty())
        {
            auto u = q.front();
            q.pop();
            if(u->left)
            {
                os<<","<<u->left->val;
                q.push(u->left);
            }
            else os<<",null";
            if(u->right)
            {
                os<<","<<u->right->val;
                q.push(u->right);
            }
            else os<<",null";
        }
        return os<<"]";
    }
};
istream& operator>>(istream& is, ranges::range auto& r)
{
    assert(is.get()=='[');
    if(is.peek()==']') return is.ignore(1);
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
    copy(r.begin(), r.end(), experimental::make_ostream_joiner(os, ","));
    return os<<']';
}
template <typename T, typename F, typename... Args>
void execute(T (F::*solve)(Args...))
{
    while(!(cin.peek()==EOF||cin.peek()=='\n'))
    {
        tuple<decay_t<Args>...> rargs;
        apply([&](auto&&... rarg) { (..., (cin>>rarg, cin.get())); }, rargs);
        auto args = tuple_cat(tuple(F()), rargs);
        if constexpr(same_as<T, void>) apply(solve, args);
        else cout<<apply(solve, args)<<'\n';
    }
}
#ifndef DEBUG
#define FOUT freopen("out.txt", "w", stdout);
#else
#define FOUT
#endif
#define LEETCODE_MAIN(solve)            \
    int main()                          \
    {                                   \
        freopen("in.txt", "r", stdin);  \
        FOUT                      \
        ios::sync_with_stdio(false);    \
        cin.tie(nullptr);               \
        execute(&Solution::solve);      \
    }
