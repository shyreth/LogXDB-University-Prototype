#ifndef _lxGrid_ //fişierul lx_grid.h
#define _lxGrid_ 
#include <wx/wx.h>
#include <wx/grid.h>
#include "lx_ctrl.h"
//clasa asigură o legătură între un control wxGrid şi un tabel
PostgreSQL, se presupune că ambele există înainte de instanţierea clasei
class lxGrid:public lxCtrl
{protected: 
 wxGrid *gridX;
int *tipCol;// tipul fiecărei coloane (nr. OID din tabelul
pg_catalog.pg_type)
PGresult *rezultatRx;
 wxString tabelBD;//tabel temporar
wxArrayString dencol; //denumiri coloane
wxString sirRcampuri;//şirul cu denumirile câmpurilor, mai puţin tcu
public:
 lxGrid(wxGrid *gridX1, wxString tabelBD1, wxArrayString dencol1);
~lxGrid();
 void preluareVarColRow(); // din tabel BD în GRID
 void salvare(); //din grid în tabel
}; 
#endif
