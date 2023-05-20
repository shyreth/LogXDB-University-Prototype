#include "lx_dpc.h" //fişirul lx_dpc.cpp
lxDPC::lxDPC(wxDatePickerCtrl *dpc1):lxCtrl()
{ dpc=dpc1;
}
//----------------------------------------------------------------
//citirea DIN baza de date (BD) în cutia de editare
int lxDPC::rdSQL(wxString rdachQ) //rdachSQKL1 - cda de citire DIN BD
{PGresult *rezultat;
 wxString ach;
 rezultat = PQexec(lxCtrl::conexiune0,rdachQ);
 //comanda rdachQ trebuie să întoarcă o singură valoare 
 if(PQresultStatus(rezultat) != PGRES_TUPLES_OK) 
 { wxMessageBox(_("Interogare ptr. preluare eronata: ") + rdachQ + 
_(" !")); return -1;}
 wxDateTime achT1;// wxMessageBox(rdachQ);
 if(((int)PQftype(rezultat, 0))!=1082) 
 {wxMessageBox(_("Valoarea nu este de tip data calendaristica!"));return -1;}
 ach=ach.FromAscii(PQgetvalue(rezultat, 0, 0)); achT1.ParseISODate(ach);
dpc->SetValue(achT1);
 return 0;
 }
//-----------------------------------------------------------------
int lxDPC::wrSQL(wxString wrachQ) 
//wrachSQKL1 - cda de scrirere în baza de date 
{ PGresult *rezultat;
 rezultat=PQexec(lxCtrl::conexiune0,wrachQ); 
 if(PQresultStatus(rezultat) != PGRES_COMMAND_OK) 
 { wxMessageBox(_("Comanda actualizare eronata: ") + wrachQ + 
_(" !")); return -1;}
 wxMessageBox("ACTUALIZAT !");
 return 0;
}
//------------------------------------------------------------------
wxString lxDPC::getValFormatStr()
{ if(!dpc->GetValue().IsValid()) return _("NULL");
return _("'")+this->dpc->GetValue().FormatISODate()+_("'");

}
