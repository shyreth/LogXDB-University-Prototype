#ifndef _lxEditN_ //fişierul lx_edit_n.h
#define _lxEditN_ 
#include <wx/wx.h>
#include "lx_ctrl.h"
/*clasa asigură o legătură între un contrl wxTextControl şi o valoare
dintr-o bază de date de tip numeric, se presupune că ambele există
înainte de instanţierea clasei */
class lxEditN:public lxCtrl
{wxTextCtrl *ed; public:
lxEditN(wxTextCtrl *ed1);
int rdSQL(wxString rdachQ1);
int wrSQL(wxString wrachQ1);
wxString getValFormatStr();
};
#endif