template <size_t S=26, char F='a'>
class trie
{
private:
    vector<array<size_t, S>> nxt;
    vector<bool> end;
public:
    void insert(const string_view& s)
    {
        assert(all_of(s.begin(), s.end(), [](char c) { return c>=F; }));
        size_t p = 0;
        for(auto c : s)
        {
            size_t x = c-F;
            if(p>=nxt.size()) nxt.emplace_back();
            if(!nxt[p][x]) nxt[p][x] = nxt.size();
            p = nxt[p][x];
        }
        if(p>=end.size()) end.resize(p+1);
        end[p] = true;
    }
    bool find(const string_view& s)
    {
        assert(all_of(s.begin(), s.end(), [](char c) { return c>=F; }));
        size_t p = 0;
        for(auto c : s)
        {
            size_t x = c-F;
            if(!nxt[p][x]) return false;
            p = nxt[p][x];
        }
        return end[p];
    }
};