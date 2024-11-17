template <integral T>
class fhq_treap
{
    mt19937 rnd;
    struct Node { int l,r,key,siz; T val; };
    int root;
    vector<Node> t;
    int new_node(T val)
    {
        t.emplace_back(0,0,rnd(),1,val);
        return t.size()-1;
    }
    void update(int x) { t[x].siz = t[t[x].l].siz+t[t[x].r].siz+1; }
    int merge(int x, int y)
    {
        if(!x||!y) return x+y;
        if(t[x].key>t[y].key)
        {
            t[x].r = merge(t[x].r, y);
            update(x);
            return x;
        }
        else
        {
            t[y].l = merge(x, t[y].l);
            update(y);
            return y;
        }
    }
    void split_by_val(int x, T val, int& u, int& v)
    {
        if(!x) { u=v=0; return; }
        if(t[x].val<=val)
        {
            u = x;
            split_by_val(t[x].r, val, t[x].r, v);
        }
        else
        {
            v = x;
            split_by_val(t[x].l, val, u, t[x].l);
        }
        update(x);
    }
public:
    fhq_treap() : rnd(chrono::steady_clock::now().time_since_epoch().count()), root(0), t(1) {}
    void insert(T val)
    {
        int u,v;
        split_by_val(root, val, u, v);
        root = merge(merge(u, new_node(val)), v);
    }
    void erase(T val)
    {
        int u,v,w;
        split_by_val(root, val-1, u, v);
        split_by_val(v, val, v, w);
        v = merge(t[v].l, t[v].r);
        root = merge(merge(u, v), w);
    }
    int order_of_key(T val)
    {
        int u,v;
        split_by_val(root, val-1, u, v);
        int ret = t[u].siz+1;
        root = merge(u, v);
        return ret;
    }
    T find_by_order(int rank)
    {
        int x = root;
        while(x)
        {
            if(t[t[x].l].siz+1==rank) break;
            else if(t[t[x].l].siz>=rank) x = t[x].l;
            else 
            {
                rank -= t[t[x].l].siz+1;
                x = t[x].r;
            }
        }
        return t[x].val;
    }
    T pre(T val)
    {
        int u,v;
        split_by_val(root, val-1, u, v);
        int x = u;
        while(t[x].r) x = t[x].r;
        root = merge(u, v);
        return t[x].val;
    }
    T nxt(T val)
    {
        int u,v;
        split_by_val(root, val, u, v);
        int x = v;
        while(t[x].l) x = t[x].l;
        root = merge(u, v);
        return t[x].val;
    }
};
