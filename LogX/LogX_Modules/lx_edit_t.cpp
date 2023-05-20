#include "lx_edit_t.h" //fişierul lx_edit_t.cpp
lxEditT::lxEditT(wxTextCtrl *ed1):lxCtrl()
{ ed=ed1;}
//------------------------------------------------------------------
//citirea DIN baza de date(BD) în cutia de editare
int lxEditT::rdSQL(wxString rdachQ)//rdSQL1-cda de citire DIN BD
{PGresult *rezultat; wxString ach;
 rezultat = PQexec(lxCtrl::conexiune0,rdachQ); /*comanda rdachQ trebuie
să întoarca o singură valoare (o înregistrare cu un singur câmp) */
if(PQresultStatus(rezultat) != PGRES_TUPLES_OK) 
{wxString ach; ach=ach.FromAscii(PQresultErrorMessage(rezultat)); 
 wxMessageBox(_("EROARE LA CITIRE: ")+rdachQ+_(" ("+ach+")!"));return -1;
 }
 ach=ach.FromAscii(PQgetvalue(rezultat, 0, 0));
 if(ach.IsEmpty()||ach.IsNull()) ach="";
 ed->SetValue(ach);
 return 0;
}
//--------------------------------------------------------------------
int lxEditT::wrSQL(wxString wrachQ)//wrSQL1-cda scrirere în baza de date
{PGresult *rezultat;
 wxString ach,achQ;
 ach=ed->GetValue();
 rezultat=PQexec(lxCtrl::conexiune0,wrachQ); 
 if(PQresultStatus(rezultat) != PGRES_COMMAND_OK) 
 { wxString ach; ach=ach.FromAscii(PQresultErrorMessage(rezultat)); 
 wxMessageBox(_("EROARE LA SCRIERE: ")+achQ+_(" ("+ach+")!"));return -1;
 }
 wxMessageBox("ACTUALIZAT !");
 return 0;
}
//--------------------------------------------------------------------
wxString lxEditT::getValFormatStr()
{ if(ed->GetValue().IsEmpty()) return _("NULL");
return _("'")+this->ed->GetValue()+_("'");
}
