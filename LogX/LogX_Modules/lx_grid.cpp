#include "lx_grid.h" //fişierul lx_grid.cpp
lxGrid::lxGrid(wxGrid *gridX1, wxString tabelBD1, wxArrayString 
dencol1):lxCtrl()
{ gridX=gridX1; tabelBD=tabelBD1; dencol=dencol1; tipCol=NULL;
/*se trece null ptr. a putea face verificarea în destructor - dacă a fost sau nu alocată memorie*/
}
//-------------------------------------------------------------------
lxGrid::~lxGrid()
{ if(tipCol) delete[] tipCol;
}
/* 1043 varchar ; 1082 date; 1083 time; 11579 seq; 21 int2 ; 23 int4; 20
int8; 16 bool; 25 text ; 700 float4; 701 float8; 25 text
- tabelele temporare de interfaţă NU vor conţine date de tip serial, 
acestea pot fi doar în tabelul sursă*/
//--------------------------------------------------------------------
void lxGrid::salvare()
{ wxString achQ,ach;
int nrCampuri=gridX->GetNumberCols();
int nrInregistrari=gridX->GetNumberRows();
 //construim interogare pentru fiecare linie
 achQ=" DELETE FROM "+tabelBD+"; INSERT INTO "+tabelBD+" VALUES "; 
 for(int i=0;i<nrInregistrari;i++)
 {for(int j=0;j<nrCampuri;j++)
 {if(!j) ach=wxT("("); else ach=ach+",";
if(gridX->GetCellValue(i,j).IsEmpty()) ach=ach+" NULL ";
 else 
switch(tipCol[j])
 {case 1042: case 1043: case 1083: case 25: case 16:
 ach=ach+_("'")+gridX->GetCellValue(i,j)+_("'"); break;
 case 1082: ach=ach+_("to_date('")+gridX->GetCellValue(i,j)
+_("','dd.mm.yyyy'"); break; 
 case 11579: case 21: case 23: case 20: case 700: case 701:
 ach=ach+gridX->GetCellValue(i,j); break;
 default: wxMessageBox(_("Tip de date neidentificat !"));
 }
 }
 ach=ach+")";
 if(i) achQ=achQ+wxT(",");
 achQ=achQ+ach;
 }
 rezultatRx = PQexec(conexiune0, achQ.ToUTF8());
 if(PQresultStatus(rezultatRx) != PGRES_COMMAND_OK) 
 {wxMessageBox(_("Eroare salvare din grid în ")+tabelBD+_("!")); }
 return;
}
//--------------------------------------------------------------------
void lxGrid::preluareVarColRow()
{ wxString achY; /*dacă nu există denumire a coloanelor transmisă şi 
există coloane în grid se vor şterge celelalte coloane */
if(!dencol.GetCount() && gridX->GetNumberCols()>0) 
gridX->DeleteCols(0,gridX->GetNumberCols()); 
//dacă există linii în grid acestea se vor şterge
if(gridX->GetNumberRows()>0) 
 gridX->DeleteRows(0,gridX->GetNumberRows());
//preia datele din tabelul "tabelBD" în structura rezultatRx
wxString ach,achQ; achQ=_("SELECT * FROM ")+tabelBD+_(";"); 
rezultatRx = PQexec(conexiune0,achQ);
//testează operaţia de preluare a datelor
if(PQresultStatus(rezultatRx) != PGRES_TUPLES_OK)
wxMessageBox(_("Interogare ptr. preluare eronata: ")+achQ+_(" !"));
int nrCampuri = PQnfields(rezultatRx); int 
nrInregistrari=PQntuples(rezultatRx);
if(((unsigned int)nrCampuri !=dencol.GetCount()) && dencol.GetCount()>0) 
 {wxMessageBox("Nr. de coloane din grid diferea de cele din tabel!");return;}
if(gridX->GetNumberCols()<1) gridX->AppendCols(nrCampuri);
gridX->AppendRows(nrInregistrari);
/*dacă există denumiri ptr. coloane, transmise, acestea vor fi setate cu
denumirile transmise, altfel preia den. câmpurilor*/
if(dencol.GetCount()) 
 for(unsigned int j=0;j<dencol.Count();j++) 
 gridX->SetColLabelValue(j,dencol[j]);
else 
for(int j = 0; j<nrCampuri; j++) 
{ach=ach.FromUTF8(PQfname(rezultatRx,j));gridX->SetColLabelValue(j,ach);}
//determină tipul de dată pentru fiecare câmp şi îl stochează într-un vector
tipCol = new int[nrCampuri]; 
for(int j=0;j<nrCampuri;j++) tipCol[j]= (int)PQftype(rezultatRx, j);
sirRcampuri=""; 
for(unsigned int j=1;j<dencol.GetCount();j++) 
 {if(j>1) sirRcampuri=sirRcampuri+_(",");
 ach=ach.FromUTF8(PQfname(rezultatRx,j)); sirRcampuri=sirRcampuri+ach;
 } 
for(int i = 0; i < nrInregistrari; i++) 
 { for(int j = 0; j < nrCampuri; j++) 
 {ach=ach.FromUTF8(PQgetvalue(rezultatRx, i, j)); 
 gridX->SetCellValue(i,j,ach);
 }
 }
//setarea gridului în modul "selecţie rând"
gridX->SetSelectionMode(wxGrid::wxGridSelectRows);
//setare culori alternate pentru randuri
//ATENŢIE ! Pentru fiecare atribuire este necesară o instanţiere !
for(int i=0; i<gridX->GetNumberRows(); i++) 
 { if(i%2)
{ wxGridCellAttr *A_rand = new wxGridCellAttr(); 
 A_rand->SetBackgroundColour(wxColor(220,250,150)); 
 gridX->SetRowAttr(i,A_rand);
 }
 else { wxGridCellAttr *A_rand = new wxGridCellAttr(); 
 A_rand->SetBackgroundColour(wxColor(248,253,217)); 
 gridX->SetRowAttr(i,A_rand);
 }
 }//endfor
gridX->AutoSize(); gridX->Fit(); this->refresh();
}
