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
	bErreur};

class analyseK7
{
private:
	md5_state_t stateDataDC;	md5_byte_t digestDataDC[16];	wxString MD5DataDC;	md5_state_t stateDataDCMO5;	md5_byte_t digestDataDCMO5[16];	wxString MD5DataDCMO5;	md5_state_t stateDataDCMO6;	md5_byte_t digestDataDCMO6[16];	wxString MD5DataDCMO6;	md5_state_t stateDataDCMOTO;
	md5_byte_t digestDataDCMOTO[16];
	wxString MD5DataDCMOTO;

	md5_state_t stateDataSync;	md5_byte_t digestDataSync[16];	wxString MD5DataSync;	md5_state_t stateData;
	md5_byte_t digestData[16];	wxString MD5Data;

	md5_state_t stateFull;
	md5_byte_t digestFull[16];	wxString MD5Full;

	wxString MD5;
	bool analyse;
	FILE *f;
	typeBloc typek7;	bool parasites;
	int nbSynchro, nbTotalPerdu, nbExtraNull;
	wxString log, diagnostic;

	void init();
	bool lireBloc(unsigned char tb, typeBloc std);	void ajoutDataMD5(unsigned char c);

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
	wxString getDiagnostic() { return diagnostic; }	typeBloc getTypeK7() { return typek7; }	bool isParasites() { return parasites; }
	int getNbSynchro() { return nbSynchro; }	int getNbExtraNull() { return nbExtraNull; }	int getNbOctetsPerdus() { return nbTotalPerdu; }};

#endif // ANALYSEK7_H_INCLUDED
