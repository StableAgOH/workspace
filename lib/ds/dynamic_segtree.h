template <typename T, auto Op, typename Alloc=allocator<T>>
requires convertible_to<invoke_result_t<decltype(Op), T, T>, T>
class dynamic_segtree
{
    typedef struct node { T value; node *left, *right; }* pnode;
    using AllocNode = allocator_traits<Alloc>::template rebind_alloc<node>;
    AllocNode alloc;
    pnode allocate_node(const T& value)
    {
        pnode u = alloc.allocate(1);
        allocator_traits<AllocNode>::construct(alloc, u, value, nullptr, nullptr);
        return u;
    }
    pnode root = nullptr;
    size_t n;
    T e;
    void update(pnode u) { u->value = Op(u->left?u->left->value:e, u->right?u->right->value:e); }
public:
    dynamic_segtree(size_t n, const T& e, Alloc alloc={}) : alloc(alloc), n(n), e(e) {}
    dynamic_segtree(ranges::range auto&& rg, const T& e, Alloc alloc={})
        : dynamic_segtree(ranges::size(rg), e, alloc)
    {
        auto it = ranges::begin(rg);
        auto impl = [&](auto&& self, pnode& u, size_t ul, size_t ur) -> void
        {
            u = allocate_node(ul==ur?*it++:e);
            if(ul==ur) return;
            auto um = (ul+ur)>>1;
            self(self, u->left, ul, um);
            self(self, u->right, um+1, ur);
            update(u);
        };
        impl(impl, root, 0, n-1);
    }
    ~dynamic_segtree()
    {
        auto impl = [&](auto&& self, pnode& u) -> void
        {
            if(!u) return;
            self(self, u->left);
            self(self, u->right);
            allocator_traits<AllocNode>::destroy(alloc, u);
            alloc.deallocate(u, 1);
        };
        impl(impl, root);
    }
    auto operator()() const { return root?root->value:e; }
    auto operator[](size_t p) const
    {
        auto impl = [&](auto&& self, pnode u, size_t ul, size_t ur)
        {
            if(!u) return e;
            if(ul==ur) return u->value;
            auto um = (ul+ur)>>1;
            return p<=um?self(self, u->left, ul, um):self(self, u->right, um+1, ur);
        };
        return impl(impl, root, 0, n-1);
    }
    auto operator()(size_t l, size_t r) const
    {
        auto impl = [&](auto&& self, pnode u, size_t ul, size_t ur)
        {
            if(!u) return e;
            if(l<=ul&&ur<=r) return u->value;
            auto um = (ul+ur)>>1;
            return (l<=um?self(self, u->left, ul, um):e)+(r>um?self(self, u->right, um+1, ur):e);
        };
        return impl(impl, root, 0, n-1);
    }
    void transform(size_t p, invocable<T&> auto&& f)
    {
        auto impl = [&](auto&& self, pnode& u, size_t ul, size_t ur) -> void
        {
            if(!u) u = allocate_node(e);
            if(ul==ur) { f(u->value); return; }
            auto um = (ul+ur)>>1;
            p<=um?self(self, u->left, ul, um):self(self, u->right, um+1, ur);
            update(u);
        };
        impl(impl, root, 0, n-1);
    }
    void set(size_t p, const T& x) { transform(p, [&](T& v) { v = x; }); }
};
