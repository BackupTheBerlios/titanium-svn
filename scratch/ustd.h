/**
 *The Unstandard Library
 *what should've been supported from the outset,yet wasn't for some reason
 */
#include <sstream>
#include <ctime>
namespace ustd{
    std::string intToString(int n);
    time_t mktime(tm* in,bool full);
}
