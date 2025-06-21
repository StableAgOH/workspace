class rollback_dsu
{
    vector<int> data;
    stack<pair<int, int>> history;
public:
    explicit rollback_dsu(int n) : data(n, -1) {}
    int operator()(int x) const { return data[x]<0?x:(*this)(data[x]); }
    int unite(int x, int y)
    {
        x=(*this)(x), y=(*this)(y);
        if(x==y)
        {
            history.emplace(-1, 0);
            return x;
        }
        if(-data[x]<-data[y]) swap(x, y);
        history.emplace(x, data[x]);
        history.emplace(y, data[y]);
        data[x] += data[y];
        data[y] = x;
        return x;
    }
    int size(int x) { return -data[(*this)(x)]; }
    int snapshot() const { return history.size(); }
    void rollback(int snap)
    {
        while((int)history.size()>snap)
        {
            auto [p, x] = history.top();
            history.pop();
            if(p==-1) continue;
            data[p] = x;
        }
    }
    auto groups()
    {
        vector<vector<int>> result(data.size());
        for(size_t i=0;i<data.size();i++) result[(*this)(i)].push_back(i);
        return result;
    }
};
