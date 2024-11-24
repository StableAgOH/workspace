class dsu
{
    vector<int> fa;
    int find(int x) { return fa[x]==x?x:fa[x]=find(fa[x]); }
public:
    dsu(int n) : fa(n) { iota(fa.begin(), fa.end(), 0); }
    bool merge(int x,int y)
    {
        x=find(x), y=find(y);
        if(x==y) return false;
        fa[x] = y;
        return true;
    }
    int operator[](int x) { return find(x); }
};
