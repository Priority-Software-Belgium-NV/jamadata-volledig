
// JMS.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols
#include "JMSDlg.h"
#include "IniFile.h"
#include "afxinet.h"

#define MAX_SYSFILE     20 // mvg22 was 50
#define MAX_SYS_LEN			32750
#define MAX_POST        40 // mvg22 was 30 
#define MAX_MSEC_EXEC	  75000							// maximum aantal msec dat een 'exec' van een task mag duren, zoniet wordt thread gekilled en herstart !

struct s_Sys {
  CFile File;							
  long Length;            // length of file on disk
  int  OpenCnt;          // open number this file 
	CString Ext;
  CString Name;						// Full Filename & Path for reopen 
	char Buf[MAX_SYS_LEN+10];  // local cache for reading
  bool PreMountBusyFlag;
  bool StdDossierFlag;
  bool Updated;
	bool PeekMode; // only to read SysFile ... not the dataset
  double DateTimeLastWrite; 
}; 

// CJMSApp:
// See JMS.cpp for the implementation of this class
//

class CJMSApp : public CWinAppEx
{
public:
	CJMSApp();
	bool m_CheckBusy;
  BOOL RemoteLink;
  CString Dossier;
  CString EncryptieText;
  BOOL HeartBeatNeeded;
  DWORD ServerIPAddress;
  CIniFile iniFile;
  bool JmsTestConfigFlag, JmsExternalControlled, JmsCreateDBFromRestore;
  int ProgDidSomeWork;
  HANDLE UCServerhThread;
  int UCServerWatchDog;
  HANDLE JMUServerhThread;
	HANDLE RemoveOldThread;
  int JMUServerWatchDog;
  HANDLE JMUPrintDocEvent;
  HANDLE MailServerhThread;
  int MailServerWatchDog;
  int CreateAndUpdateWatchDog;
  HANDLE CreateAndUpdateThread;
  HANDLE Mail2SendEvent;
  CInternetSession* pInternetSession; 

// Overrides
	public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CJMSApp theApp;
extern CJMSDlg* pMainDlg;
extern CString CustCode, PathProg, PathDB, PathDBLog, PathFSD, PathWork, PathJamaRoot, PathCopyAlt, PathTempRoot, PathSeq;
extern CString PathSpool, PathSpoolPrint, PathSpoolTemp, PathSpoolFiles, PathSpoolToClient, PathSpoolMail;
extern CString PathMailTemplates, PathMailSent, PathMailOutbox, PathMailFailed, PathMailToCheck;
extern int SysteemNr;
extern char JMSVersion;
extern bool JMSShuttingDown;
extern bool WindowsXP;
extern bool WindowsVISTA;
extern bool Windows7;
extern bool DailyBackupRequested;
extern bool JMSServiceMode;
extern bool EmergencyExit;
extern bool StdInMono;
extern double Jama360SpilDateTime;
extern CString strSessionId, strJama360SerialNr, strJama360Password;
//Global functions vanuit DataBaseDlg.cpp

extern HWND PostWnd[MAX_POST];

void EDBStart(void *dummy);
bool EDBStop(bool TerminateFlag);
void EDBBackup(struct s_DB *pDB);
void EDBCompact(struct s_DB *pDB);
bool UnMountDB(char *cDBName);
bool UnMountDB(int DBRef);
int MountDB(char* cDBName, bool CreateIfNotExists=false, bool DisableRecovery=false);
CString GetMountedDBName(int nr);
bool UploadDmpZipFile(CString FilePath);
bool UploadZippedToGeel(CString Path, CString CustCode);
void RunUCServer(void* dummy);
void RunJMUServer(void* dummy);
void RunMailServer(void* dummy);
void RemoveOldFilesFromSpool(void* dummy);

bool UpdateSysFileRead(char *DBName, int pos, int len, char *buf);
bool UpdateSysFileWrite(char *DBName, int pos, int len, char *buf);

//Global functions vanuit JMS.cpp

void LogSpec(char* Name, char* info);
void LogAdd(int nr, int LogDept, char *text, char *parm="");
void LogAddFile(char* FilePath);
void LogAdd(int nr, int LogDept, char *text, int parm);
void LogAdd(int nr, int LogDept, CString str);
void LogAdd(int nr, int LogDept, CString str, int parm);
void LogAdd(int nc, int LogDept, CString str, CString parm);
void LogAdd(int nr, int LogDept, char *text, CString parm);
bool LogGetFileName(char *p, int bufsize, int day2add);

void CheckAndExecuteCmdFile(void *dummy);
void InitHttpParms();
void HttpStart(void *dummy);
void HttpHB(void *dummy);
unsigned __stdcall HttpStop(void *dummy);
bool HttpUploadDone();
unsigned datejd(int jj,int mm,int dd);
unsigned dateget();
void jddate(unsigned short jd,int *jj,int *mm,int *dd);
int datefm(char *ps,unsigned short jd,int fm);

CString GetSubString(CString CmdLine, int nr);
