#include <bits/stdc++.h>
using namespace std;
namespace debug_macro
{
template <typename C, typename T, ranges::range R>
basic_ostream<C,T>& operator<<(basic_ostream<C,T>& os, const R& x);

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
    auto it=ranges::begin(x), ed=ranges::end(x);
    if(it!=ed) os<<*it++;
    for(;it!=ed;++it) os<<','<<*it;
    return os<<']';
}

auto trim(const string s)
{
    return s | views::drop_while(::isspace)
        | views::reverse
        | views::drop_while(::isspace)
        | views::reverse;
}
void debug(int line, string_view names, auto&& first, auto&&... args)
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
    clog<<boolalpha<<line<<" | ";
    auto it_name = begin(name_list);
    auto it_out = ostream_iterator<char>(clog);
    ranges::copy(trim(*it_name), it_out);
    clog<<'='<<first;
    ((clog<<", ", ranges::copy(trim(*++it_name), it_out), clog<<'='<<args), ...);
    clog<<endl;
}
}
namespace timer
{
    chrono::time_point<chrono::high_resolution_clock> start_time;
    void utime(int line)
    {
        auto end_time = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::milliseconds>(end_time-start_time);
        clog<<duration.count()<<" ms used at line "<<line<<endl;
    }
}

#define debug(...) debug_macro::debug(__LINE__, #__VA_ARGS__, __VA_ARGS__)
#define utime() timer::utime(__LINE__)
