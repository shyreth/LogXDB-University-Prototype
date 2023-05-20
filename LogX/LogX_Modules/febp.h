#ifndef __febp__ //fişier febp.h
#define __febp__
#include <wx/wx.h>
#include "lx.h"
class iFEBP : public wxDialog 
{public:iFEBP(wxWindow* parent, wxWindowID id = wxID_ANY, const wxString&
title = wxT("LIVRĂRI"), const wxPoint& pos = wxDefaultPosition, const
wxSize& size = wxSize(598,499), long style = wxCLOSE_BOX|
wxDEFAULT_DIALOG_STYLE|wxMAXIMIZE_BOX|wxMINIMIZE_BOX|wxRESIZE_BORDER);
virtual ~iFEBP();
protected: wxStaticText* t1; wxComboBox* cbBP; wxButton* bAddBP;
wxDatePickerCtrl* eDataBP; wxStaticText* t2; wxTextCtrl* eDestinBP;
wxButton* bDelBP; wxPanel* pBP; wxGrid* GD1; wxButton* bDelLin; wxButton*
bSelST; wxButton* bValidBP;
virtual void afis_BP(wxCommandEvent& event);
virtual void addBP(wxCommandEvent& event);
virtual void delBP(wxCommandEvent& event);
virtual void delLin(wxCommandEvent& event);
virtual void selST(wxCommandEvent& event);
virtual void validBP(wxCommandEvent& event);
wxString achBP; lxEditT *cx_destin;lxComboBox *cx_nrbp; lxDPC 
*cx_databp; lxGrid *cx_grid;
};
#endif //__febp__