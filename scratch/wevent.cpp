#include "wevent.h"
#include "ustd.h" //for intToString
#include <cmath> //for cieling function
/**
  *see wevent.h for dev notes
  */
namespace evt{
	//One day I need to move this to the class definition, but not now
	void shiftDate(Event& shifted,::Date::Time shiftee){//herpaderp, so clever
		shifted.Start+=shiftee;
		shifted.End+=shiftee;
	}
	std::vector<Event>& wEvent::eventGen(std::vector<Event>& ReturnValue){
		ReturnValue.push_back(this->Base);
		return ReturnValue;
		//should I return ReturnValue? I don't know, I hope that I figure out some chaining for that
	}
	std::vector<Event>& r_wEvent::eventGen(std::vector<Event>& ReturnValue){
		Event tBase=Base; // t is the magical temporary prefix, let's try to be consistent
		while(tBase.End<TrueEnd){
			ReturnValue.push_back(tBase);
			shiftDate(tBase,Repeater);
		}
		return ReturnValue;
	}
	std::vector<Event>& s_wEvent::eventGen(std::vector<Event>& ReturnValue){
		Event tBase=Base;
		int SubDiv=ceil(double(tBase.Length)/double(subLength));
		//that line is horrible, I'll look at that later, maybe.
		for(int i=1;i<=SubDiv;i++){//prepare yourself for a terrible use of a constructor, almost as bad as the Win32 API
			Event tEvent(((tBase.Name)+" "+ustd::intToString(i)+"/"+ustd::intToString(SubDiv)),//Name
						 ((i==SubDiv?tBase.Length:subLength)),//Length
						 (tBase.Start),//we're shifting the start later on
						 (tBase.End));
			ReturnValue.push_back(tEvent);
			tBase.Start+=tEvent.Length;
		}
		//this is some magical debug thingy I wrote to
		return ReturnValue;
	}
	std::vector<Event>& sr_wEvent::eventGen(std::vector<Event>& ReturnValue){
		//For now, the s_wEvents created aren't really differenciated. I'll fix that later by figuring out a good r_wEvent name modifier
		//I also need to adopt to a heap
		std::vector<s_wEvent> tHolder;
		Event tBase=this->Base;
		while(tBase.End<TrueEnd){
			s_wEvent t_s_wEvent(tBase,this->subLength);//well, that's a nice change compared to the other tEvent constructor
			tHolder.push_back(t_s_wEvent);
			shiftDate(tBase,Repeater);
		}
		while(!tHolder.empty()){
			tHolder.front().eventGen(ReturnValue);
			tHolder.erase(tHolder.begin());
		}
		return ReturnValue;
	}
}
