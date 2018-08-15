/***************************************************************
 * Author  : OlivierP
 * Date    : 2010-04-22
 * License : GNU GPLv3 (http://www.gnu.org/copyleft/gpl.html)
 **************************************************************/

#include "DiagnosticK7Main.h"
#include <wx/msgdlg.h>
#include <wx/dir.h>
#include <wx/filename.h>
#include <wx/arrstr.h>
#include <wx/filedlg.h>
#include <wx/icon.h>
#include "analysek7.h"

//(*InternalHeaders(DiagnosticK7Frame)
#include <wx/intl.h>
#include <wx/string.h>
//*)

enum listeCols
{
	cNom = 0,
	cMD5brut,
	cMD5propre,
	cMOTO,
	cNbPerdus,
	cDiagnostic,
	cChemin,
	cContenu,
	cMax
};


//(*IdInit(DiagnosticK7Frame)
const long DiagnosticK7Frame::ID_LISTCTRL1 = wxNewId();
const long DiagnosticK7Frame::idAjoutChemin = wxNewId();
const long DiagnosticK7Frame::idAnalyser = wxNewId();
const long DiagnosticK7Frame::idExportCSV = wxNewId();
const long DiagnosticK7Frame::idMenuQuit = wxNewId();
const long DiagnosticK7Frame::idMenuAbout = wxNewId();
const long DiagnosticK7Frame::ID_STATUSBAR1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(DiagnosticK7Frame,wxFrame)
	//(*EventTable(DiagnosticK7Frame)
	//*)
END_EVENT_TABLE()

DiagnosticK7Frame::DiagnosticK7Frame(wxWindow* parent,wxWindowID id)
{
	//(*Initialize(DiagnosticK7Frame)
	wxMenuItem* MenuItem5;
	wxMenuItem* MenuItem2;
	wxMenuItem* MenuItem1;
	wxMenu* Menu1;
	wxBoxSizer* BoxSizer1;
	wxMenuBar* MenuBar1;
	wxMenu* Menu2;

	Create(parent, id, _(L"DiagnosticK7"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("id"));
	BoxSizer1 = new wxBoxSizer(wxVERTICAL);
	ListCtrl1 = new wxListCtrl(this, ID_LISTCTRL1, wxDefaultPosition, wxSize(617,288), wxLC_REPORT|wxLC_SORT_ASCENDING|wxVSCROLL|wxHSCROLL, wxDefaultValidator, _T("ID_LISTCTRL1"));
	BoxSizer1->Add(ListCtrl1, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
	SetSizer(BoxSizer1);
	MenuBar1 = new wxMenuBar();
	Menu1 = new wxMenu();
	MenuItem3 = new wxMenuItem(Menu1, idAjoutChemin, _(L"Ajout chemin"), _(L"Ajouter le contenu d\'un répertoire"), wxITEM_NORMAL);
	Menu1->Append(MenuItem3);
	MenuItem4 = new wxMenuItem(Menu1, idAnalyser, _(L"Analyser"), _(L"Analyser les fichiers"), wxITEM_NORMAL);
	Menu1->Append(MenuItem4);
	MenuItem5 = new wxMenuItem(Menu1, idExportCSV, _(L"Export CSV"), _(L"Exporter ce qui est affiché"), wxITEM_NORMAL);
	Menu1->Append(MenuItem5);
	MenuItem1 = new wxMenuItem(Menu1, idMenuQuit, _(L"Quitter\tAlt-F4"), _(L"Quitter l\'application"), wxITEM_NORMAL);
	Menu1->Append(MenuItem1);
	MenuBar1->Append(Menu1, _(L"&Fichier"));
	Menu2 = new wxMenu();
	MenuItem2 = new wxMenuItem(Menu2, idMenuAbout, _(L"A propos\tF1"), _(L"Informations sur cette application"), wxITEM_NORMAL);
	Menu2->Append(MenuItem2);
	MenuBar1->Append(Menu2, _(L"&Aide"));
	SetMenuBar(MenuBar1);
	StatusBar1 = new wxStatusBar(this, ID_STATUSBAR1, 0, _T("ID_STATUSBAR1"));
	int __wxStatusBarWidths_1[1] = { -1 };
	int __wxStatusBarStyles_1[1] = { wxSB_NORMAL };
	StatusBar1->SetFieldsCount(1,__wxStatusBarWidths_1);
	StatusBar1->SetStatusStyles(1,__wxStatusBarStyles_1);
	SetStatusBar(StatusBar1);
	DirDialog1 = new wxDirDialog(this, _(L"Select directory"), wxEmptyString, wxDD_DEFAULT_STYLE, wxDefaultPosition, wxDefaultSize, _T("wxDirDialog"));
	BoxSizer1->Fit(this);
	BoxSizer1->SetSizeHints(this);
	Center();

	Connect(ID_LISTCTRL1,wxEVT_COMMAND_LIST_ITEM_ACTIVATED,(wxObjectEventFunction)&DiagnosticK7Frame::OnItemActivated);
	Connect(ID_LISTCTRL1,wxEVT_COMMAND_LIST_COL_CLICK,(wxObjectEventFunction)&DiagnosticK7Frame::OnColumnClick);
	Connect(idAjoutChemin,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&DiagnosticK7Frame::OnAjoutChemin);
	Connect(idAnalyser,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&DiagnosticK7Frame::OnAnalyserK7);
	Connect(idExportCSV,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&DiagnosticK7Frame::OnDoExportCSV);
	Connect(idMenuQuit,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&DiagnosticK7Frame::OnQuit);
	Connect(idMenuAbout,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&DiagnosticK7Frame::OnAbout);
	//*)

	wxIcon icon(wxT("aaaa"));
	SetIcon( icon );

	wxListItem itemCol;
	itemCol.SetText(wxT("Nom"));
	ListCtrl1->InsertColumn(cNom, itemCol);
	itemCol.SetText(wxT("MD5 brut"));
	ListCtrl1->InsertColumn(cMD5brut, itemCol);
	itemCol.SetText(wxT("MD5 propre"));
	ListCtrl1->InsertColumn(cMD5propre, itemCol);
	itemCol.SetText(wxT("MO/TO"));
	ListCtrl1->InsertColumn(cMOTO, itemCol);
	itemCol.SetText(wxT("octets en trop"));
	ListCtrl1->InsertColumn(cNbPerdus, itemCol);
	itemCol.SetText(wxT("diagnostic"));
	ListCtrl1->InsertColumn(cDiagnostic, itemCol);
	itemCol.SetText(wxT("Chemin"));
	ListCtrl1->InsertColumn(cChemin, itemCol);
	itemCol.SetText(wxT("Contenu"));
	ListCtrl1->InsertColumn(cContenu, itemCol);
	ListCtrl1->SetColumnWidth(cContenu, 0);
}

DiagnosticK7Frame::~DiagnosticK7Frame()
{
	//(*Destroy(DiagnosticK7Frame)
	//*)
}

void DiagnosticK7Frame::OnQuit(wxCommandEvent& event)
{
	Close();
}

#include "About.h"
void DiagnosticK7Frame::OnAbout(wxCommandEvent& event)
{
	About *about = new About(this);
	about->ShowModal();
}

void DiagnosticK7Frame::OnAjoutChemin(wxCommandEvent& event)
{
	if (DirDialog1->ShowModal() == wxID_OK)
	{
		wxString dirname = DirDialog1->GetPath();
		wxDir dir(dirname);
		if ( dir.IsOpened() )
		{
			long rn = ListCtrl1->GetItemCount();
			wxString filename;
			bool cont = dir.GetFirst(&filename, wxT("*.k7"), wxDIR_FILES);
			while ( cont )
			{
				int idx = ListCtrl1->InsertItem(rn++, wxEmptyString);
				if (idx != -1)
				{
					ListCtrl1->SetItem(idx, cNom, filename);
					ListCtrl1->SetItem(idx, cChemin, dirname);
				}
				cont = dir.GetNext(&filename);
			}
		    FixListCtrlItems();
	        ListCtrl1->SetColumnWidth(cNom, wxLIST_AUTOSIZE);
	        ListCtrl1->SetColumnWidth(cChemin, wxLIST_AUTOSIZE);
		}
	}
}

void DiagnosticK7Frame::OnAnalyserK7(wxCommandEvent& event)
{
	long rnmax = ListCtrl1->GetItemCount();
	long rn = ListCtrl1->GetNextItem(-1, wxLIST_NEXT_ALL);
	while (rn != -1)
	{
		wxString k7file = GetListCtrlCellString(rn, cChemin) + wxFileName::GetPathSeparator() + GetListCtrlCellString(rn, cNom);

		analyseK7 k7;
		if (k7.open(k7file))
		{
			if (GetListCtrlCellString(rn, cMD5brut).IsEmpty())
			{
				StatusBar1->SetStatusText(wxString::Format(wxT("%2d/%2d - Analyse de "), rn, rnmax) + GetListCtrlCellString(rn, cNom));

				bool k7ok = k7.run();
				k7.close();

				// md5 brut
				ListCtrl1->SetItem(rn, cMD5brut, k7.getMD5brut());

				// md5 propre
				if ((k7ok == true) && (k7.isParasites() == false) &&
					((k7.getTypeK7() == bSynchroMO) || (k7.getTypeK7() == bSynchroTO)))
				{
					ListCtrl1->SetItem(rn, cMD5propre, k7.getMD5propre());
					//if (k7.getMD5brut().Cmp(k7.getMD5propre()) == 0)
					//{
					//	ListCtrl1->SetItemBackgroundColour(rn, wxColour(0, 255, 0));
					//}
					//else if (k7.getDiagnostic().IsEmpty() == false)
					//{
					//	ListCtrl1->SetItemBackgroundColour(rn, wxColour(0, 255, 255));
					//}
				}

				// MO/TO
				switch (k7.getTypeK7())
				{
					case bSynchroMO:
						ListCtrl1->SetItem(rn, cMOTO, wxT("MO"));
						break;
					case bSynchroTO:
						ListCtrl1->SetItem(rn, cMOTO, wxT("TO"));
						break;
					case bErreur:
						ListCtrl1->SetItem(rn, cMOTO, wxT("??"));
						break;
					case bInconnu:
						ListCtrl1->SetItem(rn, cMOTO, wxT("?"));
						break;
				}

				// octets en trop
				ListCtrl1->SetItem(rn, cNbPerdus, wxString::Format(wxT("%d"), k7.getNbOctetsPerdus()));

				// diagnostic
				ListCtrl1->SetItem(rn, cDiagnostic, k7.getDiagnostic());

				// contenu
				size_t il = k7logs.Add(k7.getLog());
				ListCtrl1->SetItem(rn, cContenu, wxString::Format(wxT("%d"), il));
			}
			else
			{
				StatusBar1->SetStatusText(wxString::Format(wxT("%2d/%2d"), rn, rnmax));
			}
		}
		else
		{
			ListCtrl1->SetItemBackgroundColour(rn, wxColour(255, 0, 0));
		}

		rn = ListCtrl1->GetNextItem(rn, wxLIST_NEXT_ALL);
	}
	ListCtrl1->SetColumnWidth(cMD5brut, wxLIST_AUTOSIZE);
	ListCtrl1->SetColumnWidth(cMD5propre, wxLIST_AUTOSIZE);
	ListCtrl1->SetColumnWidth(cMOTO, wxLIST_AUTOSIZE);
	ListCtrl1->SetColumnWidth(cNbPerdus, wxLIST_AUTOSIZE);
	ListCtrl1->SetColumnWidth(cDiagnostic, wxLIST_AUTOSIZE);
	StatusBar1->SetStatusText(wxT("Analyse terminée"));
}

void DiagnosticK7Frame::OnDoExportCSV(wxCommandEvent& event)
{
	wxString filename = wxFileSelector(wxT("Choisissez un fichier"), wxEmptyString,
		wxT("diagnosticK7.csv"), wxT("csv"), wxT("*.csv"), wxFD_SAVE, this);
	if (!filename.IsEmpty())
	{
		FILE *f = fopen(filename.ToAscii(), "wb");
		if (f != NULL)
		{
			int rnmax = ListCtrl1->GetItemCount();
			for (int rn = 0; rn < rnmax; rn++)
			{
				wxString ligne = wxEmptyString;
				for (int c=0; c<cContenu; c++)
				{
					ligne += GetListCtrlCellString(rn, c);
					ligne += wxT(";");
				}
				ligne += wxT("\n");
				fputs(ligne.ToAscii(), f);
			}
			fclose(f);
		}
	}
}

wxString DiagnosticK7Frame::GetListCtrlCellString(long row, long col)
{
	wxListItem info;
	info.SetId(row);
	info.SetColumn(col);
	info.SetMask(wxLIST_MASK_TEXT);

	ListCtrl1->GetItem(info);

	return info.GetText();
}

void DiagnosticK7Frame::FixListCtrlItems()
{
	long i = ListCtrl1->GetNextItem(-1, wxLIST_NEXT_ALL);
	while (i != -1)
	{
		ListCtrl1->SetItemData(i,i);
		i = ListCtrl1->GetNextItem(i, wxLIST_NEXT_ALL);
	}
}

int wxCALLBACK MyCompareFunction(wxIntPtr item1, wxIntPtr item2, wxIntPtr sortData)
{
	DiagnosticK7Frame *doub = (DiagnosticK7Frame *)sortData;
	if (doub != NULL)
	{
		wxString str1 = doub->GetListCtrlCellString(item1, doub->GetSortColumn());
		wxString str2 = doub->GetListCtrlCellString(item2, doub->GetSortColumn());

		return str1.Cmp(str2);
	}
	return 0;
}

void DiagnosticK7Frame::OnColumnClick(wxListEvent& event)
{
	sortCol = event.GetColumn();

	FixListCtrlItems();
	ListCtrl1->SortItems(MyCompareFunction, (wxIntPtr)this);
	FixListCtrlItems();

	long nb = 0;
	wxColour cVert(0, 255, 0);
	wxColour cBleu(0, 192, 255);
	wxColour cBlanc(255, 255, 255);
	wxColour color;
	wxString prevval, currval;
	long previ = ListCtrl1->GetNextItem(-1, wxLIST_NEXT_ALL);
	if (previ != -1)
	{
		ListCtrl1->SetItemBackgroundColour(previ, cBlanc);
		prevval = GetListCtrlCellString(previ, sortCol);
		long i = ListCtrl1->GetNextItem(previ, wxLIST_NEXT_ALL);
		while (i != -1)
		{
			currval = GetListCtrlCellString(i, sortCol);
			if ((currval.length() > 0) && (currval.Cmp(prevval) == 0))
			{
				if ((nb % 2) == 0)
					color = cVert;
				else
					color = cBleu;

				ListCtrl1->SetItemBackgroundColour(previ, color);
				ListCtrl1->SetItemBackgroundColour(i, color);
			}
			else
			{
				ListCtrl1->SetItemBackgroundColour(i, cBlanc);
				if (ListCtrl1->GetItemBackgroundColour(previ) != cBlanc)
					nb++;
			}

			previ = i;
			prevval = currval;
			i = ListCtrl1->GetNextItem(i, wxLIST_NEXT_ALL);
		}
	}
}

#include "Resultat.h"
void DiagnosticK7Frame::OnItemActivated(wxListEvent& event)
{
	if (event.GetIndex() >= 0)
	{
		Resultat *res = new Resultat(this);
		if (res != NULL)
		{
			long nb = 0;
			if (GetListCtrlCellString(event.GetIndex(), cContenu).ToLong(&nb, 10))
			{
				res->SetLog(k7logs[nb]);
				res->ShowModal();
			}
		}
	}
}

