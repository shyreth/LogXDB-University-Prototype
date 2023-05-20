#ifndef __main__
#define __main__
#include <wx/wx.h>
class LogXApp : public wxApp //clasa ce implementează buclele de
evenimente
{public: virtual bool OnInit(); /* ieşirea din metoda OnInit echivalează
cu ieşirea din aplicaţie */
};
DECLARE_APP(LogXApp)
class iFPB : public wxFrame
{ public:
iFPB(wxWindow* parent, wxWindowID id = wxID_ANY, const wxString&
title = wxT("GESTIUNE STOCURI"), const wxPoint& pos = wxDefaultPosition,
const wxSize& size = wxSize(230,251), long style = wxCAPTION|wxCLOSE_BOX|
wxMINIMIZE_BOX|wxSTAY_ON_TOP|wxSYSTEM_MENU|wxTAB_TRAVERSAL);
virtual ~iFPB();
protected: wxStaticText* t1; wxStaticText* t2; wxButton* be1; wxButton*
be2; wxButton* be3; wxButton* be4; wxStaticText* t3; wxButton* br1;
wxButton* br2; wxButton* br3; wxButton* br4;
virtual void apasa_be1(wxCommandEvent& event);
virtual void apasa_be2(wxCommandEvent& event);
virtual void apasa_be4(wxCommandEvent& event);
virtual void apasa_br4(wxCommandEvent& event);
};
#endif //__main__
