auto sin(const vector<mint>& f, size_t n)
{
    auto p=exp(scalar(cut(f, n), I), n), q=exp(scalar(cut(f, n), -I), n);
    return scalar(sub(p, q), I2I);
}
auto cos(const vector<mint>& f, size_t n)
{
    auto p=exp(scalar(cut(f, n), I), n), q=exp(scalar(cut(f, n), -I), n);
    return scalar(add(p, q), I2);
}
auto tan(const vector<mint>& f, size_t n)
{
    return cut(conv(sin(f, n), inv(cos(f, n), n)), n);
}
auto asin(const vector<mint>& f, size_t n)
{
    auto t = sub({mint(1)}, conv(cut(f, n), cut(f, n)));
    return cut(integ(conv(deriv(f), inv(sqrt(t, n), n))), n);
}
auto acos(const vector<mint>& f, size_t n)
{
    auto g = asin(f, n);
    for(auto& x : g) x = -x;
    return g;
}
auto atan(const vector<mint>& f, size_t n)
{
    auto t = add({mint(1)}, conv(cut(f, n), cut(f, n)));
    return cut(integ(conv(deriv(f), inv(t, n))), n);
}
