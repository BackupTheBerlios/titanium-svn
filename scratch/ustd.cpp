#include "ustd.h"
std::string ustd::intToString(int n){
    std::stringstream out;
    out<<n;
    return out.str();
}
time_t ustd::mktime(tm* in,bool full){
    //NOTE: the month thing is completely borked. ONLY USE THIS FOR DATE::TIME CONVERSIONS
    time_t temp;
    temp+=in->tm_sec;
    temp+=in->tm_min*60;
    temp+=in->tm_hour*60*60;
    if(full){
    temp+=in->tm_mday*24*60*60;
    temp+=in->tm_mon*30*24*60*60;//This is basing a month as 30 days
    temp+=in->tm_year*365*24*60*60;}
    return temp;
}
void ustd::copyStream(std::fstream& in,std::fstream& out){//I stole this dirrectly from Bjarne, 21.5.1
    char ch;
    while(in.get(ch)) {out.put(ch); std::cout<<ch;}
}
