
// JMS.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "JMS.h"
#include "JMSDlg.h"
#include "direct.h"
#include "afxinet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#ifdef _DEBUG
int LogLevel=0; // true;
#else
int LogLevel=0;
#endif

// CJMSApp

BEGIN_MESSAGE_MAP(CJMSApp, CWinAppEx)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CJMSApp construction

CJMSApp::CJMSApp()
{
	ProgDidSomeWork=-1;
  UCServerhThread= (HANDLE) -1L; // set to invalid handle value so the OnTimer in JMSDLG will start the UCServer ...
  CreateAndUpdateThread=(HANDLE) -1L; // set to invalid handle value so the OnTimer in JMSDLG will start the CreateAndUpdateThread ...
	RemoveOldThread=(HANDLE)-1L;
  UCServerWatchDog= 0;
  CreateAndUpdateWatchDog= 0;
	pInternetSession=NULL;
}

void InitHttpParms();
void HttpStart(void* dummy);
unsigned __stdcall HttpStop(void *dummy);

// The one and only CJMSApp object

CJMSApp theApp;
CJMSDlg* pMainDlg;
CString CustCode, PathProg, PathFSD, PathDB, PathDBLog, PathWork, PathJamaRoot, PathCopyAlt, PathTempRoot, PathSeq;
CString PathSpool, PathSpoolPrint, PathSpoolTemp, PathSpoolFiles, PathSpoolToClient, PathSpoolMail;
CString PathCopy(), PathMailTemplates, PathMailSent, PathMailFailed, PathMailOutbox, PathMailToCheck;

int SysteemNr;
char JMSVersion='D';
HANDLE hMutextLogAdd;
HANDLE hMutexHTTPPost;
bool JMSShuttingDown=false;
bool WindowsXP=false;
bool WindowsVISTA=false;
bool Windows7=false;
bool DailyBackupRequested=false;
bool JMSServiceMode=false;
bool EmergencyExit=false;
bool StdInMono=false;
double Jama360SpilDateTime=-1.; // om aan te geven dat er nog geen verbinding met de Jama360 service was, en er geen DMP moet gebeuren
// CJMSApp initialization

void RecursiveDelete(CString szPath)
{
	CFileFind ff;
	CString path = szPath;
	
	if(path.Right(1) == "\\") path += "*.*";

	BOOL res = ff.FindFile(path);

	while(res)
	{
		res = ff.FindNextFile();
    if (ff.IsDots()) continue;

		if (!ff.IsDirectory()) {
			DeleteFile(ff.GetFilePath());
    }
		else if (ff.IsDirectory())
		{
			path = ff.GetFilePath() + "\\";
			RecursiveDelete(path);
			RemoveDirectory(path);
		}
	}
  ff.Close();
}

void ExecBatchJob(CString BatchName, int MaxSeconds, bool ReturnOutput2Geel)
{
  STARTUPINFO si;
  SECURITY_ATTRIBUTES sa;
	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof STARTUPINFO;
  sa.nLength = sizeof (SECURITY_ATTRIBUTES);
  sa.lpSecurityDescriptor = NULL;
  sa.bInheritHandle=TRUE;
  CString PathToGeel = PathJamaRoot + "ToGeel\\";
  CString OutputFilePath="BatchJob";
  int i = BatchName.ReverseFind('\\');
  if (i>=0) OutputFilePath=BatchName.Mid(i+1);
  OutputFilePath = PathToGeel+OutputFilePath+".output.txt";
  HANDLE hFile = CreateFile(OutputFilePath, GENERIC_READ|GENERIC_WRITE, 0, &sa, CREATE_ALWAYS, 0, 0);
  if (hFile!=INVALID_HANDLE_VALUE) {
    si.dwFlags=STARTF_USESTDHANDLES;
    si.hStdInput = GetStdHandle(STD_INPUT_HANDLE);
    si.hStdOutput= hFile;
    si.hStdError= hFile;
  }
  else {
    LogAdd(98,0,"Cannot create output.txt for",BatchName);
    return;
  }

  PROCESS_INFORMATION pi;
  BOOL res;
  res = CreateProcess(NULL,(char*)(LPCTSTR)BatchName,NULL,NULL,TRUE,NORMAL_PRIORITY_CLASS,NULL,(char*)(LPCTSTR)PathProg,&si,&pi);
  if (TRUE == res) {
	  DWORD ret = WaitForSingleObject(pi.hProcess, (MaxSeconds * 1000)); // geef deze batch-job max. x seconden tijd 
    if (ret==WAIT_TIMEOUT) {
      CString cstr;
      cstr.Format("Batch file did not finish within %d seconds",MaxSeconds);
      LogAdd(97,0,cstr,BatchName);
    }
    TerminateProcess(pi.hProcess,1);	  
    CloseHandle(pi.hProcess);
		CloseHandle(pi.hThread);
  }
  else {
    LogAdd(99,0,"Cannot execute",BatchName);
    return;
  }
  CloseHandle(hFile);

  UploadZippedToGeel(PathToGeel, theApp.iniFile.getKeyValue("SerialNr","JamaSettings").Mid(3,3).MakeUpper());
}


BOOL CJMSApp::InitInstance()
{
  //_CrtSetBreakAlloc(584); //om het 4806 alloc na te kijken ...
  //_CrtSetBreakAlloc(1803); //om het524 alloc na te kijken ...
	SetRegistryKey(_T("JMS"));
	HKEY hk;

  OSVERSIONINFO OSversion;
  OSversion.dwOSVersionInfoSize=sizeof(OSVERSIONINFO);
  ::GetVersionEx(&OSversion);
  if (OSversion.dwPlatformId==VER_PLATFORM_WIN32_NT) {
		if (OSversion.dwMajorVersion == 5 && OSversion.dwMinorVersion == 1) WindowsXP=true;
		if (OSversion.dwMajorVersion == 6 && OSversion.dwMinorVersion == 0) WindowsVISTA=true;
		if (OSversion.dwMajorVersion == 6 && OSversion.dwMinorVersion == 1) Windows7=true;
	}

  CString CommandLine=GetCommandLine();
  CommandLine.MakeUpper();
  if (CommandLine.Find("#")>=0) JmsTestConfigFlag=true;
  if (CommandLine.Find("##")>=0) JmsCreateDBFromRestore=true; 
  if (CommandLine.Find("*")>=0) JmsExternalControlled=true;

#ifdef JMSVIEWER
  JmsTestConfigFlag=true;
#endif

  char _buf[MAX_PATH]; 
	_getcwd(_buf,sizeof(_buf));
	PathProg = _buf;
  if (PathProg.Right(1)!="\\") PathProg += "\\";
  PathSeq=PathProg;
  // volgende code om input / output in oude directory te doen !
  if (PathProg.Mid(3).CompareNoCase("Jamadata\\Prog\\")==0) {
    CString OldProgJam=PathProg.Left(12)+"\\Jamadata\\prog.jam";  // eg c:\jamadata\jamadata\prog.jam 
    if (GetFileAttributes(OldProgJam)!=INVALID_FILE_ATTRIBUTES) {
      PathSeq=PathProg.Left(12)+"Jamadata\\";
    }
  }
  // _setmaxstdio(750); // Jaak 04/09/20 : default is 512, bij veel posten en dossiers mogelijk probleem, maar is GEEN oplossing
  PathTempRoot=PathProg.Left(PathProg.GetLength()-5); // voor 12/01/2012 stond de PathTempRoot op de c:\programdata, is nu gewoon j:\jamadata ....
  PathWork=PathTempRoot+"Work\\";
  CreateDirectory(PathWork,NULL);
  PathSpool = PathTempRoot + "Spool\\";
  CreateDirectory(PathSpool,NULL);
  PathSpoolTemp = PathSpool + "Temp\\";
  CreateDirectory(PathSpoolTemp,NULL);
  PathSpoolPrint = PathSpool + "Print\\";
  CString PathSpoolPrintPrev = PathSpool + "Print.Prv\\";
  RecursiveDelete(PathSpoolPrintPrev);
  RemoveDirectory(PathSpoolPrintPrev);
  MoveFile(PathSpoolPrint.Left(PathSpoolPrint.GetLength()-1),PathSpoolPrintPrev.Left(PathSpoolPrintPrev.GetLength()-1));
  CreateDirectory(PathSpoolPrint,NULL);
  PathSpoolFiles = PathSpool + "Files\\";
  CreateDirectory(PathSpoolFiles,NULL);
  PathSpoolMail = PathSpool + "Mail\\";
  CreateDirectory(PathSpoolMail,NULL);
  PathSpoolToClient = PathSpool + "ToClient\\";
  CreateDirectory(PathSpoolToClient,NULL);

#ifndef JMSVIEWER
  // We vullen de JMS in de registry HKCU in (werkt altijd)
  int errret;
  if (!(errret=RegCreateKeyEx(HKEY_CURRENT_USER, "SOFTWARE\\Jamadata\\JMS", 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hk,NULL))) { 
    RegSetValueEx(hk,_T("PathSpoolTemp"),0,REG_SZ,(LPBYTE)PathSpoolTemp.operator LPCSTR(),PathSpoolTemp.GetLength());
    RegCloseKey(hk);
  }
  // We proberen het ook in de HKLM maar dat werkt enkel wanneer we 'admin' rights hebben (als service dus).
  if (!(errret=RegCreateKeyEx(HKEY_LOCAL_MACHINE, "SOFTWARE\\Jamadata\\JMS", 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hk,NULL))) { 
    RegSetValueEx(hk,_T("PathSpoolTemp"),0,REG_SZ,(LPBYTE)PathSpoolTemp.operator LPCSTR(),PathSpoolTemp.GetLength());
    RegCloseKey(hk);
  }
#endif

/*
#ifndef _DEBUG

  CString PathWorkUpper = PathWork;
  PathWorkUpper.MakeUpper();
  AfxMessageBox(PathWorkUpper,MB_OK);
  if (!JmsTestConfigFlag && CommandLine.GetLength()>0 && PathWork.GetLength()>0 && CommandLine.Find(PathWorkUpper)==-1) {

    //Kopieer eerst alle bestanden uit \PROG naar \WORK
    CFileFind ProgDir;
    CString Prog2Find=PathProg;
    Prog2Find+="*.*";
 	  BOOL bWorking = ProgDir.FindFile(Prog2Find);
	  while (bWorking) {
		  bWorking = ProgDir.FindNextFile();
      if (ProgDir.IsDirectory()) continue;

		  CString ProgFilePath=ProgDir.GetFilePath();
      CString WorkFilePath=PathWork+ProgDir.GetFileName();
      FILETIME ProgLastWriteTime;
      bool CopyFileFlag=false;
      ProgDir.GetLastWriteTime(&ProgLastWriteTime);
      WIN32_FIND_DATA WorkFileData;
      HANDLE hFind;
      if ((hFind=FindFirstFile(WorkFilePath,&WorkFileData))==INVALID_HANDLE_VALUE) CopyFileFlag=true;
      else if (WorkFileData.nFileSizeLow!=ProgDir.GetLength() &&
          WorkFileData.ftLastWriteTime.dwHighDateTime!=ProgLastWriteTime.dwHighDateTime &&
          WorkFileData.ftLastWriteTime.dwLowDateTime!=ProgLastWriteTime.dwLowDateTime) CopyFileFlag=true;
      FindClose(hFind);
      if (CopyFileFlag) {
        CopyFile(ProgFilePath,WorkFilePath,FALSE);
        if (WorkFilePath.Right(3).MakeUpper()=="DLL") {
          typedef HRESULT (STDAPICALLTYPE *CTLREGPROC)() ; // Requires stdole.h
          HMODULE hModule = ::LoadLibrary(WorkFilePath);
          CTLREGPROC DLLRegisterServer = (CTLREGPROC)::GetProcAddress(hModule,"DllRegisterServer");
          if (DLLRegisterServer!=NULL) DLLRegisterServer();
          ::FreeLibrary(hModule);
        }
      }
	  }
    ProgDir.Close();

    //Schrap ongebruikte files in de \WORK-dir die niet in de \Prog-dir staan ...
    CFileFind WorkDir;
    CString Work2Find=PathWork;
    Work2Find+="*.*";
	  bWorking = WorkDir.FindFile(Work2Find);
	  while (bWorking) {
		  bWorking = WorkDir.FindNextFile();
      if (WorkDir.IsDirectory()) continue;

 		  CString WorkFilePath=WorkDir.GetFilePath();
      CString ProgFilePath=PathProg+"\\"+WorkDir.GetFileName();
      if (GetFileAttributes(ProgFilePath)==INVALID_FILE_ATTRIBUTES) _unlink(WorkFilePath);
    }
    WorkDir.Close();

    // Execute the JMS in de Work-subdir !
    STARTUPINFO si;
    PROCESS_INFORMATION pi;

    ZeroMemory( &si, sizeof(si) );
    si.cb = sizeof(si);
    ZeroMemory( &pi, sizeof(pi) );
// Start the child process. 
    int i = CommandLine.Find("JMS");
    AfxMessageBox(CommandLine,MB_OK);

    if (i>=0) {
      CString NewCommandLine="";
      if (CommandLine.GetAt(0)=='\"') NewCommandLine+="\"";
      CString WorkJmsPath=PathWork+"JMS.EXE";
      if (CommandLine.GetAt(0)=='\"') NewCommandLine+="\"";
      NewCommandLine+=" ";
      NewCommandLine+=WorkJmsPath;
      NewCommandLine+=CommandLine.Mid(i+8);
      AfxMessageBox(WorkJmsPath,MB_OK);
      AfxMessageBox(NewCommandLine,MB_OK);
      AfxMessageBox("CreateProcess",MB_OK);
      if( CreateProcess( NULL, // WorkJmsPath,   // No module name (use command line)
          (LPSTR)(LPCTSTR)NewCommandLine,        // Command line
          NULL,           // Process handle not inheritable
          NULL,           // Thread handle not inheritable
          FALSE,          // Set handle inheritance to FALSE
          0,              // No creation flags
          NULL,           // Use parent's environment block
          PathProg,     // previous 'default directory'. Is belangrijk om LogFiles e.d. correct te kunnen positioneren ...
          &si,            // Pointer to STARTUPINFO structure
          &pi )           // Pointer to PROCESS_INFORMATION structure
      ) return FALSE;

      else LogAdd(0,0,"CreateProcess JMS.exe failed",GetLastError());
    }
    else LogAdd(0,0,"\\JMS.EXE not found in commandline",CommandLine);
  }
#endif
*/
  PathWork=PathProg; // tijdelijk !!!!


  /* 
  Hoe staan de directories ???

  in RELEASE mode :  -> voorlopig geen copy meer ! Loopt niet goed ...
   
        men start bv. c:\jamadata\prog\jms.exe op
        Die maakt [FOLDERID_ProgramData] aan en copieert de JMS.EXE daarin
        Die roept dan [FOLDERID_ProgramData]\WORK\JMS.EXE op
        met als 'current dir' c:\jamadata\prog
         
  in DEBUG mode :

        men start bv. c:\jamadata\prog\jms.exe
        'current dir' moet c:\jamadata\prog zijn ...
  */

  // InitCommonControlsEx() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// Set this to include all the common control classes you want to use
	// in your application.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

//  if(!SetPriorityClass(GetCurrentProcess(), ABOVE_NORMAL_PRIORITY_CLASS)) {  // HIGH_PRIORITY_CLASS)) { // 
//    TRACE("ABOVE_NORMAL_PRIORITY_CLASS failed !\n");
//  } 
  
	CWinAppEx::InitInstance();

	if (!AfxSocketInit())
	{
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();

  CString iniFileName=PathProg+"JMS.ini";
  iniFile.setIniFileName(iniFileName);

	InitHttpParms();

	JMSVersion='S';
  CString SerialNr=iniFile.getKeyValue("SerialNr","JamaSettings");
  CustCode=SerialNr.Mid(3,3).MakeUpper();
  if (CustCode=="GOR" || CustCode=="SAN" || CustCode=="MIM" || CustCode=="SUP"  || CustCode=="VSP" || CustCode=="MID" || CustCode == "BQT"
    || CustCode=="NMG" || CustCode=="VVO" || CustCode=="HAR" || CustCode=="WAB" || CustCode=="SU2" || CustCode=="JRN" || CustCode=="DSP"
    || CustCode=="ERL" || CustCode=="GSS" || CustCode=="MAE" || CustCode=="THE" || CustCode=="BRA" || CustCode=="HIN"
		|| CustCode=="ALS" || CustCode=="DLA" || CustCode=="KES" || CustCode=="TVF" || CustCode=="LOY" || CustCode=="COI"
		|| CustCode=="GRF" || CustCode=="BRH" || CustCode=="DOR" || CustCode=="VRK" || CustCode=="TO1" || CustCode=="MXT"
		|| CustCode=="PRZ" || CustCode=="VLO" || CustCode=="DLT" || CustCode=="AQU" || CustCode=="GDN" || CustCode == "D4U"
		|| CustCode=="VSL" || CustCode=="FON" || CustCode=="DSS" || CustCode=="DDR" || CustCode=="HEY" || CustCode=="SPE" || CustCode=="GER"
		|| CustCode=="ABD" || CustCode=="DBT" || CustCode=="VDA" || CustCode=="VAD" || CustCode=="RRC" || CustCode=="VPT" 
		|| CustCode=="TVF" || CustCode=="GEN" || CustCode=="WIS" || CustCode=="SU3" || CustCode=="CMB" || CustCode=="DCQ" || CustCode=="VRM"
		|| CustCode=="VNT" || CustCode=="BEQ" || CustCode=="WIL" || CustCode=="TDR" || CustCode == "VDB" || CustCode == "NEE" || CustCode == "DEP"
	    || CustCode == "JEG" 
	) JMSVersion='L';

  if (!RegCreateKey(HKEY_LOCAL_MACHINE,"Software\\Jamadata\\JMS", &hk)) {
		TCHAR bufreg[10];
		DWORD size=sizeof(bufreg);
    if (RegQueryValueEx(hk,"Mono",0,0,(unsigned char *)bufreg, &size)) size=0;
    bufreg[size]=0;
		if (size>=1 && bufreg[0]=='1'){
			JMSVersion='M';
			CString cstr_=iniFile.getKeyValue("StdInMono","JamaSettings");
			if(cstr_=="1") StdInMono=true;
		}
    RegCloseKey(hk);
  }

  // UPDATE VERSION < 1, 2, 0, 38 naar >= 1, 2, 0, 38 Mag weg wanneer iedereen op versie 38 of hoger zit !
  if (iniFile.getKeyValue("CorrJD","JamaSettings").GetLength()==0) {
    for (int PrinterNr=1; PrinterNr<=20; PrinterNr++) {
      CString Section;
      Section.Format("Printer-%03d_Settings",PrinterNr);
      CString Value=theApp.iniFile.getKeyValue("JamosDriver",Section);
      int JamosDriver=0;
      if (Value.GetLength()) JamosDriver=atol(Value);
      if (JamosDriver>0) {
        Value.Format("%d",JamosDriver+1);
        theApp.iniFile.setKey(Value,"JamosDriver",Section);
      }
    }
    iniFile.setKey("1","CorrJD","JamaSettings");
  }

 	m_CheckBusy=false;
	if (GetFileAttributes(".\\FAS")!=INVALID_FILE_ATTRIBUTES) {  // staat de FAS subdir onder Jamadata ? Dan klanten met test-systeem, eg. : EET,SEV,PAUWELS-HEULE
		int i=PathProg.Left(PathProg.GetLength()-1).ReverseFind('\\');
    PathJamaRoot=PathProg.Left(i+1);
    PathDB=PathProg+"Fas\\";
    PathDBLog=PathDB+"Log\\";
		PathFSD=PathDB+"Fsd\\";
#ifndef JMSVIEWER
    PathFSD=PathSpoolFiles+"Fsd\\";
    PathDBLog=PathSpoolFiles+"Log\\";
#endif
    CreateDirectory(PathDBLog,NULL);
    CreateDirectory(PathFSD,NULL);
	}
	else {
		PathDB=PathProg.Left(PathProg.GetLength()-5)+"FAS\\";				 // 1 niveau hoger dan current directory
    PathDBLog=PathDB+"Log\\";
		PathFSD=PathDB+"FSD\\";
    PathJamaRoot=PathProg.Left(PathProg.GetLength()-5); // 1 niveau hoger dan current directory
#ifdef JMSVIEWER
    PathFSD=PathSpoolFiles+"Fsd\\";
    PathDBLog=PathSpoolFiles+"Log\\";
#else
    CreateDirectory(PathDB,NULL);
#endif
    CreateDirectory(PathDBLog,NULL);
		CreateDirectory(PathFSD,NULL);
	}
  if (PathTempRoot.GetLength()==0) PathTempRoot=PathJamaRoot; // normaal is PathTempRoot de PathWorkRoot (1 niveau hoger), hier komt de ..\work en de ..\DMP
  
  PathCopyAlt=PathJamaRoot+"Copy.alt\\";
  PathMailTemplates=PathJamaRoot+"Mail\\Templates\\";
  PathMailSent=PathJamaRoot+"Mail\\Sent\\";
  PathMailFailed=PathJamaRoot+"Mail\\Failed\\";
  PathMailOutbox=PathJamaRoot+"Mail\\Outbox\\";
  PathMailToCheck=PathJamaRoot+"Mail\\ToCheck\\";

#ifndef JMSVIEWER
  CreateDirectory(PathCopyAlt,NULL);
  CreateDirectory(PathJamaRoot+"ToGeel\\",NULL);
  CreateDirectory(PathJamaRoot+"FromGeel\\",NULL);
  CreateDirectory(PathJamaRoot+"Updates\\",NULL);
  CreateDirectory(PathJamaRoot+"Batch\\",NULL);
  CreateDirectory(PathJamaRoot+"Offerte\\",NULL);
  CreateDirectory(PathJamaRoot + "AkKopie\\", NULL);
  CreateDirectory(PathJamaRoot+"Div\\",NULL);
  CreateDirectory(PathJamaRoot+"Mail\\",NULL);
  CreateDirectory(PathMailTemplates,NULL);
  CreateDirectory(PathMailTemplates+"Msg2Eml\\",NULL);
  CreateDirectory(PathMailTemplates+"Msg2Eml\\Converted\\",NULL);
  if (JMSVersion!='M' || CustCode=="ALS" || StdInMono) {
    CreateDirectory(PathMailSent,NULL);
    CreateDirectory(PathMailOutbox,NULL);
    CreateDirectory(PathMailToCheck,NULL);
    CreateDirectory(PathMailFailed,NULL);
  }
  // mag weg wanneer iedereen op versie 1.2.0.37 of hoger zit !
  CString _cstr = PathJamaRoot;
  _cstr += "Imap\\Sjablonen";
  if (GetFileAttributes(_cstr)!=INVALID_FILE_ATTRIBUTES) {
    CFileFind finder;
    CString FindFileName=_cstr+"\\*.EML";
	  BOOL bWorking = finder.FindFile(FindFileName);
	  while (bWorking) {
      bWorking=finder.FindNextFile();
      if (finder.IsDirectory()) continue;
      CString DestFilePath=PathMailTemplates;
      CString Subject=finder.GetFileTitle();
      if (Subject.Left(1)=="[") {
        int i=Subject.Find("]");
        if (i>0) {
          DestFilePath+=Subject.Mid(1,i-1);
          DestFilePath+=".eml";
          CopyFile(finder.GetFilePath(),DestFilePath,FALSE);
        }
      }
    }
    finder.Close();      
    RecursiveDelete(PathJamaRoot+"imap");
  }
  /// hierboven wegdoen wanneer iedereen op 1.2.0.37 of hoger zit !


	// ANDERE STUKKEN update (met Logging) zitten in HTTPSTART (zie verder !)


  CString JamaSubDirs = theApp.iniFile.getKeyValue("CopyJamaSubDirs","CopySettings"); // bv PROG|KASSA|PDA|FTKOPIE
	JamaSubDirs.MakeUpper();
	if (JamaSubDirs.Find("BATCH")<0) JamaSubDirs+="|BATCH";
  if (JamaSubDirs.Find("DIV")<0) JamaSubDirs+="|DIV";
  if (JamaSubDirs.Find("MAIL")<0) JamaSubDirs+="|MAIL";
  if (JamaSubDirs.Find("OFFERTE")<0) JamaSubDirs+="|OFFERTE";
  if (JamaSubDirs.Find("AKKOPIE") < 0) JamaSubDirs += "|AKKOPIE";
	theApp.iniFile.setKey(JamaSubDirs,"CopyJamaSubDirs","CopySettings");
  
  JamaSubDirs = theApp.iniFile.getKeyValue("CopyJamaSubDirs","Jama360"); // bv PROG|KASSA|PDA|FTKOPIE
	JamaSubDirs.MakeUpper();
	if (JamaSubDirs.Find("BATCH")<0) JamaSubDirs+="|BATCH";
  if (JamaSubDirs.Find("DIV")<0) JamaSubDirs+="|DIV";
  if (JamaSubDirs.Find("MAIL")<0) JamaSubDirs+="|MAIL";
  if (JamaSubDirs.Find("OFFERTE")<0) JamaSubDirs+="|OFFERTE";
  if (JamaSubDirs.Find("AKKOPIE") < 0) JamaSubDirs += "|AKKOPIE";
	theApp.iniFile.setKey(JamaSubDirs,"CopyJamaSubDirs","Jama360");

	// Run tools\config32.exe
  STARTUPINFO si;
  ZeroMemory( &si, sizeof(si) );
  si.cb = sizeof(si);
  PROCESS_INFORMATION pi;
  ZeroMemory( &pi, sizeof(pi) );
  CString Cmd = PathProg+"config32.exe";
  if (GetFileAttributes(Cmd)==INVALID_FILE_ATTRIBUTES) {  // mag op termijn weg ...
    CString CmdSrc = PathProg+"tools\\config32.exe";      // mag op termijn weg ...
    CopyFile(CmdSrc,Cmd,TRUE);                            // mag op termijn weg ...
  }
  BOOL res = CreateProcess(NULL,(char*)(LPCTSTR)Cmd,NULL,NULL,TRUE,NORMAL_PRIORITY_CLASS,NULL,(char*)(LPCTSTR)PathProg,&si,&pi);
  if (TRUE == res) {
	  WaitForSingleObject(pi.hProcess, 10 * 1000); // geef dit process 10 seconden tijd
		CloseHandle(pi.hProcess);
		CloseHandle(pi.hThread);
  }

  Cmd = PathProg+"upsys32.exe";
  if (GetFileAttributes(Cmd)==INVALID_FILE_ATTRIBUTES) {    // mag op termijn weg ...
    CString CmdSrc = PathProg+"tools\\upsys32.exe";         // mag op termijn weg ...
    CopyFile(CmdSrc,Cmd,TRUE);                              // mag op termijn weg ...
  }
  CString cstr=PathProg+"j.bat";
  if (GetFileAttributes(cstr)!=INVALID_FILE_ATTRIBUTES) {
    ExecBatchJob(cstr,120,true);
    _unlink((char*)(LPCTSTR)cstr);
  }    
#endif

	SysteemNr=0;
	if (__argc>=2) {
		int nr=atoi(__argv[1]);
		if (nr>=0 && nr<=9) SysteemNr=nr;
	}
  hMutextLogAdd=CreateMutex(NULL,NULL,NULL);
	hMutexHTTPPost=CreateMutex(NULL,NULL,NULL);
  pInternetSession = new CInternetSession("Jamadata360 Service");

  if (WindowsXP) {
    SetThreadExecutionState(ES_CONTINUOUS | ES_SYSTEM_REQUIRED);
    SetErrorMode(SEM_FAILCRITICALERRORS | SEM_NOGPFAULTERRORBOX | SEM_NOOPENFILEERRORBOX);    
  }
  else {
    SetThreadExecutionState(ES_CONTINUOUS | ES_SYSTEM_REQUIRED | ES_AWAYMODE_REQUIRED);
    SetErrorMode(SEM_FAILCRITICALERRORS | SEM_NOGPFAULTERRORBOX | SEM_NOOPENFILEERRORBOX);
  }
 	CJMSDlg dlg;
	pMainDlg = &dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

  SetThreadExecutionState(ES_CONTINUOUS);
  CloseHandle(hMutextLogAdd);
	CloseHandle(hMutexHTTPPost);
	if (pInternetSession) {
		pInternetSession->Close();
		delete pInternetSession;
	}
	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
  
	return FALSE;
}

//******************************************
// Communication met Jama360 Service
//******************************************

CString strHTTPBoundary, strViewState, strEventValidation;
CString strSessionId, strJama360SerialNr, strJama360Password;
int WatchDogSeconds;

void InitHttpParms()
{
  strHTTPBoundary = _T("-------------------IllBeVerySurprisedIfThisTurnsUp");
  strJama360SerialNr=theApp.iniFile.getKeyValue("SerialNr","JamaSettings");
  strJama360Password=theApp.iniFile.getKeyValue("Password","JamaSettings");
}

static void AddField(CString& strPostFieldData, char *FieldName, CString Value)
{
	CString strFormat;
	CString strData;

	strFormat = _T("--%s");
	strFormat += _T("\r\n");
	strFormat += _T("Content-Disposition: form-data; name=\"");
	strFormat += FieldName;
	strFormat += _T("\"");
	strFormat += _T("\r\n\r\n");
	strFormat += Value;
	strFormat += _T("\r\n");
	strData.Format(strFormat, strHTTPBoundary);
  strPostFieldData+=strData;
return;
}

static void MakePostButtonData(CString& strPostButtonData, char *Button, char *Value)
{
	CString strFormat;
	CString strData;

	strFormat =  _T("--%s");
	strFormat += _T("\r\n");
	strFormat += _T("Content-Disposition: form-data; name=\"");
	strFormat += Button;
	strFormat += _T("\"");
	strFormat += _T("\r\n\r\n");
	strFormat += _T("\"");
	strFormat += Value;
	strFormat += _T("\"");
	strFormat += _T("\r\n");
	strFormat += _T("--%s--");
	strFormat += _T("\r\n");
	strData.Format(strFormat, strHTTPBoundary, strHTTPBoundary);
  strPostButtonData+=strData;
	return;
}

static void StdFields(CString& strPostFieldData)
{
  strPostFieldData = "\r\n";
  AddField(strPostFieldData,"__VIEWSTATE",strViewState);
	AddField(strPostFieldData,"__EVENTVALIDATION",strEventValidation);
  AddField(strPostFieldData,"boxSerialNr",strJama360SerialNr);
  AddField(strPostFieldData,"boxPassword",strJama360Password);
  return;
}

static int SendHTTPPost(CString& strResponse, CString strPostFieldData, CString strPostButtonData, CString strFileName="")
{
  DWORD ret = WaitForSingleObject(hMutexHTTPPost,100);
  if (ret!=WAIT_OBJECT_0) return -1;  // wacht max. 0,1 seconde ! Zo niet, return !
	// wat zo deze thread gekilled wordt ???
	CFile fTrack;
	DWORD dwTotalRequestLength;
	DWORD dwChunkLength;
	DWORD dwReadLength, dwRet;
	void* pBuffer=NULL;
	BOOL bSuccess = TRUE;
	int FileLen;
  CString strPreFileData;
  
  strResponse="";
  CHttpConnection* pServer = NULL;
	CHttpFile* pHTTP = NULL;


	try
	{
		if (strFileName.GetLength()==0 || (FALSE == fTrack.Open(strFileName, CFile::modeRead | CFile::shareDenyWrite)))
		{
			FileLen=0;
		}
		else FileLen=(int)fTrack.GetLength();

		char szBuff[100000];
		INTERNET_PORT nPort;
		DWORD dwFlags=0;

		if (FileLen) {
	    CString strFormat = _T("--%s");
	    strFormat += _T("\r\n");
	    strFormat += _T("Content-Disposition: form-data; name=\"filUpload\"; filename=\"%s\"");
	    strFormat += _T("\r\n");
	    strFormat += _T("Content-Type: image/gif");
	    strFormat += _T("\r\n");
	    strFormat += _T("Content-Transfer-Encoding: binary");
	    strFormat += _T("\r\n\r\n");
	    strPreFileData.Format(strFormat, strHTTPBoundary, strFileName);
    }
			
		dwTotalRequestLength = strPostFieldData.GetLength()+strPreFileData.GetLength() + strPostButtonData.GetLength();
		if (FileLen) dwTotalRequestLength+=(FileLen+2);
		dwChunkLength = 64 * 1024;
		pBuffer = malloc(dwChunkLength);

		if (NULL == pBuffer) {
			dwRet= -1;
			goto end;
		}
		
		dwFlags=INTERNET_FLAG_RELOAD;
		nPort=INTERNET_DEFAULT_HTTP_PORT;
		pServer = theApp.pInternetSession->GetHttpConnection("svc.jamadata360.be", nPort);
		pServer->SetOption(INTERNET_OPTION_CONNECT_TIMEOUT, 20000);
		pHTTP = pServer->OpenRequest(CHttpConnection::HTTP_VERB_POST, "/svc.aspx",NULL,1,NULL,NULL,dwFlags);

    CString RequestHeader;
    RequestHeader.Format(_T("Content-Type: multipart/form-data; boundary=%s\r\n"), strHTTPBoundary);
		pHTTP->AddRequestHeaders(RequestHeader);
		pHTTP->SendRequestEx(dwTotalRequestLength, HSR_SYNC | HSR_INITIATE);
    
		if (strPostFieldData.GetLength()>0) pHTTP->Write(strPostFieldData, strPostFieldData.GetLength());
		
		if (FileLen) {
			pHTTP->Write(strPreFileData, strPreFileData.GetLength());
			dwReadLength = -1;
			while (0 != dwReadLength) {
				dwReadLength = fTrack.Read(pBuffer, dwChunkLength);
				if (0 != dwReadLength) {
					pHTTP->Write(pBuffer, dwReadLength);
				}
			}
			pHTTP->Write("\r\n",2);
		}
		if (strPostButtonData.GetLength()>0) pHTTP->Write(strPostButtonData, strPostButtonData.GetLength());
    if (pHTTP->EndRequest(HSR_SYNC)) {

			pHTTP->QueryInfoStatusCode(dwRet);
    
			if (dwRet == HTTP_STATUS_OK)
			{
				strResponse=""; 
				bool filefound=false;
				long pos=0L;
				int nRead, BufSize=sizeof(szBuff)-10;
				nRead = pHTTP->Read(szBuff, BufSize);
				if (nRead >0 )  {
					if (memcmp(szBuff,"UPDATE[",7)==0 && memcmp(&szBuff[16],"]=[",3)==0) {
						// Update received, save to file and unzip to directory
						CString UpdFilePath = PathTempRoot + "upd.zip";
						if (GetFileAttributes(UpdFilePath)!=INVALID_FILE_ATTRIBUTES) _unlink(UpdFilePath);
						CFile updfil;
						updfil.Open(UpdFilePath,CFile::modeCreate|CFile::modeWrite,NULL);
						int UpdFileToRead = atol(&szBuff[7]);
						int BufPos=19;
						while (true) {
							int WriteLen=nRead-BufPos;
							if (WriteLen>UpdFileToRead) WriteLen=UpdFileToRead;
							updfil.Write(&szBuff[BufPos],WriteLen);
							UpdFileToRead-=WriteLen;
							BufPos+=WriteLen;
							if (UpdFileToRead>0) {
								BufPos=0;
								nRead = pHTTP->Read(szBuff, BufSize);
							}
							else {
								nRead-=BufPos;
								memmove(szBuff,&szBuff[BufPos],nRead);
								nRead += pHTTP->Read(&szBuff[nRead],BufSize-nRead);
								break;
							}
						}
						updfil.Close();
						if (nRead<5 || memcmp(szBuff,"]<br>",5)!=0) {
							_unlink(UpdFilePath);
							goto ret;
						}
						nRead -= 5; // ]<br> skippen !
						memmove(szBuff,&szBuff[5],nRead);
					}
  				szBuff[nRead]=0;
					strResponse=szBuff;
				}
				// opgelet : bij volgende 2 parameters is UpperCase/LowerCase van belang !
				int i=strResponse.Find("__EVENTVALIDATION");
				if (i>=0) {
					i=strResponse.Find("value=",i);
					int j=strResponse.Find("\" />",i+8);
					strEventValidation=strResponse.Mid(i+7,j-i-7);
				}
				i=strResponse.Find("__VIEWSTATE");
				if (i>=0) {
					i=strResponse.Find("value=",i);
					int j=strResponse.Find("\" />",i+8);
					strViewState=strResponse.Mid(i+7,j-i-7);
				}

				i=strResponse.Find("#SESID=");
				if (i>=0) {
					int j=strResponse.Find("#",i+1);
					int len = j - i - 7;
					strSessionId=strResponse.MakeUpper().Mid(i+7,len);
				}
				i=strResponse.Find("#WDSEC=");
				if (i>=0) {
					int j=strResponse.Find("#",i+1);
					int len = j - i - 7;
					WatchDogSeconds=atol(strResponse.Mid(i+7,len));
				}
				i=strResponse.Find("#DMPSPL="); // #DMPSPL=40628.0796758912##
				if (i>=0) {
					int j=strResponse.Find("#",i+1);
					int len = j - i - 8;
					CString strSpilDateTime=strResponse.Mid(i+8,len);
					// normaal geeft de SVC datum terug in 40628.0796758912 vorm (de SVC.aspx zet een , om in een .) en 10cijfers na komma
					if (strSpilDateTime=="2") Jama360SpilDateTime=0.; // correctie voor 'default' in SQL daar stond 0 maar geeft 2 terug via OADATE
					else if (strSpilDateTime=="3") Jama360SpilDateTime=1.; // correctie voor 'default' in SQL daar stond 0 maar geeft 2 terug via OADATE
					else {
						strSpilDateTime+="0000000000";
						if (strSpilDateTime.GetAt(5)!='.') {
							LogAdd(57,0,"Invalid format for SpilDateTime. Expected something like '40628.0796758912' but received",strSpilDateTime.Left(16));
						}
						else {
							Jama360SpilDateTime=atof(strSpilDateTime.Left(5))+atof(strSpilDateTime.Mid(6).Left(10))/10000000000.;
							TRACE("SpilDateTime=%17.10f   StringReceived=%s\n",Jama360SpilDateTime,strSpilDateTime.Left(16));
						}
					}
				}
			}
 		}
	}

	catch (CInternetException* pEx)
	{
     CString InternetErrNum;
  	 InternetErrNum.Format("(0x%08X)",pEx->m_dwError);
		 TCHAR szCause[255];
  	 pEx->GetErrorMessage(szCause, 255);
     CString cstr="Error in SendHTTPPOST: ";
     cstr+=szCause;
     int i=cstr.Find('\r');
     if (i>0) cstr=cstr.Left(i);
     i=cstr.Find('\n');
     if (i>0) cstr=cstr.Left(i); // mag geen \r \n in Logging zetten
     LogAdd(0,0,cstr,InternetErrNum);
#ifdef _DEBUG
			if (pEx->m_dwError == 12029) { // cannot make connection 
			}
			
			else {
				pEx->GetErrorMessage(szCause, 255);
				
				CString Message;
				Message  = szCause;
				Message += "\r\n\r\nError ";
				Message += InternetErrNum;
				Message += ". Suggestions :\r\n\r\n";
				Message += "    Enable JMS.exe in Firewall\r\n";
				Message += "    Check that your Internet connection is active\r\n";
				TRACE(Message);
			}
#endif
			dwRet=-1;
			pEx->Delete();
	}
ret:;
	if (pHTTP) {
		try {
			pHTTP->Close();
		}
		catch(...){}
		delete pHTTP;
	}

	if (pServer) {
		try {
			pServer->Close();	
		}
		catch(...){}
		delete pServer;
	}

	if (pBuffer) free(pBuffer);

end:;
	ReleaseMutex(hMutexHTTPPost);
	return dwRet;
}


static bool GetASPNetParameters()
{
  bool Succeeded=false;
  CString strResponse;

  for (int Retry=0; Retry<1; Retry++) {  // probeer het 1 (vroeger:3) keer opnieuw !
    if (SendHTTPPost(strResponse,"\r\n","")!=-1) {   // -1 -> no internetconnection
		  Succeeded=true;
      break;
	  }
  }
  if (!Succeeded) return false;
  if (strEventValidation.GetLength()>0 && strViewState.GetLength()>0) return true;
	return false;
}

bool UploadShaToGeel(CString CustCode)
{
  if (!GetASPNetParameters()) {
		LogAdd(0,0,"No Internetconnection for HttpUpload");
		return false;
	}
  LogAdd(0,1,"Start creating and uploading ShaZipFile");
  CString strPostFieldData;
  StdFields(strPostFieldData);
	CString strPostButtonData;
  MakePostButtonData(strPostButtonData, "BtnUpload","Upload");
	CString strResponse;
  CString ShaZipFilePath=PathTempRoot+"DUMP\\";
  CreateDirectory(ShaZipFilePath,NULL);
  COleDateTime dtNow = COleDateTime::GetCurrentTime();
  ShaZipFilePath.Format("%sDUMP\\SHA-%s.zip", PathTempRoot, CustCode);
  _unlink(ShaZipFilePath);

  CString FileList;
  // Find all DB - SHA files
  CFileFind ShaFinder;
	CString File2Find=PathDB+"SHA\\*.SHA";
	BOOL bDBWorking = ShaFinder.FindFile(File2Find);
	while (bDBWorking) {
		bDBWorking = ShaFinder.FindNextFile();
    if (ShaFinder.IsDirectory()) continue;
    FileList+=ShaFinder.GetFilePath()+"|";
  }
  ShaFinder.Close();
  // Delete alle BAK - SHA files
	File2Find=PathCopy()+"FAS\\"+"*.SHA";
	bDBWorking = ShaFinder.FindFile(File2Find);
	while (bDBWorking) {
		bDBWorking = ShaFinder.FindNextFile();
    if (ShaFinder.IsDirectory()) continue;
    FileList+=ShaFinder.GetFilePath()+"|";
  }
  ShaFinder.Close();

  if (!pMainDlg->CreateZipFromFileList(FileList,ShaZipFilePath)) return false;
  int HttpRet;
  for (int retry=0; retry<5; retry++) {
    if (JMSShuttingDown) break;
    HttpRet = SendHTTPPost(strResponse,strPostFieldData,strPostButtonData,ShaZipFilePath);   
    if (HttpRet==HTTP_STATUS_OK && strResponse.Find("Received OK")>=0) break;
    GetASPNetParameters();
  }
  _unlink(ShaZipFilePath);
  if (HttpRet==HTTP_STATUS_OK) {
    LogAdd(0,1,"ShaZipFile uploaded", ShaZipFilePath);
    return true;
  }
  else return false;
}

bool UploadZippedToGeel(CString Path, CString CustCode)
{
  if (!GetASPNetParameters()) {
		LogAdd(0,0,"No Internetconnection for HttpUpload");
		return false;
	}
	if (GetFileAttributes(Path)==INVALID_FILE_ATTRIBUTES) return false;
  CString strPostFieldData;
  StdFields(strPostFieldData);
	// deze lijn stond er, maar volgens mij deed ze niets ... zie FWPDlg MakePreFileData();
	CString strPostButtonData;
  MakePostButtonData(strPostButtonData, "BtnUpload","Upload");
	CString strResponse;
  CString ZipFilePath=PathTempRoot+"DUMP\\";
  CreateDirectory(ZipFilePath,NULL);
  COleDateTime dtNow = COleDateTime::GetCurrentTime();
  ZipFilePath.Format("%sDUMP\\%s-INFO-%02d%02d%02d-%02d%02d.zip", PathTempRoot, CustCode, dtNow.GetYear()%100, dtNow.GetMonth(), dtNow.GetDay(), dtNow.GetHour(), dtNow.GetMinute());
  LogAdd(0,0,"Path to zip", Path);
  LogAdd(0,0,"ZipFileName", ZipFilePath);
  if (!pMainDlg->CreateZipFromPath(Path,ZipFilePath)) return false;
  int HttpRet;
  for (int retry=0; retry<5; retry++) {
    if (JMSShuttingDown) break;
    HttpRet = SendHTTPPost(strResponse,strPostFieldData,strPostButtonData,ZipFilePath);   
    if (HttpRet==HTTP_STATUS_OK && strResponse.Find("Received OK")>=0) break;
    GetASPNetParameters();
  }
  _unlink(ZipFilePath);
  if (HttpRet==HTTP_STATUS_OK) {
    CFileFind Finder;
	  BOOL bWorking = Finder.FindFile(Path+"\\*.*");
	  while (bWorking) {
		  bWorking = Finder.FindNextFile();
      if (Finder.IsDirectory()) continue;
      _unlink(Finder.GetFilePath());
    }
    Finder.Close();
    return true;
  }
  return false;
}

bool UploadDmpZipFile(CString FilePath)
{
  if (!GetASPNetParameters()) {
		LogAdd(0,0,"No Internetconnection for HttpUpload");
		return false;
	}
	if (GetFileAttributes(FilePath)==INVALID_FILE_ATTRIBUTES) return false;
  CString strPostFieldData;
  StdFields(strPostFieldData);
	// deze lijn stond er, maar volgens mij deed ze niets ... zie FWPDlg MakePreFileData();
	CString strPostButtonData;
  MakePostButtonData(strPostButtonData, "BtnUpload","Upload");
	CString strResponse;
  CString ZipFilePath=FilePath+".zip";
  if (!pMainDlg->CreateZipFromFile(FilePath,ZipFilePath)) return false;
  int HttpRet;
  for (int retry=0; retry<5; retry++) {
    if (JMSShuttingDown) break;
    HttpRet = SendHTTPPost(strResponse,strPostFieldData,strPostButtonData,ZipFilePath);   
    if (HttpRet==HTTP_STATUS_OK && strResponse.Find("Received OK")>=0) break;
    GetASPNetParameters();
  }
  _unlink(ZipFilePath);
  if (HttpRet==HTTP_STATUS_OK) return true;
  return false;
}

bool HttpUploadDone()
{
  if (theApp.JmsTestConfigFlag) return false;
#ifdef _DEBUGx	
  Jama360SpilDateTime=0;
  return true; 
#endif  
  if (!GetASPNetParameters()) {
		LogAdd(0,0,"No Internetconnection for HttpUploadDone");
		return false;
	}
  CString strPostFieldData;
  StdFields(strPostFieldData);
	AddField(strPostFieldData,"boxCMD","UPLOAD-DONE");
	CString strPostButtonData;
  MakePostButtonData(strPostButtonData,"BtnSubmit","Submit");
	CString strResponse;
  SendHTTPPost(strResponse,strPostFieldData,strPostButtonData);
  return true;
}

bool HttpGetUpdate(bool RestartFlag)
{
  if (theApp.JmsTestConfigFlag) return false;
#ifdef _DEBUGx	
  Jama360SpilDateTime=0;
  return true; 
#endif  
  if (!GetASPNetParameters()) {
		LogAdd(0,0,"No Internetconnection for HttpGetUpdate");
		return false;
	}
  CString strPostFieldData;
  StdFields(strPostFieldData);
	AddField(strPostFieldData,"boxCMD","GETUPDATE");
  CString strPostButtonData;
  MakePostButtonData(strPostButtonData,"BtnSubmit","Submit");
  CString strResponse;
  CString UpdateFilePath = PathTempRoot + "upd.zip";
  _unlink(UpdateFilePath);
  SendHTTPPost(strResponse,strPostFieldData,strPostButtonData);
  if (GetFileAttributes(UpdateFilePath)!=INVALID_FILE_ATTRIBUTES) {
    // update.zip is succesvol gedownload
    CString UpdateSubDir;
    for (int UpdNr=1; UpdNr<=999; UpdNr++) {
      UpdateSubDir.Format("%sUpdates\\%03d",PathJamaRoot,UpdNr);
      if (GetFileAttributes(UpdateSubDir)==INVALID_FILE_ATTRIBUTES) {
        UpdateSubDir+="\\";
        break;
      }
    }
    if (pMainDlg->ZipExtractAll(UpdateFilePath,UpdateSubDir)) {
        _unlink(UpdateFilePath);
      // erase update on Jama360 computer
      strPostFieldData="";
      StdFields(strPostFieldData);
	    AddField(strPostFieldData,"boxCMD","DELUPDATE");
      CString strPostButtonData;
      MakePostButtonData(strPostButtonData,"BtnSubmit","Submit");
      CString strResponse;
      SendHTTPPost(strResponse,strPostFieldData,strPostButtonData);
      
      // install the update and restart !
      bool KassaZip=false, JamaPdaZip=false, KasUpdFlag=false;
      bool ExecUBatFlag=false;
      CFileFind Finder;
      CString Files2Install=UpdateSubDir+"\\*.*";
	    BOOL bWorking = Finder.FindFile(Files2Install);
	    while (bWorking) {
		    bWorking = Finder.FindNextFile();
        if (Finder.IsDirectory()) continue;
        if (Finder.GetFileName().CompareNoCase("BriefUpd.Jam")==0) {
          _unlink(Finder.GetFilePath());
          continue;
        }
        if (Finder.GetFileName().CompareNoCase("u.bat")==0) ExecUBatFlag=true;
        if (Finder.GetFileName().CompareNoCase("r.flg")==0) RestartFlag=true;
				if (Finder.GetFileName().CompareNoCase("runonce.kas")==0) KasUpdFlag=true;
        if (Finder.GetFileName().CompareNoCase("kassa.zip")==0) KassaZip=true;
        if (Finder.GetFileName().CompareNoCase("jamapda.zip")==0) JamaPdaZip=true;
        CString NewFileName=PathProg+Finder.GetFileName();
        CString PrvFileName=NewFileName+".prv";
        CString OldFileName=NewFileName+".old";
        _unlink(OldFileName);
        MoveFile(PrvFileName,OldFileName);
        MoveFile(NewFileName,PrvFileName);
        MoveFile(Finder.GetFilePath(),NewFileName);
      }
      Finder.Close();
      RemoveDirectory(UpdateSubDir);
      CString PathToGeel = PathJamaRoot + "ToGeel\\";
      CString CustCode=theApp.iniFile.getKeyValue("SerialNr","JamaSettings").Mid(3,3).MakeUpper();
      if (ExecUBatFlag) {
        CString cstr=PathProg+"u.bat";
        ExecBatchJob(cstr,120,true);
        _unlink(cstr); // en delete de u.bat daarna !
      }
			if (KasUpdFlag) {
				CString FileNameRunOnce = PathProg+"RunOnce.kas";
				for (int KassaNr=1; KassaNr<50; KassaNr++) {
					CString FileNameKassaExe;
					FileNameKassaExe.Format("%sKassa\\Kassa-%02d\\kassys.dat",PathJamaRoot,KassaNr);
					if (GetFileAttributes(FileNameKassaExe)!=INVALID_FILE_ATTRIBUTES) {
						CString FileNameKassaRunOnce=PathJamaRoot+"Kassa\\To\\";
						CreateDirectory(FileNameKassaRunOnce,NULL);
						FileNameKassaRunOnce.Format("%sKassa-%02d\\",FileNameKassaRunOnce,KassaNr);
						CreateDirectory(FileNameKassaRunOnce,NULL);
						FileNameKassaRunOnce+="RunOnce.kas";
						_unlink(FileNameKassaRunOnce);
						CopyFile(FileNameRunOnce,FileNameKassaRunOnce,FALSE);
					}
				}
				_unlink(FileNameRunOnce);
				FileNameRunOnce+=".prv";
				_unlink(FileNameRunOnce);
			}
      if (KassaZip) {
        CString cstr=PathProg+"kassa.zip";
        pMainDlg->ZipExtractAll(cstr,PathJamaRoot+"Kassa",true);
        CFile BatFile;
        CString DirTxtFileName = PathToGeel + CustCode + "-Kassa-DIR.txt";
        _unlink(DirTxtFileName);
        CString BatText, BatLine;
        BatText.Format("dir ..\\Kassa /s /on >%s\r\n", DirTxtFileName);
        CString BatFileName;
        BatFileName.Format("%smkdirlst.bat",PathToGeel);
        if (BatFile.Open(BatFileName,CFile::modeCreate|CFile::modeReadWrite)) {
          BatFile.Write(BatText,BatText.GetLength());
          BatFile.Close();
          CString Arguments = "/C " + BatFileName;
          ::ShellExecute(NULL,"open","cmd.exe",Arguments,PathToGeel,SW_NORMAL);
        }
        Sleep(2000);
        _unlink(cstr);
        _unlink(BatFileName);
        UploadZippedToGeel(PathJamaRoot+"ToGeel\\", theApp.iniFile.getKeyValue("SerialNr","JamaSettings").Mid(3,3).MakeUpper());
      }
      if (JamaPdaZip) {
        CString cstr=PathProg+"JamaPDA.zip";
        pMainDlg->ZipExtractAll(cstr,PathJamaRoot+"JamaPDA",true);
        CFile BatFile;
        CString DirTxtFileName = PathToGeel + CustCode + "-JamaPDA-DIR.txt";
        _unlink(DirTxtFileName);
        CString BatText, BatLine;
        BatText.Format("dir ..\\JamaPDA /s /on >%s\r\n", DirTxtFileName);
        CString BatFileName;
        BatFileName.Format("%smkdirlst.bat",PathToGeel);
        if (BatFile.Open(BatFileName,CFile::modeCreate|CFile::modeReadWrite)) {
          BatFile.Write(BatText,BatText.GetLength());
          BatFile.Close();
          CString Arguments = "/C " + BatFileName;
          ::ShellExecute(NULL,"open","cmd.exe",Arguments,PathToGeel,SW_NORMAL);
        }
        Sleep(2000);
        _unlink(cstr);
        _unlink(BatFileName);
        UploadZippedToGeel(PathJamaRoot+"ToGeel\\", theApp.iniFile.getKeyValue("SerialNr","JamaSettings").Mid(3,3).MakeUpper());
      }
      if (RestartFlag) {
        CString cstr=PathProg+"r.flg";
        _unlink(cstr); 
        CFile Cmd;
        CString CmdName = PathProg + "JMT.CMD";
        _unlink(CmdName);
        Sleep(250);
        for (int loop=0; loop<400; loop++) {
          Cmd.Open(CmdName,CFile::modeCreate|CFile::modeWrite,NULL);
          Cmd.Write("RESTART UPDATE\r\n",16);
          Cmd.Close();
					if ((loop%10==0) && JMSVersion=='M') {
						HWND JMD=FindWindow("THE_JMD",NULL);
 						if (JMD) PostMessage(JMD, WM_USER + 5, 0, 0); // 0x405, 0, 0); // PROC_RECEIVED_FILES -> de JMD moet deze file verwerken !							
					}
          Sleep(250);
          if (JMSShuttingDown) {
            _unlink(CmdName);
            return true;
          }
        }
        LogAdd(93,0,"JMT did not process RESTART command within 100 seconds after update was installed !");
      }
    }
  }
  return true;
}

void HttpStart(void *dummy)
{
  CString strResponse, 	strPostButtonData, strPostFieldData, JMSExeVersion;

  LogAdd(0,1,"HttpStart Started");
  if (theApp.JmsTestConfigFlag) goto end;
#ifdef _DEBUGx	
  Jama360SpilDateTime=0;
  goto end; 
#endif  
  if (!GetASPNetParameters()) {
		LogAdd(0,0,"No Internetconnection for HttpStart");
		goto end;
	}
  StdFields(strPostFieldData);
	AddField(strPostFieldData,"boxCMD","START");
  for (int i=0; i<20; i++) { // wacht max. 5 seconden
    JMSExeVersion=pMainDlg->GetJMSExeVersion();
    if (JMSExeVersion.GetLength()) break;
    Sleep(250);
  }
  if (JMSExeVersion.GetLength()==0) goto end; // probeer het 'START'-command opnieuw (in OnTimer ipv HB)
  AddField(strPostFieldData,"boxMessage",JMSExeVersion);
  MakePostButtonData(strPostButtonData,"BtnSubmit","Submit");
  SendHTTPPost(strResponse,strPostFieldData,strPostButtonData);
  if (strSessionId.GetLength()==0) LogAdd(0,1,"HttpStart Failed, no SessionID received");
	else {
		LogAdd(0,1,"HttpStart Posted");

		/// hieronder mag weg zo iedereen op versie 1.2.1.4 of hoger zit !
		if (GetFileAttributes(PathJamaRoot+"Jamadata\\AlreadyTriedToMove.flg")==INVALID_FILE_ATTRIBUTES) {
			CString _cstr = PathJamaRoot;
			_cstr += "Jamadata";
			if (GetFileAttributes(_cstr)!=INVALID_FILE_ATTRIBUTES) {
				bool SendUsed=false;
				if (GetFileAttributes(PathJamaRoot+"Jamadata\\sendkas.bat")!=INVALID_FILE_ATTRIBUTES) SendUsed=true;
				if (GetFileAttributes(PathJamaRoot+"Jamadata\\sendkassa.bat")!=INVALID_FILE_ATTRIBUTES) SendUsed=true;
				if (GetFileAttributes(PathJamaRoot+"Jamadata\\sendpda.bat")!=INVALID_FILE_ATTRIBUTES) SendUsed=true;
				bool EmptyJamadataFlag=true;
				bool NoJamadataSubdirs=true;
				bool OfferteMoved=false, JamaPDAMoved=false;
				bool NewPDAEmpty=true;
				CFileFind finder;
				CString FindFileName=_cstr+"\\*.*";
				BOOL bWorking = finder.FindFile(FindFileName);
				while (bWorking) {
					bWorking=finder.FindNextFile();
					CString FileName=finder.GetFileName();
					if (finder.IsDirectory()) {
						NoJamadataSubdirs=false;
						if (FileName.CompareNoCase("OFFERTE")==0) {
							CFileFind Ofinder;
							CString OFindFileName=finder.GetFilePath()+"\\*.*";
							BOOL ObWorking = Ofinder.FindFile(OFindFileName);
							while (ObWorking) {
								ObWorking=Ofinder.FindNextFile();
								if (Ofinder.IsDirectory()) continue;
								CString NewFileName = PathJamaRoot + "Offerte\\" + Ofinder.GetFileName();
								CopyFile(Ofinder.GetFilePath(), NewFileName, TRUE);
							}
							Ofinder.Close();
							OfferteMoved=true;
						}
						else if (!SendUsed && FileName.CompareNoCase("JAMAPDA")==0) {
							CString NewFilePath = PathJamaRoot + "JamaPDA";
							// check to see if \jamamdata\jamaPDA contains no files
							CFileFind PDAfinder;
							CString PDAFindFileName=NewFilePath+"\\*.*";
							BOOL PDAbWorking = PDAfinder.FindFile(PDAFindFileName);
							while (PDAbWorking) {
								PDAbWorking=PDAfinder.FindNextFile();
								if (PDAfinder.IsDirectory()) continue;
								NewPDAEmpty=false;
								break;
							}
							PDAfinder.Close();
							PDAFindFileName=NewFilePath+"\\PDA-01\\*.*";
							PDAbWorking = PDAfinder.FindFile(PDAFindFileName);
							while (PDAbWorking) {
								PDAbWorking=PDAfinder.FindNextFile();
								if (PDAfinder.IsDirectory()) continue;
								NewPDAEmpty=false;
								break;
							}
							PDAfinder.Close();

							if (NewPDAEmpty) {
								RecursiveDelete(NewFilePath);
								MoveFile(finder.GetFilePath(),NewFilePath);
								JamaPDAMoved=true;
							}
						}
					}
					else {
						EmptyJamadataFlag=false;
						if (FileName.GetLength()>3 && FileName.Right(3).CompareNoCase("TXT")==0) {
							CString NewFileName = PathJamaRoot + "Prog\\" + FileName;
							CopyFile(finder.GetFilePath(), NewFileName, FALSE); // zo hij al bestaat, overschrijven !
						}
					}
				}
				finder.Close();    
				if (SendUsed) {
					LogAdd(109,0,"SendKas of SendPDA gevonden, geen move JamaPDA en jamadata.old gemaakt");
					Sleep(2000);
				}
				if (OfferteMoved) {
					LogAdd(109,0,"Jamadata\\Jamadata\\Offerte moved to Jamadata\\Offerte");
					Sleep(2000);
				}
				if (JamaPDAMoved) {
 					LogAdd(109,0,"Jamadata\\Jamadata\\JAMAPDA moved to Jamadata\\jamaPDA");
					Sleep(2000);
				}
				else if (!NewPDAEmpty) {
 					LogAdd(109,0,"Jamadata\\jamaPDA was already used");
					Sleep(2000);
				}
				if (EmptyJamadataFlag && NoJamadataSubdirs) {
					RecursiveDelete(_cstr);
				}
				else if (!SendUsed) {
					CString OldJamadata = PathJamaRoot + "Jamadata.old";
					int cnt=1;
					while (GetFileAttributes(OldJamadata)!=INVALID_FILE_ATTRIBUTES) {
						OldJamadata.Format("%sJamadata.old.%d", PathJamaRoot, cnt++);
					}
					MoveFile(_cstr,OldJamadata);
					PathSeq=PathProg;
					LogAdd(0,0,"Jamadata\\Jamadata renamed to",OldJamadata);
				}
				else {
					CFile fil;
					fil.Open(PathJamaRoot+"Jamadata\\AlreadyTriedToMove.flg",CFile::modeCreate,NULL);
					fil.Close();
				}
			}
		}
	/// hierboven mag weg zo iedereen op versie 1.2.1.3 of hoger zit !

	}

end:;
	_endthread();
}

unsigned __stdcall HttpStop(void *dummy)
{
  CString strResponse, 	strPostButtonData, strPostFieldData;

  if (theApp.JmsTestConfigFlag) {
		return 0;
	}
#ifdef _DEBUGx
	return true; 
#endif  
  if (!GetASPNetParameters()) {
		LogAdd(0,0,"No Internet-connection for HttpStop");
		return 1;
	}
  StdFields(strPostFieldData);
	AddField(strPostFieldData,"boxCMD","STOP");
  AddField(strPostFieldData,"boxMessage",strSessionId);
  MakePostButtonData(strPostButtonData,"BtnSubmit","Submit");
	SendHTTPPost(strResponse,strPostFieldData,strPostButtonData);
  return 0;
}

static bool HttpUpdateBusy=false;

void HttpHB(void *dummy)
{
	CString strResponse, strPostButtonData, strPostFieldData;

  if (strSessionId.GetLength()==0) goto end;

  if (theApp.JmsTestConfigFlag) goto end;
#ifdef _DEBUGx	
  goto end; 
#endif  
  if (TRUE || strViewState.GetLength()==0) {
    if (!GetASPNetParameters()) {
		  LogAdd(0,0,"No Internet-connection for HttpHeartBeat");
      goto end;
	  }
  }
  StdFields(strPostFieldData);
	AddField(strPostFieldData,"boxCMD","HB");
  AddField(strPostFieldData,"boxMessage",strSessionId);
  MakePostButtonData(strPostButtonData,"BtnSubmit","Submit");
  if (JMSShuttingDown) goto end;
  SendHTTPPost(strResponse,strPostFieldData,strPostButtonData);
  if (JMSShuttingDown) goto end;
  int i=strResponse.Find("\r\n");
  if (i>3 && strResponse.Mid(i-3,3)=="##*") {
    if (!HttpUpdateBusy) {
      HttpUpdateBusy=true;
      HttpGetUpdate(false);
      HttpUpdateBusy=false;
    }
    SendHTTPPost(strResponse,strPostFieldData,strPostButtonData); // indien vorige lijn te lang zou duren !
  }
  else if (i>3 && strResponse.Mid(i-3,3)=="##!") { // Dagelijkse backup moet nog gemaakt worden
    DailyBackupRequested=true;
  }
  else DailyBackupRequested=false;
end:;
}

void HttpError(void *parm)
{
  CString strResponse, strPostFieldData, strPostButtonData;
  char* HttpErrorBufOnHeap=(char*) parm;

  if (theApp.JmsTestConfigFlag) goto ret;
#ifdef _DEBUGx	
  goto ret;
#endif  
	/*
	if (TRUE || strViewState.GetLength()==0) {
    if (!GetASPNetParameters()) {
		  LogAdd(0,0,"No Internet-connection for HttpError");
		  goto ret;
	  }
  }
	*/
  StdFields(strPostFieldData);
  AddField(strPostFieldData,"boxMessage",HttpErrorBufOnHeap);
  AddField(strPostFieldData,"boxCMD","ERROR");
  MakePostButtonData(strPostButtonData,"BtnSubmit","Submit");
  SendHTTPPost(strResponse,strPostFieldData,strPostButtonData);
ret:;
  delete HttpErrorBufOnHeap;
}

void RemoveOldFiles(CString Files2Del)
{
  CFileFind Finder;

  Finder.FindFile(Files2Del);
  COleDateTime now = COleDateTime::GetCurrentTime();
  CTime& FileCreationTime = CTime();

	BOOL bWorking = Finder.FindFile(Files2Del);
	while (bWorking) {
    if (JMSShuttingDown) break;
		bWorking = Finder.FindNextFile();
    if (Finder.IsDirectory()) continue;
    if (Finder.GetFileName().CompareNoCase("TempNr.Jam")==0) continue;

    Finder.GetCreationTime(FileCreationTime);
    CTimeSpan elapsedTime = CTime::GetCurrentTime() - FileCreationTime;
    if (elapsedTime.GetTotalMinutes() > 30) _unlink(Finder.GetFilePath());
  }
  Finder.Close();
}

void RemoveOldFilesFromSpool(void* dummy)
{
  CString Files2Del = PathSpoolPrint + "*.SPO";
  RemoveOldFiles(Files2Del);
  Files2Del = PathSpoolTemp + "*.*";
  RemoveOldFiles(Files2Del);
  Files2Del = PathSpoolFiles + "*.*";
  RemoveOldFiles(Files2Del);
	theApp.RemoveOldThread=(HANDLE)-1L;
}

//******************************************
// LOGGING
//******************************************

DWORD LogSpecTicksStarted=0;

void LogSpec(char* Name, char* info) 
{
	CFile fil;
	CString FilePath=PathJamaRoot+"LOG\\";
	FilePath+=Name;
	FilePath+=".log";
	int inflen=strlen(info);

	if (inflen==1 && info[0]=='D') {
		if (GetFileAttributes(FilePath)!=INVALID_FILE_ATTRIBUTES) {
			CString PrevFilePath=PathJamaRoot+"LOG\\";
			PrevFilePath+=Name;
			PrevFilePath+=".prv.log";
			_unlink(PrevFilePath);
			MoveFile(FilePath,PrevFilePath);		
		}
	}
	else if (inflen==1 && info[0]=='C') {
		CString CrashFilePath=PathJamaRoot+"LOG\\Crash-";
		CrashFilePath+=Name;
		CrashFilePath+=".log";
		if (GetFileAttributes(FilePath)!=INVALID_FILE_ATTRIBUTES) {
			_unlink(CrashFilePath);
			MoveFile(FilePath,CrashFilePath);
			CString CrashToGeel = CrashFilePath;
			CrashToGeel.Replace("\\LOG\\","\\ToGeel\\");
			CopyFile(CrashFilePath,CrashToGeel,FALSE);
		}
	}
	else if (fil.Open(FilePath,CFile::modeReadWrite|CFile::modeCreate|CFile::modeNoTruncate)) {
		ULONGLONG pos=fil.SeekToEnd();
		if (pos==0) LogSpecTicksStarted=GetTickCount();
		DWORD Sec = (GetTickCount()-LogSpecTicksStarted)/1000;
		char buf[20];
		sprintf(buf,"%04d : ",Sec);
		fil.Write(buf,strlen(buf));
		fil.Write(info,inflen);
		fil.Write("\r\n",2);
		fil.Close();
	}
}

bool LogGetFileName(char *p, int bufsize, int day2add)
{
	CString FileNamePath;
	struct tm today;
	time_t ltime;
	char timbuf[128];
  
	time( &ltime );
  ltime+=(day2add*86400);
	_localtime64_s(&today, &ltime);

	sprintf_s(timbuf,sizeof(timbuf),"%02d%02d%02d",today.tm_year%100,today.tm_mon+1,today.tm_mday);
	FileNamePath = PathJamaRoot+"LOG\\JMS-"+timbuf+".log"; 
  sprintf_s(p,bufsize,"%s", (char *)(LPCTSTR)FileNamePath);
  return true;
}

void LogAdd(int nr, int LogDept, char *text, char *parm)
{
	CFile log;
	CString FileNamePath, space="";
	struct tm today;
	time_t ltime;
	char timbuf[128];

  DWORD ret = WaitForSingleObject(hMutextLogAdd,100);
  if (ret!=WAIT_OBJECT_0) return;  // wacht max. 0,1 seconde ! Zo niet, return !

  time( &ltime );
	_localtime64_s(&today, &ltime);

	sprintf_s(timbuf,sizeof(timbuf),"%02d%02d%02d",today.tm_year%100,today.tm_mon+1,today.tm_mday);
	FileNamePath = PathJamaRoot+"LOG\\JMS-"+timbuf+".log"; 

	sprintf_s(timbuf,sizeof(timbuf),"%02d/%02d/%02d %02d:%02d:%02d",today.tm_mday,today.tm_mon+1,today.tm_year%100,today.tm_hour,today.tm_min,today.tm_sec);
	char *sep="", *errprefix="";
	if (*parm) sep=" = ";
	if (nr>0) errprefix="*** ERROR : ";
  int buflen=strlen(text)+strlen(parm)+150;
	char* buf = new char[buflen];
	for (int i=0; i<LogDept; i++) space+="  ";
	sprintf_s(buf,buflen-10,"%s #%04d %s%s%s%s%s\r\n",timbuf,nr, (char *)(LPCTSTR)space,errprefix,text,sep,parm);

  if (nr && !theApp.JmsTestConfigFlag) {
    char* HttpErrorBufOnHeap = new char[strlen(buf)+5];
    strcpy(HttpErrorBufOnHeap,buf);
    _beginthread(HttpError, 0, (void *)HttpErrorBufOnHeap);  
  }

#ifndef JMSVIEWER
	if (log.Open(FileNamePath,CFile::modeCreate|CFile::modeNoTruncate|CFile::modeWrite,0)) { // skip file-write when not possible to open file
		log.SeekToEnd();
		if (nr==0 && !*text) {
			log.Write("\r\n",2);
			log.Close();
      ReleaseMutex(hMutextLogAdd);
      delete buf;
			return;
		}
		log.Write(buf,strlen(buf));
		log.Close();
	}
  else {
    CString LogDir=PathJamaRoot+"LOG";
    CreateDirectory(LogDir,NULL); // moest die nog niet bestaan ...
  }
#endif

	if (LogDept<=LogLevel && pMainDlg!=NULL) {
		TRACE(buf);
    if (buflen<500 && !JMSShuttingDown && pMainDlg!=NULL) {
      buf[buflen-2]=0;
			try {
				pMainDlg->m_dLoggingDlg.m_listLogging.AddString(buf);
				pMainDlg->m_dLoggingDlg.m_listLogging.SetCurSel(-1);
				pMainDlg->m_dLoggingDlg.m_listLogging.SetCaretIndex(pMainDlg->m_dLoggingDlg.m_listLogging.GetCount(),0);
			}
			catch(...) {}
    }
	}

  ReleaseMutex(hMutextLogAdd);
  delete buf;

  if (pMainDlg!=NULL && !JMSShuttingDown) pMainDlg->ProcessAllMessages();
}

void LogAddFile(char* FilePath)
{
  CFile fil;
  if (fil.Open(FilePath,CFile::modeRead,NULL)) {
    char* buf = new char[(UINT)fil.GetLength()+10];
    int len=fil.Read(buf,(UINT)fil.GetLength());
    buf[len]=0;
    fil.Close();
    CString cstr;
    cstr=buf;
    delete buf;
    LogAdd(0,1,"Extra info",cstr);
  }
  _unlink(FilePath);
}

void LogAdd(int nr, int LogDept, char *text, int parm)
{
	char buf[100];
	sprintf_s(buf,sizeof(buf),"%d",parm);
	LogAdd(nr, LogDept, text, buf);
}

void LogAdd(int nr, int LogDept, CString str)
{
	LogAdd(nr, LogDept, (char *)(LPCTSTR)str);
}

void LogAdd(int nr, int LogDept, CString str, int parm)
{
	LogAdd(nr, LogDept, (char *)(LPCTSTR)str, parm);
}

void LogAdd(int nr, int LogDept, CString str, CString parm)
{
	LogAdd(nr, LogDept, (char *)(LPCTSTR)str, (char *)(LPCTSTR) parm);
}

void LogAdd(int nr, int LogDept, char *text, CString parm)
{
	LogAdd(nr, LogDept, text, (char *)(LPCTSTR) parm);
}

//Scan and process JMS.cmd

static void ExecCmdFile(CString CmdFileName)
{
	CString CmdText, Command, CmdLine;
	int i;
	
	LogAdd(0,1,"Start executing",CmdFileName);

	CFile CmdFile;
	if (CmdFile.Open(CmdFileName,CFile::modeRead,NULL)) {
		char *filbuf = new char[100000];
		i=CmdFile.Read(filbuf,100000);
		filbuf[i]=0;
		CmdText=filbuf;
		CmdFile.Close();
		delete filbuf;
	}
  
	while (CmdText.GetLength()>3) {
	  i=CmdText.FindOneOf(" \r\n");
		Command=CmdText.Left(i);
		Command.MakeUpper();
		i=CmdText.FindOneOf("\r\n");
		CmdLine=CmdText.Left(i);
		while (i<CmdText.GetLength()) {
			if (CmdText.GetAt(i)>' ') break;
			i++;
		}
		CmdText=CmdText.Mid(i);

    if (Command.Compare("UPSYS")==0) pMainDlg->m_dUtilitysDlg.ExecCmdLine(CmdLine); 
		else if (Command.Compare("MOUNT")==0) MountDB((char*)(LPCTSTR)GetSubString(CmdLine,2));
		else if (Command.Compare("UNMOUNT")==0) UnMountDB((char*)(LPCTSTR)GetSubString(CmdLine,2));
	}

	_unlink(CmdFileName);
	LogAdd(0,1,"Executed and deleted",CmdFileName);
}

void CheckAndExecuteCmdFile(void *dummy) 
{
  CString FullFileName;

  if (theApp.m_CheckBusy) return;
	else theApp.m_CheckBusy=true;
	FullFileName=PathProg+"JMS.cmd";
  if (GetFileAttributes(FullFileName)!=INVALID_FILE_ATTRIBUTES) ExecCmdFile(FullFileName);

	theApp.m_CheckBusy=false;
}

// HULP-routines

static unsigned stci_d(char *s,int in,int outlen)
{
  char buf[11];
  int i, j;

  for (i=0; i<11; i++) buf[i]=' ';
  i=0;
  if (in<0) {s[i++]='-'; in=-in;}
  if (in==0) s[i++]=0;
  else {
    j=10;
    while (in>0 && j>0) {
      buf[j]= in%10 + '0';
      in=in/10; j--;
    }
    j++;
    while (i<outlen) {
      if (j==11) break;
      s[i++]=buf[j++];
    }
  }
  s[i]=0;
  return i;
}

unsigned datejd(int jj,int mm,int dd)
{
  if(jj<60) jj=jj+2000;
  if(jj<100)jj=jj+1900;
  if(mm<3){jj=jj-1;mm=mm+12;}
  return (unsigned)((long)(306*(mm+1)/10+dd-jj/100+jj/400+(36525*jj)/100-691058));
}

unsigned dateget()
{
  SYSTEMTIME systime;

  GetLocalTime(&systime);              
  return datejd(systime.wYear,systime.wMonth,systime.wDay);
}

void jddate(unsigned short jd,int *jj,int *mm,int *dd)
{
  int alfa,c,e;
  long int b,d,z;
 
  z=jd+2412055;
  alfa=(z*100-186721625)/3652425;
  b=1525+alfa-alfa/4+z;
  c=(b*100-12210)/36525;
  d=36525*c/100;
  e=(b-d)*10000/306001;
  *dd=b-d-e*306001/10000;
  if(e<=13)*mm=e-1; else *mm=e-13;
  if(*mm<3) *jj=c-4715; else *jj=c-4716;
}

unsigned short datechk(char *ps)
{
  int c=0,j[4],k=0;
  char byte,*ps1;
 
  if (!*ps) return 0;  /* default date */
  ps1 = ps;
  while(byte=*ps1++){
    if(byte<'0'||byte>'9') break;
    k++;
  }
  if((byte==0)&&((k==6)||(k==8))){
    ps1=ps;
    for(c=0;c<3;c++){
      j[c]=*ps1++-'0';
      j[c]=j[c]*10+*ps1++-'0';
    }
    if(k==8){
      j[2]=j[2]*10+*ps1++-'0';
      j[2]=j[2]*10+*ps1-'0';
    }
    k=2;
  }
  else{
    c=0;k=-1;
    while(byte=*ps++){
      if(byte>='0'&&byte<='9'){
        if(c==0)j[++k]=0;
        if(k>2) return(0xFFFF);
        j[k]=j[k]*10+byte-'0';
        c=1;
      }
      else c=0;
    }
  }
  if(k<2)return(0xFFFF);
  if((j[2]<0)||(j[2]>=100&&j[2]<1892)||(j[2]>2068))return(0xFFFF);
  if(j[1]<1||j[1]>12)return(0xFFFF);
  if(j[0]<1||j[0]>31)return(0xFFFF);
  if(j[0]==31&&(j[1]==4||j[1]==6||j[1]==9||j[1]==11))return(0xFFFF);
  if(j[1]==2){
    if(j[0]>29)return(0xFFFF);
    if((j[0]==29)&&((j[2]%4>0)||(j[2]==1900)))return(0xFFFF);
  }
  return(datejd(j[2],j[1],j[0]));
}

int datefm(char *ps,unsigned short jd,int fm)
{
  int c,j=0,jj,mm,dd;
  char buf[7];
	char *nm_day [7] = {"Zo","Ma","Di","Wo","Do","Vr","Za"};
	char *nm_month [12] = {"januari","februari","maart","april","mei","juni",
                "juli","augustus","september","oktober","november","december"};
 
  if(jd==0xFFFF)return 0;
  if(jd==0) {                   /* return empty string with right format */
    *ps='\0';
    j=6;
    if (fm&2) j += 2;
    if (fm&4) j += 3;
    if (fm&8) j += 11;
    else if (fm&1) j += 2;
    return j;
  }
  jddate(jd,&jj,&mm,&dd);

  if(fm&4){
    c=(jd+3)%7;if(c<0)c=c+7;
    *ps++=nm_day[c][0];*ps++=nm_day[c][1];*ps++=' ';
    j=j+3;
  }
  stci_d(buf,dd+100,7);
  if(buf[1]!='0'||(fm&8)!=8){*ps++=buf[1];j++;}
  *ps++=buf[2];j++;
  if(fm&8){
    *ps++=' ';
    c=0;
    while(nm_month[mm-1][c]){
      *ps++=nm_month[mm-1][c++];
    }
    *ps++=' ';
    j=j+11;
  }
  else{
    if(fm&1){*ps++='/';j++;}
    stci_d(buf,mm+100,7);
    *ps++=buf[1];*ps++=buf[2];j=j+2;
    if(fm&1){*ps++='/';j++;}
  }
  stci_d(buf,jj,7);
  if(fm&2){
    *ps++=buf[0];*ps++=buf[1];j=j+2;
  }
  *ps++=buf[2];*ps++=buf[3];j=j+2;
  if(!(fm&16)) *ps=0;
  return(j);
}

CString GetSubString(CString CmdLine, int nr)
{
	CString Command;
  int i, pos, cnt;

	pos=0; cnt=1;
	while (true) {
		if (CmdLine.GetAt(pos)=='"') {
			i=CmdLine.Find('"',pos+1);
			if (i>0) i=CmdLine.Find(' ',i);
		}
		else i=CmdLine.Find(' ',pos);
		if (i<0) i=CmdLine.GetLength();
		if (i<=pos) break;

		if (cnt==nr) {
			Command=CmdLine.Mid(pos,i-pos);
			break;
		}
		while (i<CmdLine.GetLength()) {
			if (CmdLine.GetAt(i)>' ') break;
			i++;
		}
		pos=i; cnt++;
	}
	if (Command.GetAt(0)=='"') Command=Command.Mid(1);
	if (Command.GetAt(Command.GetLength()-1)=='"') Command=Command.Left(Command.GetLength()-1);
	return Command;
}
