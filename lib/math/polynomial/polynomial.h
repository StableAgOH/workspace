template <typename T>
class polynomial
{
public:
    polynomial() : n(0), coef(1) {}
    polynomial(int n) : n(n), coef(n+1) {}
    polynomial(initializer_list<T> l) : n(l.size()-1), coef(l) {}
    polynomial(const valarray<T>& coef) : n(coef.size()-1), coef(coef) {}
    operator valarray<T>() const { return coef; }
    auto operator[](int i) const { return coef[i]; }
    auto& operator[](int i) { return coef[i]; }
    auto& operator+=(const polynomial& rhs)
    {
        coef.resize((n=max(n,rhs.n))+1);
        coef += rhs.coef;
        return *this;
    }
    auto operator+(const polynomial& rhs) const { return polynomial(*this) += rhs; }
    auto& operator-=(const polynomial& rhs)
    {
        coef.resize((n=max(n,rhs.n))+1);
        coef -= rhs.coef;
        return *this;
    }
    auto operator-(const polynomial& rhs) const { return polynomial(*this) += rhs; }
    friend istream& operator>>(istream& is, polynomial& p)
    {
        for(int i=0;i<=p.n;i++) is>>p[i];
        return is;
    }
    friend ostream& operator<<(ostream& os, const polynomial& p)
    {
        for(int i=0;i<=p.n;i++) os<<p[i]<<' ';
        return os;
    }
    int degree() const { return n; }
private:
    int n;
    valarray<T> coef;
};
