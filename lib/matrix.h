template <typename T>
class matrix
{
public:
    size_t rows, cols;
protected:
    valarray<T> data;
public:
    matrix(size_t rows, size_t cols) : rows(rows), cols(cols), data(rows*cols) {}
    auto& operator()(size_t r, size_t c) { return data[r*cols+c]; }
    auto operator()(size_t r, size_t c) const { return data[r*cols+c]; }
    auto row(size_t r) { return data[slice(r*cols, cols, 1)]; }
    auto col(size_t c) { return data[slice(c, rows, cols)]; }
    auto operator+(const auto& rhs) const { return matrix(*this) += rhs; }
    auto operator+=(const T& rhs) { data += rhs; return *this; }
    auto operator+=(const matrix& rhs)
    {
        assert(rows==rhs.rows&&cols==rhs.cols);
        data += rhs.data;
        return *this;
    }
    auto operator-(const auto& rhs) const { return matrix(*this) -= rhs; }
    auto operator-=(const T& rhs) { data -= rhs; return *this; }
    auto operator-=(const matrix& rhs)
    {
        assert(rows==rhs.rows&&cols==rhs.cols);
        data -= rhs.data;
        return *this;
    }
    auto operator*(const T& rhs) const { return matrix(*this) *= rhs; }
    auto operator*=(const T& rhs) { data *= rhs; return *this; }
    auto operator*(const matrix& rhs) const
    {
        assert(cols==rhs.rows);
        matrix res(rows, rhs.cols);
        for(size_t i=0;i<rows;i++)
            for(size_t k=0;k<cols;k++)
                for(size_t j=0;j<rhs.cols;j++)
                    res(i,j) += operator()(i,k)*rhs(k,j);
        return res;
    }
    auto operator*=(const matrix& rhs) { return *this = *this*rhs; }
    friend auto& operator>>(istream& is, matrix& rhs)
    {
        for(size_t i=0;i<rhs.rows;i++)
            for(size_t j=0;j<rhs.cols;j++)
                is>>rhs(i,j);
        return is;
    }
    friend auto& operator<<(ostream& os, const matrix& rhs)
    {
        for(size_t i=0;i<rhs.rows;i++)
        {
            for(size_t j=0;j<rhs.cols;j++)
            {
                os<<rhs(i,j);
                if(j!=rhs.cols-1) os<<' ';
                else if(i!=rhs.rows-1) os<<'\n';
            }
        }
        return os;
    }
};
template <typename T>
class square_matrix : public matrix<T>
{
public:
    static auto identity(size_t n) { square_matrix E(n); E.diagonal() = 1; return E; }
private:
    using matrix<T>::rows;
    using matrix<T>::data;
public:
    square_matrix(size_t n) : matrix<T>(n,n) {}
    auto diagonal() { return data[slice(0, rows, rows+1)]; }
    auto antidiagonal() { return data[slice(rows-1, rows, rows-1)]; }
    auto pow(integral auto k)
    {
        square_matrix a=*this, res=identity(rows);
        for(;k;k>>=1,a*=a) if(k&1) res *= a;
        return res;
    }
};
