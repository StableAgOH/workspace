template <typename T>
class odt
{
    int n;
    map<int, T> data;
public:
    explicit odt(int n) : n(n) { data[-1] = {}; }
    void split(int x) { data[x] = prev(data.upper_bound(x))->second; }
    void assign(int l, int r, T x)
    {
        split(l), split(r+1);
        auto it = data.find(l);
        while(it->first!=r+1) it = data.erase(it);
        data[l] = x;
    }
    void apply(int l, int r, auto&& f)
    {
        split(l), split(r);
        for(auto it=data.find(l);it->first!=r;++it) f(it->second);
    }
};
