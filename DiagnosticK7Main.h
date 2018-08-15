/***************************************************************
 * Author  : OlivierP
 * Date    : 2010-04-22
 * License : GNU GPLv3 (http://www.gnu.org/copyleft/gpl.html)
 **************************************************************/

#ifndef K7CLEANERMAIN_H
#define K7CLEANERMAIN_H

//(*Headers(DiagnosticK7Frame)
#include <wx/listctrl.h>
#include <wx/sizer.h>
#include <wx/menu.h>
#include <wx/dirdlg.h>
#include <wx/frame.h>
#include <wx/statusbr.h>
//*)

class DiagnosticK7Frame: public wxFrame
{
	public:

		DiagnosticK7Frame(wxWindow* parent,wxWindowID id = -1);
		virtual ~DiagnosticK7Frame();

		long GetSortColumn() { return sortCol; }
		wxString GetListCtrlCellString(long row, long col);
		void FixListCtrlItems();

	private:

		//(*Handlers(DiagnosticK7Frame)
		void OnQuit(wxCommandEvent& event);
		void OnAbout(wxCommandEvent& event);
		void OnAjoutChemin(wxCommandEvent& event);
		void OnAnalyserK7(wxCommandEvent& event);
		void OnItemActivated(wxListEvent& event);
		void OnColumnClick(wxListEvent& event);
		void OnDoExportCSV(wxCommandEvent& event);
		//*)

		//(*Identifiers(DiagnosticK7Frame)
		static const long ID_LISTCTRL1;
		static const long idAjoutChemin;
		static const long idAnalyser;
		static const long idExportCSV;
		static const long idMenuQuit;
		static const long idMenuAbout;
		static const long ID_STATUSBAR1;
		//*)

		//(*Declarations(DiagnosticK7Frame)
		wxListCtrl* ListCtrl1;
		wxMenuItem* MenuItem4;
		wxMenuItem* MenuItem3;
		wxStatusBar* StatusBar1;
		wxDirDialog* DirDialog1;
		//*)
		long sortCol;
		wxArrayString k7logs;

		DECLARE_EVENT_TABLE()
};

#endif // K7CLEANERMAIN_H
