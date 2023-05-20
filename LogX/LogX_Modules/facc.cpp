#include "facc.h" //fişierul facc.cpp
iFACC::iFACC(wxWindow* parent, wxWindowID id, const wxString& title, 
const wxPoint& pos, const wxSize& size, long style) : wxDialog(parent, 
id, title, pos, size, style)
{ this->SetSizeHints(wxDefaultSize, wxDefaultSize);
wxBoxSizer* s1; s1 = new wxBoxSizer(wxVERTICAL);
wxFlexGridSizer* s2; s2 = new wxFlexGridSizer(0, 2, 0, 0);
s2->SetFlexibleDirection(wxBOTH);
s2->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_SPECIFIED);
t1 = new wxStaticText(this, wxID_ANY, wxT("Utilizator"), wxDefaultPosition, wxDefaultSize, 0);
t1->Wrap(-1); s2->Add(t1, 0, wxALL, 5);
e_alias = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0);
s2->Add(e_alias, 0, wxALL, 5);
t2 = new wxStaticText(this, wxID_ANY, wxT("Cod acces"), wxDefaultPosition, wxDefaultSize, 0);
t2->Wrap(-1); s2->Add(t2, 0, wxALL, 5);
e_pw = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 
wxTE_PASSWORD|wxTE_PROCESS_ENTER); s2->Add(e_pw, 0, wxALL, 5);
s1->Add(s2, 0, wxEXPAND, 5);
b42 =new wxButton(this,wxID_ANY,wxT("SCHIMBARE PAROLĂ"),wxDefaultPosition,wxDefaultSize,0);
b42->SetFont(wxFont(wxNORMAL_FONT->GetPointSize(), 70, 94, 90, false, wxEmptyString));
s1->Add(b42, 0, wxALIGN_CENTER|wxALL, 5);
wxFlexGridSizer* s3; s3 = new wxFlexGridSizer(0, 2, 0, 0);
s3->SetFlexibleDirection(wxBOTH);
s3->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_SPECIFIED);
t3 = new wxStaticText(this, wxID_ANY, wxT("IP server PG"), wxDefaultPosition, wxDefaultSize, 0);
t3->Wrap(-1); s3->Add(t3, 0, wxALL, 5);
e_host = new wxTextCtrl(this, wxID_ANY, wxT("localhost"), wxDefaultPosition, wxDefaultSize, 0);
s3->Add(e_host, 0, wxALL, 5);
t4 = new wxStaticText(this, wxID_ANY, wxT("Port"), wxDefaultPosition, wxDefaultSize, 0);
t4->Wrap(-1); s3->Add(t4, 0, wxALL, 5);
e_port = new wxTextCtrl(this, wxID_ANY, wxT("5435"), wxDefaultPosition, wxDefaultSize, 0);
s3->Add(e_port, 0, wxALL, 5); s1->Add(s3, 0, wxEXPAND, 5);
bAcces = new wxButton(this, wxID_ANY, wxT("ACCES"), wxDefaultPosition, wxDefaultSize, 0);
bAcces->SetFont(wxFont(wxNORMAL_FONT->GetPointSize(), 70, 90, 92, false, wxEmptyString));
s1->Add(bAcces, 0, wxALIGN_CENTER|wxALL, 5);
this->SetSizer(s1); this->Layout(); this->Centre(wxBOTH);
b42->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(iFACC::schimbPW), NULL, this);
bAcces->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(iFACC::acces), NULL, this);
iFACC::accesX=false;
}
//------------------------------------------------------------------
iFACC::~iFACC() {
b42->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(iFACC::schimbPW), NULL, this);
bAcces->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(iFACC::acces), NULL, this);
}
//----------------------------------------------------------------
void iFACC::schimbPW(wxCommandEvent& event) 
{ wxString pw1,pw2;
 rezX=lxCtrl::cda(_("SELECT EXISTS(select * FROM logx.acces WHERE 
alias='")+e_alias->GetValue()+_("' AND pw='")+e_pw->GetValue()+_("') AS 
acces_permis;"));
 if(rezX!=_("t")) 
 { wxMessageBox(wxT("Alias nume sau parolă incorecte!")); return;}
 pw1=wxGetPasswordFromUser(wxT("1.Introduceţi noul cod de acces!")); 
 pw2=wxGetPasswordFromUser(wxT("1.Introduceţi noul cod de acces!"));
 if(pw1!=pw2) { wxMessageBox(wxT("Cele două parole nu coincid!")); 
return;}
 rezX=lxCtrl::cda(_("UPDATE logx.acces SET pw='")+pw1+_("' WHERE 
alias='")+e_alias->GetValue()+_("';"));
 wxMessageBox(rezX); 
}
//---------------------------------------------------------------
void iFACC::acces(wxCommandEvent& event) 
{ wxString pw1,pw2,pw, pwN,ach;
 rezX=lxCtrl::cda(_("SELECT EXISTS(select * FROM logx.acces WHERE 
alias='")+e_alias->GetValue()+_("' AND pw='")+e_pw->GetValue()+_("') AS 
acces_permis;"));
if(rezX!=_("t")) 
 { wxMessageBox(wxT("Alias nume sau parolă incorecte!"));
 iFACC::accesX=false; return;
 } 
srand(time(NULL));//iniţializare generator numere aleatoare
pwN = _("123-")+ach.FromDouble(rand());
rezX=lxCtrl::cda(_("DROP ROLE IF EXISTS \"#")+e_alias->GetValue()+_("#\";
CREATE ROLE \"#")+e_alias->GetValue()+_("#\" LOGIN PASSWORD '")+pwN +
 _("' CONNECTION LIMIT 1; GRANT \"LOGX\" TO \"#")+e_alias-
>GetValue()+_("#\"; SET ROLE \"#")+e_alias->GetValue()+_("#\";"));
if(rezX!=_("OK")) 
 wxGetTextFromUser(_("Mesaj de eroare"), _("Err 101"), rezX); 
iFACC::accesX=((rezX==_("t"))||(rezX==_("OK")));
this->Destroy();//distruge fereastra principală şi continuă codul din OnInit()
}