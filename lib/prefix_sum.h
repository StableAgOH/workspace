template <typename F, typename T>
using indirect_binary_op_result_t = indirect_result_t<F,T,T>;
struct prefix_sum_fn
{
template <input_iterator I, sentinel_for<I> S, weakly_incrementable O,
          typename Op=plus<>, typename Proj=identity>
requires indirectly_writable<O, indirect_binary_op_result_t<Op&, projected<I, Proj>>>
constexpr void operator()(I first, S last, O result, Op op={}, Proj proj={}) const
{
    if(first==last) return;
    for(auto acc=*result=invoke(proj,*first);++first!=last;)
        *++result = acc = invoke(op, move(acc), invoke(proj, *first));
}
template <ranges::input_range R, weakly_incrementable O, typename Op=plus<>, typename Proj=identity>
requires indirectly_writable<O, indirect_binary_op_result_t<Op&, projected<ranges::iterator_t<R>, Proj>>>
constexpr void operator()(R&& r, O result, Op op={}, Proj proj={}) const
{
    (*this)(ranges::begin(r), ranges::end(r), move(result), move(op), move(proj));
}
};
inline constexpr prefix_sum_fn prefix_sum;
