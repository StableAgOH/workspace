#include <bits/stdc++.h>
using namespace std;
namespace debug_macro
{
    template <typename C, typename T, ranges::range R>
    basic_ostream<C,T>& operator<<(basic_ostream<C,T>&, const R&);

    template <typename T, typename U>
    auto& operator<<(ostream& os, const pair<T,U>& x)
    {
        return os<<'<'<<x.first<<','<<x.second<<'>';
    }

    template <typename... Args>
    auto& operator<<(ostream& os, const tuple<Args...>& x)
    {
        os<<'(';
        apply([&](auto&& first, auto&&... args) { os<<first; ((os<<','<<args), ...); }, x);
        return os<<')';
    }

    // std::queue, std::stack and std::priority_queue
    template <typename T> requires requires(T t) { t.pop(); }
    auto& operator<<(ostream& os, T x)
    {
        os<<'{';
        while(!x.empty())
        {
            typename T::value_type o;
            if constexpr(requires(T t) { t.top(); }) o = x.top();
            else o = x.front();
            x.pop();
            os<<o;
            if(!x.empty()) os<<',';
        }
        return os<<'}';
    }

    template <typename C, typename T, ranges::range R>
    basic_ostream<C,T>& operator<<(basic_ostream<C,T>& os, const R& x)
    {
        os<<'[';
        for(auto it=ranges::begin(x);it!=ranges::end(x);++it)
        {
            if(it!=ranges::begin(x)) os<<',';
            os<<*it;
        }
        return os<<']';
    }

    void debug(const source_location& sl, string_view names, auto&& first, auto&&... args)
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
        for(auto& s : name_list)
        {
            s.erase(0, s.find_first_not_of(' '));
            s.erase(s.find_last_not_of(' ')+1);
        }
        cerr<<boolalpha<<sl.line()<<" | ";
        auto it = name_list.begin();
        cerr<<*it<<'='<<first;
        ((cerr<<", "<<*++it<<'='<<args), ...);
        cerr<<'\n';
    }
}
#define debug(...) debug_macro::debug(source_location::current(), #__VA_ARGS__, __VA_ARGS__)

chrono::time_point<chrono::high_resolution_clock> stime;
struct local_initialer
{
    local_initialer(const char* inf, [[maybe_unused]] const char* outf)
    {
        freopen(inf, "r", stdin);
    #ifndef DEBUG
        freopen(outf, "w", stdout);
    #endif
        stime = chrono::high_resolution_clock::now();
    }
    ~local_initialer()
    {
        auto etime = chrono::high_resolution_clock::now();
        auto dur = chrono::duration_cast<chrono::milliseconds>(etime-stime);
        cerr<<dur.count()<<" ms were elapsed in total"<<'\n';
    }
};
void utime(source_location sl=source_location::current())
{
    auto etime = chrono::high_resolution_clock::now();
    auto dur = chrono::duration_cast<chrono::milliseconds>(etime-stime);
    cerr<<dur.count()<<" ms were elapsed at line "<<sl.line()<<'\n';
}
