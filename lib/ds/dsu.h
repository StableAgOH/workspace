template <bool KeepMergeOrder=false>
class dsu
{
    vector<int> data;
public:
    explicit dsu(int n) : data(n, -1) {}
    int leader(int x) { return data[x]<0?x:data[x]=leader(data[x]); }
    int merge(int x, int y)
    {
        x=leader(x), y=leader(y);
        if(x==y) return x;
        if constexpr (!KeepMergeOrder)
            if(-data[x]<-data[y])
                swap(x, y);
        data[x] += data[y];
        data[y] = x;
        return x;
    }
    bool same(int x, int y) { return leader(x)==leader(y); }
    size_t size(int x) { return -data[leader(x)]; }
    auto groups()
    {
        vector<vector<int>> result(data.size());
        for(size_t i=0;i<data.size();i++) result[leader(i)].push_back(i);
        return result;
    }
};
