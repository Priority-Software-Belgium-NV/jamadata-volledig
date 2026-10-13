// DataBaseDlg.cpp : implementation file
//

#include "stdafx.h"
#include "JMS.h"
#include "DataBaseDlg.h"
#include "JmuDoc.h"
#include "sha1.h"

// CDataBaseDlg dialog

IMPLEMENT_DYNAMIC(CDataBaseDlg, CDialog)

CDataBaseDlg::CDataBaseDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDataBaseDlg::IDD, pParent)
	, m_UpAndRunning(false)
{

}

CDataBaseDlg::~CDataBaseDlg()
{
}

void CDataBaseDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BtnExport, m_btnExport2Fas);
	DDX_Control(pDX, IDC_BtnCheck, m_btnCheck);
	DDX_Control(pDX, IDC_LSTAVAILABLEDB, m_lstDBAvailable);
	DDX_Control(pDX, IDC_LSTMOUNTEDDB, m_lstDBMounted);
	DDX_Control(pDX, IDC_BTNMOUNT, m_btnMount);
	DDX_Control(pDX, IDC_BTNUNMOUNT, m_btnUnMount);
	DDX_Control(pDX, IDC_AUTOZIPTIME, m_cboAutoZipTime);
	DDX_Control(pDX, IDC_BtnDump2Copy, m_btnDump2Copy);
}


BEGIN_MESSAGE_MAP(CDataBaseDlg, CDialog)
	ON_BN_CLICKED(IDC_BtnExport, &CDataBaseDlg::OnBnClickedBtnexport2fas)
	//	ON_WM_SETFOCUS()
	ON_BN_CLICKED(IDC_BTNREFRESH, &CDataBaseDlg::OnBnClickedBtnrefresh)
	ON_WM_SHOWWINDOW()
	ON_BN_CLICKED(IDC_BTNMOUNT, &CDataBaseDlg::OnBnClickedBtnmount)
	ON_BN_CLICKED(IDC_BTNUNMOUNT, &CDataBaseDlg::OnBnClickedBtnunmount)

	//	ON_LBN_SELCHANGE(IDC_LSTAVAILABLEDB, &CDataBaseDlg::OnLbnSelchangeLstavailabledb)
	ON_BN_CLICKED(IDC_BtnCheck, &CDataBaseDlg::OnBnClickedBtncheck)
	ON_LBN_SELCHANGE(IDC_LSTMOUNTEDDB, &CDataBaseDlg::OnLbnSelchangeLstmounteddb)
	ON_LBN_SELCHANGE(IDC_LSTAVAILABLEDB, &CDataBaseDlg::OnLbnSelchangeLstavailabledb)
	ON_CBN_SELCHANGE(IDC_AUTOZIPTIME, &CDataBaseDlg::OnCbnSelchangeAutoziptime)
	ON_BN_CLICKED(IDC_BtnDump2Copy, &CDataBaseDlg::OnBnClickedBtndump2copy)
	ON_WM_TIMER()
END_MESSAGE_MAP()

// CDataBaseDlg message handlers



//*********************
// CLASSIC EDBMNGR CODE
//*********************

// MDBMngr.cpp : Defines the entry point for the console application.
//

// JetCall(35xx is free
// LogAdd(119,0 is free

//** Extensible Storaga Engine Interfact & Parameters 

#undef JET_VERSION
#define JET_VERSION 0x0501

#include "StdAfx.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <esent.h>
#include "Nb30.h"
#include <conio.h>
#include <direct.h>

#include "JMS.h"

#pragma pack(1)

int _jetnr;
int JetCommitBits = 0; // indien nodig en manueel aangezet : JET_bitCommitLazyFlush e.d. ..
int DBLogFileMegaBytes = 5; // * std 5 MB per log-file en 50% daarvan caching in memory
int DBLogCacheMegaBytes = 20; // * std 20 MB caching logfiles, wanneer meer updates dan worden de recs in de FAS bijgewerkt.
int DBMemCacheSizeMegaBytes = 120; // 240 Jaak 12/3/19 : was 240, maar kon bij AST maar 4 dossiers openen, en bij 5-de crasht ie na 5 files owv JET_errOutOfMemory
bool JmsExtendedLogging = false;
CString ServiceInfoMessage;

#define JetCall(_jetnr,func) { \
  _jeterr = (func); \
  if(_jeterr < JET_errSuccess) { \
    LogJet(_jetnr,_jeterr); \
		return false; \
  } \
} \

#define JetCallJmpJetErrorRet(_jetnr,func) { \
  _jeterr = (func); \
  if(_jeterr < JET_errSuccess) { \
    LogJet(_jetnr,_jeterr); \
		goto JetErrorRet; \
  } \
} \

// zo met ThreadInfo
#define JetCallThd(_jetnr,func) { \
  _jeterr = (func); \
  if(_jeterr < JET_errSuccess) { \
    LogJet(_jetnr,_jeterr,ThdRef); \
    DumpBuf2Log(ThdRef); \
		return false; \
  } \
} \

#define JetCallThdJmpJetErrorRet(_jetnr,func) { \
  _jeterr = (func); \
  if(_jeterr < JET_errSuccess) { \
    LogJet(_jetnr,_jeterr,ThdRef); \
    DumpBuf2Log(ThdRef); \
		goto JetErrorRet; \
  } \
} \


// zo met ThreadInfo & RecNr
#define JetCallThdRec(_jetnr,func) { \
  _jeterr = (func); \
  if(_jeterr < JET_errSuccess) { \
    LogJet(_jetnr,_jeterr,ThdRef,RecNr,DB[DBRef].Name,DB[DBRef].Tab[TabIx].StructName); \
    DumpBuf2Log(ThdRef); \
		return false; \
  } \
} \

#define JetCallThdRecJmpJetErrorRet(_jetnr,func) { \
  _jeterr = (func); \
  if(_jeterr < JET_errSuccess) { \
    LogJet(_jetnr,_jeterr,ThdRef,RecNr,DB[DBRef].Name,DB[DBRef].Tab[TabIx].StructName); \
    DumpBuf2Log(ThdRef); \
		goto JetErrorRet; \
  } \
} \

//Ook een VoidRet (Void Return versie gemaakt)
#define JetCallVoidRet(_jetnr,func) { \
  _jeterr = (func); \
  if(_jeterr < JET_errSuccess) { \
    LogJet(_jetnr,_jeterr); \
		return; \
  } \
} \

#define JetCallVoidRetJmpJetErrorRet(_jetnr,func) { \
  _jeterr = (func); \
  if(_jeterr < JET_errSuccess) { \
    LogJet(_jetnr,_jeterr); \
		goto JetErrorRet; \
  } \
} \

//***********************************

#define NO      0
#define YES     1
#define FOREVER while(1)
#define flag    unsigned char

#define MAX_STRUCT      100/* maximum number of structures in a system */
#define MAX_STRUCT_FAS   10/* maximum number of structures in one FAS file */
#define MAX_FIELDS     300/* maximum number of fields in 1 structure */
#define MAX_FLEN        60/* maximum length of a field */
#define MAX_KEYS        15/* maximum number of keys for 1 structure */
#define MAX_KEY_LEN	   255 // wordt bepaald door max. lengte van gewoon binary-column
#define MAX_PARTS       20/* maximum parts for one key */
#define MAX_PRC					5 * MAX_POST 
#define MAX_RECS	10000000 // 10 miljoen records
#define EXTRA_FREE_RECS 10
#define MAX_PROC			 (MAX_POST*5)						// 100 posten met per post 4 voor screens en 1 voor JMH/JMD

#define MAX_XLS			 		50

#define MaxTableNameLen  50
#define MaxColumnNameLen 70
#define MaxDescLen			 20
#define MaxTableCount		 50

#define MAX_SYSPARM_LEN	 100000
#define BUF_LEN 1024 + 8  // is zelfde waarde als in COMNETB.PRC
#define LEN_FSD 16384			// max.# bytes in .fsd file 

#define	DB_MAX	180 // MVG2021 was 350
#define BAK_MAX DB_MAX*5              // gemiddeld max. 5 structs per DB ...
#define TB_MAX	MAX_STRUCT_FAS  // MVG2021  was   +5
#define CL_MAX	5+MAX_KEYS+2					// maximum aantal column in table
#define IX_MAX	MAX_KEYS+2						// maximum aantal indexen in table
#define MAX_SZKEY 100

#define THREAD_NCB_OFFSET  1					// Thread-table 0 t/m NCB_CNT-1 worden voorbehouden voor ComBuf's via Netbios
#define NCB_CNT 30
#define THREAD_MMF_OFFSET 40			    // Thread-table entry voor Shared Memory (5 stuks, 40 t/m 44)
#define MMF_COUNT	500                 // OPGELET : MMF_COUNT = 500 wordt gebruikt voor BATCH-JOBS (Cf. DCM module FWP DataMasters)
#define MAX_THREADS	(THREAD_MMF_OFFSET+MMF_COUNT+1)  // 1 voor Batch -> MMF_COUNT

#define JMS_REQ  10
//JET_INSTANCE instance;
//JET_SESID DB[DBRef].SesId[0];

#define SYS_REQ         5
#define SYS_RPL         5
#define FILENAME        "sys."
#define MAX_LENGTH      500
#define HEADERSTRING    "\xF2Vers"

struct s_Sys Sys[MAX_SYSFILE];

struct s_column
{
	char						Nam[35];
	JET_COLUMNID		Cid[MAX_THREADS];
	JET_COLTYP			Typ;
	int							Len;
};

struct s_index
{
	char						Nam[35];
	char						szKey[MAX_SZKEY];
	char						rgbIndexId[MAX_THREADS][IX_MAX]; // sizeof(JET_API_PTR) + sizeof(unsigned long) + sizeof(unsigned long)];
};

#define FLD_DATE				 0 // Datum
#define FLD_STRING			 1 // String
#define FLD_NUM					 2 // numerisch field !
#define FLD_BTW					 3 // BTW#
#define FLD_REK					 4 // Banknummer
#define FLD_GRB					 5 // Grootboeknummer

#define FLD_EX_2U				 0 // 2 byte unsigned integer
#define FLD_EX_2S				 1 // 2 byte integer
#define FLD_EX_4U				 2 // 4 byte unsigned integer
#define FLD_EX_4S				 3 // 4 byte integer
#define FLD_EX_4F				 4 // 4 byte Float
#define FLD_EX_8F				 5 // 8 byte Double

struct _stu_i {
	unsigned short len;
	unsigned short ref;
	unsigned short rlen;
	unsigned short typ;
	unsigned short recs;
};

struct _key_i {
	unsigned short len;
	unsigned short nr;
	unsigned short typ;
	unsigned short num;
};

struct _pce_i {
	unsigned short typ;
	unsigned short off;
	unsigned short len;
};

struct _fldhdr {
	unsigned short len;
	unsigned short sturef;
	unsigned short elelen;
	unsigned short reclen;
	char desc;
};

struct _namhdr {
	unsigned short len;
	char naam;
};

struct sEleInf {
	char *Name;
	short int  FldType;    // 0:Datum 1:String 2:Numerisch 3:BTW# 4:Bank# 5:GRB
	short int  FldTypeEx;  // Zo numerisch, dan 0:UnsignedShort16 1:ShortInt16 2:UnsignedInt32 3:Int32 4:Float 5:Double
	short int  FldLen;
	short int  FldOffset;
	unsigned char *Desc;
};

struct sKeyInf {
	unsigned short Nr;
	unsigned short Typ;
	unsigned short Len;
	unsigned short pceCnt;
	unsigned short ColIx;
	struct _pce_i  *pce;
};

struct s_FSD {
	char *buf;
	long len;
	bool Updated;
	double DateTimeUpdated;
	// volgende dingen zijn enkel nodig om EXPORT naar FAS te doen, zouden later wegmogen.
	int RecHD;  // aantal header&data recs in FAS
	int RecTot; // aantal totaal recs in FAS
	int FldRecs; // aantal FieldDescriptionRecords
	char *FldHdr1; // pointer naar eerste FieldDescriptor Header
	short int StuMax;
	short int StuNr[MAX_STRUCT_FAS];
} Fsd[DB_MAX];

struct s_Stu {
	short int _Structlen;
	short int _RecNrLen;

} Stu[MAX_STRUCT];

struct s_Tab {
	// Entries used in Stucture info
	char						*StructName;
	short int				StructLen;     // length of structure
	short int				EleCnt;
	struct sEleInf  EleInf[MAX_FIELDS + 1];
	struct _stu_i		*FasStu_i;				 // wordt gebruikt om volgende struct te vinden in deze file ... (fasinfo(x,5)
	short int				FasType;
	// Entries used in DataTables
	int							StuNr;
	char						Nam[35];
	JET_TABLEID			Tid[MAX_THREADS];
	struct s_column	Col[CL_MAX];
	struct s_index  Idx[IX_MAX];  // Eerste index is altijd PRIMARAY
	unsigned				UsedRec;
	unsigned				LastRec;			// Laatst gebruikt recordnummer
	unsigned 				MaxRec;
	double  				DateTimeUpdate; // DateTime last update
	short int				ChangedBy;     // procnr van post die laatste update deed in deze struct
	//unsigned				DeletedRec;   // is dit in gebruik ???
	short int				KeyMax;
	struct sKeyInf  KeyInf[MAX_KEYS + 2];
};

struct s_DB {
	char				 DBRef;
	char				 Name[20];
	char				 NamePath[150]; // MVG2021 was 250
	char				 LogPath[150]; // MVG2021 was 250
	JET_DBID		 Id[MAX_THREADS];
	JET_INSTANCE Instance;
	JET_SESID		 SesId[MAX_THREADS];
	char				 OpenCount;		// totaal van de mount (kan normaal enkel na openen van SYS-file ! Of decrement na sluiten ...)
	bool				 CreatedNew;
	bool				 DisabledRecovery;
	bool				 PreviousTimeNotClosed;
	bool         Updated;
	struct s_FSD Fsd;
	char				 Stu2Tab[MAX_STRUCT];
	char				 TabCnt;
	struct s_Tab Tab[TB_MAX];
} DB[DB_MAX];
bool DBUpdated = false;

CRITICAL_SECTION m_DBTableCs;
CRITICAL_SECTION m_DBOpenCs[DB_MAX];
CRITICAL_SECTION m_DBRecsAddDeleteCs[DB_MAX];

char ProcCurrentState[MAX_PROC];
short int Proc2DBRef[MAX_PROC][MAX_STRUCT];  // deze tabel wordt gebruikt om te zien of er nog iemand actief in een DATA-base zit (nodig ingeval van close van de JMS)
bool Proc2DBRefOpened[MAX_PROC][MAX_STRUCT]; // deze tabel geeft aan of active fasopen(file...) gebeurt is, wordt gereset na sysopen ! Zo niet active open -> indicatie error
short int Proc2ThdRef[MAX_PROC];  // deze tabel wordt gebruikt om te kunnen zien welke proc's (OVL's in het oude systeem) via deze thread komen. met de JMC is er 1 OVL per Thread
short int Proc2SysRef[MAX_PROC];  // deze tabel wordt gebruikt om te zien welke sys-file er open ligt voor de JMC (of de oude OVL). Is nodig voor wanneer men hang-up doet.
HWND PostWnd[MAX_POST];
bool IsPostActive[MAX_POST];

int StuId = 0;								// Template for creation of structure-table
int	  StuRecId = 0;
int		StuValId = 1;
int		StuDatId = 2;
int   StuChgId = 3;
int   StuDelId = 4;
int		StuRecIx = 0;
int   StuDatIx = MAX_KEYS + 1;
int   StuDelIx = MAX_KEYS + 2;
int SysId = 1;			// System strings & values
int	  SysNamId = 0;
int		SysValId = 1;
int		SysDatId = 2;
int		SysNamIx = 0;
int InfId = 2;			// Stored information on tables (for speeding up Mount)
int		InfStnId = 0;
int   InfDatId = 1;
int		InfChgId = 2;
int		InfUsdId = 3;
int		InfLstId = 4;
int   InfMstId = 5;
int		InfStnIx = 0;
int DelId = 3;			// Deleted Tables
int		DelStuId = 0;
int		DelRecId = 1;
int   DelDatId = 2;
int		DelChgId = 3;
int		DelStuRecIx = 0;
int   DelDatIx = 1;

char JATab[256], ICTab[256], SBTab[256], ICSBTab[256];

void SetTab(int DBRef, int TabIx, char* Nam);
void SetCol(int DBRef, int TabIx, int ColIx, char* Nam, JET_COLTYP	Typ, int Len);
void SetKey(int DBRef, int TabIx, int IdxIx, char* Nam, char* KeyStr);
void InitConvertTab();

void InitTab(int DBRef)
{
	SetTab(DBRef, SysId, "System");
	SetCol(DBRef, SysId, SysNamId, "Name", JET_coltypText, 35);
	SetCol(DBRef, SysId, SysValId, "Value", JET_coltypLongBinary, MAX_SYSPARM_LEN);
	SetCol(DBRef, SysId, SysDatId, "DateTimeUpdated", JET_coltypDateTime, 8);
	SetKey(DBRef, SysId, SysNamIx, "ixName", "+Name\0\0");

	SetTab(DBRef, InfId, "Info");
	SetCol(DBRef, InfId, InfStnId, "StuNr", JET_coltypShort, 2);
	SetCol(DBRef, InfId, InfDatId, "DateTimeUpdated", JET_coltypDateTime, 8);
	SetCol(DBRef, InfId, InfChgId, "ChangedBy", JET_coltypShort, 2);
	SetCol(DBRef, InfId, InfUsdId, "Used Records", JET_coltypLong, 4);
	SetCol(DBRef, InfId, InfLstId, "Last Recordnr", JET_coltypLong, 4);
	SetKey(DBRef, InfId, InfStnIx, "ixStuNr", "+StuNr\0\0");

	SetTab(DBRef, DelId, "Deleted");
	SetCol(DBRef, DelId, DelStuId, "StuNr", JET_coltypShort, 2);
	SetCol(DBRef, DelId, DelRecId, "RecNr", JET_coltypLong, 4);
	SetCol(DBRef, DelId, DelDatId, "DateTimeUpdated", JET_coltypDateTime, 8);
	SetCol(DBRef, DelId, DelChgId, "ChangedBy", JET_coltypShort, 2);
	SetKey(DBRef, DelId, DelStuRecIx, "ixStuRecNr", "+StuNr\0+RecNr\0\0");
	SetKey(DBRef, DelId, DelDatIx, "ixDelDatRecNr", "+StuNr\0+DateTimeUpdated\0+RecNr\0\0");

	SetTab(DBRef, StuId, "StrX");
	SetCol(DBRef, StuId, StuRecId, "RecNr", JET_coltypLong, 4);
	SetCol(DBRef, StuId, StuValId, "Value", JET_coltypLongBinary, BUF_LEN);
	SetCol(DBRef, StuId, StuDatId, "DateTimeUpdated", JET_coltypDateTime, 8);
	SetCol(DBRef, StuId, StuChgId, "ChangedBy", JET_coltypShort, 2);
	//SetCol(DBRef, StuId, StuDelId, "DeletedFlag", JET_coltypBit, 1);
	SetKey(DBRef, StuId, StuRecIx, "ixRecNr", "+RecNr\0\0");
	SetKey(DBRef, StuId, StuDatIx, "ixDatRecNr", "+DateTimeUpdated\0+RecNr\0\0");
	//SetKey(DBRef, StuId, StuDelIx, "ixDelRecNr", "+DeletedFlag\0+RecNr\0\0");
}

#define PROGRAMNAME	"JMS"

#pragma pack(1)

unsigned char fm_us20[] = { 7,0xC8,20,0,0,0,0 };
unsigned char fm_udat[] = { 4,0xC0,1,'/' };
unsigned char fm_btw[] = { 2,0xD8 };
unsigned char fm_rek[] = { 2,0xE0 };
unsigned char fm_grb[] = { 2,0xE8 };
unsigned char fm_uf3_3[] = { 6,0xD4,3,3,0x70,0 };

#define YES			 1
#define NO			 0

#define RTO      0/* no time-out may occur */
#define STO    100/* time - out of 50 sec. */
#define MAX_LANANR 255
#define LSN_ADJ 32/* Max. 32 LSN in table -> zie RESET adapter */
#define MAX_ADPTCNT 20

char this_name[16];
int num_name = 0;
int  adpt_cnt;/* aantal adapters found */
int  adpt_nr[MAX_ADPTCNT];/* echte nummers van de adapters */
bool EnableEnhancedFlag = false;

NCB  ncb[NCB_CNT], work_ncb, *p_ncb;
int  ncb_cnt = NCB_CNT;/* maximaal aantal te gebruiken NCB's */
char ncb_used[NCB_CNT], *p_used;

UNALIGNED struct sComBuf {
	short unsigned DestId;
	short unsigned OrigId;
	short unsigned Len;
	unsigned char Function;
	unsigned char Type;
	char Info[BUF_LEN];
};

struct s_Thd {
	bool	Used;
	int 	ReplyLength;
	char	ComBuf[16 + sizeof(struct sComBuf)];  // buffer per thread, bevat de informatie
	CString strCmdInput;
	CString strCmdReply;
} Thd[MAX_THREADS];

void CALLBACK OnListenCompleted(NCB *pncb);
void ComBufExec(int ThdRef);


void LogJet(int jetnr, int jeterr)
{
	char buf[100], errbuf[200];
	sprintf_s(buf, sizeof(buf), "JetCall(%d,...)", jetnr);
	errbuf[0] = 0;
	JetGetSystemParameter(NULL, NULL, JET_paramErrorToString, (JET_API_PTR *)&jeterr, errbuf, sizeof(errbuf));
	LogAdd(1, 0, buf, errbuf);
}

void LogJet(int jetnr, int jeterr, char* DBName, char* TabName)
{
	char buf[150], errbuf[200];
	sprintf_s(buf, sizeof(buf), "JetCall(%d,...) on %s/%s", jetnr, DBName, TabName);
	errbuf[0] = 0;
	JetGetSystemParameter(NULL, NULL, JET_paramErrorToString, (JET_API_PTR *)&jeterr, errbuf, sizeof(errbuf));
	LogAdd(1, 0, buf, errbuf);
}

void LogJet(int jetnr, int jeterr, int ThdRef)
{
	char buf[100], errbuf[200];
	sprintf_s(buf, sizeof(buf), "JetCall(%d,...) from ThdRef=%d ", jetnr, ThdRef);
	errbuf[0] = 0;
	JetGetSystemParameter(NULL, NULL, JET_paramErrorToString, (JET_API_PTR *)&jeterr, errbuf, sizeof(errbuf));
	LogAdd(1, 0, buf, errbuf);
}

void LogJet(int jetnr, int jeterr, int ThdRef, int RecNr, char* DBName, char* TabName)
{
	char buf[150], errbuf[200];
	sprintf_s(buf, sizeof(buf), "JetCall(%d,...) from ThdRef=%d on %s/%s RecNr=%d ", jetnr, ThdRef, DBName, TabName, RecNr);
	errbuf[0] = 0;
	JetGetSystemParameter(NULL, NULL, JET_paramErrorToString, (JET_API_PTR *)&jeterr, errbuf, sizeof(errbuf));
	LogAdd(1, 0, buf, errbuf);
}

void DumpBuf2Log(int ThdRef)
{
	int StuNr;
	UNALIGNED struct sComBuf *ComBuf;

	ComBuf = (struct sComBuf*)Thd[ThdRef].ComBuf;
	StuNr = *(short *)&ComBuf->Info[0];
	int DBRef = -1;
	if (ComBuf->OrigId < MAX_PROC) DBRef = Proc2DBRef[ComBuf->OrigId][StuNr];

	CString cstr, hstr, tothstr;
	for (int j = 0; j < 30; j++) {
		hstr.Format("%02X", (unsigned char)ComBuf->Info[j]);
		tothstr += hstr;
	}
	cstr.Format("%d ThdRef=%d ProcId=%d DBRef=%d ComBuf.Info=[%s]", StuNr, ThdRef, ComBuf->OrigId, DBRef, tothstr);
	LogAdd(0, 2, "StuNr", cstr);
}

void SetFileLastWriteTime(HANDLE hFile, double DateTimeLastWrite)
{
	FILETIME CreationTime, LastAccessTime, LastWriteTime;
	GetFileTime(hFile, &CreationTime, &LastAccessTime, &LastWriteTime);

	if (DateTimeLastWrite == -1000) {
		SetFileTime(hFile, &CreationTime, &LastAccessTime, &CreationTime);
	}
	else {
		COleDateTime dt((DATE)DateTimeLastWrite);
		SYSTEMTIME sysTime;
		dt.GetAsSystemTime(sysTime);
		// Get the timezone info.
		TIME_ZONE_INFORMATION TimeZoneInfo;
		GetTimeZoneInformation(&TimeZoneInfo);
		// Convert local time to UTC.
		SYSTEMTIME GmtTime = { 0 };
		TzSpecificLocalTimeToSystemTime(&TimeZoneInfo,
			&sysTime,
			&GmtTime);
		//FileTime must be in UTC format (therfor convertion)
		SystemTimeToFileTime(&GmtTime, &LastWriteTime);
		SetFileTime(hFile, &CreationTime, &LastAccessTime, &LastWriteTime);
	}
}

void SetFileLastWriteTimeFromDB(HANDLE hFile, int DBRef)
{
	double DBDateTimeUpdated = -1000;
	for (int TabIx = 0; TabIx < DB[DBRef].TabCnt; TabIx++) {
		if (DB[DBRef].Tab[TabIx].StuNr > 0 && DB[DBRef].Tab[TabIx].DateTimeUpdate > DBDateTimeUpdated) DBDateTimeUpdated = DB[DBRef].Tab[TabIx].DateTimeUpdate;
	}
	SetFileLastWriteTime(hFile, DBDateTimeUpdated);
}

//******************************************
// XLSGen -> Lezen en schrijven XLS files
//******************************************

#import "xlsgen.dll" no_function_mapping rename("value", "thevalue")

class xlsgenLoader
{
	typedef xlsgen::IXlsEngine* (*funcStart)();

	HINSTANCE m_hInst;

public:
	funcStart m_funcstart;
	xlsgenLoader(char* path) {

		m_hInst = LoadLibraryA(path);
		if (!m_hInst)
			return;

		m_funcstart = (funcStart)GetProcAddress(m_hInst, "Start");
		if (!m_funcstart) {
			FreeLibrary(m_hInst);
			m_hInst = NULL;
			return;
		}
	}

	~xlsgenLoader() {
		if (m_hInst) {
			FreeLibrary(m_hInst);
			m_hInst = NULL;
		}
	}


	bool IsInitialized() {
		return (m_hInst != NULL);
	}

	xlsgen::IXlsEnginePtr Start() {
		return m_funcstart ? (m_funcstart)() : NULL;
	}
} engine("xlsgen.dll");

//xlsgen::IXlsEnginePtr engine;

#define XLS_FIRST_DATA_ROW	25  // komt ook in OvlShare.h voor

struct sXls {
	bool used;
	bool OpenForRead;
	bool CreatePdfVersion;
	bool SaveAsAttachment;
	bool LegacyFlag; // true voor oude ovl's (XlsWrite function 1 ipv 7)
	int OrigId;
	int TempRefNr;
	short int XlsFirstDataRow;
	int DefStyleIx;
	int MaxStyleIx;
	CString XlsFileName;
	CString TmpXlsFilePath;
	xlsgen::IXlsWorkbookPtr wbk;
	xlsgen::IXlsWorksheetPtr wsht;
	xlsgen::IXlsChartPtr chart;
} Xls[MAX_XLS];

bool InitXls()
{
	// note : the xlsgenLoader class loads xlsgen as a regular dll, and calls 
	//  the Start() entry point
	// XlsGen.dll must not be registered

   // xlsgenLoader engine("xlsgen.dll");
   // if (!engine.IsInitialized()) {
   //   int i=0;
   //   return false;
   // }
	return true;
}

bool ExitXls()
{
	if (engine.IsInitialized()) engine.~xlsgenLoader();
	return true;
}

bool XlsReturn(int ThdRef, int retval, int extlen, char *extra)
{
	UNALIGNED struct sComBuf *ComBuf;
	ComBuf = (struct sComBuf*)Thd[ThdRef].ComBuf;

	ComBuf->Function = 0;
	*(int *)&ComBuf->Info[0] = retval;         // return 6/0;
	if (extlen) {
		*(int *)&ComBuf->Info[4] = extlen;  // lengte van string teruggeven
		memmove(ComBuf->Info + 8, extra, extlen); // data zit op 8
		extlen += 4;
	}
	Thd[ThdRef].ReplyLength = 4 + extlen; // indicate that a reply is ready tot send

	return true;
}

bool XlsReturn(int ThdRef, int retval)
{
	return XlsReturn(ThdRef, retval, 0, 0);
}

// Commando's :
//  1 : XlsCreate (ook 7)
//  2 : XlsClose
//  3 : XlsSaveAsPdf
//  4 : XlsWrite
//  5 : XlsChart
//  6 : XlsGraf
//  7 : XlsCreate
//  8 : XlsSelectWorksheet
//  9 : XlsRowSize
// 10 : XlsColomSize
// 11 : XlsStyle
// 12 : XlsWrite zelfde als 4
// 13 : XlsOpen
// 14 : XlsGetMaxKol
// 15 : XlsGetMaxRij
// 16 : XlsRead zowel voor string, int, double, date



bool ExecXls(int ThdRef)
{
	int i, retcd = 0, XlsRef, StyleIx;
	int rownr, colnr, type, retlen_ = 0;
	char _b100[100], retbuf_[1000];
	BSTR strlabel_;
	unsigned char *p;
	CString cstr, FileName, UniqueFileName, ExtraNummer;
	CTime ct;
	CFile fil;
	short *psi;
	xlsgen::IXlsStylePtr style, def_style;
	xlsgen::IXlsChartDataSourcePtr datasource;
	xlsgen::IXlsWorksheetPtr wsht2;
	xlsgen::IXlsChartPtr chart2;
	UNALIGNED struct sComBuf *ComBuf;
	ComBuf = (struct sComBuf*)Thd[ThdRef].ComBuf;
	int TempRefNr = 1;
	CString TempFilePath, PdfFilePath, ToClientPost;
	CFile TmpNumberFile;
	CString TmpNumberFilePath;
	char* WorkSheetName = "";
	int WorkSheetCount = 0, WorkSheetIndex = 0;
	COLORREF Color = 0;

	psi = (short int*)&ComBuf->Info[0];
	int Cmd = *psi++;
	if (Cmd != 13 && Cmd != 7 && Cmd > 1) {
		XlsRef = *psi++ - 1;
		if (!Xls[XlsRef].used) return XlsReturn(ThdRef, 0);
	}
	switch (Cmd) {

	case 7: // nieuwe vorm, geen automatische ruimte voor grafieken !
	case 1: //  1 : XlsCreate (ook 7)
		for (i = 0; i < MAX_XLS; i++) {
			if (!Xls[i].used) break;
		}
		if (i == MAX_XLS) return XlsReturn(ThdRef, 0);
		XlsRef = i;


		p = (unsigned char *)&ComBuf->Info[2];
		while (*p) {
			*p = JATab[*p];
			if (*p < 128) p++; // speciale letters skippen !
		}

		FileName = &ComBuf->Info[2];
		FileName.Replace("\"", "_");
		FileName.Replace("\\", "_");
		FileName.Replace("//", "_");
		FileName.Replace("%", "_");
		FileName.Replace("&", "_");
		FileName.Replace("@", "_");
		FileName.Replace("#", "_");
		FileName.Replace("$", "_");
		FileName.Replace("*", "_");
		FileName.Replace("\'", "_");
		FileName.Replace("?", "_");
		FileName.Replace(",", "_");
		FileName.Replace(";", "_");
		FileName.Replace(":", "_");

		// Attempt to save the file
		TmpNumberFilePath = PathSpoolFiles + "TempNr.Jam";
		if (GetFileAttributes(TmpNumberFilePath) == INVALID_FILE_ATTRIBUTES) {
			if (TmpNumberFile.Open(TmpNumberFilePath, CFile::modeCreate | CFile::modeWrite, NULL)) {
				TmpNumberFile.Write(&TempRefNr, 4);
				TmpNumberFile.Close();
			}
		}
		SetFileAttributes(TmpNumberFilePath, FILE_ATTRIBUTE_HIDDEN);
		for (int Cnt = 1; Cnt < 500; Cnt++) {
			if (TmpNumberFile.Open(TmpNumberFilePath, CFile::modeReadWrite, NULL)) {
				TmpNumberFile.Read(&TempRefNr, 4);
				if (TempRefNr == 0x7FFFFFFF) TempRefNr = 1;
				else TempRefNr++;
				TmpNumberFile.Seek(0L, CFile::begin);
				TmpNumberFile.Write(&TempRefNr, 4);
				TmpNumberFile.Close();
				break;
			}
			Sleep(50);
		}
		if (TempRefNr) { // switchen naar xlsX als naam zo opgegeven wordt
			if (FileName.Right(5).CompareNoCase(".XLSX") == 0) TempFilePath.Format("%s%08X.xlsX", PathSpoolTemp, TempRefNr);
			else TempFilePath.Format("%s%08X.xls", PathSpoolTemp, TempRefNr);
		}
		try {
			Xls[XlsRef].wbk = engine.m_funcstart()->New((LPCTSTR)TempFilePath);
			Xls[XlsRef].wbk->GetProperties()->GetSummaryProperties()->PutComments("Generated by Jamadata Server\r\nJamadata nv - OVERPELT - Belgium\r\nwww.Jamadata.be\r\n");
			Xls[XlsRef].wsht = Xls[XlsRef].wbk->AddWorksheet(L"JamaData1");
		}
		catch (...)
		{
			LogAdd(19, 0, "Cannot open XLS-file:", TempFilePath);
			return XlsReturn(ThdRef, 0);
		}
		Xls[XlsRef].used = true;
		Xls[XlsRef].OpenForRead = false;
		Xls[XlsRef].CreatePdfVersion = false;
		Xls[XlsRef].SaveAsAttachment = false;
		Xls[XlsRef].XlsFileName.Format("%08X-%03d-$%s", TempRefNr, ComBuf->OrigId, FileName); // dit is de gewenste naam
		Xls[XlsRef].TmpXlsFilePath = TempFilePath;
		Xls[XlsRef].TempRefNr = TempRefNr;
		Xls[XlsRef].OrigId = ComBuf->OrigId;
		Xls[XlsRef].LegacyFlag = false;
		Xls[XlsRef].DefStyleIx = 0;
		Xls[XlsRef].MaxStyleIx = 0;
		if (Cmd == 1) {
			Xls[XlsRef].XlsFirstDataRow = XLS_FIRST_DATA_ROW; // om compatibel te blijven met oud systeem
			Xls[XlsRef].LegacyFlag = true;
		}
		else Xls[XlsRef].XlsFirstDataRow = 0;
		return XlsReturn(ThdRef, XlsRef + 1);
		break;

	case 2: //  2 : XlsClose
		int Action;

		Action = *psi++;

		if (Xls[XlsRef].OpenForRead) {
			Xls[XlsRef].wbk->Close();
			_unlink(Xls[XlsRef].TmpXlsFilePath);
		}
		else {
			if (Xls[XlsRef].chart == NULL) { // chart is not used, delete the unused space above 
				for (int row = 1; row <= Xls[XlsRef].XlsFirstDataRow; row++) {
					Xls[XlsRef].wsht->Rows["1:1"]->Delete();
				}
			}
			Xls[XlsRef].wbk->Close();
			if (Action == 2) Xls[XlsRef].SaveAsAttachment = true;
			bool FileInToClient;
			FileInToClient = false;
			if (Xls[XlsRef].SaveAsAttachment) {
				Xls[XlsRef].XlsFileName = PathSpoolFiles + Xls[XlsRef].XlsFileName;
			}
			else {
				FileInToClient = true;
				ToClientPost.Format("%sPost-%03d\\", PathSpoolToClient, 1 + ComBuf->OrigId / 5);
				if (JMSVersion == 'M') ToClientPost = PathSpool + "Received\\";
				CreateDirectory(ToClientPost, NULL);
				Xls[XlsRef].XlsFileName = ToClientPost + Xls[XlsRef].XlsFileName;
			}
			CopyFile(Xls[XlsRef].TmpXlsFilePath, Xls[XlsRef].XlsFileName, FALSE);
			_unlink(Xls[XlsRef].TmpXlsFilePath);
			if (Xls[XlsRef].CreatePdfVersion) {
				PdfFilePath = Xls[XlsRef].XlsFileName;
				PdfFilePath = PdfFilePath.Left(PdfFilePath.GetLength() - 3) + "pdf";
				Xls[XlsRef].wbk = engine.m_funcstart()->Open((char *)(LPCTSTR)Xls[XlsRef].XlsFileName, "");
				Xls[XlsRef].wbk->WorksheetByIndex[1]->Export->ExportAsPDF((char *)(LPCTSTR)PdfFilePath);
				Xls[XlsRef].wbk->Close();
			}
			if (theApp.JmsTestConfigFlag && !Xls[XlsRef].SaveAsAttachment) {
				::ShellExecute(NULL, "open", Xls[XlsRef].XlsFileName, NULL, NULL, SW_SHOW);
				if (Xls[XlsRef].CreatePdfVersion) {
					::ShellExecute(NULL, "open", PdfFilePath, NULL, NULL, SW_SHOW);
				}
			}
			else if (FileInToClient) {
				if (JMSVersion == 'M') {
					HWND JMD = FindWindow("THE_JMD", NULL);
					if (JMD) PostMessage(JMD, WM_USER + 5, 0, 0); // 0x405, 0, 0); // PROC_RECEIVED_FILES -> de JMD moet deze file verwerken !		
				}
				else {
					int PostNr = 1 + ComBuf->OrigId / 5;
					if (PostWnd[PostNr - 1] == 0) {
						LogAdd(109, 0, "hWnd for JMH not filled in, so Txmit of XLS slow for PostNr=", PostNr);
					}
					else PostMessage(PostWnd[PostNr - 1], WM_USER + 2, 0, 0); // proc_send2peer ...
					if (JmsExtendedLogging) {
						CString cstr;
						cstr.Format("Txfer to Post-%03d = %s", PostNr, PdfFilePath);
						LogAdd(0, 1, cstr);
					}
				}
			}
		}
		if (Xls[XlsRef].chart != NULL) {
			Xls[XlsRef].chart.Release(); Xls[XlsRef].chart = NULL;
		}
		Xls[XlsRef].wsht.Release(); Xls[XlsRef].wsht = NULL;
		Xls[XlsRef].wbk.Release(); Xls[XlsRef].wbk = NULL;
		Xls[XlsRef].used = false;
		return XlsReturn(ThdRef, Xls[XlsRef].TempRefNr);
		break;

	case 3: //  3 : XlsSaveAsPdf
		Xls[XlsRef].CreatePdfVersion = true;
		return XlsReturn(ThdRef, 0);
		break;

	case 4:  // XlsWrite  oude definitie, 5 x int16 & pointer naar 'inhoud'
	case 12: // XlsWrite  nieuwe definitie, 6 x int16 + 4spare int16 & pointer naar 'inhoud'
		rownr = *(unsigned short*)psi++; // rownr=*psi++;
		colnr = *psi++;
		if (Xls[XlsRef].LegacyFlag) {
			rownr++;
			colnr++;
		}
		if (rownr < 1) rownr = 1; // om crashen te voorkomen
		if (colnr < 1) colnr = 1; // idem
		type = *psi++;
		StyleIx = 0;
		if (Cmd == 12) {
			StyleIx = *psi++;
			if (StyleIx > Xls[XlsRef].MaxStyleIx) StyleIx = Xls[XlsRef].MaxStyleIx;
			psi++; // 4 spares !
			psi++;
			psi++;
			psi++;
		}
		if (StyleIx == 0 && Xls[XlsRef].DefStyleIx != 0) StyleIx = Xls[XlsRef].DefStyleIx;

		try {
			if (StyleIx) Xls[XlsRef].wsht->DefaultStyle = StyleIx;
			switch (type) {
			case 0:
				p = (unsigned char *)psi;
				while (*p) {
					*p = JATab[*p];
					p++;
				}
				Xls[XlsRef].wsht->Label[rownr + Xls[XlsRef].XlsFirstDataRow][colnr] = (char *)psi;
				break;
			case 1: Xls[XlsRef].wsht->Number[rownr + Xls[XlsRef].XlsFirstDataRow][colnr] = *(int *)psi; break;
			case 2: Xls[XlsRef].wsht->Float[rownr + Xls[XlsRef].XlsFirstDataRow][colnr] = *(double *)psi; break;
			case 3:
				if (StyleIx == 0) {
					def_style = Xls[XlsRef].wsht->NewStyle();
					style = Xls[XlsRef].wsht->NewStyle();
					style->Format = L"dd/mm/yyyy";
					style->Apply();
				}
				Xls[XlsRef].wsht->Float[rownr + Xls[XlsRef].XlsFirstDataRow][colnr] = (double)(*(unsigned short *)psi) - 2964; // aantal dagen tussen 31/12/1899 en 18/11/1891 (nulpunt JD)
																																			//So ExelDate, midnight, 31 December 1899 is represented by 1.0. 
				def_style->Apply();
				break;
			case 4:
				p = (unsigned char *)psi;
				while (*p) {
					*p = JATab[*p];
					p++;
				}
				Xls[XlsRef].wsht->Formula[rownr + Xls[XlsRef].XlsFirstDataRow][colnr] = (char *)psi; break;
			}
		}
		catch (...) {}
		return XlsReturn(ThdRef, 0);
		break;

	case 5: //  5 : XlsChart
		if (!StdInMono && (JMSVersion == 'M' || JMSVersion == 'L')) return XlsReturn(ThdRef, 5);

		int colcnt, rowcnt, chartType;
		rowcnt = *psi++;
		colcnt = *psi++;
		chartType = *psi++;
		Xls[XlsRef].chart = Xls[XlsRef].wsht->NewChart((xlsgen::enumChartType)chartType, 1, 1, XLS_FIRST_DATA_ROW - 1, 11);
		p = (unsigned char *)psi;
		while (*p) {
			*p = JATab[*p];
			p++;
		}
		Xls[XlsRef].chart->MainTitle->Label = (char *)psi;

		/*
		Xls[XlsRef].chart->MainTitle->Options->X=30;
		Xls[XlsRef].chart->MainTitle->Options->Y=5;
		Xls[XlsRef].chart->MainTitle->Options->Font->Size=5;
		Xls[XlsRef].chart->PlotArea->Options->Height=80;
		Xls[XlsRef].chart->PlotArea->Options->Y=10;
		Xls[XlsRef].chart->PlotArea->Options->Width=80;
		Xls[XlsRef].chart->PlotArea->Options->X=10;

		Xls[XlsRef].chart->Legend->HorizontalOrientation=TRUE;
		Xls[XlsRef].chart->Legend->Show = xlsgen::chartlegend_bottom;
		*/

		datasource = Xls[XlsRef].chart->DataSource;
		datasource->SeriesInRows = FALSE; // seriesdata staan in columns, niet in ROWS
		//datasource->SeriesTitleDepth=1;
		//datasource->DataLabelDepth=1;
		//datasource->PointsPerSeries=rowcnt;
		sprintf(_b100, "JaMaData1!R%dC%d:R%dC%d", XLS_FIRST_DATA_ROW + 1, 1, XLS_FIRST_DATA_ROW + rowcnt + 1, colcnt + 1);
		datasource->Range = _b100;

		/*
		wsht2 = Xls[XlsRef].wbk->AddWorksheet(L"Blad2");
	  chart2 = wsht2->NewChart((xlsgen::enumChartType)chartType,1,1,XLS_FIRST_DATA_ROW-1,11);
		*/


		/*
		Xls[XlsRef].PDFName = Xls[XlsRef].Name;
			 j = Xls[XlsRef].PDFName.MakeUpper().Find(".XLS");
			 Xls[XlsRef].PDFName = Xls[XlsRef].Name.Left(j);
			 Xls[XlsRef].PDFName += "-1.pdf";
			 Xls[XlsRef].wsht->Zoom=60;
			 Xls[XlsRef].wsht->GetExport()->ExportAsPDF((char *)(LPCTSTR)Xls[XlsRef].PDFName);
	   */

		return XlsReturn(ThdRef, 0);
		break;

	case 6: //  6 : XlsGraf
		if (!StdInMono && (JMSVersion == 'M' || JMSVersion == 'L')) return XlsReturn(ThdRef, 5);

		int SeriesIx, Color;
		long *pl;
		SeriesIx = *psi++;
		chartType = *psi++;
		pl = (long *)psi;
		Color = *pl++;

		psi = (short *)pl;
		Xls[XlsRef].chart->SeriesByIndex[SeriesIx]->SeriesType = (xlsgen::enumChartType)chartType;
		return XlsReturn(ThdRef, 0);
		break;

	case 8://  8 : XlsSelectWorksheet
		WorkSheetCount = Xls[XlsRef].wbk->WorksheetCount;
		WorkSheetIndex = *psi++;
		WorkSheetName = (char*)psi;
		if (WorkSheetIndex <= 20) {
			for (int i = WorkSheetCount; i < WorkSheetIndex; i++) {
				char buf[20];
				sprintf_s(buf, 20, "JamaData%d", i);
				Xls[XlsRef].wsht = Xls[XlsRef].wbk->AddWorksheet(buf);
			}
			Xls[XlsRef].wsht = Xls[XlsRef].wbk->WorksheetByIndex[WorkSheetIndex];
			if (*WorkSheetName) Xls[XlsRef].wsht->Name = WorkSheetName;
		}
		return XlsReturn(ThdRef, 0);
		break;
	case 9: //XlsRowSize(int16 ref, int16 rownr, int16 size);   9 : XlsRowSize
		if (psi[0] > 0 && psi[1] > 0) Xls[XlsRef].wsht->RowHeight[psi[0]] = psi[1];
		return XlsReturn(ThdRef, 0);
		break;
	case 10:  // XlsColumsSize(int16 ref, int16 rownr, int16 size);   10 : XlsColomSize
		if (psi[0] > 0 && psi[1] > 0) Xls[XlsRef].wsht->ColWidth[psi[0]] = psi[1];
		return XlsReturn(ThdRef, 0);
		break;
	case 11:  //XlsStyle(int16 ref, char *NumFormat, int16 Size, COLORREF Color, int16 BoldFlag, int16 ItalicFlag, int16 UnderlineFlag, int16 HorAlignment, int16 VerAlignment, COLORREF BackCol, int16 Pattern, int16 Lock, int16 Hide);
		  // 11 : XlsStyle
		if (strcmp("PORTRAIT", (char *)&psi[18]) == 0) { // methode om afdrukstand in portrait te zetten (= XLSstyle(XlsRef,"PORTRAIT",0,0....)
			Xls[XlsRef].wsht->PageSetup->PageOrientation = TRUE;
			return XlsReturn(ThdRef, 1);
			break;
		}

		if (Xls[XlsRef].DefStyleIx == 0) Xls[XlsRef].DefStyleIx = Xls[XlsRef].wsht->GetDefaultStyle();
		style = Xls[XlsRef].wsht->NewStyle();
		style->Font->Size = psi[0];
		memcpy(&Color, &psi[1], 4);
		style->Font->Color = Color;
		style->Font->Bold = psi[3];
		style->Font->Italic = psi[4];
		if (psi[5]) style->Font->Underlined = xlsgen::fontunderline_simple;
		style->Alignment->Horizontal = (xlsgen::enumHorizontalAlignment)psi[6];
		style->Alignment->Vertical = (xlsgen::enumVerticalAlignment)psi[7];
		memcpy(&Color, &psi[8], 4);
		style->Pattern->BackgroundColor = Color;
		style->Pattern->Pattern = (xlsgen::enumPattern)psi[10];
		if (psi[11]) { // Kader
			memcpy(&Color, &psi[12], 4);
			style->Borders->Top->Style = (xlsgen::enumBorderStyle)psi[11];
			style->Borders->Left->Style = (xlsgen::enumBorderStyle)psi[11];
			style->Borders->Bottom->Style = (xlsgen::enumBorderStyle)psi[11];
			style->Borders->Right->Style = (xlsgen::enumBorderStyle)psi[11];
			style->Borders->Top->Color = Color;
			style->Borders->Left->Color = Color;
			style->Borders->Bottom->Color = Color;
			style->Borders->Right->Color = Color;
		}
		style->Locked = psi[14];
		style->Hidden = psi[15];
		// spares (16/17)
		style->Format = (char *)&psi[18];
		style->Apply();
		if (psi[14] || psi[15]) {
			Xls[XlsRef].wsht->LockProperties->Content = true;
		}
		i = Xls[XlsRef].wsht->GetDefaultStyle();
		if (i > Xls[XlsRef].MaxStyleIx) Xls[XlsRef].MaxStyleIx = i;
		return XlsReturn(ThdRef, i);
		break;
		//case 12: XlsWrite : already used higher under 4 !
	case 13: //  13 : XlsOpen 
		for (i = 0; i < MAX_XLS; i++) {
			if (!Xls[i].used) break;
		}
		if (i == MAX_XLS) return XlsReturn(ThdRef, 0);
		XlsRef = i;


		p = (unsigned char *)&ComBuf->Info[2];
		while (*p) {
			*p = JATab[*p];
			if (*p < 128) p++; // speciale letters skippen !
		}

		FileName = &ComBuf->Info[2];
		//FileName.Replace("\"","_");
		//FileName.Replace("\\","_");
		//FileName.Replace("//","_");
		//FileName.Replace("%","_");
		//FileName.Replace("&","_");
		//FileName.Replace("@","_");
		//FileName.Replace("#","_");
		//FileName.Replace("$","_");
		//FileName.Replace("*","_");
		//FileName.Replace("\'","_");
		//FileName.Replace("?","_");
		//FileName.Replace(",","_");
		//FileName.Replace(";","_");
//   FileName.Replace(":","_");

	   // Attempt to save the file
		TmpNumberFilePath = PathSpoolFiles + "TempNr.Jam";
		if (GetFileAttributes(TmpNumberFilePath) == INVALID_FILE_ATTRIBUTES) {
			if (TmpNumberFile.Open(TmpNumberFilePath, CFile::modeCreate | CFile::modeWrite, NULL)) {
				TmpNumberFile.Write(&TempRefNr, 4);
				TmpNumberFile.Close();
			}
		}
		SetFileAttributes(TmpNumberFilePath, FILE_ATTRIBUTE_HIDDEN);
		for (int Cnt = 1; Cnt < 500; Cnt++) {
			if (TmpNumberFile.Open(TmpNumberFilePath, CFile::modeReadWrite, NULL)) {
				TmpNumberFile.Read(&TempRefNr, 4);
				if (TempRefNr == 0x7FFFFFFF) TempRefNr = 1;
				else TempRefNr++;
				TmpNumberFile.Seek(0L, CFile::begin);
				TmpNumberFile.Write(&TempRefNr, 4);
				TmpNumberFile.Close();
				break;
			}
			Sleep(50);
		}
		if (TempRefNr) { // switchen naar xlsX als naam zo opgegeven wordt
			if (FileName.Right(5).CompareNoCase(".XLSX") == 0) TempFilePath.Format("%s%08X.xlsX", PathSpoolTemp, TempRefNr);
			else TempFilePath.Format("%s%08X.xls", PathSpoolTemp, TempRefNr);
		}
		try {
			Xls[XlsRef].wbk = engine.m_funcstart()->Open((LPCTSTR)FileName, (LPCTSTR)TempFilePath);
			//        Xls[XlsRef].wbk->GetProperties()->GetSummaryProperties()->PutComments("Generated by Jamadata Server\r\nJamadata nv - OVERPELT - Belgium\r\nwww.Jamadata.be\r\n");
			//				Xls[XlsRef].wsht= Xls[XlsRef].wbk->AddWorksheet(L"JamaData1");
		}
		catch (...)
		{
			LogAdd(19, 0, "Cannot open XLS-file:", TempFilePath);
			return XlsReturn(ThdRef, 0);
		}
		Xls[XlsRef].used = true;
		Xls[XlsRef].OpenForRead = true;
		Xls[XlsRef].CreatePdfVersion = false;
		Xls[XlsRef].SaveAsAttachment = false;
		Xls[XlsRef].XlsFileName.Format("%08X-%03d-$%s", TempRefNr, ComBuf->OrigId, FileName); // dit is de gewenste naam
		Xls[XlsRef].TmpXlsFilePath = TempFilePath;
		Xls[XlsRef].TempRefNr = TempRefNr;
		Xls[XlsRef].OrigId = ComBuf->OrigId;
		Xls[XlsRef].LegacyFlag = false;
		Xls[XlsRef].DefStyleIx = 0;
		Xls[XlsRef].MaxStyleIx = 0;
		//if (Cmd==1) {
		//  Xls[XlsRef].XlsFirstDataRow=XLS_FIRST_DATA_ROW; // om compatibel te blijven met oud systeem
		//  Xls[XlsRef].LegacyFlag=true;
		//}
		//else 
		Xls[XlsRef].wsht = Xls[XlsRef].wbk->WorksheetByIndex[1]; // eerste worksheet
		Xls[XlsRef].XlsFirstDataRow = 0;
		return XlsReturn(ThdRef, XlsRef + 1);
		break;
	case 14: //  14 : XlsGetMaxKol 
		i = Xls[XlsRef].wsht->Dimensions->LastColumn;
		return XlsReturn(ThdRef, i);
		break;
	case 15: //  15 : XlsGetMaxRij 
		i = Xls[XlsRef].wsht->Dimensions->LastRow;
		return XlsReturn(ThdRef, i);
		break;
	case 16: //  16 : XlsRead

		rownr = *psi++;
		colnr = *psi++;
		if (Xls[XlsRef].LegacyFlag) {
			rownr++;
			colnr++;
		}
		if (rownr < 1) rownr = 1; // om crashen te voorkomen
		if (colnr < 1) colnr = 1; // idem
		type = *psi++;
		StyleIx = 0;
		//if (Cmd==12) {
		//	StyleIx=*psi++;
		//	if (StyleIx>Xls[XlsRef].MaxStyleIx) StyleIx=Xls[XlsRef].MaxStyleIx;
		//	psi++; // 4 spares !
		//	psi++;
		//	psi++;
		//	psi++;
		//}
//			if (StyleIx==0 && Xls[XlsRef].DefStyleIx!=0) StyleIx=Xls[XlsRef].DefStyleIx;

		try {
			//				if (StyleIx) Xls[XlsRef].wsht->DefaultStyle=StyleIx;
			switch (type) {
			case 0:
				p = (unsigned char *)psi;
				//while (*p) {
				   // *p=JATab[*p];
				   // p++;
				//}
				strlabel_ = Xls[XlsRef].wsht->Label[rownr + Xls[XlsRef].XlsFirstDataRow][colnr];
				retlen_ = 0; while (strlabel_[retlen_] && retlen_ < 750) { retbuf_[retlen_] = strlabel_[retlen_]; retlen_++; }
				//				  (char *)*psi=Xls[XlsRef].wsht->Label[rownr+Xls[XlsRef].XlsFirstDataRow][colnr];
				break;
			case 1: *(int *)retbuf_ = Xls[XlsRef].wsht->Number[rownr + Xls[XlsRef].XlsFirstDataRow][colnr]; retlen_ = 4; break;
			case 2: *(double *)retbuf_ = Xls[XlsRef].wsht->Float[rownr + Xls[XlsRef].XlsFirstDataRow][colnr]; retlen_ = 8; break;
			case 3:
				//if (StyleIx==0) {
				//	def_style = Xls[XlsRef].wsht->NewStyle();
				//	style = Xls[XlsRef].wsht->NewStyle();
				//	style->Format = L"dd/mm/yyyy";
				//	style->Apply();
				//}
				*(unsigned short *)retbuf_ = Xls[XlsRef].wsht->Float[rownr + Xls[XlsRef].XlsFirstDataRow][colnr] + 2964; retlen_ = 2;// aantal dagen tussen 31/12/1899 en 18/11/1891 (nulpunt JD)
																																			//So ExelDate, midnight, 31 December 1899 is represented by 1.0. 
//					  def_style->Apply();
				break;
				//case 4: 
		   //   p = (unsigned char *)psi;
				   // while (*p) {
					  //  *p=JATab[*p];
					  //  p++;
				   // }
				   // Xls[XlsRef].wsht->Formula[rownr+Xls[XlsRef].XlsFirstDataRow][colnr]=(char *)psi; break;
			}
		}
		catch (...) {}
		return XlsReturn(ThdRef, 0, retlen_, retbuf_);
		break;
	}

	LogAdd(18, 0, "ExecXls received with command", Cmd);
	return XlsReturn(ThdRef, 0); // om blokkage tegen te gaan, zou normaal niet mogen voorkomen.
}



/*
  // create a new Excel file, and retrieve a workbook to work with

	wbk = engine->New( L"c:\\myfile.xls" );

  // create a new worksheet
  wsht = wbk->AddWorksheet( L"Verkopen" );

  // your code begins here
  // ...
	wsht->Label[1][2]="Januari";

  // commit all work, and make sure the .xls file is ready to use
	wbk->Close();

	wsht=NULL;
	wbk=NULL;


}
*/


//******************************************
// Lezen / schrijven records 
//******************************************

void InitConvertTab()  // zit ook in OVL's !
{
	int i;

	for (i = 0; i < 256; i++) {
		JATab[i] = ICTab[i] = ICSBTab[i] = SBTab[i] = i;
	}
	JATab[128] = SBTab[128] = 'a'; ICTab[128] = ICSBTab[128] = 'A';
	JATab[129] = SBTab[129] = 'a'; ICTab[129] = ICSBTab[129] = 'A';
	JATab[130] = SBTab[130] = 'a'; ICTab[130] = ICSBTab[130] = 'A';
	JATab[131] = SBTab[131] = 'a'; ICTab[131] = ICSBTab[131] = 'A';
	JATab[132] = SBTab[132] = 'c'; ICTab[132] = ICSBTab[132] = 'C';
	JATab[133] = SBTab[133] = 'e'; ICTab[133] = ICSBTab[133] = 'E';
	JATab[134] = SBTab[134] = 'e'; ICTab[134] = ICSBTab[134] = 'E';
	JATab[135] = SBTab[135] = 'e'; ICTab[135] = ICSBTab[135] = 'E';
	JATab[136] = SBTab[136] = 'e'; ICTab[136] = ICSBTab[136] = 'E';
	JATab[137] = SBTab[137] = 'i'; ICTab[137] = ICSBTab[137] = 'I';
	JATab[138] = SBTab[138] = 'i'; ICTab[138] = ICSBTab[138] = 'I';
	JATab[139] = SBTab[139] = 'i'; ICTab[139] = ICSBTab[139] = 'I';
	JATab[140] = SBTab[140] = 'i'; ICTab[140] = ICSBTab[140] = 'I';
	JATab[141] = SBTab[141] = 'o'; ICTab[141] = ICSBTab[141] = 'O';
	JATab[142] = SBTab[142] = 'o'; ICTab[142] = ICSBTab[142] = 'O';
	JATab[143] = SBTab[143] = 'o'; ICTab[143] = ICSBTab[143] = 'O';
	JATab[144] = SBTab[144] = 'o'; ICTab[144] = ICSBTab[144] = 'O';
	JATab[145] = SBTab[145] = 'u'; ICTab[145] = ICSBTab[145] = 'U';
	JATab[146] = SBTab[146] = 'u'; ICTab[146] = ICSBTab[146] = 'U';
	JATab[147] = SBTab[147] = 'u'; ICTab[147] = ICSBTab[147] = 'U';
	JATab[148] = SBTab[148] = 'u'; ICTab[148] = ICSBTab[148] = 'U';
	JATab[149] = SBTab[149] = 'u'; ICTab[149] = ICSBTab[149] = 'U';
	SBTab[159] = 'e'; JATab[159] = ICTab[159] = ICSBTab[159] = 'E'; // euro teken

	for (i = 'a'; i <= 'z'; i++) {
		ICTab[i] = ICSBTab[i] = i - 'a' + 'A';
	}

	for (i = ' '; i < '0'; i++) ICSBTab[i] = 0;
	for (i = '9' + 1; i < 'A'; i++) ICSBTab[i] = 0;
	for (i = 'Z' + 1; i < 'a'; i++) ICSBTab[i] = 0;
	for (i = 'z' + 1; i < 128; i++) ICSBTab[i] = 0;
	for (i = 150; i < 255; i++) ICSBTab[i] = 0;
}

bool SysParmGet(int DBRef, char *nam, char *val, int *plen)
{
	int buflen;
	unsigned long retlen;
	JET_ERR _jeterr;

	buflen = *plen;
	*val = 0; *plen = 0;
	JetCall(201, JetSetCurrentIndex4(DB[DBRef].SesId[0], DB[DBRef].Tab[SysId].Tid[0], NULL, (JET_INDEXID*)DB[DBRef].Tab[SysId].Idx[SysNamIx].rgbIndexId[0], 0, 0));
	JetCall(202, JetMakeKey(DB[DBRef].SesId[0], DB[DBRef].Tab[SysId].Tid[0], nam, strlen(nam), JET_bitNewKey));
	_jeterr = JetSeek(DB[DBRef].SesId[0], DB[DBRef].Tab[SysId].Tid[0], JET_bitSeekEQ);

	if (_jeterr != JET_errSuccess) return false;

	JetCall(203, JetRetrieveColumn(DB[DBRef].SesId[0], DB[DBRef].Tab[SysId].Tid[0], DB[DBRef].Tab[SysId].Col[SysValId].Cid[0], val, buflen, &retlen, 0, 0));
	// val[retlen]=0; mag niet want wist de byte erna, is ook niet nodig 
	*plen = retlen;

	return true;
}

bool SysParmAdd(int DBRef, char *nam, char *val, int vallen)
{
	bool NewRecord;
	JET_ERR _jeterr;

	JetCall(1, JetSetCurrentIndex4(DB[DBRef].SesId[0], DB[DBRef].Tab[SysId].Tid[0], "", (JET_INDEXID*)DB[DBRef].Tab[SysId].Idx[SysNamIx].rgbIndexId[0], 0, 0));
	JetCall(2, JetMakeKey(DB[DBRef].SesId[0], DB[DBRef].Tab[SysId].Tid[0], nam, strlen(nam), JET_bitNewKey));
	_jeterr = JetSeek(DB[DBRef].SesId[0], DB[DBRef].Tab[SysId].Tid[0], JET_bitSeekEQ);

	NewRecord = false;
	if (_jeterr == JET_errRecordNotFound) NewRecord = true;

	JetCall(3, JetBeginTransaction(DB[DBRef].SesId[0]))

		if (NewRecord) {
			JetCall(4, JetPrepareUpdate(DB[DBRef].SesId[0], DB[DBRef].Tab[SysId].Tid[0], JET_prepInsert));
		}
		else {
			JetCall(5, JetPrepareUpdate(DB[DBRef].SesId[0], DB[DBRef].Tab[SysId].Tid[0], JET_prepReplace));
		}

	if (NewRecord) {
		JetCall(6, JetSetColumn(DB[DBRef].SesId[0], DB[DBRef].Tab[SysId].Tid[0], DB[DBRef].Tab[SysId].Col[SysNamId].Cid[0], nam, strlen(nam), 0, NULL));
	}
	JetCall(7, JetSetColumn(DB[DBRef].SesId[0], DB[DBRef].Tab[SysId].Tid[0], DB[DBRef].Tab[SysId].Col[SysValId].Cid[0], val, vallen, JET_bitSetOverwriteLV, NULL));

	double now = COleDateTime::GetCurrentTime().operator double();
	JetCall(8, JetSetColumn(DB[DBRef].SesId[0], DB[DBRef].Tab[SysId].Tid[0], DB[DBRef].Tab[SysId].Col[SysDatId].Cid[0], &now, DB[DBRef].Tab[SysId].Col[SysDatId].Len, 0, NULL));

	JetCall(9, JetUpdate(DB[DBRef].SesId[0], DB[DBRef].Tab[SysId].Tid[0], NULL, 0, NULL));
	JetCall(10, JetCommitTransaction(DB[DBRef].SesId[0], JetCommitBits));

	return true;
}

bool WriteStatsToDB(int DBRef)
{
	bool NewRecord;
	unsigned short TabNr;
	int StuNr;
	JET_ERR _jeterr;

	for (TabNr = 1; TabNr < DB[DBRef].TabCnt; TabNr++) {
		StuNr = DB[DBRef].Tab[TabNr].StuNr;
		if (StuNr == 0) continue;

		JetCall(2501, JetSetCurrentIndex4(DB[DBRef].SesId[0], DB[DBRef].Tab[InfId].Tid[0], "", (JET_INDEXID*)DB[DBRef].Tab[InfId].Idx[InfStnIx].rgbIndexId[0], 0, 0));
		JetCall(2502, JetMakeKey(DB[DBRef].SesId[0], DB[DBRef].Tab[InfId].Tid[0], &TabNr, DB[DBRef].Tab[InfId].Col[InfStnId].Len, JET_bitNewKey));
		_jeterr = JetSeek(DB[DBRef].SesId[0], DB[DBRef].Tab[InfId].Tid[0], JET_bitSeekEQ);

		NewRecord = false;
		if (_jeterr == JET_errRecordNotFound) NewRecord = true;

		JetCall(2503, JetBeginTransaction(DB[DBRef].SesId[0]))

			if (NewRecord) {
				JetCall(2504, JetPrepareUpdate(DB[DBRef].SesId[0], DB[DBRef].Tab[InfId].Tid[0], JET_prepInsert));
			}
			else {
				JetCall(2505, JetPrepareUpdate(DB[DBRef].SesId[0], DB[DBRef].Tab[InfId].Tid[0], JET_prepReplace));
			}

		if (NewRecord) {
			JetCall(2506, JetSetColumn(DB[DBRef].SesId[0], DB[DBRef].Tab[InfId].Tid[0], DB[DBRef].Tab[InfId].Col[InfStnId].Cid[0], &TabNr, DB[DBRef].Tab[InfId].Col[InfStnId].Len, 0, NULL));
		}
		JetCall(2507, JetSetColumn(DB[DBRef].SesId[0], DB[DBRef].Tab[InfId].Tid[0], DB[DBRef].Tab[InfId].Col[InfDatId].Cid[0], &DB[DBRef].Tab[TabNr].DateTimeUpdate, DB[DBRef].Tab[InfId].Col[InfDatId].Len, JET_bitSetOverwriteLV, NULL));
		JetCall(2508, JetSetColumn(DB[DBRef].SesId[0], DB[DBRef].Tab[InfId].Tid[0], DB[DBRef].Tab[InfId].Col[InfChgId].Cid[0], &DB[DBRef].Tab[TabNr].ChangedBy, DB[DBRef].Tab[InfId].Col[InfChgId].Len, JET_bitSetOverwriteLV, NULL));
		JetCall(2509, JetSetColumn(DB[DBRef].SesId[0], DB[DBRef].Tab[InfId].Tid[0], DB[DBRef].Tab[InfId].Col[InfUsdId].Cid[0], &DB[DBRef].Tab[TabNr].UsedRec, DB[DBRef].Tab[InfId].Col[InfUsdId].Len, JET_bitSetOverwriteLV, NULL));
		JetCall(2511, JetSetColumn(DB[DBRef].SesId[0], DB[DBRef].Tab[InfId].Tid[0], DB[DBRef].Tab[InfId].Col[InfLstId].Cid[0], &DB[DBRef].Tab[TabNr].LastRec, DB[DBRef].Tab[InfId].Col[InfLstId].Len, JET_bitSetOverwriteLV, NULL));

		JetCall(2509, JetUpdate(DB[DBRef].SesId[0], DB[DBRef].Tab[InfId].Tid[0], NULL, 0, NULL));
		JetCall(2510, JetCommitTransaction(DB[DBRef].SesId[0], JetCommitBits));
		COleDateTime dt = COleDateTime(DB[DBRef].Tab[TabNr].DateTimeUpdate);
		CString ctime;
		ctime.Format("%02d/%02d/%04d-%02d:%02d:%02d", dt.GetDay(), dt.GetMonth(), dt.GetYear(), dt.GetHour(), dt.GetMinute(), dt.GetSecond());
		CString cstr;
		cstr.Format("%d UsedRecs=%d LastRec=%d ChgdByProcId=%d ChgdAt=%s", StuNr, DB[DBRef].Tab[TabNr].UsedRec, DB[DBRef].Tab[TabNr].LastRec, DB[DBRef].Tab[TabNr].ChangedBy, ctime);
		LogAdd(0, 2, "StuNr", cstr);
	}

	return true;
}

bool ReadStatsFromDB(int DBRef)
{
	unsigned short TabNr;
	unsigned long retlen;
	JET_ERR _jeterr;

	for (TabNr = 1; TabNr < DB[DBRef].TabCnt; TabNr++) {
		if (DB[DBRef].Tab[TabNr].StuNr == 0) continue;

		JetCall(2601, JetSetCurrentIndex4(DB[DBRef].SesId[0], DB[DBRef].Tab[InfId].Tid[0], NULL, (JET_INDEXID*)DB[DBRef].Tab[InfId].Idx[InfStnIx].rgbIndexId[0], 0, 0));
		JetCall(2602, JetMakeKey(DB[DBRef].SesId[0], DB[DBRef].Tab[InfId].Tid[0], &TabNr, DB[DBRef].Tab[InfId].Col[InfStnId].Len, JET_bitNewKey));
		_jeterr = JetSeek(DB[DBRef].SesId[0], DB[DBRef].Tab[InfId].Tid[0], JET_bitSeekEQ);

		if (_jeterr != JET_errSuccess) continue; // veronderstel 0 dus 

		JetCall(2603, JetRetrieveColumn(DB[DBRef].SesId[0], DB[DBRef].Tab[InfId].Tid[0], DB[DBRef].Tab[InfId].Col[InfDatId].Cid[0], &DB[DBRef].Tab[TabNr].DateTimeUpdate, DB[DBRef].Tab[InfId].Col[InfDatId].Len, &retlen, 0, 0));
		JetCall(2604, JetRetrieveColumn(DB[DBRef].SesId[0], DB[DBRef].Tab[InfId].Tid[0], DB[DBRef].Tab[InfId].Col[InfChgId].Cid[0], &DB[DBRef].Tab[TabNr].ChangedBy, DB[DBRef].Tab[InfId].Col[InfChgId].Len, &retlen, 0, 0));
		JetCall(2605, JetRetrieveColumn(DB[DBRef].SesId[0], DB[DBRef].Tab[InfId].Tid[0], DB[DBRef].Tab[InfId].Col[InfUsdId].Cid[0], &DB[DBRef].Tab[TabNr].UsedRec, DB[DBRef].Tab[InfId].Col[InfUsdId].Len, &retlen, 0, 0));
		JetCall(2606, JetRetrieveColumn(DB[DBRef].SesId[0], DB[DBRef].Tab[InfId].Tid[0], DB[DBRef].Tab[InfId].Col[InfLstId].Cid[0], &DB[DBRef].Tab[TabNr].LastRec, DB[DBRef].Tab[InfId].Col[InfLstId].Len, &retlen, 0, 0));
	}
	return true;
}


bool SysParmGetNr(int DBRef, int nr, char *nam, int *pnamlen, char *val, int *plen)
{
	int buflen;
	unsigned long retlen;
	int i;
	JET_ERR _jeterr;

	JetCall(101, JetSetCurrentIndex4(DB[DBRef].SesId[0], DB[DBRef].Tab[SysId].Tid[0], NULL, (JET_INDEXID*)DB[DBRef].Tab[SysId].Idx[SysNamIx].rgbIndexId[0], 0, 0));
	JetCall(102, JetMove(DB[DBRef].SesId[0], DB[DBRef].Tab[SysId].Tid[0], JET_MoveFirst, 0));
	for (i = 0; i < nr; i++) {
		_jeterr = JetMove(DB[DBRef].SesId[0], DB[DBRef].Tab[SysId].Tid[0], JET_MoveNext, 0);
		if (_jeterr != JET_errSuccess) return false;
	}
	buflen = *pnamlen;
	*nam = 0; *pnamlen = 0;
	JetCall(103, JetRetrieveColumn(DB[DBRef].SesId[0], DB[DBRef].Tab[SysId].Tid[0], DB[DBRef].Tab[SysId].Col[SysNamId].Cid[0], nam, buflen, &retlen, 0, 0));
	nam[retlen] = 0;
	*pnamlen = retlen;
	buflen = *plen;
	*val = 0; *plen = 0;
	JetCall(104, JetRetrieveColumn(DB[DBRef].SesId[0], DB[DBRef].Tab[SysId].Tid[0], DB[DBRef].Tab[SysId].Col[SysValId].Cid[0], val, buflen, &retlen, 0, 0));
	val[retlen] = 0;
	*plen = retlen;

	return true;
}

//******************************************
// ESE-Utilities
//******************************************

bool ExecESEntUtl(int DBRef, int CmdType)
{
	LogAdd(87, 0, "DB in 'DirtyShutdown', trying EseNtUtl on", DB[DBRef].Name);

	STARTUPINFO si;
	SECURITY_ATTRIBUTES sa;
	CString ESECmd;
	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof STARTUPINFO;
	sa.nLength = sizeof(SECURITY_ATTRIBUTES);
	sa.lpSecurityDescriptor = NULL;
	sa.bInheritHandle = TRUE;
	HANDLE hFile = CreateFile("esecmd.log", GENERIC_READ | GENERIC_WRITE, 0, &sa, CREATE_ALWAYS, 0, 0);
	if (hFile != INVALID_HANDLE_VALUE) {
		si.dwFlags = STARTF_USESTDHANDLES;
		si.hStdInput = GetStdHandle(STD_INPUT_HANDLE);
		si.hStdOutput = hFile;
		si.hStdError = hFile;
	}

	if (CmdType == 1) {
		PROCESS_INFORMATION pi;
		BOOL res;

		ESECmd.Format("EseNtUtl.EXE /r EDB /d %s /l %s /s %s", DB[DBRef].NamePath, DB[DBRef].LogPath, DB[DBRef].LogPath);
		res = CreateProcess(NULL, (char*)(LPCTSTR)ESECmd, NULL, NULL, TRUE, NORMAL_PRIORITY_CLASS, NULL, NULL, &si, &pi);
		if (TRUE == res) {
			WaitForSingleObject(pi.hProcess, (120 * 1000));
			CloseHandle(pi.hProcess);
			CloseHandle(pi.hThread);
		}

		ESECmd.Format("EseNtUtl.EXE /p %s /o", DB[DBRef].NamePath);
		res = CreateProcess(NULL, (char*)(LPCTSTR)ESECmd, NULL, NULL, TRUE, NORMAL_PRIORITY_CLASS, NULL, NULL, &si, &pi);
		if (TRUE == res) {
			WaitForSingleObject(pi.hProcess, (60 * 1000));
			CloseHandle(pi.hProcess);
			CloseHandle(pi.hThread);
		}
	}
	if (hFile != INVALID_HANDLE_VALUE) {
		CloseHandle(hFile);
		LogAddFile("esecmd.log");
	}
	LogAdd(0, 0, "EseNtUtl ended for", DB[DBRef].Name);

	return true;
}

//******************************************
// EDB-functions
//******************************************

bool EDBCheckAndUpdateAndInit(int DBRef);
bool CheckAndUpdateTable(int DBRef, int idt);
int FindDB(char* cDBName);
int SysOpen(char *ext, bool StdDossierFlag = false, bool PeekMode = false);

#define JET_paramEnableFileCache  126
#define JET_paramEnableViewCache  127


bool EDBInitEngine() // parameters for All Database (EDB-Engine)
{
	JET_ERR _jeterr;
	/*
	JET_paramCacheSize
	JET_paramCacheSizeMin
	JET_paramCacheSizeMax
	JET_paramCheckpointDepthMax
	JET_paramCheckpointIOMax
	JET_paramEnableViewCache
	JET_paramStartFlushThreshold
	JET_paramStopFlushThreshold
	*/
	JetCall(301, JetSetSystemParameter(NULL, JET_sesidNil, JET_paramMaxInstances, DB_MAX, NULL));
	JetCall(305, JetSetSystemParameter(NULL, JET_sesidNil, JET_paramDatabasePageSize, 8192, NULL));
	JetSetSystemParameter(NULL, JET_sesidNil, JET_paramEnableFileCache, true, NULL);
	// JetSetSystemParameter(NULL, JET_sesidNil, JET_paramEnableViewCache, true, NULL); geeft problemen :
	/*  Bij DKR ... met bovenstaande lijn
	19/05/11 20:06:45 #0000   Mounted DataBase = HIS.FAS.RES
	19/05/11 20:06:45 #0000   StuNr=16 COP P4 L140 F4
	19/05/11 20:07:52 #0000     DB=HIS.FAS StuNr=16 RecNr=#309331 Data=[9B040000DEA5000000000000000000000000000000000000000064020000]
	19/05/11 20:07:52 #0001 *** ERROR : JetCall(1613,...) = JET_errOutOfMemory, Out of Memory
	19/05/11 20:08:07 #0000   Decreased OpenCount Database = HIS.FAS (count is now=0)
	19/05/11 20:08:07 #0000     StuNr = 16 UsedRecs=0 LastRec=0 ChgdByProcId=0 ChgdAt=19/05/2011-20:06:45
	19/05/11 20:08:08 #0001 *** ERROR : JetCall(1603,...) = JET_errSessionSharingViolation, Multiple threads are using the same session
	*/
	JetSetSystemParameter(NULL, JET_sesidNil, JET_paramCacheSizeMin, (DBMemCacheSizeMegaBytes * 1024 * 1024) / 8192, NULL); // 30.000 x 8.192 = 240 MB caching
	//JetSetSystemParameter(NULL, JET_sesidNil, JET_paramCacheSize, 0, NULL);  // automatic 
	//JetSetSystemParameter(NULL, JET_sesidNil, JET_paramCacheSizeMax, 0x7FFFFFFF, NULL); // om zeker te zijn op oude ESENT ...
	JetCall(307, JetSetSystemParameter(NULL, JET_sesidNil, JET_paramOutstandingIOMax, 1024, NULL));
	JetCall(310, JetSetSystemParameter(NULL, JET_sesidNil, JET_paramDbExtensionSize, 512, NULL)); // groeit met 512 x 8192 bytes = 5 MB
	JetCall(311, JetSetSystemParameter(NULL, JET_sesidNil, JET_paramPageHintCacheSize, 5000000, NULL)); // 5 MB 

	return true;
}

bool EDBOpenDatabase(int ThdRef, int DBRef, bool CreateWhenNotFound, bool DisableRecovery)
{
	JET_ERR _jeterr;
	bool RepairDoneFlag = false;
retry:;
	if (ThdRef == 0) {
		// Initialize a INSTANCE for each database
		char InstName[20];
		sprintf_s(InstName, sizeof(InstName), "Inst-%s", DB[DBRef].Name);
		CString DBNamePath = PathDB + DB[DBRef].Name;
		sprintf_s(DB[DBRef].NamePath, sizeof(DB[0].NamePath), "%s", (char *)(LPCTSTR)DBNamePath);

		WIN32_FIND_DATA DBFileData;
		HANDLE DBFileHandle = FindFirstFile(DB[DBRef].NamePath, &DBFileData);
		FindClose(DBFileHandle);
		if (!CreateWhenNotFound && DBFileHandle == INVALID_HANDLE_VALUE) {
			LogAdd(0, 0, "Database not found", DB[DBRef].NamePath);
			return false;
		}

		CString LogPath = PathDBLog + DB[DBRef].Name + ".log\\";
		_mkdir(LogPath);

		// check 'OpenFileFlag' in LOG-dir
		CString cstr = LogPath + "OpenFile.flg";
#ifndef JMSVIEWER
		if (GetFileAttributes(cstr) != INVALID_FILE_ATTRIBUTES) {
			DB[DBRef].PreviousTimeNotClosed = true;
			LogAdd(0, 1, "Previous session was not closed cleanly");
		}
#endif
		sprintf_s(DB[DBRef].LogPath, sizeof(DB[0].LogPath), "%s", (char *)(LPCTSTR)LogPath);

		JetCall(402, JetCreateInstance(&DB[DBRef].Instance, InstName));
		// Setting JET_paramCircularLog to 1 means ESENT will automatically
		// delete unneeded logfiles. JetInit will inspect the logfiles to see if the last
		// shutdown was clean. If it wasn't (e.g. the application crashed) recovery will be
		// run automatically bringing the database to a consistent state.

		// Set Parameters for this Instance
#ifndef JMSVIEWER
		JetCall(413, JetSetSystemParameter(&DB[DBRef].Instance, JET_sesidNil, JET_paramCircularLog, 1, NULL)); // zo 0 dan alle updates in LOG-files tot file-close, dan duurt het daar we langer !
		JetCall(499, JetSetSystemParameter(&DB[DBRef].Instance, JET_sesidNil, JET_paramLogFileCreateAsynch, false, NULL));
		JetCall(498, JetSetSystemParameter(&DB[DBRef].Instance, JET_sesidNil, JET_paramLogFileSize, DBLogFileMegaBytes * 1024, NULL));	// parameter in kbytes  
		JetCall(497, JetSetSystemParameter(&DB[DBRef].Instance, JET_sesidNil, JET_paramCheckpointDepthMax, DBLogCacheMegaBytes * 1024 * 1024, NULL)); // size in bytes aan totale LOG-files in use voor ze naar de FAS gedumpt worden
		JetCall(414, JetSetSystemParameter(&DB[DBRef].Instance, JET_sesidNil, JET_paramLogBuffers, DBLogFileMegaBytes * 1024, NULL));	// in 512-bye units, 50% van LogFileSize om te cachen voor ze naar de *.log gaan 
		JetCall(420, JetSetSystemParameter(&DB[DBRef].Instance, JET_sesidNil, JET_paramTempPath, NULL, (char *)(LPCTSTR)LogPath));
		JetCall(421, JetSetSystemParameter(&DB[DBRef].Instance, JET_sesidNil, JET_paramLogFilePath, NULL, (char *)(LPCTSTR)LogPath));
		JetCall(422, JetSetSystemParameter(&DB[DBRef].Instance, JET_sesidNil, JET_paramSystemPath, NULL, (char *)(LPCTSTR)LogPath));
#else
		JetCall(413, JetSetSystemParameter(&DB[DBRef].Instance, JET_sesidNil, JET_paramCircularLog, 0, NULL)); // zo 0 dan alle updates in LOG-files tot file-close, dan duurt het daar we langer !
		JetCall(499, JetSetSystemParameter(&DB[DBRef].Instance, JET_sesidNil, JET_paramLogFileCreateAsynch, false, NULL));
		JetCall(498, JetSetSystemParameter(&DB[DBRef].Instance, JET_sesidNil, JET_paramLogFileSize, DBLogFileMegaBytes * 1024, NULL));	// parameter in kbytes  
		JetCall(497, JetSetSystemParameter(&DB[DBRef].Instance, JET_sesidNil, JET_paramCheckpointDepthMax, DBLogCacheMegaBytes * 1024 * 1024, NULL)); // size in bytes aan totale LOG-files in use voor ze naar de FAS gedumpt worden
		JetCall(414, JetSetSystemParameter(&DB[DBRef].Instance, JET_sesidNil, JET_paramLogBuffers, DBLogFileMegaBytes * 1024, NULL));	// in 512-bye units, 50% van LogFileSize om te cachen voor ze naar de *.log gaan 
		JetCall(420, JetSetSystemParameter(&DB[DBRef].Instance, JET_sesidNil, JET_paramTempPath, NULL, (char *)(LPCTSTR)LogPath));
		JetCall(421, JetSetSystemParameter(&DB[DBRef].Instance, JET_sesidNil, JET_paramLogFilePath, NULL, (char *)(LPCTSTR)LogPath));
		JetCall(422, JetSetSystemParameter(&DB[DBRef].Instance, JET_sesidNil, JET_paramSystemPath, NULL, (char *)(LPCTSTR)LogPath));
		DisableRecovery = true;
#endif

		// indien niet nodig, dan de recovery afzetten, is veel sneller ! (bv. bij creeeren nieuwe database of bij 'read only' )
		if (DisableRecovery) {
			LogAdd(0, 1, "Recovery is disabled for this instance of the DataBase");
			JetCall(415, JetSetSystemParameter(&DB[DBRef].Instance, JET_sesidNil, JET_paramRecovery, NULL, "Off"));
			DB[DBRef].DisabledRecovery = true;
		}
		else JetCall(419, JetSetSystemParameter(&DB[DBRef].Instance, JET_sesidNil, JET_paramRecovery, NULL, "On"));

		// Initialize a session for this database 
		JetCall(411, JetInit(&DB[DBRef].Instance));
	}
	else { // controleer of database ook echt open is, dwz dat vorige EDBOPenDatabase compleet uitgevoerd is, zoniet lukt de JetCall(412 niet ...
		int i;
		for (i = 0; i < 30; i++) {
			if (DB[DBRef].Id[0] != NULL) break;
			Sleep(500);
			pMainDlg->ProcessAllMessages();
		}
		if (i == 30) {
			LogAdd(1, 0, "DB was attached but did not open within 15 seconds", DB[DBRef].Name);
			return false;
		}
	}

	JetCall(412, JetBeginSession(DB[DBRef].Instance, &DB[DBRef].SesId[ThdRef], 0, 0));

	JET_GRBIT bits = 0;
#ifdef JMSVIEWER
	bits = JET_bitDbReadOnly;
#endif
	JET_ERR err = JetAttachDatabase(DB[DBRef].SesId[ThdRef], DB[DBRef].NamePath, bits); // no JET_bitDbDeleteCorruptIndexes 
	if (ThdRef > 0) { // 0 is de main-thread
		if (err != JET_errSuccess && err != JET_wrnDatabaseAttached) {
			LogAdd(26, 0, "Database not found when opening extra session for Thread", DB[DBRef].NamePath);
			JetCall(425, JetEndSession(DB[DBRef].SesId[ThdRef], 0));
			return true;
		}
		JetCall(426, JetOpenDatabase(DB[DBRef].SesId[ThdRef], DB[DBRef].NamePath, NULL, &DB[DBRef].Id[ThdRef], bits)); //JET_bitDbExclusive));
		return true;
	}
	if (err == JET_errFileNotFound) {
		if (!CreateWhenNotFound) {
			LogAdd(0, 0, "Database not found", DB[DBRef].NamePath);
			JetCall(417, JetEndSession(DB[DBRef].SesId[ThdRef], 0));
			JetCall(418, JetTerm(DB[DBRef].Instance));
			return false;
		}

		//check if xxx.FSD exists ... zoniet moet deze FAS niet gemaakt worden, wellicht oude resten in een SYS.file
		CString FsdName = PathProg + DB[DBRef].Name;
		int i = FsdName.ReverseFind('.');
		FsdName = FsdName.Left(i) + ".fsd";
		if (GetFileAttributes(FsdName) == INVALID_FILE_ATTRIBUTES) {
			LogAdd(0, 1, "Database not found (and not created as no VALID FSD-file found)", DB[DBRef].NamePath);
			return false;
		}

		DB[DBRef].CreatedNew = true;
		JetCall(401, JetCreateDatabase(DB[DBRef].SesId[ThdRef], DB[DBRef].NamePath, 0, &DB[DBRef].Id[ThdRef], 0));
		LogAdd(0, 1, "Created Database", DB[DBRef].NamePath);
		// JetCall(402,JetAttachDatabase(DB[DBRef].SesId[ThdRef], dbname, 0)); // retry
	}
	else if (err == JET_errDatabaseDirtyShutdown) {
		if (!RepairDoneFlag) {
			JetDetachDatabase(DB[DBRef].SesId[0], DB[DBRef].NamePath); // anders is de DB gelocked of busy vooo recovery !
			JetEndSession(DB[DBRef].SesId[0], 0);
			JetTerm(DB[DBRef].Instance);
			if (ExecESEntUtl(DBRef, 1)) {
				RepairDoneFlag = true;
				goto retry;  // repair after dirtystate !
			}
		}
		// Wanneer utility niet te vinden is of wanneer de repair het probleem niet oplost (en dus 2 keer error geeft)
		// dan sessie sluiten
		JetCall(417, JetEndSession(DB[DBRef].SesId[ThdRef], 0));
		JetCall(418, JetTerm(DB[DBRef].Instance));
		LogAdd(28, 0, "Database not mounted because of 'dirty shutdown'", DB[DBRef].NamePath);
		return false;
	}
	else if (err != JET_errSuccess) {
		LogJet(410, err); // om het te loggen !
		char errbuf[200];
		errbuf[0] = 0;
		JetGetSystemParameter(NULL, DB[DBRef].SesId[ThdRef], JET_paramErrorToString, (JET_API_PTR *)&err, errbuf, sizeof(errbuf));
		// MessageBox(pMainDlg->GetSafeHwnd(),errbuf,"Database kan niet geladen worden",MB_ICONEXCLAMATION|MB_OK);
		return false;
	}
	else JetCall(403, JetOpenDatabase(DB[DBRef].SesId[ThdRef], DB[DBRef].NamePath, NULL, &DB[DBRef].Id[ThdRef], 0)); //JET_bitDbExclusive));

  // create 'OpenFileFlag' in LOG-dir
	CString cstr = DB[DBRef].LogPath;
	cstr += "OpenFile.flg";
	CFile flgFile;
	flgFile.Open(cstr, CFile::modeCreate); // create file
	flgFile.Close();

	return true;
}


bool EDBClose(int DBRef)
{
	JET_ERR _jeterr;
	JetCall(501, JetCloseDatabase(DB[DBRef].SesId[0], DB[DBRef].Id[0], 0));
	JetCall(502, JetDetachDatabase(DB[DBRef].SesId[0], DB[DBRef].NamePath));
	JetCall(503, JetEndSession(DB[DBRef].SesId[0], 0));
	JetCall(504, JetTerm(DB[DBRef].Instance));

	// Zet de last write time in de file op het tijdstip wanneer de laatste record geschreven werd ... wordt gebruikt voor backuptoestanden !
	double DateTimeUpdate = -1000;
	for (int TabIx = 0; TabIx < DB[DBRef].TabCnt; TabIx++) {
		if (DB[DBRef].Tab[TabIx].StuNr > 0 && DB[DBRef].Tab[TabIx].DateTimeUpdate > DateTimeUpdate) {
			DateTimeUpdate = DB[DBRef].Tab[TabIx].DateTimeUpdate;
		}
	}
#ifndef JMSVIEWER
	CFile DBFile;
	DBFile.Open(DB[DBRef].NamePath, CFile::modeReadWrite, NULL);
	SetFileLastWriteTime(DBFile.m_hFile, DateTimeUpdate);
	DBFile.Close();
#endif

	// delete 'OpenFileFlag' in LOG-dir
	CString cstr = DB[DBRef].LogPath;
	cstr += "OpenFile.flg";
	_unlink(cstr);

	if (!EmergencyExit) {    // ruim de LOG bestanden op, tenzij EmergencyExit ! Dan geen tijd verliezen ...
	  // remove log-subdir
		CFileFind finder;
		CFile LogFile;
		CString cstr = DB[DBRef].LogPath;
		if (cstr.GetLength() < 6 || cstr.Right(5).CompareNoCase(".LOG\\") != 0) return true; // geen risico's lopen, enkel die subdir leegmaken
		cstr += _T("*.*");
		BOOL bWorking = finder.FindFile(cstr);  // zoek alle bestanden in de xxx.log subdir
		while (bWorking) {
			bWorking = finder.FindNextFile();
			if (finder.IsDirectory()) continue;
			_unlink(finder.GetFilePath());
		}
		finder.Close();
		_rmdir(DB[DBRef].LogPath);
	}
	else {
		if (DB[DBRef].DisabledRecovery) _rmdir(DB[DBRef].LogPath); // directory zou leeg moeten zijn !
	}

	return true;
}

bool EDBAddDeletedRecNr(int ThdRef, int DBRef, short int StuNr, unsigned RecNr, double DelDateTime, short int ChangedBy)
{
	UNALIGNED struct sComBuf *ComBuf;
	JET_ERR _jeterr;

	ComBuf = (struct sComBuf*)Thd[ThdRef].ComBuf;
	JetCall(601, JetBeginTransaction(DB[DBRef].SesId[ThdRef]))
		JetCall(602, JetPrepareUpdate(DB[DBRef].SesId[ThdRef], DB[DBRef].Tab[DelId].Tid[ThdRef], JET_prepInsert));

	JetCall(603, JetSetColumn(DB[DBRef].SesId[ThdRef], DB[DBRef].Tab[DelId].Tid[ThdRef], DB[DBRef].Tab[DelId].Col[DelStuId].Cid[ThdRef], &StuNr, DB[DBRef].Tab[DelId].Col[DelStuId].Len, 0, NULL));
	JetCall(604, JetSetColumn(DB[DBRef].SesId[ThdRef], DB[DBRef].Tab[DelId].Tid[ThdRef], DB[DBRef].Tab[DelId].Col[DelRecId].Cid[ThdRef], &RecNr, DB[DBRef].Tab[DelId].Col[DelRecId].Len, 0, NULL));

	JetCall(607, JetSetColumn(DB[DBRef].SesId[ThdRef], DB[DBRef].Tab[DelId].Tid[ThdRef], DB[DBRef].Tab[DelId].Col[DelDatId].Cid[ThdRef], &DelDateTime, DB[DBRef].Tab[DelId].Col[DelDatId].Len, 0, NULL));
	JetCall(608, JetSetColumn(DB[DBRef].SesId[ThdRef], DB[DBRef].Tab[DelId].Tid[ThdRef], DB[DBRef].Tab[DelId].Col[DelChgId].Cid[ThdRef], &ChangedBy, DB[DBRef].Tab[DelId].Col[DelChgId].Len, 0, NULL));

	_jeterr = JetUpdate(DB[DBRef].SesId[ThdRef], DB[DBRef].Tab[DelId].Tid[ThdRef], NULL, 0, NULL);
	if (_jeterr != JET_errSuccess) LogJet(606, _jeterr);

	JetCall(605, JetCommitTransaction(DB[DBRef].SesId[ThdRef], JetCommitBits));

	return true;
}

int EDBFindDeletedRecNr(int ThdRef, int DBRef, short int StuNr)
{
	int RecNr = 0;
	JET_ERR _jeterr;
	short int StuNrFound;
	JetCall(701, JetSetCurrentIndex4(DB[DBRef].SesId[ThdRef], DB[DBRef].Tab[DelId].Tid[ThdRef], "", (JET_INDEXID*)DB[DBRef].Tab[DelId].Idx[DelStuRecIx].rgbIndexId[ThdRef], 0, 0));
	JetCall(702, JetMakeKey(DB[DBRef].SesId[ThdRef], DB[DBRef].Tab[DelId].Tid[ThdRef], &StuNr, DB[DBRef].Tab[DelId].Col[DelStuId].Len, JET_bitNewKey));
	JetCall(703, JetMakeKey(DB[DBRef].SesId[ThdRef], DB[DBRef].Tab[DelId].Tid[ThdRef], &RecNr, DB[DBRef].Tab[DelId].Col[DelRecId].Len, 0));
	_jeterr = JetSeek(DB[DBRef].SesId[ThdRef], DB[DBRef].Tab[DelId].Tid[ThdRef], JET_bitSeekGE);
	if (_jeterr != JET_wrnSeekNotEqual) return RecNr; // is 0 (not found)

	unsigned long retreclen = 0;
	JetCall(704, JetRetrieveColumn(DB[DBRef].SesId[ThdRef], DB[DBRef].Tab[DelId].Tid[ThdRef], DB[DBRef].Tab[DelId].Col[DelStuId].Cid[ThdRef], &StuNrFound, DB[DBRef].Tab[DelId].Col[DelStuId].Len, &retreclen, 0, 0));
	if (StuNrFound != StuNr) return RecNr; // is 0 (not found)	
	JetCall(705, JetRetrieveColumn(DB[DBRef].SesId[ThdRef], DB[DBRef].Tab[DelId].Tid[ThdRef], DB[DBRef].Tab[DelId].Col[DelRecId].Cid[ThdRef], &RecNr, DB[DBRef].Tab[DelId].Col[DelRecId].Len, &retreclen, 0, 0));
	_jeterr = JetDelete(DB[DBRef].SesId[ThdRef], DB[DBRef].Tab[DelId].Tid[ThdRef]); // if a RecNr found, delete the entry in the deleted list
	if (_jeterr != JET_errSuccess) {
		LogJet(706, _jeterr);
		CString cstr;
		cstr.Format("%d ThdRef=%d DBRef=%d RecNr=%d", StuNr, ThdRef, RecNr);
		LogAdd(0, 2, "StuNr", cstr);
	}
	return RecNr;
}

int EDBCleanUpObsoleteDeletedRecNr(int DBRef, short int TabNr)
{
	unsigned long retreclen = 0;
	int RecNr, StuNr, RecNrFound, DeletedCount = 0;
	short int StuNrFound;
	JET_ERR _jeterr;

	StuNr = DB[DBRef].Tab[TabNr].StuNr;
	RecNr = DB[DBRef].Tab[TabNr].LastRec;
	RecNr++; //remove all entries beginning from stunr+RecNr

	JetCall(801, JetSetCurrentIndex4(DB[DBRef].SesId[0], DB[DBRef].Tab[DelId].Tid[0], "", (JET_INDEXID*)DB[DBRef].Tab[DelId].Idx[DelStuRecIx].rgbIndexId[0], 0, 0));
	JetCall(802, JetMakeKey(DB[DBRef].SesId[0], DB[DBRef].Tab[DelId].Tid[0], &StuNr, DB[DBRef].Tab[DelId].Col[DelStuId].Len, JET_bitNewKey));
	JetCall(803, JetMakeKey(DB[DBRef].SesId[0], DB[DBRef].Tab[DelId].Tid[0], &RecNr, DB[DBRef].Tab[DelId].Col[DelRecId].Len, 0));
	_jeterr = JetSeek(DB[DBRef].SesId[0], DB[DBRef].Tab[DelId].Tid[0], JET_bitSeekGE);
	if (_jeterr != JET_wrnSeekNotEqual && _jeterr != JET_errSuccess) return 0; // Stu+RecNr no keys equal or greater found 

	FOREVER{
		StuNrFound = 0; RecNrFound = 0;
		JetCall(804,JetRetrieveColumn(DB[DBRef].SesId[0], DB[DBRef].Tab[DelId].Tid[0], DB[DBRef].Tab[DelId].Col[DelStuId].Cid[0],&StuNrFound, DB[DBRef].Tab[DelId].Col[DelStuId].Len,&retreclen,0,0));
		JetCall(805,JetRetrieveColumn(DB[DBRef].SesId[0], DB[DBRef].Tab[DelId].Tid[0], DB[DBRef].Tab[DelId].Col[DelRecId].Cid[0],&RecNrFound, DB[DBRef].Tab[DelId].Col[DelRecId].Len,&retreclen,0,0));
		if (StuNrFound != StuNr) break;
		if (RecNrFound >= RecNr) {
			JetCall(806,JetDelete(DB[DBRef].SesId[0], DB[DBRef].Tab[DelId].Tid[0])); // if a RecNr found, delete the entry in the deleted list
			LogAdd(0,1,"End of records but DeletedEntry is found, so deleted",RecNrFound);
			DeletedCount++;
		}
		_jeterr = JetMove(DB[DBRef].SesId[0], DB[DBRef].Tab[DelId].Tid[0], JET_MoveNext,0);
		if (_jeterr != JET_errSuccess) break;
	}
	return DeletedCount;
}

bool InitSessionColumn(int ThdRef, int DBRef, int idt, int idc)
{
	JET_COLUMNDEF columndef = { 0 };

	JET_ERR err = JetGetColumnInfo(DB[DBRef].SesId[ThdRef], DB[DBRef].Id[ThdRef], DB[DBRef].Tab[idt].Nam, DB[DBRef].Tab[idt].Col[idc].Nam, &columndef, sizeof(columndef), JET_ColInfo);
	DB[DBRef].Tab[idt].Col[idc].Cid[ThdRef] = columndef.columnid;

	return true;
}


bool CheckAndUpdateColumn(int DBRef, int idt, int idc)
{
	JET_COLUMNDEF columndef = { 0 };
	JET_COLUMNID columnid;
	JET_ERR _jeterr;

	JET_ERR err = JetGetColumnInfo(DB[DBRef].SesId[0], DB[DBRef].Id[0], DB[DBRef].Tab[idt].Nam, DB[DBRef].Tab[idt].Col[idc].Nam, &columndef, sizeof(columndef), JET_ColInfo);
	DB[DBRef].Tab[idt].Col[idc].Cid[0] = columndef.columnid;

	if (err != JET_errSuccess) {
		JetCall(901, JetBeginTransaction(DB[DBRef].SesId[0])); // moet afgesloten worden met JetCommitTransaction of JetRollBack

		columndef.cbStruct = sizeof(columndef);
		columndef.coltyp = DB[DBRef].Tab[idt].Col[idc].Typ;
		columndef.cbMax = DB[DBRef].Tab[idt].Col[idc].Len;
		columndef.cp = 1252;
		columndef.grbit = 0;
		if (strcmp(DB[DBRef].Tab[idt].Col[idc].Nam, "DateTimeUpdated") == 0) {
			double now = COleDateTime::GetCurrentTime().operator double();
			DB[DBRef].Tab[idt].DateTimeUpdate = now;
			JetCall(902, JetAddColumn(DB[DBRef].SesId[0], DB[DBRef].Tab[idt].Tid[0], DB[DBRef].Tab[idt].Col[idc].Nam, &columndef, &now, sizeof(double), &columnid));
		}
		else {
			JetCall(902, JetAddColumn(DB[DBRef].SesId[0], DB[DBRef].Tab[idt].Tid[0], DB[DBRef].Tab[idt].Col[idc].Nam, &columndef, NULL, 0, &columnid));
		}
		DB[DBRef].Tab[idt].Col[idc].Cid[0] = columnid;

		JetCall(903, JetCommitTransaction(DB[DBRef].SesId[0], JetCommitBits));
		LogAdd(0, 2, "Column created", DB[DBRef].Tab[idt].Col[idc].Nam);

	}
	DB[DBRef].Tab[idt].Col[idc].Len = columndef.cbMax;
	DB[DBRef].Tab[idt].Col[idc].Typ = columndef.coltyp;

	return true;
}

bool InitSessionIndex(int ThdRef, int DBRef, int idt, int idi)
{
	JET_ERR err = JetGetIndexInfo(DB[DBRef].SesId[ThdRef], DB[DBRef].Id[ThdRef], DB[DBRef].Tab[idt].Nam, DB[DBRef].Tab[idt].Idx[idi].Nam, DB[DBRef].Tab[idt].Idx[idi].rgbIndexId[ThdRef], sizeof(DB[0].Tab[0].Idx[0].rgbIndexId[0]), JET_IdxInfoIndexId);

	return true;
}

bool CheckAndUpdateIndex(int DBRef, int idt, int idi)
{
	JET_ERR _jeterr;
	JET_ERR err = JetGetIndexInfo(DB[DBRef].SesId[0], DB[DBRef].Id[0], DB[DBRef].Tab[idt].Nam, DB[DBRef].Tab[idt].Idx[idi].Nam, DB[DBRef].Tab[idt].Idx[idi].rgbIndexId[0], sizeof(DB[0].Tab[0].Idx[0].rgbIndexId[0]), JET_IdxInfoIndexId);

	if (err != JET_errSuccess) {
		JetCall(1001, JetBeginTransaction(DB[DBRef].SesId[0])); // moet afgesloten worden met JetCommitTransaction of JetRollBack

		int grbit = 0;
		if (idi == 0) grbit = JET_bitIndexPrimary;
		// else grbit=JET_bitIndexIgnoreAnyNull;  // laat NULL toe (bij deleten) is wellicht niet nodig !
		if ((DB[DBRef].Tab[idt].KeyInf[idi].Typ & 0x08) == 0)  grbit |= JET_bitIndexUnique;
		int len = 0;
		for (len = 1; len < MAX_SZKEY; len++) {
			if (DB[DBRef].Tab[idt].Idx[idi].szKey[len - 1] == 0 && DB[DBRef].Tab[idt].Idx[idi].szKey[len] == 0) {
				len++;
				break;
			}
		}

		JetCall(1002, JetCreateIndex(DB[DBRef].SesId[0], DB[DBRef].Tab[idt].Tid[0], DB[DBRef].Tab[idt].Idx[idi].Nam, grbit, DB[DBRef].Tab[idt].Idx[idi].szKey, len, 75)); //ulDensity=75 // 100));
		JetCall(1003, JetCommitTransaction(DB[DBRef].SesId[0], JetCommitBits));
		LogAdd(0, 2, "Index created", DB[DBRef].Tab[idt].Idx[idi].Nam);
		JetCall(1004, JetGetIndexInfo(DB[DBRef].SesId[0], DB[DBRef].Id[0], DB[DBRef].Tab[idt].Nam, DB[DBRef].Tab[idt].Idx[idi].Nam, DB[DBRef].Tab[idt].Idx[idi].rgbIndexId[0], sizeof(DB[0].Tab[0].Idx[0].rgbIndexId[0]), JET_IdxInfoIndexId));
	}

	return true;
}

bool CalcAndUpdateStats(int DBRef, bool LogAsError)
{
	JET_OBJECTINFO TabInfo;
	int TabNr, StuNr, RecNr;
	unsigned long retreclen;
	CString cstr;
	JET_ERR _jeterr;

	for (TabNr = 1; TabNr <= DB[DBRef].TabCnt; TabNr++) {
		StuNr = DB[DBRef].Tab[TabNr].StuNr;
		if (StuNr == 0) continue;
		TabInfo.cbStruct = sizeof(TabInfo);
		JetCall(1101, JetComputeStats(DB[DBRef].SesId[0], DB[DBRef].Tab[TabNr].Tid[0]));
		JetCall(1102, JetGetObjectInfo(DB[DBRef].SesId[0], DB[DBRef].Id[0], JET_objtypTable, NULL, DB[DBRef].Tab[TabNr].Nam, &TabInfo, sizeof(TabInfo), JET_ObjInfo));

		if (DB[DBRef].Tab[TabNr].UsedRec != TabInfo.cRecord) {
			int ErrNum = 0;
			if (LogAsError) ErrNum = 62;
			cstr.Format("DB=%s Stu=%d UsedRecInFileTable=%d UsedRecsFound=%d", DB[DBRef].Name, StuNr, DB[DBRef].Tab[TabNr].UsedRec, TabInfo.cRecord);
			LogAdd(ErrNum, 0, "UsedRec corrected", cstr);
			DB[DBRef].Tab[TabNr].UsedRec = TabInfo.cRecord;
		}

		JetCall(1103, JetSetCurrentIndex4(DB[DBRef].SesId[0], DB[DBRef].Tab[TabNr].Tid[0], "", (JET_INDEXID*)DB[DBRef].Tab[TabNr].Idx[StuRecIx].rgbIndexId[0], 0, 0));
		_jeterr = JetMove(DB[DBRef].SesId[0], DB[DBRef].Tab[TabNr].Tid[0], JET_MoveLast, 0);
		if (_jeterr != JET_errSuccess) RecNr = 0;
		else JetCall(1104, JetRetrieveColumn(DB[DBRef].SesId[0], DB[DBRef].Tab[TabNr].Tid[0], DB[DBRef].Tab[TabNr].Col[StuRecId].Cid[0], &RecNr, DB[DBRef].Tab[TabNr].Col[StuRecId].Len, &retreclen, 0, 0));

		int CorrectionCount = DB[DBRef].Tab[TabNr].LastRec - RecNr;
		if (CorrectionCount) {
			cstr.Format("DB=%s Stu=%d LastRecInFileTable=%d LastRecFound=%d", DB[DBRef].Name, StuNr, DB[DBRef].Tab[TabNr].LastRec, RecNr);
			DB[DBRef].Tab[TabNr].LastRec = RecNr;
		}
		int DeletedCount = EDBCleanUpObsoleteDeletedRecNr(DBRef, TabNr); // doe de checkdeletedrecords ook, maar die duurt langer ...

	// tijdelijk dit niet meer doen ... lastrec is niet belangrijk, het aantal used recs wel ! MVG
	/*
	if (CorrectionCount<0 || (DeletedCount!=CorrectionCount)) {
	  int ErrNum=0;
	  if (LogAsError) ErrNum=61;
			LogAdd(ErrNum,0,"LastRec corrected",cstr);
	}
	*/

	// MVG volgende lijn is vervangen door een uitgebreidere logging
		cstr.Format("Struct %d [%s], total used records", StuNr, DB[DBRef].Tab[TabNr].StructName);
		LogAdd(0, 1, cstr, DB[DBRef].Tab[TabNr].UsedRec);

		COleDateTime dt = COleDateTime(DB[DBRef].Tab[TabNr].DateTimeUpdate);
		CString ctime;
		ctime.Format("%02d/%02d/%04d-%02d:%02d:%02d", dt.GetDay(), dt.GetMonth(), dt.GetYear(), dt.GetHour(), dt.GetMinute(), dt.GetSecond());
		cstr.Format("%d UsedRecs=%d LastRec=%d ChgdByProcId=%d ChgdAt=%s", StuNr, DB[DBRef].Tab[TabNr].UsedRec, DB[DBRef].Tab[TabNr].LastRec, DB[DBRef].Tab[TabNr].ChangedBy, ctime);
		LogAdd(0, 2, "StuNr", cstr);
	}

	return true;
}

bool CheckDeletedRecords(int DBRef, short int TabNr, bool LogAsError)
{
	unsigned RecNr, RecNrDeleted, RecNrFound, RecNrExpected;
	bool GetNextRecordFlag = false, GetNextDeletedFlag = false;
	short int StuNr, StuNrFound;
	unsigned long retreclen;
	JET_ERR jeterrDeleted, jeterrRecord;
	JET_ERR _jeterr;

	StuNr = DB[DBRef].Tab[TabNr].StuNr;
	RecNrDeleted = 0xFFFFFFFF;
	JetCall(1201, JetSetCurrentIndex4(DB[DBRef].SesId[0], DB[DBRef].Tab[DelId].Tid[0], "", (JET_INDEXID*)DB[DBRef].Tab[DelId].Idx[DelStuRecIx].rgbIndexId[0], 0, 0));
	JetCall(1202, JetMakeKey(DB[DBRef].SesId[0], DB[DBRef].Tab[DelId].Tid[0], &StuNr, DB[DBRef].Tab[DelId].Col[DelStuId].Len, JET_bitNewKey));
	RecNr = 0; // zoek eerste deleted rec in deze struct
	JetCall(1203, JetMakeKey(DB[DBRef].SesId[0], DB[DBRef].Tab[DelId].Tid[0], &RecNr, DB[DBRef].Tab[DelId].Col[DelRecId].Len, 0));
	jeterrDeleted = JetSeek(DB[DBRef].SesId[0], DB[DBRef].Tab[DelId].Tid[0], JET_bitSeekGE);
	if (jeterrDeleted == JET_wrnSeekNotEqual || jeterrDeleted == JET_errSuccess) {
		JetCall(1204, JetRetrieveColumn(DB[DBRef].SesId[0], DB[DBRef].Tab[DelId].Tid[0], DB[DBRef].Tab[DelId].Col[DelStuId].Cid[0], &StuNrFound, DB[DBRef].Tab[DelId].Col[DelStuId].Len, &retreclen, 0, 0));
		//controleer of het nog steeds deleted recs van deze structuur gaat
		if (StuNrFound == StuNr) {
			JetCall(1205, JetRetrieveColumn(DB[DBRef].SesId[0], DB[DBRef].Tab[DelId].Tid[0], DB[DBRef].Tab[DelId].Col[DelRecId].Cid[0], &RecNrDeleted, DB[DBRef].Tab[DelId].Col[DelRecId].Len, &retreclen, 0, 0));
		}
	}

	JetCall(1206, JetSetCurrentIndex4(DB[DBRef].SesId[0], DB[DBRef].Tab[TabNr].Tid[0], "", (JET_INDEXID*)DB[DBRef].Tab[TabNr].Idx[StuRecIx].rgbIndexId[0], 0, 0));
	jeterrRecord = JetMove(DB[DBRef].SesId[0], DB[DBRef].Tab[TabNr].Tid[0], JET_MoveFirst, 0);
	if (jeterrRecord != JET_errSuccess) RecNrFound = 0xFFFFFFFF;
	else JetCall(1207, JetRetrieveColumn(DB[DBRef].SesId[0], DB[DBRef].Tab[TabNr].Tid[0], DB[DBRef].Tab[TabNr].Col[StuRecId].Cid[0], &RecNrFound, DB[DBRef].Tab[TabNr].Col[StuRecId].Len, &retreclen, 0, 0));

	double now = COleDateTime::GetCurrentTime().operator double();
	for (RecNrExpected = 1; RecNrExpected < DB[DBRef].Tab[TabNr].MaxRec; RecNrExpected++) {
		GetNextRecordFlag = false; GetNextDeletedFlag = false;
		if (RecNrExpected == RecNrFound) { // RecNrExpected is found in db
			if (RecNrDeleted == RecNrExpected) {
				// recordnummer zat nog wel in deleted item, verwijder dus die record (huidige cursor) !
				JetCall(1208, JetDelete(DB[DBRef].SesId[0], DB[DBRef].Tab[DelId].Tid[0]));
				CString cstr;
				cstr.Format("RecordNr %d found in Stu-%c but DeletedEntry existed, so deleted. DB-Name", RecNrDeleted, StuNr);
				LogAdd(59, 0, cstr, DB[DBRef].Name);
				GetNextDeletedFlag = true;
			}
			GetNextRecordFlag = true;
		}
		else if (RecNrFound == 0xFFFFFFFF) {
			// geen records meer, controleer of er nog entries in de Deleted Records zitten
			  // zo neen, stop ermee
			if (RecNrDeleted == 0xFFFFFFFF) break;
			// als er nog wel Deleted records zijn, dan die rec wissen 
			JetCall(1209, JetDelete(DB[DBRef].SesId[0], DB[DBRef].Tab[DelId].Tid[0]));
			LogAdd(0, 2, "End of records but DeletedEntry is found, so deleted", RecNrDeleted);
			// Zoek volgende, als er nog zijn
			GetNextDeletedFlag = true;
		}
		else {
			// RecNrExpected is not found, there should be entry in deleted records
			if (RecNrDeleted != RecNrExpected) { // Deleted entry is missing 
				// thus add the entry
				EDBAddDeletedRecNr(0, DBRef, StuNr, RecNrExpected, now, -1);
				if (LogAsError) {
					CString cstr;
					cstr.Format("RecordNr %d was deleted in Stu-%c but DeletedEntry not found, so added. DB-Name", RecNrDeleted, StuNr);
					LogAdd(60, 0, cstr, DB[DBRef].Name);
				}
				// else LogAdd(0,2,"Rec missing but no DelEntry found, so added",RecNrExpected); GAF TEVEEL INFO BIJ OLD->NEW e.d.
			}
			else {
				// Expected nr has no entry, but Deleted record is found
				// thus get next deleted entry
				GetNextDeletedFlag = true;
			}
		}
		if (GetNextRecordFlag) {
			jeterrRecord = JetMove(DB[DBRef].SesId[0], DB[DBRef].Tab[TabNr].Tid[0], JET_MoveNext, 0);
			if (jeterrRecord != JET_errSuccess) RecNrFound = 0xFFFFFFFF;
			else JetCall(1210, JetRetrieveColumn(DB[DBRef].SesId[0], DB[DBRef].Tab[TabNr].Tid[0], DB[DBRef].Tab[TabNr].Col[StuRecId].Cid[0], &RecNrFound, DB[DBRef].Tab[TabNr].Col[StuRecId].Len, &retreclen, 0, 0));
		}
		if (GetNextDeletedFlag) {
			jeterrDeleted = JetMove(DB[DBRef].SesId[0], DB[DBRef].Tab[DelId].Tid[0], JET_MoveNext, 0);
			if (jeterrDeleted != JET_errSuccess) RecNrDeleted = 0xFFFFFFFF;
			else {
				JetCall(1211, JetRetrieveColumn(DB[DBRef].SesId[0], DB[DBRef].Tab[DelId].Tid[0], DB[DBRef].Tab[DelId].Col[DelStuId].Cid[0], &StuNrFound, DB[DBRef].Tab[DelId].Col[DelStuId].Len, &retreclen, 0, 0));
				if (StuNrFound != StuNr) RecNrDeleted = 0xFFFFFFFF;
				else JetCall(1212, JetRetrieveColumn(DB[DBRef].SesId[0], DB[DBRef].Tab[DelId].Tid[0], DB[DBRef].Tab[DelId].Col[DelRecId].Cid[0], &RecNrDeleted, DB[DBRef].Tab[DelId].Col[DelRecId].Len, &retreclen, 0, 0));
			}
		}
	}
	return true;
}

bool PeriodicCheckDatabase(int DBRef, bool LogAsError)
{
	int TabNr, StuNr;

	for (TabNr = 1; TabNr <= DB[DBRef].TabCnt; TabNr++) {

		StuNr = DB[DBRef].Tab[TabNr].StuNr;
		if (StuNr == 0) continue;
		/*
		if (DB[DBRef].Tab[TabNr].FasType&1) {
			LogAdd(0,1,"Executing compress on Struct",StuNr);
			// compress does not work by renaming the RecNr because it's a primary index
			// could only be done by deleting the old recnr and reinserting it at the empty place
			// but hey, this doesn't provide extra space ...
			CompressRecords(DBRef, StuNr);
		}
		else {
		*/
		LogAdd(0, 1, "Checking Deleted entries in Struct", StuNr);
		CheckDeletedRecords(DBRef, TabNr, LogAsError);
	}
	return true;
}


void EDBCheckCalc(int DBRef, bool LogAsError)
{
	LogAdd(0, 1, "Start checking deleted records for database", DB[DBRef].Name);
	PeriodicCheckDatabase(DBRef, LogAsError);
	LogAdd(0, 1, "Start calculating used records database", DB[DBRef].Name);
	CalcAndUpdateStats(DBRef, LogAsError);
	LogAdd(0, 1, "Calculation done ...");
}

bool InitSessionTable(int ThdRef, int DBRef, int idt)
{
	JET_TABLEID tid;
	JET_ERR _jeterr;

	JetCall(3401, JetOpenTable(DB[DBRef].SesId[ThdRef], DB[DBRef].Id[ThdRef], DB[DBRef].Tab[idt].Nam, NULL, 0, JET_bitTableUpdatable, &tid));
	DB[DBRef].Tab[idt].Tid[ThdRef] = tid;

	for (int i = 0; i < CL_MAX; i++) {
		if (DB[DBRef].Tab[idt].Col[i].Nam[0] == 0) continue;
		if (!InitSessionColumn(ThdRef, DBRef, idt, i)) return false;
	}

	for (int i = 0; i < IX_MAX; i++) {
		if (DB[DBRef].Tab[idt].Idx[i].Nam[0] == 0) continue;
		if (!InitSessionIndex(ThdRef, DBRef, idt, i)) return false;
	}

	return true;
}


bool CheckAndUpdateTable(int DBRef, int idt)
{
	JET_TABLEID tid;
	JET_ERR _jeterr;

	JET_ERR err = JetOpenTable(DB[DBRef].SesId[0], DB[DBRef].Id[0], DB[DBRef].Tab[idt].Nam, NULL, 0, JET_bitTableUpdatable, &tid);

	if (err != JET_errSuccess) {
		JetCall(1501, JetBeginTransaction(DB[DBRef].SesId[0])); // moet afgesloten worden met JetCommitTransaction of JetRollBack
		JetCall(1502, JetCreateTable(DB[DBRef].SesId[0], DB[DBRef].Id[0], DB[DBRef].Tab[idt].Nam, 0, 75, &tid)); // ulDensity = 75
		JetCall(1503, JetCommitTransaction(DB[DBRef].SesId[0], JetCommitBits));
		JetCall(1504, JetCloseTable(DB[DBRef].SesId[0], tid));
		// reopen table nu in goed formaat !
		JetCall(1505, JetOpenTable(DB[DBRef].SesId[0], DB[DBRef].Id[0], DB[DBRef].Tab[idt].Nam, NULL, 0, JET_bitTableUpdatable, &tid));
		LogAdd(0, 1, "Table created", DB[DBRef].Tab[idt].Nam);
	}

	DB[DBRef].Tab[idt].Tid[0] = tid;

	for (int i = 0; i < CL_MAX; i++) {
		if (DB[DBRef].Tab[idt].Col[i].Nam[0] == 0) continue;
		if (!CheckAndUpdateColumn(DBRef, idt, i)) return false;
	}

	for (int i = 0; i < IX_MAX; i++) {
		if (DB[DBRef].Tab[idt].Idx[i].Nam[0] == 0) continue;
		if (!CheckAndUpdateIndex(DBRef, idt, i)) return false;
	}

	return true;
}

bool EDBCloseSession(int ThdRef, int DBRef)
{
	UNALIGNED struct sComBuf *ComBuf;
	ComBuf = (struct sComBuf*)Thd[ThdRef].ComBuf;

	// Update Proc2DBRef table
	for (int TabIx = 0; TabIx < DB[DBRef].TabCnt; TabIx++) {
		int StuNr = DB[DBRef].Tab[TabIx].StuNr;
		if (StuNr) {
			Proc2DBRef[ComBuf->OrigId][StuNr] = -1;
			Proc2DBRefOpened[ComBuf->OrigId][StuNr] = false;
		}
	}

	return true;
}

void EDBEndAllSessions(int DBRef)
{
	JET_ERR _jeterr;

	for (int ThdRef = 1; ThdRef < MAX_THREADS; ThdRef++) {  // thread 0 is de 'mount' sessie, die wordt enkel via de Unmount() gesloten, als de users-sessie niet langer in gebruik zijn ...
	  // kijk of de sessie voor DBRef in deze thread gebruikt wordt, zo ja : end die session !
		if (DB[DBRef].SesId[ThdRef] != NULL) {
			JetCallVoidRet(3001, JetCloseDatabase(DB[DBRef].SesId[ThdRef], DB[DBRef].Id[ThdRef], 0));
			//JetCall(3002,JetDetachDatabase(DB[DBRef].SesId[ThdRef],DB[DBRef].NamePath));
			JetCallVoidRet(3003, JetEndSession(DB[DBRef].SesId[ThdRef], 0));
			memset(&DB[DBRef].Id[ThdRef], 0, sizeof(DB[0].Id[0]));
			memset(&DB[DBRef].SesId[ThdRef], 0, sizeof(DB[0].SesId[0]));
		}
		for (int Proc = 0; Proc < MAX_PROC; Proc++) {
			if (ThdRef == Proc2ThdRef[Proc]) {
				// Update Proc2DBRef table
				for (int TabIx = 0; TabIx < DB[DBRef].TabCnt; TabIx++) {
					int StuNr = DB[DBRef].Tab[TabIx].StuNr;
					if (StuNr) {
						Proc2DBRef[Proc][StuNr] = -1;
						Proc2DBRefOpened[Proc][StuNr] = false;
					}
				}
				break;
			}
		}
	}
}

bool EDBInitSession(int ThdRef, int DBRef)
{
	::EnterCriticalSection(&m_DBOpenCs[DBRef]);
	if (DB[DBRef].SesId[ThdRef] == NULL) {
		if (!EDBOpenDatabase(ThdRef, DBRef, false, false)) {
			::LeaveCriticalSection(&m_DBOpenCs[DBRef]);
			return false;
		}
		if (!InitSessionTable(ThdRef, DBRef, SysId)) {
			::LeaveCriticalSection(&m_DBOpenCs[DBRef]);
			return false;
		}
		if (!InitSessionTable(ThdRef, DBRef, InfId)) {
			::LeaveCriticalSection(&m_DBOpenCs[DBRef]);
			return false;
		}
		if (!InitSessionTable(ThdRef, DBRef, DelId)) {
			::LeaveCriticalSection(&m_DBOpenCs[DBRef]);
			return false;
		}
		for (int TabIx = 0; TabIx <= DB[DBRef].TabCnt; TabIx++) {
			int StuNr = DB[DBRef].Tab[TabIx].StuNr;
			if (StuNr) {
				if (!InitSessionTable(ThdRef, DBRef, TabIx)) {
					::LeaveCriticalSection(&m_DBOpenCs[DBRef]);
					return false;
				}
			}
		}
	}

	UNALIGNED struct sComBuf *ComBuf;
	ComBuf = (struct sComBuf*)Thd[ThdRef].ComBuf;

	// Update Proc2DBRef table
	for (int TabIx = 0; TabIx < DB[DBRef].TabCnt; TabIx++) {
		int StuNr = DB[DBRef].Tab[TabIx].StuNr;
		if (StuNr) {
			Proc2DBRef[ComBuf->OrigId][StuNr] = (short int)DBRef;
			Proc2DBRefOpened[ComBuf->OrigId][StuNr] = true;
		}
	}
	::LeaveCriticalSection(&m_DBOpenCs[DBRef]);
	return true;
}

int ReOpenLastSysFile(int ThdRef)
{
	int ProcId, SysRef;
	UNALIGNED struct sComBuf *ComBuf;
	ComBuf = (struct sComBuf*)Thd[ThdRef].ComBuf;

	SysRef = -1;
	ProcId = ComBuf->OrigId;
	CString LastSysOpen;
	int PostNr = 1 + (ComBuf->OrigId / 5);
	int ScreenNr = ComBuf->OrigId % 5;
	int MaxPostNr = atol(theApp.iniFile.getKeyValue("PostCount", "JamaSettings"));
	if (PostNr >= 1 && PostNr <= MaxPostNr && ScreenNr >= 1 && ScreenNr <= 4) {
		CString PostSection, Key;
		PostSection.Format("Post-%03d_Settings", PostNr);
		Key.Format("Screen-%d_LastSysOpen", ScreenNr);
		LastSysOpen = theApp.iniFile.getKeyValue(Key, PostSection);
		CString cstr;
		cstr.Format("Reopen sys:%s for PostNr=%d/ScreenNr=%d", LastSysOpen, PostNr, ScreenNr);
		LogAdd(0, 1, cstr);
	}
	if (LastSysOpen.GetLength()) {
		SysRef = Proc2SysRef[ProcId] = SysOpen((char *)(LPCTSTR)LastSysOpen); // return -1 wanneer niet gevonden !
	}
	return SysRef;
}

int ReOpenOnTheFly(int ThdRef, int StuNr)
{
	int DBRef = -1, ProcId, SysRef;
	UNALIGNED struct sComBuf *ComBuf;
	ComBuf = (struct sComBuf*)Thd[ThdRef].ComBuf;

	ProcId = ComBuf->OrigId;
	SysRef = Proc2SysRef[ProcId];
	if (SysRef < 0 || SysRef >= MAX_SYSFILE) {
		SysRef = ReOpenLastSysFile(ThdRef);
	}
	if (SysRef >= 0 && SysRef < MAX_SYSFILE && Sys[SysRef].Name.GetLength()) {
		int i;
		for (i = 0; i < 120; i++) {
			if (!Sys[SysRef].PreMountBusyFlag) break;
			Sleep(500);
			pMainDlg->ProcessAllMessages();
		}
		if (i == 120) {
			LogAdd(1, 0, "[ReOpenOnTheFly] DB was attached but Pre-Mount was not done within 60 seconds, sys=", Sys[SysRef].Ext);
			return -1;
		}
		for (i = 0; i < 15; i++) {
			char FileName[20];
			if (JMSShuttingDown) continue;
			memcpy(FileName, Sys[SysRef].Buf + 300 + i * 17, 15);
			FileName[15] = 0;
			if (FileName[0] > ' ') {
				DBRef = FindDB(FileName);
				if (DBRef >= 0) EDBInitSession(ThdRef, DBRef);
			}
		}
		DBRef = Proc2DBRef[ProcId][StuNr];
	}
	return DBRef;
}

bool EDBCheckAndUpdateAndInit(int DBRef)
{
	bool ok = true;
	char buf[100];
	int len;

	if (!CheckAndUpdateTable(DBRef, SysId)) ok = false;
	if (!CheckAndUpdateTable(DBRef, InfId)) ok = false;
	if (!CheckAndUpdateTable(DBRef, DelId)) ok = false;

	// check version entry
	len = sizeof(buf);
	SysParmGet(DBRef, "Version", buf, &len);
	buf[len] = 0;
	if (buf[0] == 0) {
		CString cstr = "03.01";
		SysParmAdd(DBRef, "Version", (char *)(LPCTSTR)cstr, cstr.GetLength());
	}
	else if (strcmp("03.01", buf)) {
		LogAdd(22, 0, "*** Error : different version DB", buf);
		return false;
	}
	LogAdd(0, 2, "Version", buf);

	return ok;
}

bool ComposeKey(int DBRef, int StuNr, int KeyIx, char *Rec, char *KeyBuf)
{
	struct _pce_i *pce;
	int pceCnt;
	int i, len, RecNrLen, TabNr;
	char *s, *d, c;

	TabNr = DB[DBRef].Stu2Tab[StuNr];
	memset(KeyBuf, 0, DB[DBRef].Tab[TabNr].KeyInf[KeyIx].Len);
	pceCnt = DB[DBRef].Tab[TabNr].KeyInf[KeyIx].pceCnt;
	if (pceCnt == 0) return false;

	RecNrLen = DB[DBRef].Tab[TabNr].EleInf[1].FldLen;
	d = KeyBuf;
	pceCnt = DB[DBRef].Tab[TabNr].KeyInf[KeyIx].pceCnt;
	pce = DB[DBRef].Tab[TabNr].KeyInf[KeyIx].pce;
	for (i = 0; i < pceCnt; i++) {
		len = pce->len;
		s = &Rec[pce->off - RecNrLen];
		switch (pce->typ) {
		case 0:
			memcpy(d, s, pce->len);
			d += pce->len;
			break;
		case 1:
			while (len-- > 0) *d++ = ICTab[*(unsigned char *)s++];
			break;
		case 2:
			while (len-- > 0) {
				c = SBTab[*(unsigned char *)s++];
				if (c) *d++ = c;
			}
			break;
		case 3:
			while (len-- > 0) {
				c = ICSBTab[*(unsigned char *)s++];
				if (c) *d++ = c;
			}
			break;
		case 8:
			s += (len - 1);
			while (len-- > 0) *d++ = *s--;
			break;
		}
		pce++;
	}

	return true;
}

bool EDBGetRec(int DBRef, int StuNr, int RecNr, int *RecLen, unsigned char *Rec, double *pDateTime, short int *pChangedBy)
{
	int ThdRef = 0;
	int TabIx = DB[DBRef].Stu2Tab[StuNr];
	unsigned long retlen;
	JET_ERR _jeterr;

	JetCall(2801, JetSetCurrentIndex4(DB[DBRef].SesId[0], DB[DBRef].Tab[TabIx].Tid[ThdRef], "", (JET_INDEXID*)DB[DBRef].Tab[TabIx].Idx[StuRecIx].rgbIndexId[ThdRef], 0, 0));
	JetCall(2802, JetMakeKey(DB[DBRef].SesId[0], DB[DBRef].Tab[TabIx].Tid[ThdRef], &RecNr, sizeof(RecNr), JET_bitNewKey));
	_jeterr = JetSeek(DB[DBRef].SesId[0], DB[DBRef].Tab[TabIx].Tid[ThdRef], JET_bitSeekEQ);
	if (_jeterr != JET_errSuccess) return false;

	JetCall(2803, JetRetrieveColumn(DB[DBRef].SesId[0], DB[DBRef].Tab[TabIx].Tid[ThdRef], DB[DBRef].Tab[TabIx].Col[StuValId].Cid[ThdRef], Rec, BUF_LEN, &retlen, 0, 0));
	if (retlen > 0) *RecLen = retlen;
	else *RecLen = 0;
	JetCall(2804, JetRetrieveColumn(DB[DBRef].SesId[0], DB[DBRef].Tab[TabIx].Tid[ThdRef], DB[DBRef].Tab[TabIx].Col[StuDatId].Cid[ThdRef], pDateTime, DB[DBRef].Tab[TabIx].Col[StuDatId].Len, &retlen, 0, 0));
	JetCall(2804, JetRetrieveColumn(DB[DBRef].SesId[0], DB[DBRef].Tab[TabIx].Tid[ThdRef], DB[DBRef].Tab[TabIx].Col[StuChgId].Cid[ThdRef], pChangedBy, DB[DBRef].Tab[TabIx].Col[StuChgId].Len, &retlen, 0, 0));
	return true;
}

bool EDBAddRec(int DBRef, int StuNr, int RecNr, int RecLen, unsigned char *Rec, double UpdDateTime, short int ChangedBy)
{
	char KeyBuf[MAX_KEYS + 1][MAX_KEY_LEN];
	char RecBack[BUF_LEN];
	bool NewRecord;
	int i, KeyIx, ColNr, SeqNr, TabNr;
	JET_ERR _jeterr;

	TabNr = DB[DBRef].Stu2Tab[StuNr];
	JetCall(1603, JetBeginTransaction(DB[DBRef].SesId[0]));

	for (SeqNr = 0; SeqNr < 20; SeqNr++) {

		for (KeyIx = 1; KeyIx <= MAX_KEYS; KeyIx++) {
			memset(KeyBuf[KeyIx], 0, MAX_KEY_LEN);
			ComposeKey(DBRef, StuNr, KeyIx, (char *)Rec, KeyBuf[KeyIx]);
		}

		JetCall(1601, JetSetCurrentIndex4(DB[DBRef].SesId[0], DB[DBRef].Tab[TabNr].Tid[0], "", (JET_INDEXID*)DB[DBRef].Tab[TabNr].Idx[StuRecIx].rgbIndexId[0], 0, 0)); // ixRecNr
		JetCall(1602, JetMakeKey(DB[DBRef].SesId[0], DB[DBRef].Tab[TabNr].Tid[0], &RecNr, sizeof(RecNr), JET_bitNewKey));
		_jeterr = JetSeek(DB[DBRef].SesId[0], DB[DBRef].Tab[TabNr].Tid[0], JET_bitSeekEQ);

		NewRecord = false;
		if (_jeterr == JET_errRecordNotFound) NewRecord = true;

		if (NewRecord) {
			JetCall(1604, JetPrepareUpdate(DB[DBRef].SesId[0], DB[DBRef].Tab[TabNr].Tid[0], JET_prepInsert));
		}
		else {
			JetCall(1605, JetPrepareUpdate(DB[DBRef].SesId[0], DB[DBRef].Tab[TabNr].Tid[0], JET_prepReplace));
		}

		if (NewRecord) {
			JetCall(1606, JetSetColumn(DB[DBRef].SesId[0], DB[DBRef].Tab[TabNr].Tid[0], DB[DBRef].Tab[TabNr].Col[StuRecId].Cid[0], &RecNr, DB[DBRef].Tab[TabNr].Col[StuRecId].Len, 0, NULL));
		}
		JetCall(1607, JetSetColumn(DB[DBRef].SesId[0], DB[DBRef].Tab[TabNr].Tid[0], DB[DBRef].Tab[TabNr].Col[StuValId].Cid[0], Rec, RecLen, JET_bitSetOverwriteLV, NULL));

		for (KeyIx = 1; KeyIx <= MAX_KEYS; KeyIx++) {
			if (DB[DBRef].Tab[TabNr].KeyInf[KeyIx].Len) {
				ColNr = DB[DBRef].Tab[TabNr].KeyInf[KeyIx].ColIx;
				JetCall(1608, JetSetColumn(DB[DBRef].SesId[0], DB[DBRef].Tab[TabNr].Tid[0], DB[DBRef].Tab[TabNr].Col[ColNr].Cid[0], KeyBuf[KeyIx], DB[DBRef].Tab[TabNr].Col[ColNr].Len, 0, NULL));
			}
		}

		JetCall(1609, JetSetColumn(DB[DBRef].SesId[0], DB[DBRef].Tab[TabNr].Tid[0], DB[DBRef].Tab[TabNr].Col[SysDatId].Cid[0], &UpdDateTime, DB[DBRef].Tab[TabNr].Col[SysDatId].Len, 0, NULL));
		JetCall(1610, JetSetColumn(DB[DBRef].SesId[0], DB[DBRef].Tab[TabNr].Tid[0], DB[DBRef].Tab[TabNr].Col[StuChgId].Cid[0], &ChangedBy, DB[DBRef].Tab[TabNr].Col[StuChgId].Len, 0, NULL));

		_jeterr = JetUpdate(DB[DBRef].SesId[0], DB[DBRef].Tab[TabNr].Tid[0], NULL, 0, NULL);
		if (_jeterr == JET_errSuccess) break; // de record is toegevoegd

		if (SeqNr == 0) {
			CString cstr, hstr, tothstr;
			for (int j = 0; j < 30; j++) {
				if (j == RecLen) break;
				hstr.Format("%02X", Rec[j]);
				tothstr += hstr;
			}
			cstr.Format("DB=%s StuNr=%d RecNr=#%d Data=[%s]", DB[DBRef].Name, StuNr, RecNr, tothstr);
			LogAdd(0, 2, cstr);
			memcpy(RecBack, Rec, RecLen);
		}
		else memcpy(Rec, RecBack, RecLen); // to get back old name-field

		if ((StuNr >= 1 && StuNr <= 3) || StuNr == 6) { // KLT, LEV, GRB of ART
			if (SeqNr % 2 == 0) {
				short int RecNrLen = DB[DBRef].Tab[TabNr].EleInf[1].FldLen;
				char *pNam = (char *)&Rec[DB[DBRef].Tab[TabNr].EleInf[3].FldOffset - RecNrLen];
				short int Len = DB[DBRef].Tab[TabNr].EleInf[3].FldLen;
				for (i = 0; i < Len; i++) if (pNam[i] == 0) break;
				if (i == Len) i--;
				pNam[i] = 'A' + SeqNr / 2;
				pNam[i + 3] = ')';
				char _b[200];
				if (Len > (sizeof(_b) - 1)) Len = sizeof(_b) - 1;
				memcpy(_b, pNam, Len);
				_b[Len] = 0;
				LogAdd(0, 2, "Duplicate key, changed/retried name with", _b);
			}
			else {
				short int Len = DB[DBRef].Tab[TabNr].EleInf[2].FldLen;
				if (Len) {
					for (i = 0; i < Len; i++) if (Rec[i] == 0) break;
					if (i == Len) i--;
					Rec[i] = 'A' + SeqNr / 2;
					char _b[200];
					memcpy(_b, Rec, Len);
					_b[Len] = 0;
					LogAdd(0, 2, "Duplicate key, changed/retried codenr with", _b);
				}
			}
		}
		else {
			break;
		}

	}
	if (_jeterr != JET_errSuccess) { // is de status van de laatste JetUpdate()
		LogJet(1613, _jeterr, DB[DBRef].Name, DB[DBRef].Tab[TabNr].StructName);
	}
	JetCall(1611, JetCommitTransaction(DB[DBRef].SesId[0], JetCommitBits));

	return true;
}

//******************************************
// Beheer Table structuren
//******************************************

void SetTab(int DBRef, int TabIx, char* Nam)
{
	strcpy(DB[DBRef].Tab[TabIx].Nam, Nam);
	DB[DBRef].Tab[TabIx].Tid[0] = NULL;
	if ((TabIx + 1) > DB[DBRef].TabCnt) DB[DBRef].TabCnt = TabIx + 1;
}

void SetCol(int DBRef, int TabIx, int ColIx, char* Nam, JET_COLTYP	Typ, int Len)
{
	strcpy(DB[DBRef].Tab[TabIx].Col[ColIx].Nam, Nam);
	DB[DBRef].Tab[TabIx].Col[ColIx].Typ = Typ;
	DB[DBRef].Tab[TabIx].Col[ColIx].Len = Len;
	DB[DBRef].Tab[TabIx].Col[ColIx].Cid[0] = NULL;
}

void SetKey(int DBRef, int TabIx, int IdxIx, char* Nam, char* KeyStr)
{
	int len;

	for (len = 1; len < MAX_SZKEY; len++) {
		if (KeyStr[len - 1] == 0 && KeyStr[len] == 0) {
			len++;
			break;
		}
	}
	strcpy(DB[DBRef].Tab[TabIx].Idx[IdxIx].Nam, Nam);
	memset(DB[DBRef].Tab[TabIx].Idx[IdxIx].rgbIndexId[0], 0, sizeof(DB[0].Tab[0].Idx[0].rgbIndexId[0]));
	memcpy(DB[DBRef].Tab[TabIx].Idx[IdxIx].szKey, KeyStr, len);
}

//******************************************
// FSD Functions
//******************************************

void AnalyseFSD(int DBRef)
{
	int ix, i, j, EleIx, len, stucnt, sturef[50], StuRef;
	char *pool_, *pool_fsd;
	int max_recs = MAX_RECS;
	CFile file;
	struct _stu_i *stu_i;
	struct _key_i *key_i;
	struct _pce_i *pce_i;
	struct _namhdr *namhdr;
	struct _fldhdr *fldhdr;

	pool_fsd = Fsd[DBRef].buf;
	pool_ = pool_fsd;

	ix = 0; stucnt = 0;
	FOREVER{
	stu_i = (struct _stu_i *)&pool_fsd[ix];
	if (!stu_i->len) break;
		StuRef = stu_i->ref;
		int TabIx = DB[DBRef].TabCnt++;
		DB[DBRef].Tab[TabIx].StuNr = StuRef;
		DB[DBRef].Stu2Tab[StuRef] = TabIx;
	if (JMSVersion == 'L' || JMSVersion == 'M') {
	  CString cstr = theApp.iniFile.getKeyValue("DBMargin","JamaSettings");
	  int DBMargin = atol(cstr);
	  switch (DBMargin) {
		case 1:  max_recs = 130000; break;
		case 2:  max_recs = 127500; break;
		case 3:  max_recs = 125000; break;
		case 4:  max_recs = 120000; break;
		case 5:  max_recs = 110000; break;
		default: max_recs = 100000; break;
	  }
	  if (!StdInMono && JMSVersion == 'M') {
				max_recs /= 2;
				if (max_recs < 60000) max_recs = 60000;
			}
	}
	DB[DBRef].Tab[TabIx].MaxRec = max_recs;
	if (StuRef == 1 || StuRef == 2) DB[DBRef].Tab[TabIx].MaxRec = 30000;
		if (StuRef == 3) DB[DBRef].Tab[TabIx].MaxRec = 5000;

		Fsd[DBRef].StuNr[Fsd[DBRef].StuMax] = StuRef;
		DB[DBRef].Tab[TabIx].FasStu_i = stu_i;
		DB[DBRef].Tab[TabIx].FasType = stu_i->typ;
		sturef[stucnt] = StuRef;
		if (stucnt == MAX_STRUCT_FAS) {
			LogAdd(7,0,"To many structures in one FSD =",MAX_STRUCT_FAS);
		}
		else {
			stucnt++;
			Fsd[DBRef].StuMax++;
		}
		ix += stu_i->len;
	}

	ix += 2;

	for (j = 0; j < stucnt; j++) {
		fldhdr = (struct _fldhdr *)&pool_fsd[ix];
		//TabInf[j].EleCnt = fldhdr->elecnt;
		i = ix + 16; EleIx = 1;  // 16 is emprisch bepaald (owv dummies)
		int FldOffset = 0;
		StuRef = sturef[j];
		int TabIx = DB[DBRef].Stu2Tab[StuRef];
		DB[DBRef].Tab[TabIx].StructLen = 0;
		FOREVER{	  // read desc
		  DB[DBRef].Tab[TabIx].EleInf[EleIx].Desc = (unsigned char *)&pool_fsd[i];
			if (pool_fsd[i + 1] & 0xC0) { // not dummy, could be input,output or update field
				int FldType = DB[DBRef].Tab[TabIx].EleInf[EleIx].FldType = (pool_fsd[i + 1] & 0x38) / 0x08;
				switch (FldType) {
					case FLD_DATE:	DB[DBRef].Tab[TabIx].EleInf[EleIx].FldLen = 2; break;
					case FLD_BTW:		DB[DBRef].Tab[TabIx].EleInf[EleIx].FldLen = 4; break;
					case FLD_GRB:		DB[DBRef].Tab[TabIx].EleInf[EleIx].FldLen = 4; break;
					case FLD_REK:		DB[DBRef].Tab[TabIx].EleInf[EleIx].FldLen = 5; break;
					case FLD_STRING:DB[DBRef].Tab[TabIx].EleInf[EleIx].FldLen = *(short int *)&pool_fsd[i + 2]; break;
					case FLD_NUM:
						int FldTypeEx = DB[DBRef].Tab[TabIx].EleInf[EleIx].FldTypeEx = (pool_fsd[i + 1] & 0x07);
						switch (FldTypeEx) {
							case FLD_EX_2U:
							case FLD_EX_2S:
								DB[DBRef].Tab[TabIx].EleInf[EleIx].FldLen = 2;
								break;
							case FLD_EX_4S:
							case FLD_EX_4U:
							case FLD_EX_4F:
								DB[DBRef].Tab[TabIx].EleInf[EleIx].FldLen = 4;
								break;
							case FLD_EX_8F:
								DB[DBRef].Tab[TabIx].EleInf[EleIx].FldLen = 8;
								break;
						}
						break;
				}
				DB[DBRef].Tab[TabIx].EleInf[EleIx].FldOffset = FldOffset;
				FldOffset += DB[DBRef].Tab[TabIx].EleInf[EleIx].FldLen;
				DB[DBRef].Tab[TabIx].StructLen += DB[DBRef].Tab[TabIx].EleInf[EleIx].FldLen;
			}
			len = *(unsigned char *)&pool_fsd[i];
			if (len == 0) break;
			i += len;
			if (i >= (ix + fldhdr->elelen)) break;
			EleIx++;
		}
		DB[DBRef].Tab[TabIx].EleCnt = EleIx;
		ix += fldhdr->len;

		namhdr = (struct _namhdr *)&pool_fsd[ix];
		DB[DBRef].Tab[TabIx].StructName = &namhdr->naam;
		i = ix + 2; EleIx = 0;
		FOREVER{   // read names
			while (pool_fsd[i] != 0) i++;
			i++;
			if (pool_fsd[i] == 0) {
				DB[DBRef].Tab[TabIx].EleCnt = EleIx;
				break;
			}
			DB[DBRef].Tab[TabIx].EleInf[++EleIx].Name = &pool_fsd[i];
		}
		ix += namhdr->len;
	}

	// Read KEY-info (first fill other info, these is needed !

	ix = 0;
	int keynr, KeyIx;
	FOREVER{
	stu_i = (struct _stu_i *)&pool_fsd[ix];
	if (!stu_i->len) break;
	StuRef = stu_i->ref;
		int TabIx = DB[DBRef].Stu2Tab[StuRef];

		int kix = ix;
		for (KeyIx = 1; KeyIx <= MAX_KEYS; KeyIx++) {
			key_i = (struct _key_i *)&pool_fsd[kix + sizeof(struct _stu_i)];
			if (key_i->len == 0) break;
			keynr = key_i->nr;
			pce_i = (struct _pce_i *)&pool_fsd[kix + sizeof(struct _stu_i) + sizeof(struct _key_i)];
			DB[DBRef].Tab[TabIx].KeyInf[KeyIx].Nr = keynr;
			DB[DBRef].Tab[TabIx].KeyInf[KeyIx].pce = pce_i;
			DB[DBRef].Tab[TabIx].KeyInf[KeyIx].Typ = key_i->typ;
			DB[DBRef].Tab[TabIx].KeyInf[KeyIx].pceCnt = key_i->num;
			DB[DBRef].Tab[TabIx].KeyInf[KeyIx].Len = 0;
			for (j = 0; j < key_i->num; j++) {
			DB[DBRef].Tab[TabIx].KeyInf[KeyIx].Len += pce_i->len;
				pce_i++;
			}
			kix += key_i->len;
		}
		DB[DBRef].Tab[TabIx].KeyMax = KeyIx;
		CString cstr;
		cstr.Format("Found struct %d (%s), with %d extra keys",StuRef,DB[DBRef].Tab[TabIx].StructName,KeyIx - 1);
		LogAdd(0,2,cstr);
		ix += stu_i->len;
	}

	int StuNr, TabNr, ColNr, IdxNr, l1;
	char b1[20], b2[20];
	for (TabNr = 0; TabNr < DB[DBRef].TabCnt; TabNr++) {
		StuNr = DB[DBRef].Tab[TabNr].StuNr;
		if (StuNr == 0) continue;

		sprintf_s(DB[DBRef].Tab[TabNr].Nam, sizeof(DB[0].Tab[0].Nam), "Stu-%03d", StuNr);
		for (ColNr = 0; ColNr < CL_MAX; ColNr++) {
			if (!DB[DBRef].Tab[StuId].Col[ColNr].Nam[0]) break;
			DB[DBRef].Tab[TabNr].Col[ColNr].Len = DB[DBRef].Tab[StuId].Col[ColNr].Len;
			DB[DBRef].Tab[TabNr].Col[ColNr].Typ = DB[DBRef].Tab[StuId].Col[ColNr].Typ;
			strcpy(DB[DBRef].Tab[TabNr].Col[ColNr].Nam, DB[DBRef].Tab[StuId].Col[ColNr].Nam);
		}
		// copy key0 => recnr
		for (IdxNr = 0; IdxNr < CL_MAX; IdxNr++) {
			if (!DB[DBRef].Tab[StuId].Idx[IdxNr].Nam[0]) continue;
			strcpy(DB[DBRef].Tab[TabNr].Idx[IdxNr].Nam, DB[DBRef].Tab[StuId].Idx[IdxNr].Nam);
			memcpy(DB[DBRef].Tab[TabNr].Idx[IdxNr].szKey, DB[DBRef].Tab[StuId].Idx[IdxNr].szKey, MAX_SZKEY);
		}
		// add extra key-fields/columns and for each an index
		for (i = 1; i <= MAX_KEYS; i++) {
			l1 = DB[DBRef].Tab[TabNr].KeyInf[i].Len;
			if (l1 == 0) continue;

			sprintf_s(b1, sizeof(b1), "+Key-%02d", DB[DBRef].Tab[TabNr].KeyInf[i].Nr);
			b1[strlen(b1) + 1] = 0; // extra 0 nodig !
			DB[DBRef].Tab[TabNr].KeyInf[i].ColIx = ColNr;
			SetCol(DBRef, TabNr, ColNr++, &b1[1], JET_coltypBinary, l1);
			sprintf_s(b2, sizeof(b2), "ixKey-%02d", DB[DBRef].Tab[TabNr].KeyInf[i].Nr);
			SetKey(DBRef, TabNr, i, b2, b1);
		}
	}
}

bool ProcessInternalFsd(int DBRef)
{
	int vallen;
	CString cstr;
	char *valbuf = new char[MAX_SYSPARM_LEN];
	bool ResFileFlag = false;

	cstr = DB[DBRef].Name;
	if (cstr.GetLength() >= 11) {
		CString ext = cstr.Mid(7, 4);
		if (cstr.GetAt(3) == '.' && ext.CompareNoCase(".res") == 0) ResFileFlag = true;
	}

	vallen = MAX_SYSPARM_LEN;
	if (!SysParmGet(DBRef, "FSD", valbuf, &vallen)) {
		LogAdd(86, 0, "No FSD information in FAS-file", DB[DBRef].Name);
		delete valbuf;
		return false;
	}
	LogAdd(0, 1, "Processing internal FSD, length", vallen);
	Fsd[DBRef].buf = new char[vallen + 10];
	memcpy(Fsd[DBRef].buf, valbuf, vallen);
	Fsd[DBRef].len = vallen;
	Fsd[DBRef].buf[vallen] = 0; Fsd[DBRef].buf[vallen + 1] = 0;

	CFile FsdFile;
	CString FsdName = PathFSD + DB[DBRef].Name + ".fsd";
	bool FsdChanged = true;
	if (FsdFile.Open(FsdName, CFile::modeRead, NULL)) {
		if (FsdFile.GetLength() == vallen) {
			FsdFile.Read(valbuf, vallen);
			if (memcmp(Fsd[DBRef].buf, valbuf, vallen) == 0) {
				FILETIME LastWriteTime;
				GetFileTime(FsdFile.m_hFile, NULL, NULL, &LastWriteTime);
				TIME_ZONE_INFORMATION TimeZoneInfo;
				GetTimeZoneInformation(&TimeZoneInfo);
				// Convert local time to UTC.
				SYSTEMTIME localTime = { 0 }, systemTime = { 0 };
				FileTimeToSystemTime(&LastWriteTime, &systemTime);
				SystemTimeToTzSpecificLocalTime(&TimeZoneInfo, &systemTime, &localTime);
				//FileTime must be in UTC format (therfor convertion)
				COleDateTime dt(localTime);
				Fsd[DBRef].DateTimeUpdated = dt.operator double();
				FsdChanged = false;
			}
		}
		FsdFile.Close();
	}

	if (FsdChanged) {
		Fsd[DBRef].DateTimeUpdated = COleDateTime::GetCurrentTime().operator double();
		if (FsdFile.Open(FsdName, CFile::modeCreate | CFile::modeWrite, NULL)) {
			FsdFile.Write(valbuf, vallen);
			FsdFile.Close();
		}
		Fsd[DBRef].Updated = true;
	}

	AnalyseFSD(DBRef);
	delete valbuf;
	return true;
}

void ImportFsd(int DBRef)
{
	CFile FsdFile;
	long len;
	char *_fsd = new char[LEN_FSD];
	CString fsdName;

	// probeer eerst of xxx.fas.fsd bestaat in de pathFSD
	fsdName = PathFSD + DB[DBRef].Name + ".fsd";
	if (!FsdFile.Open(fsdName, CFile::modeRead, 0)) { // als die file niet bestaat, neem dan xxx.fsd in de jama-dir
		fsdName = PathProg + DB[DBRef].Name;
		int i = fsdName.ReverseFind('.');
		fsdName = fsdName.Left(i) + ".fsd";
		if (!FsdFile.Open(fsdName, CFile::modeRead, 0)) {
			LogAdd(34, 0, "No FSD-file found for", DB[DBRef].NamePath);
			return;
		}
	}
	len = FsdFile.Read(_fsd, LEN_FSD);
	FsdFile.Close();
	SysParmAdd(DBRef, "FSD", _fsd, len);
	delete _fsd;
}


////////////////////////////////////////////
//  Create FSD
////////////////////////////////////////////

char txtdt[29] = "00000 xx/xx/xx (c) Jamadata\32";

struct _key_o {
	short unsigned len;
	short unsigned ref;
	short unsigned typ;
	short unsigned num;
	short unsigned hniv;
};

struct _pce_o {  // 
	short unsigned typ;
	short unsigned off;
	short unsigned len;
};

void CalcFasFileParms(int DBRef) // was de ClearFF() uit de FasCre.c ...
{
	int k, qkeys, StuNr, fldrecs;
	long recs;
	struct _fldhdr *fldhdr;
	struct _stu_i *stu_i;
	struct _key_i *key_i;
	struct _namhdr *namhdr;

	qkeys = 0;
	recs = 1; // 1 header rec

	// bereken aantal sektoren ###

	for (int TabIx = 0; TabIx < DB[DBRef].TabCnt; TabIx++) {
		StuNr = DB[DBRef].Tab[TabIx].StuNr;
		if (StuNr == 0) continue;
		recs += (((DB[DBRef].Tab[TabIx].LastRec + EXTRA_FREE_RECS) * (DB[DBRef].Tab[TabIx].StructLen - DB[DBRef].Tab[TabIx].EleInf[1].FldLen + 1)) + 512 - 1) / 512; // # datarecords
	}

	stu_i = (struct _stu_i *)Fsd[DBRef].buf;
	while (stu_i->len) {
		stu_i = (struct _stu_i *)((char *)stu_i + stu_i->len);
	}

	Fsd[DBRef].FldHdr1 = ((char *)stu_i + 2); // om de stu_i->len==0 te skippen

	fldhdr = (struct _fldhdr *)Fsd[DBRef].FldHdr1;
	fldrecs = 0;
	while (fldhdr->len) {
		k = fldhdr->len;
		namhdr = (struct _namhdr *)((char *)fldhdr + fldhdr->len);
		k += namhdr->len;
		fldrecs += (1 + ((k - 1) / 512));
		fldhdr = (struct _fldhdr *)((char *)namhdr + namhdr->len);
	}
	recs += fldrecs;

	Fsd[DBRef].RecHD = recs;/* hdr+data (zonder keys) */
	Fsd[DBRef].FldRecs = fldrecs;

	stu_i = (struct _stu_i*)Fsd[DBRef].buf;
	FOREVER{
		if (!stu_i->len)break;
		key_i = (struct _key_i*)((char *)stu_i + sizeof(struct _stu_i));
		FOREVER{
			if (!key_i->len)break;
			int TabIx = DB[DBRef].Stu2Tab[stu_i->ref];
			qkeys += ((DB[DBRef].Tab[TabIx].LastRec + EXTRA_FREE_RECS) * 12L) / 512 + 4;
			key_i = (struct _key_i*)((char *)key_i + key_i->len);
		}
		stu_i = (struct _stu_i*)((char *)stu_i + stu_i->len);
	}
	recs += qkeys;

	Fsd[DBRef].RecTot = recs;
}

//******************************************
// Read FAS-bestanden & import
//******************************************

#define	FAS_REQ	6

struct _hdr {
	unsigned char  typ;
	unsigned char  vers;
	unsigned char  dtvrs[28];
	short unsigned flags;
	short unsigned cntrl2;
	short unsigned keyst;
	short unsigned last;
	short unsigned init;
	short unsigned delnrkey;
	short unsigned dum1;
	short unsigned dum2;
} *hdr;

struct _stu {
	short unsigned len;
	short unsigned ref;
	short unsigned rlen;
	short unsigned flags;
	short unsigned mx;
	short unsigned used;
	short unsigned del;/* record # */
	short unsigned sect1;/* sector # */
	short unsigned q_del;/* delete cnt */
	short unsigned sectfld;
	short unsigned dum1;
};

bool ExportFas(int DBRef)
{
	int k, len, StuRef, locat, locatfld, qrecs;
	unsigned long retlen;
	CFile FasFile;
	CString FasFileName;
	unsigned char FasHeader[512];
	unsigned char RecBuf[BUF_LEN + 10];
	struct _hdr *hdr_o;
	struct _stu *stu_o;
	struct _stu_i *stu_i;
	struct _fldhdr *fldhdr;
	struct _namhdr *namhdr;
	struct _key_i *key_i;
	struct _key_o *key_o;
	struct _pce_i *pce_i;
	struct _pce_o *pce_o;
	int RecNr;
	JET_ERR _jeterr;

	CalcFasFileParms(DBRef);

	FasFileName = PathProg + DB[DBRef].Name;
	FasFileName.MakeUpper();
	FasFileName += ".exp";

	LogAdd(0, 0, "Exporting FAS", (char *)(LPCTSTR)FasFileName);

	_unlink(FasFileName);
	if (!FasFile.Open(FasFileName, CFile::modeReadWrite | CFile::modeCreate, 0)) {
		LogAdd(0, 0, "Cannot create file !");
		return false;
	}

	// write file with needed len and filled with 0xFF
	int tmpbufsize = 512 * 128;
	char* tmpbuf = new char[tmpbufsize];
	if (tmpbuf == NULL) {
		LogAdd(0, 0, "Cannot get memoryblock for export, size", tmpbufsize);
		return false;
	}
	memset(tmpbuf, 0xFF, tmpbufsize);
	long tot_len = Fsd[DBRef].RecTot * 512L;
	long len_;
	while (tot_len) {
		if (tot_len > tmpbufsize) len_ = tmpbufsize; else len_ = tot_len;
		FasFile.Write(tmpbuf, len_);
		tot_len -= len_;
	}
	delete tmpbuf;
	tmpbuf = NULL;

	// fill in header
	memset(FasHeader, 0xFF, sizeof(FasHeader));
	stu_i = (struct _stu_i*)Fsd[DBRef].buf;
	hdr_o = (struct _hdr*)FasHeader;
	hdr_o->typ = 0xFA;
	hdr_o->vers = 2;
	SYSTEMTIME systime;
	GetLocalTime(&systime);
	sprintf(txtdt + 6, "%02d", systime.wDay); txtdt[8] = '/';
	sprintf(txtdt + 9, "%02d", systime.wMonth); txtdt[11] = '/';
	sprintf(txtdt + 12, "%02d", systime.wYear % 100); txtdt[14] = ' ';
	for (k = 0; k < 28; k++)hdr_o->dtvrs[k] = txtdt[k];
	hdr_o->flags = 0x0000;
	hdr_o->cntrl2 = 0x0000;
	hdr_o->keyst = Fsd[DBRef].RecHD;
	hdr_o->last = Fsd[DBRef].RecHD - 1;
	hdr_o->init = Fsd[DBRef].RecTot;
	hdr_o->delnrkey = 0x0000;
	hdr_o->dum1 = 0x0000;
	hdr_o->dum2 = 0x0000;

	// add structure info to header 

	stu_o = (struct _stu*)((char *)hdr_o + sizeof(struct _hdr));
	locatfld = 1;
	locat = 1 + Fsd[DBRef].FldRecs;
	fldhdr = (struct _fldhdr *)Fsd[DBRef].FldHdr1;
	FOREVER{/*fill strukt*/
		if (stu_i->len == 0) {
			stu_o->len = 0;
			break;
		}
		int TabIx = DB[DBRef].Stu2Tab[stu_i->ref];
		if (DB[DBRef].Tab[TabIx].LastRec > 65000) {
			LogAdd(0,0,"Export impossible. Too many records in ",DB[DBRef].Tab[TabIx].StructName);
			FasFile.Close();
			_unlink(FasFileName);
			return false;
		}
		stu_o->len = sizeof(struct _stu); // ptrsub(stu_o+1,stu_o); is dat correct ???
		stu_o->ref = stu_i->ref;
		stu_o->rlen = stu_i->rlen; // dit stond er vroeger bij, maar volgens mij hoort dat niet !! -DB[DBRef].Tab[TabIx].EleInf[1].FldLen;
		stu_o->flags = stu_i->typ;
		qrecs = ((DB[DBRef].Tab[TabIx].LastRec + EXTRA_FREE_RECS) * (stu_o->rlen + 1L) + 512 - 1) / 512;
		stu_o->sect1 = locat; locat += qrecs;
		stu_o->mx = (unsigned short)((int)((qrecs * 512L) / (stu_o->rlen + 1)));
		stu_o->used = DB[DBRef].Tab[TabIx].LastRec;
		stu_o->del = 0xFFFF;
		stu_o->q_del = 0x0000;
		if (Fsd[DBRef].FldRecs) stu_o->sectfld = locatfld;
		else stu_o->sectfld = 0;
		stu_o->dum1 = 0x0000;
		key_i = (struct _key_i*)((char *)stu_i + sizeof(struct _stu_i));
		key_o = (struct _key_o*)((char *)stu_o + sizeof(struct _stu));
		FOREVER{/*fill key*/
			if (key_i->len == 0) {
				key_o->len = 0;
				stu_o->len += 2;
				break;
			}
			stu_o->len += sizeof(struct _key_o);
			key_o->len = sizeof(struct _key_o);
			key_o->ref = key_i->nr;
			key_o->typ = key_i->typ;
			key_o->num = key_i->num;
			key_o->hniv = 0;
			pce_i = (struct _pce_i*)((char *)key_i + sizeof(struct _key_i));
			pce_o = (struct _pce_o*)((char *)key_o + sizeof(struct _key_o));
			k = key_o->num;
			while (k--) {/*fill piece*/
				pce_o->typ = pce_i->typ;
				pce_o->off = pce_i->off - 2;
				pce_o->len = pce_i->len;
				stu_o->len += sizeof(struct _pce_o);
				key_o->len += sizeof(struct _pce_o);
				pce_i++; pce_o++;
			}
			key_i = (struct _key_i*)pce_i;
			key_o = (struct _key_o*)pce_o;
		}
		stu_i = (struct _stu_i*) ((char *)key_i + 2);
		stu_o = (struct _stu*) ((char *)key_o + 2);

		len = fldhdr->len;
		namhdr = (struct _namhdr *)((char *)fldhdr + fldhdr->len);
		len += namhdr->len;
		if (len > 0) {
			FasFile.Seek((long)locatfld * 512L,0);
			FasFile.Write(fldhdr,len);
			locatfld += (1 + (len - 1) / 512);
			fldhdr = (struct _fldhdr *)((char *)fldhdr + len);
		}
	}

	FasFile.Seek(0L, 0);
	FasFile.Write(FasHeader, 512);

	for (int TabIx = 0; TabIx < Fsd[DBRef].StuMax; TabIx++) {
		StuRef = Fsd[DBRef].StuNr[TabIx];

		hdr_o = (struct _hdr*)FasHeader;
		stu_o = (struct _stu*)((char *)hdr_o + sizeof(struct _hdr));

		while (stu_o->len) {
			if (stu_o->ref == StuRef) break;
			stu_o = (struct _stu*)((char *)stu_o + stu_o->len);
		}
		if (stu_o->len == 0) continue;

		FasFile.Seek(stu_o->sect1 * 512, FILE_BEGIN);
		memset(RecBuf, 0xFF, sizeof(RecBuf) - 5);
		for (RecNr = 1; RecNr <= stu_o->mx; RecNr++) {
			FasFile.Write(RecBuf, stu_o->rlen + 1);
		}

		// int TabIx=DB[DBRef].Stu2Tab[StuRef]; MVG updated 170622 denk dat dit fout was (compiler error !) en overbodig
		RecNr = 1;
		JetCall(2201, JetSetCurrentIndex4(DB[DBRef].SesId[0], DB[DBRef].Tab[TabIx].Tid[0], "", (JET_INDEXID*)DB[DBRef].Tab[TabIx].Idx[StuRecIx].rgbIndexId[0], 0, 0));
		JetCall(2202, JetMakeKey(DB[DBRef].SesId[0], DB[DBRef].Tab[TabIx].Tid[0], &RecNr, sizeof(RecNr), JET_bitNewKey));
		_jeterr = JetSeek(DB[DBRef].SesId[0], DB[DBRef].Tab[TabIx].Tid[0], JET_bitSeekGE);
		while (_jeterr == JET_wrnSeekNotEqual || _jeterr == JET_errSuccess) {
			JetCall(2203, JetRetrieveColumn(DB[DBRef].SesId[0], DB[DBRef].Tab[TabIx].Tid[0], DB[DBRef].Tab[TabIx].Col[StuRecId].Cid[0], &RecNr, DB[DBRef].Tab[TabIx].Col[StuRecId].Len, &retlen, 0, 0));
			JetCall(2204, JetRetrieveColumn(DB[DBRef].SesId[0], DB[DBRef].Tab[TabIx].Tid[0], DB[DBRef].Tab[TabIx].Col[StuValId].Cid[0], &RecBuf[1], BUF_LEN, &retlen, 0, 0));
			RecBuf[0] = 0xFC;
			FasFile.Seek(stu_o->sect1 * 512 + (RecNr - 1)*(stu_o->rlen + 1), FILE_BEGIN);
			FasFile.Write(RecBuf, stu_o->rlen + 1);
			_jeterr = JetMove(DB[DBRef].SesId[0], DB[DBRef].Tab[TabIx].Tid[0], JET_MoveNext, 0);
		}
	}

	hdr_o->flags = 0xF000; // abnormal etc. ...
	FasFile.Seek(0, FILE_BEGIN);
	FasFile.Write(FasHeader, sizeof(FasHeader));
	FasFile.Close();
	return true;
}

bool CreateFsdFromFas(char *FasFileName)
{
	CFile FasFile, FsdFile;
	CString FasFilePath;
	int i, pos;
	unsigned short *psi;
	long len;
	char* FasHeader = new char[LEN_FSD + 5000];
	char* FsdBuf = new char[LEN_FSD];
	int FsdBufLen;
	char* FsdDesc = new char[LEN_FSD];
	int FsdDescLen;
	struct _hdr *hdr_fas;
	struct _stu *stu_fas;
	struct _key_o *key_fas;
	struct _pce_o *pce_fas;
	struct _stu_i *stu_fsd;
	struct _key_i *key_fsd;
	struct _pce_i *pce_fsd;
	bool retflag = true;

	FasFilePath = PathDB + FasFileName;
	if (FALSE == FasFile.Open(FasFilePath, CFile::modeRead, 0)) {
		LogAdd(8, 0, "Cannot open FAS-file", FasFilePath);
		return false;
	}
	LogAdd(0, 1, "Creating FSD from FAS-file", FasFilePath);
	len = (long)FasFile.GetLength();
	FasFile.Read(FasHeader, LEN_FSD + 5000);
	FasFile.Close();

	CString fsdName = PathFSD + FasFileName + ".fsd";
	FsdBufLen = 0;
	FsdDescLen = 0;
	hdr_fas = (struct _hdr*)FasHeader;
	stu_fas = (struct _stu*)(hdr_fas + 1);
	stu_fsd = (struct _stu_i*) FsdBuf;

	if (stu_fas->sect1 == 1) {
		LogAdd(38, 0, "Cannot create FSD! Missing FLD-info in OLD-layout FAS-file", FasFileName);
		CString ManFsdName = fsdName + ".MAN";      // eerste alternatief
		CString NewFsdName = PathProg + FasFileName;  // default .fsd voor nieuwe FAS-files ...
		int i = NewFsdName.ReverseFind('.');
		NewFsdName = NewFsdName.Left(i) + ".fsd";
		if (GetFileAttributes(ManFsdName) != INVALID_FILE_ATTRIBUTES) {
			CopyFile(ManFsdName, fsdName, FALSE);
			LogAdd(0, 0, "Copied FSD-info from manual added FSD-file", ManFsdName);
		}
		else if (GetFileAttributes(NewFsdName) != INVALID_FILE_ATTRIBUTES) {
			// neem dan de .FSD uit de PROG-dir (dat is de nieuwe, wellicht is die nu nog ok). Zo dat niet klopt zien we dat bij de ShadowCopy (die een ander REClen terugvindt).
			CopyFile(NewFsdName, fsdName, FALSE);
			LogAdd(0, 0, "Copied FSD-info from newly created default FSD-file", NewFsdName);
		}
		else retflag = false;
	}
	else {
		while (stu_fas->len) {
			stu_fsd->len = sizeof(struct _stu_i);
			stu_fsd->ref = stu_fas->ref;
			stu_fsd->rlen = stu_fas->rlen;
			stu_fsd->typ = stu_fas->flags;
			stu_fsd->recs = stu_fas->mx;
			key_fsd = (struct _key_i *)(stu_fsd + 1); key_fas = (struct _key_o *)(stu_fas + 1);
			while (key_fas->len) {
				key_fsd->len = sizeof(struct _key_i);
				key_fsd->nr = key_fas->ref;
				key_fsd->typ = key_fas->typ;
				key_fsd->num = key_fas->num;
				pce_fsd = (struct _pce_i *)(key_fsd + 1); pce_fas = (struct _pce_o *)(key_fas + 1);
				for (i = 0; i < key_fas->num; i++) {
					pce_fsd->typ = pce_fas->typ;
					pce_fsd->off = pce_fas->off + 2; // RecNr lengte zou altijd 2 moeten zijn (unsigned short int) !
					pce_fsd->len = pce_fas->len;
					key_fsd->len += sizeof(struct _pce_i);
					pce_fsd++; pce_fas++;
				}
				stu_fsd->len += key_fsd->len;
				key_fsd = (struct _key_i*)((char *)key_fsd + key_fsd->len);
				key_fas = (struct _key_o*)((char *)key_fas + key_fas->len);
			}
			key_fsd->len = 0;
			stu_fsd->len += 2;
			FsdBufLen += stu_fsd->len;

			pos = 512 * stu_fas->sectfld;
			psi = (unsigned short *)&FasHeader[pos];
			memcpy(&FsdDesc[FsdDescLen], &FasHeader[pos], *psi);
			FsdDescLen += *psi;
			pos += *psi;
			psi = (unsigned short *)&FasHeader[pos];
			memcpy(&FsdDesc[FsdDescLen], &FasHeader[pos], *psi);
			FsdDescLen += *psi;

			stu_fsd = (struct _stu_i*)((char *)stu_fsd + stu_fsd->len);
			stu_fas = (struct _stu*) ((char *)stu_fas + stu_fas->len);
		}
		stu_fsd->len = 0;
		FsdBufLen += 2;
		FsdDesc[FsdDescLen++] = 0;
		FsdDesc[FsdDescLen++] = 0;
		FsdFile.Open(fsdName, CFile::modeReadWrite | CFile::modeCreate, 0);
		FsdFile.Write(FsdBuf, FsdBufLen);
		FsdFile.Write(FsdDesc, FsdDescLen);
		FsdFile.Close();
	}

	delete FasHeader;
	delete FsdBuf;
	delete FsdDesc;

	return retflag;
}



bool ImportFas(char *FasFileName)/* read .fas & import data-records */
{
	CFile FasFile;
	long len;
	char FasHeader[512];
	unsigned char RecBuf[BUF_LEN + 10];
	struct _hdr *hdr_i;
	struct _stu *stu_i;
	int RecNr, RecCnt, StuLenInFsd;
	CString cstr;

	LogAdd(0, 0, "Converting OLD to NEW version", FasFileName);
	CString FasFilePath = PathDB + FasFileName;
	if (!CreateFsdFromFas((char *)(LPCTSTR)FasFileName)) {    // komt in PathFSD
		LogAdd(33, 0, "Cannot create FSD-file for", FasFilePath);
		return false;
	}

	CString OldVersionPath = FasFilePath;
	OldVersionPath += ".OLD";
	_unlink(OldVersionPath);
	MoveFile(FasFilePath, OldVersionPath);

	if (FALSE == FasFile.Open(OldVersionPath, CFile::modeRead, 0)) {
		LogAdd(8, 0, "Cannot open FAS-file", (char *)(LPCTSTR)cstr);
		return false;
	}

	int DBRef = MountDB(FasFileName, true, true);

	len = (long)FasFile.GetLength();
	FasFile.Read(FasHeader, sizeof(FasHeader));
	hdr_i = (struct _hdr*)FasHeader;
	stu_i = (struct _stu*)(hdr_i + 1);

	double now = COleDateTime::GetCurrentTime().operator double();

	while (stu_i->len) {
		int TabIx = DB[DBRef].Stu2Tab[stu_i->ref];
		StuLenInFsd = DB[DBRef].Tab[TabIx].StructLen - 2; // in de oude fassen moet dit altijd 2 zijn ... Maar DB[DBRef].Tab[TabIx].EleInf[1].FldLen -> gaf soms 4 (testdata die res2fas kregen ?)
		if (StuLenInFsd != stu_i->rlen) {
			LogAdd(20, 0, "NO import, length in FAS differs from FSD in structure", stu_i->ref);
		}
		else {
			FasFile.Seek(stu_i->sect1 * 512, FILE_BEGIN);
			RecCnt = 0;
			for (RecNr = 1; RecNr <= stu_i->mx; RecNr++) {
				FasFile.Read(RecBuf, stu_i->rlen + 1);
				if (!(RecBuf[0] & 0x01)) { // bit-0 : if 0 then active, if 1 then deleted    // ==0xFC) {
					if (EDBAddRec(DBRef, stu_i->ref, RecNr, stu_i->rlen, &RecBuf[1], now, -1)) RecCnt++;
				}
			}
			CString cstr;
			cstr.Format("Added records in STU-%03d, count", stu_i->ref);
			LogAdd(0, 1, cstr, RecCnt);
		}
		stu_i = (struct _stu*)((char *)stu_i + stu_i->len);
	}
	FasFile.Close();

	CString FsdFilePath = FasFilePath;
	FsdFilePath.MakeUpper();
	FsdFilePath.Replace(".FAS", ".FSD");
	_unlink(FsdFilePath);

	EDBCheckCalc(DBRef, false);
	UnMountDB(DBRef);
	LogAdd(0, 1, "Import of data done from OLD FAS-version", FasFileName);
	return true;
}

int RepCompress(void *source, void *dest, int len, int DestLen) // RecDump->RecBuf,Exp->Stu[_stuix].RecLen);
{
	unsigned char *s = (unsigned char *)source;
	unsigned char *buf = (unsigned char *)dest;
	unsigned char p;
	int i = 0, retlen = 0, SkipNoCheckRep = 4; // NextRepIx dient om deze sequentie te vermijden : 37373737303030 gaf FC73FC0303 ipv FC3703FC3003
	bool RepFlag = false;

	if (len == 0) return 0;

	while (i < len) {
		p = s[i++];
		buf[retlen++] = (p >> 4) | (p << 4);        // FC Byte RepCnt-1 (0 is dus 1x, 1 is dus 2x ...)
		if (RepFlag) {
			if (buf[retlen - 1] == buf[retlen - 3] && buf[retlen - 2] < 0xFF) {
				buf[retlen - 2]++;
				retlen--;
			}
			else {
				RepFlag = false;
				SkipNoCheckRep = retlen + 3;
			}
		}
		if (RepFlag == false) {
			if (buf[retlen - 1] == 0xFC) {
				buf[retlen++] = 0xFC;
				buf[retlen++] = 0;
				RepFlag = true;
			}
			else if (retlen >= SkipNoCheckRep && buf[retlen - 4] == buf[retlen - 1] && buf[retlen - 3] == buf[retlen - 1] && buf[retlen - 2] == buf[retlen - 1]) {
				buf[retlen - 4] = 0xFC;
				buf[retlen - 2] = 3;    // 3 is dus 4x identiek ...
				retlen--;
				RepFlag = true;
			}
		}
		if (retlen >= DestLen) return -len; // to indicate compression not done (not possible. Zip ? Lzh ?)
	}

	return retlen;
}

bool RestoreFasFromBak(char *FasFileName);
bool CompareSysFromRestore(char *ext);
void CompareSignaturesDBvsCopy(bool UseRestoreDir);
void CheckAllShaFileInRestore();

void CheckFiles2Restore()
{
	CFileFind finder;
	CString FileName;
	CFile FasFile;

	CString PathRestore = PathJamaRoot + "RESTORE\\";
	if (GetFileAttributes(PathRestore) == INVALID_FILE_ATTRIBUTES) return;

	CString FindFileName = PathRestore + "*.fsd";
	BOOL bWorking = finder.FindFile(FindFileName);
	while (bWorking) {
		bWorking = finder.FindNextFile();
		if (finder.IsDirectory()) continue;
		FileName = finder.GetFileTitle();
		CString FasFilePath = PathDB + FileName;
		if (GetFileAttributes(FasFilePath) == INVALID_FILE_ATTRIBUTES) { // de FAS file mag niet bestaan in de FAS subdir
			RestoreFasFromBak((char *)(LPCTSTR)FileName);
		}
	}
	finder.Close();

	FindFileName = PathRestore + "sys.*";
	bWorking = finder.FindFile(FindFileName);
	while (bWorking) {
		bWorking = finder.FindNextFile();
		if (finder.IsDirectory()) continue;
		FileName = finder.GetFileName();
		if (FileName.Right(3).CollateNoCase("SHA") == 0) continue;
		CString FasFilePath = PathDB + FileName;
		if (GetFileAttributes(FasFilePath) == INVALID_FILE_ATTRIBUTES) { // Wanneer de gevonden SYS-file niet bestaat in de PathDB, kopieren
			CopyFile((char *)(LPCTSTR)finder.GetFilePath(), FasFilePath, TRUE);
			LogAdd(0, 0, "Restored SYS-file", finder.GetFileName());
		}
	}
	finder.Close();
}

void CheckFasForImport()
{
	CFileFind finder;
	CString FileName;
	CFile FasFile;
	CString FindFileName = PathDB + "*.*";
	BOOL bWorking = finder.FindFile(FindFileName);
	while (bWorking) {
		bWorking = finder.FindNextFile();
		FileName = finder.GetFilePath();
		if (FileName.GetLength() < 7) continue;
		if (FileName.Left(3).CompareNoCase("sys") == 0) continue;
		if (FileName.Right(3).CompareNoCase("old") == 0) continue;
		if (FileName.Right(3).CompareNoCase("res") == 0) continue;
		if (FileName.Right(3).CompareNoCase("raw") == 0) continue;
		if (FileName.Right(3).CompareNoCase("zip") == 0) continue;

		bool FasOldVersion = false;
		if (FasFile.Open(FileName, CFile::modeRead, NULL)) {
			char buf[35];
			FasFile.Read(buf, 30);
			FasFile.Close();
			if (memcmp(buf, "\xFA\x02", 2) == 0 && buf[7] == ' ' && buf[10] == '/' && buf[13] == '/') FasOldVersion = true;
		}
		if (FasOldVersion) {
			ImportFas((char *)(LPCTSTR)finder.GetFileName());
		}
	}
	finder.Close();
}

// code uit Res2Fas.c ...

#define DEF_LEN 50
#define DAT_CNT 50

struct {
	short int   ref;
	short int   dat_cnt;
	struct {
		short int  type;
		short int  sour;
		short int  dest;
		short int  len;
		char def[DEF_LEN];
	} dat[DAT_CNT];
} st[MAX_STRUCT];

UNALIGNED struct htype {
	unsigned short length : 8;
	unsigned short type_ex : 3;
	unsigned short type : 3;
	unsigned short ioclass : 2;
} *header;

int frmtnum(char *ptxt, int type, double *adresfl, int qvoor, int qna, int opt1)
{
	char sbuf[81], *adresc, byte, byte1, *psbuf, *p;
	int i, i2, i3, j, j1, insert, zerosup, zeroflag;
	int cijf, level, len, posit, qvoorzien, dig_tolarge;
	long div, langi, langi_r;
	double divfl, langfl, langfl_r;
	short int *adresi;
	short unsigned *adresu;
	long *adresl;
	float *adresf;
	/*sbuf : +xxxyy+zz : sbuf[0]=teken x=qvoor y=qna +=sign mant. z=mant. */

	langi = 0; langfl = 0;
	adresc = (char *)adresfl;
	adresi = (short int *)adresfl;
	adresu = (short unsigned *)adresfl;
	adresl = (long *)adresfl;
	adresf = (float *)adresfl;
	type = type & 7;
	qvoorzien = qvoor;
	if (type == 3 && qvoor < 10) qvoor = 10;
	if (type < 2) len = 2; else if (type == 5) len = 8; else len = 4;
	if ((opt1 & 3) == 1) { qvoor = len * 2; qna = 0; }
	if ((opt1 & 3) == 2) { qvoor = len * 8; qna = 0; }
	switch (type) {
	case 0:langi = *adresu; break;
	case 1:langi = *adresi; break;
	case 3:langi = *adresl; break;
	case 4:langfl = *adresf; break;
	case 5:langfl = *adresfl; break;
	}
	langi_r = langi; langfl_r = langfl;
	/* convert to string */
	j = 1;
	if ((opt1 & 3) == 0) { /* decimaal */
		sbuf[0] = '+';
		if (type <= 3) {
			if (langi < 0) { sbuf[0] = '-'; langi = -langi; }
		}
		else {
			if (langfl < 0) { sbuf[0] = '-'; langfl = -langfl; }
			i = qna; divfl = 0.5; /* use divfl */
			while (i--) divfl = divfl / 10;
			langfl += divfl;
		}
		if (opt1 & 4) {
			if (type <= 3) opt1 = opt1 & 0xFFFFB;
			else {
				i3 = qvoor + qna + 1;
				sbuf[i3] = '+'; sbuf[i3 + 1] = '0'; sbuf[i3 + 2] = '0';
				i2 = 0;
				FOREVER{
				  if (langfl < 10)break;
				  i2++;
				  langfl = langfl / 10;
				}
					FOREVER{
					  if (langfl == 0 || langfl >= 1)break;
					  i2--;
					  langfl = langfl * 10;
				}
				sbuf[i3] = '+'; if (i2 < 0) { sbuf[i3] = '-'; i2 = -i2; }
				sbuf[++i3] = '0' + i2 / 10; i2 = i2 - (i2 / 10) * 10;
				sbuf[++i3] = '0' + i2;
			}
		}
		div = 1L; for (i = qvoor - 1; i > 0; i--)div = div * 10L;
		i2 = qvoor;
		while (i2--) {
			if (type <= 3) {
				cijf = langi / div;
				langi = langi - cijf * div;
			}
			else {
				cijf = (int)(langfl / div);
				langfl = langfl - cijf * div;
			}
			if (cijf > 9)sbuf[j++] = '*'; else sbuf[j++] = cijf + '0';
			div = div / 10L;
		}
		i2 = qna;
		while (i2--) {
			if (type <= 3) {
				sbuf[j++] = '0';
			}
			else {
				langfl = langfl * 10;
				cijf = (int)(langfl / 1);
				langfl = langfl - cijf;
				sbuf[j++] = cijf + '0';
			}
		}
	}
	if (opt1 & 3) { /* hex en bin */
		for (i = len - 1; i >= 0; i--) {
			byte = *(adresc + i);
			if ((opt1 & 3) == 1) i3 = 1; else i3 = 7;
			for (i2 = i3; i2 >= 0; i2--) {
				if ((opt1 & 3) == 1) {
					byte1 = (byte >> (i2 * 4)) & 0xF;
					if (byte1 > 9)sbuf[j++] = byte1 - 10 + 'A'; else sbuf[j++] = byte1 + '0';
				}
				else {
					byte1 = (byte >> i2) & 1;
					if (byte1)sbuf[j++] = '1'; else sbuf[j++] = '0';
				}
			}
		}
	}
	level = qvoor; insert = 0;

	/* oude _kbnum1() */

	psbuf = sbuf; posit = 0; zerosup = 0;
	j = 0; j1 = 1;
	zeroflag = 1; p = psbuf + 1; i = qvoor + qna;
	while (i-- > 0) {
		if (*p != '0') { zeroflag = 0; break; }
		p++;
	}
	if ((opt1 & 3) == 1 || (opt1 & 3) == 2) {         /* hex or bin */
		for (i = 0; i < len; i++) {
			if (i)*(ptxt + j++) = ' ';
			if ((opt1 & 3) == 1) i2 = 2; else i2 = 8;
			while (i2--) {
				if (j1 == level)posit = j;
				*(ptxt + j++) = *(psbuf + j1++);
			}
		}
	}
	else {                        /* decimaal */
		zerosup = opt1 & 32;
		if (qvoor > qvoorzien) {
			for (i = 1; i <= qvoor; i++) if (*(psbuf + i) != '0') break;
			len = qvoor - i + 1;
			dig_tolarge = len - qvoorzien;
			if (opt1 & 128 || *psbuf == '-') dig_tolarge++;
			if (dig_tolarge > 0) {
				if (opt1 & 16) {
					i = (qvoorzien - 1) / 3;
					if (i > (qvoor - qvoorzien)) {
						for (j = 0; j < (i - qvoor + qvoorzien); j++) *(ptxt + j) = ' ';
						i = qvoor - qvoorzien;
					}
					dig_tolarge -= i; qvoorzien += i; opt1 &= 0xFFEF;
				}
			}
			j1 += qvoor - qvoorzien; qvoor = qvoorzien;
			if (dig_tolarge > 0) *(psbuf + j1) = '*';
		}
		while (qvoor--) {
			if ((opt1 & 16) && j && ((qvoor + 1) % 3 == 0)) {
				if (zerosup == 0) {
					if (opt1 & 8)*(ptxt + j++) = ','; else *(ptxt + j++) = '.';
				}
				else *(ptxt + j++) = ' ';
			}
			if (qvoor == 0)zerosup = 0;
			if (j1 == level)posit = j;
			*(ptxt + j) = *(psbuf + j1++);
			if (zerosup) {
				if (*(ptxt + j) == '0') *(ptxt + j) = ' ';
				else zerosup = 0;
			}
			j++;
		}
		if (qna) {
			if (opt1 & 8)*(ptxt + j++) = '.'; else *(ptxt + j++) = ',';
		}
		while (qna--) {
			if (j1 == level)posit = j;
			*(ptxt + j++) = *(psbuf + j1++);
		}
		if (opt1 & 4) {
			i = 3;
			while (i--) {
				if (j1 == level)posit = j;
				*(ptxt + j++) = *(psbuf + j1++);
			}
		}
		if ((*psbuf == '-') || (opt1 & 128)) {
			for (i = 0;; i++) {
				if (*(ptxt + i) != ' ')break;
			}
			i--; if (i < 0) i = 0;
			*(ptxt + i) = *psbuf;
		}
	}
	*(ptxt + j) = 0;
	if (opt1 & 64 && zeroflag) {
		for (i = 0; i < j; i++) *(ptxt + i) = ' ';
	}
	return (j);
}

int stcd_df(char *s, double *df)
{
	char ap;
	int neg, i, stop;
	double add;

	*df = 0; i = 0; stop = 0; neg = 0; ap = 0; add = 0.1;
	while (*s) {
		if ((*s >= '0') && (*s <= '9')) {
			if (ap) {
				*df += ((*s - '0') * add);
				add /= 10.;
			}
			else *df = *df * 10 + *s - '0';
		}
		else if (*s == '.' || *s == ',') ap = 1;
		else if (*s == '-') neg = 1;
		else if (*s != '+') { stop = 1; break; }
		i++;
		s++;
	}
	if (neg == 1)  *df = -*df;
	if (stop == 1) i = -i;
	return(i);
}

void StructConvertProcess(int DBRefFas, int TabIxFas, int DBRefRes, int TabIxRes, unsigned char *buf_i, unsigned char *buf_o)
{
	unsigned char *s, *d;
	char buf[100];
	int i, j, type, typ_i, typ_o, l, len, cntbf, ap, dat_ix, sour, dest;
	double dbl;

	int StuNr = DB[DBRefFas].Tab[TabIxFas].StuNr;
	int RecNrLen_i = DB[DBRefRes].Tab[TabIxRes].EleInf[1].FldLen; // in de RES-file
	int RecNrLen_o = DB[DBRefFas].Tab[TabIxFas].EleInf[1].FldLen; // in de nieuwe FAS-file

	for (dat_ix = 0; dat_ix < st[StuNr].dat_cnt; dat_ix++) {
		sour = st[StuNr].dat[dat_ix].sour;
		dest = st[StuNr].dat[dat_ix].dest;
		len = st[StuNr].dat[dat_ix].len;
		type = st[StuNr].dat[dat_ix].type;
		s = buf_i + sour - RecNrLen_i; d = buf_o + dest - RecNrLen_o;

		switch (type & 0x7F00) {
		case 0x0000:
			while (len-- > 0) *d++ = *s++;
			break;
		case 0x0100:
			switch (type & 0x00FF) {
			case 0x00:
				while (len-- > 0) *d++ = '\0';
				break;
			case 0x01:
				l = len;
				if (l > DEF_LEN - 1) l = DEF_LEN - 1;
				s = (unsigned char*)st[StuNr].dat[dat_ix].def;
				while (l-- > 0) *d++ = *s++;
				l = len - l;
				while (l-- > 0) *d++ = '\0';
				break;
			}
			break;
		case 0x0200:
			// round if necessary
			typ_i = type & 0x000F; typ_o = type & 0x00F0;
			if ((typ_i >= 4 && typ_i <= 5) && (typ_o >= 0x00 && typ_o <= 0x30)) {
				if (typ_i == 4) {
					if (*(float *)s < 0) *(float *)s -= .5;
					else *(float *)s += .5;
				}
				else if (typ_i == 5) {
					if (*(double *)s < 0) *(double *)s -= .5;
					else *(double *)s += .5;
				}
			}

			switch (type & 0x00F0) {
			case 0x00:
				switch (type & 0x000F) {
				case 0: *(unsigned short *)d = *(unsigned short *)s; break;
				case 1: *(unsigned short *)d = *(short int *)s;      break;
				case 3: *(unsigned short *)d = (unsigned short int) *(long *)s;     break;
				case 4: *(unsigned short *)d = (unsigned short int) *(float *)s;    break;
				case 5: *(unsigned short *)d = (unsigned short int) *(double *)s;   break;
				}
				break;
			case 0x10:
				switch (type & 0x000F) {
				case 0: *(short int *)d = *(unsigned short *)s; break;
				case 1: *(short int *)d = *(short int *)s;      break;
				case 3: *(short int *)d = (short int) *(long *)s;     break;
				case 4: *(short int *)d = (short int)*(float *)s;    break;
				case 5: *(short int *)d = (short int)*(double *)s;   break;
				}
				break;
			case 0x30:
				switch (type & 0x000F) {
				case 0: *(long *)d = *(unsigned short *)s; break;
				case 1: *(long *)d = *(short int *)s;      break;
				case 3: *(long *)d = *(long *)s;     break;
				case 4: *(long *)d = (long)*(float *)s;    break;
				case 5: *(long *)d = (long)*(double *)s;   break;
				}
				break;
			case 0x40:
				switch (type & 0x000F) {
				case 0: *(float *)d = (float) *(unsigned short *)s; break;
				case 1: *(float *)d = (float) *(short int *)s;      break;
				case 3: *(float *)d = (float) *(long *)s;     break;
				case 4: *(float *)d = *(float *)s;    break;
				case 5: *(float *)d = (float)*(double *)s;   break;
				}
				break;
			case 0x50:
				switch (type & 0x000F) {
				case 0: *(double *)d = *(unsigned short *)s; break;
				case 1: *(double *)d = *(short int *)s;      break;
				case 3: *(double *)d = *(long *)s;     break;
				case 4: *(double *)d = *(float *)s;    break;
				case 5: *(double *)d = *(double *)s;   break;
				}
				break;
			}
		case 0x0300:
			typ_i = type & 0x000F; ap = (type & 0x00F0) / 0x0010;
			cntbf = frmtnum(buf, typ_i, (double *)s, 10, ap, 0x28);// niet meer dan 10 voor int ??
			buf[cntbf] = 0;
			for (i = 0; i < cntbf; i++) if (buf[i] != ' ') break;
			for (j = 0; j < len; j++) {
				if ((j + i) < cntbf) d[j] = buf[j + i];
				else d[j] = 0;
			}
			break;
		case 0x0400:
			typ_o = type & 0x000F;
			stcd_df((char *)s, &dbl);
			if (typ_o >= 0 && typ_o <= 3) {
				if (dbl < 0) dbl -= .5;
				else dbl += .5;
			}
			switch (typ_o) {
			case 0: *(unsigned short *)d = (unsigned short)dbl; break;
			case 1: *(short int *)d = (short int)dbl; break;
			case 2:
			case 3: *(long *)d = (long)dbl; break;
			case 4: *(float *)d = (float)dbl; break;
			case 5: *(double *)d = dbl; break;
			}
			break;
		}
	}
}

int desc2len(char *desc)
{
	char *s;
	int len = 1000;
	UNALIGNED struct htype *hdr;

	hdr = (struct htype *)desc;
	switch (hdr->type) {
	case 0: len = 4; break;
	case 1: s = desc + 6; len = 7;
		while (*s++) len++;
		break;
	case 2: len = 6;
		if (*(desc + 5) & 0x80) len += 2;
		if (*(desc + 5) & 0x40) len += 2;
		break;
	case 3: case 4: case 5: len = 2; break;
	}
	return len;
}

void UpdateDefault(unsigned char *desc, char *DefInfo)
{
	UNALIGNED unsigned char *descextra;
	int  i, len;

	header = (struct htype *)desc;
	*DefInfo = 0;
	if ((len = desc2len((char *)desc)) < (int)header->length) {
		descextra = desc + len;
		FOREVER{
		  if (*descextra == 0) break;
		  if (*(descextra + 1) == 2) {/* type DEF INFO */
					len = *descextra - 2;
					for (i = 0; i < len; i++) {
						if (*(descextra + 2 + i) == 0) {
							len = i; break;
						}
					}
					if (header->type == 1 && len > *(int *)(desc + 2)) len = *(int *)(desc + 2);
					if (len > 0) memcpy(DefInfo,descextra + 2,len);
					break;
		  }
		  descextra += *descextra;
		}
	}
}

void add_dat(int DBRefFas, int type, int StuNr, int EleIx, int len, int dest, int sour)
{
	int dat_ix;
	char *desttyp, *sourtyp;
	char buf[1000];

	if (len > 0) {
		dat_ix = st[StuNr].dat_cnt;
		st[StuNr].dat[dat_ix].dest = dest;
		st[StuNr].dat[dat_ix].sour = sour;
		st[StuNr].dat[dat_ix].len = len;
		st[StuNr].dat[dat_ix].type = type;
		switch (type & 0x7F00) {
		case 0x0000:
			sprintf(buf, "StuNr=%d COP P%d L%d F%d", StuNr, dest, len, sour);
			break;
		case 0x0100:
			switch (type & 0x00FF) {
			case 0x00:
				sprintf(buf, "StuNr=%d CLR P%d L%d", StuNr, dest, len);
				break;
			case 0x01:
				sprintf(buf, "StuNr=%d NEW E%d L%d", StuNr, EleIx, len);
				break;
			}
			break;
		case 0x0200:
			switch (type & 0x00F0) {
			case 0x0000: desttyp = "uns"; break;
			case 0x0010: desttyp = "int"; break;
			case 0x0030: desttyp = "lon"; break;
			case 0x0040: desttyp = "flo"; break;
			case 0x0050: desttyp = "dou"; break;
			default: desttyp = "xxx"; break;
			}
			switch (type & 0x000F) {
			case 0x0000: sourtyp = "uns"; break;
			case 0x0001: sourtyp = "int"; break;
			case 0x0003: sourtyp = "lon"; break;
			case 0x0004: sourtyp = "flo"; break;
			case 0x0005: sourtyp = "dou"; break;
			default: sourtyp = "xxx"; break;
			}
			sprintf(buf, "StuNr=%d CNV E%d %s < %s", StuNr, EleIx, desttyp, sourtyp);
			break;
		case 0x0300:
			switch (type & 0x0007) {
			case 0x0000: sourtyp = "uns"; break;
			case 0x0001: sourtyp = "int"; break;
			case 0x0003: sourtyp = "lon"; break;
			case 0x0004: sourtyp = "flo"; break;
			case 0x0005: sourtyp = "dou"; break;
			default: sourtyp = "xxx"; break;
			}
			sprintf(buf, "StuNr=%d CNV E%d string from %s", StuNr, EleIx, sourtyp);
			break;
		case 0x0400:
			switch (type & 0x000F) {
			case 0x0000: desttyp = "uns"; break;
			case 0x0001: desttyp = "int"; break;
			case 0x0003: desttyp = "lon"; break;
			case 0x0004: desttyp = "flo"; break;
			case 0x0005: desttyp = "dou"; break;
			default: desttyp = "xxx"; break;
			}
			sprintf(buf, "StuNr=%d CNV E%d %s from string", StuNr, EleIx, desttyp);
			break;
		}
		LogAdd(0, 1, buf);
		if (type == 0x0101) {
			int TabIx = DB[DBRefFas].Stu2Tab[StuNr];
			UpdateDefault(DB[DBRefFas].Tab[TabIx].EleInf[EleIx].Desc, st[StuNr].dat[dat_ix].def);
		}
		st[StuNr].dat_cnt++;
	}
}

unsigned CompareEle(unsigned char *res_inf, unsigned char *fas_inf)
{
	char fas_typ, res_typ;
	unsigned char dummy[10];
	memset(dummy, 0, 10);
	if (res_inf == NULL) res_inf = dummy;
	if (fas_inf == NULL) fas_inf = dummy;

	fas_typ = fas_inf[1]; res_typ = res_inf[1];
	if ((fas_typ & 0xC0) == 0) {
		if ((res_typ & 0xC0) == 0) return NO;
		else return 0x0101;
	}
	else {
		if ((res_typ & 0xC0) == 0) return 0x0101;
		if ((res_typ & 0x3F) == (fas_typ & 0x3F)) {
			if ((res_typ & 0x38) == 8) {
				if (*(int *)&res_inf[2] == *(int *)&fas_inf[2]) return NO;
				return 0x0100;  // string length differs 
			}
			return NO; // identical fields
		}
		if (((res_typ & 0x38) == 0x10) && ((fas_typ & 0x38) == 0x10)) {
			return (0x0200 + (fas_typ & 7) * 16 + (res_typ & 7));
		}
		if (((res_typ & 0x38) == 0x10) && ((fas_typ & 0x38) == 0x08)) {
			return (0x0300 + (res_inf[3] * 16) + (res_typ & 7));  // numerical to string
		}
		if (((res_typ & 0x38) == 0x08) && ((fas_typ & 0x38) == 0x10)) {
			return (0x0400 + (fas_typ & 7));  // string to numerical 
		}
		return 0x0101;  // differ completely
	}
}

void StructDifferAnalyse(int DBRefFas, int DBRefRes)
{
	int StuNr, EleIx, dest, sour, len;
	int TabIxFas, TabIxRes, dif, res_pos, res_len, fas_pos, fas_len;

	for (TabIxFas = 0; TabIxFas < DB[DBRefFas].TabCnt; TabIxFas++) {
		StuNr = DB[DBRefFas].Tab[TabIxFas].StuNr;
		if (StuNr == 0 || DB[DBRefFas].Tab[TabIxFas].StructLen == 0) continue;

		for (TabIxRes = 0; TabIxRes < DB[DBRefRes].TabCnt; TabIxRes++) {
			if (DB[DBRefRes].Tab[TabIxRes].StuNr == StuNr) break;
		}
		if (TabIxRes == DB[DBRefRes].TabCnt) continue; // deze StuNr zit wel in nieuwe file, maar niet in oude !

		sour = 0; dest = 0; len = -1;

		for (EleIx = 2; EleIx <= MAX_FIELDS; EleIx++) {
			if (EleIx > DB[DBRefFas].Tab[TabIxFas].EleCnt && EleIx > DB[DBRefRes].Tab[TabIxRes].EleCnt) break;

			res_len = DB[DBRefRes].Tab[TabIxRes].EleInf[EleIx].FldLen;
			res_pos = DB[DBRefRes].Tab[TabIxRes].EleInf[EleIx].FldOffset;
			fas_len = DB[DBRefFas].Tab[TabIxFas].EleInf[EleIx].FldLen;
			fas_pos = DB[DBRefFas].Tab[TabIxFas].EleInf[EleIx].FldOffset;

			if ((len == -1) && (fas_len > 0)) {
				dest = fas_pos; sour = res_pos; len = 0;
			}
			dif = CompareEle(DB[DBRefRes].Tab[TabIxRes].EleInf[EleIx].Desc, DB[DBRefFas].Tab[TabIxFas].EleInf[EleIx].Desc);
			if (dif == 0) {
				len += fas_len;   // identical fields
			}
			else if (dif == 0x0101) {  // completely different 
				add_dat(DBRefFas, 0, StuNr, EleIx, len, dest, sour); // save copy piece 
				add_dat(DBRefFas, dif, StuNr, EleIx, fas_len, fas_pos, sour);
				len = -1;
			}
			else if (dif == 0x0100) { // both strings, but len can differ 
				if (fas_len < res_len) { // fas is shorter
					len += fas_len;
					add_dat(DBRefFas, 0, StuNr, EleIx, len, dest, sour);
					len = -1;
				}
				else {								// fas is longer
					len += res_len;
					add_dat(DBRefFas, 0, StuNr, EleIx, len, dest, sour);
					dest = fas_pos + res_len; len = fas_len - res_len;
					add_dat(DBRefFas, 0x0100, StuNr, EleIx, len, dest, sour);
					len = -1;
				}
			}
			else if (((dif & 0x7F00) >= 0x0200) && ((dif & 0x7F00) <= 0x0400)) { // convertion 
				add_dat(DBRefFas, 0, StuNr, EleIx, len, dest, sour);
				dest = fas_pos; sour = res_pos; len = 1;  // len not relevant 
				if ((dif & 0x7F00) == 0x0300) len = fas_len;
				else if ((dif & 0x7F00) == 0x0400) len = res_len;
				add_dat(DBRefFas, dif, StuNr, EleIx, len, dest, sour);
				len = -1;
			}
		}
		add_dat(DBRefFas, 0, StuNr, EleIx, len, dest, sour);
	}
}

void UpdateLayout(CString FasFileName)
{
	unsigned char ReadRecBuf[BUF_LEN + 10], WriteRecBuf[BUF_LEN + 10];
	int i;
	CString FsdFilePath, ResFileName, ResFilePath, FasFilePath;

	LogAdd(0, 0, "Changing structure", FasFileName);

	// check 'OpenFileFlag' in LOG-dir (Mount/UnMount wanneer file niet goed gesloten was ! Neem geen risico's)
	CString LogPath = PathDBLog + FasFileName + ".log\\";
	CString OpenFileFlagName = LogPath + "OpenFile.flg";
	if (GetFileAttributes(OpenFileFlagName) != INVALID_FILE_ATTRIBUTES) {
		LogAdd(0, 0, "Database was not closed correctly, so Mount/UnMount", FasFileName);
		int DBRef = MountDB((char *)(LPCTSTR)FasFileName);
		UnMountDB(DBRef);
	}

	// remove LOG-dir if it exists (because Fas-file will be renamed !) (zou kunnen dat die niet gebeurd is owv emergency exit vorige sessie !)
	CFileFind finder;
	CString LogFilesFinder;
	LogFilesFinder += LogPath + _T("*.*");
	BOOL bWorking = finder.FindFile(LogFilesFinder);  // zoek alle bestanden in de xxx.log subdir
	while (bWorking) {
		bWorking = finder.FindNextFile();
		if (finder.IsDirectory()) continue;
		_unlink(finder.GetFilePath());
	}
	finder.Close();
	_rmdir(LogPath);

	//Copieer de nieuwe xxx.FSD uit JamaProg naar xxx.xxx.fsd in de FSD subdir	
	CString NewFsdFilePath = PathProg + FasFileName;
	i = NewFsdFilePath.ReverseFind('.');
	NewFsdFilePath = NewFsdFilePath.Left(i) + ".fsd";
	FsdFilePath = PathFSD + FasFileName + ".fsd";
	CopyFile(NewFsdFilePath, FsdFilePath, false);

	// rename de bestaande FAS file (xxx.xxx) naar RES als xxx.xxx.res
	ResFileName = FasFileName + ".res";
	ResFilePath = PathDB + ResFileName;
	FasFilePath = PathDB + FasFileName;
	_unlink(ResFilePath);
	MoveFile(FasFilePath, ResFilePath);

	// mount new FAS-file (create new one using NewFSD
	int DBRefFas = MountDB((char *)(LPCTSTR)FasFileName, true, true);
	// mount RES-file (was the old FAS-file)
	int DBRefRes = MountDB((char *)(LPCTSTR)ResFileName, false, true);

	StructDifferAnalyse(DBRefFas, DBRefRes);

	int TabIxRes, TabIxFas;
	for (TabIxFas = 0; TabIxFas < DB[DBRefFas].TabCnt; TabIxFas++) {
		if (DB[DBRefFas].Tab[TabIxFas].StuNr == 0) continue;

		for (TabIxRes = 0; TabIxRes < DB[DBRefRes].TabCnt; TabIxRes++) {
			if (DB[DBRefFas].Tab[TabIxFas].StuNr == DB[DBRefRes].Tab[TabIxRes].StuNr) break;
		}
		if (TabIxRes == DB[DBRefRes].TabCnt) continue; // deze StuNr zit wel in nieuwe file, maar niet in oude !

		unsigned int RecCnt = 0;
		short int ChangedBy;
		int ReadRecLen;
		int WriteRecLen = DB[DBRefFas].Tab[TabIxFas].StructLen - DB[DBRefFas].Tab[TabIxFas].EleInf[1].FldLen;
		double TmpDateTime, DateTimeUpdatedLast = -1000;
		for (unsigned int RecNr = 1; RecNr <= DB[DBRefRes].Tab[TabIxRes].LastRec; RecNr++) {
			if (EDBGetRec(DBRefRes, DB[DBRefRes].Tab[TabIxRes].StuNr, RecNr, &ReadRecLen, ReadRecBuf, &TmpDateTime, &ChangedBy)) { // true when record read
				if (TmpDateTime > DateTimeUpdatedLast) DateTimeUpdatedLast = TmpDateTime;
				StructConvertProcess(DBRefFas, TabIxFas, DBRefRes, TabIxRes, ReadRecBuf, WriteRecBuf);
				if (EDBAddRec(DBRefFas, DB[DBRefFas].Tab[TabIxFas].StuNr, RecNr, WriteRecLen, WriteRecBuf, TmpDateTime, ChangedBy)) RecCnt++;
			}
		}
		DB[DBRefFas].Tab[TabIxFas].DateTimeUpdate = DateTimeUpdatedLast;
	}
	UnMountDB(DBRefRes);
	EDBCheckCalc(DBRefFas, false);
	UnMountDB(DBRefFas);
	LogAdd(0, 1, "New FAS created and all records imported for previous version", ResFileName);
}

bool CheckFsdChanged()
{
	int j;
	CFileFind finder;
	CFile FsdFile;
	CString FsdFileName, FileName, FindFileName = PathDB + "???.???";

	// gebruik de laatste en voorlaatste DB (nodig voor de TAB-tabel).
	int FsdIx0 = DB_MAX - 1;
	char* FsdBuf0 = new char[LEN_FSD + 10];
	int FsdIx1 = DB_MAX - 2;
	char* FsdBuf1 = new char[LEN_FSD + 10];

	BOOL bWorking = finder.FindFile(FindFileName);
	while (bWorking) {
		bWorking = finder.FindNextFile();
		FileName = finder.GetFileName();
		if (FileName.GetLength() < 7) continue;
		if (FileName.Left(3).CompareNoCase("sys") == 0) continue;
		if (FileName.Right(3).CompareNoCase("old") == 0) continue;
		if (FileName.Right(3).CompareNoCase("res") == 0) continue;
		if (FileName.Right(3).CompareNoCase("raw") == 0) continue;
		if (FileName.Right(3).CompareNoCase("zip") == 0) continue;

		// initialiseer de werkbuffers
		memset(&Fsd[FsdIx0], 0, sizeof(struct s_FSD));
		Fsd[FsdIx0].buf = FsdBuf0;
		memset(&Fsd[FsdIx1], 0, sizeof(struct s_FSD));
		Fsd[FsdIx1].buf = FsdBuf1;
		memset(&DB[FsdIx0], 0, sizeof(struct s_DB));
		memset(&DB[FsdIx1], 0, sizeof(struct s_DB));

		// kijk of de xxx.xxx.fsd bestaat in de PahtFSD, zo niet mount de file om de FSD te maken
		FsdFileName = PathFSD + FileName + ".fsd";
		if (GetFileAttributes(FsdFileName) == INVALID_FILE_ATTRIBUTES) {
			// probeer de database te openen, dan wordt de FSD aangemaakt
			int DBRef = MountDB((char *)(LPCTSTR)FileName, false, true);
			if (DBRef >= 0) UnMountDB(DBRef);
			if (GetFileAttributes(FsdFileName) == INVALID_FILE_ATTRIBUTES) continue; //kan niet verder als de FSD niet bestaat
		}

		// read xxx.xxx.fsd in PathFSD into Fsd[FsdIx1]
		if (!FsdFile.Open(FsdFileName, CFile::modeRead, NULL)) continue;
		FsdFile.Read(Fsd[FsdIx1].buf, LEN_FSD + 8);
		FsdFile.Close();
		LogAdd(0, 1, "Processing structure-info from", FsdFileName);
		AnalyseFSD(FsdIx1);

		// read xxx.fsd in PathOld into Fsd[FsdIx0] (aangemaakt door config.exe)
		FsdFileName = FileName;
		int i = FsdFileName.ReverseFind('.');
		FsdFileName = FsdFileName.Left(i);
		FsdFileName = PathProg + FsdFileName + ".fsd";
		if (!FsdFile.Open(FsdFileName, CFile::modeRead, NULL)) continue;
		FsdFile.Read(Fsd[FsdIx0].buf, LEN_FSD + 8);
		FsdFile.Close();
		LogAdd(0, 1, "Processing structure-info from", FsdFileName);
		AnalyseFSD(FsdIx0);

		// compare de TAB voor de keys
		int TabIx = -1;
		if (DB[FsdIx0].TabCnt == DB[FsdIx1].TabCnt) {
			for (TabIx = 0; TabIx < DB[FsdIx0].TabCnt; TabIx++) {
				if (DB[FsdIx0].Tab[TabIx].StuNr != DB[FsdIx1].Tab[TabIx].StuNr) break;
				if (strcmp(DB[FsdIx0].Tab[TabIx].Nam, DB[FsdIx1].Tab[TabIx].Nam) != 0) break;
				if (DB[FsdIx0].Tab[TabIx].KeyMax != DB[FsdIx1].Tab[TabIx].KeyMax) break;
				for (i = 0; i < DB[FsdIx0].Tab[TabIx].KeyMax; i++) {
					if (DB[FsdIx0].Tab[TabIx].KeyInf[i].Typ != DB[FsdIx1].Tab[TabIx].KeyInf[i].Typ) break;
					if (DB[FsdIx0].Tab[TabIx].KeyInf[i].pceCnt != DB[FsdIx1].Tab[TabIx].KeyInf[i].pceCnt) break;
					for (j = 0; j < DB[FsdIx0].Tab[TabIx].KeyInf[i].pceCnt; j++) {
						if (DB[FsdIx0].Tab[TabIx].KeyInf[i].pce[j].len != DB[FsdIx1].Tab[TabIx].KeyInf[i].pce[j].len) break;
						if (DB[FsdIx0].Tab[TabIx].KeyInf[i].pce[j].off != DB[FsdIx1].Tab[TabIx].KeyInf[i].pce[j].off) break;
						if (DB[FsdIx0].Tab[TabIx].KeyInf[i].pce[j].typ != DB[FsdIx1].Tab[TabIx].KeyInf[i].pce[j].typ) break;
					}
					if (j < DB[FsdIx0].Tab[TabIx].KeyInf[i].pceCnt) break;
				}
				if (i < DB[FsdIx0].Tab[TabIx].KeyMax) break;
			}
		}
		if (TabIx < DB[FsdIx0].TabCnt) {
			UpdateLayout(FileName);
			continue;
		}

		// compare de Fsd voor de Stu/Elet
		int StuNr;
		for (StuNr = 0; StuNr < MAX_STRUCT; StuNr++) {
			int TabIxFas = DB[FsdIx0].Stu2Tab[StuNr];
			int TabIxRes = DB[FsdIx1].Stu2Tab[StuNr];
			if (DB[FsdIx0].Tab[TabIxFas].StructLen != DB[FsdIx1].Tab[TabIxRes].StructLen) break;
			if (DB[FsdIx0].Tab[TabIxFas].StructLen) {
				if (DB[FsdIx0].Tab[TabIxFas].EleCnt != DB[FsdIx1].Tab[TabIxRes].EleCnt) break;
				if (strcmp(DB[FsdIx0].Tab[TabIxFas].StructName, DB[FsdIx1].Tab[TabIxRes].StructName) != 0) break;
				int EleIx;
				for (EleIx = 0; EleIx <= MAX_FIELDS; EleIx++) {
					if (DB[FsdIx0].Tab[TabIxFas].EleInf[EleIx].FldLen != DB[FsdIx1].Tab[TabIxRes].EleInf[EleIx].FldLen) break;
					if (DB[FsdIx0].Tab[TabIxFas].EleInf[EleIx].FldLen) {
						if (memcmp(DB[FsdIx0].Tab[TabIxFas].EleInf[EleIx].Desc, DB[FsdIx1].Tab[TabIxRes].EleInf[EleIx].Desc, DB[FsdIx1].Tab[TabIxRes].EleInf[EleIx].Desc[0]) != 0) break;
						if (strcmp(DB[FsdIx0].Tab[TabIxFas].EleInf[EleIx].Name, DB[FsdIx1].Tab[TabIxRes].EleInf[EleIx].Name) != 0) break;
					}
				}
				if (EleIx < MAX_FIELDS) break;
			}
		}
		if (StuNr < MAX_STRUCT) {
			UpdateLayout(FileName);
			continue;
		}
	}
	finder.Close();
	delete FsdBuf0;
	delete FsdBuf1;
	memset(&Fsd[FsdIx0], 0, sizeof(struct s_FSD));
	memset(&Fsd[FsdIx1], 0, sizeof(struct s_FSD));
	memset(&DB[FsdIx0], 0, sizeof(struct s_DB));
	memset(&DB[FsdIx1], 0, sizeof(struct s_DB));

	return true;
}


//*********************************************
// Memory Mapped File / Shared Memory for IPC
//*********************************************

struct s_SharedMem {
	bool Used;
	char TaskBuf[BUF_LEN];
} *pSharedMemArray[MMF_COUNT + 1];

HANDLE JMSProcEvent[MMF_COUNT + 1];
DWORD TickOnEntry[MMF_COUNT + 1];
HANDLE hListenThread[MMF_COUNT + 1];

int MMFUsedCount = 0;

void CloseSharedMemThreads()
{
	for (int ix = 0; ix < MMFUsedCount; ix++) {
		SetEvent(JMSProcEvent[ix]);
	}
	SetEvent(JMSProcEvent[MMF_COUNT]); // om batch kanaal te closen
	Sleep(500);
}

void ListenSharedMem(int MMFIx)
{
	HANDLE SharedMemMutex;
	HANDLE JMSDoneEvent, OVLProcEvent, OVLDoneEvent;
	HANDLE hMMFile;

	struct s_SharedMem *pSharedMem = pSharedMemArray[MMFIx];
	CString strSharedMemMutex;
	strSharedMemMutex.Format("JMwSharedMemoryMutex-%d", MMFIx);
	SharedMemMutex = CreateMutex(NULL, FALSE, strSharedMemMutex);
	CString strJMSProcEvent;
	strJMSProcEvent.Format("JMwJMSProcEvent-%d", MMFIx);
	JMSProcEvent[MMFIx] = CreateEvent(
		NULL,               // default security attributes
		FALSE,              // auto-reset event
		FALSE,              // initial state is nonsignaled
		strJMSProcEvent     // object name
	);

	if (JMSProcEvent[MMFIx] == NULL)
	{
		LogAdd(35, 0, "Cannot make JMSProcEvent");
		return;
	}

	CString strJMSDoneEvent;
	strJMSDoneEvent.Format("JMwJMSDoneEvent-%d", MMFIx);
	JMSDoneEvent = CreateEvent(
		NULL,               // default security attributes
		FALSE,              // auto-reset event
		FALSE,              // initial state is nonsignaled
		strJMSDoneEvent     // object name
	);

	if (JMSDoneEvent == NULL)
	{
		LogAdd(35, 0, "Cannot make JMSProcEvent");
		return;
	}

	CString strJMwOVLProcEvent;
	strJMwOVLProcEvent.Format("JMwOVLProcEvent-%d", MMFIx);
	OVLProcEvent = CreateEvent(
		NULL,               // default security attributes
		FALSE,              // auto-reset event
		FALSE,              // initial state is nonsignaled
		strJMwOVLProcEvent  // object name
	);

	if (OVLProcEvent == NULL)
	{
		//LogAdd(35,0,"Cannot make JMSProcEvent");
		return;
	}

	CString strJMwOVLDoneEvent;
	strJMwOVLDoneEvent.Format("JMwOVLDoneEvent-%d", MMFIx);
	OVLDoneEvent = CreateEvent(
		NULL,               // default security attributes
		FALSE,              // auto-reset event
		FALSE,              // initial state is nonsignaled
		strJMwOVLDoneEvent  // object name
	);

	if (OVLDoneEvent == NULL)
	{
		//LogAdd(35,0,"Cannot make JMSDoneEvent");
		return;
	}

	int size = sizeof(s_SharedMem);
	CString strJMwSharedMemoryFile;
	strJMwSharedMemoryFile.Format("JMwSharedMemoryFile-%d", MMFIx);
	hMMFile = CreateFileMapping(INVALID_HANDLE_VALUE,    // Current file handle. 
		NULL,                              // Default security. 
		PAGE_READWRITE,                    // Read/write permission. 
		0,
		size,
		strJMwSharedMemoryFile);					 // Name of mapping object. 
	int ret = GetLastError();

	pSharedMem = (struct s_SharedMem *)MapViewOfFile(hMMFile, // Handle to mapping object. 
		FILE_MAP_ALL_ACCESS,               // Read/write permission 
		0,                                 // Max. object size. 
		0,                                 // Size of hFile. 
		size);                                // Map entire file. 

	if (hMMFile == NULL) {
		LogAdd(35, 0, "Cannot make Memory Mapped File");
		return;
	}

	while (!JMSShuttingDown) {
		// wait for a netbios-packet to be received 
		DWORD dwWaitResult;

		TickOnEntry[MMFIx] = 0;
		dwWaitResult = WaitForSingleObject(JMSProcEvent[MMFIx], INFINITE);    // indefinite wait
		TickOnEntry[MMFIx] = GetTickCount();
		if (dwWaitResult == WAIT_OBJECT_0) {
			if (JMSShuttingDown) break;
			/*
			if (memcmp(Thd[THREAD_MMF_OFFSET+MMFIx].ComBuf,pSharedMem->TaskBuf,8)==0) {
			  LogAdd(0,1,"Handshaking failed, JMSProcEvent fired but SharedMem was not changed !");
			  continue;
			}
			*/
			//wat stond dat hier te doen ????

			memcpy(Thd[THREAD_MMF_OFFSET + MMFIx].ComBuf, pSharedMem->TaskBuf, BUF_LEN);
			ComBufExec(THREAD_MMF_OFFSET + MMFIx);
			if (Thd[THREAD_MMF_OFFSET + MMFIx].ReplyLength) {
				// sent the reply that is prepared
				memcpy(pSharedMem->TaskBuf, Thd[THREAD_MMF_OFFSET + MMFIx].ComBuf, Thd[THREAD_MMF_OFFSET + MMFIx].ReplyLength + 8);
				SetEvent(JMSDoneEvent); // om de sendtask aan de OVL-kant terug vrij te geven ...
				SetEvent(OVLProcEvent);
				// Wait for OVLDoneEvent is niet nodig ... geen overlap mogelijk, zij zijn de baas
			}
			else {
				SetEvent(JMSDoneEvent);
			}
		}
		else break;
	}
	CloseHandle(SharedMemMutex);
	CloseHandle(JMSProcEvent[MMFIx]);
	CloseHandle(JMSDoneEvent);
	CloseHandle(OVLProcEvent);
	CloseHandle(OVLDoneEvent);
	CloseHandle(hMMFile);
}

void RestartListenThread(int MMFIx)
{
	TerminateThread(hListenThread[MMFIx], 0);
	hListenThread[MMFIx] = 0;
	if (JMSProcEvent[MMFIx]) {
		CloseHandle(JMSProcEvent[MMFIx]);
		JMSProcEvent[MMFIx] = NULL;
	}
	LogAdd(113, 0, "Terminate and Restart ListenThread", MMFIx);
	Sleep(250);
	hListenThread[MMFIx] = (HANDLE)_beginthread((void(*)(void*))ListenSharedMem, 0, (void*)MMFIx);

}

void ReleaseBuffers()
{
	int DBRef;

	::DeleteCriticalSection(&m_DBTableCs);

	for (DBRef = 0; DBRef < DB_MAX; DBRef++) {

		::DeleteCriticalSection(&m_DBOpenCs[DBRef]);
		::DeleteCriticalSection(&m_DBRecsAddDeleteCs[DBRef]);

		if (Fsd[DBRef].buf) {
			delete Fsd[DBRef].buf;
			memset(&Fsd[DBRef], 0, sizeof(struct s_FSD));
		}
	}
}

int FindDB(char* cDBName)
{
	int DBRef;
	CString DBName;

	DBName = cDBName;
	DBName.MakeUpper();

	for (DBRef = 0; DBRef < DB_MAX; DBRef++) {
		if (DBName.CompareNoCase(DB[DBRef].Name) == 0) return DBRef;
	}
	return -1;
}

bool UnMountDB(int DBRef)
{
	CString cstr;

	::EnterCriticalSection(&m_DBOpenCs[DBRef]);

	if (DB[DBRef].OpenCount >= 1) DB[DBRef].OpenCount--;
	cstr.Format("%s (count is now=%d)", DB[DBRef].Name, DB[DBRef].OpenCount);
	LogAdd(0, 1, "Decreased OpenCount Database", cstr);
#ifndef JMSVIEWER
	WriteStatsToDB(DBRef); // voor alle veiligheid
#endif
	if (DB[DBRef].OpenCount > 0) {
		::LeaveCriticalSection(&m_DBOpenCs[DBRef]);
		return true;
	}

	EDBEndAllSessions(DBRef);
	if (!EDBClose(DBRef)) {
		LogAdd(66, 0, "Could not cleanly close DB", DB[DBRef].Name);
	}

	if (Fsd[DBRef].buf) {
		delete Fsd[DBRef].buf;
		memset(&Fsd[DBRef], 0, sizeof(struct s_FSD));
	}
	cstr = DB[DBRef].Name;
	int Level = 0;
	if (DB[DBRef].DisabledRecovery) Level = 1;
	memset(&DB[DBRef], 0, sizeof(struct s_DB));
	::LeaveCriticalSection(&m_DBOpenCs[DBRef]);
	LogAdd(0, Level, "UnMounted DataBase", cstr);
	return true;
}

bool UnMountDB(char *cDBName)
{
	int DBRef;

	DBRef = FindDB(cDBName);
	if (DBRef < 0) return false;
	return UnMountDB(DBRef);
}

int MountDB(char* cDBName, bool CreateIfNotExists, bool DisableRecovery) // return DBRef=-1 zo error
{
	int DBRef;
	CString DBName;

	DBName = cDBName;
	DBName.MakeUpper();

	::EnterCriticalSection(&m_DBTableCs);
	for (DBRef = 0; DBRef < DB_MAX; DBRef++) {
		if (DBName.CompareNoCase(DB[DBRef].Name) == 0) break;
	}
	if (DBRef < DB_MAX) {
		DB[DBRef].OpenCount++;
		CString cstr;
		cstr.Format("%s (count is now=%d)", DB[DBRef].Name, DB[DBRef].OpenCount);
		LogAdd(0, 1, "Increased OpenCount Database", cstr);
		::LeaveCriticalSection(&m_DBTableCs);
		return DBRef;
	}
	LogAdd(0, 1, "Starting to mount DataBase", DBName);
	for (DBRef = 0; DBRef < DB_MAX; DBRef++) {
		if (DB[DBRef].Name[0] == 0) {
			sprintf_s(DB[DBRef].Name, sizeof(DB[0].Name) - 1, "%s", (LPCTSTR)DBName);
			break;
		}
	}
	if (DBRef == DB_MAX) {  // maximum aantal database in gebruik !
		LogAdd(21, 0, "DB_MAX number of databases in use", DB_MAX);
		::LeaveCriticalSection(&m_DBTableCs);
		return -1;
	}
	::LeaveCriticalSection(&m_DBTableCs);
	::EnterCriticalSection(&m_DBOpenCs[DBRef]);

	if (!EDBOpenDatabase(0, DBRef, CreateIfNotExists, DisableRecovery)) {
		memset(DB[DBRef].Name, 0, sizeof(DB[0].Name)); // wis de ingevulde naam !
		::LeaveCriticalSection(&m_DBOpenCs[DBRef]);
		return -1;
	}

	DB[DBRef].DBRef = DBRef;
	InitTab(DBRef);
	LogAdd(0, 1, "Tables Initialized, DBRef", DBRef);
	EDBCheckAndUpdateAndInit(DBRef);
	LogAdd(0, 1, "All Standard Tables are setup and checked");
	Fsd[DBRef].Updated = false;
	if (DB[DBRef].CreatedNew) {
		ImportFsd(DBRef); // Internal FSD is nodig om OLD-FAS te kunnen inlezen ...
		Fsd[DBRef].Updated = true;
	}
	ProcessInternalFsd(DBRef);
	for (int TabNr = 0; TabNr < DB[DBRef].TabCnt; TabNr++) {
		if (DB[DBRef].Tab[TabNr].StuNr) CheckAndUpdateTable(DBRef, TabNr);
	}
	LogAdd(0, 1, "All User Defined Tables are setup and checked");
	ReadStatsFromDB(DBRef);
	if (DB[DBRef].PreviousTimeNotClosed) {
		EDBCheckCalc(DBRef, true);
	}

	DB[DBRef].OpenCount++;
	DB[DBRef].Updated = true;
	::LeaveCriticalSection(&m_DBOpenCs[DBRef]);
	int Level = 0;
	if (DisableRecovery) Level = 1;
	LogAdd(0, Level, "Mounted DataBase", DB[DBRef].Name);

	return DBRef;
}

void ReOpenAllPreviousMountedDBs()
{
	// remove log-subdir
	CFileFind finder;
	CFile LogFile;
	CString cstr = PathDBLog + "*.log";
	BOOL bWorking = finder.FindFile(cstr);  // zoek alle bestanden in de xxx.log subdir
	while (bWorking) {
		bWorking = finder.FindNextFile();
		if (!finder.IsDirectory()) continue;
		MountDB((char *)(LPCTSTR)finder.GetFileTitle());
	}
	finder.Close();
}

bool TestFunc();

void InitDivers()
{
	int i;

	::InitializeCriticalSection(&m_DBTableCs);
	for (i = 0; i < DB_MAX; i++) {
		::InitializeCriticalSection(&m_DBOpenCs[i]);
		::InitializeCriticalSection(&m_DBRecsAddDeleteCs[i]);
	}
	InitConvertTab();

	for (int PostNr = 1; PostNr <= MAX_POST; PostNr++) {
		IsPostActive[PostNr - 1] = false;
		PostWnd[PostNr - 1] = NULL;
	}

	for (int i = 0; i < MAX_PROC; i++) {
		for (int j = 0; j < MAX_STRUCT; j++) {
			Proc2DBRef[i][j] = -1;
			Proc2DBRefOpened[i][j] = false;
		}
		Proc2ThdRef[i] = -1;
		Proc2SysRef[i] = -1;
	}

	for (int i = 0; i < MAX_SYSFILE; i++) {
		Sys[i].OpenCnt = 0;
		Sys[i].Ext = "";
		Sys[i].Name = "";
		Sys[i].PreMountBusyFlag = false;
		Sys[i].StdDossierFlag = false;
	}

	JetCommitBits = 0;
	if (theApp.iniFile.getKeyValue("JetCommitLazyFlushEnable", "DataBaseSettings").CompareNoCase("true") == 0) {
		JetCommitBits = JET_bitCommitLazyFlush;
		LogAdd(0, 0, "CommitLazyFlush is enabled ! Take care for dataloss ...");
	}
	CString cstr = theApp.iniFile.getKeyValue("LogFileMB", "DataBaseSettings");
	if (cstr.GetLength() > 0) DBLogFileMegaBytes = atoi(cstr);
	LogAdd(0, 1, "LogFileMB", DBLogFileMegaBytes);
	cstr = theApp.iniFile.getKeyValue("LogFileCacheMB", "DataBaseSettings");
	if (cstr.GetLength() > 0) DBLogCacheMegaBytes = atoi(cstr);
	LogAdd(0, 1, "LogFileCacheMB", DBLogCacheMegaBytes);
	cstr = theApp.iniFile.getKeyValue("MemCacheSizeMB", "DataBaseSettings");
	if (cstr.GetLength() > 0) DBMemCacheSizeMegaBytes = atoi(cstr);
	LogAdd(0, 1, "MemCacheSizeMB", DBMemCacheSizeMegaBytes);
	cstr = theApp.iniFile.getKeyValue("ExtendedLogging", "DataBaseSettings");
#ifndef JMSVIEWER
	if (cstr.GetLength() > 0 && cstr.Left(1) == "1") JmsExtendedLogging = true;
#endif
}

bool SysInit();
bool SysCloseAll();
bool SysClose(int file_ix);
void CreateAndUpdateCopy(int dummy);

void EDBStart(void *dummy)
{
	::CoInitialize(NULL);

	ServiceInfoMessage = "Starting Jamadata Server";

	LogAdd(0, 1, "");
	LogAdd(0, 0, "Startup");

#ifndef JMSVIEWER
	// InitHttpParms(); nu bij jms.cpp
  // _beginthread(HttpStart, 0, 0); gebeurt nu al via ONTIMER (timer1min)
#endif

	InitXls();
	InitDivers();
	if (!EDBInitEngine()) return; // 1;
	LogAdd(0, 0, "DataBase-Engine has been started");

#ifndef JMSVIEWER
	CheckFasForImport();
	CheckFiles2Restore();
	if (theApp.JmsCreateDBFromRestore) {
		CompareSignaturesDBvsCopy(true);
		CheckAllShaFileInRestore();
		CheckFsdChanged();
		PostMessage(theApp.m_pMainWnd->GetSafeHwnd(), WM_CLOSE, 0, 0);
		return;
	}
	CheckFsdChanged();

	ReOpenAllPreviousMountedDBs();
#endif
	ServiceInfoMessage = "Opening DataBase-Files";
	SysInit();

	MMFUsedCount = 5 * atol(theApp.iniFile.getKeyValue("PostCount", "JamaSettings"));
	LogAdd(0, 1, "Start for incoming event on shared memory connector, Count", MMFUsedCount);
	for (int ix = 0; ix < MMFUsedCount; ix++) {
		hListenThread[ix] = (HANDLE)_beginthread((void(*)(void*))ListenSharedMem, 0, (void*)ix);
	}
	_beginthread((void(*)(void*))ListenSharedMem, 0, (void*)MMF_COUNT); // voor BatchJobs ...

	pMainDlg->m_dDataBaseDlg.m_UpAndRunning = true;
	ServiceInfoMessage = "";
	theApp.ProgDidSomeWork = 0;
	if (JMSVersion == 'M') pMainDlg->OnTimer(TIMER1MIN);

	CFile fil;
	fil.Open("JMS.OK", CFile::modeCreate | CFile::modeWrite, 0);
	fil.Close();

	return; // 0;
}

/***********************************************************************
*
*  MessageBoxTimer
*
*      The timer callback function that posts the fake quit message.
*      This function causes the message box to exit because the message box
*      has determined that the application is exiting.
*
***********************************************************************/

HWND g_hwndTimedOwner;
BOOL g_bTimedOut;

void CALLBACK MessageBoxTimer(HWND hwnd, UINT uiMsg, UINT idEvent, DWORD dwTime)
{
	g_bTimedOut = TRUE;
	if (g_hwndTimedOwner) EnableWindow(g_hwndTimedOwner, TRUE);
	PostQuitMessage(0);
}


/***********************************************************************
*
*  TimedMessageBox
*
*      The same as the standard MessageBox, except that TimedMessageBox
*      also accepts a timeout. If the user does not respond within the
*      specified timeout, the value 0 is returned instead of one of the
*      ID* values.
*
***********************************************************************/
int TimedMessageBox(HWND hwndOwner,
	LPCTSTR pszMessage,
	LPCTSTR pszTitle,
	UINT flags,
	DWORD dwTimeout)
{
	UINT idTimer;
	int iResult;

	g_hwndTimedOwner = NULL;
	g_bTimedOut = FALSE;

	if (hwndOwner && IsWindowEnabled(hwndOwner))
		g_hwndTimedOwner = hwndOwner;

	//
	// Set a timer to dismiss the message box.
	idTimer = SetTimer(NULL, 0, dwTimeout, (TIMERPROC)MessageBoxTimer);

	iResult = MessageBox(hwndOwner, pszMessage, pszTitle, flags);

	//
	// Finished with the timer.
	KillTimer(NULL, idTimer);

	//
	// See if there is a WM_QUIT message in the queue if we timed out.
	// Eat the message so we do not quit the whole application.
	if (g_bTimedOut)
	{
		MSG msg;
		PeekMessage(&msg, NULL, WM_QUIT, WM_QUIT, PM_REMOVE);
		iResult = IDYES;
	}

	return iResult;
}

/*
void EDBTerminate()  // in case of emergency (at shutdown)
{
	int DBRef;
  JET_ERR _jeterr;

	// check if instance is actively using a database

  EmergencyExit=true;
  JMSShuttingDown=true;

  HANDLE hThread = (HANDLE)_beginthread(HttpStop, 0, NULL);
	for (DBRef=0; DBRef<DB_MAX; DBRef++) {
		if (!DB[DBRef].Name[0]) continue;
	  JetCallVoidRet(3301,JetTerm2(DB[DBRef].Instance,JET_bitTermComplete));

	// delete 'OpenFileFlag' in LOG-dir
	CString cstr=DB[DBRef].LogPath;
	cstr += "OpenFile.flg";
	_unlink(cstr);

	// Zet de last write time in de file op het tijdstip wanneer de laatste record geschreven werd ... wordt gebruikt voor backuptoestanden !
	double DateTimeUpdate=-1000;
	for (int TabIx=0; TabIx<DB[DBRef].TabCnt; TabIx++) {
	  if (DB[DBRef].Tab[TabIx].StuNr>0 && DB[DBRef].Tab[TabIx].DateTimeUpdate>DateTimeUpdate) {
		DateTimeUpdate=DB[DBRef].Tab[TabIx].DateTimeUpdate;
	  }
	}
	if (DateTimeUpdate>0) {
	  CFile DBFile;
	  DBFile.Open(DB[DBRef].NamePath,CFile::modeReadWrite,NULL);
	  SetFileLastWriteTime(DBFile.m_hFile,DateTimeUpdate);
	  DBFile.Close();
	}
	}
	SysClose("*");
  CloseSharedMemThreads();
	ReleaseBuffers();
	ExitXls();
	// frees the COM library
  ::CoUninitialize();
  LogAdd(0,0,"Ended");
  WaitForSingleObject(hThread, 10*1000);
  CloseHandle(hThread);
  return;
}
*/

bool EDBStop(bool TerminateFlag)
{
	int DBRef;

#ifdef JMSVIEWER
	TerminateFlag = true;
#endif
	if (JMSVersion != 'M') {
		if (!TerminateFlag) {
			// check if instance is actively using a database
			int BusyCount = 0, CriticalCount = 0;
			for (int ProcId = 0; ProcId < MAX_PROC; ProcId++) {
				if (ProcCurrentState[ProcId] == 1) BusyCount++;
				if (ProcCurrentState[ProcId] == 2) CriticalCount++;
			}

			if ((BusyCount + CriticalCount) > 0 && !theApp.JmsTestConfigFlag && !theApp.JmsExternalControlled) {
				CString MsgText = "Kan de server niet afsluiten, want er zijn nog :\r\n\r\n";
				CString CountText;
				CountText.Format("   %3d", BusyCount + CriticalCount);
				MsgText += CountText + " post(en) actief";
				if (CriticalCount) {
					CountText.Format(" (%d in kritische fase)", CriticalCount);
					MsgText += CountText;
				}
				MsgText += " !\r\n\r\nWenst u toch af te sluiten (enkel voor noodgevallen !) ?\r\n";
				CString MsgCaption = "Sluiten JMS : opgelet !";
				pMainDlg->ShowWindow(SW_SHOW);

				int TimeOut = 20000; // 20 seconden wachten zo iemand bezig is
				if (CriticalCount) TimeOut = 60000; // 60 seconden zo critical section !
				int ret = TimedMessageBox(pMainDlg->GetSafeHwnd(), MsgText, MsgCaption, MB_YESNOCANCEL, TimeOut);

				if (ret != IDYES) return false;
			}
		}
		else EmergencyExit = true;
	}

	JMSShuttingDown = true;
#ifndef JMSVIEWER
	HANDLE hThread = (HANDLE)_beginthreadex(0, 0, HttpStop, 0, 0, 0);
#endif

	for (DBRef = 0; DBRef < DB_MAX; DBRef++) {
		if (!DB[DBRef].Name[0]) continue;
		EDBEndAllSessions(DBRef);
		DB[DBRef].OpenCount = 1;
		UnMountDB(DBRef);
	}
	CloseSharedMemThreads();
	ReleaseBuffers();
	ExitXls();
	SysCloseAll();
	// frees the COM library
	::CoUninitialize();
	LogAdd(0, 0, "Ended");
#ifndef JMSVIEWER
	DWORD dwRet = WaitForSingleObject(hThread, 10 * 1000);
	try {
		if (dwRet == WAIT_TIMEOUT) TerminateThread(hThread, 1);
	}
	catch (...) {}
	CloseHandle(hThread);
#endif
	return true;
}

/////////////////////////////////////
//  Vervaldag
/////////////////////////////////////

/* gedeelte vervaldag */
#define FILLEN          136
#define FILTIME         0x12B2A0A0/* 180589 */

struct {
	long dt_72;
	unsigned short version;
	unsigned short dt_huid;
	unsigned short volgnr_dt;
	char reser[24];
	unsigned short dt_sys;
	unsigned short dt_prot;
	unsigned short dt_protEM;
	unsigned short klantkod;
	unsigned short cnt_waarsch;
} vv_sys;

struct {
	long dt_72;
	unsigned short version;
	char reser[24];
	unsigned short exclusiv;
	unsigned short klantkod;
	char XOR_chk;
} vv_prot;

struct {
	unsigned char known1;
	long dt_72;
	unsigned short version;
	unsigned char reser1[24];
	unsigned char known2;
	unsigned short cnt_illeg;
	unsigned short cnt_waarsch;
	unsigned short cnt_sameday;
	unsigned short dt_last;
	unsigned char reser2[10];
	unsigned char known3;
	unsigned char XOR_chk;
} vv_protEM;

struct {
	long dt_72;
	unsigned short version;
} vv_ok;

CFile vv_fil;
char dummy;
unsigned short int vv_yettst, vv_vv_err, vv_78;
short int vv_akt_q;

long getft(HANDLE hFile)
{
	long ft;
	unsigned short timeval, dateval;
	FILETIME ftWrite;

	memset(&ftWrite, 0, sizeof(FILETIME));
	int ret = GetFileTime(hFile, NULL, NULL, &ftWrite);
	FileTimeToDosDateTime(&ftWrite, &dateval, &timeval);
	ft = dateval * 0x10000 + timeval;
	return ft;
}

unsigned chgft(HANDLE hFile, long ft)
{
	unsigned short timeval, dateval;
	FILETIME ftWrite;
	unsigned ret;

	dateval = (unsigned short)(ft / 0x10000); timeval = (unsigned short)(ft % 0x10000);
	DosDateTimeToFileTime(dateval, timeval, &ftWrite);
	ret = SetFileTime(hFile, NULL, &ftWrite, &ftWrite);
	if (ret) ret = 0xFFFFFFFF;
	else ret = 0;
	return ret;
}

char vv_chkxor(char *ps, int len)
{
	char byte = '\0';

	while (len--) byte ^= *(ps++);
	return (int)byte;
}

void cdv(void *ps, void *pd)
{
	memcpy(pd, ps, sizeof vv_prot.dt_72 + sizeof vv_prot.version);
}

unsigned short get_dt(long *pl_)
{
	return (unsigned short)((*pl_ - 2) / 7);
}

void vv_mk_EM(void *ps)
/* indien ps==&vv_protEM.dt_72, wordt er geen datum ingevuld (wordt immers
   eerst via zeros op 0 gezet, en daarna op zichzelf gekopieerd */
{
	memset(&vv_protEM, 0, sizeof vv_protEM);
	vv_protEM.known1 = 0x63; vv_protEM.known2 = 0xD9; vv_protEM.known3 = 0x7D;
	cdv(ps, &vv_protEM.dt_72);
	vv_protEM.XOR_chk = vv_chkxor((char *)&vv_protEM, sizeof vv_protEM);
}

void vv_chk72(long *pl)
{
	if (*pl) {
		if ((*pl - 2) % 7) {
			vv_78 = YES;
			*pl = 0;
		}
	}
}

void vv_open()
{
	CString ProgJamName = PathSeq + "prog.jam";
	vv_fil.Open(ProgJamName, CFile::modeReadWrite, 0);
	if (vv_fil.m_hFile != CFile::hFileNull) {/* wat bij error ???? */
		if (getft(vv_fil.m_hFile) != FILTIME) vv_78 = YES;
		/* if(dseek(vv_filno,0L,2)!=FILLEN) vv_78=YES; 07/03/05 */
		vv_fil.Seek(56L, 0);
		vv_fil.Read(&vv_prot, sizeof vv_prot);
		if (vv_chkxor((char *)&vv_prot, sizeof vv_prot)) vv_78 = YES;
		vv_fil.Seek(1026L, 0);
		vv_fil.Write(&dummy, 1);
		vv_fil.Seek(647L, 0);
		vv_fil.Read(&vv_protEM, sizeof vv_protEM);
	}
}

void vv_close()
{
	vv_protEM.known1 = 0x63; vv_protEM.known2 = 0xD9; vv_protEM.known3 = 0x7D;
	vv_prot.XOR_chk = 0; vv_protEM.XOR_chk = 0;
	if (vv_78) vv_protEM.cnt_illeg = 50;
	vv_prot.XOR_chk = vv_chkxor((char *)&vv_prot, sizeof vv_prot);
	vv_protEM.XOR_chk = vv_chkxor((char *)&vv_protEM, sizeof vv_protEM);
	vv_fil.Seek(647L, 0);
	vv_fil.Write(&vv_protEM, sizeof vv_protEM);
	vv_fil.Seek(56L, 0);
	vv_fil.Write(&vv_prot, sizeof vv_prot);
	vv_fil.Seek((long)FILLEN, 0);
	/* dwrite(vv_filno,&dummy,0); 07/02/05 cut rest of file */
	chgft(vv_fil.m_hFile, FILTIME);
	vv_fil.Close();
	CString ProgJamName = PathSeq + "prog.jam";
	SetFileAttributes(ProgJamName, 0xFFFFFFDF & GetFileAttributes(ProgJamName));
}

void vv_kriter()
{
	int k, q_ = 0;
	long *pl[3], *p_recent;

	pl[0] = &vv_sys.dt_72; pl[1] = &vv_prot.dt_72; pl[2] = &vv_protEM.dt_72;
	for (k = 0; k < 3; k++) { vv_chk72(pl[k]); if (*pl[k]) q_++; }
	if (q_) {/*!A*/
		if (q_ != 3) {
			if (vv_protEM.dt_72 == 0 && vv_sys.dt_72 != vv_prot.dt_72) {/*B*/
				cdv(&vv_sys.dt_72, &vv_protEM.dt_72);
				if (vv_prot.dt_72 && vv_prot.dt_72 < vv_protEM.dt_72)
					cdv(&vv_prot.dt_72, &vv_protEM.dt_72);
			}
			p_recent = pl[0];
			for (k = 1; k < 3; k++) if (*p_recent < *pl[k]) p_recent = pl[k];
			for (k = 0; k < 3; k++) if (*pl[k] == 0) cdv(p_recent, pl[k]);/*C*/
		}/*D*/
		if (vv_sys.dt_72 == vv_prot.dt_72) cdv(&vv_sys.dt_72, &vv_protEM.dt_72);
		if (vv_sys.dt_72 == vv_protEM.dt_72) cdv(&vv_sys.dt_72, &vv_prot.dt_72);
		if (vv_prot.dt_72 == vv_protEM.dt_72) {
			cdv(&vv_prot.dt_72, &vv_sys.dt_72);
			LogAdd(0, 1, "vv_kriter errnr=YES;");
		}
		if (vv_sys.dt_72 != vv_prot.dt_72) vv_vv_err = 2;/*E*/
		else {
			cdv(&vv_sys.dt_72, &vv_ok.dt_72);/*F*/
			if (get_dt(&vv_ok.dt_72) < vv_sys.dt_huid) vv_vv_err = 2;
		}
	}
}


void vervaldag(int mode_, char *msgbuf)
{
	if (mode_ == 500) {
		memcpy((char *)&vv_sys, &msgbuf[6], 10);
		if (vv_yettst) {
			if (vv_ok.dt_72 && vv_ok.dt_72 != vv_sys.dt_72) {
				cdv(&vv_ok.dt_72, &vv_sys.dt_72);
				LogAdd(15, 0, "Vervaldag errnr=YES");
			}
		}
		else {
			vv_open();
			if (vv_prot.exclusiv == 42933) {
				vv_mk_EM(&vv_prot.dt_72);
				cdv(&vv_prot.dt_72, &vv_sys.dt_72);
				vv_prot.exclusiv = 52921;
				LogAdd(0, 1, "Vervaldag errnr=YES;");
			}
			if (vv_protEM.known1 == 0x63 && vv_protEM.known2 == 0xD9 && vv_protEM.known3 == 0x7D) {
				if (vv_chkxor((char *)&vv_protEM, sizeof vv_protEM)) vv_78 = YES;
			}
			else vv_mk_EM(&vv_protEM.dt_72);/* dus datum 0 invullen ! */
			vv_kriter();
			if (!vv_vv_err) {
				vv_protEM.cnt_sameday = 0; vv_protEM.cnt_waarsch = 0;
			}
			else {
				if (vv_sys.dt_huid == vv_protEM.dt_last) {
					if (++vv_protEM.cnt_sameday == 5) vv_protEM.cnt_sameday = 0;
					else vv_vv_err = NO;
				}
				if (vv_vv_err) if (++vv_protEM.cnt_waarsch > 10) vv_vv_err = 3;
			}
			vv_close();
			vv_yettst = YES;
		}
	}
	if (mode_ == 501) {
		vv_sys.dt_sys = get_dt(&vv_sys.dt_72);
		vv_sys.dt_prot = get_dt(&vv_prot.dt_72);
		vv_sys.dt_protEM = get_dt(&vv_protEM.dt_72);
		vv_sys.klantkod = vv_prot.klantkod;
		vv_sys.cnt_waarsch = vv_protEM.cnt_waarsch;
	}
	if (mode_ == 502) {
		vv_open();
		vv_sys.dt_72 = (*(unsigned *)&msgbuf[6]) * 7L + 2;
		vv_prot.dt_72 = vv_sys.dt_72;
		vv_mk_EM(&vv_sys.dt_72); vv_78 = 0;
		vv_close();
	}
}

//////////////////////////////////////
//  FASFunctions
/////////////////////////////////////

CFile fil_seq[MAX_PRC][3];
FILETIME fil_LastWriteTime[MAX_PRC][3];
bool fil_seq2Post[MAX_PRC][3];

struct sSrh {
	bool active;
	CFileFind findfile;
	BOOL bWorking;
} Srh[MAX_PRC];

unsigned seq2prc[MAX_PRC];

bool FasReturn(int ThdRef, int retval, int extlen, char *extra)
{
	UNALIGNED struct sComBuf *ComBuf;
	ComBuf = (struct sComBuf*)Thd[ThdRef].ComBuf;

	// return true; // TestFunc

	if (extlen > 2000) {
		int i = 0;
	}
	ComBuf->Function = 0;
	*(short *)&ComBuf->Info[0] = retval;         // return 6/0;
	if (extlen) memmove(ComBuf->Info + 2, extra, extlen);
	Thd[ThdRef].ReplyLength = 2 + extlen; // indicate that a reply is ready tot send

	return true;
}



bool FasReturn(int ThdRef, int fuval, unsigned retval)
{
	return FasReturn(ThdRef, fuval, 4, (char *)&retval);
}

bool FasReturn(int ThdRef, int fuval)
{
	return FasReturn(ThdRef, fuval, 0, 0);
}

bool FasReturn(int ThdRef, int fuval, int retval)
{
	return FasReturn(ThdRef, fuval, 4, (char *)&retval);
}

int getseqix(int req_proc, int create_fl)
{
	int seqix;
	for (seqix = 0; seqix < MAX_PRC; seqix++) {
		if (req_proc == (int)seq2prc[seqix]) break;
		if (0 == seq2prc[seqix]) {
			if (create_fl) seq2prc[seqix] = req_proc;
			else seqix = -1;
			break;
		}
	}
	if (seqix == MAX_PRC) {
		seqix = MAX_PRC - 1;
		LogAdd(12, 0, "Seq2Prc table is full, cannot add", req_proc);
	}
	return seqix;
}

bool FasSeqi(int ThdRef)
{
	int k, errnr = 0, chan_, len_;
	long lpos_;
	char buf[1050];
	UNALIGNED struct sComBuf *ComBuf;
	ComBuf = (struct sComBuf*)Thd[ThdRef].ComBuf;

	errnr = 54;
	chan_ = *(UNALIGNED short int *)&ComBuf->Info[2];
	if (chan_ < 1 || chan_>3) {
		LogAdd(13, 0, "Invalid chan in FasSeqi, only 1,2 or 3 but received", chan_);
		return FasReturn(ThdRef, 0);
	}
	int seqix = getseqix(ComBuf->OrigId, NO);
	if (seqix < 0) return FasReturn(ThdRef, 2022);
	len_ = *(UNALIGNED short int *)&ComBuf->Info[4] - 4;
	lpos_ = *(unsigned long *)&ComBuf->Info[6];
	try {
		if (lpos_ == fil_seq[seqix][chan_ - 1].Seek(lpos_, CFile::begin)) {
			memset(buf, 0, len_ + 20);
			k = fil_seq[seqix][chan_ - 1].Read(&buf[4], len_);
			if (k > 0) {
				*(unsigned long *)&buf[0] = lpos_ + k;
				return FasReturn(ThdRef, 0, len_ + 4, buf);
			}
		}
	}
	catch (...) {}
	return FasReturn(ThdRef, errnr);
}

bool FasSeqo(int ThdRef)
{
	UNALIGNED struct sComBuf *ComBuf;
	ComBuf = (struct sComBuf*)Thd[ThdRef].ComBuf;

	int chan_;
	chan_ = *(UNALIGNED short int *)&ComBuf->Info[2];
	int seqix = getseqix(ComBuf->OrigId, NO);
	if (seqix < 0) return FasReturn(ThdRef, 2022);
	long pos = *(long *)&ComBuf->Info[6];

	if (pos == -1L) {
		/// Indien pos==0xFFFFFFFF dan restore originele timestamp op file (datum & uur)
		SetFileTime(fil_seq[seqix][chan_ - 1].m_hFile, NULL, NULL, &fil_LastWriteTime[seqix][chan_ - 1]);
	}
	else {
		if (chan_ == 3) {
			if (pos > fil_seq[seqix][chan_ - 1].GetLength()) {
				fil_seq[seqix][chan_ - 1].Seek(0, CFile::end);
				ULONGLONG ToAdd = pos - fil_seq[seqix][chan_ - 1].GetLength();
				while (ToAdd-- > 0) {
					fil_seq[seqix][chan_ - 1].Write("\0", 1);
				}
			}
			fil_seq[seqix][chan_ - 1].Seek(pos, CFile::begin);
		}
		fil_seq[seqix][chan_ - 1].Write(&ComBuf->Info[10], *(UNALIGNED short int *)&ComBuf->Info[4] - 4);
	}
	return FasReturn(ThdRef, 0);
}

void CloseFilSeq(int seqix, int chan, int PostNr)
{
	CString FilePath = fil_seq[seqix][chan].GetFilePath();
	CString FileName = fil_seq[seqix][chan].GetFileName();
	fil_seq[seqix][chan].Close();
	if (fil_seq2Post[seqix][chan]) {
		CString ToClientPostFileName, ToClientPost;
		ToClientPost.Format("%sPost-%03d\\", PathSpoolToClient, PostNr);
		if (JMSVersion == 'M') ToClientPost = PathSpool + "Received\\";
		CreateDirectory(ToClientPost, NULL);
		ToClientPostFileName = ToClientPost + FileName;
		CopyFile(FilePath, ToClientPostFileName, FALSE);
		_unlink(FilePath);
		if (theApp.JmsTestConfigFlag) {
			::ShellExecute(NULL, NULL, ToClientPost, NULL, NULL, SW_SHOW);
		}
		else if (JMSVersion == 'M') {
			HWND JMD = FindWindow("THE_JMD", NULL);
			if (JMD) PostMessage(JMD, WM_USER + 5, 0, 0); // 0x405, 0, 0); // PROC_RECEIVED_FILES -> de JMD moet deze file verwerken !									
		}
		else {
			if (PostWnd[PostNr - 1] == 0) {
				LogAdd(110, 0, "hWnd for JMH not filled in, so Txmit of File slow for PostNr=", PostNr);
			}
			else PostMessage(PostWnd[PostNr - 1], WM_USER + 2, 0, 0); // proc_send2peer ...
			if (JmsExtendedLogging) {
				CString cstr;
				cstr.Format("Txfer to Post-%03d = %s", PostNr, ToClientPostFileName);
				LogAdd(0, 1, cstr);
			}
		}
	}
}

bool FasOpen(int ThdRef)
{
	int k, errnr = 0;
	flag add_path = YES;
	unsigned mode_;
	int seqix, DBRef;
	CString cstr;
	int ProcId, SysRef;

	UNALIGNED struct sComBuf *ComBuf;
	ComBuf = (struct sComBuf*)Thd[ThdRef].ComBuf;
	int strunr = *(short *)&ComBuf->Info[0];

	// StuNr zit in ComBuf->StuNr

	switch (strunr) {
	case 0:
		ProcId = ComBuf->OrigId;
		if (ProcId < 0 || ProcId >= MAX_PROC) {
			LogAdd(1, 0, "FileOpen received from unknown ProcId", ProcId);
			return FasReturn(ThdRef, 1); // bestand niet te vinden ...
		}
		if (JMSServiceMode) return FasReturn(ThdRef, 1);

		SysRef = Proc2SysRef[ProcId];
		if (SysRef < 0 || SysRef >= MAX_SYSFILE) {
			SysRef = ReOpenLastSysFile(ThdRef);
			if (SysRef == -1) {
				LogAdd(1, 0, "FileOpen received but Sys-file was not opened and could not reopen it, for this ProcId", ProcId);
				return FasReturn(ThdRef, 1); // SysFile was niet open
			}
		}
		int i;
		for (i = 0; i < 120; i++) {
			if (!Sys[SysRef].PreMountBusyFlag) break;
			Sleep(500);
			pMainDlg->ProcessAllMessages();
		}
		if (i == 120) {
			LogAdd(1, 0, "DB was attached but Pre-Mount was not done within 60 seconds, sys=", Sys[SysRef].Ext);
			return false;
		}
		if (ComBuf->Info[2] == 0) return FasReturn(ThdRef, 1);
		DBRef = FindDB(&ComBuf->Info[2]);
		if (DBRef == -1) return FasReturn(ThdRef, 1);
		EDBInitSession(ThdRef, DBRef);
		return FasReturn(ThdRef, 0);
		break;
	case 99:
		_chdir(PathSeq);
		remove(&ComBuf->Info[2]);
		return FasReturn(ThdRef, 0);
		break;
	case 100:
		_chdir(PathSeq);
		cstr = &ComBuf->Info[2];
		k = cstr.Find("|");
		if (k > 0) MoveFile(cstr.Left(k), cstr.Mid(k + 1));
		return FasReturn(ThdRef, 0);
		break;
	case 101:
		_chdir(PathSeq);
		cstr = &ComBuf->Info[2];
		k = cstr.Find("|");
		if (k > 0) CopyFile(cstr.Left(k), cstr.Mid(k + 1), FALSE);
		return FasReturn(ThdRef, 0);
		break;
	case 102:
		_chdir(PathSeq);
		seqix = getseqix(ComBuf->OrigId, YES);
		if (Srh[seqix].active) {
			Srh[seqix].findfile.Close();
			Srh[seqix].active = false;
		}
		Srh[seqix].bWorking = Srh[seqix].findfile.FindFile(&ComBuf->Info[2]);
		if (!Srh[seqix].bWorking) return FasReturn(ThdRef, 203);
		Srh[seqix].active = true;
		return FasReturn(ThdRef, 0);
		break;
	case 103:
		_chdir(PathSeq);
		SetFileAttributes(&ComBuf->Info[4], 0xFFFFFFDF & GetFileAttributes(&ComBuf->Info[2]));
		return FasReturn(ThdRef, 0);
		break;
	case 0x8000:
		return FasReturn(ThdRef, 0);
		break;
	}

	_chdir(PathSeq);
	bool Send2Post = false;
	if (strunr >= 11 && strunr <= 13) {
		Send2Post = true;
		strunr -= 10;
	}
	if (strunr >= 1 && strunr <= 3) {
		int seqix = getseqix(ComBuf->OrigId, YES);
		strunr--; // LET OP : FasOpen(2) wordt hier strunr=1 !! (dus 12 wordt 11)
		if (strunr == 0)      mode_ = CFile::modeRead | CFile::shareDenyNone; // allow other read, but no writes 
		else if (strunr == 1) mode_ = CFile::modeReadWrite | CFile::modeCreate; // must be able to write to file and create/truncate if exist 
		else                mode_ = CFile::modeReadWrite | CFile::modeCreate | CFile::modeNoTruncate;/* must be able to write to file */
		if (fil_seq[seqix][strunr].m_hFile != CFile::hFileNull) {
			CloseFilSeq(seqix, strunr, 1 + ComBuf->OrigId / 5);
		}
		fil_seq2Post[seqix][strunr] = false;
		if (Send2Post) {
			// Find free TmpNumber ....
			CString TempFilePath;
			CString TmpNumberFilePath = PathSpoolFiles + "TempNr.Jam";
			CFile TmpNumberFile;
			int TempRefNr = 1;
			if (GetFileAttributes(TmpNumberFilePath) == INVALID_FILE_ATTRIBUTES) {
				if (TmpNumberFile.Open(TmpNumberFilePath, CFile::modeCreate | CFile::modeWrite, NULL)) {
					TmpNumberFile.Write(&TempRefNr, 4);
					TmpNumberFile.Close();
				}
			}
			SetFileAttributes(TmpNumberFilePath, FILE_ATTRIBUTE_HIDDEN);
			for (int Cnt = 1; Cnt < 500; Cnt++) {
				if (TmpNumberFile.Open(TmpNumberFilePath, CFile::modeReadWrite, NULL)) {
					TmpNumberFile.Read(&TempRefNr, 4);
					if (TempRefNr == 0x7FFFFFFF) TempRefNr = 1;
					else TempRefNr++;
					TmpNumberFile.Seek(0L, CFile::begin);
					TmpNumberFile.Write(&TempRefNr, 4);
					TmpNumberFile.Close();
					break;
				}
				Sleep(50);
			}
			if (TempRefNr) {
				TempFilePath.Format("%s%08X-$%s", PathSpoolTemp, TempRefNr, &ComBuf->Info[2]);
			}
			else TempFilePath = &ComBuf->Info[2];
			fil_seq[seqix][strunr].Open(TempFilePath, mode_, 0);
			fil_seq2Post[seqix][strunr] = true;
		}
		else fil_seq[seqix][strunr].Open(&ComBuf->Info[2], mode_, 0);
		if (fil_seq[seqix][strunr].m_hFile == CFile::hFileNull) {
			//LogAdd(12,0,"FasOpen Sequential failed",(char *)&ComBuf->Info[2]); 
			errnr = 1;
		}
		GetFileTime(fil_seq[seqix][strunr].m_hFile, NULL, NULL, &fil_LastWriteTime[seqix][strunr]);
	}
	else {
		LogAdd(11, 0, "FasOpen received with Mode", strunr);
		errnr = 1;
	}

	return FasReturn(ThdRef, errnr);
}

bool FasUnlock(int ThdRef)
{
	int ret = 0;
	short *psi;
	UNALIGNED struct sComBuf *ComBuf;
	ComBuf = (struct sComBuf*)Thd[ThdRef].ComBuf;
	psi = (short int*)ComBuf->Info;

	int PostNr = 1 + (ComBuf->OrigId / 5);
	if (*psi < 0 && PostNr >= 1 && PostNr <= MAX_POST) IsPostActive[PostNr - 1] = true;

	switch (*psi) {
	case  0: ProcCurrentState[ComBuf->OrigId] = 0; break;
	case -1: ProcCurrentState[ComBuf->OrigId] = 1; break;
	case -2: ProcCurrentState[ComBuf->OrigId] = 2; break;
	}
	return FasReturn(ThdRef, ret);
}

bool FasClose(int ThdRef)
{
	int i;
	short *psi;
	UNALIGNED struct sComBuf *ComBuf;
	ComBuf = (struct sComBuf*)Thd[ThdRef].ComBuf;
	psi = (short int*)ComBuf->Info;

	if (*psi == 0) { // fasclose van alle structuren voor deze gebruiker ...
		int DBRef;
		for (int StuNr = 0; StuNr < MAX_STRUCT; StuNr++) {
			DBRef = Proc2DBRef[ComBuf->OrigId][StuNr];
			if (DBRef >= 0) EDBCloseSession(ThdRef, DBRef);
		}
		return FasReturn(ThdRef, 0);
	}

	if (*psi > 0 && *psi < MAX_STRUCT) {   // fasclose(StuNr)
		int DBRef = Proc2DBRef[ComBuf->OrigId][*psi];
		if (DBRef >= 0) {
			EDBCloseSession(ThdRef, DBRef);
		}
		return FasReturn(ThdRef, 0);
	}

	int seqix = getseqix(ComBuf->OrigId, NO);
	if (seqix < 0) return FasReturn(ThdRef, 0); // nog geen files geopend

	CString FileName, FilePath;
	switch (*psi) {
	case -2:
	case -5:
		for (i = 0; i < 3; i++) {
			if (fil_seq[seqix][i].m_hFile != CFile::hFileNull) {
				if (*psi == -5 && i == 1) {
					FileName = fil_seq[seqix][i].GetFileName();
					FilePath = fil_seq[seqix][i].GetFilePath();
				}
				CloseFilSeq(seqix, i, 1 + ComBuf->OrigId / 5);
			}
		}
		if (FilePath.GetLength()) {
			CString TempFilePath;
			CFile TmpNumberFile;
			CString TmpNumberFilePath;
			int TempRefNr;
			// Attempt to save the file
			TmpNumberFilePath = PathSpoolFiles + "TempNr.Jam";
			if (GetFileAttributes(TmpNumberFilePath) == INVALID_FILE_ATTRIBUTES) {
				if (TmpNumberFile.Open(TmpNumberFilePath, CFile::modeCreate | CFile::modeWrite, NULL)) {
					TmpNumberFile.Write(&TempRefNr, 4);
					TmpNumberFile.Close();
				}
			}
			SetFileAttributes(TmpNumberFilePath, FILE_ATTRIBUTE_HIDDEN);
			for (int Cnt = 1; Cnt < 500; Cnt++) {
				if (TmpNumberFile.Open(TmpNumberFilePath, CFile::modeReadWrite, NULL)) {
					TmpNumberFile.Read(&TempRefNr, 4);
					if (TempRefNr == 0x7FFFFFFF) TempRefNr = 1;
					else TempRefNr++;
					TmpNumberFile.Seek(0L, CFile::begin);
					TmpNumberFile.Write(&TempRefNr, 4);
					TmpNumberFile.Close();
					break;
				}
				Sleep(50);
			}
			if (TempRefNr) {
				TempFilePath.Format("%s%08X-$%s", PathSpoolFiles, TempRefNr, FileName);
				MoveFileEx(FilePath, TempFilePath, MOVEFILE_REPLACE_EXISTING);
				return FasReturn(ThdRef, TempRefNr);
			}
		}
		return FasReturn(ThdRef, 0);
		break;
	case -3:
	case -4:
		// MVG nog te doen ! for (i=0; alle databases overlopen en aanduiden dat de file niet meer in gebruik is !
		return FasReturn(ThdRef, 0);
		break;

	}

	return FasReturn(ThdRef, 0);
}

bool GetStatistics(int ThdRef)
{
	struct _stu_i *stu_i;
	char *p;
	short *psi;
	int RetVal = 0, RecNr = 0;
	UNALIGNED struct sComBuf *ComBuf;
	ComBuf = (struct sComBuf*)Thd[ThdRef].ComBuf;

	psi = (short int*)&ComBuf->Info[0];
	int StuNr = *psi++;
	int Cmd = *psi;

	int DBRef = -1;
	if (ComBuf->OrigId < MAX_PROC) DBRef = Proc2DBRef[ComBuf->OrigId][StuNr];
	if (DBRef < 0) {
		DBRef = ReOpenOnTheFly(ThdRef, StuNr);
		if (DBRef < 0) return FasReturn(ThdRef, 46);
	}

	int TabIx = DB[DBRef].Stu2Tab[StuNr];

	if (DB[DBRef].Tab[TabIx].StructLen == 0) return FasReturn(ThdRef, 0, RetVal);

	switch (Cmd) {
	case 1:
		RetVal = DB[DBRef].Tab[TabIx].LastRec;
		break;
	case 2:
		RetVal = DB[DBRef].Tab[TabIx].MaxRec;
		if (!EnableEnhancedFlag) {
			if (RetVal > 0xFFFF) RetVal = 0xFFFF;
		}
		else RetVal -= DB[DBRef].Tab[TabIx].UsedRec;
		break;
	case 3:
		RetVal = DB[DBRef].Tab[TabIx].MaxRec;
		if (!EnableEnhancedFlag) {
			if (RetVal > 0xFFFF) RetVal = 0xFFFF; // maximum getal
		}
		break;
	case 4:
		RetVal = DB[DBRef].Tab[TabIx].LastRec - DB[DBRef].Tab[TabIx].UsedRec;
		break;
	case 5:
		p = (char *)DB[DBRef].Tab[TabIx].FasStu_i;
		p += DB[DBRef].Tab[TabIx].FasStu_i->len;
		stu_i = (struct _stu_i *)p;
		if (stu_i->len == 0) RetVal = 0;
		else RetVal = stu_i->ref;
		break;
	case 6:
		RetVal = DB[DBRef].Tab[TabIx].UsedRec;
		if (JmsExtendedLogging) {
			CString cstr;
			cstr.Format("StuNr=%3d DBRef=%3d ThdRef=%3d ProcId=%3d RecUsed=%7d", StuNr, DBRef, ThdRef, ComBuf->OrigId, RetVal);
			LogAdd(0, 1, "Fasinfo-6", cstr);
		}
		break;
	case 7:
		return FasReturn(ThdRef, 0, strlen(DB[DBRef].Tab[TabIx].StructName) + 1, DB[DBRef].Tab[TabIx].StructName);
		break;
	}

	return FasReturn(ThdRef, 0, RetVal);
}

bool FasInfo(int ThdRef)
{
	int seqix, retcd = 0;
	CTime t;
	CString cstr;
	short *psi;
	unsigned seconds;
	SYSTEMTIME ST;
	UNALIGNED struct sComBuf *ComBuf;
	ComBuf = (struct sComBuf*)Thd[ThdRef].ComBuf;

	psi = (short int*)&ComBuf->Info[0];
	int StuNr = *psi++;
	int Cmd = *psi;

	// StuNr zit in ComBuf->StuNr

	switch (Cmd) {
	case 1:
	case 2:
	case 3:
	case 4:
	case 5:
	case 6:
	case 7:
		return GetStatistics(ThdRef);
		break;
	case 101: return FasReturn(ThdRef, 0); break; // many del aanzetten ...
	case 201:
		return FasReturn(ThdRef, 0, dateget());
		break;
	case 202:
		SetSystemTime(&ST);
		seconds = ((ST.wHour * 60) + ST.wMinute) * 60 + ST.wSecond;
		return FasReturn(ThdRef, 0, seconds);
		break;
	case 203:
		return FasReturn(ThdRef, 0, 0);
		break; // aantal actieve gebruikers ...
	case 204:
		seqix = getseqix(ComBuf->OrigId, NO);
		if (!Srh[seqix].active) return FasReturn(ThdRef, 0, 1, "");
		if (!Srh[seqix].bWorking) {
			Srh[seqix].active = false;
			return FasReturn(ThdRef, 0, 1, "");
		}
		Srh[seqix].bWorking = Srh[seqix].findfile.FindNextFile();
		cstr = Srh[seqix].findfile.GetFileName();
		return FasReturn(ThdRef, 0, cstr.GetLength(), (char *)(LPCTSTR)cstr);
		break;
	case 205:
		seqix = getseqix(ComBuf->OrigId, NO);
		if (!Srh[seqix].active) return FasReturn(ThdRef, 0);
		Srh[seqix].findfile.GetLastWriteTime(t);
		cstr = t.Format("%d/%m/%Y %H:%M:%S");
		return FasReturn(ThdRef, 0, cstr.GetLength(), (char *)(LPCTSTR)cstr);
		break;
	case 206:
		seqix = getseqix(ComBuf->OrigId, NO);
		if (!Srh[seqix].active) return FasReturn(ThdRef, 0);
		return FasReturn(ThdRef, 0, (unsigned int)Srh[seqix].findfile.GetLength());
		break;
	case 207:
		EnableEnhancedFlag = true;
		return FasReturn(ThdRef, 0, 1); // 1 is EDBMngr als database
		break;
	case 1001:
		if (vv_akt_q) {
			if (vv_vv_err >= 2) { retcd = vv_vv_err; vv_vv_err = 0; }
			else if ((vv_akt_q & 0x003F) == 0) retcd = vv_78;
		}
		return FasReturn(ThdRef, 0, retcd);
		break;
	case 1101:
	case 1102:
	case 1103:
		if (Cmd == 1101) vv_78 = YES; else vv_vv_err = Cmd - 1100;
		vv_akt_q = 1;
		return FasReturn(ThdRef, 0);
		break;
	}

	LogAdd(10, 0, "Fasinfo received with command", Cmd);
	return FasReturn(ThdRef, 0); // om blokkage tegen te gaan, zou normaal niet mogen voorkomen.

}

bool FasGetu(int ThdRef)
{
	int StuNr, RecNrLen;
	unsigned long retlen;
	unsigned RecNr;
	char *p;
	UNALIGNED struct sComBuf *ComBuf;
	JET_ERR _jeterr;

	ComBuf = (struct sComBuf*)Thd[ThdRef].ComBuf;
	StuNr = *(short *)&ComBuf->Info[0];
	int DBRef = -1;
	if (ComBuf->OrigId < MAX_PROC) DBRef = Proc2DBRef[ComBuf->OrigId][StuNr];
	if (DBRef < 0) {
		DBRef = ReOpenOnTheFly(ThdRef, StuNr);
		if (DBRef < 0) return FasReturn(ThdRef, 46);
	}
	if (!Proc2DBRefOpened[ComBuf->OrigId][StuNr]) {
		CString cstr;
		cstr.Format("ProcId=%d did FasGet on StuNr=%d without opening a file (%s was still open)", ComBuf->OrigId, StuNr, DB[DBRef].Name);
		LogAdd(109, 0, cstr);
		Proc2DBRefOpened[ComBuf->OrigId][StuNr] = true;
	}
	int TabIx = DB[DBRef].Stu2Tab[StuNr];

	RecNrLen = DB[DBRef].Tab[TabIx].EleInf[1].FldLen;
	if (RecNrLen == 4) RecNr = *(unsigned *)&ComBuf->Info[2];
	else RecNr = *(unsigned short *)&ComBuf->Info[2];

	JetCallThdRec(1701, JetSetCurrentIndex4(DB[DBRef].SesId[ThdRef], DB[DBRef].Tab[TabIx].Tid[ThdRef], "", (JET_INDEXID*)DB[DBRef].Tab[TabIx].Idx[StuRecIx].rgbIndexId[ThdRef], 0, 0));
	JetCallThdRec(1702, JetMakeKey(DB[DBRef].SesId[ThdRef], DB[DBRef].Tab[TabIx].Tid[ThdRef], &RecNr, sizeof(RecNr), JET_bitNewKey));
	_jeterr = JetSeek(DB[DBRef].SesId[ThdRef], DB[DBRef].Tab[TabIx].Tid[ThdRef], JET_bitSeekEQ);
	if (_jeterr != JET_errSuccess) {
		if (RecNr == 0 || RecNr > DB[DBRef].Tab[TabIx].LastRec) return FasReturn(ThdRef, 47);
		return FasReturn(ThdRef, 46);
	}

	/*
		JetCall(1703,JetRetrieveColumn(DB[DBRef].SesId[ThdRef], DB[DBRef].Tab[TabIx].Tid[ThdRef], DB[DBRef].Tab[TabIx].Col[StuRecId].Cid[ThdRef],&RecNrCursor, sizeof(RecNrCursor),&retreclen,0,0));
		if (RecNr!=RecNrCursor) return FasReturn(ThdRef,46); // Cursor is groter dan recnr ... dus recnr moet geschrapt zijn.
	*/

	JetCallThdRec(1704, JetRetrieveColumn(DB[DBRef].SesId[ThdRef], DB[DBRef].Tab[TabIx].Tid[ThdRef], DB[DBRef].Tab[TabIx].Col[StuValId].Cid[ThdRef], &ComBuf->Info[6], BUF_LEN, &retlen, 0, 0));

	p = &ComBuf->Info[6];
	p -= RecNrLen;
	if (RecNrLen == 2) *(unsigned short *)p = (unsigned short)RecNr;
	else if (RecNrLen == 4) *(unsigned *)p = RecNr;
	return FasReturn(ThdRef, 0, DB[DBRef].Tab[TabIx].StructLen, p);
}

bool FasUpd(int ThdRef)
{
	char KeyBuf[MAX_KEYS + 1][MAX_KEY_LEN];
	int KeyIx, ColNr;
	int StuNr, RecNrLen;
	unsigned RecNr;
	UNALIGNED struct sComBuf *ComBuf;
	JET_ERR _jeterr;

#ifdef JMSVIEWER
	return FasReturn(ThdRef, 0);
#endif

	ComBuf = (struct sComBuf*)Thd[ThdRef].ComBuf;
	StuNr = *(short *)&ComBuf->Info[0];
	int DBRef = -1;
	if (ComBuf->OrigId < MAX_PROC) DBRef = Proc2DBRef[ComBuf->OrigId][StuNr];
	if (DBRef < 0) {
		DBRef = ReOpenOnTheFly(ThdRef, StuNr);
		if (DBRef < 0) return FasReturn(ThdRef, 46);
	}
	if (!Proc2DBRefOpened[ComBuf->OrigId][StuNr]) {
		CString cstr;
		cstr.Format("ProcId=%d did FasUpd on StuNr=%d without opening a file (%s was still open)", ComBuf->OrigId, StuNr, DB[DBRef].Name);
		LogAdd(109, 0, cstr);
		Proc2DBRefOpened[ComBuf->OrigId][StuNr] = true;
	}
	int TabIx = DB[DBRef].Stu2Tab[StuNr];

	RecNrLen = DB[DBRef].Tab[TabIx].EleInf[1].FldLen;
	if (RecNrLen == 4) RecNr = *(unsigned *)&ComBuf->Info[2];
	else RecNr = *(unsigned short *)&ComBuf->Info[2];
	char *Rec = &ComBuf->Info[2 + RecNrLen];

	for (KeyIx = 1; KeyIx <= MAX_KEYS; KeyIx++) {
		memset(KeyBuf[KeyIx], 0, MAX_KEY_LEN);
		ComposeKey(DBRef, StuNr, KeyIx, Rec, KeyBuf[KeyIx]);
	}

	JetCallThdRec(1801, JetSetCurrentIndex4(DB[DBRef].SesId[ThdRef], DB[DBRef].Tab[TabIx].Tid[ThdRef], "", (JET_INDEXID*)DB[DBRef].Tab[TabIx].Idx[StuRecIx].rgbIndexId[ThdRef], 0, 0));
	JetCallThdRec(1802, JetMakeKey(DB[DBRef].SesId[ThdRef], DB[DBRef].Tab[TabIx].Tid[ThdRef], &RecNr, sizeof(RecNr), JET_bitNewKey));
	_jeterr = JetSeek(DB[DBRef].SesId[ThdRef], DB[DBRef].Tab[TabIx].Tid[ThdRef], JET_bitSeekEQ);
	if (_jeterr != JET_errSuccess) {
		if (RecNr == 0 || RecNr > DB[DBRef].Tab[TabIx].LastRec) return FasReturn(ThdRef, 47);
		return FasReturn(ThdRef, 46);
	}

	::EnterCriticalSection(&m_DBRecsAddDeleteCs[DBRef]);

	JetCallThdRecJmpJetErrorRet(1803, JetBeginTransaction(DB[DBRef].SesId[ThdRef]))

		_jeterr = JetPrepareUpdate(DB[DBRef].SesId[ThdRef], DB[DBRef].Tab[TabIx].Tid[ThdRef], JET_prepReplace);
	if (_jeterr != JET_errSuccess)
	{
		LogJet(1810, _jeterr, ThdRef, RecNr, DB[DBRef].Name, DB[DBRef].Tab[TabIx].StructName);
		DumpBuf2Log(ThdRef);
		JetPrepareUpdate(DB[DBRef].SesId[ThdRef], DB[DBRef].Tab[TabIx].Tid[ThdRef], JET_prepCancel);
		JetCallThdRecJmpJetErrorRet(1812, JetPrepareUpdate(DB[DBRef].SesId[ThdRef], DB[DBRef].Tab[TabIx].Tid[ThdRef], JET_prepReplace));
	}

	JetCallThdRecJmpJetErrorRet(1805, JetSetColumn(DB[DBRef].SesId[ThdRef], DB[DBRef].Tab[TabIx].Tid[ThdRef], DB[DBRef].Tab[TabIx].Col[StuValId].Cid[ThdRef], Rec, DB[DBRef].Tab[TabIx].StructLen - RecNrLen, 0, NULL));
	for (KeyIx = 1; KeyIx <= MAX_KEYS; KeyIx++) {
		if (DB[DBRef].Tab[TabIx].KeyInf[KeyIx].Len) {
			ColNr = DB[DBRef].Tab[TabIx].KeyInf[KeyIx].ColIx;
			JetCallThdRecJmpJetErrorRet(1806, JetSetColumn(DB[DBRef].SesId[ThdRef], DB[DBRef].Tab[TabIx].Tid[ThdRef], DB[DBRef].Tab[TabIx].Col[ColNr].Cid[ThdRef], KeyBuf[KeyIx], DB[DBRef].Tab[TabIx].Col[ColNr].Len, 0, NULL));
		}
	}

	double now = COleDateTime::GetCurrentTime().operator double();
	JetCallThdRecJmpJetErrorRet(1807, JetSetColumn(DB[DBRef].SesId[ThdRef], DB[DBRef].Tab[TabIx].Tid[ThdRef], DB[DBRef].Tab[TabIx].Col[StuDatId].Cid[ThdRef], &now, DB[DBRef].Tab[TabIx].Col[StuDatId].Len, 0, NULL));
	JetCallThdRecJmpJetErrorRet(1808, JetSetColumn(DB[DBRef].SesId[ThdRef], DB[DBRef].Tab[TabIx].Tid[ThdRef], DB[DBRef].Tab[TabIx].Col[StuChgId].Cid[ThdRef], &ComBuf->OrigId, DB[DBRef].Tab[TabIx].Col[StuChgId].Len, 0, NULL));

	_jeterr = JetUpdate(DB[DBRef].SesId[ThdRef], DB[DBRef].Tab[TabIx].Tid[ThdRef], NULL, 0, NULL);
	JetCommitTransaction(DB[DBRef].SesId[ThdRef], JetCommitBits);
	DBUpdated = DB[DBRef].Updated = true;

	if (_jeterr != JET_errSuccess) {
		if (_jeterr != -1605) {   // JET_errKeyDuplicate
			LogJet(1809, _jeterr, ThdRef, RecNr, DB[DBRef].Name, DB[DBRef].Tab[TabIx].StructName);
			DumpBuf2Log(ThdRef);
		}
	JetErrorRet:;
		::LeaveCriticalSection(&m_DBRecsAddDeleteCs[DBRef]);
		JetPrepareUpdate(DB[DBRef].SesId[ThdRef], DB[DBRef].Tab[TabIx].Tid[ThdRef], JET_prepCancel);
		JetRollback(DB[DBRef].SesId[ThdRef], 0);
		return FasReturn(ThdRef, 31);
	}
	::LeaveCriticalSection(&m_DBRecsAddDeleteCs[DBRef]);

	memcpy(&DB[DBRef].Tab[TabIx].DateTimeUpdate, &now, DB[DBRef].Tab[TabIx].Col[StuDatId].Len);
	memcpy(&DB[DBRef].Tab[TabIx].ChangedBy, &ComBuf->OrigId, sizeof(DB[0].Tab[0].ChangedBy));

	if (JmsExtendedLogging) {
		CString cstr, hstr, tothstr;
		for (int j = 0; j < 20; j++) {
			if (j == (DB[DBRef].Tab[TabIx].StructLen - RecNrLen)) break;
			hstr.Format("%02X", (unsigned char)ComBuf->Info[2 + RecNrLen + j]);
			tothstr += hstr;
		}
		cstr.Format("StuNr=%3d RecNr=%7d DBRef=%3d ThdRef=%3d ProcId=%3d RecUsed=%7d Rec=[%s]", StuNr, RecNr, DBRef, ThdRef, ComBuf->OrigId, DB[DBRef].Tab[TabIx].UsedRec, tothstr);
		LogAdd(0, 2, "RecUpd", cstr);
	}

	return FasReturn(ThdRef, 0);
}

bool FasKill(int ThdRef)
{
	int KeyIx, ColNr;
	short int StuNr, RecNrLen;
	unsigned RecNr;
	UNALIGNED struct sComBuf *ComBuf;
	JET_ERR _jeterr;

#ifdef JMSVIEWER
	return FasReturn(ThdRef, 0);
#endif

	ComBuf = (struct sComBuf*)Thd[ThdRef].ComBuf;
	StuNr = *(short *)&ComBuf->Info[0];
	int DBRef = -1;
	if (ComBuf->OrigId < MAX_PROC) DBRef = Proc2DBRef[ComBuf->OrigId][StuNr];
	if (DBRef < 0) {
		DBRef = ReOpenOnTheFly(ThdRef, StuNr);
		if (DBRef < 0) return FasReturn(ThdRef, 46);
	}
	if (!Proc2DBRefOpened[ComBuf->OrigId][StuNr]) {
		CString cstr;
		cstr.Format("ProcId=%d did FasKill on StuNr=%d without opening a file (%s was still open)", ComBuf->OrigId, StuNr, DB[DBRef].Name);
		LogAdd(109, 0, cstr);
		Proc2DBRefOpened[ComBuf->OrigId][StuNr] = true;
	}
	int TabIx = DB[DBRef].Stu2Tab[StuNr];

	RecNrLen = DB[DBRef].Tab[TabIx].EleInf[1].FldLen;
	if (RecNrLen == 4) RecNr = *(unsigned *)&ComBuf->Info[2];
	else RecNr = *(unsigned short *)&ComBuf->Info[2];
	char *Rec = &ComBuf->Info[2 + RecNrLen];

	JetCallThdRec(1901, JetSetCurrentIndex4(DB[DBRef].SesId[ThdRef], DB[DBRef].Tab[TabIx].Tid[ThdRef], "", (JET_INDEXID*)DB[DBRef].Tab[TabIx].Idx[StuRecIx].rgbIndexId[ThdRef], 0, 0));
	JetCallThdRec(1902, JetMakeKey(DB[DBRef].SesId[ThdRef], DB[DBRef].Tab[TabIx].Tid[ThdRef], &RecNr, sizeof(RecNr), JET_bitNewKey));
	_jeterr = JetSeek(DB[DBRef].SesId[ThdRef], DB[DBRef].Tab[TabIx].Tid[ThdRef], JET_bitSeekEQ);
	if (_jeterr != JET_errSuccess) {
		if (RecNr == 0 || RecNr > DB[DBRef].Tab[TabIx].LastRec) return FasReturn(ThdRef, 65);
		return FasReturn(ThdRef, 46);
	}
	if (JmsExtendedLogging) {
		unsigned long retlen;
		JetCallThdRec(1920, JetRetrieveColumn(DB[DBRef].SesId[ThdRef], DB[DBRef].Tab[TabIx].Tid[ThdRef], DB[DBRef].Tab[TabIx].Col[StuValId].Cid[ThdRef], Rec, BUF_LEN, &retlen, 0, 0));
		CString cstr, hstr, tothstr;
		for (int j = 0; j < 20; j++) {
			if (j == (DB[DBRef].Tab[TabIx].StructLen - RecNrLen)) break;
			hstr.Format("%02X", (unsigned char)Rec[j]);
			tothstr += hstr;
		}
		cstr.Format("StuNr=%3d RecNr=%7d DBRef=%3d ThdRef=%3d ProcId=%3d RecUsed=%7d Rec=[%s]", StuNr, RecNr, DBRef, ThdRef, ComBuf->OrigId, DB[DBRef].Tab[TabIx].UsedRec, tothstr);
		LogAdd(0, 2, "RecDel", cstr);
	}
	::EnterCriticalSection(&m_DBRecsAddDeleteCs[DBRef]);
	// erase old record to avoid problems if fail
	unsigned char EmptyValue = 0xFF;
	JetCallThdRecJmpJetErrorRet(1911, JetBeginTransaction(DB[DBRef].SesId[ThdRef]))
		_jeterr = JetPrepareUpdate(DB[DBRef].SesId[ThdRef], DB[DBRef].Tab[TabIx].Tid[ThdRef], JET_prepReplace);
	if (_jeterr != JET_errSuccess)
	{
		LogJet(1915, _jeterr, ThdRef, RecNr, DB[DBRef].Name, DB[DBRef].Tab[TabIx].StructName);
		DumpBuf2Log(ThdRef);
		JetPrepareUpdate(DB[DBRef].SesId[ThdRef], DB[DBRef].Tab[TabIx].Tid[ThdRef], JET_prepCancel);
		JetCallThdRecJmpJetErrorRet(1917, JetPrepareUpdate(DB[DBRef].SesId[ThdRef], DB[DBRef].Tab[TabIx].Tid[ThdRef], JET_prepReplace));
	}

	FOREVER{
		memset(Rec,EmptyValue,DB[DBRef].Tab[TabIx].StructLen);
		JetCallThdRecJmpJetErrorRet(1905,JetSetColumn(DB[DBRef].SesId[ThdRef], DB[DBRef].Tab[TabIx].Tid[ThdRef], DB[DBRef].Tab[TabIx].Col[StuValId].Cid[ThdRef], Rec, DB[DBRef].Tab[TabIx].StructLen - RecNrLen, 0, NULL));
		for (KeyIx = 1; KeyIx <= MAX_KEYS; KeyIx++) {
			if (DB[DBRef].Tab[TabIx].KeyInf[KeyIx].Len) {
				ColNr = DB[DBRef].Tab[TabIx].KeyInf[KeyIx].ColIx;
				// gebruik de Rec (die 0 is) om die columns te clearen, die zouder korter moeten zijn
				JetCallThdRecJmpJetErrorRet(1906,JetSetColumn(DB[DBRef].SesId[ThdRef], DB[DBRef].Tab[TabIx].Tid[ThdRef], DB[DBRef].Tab[TabIx].Col[ColNr].Cid[ThdRef], Rec, DB[DBRef].Tab[TabIx].Col[ColNr].Len, 0, NULL));
			}
		}
		_jeterr = JetUpdate(DB[DBRef].SesId[ThdRef], DB[DBRef].Tab[TabIx].Tid[ThdRef], NULL, 0, NULL);
	  if (_jeterr == JET_errSuccess) break;
		  JetPrepareUpdate(DB[DBRef].SesId[ThdRef], DB[DBRef].Tab[TabIx].Tid[ThdRef], JET_prepCancel);
	  LogJet(1909,_jeterr);
	  if (_jeterr != -1605) {  // JET_errKeyDuplicate
		LogAdd(39,0,"Unexpected error, cannot proceed retry");
		DumpBuf2Log(ThdRef);
			  goto JetErrorRet2;
	  }
	  if (EmptyValue == 0) {
		LogAdd(40,0,"255 retries done in FasKill to erase, but failed !");
		DumpBuf2Log(ThdRef);
			  goto JetErrorRet2;
	  }
	  EmptyValue--;
	  LogAdd(0,1,"Retrying with EmptyValue",EmptyValue);
	}

		/* code weggehaald op 16/12/2010 is overbodig ... mvg. Nog van het oude testen ???

	  JetCallThdRec(1912,JetPrepareUpdate(DB[DBRef].SesId[ThdRef], DB[DBRef].Tab[TabIx].Tid[ThdRef], JET_prepReplace));
	  JetCallThdRec(1913,JetSetColumn(DB[DBRef].SesId[ThdRef], DB[DBRef].Tab[TabIx].Tid[ThdRef], DB[DBRef].Tab[TabIx].Col[StuValId].Cid[ThdRef], NULL, 0, 0, NULL));
		for (KeyIx=1; KeyIx<=MAX_KEYS; KeyIx++) {
			if (DB[DBRef].Tab[TabIx].KeyInf[KeyIx].Len) {
				JetCallThdRec(1914,JetSetColumn(DB[DBRef].SesId[ThdRef], DB[DBRef].Tab[TabIx].Tid[ThdRef], DB[DBRef].Tab[TabIx].Col[ColNr].Cid[ThdRef], NULL, 0, 0, NULL));
			}
		}
		JetCallThdRec(1915,JetUpdate(DB[DBRef].SesId[ThdRef], DB[DBRef].Tab[TabIx].Tid[ThdRef], NULL, 0, NULL));
	  */

	JetCallThdRecJmpJetErrorRet(1910, JetCommitTransaction(DB[DBRef].SesId[ThdRef], JetCommitBits));

	// then delete this record
	JetCallThdRecJmpJetErrorRet(1903, JetDelete(DB[DBRef].SesId[ThdRef], DB[DBRef].Tab[TabIx].Tid[ThdRef]));

	DB[DBRef].Tab[TabIx].UsedRec--;

	double now = COleDateTime::GetCurrentTime().operator double();
	EDBAddDeletedRecNr(ThdRef, DBRef, StuNr, RecNr, now, ComBuf->OrigId);
	DBUpdated = DB[DBRef].Updated = true;

	::LeaveCriticalSection(&m_DBRecsAddDeleteCs[DBRef]);
	memcpy(&DB[DBRef].Tab[TabIx].DateTimeUpdate, &now, DB[DBRef].Tab[TabIx].Col[StuDatId].Len);
	memcpy(&DB[DBRef].Tab[TabIx].ChangedBy, &ComBuf->OrigId, sizeof(DB[0].Tab[0].ChangedBy));
	return FasReturn(ThdRef, 0);

JetErrorRet:;
	JetPrepareUpdate(DB[DBRef].SesId[ThdRef], DB[DBRef].Tab[TabIx].Tid[ThdRef], JET_prepCancel);
	JetRollback(DB[DBRef].SesId[ThdRef], 0);
JetErrorRet2:;
	::LeaveCriticalSection(&m_DBRecsAddDeleteCs[DBRef]);
	return FasReturn(ThdRef, 46);

}

bool FasAddi(int ThdRef)
{
	char KeyBuf[MAX_KEYS + 1][MAX_KEY_LEN];
	int KeyIx, ColNr;
	int StuNr, RecNrLen;
	unsigned RecNr;
	UNALIGNED struct sComBuf *ComBuf;
	JET_ERR _jeterr;

#ifdef JMSVIEWER
	return FasReturn(ThdRef, 0);
#endif

	ComBuf = (struct sComBuf*)Thd[ThdRef].ComBuf;
	StuNr = *(short *)&ComBuf->Info[0];
	int DBRef = -1;
	if (ComBuf->OrigId < MAX_PROC) DBRef = Proc2DBRef[ComBuf->OrigId][StuNr];
	if (DBRef < 0) {
		DBRef = ReOpenOnTheFly(ThdRef, StuNr);
		if (DBRef < 0) return FasReturn(ThdRef, 46);
	}
	if (!Proc2DBRefOpened[ComBuf->OrigId][StuNr]) {
		CString cstr;
		cstr.Format("ProcId=%d did FasAdd on StuNr=%d without opening a file (%s was still open)", ComBuf->OrigId, StuNr, DB[DBRef].Name);
		LogAdd(109, 0, cstr);
		Proc2DBRefOpened[ComBuf->OrigId][StuNr] = true;
	}
	int TabIx = DB[DBRef].Stu2Tab[StuNr];

	RecNrLen = DB[DBRef].Tab[TabIx].EleInf[1].FldLen;
	char *Rec = &ComBuf->Info[2 + RecNrLen];

	for (KeyIx = 1; KeyIx <= MAX_KEYS; KeyIx++) {
		memset(KeyBuf[KeyIx], 0, MAX_KEY_LEN);
		ComposeKey(DBRef, StuNr, KeyIx, Rec, KeyBuf[KeyIx]);
	}

	::EnterCriticalSection(&m_DBRecsAddDeleteCs[DBRef]);

	JetCallThdJmpJetErrorRet(2001, JetBeginTransaction(DB[DBRef].SesId[ThdRef]));
	_jeterr = JetPrepareUpdate(DB[DBRef].SesId[ThdRef], DB[DBRef].Tab[TabIx].Tid[ThdRef], JET_prepInsert);
	if (_jeterr != JET_errSuccess)
	{
		LogJet(2012, _jeterr);
		CString cstr;
		cstr.Format("%d ThdRef=%d DBRef=%d", StuNr, ThdRef);
		LogAdd(0, 2, "StuNr", cstr);
		JetPrepareUpdate(DB[DBRef].SesId[ThdRef], DB[DBRef].Tab[TabIx].Tid[ThdRef], JET_prepCancel);
		JetCallThdJmpJetErrorRet(2011, JetPrepareUpdate(DB[DBRef].SesId[ThdRef], DB[DBRef].Tab[TabIx].Tid[ThdRef], JET_prepInsert));
	}

	RecNr = EDBFindDeletedRecNr(ThdRef, DBRef, StuNr);
	if (RecNr == 0) {
		RecNr = DB[DBRef].Tab[TabIx].LastRec + 1;
	}
	JetCallThdRecJmpJetErrorRet(2003, JetSetColumn(DB[DBRef].SesId[ThdRef], DB[DBRef].Tab[TabIx].Tid[ThdRef], DB[DBRef].Tab[TabIx].Col[StuRecId].Cid[ThdRef], &RecNr, DB[DBRef].Tab[TabIx].Col[StuRecId].Len, 0, NULL));
	JetCallThdRecJmpJetErrorRet(2004, JetSetColumn(DB[DBRef].SesId[ThdRef], DB[DBRef].Tab[TabIx].Tid[ThdRef], DB[DBRef].Tab[TabIx].Col[StuValId].Cid[ThdRef], Rec, DB[DBRef].Tab[TabIx].StructLen - RecNrLen, 0, NULL));
	for (KeyIx = 1; KeyIx <= MAX_KEYS; KeyIx++) {
		if (DB[DBRef].Tab[TabIx].KeyInf[KeyIx].Len) {
			ColNr = DB[DBRef].Tab[TabIx].KeyInf[KeyIx].ColIx;
			JetCallThdRecJmpJetErrorRet(2005, JetSetColumn(DB[DBRef].SesId[ThdRef], DB[DBRef].Tab[TabIx].Tid[ThdRef], DB[DBRef].Tab[TabIx].Col[ColNr].Cid[ThdRef], KeyBuf[KeyIx], DB[DBRef].Tab[TabIx].Col[ColNr].Len, 0, NULL));
		}
	}

	double now = COleDateTime::GetCurrentTime().operator double();
	JetCallThdRecJmpJetErrorRet(2006, JetSetColumn(DB[DBRef].SesId[ThdRef], DB[DBRef].Tab[TabIx].Tid[ThdRef], DB[DBRef].Tab[TabIx].Col[StuDatId].Cid[ThdRef], &now, DB[DBRef].Tab[TabIx].Col[StuDatId].Len, 0, NULL));
	JetCallThdRecJmpJetErrorRet(2007, JetSetColumn(DB[DBRef].SesId[ThdRef], DB[DBRef].Tab[TabIx].Tid[ThdRef], DB[DBRef].Tab[TabIx].Col[StuChgId].Cid[ThdRef], &ComBuf->OrigId, DB[DBRef].Tab[TabIx].Col[StuChgId].Len, 0, NULL));

	_jeterr = JetUpdate(DB[DBRef].SesId[ThdRef], DB[DBRef].Tab[TabIx].Tid[ThdRef], NULL, 0, NULL);
	if (_jeterr != JET_errSuccess) {
	JetErrorRet:;
		JetPrepareUpdate(DB[DBRef].SesId[ThdRef], DB[DBRef].Tab[TabIx].Tid[ThdRef], JET_prepCancel);
		JetRollback(DB[DBRef].SesId[ThdRef], 0); // deze voegt eventueel ook de gedelete deletedentry terug bij !
		::LeaveCriticalSection(&m_DBRecsAddDeleteCs[DBRef]);
		return FasReturn(ThdRef, 31);
	}
	JetCallThdRecJmpJetErrorRet(2009, JetCommitTransaction(DB[DBRef].SesId[ThdRef], JetCommitBits));

	if (RecNr > DB[DBRef].Tab[TabIx].LastRec) DB[DBRef].Tab[TabIx].LastRec = RecNr;
	DB[DBRef].Tab[TabIx].UsedRec++;
	DBUpdated = DB[DBRef].Updated = true;

	::LeaveCriticalSection(&m_DBRecsAddDeleteCs[DBRef]);
	memcpy(&DB[DBRef].Tab[TabIx].DateTimeUpdate, &now, DB[DBRef].Tab[TabIx].Col[StuDatId].Len);
	memcpy(&DB[DBRef].Tab[TabIx].ChangedBy, &ComBuf->OrigId, sizeof(DB[0].Tab[0].ChangedBy));

	if (JmsExtendedLogging) {
		CString cstr, hstr, tothstr;
		for (int j = 0; j < 20; j++) {
			if (j == (DB[DBRef].Tab[TabIx].StructLen - RecNrLen)) break;
			hstr.Format("%02X", (unsigned char)ComBuf->Info[2 + RecNrLen + j]);
			tothstr += hstr;
		}
		cstr.Format("StuNr=%3d RecNr=%7d DBRef=%3d ThdRef=%3d ProcId=%3d RecUsed=%7d Rec=[%s]", StuNr, RecNr, DBRef, ThdRef, ComBuf->OrigId, DB[DBRef].Tab[TabIx].UsedRec, tothstr);
		LogAdd(0, 2, "RecAdd", cstr);
	}

	return FasReturn(ThdRef, 0, RecNrLen, (char *)&RecNr);
}

bool FasKeyu(int ThdRef)
{
	int i, StuNr, KeyNr, KeyIx, Mode, error = 0, RecNrLen, Grbit;
	unsigned long retlen, retreclen;
	unsigned RecNr;
	char KeyBuf[MAX_KEY_LEN + 10], KeyBufRec[MAX_KEY_LEN + 10], *p;
	UNALIGNED struct sComBuf *ComBuf;
	JET_ERR _jeterr;

	ComBuf = (struct sComBuf*)Thd[ThdRef].ComBuf;
	StuNr = *(short *)&ComBuf->Info[0];
	int DBRef = -1;
	if (ComBuf->OrigId < MAX_PROC) DBRef = Proc2DBRef[ComBuf->OrigId][StuNr];
	if (DBRef < 0) {
		DBRef = ReOpenOnTheFly(ThdRef, StuNr);
		if (DBRef < 0) return FasReturn(ThdRef, 46);
	}
	if (!Proc2DBRefOpened[ComBuf->OrigId][StuNr]) {
		CString cstr;
		cstr.Format("ProcId=%d did FasKey on StuNr=%d without opening a file (%s was still open)", ComBuf->OrigId, StuNr, DB[DBRef].Name);
		LogAdd(109, 0, cstr);
		Proc2DBRefOpened[ComBuf->OrigId][StuNr] = true;
	}
	int TabIx = DB[DBRef].Stu2Tab[StuNr];

	KeyNr = *(short int*)&ComBuf->Info[2];
	Mode = *(short int*)&ComBuf->Info[4];
	for (KeyIx = 1; KeyIx <= MAX_KEYS; KeyIx++) {
		if (DB[DBRef].Tab[TabIx].KeyInf[KeyIx].Nr == KeyNr) break;
	}
	if (KeyIx > MAX_KEYS) return FasReturn(ThdRef, 45); // key not found ...
	RecNrLen = DB[DBRef].Tab[TabIx].EleInf[1].FldLen;
	ComposeKey(DBRef, StuNr, KeyIx, &ComBuf->Info[6 + RecNrLen], KeyBuf);
	RecNr = 0;
	if (RecNrLen == 2) RecNr = *(unsigned short *)&ComBuf->Info[6];
	else if (RecNrLen == 4) RecNr = *(unsigned *)&ComBuf->Info[6];

	switch (Mode) {
	case 0: Grbit = JET_bitSeekEQ; break;
	case 1: Grbit = JET_bitSeekGE; break;
	case 2: Grbit = JET_bitSeekGT; break;
	case 5:
		if (KeyBuf[0] == 0) return FasReturn(ThdRef, 38); // er moet een zoekterm ingevuld zijn
		Grbit = JET_bitSeekGE;
		break;
	default:
		LogAdd(15, 0, "FasKeyu with invalid Mode", Mode);
		Grbit = JET_bitSeekEQ;
		break;
	}

	if (Mode == 5 && RecNr && DB[DBRef].Tab[TabIx].KeyInf[KeyIx].Typ & 0x04) {
		JetCallThdRec(2102, JetSetCurrentIndex4(DB[DBRef].SesId[ThdRef], DB[DBRef].Tab[TabIx].Tid[ThdRef], "", (JET_INDEXID*)DB[DBRef].Tab[TabIx].Idx[StuRecIx].rgbIndexId[ThdRef], 0, 0));
		JetCallThdRec(2103, JetMakeKey(DB[DBRef].SesId[ThdRef], DB[DBRef].Tab[TabIx].Tid[ThdRef], &RecNr, sizeof(RecNr), JET_bitNewKey));
		_jeterr = JetSeek(DB[DBRef].SesId[ThdRef], DB[DBRef].Tab[TabIx].Tid[ThdRef], JET_bitSeekEQ);
		if (_jeterr == JET_errRecordNotFound) {

			LogAdd(16, 0, "FasKey executed with RecNr, but not found", RecNr);
			return FasReturn(ThdRef, 39);
		}
		JetCallThdRec(2104, JetSetCurrentIndex4(DB[DBRef].SesId[ThdRef], DB[DBRef].Tab[TabIx].Tid[ThdRef], "", (JET_INDEXID*)DB[DBRef].Tab[TabIx].Idx[KeyIx].rgbIndexId[ThdRef], JET_bitNoMove, 0));
		_jeterr = JetMove(DB[DBRef].SesId[ThdRef], DB[DBRef].Tab[TabIx].Tid[ThdRef], JET_MoveNext, 0);
		if (_jeterr != JET_errSuccess) return FasReturn(ThdRef, 39);
	}
	else if (Mode == 2 && RecNr) {
		JetCallThdRec(2105, JetSetCurrentIndex4(DB[DBRef].SesId[ThdRef], DB[DBRef].Tab[TabIx].Tid[ThdRef], "", (JET_INDEXID*)DB[DBRef].Tab[TabIx].Idx[StuRecIx].rgbIndexId[ThdRef], 0, 0));
		JetCallThdRec(2106, JetMakeKey(DB[DBRef].SesId[ThdRef], DB[DBRef].Tab[TabIx].Tid[ThdRef], &RecNr, sizeof(RecNr), JET_bitNewKey));
		_jeterr = JetSeek(DB[DBRef].SesId[ThdRef], DB[DBRef].Tab[TabIx].Tid[ThdRef], JET_bitSeekEQ);
		if (_jeterr == JET_errRecordNotFound) {
			// het doorgegeven recordnr is ondertussen geschrapt
			// zoek dan op de key maar aanvaard ook dezelfde key om ev. duplicated keys niet te missen
			// alternatief zou kunnen zijn om recordnr toe te voegen in alle key's, zeker die duplicated toestaan
			// dan dan verder te zoeken naar 'greather'
			// nu gaat hij bij duplicated terug naar de eerste record gaan, na een deleted record als pointer te hebben.
			JetCallThdRec(2115, JetSetCurrentIndex4(DB[DBRef].SesId[ThdRef], DB[DBRef].Tab[TabIx].Tid[ThdRef], "", (JET_INDEXID*)DB[DBRef].Tab[TabIx].Idx[KeyIx].rgbIndexId[ThdRef], 0, 0));
			JetCallThdRec(2116, JetMakeKey(DB[DBRef].SesId[ThdRef], DB[DBRef].Tab[TabIx].Tid[ThdRef], KeyBuf, DB[DBRef].Tab[TabIx].KeyInf[KeyIx].Len, JET_bitNewKey));
			_jeterr = JetSeek(DB[DBRef].SesId[ThdRef], DB[DBRef].Tab[TabIx].Tid[ThdRef], JET_bitSeekGE);
			if (_jeterr != JET_errSuccess && _jeterr != JET_wrnSeekNotEqual) return FasReturn(ThdRef, 39);
		}
		else {
			JetCallThdRec(2107, JetSetCurrentIndex4(DB[DBRef].SesId[ThdRef], DB[DBRef].Tab[TabIx].Tid[ThdRef], "", (JET_INDEXID*)DB[DBRef].Tab[TabIx].Idx[KeyIx].rgbIndexId[ThdRef], JET_bitNoMove, 0));
			_jeterr = JetMove(DB[DBRef].SesId[ThdRef], DB[DBRef].Tab[TabIx].Tid[ThdRef], JET_MoveNext, 0);
			if (_jeterr != JET_errSuccess) return FasReturn(ThdRef, 39);
		}
	}
	else {
		JetCallThdRec(2108, JetSetCurrentIndex4(DB[DBRef].SesId[ThdRef], DB[DBRef].Tab[TabIx].Tid[ThdRef], "", (JET_INDEXID*)DB[DBRef].Tab[TabIx].Idx[KeyIx].rgbIndexId[ThdRef], 0, 0));
		JetCallThdRec(2109, JetMakeKey(DB[DBRef].SesId[ThdRef], DB[DBRef].Tab[TabIx].Tid[ThdRef], KeyBuf, DB[DBRef].Tab[TabIx].KeyInf[KeyIx].Len, JET_bitNewKey));
		_jeterr = JetSeek(DB[DBRef].SesId[ThdRef], DB[DBRef].Tab[TabIx].Tid[ThdRef], Grbit);
		if (_jeterr == JET_errRecordNotFound) return FasReturn(ThdRef, 39);
	}
	if (Mode == 5 && DB[DBRef].Tab[TabIx].KeyInf[KeyIx].Typ & 0x04) {
		JetCallThdRec(2110, JetRetrieveColumn(DB[DBRef].SesId[ThdRef], DB[DBRef].Tab[TabIx].Tid[ThdRef], DB[DBRef].Tab[TabIx].Col[DB[DBRef].Tab[TabIx].KeyInf[KeyIx].ColIx].Cid[ThdRef], KeyBufRec, MAX_KEY_LEN, &retlen, 0, 0));
		KeyBufRec[retlen] = 0;
		for (i = 0; i < MAX_KEY_LEN; i++) {
			if (KeyBuf[i] == 0) break;
			if (KeyBuf[i] != KeyBufRec[i]) return FasReturn(ThdRef, 39);
		}
		// _jeterr==JET_wrnSeekNotEqual
	}
	JetCallThdRec(2111, JetRetrieveColumn(DB[DBRef].SesId[ThdRef], DB[DBRef].Tab[TabIx].Tid[ThdRef], DB[DBRef].Tab[TabIx].Col[StuValId].Cid[ThdRef], &ComBuf->Info[6], BUF_LEN, &retlen, 0, 0));
	JetCallThdRec(2112, JetRetrieveColumn(DB[DBRef].SesId[ThdRef], DB[DBRef].Tab[TabIx].Tid[ThdRef], DB[DBRef].Tab[TabIx].Col[StuRecId].Cid[ThdRef], &RecNr, sizeof(RecNr), &retreclen, 0, 0));

	p = &ComBuf->Info[6];
	p -= RecNrLen;
	if (RecNrLen == 2) *(unsigned short *)p = (unsigned short)RecNr;
	else if (RecNrLen == 4) *(unsigned *)p = RecNr;
	return FasReturn(ThdRef, 0, DB[DBRef].Tab[TabIx].StructLen, p);
}

/////////////////////////////////////////
//  SYSMngr
/////////////////////////////////////////

void PreMountDB(int SysFileIx)
{
	int i, MountedCount = 0;
	char FileName[20];
	bool CreateAnyWay = false, NotCreated = false;

	Sys[SysFileIx].PreMountBusyFlag = true;
redo:;
	for (i = 0; i < 15; i++) {
		if (JMSShuttingDown) return;
		memcpy(FileName, Sys[SysFileIx].Buf + 300 + i * 17, 15);
		FileName[15] = 0;
		if (FileName[0] > ' ') {
			CString FilePath = PathDB + FileName;
			if (GetFileAttributes(FilePath) != INVALID_FILE_ATTRIBUTES) {
				if (!CreateAnyWay) {  // bestand is al open, 2-de run
					MountedCount++;
					MountDB(FileName);
				}
			}
			else {
				if (CreateAnyWay || Sys[SysFileIx].StdDossierFlag) {
					LogAdd(0, 0, "Creating empty", FileName);
					MountDB(FileName, true); // creeer het bestand 
					MountedCount++;
				}
				else NotCreated = true; // voor eventuele 2-de run 
			}
		}
	}
	if (!CreateAnyWay && MountedCount > 0 && NotCreated) {
		CreateAnyWay = true;
		goto redo;
	}
	Sys[SysFileIx].PreMountBusyFlag = false;
	theApp.ProgDidSomeWork++;
}

bool ExportAllFas(char *ext)
{

	int file_ix;
	for (file_ix = 0; file_ix < MAX_SYSFILE; file_ix++) {
		if (Sys[file_ix].Ext.CompareNoCase(ext) == 0) break;
	}
	if (file_ix == MAX_SYSFILE) return false;

	for (int i = 0; i < 15; i++) {
		char FileName[20];
		memcpy(FileName, Sys[file_ix].Buf + 300 + i * 17, 15);
		FileName[15] = 0;
		if (FileName[0]) {
			int DBRef = FindDB(FileName);
			if (DBRef < 0) DBRef = MountDB(FileName, true);
			if (DBRef >= 0) ExportFas(DBRef);
		}
	}

	CString SysFileName;
	SysFileName = "SYS.";
	SysFileName += ext;
	SysFileName = PathProg + SysFileName;
	SysFileName.MakeUpper();
	SysFileName += ".exp";
	CFile SysFile;
	LogAdd(0, 0, "Exporting SYS", SysFileName);
	SysFile.Open(SysFileName, CFile::modeReadWrite | CFile::modeCreate, 0);
	SysFile.Write(Sys[file_ix].Buf, Sys[file_ix].Length);
	SysFile.Close();

	CString cstr;
	cstr.Format("Export %s done ...", ext);
	LogAdd(0, 0, cstr);
	return true;
}

int SysOpen(char *ext, bool StdDossierFlag, bool PeekMode)
{
	int file_ix;

	for (file_ix = 0; file_ix < MAX_SYSFILE; file_ix++) {
		if (Sys[file_ix].Ext.CompareNoCase(ext) == 0) break;
	}
	if (file_ix < MAX_SYSFILE) {   // file already open
		Sys[file_ix].OpenCnt++;
		if (Sys[file_ix].PeekMode && !PeekMode) Sys[file_ix].PeekMode = false;
		return file_ix;
	}
	else {
		for (file_ix = 0; file_ix < MAX_SYSFILE; file_ix++) {
			if (Sys[file_ix].Ext.GetLength() == 0) break;
		}
		if (file_ix == MAX_SYSFILE) {
			LogAdd(31, 0, "Too many SYS-files in use, max=", MAX_SYSFILE);
			return -1;
		}
		else {
			CString FileName = PathDB + "SYS." + ext;
			UINT FileMode = CFile::modeReadWrite;
#ifdef JMSVIEWER
			FileMode = CFile::modeRead;
#endif
			LogAdd(0, 0, "Going to open", FileName);
			if (Sys[file_ix].File.Open(FileName, FileMode, NULL) == FALSE) {
				LogAdd(0, 1, "FileName sys", FileName);
				LogAdd(0, 1, "error ret", GetLastError());
				return -1;
			}
			else {
				Sys[file_ix].Ext = ext;
				Sys[file_ix].Name = FileName;
				Sys[file_ix].Length = (long)Sys[file_ix].File.GetLength();
				Sys[file_ix].PeekMode = PeekMode;
				if (Sys[file_ix].Length > MAX_SYS_LEN) Sys[file_ix].Length = MAX_SYS_LEN;
				Sys[file_ix].File.Read(Sys[file_ix].Buf, Sys[file_ix].Length);
				Sys[file_ix].StdDossierFlag = StdDossierFlag;
				if (memcmp(Sys[file_ix].Buf, HEADERSTRING, 5) != 0) {
					char *hs = HEADERSTRING;
					if (memcmp(Sys[file_ix].Buf + 2, &hs[2], 3) == 0) {
						memcpy(Sys[file_ix].Buf, HEADERSTRING, 2);
						LogAdd(0, 1, "Header Sys-file corrected (2 first bytes)");
						Sys[file_ix].File.SeekToBegin();
						Sys[file_ix].File.Write(Sys[file_ix].Buf, 2);
					}
					else {
						Sys[file_ix].Ext = "";
						Sys[file_ix].Name = "";
						Sys[file_ix].File.Close();;
						LogAdd(32, 0, "No valid Sys-file !");
						goto cont;
					}
				}
				if (Sys[file_ix].Length < MAX_SYS_LEN) {  // sys-files moet allemaal MAX_SYS_LEN lengte krijgen (32750)
					memset(&Sys[file_ix].Buf[Sys[file_ix].Length], 0, MAX_SYS_LEN - Sys[file_ix].Length);
					Sys[file_ix].Length = MAX_SYS_LEN;
					Sys[file_ix].File.SeekToBegin();
					Sys[file_ix].File.Write(Sys[file_ix].Buf, Sys[file_ix].Length);
				}
				Sys[file_ix].OpenCnt = 1;
				FILETIME CreationTime, LastWriteTime, LastAccessTime;
				GetFileTime(Sys[file_ix].File.m_hFile, &CreationTime, &LastAccessTime, &LastWriteTime);
				TIME_ZONE_INFORMATION TimeZoneInfo;
				GetTimeZoneInformation(&TimeZoneInfo);
				// Convert local time to UTC.
				SYSTEMTIME localTime = { 0 }, systemTime = { 0 };
				FileTimeToSystemTime(&LastWriteTime, &systemTime);
				SystemTimeToTzSpecificLocalTime(&TimeZoneInfo, &systemTime, &localTime);
				//FileTime must be in UTC format (therfor convertion)
				COleDateTime dt(localTime);
				Sys[file_ix].DateTimeLastWrite = dt.operator double();
			}
		cont:;
		}
	}

	CString cstr;
	cstr.Format("SYS-file [#%d] opened : %s", file_ix, Sys[file_ix].Ext);
	if (PeekMode) cstr += " [PeekMode]";
	LogAdd(0, 0, cstr);
	if (file_ix >= 0 && !PeekMode) {
		_beginthread((void(*)(void*))PreMountDB, 0, (void*)file_ix);
	}

	return file_ix;
}

bool SysInit()
{
	for (int i = 1; i <= 10; i++) {
		CString DossierNr;
		DossierNr.Format("StdDossier%d", i);
		CString DossierExt = theApp.iniFile.getKeyValue(DossierNr, "DataBaseSettings");
		if (i == 1 && DossierExt == "") DossierExt = "FAS";
		if (DossierExt == "") continue;

		int file_ix = SysOpen((char *)(LPCTSTR)DossierExt, true);
		if (file_ix == -1) {
			LogAdd(30, 0, "SYSFile could not be opened", DossierExt);
			return false;
		}
		LogAdd(0, 1, "SYSFile is now open", DossierExt);
	}
	return true;
}

bool SysCloseAll()
{
	for (int file_ix = 0; file_ix < MAX_SYSFILE; file_ix++) {
		if (Sys[file_ix].Ext.GetLength() == 0) continue;
		Sys[file_ix].StdDossierFlag = false;
		Sys[file_ix].OpenCnt = 1;
		SysClose(file_ix);
	}
	return true;
}

bool SysClose(int file_ix)
{
	if (file_ix < 0 || file_ix >= MAX_SYSFILE || Sys[file_ix].Ext.GetLength() == 0) return false;

	if (Sys[file_ix].OpenCnt >= 1) Sys[file_ix].OpenCnt--;
	if (Sys[file_ix].StdDossierFlag || Sys[file_ix].OpenCnt > 0)
		return false; // Geen UnMountDB want er zijn nog gebruikers van deze SYS.* of het is een Standaard Dossier (blijven altijd open !) 

	if (Sys[file_ix].PeekMode == false) { // zo in PeekMode dan was er geen pre-mount gedaan !
		for (int i = 0; i < 15; i++) {
			char FileName[20];
			memcpy(FileName, Sys[file_ix].Buf + 300 + i * 17, 15);
			FileName[15] = 0;
			if (FileName[0]) UnMountDB(FileName);
		}
	}
#ifndef JMSVIEWER
	SetFileLastWriteTime(Sys[file_ix].File.m_hFile, Sys[file_ix].DateTimeLastWrite);
#endif
	Sys[file_ix].File.Close(); // close file fysically 

	CString cstr;
	cstr.Format("SYS-file [#%d] closed : %s", file_ix, Sys[file_ix].Ext);
	if (Sys[file_ix].PeekMode) cstr += " [PeekMode]";
	LogAdd(0, 0, cstr);

	Sys[file_ix].Ext = "";
	Sys[file_ix].OpenCnt = 0;
	Sys[file_ix].Name = "";
	Sys[file_ix].PreMountBusyFlag = false;
	Sys[file_ix].StdDossierFlag = false;
	Sys[file_ix].Updated = false;
	Sys[file_ix].PeekMode = false;
	Sys[file_ix].DateTimeLastWrite = 0.;

	return true;
}

bool SysFileOpen(int ThdRef)
{
	UNALIGNED short int *psi;
	UNALIGNED struct sComBuf *ComBuf;
	ComBuf = (struct sComBuf*)Thd[ThdRef].ComBuf;
	psi = (UNALIGNED short int *)ComBuf->Info;
	bool PeekMode = false;

	if (Sys[0].Ext[0] && memcmp(ComBuf->Info, "FAS", 3) == 0) { // is de standaard in OVLFUNC ... in ovl001 doet men sysopen("","") en dan wordt het FAS
		memcpy(ComBuf->Info, Sys[0].Ext, 3);
	}
	if (ComBuf->Info[4] == '?') PeekMode = true;
	int ret = SysOpen(ComBuf->Info, false, PeekMode); // ext is passed from info[0] ... [2} + \0
	if (JmsExtendedLogging) {
		CString cstr;
		cstr.Format("%s SysRef=%d ThdRef=%d ProcId=%d", ComBuf->Info, ret, ThdRef, ComBuf->OrigId);
		LogAdd(0, 2, "SysFileOpen", cstr);
		LogAdd(0, 2, cstr);
	}

	if (ret == -1) { // error
		*psi++ = 1;
		*psi++ = -1;
	}
	else {
		if (ComBuf->OrigId >= 0 && ComBuf->OrigId < MAX_PROC) {
			int PostNr = 1 + (ComBuf->OrigId / 5);
			int ScreenNr = ComBuf->OrigId % 5;
			int MaxPostNr = atol(theApp.iniFile.getKeyValue("PostCount", "JamaSettings"));
#ifndef JMSVIEWER
			if (PostNr >= 1 && PostNr <= MaxPostNr && ScreenNr >= 1 && ScreenNr <= 4) {
				CString PostSection, Key;
				PostSection.Format("Post-%03d_Settings", PostNr);
				Key.Format("Screen-%d_LastSysOpen", ScreenNr);
				theApp.iniFile.setKey(ComBuf->Info, Key, PostSection);
			}
#endif
			Proc2SysRef[ComBuf->OrigId] = ret;
			// aanduiden dat die structuren eigenlijk gekoppeld zijn aan andere dossiers ! Correct FASOPEN voor die files moet nog gebeuren !
			for (int StuNr = 0; StuNr < MAX_STRUCT; StuNr++) {
				Proc2DBRefOpened[ComBuf->OrigId][StuNr] = false;
			}
		}
		*psi++ = 0;
		*psi++ = ret;
	}
	ComBuf->Function = 101;
	Thd[ThdRef].ReplyLength = 4;

	return true;
}

bool SysFileClose(int ThdRef)
{
	UNALIGNED struct sComBuf *ComBuf;
	short int *psi;

	ComBuf = (struct sComBuf*)Thd[ThdRef].ComBuf;
	psi = (UNALIGNED short int *)ComBuf->Info;

	int file_ix = *psi;
	if (file_ix <0 || file_ix > MAX_SYSFILE - 1) return false;
	if (file_ix == 0) return true; // do not close the SYS.FAS (always index 0)

	if (Sys[file_ix].Ext.GetLength() == 0 || Sys[file_ix].OpenCnt <= 0) {
		LogAdd(0, 1, "Sys-file was not open", file_ix);
		return false;
	}
	else {
		if (SysClose(file_ix)) {
			if (ComBuf->OrigId >= 0 && ComBuf->OrigId < MAX_PROC) Proc2SysRef[ComBuf->OrigId] = -1;
		}
	}

	return true;
}

bool SysFileRead(int ThdRef)
{
	UNALIGNED struct sComBuf *ComBuf;
	short int *psi;
	int pos, len;

	ComBuf = (struct sComBuf*)Thd[ThdRef].ComBuf;
	psi = (UNALIGNED short int *)ComBuf->Info;
	int file_ix = *psi++;
	pos = *psi++;
	len = *psi++;
	if (pos > Sys[file_ix].Length) pos = Sys[file_ix].Length;
	if (pos + len > Sys[file_ix].Length) len = Sys[file_ix].Length - pos;
	if (len < 0) len = 0;

	ComBuf->Function = 102;
	memcpy(ComBuf->Info, &Sys[file_ix].Buf[pos], len);
	Thd[ThdRef].ReplyLength = len;
	return true;
}

bool SysFileWrite(int ThdRef)
{
	UNALIGNED struct sComBuf *ComBuf;
	short int *psi;
	int pos, len;

	ComBuf = (struct sComBuf*)Thd[ThdRef].ComBuf;
	psi = (UNALIGNED short int *)ComBuf->Info;
	int file_ix = *psi++;
	pos = *psi++;
	len = *psi++;
	if (pos > Sys[file_ix].Length) pos = Sys[file_ix].Length;
	if (pos + len > Sys[file_ix].Length) len = Sys[file_ix].Length - pos;
	if (len < 0) len = 0;

	if (len > 0) {
		memcpy(&Sys[file_ix].Buf[pos], &ComBuf->Info[6], len);
#ifndef JMSVIEWER
		Sys[file_ix].File.Seek(pos, 0);
		Sys[file_ix].File.Write(&ComBuf->Info[6], len);
		Sys[file_ix].Updated = true;
		Sys[file_ix].DateTimeLastWrite = COleDateTime::GetCurrentTime().operator double();
		DBUpdated = true;
		if (JmsExtendedLogging) {
			CString cstr, hstr, tothstr;
			for (int j = 0; j < 20; j++) {
				if (j == len) break;
				hstr.Format("%02X", (unsigned char)ComBuf->Info[6 + j]);
				tothstr += hstr;
			}
			cstr.Format("%s ThdRef=%d SysRef=%d ProcId=%d Pos=%d Len=%d Data=[%s]", Sys[file_ix].Ext, ThdRef, file_ix, ComBuf->OrigId, pos, len, tothstr);
			LogAdd(0, 2, "SysUpd", cstr);
		}
#endif
	}
	return true;
}

//****

CString GetIniSections()
{
	CString strReturn = "";

	CStringList* strList;
	CIniFile Ini(theApp.iniFile.m_strFileName);
	strList = Ini.getSectionNames();
	for (POSITION pos = strList->GetHeadPosition(); pos != NULL;) {
		strReturn += strList->GetNext(pos) + "\r\n";
	}

	return strReturn;
}

CString GetIniSectionData(CString Cmd)
{
	CString strReturn = "";

	int i = Cmd.Find("|");
	if (i > 0 && i < Cmd.GetLength() - 1) {
		CStringList* strList;
		CIniFile Ini(theApp.iniFile.m_strFileName);
		strList = Ini.getSectionData(Cmd.Mid(i + 1));
		for (POSITION pos = strList->GetHeadPosition(); pos != NULL;) {
			strReturn += strList->GetNext(pos) + "\r\n";
		}
	}
	return strReturn;
}

CString GetIniKeyValue(CString Cmd)  //  GetIniKeyValue|PrinterSettings|JamaPrinter9
{
	CString strReturn = "@%!";

	int i = Cmd.Find("|");
	int j = Cmd.Find("|", i + 1);
	if (j > 0 && j < Cmd.GetLength() - 1) {
		CIniFile Ini(theApp.iniFile.m_strFileName);
		CString strSectionName = Cmd.Mid(i + 1, j - i - 1);
		CString strKeyName = Cmd.Mid(j + 1);
		bool WildCardFound = false;
		if (strSectionName.Find("?") >= 0) WildCardFound = true;
		if (WildCardFound) {
			CStringList* strList = Ini.getSectionNames();
			for (POSITION pos = strList->GetHeadPosition(); pos != NULL;) {
				CString strSectionNameFound = strList->GetNext(pos);
				if (strSectionName.GetLength() != strSectionNameFound.GetLength()) continue;
				CString strSectionNameFoundDup = strSectionNameFound;
				i = 0;
				while ((i = strSectionName.Find("?", i)) >= 0) {
					strSectionNameFoundDup.SetAt(i, '?');
					i++;
				}
				if (strSectionName.CompareNoCase(strSectionNameFoundDup) != 0) continue;
				i = strSectionName.Find("?");
				CString strAdd;
				strAdd.Format("%d|%s\r\n", atol(strSectionNameFound.Mid(i)), Ini.getKeyValue(strKeyName, strSectionNameFound));
				if (strReturn == "@%!") strReturn = "";
				strReturn += strAdd;
			}
		}
		else strReturn = Ini.getKeyValue(strKeyName, strSectionName);
	}

	return strReturn;
}

CString SetIniKeyValue(CString Cmd, int ProcId)  // SetInikeyValue|PrinterSettings|JamaPrinter9|Samsung SCX-4x24 Series PCL 6

{
	CString strReturn = "@%!";

	int i = Cmd.Find("|");
	int j = Cmd.Find("|", i + 1);
	int k = Cmd.Find("|", j + 1);
	int l = Cmd.Find("\r\n");
	if (l == -1 || (k > 0 && l > k)) {  // klassiek vorm (zie titel)
		CString strSection = Cmd.Mid(i + 1, j - (i + 1));
		if (k > 0 && k < Cmd.GetLength() - 1) {
			CIniFile Ini(theApp.iniFile.m_strFileName);
			strReturn.Format("RetValue=%d", Ini.setKey(Cmd.Mid(k + 1), Cmd.Mid(j + 1, k - j - 1), strSection));
		}
	}
	else {    // Bulk SetIniKeyValue|Post-001_Settings \r\n JMM_Document-002|Printer|Tray|MediaType|PaperSize  \r\n ...
		CString strSection = Cmd.Mid(i + 1, l - (i + 1));
		CIniFile Ini(theApp.iniFile.m_strFileName);
		while ((l > 0) && ((l + 3) < Cmd.GetLength())) {
			l += 2;
			k = Cmd.Find("|", l);
			if (k > 0) {
				i = Cmd.Find("\r", l);
				if (i < 0) i = Cmd.GetLength();
				Ini.setKey(Cmd.Mid(k + 1, i - (k + 1)), Cmd.Mid(l, k - l), strSection);
			}
			l = Cmd.Find("\r\n", l);
		}
		strReturn = "OK";
	}

	if (JmsExtendedLogging) {
		CString cstr;
		cstr.Format("ProcId=%3d - JmsCmd=%s - Reply=%s", ProcId, Cmd, strReturn);
		cstr.Replace("\r\n", "\\r\\n");
		LogAdd(0, 2, cstr);
	}

	return strReturn;
}

CString OvlError(CString Cmd, int ProcId)  // OvlError|19|240|De waarde van Test=1 en had =0 moeten zijn
{
	CString strReturn = "@%!";

	int i = Cmd.Find("|");
	int j = Cmd.Find("|", i + 1);
	int k = Cmd.Find("|", j + 1);
	if (i > 0 && j > i && k > j) {
		int OvlNum = atol(Cmd.Mid(i + 1, j - (i + 1)));
		int ErrNum = atol(Cmd.Mid(j + 1, k - (j + 1)));
		CString ErrString = Cmd.Mid(k + 1);
		CString cstr;
		cstr.Format("OVL-%04d ERR-%d : %s", OvlNum, ErrNum, ErrString);
		if (ErrNum) LogAdd(109, 0, cstr);
		else LogAdd(0, 0, cstr);
		strReturn = "OK";
	}

	return strReturn;
}


CString SetJmhWnd(CString Cmd)  // SetJmhWnd-002|B23710    
{
	CString strReturn = "@%!";

	int i = Cmd.Find("|");
	if (i > 0 && i < Cmd.GetLength() - 1) {
		int PostNr = atol(Cmd.Mid(10));
		HWND JmhWnd;
		i = sscanf_s(Cmd.Mid(i + 1), "%x", &JmhWnd, sizeof(HWND));
		if (PostNr >= 1 && PostNr <= MAX_POST) {
			PostWnd[PostNr - 1] = JmhWnd;
			if (JmsExtendedLogging) {
				CString cstr;
				cstr.Format("SetJmhWnd[%3d] = %X", PostNr, JmhWnd);
				LogAdd(0, 2, cstr);
			}
		}
		strReturn = "OK";
	}
	return strReturn;
}

CString GetJmhWnd(CString Cmd)  // GetJmhWnd-002   -> reply is HEX-vorm    
{
	CString strReturn = "@%!";

	if (Cmd.GetLength() > 10) {
		int PostNr = atol(Cmd.Mid(10));
		strReturn.Format("%08X", PostWnd[PostNr - 1]);
	}
	return strReturn;
}

CString GetPostNrFromLicense(CString Cmd)  // GetPostNrFromLicense|02ABCDEFGB   
{
	CString strReturn = "@%!";

	int i = Cmd.Find("|");
	if (i > 0 && (i + 1 + 10) <= Cmd.GetLength()) {
		CString JamaSettings = GetIniSectionData("GetIniSectionData|JamaSettings");
		i = JamaSettings.Find(Cmd.Mid(i + 1, 10));
		if (i > 0) {
			while (i > 0 && JamaSettings.GetAt(i) != '\n') i--;
			if (i > 0) {
				i += 10;
				strReturn = JamaSettings.Mid(i, 8);
			}
		}
	}
	return strReturn;
}

CString CheckLayout(CString Cmd)   // "CheckLayout|DEMO-JMD32\r\nFTLT3BEU.BMP|01CAD6F8|EFFC4000\r\nFTLT3BEU.GIF|01CAD6F9|25A12900\r\nftlt3ghf.gif|01CBAB2E|E3EF7DDC\r\n"
{
	CString strReturn = "@%!";
	CString cstr, PostNr;

	int i = Cmd.Find("|");
	int j = Cmd.Find("\r\n");
	if (i < 0 || j < i) return strReturn;

	cstr = Cmd.Mid(i + 1, j - (i + 1));
	if (cstr.GetLength() > 5 && cstr.Left(5).Compare("Post-") == 0) PostNr = cstr;
	else {
		cstr = "GetPostNrFromLicense|" + cstr;
		PostNr = GetPostNrFromLicense(cstr);
	}
	if (PostNr.Left(4).CompareNoCase("post") != 0) return strReturn;

	Cmd = Cmd.MakeLower();

	CFileFind finder;
	CString FileNameToFind = PathProg + "LT??????.*";
	BOOL bWorking = finder.FindFile(FileNameToFind);
	bool DidICopyFileFlag = false;
	while (bWorking) {
		bWorking = finder.FindNextFile();
		if (finder.IsDirectory()) continue;

		CString JmsLine = "";
		CString Ext = finder.GetFileName().Right(3).MakeLower();
		if (Ext == "jpg" || Ext == "png" || Ext == "gif" || Ext == "bmp") {
			FILETIME ftLastWrite;
			finder.GetLastWriteTime(&ftLastWrite);
			JmsLine.Format("%s|%08X|%08X\r\n", finder.GetFileName(), ftLastWrite.dwLowDateTime, ftLastWrite.dwHighDateTime);
			JmsLine.MakeLower();
			if (Cmd.Find(JmsLine) < 0) {
				CString ToClientFilePath = PathSpoolToClient + PostNr + "\\";
				CreateDirectory(ToClientFilePath, NULL);
				ToClientFilePath += finder.GetFileName();
				CopyFile(finder.GetFilePath(), ToClientFilePath, FALSE);
				DidICopyFileFlag = true;
			}
		}
	}
	finder.Close();
	int numPostNr = atol(PostNr.Mid(5));
	if (DidICopyFileFlag && numPostNr >= 1 && numPostNr <= MAX_POST) ::PostMessage(PostWnd[numPostNr - 1], WM_USER + 2, 0, 0); // proc_send2peer ...

	return strReturn;
}

extern char FullJamadataBackupStatus[200];
CString CreateFullJamadataBackup(CString Cmd, int ProcId)   // "CreateFullJamadataBackup|w
{
	CString strReturn = "@%!";
	bool WorkFiles = false;

	int i = Cmd.Find("|");
	if (i > 0 && Cmd.GetLength() > i + 1) {
		if (Cmd.GetAt(i + 1) == 'w' || Cmd.GetAt(i + 1) == 'W') WorkFiles = true;
	}

	pMainDlg->CreateFullJamadataBackup(WorkFiles, 1 + (ProcId / 5)); // PostNr doorgeven !
	strReturn = "OK";

	return strReturn;
}

bool HttpGetUpdate(bool RestartFlag);

void _HttpGetUpdate(void *) {
	HttpGetUpdate(true);
}

CString DownloadUpdate(CString Cmd, int ProcId)   // "CreateFullJamadataBackup|w
{
	CString strReturn = "@%!";

	_beginthread(_HttpGetUpdate, 0, NULL);
	strReturn = "OK";
	return strReturn;
}

CString CmdControlDBSessions(CString Cmd, int ProcId)   // "ControlDBSessions|GetSessionsInfo" "ControlDBSessions|GetMySessionInfo"
																											  // "ControlDBSessions|GetFullBackupStatus"
														// "ControlDBSessions|JmdLogOff" 
{                                                       // "ControlDBSessions|SetServiceMode" "ControlDBSession|SetOperational" 
														// "ControlDBSessions|SetServiceInfo|[message]" "ControlDBSessions|GetServiceInfo"
	CString strReturn = "@%!";

	int i = Cmd.Find("|");
	if (i < 0) return strReturn;
	int k = Cmd.Find("|", i + 1);
	CString SubCmd = Cmd.Mid(i + 1);
	if (k > 0) SubCmd = Cmd.Mid(i + 1, k - (i + 1));

	SubCmd.MakeUpper();
	bool AllFlag = false;
	if (SubCmd.GetLength() > 3 && SubCmd.Left(3) == "ALL") {
		AllFlag = true;
		SubCmd = SubCmd.Mid(3);
	}
	int PostNr = 1 + (ProcId / 5);
	if (PostNr<1 || PostNr>MAX_POST) return strReturn;

	if (SubCmd == "GETSESSIONSINFO" || SubCmd == "GETMYSESSIONINFO") {
		strReturn = "";
		int LineCount = 0, ProcIdStart = 0, ProcIdStop = MAX_PROC;
		if (SubCmd == "GETMYSESSIONINFO") {
			IsPostActive[PostNr - 1] = true;
			ProcIdStart = (PostNr - 1) * 5;
			ProcIdStop = ProcIdStart + 5;
		}
		for (i = ProcIdStart; i < ProcIdStop; i++) {
			int ThatPostNr = 1 + (i / 5);
			if (IsPostActive[ThatPostNr - 1] && ProcCurrentState[i] > 0) {
				CString cstr;
				cstr.Format("%03d|%d\r\n", i, ProcCurrentState[i]);
				strReturn += cstr; LineCount++;
			}
		}
		CString cstr;
		cstr.Format("LINCNT=%d\r\n", LineCount);
		strReturn = cstr + strReturn;
	}
	else if (SubCmd == "JMDLOGOFF") {
		strReturn = "OK";
		IsPostActive[PostNr - 1] = false;
	}
	else if (SubCmd == "SETSERVICEMODE") {
		JMSServiceMode = true;
		for (int DBRef = 0; DBRef < DB_MAX; DBRef++) {
			if (!DB[DBRef].Name[0]) continue;
			EDBEndAllSessions(DBRef);
			DB[DBRef].OpenCount = 1;
			UnMountDB(DBRef);
		}
		SysCloseAll();
		ServiceInfoMessage = "SERVICE";
		strReturn = "OK";
	}
	else if (SubCmd == "SETOPERATIONAL") {
		JMSServiceMode = false;
		SysInit();
		ServiceInfoMessage = "OPERATIONAL";
		strReturn = "OK";
	}
	else if (SubCmd == "SETSERVICEINFO") {
		if (k > 0) {
			ServiceInfoMessage = Cmd.Mid(k + 1);
			strReturn = "OK";
		}
	}
	else if (SubCmd == "GETSERVICEINFO") {
		strReturn = ServiceInfoMessage;
	}
	else if (SubCmd == "GETFULLBACKUPSTATUS") {
		strReturn = FullJamadataBackupStatus;
	}

	if (JmsExtendedLogging) {
		CString cstr;
		cstr.Format("ProcId=%3d - JmsCmd=%s - Reply=%s", ProcId, Cmd, strReturn);
		cstr.Replace("\r\n", "\\r\\n");
		LogAdd(0, 2, cstr);
	}

	return strReturn;
}

void CreateSnapShot(char *ext, int LifeTimeMinutes, bool IncludeWorkFiles);

CString CmdCreateSnapshot(CString Cmd, int ProcId)   // "CreateSnapshot|w90"
{
	CString strReturn = "@%!";
	bool WorkFiles = false;

	int i = Cmd.Find("|");
	if (i < 0) return strReturn;
	if (Cmd.GetAt(i + 1) == 'w' || Cmd.GetAt(i + 1) == 'W') {
		WorkFiles = true;
		i++;
	}
	int LifeTimeMinutes = atol(Cmd.Mid(i + 1));

	int SysIx = Proc2SysRef[ProcId];
	if (Sys[SysIx].Name[0]) {
		CreateSnapShot((char*)(LPCTSTR)Sys[SysIx].Ext, LifeTimeMinutes, WorkFiles);
		strReturn = "OK";
	}

	if (JmsExtendedLogging) {
		CString cstr;
		cstr.Format("ProcId=%3d - JmsCmd=%s - Reply=%s", ProcId, Cmd, strReturn);
		cstr.Replace("\r\n", "\\r\\n");
		LogAdd(0, 2, cstr);
	}

	return strReturn;
}

CString CmdRestartUcServer(CString Cmd, int ProcId)
{
	CString strReturn = "@%!";
	bool WorkFiles = false;

	TerminateThread(theApp.UCServerhThread, 0);
	CloseHandle(theApp.UCServerhThread);
	theApp.UCServerhThread = (HANDLE)-1L;

	// if (JmsExtendedLogging) {
	CString cstr;
	cstr.Format("ProcId=%3d - JmsCmd=%s - Reply=%s", ProcId, Cmd, "Done" /* strReturn*/);
	cstr.Replace("\r\n", "\\r\\n");
	LogAdd(0, 2, cstr);
	//}
	return strReturn;
}


CString CmdExecBatch(CString Cmd, int ProcId) // cstr=JmsCmd("ExecBatch|[NAAM VAN FILE INCL EXT]") (uiteraard zonder [] tekens/ cstr krijgt de output
{
	CString strReturn = "@%!";

	int i = Cmd.Find("|");
	if (i < 0) return strReturn;
	CString BatchCmd = PathJamaRoot + "Batch\\" + Cmd.Mid(i + 1);

	STARTUPINFO si;
	SECURITY_ATTRIBUTES sa;
	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof STARTUPINFO;
	sa.nLength = sizeof(SECURITY_ATTRIBUTES);
	sa.lpSecurityDescriptor = NULL;
	sa.bInheritHandle = TRUE;
	CString OutputFilePath;
	OutputFilePath.Format("BatchOut%d", ProcId);
	HANDLE hFile = CreateFile(OutputFilePath, GENERIC_READ | GENERIC_WRITE, 0, &sa, CREATE_ALWAYS, 0, 0);
	if (hFile != INVALID_HANDLE_VALUE) {
		si.dwFlags = STARTF_USESTDHANDLES;
		si.hStdInput = GetStdHandle(STD_INPUT_HANDLE);
		si.hStdOutput = hFile;
		si.hStdError = hFile;
	}
	else return strReturn;

	PROCESS_INFORMATION pi;
	BOOL res;
	res = CreateProcess(NULL, (char*)(LPCTSTR)BatchCmd, NULL, NULL, TRUE, NORMAL_PRIORITY_CLASS, NULL, NULL, &si, &pi);
	if (TRUE == res) {
		WaitForSingleObject(pi.hProcess, (120 * 1000));
		CloseHandle(pi.hProcess);
		CloseHandle(pi.hThread);
	}
	else return strReturn;

	CloseHandle(hFile);
	CFile fil;
	if (fil.Open(OutputFilePath, CFile::modeRead, NULL)) {
		char* buf = new char[(UINT)fil.GetLength() + 10];
		int len = fil.Read(buf, (UINT)fil.GetLength());
		buf[len] = 0;
		fil.Close();
		strReturn = buf;
		delete buf;
	}
	_unlink(OutputFilePath);

	if (JmsExtendedLogging) {
		CString cstr;
		cstr.Format("ProcId=%3d - JmsCmd=%s - Reply=%s", ProcId, Cmd, strReturn);
		cstr.Replace("\r\n", "\\r\\n");
		LogAdd(0, 2, cstr);
	}

	return strReturn;
}

CString CmdGetFileFromServer(CString FileName, int ProcId) // cstr=JmsCmd("GetFileFromServer|[NAAM VAN FILE INCL EXT]") (uiteraard zonder [] tekens/ cstr krijgt de output
{
	CString strReturn = "@%!";
	CString ToClientPost, fromname_;

	if (FileName.GetAt(1) == ':' || FileName.Left(2).Compare("\\\\") == 0) fromname_ = FileName;
	else fromname_ = PathProg + FileName;
	if (GetFileAttributes(fromname_) != INVALID_FILE_ATTRIBUTES) {
		ToClientPost.Format("%sPost-%03d\\", PathSpoolToClient, 1 + ProcId / 5);
		if (JMSVersion == 'M') ToClientPost = PathSpool + "Received\\";
		CreateDirectory(ToClientPost, NULL);
		int j = FileName.ReverseFind('\\');
		if (j >= 0) ToClientPost += FileName.Mid(j + 1);
		else ToClientPost += FileName;
		CopyFile(fromname_, ToClientPost, FALSE);
		if (JMSVersion == 'M') {  // forceren om file door te sturen en verkenner open te doen
			HWND JMD = FindWindow("THE_JMD", NULL);
			if (JMD) PostMessage(JMD, WM_USER + 5, 0, 0); // 0x405, 0, 0); // PROC_RECEIVED_FILES -> de JMD moet deze file verwerken !		
		}
		else {
			int PostNr = 1 + ProcId / 5; // ComBuf->OrigId/5;
			if (PostWnd[PostNr - 1] == 0) {
				LogAdd(109, 0, "hWnd for JMH not filled in, so Txmit of file slow for PostNr=", PostNr);
			}
			else PostMessage(PostWnd[PostNr - 1], WM_USER + 2, 0, 0); // proc_send2peer ...
			if (JmsExtendedLogging) {
				CString cstr;
				cstr.Format("Txfer to Post-%03d = %s", PostNr, FileName);
				LogAdd(0, 1, cstr);
			}
		}
		strReturn = "OK";
	}
	return strReturn;
}

CString CmdGetJMSVersion() // "CmdGetJMSVersion\r\n" -> return "M" of "S" of "L" of "P"
{
	CString strReturn;
	strReturn += JMSVersion;
	return strReturn;
}

CString CmdGetIniRemotePrintInfo(CString Cmd)  // "CmdGetIniRemotePrintInfo|Post-001 of CmdGetIniRemotePrintInfo|0123456789 (dossiernr)\r\n" 
{
	CString strReturn;
	int PostNr = 0;

	int i = Cmd.Find("|");
	if (i < 0) return strReturn;
	if (Cmd.Mid(i + 1, 5).CompareNoCase("Post-") == 0) {
		PostNr = atol(Cmd.Mid(i + 6, 3));
	}
	else {
		CString JamaSettings = GetIniSectionData("GetIniSectionData|JamaSettings");
		i = JamaSettings.Find(Cmd.Mid(i + 1, 10));
		if (i > 0) {
			while (i > 0 && JamaSettings.GetAt(i) != '\n') i--;
			if (i > 0) {
				i += 10;
				PostNr = atol(JamaSettings.Mid(i + 5, 3));
			}
		}
	}

	int PostCnt = atol(theApp.iniFile.getKeyValue("PostCount", "JamaSettings"));
	if (PostNr<1 || PostNr>PostCnt) PostNr = 1;

	CString IniSections = GetIniSections();
	CString PrinterSection, DrukPostName, DrukPostInfo, PostSection, PostName, PostInfo;
	for (int i = 1; i < 100; i++) {
		PrinterSection.Format("Printer-%03d_Settings", i);
		if (IniSections.Find(PrinterSection) > 0) {
			DrukPostName = theApp.iniFile.getKeyValue("Name", PrinterSection);
			DrukPostInfo.Format("D%03d|%s|", i, DrukPostName);
			strReturn += DrukPostInfo + "\r\n";
		}
	}

	for (int i = 1; i <= PostCnt; i++) {
		PostSection.Format("Post-%03d_Settings", i);
		PostName = theApp.iniFile.getKeyValue("Name", PostSection);
		PostInfo.Format("P%03d|%s|", i, PostName);
		strReturn += PostInfo + "\r\n";
	}

	CString PrinterEntry, PrinterInfo;
	PostSection.Format("Post-%03d_Settings", PostNr);
	for (int i = 1; i < 100; i++) {
		PrinterEntry.Format("Printer-%03d", i);
		PrinterInfo = theApp.iniFile.getKeyValue(PrinterEntry, PostSection);
		if (PrinterInfo.GetLength() > 0) {
			CString AddLine;
			AddLine.Format("R%03d|%s|\r\n", i, PrinterInfo);
			strReturn += AddLine;
		}
	}

	if (strReturn == "") strReturn = "@%!";
	return strReturn;
}

int JamaStrCmpi(char *s, char *f)
{
	int i = strlen(f);
	int j = strlen(s);
	if (j < i) return 0;
	if (_memicmp(s, f, i) != 0) return 0;
	while (i < j) {
		if (s[i] > ' ' && s[i] != '|') break;
		i++;
	}
	return i;
}

void ExecJmsCmd(int ThdRef)
{
	UNALIGNED struct sComBuf *ComBuf;
	char *s = (char *)(LPCTSTR)Thd[ThdRef].strCmdInput;
	ComBuf = (struct sComBuf*)Thd[ThdRef].ComBuf;
	int Len = Thd[ThdRef].strCmdInput.GetLength();
	int l = 0;

	if ((l = JamaStrCmpi(s, "ProcessSplFile")) && (l < Len)) Thd[ThdRef].strCmdReply = pMainDlg->m_dPrintersDlg.AddSPLFileToPrintQueue(Thd[ThdRef].strCmdInput.Mid(l));
	else if ((l = JamaStrCmpi(s, "GetMailTemplates"))) Thd[ThdRef].strCmdReply = pMainDlg->m_dMailDlg.GetTemplateNames();
	else if ((l = JamaStrCmpi(s, "GetAllPrinters"))) Thd[ThdRef].strCmdReply = pMainDlg->m_dPrintersDlg.GetAllPrinterNames();
	else if ((l = JamaStrCmpi(s, "GetAllPrinterBins")) && (l < Len)) Thd[ThdRef].strCmdReply = pMainDlg->m_dPrintersDlg.GetAllPrinterBins(Thd[ThdRef].strCmdInput.Mid(l));
	else if ((l = JamaStrCmpi(s, "GetAllPrinterMedia")) && (l < Len)) Thd[ThdRef].strCmdReply = pMainDlg->m_dPrintersDlg.GetAllPrinterMedia(Thd[ThdRef].strCmdInput.Mid(l));
	else if ((l = JamaStrCmpi(s, "GetAllPrinterPapers")) && (l < Len)) Thd[ThdRef].strCmdReply = pMainDlg->m_dPrintersDlg.GetAllPrinterPapers(Thd[ThdRef].strCmdInput.Mid(l));
	else if ((l = JamaStrCmpi(s, "GetIniSections"))) Thd[ThdRef].strCmdReply = GetIniSections();
	else if ((l = JamaStrCmpi(s, "GetIniSectionData"))) Thd[ThdRef].strCmdReply = GetIniSectionData(Thd[ThdRef].strCmdInput);
	else if ((l = JamaStrCmpi(s, "GetIniKeyValue"))) Thd[ThdRef].strCmdReply = GetIniKeyValue(Thd[ThdRef].strCmdInput);
	else if ((l = JamaStrCmpi(s, "SetInikeyValue"))) Thd[ThdRef].strCmdReply = SetIniKeyValue(Thd[ThdRef].strCmdInput, ComBuf->OrigId);
	else if ((l = JamaStrCmpi(s, "GetMailEnveloppes")) && (l < Len)) Thd[ThdRef].strCmdReply = pMainDlg->m_dMailDlg.GetMailEnveloppes(Thd[ThdRef].strCmdInput.Mid(l), ComBuf->OrigId);
	else if ((l = JamaStrCmpi(s, "GetMailMessage")) && (l < Len)) Thd[ThdRef].strCmdReply = pMainDlg->m_dMailDlg.GetMailMessage(Thd[ThdRef].strCmdInput.Mid(l), ComBuf->OrigId);
	else if ((l = JamaStrCmpi(s, "GetTemplateMergeFields")) && (l < Len)) {
		Thd[ThdRef].strCmdReply = pMainDlg->m_dMailDlg.GetTemplateMergeFields(Thd[ThdRef].strCmdInput.Mid(l));
	}
	else if ((l = JamaStrCmpi(s, "MergeTemplateAndMail")) && (l < Len)) {
		Thd[ThdRef].strCmdReply = pMainDlg->m_dMailDlg.MergeTemplateAndMail(Thd[ThdRef].strCmdInput.Mid(l), ComBuf->OrigId);
	}
	else if ((l = JamaStrCmpi(s, "CheckEmailAddress")) && (l < Len)) Thd[ThdRef].strCmdReply = pMainDlg->m_dMailDlg.CheckEmailAddress(Thd[ThdRef].strCmdInput.Mid(l));
	else if ((l = JamaStrCmpi(s, "SetJmhWnd-")) && (l < Len)) Thd[ThdRef].strCmdReply = SetJmhWnd(Thd[ThdRef].strCmdInput);
	else if ((l = JamaStrCmpi(s, "GetJmhWnd-")) && (l < Len)) Thd[ThdRef].strCmdReply = GetJmhWnd(Thd[ThdRef].strCmdInput);
	else if ((l = JamaStrCmpi(s, "GetPostNrFromLicense")) && (l < Len)) Thd[ThdRef].strCmdReply = GetPostNrFromLicense(Thd[ThdRef].strCmdInput);
	else if ((l = JamaStrCmpi(s, "CheckLayout")) && (l < Len)) Thd[ThdRef].strCmdReply = CheckLayout(Thd[ThdRef].strCmdInput);
	else if ((l = JamaStrCmpi(s, "CreateSnapshot")) && (l < Len)) Thd[ThdRef].strCmdReply = CmdCreateSnapshot(Thd[ThdRef].strCmdInput, ComBuf->OrigId);
	else if ((l = JamaStrCmpi(s, "RestartUcServer")) && (l <= Len)) Thd[ThdRef].strCmdReply = CmdRestartUcServer(Thd[ThdRef].strCmdInput, ComBuf->OrigId);
	else if ((l = JamaStrCmpi(s, "GetJMSVersion"))) Thd[ThdRef].strCmdReply = CmdGetJMSVersion();
	else if ((l = JamaStrCmpi(s, "GetIniRemotePrintInfo")) && (l < Len)) Thd[ThdRef].strCmdReply = CmdGetIniRemotePrintInfo(Thd[ThdRef].strCmdInput);
	else if ((l = JamaStrCmpi(s, "ControlDBSessions")) && (l < Len)) Thd[ThdRef].strCmdReply = CmdControlDBSessions(Thd[ThdRef].strCmdInput, ComBuf->OrigId);
	else if ((l = JamaStrCmpi(s, "CreateFullJamadataBackup")) && (l < Len)) Thd[ThdRef].strCmdReply = CreateFullJamadataBackup(Thd[ThdRef].strCmdInput, ComBuf->OrigId);
	else if ((l = JamaStrCmpi(s, "DownloadUpdate")) && (l <= Len)) Thd[ThdRef].strCmdReply = DownloadUpdate(Thd[ThdRef].strCmdInput, ComBuf->OrigId);
	else if ((l = JamaStrCmpi(s, "ExecBatch")) && (l < Len)) Thd[ThdRef].strCmdReply = CmdExecBatch(Thd[ThdRef].strCmdInput, ComBuf->OrigId);
	else if ((l = JamaStrCmpi(s, "GetFileFromServer")) && (l < Len)) Thd[ThdRef].strCmdReply = CmdGetFileFromServer(Thd[ThdRef].strCmdInput.Mid(l), ComBuf->OrigId);
	else if ((l = JamaStrCmpi(s, "ViewMail")) && (l < Len)) Thd[ThdRef].strCmdReply = pMainDlg->m_dMailDlg.ViewMail(Thd[ThdRef].strCmdInput.Mid(l), ComBuf->OrigId);
	else if ((l = JamaStrCmpi(s, "OvlError")) && (l < Len)) Thd[ThdRef].strCmdReply = OvlError(Thd[ThdRef].strCmdInput, ComBuf->OrigId);
	// new by marc on 25/08/2017
	else if ((l = JamaStrCmpi(s, "FtpUpload")) && (l < Len)) Thd[ThdRef].strCmdReply = pMainDlg->CmdFtpUpload(Thd[ThdRef].strCmdInput.Mid(l));
	else if ((l = JamaStrCmpi(s, "FtpDownload")) && (l < Len)) Thd[ThdRef].strCmdReply = pMainDlg->CmdFtpDownload(Thd[ThdRef].strCmdInput.Mid(l));
	else if ((l = JamaStrCmpi(s, "FtpDirectory")) && (l < Len)) Thd[ThdRef].strCmdReply = pMainDlg->CmdFtpDirectory(Thd[ThdRef].strCmdInput.Mid(l));
	else if ((l = JamaStrCmpi(s, "FtpDelete")) && (l < Len)) Thd[ThdRef].strCmdReply = pMainDlg->CmdFtpDelete(Thd[ThdRef].strCmdInput.Mid(l));
	else if ((l = JamaStrCmpi(s, "SFtpUpload2")) && (l < Len)) Thd[ThdRef].strCmdReply = pMainDlg->CmdSFtpUpload2(Thd[ThdRef].strCmdInput.Mid(l));
	else if ((l = JamaStrCmpi(s, "SFtpUpload")) && (l < Len)) Thd[ThdRef].strCmdReply = pMainDlg->CmdSFtpUpload(Thd[ThdRef].strCmdInput.Mid(l));
	else if ((l = JamaStrCmpi(s, "SFtpDownload2")) && (l < Len)) Thd[ThdRef].strCmdReply = pMainDlg->CmdSFtpDownload2(Thd[ThdRef].strCmdInput.Mid(l));
	else if ((l = JamaStrCmpi(s, "SFtpDownload")) && (l < Len)) Thd[ThdRef].strCmdReply = pMainDlg->CmdSFtpDownload(Thd[ThdRef].strCmdInput.Mid(l));
	else if ((l = JamaStrCmpi(s, "SFtpDirectory2")) && (l < Len)) Thd[ThdRef].strCmdReply = pMainDlg->CmdSFtpDirectory2(Thd[ThdRef].strCmdInput.Mid(l));
	else if ((l = JamaStrCmpi(s, "SFtpDirectory")) && (l < Len)) Thd[ThdRef].strCmdReply = pMainDlg->CmdSFtpDirectory(Thd[ThdRef].strCmdInput.Mid(l));
	else if ((l = JamaStrCmpi(s, "SFtpDelete2")) && (l < Len)) Thd[ThdRef].strCmdReply = pMainDlg->CmdSFtpDelete2(Thd[ThdRef].strCmdInput.Mid(l));
	else if ((l = JamaStrCmpi(s, "SFtpDelete")) && (l < Len)) Thd[ThdRef].strCmdReply = pMainDlg->CmdSFtpDelete(Thd[ThdRef].strCmdInput.Mid(l));
	else if ((l = JamaStrCmpi(s, "IbanityShowLicence")) && (l < Len)) Thd[ThdRef].strCmdReply = pMainDlg->CmdIbanityShowLicence(Thd[ThdRef].strCmdInput.Mid(l));
	else if ((l = JamaStrCmpi(s, "IbanityCheckVAT")) && (l < Len)) Thd[ThdRef].strCmdReply = pMainDlg->CmdIbanityCheckVAT(Thd[ThdRef].strCmdInput.Mid(l));
	else if ((l = JamaStrCmpi(s, "IbanityCheckGLN")) && (l < Len)) Thd[ThdRef].strCmdReply = pMainDlg->CmdIbanityCheckGLN(Thd[ThdRef].strCmdInput.Mid(l));
	else if ((l = JamaStrCmpi(s, "IbanityUBLUpload")) && (l < Len)) Thd[ThdRef].strCmdReply = pMainDlg->CmdIbanityUBLUpload(Thd[ThdRef].strCmdInput.Mid(l));
	else if ((l = JamaStrCmpi(s, "IbanityUBLStatus")) && (l < Len)) Thd[ThdRef].strCmdReply = pMainDlg->CmdIbanityUBLStatus(Thd[ThdRef].strCmdInput.Mid(l));
	else if ((l = JamaStrCmpi(s, "PeppolSendDocument")) && (l < Len)) Thd[ThdRef].strCmdReply = pMainDlg->CmdPeppolSendDocument(Thd[ThdRef].strCmdInput.Mid(l));
	else if ((l = JamaStrCmpi(s, "PeppolGetDocumentStatus")) && (l < Len)) Thd[ThdRef].strCmdReply = pMainDlg->CmdPeppolGetDocumentStatus(Thd[ThdRef].strCmdInput.Mid(l));
	else if ((l = JamaStrCmpi(s, "PeppolExportDocuments")) && (l < Len)) Thd[ThdRef].strCmdReply = pMainDlg->CmdPeppolExportDocuments(Thd[ThdRef].strCmdInput.Mid(l));
	else if ((l = JamaStrCmpi(s, "PeppolMarkDocumentAsExported")) && (l < Len)) Thd[ThdRef].strCmdReply = pMainDlg->CmdPeppolMarkDocumentAsExported(Thd[ThdRef].strCmdInput.Mid(l));
	else if ((l = JamaStrCmpi(s, "PeppolLookup")) && (l < Len)) Thd[ThdRef].strCmdReply = pMainDlg->CmdPeppolLookup(Thd[ThdRef].strCmdInput.Mid(l));
	else if ((l = JamaStrCmpi(s, "PepPolCheckVAT")) && (l < Len)) Thd[ThdRef].strCmdReply = pMainDlg->CmdPepPolCheckVAT(Thd[ThdRef].strCmdInput.Mid(l));
	else if ((l = JamaStrCmpi(s, "PepPolUBLUpload")) && (l < Len)) Thd[ThdRef].strCmdReply = pMainDlg->CmdPepPolUBLUpload(Thd[ThdRef].strCmdInput.Mid(l));
	else if ((l = JamaStrCmpi(s, "PepPolUBLStatus")) && (l < Len)) Thd[ThdRef].strCmdReply = pMainDlg->CmdPepPolUBLStatus(Thd[ThdRef].strCmdInput.Mid(l));
	else if ((l = JamaStrCmpi(s, "WebrequestJson")) && (l < Len)) Thd[ThdRef].strCmdReply = pMainDlg->CmdWebrequestJson(Thd[ThdRef].strCmdInput.Mid(l));
	else if ((l = JamaStrCmpi(s, "JsonToXml")) && (l < Len)) Thd[ThdRef].strCmdReply = pMainDlg->CmdJsonToXml(Thd[ThdRef].strCmdInput.Mid(l));
	else if ((l = JamaStrCmpi(s, "XmlToJson")) && (l < Len)) Thd[ThdRef].strCmdReply = pMainDlg->CmdXmlToJson(Thd[ThdRef].strCmdInput.Mid(l));
	else Thd[ThdRef].strCmdReply = "*** Error ! Command not recognised : " + Thd[ThdRef].strCmdInput;



}

void ComBufExec(int ThdRef)
{
	int error = 0;
	//char ThdBuf_OnEntry[50];
	UNALIGNED struct sComBuf *ComBuf;
	CString cstr;
	//DWORD TickOnEntry, TickOnExit;

	Thd[ThdRef].ReplyLength = 0;
	//memcpy(ThdBuf_OnEntry,Thd[ThdRef].ComBuf,sizeof(ThdBuf_OnEntry));
	//TickOnEntry=GetTickCount();

	int WaitCnt = 120;
	while (WaitCnt-- > 0) {
		if (pMainDlg->m_dDataBaseDlg.m_UpAndRunning) break;
		Sleep(500);
		pMainDlg->ProcessAllMessages();
	}

	theApp.ProgDidSomeWork++;
	ComBuf = (struct sComBuf*)Thd[ThdRef].ComBuf;
	if (ComBuf->Type == SYS_REQ) { // SYSMNGR
		switch (ComBuf->Function) {
		case 1:
			if (ComBuf->OrigId >= 0 && ComBuf->OrigId < MAX_PROC) Proc2ThdRef[ComBuf->OrigId] = ThdRef;
			SysFileOpen(ThdRef);
			break;
		case 2:
			SysFileClose(ThdRef);
			break;
		case 3:
			SysFileRead(ThdRef);
			break;
		case 4:
			SysFileWrite(ThdRef);
			break;
		case 5: // flush, not needed anymore
				  // no reply needed
			break;
		default:
			CString cstr;
			cstr.Format("Call SysMngr from ThdRef=%d (OrigId=%d) not handled", ThdRef, ComBuf->OrigId);
			LogAdd(17, 0, cstr, ComBuf->Function);
			break;
		}
	}
	else if (ComBuf->Type == FAS_REQ) {
		switch (ComBuf->Function) {
		case 1: FasOpen(ThdRef); break;
		case 20:
		case 21:
			FasGetu(ThdRef);
			break;
		case 40:
		case 41:
			if (*(short int *)&ComBuf->Info[4] > 499) {
				vervaldag(*(short int *)&ComBuf->Info[4], (char *)&ComBuf->Info[0]);
				FasReturn(ThdRef, 0, sizeof(vv_sys), (char *)&vv_sys);
				break;
			}
			FasKeyu(ThdRef);
			break;
		case 42:
			//			memcpy(u(ComBuf->StuNr,0),&ComBuf->Info[6],fldlen(ComBuf->StuNr,0));
			//			error=mdbskip(ComBuf->StuNr,ComBuf->Info[0],ComBuf->Info[1]);
			break;
		case 90:
		case 91:
			FasUpd(ThdRef);
			break;
		case 110:
		case 111:
			FasAddi(ThdRef);
			break;
		case 180:
			FasKill(ThdRef);
			//			error=mdbkill(ComBuf->StuNr);
			break;
		case 200: FasClose(ThdRef); break;
		case 201: FasReturn(ThdRef, 0); break; //fasflush()
		case 202: ExecXls(ThdRef); break;
		case 210: FasUnlock(ThdRef); break;
		case 240: FasInfo(ThdRef); break;
		case 250: FasSeqi(ThdRef); break;
		case 251: FasSeqo(ThdRef); break;
		default:
			CString cstr;
			cstr.Format("Call FasMngr from ThdRef=%d (OrigId=%d) not handled", ThdRef, ComBuf->OrigId);
			LogAdd(9, 0, cstr, ComBuf->Function);
			break;
		}
	}
	else if (ComBuf->Type == JMS_REQ) {
		Thd[ThdRef].ReplyLength = -1;
		switch (ComBuf->Function) {
		case 100: // Het ganse JmsCmd zit in de buffer
			ComBuf->Info[ComBuf->Len] = 0;
			Thd[ThdRef].strCmdInput = ComBuf->Info;
			ExecJmsCmd(ThdRef);
			break;
		case 101: // Dit is de eerste buffer vd JmsCmd, maar er komen er nog !
			ComBuf->Info[ComBuf->Len] = 0;
			Thd[ThdRef].strCmdInput = ComBuf->Info;
			break;
		case 102: // Dit is het tweede of later deel buffer vd JmsCmd, maar er komen er nog !
			ComBuf->Info[ComBuf->Len] = 0;
			Thd[ThdRef].strCmdInput += ComBuf->Info;
			break;
		case 103: // Dit is het tweede of later deel buffer vd JmsCmd, en ook het laatste, voer het dus uit !
			ComBuf->Info[ComBuf->Len] = 0;
			Thd[ThdRef].strCmdInput += ComBuf->Info;
			ExecJmsCmd(ThdRef);
			break;
		case 104: // callback om rest van antwoord op te halen ... (106)
			break;
		default:
			CString cstr;
			cstr.Format("Call JMS_REQ from ThdRef=%d (OrigId=%d) not handled", ThdRef, ComBuf->OrigId);
			LogAdd(9, 0, cstr, ComBuf->Function);
			break;
		}
		ComBuf->Type = JMS_REQ;
		ComBuf->Function = 101;
	}
	else {
		LogAdd(2, 0, "Unhandled Task received in JMS, Type", ComBuf->Type);
	}

	int ThisId = ComBuf->DestId;
	ComBuf->DestId = ComBuf->OrigId;


	if (Thd[ThdRef].ReplyLength == -1) { // return zit in CString strCmdReply, die groter kan zijn info-buf
		if (Thd[ThdRef].strCmdReply == "@%!") Thd[ThdRef].strCmdReply = "Invalid JmsCmd = " + Thd[ThdRef].strCmdInput;  // bij functies die geen antwoord mogen teruggeven
		Thd[ThdRef].ReplyLength = Thd[ThdRef].strCmdReply.GetLength() + 1;
		if (Thd[ThdRef].ReplyLength > BUF_LEN - 1) Thd[ThdRef].ReplyLength = BUF_LEN - 1;
		memcpy(ComBuf->Info, Thd[ThdRef].strCmdReply, Thd[ThdRef].ReplyLength);
		if (Thd[ThdRef].ReplyLength < Thd[ThdRef].strCmdReply.GetLength()) {
			Thd[ThdRef].strCmdReply = Thd[ThdRef].strCmdReply.Mid(Thd[ThdRef].ReplyLength);
			ComBuf->Function = 106; // komt aub terug om vervolg op te halen ...
		}
		else {
			Thd[ThdRef].strCmdReply = "";
			ComBuf->Function = 105; // het hele antwoord is verstuurd ! Ge moet niet meer terug komen om een langer antwoord op te halen ...
		}
	}
	if (Thd[ThdRef].ReplyLength) {
		ComBuf->Len = Thd[ThdRef].ReplyLength;
	}

	/*
  TickOnExit=GetTickCount();
	if (TickOnExit>(TickOnEntry+MAX_MSEC_EXEC)) {
		LogAdd(0,1,"Task executed too slow, time(ms)",(int)(TickOnExit-TickOnEntry));
		CString cstr, hstr;
		char *pp;
		for (int i=0; i<2; i++) {
			if (i==0) {
				ComBuf=(struct sComBuf*)ThdBuf_OnEntry;
				pp="Rc";
			}
			else {
				ComBuf=(struct sComBuf*)Thd[ThdRef].ComBuf;
				pp="Tx";
			}
			cstr.Format(" %s-> Typ=%03d Fun=%03d Len=%04d Inf=x",pp,ComBuf->Type,ComBuf->Function,ComBuf->Len);
			for (int j=0; j<20; j++) {
				if (j==ComBuf->Len) break;
				hstr.Format("%02X",ComBuf->Info[j]);
				cstr+=hstr;
			}
			LogAdd(0,1,cstr);
		}
	}
  */

}

void CDataBaseDlg::OnBnClickedBtncheck()
{
	CString SysExt;

	CString Reply = DownloadUpdate("DownloadUpdate", 1);

	return;

	//  CString Reply = OvlError("OvlError|19|240|De waarde van Test=1 en had =0 moeten zijn",1);

	return;


	Reply = SetIniKeyValue("SetIniKeyValue|Post-009_Settings\r\nPrinter-001|\r\n", 5);

	return;




	Reply = CmdExecBatch("ExecBatch|dir.bat", 1);

	Reply = CmdControlDBSessions("ControlDBSessions|SetServiceMode", 1);
	Reply = CmdControlDBSessions("ControlDBSessions|GetServiceInfo", 1);
	Reply = CmdControlDBSessions("ControlDBSessions|SetServiceInfo|TestMessage", 1);
	Reply = CmdControlDBSessions("ControlDBSessions|GetServiceInfo", 1);
	Reply = CmdControlDBSessions("ControlDBSessions|SetOperational", 1);
	Reply = CmdControlDBSessions("ControlDBSessions|GetServiceInfo", 1);

	// CompareSignaturesDBvsCopy();

	//HttpGetUpdate();
	//CString cstr = CmdGetIniRemotePrintInfo("CmdGetIniRemotePrintInfo|Post-001");

	/*
	  int DBRef;
	  CString DBName;

	  DBRef=FindDB((char *)(LPCTSTR)DBName);
	  if (DBRef<0) return;

	  _beginthread((void(*)(void*))EDBCheckCalc, 0, (void*)&DB[DBRef]);
	  pMainDlg->ShowWindowNumber(0);
	*/
}


/*
bool CompactAllFas(char *ext)
{
	CString SysFilePath, PathDBackupSub;
  char SysBuf[MAX_SYS_LEN];
	CFile SysFile;
	char BackupName[350], OrigName[350];
  JET_ERR _jeterr;

	CString cstr;
	cstr.Format("Start compact backup of dataset %s",ext);
	LogAdd(0,1,cstr);

	PathDBackupSub=PathDBackup;
	PathDBackupSub+=ext;
	PathDBackupSub+="\\";
	_mkdir(PathDBackupSub);

	SysFilePath=PathDB;
	SysFilePath+="SYS.";
	SysFilePath+=ext;

	SysFile.Open(SysFilePath,CFile::modeRead,0);
	SysFile.Read(SysBuf,MAX_SYS_LEN);
	SysFile.Close();

	JET_INSTANCE inst;
	JET_SESID sesid;
	JetCall(2901,JetCreateInstance(&inst,"CompactInst"));
	JetCall(2901,JetInit(&inst));
	JetCall(2903,JetBeginSession(inst,&sesid, 0, 0));

	for (int i=0; i<15; i++) {
		char FileName[20];
		memcpy(FileName,SysBuf+300+i*17,15);
		FileName[15]=0;
		if (FileName[0]) {
			sprintf_s(OrigName,sizeof(OrigName),"%s%s",PathDB,FileName);
			if (GetFileAttributes(OrigName)!=INVALID_FILE_ATTRIBUTES) {
				sprintf_s(BackupName,sizeof(BackupName),"%s%s",PathDBackupSub,FileName);
				JET_ERR err=JetAttachDatabase(sesid, OrigName, JET_bitDbReadOnly);
				if (err) {
					LogJet(2904,err);
					CString BadName=BackupName;
					BadName+=".Previous";
					if (GetFileAttributes(BackupName)!=INVALID_FILE_ATTRIBUTES) {
						CString BadName=BackupName;
						BadName+=".Previous";
						rename(BackupName,BadName);
					  LogAdd(0,0,"Previous verion used",BadName);
					}
				}
				else {
					remove(BackupName);
					cstr=BackupName;
					cstr+=".Previous";
					remove(cstr); // moest die previous-version nog bestaan, dan mag die nu wel weg.
					JetCall(2905,JetCompact(sesid,OrigName,BackupName, NULL, NULL,JET_bitCompactStats));
					JetCall(2906,JetDetachDatabase(sesid, OrigName));
					LogAdd(0,0,"Compact backup created",BackupName);
				}
			}
		}
	}
	JetCall(2907,JetEndSession(sesid,0));
	JetCall(2908,JetTerm(inst));

	CString BackupSysFileName=PathDBackupSub;
	BackupSysFileName+="SYS.";
	BackupSysFileName+=ext;
	BackupSysFileName.MakeLower();
	if (CopyFile(SysFilePath,BackupSysFileName,FALSE)) {
	LogAdd(0,0,"Sys-file copied",BackupSysFileName);
	}

	cstr.Format("Compact backup of dataset %s done ...",ext);
	LogAdd(0,0,cstr);

	return true;
}
*/

void CDataBaseDlg::OnBnClickedBtnexport2fas()
{
	int i;
	CString SysExt;

	int numberSelected = m_lstDBMounted.GetSelCount();
	if (numberSelected > 0)
	{
		int *selIndex = new int[numberSelected];
		m_lstDBMounted.GetSelItems(numberSelected, selIndex);
		pMainDlg->ShowWindowNumber(0);
		for (i = 0; i < numberSelected; i++) {
			m_lstDBMounted.GetText(selIndex[i], SysExt);
			ExportAllFas((char *)(LPCTSTR)SysExt);
		}
		delete selIndex;
	}
}

void ShadowCopyFullCheck();
void CDataBaseDlg::OnBnClickedBtndump2copy()
{
	ShadowCopyFullCheck();
}

void CDataBaseDlg::OnOK()
{
	// CDialog::OnOK(); // moet weg of <ENTER> closed de dialog
}


void CDataBaseDlg::OnBnClickedBtnmount()
{
	int i;
	CString SysExt;

	int numberSelected = m_lstDBAvailable.GetSelCount();
	if (numberSelected > 0)
	{
		int *selIndex = new int[numberSelected];
		m_lstDBAvailable.GetSelItems(numberSelected, selIndex);
		pMainDlg->ShowWindowNumber(0);
		for (i = 0; i < numberSelected; i++) {
			m_lstDBAvailable.GetText(selIndex[i], SysExt);
			int file_ix = SysOpen((char *)(LPCTSTR)SysExt);
		}
		delete selIndex;
	}
}

void CDataBaseDlg::OnBnClickedBtnunmount()
{
	int i;
	CString SysExt;

	int numberSelected = m_lstDBMounted.GetSelCount();
	if (numberSelected > 0)
	{
		int *selIndex = new int[numberSelected];
		m_lstDBMounted.GetSelItems(numberSelected, selIndex);
		pMainDlg->ShowWindowNumber(0);
		for (i = 0; i < numberSelected; i++) {
			m_lstDBMounted.GetText(selIndex[i], SysExt);
			for (int j = 0; j < MAX_SYSFILE; j++) {
				if (Sys[j].Ext.CompareNoCase(SysExt) == 0) {
					Sys[j].StdDossierFlag = false; // om ook 'standaard-dossiers te kunnen sluiten !
					SysClose(j);
					break;
				}
			}
		}
		delete selIndex;
	}
}

void CDataBaseDlg::OnBnClickedBtnrefresh()
{

	m_lstDBAvailable.ResetContent();
	m_lstDBMounted.ResetContent();
	OnLbnSelchangeLstavailabledb();
	OnLbnSelchangeLstmounteddb();

	CFileFind finder;
	CString SysExt, FilePath;
	CString FindFileName = PathDB + "SYS.*";
	int file_ix;
	BOOL bWorking = finder.FindFile(FindFileName);
	while (bWorking) {
		bWorking = finder.FindNextFile();
		FilePath = finder.GetFilePath().MakeUpper();
		SysExt = FilePath.Right(3);
		for (file_ix = 0; file_ix < MAX_SYSFILE; file_ix++) {
			if (Sys[file_ix].Ext.CompareNoCase(SysExt) == 0) break;
		}
		char *SysBuf, TempBuf[MAX_SYS_LEN + 10];
		if (file_ix < MAX_SYSFILE) {   // file already open
			SysBuf = Sys[file_ix].Buf;
		}
		else {
			CFile SysFile;
			SysFile.Open(FilePath, CFile::modeRead, 0);
			SysFile.Read(TempBuf, MAX_SYS_LEN);
			SysFile.Close();
			SysBuf = TempBuf;
		}
		for (int i = 0; i < 15; i++) { // kijk of 1 van de 15 files ook effectief bestaat (om sys.fas te vermijden en gecopieerde systemen);
			char _FileName[20];
			memcpy(_FileName, SysBuf + 300 + i * 17, 15);
			_FileName[15] = 0;
			if (_FileName[0] > ' ') {
				CString _FilePath = PathDB + _FileName;
				if (GetFileAttributes(_FilePath) != INVALID_FILE_ATTRIBUTES) {
					if (SysBuf == TempBuf) m_lstDBAvailable.AddString(SysExt);
					else m_lstDBMounted.AddString(SysExt);
					break;
				}
			}
		}
	}
	finder.Close();
	if (m_lstDBMounted.GetCount() > 0) m_btnDump2Copy.EnableWindow(TRUE);
	else m_btnDump2Copy.EnableWindow(FALSE);
}

void CDataBaseDlg::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialog::OnShowWindow(bShow, nStatus);

	if (bShow == SW_HIDE) return;

	OnBnClickedBtnrefresh();
}

void RecursiveDelete(CString szPath);

BOOL CDataBaseDlg::OnInitDialog()
{
	SetTimer(TIMER10SEC, VALTIMER10SEC * 1000, NULL);
	CDialog::OnInitDialog();

	//CreateSnapShot("fas", 3600, false); 
	// find all *.DB files and add them to Available ListBox
	OnBnClickedBtnrefresh();

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

//void CDataBaseDlg::OnLbnSelchangeLstavailabledb()
//{
//	// TODO: Add your control notification handler code here
//}


// CUtilitysDlg dialog

IMPLEMENT_DYNAMIC(CUtilitysDlg, CDialog)

CUtilitysDlg::CUtilitysDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CUtilitysDlg::IDD, pParent)
{

}

CUtilitysDlg::~CUtilitysDlg()
{
}

void CUtilitysDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CBOSYSSELECT, m_cboSysSelect);
	DDX_Control(pDX, IDC_CBOUPSYSTYPE, m_cboSysValType);
	DDX_Control(pDX, IDC_EDITSYSPOS, m_edtSysPos);
	DDX_Control(pDX, IDC_EDITSYSVALUE, m_edtSysValue);
	DDX_Control(pDX, IDC_EDITSTRINGLEN, m_edtStringLen);
}


BEGIN_MESSAGE_MAP(CUtilitysDlg, CDialog)
	//	ON_WM_CREATE()
	//	ON_EN_CHANGE(IDC_EDITSYSVALUE, &CUtilitysDlg::OnEnChangeEditsysvalue)
	ON_CBN_SELCHANGE(IDC_CBOSYSSELECT, &CUtilitysDlg::OnCbnSelchangeCbosysselect)
	ON_CBN_SELCHANGE(IDC_CBOUPSYSTYPE, &CUtilitysDlg::OnCbnSelchangeCboupsystype)
	ON_EN_KILLFOCUS(IDC_EDITSYSPOS, &CUtilitysDlg::OnEnKillfocusEditsyspos)
	ON_BN_CLICKED(IDC_BTNSYSUPDATE, &CUtilitysDlg::OnBnClickedBtnsysupdate)
	ON_EN_KILLFOCUS(IDC_EDITSTRINGLEN, &CUtilitysDlg::OnEnKillfocusEditstringlen)
	//ON_EN_CHANGE(IDC_EDITSYSPOS, &CUtilitysDlg::OnEnChangeEditsyspos)
	ON_EN_SETFOCUS(IDC_EDITSYSVALUE, &CUtilitysDlg::OnEnSetfocusEditsysvalue)
	//ON_CBN_SETFOCUS(IDC_CBOSYSSELECT, &CUtilitysDlg::OnCbnSetfocusCbosysselect)
	ON_WM_SHOWWINDOW()
END_MESSAGE_MAP()


// CUtilitysDlg message handlers

//int CUtilitysDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
//{
//	if (CDialog::OnCreate(lpCreateStruct) == -1)
//		return -1;
//
//	// TODO:  Add your specialized creation code here
//
//	return 0;
//}


BOOL CUtilitysDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here

	memcpy(m_DataBaseName, "FAS", 4);
	m_cboSysSelect.SelectString(0, m_DataBaseName);
	m_cboSysValType.SetCurSel(0);
	m_edtSysPos.SetWindowText("1");
	m_edtStringLen.EnableWindow(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CUtilitysDlg::OnCbnSelchangeCbosysselect()
{
	// TODO: Add your control notification handler code here
	CString cstr;
	m_cboSysSelect.GetLBText(m_cboSysSelect.GetCurSel(), cstr);
	sprintf_s(m_DataBaseName, sizeof(m_DataBaseName), "%s", (char *)(LPCTSTR)cstr);
	UpdateSysValue();
}

void CUtilitysDlg::OnCbnSelchangeCboupsystype()
{
	// TODO: Add your control notification handler code here
	CString cstr;

	m_SysType = m_cboSysValType.GetCurSel();
	m_edtStringLen.EnableWindow(FALSE);
	switch (m_SysType) {
	case 0: m_SysLen = 1; break;
	case 1: m_SysLen = 2; break;
	case 2: m_SysLen = 2; break;
	case 3: m_SysLen = 4; break;
	case 4: m_SysLen = 4; break;
	case 5: m_SysLen = 8; break;
	case 6: m_SysLen = 2; break;
	case 7:
		m_SysLen = 0;
		m_edtStringLen.EnableWindow(TRUE);
		break;
	}
	char buf[10];
	sprintf_s(buf, sizeof(buf), "%d", m_SysLen);
	m_edtStringLen.SetWindowText(buf);
	UpdateSysValue();
}

void CUtilitysDlg::OnEnKillfocusEditsyspos()
{
	CString cstr;
	m_edtSysPos.GetWindowText(cstr);
	m_SysPos = atol(cstr);
	UpdateSysValue();
}

bool UpdateSysFileRead(char *DBName, int pos, int len, char *buf) { return false; }
bool UpdateSysFileWrite(char *DBName, int pos, int len, char *buf) { return false; }

void CUtilitysDlg::UpdateSysValue(bool ForceUpdate)
{
	char buf[1000], numbuf[20];
	CString cstr;
	int jj, mm, dd;

	if (m_SysLen >= sizeof(buf)) return;

	if (!ForceUpdate && m_Prev_SysPos == m_SysPos && m_Prev_SysLen == m_SysLen && memcmp(m_Prev_DataBaseName, m_DataBaseName, sizeof(m_DataBaseName)) == 0
		&& m_Prev_SysType == m_SysType) return;

	if (UpdateSysFileRead(m_DataBaseName, m_SysPos, m_SysLen, buf)) {
		memcpy(numbuf, buf, 8);
		switch (m_SysType) {
		case 0:
			sprintf_s(buf, sizeof(buf), "%d", numbuf[0]);
			break;
		case 1:
			sprintf_s(buf, sizeof(buf), "%d", *(short int *)numbuf);
			break;
		case 2:
			sprintf_s(buf, sizeof(buf), "%d", *(short unsigned *)numbuf);
			break;
		case 3:
			sprintf_s(buf, sizeof(buf), "%d", *(long *)numbuf);
			break;
		case 4:
			sprintf_s(buf, sizeof(buf), "%10.5f", *(float *)numbuf);
			break;
		case 5:
			sprintf_s(buf, sizeof(buf), "%10.5Lf", *(double *)numbuf);
			break;
		case 6:
			jddate(*(short unsigned *)numbuf, &jj, &mm, &dd);
			sprintf_s(buf, sizeof(buf), "%02d/%02d/%04d", dd, mm, jj);
			break;
		case 7:
			buf[m_SysLen] = 0;
			break;
		}
		m_edtSysValue.SetWindowText(buf);

		m_Prev_SysPos = m_SysPos;
		m_Prev_SysLen = m_SysLen;
		m_Prev_SysType = m_SysType;
		memcpy(m_Prev_DataBaseName, m_DataBaseName, sizeof(m_DataBaseName));
	}
}

void CUtilitysDlg::OnEnKillfocusEditstringlen()
{
	CString cstr;
	m_edtStringLen.GetWindowText(cstr);
	m_SysLen = atol(cstr);
	UpdateSysValue();
}

void CUtilitysDlg::OnEnSetfocusEditsysvalue()
{
	UpdateSysValue(true);
}

void CUtilitysDlg::OnOK()
{
	// CDialog::OnOK(); // wegdoen of <ENTER> closed de dialoge
	PostMessage(WM_NEXTDLGCTL, 0, 0L); // bij <ENTER> gaat hij nu naar volgende veld !
}

void CUtilitysDlg::OnBnClickedBtnsysupdate()
{
	CString cstr;
	m_edtSysValue.GetWindowText(cstr);
	UpdateSysfile(m_DataBaseName, m_SysType, m_SysPos, m_SysLen, (char *)(LPCTSTR)cstr);
}

bool CUtilitysDlg::UpdateSysfile(char* DataBaseName, int Type, int Pos, int Len, char* TextBuf)
{
	char buf[1000];
	int jj, mm, dd;

	if (Len < 0 || Len >= sizeof(buf)) return false;

	switch (Type) {
	case 0:
		*(unsigned char *)buf = atoi(TextBuf);
		break;
	case 1:
		*(short int *)buf = atoi(TextBuf);
		break;
	case 2:
		*(short unsigned *)buf = (short unsigned)atol(TextBuf);
		break;
	case 3:
		*(long *)buf = atol(TextBuf);
		break;
	case 4:
		*(float *)buf = (float)atof(TextBuf);
		break;
	case 5:
		*(double *)buf = atof(TextBuf);
		break;
	case 6:
		if (TextBuf[2] != '/' || TextBuf[5] != '/') return false;
		dd = atoi(&TextBuf[0]);
		mm = atoi(&TextBuf[3]);
		jj = atoi(&TextBuf[6]);
		*(unsigned short *)buf = datejd(jj, mm, dd);
		break;
	case 7:
		memcpy(buf, TextBuf, Len);
		break;
	}

	return UpdateSysFileWrite(DataBaseName, Pos, Len, buf);
}


void CUtilitysDlg::ExecCmdLine(CString CmdLine)
{
	if (GetSubString(CmdLine, 1).CompareNoCase("UPSYS") == 0) {
		CString SysName = GetSubString(CmdLine, 2);
		if (SysName.Left(4).CompareNoCase("SYS.") == 0) SysName = SysName.Mid(4);
		CString TypeChar = GetSubString(CmdLine, 3).Left(1);
		TypeChar.MakeUpper();
		CString TypesArr = "CIULFDJT";
		int Type = TypesArr.Find(TypeChar);
		if (Type < 0) return;
		int Pos = atoi(GetSubString(CmdLine, 4));
		int Len; CString Tekst;
		switch (Type) {
		case 0: Len = 1; Tekst = GetSubString(CmdLine, 5); break;
		case 1: Len = 2; Tekst = GetSubString(CmdLine, 5); break;
		case 2: Len = 2; Tekst = GetSubString(CmdLine, 5); break;
		case 3: Len = 4; Tekst = GetSubString(CmdLine, 5); break;
		case 4: Len = 4; Tekst = GetSubString(CmdLine, 5); break;
		case 5: Len = 8; Tekst = GetSubString(CmdLine, 5); break;
		case 6: Len = 2; Tekst = GetSubString(CmdLine, 5); break;
		case 7:
			Len = atoi(GetSubString(CmdLine, 5));
			Tekst = GetSubString(CmdLine, 6);
			break;
		}
		UpdateSysfile((char *)(LPCTSTR)SysName, Type, Pos, Len, (char *)(LPCTSTR)Tekst);
		return;
	}
}


void CUtilitysDlg::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialog::OnShowWindow(bShow, nStatus);

	if (bShow == SW_HIDE) return;

	bool SysFl = true;

	if (m_cboSysSelect.GetCurSel() >= 0) SysFl = false;

	if (SysFl) m_cboSysSelect.ResetContent();
	for (int i = 0; i < DB_MAX; i++) {
		CString DBName = DB[i].Name;
		if (DBName.GetLength()) {
			if (SysFl) m_cboSysSelect.AddString(DBName);
		}
	}
}

void CDataBaseDlg::OnLbnSelchangeLstmounteddb()
{
	if (m_lstDBMounted.GetSelCount() > 0) {
		m_btnCheck.EnableWindow(TRUE);
		m_btnExport2Fas.EnableWindow(TRUE);
		m_btnUnMount.EnableWindow(TRUE);
	}
	else {
		m_btnCheck.EnableWindow(TRUE); // was FALSE
		m_btnExport2Fas.EnableWindow(FALSE);
		m_btnUnMount.EnableWindow(FALSE);
	}
}


void CDataBaseDlg::OnLbnSelchangeLstavailabledb()
{
	if (m_lstDBAvailable.GetSelCount() > 0) {
		m_btnMount.EnableWindow(TRUE);
	}
	else {
		m_btnMount.EnableWindow(FALSE);
	}
}

void CDataBaseDlg::OnCbnSelchangeAutoziptime()
{
	// TODO: Add your control notification handler code here
}

// Manage the BAK-files

#define  BAK_WAKEUP_INTERVAL            10   // Wanneer er tijdens een volledig interval geen update gebeurde, dan worden de gewijzigde databases overlopen en de geupdate records gedumpt
#define  BAK_PERIODIC_CHECK_INTERVAL  3600   // om de 60 minuten alle bestanden controleren ... bak, sys, fsd ... Uiteraard enkel voor de Mounted DB's !
											 // bovenstaand getal wordt ook met factor / 2 gebruikt, moet moet dus minstens viervoud van wak_wakeup_interval zijn
#define  BAK_PERIODIC_REMOVE_SNAPSHOTS  60   // om de minuut nakijken om overdue snapshots te verwijderen ...
#define  BAK_INACTIVE_SHADOW_CHECK_INTERVAL    10   // Moet veelvoud van BAK_WAKEUP_INTERVAL zijn, maar bij voorkeur hetzelfde ...
#define  BAK_INACTIVE_ONLINE_CHECK_INTERVAL   600   // 10 minuten inactiviteit Moet veelvoud van BAK_WAKEUP_INTERVAL zijn
#define  BAK_INACTIVE_WRITE_STATS      300  // na 5 minuten inactiviteit de statististiek in de file schrijven ...
#define  BAK_FIRST_RUN_TIME            -120   // Deze parameter op + zetten om te testen, anders wordt de online backup te snel gemaakt !
#define  BAK_DAILY_BACKUP_INTERVAL     600   // na (of om de) 10 minuten inactiviteit proberen om handtekeningen te maken ... zo bit DailyBackupRequested aan staat ! (via Jama360 gestuurd !)

int BakSecondsInactive = BAK_DAILY_BACKUP_INTERVAL - 180; // om na 3 minuten de DailyBackup te proberen ! BAK_INACTIVE_SHADOW_CHECK_INTERVAL; // om niet onmiddellijk al een dump te maken !
int BakSecondsRunning = 0;
bool PrevPathCopyErrorFlag = false;
bool BakPeriodicFlag = false;

CString BakFilePath;
CFile BakFile;
ULONGLONG BakFileLength;
// Volgende structs komen ook terug in de Dmp2Copy
unsigned char BakHeader[512];
struct s_BakHdr {
	unsigned char Type;
	char Version;
	double DateTimeLastUpdated;
	short int RecBakLen;
	long RecPos;
	long RecCount; // is eigenlijk het max. aantal gebruikte records in deze file
	FILETIME LastFileUpdateTime;
	unsigned char OrigDBName[48];
	long RecUsed;  // het echt aantal gebruikte records in deze file (wordt geteld)
} *BakHdr = (struct s_BakHdr *) BakHeader;
int BakUpdCount, BakDelCount, FilWrtCount;
UNALIGNED struct s_RecDump {   // indien deze structuur aangepast wordt, het ook verder aanpassen in de RecLen ...
	unsigned char Used;
	double DateTimeUpdated;
	short int ChangedBy;
	unsigned char RecBuf[BUF_LEN + 40];
} RecDump, RecComp;
char BakFileCmpBuf[MAX_SYS_LEN + 10]; // moet de max. grootte van de FSD en sys.* bestanden zijn, wordt gecontroleerd bij het inlezen ...

bool CreateSubDirNested(CString Path)   // moet op \ eindigen ....
{
	int i;

	if (Path.Right(1) != "\\") Path += "\\";

	i = Path.Find("\\");
	if (Path.GetAt(1) == ':' && i == 2) i = Path.Find("\\", i + 1);
	else if (Path.Left(2) == "\\\\") {
		// bv. \\server\share\subdir\subdir ...
		i = Path.Find("\\", 2);
		if (i > 0) i = Path.Find("\\", i + 1);
		if (i > 0) i = Path.Find("\\", i + 1);
	}
	while (i > 0) {
		if (GetFileAttributes(Path.Left(i)) == INVALID_FILE_ATTRIBUTES) { // directory bestaat niet ...
			if (_mkdir(Path.Left(i))) return false; // maak hem bij ... en zo het niet lukt, return false
		}
		i = Path.Find("\\", i + 1);
	}
	return true;
}

CString PathCopy()
{
	bool PathCopyErrorFlag = true;
	CString PathCopy = theApp.iniFile.getKeyValue("CopyPath", "CopySettings");
	CString PathCopyFas;
	if (PathCopy.GetLength() <= 1) goto error;

	if (PathCopy.Right(1) != "\\") PathCopy += "\\";
	PathCopyFas = PathCopy + "FAS";
	DWORD dwAttrib = GetFileAttributes(PathCopyFas);
	if (dwAttrib != INVALID_FILE_ATTRIBUTES) PathCopyErrorFlag = false;
	else {
		CreateSubDirNested(PathCopyFas);
		dwAttrib = GetFileAttributes(PathCopyFas);
		if (dwAttrib != INVALID_FILE_ATTRIBUTES) PathCopyErrorFlag = false;
	}
	if (PathCopyErrorFlag == false) { // controleren of we kunnen schrijven op stick !
		CString TestFileName = PathCopyFas + "\\jmswrite.tst";
		HANDLE hWrite = CreateFile(TestFileName, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);
		if (hWrite != INVALID_HANDLE_VALUE) {
			DWORD dwWrite;
			BOOL fWrite = WriteFile(hWrite, "jmswrite-test", 13, &dwWrite, 0);
			if (dwWrite != 13 || fWrite != TRUE) PathCopyErrorFlag = true;
			CloseHandle(hWrite);
		}
		else PathCopyErrorFlag = true;
		if (PathCopyErrorFlag && !PrevPathCopyErrorFlag) {
			LogAdd(115, 0, "Path for Copy-SubDir is not writeable", PathCopy);
		}
		_unlink(TestFileName);
	}
	if (PathCopyErrorFlag == false) {
		if (PrevPathCopyErrorFlag) {
			LogAdd(72, 0, "Path for Copy-SubDir is RESTORED", PathCopy);
			BakPeriodicFlag = true;
		}
		CString PathCopyAltFas = PathCopyAlt + "FAS";
		if (GetFileAttributes(PathCopyAltFas) != INVALID_FILE_ATTRIBUTES) { // wis copy.alt\fas subdir, is niet meer nodig !
		  //Schrap eerst ongebruikte files in de \fas subdir staan ...
			PathCopyAltFas += "\\";
			CFileFind FasDir;
			CString File2Find = PathCopyAltFas + "*.*";
			BOOL bWorking = FasDir.FindFile(File2Find);
			while (bWorking) {
				bWorking = FasDir.FindNextFile();
				if (FasDir.IsDirectory()) continue;
				_unlink(FasDir.GetFilePath());
			}
			FasDir.Close();
			RemoveDirectory(PathCopyAltFas);
		}
		PrevPathCopyErrorFlag = false;
		return PathCopy;
	}

error:;
	if (!PrevPathCopyErrorFlag) {
		CString cstr;
		cstr.Format("%s (dwAttrib=%X)", PathCopy, dwAttrib);
		LogAdd(46, 0, "Path for Copy-SubDir is not available", cstr);
		BakPeriodicFlag = true;
	}
	PrevPathCopyErrorFlag = true;

	// switch to COPY - ALT
	PathCopy = PathCopyAlt;
	PathCopyFas = PathCopy + "FAS\\";
	CreateDirectory(PathCopyFas, NULL);
	return PathCopy;

	return "";
}

bool AdjustLenBakFile(ULONGLONG Length)
{
	bool ret = true;

	if (Length > BakFileLength) {
		BakFile.Seek(0, CFile::end);
		char* dumbuf = new char[10 + 1024 * 16];
		memset(dumbuf, 0, 1024 * 16);
		try {
			for (int cnt = 0; cnt < 64; cnt++) {
				BakFile.Write(dumbuf, 1024 * 16);
			}
		}
		catch (...) {
			ret = false;
			LogAdd(116, 0, "Shadowdisk Full?? Cannot extend BAK-file", BakFilePath);
		}
		BakFileLength = BakFile.GetLength();
		delete[] dumbuf;
	}
	return ret;
}

void UpdateBakFile(int DBRef, int TabIx)
{
	int RecNr;
	JET_ERR _jeterr;
	unsigned long retlen;
	unsigned char *p;

	CString Path = PathCopy();
	if (Path == "") return;
	BakFilePath.Format("%sFAS\\%s.%03d.BAK", Path, DB[DBRef].Name, DB[DBRef].Tab[TabIx].StuNr);
redo:;
	if (!BakFile.Open(BakFilePath, CFile::shareDenyWrite | CFile::modeReadWrite, NULL)) {
		if (!BakFile.Open(BakFilePath, CFile::modeCreate | CFile::shareDenyWrite | CFile::modeReadWrite, NULL)) {
			LogAdd(42, 0, "Cannot create Backup-file", BakFilePath);
			return;
		}
		BakFileLength = 0;
		if (!AdjustLenBakFile(sizeof(BakHeader))) goto JetErrorRet;
		// fill in header
		memset(BakHeader, 0x00, sizeof(BakHeader));
		BakHdr->Type = 0xFE; // fas export
		BakHdr->Version = 01;
		BakHdr->RecPos = sizeof(BakHeader);
		BakHdr->RecBakLen = DB[DBRef].Tab[TabIx].StructLen - DB[DBRef].Tab[TabIx].EleInf[1].FldLen + 11;   // zie hoger in Struct RecDump
		BakHdr->DateTimeLastUpdated = -1.; // dag -1 (in jaar 1899). Om volledige update te forceren
		sprintf_s((char *)BakHdr->OrigDBName, sizeof(BakHdr[0].OrigDBName) - 1, "%s", DB[DBRef].Name);
		BakFile.Seek(0L, 0);
		BakFile.Write(BakHeader, sizeof(BakHeader));
	}
	else {
		BakFile.Seek(0L, 0);
		BakFile.Read(BakHeader, sizeof(BakHeader));
		bool DeleteThisBak = false;

		if (BakHdr->Type != 0xFE) DeleteThisBak = true;
		if (BakHdr->Version != 01) DeleteThisBak = true;
		if (BakHdr->RecPos != sizeof(BakHeader)) DeleteThisBak = true;
		if (BakHdr->RecBakLen != (DB[DBRef].Tab[TabIx].StructLen - DB[DBRef].Tab[TabIx].EleInf[1].FldLen + 11)) DeleteThisBak = true;
		if (_strcmpi((const char *)BakHdr->OrigDBName, DB[DBRef].Name) != 0) DeleteThisBak = true;

		if (DeleteThisBak) {
			BakFile.Close();
			_unlink(BakFilePath);
			goto redo;
		}
	}
	BakFileLength = BakFile.GetLength();
	double NewDateTime = COleDateTime::GetCurrentTime().operator double();

	double SpilDateTime = BakHdr->DateTimeLastUpdated;
	// find recs that are updated after SpilDateTime
	RecNr = 1; RecDump.Used = 1;
	JetCallJmpJetErrorRet(3101, JetSetCurrentIndex4(DB[DBRef].SesId[0], DB[DBRef].Tab[TabIx].Tid[0], "", (JET_INDEXID*)DB[DBRef].Tab[TabIx].Idx[StuDatIx].rgbIndexId[0], 0, 0));
	JetCallJmpJetErrorRet(3102, JetMakeKey(DB[DBRef].SesId[0], DB[DBRef].Tab[TabIx].Tid[0], &SpilDateTime, DB[DBRef].Tab[TabIx].Col[StuDatId].Len, JET_bitNewKey));
	JetCallJmpJetErrorRet(3110, JetMakeKey(DB[DBRef].SesId[0], DB[DBRef].Tab[TabIx].Tid[0], &RecNr, sizeof(RecNr), 0));
	_jeterr = JetSeek(DB[DBRef].SesId[0], DB[DBRef].Tab[TabIx].Tid[0], JET_bitSeekGE);
	while (_jeterr == JET_wrnSeekNotEqual || _jeterr == JET_errSuccess) {
		if (JMSShuttingDown) break;
		JetCallJmpJetErrorRet(3103, JetRetrieveColumn(DB[DBRef].SesId[0], DB[DBRef].Tab[TabIx].Tid[0], DB[DBRef].Tab[TabIx].Col[StuRecId].Cid[0], &RecNr, DB[DBRef].Tab[TabIx].Col[StuRecId].Len, &retlen, 0, 0));
		JetCallJmpJetErrorRet(3104, JetRetrieveColumn(DB[DBRef].SesId[0], DB[DBRef].Tab[TabIx].Tid[0], DB[DBRef].Tab[TabIx].Col[StuChgId].Cid[0], &RecDump.ChangedBy, DB[DBRef].Tab[TabIx].Col[StuChgId].Len, &retlen, 0, 0));
		JetCallJmpJetErrorRet(3104, JetRetrieveColumn(DB[DBRef].SesId[0], DB[DBRef].Tab[TabIx].Tid[0], DB[DBRef].Tab[TabIx].Col[StuDatId].Cid[0], &RecDump.DateTimeUpdated, DB[DBRef].Tab[TabIx].Col[StuDatId].Len, &retlen, 0, 0));
		JetCallJmpJetErrorRet(3104, JetRetrieveColumn(DB[DBRef].SesId[0], DB[DBRef].Tab[TabIx].Tid[0], DB[DBRef].Tab[TabIx].Col[StuValId].Cid[0], RecDump.RecBuf, BUF_LEN, &retlen, 0, 0));
		if (retlen != BakHdr->RecBakLen - 11) {
			CString cstr;
			cstr.Format("Read in StuNr=%d at RecNr=%d returned %d bytes. But in BackupFile the RecBakLen is %d bytes.", DB[DBRef].Tab[TabIx].StuNr, RecNr, retlen, BakHdr->RecBakLen - 11);
			LogAdd(0, 0, cstr);
		}
		p = RecDump.RecBuf;

		while (retlen--) *p++ = (*p >> 4) | (*p << 4);
		ULONGLONG WritePos = BakHdr->RecPos + BakHdr->RecBakLen*(RecNr - 1);
		if (!AdjustLenBakFile(WritePos)) goto JetErrorRet;
		BakFile.Seek(WritePos, CFile::begin);
		BakFile.Write(&RecDump, BakHdr->RecBakLen); BakUpdCount++;
		if (RecNr > BakHdr->RecCount) BakHdr->RecCount = RecNr;

		_jeterr = JetMove(DB[DBRef].SesId[0], DB[DBRef].Tab[TabIx].Tid[0], JET_MoveNext, 0);
	}

	// find recs that are deleted after SpilDateTime
	RecNr = 1; RecDump.Used = 0; memset(RecDump.RecBuf, 0, BUF_LEN);
	JetCallJmpJetErrorRet(3125, JetSetCurrentIndex4(DB[DBRef].SesId[0], DB[DBRef].Tab[DelId].Tid[0], "", (JET_INDEXID*)DB[DBRef].Tab[DelId].Idx[DelDatIx].rgbIndexId[0], 0, 0));
	JetCallJmpJetErrorRet(3126, JetMakeKey(DB[DBRef].SesId[0], DB[DBRef].Tab[DelId].Tid[0], &DB[DBRef].Tab[TabIx].StuNr, DB[DBRef].Tab[DelId].Col[DelStuId].Len, JET_bitNewKey));
	JetCallJmpJetErrorRet(3124, JetMakeKey(DB[DBRef].SesId[0], DB[DBRef].Tab[DelId].Tid[0], &SpilDateTime, DB[DBRef].Tab[DelId].Col[DelDatId].Len, 0));
	JetCallJmpJetErrorRet(3127, JetMakeKey(DB[DBRef].SesId[0], DB[DBRef].Tab[DelId].Tid[0], &RecNr, DB[DBRef].Tab[DelId].Col[DelRecId].Len, 0));
	_jeterr = JetSeek(DB[DBRef].SesId[0], DB[DBRef].Tab[DelId].Tid[0], JET_bitSeekGE);
	while (_jeterr == JET_wrnSeekNotEqual || _jeterr == JET_errSuccess) {
		if (JMSShuttingDown) break;
		unsigned long retreclen = 0;
		short int StuNrFound;
		JetCallJmpJetErrorRet(3128, JetRetrieveColumn(DB[DBRef].SesId[0], DB[DBRef].Tab[DelId].Tid[0], DB[DBRef].Tab[DelId].Col[DelStuId].Cid[0], &StuNrFound, DB[DBRef].Tab[DelId].Col[DelStuId].Len, &retreclen, 0, 0));
		if (StuNrFound != DB[DBRef].Tab[TabIx].StuNr) break;
		RecDump.ChangedBy = 0;
		JetCallJmpJetErrorRet(3129, JetRetrieveColumn(DB[DBRef].SesId[0], DB[DBRef].Tab[DelId].Tid[0], DB[DBRef].Tab[DelId].Col[DelRecId].Cid[0], &RecNr, DB[DBRef].Tab[DelId].Col[DelRecId].Len, &retreclen, 0, 0));
		JetCallJmpJetErrorRet(3131, JetRetrieveColumn(DB[DBRef].SesId[0], DB[DBRef].Tab[DelId].Tid[0], DB[DBRef].Tab[DelId].Col[DelChgId].Cid[0], &RecDump.ChangedBy, DB[DBRef].Tab[DelId].Col[DelChgId].Len, &retlen, 0, 0));
		JetCallJmpJetErrorRet(3132, JetRetrieveColumn(DB[DBRef].SesId[0], DB[DBRef].Tab[DelId].Tid[0], DB[DBRef].Tab[DelId].Col[DelDatId].Cid[0], &RecDump.DateTimeUpdated, DB[DBRef].Tab[DelId].Col[DelDatId].Len, &retlen, 0, 0));

		ULONGLONG WritePos = BakHdr->RecPos + BakHdr->RecBakLen*(RecNr - 1);
		if (!AdjustLenBakFile(WritePos)) goto JetErrorRet;
		BakFile.Seek(WritePos, CFile::begin);
		BakFile.Write(&RecDump, BakHdr->RecBakLen); BakDelCount++;
		if (RecNr > BakHdr->RecCount) BakHdr->RecCount = RecNr;

		_jeterr = JetMove(DB[DBRef].SesId[0], DB[DBRef].Tab[DelId].Tid[0], JET_MoveNext, 0);
	}

	// update header of BAK-file
	if (!JMSShuttingDown) {
		BakFile.Seek(0L, 0);
		BakHdr->DateTimeLastUpdated = NewDateTime;  // alleen vervangen wanneer alles goed verlopen is !
		BakFile.Write(BakHeader, sizeof(BakHeader));
	}
	SetFileLastWriteTimeFromDB(BakFile.m_hFile, DBRef);
JetErrorRet:;
	try {
		if (BakFile.m_hFile != CFile::hFileNull) BakFile.Close();
	}
	catch (...) {}
}

bool MakeAndCompareSignatureFromSysFile(char *SysName, unsigned char *Sha1Source)  // deze routine zit ook in DMP2COPY !
{
	CFile SysFil;
	bool ret = false;

	if (!SysFil.Open(SysName, CFile::shareDenyWrite | CFile::modeReadWrite, NULL)) {
		// LogAdd(94,0,"Cannot open SysBackup-file",SysName); Moet hier geen error geven, kan immers vaak voorkomen wanneer SYS nog niet in shadowcopy zit !
		return ret;
	}

	char* SysBuf = new char[(int)SysFil.GetLength() + 10];
	SysFil.Read(SysBuf, (int)SysFil.GetLength());
	sha1_context ctx;
	sha1_starts(&ctx);
	sha1_update(&ctx, (const unsigned char *)SysBuf, (int)SysFil.GetLength());
	SysFil.Close();
	delete SysBuf;
	// close SHA algrorithm en schrijf SHA file uit !
	unsigned char sha1[30];
	memset(sha1, 0, 30);
	sha1_finish(&ctx, sha1);
	CString LogLine, cstr;
	cstr = SysName;
	LogLine.Format("Signature [SYS.%s]     : ", cstr.Right(3).MakeUpper());
	CString SignatureFile;
	SignatureFile.Format("%s.BAK.SHA", SysName);
	CFile Sig;
	if (Sig.Open(SignatureFile, CFile::modeCreate | CFile::modeWrite, NULL)) {
		CString cstr, sigstr;
		sigstr.Format("SHA1=");
		for (int i = 0; i < 20; i++) {
			cstr.Format("%02X", sha1[i]);
			sigstr += cstr;
			LogLine += cstr;
		}
		sigstr += "\r\n";
		Sig.Write(sigstr, sigstr.GetLength());
		Sig.Close();
	}
	LogAdd(0, 1, LogLine);

	if (memcmp(Sha1Source, sha1, 30) == 0) ret = true;
	return ret;
}

bool MakeSignatureFromBAK(char *BAKName)  // deze routine zit ook in DMP2COPY !
{
	unsigned long retlen;
	bool Succeeded = true;
	unsigned char *p;
	bool BakErr = false;
	CString LogLine, cstr;

	if (!BakFile.Open(BAKName, CFile::shareDenyWrite | CFile::modeReadWrite, NULL)) {
		BakErr = true;
		LogAdd(50, 0, "Cannot open Backup-file", BakFilePath);
		return false;
	}

	BakFile.Seek(0L, 0);
	BakFile.Read(BakHeader, sizeof(BakHeader));
	bool BadBak = false;
	if (BakHdr->Type != 0xFE) BadBak = true;
	if (BakHdr->Version != 01) BadBak = true;
	if (BakHdr->RecPos != sizeof(BakHeader)) BadBak = true;
	//if (BakHdr->RecBakLen!=(RecLen+11)) BadBak=true; 

	sha1_context ctx;
	sha1_starts(&ctx);

	int RecNr = 1, DeletedCount = 0, RecCount = 0, LastRecUsed = 0;

	while (RecNr <= BakHdr->RecCount) {
		if (JMSShuttingDown) break;
		int rLen = BakFile.Read(&RecDump, BakHdr->RecBakLen);
		if (rLen < BakHdr->RecBakLen) {
			LogAdd(50, 0, "BakFile too short (incomplete record read)", BakFilePath);
			BakErr = false;
			break;
		}
		if (RecDump.Used) {
			LastRecUsed = RecNr;
			p = RecDump.RecBuf; retlen = rLen - sizeof(RecDump.Used) - sizeof(RecDump.DateTimeUpdated) - sizeof(RecDump.ChangedBy);
			while (retlen--) *p++ = (*p >> 4) | (*p << 4);

			sha1_update(&ctx, (const unsigned char *)&RecNr, sizeof(RecNr));
			sha1_update(&ctx, (const unsigned char *)&RecDump.DateTimeUpdated, rLen - 1);
			RecCount++;
		}
		else {
			DeletedCount++;
		}
		RecNr++;
	}
	BakFile.Close();

	if (RecNr > LastRecUsed) {
		DeletedCount -= (RecNr - LastRecUsed);
		RecNr = LastRecUsed;
	}
	if (JMSShuttingDown) return false;

	unsigned char sha1[30];
	memset(sha1, 0, 30);
	sha1_finish(&ctx, sha1);

	CFile Sig;
	CString SignatureFile = BAKName;
	SignatureFile += ".SHA";
	int k = SignatureFile.ReverseFind('\\');
	if (k >= 0) cstr = SignatureFile.Mid(k + 1);
	else cstr = SignatureFile;
	LogLine.Format("Signature [%s] : ", cstr.Left(cstr.GetLength() - 4));
	if (Sig.Open(SignatureFile, CFile::modeCreate | CFile::modeWrite, NULL)) {
		CString sigstr;
		sigstr.Format("SHA1=");
		for (int i = 0; i < 20; i++) {
			cstr.Format("%02X", sha1[i]);
			sigstr += cstr;
			LogLine += cstr;
		}
		sigstr += "\r\n";
		cstr.Format("RecordCount=%d\r\n", RecCount);
		sigstr += cstr;
		cstr.Format("RecLastUsed=%d\r\n", LastRecUsed);
		sigstr += cstr;
		Sig.Write(sigstr, sigstr.GetLength());
		Sig.Close();

		cstr.Format(" (Cnt=%d/Lst=%d)", RecCount, LastRecUsed);
		LogLine += cstr;
		LogAdd(0, 1, LogLine);
	}
	else Succeeded = false;

	return Succeeded;
}

bool CompareFasFromRestore(char *FasFileName) // om de bak files te comparen (zien of alles OK is !)
{
	unsigned long retlen;
	unsigned char *p;
	bool Identical = true;
	bool BakErr = false;

	int DBRef = FindDB(FasFileName);
	if (DBRef < 0) return false;

	CString PathRestore = PathJamaRoot + "RESTORE\\";
	for (int TabIx = 0; TabIx < DB[DBRef].TabCnt; TabIx++) {
		if (DB[DBRef].Tab[TabIx].StuNr == 0) continue;

		CFile BakFile;
		CString BakFilePath;
		BakFilePath.Format("%s%s.%03d.BAK", PathRestore, FasFileName, DB[DBRef].Tab[TabIx].StuNr);
		if (!BakFile.Open(BakFilePath, CFile::shareDenyWrite | CFile::modeReadWrite, NULL)) {
			BakErr = true;
			LogAdd(50, 0, "Cannot open Backup-file", BakFilePath);
			continue;
		}

		BakFile.Seek(0L, 0);
		BakFile.Read(BakHeader, sizeof(BakHeader));
		bool BadBak = false;
		if (BakHdr->Type != 0xFE) BadBak = true;
		if (BakHdr->Version != 01) BadBak = true;
		if (BakHdr->RecPos != sizeof(BakHeader)) BadBak = true;
		int RecLen = DB[DBRef].Tab[TabIx].StructLen - DB[DBRef].Tab[TabIx].EleInf[1].FldLen;
		if (BakHdr->RecBakLen != (RecLen + 11)) BadBak = true;
		if (_strcmpi((const char *)BakHdr->OrigDBName, DB[DBRef].Name) != 0) BadBak = true;

		if (BadBak) {
			BakFile.Close();
			BakErr = true;
			continue;
		}

		int RecCompLen;
		int RecNr = 1;
		int RecUsed = 0;
		int StuNr = DB[DBRef].Tab[TabIx].StuNr;
		while (RecNr <= BakHdr->RecCount) {
			int rLen = BakFile.Read(&RecDump, BakHdr->RecBakLen);
			if (rLen < BakHdr->RecBakLen) {
				LogAdd(50, 0, "BakFile too short (incomplete record read)", BakFilePath);
				BakErr = false;
				break;
			}
			if (RecDump.Used) {
				p = RecDump.RecBuf; retlen = RecLen;
				while (retlen--) *p++ = (*p >> 4) | (*p << 4);
				if (!EDBGetRec(DBRef, StuNr, RecNr, &RecCompLen, RecComp.RecBuf, &RecComp.DateTimeUpdated, &RecComp.ChangedBy)) {
					CString cstr;
					cstr.Format("DB=%s Stu=%03d RecNr=%07d : Record was deleted DB but was exists in BAK !", DB[DBRef].Name, StuNr, RecNr);
					LogAdd(0, 0, cstr);
					Identical = false;
				}
				else if (RecCompLen != RecLen) {
					CString cstr;
					cstr.Format("DB=%s Stu=%03d RecNr=%07d : RecLen differs. In BAK=%d and in DB=%d", DB[DBRef].Name, StuNr, RecNr, RecLen, RecCompLen);
					LogAdd(0, 0, cstr);
					Identical = false;
				}
				else {
					if (memcmp(RecComp.RecBuf, RecDump.RecBuf, RecLen) != 0) {
						CString cstr;
						cstr.Format("DB=%s Stu=%03d RecNr=%07d : Record differs !", DB[DBRef].Name, StuNr, RecNr);
						LogAdd(0, 0, cstr);
						Identical = false;
					}
					else if (RecComp.DateTimeUpdated != RecDump.DateTimeUpdated) {
						CString cstr;
						cstr.Format("DB=%s Stu=%03d RecNr=%07d : DateTimeUpdated differs !", DB[DBRef].Name, StuNr, RecNr);
						LogAdd(0, 0, cstr);
						Identical = false;
					}
					else if (RecComp.ChangedBy != RecDump.ChangedBy) {
						CString cstr;
						cstr.Format("DB=%s Stu=%03d RecNr=%07d : ChangedBy differs !", DB[DBRef].Name, StuNr, RecNr);
						LogAdd(0, 0, cstr);
						Identical = false;
					}
				}
				RecUsed++;
			}
			else {
				if (EDBGetRec(DBRef, StuNr, RecNr, &RecCompLen, RecComp.RecBuf, &RecComp.DateTimeUpdated, &RecComp.ChangedBy)) {
					CString cstr;
					cstr.Format("DB=%s Stu=%03d RecNr=%07d : Record exists in DB but was deleted in BAK !", DB[DBRef].Name, StuNr, RecNr);
					LogAdd(0, 0, cstr);
					Identical = false;
				}
			}
			RecNr++;
		}
		BakFile.Close();
		if (DB[DBRef].Tab[TabIx].UsedRec != RecUsed) {
			CString cstr;
			cstr.Format("  Used recs in BAK=%d  but in DB we found=%d", RecUsed, DB[DBRef].Tab[TabIx].UsedRec);
			LogAdd(0, 0, cstr);
		}
	}

	return Identical;
}

void WriteSysBakFile(int file_ix);

void CheckAllShaFileInRestore()
{
	CFileFind DBfinder;


	// nu comparen of alle SHA files hetzelfde zijn, overloop daarom de SHA files van de 'databases' bij de klant
	CString LogLine;
	CFile ShaLog;
	CString ShaLogFileName = PathJamaRoot + "..\\" + strJama360SerialNr.Mid(3, 3).MakeUpper() + "-Log.txt";
	ShaLog.Open(ShaLogFileName, CFile::modeCreate | CFile::modeWrite, NULL);
	bool BakFilesIdentical = true;
	char ShaBuf[1000], Jama360Buf[1000];
	CString File2Find = PathJamaRoot + "Restore\\*.SHA";
	BOOL bDBWorking = DBfinder.FindFile(File2Find);
	while (bDBWorking) {
		bDBWorking = DBfinder.FindNextFile();
		if (DBfinder.IsDirectory()) continue;

		if (DBfinder.GetFileName().Left(3).CompareNoCase("sys") == 0) {
			if (DBfinder.GetFileName().GetLength() != 19) continue; // enkel triggeren op SYS.FAS.BAK.360.SHA // zou later terug op 11 mogen komen (om van sys.fas.sha te vertrekken !)
			// deze bestaat niet voor oudere JMS versie (1.2.0.6 en vroeger)
			CString Sha360FileName = DBfinder.GetFilePath();
			CString ShaFileName = PathDB + "Sha\\" + DBfinder.GetFileName().Mid(0, 8) + "SHA";
			CFile Sha, Sha360;
			bool ShaDiffers = false;
			if (Sha.Open(ShaFileName, CFile::modeRead, NULL)) {
				if (Sha360.Open(Sha360FileName, CFile::modeRead, NULL)) {
					// Compare de 2 files die alle 2 dus moeten bestaan !
					if (Sha.GetLength() != Sha360.GetLength()) ShaDiffers = true;
					else {
						int len = (int)Sha.GetLength();
						if (len > 990) ShaDiffers = true;
						else {
							Sha.Read(ShaBuf, 990);
							ShaBuf[len] = 0;
							int i = ShaFileName.ReverseFind('\\');
							if (i < 0) i = 0;
							else i++;
							LogLine.Format("%sSHA     [DVD]%36s%s", DBfinder.GetFileName().Left(8).MakeUpper(), "", ShaBuf);
							ShaLog.Write(LogLine, LogLine.GetLength());
							Sha360.Read(Jama360Buf, 990);
							Jama360Buf[len] = 0;
							LogLine.Format("%sSHA     [ORI]%36s%s\r\n", DBfinder.GetFileName().Left(8).MakeUpper(), "", Jama360Buf);
							ShaLog.Write(LogLine, LogLine.GetLength());
							if (strcmp(ShaBuf, Jama360Buf) != 0) ShaDiffers = true;
						}
					}
					Sha360.Close();
				}
				else ShaDiffers = true;
				Sha.Close();
			}
			else ShaDiffers = true;
			if (ShaDiffers) {
				LogLine.Format("%s differs from 360 version\r\n", ShaFileName);
				ShaLog.Write(LogLine, LogLine.GetLength());
				CFile DifFile;
				CString ErrorFileName = PathJamaRoot + "..\\" + strJama360SerialNr.Mid(3, 3).MakeUpper() + "-Error.txt";
				DifFile.Open(ErrorFileName, CFile::modeCreate | CFile::modeWrite, NULL);
				DifFile.Write(LogLine, LogLine.GetLength());
				DifFile.Close();
				BakFilesIdentical = false;
			}
			continue;
		}

		if (DBfinder.GetFileName().GetLength() != 15) continue; // enkel SHA files van de FAS (bv. ART.FAS.006.SHA)
		CString Sha360FileName = DBfinder.GetFilePath();
		CString ShaFileName = PathDB + "Sha\\" + DBfinder.GetFileName().Mid(0, 12) + "SHA";
		CFile Sha, Sha360;
		bool ShaDiffers = false;
		if (Sha.Open(ShaFileName, CFile::modeRead, NULL)) {
			if (Sha360.Open(Sha360FileName, CFile::modeRead, NULL)) {
				// Compare de 2 files die alle 2 dus moeten bestaan !
				if (Sha.GetLength() != Sha360.GetLength()) ShaDiffers = true;
				else {
					int len = (int)Sha.GetLength();
					if (len > 990) ShaDiffers = true;
					else {
						Sha.Read(ShaBuf, 990);
						ShaBuf[len] = 0;
						if (ShaLog.m_hFile != CFile::hFileNull) {
							CString ShaStruct = DBfinder.GetFileTitle();
							CString ShaReccnt, ShaRecLast, ShaResult;
							CString Sha = ShaBuf;
							int i = Sha.Find("RecordCount=");
							if (i >= 0) {
								int j = Sha.Find("\r", i);
								if (j >= 0) ShaReccnt = Sha.Mid(i + 12, j - (i + 12));
							}
							i = Sha.Find("RecLastUsed=");
							if (i >= 0) {
								int j = Sha.Find("\r", i);
								if (j >= 0) ShaRecLast = Sha.Mid(i + 12, j - (i + 12));
							}
							i = Sha.Find("SHA1=");
							if (i >= 0) {
								int j = Sha.Find("\r", i);
								if (j >= 0) ShaResult = Sha.Mid(i + 5, j - (i + 5));
							}
							LogLine.Format("%s.FAS [DVD]  RecCnt=%-10sRecLst=%-10sSha1=%s\r\n", ShaStruct, ShaReccnt, ShaRecLast, ShaResult);
							ShaLog.Write(LogLine, LogLine.GetLength());
						}
						Sha360.Read(Jama360Buf, 990);
						Jama360Buf[len] = 0;
						if (ShaLog.m_hFile != CFile::hFileNull) {
							CString ShaStruct = DBfinder.GetFileTitle();
							CString ShaReccnt, ShaRecLast, ShaResult;
							CString Sha = Jama360Buf;
							int i = Sha.Find("RecordCount=");
							if (i >= 0) {
								int j = Sha.Find("\r", i);
								if (j >= 0) ShaReccnt = Sha.Mid(i + 12, j - (i + 12));
							}
							i = Sha.Find("RecLastUsed=");
							if (i >= 0) {
								int j = Sha.Find("\r", i);
								if (j >= 0) ShaRecLast = Sha.Mid(i + 12, j - (i + 12));
							}
							i = Sha.Find("SHA1=");
							if (i >= 0) {
								int j = Sha.Find("\r", i);
								if (j >= 0) ShaResult = Sha.Mid(i + 5, j - (i + 5));
							}
							LogLine.Format("%s.FAS [ORI]  RecCnt=%-10sRecLst=%-10sSha1=%s\r\n\r\n", ShaStruct, ShaReccnt, ShaRecLast, ShaResult);
							ShaLog.Write(LogLine, LogLine.GetLength());
						}

						if (memcmp(ShaBuf, Jama360Buf, len) != 0) ShaDiffers = true;
					}
				}
				Sha360.Close();
			}
			else ShaDiffers = true;
			Sha.Close();
		}
		else ShaDiffers = true;
		if (ShaDiffers) {
			LogLine.Format("%s differs from 360 version\r\n", ShaFileName);
			ShaLog.Write(LogLine, LogLine.GetLength());
			CFile DifFile;
			CString ErrorFileName = PathJamaRoot + "..\\" + strJama360SerialNr.Mid(3, 3).MakeUpper() + "-Error.txt";
			DifFile.Open(ErrorFileName, CFile::modeCreate | CFile::modeWrite, NULL);
			DifFile.Write(LogLine, LogLine.GetLength());
			DifFile.Close();
			BakFilesIdentical = false;
		}
	}
	DBfinder.Close();
	ShaLog.Close();
}

void WriteFsdFile2Copy(int DBRef)
{
	CString FsdFilePath;

	CString Path = PathCopy();
	if (Path == "") return;
	FsdFilePath.Format("%sFAS\\%s.fsd", Path, DB[DBRef].Name);
	CFile fsdfil;
	if (fsdfil.Open(FsdFilePath, CFile::modeCreate | CFile::modeWrite, NULL)) {
		fsdfil.Write(Fsd[DBRef].buf, Fsd[DBRef].len);
		fsdfil.SetLength(Fsd[DBRef].len);
		SetFileLastWriteTimeFromDB(fsdfil.m_hFile, DBRef);
		fsdfil.Close();
		FilWrtCount++;
	}
}

bool CheckOutdatedFsdBak(int DBRef)
{
	bool ReWriteFsd = true;
	CString FsdFilePath;

	CString Path = PathCopy();
	if (Path == "") return false;
	FsdFilePath.Format("%sFAS\\%s.fsd", Path, DB[DBRef].Name);
	CFile fsdfil;
	if (fsdfil.Open(FsdFilePath, CFile::shareDenyNone | CFile::modeRead, NULL)) {
		ReWriteFsd = false;
		int rdlen = fsdfil.Read(BakFileCmpBuf, sizeof(BakFileCmpBuf));
		SetFileLastWriteTimeFromDB(fsdfil.m_hFile, DBRef);
		fsdfil.Close();
		if (rdlen == sizeof(BakFileCmpBuf)) {
			LogAdd(44, 0, "Sizeof FSD-file on disk too long for BakFileCmpBuf", FsdFilePath);
			ReWriteFsd = true;
		}
		else if (memcmp(Fsd[DBRef].buf, BakFileCmpBuf, Fsd[DBRef].len) || Fsd[DBRef].len != rdlen) ReWriteFsd = true;
		//if (ReWriteFsd) _unlink(FsdFilePath);
	}
	return ReWriteFsd;
}

void CompareSignaturesDBvsCopy(bool UseRestoreDir)
{
	CString PathDBSignature = PathDB + "SHA\\";
	CreateDirectory(PathDBSignature, NULL);

	if (UseRestoreDir) LogAdd(0, 0, "CompareSignatures DB versus Restore started");
	else LogAdd(0, 0, "CompareSignaturesDBvsCopy started");
	// Delete alle DB - SHA files
	CFileFind ShaFinder;
	CString File2Find = PathDBSignature + "*.SHA";
	BOOL bDBWorking = ShaFinder.FindFile(File2Find);
	while (bDBWorking) {
		bDBWorking = ShaFinder.FindNextFile();
		if (ShaFinder.IsDirectory()) continue;
		_unlink(ShaFinder.GetFilePath());
	}
	ShaFinder.Close();
	if (!UseRestoreDir) {
		// Delete alle BAK - SHA files
		File2Find = PathCopy() + "FAS\\" + "*.SHA";
		bDBWorking = ShaFinder.FindFile(File2Find);
		while (bDBWorking) {
			bDBWorking = ShaFinder.FindNextFile();
			if (ShaFinder.IsDirectory()) continue;
			_unlink(ShaFinder.GetFilePath());
		}
		ShaFinder.Close();
	}
	// Create NEW SHA files (DB and BAK)
	CFileFind DBfinder;
	File2Find = PathDB + "*.*";
	bDBWorking = DBfinder.FindFile(File2Find);
	while (bDBWorking) {
		if (JMSShuttingDown) break;
		bDBWorking = DBfinder.FindNextFile();
		if (DBfinder.IsDirectory()) continue;
		CString DBName = DBfinder.GetFileName();
		if (DBName.GetLength() != 7) continue; // moet sys.xxx zijn !
		if (DBName.Left(3).CompareNoCase("sys") == 0) {
			// create SHA-file for SYS-file
			// First check to see if it's loaded ...
			CString Ext = DBName.Right(3).MakeUpper();
			int file_ix = SysOpen((char *)(LPCTSTR)Ext, false, true);
			if (file_ix == -1) continue;
			sha1_context ctx;
			sha1_starts(&ctx);
			sha1_update(&ctx, (const unsigned char *)Sys[file_ix].Buf, Sys[file_ix].Length);
			// close SHA algrorithm en schrijf SHA file uit !
			unsigned char sha1[30];
			memset(sha1, 0, 30);
			sha1_finish(&ctx, sha1);
			CString LogLine, cstr;
			LogLine.Format("Signature [SYS.%s]     : ", Ext);
			CString SignatureFile;
			SignatureFile.Format("%sSYS.%s.SHA", PathDBSignature, Ext);
			CFile Sig;
			if (Sig.Open(SignatureFile, CFile::modeCreate | CFile::modeWrite, NULL)) {
				CString cstr, sigstr;
				sigstr.Format("SHA1=");
				for (int i = 0; i < 20; i++) {
					cstr.Format("%02X", sha1[i]);
					sigstr += cstr;
					LogLine += cstr;
				}
				sigstr += "\r\n";
				Sig.Write(sigstr, sigstr.GetLength());
				Sig.Close();
			}
			LogAdd(0, 1, LogLine);
			if (!UseRestoreDir) {
				// create SHA for SysBak-file
				CString SysBakName = PathCopy() + "FAS\\SYS." + Ext;
				if (!MakeAndCompareSignatureFromSysFile((char *)(LPCTSTR)SysBakName, sha1)) {
					WriteSysBakFile(file_ix);
					if (!MakeAndCompareSignatureFromSysFile((char *)(LPCTSTR)SysBakName, sha1)) {
						LogAdd(95, 0, "Shadow SYS-backup not good", SysBakName);
					}
				}
			}
			SysClose(file_ix);
			continue;
		}
		if (DBName.Right(3).CompareNoCase("old") == 0) continue;
		if (DBName.Right(3).CompareNoCase("res") == 0) continue;
		if (DBName.Right(3).CompareNoCase("raw") == 0) continue;
		if (DBName.Right(3).CompareNoCase("zip") == 0) continue;
		// open de DB
		int DBRef = FindDB((char *)(LPCTSTR)DBName);
		bool NotMountedFlag = false;
		if (DBRef < 0) {
			NotMountedFlag = true;
			DBRef = MountDB((char *)(LPCTSTR)DBName, false, true);
			if (DBRef < 0) {
				LogAdd(82, 0, "Cannot temporary load for SHA/BAK-creation", DBName);
				return;
			}
		}
		// om te zorgen dat de .fsd ook in de copy-subdir zit !
		if (CheckOutdatedFsdBak(DBRef)) WriteFsdFile2Copy(DBRef);
		// overloop nu alle TAB's van structuren om SHA van de DB-structs te maken
		for (int TabIx = 0; TabIx < DB[DBRef].TabCnt; TabIx++) {
			bool RebuildBakFlag = true;
			if (JMSShuttingDown) break;
			if (DB[DBRef].Tab[TabIx].StuNr == 0) continue;
			// create DB SHA-file
			unsigned long retlen;
			JET_ERR _jeterr;
			struct s_Rec {
				int RecNr;
				double DateTimeUpdated;
				short int ChangedBy;
				unsigned char Buf[BUF_LEN + 50];
			} Rec;
			memset(&Rec, 0, sizeof(struct s_Rec));
			sha1_context ctx;
			sha1_starts(&ctx);
			int RecNr = 1, DeletedCount = 0, RecCount = 0;
			JetCallVoidRet(2201, JetSetCurrentIndex4(DB[DBRef].SesId[0], DB[DBRef].Tab[TabIx].Tid[0], "", (JET_INDEXID*)DB[DBRef].Tab[TabIx].Idx[StuRecIx].rgbIndexId[0], 0, 0));
			JetCallVoidRet(2202, JetMakeKey(DB[DBRef].SesId[0], DB[DBRef].Tab[TabIx].Tid[0], &RecNr, sizeof(RecNr), JET_bitNewKey));
			_jeterr = JetSeek(DB[DBRef].SesId[0], DB[DBRef].Tab[TabIx].Tid[0], JET_bitSeekGE);
			// overloop nu alle records en bereken de SHA-value
			while (_jeterr == JET_wrnSeekNotEqual || _jeterr == JET_errSuccess) {
				if (JMSShuttingDown) break;
				JetCallVoidRet(3203, JetRetrieveColumn(DB[DBRef].SesId[0], DB[DBRef].Tab[TabIx].Tid[0], DB[DBRef].Tab[TabIx].Col[StuRecId].Cid[0], &Rec.RecNr, DB[DBRef].Tab[TabIx].Col[StuRecId].Len, &retlen, 0, 0));
				JetCallVoidRet(3204, JetRetrieveColumn(DB[DBRef].SesId[0], DB[DBRef].Tab[TabIx].Tid[0], DB[DBRef].Tab[TabIx].Col[StuChgId].Cid[0], &Rec.ChangedBy, DB[DBRef].Tab[TabIx].Col[StuChgId].Len, &retlen, 0, 0));
				JetCallVoidRet(3204, JetRetrieveColumn(DB[DBRef].SesId[0], DB[DBRef].Tab[TabIx].Tid[0], DB[DBRef].Tab[TabIx].Col[StuDatId].Cid[0], &Rec.DateTimeUpdated, DB[DBRef].Tab[TabIx].Col[StuDatId].Len, &retlen, 0, 0));
				JetCallVoidRet(3204, JetRetrieveColumn(DB[DBRef].SesId[0], DB[DBRef].Tab[TabIx].Tid[0], DB[DBRef].Tab[TabIx].Col[StuValId].Cid[0], Rec.Buf, BUF_LEN, &retlen, 0, 0));
				sha1_update(&ctx, (const unsigned char *)&Rec, retlen + sizeof(Rec.RecNr) + sizeof(Rec.ChangedBy) + sizeof(Rec.DateTimeUpdated));
				RecCount++;
				if (RecNr != Rec.RecNr) DeletedCount += (Rec.RecNr - RecNr);
				RecNr = Rec.RecNr + 1;
				_jeterr = JetMove(DB[DBRef].SesId[0], DB[DBRef].Tab[TabIx].Tid[0], JET_MoveNext, 0);
			}
			if (JMSShuttingDown) break;
			// close SHA algrorithm en schrijf SHA file uit !
			unsigned char sha1[30];
			memset(sha1, 0, 30);
			sha1_finish(&ctx, sha1);
			CString LogLine, cstr;
			LogLine.Format("Signature [%s.%03d]     : ", DB[DBRef].Name, DB[DBRef].Tab[TabIx].StuNr);
			CString SignatureFile;
			SignatureFile.Format("%s%s.%03d.SHA", PathDBSignature, DB[DBRef].Name, DB[DBRef].Tab[TabIx].StuNr);
			CFile Sig;
			if (Sig.Open(SignatureFile, CFile::modeCreate | CFile::modeWrite, NULL)) {
				CString cstr, sigstr;
				sigstr.Format("SHA1=");
				for (int i = 0; i < 20; i++) {
					cstr.Format("%02X", sha1[i]);
					sigstr += cstr;
					LogLine += cstr;
				}
				sigstr += "\r\n";
				cstr.Format("RecordCount=%d\r\n", RecCount);
				sigstr += cstr;
				cstr.Format("RecLastUsed=%d\r\n", Rec.RecNr);
				sigstr += cstr;
				Sig.Write(sigstr, sigstr.GetLength());
				Sig.Close();
			}
			cstr.Format(" (Cnt=%d/Lst=%d)", RecCount, Rec.RecNr);
			LogLine += cstr;
			LogAdd(0, 1, LogLine);
			if (UseRestoreDir) {
				bool IsWorkFile = false;
				CString DBNameType = DB[DBRef].Name;
				DBNameType = DBNameType.Left(3);
				if (theApp.iniFile.getKeyValue("WorkFiles", "DataBaseSettings").Find(DBNameType) >= 0) IsWorkFile = true;
				if (!IsWorkFile) {
					// READ DB-Sha file
					char buf[2000];
					CString DBSha, BakSha;
					if (Sig.Open(SignatureFile, CFile::modeRead, NULL)) {
						int cnt = Sig.Read(buf, 1999);
						buf[cnt] = 0;
						DBSha = buf;
						Sig.Close();
					}
					else LogAdd(85, 0, "Cannot open/read DB-SHA-file", SignatureFile);
					// READ BAK-Sha file
					int k = SignatureFile.ReverseFind('\\');
					CString BakSignatureFile = PathJamaRoot + "Restore\\" + SignatureFile.Mid(k + 1);
					CString BakFileName = BakSignatureFile.Left(BakSignatureFile.GetLength() - 3) + "BAK";
					BakSignatureFile = BakSignatureFile.Left(BakSignatureFile.GetLength() - 3) + "BAK.SHA";
					if (Sig.Open(BakSignatureFile, CFile::modeRead, NULL)) {
						int cnt = Sig.Read(buf, 1999);
						buf[cnt] = 0;
						BakSha = buf;
						Sig.Close();
					}
					else LogAdd(84, 0, "Cannot open/read Restore-SHA-file", BakSignatureFile);
					// Compare the versions !
					if (DBSha != BakSha) {
						LogAdd(83, 0, "Difference found in SHA between DB and Restore/BAK-version", SignatureFile.Mid(k + 1));
					}
				}
			}
			else {
			RebuildBak:
				// controleer nu ook of de BAK-file up to date is voor de structuur !
				UpdateBakFile(DBRef, TabIx);
				// Maak dan SHA-file voor deze BAK-file
				BakFilePath.Format("%sFAS\\%s.%03d.BAK", PathCopy(), DB[DBRef].Name, DB[DBRef].Tab[TabIx].StuNr);
				MakeSignatureFromBAK((char *)(LPCTSTR)BakFilePath);
				// READ DB-Sha file
				char buf[2000];
				CString DBSha, BakSha;
				if (Sig.Open(SignatureFile, CFile::modeRead, NULL)) {
					int cnt = Sig.Read(buf, 1999);
					buf[cnt] = 0;
					DBSha = buf;
					Sig.Close();
				}
				else LogAdd(85, 0, "Cannot open/read DB-SHA-file", SignatureFile);
				// READ BAK-Sha file
				int k = SignatureFile.ReverseFind('\\');
				CString BakSignatureFile = PathCopy() + "FAS\\" + SignatureFile.Mid(k + 1);
				CString BakFileName = BakSignatureFile.Left(BakSignatureFile.GetLength() - 3) + "BAK";
				BakSignatureFile = BakSignatureFile.Left(BakSignatureFile.GetLength() - 3) + "BAK.SHA";
				if (Sig.Open(BakSignatureFile, CFile::modeRead, NULL)) {
					int cnt = Sig.Read(buf, 1999);
					buf[cnt] = 0;
					BakSha = buf;
					Sig.Close();
				}
				else LogAdd(84, 0, "Cannot open/read Bak-SHA-file", BakSignatureFile);
				// Compare the versions !
				if (DBSha != BakSha) {
					LogAdd(83, 0, "Difference found in SHA between DB and BAK-version", SignatureFile.Mid(k + 1));
					if (RebuildBakFlag) {
						LogAdd(0, 0, "Adding old BAK into Snapshot-OLD and starting to rebuild BAK-file");
						CString ZipFileList = (BakFileName + "|");
						pMainDlg->CreateZipSnapShotFromFasBack("OLD", ZipFileList, PathCopy(), 10080); // 1 week lifetime !
						LogAdd(0, 1, "Removing Bak-file (with SHA-file)", BakFileName);
						_unlink(BakFileName);
						_unlink(BakSignatureFile);
						RebuildBakFlag = false;
						goto RebuildBak;
					}
					else {
						LogAdd(88, 0, "Rebuilding did not solve the SHA-difference", SignatureFile.Mid(k + 1));
					}
				}
			}
		}
		// all structures processed !
		if (NotMountedFlag) {
			UnMountDB(DBRef);
		}
	}
	DBfinder.Close();
	if (UseRestoreDir) LogAdd(0, 0, "CompareSignatures DB versus Restore ended");
	else LogAdd(0, 0, "CompareSignaturesDBvsCopy ended");
}

bool CompareSysFromRestore(char *ext)
{
	int file_ix;
	for (file_ix = 0; file_ix < MAX_SYSFILE; file_ix++) {
		if (Sys[file_ix].Ext.CompareNoCase(ext) == 0) break;
	}
	if (file_ix == MAX_SYSFILE) return false;

	for (int i = 0; i < 15; i++) {
		char FileName[20];
		memcpy(FileName, Sys[file_ix].Buf + 300 + i * 17, 15);
		FileName[15] = 0;
		if (FileName[0]) {
			if (CompareFasFromRestore(FileName)) LogAdd(0, 0, "Identical DB", FileName);
		}
	}

	/*
	   CString SysFileName;
	   SysFileName="SYS.";
	   SysFileName+=ext;
	   SysFileName = PathProg + SysFileName;
	   SysFileName.MakeUpper();
	   SysFileName+=".exp";
	   CFile SysFile;
	   LogAdd(0,0,"Exporting SYS",SysFileName);
	 SysFile.Open(SysFileName,CFile::modeReadWrite|CFile::modeCreate,0);
	   SysFile.Write(Sys[file_ix].Buf,Sys[file_ix].Length);
	   SysFile.Close();
	 */

	LogAdd(0, 0, "Compare done for system", ext);
	return true;
}


bool RestoreFasFromBak(char *FasFileName) // de FAS-file bestaat niet in de subdir, moeten dus creeren.
{
	LogAdd(0, 0, "Restoring into NEW DataBase", FasFileName);

	unsigned long retlen;
	unsigned char *p;
	bool BakErr = false;
	CString PathRestore = PathJamaRoot + "RESTORE\\";
	CString FsdInRestore = PathRestore + FasFileName + ".fsd";
	CString FsdInFas = PathFSD + FasFileName + ".fsd";
	CopyFile(FsdInRestore, FsdInFas, FALSE);

	int DBRef = MountDB(FasFileName, true, true);
	if (DBRef < 0) return false;

	for (int TabIx = 0; TabIx < DB[DBRef].TabCnt; TabIx++) {
		if (DB[DBRef].Tab[TabIx].StuNr == 0) continue;

		CFile BakFile;
		CString BakFilePath;
		BakFilePath.Format("%s%s.%03d.BAK", PathRestore, FasFileName, DB[DBRef].Tab[TabIx].StuNr);
		if (!BakFile.Open(BakFilePath, CFile::shareDenyWrite | CFile::modeReadWrite, NULL)) {
			BakErr = true;
			if (theApp.JmsCreateDBFromRestore) {
				CString FasType = FasFileName;
				FasType = FasType.Left(3).MakeUpper();
				if (theApp.iniFile.getKeyValue("WorkFiles", "DataBaseSettings").Find(FasType) >= 0) continue; // 
			}
			LogAdd(50, 0, "Cannot open Backup-file", BakFilePath);
			continue;
		}

		BakFile.Seek(0L, 0);
		BakFile.Read(BakHeader, sizeof(BakHeader));
		bool BadBak = false;
		if (BakHdr->Type != 0xFE) BadBak = true;
		if (BakHdr->Version != 01) BadBak = true;
		if (BakHdr->RecPos != sizeof(BakHeader)) BadBak = true;
		int RecLen = DB[DBRef].Tab[TabIx].StructLen - DB[DBRef].Tab[TabIx].EleInf[1].FldLen;
		if (BakHdr->RecBakLen != (RecLen + 11)) BadBak = true;
		if (_strcmpi((const char *)BakHdr->OrigDBName, DB[DBRef].Name) != 0) BadBak = true;

		if (BadBak) {
			BakFile.Close();
			BakErr = true;
			continue;
		}

		int RecNr = 1;
		int RecUsed = 0;
		int StuNr = DB[DBRef].Tab[TabIx].StuNr;
		while (RecNr <= BakHdr->RecCount) {
			int rLen = BakFile.Read(&RecDump, BakHdr->RecBakLen);
			if (rLen < BakHdr->RecBakLen) {
				LogAdd(50, 0, "BakFile too short (incomplete record read)", BakFilePath);
				BakErr = false;
				break;
			}
			if (RecDump.Used) {
				p = RecDump.RecBuf; retlen = RecLen;
				while (retlen--) *p++ = (*p >> 4) | (*p << 4);
				EDBAddRec(DBRef, StuNr, RecNr, RecLen, RecDump.RecBuf, RecDump.DateTimeUpdated, RecDump.ChangedBy);
				RecUsed++;
			}
			else {
				EDBAddDeletedRecNr(0, DBRef, StuNr, RecNr, RecDump.DateTimeUpdated, RecDump.ChangedBy);
			}
			RecNr++;
		}
		BakFile.Close();
		DB[DBRef].Tab[TabIx].LastRec = RecNr - 1;
		DB[DBRef].Tab[TabIx].UsedRec = RecUsed;
	}

	EDBCheckCalc(DBRef, false);
	UnMountDB(DBRef);
	LogAdd(0, 0, "Data restored", FasFileName);

	return true;
}

void WriteSysBakFile(int file_ix)
{
	CString SysFilePath;
	CString Path = PathCopy();
	if (Path == "") return;
	SysFilePath.Format("%sFAS\\SYS.%s", Path, Sys[file_ix].Ext);
	try {
		CFile sysfil;
		if (sysfil.Open(SysFilePath, CFile::modeCreate | CFile::modeWrite, NULL)) {
			sysfil.Write(Sys[file_ix].Buf, Sys[file_ix].Length);
			sysfil.SetLength(Sys[file_ix].Length);
			SetFileLastWriteTime(sysfil.m_hFile, Sys[file_ix].DateTimeLastWrite);
			sysfil.Close();
			FilWrtCount++;
		}
	}
	catch (...) {}
}

bool CheckOutdatedSysBak(int file_ix)
{
	bool ReWriteSys = true;
	CString SysFilePath;

	CString Path = PathCopy();
	if (Path == "") return false;
	SysFilePath.Format("%sFAS\\SYS.%s", Path, Sys[file_ix].Ext);
	try {
		CFile sysfil;
		if (sysfil.Open(SysFilePath, CFile::shareDenyNone | CFile::modeRead, NULL)) {
			ReWriteSys = false;
			int rdlen = sysfil.Read(BakFileCmpBuf, sizeof(BakFileCmpBuf));
			sysfil.Close();
			if (rdlen == sizeof(BakFileCmpBuf)) {
				LogAdd(44, 0, "Sizeof SYS-file on disk too long for BakFileCmpBuf", SysFilePath);
				ReWriteSys = true;
			}
			else if (memcmp(Sys[file_ix].Buf, BakFileCmpBuf, Sys[file_ix].Length) || Sys[file_ix].Length != rdlen) ReWriteSys = true;
			//if (ReWriteSys) _unlink(SysFilePath);
		}
	}
	catch (...) {}
	return ReWriteSys;
}

void CreateSnapShot(char *ext, int LifeTimeMinutes, bool IncludeWorkFiles)
{
	CString FileList = "";
	char SysBuf[MAX_SYS_LEN + 10];
	CFile SysFile;
	CString cstr;

	if (ext[0] == 0) {
		ext = "$$$";
		cstr.Format("Start Zip-SnapShot of dataset %s", ext);
		LogAdd(0, 1, cstr);

		CFileFind DBfinder;
		CString File2Find = PathCopy();
		File2Find += "*.zip"; // bv. prog.zip, jamapda.zip, kassa.zip, ....
		BOOL bDBWorking = DBfinder.FindFile(File2Find);
		while (bDBWorking) {
			bDBWorking = DBfinder.FindNextFile();
			CString FileTitle = DBfinder.GetFileTitle();
			if (FileTitle.GetLength() > 8) continue;
			FileTitle.MakeLower();
			if (FileTitle == "mail") continue;
			FileList += DBfinder.GetFilePath();
			FileList += "|";
		}
		DBfinder.Close();
	}
	else {
		CString WorkFilesList = theApp.iniFile.getKeyValue("WorkFiles", "DataBaseSettings");
		WorkFilesList.MakeUpper();

		cstr.Format("Start Zip-SnapShot of dataset %s", ext);
		LogAdd(0, 1, cstr);

		CString SysFilePath = PathCopy(); // als deze leeg is wordt dat hieronder dedetecteerd ...
		SysFilePath += "FAS\\SYS."; // zie hieronder om te zien of hij leeg is ....
		SysFilePath += ext;

		if (SysFilePath.Left(3) == "SYS" || !SysFile.Open(SysFilePath, CFile::modeRead, 0)) {
			LogAdd(45, 0, "Snapshot failed. SysFile for snapshot not found", SysFilePath);
			return;
		}
		SysFile.Read(SysBuf, MAX_SYS_LEN);
		SysFile.Close();

		FileList += SysFilePath;
		FileList += "|";

		for (int i = 0; i < 15; i++) {
			char FileName[20];
			memcpy(FileName, SysBuf + 300 + i * 17, 15);
			FileName[15] = 0;
			if (FileName[0]) {
				CString DBFileTitle = FileName;
				DBFileTitle.MakeUpper();
				int j = DBFileTitle.Find('.');
				if (j > 0 && !IncludeWorkFiles && WorkFilesList.Find(DBFileTitle.Left(j)) >= 0) continue;

				CFileFind DBfinder;
				CString File2Find = PathCopy();
				File2Find += "FAS\\";
				File2Find += FileName;
				File2Find += "*.*";     // bv. lev.fas*.* dat is lev.fas.fsd, lev.fas-001.bak, ...
				BOOL bDBWorking = DBfinder.FindFile(File2Find);
				while (bDBWorking) {
					bDBWorking = DBfinder.FindNextFile();
					FileList += DBfinder.GetFilePath();
					FileList += "|";
				}
				DBfinder.Close();
			}
		}
	}

	pMainDlg->CreateZipSnapShotFromFasBack(ext, FileList, PathCopy(), LifeTimeMinutes);
	cstr.Format("SnapShot of dataset %s created, Lt", ext);
	LogAdd(0, 0, cstr, LifeTimeMinutes);

	// compare all existing ZIP-files for this EXT for identical snapshots, and remove the lowest TTL !  
	CFileFind SnapShotFinder;
	CString File2Find;
	CString SnapShotPath[200];
	int SnapShotCount = 0;

	for (int d = 0; d < 2; d++) {
		SnapShotCount = 0;
		File2Find = PathCopy();
		if (d == 1) {
			if (File2Find == PathCopyAlt) continue;
			File2Find = PathCopyAlt;
		}
		if (File2Find.GetLength() == 0) continue;

		File2Find.Format("%ssnapshot-%s-*.zip", File2Find, ext);
		BOOL bWorking = SnapShotFinder.FindFile(File2Find);
		while (bWorking) {
			bWorking = SnapShotFinder.FindNextFile();
			if (SnapShotFinder.IsDirectory()) continue;
			if (pMainDlg->IsValidZipArchive((char *)(LPCTSTR)SnapShotFinder.GetFilePath())) {
				SnapShotPath[SnapShotCount++] = SnapShotFinder.GetFilePath();
			}
		}
		SnapShotFinder.Close();

		// sort names
		for (int i = 0; i < SnapShotCount - 1; i++) {
			int imax = i;
			for (int j = i + 1; j < SnapShotCount; j++) {
				if (SnapShotPath[j] > SnapShotPath[imax]) imax = j;
			}
			CString cstr = SnapShotPath[i];
			SnapShotPath[i] = SnapShotPath[imax];
			SnapShotPath[imax] = cstr;
		}

		// compare the contents of the snapshots
		for (int i = 0; i < SnapShotCount - 1; i++) {
			for (int j = i + 1; j < SnapShotCount; j++) {
				if (pMainDlg->AreSnapShotsIdentical(SnapShotPath[i], SnapShotPath[j])) {
					if (_unlink(SnapShotPath[j]) == 0) { // succesfull delete
						cstr.Format("Deleted identical snapshot with lowest TTL : %s", SnapShotPath[j]);
					}
					else cstr.Format("Cannot delete identical snapshot with lowest TTL : %s", SnapShotPath[j]);
					LogAdd(0, 0, cstr);
				}
			}
		}
		int j = 0;

	}
}

void RemoveOverdueSnapShotsAndTMPInCopy()
{
	CString cstr, ExpDate, Ext;
	COleDateTime now = COleDateTime::GetCurrentTime();
	COleDateTime Exp;

	CFileFind SnapShotFinder;
	CString File2Find;

	for (int d = 0; d < 2; d++) {
		if (d == 0) File2Find = PathCopy();
		if (d == 1) File2Find = PathCopyAlt;
		if (File2Find.GetLength() == 0) continue;

		File2Find += "snapshot-*.*";
		BOOL bWorking = SnapShotFinder.FindFile(File2Find);
		while (bWorking) {
			bWorking = SnapShotFinder.FindNextFile();
			CString FileTitle = SnapShotFinder.GetFileTitle();
			Ext = FileTitle.Mid(9, 3);
			ExpDate = FileTitle.Mid(13, 11);
			Exp = COleDateTime(2000 + StrToInt(ExpDate.Mid(0, 2)), StrToInt(ExpDate.Mid(2, 2)), StrToInt(ExpDate.Mid(4, 2)), StrToInt(ExpDate.Mid(7, 2)), StrToInt(ExpDate.Mid(9, 2)), 0);
			if (Exp > now) continue;

			if (_unlink(SnapShotFinder.GetFilePath()) == 0) { // succesfull delete
				cstr.Format("Deleted SnapShot of Dataset %s, expire-date", Ext);
			}
			else cstr.Format("Cannot delete SnapShot of Dataset %s, expire-date", Ext);
			LogAdd(0, 0, cstr, ExpDate);
		}
		SnapShotFinder.Close();

		CFileFind TMPFinder;
		if (d == 0) File2Find = PathCopy();
		if (d == 1) File2Find = PathCopyAlt;
		if (File2Find.GetLength() == 0) continue;

		File2Find += "*.TMP";
		bWorking = TMPFinder.FindFile(File2Find);
		while (bWorking) {
			bWorking = TMPFinder.FindNextFile();
			if (TMPFinder.IsDirectory()) continue;
			if (_unlink(TMPFinder.GetFilePath()) == 0) { // succesfull delete
				LogAdd(0, 0, "TMP-file deleted", TMPFinder.GetFilePath());
			}
			else LogAdd(0, 0, "Cannot delete TMP-file", TMPFinder.GetFilePath());
		}
		TMPFinder.Close();
	}
}

bool CheckOutdatedJamaSubDirZip(CString JamaSubDir, CString ZipFilePath, LPFILETIME pftLastUpdate)
{
	bool ReWriteZip = true;
	CString PathJamaSubDir = PathJamaRoot + JamaSubDir + "\\";
	if (GetFileAttributes(PathJamaSubDir) == INVALID_FILE_ATTRIBUTES) return false; // directory bestaat niet !

	memset(pftLastUpdate, 0, sizeof(FILETIME));
	int DirNesting = 0;
	CFileFind FileFinder[10]; // maximaal 10 niveau's diep
	CString File2Find[10];
	BOOL bWorking[10];
	File2Find[0] = PathJamaSubDir + "*.*";
	bWorking[0] = FileFinder[0].FindFile(File2Find[0]);

	while (DirNesting >= 0) {
		while (bWorking[DirNesting]) {
			bWorking[DirNesting] = FileFinder[DirNesting].FindNextFile();
			if (FileFinder[DirNesting].IsDots()) continue;

			CString Ext = FileFinder[DirNesting].GetFileName();
			if (Ext.GetLength() < 4) Ext = "";
			else Ext = Ext.Right(3);
			if (Ext.CompareNoCase(".OK") == 0) continue;
			if (Ext.CompareNoCase("FLG") == 0) continue;
			if (Ext.CompareNoCase("STA") == 0) continue;
			if (Ext.CompareNoCase("SER") == 0) continue;

			if (FileFinder[DirNesting].IsDirectory()) {
				if (DirNesting == 9) continue;

				DirNesting++;
				File2Find[DirNesting] = FileFinder[DirNesting - 1].GetFilePath() + "\\*.*";
				bWorking[DirNesting] = FileFinder[DirNesting].FindFile(File2Find[DirNesting]);
			}
			else {
				FILETIME ftFileLastUpdated;
				if (FileFinder[DirNesting].GetLastWriteTime(&ftFileLastUpdated)) {
					if (ftFileLastUpdated.dwHighDateTime > pftLastUpdate->dwHighDateTime ||
						(ftFileLastUpdated.dwHighDateTime == pftLastUpdate->dwHighDateTime && ftFileLastUpdated.dwLowDateTime > pftLastUpdate->dwLowDateTime)) {

						pftLastUpdate->dwHighDateTime = ftFileLastUpdated.dwHighDateTime;
						pftLastUpdate->dwLowDateTime = ftFileLastUpdated.dwLowDateTime;
					}
				}
			}
		}
		FileFinder[DirNesting].Close();
		DirNesting--;
	}

	WIN32_FIND_DATA ZipFileData;
	HANDLE hFind;
	if ((hFind = FindFirstFile(ZipFilePath, &ZipFileData)) != INVALID_HANDLE_VALUE) {
		FindClose(hFind);
		if (ZipFileData.ftLastWriteTime.dwHighDateTime > pftLastUpdate->dwHighDateTime) {
			ReWriteZip = false;
		}
		if (ZipFileData.ftLastWriteTime.dwHighDateTime == pftLastUpdate->dwHighDateTime && ZipFileData.ftLastWriteTime.dwLowDateTime >= pftLastUpdate->dwLowDateTime) {  // niet gelijk nemen, de resolutie van de FILETIME op disk is niet zo nauwkeurig !
			ReWriteZip = false;
		}
	}

	// if (ReWriteZip) _unlink(ZipFilePath); niet doen, want anders is de backup weg terwijl hij stopt wanneer de update gebeurt ...
	return ReWriteZip;
}


void ProcessJamaSubDirs()
{
	CString JamaSubDirs = theApp.iniFile.getKeyValue("CopyJamaSubDirs", "CopySettings"); // bv PROG|KASSA|PDA|FTKOPIE
	CString cstr;
	int ParseIx = 0;
	while (!JMSShuttingDown) {
		if (ParseIx >= JamaSubDirs.GetLength()) break;
		int NewParseIx = JamaSubDirs.Find("|", ParseIx);
		if (NewParseIx == -1) NewParseIx = JamaSubDirs.GetLength();
		CString File2Copy = JamaSubDirs.Mid(ParseIx, NewParseIx - ParseIx);
		cstr.Format("ProcessJamaSubDirs for %s", File2Copy);
		LogSpec("JMSCreateAndUpdateCopy", (char*)(LPCTSTR)cstr);

		if (File2Copy.MakeUpper() == "FTKOPIE") {
			CString ZipFilePath = PathCopy() + "FTKOPIE.zip";
			pMainDlg->CreateAndMaintainZipArchiveFTKopie(ZipFilePath);
		}
		else {
			CString ZipFilePath = PathCopy() + File2Copy.MakeUpper() + ".zip";
			FILETIME ftLastUpdate;
			if (CheckOutdatedJamaSubDirZip(File2Copy, ZipFilePath, &ftLastUpdate)) {
				pMainDlg->CreateZipArchiveJamaSubDir(File2Copy, ZipFilePath);
				CFile file;
				file.Open(ZipFilePath, CFile::modeWrite, NULL);
				SetFileTime(file.m_hFile, NULL, NULL, &ftLastUpdate);
				file.Close();
			}
		}
		ParseIx = NewParseIx + 1;
	}
}

double DmpStartedJama360SpilDateTime = -1;  // voor het geval ondertussen een update zou gebeuren met een nieuwe Jama360SpilDateTime (blijft dus constant tijdens dump, ook gebruikt als semaphoor)
void DmpAll(int dummy);
bool UploadShaToGeel(CString CustCode);

void ShadowCopyWriteUpdates()
{
	int DBRef, TabIx;
	CString cstr;

	BakUpdCount = 0;
	BakDelCount = 0;
	FilWrtCount = 0;
	LogAdd(0, 0, "Update Shadow-Copy : Started");
	for (DBRef = 0; DBRef < DB_MAX; DBRef++) {
		if (!DB[DBRef].Updated) continue;
		if (DB[DBRef].Id[0]) {
			DB[DBRef].Updated = false;
			for (TabIx = 0; TabIx < DB[DBRef].TabCnt; TabIx++) {
				if (JMSShuttingDown) break;
				if (DB[DBRef].Tab[TabIx].StuNr == 0) continue;
				cstr.Format("Update Shadow-Copy - Update Bakfile for %s Stu=%d", DB[DBRef].Name, DB[DBRef].Tab[TabIx].StuNr);
				LogSpec("JMSCreateAndUpdateCopy", (char*)(LPCTSTR)cstr);
				UpdateBakFile(DBRef, TabIx);
			}
		}
	}

	for (int file_ix = 0; file_ix < MAX_SYSFILE; file_ix++) {
		if (Sys[file_ix].Name[0] && Sys[file_ix].Updated) {
			cstr.Format("Update Shadow-Copy - Update SysFile %s", Sys[file_ix].Name);
			LogSpec("JMSCreateAndUpdateCopy", (char*)(LPCTSTR)cstr);
			Sys[file_ix].Updated = false;
			WriteSysBakFile(file_ix);
		}
	}

	for (DBRef = 0; DBRef < DB_MAX; DBRef++) {
		if (Fsd[DBRef].Updated) {
			cstr.Format("Periodic Shadow-Copy - Update Fsdfile for %s", DB[DBRef].Name);
			LogSpec("JMSCreateAndUpdateCopy", (char*)(LPCTSTR)cstr);
			Fsd[DBRef].Updated = false;
			WriteFsdFile2Copy(DBRef);
		}
	}

	cstr.Format("Update Shadow-Copy : Done (Rcs=%d / Rem=%d / Fil=%d)", BakUpdCount, BakDelCount, FilWrtCount);
	LogAdd(0, 0, cstr);
}

void ShadowCopyFullCheck()
{
	int DBRef, TabIx;
	LogAdd(0, 0, "Periodic check Shadow-Copy : Started");
	ProcessJamaSubDirs();
	CString cstr;

	BakUpdCount = 0;
	BakDelCount = 0;
	FilWrtCount = 0;
	// Alle Mounted DataBases overlopen ...
	for (DBRef = 0; DBRef < DB_MAX; DBRef++) {
		if (DB[DBRef].Id[0]) {
			DB[DBRef].Updated = false;
			for (TabIx = 0; TabIx < DB[DBRef].TabCnt; TabIx++) {
				if (JMSShuttingDown) break;
				if (DB[DBRef].Tab[TabIx].StuNr == 0) continue;
				cstr.Format("Periodic Shadow-Copy - Update Bakfile for %s Stu=%d", DB[DBRef].Name, DB[DBRef].Tab[TabIx].StuNr);
				LogSpec("JMSCreateAndUpdateCopy", (char*)(LPCTSTR)cstr);
				UpdateBakFile(DBRef, TabIx);
			}
		}
	}

	for (int file_ix = 0; file_ix < MAX_SYSFILE; file_ix++) {
		if (Sys[file_ix].Name[0]) {
			if (CheckOutdatedSysBak(file_ix)) {
				cstr.Format("Periodic Shadow-Copy - Update SysFile %s", Sys[file_ix].Name);
				LogSpec("JMSCreateAndUpdateCopy", (char*)(LPCTSTR)cstr);
				WriteSysBakFile(file_ix);
			}
		}
	}

	for (DBRef = 0; DBRef < DB_MAX; DBRef++) {
		if (DB[DBRef].Id[0]) {
			cstr.Format("Periodic Shadow-Copy - Update Fsdfile for %s", DB[DBRef].Name);
			LogSpec("JMSCreateAndUpdateCopy", (char*)(LPCTSTR)cstr);
			if (CheckOutdatedFsdBak(DBRef)) WriteFsdFile2Copy(DBRef);
		}
	}

	cstr.Format("Periodic check Shadow-Copy : Done (Rcs=%d / Rem=%d / Fil=%d)", BakUpdCount, BakDelCount, FilWrtCount);
	LogAdd(0, 0, cstr);

}

#ifdef _DEBUG
bool SendInfo2GeelFlag = false;
#else
bool SendInfo2GeelFlag = true;
#endif

void SendInfo2Geel()
{
	LogAdd(0, 0, "PC-Info-Rapport for Jamadata : creating");
	CString CustCode = theApp.iniFile.getKeyValue("SerialNr", "JamaSettings").Mid(3, 3).MakeUpper();
	CString PathToGeel = PathJamaRoot + "ToGeel\\";

	//Copy JMS.ini 
	CString JMSFileName = PathProg + "JMS.ini";
	CString ToGeelJmsFileName = PathToGeel + "JMS.ini";
	CopyFile(JMSFileName, ToGeelJmsFileName, FALSE);
	//Copy Struct.cnf
	CString CnfFileName = PathProg + "struct.cnf";
	CString ToGeelCnfFileName = PathToGeel + "struct.cnf";
	CopyFile(CnfFileName, ToGeelCnfFileName, FALSE);

	//CopyLast LOG-file (yesterday)
	char LogFilePath[MAX_PATH + 10];
	LogGetFileName(LogFilePath, sizeof(LogFilePath), -1); // Logfile yesterday
	CString LogFileNameOnly = LogFilePath;
	int i = LogFileNameOnly.ReverseFind('\\');
	if (i > 0) LogFileNameOnly = LogFileNameOnly.Mid(i + 1); // Logfile today 
	CopyFile(LogFilePath, PathToGeel + LogFileNameOnly, FALSE);
	LogGetFileName(LogFilePath, sizeof(LogFilePath), 0);
	LogFileNameOnly = LogFilePath;
	i = LogFileNameOnly.ReverseFind('\\');
	if (i > 0) LogFileNameOnly = LogFileNameOnly.Mid(i + 1);
	CopyFile(LogFilePath, PathToGeel + LogFileNameOnly, FALSE);

	CFile BatFile;
	CString DirTxtFileName = PathToGeel + "DIR.txt";
	_unlink(DirTxtFileName);
	CString BatText, BatLine;
	BatLine.Format("del 1.tmp\n\r");
	BatText += BatLine;
	BatLine.Format("dir .. /s /on >1.tmp\r\n");
	BatText += BatLine;
	BatLine.Format("del 2.tmp\n\r");
	BatText += BatLine;
	CString CopyDir = PathCopy();
	if (CopyDir.GetLength() < 2) {
		BatLine.Format("echo ShadowCopyNotFound >2.tmp\r\n");
	}
	else {
		BatLine.Format("dir %s /s /on >2.tmp\r\n", CopyDir);
	}
	BatText += BatLine;
	BatLine.Format("copy 1.tmp+2.tmp %s\r\n", DirTxtFileName);
	BatText += BatLine;
	BatLine.Format("del 1.tmp\r\n");
	BatText += BatLine;
	BatLine.Format("del 2.tmp\r\n");
	BatText += BatLine;
	CString BatFileName;
	BatFileName.Format("%smkdirlst.bat", PathToGeel);
	if (BatFile.Open(BatFileName, CFile::modeCreate | CFile::modeReadWrite)) {
		BatFile.Write(BatText, BatText.GetLength());
		BatFile.Close();
		CString Arguments = "/C " + BatFileName;
		::ShellExecute(NULL, "open", "cmd.exe", Arguments, PathToGeel, SW_HIDE); // SW_NORMAL);
	}

	Sleep(2000); // wacht 2 seconden, dat de batch file zeker gestart is !
	// wait max 20 seconds for mkdirlst.bat to complete 
	CFile DirTxtFile;
	for (int i = 0; i < 20; i++) {
		if (JMSShuttingDown) return;
		if (DirTxtFile.Open(DirTxtFileName, CFile::modeReadWrite)) {
			DirTxtFile.Close();
			break;
		}
		Sleep(1000);
		pMainDlg->ProcessAllMessages();
	}
	Sleep(1000);

	// Copy all sys-files 
	CFileFind SysFinder;
	CString File2Find = PathDB + "SYS.*";
	BOOL bSysWorking = SysFinder.FindFile(File2Find);
	while (bSysWorking) {
		bSysWorking = SysFinder.FindNextFile();
		if (SysFinder.IsDirectory()) continue;
		CString SysName = SysFinder.GetFileName();
		if (SysName.GetLength() != 7) continue;  // enkel namen met op dit niveau SYS.xxx waarbij xxx de EXT is

		CString Ext = SysName.Right(3).MakeUpper();

		int file_ix;
		for (file_ix = 0; file_ix < MAX_SYSFILE; file_ix++) {
			if (Sys[file_ix].Ext.CompareNoCase(Ext) == 0) break;
		}
		CString SysFilePath = PathToGeel;
		SysFilePath += "SYS.";
		SysFilePath += Ext;
		if (file_ix == MAX_SYSFILE) {
			// SysFile not mounted
			CopyFile(SysFinder.GetFilePath(), SysFilePath, FALSE);
		}
		else {
			// SysFile is mounted
			CFile sysfil;
			if (sysfil.Open(SysFilePath, CFile::modeCreate | CFile::modeWrite, NULL)) {
				sysfil.Write(Sys[file_ix].Buf, Sys[file_ix].Length);
				sysfil.SetLength(Sys[file_ix].Length);
				SetFileLastWriteTime(sysfil.m_hFile, Sys[file_ix].DateTimeLastWrite);
				sysfil.Close();
			}
		}
	}

	// copy interesting files for all kassa's
	for (int KassaNr = 1; KassaNr < 50; KassaNr++) {
		CString DirNameKassa, SrcName, DstName, FileName;
		DirNameKassa.Format("%sKassa\\Kassa-%02d\\", PathJamaRoot, KassaNr);
		if (GetFileAttributes(DirNameKassa) != INVALID_FILE_ATTRIBUTES) {
			for (int fix = 0; fix < 3; fix++) {
				if (fix == 0) FileName = "jama.bat";
				else if (fix == 1) FileName = "kasmenu.dat";
				else if (fix == 2) FileName = "kassys.dat";
				SrcName = DirNameKassa + FileName;
				DstName.Format("%sK%02d-%s", PathToGeel, KassaNr, FileName);
				CopyFile(SrcName, DstName, FALSE);
			}
		}
	}

	_unlink(BatFileName);

	if (UploadZippedToGeel(PathToGeel, CustCode)) LogAdd(0, 0, "PC-Info-Rapport for Jamadata : done");
}

void AskJmtToReloadSystem()
{
	LogAdd(0, 1, "JMT.cmd created to request reload of all programmodules");
	CFile Cmd;
	//CString WrkName = PathProg + "JMT.WRK";
	CString CmdName = PathProg + "JMT.CMD";
	_unlink(CmdName);
	Cmd.Open(CmdName, CFile::modeCreate | CFile::modeWrite, NULL);
	Cmd.Write("RELOAD\r\n", 8);
	Cmd.Close();
	//MoveFile(WrkName,CmdName);
	for (int loop = 0; loop < 200; loop++) {
		Sleep(250);
		if (JMSShuttingDown) return;
	}
	LogAdd(81, 0, "JMT did not process RELOAD command within 50 seconds !");
	PrevPathCopyErrorFlag = false; // geef ministens 1 error per dag als USB-stick niet ingeplugd is, ook als server blijft draaien
	SendInfo2GeelFlag = true;
}

void CreateAndUpdateCopy(int dummy)
{
	int DBRef, DBRef_Check = -1;
	int DaysPrevious = 0;
	int BakDailyBackupNotBeforeRunning = 0;

	BakHdr = (struct s_BakHdr *)BakHeader;
	double NextSnapShot = 0;
	CString strNextSnapShot;
	BakPeriodicFlag = false;

	LogSpec("JMSCreateAndUpdateCopy", "C"); // als er nu een Logging was, dan was dit een crash !!!
	LogAdd(0, 1, "CreateAndUpdateCopy : Starting-up");
	BakFile.Abort();

	srand((unsigned)time(NULL));
	bool PreMountBusy = true;
	int PreMountBusyWait = 0;
	while (PreMountBusy) {
		if (JMSShuttingDown) return;
		PreMountBusy = false;
		for (int file_ix = 0; file_ix < MAX_SYSFILE; file_ix++) {
			if (Sys[file_ix].PreMountBusyFlag) PreMountBusy = true;
		}
		if (PreMountBusy) {
			Sleep(1000);
			theApp.CreateAndUpdateWatchDog = 0;
			PreMountBusyWait++;
			if (PreMountBusyWait % 300 == 0) LogAdd(104, 0, "Waited 300 sec while PreMountBusyFlag ...");
		}
	}

	while (!JMSShuttingDown) {
		LogSpec("JMSCreateAndUpdateCopy", "D"); // wis de logging, de thread is OK and running
		theApp.CreateAndUpdateWatchDog = 0;
		for (int loop = 0; loop < BAK_WAKEUP_INTERVAL; loop++) {
			Sleep(1000);
			if (JMSShuttingDown) break;
		}
		if (JMSShuttingDown) break;
		if (JMSServiceMode) continue;

		COleDateTime dtNow = COleDateTime::GetCurrentTime();
		double now = dtNow.operator double();
		int Days = (int)now;
		double DayPart = now - Days;

		BakSecondsRunning += BAK_WAKEUP_INTERVAL;
		BakSecondsInactive += BAK_WAKEUP_INTERVAL;
		if (DBUpdated) BakSecondsInactive = 0;
		DBUpdated = false;
		strNextSnapShot = theApp.iniFile.getKeyValue("NextSnapShot", "DataBaseSettings");
		if (strNextSnapShot.GetLength()) NextSnapShot = StrToInt((LPCSTR)strNextSnapShot);
		strNextSnapShot = theApp.iniFile.getKeyValue("NextSnapShotMin", "DataBaseSettings");
		if (strNextSnapShot.GetLength()) NextSnapShot += StrToInt((LPCSTR)strNextSnapShot) / 1440.;
		if (NextSnapShot<1 || NextSnapShot>(now + 0.33)) NextSnapShot = now + 0.01; // na 14 minuten een snapshot maken zo snapshot meer dan 8 uur in de toekomst ligt !

		if (BakSecondsRunning % 60 == 0) {
			theApp.ProgDidSomeWork++;
			CString cstr = theApp.iniFile.getKeyValue("ExtendedLogging", "DataBaseSettings");
			if (cstr.GetLength() > 0 && cstr.Left(1) == "1") JmsExtendedLogging = true;
			else JmsExtendedLogging = false;
		}

		if (DaysPrevious != Days && BakSecondsInactive > 3600 && DayPart > 0.052 && (BakSecondsRunning % BAK_PERIODIC_CHECK_INTERVAL) == 0) { // indien na 1u15, én eerste keer vandaag én al 1 uur inactief, en gespreid over uur ...
			if (DaysPrevious) { // was gisteren al opgestart !
				if (DayPart < 0.208) { // herstarten slechts voor 5u, daarna niet meer, maar wel noteren dat nieuwe dag begonnen is !
					AskJmtToReloadSystem();
					// Normaal keert hij hier niet uit terug, tenzij de JMT de CMD niet uitvoert !
				}
				PrevPathCopyErrorFlag = false; // geef minstens 1 error per dag als USB-stick niet ingeplugd is, ook als server blijft draaien
				SendInfo2GeelFlag = true;
			}
			DaysPrevious = (int)now;
		}

		if (DailyBackupRequested && DayPart<0.014 && BakSecondsRunning>BakDailyBackupNotBeforeRunning) { // eerste 20 minuten van de dag 
			BakDailyBackupNotBeforeRunning = BakSecondsRunning + rand() / 10;  // random getal van 0 tot 32767 ... dus maximaal 54 minuten uitstel
		}

		if (Jama360SpilDateTime > 5 && Jama360SpilDateTime<90000 && BakSecondsRunning>BakDailyBackupNotBeforeRunning && BakSecondsInactive > 0 && BakSecondsInactive%BAK_DAILY_BACKUP_INTERVAL == 0) { // er moet al een goede backup in Geel voorhanden zijn !
			if (DailyBackupRequested) {
				CString cstr;
				LogAdd(0, 0, "Start Daily Full Check DB, ShadowCopy & OnlineCopy");
				LogAdd(0, 0, "Start Checking all mounted DataBases");
				for (DBRef = 0; DBRef < DB_MAX; DBRef++) {
					if (DB[DBRef].Id[0]) {
						cstr.Format("EDBCheckCalc for %s", DB[DBRef].Name);
						LogSpec("JMSCreateAndUpdateCopy", (char*)(LPCTSTR)cstr);
						EDBCheckCalc(DBRef, true);
					}
				}
				LogAdd(0, 0, "Ended Checking all mounted DataBases");
				DmpStartedJama360SpilDateTime = Jama360SpilDateTime;
				DmpAll(0); // om zeker de files in Geel up-to-date te maken !
				if (DBUpdated) {
					LogAdd(0, 0, "Terminated [DBUpdated] Daily Full Check DB, ShadowCopy & OnlineCopy");
				}
				else {
					CompareSignaturesDBvsCopy(false); // om te comparen met BAK-files in CopySubdir
					if (DBUpdated) {
						LogAdd(0, 0, "Terminated [DBUpdated] Daily Full Check DB, ShadowCopy & OnlineCopy");
					}
					else {
						CString CustCode = theApp.iniFile.getKeyValue("SerialNr", "JamaSettings").Mid(3, 3).MakeUpper();
						UploadShaToGeel(CustCode);
						LogAdd(0, 0, "Ended Daily Full Check DB, ShadowCopy & OnlineCopy");
						BakDailyBackupNotBeforeRunning = BakSecondsRunning + 3600; // om minstens een uur te wachten voor een nieuwe poging ...
						BakSecondsInactive = 0; // om te zorgen dat de dmpall iets verder niet start (zal dus nog zeker 10 minuten duren voor die komt, geeft server tijd voor SHA te controleren !)
						if ((BakSecondsRunning % BAK_PERIODIC_CHECK_INTERVAL) == 0) BakSecondsRunning += BAK_WAKEUP_INTERVAL; // idem 
					}
				}
				if (DayPart < 0.208) { // Enkel 's nachts doen ...
					CString CustCode = theApp.iniFile.getKeyValue("SerialNr", "JamaSettings").Mid(3, 3).MakeUpper();
					CString PathToGeel = PathJamaRoot + "ToGeel\\";
					CString NFOFileName = PathToGeel + CustCode + "-PC.nfo";
					_unlink(NFOFileName);
					CString Arguments = "/nfo " + NFOFileName;
					::ShellExecute(pMainDlg->GetSafeHwnd(), "open", "msinfo32", Arguments, NULL, SW_HIDE); // kan wel even duren ! 
				}
			}
		}

		if (JMSVersion != 'M' && BakSecondsInactive == BAK_INACTIVE_WRITE_STATS) {
			LogAdd(0, 1, "WriteStatsToDB : Starting");
			for (DBRef = 0; DBRef < DB_MAX; DBRef++) {
				if (DB[DBRef].Id[0]) {
					WriteStatsToDB(DBRef);
				}
			}
		}

		if (JMSVersion != 'M' && PathCopy().GetLength()) {
			if (BakPeriodicFlag || ((BakSecondsRunning + BAK_PERIODIC_CHECK_INTERVAL / 2) % BAK_PERIODIC_CHECK_INTERVAL) == 0) {
				BakPeriodicFlag = false;
				ShadowCopyFullCheck();
			}
			else if (BakSecondsRunning == BAK_FIRST_RUN_TIME || BakSecondsInactive == BAK_INACTIVE_SHADOW_CHECK_INTERVAL) {  // Ofwel de eerste keer, ofwel elke keer wanneer er exact zoveel seconden inactiviteit is ! Dan was er daarvoor ook echt iets veranderd ...
				ShadowCopyWriteUpdates();
			}

			if ((BakSecondsRunning % BAK_PERIODIC_REMOVE_SNAPSHOTS) == 0) {
				RemoveOverdueSnapShotsAndTMPInCopy();
				if (now > NextSnapShot) {

					//Snapshots om 0u, 8u, 10u, 12u, 15u, 18u en 21u
					double DayPart2Add = 0;
					if (DayPart >= 0.875) DayPart2Add = 1.;
					else if (DayPart >= 0.750000) DayPart2Add = 0.875;
					else if (DayPart >= 0.625000) DayPart2Add = 0.75;
					else if (DayPart >= 0.500000) DayPart2Add = 0.625;
					else if (DayPart >= 0.416666) DayPart2Add = 0.500;
					else if (DayPart >= 0.333333) DayPart2Add = 0.416666;
					else DayPart2Add = 0.333333;
					NextSnapShot = Days + DayPart2Add;

					int TTL = 2 * 1440; // standaard TTL is 2 dagen ...
					if (DayPart >= 0.500000 && DayPart <= 0.541) TTL = 8 * 1440;  // Tussen 12u en 13u -> 8 dagen

					int NextSnapShotNewYear = 0, NextSnapShotNewMonth = 0, NextSnapShotNewWeek = 0, NextSnapShotNewDay = 0;
					CString strNextSnapShotNewYear, strNextSnapShotNewMonth, strNextSnapShotNewWeek, strNextSnapShotNewDay;

					strNextSnapShotNewDay = theApp.iniFile.getKeyValue("NextSnapShotNewDay", "DataBaseSettings");
					if (strNextSnapShotNewDay.GetLength()) NextSnapShotNewDay = StrToInt((LPCSTR)strNextSnapShotNewDay);
					if ((int)now >= NextSnapShotNewDay) {
						TTL = 15 * 1440; // Tussen 0u en 0u14 -> 15 dagen
						NextSnapShotNewDay = (int)now + 1;
					}
					strNextSnapShotNewWeek = theApp.iniFile.getKeyValue("NextSnapShotNewWeek", "DataBaseSettings");
					if (strNextSnapShotNewWeek.GetLength()) NextSnapShotNewWeek = StrToInt((LPCSTR)strNextSnapShotNewWeek);
					if ((int)now >= NextSnapShotNewWeek) {
						TTL = 100 * 1440; // De backup eerste weekdag wordt 100 dagen bijgehouden
						NextSnapShotNewWeek = (int)now - dtNow.GetDayOfWeek() + 2 + 7;
					}
					strNextSnapShotNewMonth = theApp.iniFile.getKeyValue("NextSnapShotNewMonth", "DataBaseSettings");
					if (strNextSnapShotNewMonth.GetLength()) NextSnapShotNewMonth = StrToInt((LPCSTR)strNextSnapShotNewMonth);
					if ((int)now >= NextSnapShotNewMonth) {
						TTL = (365 + 32) * 1440; // De backup van de eerste van de maand wordt 12 maand + 1 bijgehouden
						int NextYear = dtNow.GetYear();
						int NextMonth = dtNow.GetMonth() + 1;
						if (NextMonth > 12) {
							NextMonth = 1;
							NextYear++;
						}
						NextSnapShotNewMonth = (int)COleDateTime(NextYear, NextMonth, 1, 0, 0, 1).operator DOUBLE();
					}
					strNextSnapShotNewYear = theApp.iniFile.getKeyValue("NextSnapShotNewYear", "DataBaseSettings");
					if (strNextSnapShotNewYear.GetLength()) NextSnapShotNewYear = StrToInt((LPCSTR)strNextSnapShotNewYear);
					if ((int)now >= NextSnapShotNewYear) {
						TTL = 6 * 365 * 1440; // De backup van 1 januari wordt 6 jaar bijgehouden ...
						NextSnapShotNewYear = (int)COleDateTime(dtNow.GetYear() + 1, 1, 1, 0, 0, 1).operator DOUBLE();
					}

					strNextSnapShot.Format("%d", (int)NextSnapShot);
					theApp.iniFile.setKey(strNextSnapShot, "NextSnapShot", "DataBaseSettings");
					strNextSnapShot.Format("%d", (int)((NextSnapShot - (int)NextSnapShot)*1440.));
					theApp.iniFile.setKey(strNextSnapShot, "NextSnapShotMin", "DataBaseSettings");

					if (NextSnapShotNewDay > 0) {
						strNextSnapShotNewDay.Format("%d", NextSnapShotNewDay);
						theApp.iniFile.setKey(strNextSnapShotNewDay, "NextSnapShotNewDay", "DataBaseSettings");
					}
					if (NextSnapShotNewWeek > 0) {
						strNextSnapShotNewWeek.Format("%d", NextSnapShotNewWeek);
						theApp.iniFile.setKey(strNextSnapShotNewWeek, "NextSnapShotNewWeek", "DataBaseSettings");
					}
					if (NextSnapShotNewMonth > 0) {
						strNextSnapShotNewMonth.Format("%d", NextSnapShotNewMonth);
						theApp.iniFile.setKey(strNextSnapShotNewMonth, "NextSnapShotNewMonth", "DataBaseSettings");
					}
					if (NextSnapShotNewYear > 0) {
						strNextSnapShotNewYear.Format("%d", NextSnapShotNewYear);
						theApp.iniFile.setKey(strNextSnapShotNewYear, "NextSnapShotNewYear", "DataBaseSettings");
					}

					CFileFind SysFinder;
					CString File2Find = PathCopy() + "FAS\\SYS.*";
					BOOL bSysWorking = SysFinder.FindFile(File2Find);
					while (bSysWorking) {
						if (JMSShuttingDown) break;
						bSysWorking = SysFinder.FindNextFile();
						if (SysFinder.IsDirectory()) continue;
						CString SysName = SysFinder.GetFileName();
						if (SysName.GetLength() != 7) continue;  // enkel namen met op dit niveau SYS.xxx waarbij xxx de EXT is

						CString Ext = SysName.Right(3).MakeUpper();

						int file_ix = SysOpen((char *)(LPCTSTR)Ext, false, true);
						if (file_ix == -1) continue;
						CreateSnapShot((char*)(LPCTSTR)Sys[file_ix].Ext, TTL, false); // overbodige files niet meenemen  
						SysClose(file_ix);
					}
					SysFinder.Close();

					CreateSnapShot("", TTL, false); // Van de backup-files prog, ftkopie, kassa, .... 

				}
			}
		}

		if (Jama360SpilDateTime >= 0) {  // zo geen connectie geweest, dan staat deze op -1 !
			if (BakSecondsRunning == BAK_FIRST_RUN_TIME || BakSecondsInactive == BAK_INACTIVE_ONLINE_CHECK_INTERVAL || (BakSecondsRunning % BAK_PERIODIC_CHECK_INTERVAL) == 0) {
				// Na 10 minuten geen wijziging of om het uur
				if (SendInfo2GeelFlag && DayPart > 0.208) {  // Pas na 5u doorsturen ! Dan is alle maintenance gedaan ...
					SendInfo2Geel();
					SendInfo2GeelFlag = false;
				}
				if (Jama360SpilDateTime >= 0 && Jama360SpilDateTime < 90000) { //zo geen BACKUP nodig, dan op >=90000
					if (Jama360SpilDateTime > 0.001 || BakSecondsRunning > (3 * 3600)) { // de eerste 3 uren bij nieuwe installatie geen upload doen !
						DmpStartedJama360SpilDateTime = Jama360SpilDateTime;
						DmpAll(0); // binnen deze thread doen, dus controle op DmpStartedJama360SpilDateTime==-1 is niet meer nodig
					}
				}
			}
		}
	}
}

// Add to (and create) DMP-file

#define MAX_DMP_LEN 5*1048576           // 5 Mbytes uncompressed -> 3  MB compressed ?

int DmpUpdCount, DmpDelCount, DmpFilCount;
CFile DmpFile;
int DmpSeqNr;
double DmpDateTime;

// volgende structs komen ook voor in de Dmp2Copy ... pas ze zonodig ook daar aan !
unsigned char DmpHeader[512];
struct s_DmpHdr {
	unsigned char Type;
	char Version;
	long DmpPos;
	long DmpLenTotUsed;
	int  RecCnt;
} *DmpHdr;

struct s_DmpRec {   // na deze lead-in komt het Frame met Compressed Rec Dump 
	char Type;
	short unsigned Len; // len van de RecDump (die na deze lead-in komt)
	long RecNr;
	double DateTimeUpdated;
	short int ChangedBy;
} DmpRec = { 'R' };

struct s_DmpRhd { // fixed length 
	char Type;
	unsigned char StuNr;
	unsigned short RecLen; // len van records
	unsigned RecCount;
	FILETIME LastFileUpdateTime;
	char OrigDBName[48];
} DmpRhd = { 'H' };

struct s_DmpDel {  // fixed length 
	char Type;
	long RecNr;
	double DateTimeUpdated;
	short int ChangedBy;
} DmpDel = { 'D' };

struct s_DmpFil {  // na deze lead-in komen 2 frames, het eerste de FileName en het 2-de de Compressed File Dump
	char Type;
	unsigned Len;  // len van de Compressed File Dump (die na deze lead-in komt)
	unsigned origLen;   // is 0 zo UnCompressed
	FILETIME LastWriteTime;
	short unsigned FileNameLen;
} DmpFil = { 'F' };

unsigned char DmpBuf[BUF_LEN + 50];
unsigned char DmpCompressBuf[BUF_LEN + 50];

void DmpClose()
{
	bool DelFlag = false;
	CString DelFilePath;

	DmpHdr->DmpLenTotUsed = (long)DmpFile.Seek(0, CFile::current);
	if (DmpHdr->DmpLenTotUsed == DmpHdr->DmpPos) {
		DelFlag = true;
		DelFilePath = DmpFile.GetFilePath();
	}
	DmpFile.Seek(0, FILE_BEGIN);
	DmpFile.Write(DmpHeader, sizeof(DmpHeader));
	DmpFile.Close();
	if (DelFlag) {
		_unlink(DelFilePath);
		DmpSeqNr--;
	}
}

bool DmpOpen()
{
	CString PathDMP = PathTempRoot + "Dump\\";
	if (GetFileAttributes(PathDMP) == INVALID_FILE_ATTRIBUTES) CreateDirectory(PathDMP, NULL);

	CString DmpFileName;
	DmpSeqNr++;
	DmpFileName.Format("%sJMS-%s-%03d-%022.16f-%022.16f", PathDMP, strJama360SerialNr.Mid(3, 3), DmpSeqNr, DmpStartedJama360SpilDateTime, DmpDateTime);
	DmpFileName.Replace(".", "_");
	DmpFileName.Replace(",", "_");
	DmpFileName += ".dmp";
	if (!DmpFile.Open(DmpFileName, CFile::modeReadWrite | CFile::modeCreate, 0)) { // create file
		LogAdd(0, 0, "Cannot create DMP-file", DmpFileName);
		return false;
	}

	// fill in header
	memset(DmpHeader, 0x00, sizeof(DmpHeader));
	DmpHdr = (struct s_DmpHdr *)DmpHeader;
	DmpHdr->Type = 0xFD; // fas Dump
	DmpHdr->Version = 01;

	DmpFile.Seek(0L, 0);
	DmpFile.Write(DmpHeader, 512);
	DmpHdr->DmpPos = (long)DmpFile.Seek(0L, CFile::current);
	DmpHdr->DmpLenTotUsed = DmpHdr->DmpPos;

	return true;
}

void WriteDmpRhd(int DBRef, int TabIx)
{
	// zoek de LastFileUpdateTime
	double DBDateTimeUpdated = -1000;
	for (int Ix = 0; Ix < DB[DBRef].TabCnt; Ix++) {
		if (DB[DBRef].Tab[Ix].StuNr > 0 && DB[DBRef].Tab[Ix].DateTimeUpdate > DBDateTimeUpdated) DBDateTimeUpdated = DB[DBRef].Tab[Ix].DateTimeUpdate;
	}
	COleDateTime dt((DATE)DBDateTimeUpdated);
	SYSTEMTIME sysTime;
	dt.GetAsSystemTime(sysTime);
	// Get the timezone info.
	TIME_ZONE_INFORMATION TimeZoneInfo;
	GetTimeZoneInformation(&TimeZoneInfo);
	// Convert local time to UTC.
	SYSTEMTIME GmtTime = { 0 };
	TzSpecificLocalTimeToSystemTime(&TimeZoneInfo, &sysTime, &GmtTime);
	//FileTime must be in UTC format (therfor convertion)
	SystemTimeToFileTime(&GmtTime, &DmpRhd.LastFileUpdateTime);
	// filled DmpRhd.LastFileUpdateTime
	sprintf_s(DmpRhd.OrigDBName, sizeof(DmpRhd.OrigDBName), "%s", DB[DBRef].Name);
	DmpRhd.StuNr = DB[DBRef].Tab[TabIx].StuNr;
	DmpRhd.RecLen = DB[DBRef].Tab[TabIx].StructLen - DB[DBRef].Tab[TabIx].EleInf[1].FldLen;
	DmpRhd.RecCount = DB[DBRef].Tab[TabIx].LastRec;
	DmpFile.Write(&DmpRhd, sizeof(struct s_DmpRhd));
}

void DmpFas(int DBRef, double SpilDateTime)
{
	int StuNr;
	long DmpLenTot;
	unsigned long retlen;
	int RecNr;
	JET_ERR _jeterr;
	int DmpUpdCountOnEntry = DmpUpdCount;
	int DmpDelCountOnEntry = DmpDelCount;

	DmpLenTot = (long)DmpFile.Seek(0L, CFile::current);
	for (int TabIx = 0; TabIx < DB[DBRef].TabCnt; TabIx++) {
		StuNr = DB[DBRef].Tab[TabIx].StuNr;
		if (StuNr == 0) continue;

		// find recs that are updated after SpilDateTime
		RecNr = 1;
		JetCallVoidRet(3201, JetSetCurrentIndex4(DB[DBRef].SesId[0], DB[DBRef].Tab[TabIx].Tid[0], "", (JET_INDEXID*)DB[DBRef].Tab[TabIx].Idx[StuDatIx].rgbIndexId[0], 0, 0));
		JetCallVoidRet(3202, JetMakeKey(DB[DBRef].SesId[0], DB[DBRef].Tab[TabIx].Tid[0], &SpilDateTime, DB[DBRef].Tab[TabIx].Col[StuDatId].Len, JET_bitNewKey));
		JetCallVoidRet(3210, JetMakeKey(DB[DBRef].SesId[0], DB[DBRef].Tab[TabIx].Tid[0], &RecNr, sizeof(RecNr), 0));
		_jeterr = JetSeek(DB[DBRef].SesId[0], DB[DBRef].Tab[TabIx].Tid[0], JET_bitSeekGE);

		// zo er ge-update records zijn, dan de DmpRhd wegschrijven ...
		bool DmpRhdWritten = false;
		// nu de records adden ...
		while (_jeterr == JET_wrnSeekNotEqual || _jeterr == JET_errSuccess) {
			if (JMSShuttingDown) break;
			if (!DmpRhdWritten) {
				DmpRhdWritten = true;
				WriteDmpRhd(DBRef, TabIx);
			}
			JetCallVoidRet(3203, JetRetrieveColumn(DB[DBRef].SesId[0], DB[DBRef].Tab[TabIx].Tid[0], DB[DBRef].Tab[TabIx].Col[StuRecId].Cid[0], &DmpRec.RecNr, DB[DBRef].Tab[TabIx].Col[StuRecId].Len, &retlen, 0, 0));
			JetCallVoidRet(3204, JetRetrieveColumn(DB[DBRef].SesId[0], DB[DBRef].Tab[TabIx].Tid[0], DB[DBRef].Tab[TabIx].Col[StuChgId].Cid[0], &DmpRec.ChangedBy, DB[DBRef].Tab[TabIx].Col[StuChgId].Len, &retlen, 0, 0));
			JetCallVoidRet(3204, JetRetrieveColumn(DB[DBRef].SesId[0], DB[DBRef].Tab[TabIx].Tid[0], DB[DBRef].Tab[TabIx].Col[StuDatId].Cid[0], &DmpRec.DateTimeUpdated, DB[DBRef].Tab[TabIx].Col[StuDatId].Len, &retlen, 0, 0));
			JetCallVoidRet(3204, JetRetrieveColumn(DB[DBRef].SesId[0], DB[DBRef].Tab[TabIx].Tid[0], DB[DBRef].Tab[TabIx].Col[StuValId].Cid[0], DmpBuf, BUF_LEN, &retlen, 0, 0));
			unsigned char *p = DmpBuf;
			int _retlen = retlen;
			while (_retlen--) *p++ = (*p >> 4) | (*p << 4);
			DmpRec.Len = RepCompress(DmpBuf, DmpCompressBuf, retlen, sizeof(DmpCompressBuf) - 5);
			DmpFile.Write(&DmpRec, sizeof(struct s_DmpRec));
			DmpFile.Write(DmpCompressBuf, DmpRec.Len);
			DmpLenTot += (sizeof(struct s_DmpRec) + DmpRec.Len);
			DmpUpdCount++;
			_jeterr = JetMove(DB[DBRef].SesId[0], DB[DBRef].Tab[TabIx].Tid[0], JET_MoveNext, 0);
			if (DmpLenTot > MAX_DMP_LEN) {
				DmpClose();
				DmpOpen(); DmpLenTot = 0;
			}
		}

		// find recs that are deleted after SpilDateTime
		RecNr = 1; RecDump.Used = 0; memset(RecDump.RecBuf, 0, BUF_LEN);
		JetCallVoidRet(3225, JetSetCurrentIndex4(DB[DBRef].SesId[0], DB[DBRef].Tab[DelId].Tid[0], "", (JET_INDEXID*)DB[DBRef].Tab[DelId].Idx[DelDatIx].rgbIndexId[0], 0, 0));
		JetCallVoidRet(3226, JetMakeKey(DB[DBRef].SesId[0], DB[DBRef].Tab[DelId].Tid[0], &DB[DBRef].Tab[TabIx].StuNr, DB[DBRef].Tab[DelId].Col[DelStuId].Len, JET_bitNewKey));
		JetCallVoidRet(3224, JetMakeKey(DB[DBRef].SesId[0], DB[DBRef].Tab[DelId].Tid[0], &SpilDateTime, DB[DBRef].Tab[DelId].Col[DelDatId].Len, 0));
		JetCallVoidRet(3227, JetMakeKey(DB[DBRef].SesId[0], DB[DBRef].Tab[DelId].Tid[0], &RecNr, DB[DBRef].Tab[DelId].Col[DelRecId].Len, 0));
		_jeterr = JetSeek(DB[DBRef].SesId[0], DB[DBRef].Tab[DelId].Tid[0], JET_bitSeekGE);
		while (_jeterr == JET_wrnSeekNotEqual || _jeterr == JET_errSuccess) {
			if (JMSShuttingDown) break;
			unsigned long retreclen = 0;
			short int StuNrFound;
			JetCallVoidRet(3228, JetRetrieveColumn(DB[DBRef].SesId[0], DB[DBRef].Tab[DelId].Tid[0], DB[DBRef].Tab[DelId].Col[DelStuId].Cid[0], &StuNrFound, DB[DBRef].Tab[DelId].Col[DelStuId].Len, &retreclen, 0, 0));
			if (StuNrFound != DB[DBRef].Tab[TabIx].StuNr) {
				break;
			}
			if (!DmpRhdWritten) {
				DmpRhdWritten = true;
				WriteDmpRhd(DBRef, TabIx);
			}
			JetCallVoidRet(3229, JetRetrieveColumn(DB[DBRef].SesId[0], DB[DBRef].Tab[DelId].Tid[0], DB[DBRef].Tab[DelId].Col[DelRecId].Cid[0], &DmpDel.RecNr, DB[DBRef].Tab[DelId].Col[DelRecId].Len, &retreclen, 0, 0));
			DmpDel.ChangedBy = 0;
			JetCallVoidRet(3231, JetRetrieveColumn(DB[DBRef].SesId[0], DB[DBRef].Tab[DelId].Tid[0], DB[DBRef].Tab[DelId].Col[DelChgId].Cid[0], &DmpDel.ChangedBy, DB[DBRef].Tab[DelId].Col[DelChgId].Len, &retlen, 0, 0));
			JetCallVoidRet(3232, JetRetrieveColumn(DB[DBRef].SesId[0], DB[DBRef].Tab[DelId].Tid[0], DB[DBRef].Tab[DelId].Col[DelDatId].Cid[0], &DmpDel.DateTimeUpdated, DB[DBRef].Tab[DelId].Col[DelDatId].Len, &retlen, 0, 0));
			TRACE("StuNr=%d   RecNr=%d\n", StuNrFound, DmpDel.RecNr);
			DmpFile.Write(&DmpDel, sizeof(struct s_DmpDel));
			DmpLenTot += sizeof(struct s_DmpDel);
			DmpDelCount++;
			_jeterr = JetMove(DB[DBRef].SesId[0], DB[DBRef].Tab[DelId].Tid[0], JET_MoveNext, 0);
			if (DmpLenTot > MAX_DMP_LEN) {
				DmpClose();
				DmpOpen(); DmpLenTot = 0;
			}

		}
		if (!DmpRhdWritten && SpilDateTime <= 0.) {  // in geval van nieuwe FSD en lege file, dan toch header uitschrijven zodat Jama360 een nieuwe lege file zal aanmaken !
			DmpRhdWritten = true;
			WriteDmpRhd(DBRef, TabIx);
		}
	}
	CString cstr;
	cstr.Format("Checking %s : found %d updated and %d deleted records", DB[DBRef].Name, DmpUpdCount - DmpUpdCountOnEntry, DmpDelCount - DmpDelCountOnEntry);
	LogAdd(0, 1, cstr);
	return;
}

bool DmpFtKopie()
{
	COleDateTime now = COleDateTime::GetCurrentTime();
	int DmpLenTot = (long)DmpFile.Seek(0L, CFile::current);

	// Convert DmpStartedJama360SpilDateTime tot FILETIME
	COleDateTime DmpSpil = COleDateTime((DATE)DmpStartedJama360SpilDateTime);
	SYSTEMTIME DmpSystemTime;
	DmpSpil.GetAsSystemTime(DmpSystemTime);
	// Get the timezone info.
	TIME_ZONE_INFORMATION TimeZoneInfo;
	GetTimeZoneInformation(&TimeZoneInfo);
	// Convert local time to UTC.
	SYSTEMTIME GmtTime = { 0 };
	TzSpecificLocalTimeToSystemTime(&TimeZoneInfo, &DmpSystemTime, &GmtTime);
	//FileTime must be in UTC format (therfor convertion)
	FILETIME DmpFileTime;
	SystemTimeToFileTime(&GmtTime, &DmpFileTime);

	for (int yr = now.GetYear(); yr > now.GetYear() - 8; yr--) {
		if (yr < DmpSpil.GetYear()) break;

		CFileFind FileFinder;
		CString File2Find;
		File2Find.Format("%sFtKopie\\*.%02d*", PathJamaRoot, yr % 100);
		int PathJamaRootLen = PathJamaRoot.GetLength();
		BOOL bWorking = FileFinder.FindFile(File2Find);
		while (bWorking) {
			bWorking = FileFinder.FindNextFile();
			if (FileFinder.IsDirectory()) continue;

			FILETIME ftFileLastUpdated;
			if (FileFinder.GetLastWriteTime(&ftFileLastUpdated)) {
				if (ftFileLastUpdated.dwHighDateTime > DmpFileTime.dwHighDateTime || (ftFileLastUpdated.dwHighDateTime == DmpFileTime.dwHighDateTime && ftFileLastUpdated.dwLowDateTime > DmpFileTime.dwLowDateTime)) {
					CString DmpFileName = FileFinder.GetFilePath().Mid(PathJamaRootLen);
					DmpFil.FileNameLen = DmpFileName.GetLength();
					CFile FtKopieFile;
					if (!FtKopieFile.Open(FileFinder.GetFilePath(), CFile::modeRead, NULL)) {
						LogAdd(54, 0, "Cannot Dump", FileFinder.GetFilePath());
						continue;
					}
					int buflen = (int)FileFinder.GetLength() + 100;
					char *b = new char[buflen];
					char *c = new char[buflen];
					int retlen = FtKopieFile.Read(b, (int)FileFinder.GetLength());
					FtKopieFile.Close();
					DmpFil.origLen = retlen;
					retlen = RepCompress(b, c, retlen, buflen - 5);
					if (retlen <= 0) { retlen = -retlen; DmpFil.origLen = 0; }
					DmpFil.Len = retlen;
					memcpy(&DmpFil.LastWriteTime, &ftFileLastUpdated, sizeof(FILETIME));
					DmpFile.Write(&DmpFil, sizeof(struct s_DmpFil));
					DmpFile.Write(DmpFileName, DmpFil.FileNameLen);
					if (DmpFil.origLen == 0) DmpFile.Write(b, DmpFil.Len);
					else DmpFile.Write(c, DmpFil.Len);
					delete c;
					delete b;
					DmpFilCount++; DmpLenTot += (sizeof(struct s_DmpFil) + DmpFil.FileNameLen + DmpFil.Len);
					if (DmpLenTot > MAX_DMP_LEN) {
						DmpClose();
						DmpOpen(); DmpLenTot = 0;
					}
				}
			}
		}
		FileFinder.Close();
	}
	return true;
}

bool DmpSubDir(CString JamaSubDir)
{
	COleDateTime now = COleDateTime::GetCurrentTime();
	int DmpLenTot = (long)DmpFile.Seek(0L, CFile::current);

	// alle namen in lowercase !

	CString DmpReplaceDummyFiles = "jamares.exe|ese.dll|xlsgen.dll|jamap.dll|mailbee.net.dll|runonce.kas|";
	CString DmpExcludeFiles = "kastest.dat|kastest.bat|kastest.exe|dotNetFx40_Full_setup.exe|vcredist_x86.exe|";

	// Convert DmpStartedJama360SpilDateTime tot FILETIME
	COleDateTime DmpSpil = COleDateTime((DATE)DmpStartedJama360SpilDateTime);
	SYSTEMTIME DmpSystemTime;
	DmpSpil.GetAsSystemTime(DmpSystemTime);
	// Get the timezone info.
	TIME_ZONE_INFORMATION TimeZoneInfo;
	GetTimeZoneInformation(&TimeZoneInfo);
	// Convert local time to UTC.
	SYSTEMTIME GmtTime = { 0 };
	TzSpecificLocalTimeToSystemTime(&TimeZoneInfo, &DmpSystemTime, &GmtTime);
	//FileTime must be in UTC format (therfor convertion)
	FILETIME DmpFileTime;
	SystemTimeToFileTime(&GmtTime, &DmpFileTime);

	int DirNesting = 0;
	CFileFind FileFinder[10]; // maximaal 10 niveau's diep
	CString File2Find[10];
	BOOL bWorking[10];
	File2Find[0].Format("%s%s\\*.*", PathJamaRoot, JamaSubDir);
	int PathJamaRootLen = PathJamaRoot.GetLength();
	bWorking[0] = FileFinder[0].FindFile(File2Find[0]);
	while (DirNesting >= 0) {
		while (bWorking[DirNesting]) {
			bWorking[DirNesting] = FileFinder[DirNesting].FindNextFile();
			if (FileFinder[DirNesting].IsDots()) continue;

			if (FileFinder[DirNesting].IsDirectory()) {
				if (DirNesting == 9) continue;

				DirNesting++;
				File2Find[DirNesting] = FileFinder[DirNesting - 1].GetFilePath() + "\\*.*";
				bWorking[DirNesting] = FileFinder[DirNesting].FindFile(File2Find[DirNesting]);
			}
			else {
				if (FileFinder[DirNesting].GetLength() == 0) continue;
				CString Ext = FileFinder[DirNesting].GetFileName();
				if (Ext.GetLength() < 4) Ext = "";
				else Ext = Ext.Right(3);
				Ext.MakeLower();
				if (Ext.Compare("zip") == 0) continue;
				if (Ext.Compare("lzh") == 0) continue;
				if (Ext.Compare("prv") == 0) continue;
				if (Ext.Compare("old") == 0) continue;
				if (Ext.Compare(".ok") == 0) continue;
				if (Ext.Compare("flg") == 0) continue;
				if (Ext.Compare("sta") == 0) continue;

				CString FileName = FileFinder[DirNesting].GetFileName() + "|";
				FileName.MakeLower();
				bool DumpAsDummy = false;
				if (FileName.Find("jmc.exe") < 0 && Ext.Compare("exe") == 0) { // alle exe's behalve jmc.exe checken op grootte
					if (FileFinder[DirNesting].GetLength() > 6000000) DumpAsDummy = true; // boven 6mb als dummy backuppen
				}

				if (DmpExcludeFiles.Find(FileName) >= 0) continue; // excluded file

				FILETIME ftFileLastUpdated;
				if (FileFinder[DirNesting].GetLastWriteTime(&ftFileLastUpdated)) {
					if (FileFinder[DirNesting].IsArchived() || ftFileLastUpdated.dwHighDateTime > DmpFileTime.dwHighDateTime || (ftFileLastUpdated.dwHighDateTime == DmpFileTime.dwHighDateTime && ftFileLastUpdated.dwLowDateTime > DmpFileTime.dwLowDateTime)) {
						CString DmpFileName = FileFinder[DirNesting].GetFilePath().Mid(PathJamaRootLen);
						DmpFil.FileNameLen = DmpFileName.GetLength();

						int retlen, buflen;
						char *b, *c;
						b = c = NULL;
						try {
							if (DumpAsDummy || DmpReplaceDummyFiles.Find(FileName) >= 0) {
								retlen = 6;
								buflen = retlen + 100;
								b = new char[buflen];
								c = new char[buflen];
								memcpy(b, "Dummy", 6);
							}
							else {
								CFile DmpSubDirFile;
								if (!DmpSubDirFile.Open(FileFinder[DirNesting].GetFilePath(), CFile::modeRead, NULL)) {
									LogAdd(0, 1, "Cannot Dump", FileFinder[DirNesting].GetFilePath());
									retlen = 5;
									buflen = retlen + 100;
									b = new char[buflen];
									c = new char[buflen];
									memcpy(b, "Busy", 5);
								}
								else {
									buflen = (int)FileFinder[DirNesting].GetLength() + 100;
									b = new char[buflen];
									c = new char[buflen];
									retlen = DmpSubDirFile.Read(b, (int)FileFinder[DirNesting].GetLength());
									DmpSubDirFile.Close();
								}
							}
							// files met archive on worden altijd gedumpt naar Jama360
							SetFileAttributes(FileFinder[DirNesting].GetFilePath(), GetFileAttributes(FileFinder[DirNesting].GetFilePath()) & ~(CFile::archive));

							DmpFil.origLen = retlen;
							retlen = RepCompress(b, c, retlen, buflen - 5);
							if (retlen <= 0) { retlen = -retlen; DmpFil.origLen = 0; }
							DmpFil.Len = retlen;
							memcpy(&DmpFil.LastWriteTime, &ftFileLastUpdated, sizeof(FILETIME));
							DmpFile.Write(&DmpFil, sizeof(struct s_DmpFil));
							DmpFile.Write(DmpFileName, DmpFil.FileNameLen);
							if (DmpFil.origLen == 0) DmpFile.Write(b, DmpFil.Len);
							else DmpFile.Write(c, DmpFil.Len);
							DmpFilCount++; DmpLenTot += (sizeof(struct s_DmpFil) + DmpFil.FileNameLen + DmpFil.Len);
							if (DmpLenTot > MAX_DMP_LEN) {
								DmpClose();
								DmpOpen(); DmpLenTot = 0;
							}
						}
						catch (...) {
							LogAdd(112, 0, "Exception in DmpSubDir while dumping", DmpFileName);
						}
						if (c != NULL) delete[] c;
						if (b != NULL) delete[] b;
					}
				}
			}
		}
		FileFinder[DirNesting].Close();
		DirNesting--;
	}

	return true;
}

bool DmpSysFile(int file_ix)
{
	int buflen = Sys[file_ix].Length + 100;
	char *c = new char[buflen];
	DmpFil.origLen = Sys[file_ix].Length;
	int retlen = RepCompress(Sys[file_ix].Buf, c, Sys[file_ix].Length, buflen - 5);
	if (retlen < 0) { retlen = -retlen; DmpFil.origLen = 0; }
	DmpFil.Len = retlen;
	// Convert DateTimeLastWrite tot FILETIME !
	COleDateTime dt((DATE)Sys[file_ix].DateTimeLastWrite);
	SYSTEMTIME sysTime;
	dt.GetAsSystemTime(sysTime);
	// Get the timezone info.
	TIME_ZONE_INFORMATION TimeZoneInfo;
	GetTimeZoneInformation(&TimeZoneInfo);
	// Convert local time to UTC.
	SYSTEMTIME GmtTime = { 0 };
	TzSpecificLocalTimeToSystemTime(&TimeZoneInfo, &sysTime, &GmtTime);
	//FileTime must be in UTC format (therfor convertion)
	SystemTimeToFileTime(&GmtTime, &DmpFil.LastWriteTime);
	DmpFil.FileNameLen = 7;
	DmpFile.Write(&DmpFil, sizeof(struct s_DmpFil));
	DmpFile.Write(Sys[file_ix].Name.Right(7), 7);
	if (DmpFil.origLen == 0) DmpFile.Write(Sys[file_ix].Buf, DmpFil.Len);
	else DmpFile.Write(c, DmpFil.Len);
	delete c;
	DmpFilCount++;
	return true;
}

bool DmpFsdFile(int DBRef)
{
	// include new version in DMP-file, this indicates that BAK file on server must be deleted (new layout ?)
	int buflen = Fsd[DBRef].len + 100;
	char *c = new char[buflen];

	DmpFil.origLen = Fsd[DBRef].len;
	int retlen = RepCompress(Fsd[DBRef].buf, c, Fsd[DBRef].len, buflen - 5);
	if (retlen < 0) { retlen = -retlen; DmpFil.origLen = 0; }
	DmpFil.Len = retlen;
	// Convert DateTimeLastWrite tot FILETIME !
	COleDateTime dt((DATE)Fsd[DBRef].DateTimeUpdated);
	SYSTEMTIME sysTime;
	dt.GetAsSystemTime(sysTime);
	// Get the timezone info.
	TIME_ZONE_INFORMATION TimeZoneInfo;
	GetTimeZoneInformation(&TimeZoneInfo);
	// Convert local time to UTC.
	SYSTEMTIME GmtTime = { 0 };
	TzSpecificLocalTimeToSystemTime(&TimeZoneInfo, &sysTime, &GmtTime);
	//FileTime must be in UTC format (therfor convertion)
	SystemTimeToFileTime(&GmtTime, &DmpFil.LastWriteTime);
	CString FsdFileName = DB[DBRef].Name;
	FsdFileName += ".fsd";
	DmpFil.FileNameLen = FsdFileName.GetLength();
	DmpFile.Write(&DmpFil, sizeof(struct s_DmpFil));
	DmpFile.Write(FsdFileName, DmpFil.FileNameLen);
	if (DmpFil.origLen == 0) DmpFile.Write(Fsd[DBRef].buf, DmpFil.Len);
	else DmpFile.Write(c, DmpFil.Len);
	delete c;
	DmpFilCount++;
	return true;
}

/* niet meer nodig, werken nu met datatime 09/01/2011
bool CheckOutdatedDmpFsd(int DBRef)
{
  bool ReWriteFsd=true;
  CString FsdFilePath;

  CString PathDMP = PathTempRoot + "Dmp\\";
  FsdFilePath.Format("%sfsd\\%s.fsd",PathDMP,DB[DBRef].Name);
  CFile fsdfil;
  if (fsdfil.Open(FsdFilePath,CFile::shareDenyNone|CFile::modeRead,NULL)) {
	ReWriteFsd=false;
	int rdlen=fsdfil.Read(DmpFsdCmpBuf,sizeof(DmpFsdCmpBuf));
	SetFileLastWriteTimeFromDB(fsdfil.m_hFile,DBRef);
	fsdfil.Close();
	if (rdlen==sizeof(DmpFsdCmpBuf)) {
	  LogAdd(51,0,"Sizeof FSD-file on disk too long for DmpFsdCmpBuf",FsdFilePath);
	  ReWriteFsd=true;
	}
	else if (memcmp(Fsd[DBRef].buf,DmpFsdCmpBuf,Fsd[DBRef].len) || Fsd[DBRef].len!=rdlen) ReWriteFsd=true;
	if (ReWriteFsd) _unlink(FsdFilePath);
  }
  return ReWriteFsd;
}
*/

void DmpAll(int dummy)
{
	bool CompleteRetransmit = false;
	CString File2Find;
	CFileFind DBfinder;
	COleDateTime dt;
	SYSTEMTIME GmtTime = { 0 };

	if (Jama360SpilDateTime == 1.) {
		Jama360SpilDateTime = 0.;
		CompleteRetransmit = true;
		LogAdd(90, 0, "Update OnLine-Copy : Restarting from scratch after mismatch on Jama360-server !");
	}
	else LogAdd(0, 0, "Update OnLine-Copy : Starting");
	DmpDateTime = COleDateTime::GetCurrentTime().operator double();
	DmpSeqNr = 0;
	CString CountStr, cstr, JamaSubDirs;
	CString PathDMP = PathTempRoot + "Dump\\";

	// Delete DMP-files from previous run that were not uploaded !
	CFileFind DmpFinder;
	CString Dmp2Find = PathDMP + "*.dmp";
	BOOL bWorking = DmpFinder.FindFile(Dmp2Find);
	while (bWorking) {
		bWorking = DmpFinder.FindNextFile();
		if (DmpFinder.IsDirectory()) continue;
		if (_unlink(DmpFinder.GetFilePath()) == 0) { // succesfull delete
			LogAdd(0, 0, "DMP-file deleted", DmpFinder.GetFileName());
		}
		else LogAdd(0, 0, "Cannot delete DMP-file", DmpFinder.GetFilePath());
	}
	DmpFinder.Close();
	// Delete DMP-files from previous run that were not uploaded !
	Dmp2Find = PathDMP + "*.zip";
	bWorking = DmpFinder.FindFile(Dmp2Find);
	while (bWorking) {
		bWorking = DmpFinder.FindNextFile();
		if (DmpFinder.IsDirectory()) continue;
		if (_unlink(DmpFinder.GetFilePath()) == 0) { // succesfull delete
			LogAdd(0, 0, "ZIP-file in DMP-dir deleted", DmpFinder.GetFileName());
		}
		else LogAdd(0, 0, "Cannot delete ZIP-file in DMP-dir", DmpFinder.GetFileName());
	}
	DmpFinder.Close();

	DmpUpdCount = 0; DmpDelCount = 0; DmpFilCount = 0;
	if (!DmpOpen()) {
		LogAdd(53, 0, "Cannot open first DMP-File");
		goto ret;
	}

	DmpFile.Seek(DmpHdr->DmpLenTotUsed, 0);

	// Convert DmpStartedJama360SpilDateTime to FileTime
	FILETIME ftSpil;
	dt = COleDateTime((DATE)DmpStartedJama360SpilDateTime);
	SYSTEMTIME sysTime;
	dt.GetAsSystemTime(sysTime);
	// Get the timezone info.
	TIME_ZONE_INFORMATION TimeZoneInfo;
	GetTimeZoneInformation(&TimeZoneInfo);
	// Convert local time to UTC.
	TzSpecificLocalTimeToSystemTime(&TimeZoneInfo,
		&sysTime,
		&GmtTime);
	//FileTime must be in UTC format (therfor convertion)
	SystemTimeToFileTime(&GmtTime, &ftSpil);

	File2Find = PathDB + "*.*";
	BOOL bDBWorking = DBfinder.FindFile(File2Find);
	while (bDBWorking) {
		if (JMSShuttingDown) break;
		bDBWorking = DBfinder.FindNextFile();
		if (DBfinder.IsDirectory()) continue;
		CString DBName = DBfinder.GetFileName();
		if (DBName.GetLength() != 7) continue; // moet xxx.xxx zijn !
		if (DBName.Left(3).CompareNoCase("sys") == 0) {
			// sys-file. 
			CString Ext = DBName.Right(3).MakeUpper();
			int file_ix = SysOpen((char *)(LPCTSTR)Ext, false, true);
			if (file_ix == -1) continue;
			if (Sys[file_ix].DateTimeLastWrite >= DmpStartedJama360SpilDateTime) {
				DmpSysFile(file_ix);
			}
			SysClose(file_ix);
			continue;
		}

		if (DBName.Right(3).CompareNoCase("raw") == 0) continue;
		if (DBName.Right(3).CompareNoCase("zip") == 0) continue;
		// open de DB
		int DBRef = FindDB((char *)(LPCTSTR)DBName);
		bool NotMountedFlag = false;
		if (DBRef < 0) {
			// database is not mounted, check filetime to see if it's older than DmpStartedJama360SpilDateTime
			FILETIME ftDB;
			DBfinder.GetLastWriteTime(&ftDB);
			if (!CompleteRetransmit && ((ftDB.dwHighDateTime < ftSpil.dwHighDateTime) || ((ftDB.dwHighDateTime == ftSpil.dwHighDateTime) && (ftDB.dwLowDateTime < ftSpil.dwLowDateTime)))) continue;
			// indien DB recenter gewijzigd dan SpilDateTIme, dan ook dumpen naar Jama360
			NotMountedFlag = true;
			DBRef = MountDB((char *)(LPCTSTR)DBName, false, true);
			if (DBRef < 0) {
				LogAdd(91, 0, "Cannot temporary load DB for OnlineCopy Check", DBName);
				goto ret;
			}
		}
		bool TransmitAllRecsFlag = false;
		if (CompleteRetransmit || Fsd[DBRef].DateTimeUpdated >= DmpStartedJama360SpilDateTime) {
			cstr.Format("DmpAll - DmpFsdfile for %s", DB[DBRef].Name);
			LogSpec("JMSCreateAndUpdateCopy", (char*)(LPCTSTR)cstr);
			DmpFsdFile(DBRef);
			TransmitAllRecsFlag = true;
		}
		DB[DBRef].Updated = false;
		LogAdd(0, 1, "Checking database for updated records", DB[DBRef].Name);
		double _sd = DmpStartedJama360SpilDateTime;
		if (CompleteRetransmit || TransmitAllRecsFlag) _sd = 0.;
		if (_sd == 0.) _sd = -10.; // om ook de rec's te nemen die niet gewijzigd zijn ... // tijdelijk ?
		cstr.Format("DmpAll - DmpFas for %s", DB[DBRef].Name);
		LogSpec("JMSCreateAndUpdateCopy", (char*)(LPCTSTR)cstr);
		DmpFas(DBRef, _sd);
		if (NotMountedFlag) {
			UnMountDB(DBRef);
		}
	}

	JamaSubDirs = theApp.iniFile.getKeyValue("CopyJamaSubDirs", "Jama360"); // bv PROG|KASSA|PDA|FTKOPIE
	int ParseIx = 0;
	while (!JMSShuttingDown) {
		if (ParseIx >= JamaSubDirs.GetLength()) break;
		int NewParseIx = JamaSubDirs.Find("|", ParseIx);
		if (NewParseIx == -1) NewParseIx = JamaSubDirs.GetLength();
		CString File2Copy = JamaSubDirs.Mid(ParseIx, NewParseIx - ParseIx);
		LogAdd(0, 0, "Dumping", File2Copy);
		if (File2Copy.MakeUpper() == "FTKOPIE") {
			DmpFtKopie();
		}
		else {
			DmpSubDir(File2Copy);
		}
		ParseIx = NewParseIx + 1;
	}

	DmpClose();
	cstr.Format("Update OnLine-Copy : Done (Rcs=%d / Rem=%d / Fil=%d)", DmpUpdCount, DmpDelCount, DmpFilCount);
	LogAdd(0, 0, cstr);

	if (DmpSeqNr == 0) goto ret;

	// Find alle *.dmp files, rename them one by one (with count) and upload as zip
	CountStr.Format(".%03d.dmp", DmpSeqNr);
	Dmp2Find = PathDMP + "*.dmp";
	bWorking = DmpFinder.FindFile(Dmp2Find);
	while (bWorking) {
		bWorking = DmpFinder.FindNextFile();
		if (DmpFinder.IsDirectory()) continue;
		CString DmpFileWithCount = DmpFinder.GetFilePath();

		DmpFileWithCount.Replace(".dmp", CountStr);
		rename(DmpFinder.GetFilePath(), DmpFileWithCount);
	}
	DmpFinder.Close();

	// Find alle *.dmp files, rename them one by one (with count) and upload as zip
	int TotalUploadedFiles = 0;
	for (int Retry = 0; Retry < 5; Retry++) {
		int uploaded = 0, failed = 0;
		bWorking = DmpFinder.FindFile(Dmp2Find);
		while (bWorking) {
			if (JMSShuttingDown) break;
			bWorking = DmpFinder.FindNextFile();
			if (DmpFinder.IsDirectory()) continue;
			CString DmpFileWithCount = DmpFinder.GetFilePath();

			if (UploadDmpZipFile(DmpFileWithCount)) {
				LogAdd(0, 0, "Uploaded", DmpFileWithCount.Mid(PathDMP.GetLength()));
				theApp.CreateAndUpdateWatchDog = 0;
				TotalUploadedFiles++;
				_unlink(DmpFileWithCount);
				uploaded++;
			}
			else {
				LogAdd(52, 0, "Failed", DmpFileWithCount.Mid(PathDMP.GetLength()));
				failed++;
			}
		}
		DmpFinder.Close();
		if (JMSShuttingDown) break;
		if (failed == 0) break; // er is niets meer over te sturen, want het alles was ge-upload
		if (uploaded == 0) break; // de laatste Retry lukte er geen enkele upload ...
	}

	HttpUploadDone();

	int TimeOutSecs = 120 + TotalUploadedFiles * 15; // geef server voldoende tijd om de files te verwerken ...  vooral voor ftkopie, daar kan het lang duren bij volledige upload !
	if (TimeOutSecs < 150) TimeOutSecs = 150; // Wacht minimaal 2 HB (dan pas nieuw SpilDate ontvangen ...
	for (int i = 0; i < TimeOutSecs; i++) {
		if (JMSShuttingDown) break;
		Sleep(1000);
		if (i % 10 == 9) {   // om de 10 seconden testen, belangrijk voor DailyBackup ... 
			_beginthread(HttpHB, 0, 0);
		}
		theApp.ProgDidSomeWork++;
		if (DmpStartedJama360SpilDateTime != Jama360SpilDateTime) break;   // indien we al een nieuwe spildate hebben, dan eruit springen. Dan is de upload al verwerkt !
	}
	if (!JMSShuttingDown && DmpStartedJama360SpilDateTime == Jama360SpilDateTime) LogAdd(56, 0, "Upload failed: Jama360 did not confirm the new SpilDateTime");
ret:;
}

void CDataBaseDlg::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent == TIMER10SEC) {
		DWORD TicksNow = GetTickCount();
		for (int ix = 0; ix < MMFUsedCount; ix++) {
			if (TickOnEntry[ix]) {
				if (TicksNow < TickOnEntry[ix]) {
					if (TicksNow < MAX_MSEC_EXEC) continue;
				}
				else if (TicksNow < TickOnEntry[ix] + MAX_MSEC_EXEC) continue;
				// thread is langer dan MAX_MSEC_EXEC geblokkeerd, release hem en herstart !
				TickOnEntry[ix] = 0;
				RestartListenThread(ix);
			}
		}
	}

	CDialog::OnTimer(nIDEvent);
}
