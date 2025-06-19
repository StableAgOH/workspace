template <typename Key, typename Cmp=less<Key>>
struct splay
{
    struct node { Key key; int ch[2], p, siz; };

    Cmp cmp{};
    int root{0};
    vector<node> pool{1};

    void update(int x) { pool[x].siz = pool[pool[x].ch[0]].siz+pool[pool[x].ch[1]].siz+1; }
    int new_node(const Key& key)
    {
        pool.push_back({key, {0, 0}, 0, 1});
        return pool.size()-1;
    }

    int dir(int x, int p) const { return pool[p].ch[1]==x; }
    void link(int x, int p, int d)
    {
        pool[p].ch[d] = x;
        if(x) pool[x].p = p;
    }
    void rotate(int x)
    {
        int p=pool[x].p, pp=pool[p].p, d=dir(x, p);
        link(pool[x].ch[d^1], p, d), link(x, pp, dir(p, pp)), link(p, x, d^1);
        update(p), update(x);
    }
    void splaying(int x, int top=0)
    {
        if(!top) root = x;
        while(pool[x].p!=top)
        {
            int p=pool[x].p, pp=pool[p].p;
            if(pp!=top) dir(x, p)^dir(p, pp)?rotate(x):rotate(p);
            rotate(x);
        }
    }

    void insert(const Key& key)
    {
        int nn = new_node(key);
        if(!root) root = nn;
        else
        {
            int x=root, p=0, d=0;
            while(x)
            {
                p = x;
                d = !cmp(key, pool[x].key);
                x = pool[x].ch[d];
            }
            link(nn, p, d);
            splaying(nn);
        }
    }
    void erase(const Key& key)
    {
        int x = root;
        while(x&&pool[x].key!=key) x = pool[x].ch[!cmp(key, pool[x].key)];
        if(!x) return;
        splaying(x);
        int y=pool[x].ch[0], z=pool[x].ch[1];
        pool[y].p = pool[z].p = 0;
        if(!y) root = z;
        else
        {
            root = y;
            while(pool[y].ch[1]) y = pool[y].ch[1];
            splaying(y);
            link(z, root, 1);
            update(root);
        }
    }
    int order_of_key(const Key& key)
    {
        int x=root, p=0, ord=0;
        while(x)
        {
            p = x;
            if(cmp(pool[x].key, key))
            {
                ord += pool[pool[x].ch[0]].siz+1;
                x = pool[x].ch[1];
            }
            else x = pool[x].ch[0];
        }
        if(p) splaying(p);
        return ord;
    }
    Key find_by_order(int ord)
    {
        int x = root;
        while(x)
        {
            int ls = pool[pool[x].ch[0]].siz;
            if(ord==ls) break;
            if(ord<ls) x = pool[x].ch[0];
            else
            {
                ord -= ls+1;
                x = pool[x].ch[1];
            }
        }
        splaying(x);
        return pool[x].key;
    }
    Key predecessor(const Key& key)
    {
        int x=root, y=0;
        while(x)
        {
            if(cmp(pool[x].key, key))
            {
                y = x;
                x = pool[x].ch[1];
            }
            else x = pool[x].ch[0];
        }
        splaying(y);
        return pool[y].key;
    }
    Key successor(const Key& key)
    {
        int x=root, y=0;
        while(x)
        {
            if(cmp(key, pool[x].key))
            {
                y = x;
                x = pool[x].ch[0];
            }
            else x = pool[x].ch[1];
        }
        splaying(y);
        return pool[y].key;
    }
};
