#include <chrono>
#include "dbg-macro/dbg.h"
#define debug(...) dbg(__VA_ARGS__)
using namespace std;
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
