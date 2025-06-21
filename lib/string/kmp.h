auto prefix_function(const string& s)
{
    vector<size_t> nxt(s.length());
    for(size_t i=1,j=0;i<s.length();i++)
    {
        while(j>0&&s[j]!=s[i]) j = nxt[j-1];
        if(s[j]==s[i]) nxt[i] = ++j;
    }
    return nxt;
}
auto kmp(const string& match, const string& pattern, char split='#')
{
    vector<size_t> res;
    auto s = pattern+split+match;
    auto nxt = prefix_function(s);
    for(auto i=pattern.length()+1;i<s.length();i++)
        if(nxt[i]==pattern.length())
            res.push_back(i-(pattern.length()<<1));
    return res;
}
