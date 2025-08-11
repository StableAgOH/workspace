class dsu
{
    vector<int> data;
public:
    explicit dsu(int n) : data(n, -1) {}
    int operator[](int x) { return data[x]<0?x:data[x]=(*this)[data[x]]; }
    int unite(int x, int y)
    {
        x=(*this)[x], y=(*this)[y];
        if(x==y) return x;
        if(-data[x]<-data[y]) swap(x, y);
        data[x] += data[y];
        data[y] = x;
        return x;
    }
    int size(int x) { return -data[(*this)[x]]; }
    auto groups()
    {
        vector<vector<int>> result(data.size());
        for(size_t i=0;i<data.size();i++) result[(*this)[i]].push_back(i);
        erase_if(result, &vector<int>::empty);
        return result;
    }
};
