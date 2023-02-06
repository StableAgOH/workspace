#include <bits/stdc++.h>
#include "prettyprint.hpp"
using namespace std;

template <typename Arg1>
void debug(const char* name, Arg1&& arg1) { clog<<name<<": "<<arg1<<endl; }
template <typename Arg1, typename... Args>
void debug(const char* names, Arg1&& arg1, Args&&... args)
{
    auto comma = strchr(names+1, ',');
    clog.write(names, comma-names)<<": "<<arg1<<" | ";
    while(*++comma==' ');
    debug(comma, args...);
}

class timer
{
private:
    static chrono::_V2::system_clock::time_point begin_time;
public:
    static void set_begin_time() { begin_time = chrono::high_resolution_clock::now(); }
    static void utime(int line)
    {
        auto end_time = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::milliseconds>(end_time-begin_time);
        clog<<duration.count()<<" ms used at line "<<line<<endl;
    }
};
chrono::_V2::system_clock::time_point timer::begin_time;
