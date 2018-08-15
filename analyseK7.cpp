/***************************************************************
 * Author  : OlivierP
 * Date    : 2010-04-22
 * License : GNU GPLv3 (http://www.gnu.org/copyleft/gpl.html)
 **************************************************************/

#include "analysek7.h"

unsigned char SynchroDCMO5[] = {0x44, 0x43, 0x4D, 0x4F, 0x35, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x3C, 0x5A};
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
{
	f = NULL;
	typek7 = bInconnu;
	nbTotalPerdu = 0;
	log = wxEmptyString;
	memset(digestDataDC, 0, sizeof(digestDataDC));
	memset(digestDataSync, 0, sizeof(digestDataSync));
	memset(digestFull, 0, sizeof(digestFull));
	MD5DataSync = wxEmptyString;

bool analyseK7::open(wxString filename)
{
	init();

	md5_init(&stateDataDC);
	md5_init(&stateDataSync);
	md5_init(&stateFull);

	log = filename + wxT("\n\n");
	f = fopen(filename.ToAscii(), "rb");
	return (f != NULL);
}

	md5_append(&stateDataSync, (const md5_byte_t *)&c, 1);
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

			{
				MD5 = getMD5propre();
			}
				if ((getTypeK7() == bSynchroMO) || (getTypeK7() == bSynchroTO))
				if ((getTypeK7() == bSynchroMO) || (getTypeK7() == bSynchroTO))
				if ((getTypeK7() == bSynchroMO) || (getTypeK7() == bSynchroTO))
			{
				diagnostic = wxT("OK (DCMOTO)");
				MD5 = MD5DataDCMOTO;
				if ((getTypeK7() == bSynchroMO) || (getTypeK7() == bSynchroTO))
					nbTotalPerdu -= 6 * getNbSynchro();
			}
			else if (getMD5brut().Cmp(MD5DataSync) == 0)
			{
				MD5 = MD5DataSync;
			}
}

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
	ajoutDataMD5(c);
	int len = c;
	log += wxString::Format(wxT("Len = %03d    "), len);

	// len TO = donn�es, rien a faire
	if (std == bSynchroMO)
	{
		if (len == 0)
			len = 256;
		// len MO = 1 octet longueur + donn�es + 1 octet checksum
		len -= 2;
	}

	/**************************************
	** lecture des donn�es ****************
	**************************************/
	for (int i=0; i<len; i++)
	{
		c = fgetc(f);
		ajoutDataMD5(c);
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
	ajoutDataMD5(c);
	log += wxString::Format(wxT("Checksum (%02x) "), c);

	if (std == bSynchroMO)
	{
		chksum += c;
		// checksum OK si somme(donn�es + checksum) modulo 256 == 0
		retval = (chksum % 256 == 0);
	}
	else
	{
		chksum += tb;
		chksum += len;
		// checksum OK si somme(octet type bloc + octet longueur + donn�es) modulo 256 == checksum
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
			if (feof(f))
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
					}
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
						nb01 = 0;
					else
						if (prevc == 0x3C)
					break;
				case 0xFF:
					if ((tb == bSynchroMO) || (tb == bSynchroTO))
					{
						log += wxT("FIN        ");
						if (lireBloc(c, tb) == false)
							retval = false;
						tb = bInconnu;
						nb01 = 0;
					else
				case 0x5A:
					if ((nb01 >= 2) && (prevc == 0x3C))
					{
						if (nbperdu > 0)
						{
							nbperdu = 0;
							log += wxT("\n");
						}
						tb = bSynchroMO;
						if (typek7 != bErreur)
						{
						    typek7 = (typek7 == bSynchroTO) ? bErreur : tb;
						}
						log += wxT("      Synchro MO        (");
							for (int n=0; n<nb01; n++)
								log += wxT("01 ");
							log += wxT("3c 5a)\n");
						nbFF = 0;
						md5_append(&stateDataDCMO5, (const md5_byte_t *)SynchroDCMO5, sizeof(SynchroDCMO5));
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
						nbSynchro++;
						if (typek7 != bErreur)
						{
						    typek7 = (typek7 == bSynchroMO) ? bErreur : tb;
						}
						log += wxT("      Synchro TO        (");
							unsigned char val = 0xFF;
								log += wxT("ff ");
							log += wxT("01 3c)\n");
						nbFF = 0;
						nb01 = 0;
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
	}
}