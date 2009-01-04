#include "date.h"
#include "ustd.h"
#include <ctime>
/**
 *NOTES:
      int tm_sec;    // seconds after the minute (0 to 61)
     int tm_min;    /* minutes after the hour (0 to 59)
     int tm_hour;   /* hours since midnight (0 to 23)
     int tm_mday;   /* day of the month (1 to 31)
     int tm_mon;    /* months since January (0 to 11)
     int tm_year;   /* years since 1900
     int tm_wday;   /* days since Sunday (0 to 6 Sunday=0)
     int tm_yday;   /* days since January 1 (0 to 365)
     int tm_isdst;  /* Daylight Savings Time
**/
namespace Date{
	int Date::Year(){
	    tm* temp=gmtime(&seconds);
		return temp->tm_year+1900;
	}
	int Date::Month(){
	     tm* temp=gmtime(&seconds);
		return temp->tm_mon+1;
	}
	int Date::Day(){
	    tm* temp=gmtime(&seconds);
		return temp->tm_mday;
	}
	int Date::Hour(){
	    tm* temp=gmtime(&seconds);
	    return (temp->tm_hour)+1;
	}
	int Date::Min(){
	    tm* temp=gmtime(&seconds);
	    return (temp->tm_min);
	}
	int Date::Sec(){
	    tm* temp=gmtime(&seconds);
        return (temp->tm_sec)+1;
	}
	long Date::tSeconds(){
		return seconds;
	}
	Time Date::operator -(Date second){
	    long temp=(seconds-second.tSeconds());
	    Time tem(true,temp);
		return tem;
	}
	Date Date::operator +(Time second){
		return Date(true,this->seconds+second.tSeconds());
	}
	Date Date::operator +=(Time second){
		this->seconds+=second.tSeconds();
		return *this;
	}
	Date Date::operator -=(Time second){
		this->seconds-=second.tSeconds();
		return *this;
	}
	bool Date::operator <(Date second){
		return this->seconds<second.tSeconds();
	}
	bool Date::operator <(long second){
		return this->seconds<second;
	}
	bool Date::operator >=(Date second){
		return this->seconds>=second.tSeconds();
	}
	Date::Date(bool truth,long tSeconds){
		seconds=tSeconds;
	}
	Date::Date(int year,int month,int day,int hour,int min,int second){
		tm temp;
		temp.tm_year=year-1900;
		temp.tm_mon=month-1;//January is represented by 0
		temp.tm_mday=day;
		temp.tm_hour=hour;
		temp.tm_min=min;
		temp.tm_sec=second;
		seconds=mktime(&temp);
	}
	int Time::Year(){
	     tm* temp=gmtime(&seconds);
		return temp->tm_year;
	}
	int Time::Month(){
	     tm* temp=gmtime(&seconds);
		return temp->tm_mon;
	}
	int Time::Day(){
	     tm* temp=gmtime(&seconds);
		return temp->tm_mday-1;//for time that lasts less than one day, we still have one day on the counter
	}
	Date::operator long(){
	    return seconds;
	}
    std::fstream& operator <<(std::fstream& file,Date& date){
        file<<date.tSeconds();
        return file;
    }
    std::fstream& operator >>(std::fstream& file,Date& date){
        file>>date.seconds;
        return file;
    }
    std::fstream& operator <<(std::fstream& file,Time& time){
        long temp=time.seconds;
        file<<temp;
        return file;
    }
    std::fstream& operator >>(std::fstream& file,Time& time){
        file>>time.seconds;
        return file;
    }
    std::string Date::str(){//format in DD/MM/YYY HH:MM:SS}
        return std::string(ustd::intToString(Day())+"/"
                           +ustd::intToString(Month())+"/"
                           +ustd::intToString(Year())+" "
                           +ustd::intToString(Hour())+":"
                           +ustd::intToString(Min())+":"
                           +ustd::intToString(Sec()));
    }
    Date curDate(){
        time_t temp;
        return Date(true,time(&temp));
    }
}
