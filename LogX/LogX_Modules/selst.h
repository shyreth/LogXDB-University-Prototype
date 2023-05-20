#ifndef __fselst__ //fişier selst.h
#define __fselst__
#include <wx/wx.h>
#include <wx/choicebk.h>
#include "lx.h"
class iFSELST : public wxDialog 
{ wxArrayString listaN,listaT,val1,val2;
 lxGrid *cx_grid1, *cx_grid2;
 lxComboBox *cx_dep, *cx_ampl;
 wxArrayString aL,sL,valL,aListaInit;
//lista cu câmpuri ptr. afişare şi selecţie 
 wxString achBP; //numărul BP pentru care se face selecţia 
 public:iFSELST(wxWindow* parent, wxString achBP1, wxWindowID id =
wxID_ANY, const wxString& title = wxT("SELECŢIE STOC"), const wxPoint&
pos = wxDefaultPosition, const wxSize& size = wxSize(800,650), 
long style = wxCLOSE_BOX|wxDEFAULT_DIALOG_STYLE|wxMAXIMIZE_BOX|wxMINIMIZE_BOX|
wxRESIZE_BORDER|wxFULL_REPAINT_ON_RESIZE);
virtual ~iFSELST();
protected:
 wxStaticText* t8; wxCheckListBox* cblA; wxStaticText* t9; 
wxCheckListBox* cblS; wxChoicebook* CBP; wxPanel* p1; wxButton* 
bNom; wxPanel* p2; wxStaticText* t1; wxTextCtrl* eSupplier; wxButton* 
bRetFurnizor; wxPanel* p3;
 wxDatePickerCtrl* eData1; wxStaticText* t2; wxDatePickerCtrl* eData2;
wxButton* bRetData; wxPanel* p4; wxStaticText* t3; wxComboBox* cbDep; 
wxStaticText* t4; wxComboBox* cbAmpl; wxButton* bRetDepAmp; wxPanel*
p5; wxStaticText* t5; wxTextCtrl* ePO; wxButton* bRetPO; wxPanel* p6; 
wxStaticText* t6; wxChoice* cbStatus; wxButton* bRetStatus; wxPanel* p7; 
wxStaticText* t7; wxTextCtrl* eSerialNo; wxButton* bRetSerialNo;
wxPanel* p10; wxStaticText* t10; wxTextCtrl* eID; wxButton*
bRetID; wxStaticText* t13; wxChoice* cbOrd; wxButton* bCopiaza; 
wxButton* bQ; wxGrid* GD1; wxPanel* pSelBP; wxPanel* P_QtyPrep;
wxStaticText* t12; wxTextCtrl* eQtyPrep; wxButton* bRezerva; 
wxGrid* GD2; wxPanel* p9; wxButton* bDelLin; wxButton* bBP;
virtual void selNom(wxCommandEvent& event);//Selecţie NOMENCLATOR
virtual void retineFurnizor(wxCommandEvent& event);//selectează furnizor
virtual void retineData(wxCommandEvent& event);//selectează filtru data calendaristică de intrare
virtual void selDep(wxCommandEvent& event);//Schimbă lista cu amplasamentele în funcţie de depozitul selectat
virtual void retineDepAmp(wxCommandEvent& event);//selectează depozitul şi amplasamentul curent 
virtual void retinePO(wxCommandEvent& event);//selectează PO
virtual void retineID(wxCommandEvent& event);//selectează ID 
virtual void retineSTATUS(wxCommandEvent& event);//selectează STATUS
virtual void retineSerialNo(wxCommandEvent& event);//selectează SerialNo
virtual void qST(wxCommandEvent& event);//FUNCŢIA DE INTEROGARE A STOCULUI
virtual void rezervaQtySelST(wxCommandEvent& event);//Rezervă item-uri
virtual void delLinSelST(wxCommandEvent& event);//Şterge linia selectată
virtual void transferBP(wxCommandEvent& event);//Închide fereastra de sel.
virtual void copiaza(wxCommandEvent& event);//Copiază din GRID în CLIPBOARD
virtual void afis_sel(); // AFIŞARE PANOU SELECŢIE --FILTRE
};
#endif //__fselst__