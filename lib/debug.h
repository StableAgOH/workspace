#include <bits/stdc++.h>
using namespace std;
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
template <typename T> requires requires(T t) { t.pop(); }
ostream& operator<<(ostream& os, T x)
{
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
template <ranges::range R> requires (!requires(R r) { cout<<r; })
ostream& operator<<(ostream& os, const R& x)
{
    for(auto it=begin(x);it!=end(x);++it) os<<",["[it==begin(x)]<<*it;
    return os<<']';
}
template <ranges::range R>
auto trim(const R& r)
{
    return r | views::drop_while(::isspace)
        | views::reverse
        | views::drop_while(::isspace)
        | views::reverse;
}
template <typename F, typename... Args>
void _debug(int line, string_view names, F&& first, Args&&... args)
{
    clog<<line<<" | ";
    auto vi = views::split(names, ',');
    auto it = begin(vi);
    ranges::copy(trim(*it), ostream_iterator<char>(clog));
    clog<<'='<<first;
    ((clog<<", ", ranges::copy(trim(*++it), ostream_iterator<char>(clog)), clog<<'='<<args), ...);
    clog<<endl;
}
#define debug(...) _debug(__LINE__, #__VA_ARGS__, __VA_ARGS__)
