#include "lx_edit_n.h" // fişierul lx_edit_n.cpp
lxEditN::lxEditN(wxTextCtrl *ed1):lxCtrl()
{ ed=ed1;}
//-------------------------------------------------------------------
//citirea DIN baza de date în cutia de editare
int lxEditN::rdSQL(wxString rdachQ) // - cda de citire DIN baza de date
{PGresult *rezultat;
 wxString ach;
 rezultat = PQexec(lxCtrl::conexiune0,rdachQ);/*comanda din rdachQ 
trebuie să întoarca o singură valoare (o înregistrare - un câmp)*/
if(PQresultStatus(rezultat) != PGRES_TUPLES_OK)
{wxString ach; ach=ach.FromAscii(PQresultErrorMessage(rezultat)); 
 wxMessageBox(_("EROARE LA CITIRE: ")+rdachQ+_(" ("+ach+")!"));return -1;
 }
 ach=ach.FromAscii(PQgetvalue(rezultat, 0, 0));
 ed->SetValue(ach);
return 0; 
}
//--------------------------------------------------------------
int lxEditN::wrSQL(wxString wrachQ) // - cda de scrirere în baza de date
{PGresult *rezultat;
 wxString ach,achQ;
 ach=ed->GetValue();
 rezultat=PQexec(lxCtrl::conexiune0,wrachQ); 
 if(PQresultStatus(rezultat) != PGRES_COMMAND_OK) 
 {wxString ach; ach=ach.FromAscii(PQresultErrorMessage(rezultat)); 
 wxMessageBox(_("EROARE LA SCRIERE: ")+achQ+_(" ("+ach+")!"));return -1;
 }
 wxMessageBox("ACTUALIZAT !");
 return 0;
}
//------------------------------------------------------------------
wxString lxEditN::getValFormatStr()
{ if(ed->GetValue().IsEmpty()) return _("NULL");
return this->ed->GetValue();
}
