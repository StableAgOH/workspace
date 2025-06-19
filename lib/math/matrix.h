template <typename T, auto Op1=plus{}, auto Op2=multiplies{}>
class matrix
{
protected:
    size_t m_rows, m_cols;
    valarray<T> m_data;
public:
    matrix(size_t r, size_t c) : m_rows(r), m_cols(c), m_data(r*c) { assert(r>0&&c>0); }
    auto operator()(size_t r, size_t c) const { return m_data[r*m_cols+c]; }
    auto& operator()(size_t r, size_t c) { return m_data[r*m_cols+c]; }
    auto row(size_t r) const { return m_data[slice(r*m_cols, m_cols, 1)]; }
    auto col(size_t c) const { return m_data[slice(c, m_rows, m_cols)]; }
    auto rows() const { return m_rows; }
    auto cols() const { return m_cols; }
    auto& operator+=(const T& rhs) { m_data += rhs; return *this; }
    auto& operator+=(const matrix& rhs)
    {
        assert(m_rows==rhs.m_rows&&m_cols==rhs.m_cols);
        m_data += rhs.m_data;
        return *this;
    }
    auto operator+(const auto& rhs) const { return matrix(*this) += rhs; }
    auto& operator-=(const T& rhs) { m_data -= rhs; return *this; }
    auto& operator-=(const matrix& rhs)
    {
        assert(m_rows==rhs.m_rows&&m_cols==rhs.m_cols);
        m_data -= rhs.m_data;
        return *this;
    }
    auto operator-(const auto& rhs) const { return matrix(*this) -= rhs; }
    auto& operator*=(const T& rhs) { m_data *= rhs; return *this; }
    auto& operator*=(const matrix& rhs)
    {
        assert(m_cols==rhs.m_rows);
        matrix res(m_rows, rhs.m_cols);
        for(size_t i=0; i<m_rows; i++)
            for(size_t k=0; k<m_cols; k++)
                for(size_t j=0; j<rhs.m_cols; j++)
                    res(i, j) = Op1(res(i, j), Op2((*this)(i, k), rhs(k, j)));
        return *this = move(res);
    }
    auto operator*(const auto& rhs) const { return matrix(*this) *= rhs; }
};
template <typename T, auto Op1=plus{}, auto Op2=multiplies{}>
class square_matrix : public matrix<T, Op1, Op2>
{
    using super = matrix<T, Op1, Op2>;
    using super::m_data, super::m_rows, super::m_cols;
public:
    explicit square_matrix(size_t n) : super(n, n) {}
    auto diagonal() { return m_data[slice(0, m_rows, m_rows+1)]; }
    auto antidiagonal() { return m_data[slice(m_rows-1, m_rows, m_rows-1)]; }
    auto pow(integral auto k, square_matrix init)
    {
        auto a = *this;
        for(; k; k>>=1,a*=a) if(k&1) init *= a;
        return init;
    }
};
