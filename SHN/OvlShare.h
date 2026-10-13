#pragma pack(1)

typedef unsigned long uint32;
typedef unsigned short uint16;
typedef short int int16;

#define XLS_FIRST_DATA_ROW	25  // komt ook in DataBaseDlg.cpp voor
#define SERVER_MONO       0
#define SERVER_LIGHT      1
#define SERVER_STANDAARD  2

#define MAX_WERKPOST      40

#define BTWNR_OFFSET 1073741824L
#define DIM_PEPPOLLIJN  300

struct s_ArtSelData {
  char data_begin;
  uint16 tab_read;
  int16 p_max_grp,p_max_lev,slev_used,sgrp_used,sklt_used,klt_st_used,safsp_used;
  int16 fl_afspraak;
	int16 allow_blocked_art,sel_met_stock;
  uint16 prx_klt,inq_klt,inq_merk,dt_p_beg,dt_p_end,dt_s_beg,dt_s_end,inq_filiaal;
  char selp_bf[4][1000],selp_des[40],*selp_fld;
  uint16 selp_use,selp_ge,selp_le;
  struct{
    uint16 rec;
    char select;
  } tb[600];
};
 
struct s_FactuurTotalen {
  uint16 ft_nr;
  uint16 ft_date;
  double alg_tot;
  double belastbt;
  double btw_tot;
  double tot_leeg;
};

struct s_PeppolLijn { 
	char Code[20];
	char Naam[40];
	char FactuurLineNr[5];
	float Aantal;
	float Prijs;
	double Bedrag;
	float BtwPct;
	char BtwId;
	float AfwijkendAantal;
	uint16 GrbRec;
	uint16 ArtRec;
	uint16 Rec11;
} ;

struct s_PeppolHeader { 
	char FactuurNr[15];
	int16 CNflag;
	uint16 Datum;
	uint16 VervalDatum;
	uint16 PdfIncluded;
	char Naam[40];
	char Adres[40];
	char Postcode[10];
	char Gemeente[30];
	char Telefoon[15];
	char Email[50];
	char BTWNummer[20];
	char IBAN[35];
	char BICcode[15];
	uint16 LevRec;
	char KoperReferentie[50];
	char OrderReferentie[50];
	char Mededeling[30];
	char Opmerking[100];
	char PdfFileName[200];
	char PeppolFileName[200];
	float BtwPct[10];
	char  BtwId[10];
	double Belastbaar[10];
	double BTWbedrag[10];
	uint16 GrbRecBtw[10];
	char   InvoiceTypeCode[5];
	int    BewCount;
	double Ft_belastbaar;
	double Ft_btw;
	double Ft_totaal;
	double Ft_Tebetalen;
	int    Detailverwerking;
	int    Selfbilling;
	int    StockVerwerkt;
} ;

#define DIM_MAILMERGEKEYWORDS				19
#ifdef OvlCpp

extern "C" int ServerVersion, StdInMono,WarnForProgramUpdate,DefaultBackGroundColor,AllowMasterFunctions,WerkpostFiliaalNr,CallingOvl,PeppollijstSort;
extern "C" char NextUpdateCheck[],BackupFile2Receive[100];
extern "C" char NaamWerkPost[];
extern "C" struct s_ArtSelData seldata;
extern "C" struct s_FactuurTotalen FactuurTotalen;
extern "C" struct s_PeppolHeader PeppolHeader;
extern "C" struct s_PeppolLijn PeppolLijn[];
extern "C" char BicCodes[];
extern "C" char RamBon[];
extern "C" int RamBonSize;
extern "C" char SelectedFileName[]; // resultaat van GetFileFromSelection()
extern "C" char SearchText[]; // gebruikt in ovl2900
extern "C" int SearchTextSize;
extern "C" char SearchFilterTabel[];
extern "C" int SearchFilterTabelSize;

extern "C" int PrNrs[20];
extern "C" char MailMergeKeywords[DIM_MAILMERGEKEYWORDS][15];
extern "C" char MailMergeData[DIM_MAILMERGEKEYWORDS][100];
extern "C" char MailMergeBodyText[500];
extern "C" char MailMergeSpecialTemplate[10];
extern "C" char MailMergeTaal,MailSaveAdres;
extern "C" unsigned  MailMergeBijlage[10];
extern "C" char MailMergeFileBijlage[10][100]; // echte filename+path hier meegeven
extern "C" int  MailMergeFormaat;
extern "C" char MailUniqueID[20];
extern "C" char BestelFileUsed[2][102];
extern "C" char CodaboxUniqueID[20];
extern "C" char CodaboxRefID[50];
extern "C" char GlobalTextBuffer[150];
extern "C" int SelfBilling,KL_Stu2240;

#else
extern  int ServerVersion, StdInMono, WarnForProgramUpdate,DefaultBackGroundColor,AllowMasterFunctions,WerkpostFiliaalNr,CallingOvl;
extern  char NextUpdateCheck[],BackupFile2Receive[100];
extern  char NaamWerkPost[];
extern  struct s_ArtSelData seldata;
extern  struct s_FactuurTotalen FactuurTotalen;
extern  struct s_PeppolHeader PeppolHeader;
extern  struct s_PeppolLijn PeppolLijn[];
extern  char BicCodes[];
extern  char RamBon[];
extern  int RamBonSize;
extern  char SelectedFileName[]; // resultaat van GetFileFromSelection()
extern  char SearchText[]; // gebruikt in ovl2900
extern  int SearchTextSize;
extern  char SearchFilterTabel[];
extern  int SearchFilterTabelSize;

extern  int PrNrs[20];
extern  char MailMergeKeywords[DIM_MAILMERGEKEYWORDS][15];
extern  char MailMergeData[DIM_MAILMERGEKEYWORDS][100];
extern  char MailMergeBodyText[500];
extern  char MailMergeSpecialTemplate[10];
extern  char MailMergeTaal,MailSaveAdres;
extern  unsigned MailMergeBijlage[10];
extern  char MailMergeFileBijlage[10][100]; // echte filename+path hier meegeven
extern  int  MailMergeFormaat;
extern  char MailUniqueID[20];
extern  char BestelFileUsed[2][102];
extern  char CodaboxUniqueID[20];
extern  char CodaboxRefID[50];
extern  char GlobalTextBuffer[150];
extern  int SelfBilling,KL_Stu2240;
#endif

/*
#ifdef OvlCpp
#define ExternPrefix  
extern "C" {
#else
#define ExternPrefix  extern
#endif

ExternPrefix struct s_ArtSelData seldata;
ExternPrefix char RamBon[];
ExternPrefix int RamBonSize;
ExternPrefix char SearchText[]; // gebruikt in ovl2900
ExternPrefix int SearchTextSize;

ExternPrefix char MailMergeKeywords[DIM_MAILMERGEKEYWORDS][15];
ExternPrefix char MailMergeData[DIM_MAILMERGEKEYWORDS][100];
ExternPrefix int  MailMergeBijlage[10];
ExternPrefix int  MailMergeFormaat;
#ifdef OvlCpp
}
#endif
*/