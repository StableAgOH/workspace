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
    __cerr(comma+1, args...);
}
