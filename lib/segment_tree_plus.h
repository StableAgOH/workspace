template <typename T>
class segment_tree_plus
{
private:
    struct Node
    {
        Node* ls;
        Node* rs;
        T val, lazy;
    };
    int n;
    Node* root;
    void pushup(Node* k) { k->val = k->ls->val+k->rs->val; }
    void pushdw(int l,int r,Node* k)
    {
        int m = midpoint(l,r);
        k->ls->lazy += k->lazy;
        k->rs->lazy += k->lazy;
        k->ls->val += k->lazy*(m-l+1);
        k->rs->val += k->lazy*(r-m);
        k->lazy = T();
    }
    template <typename Iter>
    void build(int l,int r,Node*& k,Iter& it)
    {
        k = new Node;
        if(l==r) k->val = *it++;
        else
        {
            int m = midpoint(l,r);
            build(l,m,k->ls,it);
            build(m+1,r,k->rs,it);
            pushup(k);
        }
    }
    void add(int x,int y,const T& z,int l,int r,Node* k)
    {
        if(x<=l&&r<=y)
        {
            k->lazy += z;
            k->val += z*(r-l+1);
        }
        else
        {
            pushdw(l,r,k);
            int m = midpoint(l,r);
            if(x<=m) add(x,y,z,l,m,k->ls);
            if(y>m) add(x,y,z,m+1,r,k->rs);
            pushup(k);
        }
    }
    T query(int x,int y,int l,int r,Node* k)
    {
        if(x<=l&&r<=y) return k->val;
        else
        {
            pushdw(l,r,k);
            int m = midpoint(l,r);
            T res{};
            if(x<=m) res += query(x,y,l,m,k->ls);
            if(y>m) res += query(x,y,m+1,r,k->rs);
            return res;
        }
    }
public:
    segment_tree_plus(int n) : n(n), root(nullptr) {}
    segment_tree_plus(const ranges::range auto& rg) : segment_tree_plus(rg.size())
    {
        auto it = rg.begin();
        build(0,n-1,root,it);
    }
    void add(int x,int y,const T& z) { add(x,y,z,0,n-1,root); }
    T query(int x,int y) { return query(x,y,0,n-1,root); }
};
