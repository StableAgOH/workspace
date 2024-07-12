class Fraction
{
private:
    __int128_t numerator, denominator;

    static __int128_t gcd(const __int128_t a, const __int128_t b)
    {
        return b ? gcd(b, a % b) : a;
    }
    void reduct()
    {
        auto g = gcd(this->numerator, this->denominator);
        this->numerator /= g;
        this->denominator /= g;
    }

public:
    Fraction() : numerator(0), denominator(1)
    {
    }
    Fraction(const __int128_t num) : numerator(num), denominator(1)
    {
    }
    Fraction(const __int128_t numerator, const __int128_t denominator)
        : numerator(((denominator > 0) ? 1 : -1) * numerator), denominator(denominator > 0 ? denominator : -denominator)
    {
        reduct();
    }
    auto get_numerator() const
    {
        return numerator;
    }
    auto get_denominator() const
    {
        return denominator;
    }
    auto operator-() const
    {
        return Fraction(-numerator, denominator);
    }
    auto operator+=(const Fraction& f)
    {
        auto g = gcd(denominator, f.denominator);
        numerator = f.denominator / g * numerator + denominator / g * f.numerator;
        denominator = denominator / g * f.denominator;
        reduct();
        return *this;
    }
    auto operator-=(const Fraction& f)
    {
        auto g = gcd(denominator, f.denominator);
        numerator = f.denominator / g * numerator - denominator / g * f.numerator;
        denominator = denominator / g * f.denominator;
        reduct();
        return *this;
    }
    auto operator*=(const Fraction& f)
    {
        auto g1 = gcd(numerator, f.denominator);
        auto g2 = gcd(denominator, f.numerator);
        numerator = numerator / g1 * (f.numerator / g2);
        denominator = denominator / g2 * (f.denominator / g1);
        return *this;
    }
    auto operator/=(const Fraction& f)
    {
        auto g1 = gcd(numerator, f.numerator);
        auto g2 = gcd(denominator, f.denominator);
        numerator = numerator / g1 * (f.denominator / g2);
        denominator = denominator / g2 * (f.numerator / g1);
        return *this;
    }
    auto toInteger() const
    {
        return numerator / denominator;
    }
    auto toDouble() const
    {
        return double(numerator) / denominator;
    }
    auto toString() const
    {
        std::stack<char> st;
        std::string ret;
        auto f = [&](__int128_t x) {
            while(x)
            {
                st.push(x % 10 + '0');
                x /= 10;
            }
            while(!st.empty())
            {
                ret.push_back(st.top());
                st.pop();
            }
            if(ret.empty()) ret.push_back('0');
        };
        f(numerator);
        ret.push_back(' ');
        f(denominator);
        return ret;
    }
    friend Fraction operator+(const Fraction&, const Fraction&);
    friend Fraction operator-(const Fraction&, const Fraction&);
    friend Fraction operator*(const Fraction&, const Fraction&);
    friend Fraction operator/(const Fraction&, const Fraction&);
    friend bool operator<(const Fraction&, const Fraction&);
    friend bool operator>(const Fraction&, const Fraction&);
    friend bool operator==(const Fraction&, const Fraction&);
    friend bool operator!=(const Fraction&, const Fraction&);
};

Fraction operator+(const Fraction& f1, const Fraction& f2)
{
    auto g = Fraction::gcd(f1.denominator, f2.denominator);
    return Fraction(f2.denominator / g * f1.numerator + f1.denominator / g * f2.numerator,
                    f1.denominator / g * f2.denominator);
}
Fraction operator-(const Fraction& f1, const Fraction& f2)
{
    auto g = Fraction::gcd(f1.denominator, f2.denominator);
    return Fraction(f2.denominator / g * f1.numerator - f1.denominator / g * f2.numerator,
                    f1.denominator / g * f2.denominator);
}
Fraction operator*(const Fraction& f1, const Fraction& f2)
{
    auto g1 = Fraction::gcd(f1.numerator, f2.denominator);
    auto g2 = Fraction::gcd(f1.denominator, f2.numerator);
    return Fraction(f1.numerator / g1 * (f2.numerator / g2), f1.denominator / g2 * (f2.denominator / g1));
}
Fraction operator/(const Fraction& f1, const Fraction& f2)
{
    auto g1 = Fraction::gcd(f1.numerator, f2.numerator);
    auto g2 = Fraction::gcd(f1.denominator, f2.denominator);
    return Fraction(f1.numerator / g1 * (f2.denominator / g2), f1.denominator / g2 * (f2.numerator / g1));
}
bool operator<(const Fraction& f1, const Fraction& f2)
{
    return (f1 - f2).numerator < 0;
}
bool operator>(const Fraction& f1, const Fraction& f2)
{
    return (f1 - f2).numerator > 0;
}
bool operator==(const Fraction& f1, const Fraction& f2)
{
    return f1.numerator == f2.numerator && f1.denominator == f2.denominator;
}
bool operator!=(const Fraction& f1, const Fraction& f2)
{
    return !(f1 == f2);
}
