﻿#include "event.h"
/**
  *A couple developement notes:
  *	If you make a direct derivation of wEvent, don't forget to virtualise, to support  merging
  *		I'll probably try and build a "better" system with function objects later. Granted, this will
  *		break code, but it looks cleaner. But for now I only see two variants, so we'll keep it like
  *		for now. 4 classes is easy to handle. 12 classes is not, however.
  */
namespace evt{
	class wEvent{
	public:
		//for those who don't get the constructor notation, see [Bjarne-くん,1998], 11.3.4
		wEvent(Event base):Base(base);//I will personally shoot the first person who says capital overloading is bad form
		Event Base;
		virtual std::vector<Event>& eventGen(std::vector<Event>& ReturnValue);
		//yeah, my variable names aren't imaginative, sue me
		//(don't sue me, I  lack enough money as it is)
	};
	class r_wEvent:public virtual wEvent{
	//repeating event,  repeats every  repeater until trueend
	//(note, we add repeater to the start)
	public:
		r_wEvent(Event base,Time repeater,Date trueEnd):
		wEvent(base),Repeater(repeater),TrueEnd(trueEnd);
		Time Repeater;
		Date TrueEnd;
		virtual std::vector<Event>& eventGen(std::vector<Event>& ReturnValue);
	};
	class s_wEvent:public virtual wEvent{
	//This time we're cutting the  event up into bits of length SubLength
	public:
		s_wEvent(Event base,Time SubLength):
		wEvent(base),subLength(SubLength);
		Time subLength;
		virtual std::vector<Event>& eventGen(std::vector<Event>& ReturnValue);
	};
	class sr_wEvent:public s_wEvent,public r_wEvent{
	//a merge of s_wEvent and r_wEvent. see the cpp file to why the current model is dated, function object
	//transition SOON
	public:
		sr_wEvent(Event base,Time SubLength,Time repeater,Date trueEnd):
		s_wEvent(base,SubLength),r_wEvent(base,repeater,trueEnd);
		virtual stD::vector<Event>& eventGen(std::vector<Event>& ReturnValue);
	};
}
