__int128 abs(__int128 x) { return x<0?-x:x; }
__int128 gcd(__int128 a, __int128 b) { return b?gcd(b,a%b):a; }
__int128 lcm(__int128 a, __int128 b) { return a/gcd(a,b)*b; }
istream& operator>>(istream& is, __int128& x)
{
    string s;
    is>>s;
    x = 0;
    for(auto c : s)
    {
        if(c=='-') continue;
        x = x*10+c-'0';
    }
    if(s[0]=='-') x = -x;
    return is;
}
ostream& operator<<(ostream& os, __int128 x)
{
    if(x<0) os<<'-';
    if(x>9) os<<x/10;
    os<<int(abs(x)%10);
    return os;
}
