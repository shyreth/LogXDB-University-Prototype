#ifndef _lxEditT_ //fişierul lx_edit_t.h
#define _lxEditT_ 
#include <wx/wx.h>
#include "lx_ctrl.h"
/*clasa asigură o legătură între un control wxTextControl şi o valoare
dintr-o bază de date de tip text, se presupune că ambele există înainte
de instanţierea clasei */
class lxEditT: public lxCtrl
{wxTextCtrl *ed; public: lxEditT(wxTextCtrl *ed1);
int rdSQL(wxString rdachQ1);
int wrSQL(wxString wrachQ1);
wxString getValFormatStr(); };
#endif
