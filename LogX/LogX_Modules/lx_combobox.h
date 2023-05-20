#ifndef _lxComboBox_ //fişierul lx_combobox.h
#define _lxComboBox_ 
#include <wx/wx.h>
#include "lx_ctrl.h"
//clasa asigură o legătură între un contrl ComboBox şi o bază de date
// se presupune că ambele există înainte de instanţierea clasei
class lxComboBox:public lxCtrl
{wxComboBox *cb;
int tipdata;
wxString achQRD; 
 public: 
lxComboBox(wxComboBox *cb1, wxString achQ1);
int rdLista(wxString achQ1);//reactualizeaza lista în urma actualizării
bazei de date
int refreshlx();
wxString getSel();
};
#endif