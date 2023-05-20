//fişierul lx_ctrl.h
#ifndef _lxCtrl_ //previne includerea multipla : dacă nu EXISTĂ _lxCtrl_
#define _lxCtrl_ // defineste _lxCtrl_
#include <libpq-fe.h>
#include <wx/wx.h>
class lxCtrl
{public:
 static PGconn *conexiune0;
 lxCtrl();
static void conectare(wxString dbname, wxString user, wxString pw,
wxString host, wxString port);
 static void deconectare();
 static wxString cda(wxString achSQL);
 static wxString lista(wxString achQ, wxArrayString& a);/*comandă ce are
ca rezultat un singur câmp, valorile rezultate vor fi transmise prin
referinţă sub forma unei liste cu elemente de tip wxString */
 virtual int refreshlx();
};
#endif //închide condiţia