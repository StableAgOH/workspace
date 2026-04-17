constexpr size_t DYN = -1;
template <typename T, size_t R=DYN, size_t C=DYN>
class matrix
{
    struct empty_t {};
    [[no_unique_address]] conditional_t<R==DYN, size_t, empty_t> r{};
    [[no_unique_address]] conditional_t<C==DYN, size_t, empty_t> c{};
    static constexpr bool is_dyn = R==DYN||C==DYN;
    conditional_t<is_dyn, vector<T>, array<T, is_dyn?0:R*C>> data{};
public:
    constexpr matrix(size_t r=(R==DYN?0:R), size_t c=(C==DYN?0:C))
    {
        if constexpr(R==DYN) this->r = r;
        if constexpr(C==DYN) this->c = c;
        if constexpr(is_dyn) data.resize(r*c);
    }
    constexpr size_t rows() const { if constexpr(R==DYN) return r; else return R; }
    constexpr size_t cols() const { if constexpr(C==DYN) return c; else return C; }
    constexpr decltype(auto) operator()(this auto&& self, size_t i, size_t j)
    {
        return forward_like<decltype(self)>(self.data[i*self.cols()+j]);
    }
    constexpr bool operator==(const matrix& o) const { return data==o.data; }
    constexpr matrix(initializer_list<T> il) requires (!is_dyn)
    {
        ranges::copy(il, data.begin());
    }
    constexpr matrix& operator+=(const matrix& o)
    {
        assert(rows()==o.rows()&&cols()==o.cols());
        for(size_t i=0;i<data.size();i++) data[i] += o.data[i];
        return *this;
    }
    constexpr matrix& operator-=(const matrix& o)
    {
        assert(rows()==o.rows()&&cols()==o.cols());
        for(size_t i=0;i<data.size();i++) data[i] -= o.data[i];
        return *this;
    }
    constexpr matrix& operator*=(const T& x)
    {
        for(auto& i : data) i *= x;
        return *this;
    }
    friend constexpr matrix operator+(matrix a, const matrix& b) { return a += b; }
    friend constexpr matrix operator-(matrix a, const matrix& b) { return a -= b; }
    friend constexpr matrix operator*(matrix a, const T& x) { return a *= x; }
    friend constexpr matrix operator*(const T& x, matrix a) { return a *= x; }
    template <size_t OR, size_t OC>
    constexpr auto operator*(const matrix<T, OR, OC>& o) const
    {
        assert(this->cols()==o.rows());
        matrix<T, R, OC> res(this->rows(), o.cols());
        for(size_t i=0;i<this->rows();i++)
            for(size_t k=0;k<this->cols();k++)
                for(size_t j=0;j<o.cols();j++)
                    res(i, j) += (*this)(i, k)*o(k, j);
        return res;
    }
    template <size_t OR, size_t OC>
    constexpr auto& operator*=(const matrix<T, OR, OC>& o) { return *this = *this*o; }
};
template <typename T, size_t N=DYN>
class square_matrix : public matrix<T, N, N>
{
public:
    using matrix<T, N, N>::matrix;
    constexpr square_matrix(size_t n=N) : matrix<T, N, N>(n, n) {}
    constexpr square_matrix(const matrix<T, N, N>& m) : matrix<T, N, N>(m) {}
    static constexpr square_matrix identity(size_t n=N)
    {
        square_matrix res(n);
        for(size_t i=0;i<n;i++) res(i, i) = 1;
        return res;
    }
    constexpr square_matrix pow(uint64_t p) const
    {
        auto res=identity(this->rows()), a=*this;
        for(;p;p>>=1,a=a*a)
            if(p&1) res = res*a;
        return res;
    }
    constexpr square_matrix transpose() const
    {
        square_matrix res(this->rows());
        for(size_t i=0;i<this->rows();i++)
            for(size_t j=0;j<this->cols();j++)
                res(j, i) = (*this)(i, j);
        return res;
    }
    template <typename Aug>
    static constexpr T gauss_jordan(Aug& aug, size_t n)
    {
        auto m = aug.cols();
        T det{1};
        for(size_t i=0;i<n;i++)
        {
            auto p = i;
            if constexpr(floating_point<T>)
            {
                for(auto j=i+1;j<n;j++)
                    if(abs(aug(j, i))>abs(aug(p, i)))
                        p = j;
            }
            else while(p<n&&aug(p, i)==T{0}) p++;
            if(p==n) return T{0};
            if(i!=p)
            {
                for(auto j=i;j<m;j++) swap(aug(i, j), aug(p, j));
                det = -det;
            }
            T pivot=aug(i, i), inv=T{1}/pivot;
            det *= pivot;
            aug(i, i) = T{1};
            for(auto j=i+1;j<m;j++) aug(i, j) *= inv;
            for(size_t k=0;k<n;k++)
            {
                if(k!=i&&aug(k, i)!=T{0})
                {
                    T fac = aug(k, i);
                    aug(k, i) = T{0};
                    for(auto j=i+1;j<m;j++) aug(k, j) -= fac*aug(i, j);
                }
            }
        }
        return det;
    }
    constexpr T det(this auto self) { return gauss_jordan(self, self.rows()); }
    template <size_t BC>
    constexpr optional<matrix<T, N, BC>> solve(const matrix<T, N, BC>& b)
    {
        auto n=this->rows(), bc=b.cols();
        assert(b.rows()==n);
        matrix<T, N, (N==DYN||BC==DYN)?DYN:N+BC> aug(n, n+bc);
        for(size_t i=0;i<n;i++)
        {
            for(size_t j=0;j<n;j++) aug(i, j) = (*this)(i, j);
            for(size_t j=0;j<bc;j++) aug(i, n+j) = b(i, j);
        }
        if(gauss_jordan(aug, n)==T{0}) return nullopt;
        matrix<T, N, BC> res(n, bc);
        for(size_t i=0;i<n;i++)
            for(size_t j=0;j<bc;j++)
                res(i, j) = aug(i, n+j);
        return res;
    }
    constexpr optional<square_matrix> inv() { return solve(identity(this->rows())); }
    constexpr T euclid_det(this auto self) requires requires { T::mod(); }
    {
        auto n = self.rows();
        T det{1};
        for(size_t i=0;i<n;i++)
        {
            for(size_t j=i+1;j<n;j++)
            {
                while(self(j, i)!=T{0})
                {
                    T q = int(self(i, i))/int(self(j, i));
                    for(auto k=i;k<n;k++)
                    {
                        self(i, k) -= q*self(j, k);
                        swap(self(i, k), self(j, k));
                    }
                    det = -det;
                }
            }
            if(self(i, i)==T{0}) return T{0};
            det *= self(i, i);
        }
        return det;
    }
};
