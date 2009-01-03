#include "event.h"
#include <fstream>
Date::Date evt::Event::start(){
    return Start;
}
Date::Date evt::Event::end(){
    return End;
}
Date::Time evt::Event::length(){
    return Length;
}
bool evt::Event::startsBefore(evt::Event second){
    return (start()<second.start());
}
evt::Event::Event(std::string name,Date::Time length,Date::Date start,Date::Date end){
    Name=name;
    Length=length;
    Start=start;
    End=end;
}
evt::Event::Event(std::string name,long len,long sta,long ed){
    Date::Time length(true,len);
    Date::Date start(true,sta);
    Date::Date end(true,ed);
    Name=name;
    Length=length;
    Start=start;
    End=end;
}
bool evt::Event::endsBefore(evt::Event second){
    return end()<second.end();
}
bool evt::Event::startsBefore(Date::Date second){
    return start()<second;
}
bool evt::Event::endsBefore(Date::Date second){
    return end()<second;
}
std::fstream& evt::operator <<(std::fstream& file, evt::Event event){
    file<<event.Name<<" ";
    file<<event.Length<<" "<<event.Start<<" "<<event.End<<"\n";
    /*file.put(event.Length.tSeconds());
    file<<" ";
    file.put(event.Start.tSeconds());
    file<<" ";
    file.put(event.End.tSeconds());
    file<<"\n";*/
    return file;
}
std::fstream& evt::operator >>(std::fstream& file,evt::Event& event){
    file>>event.Name;
    file>>event.Length;
    file>>event.Start;
    file>>event.End;
    return file;
}

