#include <bits/stdc++.h>
#include "prettyprint.hpp"
using namespace std;

#ifdef LOCAL
    ifstream __fin("in.in");
    ofstream __fout("out.out");
#define cin __fin
#ifndef DEBUG
#define cout __fout
#endif
#endif

namespace local
{
template <typename Arg1>
void debug(const char* name, Arg1&& arg1) { cerr<<name<<": "<<arg1<<endl; }
template <typename Arg1, typename... Args>
void debug(const char* names, Arg1&& arg1, Args&&... args)
{
    auto comma = strchr(names+1, ',');
    cerr.write(names, comma-names)<<": "<<arg1<<" | ";
    while(*++comma==' ');
    debug(comma, args...);
}
} // namespace local
