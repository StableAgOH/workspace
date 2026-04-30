template <integral T>
array<T, 3> exgcd(T a, T b) // ax + by = gcd(a, b)
{
    T x0=1, x1=0, y0=0, y1=1;
    while(b!=0)
    {
        T q = a/b;
        a = exchange(b, a%b);
        x0 = exchange(x1, x0-q*x1);
        y0 = exchange(y1, y0-q*y1);
    }
    return {a, x0, y0}; // <gcd, x, y>
}
template <integral T>
optional<array<T, 3>> lieu(T a, T b, T c) // ax + by = c
{
    auto [d, x, y] = exgcd(a, b);
    if(c%d!=0) return nullopt;
    T k = c/d;
    return array<T, 3>{d, x*k, y*k}; // <gcd, x, y>
}
template <integral T>
optional<T> inv(T a, T p) // a^-1 mod p
{
    auto [d, x, y] = exgcd(a, p);
    if(d!=1) return nullopt;
    return (x%p+p)%p;
}
