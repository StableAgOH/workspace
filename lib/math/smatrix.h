template <typename T>
concept semiring = requires(T a, T b) {
    typename T::value_type;
    { T::zero() } -> same_as<typename T::value_type>;
    { T::add(a, b) } -> same_as<typename T::value_type>;
    { T::one() } -> same_as<typename T::value_type>;
    { T::mul(a, b) } -> same_as<typename T::value_type>;
};
template <typename T>
struct semiring_wrapper
{
    using value_type = T;
    static T zero() { return T(0); }
    static T add(const T& a, const T& b) { return a+b; }
    static T one() { return T(1); }
    static T mul(const T& a, const T& b) { return a*b; }
};
template <semiring T>
class smatrix
{
public:
    using value_type = typename T::value_type;
private:
    size_t n;
    vector<value_type> data;
public:
    static smatrix identity(size_t n)
    {
        smatrix res(n, T::zero());
        for(size_t i=0;i<n;i++) res(i, i) = T::one();
        return res;
    }
    smatrix() = default;
    explicit smatrix(size_t n, const value_type& init=T::zero())
        : n(n), data(n*n, init) {}
    auto size() const { return n; }
    decltype(auto) operator()(this auto&& self, size_t i, size_t j)
    {
        return self.data[i*self.n+j];
    }
    friend auto operator*(const smatrix& a, const smatrix& b)
    {
        assert(a.n==b.n);
        smatrix c(a.n, T::zero());
        for(size_t i=0;i<a.n;i++)
            for(size_t k=0;k<a.n;k++)
                for(size_t j=0;j<a.n;j++)
                    c(i, j) = T::add(c(i, j), T::mul(a(i, k), b(k, j)));
        return c;
    }
    auto& operator*=(const smatrix& rhs) { return *this = *this*rhs; }
    auto pow(uint64_t k) const
    {
        auto base=*this, res=identity(n);
        for(;k;k>>=1,base*=base)
            if(k&1) res *= base;
        return res;
    }
};
