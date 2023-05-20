#include <wx/clipbrd.h> //fişierul selst.cpp
#include "selst.h"
#include "fnom.h"
iFSELST::iFSELST(wxWindow* parent, wxString achBP1, wxWindowID id, const 
wxString& title, const wxPoint& pos, const wxSize& size, long style) : wxDialog(parent, id, title, pos, size, style)
{this->SetBackgroundColour(wxColour(228, 243, 235));//setare culoare 
fundal
 wxBoxSizer* s1; s1 = new wxBoxSizer(wxVERTICAL);
 wxBoxSizer* s2; s2 = new wxBoxSizer(wxHORIZONTAL);
 wxBoxSizer* s3; s3 = new wxBoxSizer(wxVERTICAL);
 t8 = new 
wxStaticText(this,wxID_ANY,wxT("AFIŞARE"),wxDefaultPosition,wxDefaultSize,wxALIGN_CENTRE);
t8->Wrap(-1); s3->Add(t8, 0, wxALIGN_CENTER|wxALL, 5);
 wxString cblAChoices[] = { wxT("ID Code"), wxT("Ref Com"), wxT("Ref Teh."), wxT("Descriere"), wxT("Furnizor"), wxT("Data IN"), 
wxT("SerialNo"), wxT("Status"), wxT("Comandă (PO)"), wxT("Depozit"), 
wxT("Amplasament"), wxT("ID") };
 int cblANChoices = sizeof(cblAChoices) / sizeof(wxString);
 cblA=new wxCheckListBox(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, cblANChoices, 
cblAChoices,0);
 cblA->SetBackgroundColour(wxColour(252, 253, 223));
 s3->Add(cblA, 0, wxALL, 5); s2->Add(s3, 0, wxEXPAND, 5);
 wxBoxSizer* s4; s4 = new wxBoxSizer(wxVERTICAL);
 t9 = new wxStaticText(this, wxID_ANY, wxT("SELECŢIE"), wxDefaultPosition, wxDefaultSize,0);
 t9->Wrap(-1); s4->Add(t9, 0, wxALIGN_CENTER|wxALL, 5);
 wxString cblSChoices[] = { wxT("ID Code"), wxT("Ref Com"), wxT("Ref 
Teh."), wxT("Descriere"), wxT("Furnizor"), wxT("Data IN"), 
wxT("SerialNo"), wxT("Staus"), wxT("Comandă (PO)"), wxT("Depozit"), 
wxT("Amplasament"), wxT("ID") };
 int cblSNChoices = sizeof(cblSChoices) / sizeof(wxString);
 cblS=new wxCheckListBox(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, cblSNChoices, 
cblSChoices,0);
 cblS->SetBackgroundColour(wxColour(231, 238, 254));
 s4->Add(cblS, 1, wxALL|wxEXPAND, 5); s2->Add(s4, 1, wxEXPAND, 5);
 wxBoxSizer* s5; s5 = new wxBoxSizer(wxVERTICAL);
 CBP = new wxChoicebook(this,wxID_ANY,wxDefaultPosition,wxDefaultSize,wxCHB_DEFAULT);
 CBP->SetBackgroundColour(wxColour(217, 234, 215));
 p1 = new wxPanel(CBP, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
 p1->SetBackgroundColour(wxColour(231, 245, 226));
 wxBoxSizer* s6; s6 = new wxBoxSizer(wxVERTICAL);
 bNom =new wxButton(p1, wxID_ANY, wxT("NOMENCLATOR"), wxDefaultPosition, wxDefaultSize, 0);
 s6->Add(bNom, 0,wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL,5);
 p1->SetSizer(s6); p1->Layout(); s6->Fit(p1);
 CBP->AddPage(p1, wxT("ID Code/ RefCom/ RefTeh/ Descriere"), false);
 p2 = new wxPanel(CBP, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
 wxBoxSizer* s7; s7 = new wxBoxSizer(wxHORIZONTAL);
 t1 = new wxStaticText(p2, wxID_ANY, wxT("="), wxDefaultPosition, wxDefaultSize, 0); 
t1->Wrap(-1); s7->Add(t1, 0, wxALL, 5);
 eSupplier=new wxTextCtrl(p2, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0);
 s7->Add(eSupplier, 1, wxALL, 5);
bRetFurnizor=new wxButton(p2, wxID_ANY, wxT("Reţine"),wxDefaultPosition,wxSize(60,-1),0);
 s7->Add(bRetFurnizor, 0, wxALL, 5);
 p2->SetSizer(s7); p2->Layout(); s7->Fit(p2);
 CBP->AddPage(p2, wxT("Furnizor"), false);
p3 = new wxPanel(CBP, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
 p3->SetBackgroundColour(wxColour(217, 244, 225));
 wxBoxSizer* s8; s8 = new wxBoxSizer(wxVERTICAL);
 wxBoxSizer* s9; s9 = new wxBoxSizer(wxHORIZONTAL);
 eData1= new wxDatePickerCtrl(p3, wxID_ANY, wxDefaultDateTime, wxDefaultPosition, 
wxDefaultSize, 0);
 s9->Add(eData1, 0, wxALL, 5);
 t2 = new wxStaticText(p3, wxID_ANY, wxT(">->"), wxDefaultPosition, wxDefaultSize, 0);
 t2->Wrap(-1); s9->Add(t2, 0, wxALL, 5);
 eData2=new wxDatePickerCtrl(p3, wxID_ANY, wxDefaultDateTime, wxDefaultPosition, 
wxDefaultSize,0);
 s9->Add(eData2, 0, wxALL, 5); s8->Add(s9, 0, wxEXPAND, 5);
 bRetData = new wxButton(p3, wxID_ANY, wxT("Reţine"), wxDefaultPosition, wxSize(60,-1), 0);
 s8->Add(bRetData, 0, wxALIGN_CENTER|wxALL, 5);
 p3->SetSizer(s8); p3->Layout(); s8->Fit(p3);
 CBP->AddPage(p3, wxT("Data IN"), false);
 p4 = new wxPanel(CBP, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
 wxFlexGridSizer* s10; s10 = new wxFlexGridSizer(0, 2, 0, 0);
 s10->SetFlexibleDirection(wxBOTH); 
 s10->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_SPECIFIED);
 t3 = new wxStaticText(p4, wxID_ANY, wxT("Depozit"), wxDefaultPosition, wxDefaultSize, 0);
 t3->Wrap(-1); s10->Add(t3, 0, wxALL, 5);
cbDep=new wxComboBox(p4, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize,0, NULL,0);
 s10->Add(cbDep, 0, wxALL, 5);
t4=new wxStaticText(p4, wxID_ANY, wxT("Amplasament"), wxDefaultPosition, wxDefaultSize, 0);
 t4->Wrap(-1); s10->Add(t4, 0, wxALL, 5);
cbAmpl=new wxComboBox(p4, wxID_ANY, wxEmptyString,wxDefaultPosition,wxDefaultSize,0,NULL,0); 
 s10->Add(cbAmpl,0,wxALL,5); s10->Add(0, 0, 1, wxEXPAND, 5);
 bRetDepAmp=new wxButton(p4, wxID_ANY, wxT("Reţine"), wxDefaultPosition, wxDefaultSize, 0);
 s10->Add(bRetDepAmp,0,wxALL,5); p4->SetSizer(s10);
 p4->Layout(); s10->Fit(p4);
 CBP->AddPage(p4, wxT("Depozit/ Amplasament"), false);
 p5 = new wxPanel(CBP, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
 wxBoxSizer* s11; s11 = new wxBoxSizer(wxHORIZONTAL);
 t5 = new wxStaticText(p5, wxID_ANY, wxT("="), wxDefaultPosition, wxDefaultSize, 0);
 t5->Wrap(-1); s11->Add(t5, 0, wxALL, 5);
 ePO = new wxTextCtrl(p5, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0);
 s11->Add(ePO, 1, wxALL, 5);
 bRetPO=new wxButton(p5, wxID_ANY, wxT("Reţine"), wxDefaultPosition, wxSize(60,-1), 0);
 s11->Add(bRetPO,0,wxALL,5); p5->SetSizer(s11);
 p5->Layout(); s11->Fit(p5);
 CBP->AddPage(p5, wxT("Comandă (PO)"), false);
 p6 = new wxPanel(CBP, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
 wxBoxSizer* s12; s12 = new wxBoxSizer(wxHORIZONTAL);
 t6 = new wxStaticText(p6, wxID_ANY, wxT("="), wxDefaultPosition, wxDefaultSize,0);
 t6->Wrap(-1); s12->Add(t6, 0, wxALL, 5);
 wxString cbStatusChoices[] = { wxT("Funcţional"), wxT("Defect"), 
wxT("Rebut"), wxT("Incert"), wxT("Casare") };
 int cbStatusNChoices = sizeof(cbStatusChoices) / sizeof(wxString);
cbStatus=new wxChoice(p6,wxID_ANY,wxDefaultPosition,wxDefaultSize,cbStatusNChoices,cbStatusChoices,0); 
 cbStatus->SetSelection(2); s12->Add(cbStatus, 0, wxALL, 5);
 bRetStatus=new wxButton(p6, wxID_ANY, wxT("Reţine"), wxDefaultPosition, wxSize(60,-1), 0);
 s12->Add(bRetStatus,0,wxALL,5);p6->SetSizer(s12);
 p6->Layout();s12->Fit(p6);
 CBP->AddPage(p6, wxT("STATUS"), true);
 p7 = new wxPanel(CBP, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
 wxBoxSizer* s13; s13 = new wxBoxSizer(wxHORIZONTAL);
 t7 = new wxStaticText(p7, wxID_ANY, wxT("="), wxDefaultPosition, wxDefaultSize, 0);
 t7->Wrap(-1); s13->Add(t7, 0, wxALL, 5);
 eSerialNo=new wxTextCtrl(p7, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0);
 s13->Add(eSerialNo, 1, wxALL, 5);
bRetSerialNo=new wxButton(p7, wxID_ANY, wxT("Reţine"), wxDefaultPosition, wxSize(60,-1),0);
 s13->Add(bRetSerialNo, 0, wxALL, 5);
 p7->SetSizer(s13); p7->Layout(); s13->Fit(p7);
 CBP->AddPage(p7, wxT("SerialNo"), false);
 p10 = new wxPanel(CBP, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
 wxBoxSizer* s16; s16 = new wxBoxSizer(wxHORIZONTAL);
 t10 = new wxStaticText(p10, wxID_ANY, wxT("="), wxDefaultPosition, wxDefaultSize, 0);
 t10->Wrap(-1); s16->Add(t10, 0, wxALL, 5);
 eID = new wxTextCtrl(p10, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0);
 s16->Add(eID, 1, wxALL, 5);
 bRetID = new wxButton(p10, wxID_ANY, wxT("Reţine"), wxDefaultPosition, wxSize(60,-1), 0);
 s16->Add(bRetID, 0, wxALL, 5);
 p10->SetSizer(s16); p10->Layout();s16->Fit(p10);
 CBP->AddPage(p10, wxT("ID"), false);
 s5->Add(CBP, 1, wxEXPAND | wxALL, 5);
 wxBoxSizer* s35; s35 = new wxBoxSizer(wxHORIZONTAL);
 t13=new wxStaticText(this, wxID_ANY, wxT("Sortare:"), wxDefaultPosition,wxDefaultSize, 0);
 t13->Wrap(-1); s35->Add(t13, 0, wxALL, 5);
 wxString cbOrdChoices[] = { wxT("ID Code"), wxT("Ref Com"), wxT("Ref Teh."), wxT("Descriere"), wxT("Furnizor"), wxT("Data IN"), 
wxT("SerialNo"), wxT("Depozit"), wxT("Status"), wxT("Amplasament"), 
wxT("Comandă (PO)"), wxT("ID"), wxT("Neordonat") };
 int cbOrdNChoices = sizeof(cbOrdChoices) / sizeof(wxString);
 cbOrd = new wxChoice(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, cbOrdNChoices, 
cbOrdChoices, 0);
 cbOrd->SetSelection(12); s35->Add(cbOrd, 1, wxALL, 5);
 bCopiaza = new wxButton(this,wxID_ANY,wxT("Copiază"),wxDefaultPosition, wxSize(-1,-
1),wxBU_EXACTFIT);
 s35->Add(bCopiaza, 0, wxALL, 5); s5->Add(s35, 0, wxEXPAND, 5);
 bQ =new wxButton(this, wxID_ANY,wxT("INTEROGARE STOC"), wxDefaultPosition,wxDefaultSize, 0);
 bQ->SetFont(wxFont(13, 70, 90, 92, false, wxEmptyString));
 bQ->SetForegroundColour(wxColour(109, 143, 71));
 s5->Add(bQ, 0, wxALL|wxEXPAND, 5); s2->Add(s5, 0, wxEXPAND, 5); 
 s1->Add(s2, 0, wxEXPAND, 5);
 GD1 = new wxGrid(this, wxID_ANY, wxDefaultPosition, wxSize(-1,150), 
wxALWAYS_SHOW_SB|wxFULL_REPAINT_ON_RESIZE);
 GD1->CreateGrid(0,0); GD1->EnableEditing(true);
 GD1->EnableGridLines(true);
 GD1->EnableDragGridSize(false); GD1->SetMargins(0, 0);
 GD1->AutoSizeColumns(); GD1->EnableDragColMove(false);
 GD1->EnableDragColSize(true); GD1->SetColLabelSize(20);
 GD1->SetColLabelAlignment(wxALIGN_CENTRE, wxALIGN_CENTRE);
 GD1->AutoSizeRows(); GD1->EnableDragRowSize(true); 
 GD1->SetRowLabelSize(80);
 GD1->SetRowLabelAlignment(wxALIGN_CENTRE, wxALIGN_CENTRE);
 GD1->SetDefaultCellBackgroundColour(wxColour(226, 249, 250));
 GD1->SetDefaultCellAlignment(wxALIGN_LEFT, wxALIGN_TOP);
 GD1->SetBackgroundColour(wxColour(236, 250, 251));
 s1->Add(GD1, 1, wxALL|wxEXPAND, 5);
 pSelBP = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
 wxBoxSizer* s17; s17 = new wxBoxSizer(wxVERTICAL);
 P_QtyPrep = new wxPanel(pSelBP,wxID_ANY, wxPoint(-1,-1), wxSize(-1,40), wxTAB_TRAVERSAL);
 P_QtyPrep->SetBackgroundColour(wxColour(247, 244, 232));
 P_QtyPrep->SetMinSize(wxSize(-1,40));
 wxBoxSizer* s14; s14 = new wxBoxSizer(wxHORIZONTAL);
 s14->Add(0, 0, 1, wxALL|wxEXPAND, 5);
 t12 = new wxStaticText(P_QtyPrep,wxID_ANY,wxT("Qty Preparată:"),wxDefaultPosition,
wxDefaultSize,0); t12->Wrap(-1); s14->Add(t12, 0, wxALL, 5);
eQtyPrep = new wxTextCtrl(P_QtyPrep, wxID_ANY, wxT("1"), wxDefaultPosition, wxSize(30,-1), 0);
 s14->Add(eQtyPrep, 0, wxALL, 5);
 bRezerva = new wxButton(P_QtyPrep,wxID_ANY,wxT("Rezervă !"),wxDefaultPosition, 
wxSize(-1,-1),0);
 s14->Add(bRezerva, 0, wxALL, 5); s14->Add(0,0,1,wxALL|wxEXPAND,5);
 P_QtyPrep->SetSizer(s14);P_QtyPrep->Layout();
 s17->Add(P_QtyPrep,0,wxALL|wxEXPAND,5);
 GD2 = new wxGrid(pSelBP,wxID_ANY,wxDefaultPosition,wxDefaultSize,wxALWAYS_SHOW_SB|
wxFULL_REPAINT_ON_RESIZE);
 GD2->CreateGrid(0,0); GD2->EnableEditing(true); 
 GD2->EnableGridLines(true);
 GD2->EnableDragGridSize(false);GD2->SetMargins(0, 0);
 GD2->AutoSizeColumns(); GD2->EnableDragColMove(false);
 GD2->EnableDragColSize(true); GD2->SetColLabelSize(20);
 GD2->SetColLabelAlignment(wxALIGN_CENTRE, wxALIGN_CENTRE);
 GD2->AutoSizeRows(); GD2->EnableDragRowSize(true); 
 GD2->SetRowLabelSize(80);
 GD2->SetRowLabelAlignment(wxALIGN_CENTRE, wxALIGN_CENTRE);
 GD2->SetDefaultCellBackgroundColour(wxColour(247, 224, 223));
 GD2->SetDefaultCellAlignment(wxALIGN_LEFT, wxALIGN_TOP);
 GD2->SetMinSize(wxSize(-1,200)); s17->Add(GD2,1,wxALL|wxEXPAND,5);
 p9 = new wxPanel(pSelBP,wxID_ANY,wxPoint(-1,-1),wxSize(-1,40),wxTAB_TRAVERSAL);
 p9->SetBackgroundColour(wxColour(243, 245, 220));
 wxBoxSizer* s15; s15 = new wxBoxSizer(wxHORIZONTAL);
 bDelLin=new wxButton(p9, wxID_ANY, wxT("Şterge linia"), wxDefaultPosition, wxDefaultSize,0);
 s15->Add(bDelLin, 0, wxALL, 5); s15->Add(0, 0, 1, wxEXPAND, 5);
 bBP = new wxButton(p9,wxID_ANY,wxT("OK"),wxDefaultPosition,wxDefaultSize,0);
 bBP->SetFont(wxFont(wxNORMAL_FONT->GetPointSize(),70,90,92,false, wxEmptyString));
 bBP->SetForegroundColour(wxColour(128, 49, 72));
 bBP->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_WINDOW));
 s15->Add(bBP, 0, wxALL, 5); p9->SetSizer(s15); p9->Layout();
 s17->Add(p9, 0, wxALL|wxEXPAND, 5); pSelBP->SetSizer(s17);
 pSelBP->Layout(); s17->Fit(pSelBP); s1->Add(pSelBP,1,wxEXPAND|wxALL,5);
 this->SetSizer(s1);this->Layout();this->Centre(wxBOTH);
bNom->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(iFSELST::selNom), NULL, this);
bRetFurnizor->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(iFSELST::retineFurnizor), NULL, 
this); 
bRetData->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(iFSELST::retineData), NULL, this);
cbDep->Connect(wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(iFSELST::selDep), NULL, this);
bRetDepAmp->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(iFSELST::retineDepAmp), NULL, 
this); 
bRetPO->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(iFSELST::retinePO), NULL, this);
bRetStatus->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(iFSELST::retineSTATUS),NULL,this);
bRetSerialNo->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(iFSELST::retineSerialNo), NULL, 
this); 
bRetID->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(iFSELST::retineID), NULL, this);
bCopiaza->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(iFSELST::copiaza), NULL, this);
bQ->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(iFSELST::qST), NULL, this);
bRezerva->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(iFSELST::rezervaQtySelST), NULL, 
this); 
bDelLin->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(iFSELST::delLinSelST), NULL, this);
bBP->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(iFSELST::transferBP), NULL, this);
const char* achN[] = {"inx.idcode", "refcom", "refteh", "descr", 
"supplier", "datain", "serialno","status","po", 
"stx.dep","stx.ampl","stx.id"};
const char* achT[] = {"C","C","C","A","C","D2","C","C","C","C","C","C"};
wxArrayString a; achBP=achBP1; 
for(unsigned int i=0;i<cblS->GetCount();i++)
 {listaN.Add(achN[i]); listaT.Add(achT[i]);}
aListaInit=cblS->GetStrings();
for(unsigned int j=0;j<cblS->GetCount();j++) 
 { val1.Add("NULL"); val2.Add("NULL");}
cx_grid1=new lxGrid(GD1,_("q_tmp_st"),a);
if(achBP != _("#")) cx_grid2=new lxGrid(GD2,_("tmpselst"),a);
 else pSelBP->Hide(); 
cx_dep = new lxComboBox(cbDep, _("DROP TABLE IF EXISTS tmpacc; CREATE TEMP TABLE tmpacc AS SELECT dep[s] FROM (select acces.*,generate_subscripts(dep,1) as s from logx.acces)par; SELECT DISTINCT loc.dep FROM logx.loc,tmpacc WHERE loc.dep=tmpacc.dep ORDER BY loc.dep;"));
//lista ptr.amplasament va cuprinde selecţia pentru primul depozit
cx_ampl = new lxComboBox(cbAmpl,_("SELECT DISTINCT ampl FROM logx.loc 
WHERE dep = (SELECT DISTINCT dep FROM logx.loc ORDER BY dep LIMIT 1) 
ORDER BY ampl;"));
}
//-------------------------------------------------------------------
iFSELST::~iFSELST() {
bNom->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(iFSELST::selNom), NULL, this);
bRetFurnizor->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(iFSELST::retineFurnizor), NULL, this); 
bRetData->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(iFSELST::retineData), NULL, this);
cbDep->Disconnect(wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(iFSELST::selDep), NULL, this);
bRetDepAmp->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(iFSELST::retineDepAmp), 
NULL, this); 
bRetPO->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(iFSELST::retinePO), NULL, this);
bRetStatus->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(iFSELST::retineSTATUS), NULL, 
this); 
bRetSerialNo->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(iFSELST::retineSerialNo), 
NULL, this); 
bRetID->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(iFSELST::retineID), NULL, this);
bCopiaza->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(iFSELST::copiaza), NULL, this);
bQ->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(iFSELST::qST), NULL, this);
bRezerva->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(iFSELST::rezervaQtySelST), NULL, 
this);
bDelLin->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(iFSELST::delLinSelST), NULL, this);
bBP->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(iFSELST::transferBP), NULL, this);
}
//-----------------------------------------------------------------
//FUNCŢIA DE INTEROGARE A STOCULUI
void iFSELST::qST(wxCommandEvent& event)
{wxString achListaCampuri, achTipCampuri, achAfisare, achSelectie, 
achVal1, achVal2, achOrd, achR, ach;
wxArrayInt b;
//selecţie obligatorie ptr. Dep,Ampl,ID
if(achBP!=_("#")) 
 for(int j=0;j<3;j++) cblA->Check(cblA->GetCount()-1-j); 
cblA->GetCheckedItems(b);
for(unsigned int j=0;j<12;j++)
 {if(!achListaCampuri.IsEmpty()) achListaCampuri=achListaCampuri+_(",");
 achListaCampuri=achListaCampuri+_("'")+listaN[j]+_("'"); 
 if(!achTipCampuri.IsEmpty()) achTipCampuri = achTipCampuri+_(",");
 achTipCampuri=achTipCampuri+_("'")+listaT[j]+_("'"); 
 if(!achAfisare.IsEmpty()) achAfisare=achAfisare+_(","); 
 if(cblA->IsChecked(j)) achAfisare=achAfisare+_("'t'"); 
 else achAfisare=achAfisare+_("'f'");
 if(!achSelectie.IsEmpty()) achSelectie=achSelectie+_(",");
 if(cblS->IsChecked(j)) achSelectie=achSelectie+_("'t'"); 
 else achSelectie=achSelectie+_("'f'");
 if(j) achVal1=achVal1+_(","); achVal1=achVal1+val1[j]; 
 if(j) achVal2=achVal2+_(","); achVal2=achVal2+val2[j]; 
 if(cbOrd->GetSelection()<12) achOrd=listaN[cbOrd->GetSelection()]; 
 else achOrd=_("---");
 }//endfor
if(achBP==_("#")) ach = _("ST"); else ach = _("STL"); 
//dacă interogarea este pentru rezervare (STL -stoc cu qtzdisp > 0
if((achR = lxCtrl::cda(_("SELECT logx.q_x('")+ ach+_("'::text,12::smallint, ARRAY[") + achListaCampuri+_("]::text[], ARRAY[") +
achTipCampuri + _("]::text[], ARRAY[") + achAfisare + _("]::boolean[], 
ARRAY[") + achSelectie +_("]::boolean[], ARRAY[") + achVal1+_("]::text[],
ARRAY[") + achVal2+_("]::text[], '")+achOrd+_("'::text);")))!=_("OK"))
wxMessageBox(achR);
GD1->SetRowLabelSize(20);
cx_grid1->preluareVarColRow(); 
if(achBP != _("#")) //dacă este selecţie pentru BP
lxCtrl::cda(_("DROP TABLE IF EXISTS tmpselst;CREATE TEMPORARY TABLE tmpselst as SELECT _bp.nrbp, _bp.qtyrez, inx.idcode, nom.descr, _bp.id, _bp.dep, _bp.ampl FROM logx.inx, logx.nom, logx._bp WHERE inx.idcode=nom.idcode AND _bp.id= inx.id AND _bp.nrbp=")+ achBP+_(" ;"));
}
//------------------------------------------------------------------
// AFIŞARE PANOU SELECŢIE --FILTRE 
void iFSELST::afis_sel()//afişare panou selecţie - filtrare
{wxString ach;
wxArrayString aLista;
aLista=aListaInit; cblS->Clear();
for(unsigned int j=0;j<aLista.GetCount();j++)
 {ach = aLista[j];
 if(val1[j]!=_("NULL")) //diferit de ŞIRUL ce conţine caracterele N U
L L!
 {if(val2[j]!=_("NULL") && (listaT[j]==_("N2") || 
listaT[j]==_("D2"))) 
 ach = val1[j] + wxT(" ≤ ") + aLista[j] + wxT(" ≤ ") +val2[j];
 if(val2[j]==_("NULL") && (listaT[j]==_("N1") || 
listaT[j]==_("D1")))
 ach= aLista[j] + _(" = ") + val1[j];
 if(val2[j]==_("NULL") && listaT[j]==_("C")) 
 ach= aLista[j] + wxT(" ") + val1[j]; ≡
 if(val2[j]==_("NULL") && listaT[j]==_("A")) 
 ach= val1[j] +wxT(" є ") + aLista[j] ; 
 if(val2[j]==_("NULL") && listaT[j]==_("B")) 
 ach= aLista[j] + _(" : ") + val1[j];
 } //endif 
 cblS->Append(ach);
 } //endfor
}
//------------------------------------------------------------------
//Selecţie NOMENCLATOR
void iFSELST::selNom(wxCommandEvent& event)
{wxArrayString* rez=new wxArrayString; 
iFNOM* x; x=new iFNOM(this,rez); x->ShowModal(); 
if(rez->GetCount()<1) 
 {wxMessageBox("Nu a fost selectat nimic !"); return;} 
for(int j=0; j<4; j++) 
 val1[j]=_("'")+rez->Item(j)+_("'");
afis_sel();}
//Şterge linia selectată
void iFSELST::delLinSelST(wxCommandEvent& event) 
{ wxArrayString achS;
//dacă există selecţie în cadrul gridului
if(!GD2->IsSelection()) 
 {wxMessageBox(wxT("Selectaţi linia!")); return;} 
for(int j=0; j<GD2->GetNumberCols(); j++)
 achS.Add(GD2->GetCellValue(GD2->GetSelectedRows()[0],j));
 wxString ach = lxCtrl::cda(_("SELECT logx.del_bp_id(")+ achBP+ 
_("::int,'")+achS[achS.GetCount()-1]+_("'::text,'")+achS[achS.GetCount()-
3]+_("'::text,'")+achS[achS.GetCount()-2]+_("'::text,")+eQtyPrep-
>GetValue()+_("::int);"));
if(ach != _("OK")) { wxMessageBox(ach); return;}
if(achBP != _("#")) //dacă este selecţie pentru BP
lxCtrl::cda(_("DROP TABLE IF EXISTS tmpselst; CREATE TEMPORARY TABLE 
tmpselst as SELECT _bp.nrbp, _bp.qtyrez, inx.idcode, nom.descr, _bp.id,
_bp.dep, _bp.ampl FROM logx.inx, logx.nom, logx._bp WHERE 
inx.idcode=nom.idcode AND _bp.id= inx.id AND _bp.nrbp=")+achBP+_(" ;"));
cx_grid2->preluareVarColRow(); GD2->Refresh();
}
//--------------------------------------------------------------------
//Rezervă cantitate din stoc
void iFSELST::rezervaQtySelST(wxCommandEvent& event)
{wxArrayString achS;
if(!GD1->IsSelection()) 
 {wxMessageBox(wxT("Selectaţi linia!")); return;} //dacă există 
selecţie în cadrul gridului
for(int j=0; j<GD1->GetNumberCols(); j++)
 achS.Add(GD1->GetCellValue(GD1->GetSelectedRows()[0],j));
if(eQtyPrep->IsEmpty()) 
 {wxMessageBox(wxT("Completaţi cantitatea!")); return;} 
wxString ach = lxCtrl::cda(_("SELECT logx.add_bp_id(")+ achBP+ 
_("::int,'")+achS[achS.GetCount()-1]+_("'::text,'")+achS[achS.GetCount()-
3]+_("'::text,'")+achS[achS.GetCount()-2]+_("'::text,")+eQtyPrep-
>GetValue()+_("::int);"));
if(ach != _("OK")) 
 { wxMessageBox(ach); return;}
if(achBP != _("#")) //dacă este selecţie pentru BP
 lxCtrl::cda(_("DROP TABLE IF EXISTS tmpselst; CREATE TEMPORARY TABLE 
tmpselst as SELECT _bp.nrbp, _bp.qtyrez, inx.idcode, nom.descr, _bp.id, 
_bp.dep, _bp.ampl FROM logx.inx, logx.nom, logx._bp WHERE inx.idcode = 
nom.idcode AND _bp.id = inx.id AND _bp.nrbp =")+achBP+_(" ;"));
GD1->DeleteRows(GD1->GetSelectedRows()[0]);
cx_grid2->preluareVarColRow(); GD1->Refresh(); GD2->Refresh();
}
//-------------------------------------------------------------------
//Închide fereastra de selecţie din stoc
void iFSELST::transferBP(wxCommandEvent& event)
{ lxCtrl::cda(_("DELETE FROM tmpselst USING logx._bp WHERE 
_bp.nrbp=tmpselst.nrbp AND _bp.id=tmpselst.id AND _bp.dep=tmpselst.dep 
AND _bp.ampl=tmpselst.ampl;"));
this->Close();
}
//---------------------------------------------------------------
//Schimbă lista cu amplasamentele în funcţie de depozitul selectat
void iFSELST::selDep(wxCommandEvent& event) 
{cx_ampl->rdLista(_("SELECT DISTINCT ampl::text FROM logx.loc WHERE 
dep='")+cx_dep->getSel()+("' ORDER BY ampl;"));
}
//------------------------------------------------------------------
//selectează depozitul şi amplasamentul curent
void iFSELST::retineDepAmp(wxCommandEvent& event) 
{ for(unsigned int j=0;j<listaN.GetCount();j++) 
 { if(listaN[j]==_("stx.dep")) val1[j]=_("'")+cx_dep->getSel()+_("'");
 if(listaN[j]==_("stx.ampl")) val1[j]=_("'")+cx_ampl->getSel()
+_("'");
 }
 afis_sel();
}
//--------------------------------------------------------------------
//selectează PO
void iFSELST::retinePO(wxCommandEvent& event) 
{ for(unsigned int j=0;j<listaN.GetCount();j++) 
 { if(listaN[j]==_("po") && !ePO->GetValue().IsEmpty()) 
 val1[j]=_("'")+ePO->GetValue()+_("'"); 
 }
 afis_sel();
}
//----------------------------------------------------------------
//selectează furnizor
void iFSELST::retineFurnizor(wxCommandEvent& event) 
{ for(unsigned int j=0;j<listaN.GetCount();j++) 
 { if(listaN[j]==_("supplier") && !eSupplier->GetValue().IsEmpty())
 val1[j]=_("'")+eSupplier->GetValue()+_("'"); 
 }
 afis_sel(); 
}
//------------------------------------------------------------------
//selectează STATUS
void iFSELST::retineSTATUS(wxCommandEvent& event) 
{ for(unsigned int j=0;j<listaN.GetCount();j++) 
 { if(listaN[j]==_("status") && !cbStatus-
>GetStringSelection().IsEmpty())
 val1[j]=_("'")+cbStatus->GetStringSelection()+_("'"); 
 }
 afis_sel(); 
}
//-----------------------------------------------------------------
//selectează SerialNo
void iFSELST::retineSerialNo(wxCommandEvent& event) 
{ for(unsigned int j=0;j<listaN.GetCount();j++) 
 { if(listaN[j]==_("serialno") && !eSerialNo->GetValue().IsEmpty()) 
 val1[j]=_("'")+eSerialNo->GetValue()+_("'"); 
 }
 afis_sel(); 
}
//-------------------------------------------------------------------
//selectează ID 
void iFSELST::retineID(wxCommandEvent& event) 
{ for(unsigned int j=0;j<listaN.GetCount();j++) { 
 if(listaN[j]==_("stx.id") && !eID->GetValue().IsEmpty())
	val1[j]=_("'")+eID->GetValue()+_("'"); 
 }
 afis_sel();
}
//-------------------------------------------------------------------
//selectează filtru data calendaristică de intrare 
void iFSELST::retineData(wxCommandEvent& event) 
{ for(unsigned int j=0;j<listaN.GetCount();j++) 
 {if(listaN[j]==_("datain")) 
 val1[j]=_("'")+eData1->GetValue().FormatISODate()+_("'"); 
 if(listaN[j]==_("datain")) 
 val2[j]=_("'")+eData2->GetValue().FormatISODate()+_("'"); 
 }
afis_sel();
}
//-------------------------------------------------------------------
//copiază datele din GRID ÎN CLIPBOARD în vederea exportului
void iFSELST::copiaza(wxCommandEvent& event) 
{ wxString ach,dx;
 for(int j=0;j<GD1->GetNumberCols();j++)
 { if(j) dx=dx+_(",");
dx = dx + GD1->GetColLabelValue(j); 
 }
 for(int i=0;i<GD1->GetNumberRows();i++)
{ dx=dx+_("\n");
 for(int j=0;j<GD1->GetNumberCols();j++) 
 { if(j) dx=dx+_(",");
 dx=dx+GD1->GetCellValue(i,j);
 }
}
if (wxTheClipboard->Open()) 
 {wxTheClipboard->SetData(new wxTextDataObject(dx)); 
 wxTheClipboard->Close(); 
 wxMessageBox(_("Au fost copiate "+ach.FromDouble(GD1->GetNumberRows()))
+ _(" linii !"));
 } 
 /*funcţia se poate extinde prin testarea existenţei virgulei în şir şi 
punerea între ghilimele a acestor şiruri etc*/
}
