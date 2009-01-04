/***************************************************************************
 *   Copyright (C) 2008 by RaphaelÅ@Gaschignard   *
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
#include "organise.h"
#include <iostream>
#include <cstdlib>
#include <sstream>
#define DEBUG 1
#define DD if(DEBUG) std::cout<<
#define EE ;std::cout<<"\n";
void Organise(evtlist* In,std::vector<std::pair<bool,evt::Event> >* Out){
	Date::Date marker=currTime();
	evtSort(*In);
	std::vector<std::pair<long,evt::Event> > organiser;
	for(;;){
	    //DD "start" EE
		if(marker<In->front().start()){
			marker+=(In->front().start()-marker);
		}
		//DD "moved marker" EE
		for(;;){
		    DD "begin loop" EE
		    if(In->empty()) break;
			if(marker>=In->front().start()){
			    DD "adding organiser" EE
			    DD In->front().Name EE
				long seperator=In->front().end()-marker;
				organiser.push_back(std::pair<long,evt::Event>(seperator,In->front()));
				In->erase(In->begin());
				DD "Erased" EE
			}else break;
		}
		//DD "sorting organiser" EE
		sSort(organiser);

		marker+=(organiser.front().second.length());
		bool overdue=(marker<organiser.front().second.end());
		Out->push_back(std::pair<bool,evt::Event>(overdue,organiser.front().second));
		organiser.erase(organiser.begin());
		if(In->empty()) break;
	}
	DD "done sorting" EE
}
void sSort(std::vector<std::pair<long,evt::Event> >& sortee){
	bool sorted=false;
	if(sortee.size()<=1) return;
	while(!sorted){
		for(unsigned int i=0;i<sortee.size();i++){
			for(unsigned int j=i+1;j<sortee.size();j++){
				if(!pCheck(sortee[i],sortee[j]) && (j==(sortee.size()-1))){sorted=true;}
			}
		}
	}
}
void evtSort(std::vector<evt::Event>& sortee){
	bool sorted=false;
	if(sortee.size()<=1) return;
	while(!sorted){
		for(unsigned int i=0;i<sortee.size();i++){
			for(unsigned int j=i+1;j<sortee.size();j++){
				if(!sStartsBefore(sortee[i],sortee[j]) && (j==(sortee.size()-1))){sorted=true;}
			}
		}
	}
}
Date::Date currTime(){
	time_t ret=time(NULL);
	Date::Date returnvalue(true,ret-30*365*24*60*60);//this should work until 2067 or so
	return returnvalue;
}
bool startsBefore(evt::Event first,evt::Event second){
	return first.startsBefore(second.start());
}
bool endsBefore(evt::Event first,evt::Event second){
	return first.endsBefore(second.end());
}
bool pCheck(std::pair<long,evt::Event>& first,std::pair<long,evt::Event>& second){
	std::pair<long,evt::Event> c=first;
	if(first.first<second.first){
		return false;
	}else{first=second; second=c; return true;}
}
bool sStartsBefore(evt::Event& first,evt::Event& second){
	evt::Event c=first;
	if(first.start()<second.start()){
		return false;
	}else{first=second; second=c; return true;}
}
evtlist readFromFile(std::fstream& file){
	evtlist returnvalue;
        evt::Event temp;
        file>>temp;
        returnvalue.push_back(temp);
	return returnvalue;
}
void writeToFile(evtlist events,std::fstream& file){
    DD "starting file write" EE
	while(!events.empty()){
		file<<events.front();
		events.erase(events.begin());
	}
}
