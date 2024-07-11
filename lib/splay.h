template <typename T, int Size>
struct splay
{
    struct Node
    {
        int ch[2], fa, siz;
        T val;
    };
    int root;
    vector<Node> t;
    splay() { root=0; t.resize(1); t.reserve(Size); }
    void update(int x) { t[x].siz = t[t[x].ch[0]].siz+t[t[x].ch[1]].siz+1; }
    int ident(int x, int f) { return t[f].ch[1]==x; }
    void connect(int x,int f,int s) { t[f].ch[s]=x; t[x].fa=f; }
    void rotate(int x)
    {
        int f=t[x].fa, ff=t[f].fa, k=ident(x,f);
        connect(t[x].ch[k^1], f, k);
        connect(x, ff, ident(f,ff));
        connect(f, x, k^1);
        update(f); update(x);
    }
    void splaying(int x,int top)
    {
        if(!top) root = x;
        while(t[x].fa!=top)
        {
            int f=t[x].fa, ff=t[f].fa;
            if(ff!=top) ident(x,f)^ident(f,ff)?rotate(x):rotate(f);
            rotate(x);
        }
    }
    int newnode(T x,int fa)
    {
        t.emplace_back();
        t.back().val = x;
        t.back().fa = fa;
        t.back().siz = 1;
        return t.size()-1;
    }
    void insert(const T& x, int& k, int fa)
    {
        if(!k)
        {
            k = newnode(x, fa);
            splaying(k, 0);
        }
        else if(x<t[k].val) insert(x, t[k].ch[0], k);
        else insert(x, t[k].ch[1], k);
    }
    void insert(const T& x) { insert(x, root, 0);}
    void erase_node(int k)
    {
        splaying(k, 0);
        if(t[k].ch[1])
        {
            int p=t[k].ch[1];
            while(t[p].ch[0]) p = t[p].ch[0];
            splaying(p, k);
            connect(t[k].ch[0], p, 0);
            root = p;
            t[root].fa = 0;
            update(root);
        }
        else
        {
            root = t[k].ch[0];
            t[root].fa = 0;
        }
    }
    void erase(const T& x, int& k)
    {
        if(x==t[k].val) erase_node(k);
        else if(x<t[k].val) erase(x, t[k].ch[0]);
        else erase(x, t[k].ch[1]);
    }
    void erase(const T& x) { erase(x, root); }
    int get_rank(T x)
    {
        int u=root, rank=1, p=0;
        while(u)
        {
            if (x<=t[u].val)
            {
                p = u;
                u = t[u].ch[0];
            }
            else
            {
                rank += t[t[u].ch[0]].siz+1;
                u = t[u].ch[1];
            }
        }
        if(p) splaying(p, 0);
        return rank;
    }
    T get_val(int rank)
    {
        int u = root;
        while (u)
        {
            if(t[t[u].ch[0]].siz + 1 == rank)
            {
                splaying(u, 0);
                break;
            }
            else if(t[t[u].ch[0]].siz >= rank) u = t[u].ch[0];
            else
            {
                rank -= t[t[u].ch[0]].siz+1;
                u = t[u].ch[1];
            }
        }
        return t[u].val;
    }
    T pre(T x) { return get_val(get_rank(x)-1); }
    T nxt(T x) { return get_val(get_rank(x+1)); }
};
