/***************************************************************
 * Author  : OlivierP
 * Date    : 2010-04-22
 * License : GNU GPLv3 (http://www.gnu.org/copyleft/gpl.html)
 **************************************************************/

#ifndef ANALYSEK7_H_INCLUDED
#define ANALYSEK7_H_INCLUDED

#include "md5.h"
#include <math.h>
#include <stdio.h>
#include <wx/string.h>

enum typeBloc
{
	bSynchroMO,
	bSynchroTO,
	bInconnu,
	bErreur

class analyseK7
{
private:
	md5_state_t stateDataDC;
	md5_byte_t digestDataDCMOTO[16];
	wxString MD5DataDCMOTO;

	md5_state_t stateDataSync;
	md5_byte_t digestData[16];

	md5_state_t stateFull;
	md5_byte_t digestFull[16];

	wxString MD5;

	FILE *f;
	typeBloc typek7;
	int nbSynchro, nbTotalPerdu, nbExtraNull;
	wxString log, diagnostic;

	void init();
	bool lireBloc(unsigned char tb, typeBloc std);

public:
	analyseK7();
	~analyseK7();

	bool open(wxString filename);
	bool run();
	void close();

	wxString getMD5() { return MD5; }
	wxString getMD5brut() { return MD5Full; }
	wxString getMD5propre() { return MD5Data; }
	wxString getLog() { return log; }
	wxString getDiagnostic() { return diagnostic; }
	int getNbSynchro() { return nbSynchro; }

#endif // ANALYSEK7_H_INCLUDED