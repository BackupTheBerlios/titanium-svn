#include <wx/wxprec.h>
#ifdef __BORLANDC__
#pragma hdrstop
#endif
#ifndef WX_PRECOMP
// Include your minimal set of headers here, or wx.h
#include <wx/wx.h>
#endif
#include <fstream>
#include <vector>
#include "organise.h"
#include "ustd.h"
class MyWindow: public wxApp
{
  public:
    virtual bool OnInit();
  private:
	std::fstream cal;
	std::fstream trash;
	evt::wEcontainer* tCal,*tTrash;
	evtlist* tSorter;
	calendar* Caldar;
	
};
