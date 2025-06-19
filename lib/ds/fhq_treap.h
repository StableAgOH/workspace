template <typename Key, typename Cmp=less<Key>>
struct fhq_treap
{
    inline static mt19937 rng{random_device{}()};

    struct node { Key key; int l, r, pri, siz; };

    int root{0};
    vector<node> pool{1};

    void update(int x) { pool[x].siz = pool[pool[x].l].siz+pool[pool[x].r].siz+1; }
    int new_node(const Key& key)
    {
        pool.push_back({key, 0, 0, rng(), 1});
        return pool.size()-1;
    }

    int merge(int x, int y)
    {
        if(!x||!y) return x+y;
        if(pool[x].pri<pool[y].pri)
        {
            pool[x].r = merge(pool[x].r, y);
            update(x);
            return x;
        }
        else
        {
            pool[y].l = merge(x, pool[y].l);
            update(y);
            return y;
        }
    }
    template <typename SCmp=Cmp>
    pair<int, int> split_by_key(int x, const Key& key, SCmp cmp={})
    {
        if(!x) return {0, 0};
        if(cmp(pool[x].key, key))
        {
            auto [l, r] = split_by_key(pool[x].r, key, cmp);
            pool[x].r = l;
            update(x);
            return {x, r};
        }
        else
        {
            auto [l, r] = split_by_key(pool[x].l, key, cmp);
            pool[x].l = r;
            update(x);
            return {l, x};
        }
    }
    pair<int, int> split_by_size(int x, int s)
    {
        if(!x) return {0, 0};
        int ls = pool[pool[x].l].siz;
        if(ls>=s)
        {
            auto [l, r] = split_by_size(pool[x].l, s);
            pool[x].l = r;
            update(x);
            return {l, x};
        }
        else
        {
            auto [l, r] = split_by_size(pool[x].r, s-ls-1);
            pool[x].r = l;
            update(x);
            return {x, r};
        }
    }

    void insert(const Key& key)
    {
        auto [l, r] = split_by_key(root, key);
        root = merge(merge(l, new_node(key)), r);
    }
    void erase(const Key& key)
    {
        auto [l, r] = split_by_key(root, key);
        auto [rl, rr] = split_by_size(r, 1);
        root = merge(l, rr);
    }
    int order_of_key(const Key& key)
    {
        auto [l, r] = split_by_key(root, key);
        int ord = pool[l].siz;
        root = merge(l, r);
        return ord;
    }
    Key find_by_order(int ord)
    {
        auto [l, r] = split_by_size(root, ord);
        int x = r;
        while(pool[x].l) x = pool[x].l;
        Key k = pool[x].key;
        root = merge(l, r);
        return k;
    }
    Key predecessor(const Key& key)
    {
        auto [l, r] = split_by_key(root, key);
        int x = l;
        while(pool[x].r) x = pool[x].r;
        Key k = pool[x].key;
        root = merge(l, r);
        return k;
    }
    Key successor(const Key& key)
    {
        auto [l, r] = split_by_key(root, key, [](const Key& a, const Key& b) { return !Cmp()(b, a); });
        int x = r;
        while(pool[x].l) x = pool[x].l;
        Key k = pool[x].key;
        root = merge(l, r);
        return k;
    }
};
