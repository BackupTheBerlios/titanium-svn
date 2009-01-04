#include <iostream>
#include "organise.h"
evt::wEvent* assign();
int main(){
    evtlist main;
    calendar secondary;
    evt::wEcontainer tMain;
    std::fstream cal("calen.dar");
    for(int i=0;i<3;i++){

    }
    writeToFile(main,cal);
    std::cout<<"sorting file"<<"\n";
    Organise(&main,&secondary);
    for(int i=0;i<3;i++){
        evt::Event bob=secondary[i].second;
        std::cout<<bob.Name<<" "<<bob.Start<<" "<<bob.End<<" "<<bob.Length<<"\n";
    }
    return 0;

}
Date::Date dateInput(){
	int Year,Month,Day,Hour,Min,Sec;
	std::cin>>Year>>Month>>Day>>Hour>>Min>>Sec;
	tm temp;
	//man ctime for details
	temp.tm_sec=Sec;
	temp.tm_min=Min;
	temp.tm_hour=Hour;
	temp.tm_mday=Day;
	temp.tm_mon=Month-1;
	temp.tm_year=Year-1970;
	return Date::Date(true,long(mktime(&temp)));
}
Date::Time timeInput(){
	int Hour,Min,Sec;
	tm temp;
	std::cin>>Hour>>Min>>Sec;
	temp.tm_hour=Hour;
	temp.tm_min=Min;
	temp.tm_sec=Sec;
	return Date::Time(true,mktime(&temp));
}
Date::Time timeInput2(){
	int Year,Month,Day,Hour,Min,Sec;
	std::cin>>Year>>Month>>Day>>Hour>>Min>>Sec;
	tm temp;
	//man ctime for details
	temp.tm_sec=Sec;
	temp.tm_min=Min;
	temp.tm_hour=Hour;
	temp.tm_mday=Day;
	temp.tm_mon=Month;
	temp.tm_year=Year-1970;
	return Date::Time(true,mktime(&temp));
}
evt::wEvent* assign(){
	evt::wEvent* ReturnValue;
    std::cout<<"What kind of event do you want?\n"
             <<"1.Normal\n"
             <<"2.Repeating\n"
             <<"4.Sequential\n"
             <<"6.Repeating and sequential \n";
    int x;
    std::string name;
	Date::Time length,repeater,sublength;
	Date::Date start,TrueEnd;
	Date::Date end;
    std::cin>>x;
	std::cout<<"\n Name"<<std::endl;
	std::cin>>name;
	std::cout<<"\n Length \n HH MM SS \n";
	length=timeInput();
	std::cout<<"\n Start \n YYYY MM DD HH MM SS\n";
	start=dateInput();
	std::cout<<"\n End \n YYYY MM DD HH MM SS\n";
	end=dateInput();
	evt::Event Base(name,length,start,end);
	if(x & 2){ //2,6
		std::cout<<"\nRepeater \n YYYY MM DD HH MM SS\n";
		repeater=timeInput2();
		std::cout<<"\n True end \n YYYY MM DD HH MM SS\n";
		TrueEnd=dateInput();
	}
	if(x & 4){//4,6
		std::cout<<"\n sublength \n HH MM SS\n";
		sublength=timeInput();
	}
	switch(x){
		case 1:
			evt::wEvent* temp1=new evt::wEvent(Base);
			ReturnValue=temp1;
			break;
		case 2:
			evt::wEvent* temp2=new evt::r_wEvent(Base,repeater,TrueEnd);
			ReturnValue=temp2;
			break;
		case 4:
			evt::wEvent* temp3=new evt::s_wEvent(Base,sublength);
			ReturnValue=temp3;
			break;
		case 6:
			evt::wEvent* temp4=new evt::sr_wEvent(Base,sublength,repeater,TrueEnd);
			ReturnValue=temp4;
			break;
	}
	return ReturnValue;
}
