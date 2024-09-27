#include <bits/stdc++.h>
using namespace std;
template <typename T, typename U>
struct formatter<pair<T,U>> : formatter<string>
{
    auto format(const pair<T,U>& x, format_context& ctx) const
    {
        return format_to(ctx.out(), "<{},{}>", x.first, x.second);
    }
};
template <typename... Args>
struct formatter<tuple<Args...>> : formatter<string>
{
    auto format(const tuple<Args...>& x, format_context& ctx) const
    {
        format_to(ctx.out(), "(");
        apply([&](auto&& first, auto&&... args) {
            format_to(ctx.out(), "{}", first);
            (format_to(ctx.out(), ",{}", args), ...);
        }, x);
        return format_to(ctx.out(), ")");
    }
};
// std::queue, std::stack and std::priority_queue
template <typename T> requires requires(T t) { t.pop(); }
struct formatter<T> : formatter<string>
{
    auto format(T x, format_context& ctx) const
    {
        format_to(ctx.out(), "{{");
        while(!x.empty())
        {
            typename T::value_type o;
            if constexpr(requires(T t) { t.top(); }) o = x.top();
            else o = x.front();
            x.pop();
            format_to(ctx.out(), "{}{}", o, x.empty()?"":",");
        }
        return format_to(ctx.out(), "}}");
    }
};
template <ranges::range T>
struct formatter<T> : formatter<string>
{
    auto format(const T& x, format_context& ctx) const
    {
        format_to(ctx.out(), "[");
        for(auto it=ranges::begin(x);it!=ranges::end(x);++it)
            format_to(ctx.out(), "{}{}", it==ranges::begin(x)?"":",", *it);
        return format_to(ctx.out(), "]");
    }
};

namespace debug_macro
{
auto trim(const string& s)
{
    return s | views::drop_while(::isspace)
        | views::reverse
        | views::drop_while(::isspace)
        | views::reverse
        | ranges::to<string>();
}
template <typename F, typename... Args>
void debug(int line, string_view names, F&& first, Args&&... args)
{
    vector<string> name_list(1);
    int cnt = 0;
    for(auto c : names)
    {
        if(c==','&&!cnt) name_list.emplace_back();
        else
        {
            if(c=='(') cnt++;
            else if(c==')') cnt--;
            name_list.back().push_back(c);
        }
    }
    auto it_name = begin(name_list);
    print(stderr, "{} | {}={}", line, *it_name, first);
    (print(stderr, ", {}={}", *++it_name, args), ...);
    print(stderr, "\n");
}
}
class timer
{
private:
    static chrono::_V2::system_clock::time_point start_time;
public:
    static void set_start_time() { start_time = chrono::high_resolution_clock::now(); }
    static void utime(int line)
    {
        auto end_time = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::milliseconds>(end_time-start_time);
        println(stderr, "{} ms used at line {}", duration.count(), line);
    }
};
chrono::_V2::system_clock::time_point timer::start_time;

#define debug(...) debug_macro::debug(__LINE__, #__VA_ARGS__, __VA_ARGS__)
#define utime() timer::utime(__LINE__)
