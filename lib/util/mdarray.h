template <typename T, size_t S, size_t... Sizes>
struct mdarray_helper { using type = array<typename mdarray_helper<T, Sizes...>::type, S>; };
template <typename T, size_t L>
struct mdarray_helper<T, L> { using type = array<T, L>; };
template <typename T, size_t... Sizes>
using mdarray = typename mdarray_helper<T, Sizes...>::type;
