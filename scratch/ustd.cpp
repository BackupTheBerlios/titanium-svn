#include "ustd.h"
std::string ustd::intToString(int n){
    std::stringstream out;
    out<<n;
    return out.str();
}
