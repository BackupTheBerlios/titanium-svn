#include <wx/wxprec.h>
#ifdef __BORLANDC__
#pragma hdrstop
#endif
#ifndef WX_PRECOMP
// Include your minimal set of headers here, or wx.h
#endif
#include <wx/wx.h>
#include <wx/listctrl.h>
class Simple : public wxFrame
{
public:
    Simple(const wxString& title);
	wxListCtrl* evtList;
};
