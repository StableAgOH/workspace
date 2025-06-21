template <typename T>
struct polynomial : valarray<T>
{
    using valarray<T>::operator[];
    using valarray<T>::min;
    using valarray<T>::max;
    polynomial() : valarray<T>(1) {}
    explicit polynomial(size_t deg) : valarray<T>(deg+1) {}
    polynomial(const valarray<T>& v) : valarray<T>(v) {}
    polynomial(valarray<T>&& v) : valarray<T>(move(v)) {}
    template <typename U=T>
    auto operator()(T x, U init=T{}) const
    {
        for(int i=degree();i>=0;i--) init = init*x+(*this)[i];
        return init;
    }
    auto& operator+=(const polynomial& rhs)
    {
        redegree(max(degree(), rhs.degree()));
        for(size_t i=0;i<=rhs.degree();i++) (*this)[i] += rhs[i];
        return *this;
    }
    auto& operator-=(const polynomial& rhs)
    {
        redegree(max(degree(), rhs.degree()));
        for(size_t i=0;i<=rhs.degree();i++) (*this)[i] -= rhs[i];
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
    auto degree() const { return valarray<T>::size()-1; }
    auto redegree(size_t deg) { valarray<T>::resize(deg+1); }
};
