/***************************************************************
 * Author  : OlivierP
 * Date    : 2010-04-22
 * License : GNU GPLv3 (http://www.gnu.org/copyleft/gpl.html)
 **************************************************************/

#include "analysek7.h"

unsigned char SynchroDCMO5[] = {0x44, 0x43, 0x4D, 0x4F, 0x35, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x3C, 0x5A};unsigned char SynchroDCMO6[] = {0x44, 0x43, 0x4D, 0x4F, 0x36, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x3C, 0x5A};unsigned char SynchroDCMOTO[] = {0x44, 0x43, 0x4D, 0x4F, 0x54, 0x4F, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x3C, 0x5A};
unsigned char SynchroMO[]    = {0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x3C, 0x5A};
unsigned char SynchroTO[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x01, 0x3C};

analyseK7::analyseK7()
{
	init();
}

analyseK7::~analyseK7()
{
	close();
}

void analyseK7::init()
{	analyse = false;
	f = NULL;
	typek7 = bInconnu;	parasites = false;	nbSynchro = 0;
	nbTotalPerdu = 0;	nbExtraNull = 0;
	log = wxEmptyString;	diagnostic = wxEmptyString;
	memset(digestDataDC, 0, sizeof(digestDataDC));	memset(digestDataDCMO5, 0, sizeof(digestDataDCMO5));	memset(digestDataDCMO6, 0, sizeof(digestDataDCMO6));	memset(digestDataDCMOTO, 0, sizeof(digestDataDCMOTO));
	memset(digestDataSync, 0, sizeof(digestDataSync));	memset(digestData, 0, sizeof(digestData));
	memset(digestFull, 0, sizeof(digestFull));	MD5DataDC = wxEmptyString;	MD5DataDCMO5 = wxEmptyString;	MD5DataDCMO6 = wxEmptyString;	MD5DataDCMOTO = wxEmptyString;
	MD5DataSync = wxEmptyString;	MD5Data = wxEmptyString;	MD5Full = wxEmptyString;}

bool analyseK7::open(wxString filename)
{
	init();

	md5_init(&stateDataDC);	md5_init(&stateDataDCMO5);	md5_init(&stateDataDCMO6);	md5_init(&stateDataDCMOTO);
	md5_init(&stateDataSync);	md5_init(&stateData);
	md5_init(&stateFull);

	log = filename + wxT("\n\n");
	f = fopen(filename.ToAscii(), "rb");
	return (f != NULL);
}
void analyseK7::ajoutDataMD5(unsigned char c){	md5_append(&stateDataDC, (const md5_byte_t *)&c, 1);	md5_append(&stateDataDCMO5, (const md5_byte_t *)&c, 1);	md5_append(&stateDataDCMO6, (const md5_byte_t *)&c, 1);	md5_append(&stateDataDCMOTO, (const md5_byte_t *)&c, 1);
	md5_append(&stateDataSync, (const md5_byte_t *)&c, 1);	md5_append(&stateData, (const md5_byte_t *)&c, 1);}
void analyseK7::close()
{
	md5_finish(&stateDataDC, digestDataDC);
	md5_finish(&stateDataDCMO5, digestDataDCMO5);
	md5_finish(&stateDataDCMO6, digestDataDCMO6);
	md5_finish(&stateDataDCMOTO, digestDataDCMOTO);
	md5_finish(&stateDataSync, digestDataSync);
	md5_finish(&stateData, digestData);
	md5_finish(&stateFull, digestFull);

	MD5DataDC = wxEmptyString;
	for (int dc = 0; dc < 16; ++dc)
	{
		MD5DataDC += wxString::Format(wxT("%02x"), digestDataDC[dc]);
	}

	MD5DataDCMO5 = wxEmptyString;
	for (int di5 = 0; di5 < 16; ++di5)
	{
		MD5DataDCMO5 += wxString::Format(wxT("%02x"), digestDataDCMO5[di5]);
	}

	MD5DataDCMO6 = wxEmptyString;
	for (int di6 = 0; di6 < 16; ++di6)
	{
		MD5DataDCMO6 += wxString::Format(wxT("%02x"), digestDataDCMO6[di6]);
	}

	MD5DataDCMOTO = wxEmptyString;
	for (int dio = 0; dio < 16; ++dio)
	{
		MD5DataDCMOTO += wxString::Format(wxT("%02x"), digestDataDCMOTO[dio]);
	}

	MD5DataSync = wxEmptyString;
	for (int dis = 0; dis < 16; ++dis)
	{
		MD5DataSync += wxString::Format(wxT("%02x"), digestDataSync[dis]);
	}

	MD5Data = wxEmptyString;
	for (int did = 0; did < 16; ++did)
	{
		MD5Data += wxString::Format(wxT("%02x"), digestData[did]);
	}

	MD5Full = wxEmptyString;
	for (int dif = 0; dif < 16; ++dif)
	{
		MD5Full += wxString::Format(wxT("%02x"), digestFull[dif]);
	}

	MD5 = wxEmptyString;

	if (f != NULL)
	{
		fclose(f);
		f = NULL;
		if (analyse == true)		{			if (getMD5brut().Cmp(getMD5propre()) == 0)
			{				diagnostic = wxT("OK");
				MD5 = getMD5propre();
			}			else if (getMD5brut().Cmp(MD5DataDC) == 0)			{				diagnostic = wxT("OK (DC)");				MD5 = MD5DataDC;
				if ((getTypeK7() == bSynchroMO) || (getTypeK7() == bSynchroTO))					nbTotalPerdu -= getNbSynchro();			}			else if (getMD5brut().Cmp(MD5DataDCMO5) == 0)			{				diagnostic = wxT("OK (DCMO5)");				MD5 = MD5DataDCMO5;
				if ((getTypeK7() == bSynchroMO) || (getTypeK7() == bSynchroTO))					nbTotalPerdu -= 5 * getNbSynchro();			}			else if (getMD5brut().Cmp(MD5DataDCMO6) == 0)			{				diagnostic = wxT("OK (DCMO6)");				MD5 = MD5DataDCMO6;
				if ((getTypeK7() == bSynchroMO) || (getTypeK7() == bSynchroTO))					nbTotalPerdu -= 5 * getNbSynchro();			}			else if (getMD5brut().Cmp(MD5DataDCMOTO) == 0)
			{
				diagnostic = wxT("OK (DCMOTO)");
				MD5 = MD5DataDCMOTO;
				if ((getTypeK7() == bSynchroMO) || (getTypeK7() == bSynchroTO))
					nbTotalPerdu -= 6 * getNbSynchro();
			}
			else if (getMD5brut().Cmp(MD5DataSync) == 0)
			{				diagnostic = wxT("Pb. Synchro.");
				MD5 = MD5DataSync;
			}			else switch (getTypeK7())			{				case bErreur:					diagnostic = wxT("MO et TO ???");					break;				case bInconnu:					diagnostic = wxT("ni MO ni TO ???");					break;				default:					break;			}			if ((diagnostic.IsEmpty() == false) && (nbExtraNull>0) && (nbExtraNull == nbTotalPerdu))				diagnostic += wxString::Format(wxT(" (%d extra)"), nbExtraNull);			if ( (nbTotalPerdu - nbExtraNull > 0) && ((typek7 == bSynchroMO) || (typek7 == bSynchroTO)) )			{				parasites = true;				diagnostic = wxT("Parasites");			}		}		else		{			diagnostic = wxT("Err. checksum");		}	}
}
bool analyseK7::lireBloc(unsigned char tb, typeBloc std)
{
	bool retval = true;
	long chksum = 0;
	unsigned char c = 0;
	unsigned char nom[256] = {""};

	c = tb;
	ajoutDataMD5(c);
	/**************************************
	** traitement de la longueur du bloc **
	**************************************/
	c = fgetc(f);
	ajoutDataMD5(c);	md5_append(&stateFull, (const md5_byte_t *)&c, 1);
	int len = c;
	log += wxString::Format(wxT("Len = %03d    "), len);

	// len TO = données, rien a faire
	if (std == bSynchroMO)
	{
		if (len == 0)
			len = 256;
		// len MO = 1 octet longueur + données + 1 octet checksum
		len -= 2;
	}

	/**************************************
	** lecture des données ****************
	**************************************/
	for (int i=0; i<len; i++)
	{
		c = fgetc(f);
		ajoutDataMD5(c);		md5_append(&stateFull, (const md5_byte_t *)&c, 1);
		chksum += c;

		// lecture du nom du fichier
		if ((tb == 0x00) && (i<11))
		{
			if (i <= 7)  nom[i] = c;
			else         nom[i+1] = c;
			if (i == 7)  nom[i+1] = '.';
			if (i == 10) nom[i+2] = 0;
		}
	}

	/**************************************
	** traitement du checksum *************
	**************************************/
	c = fgetc(f);
	ajoutDataMD5(c);	md5_append(&stateFull, (const md5_byte_t *)&c, 1);
	log += wxString::Format(wxT("Checksum (%02x) "), c);

	if (std == bSynchroMO)
	{
		chksum += c;
		// checksum OK si somme(données + checksum) modulo 256 == 0
		retval = (chksum % 256 == 0);
	}
	else
	{
		chksum += tb;
		chksum += len;
		// checksum OK si somme(octet type bloc + octet longueur + données) modulo 256 == checksum
		retval = (chksum % 256 == c);
	}

	log += (retval == true) ? wxT("OK"):wxT("KO");

	// affichage du nom du fichier
	if (tb == 0x00)
		log += wxT("    ") + wxString::FromAscii((const char *)nom);

	log += wxT("\n");

	return retval;
}

bool analyseK7::run()
{
	bool retval = true;
	if (f != NULL)
	{
		typeBloc tb = bInconnu;
		int nb01 = 0;
		int nbFF = 0;
		unsigned char c = 0, prevc;
		int nbperdu = 0;

		while (!feof(f))
		{
			prevc = c;
			c = fgetc(f);
			if (feof(f))			{				// cas des 0xFF en fin de fichier				for (int nf=0; nf<nbFF; nf++)				{					c = 0xFF;					ajoutDataMD5(c);					nbperdu++;					nbTotalPerdu++;					nbExtraNull++;					log += wxString::Format(wxT("%02x[%c]%c"), c, (c>='0') ? c:' ', (nbperdu % 16 == 0) ? '\n':' ');				}			}			else
				md5_append(&stateFull, (const md5_byte_t *)&c, 1);
			switch (c)
			{
				case 0x00:
					if ((tb == bSynchroMO) || (tb == bSynchroTO))
					{
						log += wxT("ENTETE     ");
						if (lireBloc(c, tb) == false)
							retval = false;
						tb = bInconnu;
					}					else					{	// cas des 0x00 en fin de fichier						ajoutDataMD5(c);						nbperdu++;						nbTotalPerdu++;						nbExtraNull++;						log += wxString::Format(wxT("%02x[%c]%c"), c, (c>='0') ? c:' ', (nbperdu % 16 == 0) ? '\n':' ');					}
					nb01 = 0;
					nbFF = 0;
					break;
				case 0x01:
					if ((tb == bSynchroMO) || (tb == bSynchroTO))
					{
						log += wxT("DONNES     ");
						if (lireBloc(c, tb) == false)
							retval = false;
						tb = bInconnu;
						nb01 = 0;						nbFF = 0;					}
					else					{
						if (prevc == 0x3C)						{							for (int n1=0; n1<nb01; n1++)							{								ajoutDataMD5(c);								nbperdu++;								nbTotalPerdu++;								log += wxString::Format(wxT("%02x[%c]%c"), c, (c>='0') ? c:' ', (nbperdu % 16 == 0) ? '\n':' ');							}							ajoutDataMD5(prevc);							nbperdu++;							nbTotalPerdu++;							log += wxString::Format(wxT("%02x[%c]%c"), prevc, (prevc>='0') ? prevc:' ', (nbperdu % 16 == 0) ? '\n':' ');							nb01 = 0;						}						nb01++;					}
					break;
				case 0xFF:
					if ((tb == bSynchroMO) || (tb == bSynchroTO))
					{
						log += wxT("FIN        ");
						if (lireBloc(c, tb) == false)
							retval = false;
						tb = bInconnu;
						nb01 = 0;						nbFF = 0;					}
					else						nbFF++;					break;
				case 0x5A:
					if ((nb01 >= 2) && (prevc == 0x3C))
					{
						if (nbperdu > 0)
						{
							nbperdu = 0;
							log += wxT("\n");
						}						nbSynchro++;
						tb = bSynchroMO;
						if (typek7 != bErreur)
						{
						    typek7 = (typek7 == bSynchroTO) ? bErreur : tb;
						}
						log += wxT("      Synchro MO        (");						unsigned char dc = 0xdc;						md5_append(&stateDataDC, (const md5_byte_t *)&dc, 1);						if (nb01 == 16)						{							log += wxT("normal)\n");							md5_append(&stateDataSync, (const md5_byte_t *)SynchroMO, sizeof(SynchroMO));							md5_append(&stateDataDC, (const md5_byte_t *)SynchroMO, sizeof(SynchroMO));						}						else						{							unsigned char val = 0x01;
							for (int n=0; n<nb01; n++)							{
								log += wxT("01 ");								md5_append(&stateDataSync, (const md5_byte_t *)&val, 1);								md5_append(&stateDataDC, (const md5_byte_t *)&val, 1);							}
							log += wxT("3c 5a)\n");							val = 0x3C;							md5_append(&stateDataSync, (const md5_byte_t *)&val, 1);							md5_append(&stateDataDC, (const md5_byte_t *)&val, 1);							val = 0x5A;							md5_append(&stateDataSync, (const md5_byte_t *)&val, 1);							md5_append(&stateDataDC, (const md5_byte_t *)&val, 1);						}
						nbFF = 0;						nb01 = 0;
						md5_append(&stateDataDCMO5, (const md5_byte_t *)SynchroDCMO5, sizeof(SynchroDCMO5));						md5_append(&stateDataDCMO6, (const md5_byte_t *)SynchroDCMO6, sizeof(SynchroDCMO6));						md5_append(&stateDataDCMOTO, (const md5_byte_t *)SynchroDCMOTO, sizeof(SynchroDCMOTO));
						md5_append(&stateData, (const md5_byte_t *)SynchroMO, sizeof(SynchroMO));
					}
					break;
				case 0x3C:
					if ((nbFF >= 2) && (prevc == 0x01))
					{
						if (nbperdu > 0)
						{
							nbperdu = 0;
							log += wxT("\n");
						}
						nbSynchro++;						tb = bSynchroTO;
						if (typek7 != bErreur)
						{
						    typek7 = (typek7 == bSynchroMO) ? bErreur : tb;
						}
						log += wxT("      Synchro TO        (");						unsigned char dc = 0xdc;						md5_append(&stateDataDC, (const md5_byte_t *)&dc, 1);						if (nbFF == 10)						{							log += wxT("normal)\n");							md5_append(&stateDataSync, (const md5_byte_t *)SynchroTO, sizeof(SynchroTO));							md5_append(&stateDataDC, (const md5_byte_t *)SynchroTO, sizeof(SynchroTO));						}						else						{
							unsigned char val = 0xFF;							for (int n=0; n<nbFF; n++)							{
								log += wxT("ff ");								md5_append(&stateDataSync, (const md5_byte_t *)&val, 1);								md5_append(&stateDataDC, (const md5_byte_t *)&val, 1);							}
							log += wxT("01 3c)\n");							val = 0x01;							md5_append(&stateDataSync, (const md5_byte_t *)&val, 1);							md5_append(&stateDataDC, (const md5_byte_t *)&val, 1);							val = 0x3C;							md5_append(&stateDataSync, (const md5_byte_t *)&val, 1);							md5_append(&stateDataDC, (const md5_byte_t *)&val, 1);						}
						nbFF = 0;
						nb01 = 0;						md5_append(&stateDataDCMO5, (const md5_byte_t *)SynchroDCMO5, sizeof(SynchroDCMO5));						md5_append(&stateDataDCMO6, (const md5_byte_t *)SynchroDCMO6, sizeof(SynchroDCMO6));						md5_append(&stateDataDCMOTO, (const md5_byte_t *)SynchroDCMOTO, sizeof(SynchroDCMOTO));
						md5_append(&stateData, (const md5_byte_t *)SynchroTO, sizeof(SynchroTO));
					}
					break;
				default:
					nbperdu++;
					nbTotalPerdu++;
					log += wxString::Format(wxT("%02x[%c]%c"), c, (c>='0') ? c:' ', (nbperdu % 16 == 0) ? '\n':' ');
					break;
			}
		}
	}	analyse = retval;	return retval;
}
