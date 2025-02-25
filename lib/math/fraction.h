template <typename T>
class fraction
{
    T x, y;
    void reduct()
    {
        auto g = gcd(x, y);
        x /= g;
        y /= g;
    }
public:
    fraction(): x(0), y(1) {}
    fraction(const auto& x) : x(x), y(1) {}
    fraction(const T& x, const T& y) : x(y>0?x:-x), y(abs(y)) { reduct(); }
    template <typename U>
    explicit operator U() const { return U(x)/y; }
    auto numerator() const { return x; }
    auto denominator() const { return y; }
    auto operator<=>(const fraction& rhs) const { return x*rhs.y<=>rhs.x*y; }
    auto operator==(const fraction& rhs) const { return x*rhs.y==rhs.x*y; }
    auto operator-() const { return fraction(-x, y); }
    auto& operator+=(const fraction& rhs) { return *this = fraction(x*rhs.y+rhs.x*y, y*rhs.y); }
    auto& operator-=(const fraction& rhs) { return *this = fraction(x*rhs.y-rhs.x*y, y*rhs.y); }
    auto& operator*=(const fraction& rhs) { return *this = fraction(x*rhs.x, y*rhs.y); }
    auto& operator/=(const fraction& rhs) { return *this = fraction(x*rhs.y, y*rhs.x); }
    friend auto operator+(fraction lhs, const fraction& rhs) { return lhs += rhs; }
    friend auto operator-(fraction lhs, const fraction& rhs) { return lhs -= rhs; }
    friend auto operator*(fraction lhs, const fraction& rhs) { return lhs *= rhs; }
    friend auto operator/(fraction lhs, const fraction& rhs) { return lhs /= rhs; }
    friend auto& operator>>(istream& is, fraction& rhs) { is>>rhs.x>>rhs.y; rhs.reduct(); return is; }
    friend auto& operator<<(ostream& os, const fraction& rhs) { return os<<rhs.x<<'/'<<rhs.y; }
};
