vector<ll> pow9 = {1};
for(int i=1;i<=18;i++) pow9.push_back(pow9[i-1]*9);
// [1,x] 中数位不含有 o 的数字个数
auto count_digit_not_have = [&](ll x, int o)
{
    string s = to_string(x);
    int n = s.length();
    ll cnt = 0;
    for(int i=0;i<n;i++)
    {
        int d = s[i]-'0';
        if(!d) continue;
        if(d>o) cnt += pow9[n-i-1]*(d-1);
        else
        {
            cnt += pow9[n-i-1]*d;
            if(d==o)
            {
                cnt--;
                break;
            }
        }
    }
    return cnt;
};
