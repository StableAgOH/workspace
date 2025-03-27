template <bool KeepMergeOrder=false>
class dsu
{
public:
    explicit dsu(int n) : n(n), data(n, -1) {}
    int leader(int x) { return data[x]<0?x:data[x]=leader(data[x]); }
    int merge(int x, int y)
    {
        x = leader(x);
        y = leader(y);
        if(x==y) return x;
        if constexpr (!KeepMergeOrder)
            if(-data[x]<-data[y])
                swap(x,y);
        data[x] += data[y];
        data[y] = x;
        return x;
    }
    bool same(int x, int y) { return leader(x)==leader(y); }
    int size(int x) { return -data[leader(x)]; }
    auto groups()
    {
        vector<int> leader_buf(n), group_size(n);
        for(int i=0;i<n;i++)
        {
            leader_buf[i] = leader(i);
            group_size[leader_buf[i]]++;
        }
        vector<vector<int>> result(n);
        for(int i=0;i<n;i++) result[leader_buf[i]].push_back(i);
        erase_if(result, [&](const auto& v) { return v.empty(); });
        return result;
    }
private:
    int n;
    vector<int> data;
};
