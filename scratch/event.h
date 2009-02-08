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
#ifndef EVENT_H
#define EVENT_H
#include <string>
#include "date.h"
namespace evt{
	class Event{
    public:
		std::string Name;
		Date::Time Length;
		Date::Date Start;
		Date::Date End;
	public:
		bool startsBefore(Date::Date second);
		bool endsBefore(Date::Date second);
		bool startsBefore(Event second);
		bool endsBefore(Event second);
		Event(std::string name,Date::Time length,Date::Date start,Date::Date end);
		Event(std::string name,long len,long sta,long en);
		Event(){};
		Date::Date start();
		Date::Date end();
		Date::Time length();
		friend std::fstream& operator <<(std::fstream& file,Event event);
		friend std::fstream& operator >>(std::fstream& file,Event& event);
	};
	std::fstream& operator <<(std::fstream& file,Event event);
	std::fstream& operator >>(std::fstream& file,Event& event);
}
#endif
