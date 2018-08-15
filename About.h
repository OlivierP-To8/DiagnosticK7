/***************************************************************
 * Author  : OlivierP
 * Date    : 2010-04-22
 * License : GNU GPLv3 (http://www.gnu.org/copyleft/gpl.html)
 **************************************************************/

#ifndef ABOUT_H
#define ABOUT_H

//(*Headers(About)
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/dialog.h>
//*)

class About: public wxDialog
{
	public:

		About(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~About();

		//(*Declarations(About)
		wxStaticText* StaticText1;
		//*)

	protected:

		//(*Identifiers(About)
		static const long ID_STATICTEXT1;
		//*)

	private:

		//(*Handlers(About)
		//*)

		DECLARE_EVENT_TABLE()
};

#endif
