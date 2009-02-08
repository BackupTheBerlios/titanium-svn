#include <wx/wxprec.h>
#ifdef __BORLANDC__
#pragma hdrstop
#endif
#ifndef WX_PRECOMPok
// Include your minimal set of headers here, or wx.h
#include <wx/wx.h>
#endif
#include "simple.h"

Simple::Simple(const wxString& title)
       : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(700,600))
{
  wxPanel* panel=new wxPanel(this);
  //spawns the list table in Report view mode(columns, whatnot)
  evtList=new wxListCtrl(this,wxID_ANY,wxPoint(10,10),wxSize(500,400),wxLC_REPORT);
  Centre();
}
