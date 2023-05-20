#include <wx/clipbrd.h> //fişierul febp.cpp
#include "febp.h"
#include "selst.h"
iFEBP::iFEBP(wxWindow* parent, wxWindowID id, const wxString& title, 
const wxPoint& pos, const wxSize& size, long style) : wxDialog(parent, 
id, title, pos, size, style)
{ this->SetSizeHints(wxDefaultSize, wxDefaultSize);
wxBoxSizer* s1; s1 = new wxBoxSizer(wxVERTICAL);
wxBoxSizer* s2; s2 = new wxBoxSizer(wxHORIZONTAL);
t1 = new wxStaticText(this, wxID_ANY, wxT("BP nr:"), wxDefaultPosition, wxDefaultSize, 0);
t1->Wrap(-1); s2->Add(t1, 0, wxALL, 5);
cbBP = new wxComboBox(this, wxID_ANY, wxT("0000"), wxDefaultPosition, 
wxSize(60,-1),0,NULL,0); s2->Add(cbBP, 0, wxALL, 5);
bAddBP = new wxButton(this, wxID_ANY, wxT("Adaugă BP"), wxDefaultPosition, wxSize(-1,25),0); 
s2->Add(bAddBP, 0, wxALL, 5);
eDataBP = new wxDatePickerCtrl(this, wxID_ANY, wxDefaultDateTime, wxDefaultPosition, 
wxDefaultSize, DEFAULT|wxDP_DROPDOWN); s2->Add(eDataBP, 0, wxALL, 5);
t2 = new wxStaticText(this,wxID_ANY,wxT("Destinaţie"), wxDefaultPosition, 
wxDefaultSize,0); t2->Wrap(-1); s2->Add(t2, 0, wxALL, 5);
eDestinBP = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, 
wxDefaultSize,0); s2->Add(eDestinBP, 0, wxALL, 5);
bDelBP = new wxButton(this, wxID_ANY, wxT("Anulează BP"), wxDefaultPosition, wxDefaultSize, 0); 
s2->Add(bDelBP, 0, wxALL, 5); s1->Add(s2, 0, wxEXPAND, 5);
pBP = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 
wxTAB_TRAVERSAL); wxBoxSizer* s4; s4 = new wxBoxSizer(wxVERTICAL);
GD1 = new wxGrid(pBP, wxID_ANY, wxDefaultPosition,wxSize(-1,400), wxALWAYS_SHOW_SB);
GD1->CreateGrid(0, 0); GD1->EnableEditing(true); 
GD1->EnableGridLines(true);
GD1->EnableDragGridSize(false); GD1->SetMargins(0, 0);
GD1->AutoSizeColumns();GD1->EnableDragColMove(false);
GD1->EnableDragColSize(true);GD1->SetColLabelSize(30);
GD1->SetColLabelAlignment(wxALIGN_CENTRE, wxALIGN_CENTRE);
GD1->AutoSizeRows(); GD1->EnableDragRowSize(true);
GD1->SetRowLabelSize(80);
GD1->SetRowLabelAlignment(wxALIGN_CENTRE, wxALIGN_CENTRE);
GD1->SetDefaultCellBackgroundColour(wxColour(237, 250, 237));
GD1->SetDefaultCellAlignment(wxALIGN_LEFT, wxALIGN_TOP);
GD1->SetBackgroundColour(wxColour(238, 251, 236));
s4->Add(GD1, 1, wxALL|wxEXPAND, 5);
wxBoxSizer* s3; s3 = new wxBoxSizer(wxHORIZONTAL);
bDelLin = new wxButton(pBP, wxID_ANY, wxT("Şterge linia"), wxDefaultPosition, wxDefaultSize,0);
s3->Add(bDelLin, 0, wxALL, 5); s3->Add(0, 0, 1, wxEXPAND, 5);
bSelST =new wxButton(pBP, wxID_ANY,wxT("Adaugă din 
STOC"),wxDefaultPosition,wxDefaultSize,0); s3->Add(bSelST, 0, wxALL, 5); s3->Add(0, 
0, 1, wxEXPAND, 5);
bValidBP=new wxButton(pBP, wxID_ANY, wxT("VALIDEAZĂ BP"),wxDefaultPosition,wxDefaultSize,0);
s3->Add(bValidBP, 0, wxALL, 5); s4->Add(s3,0,wxEXPAND,5);
pBP->SetSizer(s4); pBP->Layout(); s4->Fit(pBP);
s1->Add(pBP, 0, wxEXPAND | wxALL, 5);
this->SetSizer(s1); this->Layout(); this->Centre(wxBOTH);
cbBP->Connect(wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(iFEBP::afis_BP), NULL, this);
bAddBP->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(iFEBP::addBP), NULL, this);
bDelBP->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(iFEBP::delBP), NULL, this);
bDelLin->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(iFEBP::delLin), NULL, this);
bSelST->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(iFEBP::selST), NULL, this);
bValidBP->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(iFEBP::validBP), NULL, this);
 pBP->Hide();
cx_nrbp = new lxComboBox(cbBP,_("SELECT DISTINCT nrbp::text FROM logx.bp_ 
ORDER BY nrbp;"));
cx_destin=new lxEditT(eDestinBP); cx_databp=new lxDPC(eDataBP);
wxArrayString a; cx_grid=new lxGrid(GD1,_("itmp_bp"),a);
GD1->SetColMinimalAcceptableWidth(0);
}
//-------------------------------------------------------------
iFEBP::~iFEBP() {
cbBP->Disconnect(wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(iFEBP::afis_BP), NULL, this);
bAddBP->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(iFEBP::addBP), NULL, this);
bDelBP->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(iFEBP::delBP), NULL, this);
bDelLin->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(iFEBP::delLin), NULL, this);
bSelST->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(iFEBP::selST), NULL, this);
bValidBP->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(iFEBP::validBP), NULL, this);
}
//-------------------------------------------------------------
void iFEBP::afis_BP(wxCommandEvent& event)
{if(cbBP->GetCount()<1) { pBP->Hide(); return;} 
cx_destin->rdSQL(_("SELECT destin::text FROM logx.bp_ WHERE nrbp=")
+cx_nrbp->getSel()+_(" LIMIT 1;")); 
cx_databp->rdSQL(_("SELECT databp::date FROM logx.bp_ WHERE nrbp=")
+cx_nrbp->getSel()+_(" LIMIT 1;")); 
lxCtrl::cda(_("DROP TABLE IF EXISTS itmp_bp; CREATE TEMPORARY TABLE 
itmp_bp AS SELECT (_bp.nrbp::text||'->'||_bp.id::text||'->'||
_bp.dep::text||'->'||_bp.ampl::text) AS tcu, _bp.nrbp, _bp.id, 
nom.idcode, nom.refcom, nom.refteh, nom.descr, inx.po, inx.status, 
inx.serialno, _bp.dep, _bp.ampl, _bp.qtyrez, _bp.qtyconf FROM 
logx._bp,logx.inx,logx.nom WHERE nom.idcode=inx.idcode AND nrbp=")
+cx_nrbp->getSel()+_(" AND inx.id=_bp.id;"));
/* cu contor unic pentru a realiza legătura între cele două tabele, în 
grid va fi în prima coloana care va fi setată pe invizibil(dimensiune 
zero)*/ cx_grid->preluareVarColRow();GD1->SetColSize(0,0);pBP->Show();
}
//-------------------------------------------------------------
void iFEBP::addBP(wxCommandEvent& event)
{lxCtrl::cda(_("select logx.bp_nou(")+cx_destin->getValFormatStr()+_(",")
+cx_databp->getValFormatStr()+_(");"));
 cx_nrbp->rdLista(_("SELECT DISTINCT nrbp::text FROM logx.bp_ ORDER BY 
nrbp;"));
 cbBP->SetSelection(cbBP->GetCount()-1); 
 afis_BP(event);
}
//-------------------------------------------------------------
void iFEBP::delLin(wxCommandEvent& event)
{wxMessageDialog *x = 
new wxMessageDialog(this,wxT("Doriţi ştergerea liniei curente?"), _(""), 
wxYES_NO|wxICON_QUESTION); x->SetYesNoLabels(_("&Nu"),_("&Da"));
if(x->ShowModal() == wxID_NO) 
 { lxCtrl::cda(_("DELETE FROM logx._bp USING itmp_bp WHERE itmp_bp.tcu =
(bp.nrbp::text||'->'||bp.id::text||'->'||_bp.dep::text||'->'||
_bp.ampl::text) AND tcu='") + GD1->GetCellValue(GD1->GetSelectedRows()
[0],0) +_("'; DELETE FROM itmp_bp WHERE itmp_bp.tcu='") + 
GD1->GetCellValue(GD1->GetSelectedRows()[0],0) +_("';"));
GD1->DeleteRows(GD1->GetSelectedRows()[0],1);GD1->Fit(); 
 }
afis_BP(event); 
}
//-------------------------------------------------------------
void iFEBP::delBP(wxCommandEvent& event)
{ wxMessageDialog *x = 
new wxMessageDialog(this,wxT("Doriţi ştergerea BPORDEROULUI curent?"), 
_(""),wxYES_NO|wxICON_QUESTION); x->SetYesNoLabels(_("&Nu"),_("&Da"));
if(x->ShowModal() == wxID_NO) //&Nu corespunde lui wxID_YES
lxCtrl::cda(_("UPDATE logx.stx SET qtydisp=qtydisp+qtyrez FROM itmp_bp 
WHERE stx.id=itmp_bp.id AND stx.dep=itmp_bp.dep AND stx.ampl=itmp_bp.ampl
AND itmp_bp.nrbp = ")+cx_nrbp->getSel()+_("; \
DELETE FROM logx._bp WHERE nrbp = ")+cx_nrbp->getSel()+_("; DELETE FROM 
logx.bp_ WHERE nrbp = ")+cx_nrbp->getSel()+_(";"));
int s=cbBP->GetSelection(); cx_nrbp->refreshlx(); cbBP->Select(s-1); 
afis_BP(event);
}
//-------------------------------------------------------------
void iFEBP::selST(wxCommandEvent& event)
{ iFSELST* x; x=new iFSELST(this, cx_nrbp->getSel()); x->ShowModal(); 
 afis_BP(event);
}
//-------------------------------------------------------------
void iFEBP::validBP(wxCommandEvent& event)
{ wxString achQ,ach; 
 if(cbBP->GetSelection()<0) wxMessageBox(_("Nimic de selectat!"));
 //actualizare în BP qtyconf
 for(int i=0;i<GD1->GetNumberRows();i++)
 lxCtrl::cda(_("UPDATE logx._bp SET qtyconf=") + GD1->GetCellValue(i, 
GD1->GetNumberCols() - 1) + _(" FROM itmp_bp WHERE itmp_bp.tcu = 
(_bp.nrbp::text || '->' || _bp.id::text || '->' || _bp.dep::text || '->' 
|| _bp.ampl::text) AND itmp_bp.tcu='")+GD1->GetCellValue(i,0)+_("';"));
 
if((ach=lxCtrl::cda(_("SELECT logx.valid_bp(")+cx_nrbp->getSel()
+");"))==_("OK")) wxMessageBox(_("Validat!")); else 
wxMessageBox(ach);
 cx_nrbp->refreshlx(); afis_BP(event);
}
