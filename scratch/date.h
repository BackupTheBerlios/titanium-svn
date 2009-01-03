/***************************************************************************
 *   Copyright (C) 2008 by Raphael　Gaschignard   *
 *   dasuraga@gmail.com   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU Library General Public License as       *
 *   published by the Free Software Foundation; either version 2 of the    *
 *   License, or (at your option) any later version.                       *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU Library General Public     *
 *   License along with this program; if not, write to the                 *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
/**
 *NOTE: pleas do not try and make this a generalised Date namespace;
 *this is meant to be used for Titanium and nothing more;
 */
 #ifndef DATE_H
 #define DATE_H

#include <iostream>
#include <fstream>
namespace Date{
	class Date;
	class Time;
	class Date{
    public:
        time_t seconds;
        virtual int Year();
		virtual int Month();
		virtual int Day();
		long tSeconds();//used for comparison
        virtual Time operator -( Date second);
		Date operator +(Time second);
		Date operator +=(Time second);
		Date operator -=(Time second);
		bool operator <(Date second);//STRICT
		bool operator <(long second);
		bool operator >=(Date second);
        Date(bool truth,long tSeconds);
        Date(){ seconds=0;};
		Date(int year,int month,int day,int hour,int min,int second);
		virtual ~Date(){};
		friend std::fstream& operator <<(std::fstream& file,Date& date);
		friend std::fstream& operator >>(std::fstream& file,Date& date);
		virtual operator long();
	};
	class Time:public Date{
    public:
		Time(bool truth,long tSeconds):Date(truth,tSeconds){}
		Time():Date(){}
		virtual int Year();
		virtual int Month();
		virtual int Day();
		friend std::fstream& operator <<(std::fstream& file,Time& time);
		friend std::fstream& operator >>(std::fstream& file,Time& time);
	};
    std::fstream& operator <<(std::fstream& file,Date& date);
    std::fstream& operator >>(std::fstream& file,Date& date);
    std::fstream& operator <<(std::fstream& file,Time& time);
    std::fstream& operator >>(std::fstream& file,Time& time);
}
#endif
