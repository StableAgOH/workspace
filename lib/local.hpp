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

chrono::_V2::system_clock::time_point __c1;
void __before_run()
{
    freopen("in.in", "r", stdin);
#ifndef DEBUG
    freopen("out.out", "w", stdout);
#endif
    __c1 = chrono::high_resolution_clock::now();
}

void __after_run()
{
    auto __c2 = chrono::high_resolution_clock::now();
    cerr<<"Time Used:"<<chrono::duration_cast<chrono::milliseconds>(__c2-__c1).count()<<"ms"<<endl;
}
