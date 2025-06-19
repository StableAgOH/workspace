struct prev_less_fn
{
    template <input_iterator I, sentinel_for<I> S, output_iterator<int> O, typename Cmp=ranges::less>
    constexpr void operator()(I first, S last, O result, int default_val, Cmp cmp={}) const
    {
        stack<I> st;
        for(auto it=first; it!=last; ++it)
        {
            while(!st.empty()&&!cmp(*st.top(), *it)) st.pop();
            *result++ = st.empty()?default_val:ranges::distance(first, st.top());
            st.push(it);
        }
    }
    template <ranges::input_range R, output_iterator<int> O, typename Cmp=ranges::less>
    constexpr void operator()(R&& rg, O result, int default_val, Cmp cmp={}) const
    {
        (*this)(ranges::begin(rg), ranges::end(rg), move(result), default_val, move(cmp));
    }
};
inline constexpr prev_less_fn prev_less;
struct next_less_fn
{
    template <bidirectional_iterator I, sentinel_for<I> S, bidirectional_iterator O, typename Cmp=ranges::less>
    requires indirectly_writable<O, int>
    constexpr void operator()(I first, S last, O result, int default_val, Cmp cmp={}) const
    {
        auto sz = ranges::distance(first, last);
        auto iit=ranges::next(first, sz), oit=ranges::next(result, sz);
        stack<I> st;
        while(iit!=first)
        {
            --iit;
            while(!st.empty()&&!cmp(*st.top(), *iit)) st.pop();
            *--oit = st.empty()?default_val:ranges::distance(first, st.top());
            st.push(iit);
        }
    }
    template <ranges::bidirectional_range R, bidirectional_iterator O, typename Cmp=ranges::less>
    requires indirectly_writable<O, int>
    constexpr void operator()(R&& rg, O result, int default_val, Cmp cmp={}) const
    {
        (*this)(ranges::begin(rg), ranges::end(rg), move(result), default_val, move(cmp));
    }
};
inline constexpr next_less_fn next_less;
