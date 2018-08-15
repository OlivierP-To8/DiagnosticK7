/***************************************************************
 * Author  : OlivierP
 * Date    : 2010-04-22
 * License : GNU GPLv3 (http://www.gnu.org/copyleft/gpl.html)
 **************************************************************/

#include "Resultat.h"

//(*InternalHeaders(Resultat)
#include <wx/intl.h>
#include <wx/string.h>
//*)

//(*IdInit(Resultat)
const long Resultat::ID_TEXTCTRL1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(Resultat,wxDialog)
	//(*EventTable(Resultat)
	//*)
END_EVENT_TABLE()

Resultat::Resultat(wxWindow* parent,wxWindowID id)
{
	//(*Initialize(Resultat)
	Create(parent, id, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER|wxMAXIMIZE_BOX, _T("id"));
	BoxSizer1 = new wxBoxSizer(wxVERTICAL);
	TextCtrl1 = new wxTextCtrl(this, ID_TEXTCTRL1, wxEmptyString, wxDefaultPosition, wxSize(700,480), wxTE_MULTILINE|wxTE_READONLY, wxDefaultValidator, _T("ID_TEXTCTRL1"));
	BoxSizer1->Add(TextCtrl1, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	SetSizer(BoxSizer1);
	BoxSizer1->Fit(this);
	BoxSizer1->SetSizeHints(this);
	Center();
	//*)
}

Resultat::~Resultat()
{
	//(*Destroy(Resultat)
	//*)
}
void Resultat::SetLog(wxString log){	if (TextCtrl1 != NULL)	{		wxFont font(8, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxEmptyString, wxFONTENCODING_SYSTEM);		TextCtrl1->SetFont(font);
		TextCtrl1->SetMaxLength(0);		TextCtrl1->AppendText(log);	}	if (BoxSizer1 != NULL)	{		BoxSizer1->Fit(this);		BoxSizer1->SetSizeHints(this);	}}
