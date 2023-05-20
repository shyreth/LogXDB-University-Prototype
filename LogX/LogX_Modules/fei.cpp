#include "fei.h" //fişierul fei.cpp
#include "fnom.h"
#define _COLDEP_ 8
#define _COLAMPL_ 9
#define _COLSTATUS_ 6
iFEI::iFEI(wxWindow* parent, wxWindowID id, const wxString& title, const 
wxPoint& pos, const wxSize& size, long style) : wxDialog(parent, id, 
title, pos, size, style)
{ this->SetSizeHints(wxDefaultSize, wxDefaultSize);
 wxBoxSizer* s1; s1 = new wxBoxSizer(wxVERTICAL);
 wxBoxSizer* s2; s2 = new wxBoxSizer(wxHORIZONTAL);
 t4=new wxStaticText(this,wxID_ANY,wxT("BR nr:"),wxDefaultPosition,wxDefaultSize,0);
 t4->Wrap(-1);s2->Add(t4, 0, wxALL|wxEXPAND, 5);
 cbBR =new wxComboBox(this,wxID_ANY,wxT("Combo!"),wxDefaultPosition, wxDefaultSize,0,NULL,0);
 s2->Add(cbBR, 0, wxALL, 5);
 eDataBR = new wxDatePickerCtrl(this, wxID_ANY, wxDefaultDateTime, wxDefaultPosition, 
wxDefaultSize, wxDP_DEFAULT|wxDP_DROPDOWN);
 s2->Add(eDataBR, 0, wxALL, 5); 
 t5 = new wxStaticText(this, wxID_ANY, wxT("Supplier"), wxDefaultPosition, wxDefaultSize, 0);
 t5->Wrap(-1); s2->Add(t5, 0, wxALL, 5);
 SupplierBR=new wxTextCtrl(this,wxID_ANY,wxEmptyString,wxDefaultPosition,wxDefaultSize,0);
 s2->Add(eSupplierBR, 0, wxALL, 5);
 bAddBR = new wxButton(this, wxID_ANY, wxT("Adaugă BR"), wxDefaultPosition,wxSize(-1,25),0);
 s2->Add(bAddBR, 0,wxALL,5);s1->Add(s2,0, wxEXPAND, 5);
 pBR = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 
wxFULL_REPAINT_ON_RESIZE|wxRAISED_BORDER|wxTAB_TRAVERSAL);
 wxBoxSizer* s3; s3 = new wxBoxSizer(wxVERTICAL);
 wxBoxSizer* s4; s4 = new wxBoxSizer(wxHORIZONTAL);
 bDelBR = new wxButton(pBR, wxID_ANY, wxT("ŞTERGE BR"), wxDefaultPosition, wxSize(-1,25),0);
 bDelBR->SetForegroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_WINDOWTEXT));
 s4->Add(bDelBR, 0, wxALL, 5); s4->Add(0, 0, 1, wxEXPAND, 5);
 bSavBR = new wxButton(pBR,wxID_ANY,wxT("SALVEAZĂ BR"),wxDefaultPosition,wxSize(-1,25),0);
 s4->Add(bSavBR, 0, wxALL, 5);s3->Add(s4,0,wxEXPAND,5);
 GD1 = new wxGrid(pBR, wxID_ANY, wxDefaultPosition, wxSize(600,400), wxALWAYS_SHOW_SB);
 GD1->CreateGrid(0,0);GD1->EnableEditing(true);
 GD1->EnableGridLines(true);
 GD1->EnableDragGridSize(false); GD1->SetMargins(0, 0);
 GD1->AutoSizeColumns();GD1->EnableDragColMove(false);
 GD1->EnableDragColSize(true); GD1->SetColLabelSize(30); 
 GD1->SetColLabelAlignment(wxALIGN_CENTRE, wxALIGN_CENTRE);
 GD1->AutoSizeRows();GD1->EnableDragRowSize(true);
 GD1->SetRowLabelSize(80);
 GD1->SetRowLabelAlignment(wxALIGN_CENTRE, wxALIGN_CENTRE);
 GD1->SetDefaultCellAlignment(wxALIGN_LEFT, wxALIGN_TOP);
 s3->Add(GD1, 1, wxALL|wxEXPAND, 5);
 wxBoxSizer* s5; s5 = new wxBoxSizer(wxHORIZONTAL);
 bValidBR=new wxButton(pBR,wxID_ANY,wxT("VALIDEAZĂ BR"),wxDefaultPosition,wxSize(-1,25),0);
 s5->Add(bValidBR, 0, wxALL, 5);
 bAddLin =new wxButton(pBR, wxID_ANY,wxT("ADAUGĂ LINIE"),wxDefaultPosition,wxSize(-1,25),0);
 s5->Add(bAddLin, 0, wxALL, 5);
 bDelLin =new wxButton(pBR, wxID_ANY,wxT("ŞTERGE LINIE"),wxDefaultPosition, wxSize(-1,25),0);
 s5->Add(bDelLin, 0, wxALL, 5); s5->Add(0, 0, 1, wxEXPAND, 5);
 B_selNom = new wxButton(pBR,wxID_ANY,wxT("SELECŢIE NOMENCLATOR"), wxDefaultPosition, 
wxSize(-1,25),0);
 s5->Add(B_selNom, 0, wxALL, 5); s3->Add(s5, 0, wxEXPAND, 5);
 pBR->SetSizer(s3);pBR->Layout();
 s3->Fit(pBR);s1->Add(pBR,1,wxEXPAND,5);
 this->SetSizer(s1); this->Layout();
cbBR->Connect(wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(iFEI::afis_BR), NULL, this);
bAddBR->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(iFEI::add_BR), NULL, this);
bDelBR->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(iFEI::del_BR), NULL, this);
bSavBR->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(iFEI::sav_BR), NULL, this);
GD1->Connect(wxEVT_GRID_CELL_CHANGE, wxGridEventHandler(iFEI::GD1OnGridCellChange), NULL, this);
GD1->Connect(wxEVT_GRID_EDITOR_SHOWN, wxGridEventHandler(iFEI::GD1OnGridEditorShown), NULL, this);
bValidBR->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(iFEI::valid_BR), NULL, this);
bAddLin->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(iFEI::add_Lin), NULL, this);
bDelLin->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(iFEI::del_Lin), NULL, this);
B_selNom->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(iFEI::sel_nom), NULL, this);
 pBR->Hide();
 cx_nrbr = new lxComboBox(cbBR,_("SELECT DISTINCT nrbr::text FROM 
logx.br ORDER BY nrbr;"));
 cx_supplier=new lxEditT(eSupplierBR); cx_datain=new lxDPC(eDataBR);
 const char* 
ach[]={"tcu","IDCode","RefCom","RefTeh","Descr","PO","Status", 
"SerialNo","DepInit","Ampl.Init","Qty"};
 wxArrayString a; for(int i=0;i<11;i++) a.Add(ach[i]);
 cx_grid=new lxGrid(GD1,_("itmp_br"),a);
 GD1->SetColMinimalAcceptableWidth(0); 
//adăugare control combobox în grid pentru STATUS
 wxGridCellAttr *A_col= new wxGridCellAttr(); 
 wxString sel[] = { wxT("Funcţional"), wxT("Defect"), wxT("Rebut"), 
wxT("Incert"), wxT("Casare") }; 
 A_col->SetEditor(new wxGridCellChoiceEditor(5, sel));
 GD1->SetColAttr(_COLSTATUS_, A_col);
//adaugare controale combobox pentru depozite şi amplasamente, lista 
pentru amplasament va cuprinde selecţia pentru primul depozit afişat */
lxCtrl::lista(_("DROP TABLE IF EXISTS tmpacc; CREATE TEMP TABLE tmpacc AS
SELECT dep[s] FROM (select acces.*, generate_subscripts(dep,1) as s from 
logx.acces where ('#'||alias||'#') = CURRENT_USER)par; SELECT DISTINCT 
loc.dep FROM logx.loc,tmpacc WHERE loc.dep=tmpacc.dep ORDER BY 
loc.dep;"),a); 
 A_col= new wxGridCellAttr(); 
 A_col->SetEditor(new wxGridCellChoiceEditor(a));
 GD1->SetColAttr(_COLDEP_ ,A_col);
/*obiectul de tip combobox pentru amplasament este pus şi aici doar 
pentru agenerarea evenimentelor de afişare control în celulă */
 lxCtrl::lista(_("SELECT DISTINCT ampl FROM logx.loc WHERE dep=(SELECT 
DISTINCT dep FROM tmpacc ORDER BY dep LIMIT 1) ORDER BY ampl;"),a); 
 A_col= new wxGridCellAttr(); 
 A_col->SetEditor(new wxGridCellChoiceEditor(a));
 GD1->SetColAttr(_COLAMPL_,A_col);
}
//----------------------------------------------------------------------
----
iFEI::~iFEI() {
cbBR->Disconnect(wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(iFEI::afis_BR), NULL, this);
bAddBR->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(iFEI::add_BR), NULL, this);
bDelBR->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(iFEI::del_BR), NULL, this);
bSavBR->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(iFEI::sav_BR), NULL, this);
GD1->Disconnect(wxEVT_GRID_CELL_CHANGE, wxGridEventHandler(iFEI::GD1OnGridCellChange), NULL, this);
GD1->Disconnect(wxEVT_GRID_EDITOR_SHOWN, wxGridEventHandler(iFEI::GD1OnGridEditorShown), NULL, this);
bValidBR->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(iFEI::valid_BR), NULL, this);
bAddLin->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(iFEI::add_Lin), NULL, this);
bDelLin->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(iFEI::del_Lin), NULL, this);
B_selNom->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(iFEI::sel_nom), NULL, this);
}
//-------------------------------------------------------------------
void iFEI::afis_BR(wxCommandEvent& event)
{ cx_supplier->rdSQL(_("SELECT supplier::text FROM logx.br WHERE nrbr=")
+cx_nrbr->getSel()+_(" LIMIT 1;")); 
 cx_datain->rdSQL(_("SELECT datain::date FROM logx.br WHERE nrbr=")
+cx_nrbr->getSel()+_(" LIMIT 1;")); 
 lxCtrl::cda(_("DROP TABLE IF EXISTS itmp_br; CREATE TEMPORARY TABLE 
itmp_br AS SELECT (br.nrbr::text||'->'||br.idx::text) AS tcu, 
br.idcode,refcom,refteh,descr,po,status,serialno,depinit,amplinit,qty 
FROM logx.br,logx.nom WHERE nom.idcode=br.idcode AND nrbr=")+cx_nrbr-
>getSel()+_(";"));
//tcu contor unic pentru a realiza legaătura între cele două tabele, în 
grid va fi în prima coloana care va fi setată pe invizibil
 cx_grid->preluareVarColRow(); GD1->SetColSize(0,0); pBR->Show();
}
//---------------------------------------------------------------------
void iFEI::sav_BR(wxCommandEvent& event)
{ wxString achQ; 
 cx_grid->salvare(); // copiere din celule gridului în tabelul temporar
//şterge borderoul curent pentru numărul selectat şi adaugă în acesta 
noua informaţie
 if(!lxCtrl::cda(_("DELETE FROM logx.br USING itmp_br WHERE 
itmp_br.tcu=(br.nrbr::text||'->'||br.idx); \
INSERT INTO 
logx.br(nrbr,datain,supplier,idcode,po,status,serialno,depinit, 
amplinit,qty) \
 SELECT ")+cx_nrbr->getSel()+_(",")+cx_datain->getValFormatStr()+_(",")
+cx_supplier->getValFormatStr()+ 
_(" ,idcode,po,status,serialno,depinit,amplinit,qty FROM itmp_br; ")));
wxMessageBox(_("Salvat!")); 
}
//---------------------------------------------------------------------
void iFEI::add_BR(wxCommandEvent& event)
{lxCtrl::cda(_("select logx.br_nou();"));
 cx_nrbr->rdLista(_("SELECT DISTINCT nrbr::text FROM logx.br ORDER BY 
nrbr;"));
 cbBR->SetSelection(cbBR->GetCount()-1); 
 afis_BR(event);
}
//---------------------------------------------------------------------
void iFEI::add_Lin(wxCommandEvent& event)
{ GD1->AppendRows(); GD1->Fit();
}
//--------------------------------------------------------------------
void iFEI::del_Lin(wxCommandEvent& event)
{ wxMessageDialog *x = 
new wxMessageDialog(this, wxT("Doriţi ştergerea liniei curente?"), 
_(""),wxYES_NO|wxICON_QUESTION); 
x->SetYesNoLabels(_("&Nu"),_("&Da"));

if(x->ShowModal() == wxID_NO) //DA=ID_NO
 {// ştergere linia unde valoarea tpu = cu expresia formată în BR
 lxCtrl::cda(_("DELETE FROM logx.br WHERE '") + 
 GD1->GetCellValue(GD1->GetSelectedRows()[0],0) + 
 ("'=(br.nrbr::text||'->'||br.idx)")); 
 afis_BR(event);
 }
}
//--------------------------------------------------------------------
void iFEI::del_BR(wxCommandEvent& event)
{ wxMessageDialog *x = 
new wxMessageDialog(this,wxT("Doriţi ştergerea BPORDEROULUI 
curent?"),_(""),wxYES_NO|wxICON_QUESTION);
 x->SetYesNoLabels(_("&Nu"),_("&Da"));
if(x->ShowModal() == wxID_NO) //&Nu corespunde lui wxID_YES
 lxCtrl::cda(_("DELETE FROM logx.br USING itmp_br WHERE 
itmp_br.tcu=(br.nrbr::text||'->'||br.idx);")); 
 pBR->Hide(); cx_nrbr->refreshlx(); 
}
//-------------------------------------------------------------------
void iFEI::sel_nom(wxCommandEvent& event)
{ if(!GD1->IsSelection()) 
 {wxMessageBox(wxT("Selectaţi linia!")); return;} 
wxArrayString* rez=new wxArrayString; 
iFNOM* x; x=new iFNOM(this,rez); x->ShowModal(); 
if(rez->GetCount()<1) 
 {wxMessageBox("Nu a fost selectat nimic >>>>>!"); return;} 
for(int j=0; j<4; j++) 
 GD1->SetCellValue(GD1->GetSelectedRows()[0],j+1,rez->Item(j));
}
//--------------------------------------------------------------------
void iFEI::valid_BR(wxCommandEvent& event)
{ wxString achQ, achR; 
 sav_BR(event);
 if((achR=lxCtrl::cda(_("SELECT logx.valid_br(")+cx_nrbr->getSel()
+");"))==_("OK"))
 wxMessageBox(_("Validat!")); 
 else wxMessageBox(achR); 
 pBR->Hide(); cx_nrbr->refreshlx(); 
}
//--------------------------------------------------------------------
void iFEI::GD1OnGridEditorShown(wxGridEvent& event) 
{if(event.GetCol()!=_COLAMPL_) return; 
 wxArrayString a;
 lxCtrl::lista(_("SELECT DISTINCT ampl FROM logx.loc WHERE dep='") + 
 GD1->GetCellValue(event.GetRow(),_COLDEP_) + _("' ORDER BY ampl;"),a); 
 wxGridCellAttr *A_col= new wxGridCellAttr(); 
 A_col->SetEditor(new wxGridCellChoiceEditor(a)); 
 GD1->SetColAttr(_COLAMPL_,A_col);
}
//----------------------------------------------------------------------
//modifică culuarea de scriere în roşu pentru celulele cu conţinut modificat
void iFEI::GD1OnGridCellChange(wxGridEvent& event) 
{ GD1->SetCellTextColour(event.GetRow(),event.GetCol(),wxColour(wxT("RED")));
} 