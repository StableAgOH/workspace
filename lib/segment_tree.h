#include <bits/stdc++.h>
using namespace std;
template <typename T>
class segment_tree
{
private:
    struct Node
    {
        int l,r;
        T f,val;
    };
    int n;
    int root;
    vector<Node> t;
    void assign(int& k)
    {
        if(k) return;
        k = t.size();
        t.emplace_back();
    }
    void pushup(int k) { t[k].val = t[t[k].l].val+t[t[k].r].val; }
    void pushdw(int k,int l,int r)
    {
        auto f = t[k].f;
        t[k].f = T();
        t[t[k].l].f += f;
        t[t[k].r].f += f;
        int m = midpoint(l,r);
        t[t[k].l].val += (m-l+1)*f;
        t[t[k].r].val += (r-m)*f;
    }
    void update_impl(int& k,int l,int r,int p,const T& x)
    {
        assign(k);
        if(l==r)
        {
            t[k].val += x;
            return;
        }
        pushdw(k,l,r);
        int m = midpoint(l,r);
        if(p<=m) update_impl(t[k].l,l,m,p,x);
        else update_impl(t[k].r,m+1,r,p,x);
        pushup(k);
    }
    void update_impl(int& k,int l,int r,int L,int R,const T& x)
    {
        assign(k);
        if(L<=l&&R>=r)
        {
            t[k].f += x;
            t[k].val += (r-l+1)*x;
            return;
        }
        pushdw(k,l,r);
        int m = midpoint(l,r);
        if(L<=m) update_impl(t[k].l,l,m,L,R,x);
        if(R>m) update_impl(t[k].r,m+1,r,L,R,x);
        pushup(k);
    }
    T query_impl(int k,int l,int r,int p)
    {
        if(l==r) return t[k].val;
        pushdw(k,l,r);
        int m = midpoint(l,r);
        if(p<=m) return query_impl(t[k].l,l,m,p);
        else return query_impl(t[k].r,m+1,r,p);
    }
    T query_impl(int k,int l,int r,int L,int R)
    {
        if(L<=l&&R>=r) return t[k].val;
        pushdw(k,l,r);
        int m = midpoint(l,r);
        T res = T();
        if(L<=m) res += query_impl(t[k].l,l,m,L,R);
        if(R>m) res += query_impl(t[k].r,m+1,r,L,R);
        return res;
    }
public:
    segment_tree(int n) : n(n), root(0) { t.reserve(2*n); t.resize(1); }
    template <ranges::range R>
    segment_tree(const R& r) : segment_tree(ranges::size(r))
    {
        auto it = ranges::begin(r);
        auto build = [&](auto&& build,int& k,int l,int r)
        {
            assign(k);
            if(l==r)
            {
                t[k].val = *it++;
                return;
            }
            int m = midpoint(l,r);
            build(build,t[k].l,l,m);
            build(build,t[k].r,m+1,r);
            pushup(k);
        };
        build(build,root,0,n-1);
    }
    void update(int p,const T& x) { update_impl(root,0,n-1,p,x); }
    void update(int l,int r,const T& x) { update_impl(root,0,n-1,l,r,x); }
    T operator()(int p) { return query_impl(root,0,n-1,p); }
    T operator()(int l,int r) { return query_impl(root,0,n-1,l,r); }
};
