#pragma pack(1)

__declspec(dllimport) short int errnum;
__declspec(dllimport) short int scrnum;
__declspec(dllimport) short int fldcurs;
__declspec(dllimport) int ExtraSTOSize;

typedef unsigned long uint32;
typedef unsigned short uint16;
typedef short int int16;

#define FOREVER         while(1)
#define YES             1
#define NO              0

#include "OvlShare.h"

int ServerVersion, StdInMono, WarnForProgramUpdate,DefaultBackGroundColor,AllowMasterFunctions,WerkpostFiliaalNr,CallingOvl,PeppollijstSort=2;
char NextUpdateCheck[20],BackupFile2Receive[100];
char NaamWerkPost[21],BicCodes[8000];
char RamBon[1000000];
int RamBonSize=sizeof(RamBon);
char SelectedFileName[100]; // resultaat van GetFileFromSelection(). NIET kleiner maken, want wordt vast gewist op 100 karakters
char SearchText[512]; 
int SearchTextSize=sizeof(SearchText);// gebruikt in ovl2900
char SearchFilterTabel[25000];
int SearchFilterTabelSize=25000;

struct s_ArtSelData seldata;
struct s_FactuurTotalen FactuurTotalen;
struct s_PeppolHeader PeppolHeader;
struct s_PeppolLijn PeppolLijn[DIM_PEPPOLLIJN];

int PrNrs[20]={21,22,23,24,25,26,185,186,187,188,115,116,117,118,119,120,190,191,192,193}; // stunummers verkoopprijzen 10 + 10 op datum

char MailMergeKeywords[DIM_MAILMERGEKEYWORDS][15]={"NAAM","ADRES","POSTCODE","GEMEENTE","CONTACTPERSOON","EMAILADRES",
	"DOCUMENTNUMMER","DOCUMENTNAAM","DATUM","TOTAALBEDRAG","CC_EMAILADRES","PERIODE","KLANTID","FIRMANAAM","FIRMAADRES","FIRMAPOSTCODE","FIRMAGEMEENTE","FIRMATELEFOON","FIRMAEMAIL"};
char MailMergeData[DIM_MAILMERGEKEYWORDS][100];
char MailMergeBodyText[500]; // gebruikt voor keyword TEXTINMAIL
char MailMergeSpecialTemplate[10]; // gebruikt voor keyword TEXTINMAIL
char MailMergeTaal,MailSaveAdres;
unsigned  MailMergeBijlage[10]; // SpoolFileNr hier meegeven
char MailMergeFileBijlage[10][100]; // echte filename+path hier meegeven
int  MailMergeFormaat;
char MailUniqueID[20];
char BestelFileUsed[2][102];
char CodaboxUniqueID[20], CodaboxRefID[50],GlobalTextBuffer[150];
int SelfBilling,KL_Stu2240;
// nieuwe versie van routines die vaak in OVL's gebruikt worden (moet wegvallen OVLxxxx.C)

