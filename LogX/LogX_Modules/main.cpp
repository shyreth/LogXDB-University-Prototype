#include "main.h"
#include "fei.h"
#include "fnom.h"
#include "selst.h"
#include "febp.h"
#include "facc.h"
#include "lx.h"
PGconn *lxCtrl::conexiune0;

IMPLEMENT_APP(LogXApp);
bool iFACC::accesX=false;
//-------------------------------------------------------------------
bool LogXApp::OnInit()
{ lxCtrl::conexiune0=NULL;
/*conexiunea iniţială pentru verificarea parolei de acces - se 
conectează cu parola la nivel de aplicaţie*/
lxCtrl::conectare(_("picdb"),_("logx_sw"),_("lilo"),_("localhost"),_("543
5"));
/* Prin "return true" se asigură menţinerea în aplicaţie
 în buclele de citire a evenimentelor şi de tratare a acestora*/
 (new iFACC(NULL))->ShowModal();
 if(iFACC::accesX)
 {(new iFPB(NULL))->Show(); return true;} 
//este lansată fereastra cu panoul cu butoane, nu este fereastră modală,
 else return false;
}
//-------------------------------------------------------------------
iFPB::iFPB(wxWindow* parent, wxWindowID id, const wxString& title, const 
wxPoint& pos, const wxSize& size, long style): wxFrame(parent, id, title,
pos, size, style)
{ this->SetSizeHints(wxDefaultSize, wxDefaultSize);
 this->SetFont(wxFont(wxNORMAL_FONT->GetPointSize(),70,90,90,false, wxEmptyString));
 this->SetBackgroundColour(wxColour(244, 244, 244));
 wxBoxSizer* s1; s1 = new wxBoxSizer(wxVERTICAL);
 t1 = new wxStaticText(this, wxID_ANY, wxT("LogX"), wxDefaultPosition, wxDefaultSize, 
wxALIGN_CENTRE);
 t1->Wrap(-1); t1->SetFont(wxFont(18,72,90,92,false,wxEmptyString));
 t1->SetHelpText(wxT("Exemplu pentru o aplicaţie simplă de gestiune a stocurilor."));
 s1->Add(t1, 0, wxALIGN_CENTER|wxALL, 5);
 wxBoxSizer* s2; s2 = new wxBoxSizer(wxHORIZONTAL);
 wxBoxSizer* s3; s3 = new wxBoxSizer(wxVERTICAL);
 t2 = new wxStaticText(this,wxID_ANY,wxT("EDITARE"), wxDefaultPosition, wxDefaultSize, 
wxALIGN_CENTRE);
 t2->Wrap(-1); t2->SetFont(wxFont(12,75,90,92,false,wxEmptyString));
 s3->Add(t2, 0, wxALIGN_CENTER|wxALL, 5);
 be1 = new wxButton(this, wxID_ANY, wxT("INTRĂRI"), wxDefaultPosition, wxDefaultSize, 0);
 be1->SetFont(wxFont(wxNORMAL_FONT->GetPointSize(),70,90,90,false, wxEmptyString));
 s3->Add(be1, 0, wxALL|wxEXPAND, 5);
 be2 = new wxButton(this, wxID_ANY, wxT("LIVRĂRI"), wxDefaultPosition, wxDefaultSize, 0);
 be2->SetFont(wxFont(wxNORMAL_FONT->GetPointSize(),70,90,90,false, wxEmptyString));
 s3->Add(be2, 0, wxALL|wxEXPAND, 5);
 be3 = new wxButton(this, wxID_ANY, wxT("TRANSFER"), wxDefaultPosition, wxDefaultSize, 0);
 be3->SetFont(wxFont(wxNORMAL_FONT->GetPointSize(),70,90,90,false, wxEmptyString));
 be3->Enable(false); s3->Add(be3, 0, wxALL|wxEXPAND, 5);
 be4 = new wxButton(this,wxID_ANY,wxT("NOMENCLATOR"),wxDefaultPosition, wxDefaultSize, 0);
 s3->Add(be4, 0, wxALL|wxEXPAND, 5); s2->Add(s3, 1, wxEXPAND, 5);
 wxBoxSizer* s4; s4 = new wxBoxSizer(wxVERTICAL);
 t3 = new wxStaticText(this,wxID_ANY,wxT("RAPOARTE"),wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE);
 
 t3->Wrap(-1); t3->SetFont(wxFont(12,75,90,92,false,wxEmptyString));
 s4->Add(t3, 0, wxALIGN_CENTER|wxALL, 5);
 br1 = new wxButton(this, wxID_ANY, wxT("INTRĂRI"), wxDefaultPosition, wxDefaultSize, 0);
 br1->SetFont(wxFont(wxNORMAL_FONT->GetPointSize(), 70, 90, 90, false, wxEmptyString));
 br1->Enable(false); s4->Add(br1, 0, wxALL|wxEXPAND, 5);
 br2=new wxButton(this, wxID_ANY, wxT("LIVRĂRI"), wxDefaultPosition, wxDefaultSize, 0);
 br2->SetFont(wxFont(wxNORMAL_FONT->GetPointSize(), 70, 90, 90, false, wxEmptyString));
 br2->Enable(false); s4->Add(br2, 0, wxALL|wxEXPAND, 5);
 br3=new wxButton(this, wxID_ANY, wxT("TRANSFER"), wxDefaultPosition, wxDefaultSize, 0);
 br3->Enable(false); s4->Add(br3, 0, wxALL|wxEXPAND, 5);
 br4 = new wxButton(this, wxID_ANY, wxT("STOC"), wxDefaultPosition, wxDefaultSize, 0);
 s4->Add(br4, 0, wxALL|wxEXPAND, 5); s2->Add(s4, 1, wxEXPAND, 5);
 s1->Add(s2, 1, wxEXPAND, 5); this->SetSizer(s1);
 this->Layout();
// Evenimente pentru conectare
be1->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(iFPB::apasa_be1), NULL, this);
be2->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(iFPB::apasa_be2), NULL, this);
be4->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(iFPB::apasa_be4), NULL, this);
br4->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(iFPB::apasa_br4), NULL, this);
}
//-----------------------------------------------------------------
iFPB::~iFPB()
{ lxCtrl::deconectare();
be1->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(iFPB::apasa_be1), NULL, this);
be2->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(iFPB::apasa_be2), NULL, this);
be4->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(iFPB::apasa_be4), NULL, this);
br4->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(iFPB::apasa_br4), NULL, this);
}
//------------------------------------------------------------------
void iFPB::apasa_be1(wxCommandEvent& event)
{ (new iFEI(this))->ShowModal(); 
}
//------------------------------------------------------------------
void iFPB::apasa_be4(wxCommandEvent& event)
{ (new iFNOM(this,NULL))->ShowModal(); 
}
//-----------------------------------------------------------------
void iFPB::apasa_br4(wxCommandEvent& event)
{ (new iFSELST(this,_("#")))->ShowModal(); 
}
//--------------------------------------------------------------------
void iFPB::apasa_be2(wxCommandEvent& event)
{(new iFEBP(this))->ShowModal(); 
}