#include <bits/stdc++.h>
#include "prettyprint.hpp"
using namespace std;
template <typename Arg1>
void __cerr(const char* name, Arg1&& arg1) { cerr<<name<<": "<<arg1<<endl; }
template <typename Arg1, typename... Args>
void __cerr(const char* names, Arg1&& arg1, Args&&... args)
{
    auto comma = strchr(names+1, ',');
    cerr.write(names, comma-names)<<": "<<arg1<<" | ";
    while(*++comma==' ');
    __cerr(comma, args...);
}
void __red(signed argc, char const *argv[])
{
    auto __case = string(argc==1?"1":argv[1]);
    auto __ifname = "testcases/"+__case+".in";
    freopen(__ifname.c_str(), "r", stdin);
#ifndef DEBUG
    auto __ofname = "testcases/"+__case+".out";
    freopen(__ofname.c_str(), "w", stdout);
#endif
}
