template <typename T>
struct max_f
{
    constexpr T operator()(const T& x, const T& y) const { return max(x,y); }
};
template <typename T>
struct min_f
{
    constexpr T operator()(const T& x, const T& y) const { return min(x,y); }
};
template <typename T>
struct gcd_f
{
    constexpr T operator()(const T& x, const T& y) const { return gcd(x,y); }
};
