class dsu
{
private:
    vector<int> fa, siz;
    int find(int x) { return fa[x]==x?x:fa[x]=find(fa[x]); }
public:
    dsu(int n) : fa(ranges::to<vector>(views::iota(0,n))), siz(n,1) {}
    bool merge(int x,int y)
    {
        x=find(x), y=find(y);
        if(x==y) return false;
        fa[x] = y;
        siz[y] += siz[x];
        return true;
    }
    int operator[](int x) { return find(x); }
    int size(int x) { return siz[x]; }
};
