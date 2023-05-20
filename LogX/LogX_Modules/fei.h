#ifndef __fei__ //fişierul fei.h
#define __fei__
#include <wx/wx.h>
#include "lx.h"
class iFEI : public wxDialog 
{ lxComboBox *cx_nrbr; lxEditT *cx_supplier; lxDPC *cx_datain; 
 lxGrid *cx_grid;
public: iFEI(wxWindow* parent, wxWindowID id = wxID_ANY, const wxString&
title = wxT("EDITARE INTRARI"), const wxPoint& pos = wxDefaultPosition, 
const wxSize& size = wxSize(700,549), long style = wxCAPTION|wxCLOSE_BOX|
wxDEFAULT_DIALOG_STYLE|wxMAXIMIZE_BOX|wxMINIMIZE_BOX|wxRESIZE_BORDER|
wxSYSTEM_MENU|wxALWAYS_SHOW_SB);
virtual ~iFEI();
protected: wxStaticText* t4; wxComboBox* cbBR;
 wxDatePickerCtrl* eDataBR; wxStaticText* t5; wxTextCtrl* eSupplierBR;
 wxButton* bAddBR; wxPanel* pBR; wxButton* bDelBR; wxButton* bSavBR;
 wxGrid* GD1; wxButton* bValidBR; wxButton* bAddLin; wxButton* bDelLin;
 wxButton* B_selNom; 
virtual void afis_BR(wxCommandEvent& event);
virtual void sav_BR(wxCommandEvent& event);
virtual void add_BR(wxCommandEvent& event);
virtual void add_Lin(wxCommandEvent& event);
virtual void del_Lin(wxCommandEvent& event);
virtual void sel_nom(wxCommandEvent& event); 
virtual void del_BR(wxCommandEvent& event); 
virtual void valid_BR(wxCommandEvent& event); 
virtual void GD1OnGridEditorShown(wxGridEvent& event);
virtual void GD1OnGridCellChange(wxGridEvent& event);
};
#endif //__fei__
