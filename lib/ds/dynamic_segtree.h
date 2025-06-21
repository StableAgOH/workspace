template <typename T, auto Op, typename Alloc=allocator<T>>
requires same_as<invoke_result_t<decltype(Op), T, T>, T>
class dynamic_segtree
{
    typedef struct node { T data; node *left, *right; }* pnode;
    using AllocNode = allocator_traits<Alloc>::template rebind_alloc<node>;
    AllocNode alloc;
    
    size_t n;
    T e;
    pnode root;

    void update(pnode x) { x->data = Op(x->left?x->left->data:e, x->right?x->right->data:e); }
    pnode new_node()
    {
        pnode nn = alloc.allocate(1);
        allocator_traits<AllocNode>::construct(alloc, nn, e, nullptr, nullptr);
        return nn;
    }
public:
    dynamic_segtree(size_t n, const T& e, Alloc alloc={}) : alloc(alloc), n(n), e(e), root(new_node()) {}
    auto operator()() const { return root->data; }
    auto operator[](size_t p) const { return (*this)(p, p); }
    auto operator()(size_t l, size_t r) const
    {
        auto impl = [&](auto&& impl, size_t L, size_t R, pnode cur)
        {
            if(!cur) return e;
            if(l<=L&&R<=r+1) return cur->data;
            auto M = (L+R)>>1;
            T res = e;
            if(l<M) res = Op(res, impl(impl, L, M, cur->left));
            if(r>=M) res = Op(res, impl(impl, M, R, cur->right));
            return res;
        };
        return impl(impl, 0, n, root);
    }
    void set(size_t p, const T& x)
    {
        auto impl = [&](auto&& impl, size_t L, size_t R, pnode& cur) -> void
        {
            if(!cur) cur = new_node();
            if(L+1==R)
            {
                cur->data = x;
                return;
            }
            auto M = (L+R)>>1;
            if(p<M) impl(impl, L, M, cur->left);
            else impl(impl, M, R, cur->right);
            update(cur);
        };
        impl(impl, 0, n, root);
    }
};
