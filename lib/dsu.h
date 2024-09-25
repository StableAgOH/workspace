class dsu
{
private:
    vector<int> fa, siz;
    int find(int x) { return fa[x]==x?x:fa[x]=find(fa[x]); }
public:
    dsu(int n)
    {
        fa.resize(n);
        siz.assign(n,1);
        iota(fa.begin(), fa.end(), 0);
    }
    bool merge(int x,int y)
    {
        x=find(x), y=find(y);
        if(x==y) return false;
        fa[x] = y;
        siz[y] += siz[x];
        return true;
    }
    int operator[](int x) { return find(x); }
    int size(int x) { return this->siz[x]; }
};
