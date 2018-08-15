/***************************************************************
 * Author  : OlivierP
 * Date    : 2010-04-22
 * License : GNU GPLv3 (http://www.gnu.org/copyleft/gpl.html)
 **************************************************************/

#ifndef RESULTAT_H
#define RESULTAT_H

//(*Headers(Resultat)
#include <wx/sizer.h>
#include <wx/textctrl.h>
#include <wx/dialog.h>
//*)

class Resultat: public wxDialog
{
	public:

		Resultat(wxWindow* parent,wxWindowID id=wxID_ANY);
		virtual ~Resultat();		void SetLog(wxString log);

		//(*Declarations(Resultat)
		wxBoxSizer* BoxSizer1;
		wxTextCtrl* TextCtrl1;
		//*)

	protected:

		//(*Identifiers(Resultat)
		static const long ID_TEXTCTRL1;
		//*)

	private:

		//(*Handlers(Resultat)
		//*)

		DECLARE_EVENT_TABLE()
};

#endif
