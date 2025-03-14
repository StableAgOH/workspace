template <typename T>
class polynomial
{
public:
    polynomial() : coef(1) {}
    explicit polynomial(size_t deg) : coef(deg+1) {}
    polynomial(initializer_list<T> il) : coef(il) {}
    polynomial(const valarray<T>& v) : coef(v) {}
    polynomial(valarray<T>&& v) : coef(move(v)) {}
    operator valarray<T>() const { return coef; }
    auto operator[](size_t i) const { return coef[i]; }
    auto& operator[](size_t i) { return coef[i]; }
    auto& operator+=(const polynomial& rhs)
    {
        coef.redegree(max(degree(), rhs.degree()));
        for(size_t i=0;i<=rhs.degree();i++) coef[i] += rhs[i];
        return *this;
    }
    auto& operator-=(const polynomial& rhs)
    {
        coef.redegree(max(degree(), rhs.degree()));
        for(size_t i=0;i<=rhs.degree();i++) coef[i] -= rhs[i];
        return *this;
    }
    auto operator+(const polynomial& rhs) const { return polynomial(*this) += rhs; }
    auto operator-(const polynomial& rhs) const { return polynomial(*this) -= rhs; }
    friend istream& operator>>(istream& is, polynomial& p)
    {
        for(size_t i=0;i<=p.degree();i++) is>>p[i];
        return is;
    }
    friend ostream& operator<<(ostream& os, const polynomial& p)
    {
        for(size_t i=0;i<=p.degree();i++) os<<p[i]<<' ';
        return os;
    }
    auto min() const { return coef.min(); }
    auto max() const { return coef.max(); }
    auto sum() const { return coef.sum(); }
    auto degree() const { return coef.size()-1; }
    auto redegree(size_t deg) { coef.resize(deg+1); }
private:
    valarray<T> coef;
};
