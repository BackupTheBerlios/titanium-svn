#include <iostream>
#include "organise.h"
#include "ustd.h"
evt::wEvent* assign();
using std::endl;
int main(){
    //These first functions put the data in some temp files, to avoid any file corruption
    std::fstream cal("trash.dar",std::ios::in);
    std::fstream trash("trash.tmp",std::ios::out|std::ios::trunc);
    ustd::copyStream(cal,trash);
    std::cin.get();
    cal.close();
    cal.clear();
    cal.open("calen.dar",std::ios::in);
    trash.close();
    trash.clear();
    trash.open("calen.tmp",std::ios::out|std::ios::trunc);
    ustd::copyStream(cal,trash);
    cal.close();cal.clear();cal.open("calen.tmp",std::ios::in);
    trash.close();trash.clear(); trash.open("trash.tmp",std::ios::in);
    evt::wEcontainer tCal,tTrash;
    std::cin.get();
    readFromFile(tCal,cal);
    readFromFile(tTrash,trash);
    std::vector<evt::wEvent*>& tCalVec=tCal.v;
    std::vector<evt::wEvent*>& tTrashVec=tTrash.v;
    //calculate calendar

    evtlist tSorter;
    tCal.EventGen(tSorter);
    calendar Caldar;
    Organise(&tSorter,&Caldar);
    tSorter.clear();
    std::cout<<"Welcome to Titanium(CLI edition) \n"
             <<"The Todo list that does it for you\n";
    int choice=9;
    while(choice!=6 && choice !=7){
        std::cout<<"\n\n\n\n\n\n\n\n1. View List"<<endl
                 <<"2. View Garbage"<<endl
                 <<"3. View Events"<<endl
                 <<"4. Help"<<endl
                 <<"5. Save"<<endl
                 <<"6. Save & Quit"<<endl
                 <<"7. Quit without Saving"<<endl<<endl<<endl
                 <<"\t input choice:";
        std::cin>>choice;
        ReChoice://for switching menus
        std::cout<<"\n\n\n\n\n\n\n\n\n\n\n\n";//Clear screen
        //other Choices:
        //8: create events
        switch(choice){
            case 1:
                std::cout<<"   Name          Length               End            Overdue\n";//10 spaces
                for(int i=0;i<Caldar.size();++i){
                    evt::Event tBase=Caldar[i].second;
                    std::cout<<i<<". "
                             <<tBase.Name<<"\t"
                             <<tBase.length().str()<<"\t"
                             <<tBase.End.str()<<"\t"
                             <<(Caldar[i].first?"YES":"NO");
                }
                std::cout<<"\n\n\n1. Finished Event"<<endl
                         <<"2.Add Event"<<endl
                         <<"3.Remove Events"<<endl
                         <<"4.View Garbage"<<endl
                         <<"5.Main Menu"<<endl;
                int j;
                std::cin>>j; j--;
                switch(j){
                    case 0:
                        std::cout<<endl<<"Which event did you finish(Index number)?";
                        std::cin>>choice;
                        if(choice<1 || choice >=Caldar.size()){
                            choice=1;
                            std::cout<<"Index error, Event does not exist";
                            goto ReChoice;
                        }
                        else{
                            Caldar.erase(Caldar.begin()+choice-1,Caldar.begin()+choice);
                            choice=1;
                            goto ReChoice;
                        }
                        break;
                    case 1:
                        choice=8;
                        goto ReChoice;
                        break;
                    case 2:
                        choice=3;
                        goto ReChoice;
                        break;
                    case 3:
                        choice=2;
                        goto ReChoice;
                        break;
                    case 4:
                        break;
                    default:
                    //This is easier to do, I'll fix it later
                        std::cout<<"Invalid input, returning to main menu"<<endl;
                        break;
                }
                break;
            case 2:
                std::cout<<"Name"<<endl;
                for(int i=0;i<tTrashVec.size();++i){
                    evt::Event tBase=tTrashVec[i]->Base;
                    std::cout<<i<<". "
                             <<tBase.Name<<"\n";
                }
                std::cout<<"\n\n 1. Recover Event"<<endl
                         <<"2.Delete Event"<<endl
                         <<"3.Main Menu"<<endl;
                j=0;
                std::cin>>j;
                switch(j){
                    case 1:
                        std::cout<<endl<<"Which event do you want to recover(Index number)?";
                        std::cin>>choice;
                        if(choice<1 || choice >=tTrashVec.size()){
                            choice=2;
                            std::cout<<"Index error, Event does not exist";
                            goto ReChoice;
                        }
                        else{
                            tCalVec.push_back(tTrashVec[choice-1]);
                            tTrashVec.erase(tTrashVec.begin()+choice-1,tTrashVec.begin()+choice);
                            //recalculate
                            tCal.EventGen(tSorter);
                            Caldar.clear();
                            Organise(&tSorter,&Caldar);
                            tSorter.clear();
                            //end recalculate
                            choice=2;
                            goto ReChoice;
                        }
                        break;
                    case 2:
                        std::cout<<endl<<"Which event do you want to recover(Index number)?";
                        std::cin>>choice;
                        if(choice<1 || choice >=tTrashVec.size()){
                            choice=2;
                            std::cout<<"Index error, Event does not exist";
                            goto ReChoice;
                        }
                        else{
                            tTrashVec.erase(tTrashVec.begin()+choice-1,tTrashVec.begin()+choice);
                            choice=2;
                            goto ReChoice;
                        }
                        break;
                    case 3:
                        choice=1;
                        goto ReChoice;
                        break;
                }
                break;
            case 3:
		   std::cout<<"Name"<<endl;
                for(int i=0;i<tCalVec.size();++i){
                    evt::Event tBase=tCalVec[i]->Base;
                    std::cout<<i<<". "
                             <<tBase.Name<<"\n";
                }
        }
    }

    return 0;

}
void dateInput(Date::Date& in){
	int Year,Month,Day,Hour,Min,Sec;
	std::cin>>Year>>Month>>Day>>Hour>>Min>>Sec;
	tm temp;
	//man ctime for details
	temp.tm_sec=Sec;
	temp.tm_min=Min;
	temp.tm_hour=Hour;
	temp.tm_mday=Day;
	temp.tm_mon=Month-1;
	temp.tm_year=Year-1900;
	in=Date::Date(true,long(mktime(&temp)));
}
void timeInput(Date::Time& in){
	int Hour,Min,Sec;
	tm temp;
	std::cin>>Hour>>Min>>Sec;
	temp.tm_hour=Hour;
	temp.tm_min=Min;
	temp.tm_sec=Sec;
	in=Date::Time(true,ustd::mktime(&temp,false));
}
void timeInput2(Date::Time& in){
	int Year,Month,Day,Hour,Min,Sec;
	std::cin>>Year>>Month>>Day>>Hour>>Min>>Sec;
	tm temp;
	//man ctime for details
	temp.tm_sec=Sec;
	temp.tm_min=Min;
	temp.tm_hour=Hour;
	temp.tm_mday=Day;
	temp.tm_mon=Month;
	temp.tm_year=Year-1900;
	in=Date::Time(true,ustd::mktime(&temp,true));
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
    std::cin.get();
	std::cout<<"\n Name \n ";
	getline(std::cin,name);
	std::cout<<"\n Length \n HH MM SS \n ";
	timeInput(length);
	std::cout<<"\n Start \n YYYY MM DD HH MM SS\n ";
	dateInput(start);
	std::cout<<"\n End \n YYYY MM DD HH MM SS\n ";
	dateInput(end);
	evt::Event Base(name,length,start,end);
	if(x & 2){ //2,6
		std::cout<<"\nRepeater \n YYYY MM DD HH MM SS\n";
		timeInput2(repeater);
		std::cout<<"\n True end \n YYYY MM DD HH MM SS\n";
		dateInput(TrueEnd);
	}
	if(x & 4){//4,6
		std::cout<<"\n sublength \n HH MM SS\n";
		timeInput(sublength);
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
