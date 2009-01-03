#include <iostream>
#include "organise.h"
int main(){
    evtlist main;
    calendar secondary;
    std::fstream cal("calen.dar");
    for(int i=0;i<3;i++){
        std::string name;
        int a,b,c;
        std::cin>>name>>a>>b>>c;
        evt::Event temp(name,a,b,c);
        main.push_back(temp);
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
