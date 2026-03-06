generator<const vector<int>&> combinations(int n, int m)
{
    if(m<0||m>n) co_return;
    vector<int> o(m);
    ranges::iota(o, 0);
    while(true)
    {
        co_yield o;
        int i = m-1;
        while(i>=0&&o[i]==i+n-m) i--;
        if(i<0) break;
        o[i]++;
        for(int j=i+1;j<m;j++) o[j] = o[j-1]+1;
    }
}
generator<const vector<int>&> permutations(int n, int m)
{
    if(m<0||m>n) co_return;
    for(const auto& comb : combinations(n, m))
    {
        auto cur = comb;
        do co_yield cur;
        while(ranges::next_permutation(cur).found);
    }
}
