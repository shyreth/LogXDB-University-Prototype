 #include "lx_combobox.h" //lx_combobox.cpp
lxComboBox::lxComboBox(wxComboBox *cb1, wxString achQ):lxCtrl()
{ cb=cb1; tipdata=0; achQRD=achQ; rdLista(achQ); }
int lxComboBox::rdLista(wxString achQ)
{PGresult *rezultat;
 int nrInregistrari;
 wxString ach,ach_dmy;
 rezultat = PQexec(lxCtrl::conexiune0,achQ);
 if(PQresultStatus(rezultat) != PGRES_TUPLES_OK) 
 { wxString ach; ach=ach.FromAscii(PQresultErrorMessage(rezultat)); 
 wxMessageBox(_("EROARE LA CITIRE: ")+achQ+_(" ("+ach+")!")); return -1;
 }
 nrInregistrari=PQntuples(rezultat);
 cb->Clear();
 int tipData=PQftype(rezultat,0);
wxDateTime achT1;
for(int i = 0; i < nrInregistrari; i++) {
if(tipData==1082) { //1082 date
ach=ach.FromAscii(PQgetvalue(rezultat, i, 0));
achT1.ParseISODate(ach);
achT1.ParseFormat(ach,wxT("%d.%m.%Y"));
cb->AppendString(ach);}
else {ach=ach.FromAscii(PQgetvalue(rezultat, i, 0));
cb->AppendString(ach);} //end if
 }//endfor i
return -1;
}
//-----------------------------------------------------------------
wxString lxComboBox::getSel()
{ return cb->GetStringSelection();
}
//-----------------------------------------------------------------
int lxComboBox::refreshlx()
{ rdLista(achQRD); return 0;
}