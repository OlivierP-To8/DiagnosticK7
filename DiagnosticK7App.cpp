/***************************************************************
 * Author  : OlivierP
 * Date    : 2010-04-22
 * License : GNU GPLv3 (http://www.gnu.org/copyleft/gpl.html)
 **************************************************************/

#include "DiagnosticK7App.h"

//(*AppHeaders
#include "DiagnosticK7Main.h"
#include <wx/image.h>
//*)

IMPLEMENT_APP(DiagnosticK7App);

bool DiagnosticK7App::OnInit()
{
	//(*AppInitialize
	bool wxsOK = true;
	wxInitAllImageHandlers();
	if ( wxsOK )
	{
		DiagnosticK7Frame* Frame = new DiagnosticK7Frame(0);
		Frame->Maximize();
		Frame->Show();		SetTopWindow(Frame);
	}
	//*)
	return wxsOK;

}
