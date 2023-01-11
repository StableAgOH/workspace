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
