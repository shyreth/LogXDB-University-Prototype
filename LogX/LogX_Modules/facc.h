#ifndef __facc__ //fişierul facc.h
#define __facc__
#include <wx/wx.h>
#include "lx.h"
class iFACC : public wxDialog
{wxString rezX; public: static bool accesX;
iFACC(wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title
= wxT("Acces"), const wxPoint& pos = wxDefaultPosition, const wxSize&
size = wxSize(201,234), long style = wxDEFAULT_DIALOG_STYLE);
 ~iFACC();
protected: wxStaticText* t1; wxTextCtrl* e_alias; wxStaticText* t2;
wxTextCtrl* e_pw; wxButton* b42; wxStaticText* t3; wxTextCtrl* e_host;
wxStaticText* t4; wxTextCtrl* e_port; wxButton* bAcces;
virtual void schimbPW(wxCommandEvent& event);
virtual void acces(wxCommandEvent& event);
};
#endif