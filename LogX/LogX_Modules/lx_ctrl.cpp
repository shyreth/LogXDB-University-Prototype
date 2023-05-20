#include "lx_ctrl.h" //fişierul lx_ctrl.cpp

lxCtrl::lxCtrl() { }
//-----------------------------------------------------------------
void lxCtrl::conectare(wxString dbname, wxString user, wxString pw, 
wxString host, wxString port)
 {wxString ach;
 char sir_conexiune[500];
 ach=wxT(" dbname=")+dbname+wxT(" user=")+user+wxT(" password=")+pw+wxT("
host=")+host+wxT(" port=")+port; 
 strcpy(sir_conexiune,ach.c_str());
lxCtrl::conexiune0 = PQconnectdb(sir_conexiune);
 if (PQstatus(lxCtrl::conexiune0) != CONNECTION_OK) 
 {PQfinish(lxCtrl::conexiune0); wxMessageBox("EROARE LA CONECTARE!");} 
 } 
 void lxCtrl::deconectare()
 {PQfinish(lxCtrl::conexiune0);
 }
//-------------------------------------------------------------------
 int lxCtrl::refreshlx() {return 0;}
//-----------------------------------------------------------------
wxString lxCtrl::cda(wxString achQ)
{PGresult *rezultat;
 rezultat = PQexec(lxCtrl::conexiune0,achQ);
 if((PQresultStatus(rezultat) != PGRES_COMMAND_OK) && 
(PQresultStatus(rezultat) != PGRES_TUPLES_OK))
 { wxString ach; 
ach=ach.FromAscii(PQresultErrorMessage(rezultat));
 wxMessageBox(_("EROARE CDA: ")+achQ+_(" ("+ach+")!")); return _(ach);}
 if(PQresultStatus(rezultat) == PGRES_TUPLES_OK) 
 { wxString achR=_("#");
 int nrCampuri = PQnfields(rezultat);
 int nrInregistrari=PQntuples(rezultat); 
 if(nrCampuri==1 && nrInregistrari==1) 
 achR=achR.FromUTF8(PQgetvalue(rezultat, 0, 0));
 return achR;
 }
return _("OK");
}
//------------------------------------------------------------------
//comanda ce întoarce o lista
wxString lxCtrl::lista(wxString achQ, wxArrayString & a)
{PGresult *rezultat;
 rezultat = PQexec(lxCtrl::conexiune0,achQ);
 if((PQresultStatus(rezultat) != PGRES_COMMAND_OK) && 
(PQresultStatus(rezultat) != PGRES_TUPLES_OK))
 { wxString ach; ach=ach.FromAscii(PQresultErrorMessage(rezultat));
 wxMessageBox(_("EROARE CDA: ")+achQ+_(" ("+ach+")!")); return _(ach);}
 if(PQresultStatus(rezultat) == PGRES_TUPLES_OK) 
 { wxString achR=_("#");
int nrCampuri = PQnfields(rezultat); int 
nrInregistrari=PQntuples(rezultat); 
if(nrCampuri!=1) return wxT("Comanda SQL întoarce mai mult de o coloană !");
 a.Clear(); 
 for(int i=0; i<nrInregistrari; i++) 
a.Add(achR.FromUTF8(PQgetvalue(rezultat, i, 0))); 
return achR; 
 }
return _("OK");
}