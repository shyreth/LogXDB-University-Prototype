#define __fnom__
#include <wx/wx.h>
#include "lx.h"
class iFNOM : public wxDialog
{public:iFNOM(wxWindow* parent, wxArrayString* rez1, wxWindowID id =
wxID_ANY, const wxString& title = wxT("Nomenclator produse"), const
wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize,
long style = wxCLOSE_BOX|wxDEFAULT_DIALOG_STYLE|wxMAXIMIZE_BOX|
wxMINIMIZE_BOX|wxRESIZE_BORDER);
virtual ~iFNOM();
protected:wxRadioBox* rOrd; wxGrid* GD1; wxPanel* pEdit; wxButton* bAdd; 
wxButton* bDel; wxButton* bSav; wxButton* bRenEdit; wxButton* bEdit; 
wxButton* bSel; wxButton* bRenNom;
 void afis_NOM();
virtual void ordoneaza(wxCommandEvent& event); 
virtual void add_Lin(wxCommandEvent& event);
virtual void del_Lin(wxCommandEvent& event);
virtual void salveaza(wxCommandEvent& event);
virtual void ren_Edit(wxCommandEvent& event);
virtual void editare(wxCommandEvent& event);
virtual void selecteaza(wxCommandEvent& event);
virtual void ren_Nom(wxCommandEvent& event);
wxArrayString *rez, ord; int nr_ord; lxGrid *cx_grid; 
};
#endif