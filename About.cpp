/***************************************************************
 * Author  : OlivierP
 * Date    : 2010-04-22
 * License : GNU GPLv3 (http://www.gnu.org/copyleft/gpl.html)
 **************************************************************/

#include "About.h"

//(*InternalHeaders(About)
#include <wx/intl.h>
#include <wx/string.h>
//*)

//(*IdInit(About)
const long About::ID_STATICTEXT1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(About,wxDialog)
	//(*EventTable(About)
	//*)
END_EVENT_TABLE()

About::About(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(About)
	
	Create(parent, id, wxEmptyString, wxDefaultPosition, wxSize(600,500), wxDEFAULT_DIALOG_STYLE, _T("id"));
	StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _(L"DiagnosticK7 1.0 par OlivierP.\n___________________________________________________________________________________\n\nLICENCE D\'UTILISATION\nCe logiciel est fourni en l\'état. L\'utilisateur l\'utilise à ses risques et périls, sans garantie d\'aucune sorte de la part de l\'auteur. L\'auteur n\'est responsable d\'aucun dommage subi par l\'utilisateur pouvant résulter de l\'utilisation ou de la distribution de ce logiciel. \nL\'utilisateur a le droit d\'utiliser ce logiciel et d\'en faire autant de copies qu\'il le souhaite. \nL\'utilisation de ce logiciel vaut acceptation par l\'utilisateur des termes de la licence ci-dessus.\n___________________________________________________________________________________\n\nAttention, les formats protégés ne sont pas gérés, ils sont souvent considérés par cet utilitaire comme ayant des erreurs cheksum ou des parasites. \n\nCet utilitaire analyse les fichiers K7 pour MO/TO et affiche plusieurs informations :\n - le MD5 brut, de l\'ensemble des octets. \n - le MD5 propre, tel qu\'il serait si les synchronisations entre blocs étaient correctes. \n - le type d\'ordinateur : MO ou TO. \n - le nombre d\'octets en trop (parasites ou octets superflus en fin de fichier). \n - le diagnostic : OK / DC / DCMO5 / DCMO6 / DCMOTO / Pb. Synchro / Parasites / Err. Checksum.\n\nPour voir le détail d\'un fichier, double-cliquer sur sa ligne.\nPour trier les colonnes et afficher les doublons en couleur, cliquer sur le nom de la colonne.\n___________________________________________________________________________________\n\nLe calcul des MD5 est effectué par la librairie RFC1321-based (RSA-free) disponible à http://libmd5-rfc.sourceforge.net/\n___________________________________________________________________________________\n\nMerci à Daniel pour les informations sur la structure des fichiers K7. "), wxDefaultPosition, wxSize(503,399), wxST_NO_AUTORESIZE, _T("ID_STATICTEXT1"));
	Center();
	//*)
}

About::~About()
{
	//(*Destroy(About)
	//*)
}

