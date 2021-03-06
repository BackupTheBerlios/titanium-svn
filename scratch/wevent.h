#ifndef W_EVENT_H
#define W_EVENT_H
#include "event.h"
#include <vector>
#include <fstream>
/**
  *A couple developement notes:
  *	If you make a direct derivation of wEvent, don't forget to virtualise, to support  merging
  *		I'll probably try and build a "better" system with function objects later. Granted, this will
  *		break code, but it looks cleaner. But for now I only see two variants, so we'll keep it like
  *		for now. 4 classes is easy to handle. 12 classes is not, however.
  */
namespace evt{
    class wEcontainer;
	class wEvent{
	public:
		//for those who don't get the constructor notation, see [Bjarne], 11.3.4
		wEvent(Event base):Base(base){};//I will personally shoot the first person who says capital overloading is bad form
		wEvent(){};
		Event Base;
		virtual std::vector<Event>& eventGen(std::vector<Event>& ReturnValue);
		virtual void writeToFile(std::fstream& file){};
		virtual void readFromFile(std::fstream& file){};
		virtual std::string Type(){return "N";}
		//yeah, my variable names aren't imaginative, sue me
		//(don't sue me, I  lack enough money as it is)
	};
	class r_wEvent:public virtual wEvent{
	//repeating event,  repeats every  repeater until trueend
	//(note, we add repeater to the start)
	public:
		r_wEvent(Event base,Date::Time repeater,Date::Date trueEnd):
		wEvent(base),Repeater(repeater),TrueEnd(trueEnd){};
		r_wEvent(){};
		Date::Time Repeater;
		Date::Date TrueEnd;
		virtual std::vector<Event>& eventGen(std::vector<Event>& ReturnValue);
        virtual void writeToFile(std::fstream& file);
        virtual void readFromFile(std::fstream& file);
        virtual std::string Type(){return "R";}
	};
	class s_wEvent:public virtual wEvent{
	//This time we're cutting the  event up into bits of length SubLength
	public:
		s_wEvent(Event base,Date::Time SubLength):
		wEvent(base),subLength(SubLength){};
		s_wEvent(){};
		Date::Time subLength;
		virtual std::vector<Event>& eventGen(std::vector<Event>& ReturnValue);
        virtual void writeToFile(std::fstream& file);
        virtual void readFromFile(std::fstream& file);
        virtual std::string Type(){return "S";}
	};
	class sr_wEvent:public s_wEvent,public r_wEvent{
	//a merge of s_wEvent and r_wEvent. see the cpp file to why the current model is dated, function object
	//transition SOON
	public:
		sr_wEvent(Event base,Date::Time SubLength,Date::Time repeater,Date::Date trueEnd):
		wEvent(base),s_wEvent(base,SubLength),r_wEvent(base,repeater,trueEnd){};
		sr_wEvent(){};
		virtual std::vector<Event>& eventGen(std::vector<Event>& ReturnValue);
        virtual void writeToFile(std::fstream& file){
            this->s_wEvent::writeToFile(file);
            this->r_wEvent::writeToFile(file);
        }
        virtual void readFromFile(std::fstream& file){
            this->s_wEvent::readFromFile(file);
            this->r_wEvent::readFromFile(file);
        }
        virtual std::string Type(){return "SR";}
	};
	//right now I'm too lazy to actually build a good container class
	//I'm just going to overload ->
	class wEcontainer{
    public:
        std::vector<wEvent*> v;
        std::vector<Event>& EventGen(std::vector<Event>& ReturnValue){
            for(int i=0;i<v.size();i++) v[i]->eventGen(ReturnValue);
            return ReturnValue;
        }
		std::vector<Event>& eventGen(std::vector<Event>& ReturnValue){
			for(unsigned int i=0;i<v.size();i++){
				v[i]->eventGen(ReturnValue);
			}
			return ReturnValue;
		}
        ~wEcontainer(){
            for(int i=0;i<v.size();i++) delete v[i];
        }
	};
}
#endif
