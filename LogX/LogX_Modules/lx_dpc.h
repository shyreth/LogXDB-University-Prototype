#ifndef _lxDPC_ //fişierul lx_dpc.h
#define _lxDPC_ 
#include <wx/wx.h>
#include <wx/datectrl.h>
#include "lx_ctrl.h"
class lxDPC:public lxCtrl
{ wxDatePickerCtrl *dpc;
public: lxDPC(wxDatePickerCtrl *dpc1);
int rdSQL(wxString rdachQ1);
int wrSQL(wxString wrachQ1);
wxString getValFormatStr();
};
#endif