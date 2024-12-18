#include <bits/stdc++.h>
#include <experimental/iterator>
using namespace std;
namespace debug_macro
{
template <typename C, typename T, ranges::range R>
basic_ostream<C,T>& operator<<(basic_ostream<C,T>&, const R&);
template <typename T, typename U>
ostream& operator<<(ostream& os, const pair<T,U>& x)
{
    return os<<'<'<<x.first<<','<<x.second<<'>';
}
template <typename... Args>
ostream& operator<<(ostream& os, const tuple<Args...>& x)
{
    os<<'(';
    apply([&](auto&& first, auto&&... args) { os<<first; ((os<<','<<args), ...); }, x);
    return os<<')';
}
// std::queue, std::stack and std::priority_queue
template <typename T> requires requires(T t) { t.pop(); }
ostream& operator<<(ostream& os, T x)
{
    if(x.empty()) return os<<"{}";
    os<<'{';
    while(!x.empty())
    {
        typename T::value_type o;
        if constexpr(requires(T t) { t.top(); }) o = x.top();
        else o = x.front();
        x.pop();
        os<<o<<",}"[x.empty()];
    }
    return os;
}
template <typename C, typename T, ranges::range R>
basic_ostream<C,T>& operator<<(basic_ostream<C,T>& os, const R& x)
{
    os<<'[';
    copy(x.begin(), x.end(), experimental::make_ostream_joiner(os, ","));
    return os<<']';
}
auto trim(const string s)
{
    return s | views::drop_while(::isspace)
        | views::reverse
        | views::drop_while(::isspace)
        | views::reverse;
}
void debug(source_location loc, string_view names, auto&& first, auto&&... args)
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
    cerr<<boolalpha<<loc.line()<<" | ";
    auto it_name = begin(name_list);
    auto it_out = ostream_iterator<char>(cerr);
    ranges::copy(trim(*it_name), it_out);
    cerr<<'='<<first;
    ((cerr<<", ", ranges::copy(trim(*++it_name), it_out), cerr<<'='<<args), ...);
    cerr<<'\n';
}
}
#define debug(...) debug_macro::debug(source_location::current(), #__VA_ARGS__, __VA_ARGS__)

chrono::time_point<chrono::high_resolution_clock> stime;
struct local_initialer
{
    local_initialer(const char* inf, const char* outf)
    {
        freopen(inf, "r", stdin);
    #ifndef DEBUG
        freopen(outf, "w", stdout);
    #endif
        stime = chrono::high_resolution_clock::now();
    }
};
void utime(source_location loc=source_location::current())
{
    auto etime = chrono::high_resolution_clock::now();
    auto dur = chrono::duration_cast<chrono::milliseconds>(etime-stime);
    cerr<<dur.count()<<" ms used at line "<<loc.line()<<" in function "<<loc.function_name()<<'\n';
}
