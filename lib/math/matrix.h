template <typename T>
class matrix
{
protected:
    size_t m_rows, m_cols;
    valarray<T> m_data;
public:
    matrix(size_t rows, size_t cols) : m_rows(rows), m_cols(cols), m_data(rows*cols) { assert(rows>0&&cols>0); }
    auto rows() const { return m_rows; }
    auto cols() const { return m_cols; }
    auto& operator()(size_t r, size_t c) { return m_data[r*m_cols+c]; }
    auto operator()(size_t r, size_t c) const { return m_data[r*m_cols+c]; }
    auto row(size_t r) { return m_data[slice(r*m_cols, m_cols, 1)]; }
    auto col(size_t c) { return m_data[slice(c, m_rows, m_cols)]; }
    auto operator+=(const T& rhs)
    {
        m_data += rhs;
        return *this;
    }
    auto operator+=(const matrix& rhs)
    {
        assert(m_rows==rhs.m_rows&&m_cols==rhs.m_cols);
        m_data += rhs.m_data;
        return *this;
    }
    auto operator+(const auto& rhs) const { return matrix(*this) += rhs; }
    auto operator-=(const T& rhs)
    {
        m_data -= rhs;
        return *this;
    }
    auto operator-=(const matrix& rhs)
    {
        assert(m_rows==rhs.m_rows&&m_cols==rhs.m_cols);
        m_data -= rhs.m_data;
        return *this;
    }
    auto operator-(const auto& rhs) const { return matrix(*this) -= rhs; }
    auto operator*=(const T& rhs) { m_data *= rhs; return *this; }
    auto operator*=(const matrix& rhs) { return *this = *this*rhs; }
    auto operator*(const T& rhs) const { return matrix(*this) *= rhs; }
    auto operator*(const matrix& rhs) const
    {
        assert(m_cols==rhs.m_rows);
        matrix res(m_rows, rhs.m_cols);
        for(size_t i=0;i<m_rows;i++)
            for(size_t k=0;k<m_cols;k++)
                for(size_t j=0;j<rhs.m_cols;j++)
                    res(i, j) += (*this)(i, k)*rhs(k, j);
        return res;
    }
    friend auto& operator>>(istream& is, matrix& rhs)
    {
        for(size_t i=0;i<rhs.m_rows;i++)
            for(size_t j=0;j<rhs.m_cols;j++)
                is>>rhs(i,j);
        return is;
    }
    friend auto& operator<<(ostream& os, const matrix& rhs)
    {
        for(size_t i=0;i<rhs.m_rows-1;i++)
            for(size_t j=0;j<rhs.m_cols;j++)
                os<<rhs(i,j)<<" \n"[j==rhs.m_cols-1];
        os<<rhs(rhs.m_rows-1, 0);
        for(size_t j=1;j<rhs.m_cols;j++) os<<' '<<rhs(rhs.m_rows-1, j);
        return os;
    }
};
template <typename T>
class square_matrix : public matrix<T>
{
    using matrix<T>::m_rows;
    using matrix<T>::m_data;
public:
    static auto identity(size_t n) { square_matrix E(n); E.diagonal() = 1; return E; }
    explicit square_matrix(size_t n) : matrix<T>(n, n) {}
    auto diagonal() { return m_data[slice(0, m_rows, m_rows+1)]; }
    auto antidiagonal() { return m_data[slice(m_rows-1, m_rows, m_rows-1)]; }
    auto pow(integral auto k) const
    {
        square_matrix a=*this, res=identity(m_rows);
        for(;k;k>>=1,a*=a) if(k&1) res *= a;
        return res;
    }
};
