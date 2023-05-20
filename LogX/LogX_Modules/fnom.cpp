#include <wx/valgen.h>
#include "fnom.h"
iFNOM::iFNOM(wxWindow* parent, wxArrayString* rez1, wxWindowID id, const 
wxString& title, const wxPoint& pos, const wxSize& size, long style) :
wxDialog(parent, id, title, pos, size, style)
{this->SetSizeHints(wxDefaultSize, wxDefaultSize);
 wxBoxSizer* s1; s1 = new wxBoxSizer(wxVERTICAL);
 wxString rOrdChoices[] = { wxT("RefCom"), wxT("RefTeh"), 
wxT("Descriere"), wxT("idCode") };
 int rOrdNChoices = sizeof(rOrdChoices) / sizeof(wxString);
 rOrd = new wxRadioBox(this, wxID_ANY, wxT("Ordonare după:"), wxDefaultPosition, wxDefaultSize, 
rOrdNChoices, rOrdChoices, 1, wxRA_SPECIFY_ROWS); rOrd->SetSelection(2); 
 rOrd->SetForegroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_WINDOWTEXT));
 rOrd->SetValidator(wxGenericValidator(&nr_ord));s1->Add(rOrd,0,wxALL,5);
 GD1 = new wxGrid(this, wxID_ANY, wxDefaultPosition, wxSize(300,200), 0);
 GD1->CreateGrid(0,0); GD1->EnableEditing(true); 
 GD1->EnableGridLines(true);
 GD1->EnableDragGridSize(false); GD1->SetMargins(0, 0);
 GD1->EnableDragColMove(false); GD1->EnableDragColSize(true);
 GD1->SetColLabelSize(30);
 GD1->SetColLabelAlignment(wxALIGN_CENTRE, wxALIGN_CENTRE);
 GD1->EnableDragRowSize(true);GD1->SetRowLabelSize(80);
 GD1->SetRowLabelAlignment(wxALIGN_CENTRE, wxALIGN_CENTRE);
 GD1->SetDefaultCellAlignment(wxALIGN_LEFT, wxALIGN_TOP);
 s1->Add(GD1, 1, wxALL|wxEXPAND, 5);
 pEdit = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
 wxBoxSizer* s2Nom; s2Nom = new wxBoxSizer(wxHORIZONTAL);
 bAdd = new wxButton(pEdit, wxID_ANY, wxT("ADAUGĂ"), wxDefaultPosition, wxDefaultSize, 0);
 s2Nom->Add(bAdd, 0, wxALL|wxEXPAND, 5);
 bDel = new wxButton(pEdit, wxID_ANY, wxT("ŞTERGE"), wxDefaultPosition, wxDefaultSize, 0); 
 s2Nom->Add(bDel, 0, wxALL|wxEXPAND, 5);
 bSav = new wxButton(pEdit, wxID_ANY, wxT("SALVEAZĂ"), wxDefaultPosition, wxDefaultSize, 0);
 s2Nom->Add(bSav, 0, wxALL|wxEXPAND, 5);
 bRenEdit=new wxButton(pEdit, wxID_ANY, wxT("RENUNŢĂ"), wxDefaultPosition, wxDefaultSize, 0);
 s2Nom->Add(bRenEdit, 0, wxALL|wxEXPAND, 5);
 pEdit->SetSizer(s2Nom); pEdit->Layout(); s2Nom->Fit(pEdit);
 s1->Add(pEdit, 0, wxALIGN_BOTTOM|wxEXPAND, 5);
 wxBoxSizer* s2; s2 = new wxBoxSizer(wxHORIZONTAL);
 bEdit = new wxButton(this, wxID_ANY, wxT("EDITARE"), wxDefaultPosition, wxDefaultSize, 0);
 s2->Add(bEdit, 0, wxALL, 5);
 bSel = new wxButton(this, wxID_ANY, wxT("SELECTEAZĂ"), wxDefaultPosition, wxDefaultSize, 0);
 bSel->SetDefault(); 
 bSel->SetFont(wxFont(wxNORMAL_FONT->GetPointSize(), 70, 90, 92, false, wxEmptyString)); 
 s2->Add(bSel, 0, wxALL, 5);
bRenNom = new wxButton(this, wxID_ANY, wxT("RENUNŢĂ"), wxDefaultPosition, wxDefaultSize, 0);
 s2->Add(bRenNom, 0, wxALL, 5); s1->Add(s2, 0, wxEXPAND, 5); 
 this->SetSizer(s1);this->Layout(); 
 s1->Fit(this);this->Centre(wxBOTH);
// Evenumente de conectare
rOrd->Connect(wxEVT_COMMAND_RADIOBOX_SELECTED, wxCommandEventHandler(iFNOM::ordoneaza), NULL, this);
bAdd->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(iFNOM::add_Lin), NULL, this);
bDel->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(iFNOM::del_Lin), NULL, this);
bSav->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(iFNOM::salveaza), NULL, this);
bRenEdit->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(iFNOM::ren_Edit), NULL, this);
bEdit->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(iFNOM::editare), NULL, this);
bSel->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(iFNOM::selecteaza), NULL, this);
bRenNom->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(iFNOM::ren_Nom), NULL, this);
 const char* ach[]={"ID Code","RefCom","RefTeh","Descriere"};
 const char* ord1[]={"refcom","refteh","descr","idcode"};
 wxArrayString a; nr_ord=2;
 for(int i=0;i<4;i++) {a.Add(ach[i]); ord.Add(ord1[i]);} 
 if(rez1) {rez=rez1; rez->Clear();} else bSel->Hide();
 cx_grid=new lxGrid(GD1,_("itmp_nom"),a);
 pEdit->Hide(); GD1->EnableEditing(false); 
 GD1->SetSelectionMode(wxGrid::wxGridSelectRows); 
 afis_NOM();
}
//----------------------------------------------------------------------
----
iFNOM::~iFNOM() {
rOrd->Disconnect(wxEVT_COMMAND_RADIOBOX_SELECTED,wxCommandEventHandler(iFNOM::ordoneaza),NULL,this);
bAdd->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(iFNOM::add_Lin), NULL, this);
bDel->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(iFNOM::del_Lin), NULL, this);
bSav->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(iFNOM::salveaza), NULL, this);
bRenEdit->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED,wxCommandEventHandler(iFNOM::ren_Edit),NULL,this);
bEdit->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(iFNOM::editare), NULL, this);
bSel->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(iFNOM::selecteaza), NULL, this);
bRenNom->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED,wxCommandEventHandler(iFNOM::ren_Nom),NULL,this);
}
//------------------------------------------------------------------
void iFNOM::afis_NOM()
{ nr_ord=rOrd->GetSelection();
 lxCtrl::cda(_("DROP TABLE IF EXISTS itmp_nom; CREATE TEMPORARY TABLE 
itmp_nom AS SELECT idcode,refcom,refteh,descr FROM logx.nom ORDER BY ") +
ord.Item(nr_ord)+_(";"));
 cx_grid->preluareVarColRow(); 
}
//-------------------------------------------------------------------
void iFNOM::salveaza(wxCommandEvent& event)
{ lxCtrl::cda(_("DROP TABLE IF EXISTS itmp_nom; CREATE TEMPORARY TABLE 
itmp_nom AS SELECT idcode,refcom,refteh,descr FROM logx.nom;"));
 wxString achQ; 
 cx_grid->salvare();
 if(!lxCtrl::cda(_("UPDATE logx.nom SET 
refcom=itmp_nom.refcom,refteh=itmp_nom.refteh,descr=itmp_nom.descr \
FROM itmp_nom WHERE itmp_nom.idcode=nom.idcode; \

INSERT INTO logx.nom SELECT par.* FROM (SELECT 
idcode,refcom,refteh,descr FROM itmp_nom EXCEPT SELECT 
idcode,refcom,refteh,descr FROM logx.nom)par;")))
 wxMessageBox(_("Salvat!")); 
}
//--------------------------------------------------------------------
void iFNOM::editare(wxCommandEvent& event)
{ pEdit->Show();GD1->EnableEditing(true); this->Fit();
 GD1->SetSelectionMode(wxGrid::wxGridSelectCells); 
}
//------------------------------------------------------------------
void iFNOM::ren_Edit(wxCommandEvent& event) 
{ pEdit->Hide();GD1->EnableEditing(false);
 GD1->SetSelectionMode(wxGrid::wxGridSelectRows); 
}
//------------------------------------------------------------------
 void iFNOM::selecteaza(wxCommandEvent& event)
{ if(!GD1->IsSelection()) {wxMessageBox(wxT("Selectaţi linia!")); 
return;} //dacă există selecţie în cadrul gridului
 for(int i=0;i<4;i++) 
 rez->Add(GD1->GetCellValue(GD1->GetSelectedRows()[0],i));
 this->Close(); 
}
//--------------------------------------------------------------------
void iFNOM::ren_Nom(wxCommandEvent& event)
 { this->Close(); 
 }
//-------------------------------------------------------------------
 void iFNOM::add_Lin(wxCommandEvent& event)
{ GD1->AppendRows(); GD1->Fit(); 
} 
//------------------------------------------------------------------
 void iFNOM::del_Lin(wxCommandEvent& event)
{ wxMessageDialog *x = 
 new wxMessageDialog(this,wxT("Doriţi ştergerea liniei curente?"), 
_(""),wxYES_NO|wxICON_QUESTION); x->SetYesNoLabels(_("&Nu"),_("&Da"));
if(x->ShowModal() == wxID_NO) 
 {GD1->DeleteRows(GD1->GetGridCursorRow(),1);GD1->Fit(); }
} 
//--------------------------------------------------------------
void iFNOM::ordoneaza(wxCommandEvent& event)
{ afis_NOM();
} 