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
#ifndef ORGANISE_H
#define ORGANISE_H
#include <ctime>
#include <vector>
#include <algorithm>
#include "event.h"
typedef std::vector<std::pair<bool,evt::Event> > calendar;
typedef std::vector<evt::Event> evtlist;
Date::Date currTime();
void Organise(evtlist* In,std::vector<std::pair<bool,evt::Event> >* Out);
void evtSort(evtlist& in);
bool startsBefore(evt::Event first,evt::Event second);
bool endsBefore(evt::Event first,evt::Event second);
void sSort(std::vector<std::pair<long,evt::Event> >& sortee);
bool pCheck(std::pair<long,evt::Event>& first,std::pair<long,evt::Event>& second);
bool sStartsBefore(evt::Event& first,evt::Event& second);
evtlist readFromFile(std::fstream& file);
std::fstream& writeToFile(evtlist events,std::fstream& file);
#endif
