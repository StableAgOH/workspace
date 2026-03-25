class rect_union
{
    struct line { int x, y1, y2, type; };
    struct node { int cnt; ll len; };
    vector<int> ys;
    vector<line> ls;
    vector<node> sgt;
    void update(int k, int l, int r, int ql, int qr, int x)
    {
        if(ql<=l&&qr>=r) sgt[k].cnt += x;
        else
        {
            int mid = (l+r)>>1;
            if(ql<mid) update(k<<1, l, mid, ql, qr, x);
            if(qr>mid) update(k<<1|1, mid, r, ql, qr, x);
        }
        if(sgt[k].cnt>0) sgt[k].len = ys[r]-ys[l];
        else if(r-l>1) sgt[k].len = sgt[k<<1].len+sgt[k<<1|1].len;
        else sgt[k].len = 0;
    }
public:
    void add_rect(int x1, int y1, int x2, int y2)
    {
        ys.push_back(y1);
        ls.push_back({x1, y1, y2, 1});
        ys.push_back(y2);
        ls.push_back({x2, y1, y2, -1});
    }
    ll operator()()
    {
        if(ys.empty()) return 0;
        sort(ys.begin(), ys.end());
        ys.erase(unique(ys.begin(), ys.end()), ys.end());
        auto id = [&](int x) { return lower_bound(ys.begin(), ys.end(), x)-ys.begin(); };
        sort(ls.begin(), ls.end(), [](const line& a, const line& b) { return a.x<b.x; });
        int m = ys.size();
        sgt.resize(m<<2);
        ll ans = 0;
        for(size_t i=0;i<ls.size()-1;i++)
        {
            auto [x, y1, y2, type] = ls[i];
            update(1, 0, m-1, id(y1), id(y2), type);
            ans += (ll)sgt[1].len*(ls[i+1].x-x);
        }
        return ans;
    }
};
