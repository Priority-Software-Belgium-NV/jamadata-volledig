// PrintersDlg.cpp : implementation file
//

#include "stdafx.h"
#include "winspool.h"
#include "JMS.h"
#include "JmuDoc.h"
#include "PrintersDlg.h"

extern struct s_Sys Sys[];
extern bool JmsExtendedLogging;
static CString strSplFilePath;
static CRITICAL_SECTION csStrSplFilePath;
static int ProcessStrSplFilePathRunning=0;

#define TIMER_PROC_SPL  1
#define TIMER_PROC_SPL_VALUE  30000   // om de 30 seconden scan van de spool\temp subdir doen ...

// CPrintersDlg dialog

IMPLEMENT_DYNAMIC(CPrintersDlg, CDialog)

CPrintersDlg::CPrintersDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPrintersDlg::IDD, pParent)
{
  ::InitializeCriticalSection(&csStrSplFilePath);
  strSplFilePath=_T("");
  theApp.JMUServerhThread=(HANDLE) -1L; // set to invalid handle value so the OnTimer in JMSDLG will start the UCServer ...

  theApp.JMUPrintDocEvent = CreateEvent(NULL,FALSE,FALSE,NULL); // default security attributes, auto-reset event, initial state is nonsignaled
  theApp.JMUServerWatchDog= 0;
}

CPrintersDlg::~CPrintersDlg()
{
  ::DeleteCriticalSection(&csStrSplFilePath);
  if (theApp.JMUServerhThread!=(HANDLE)-1L) {
    TerminateThread(theApp.JMUServerhThread,0);
    theApp.JMUServerhThread=(HANDLE)-1L;
  }
  CloseHandle(theApp.JMUPrintDocEvent);
}

void CPrintersDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CPrintersDlg, CDialog)
  ON_BN_CLICKED(IDC_BUTTON1, &CPrintersDlg::OnBnClickedButton1)
  ON_WM_DESTROY()
END_MESSAGE_MAP()

// CPrintersDlg message handlers

void CPrintersDlg::OnBnClickedButton1()
{
  AddSPLFileToPrintQueue("c:\\smm\\000068E4.spl");
	CString cstr1 = GetAllPrinterNames();
  return;
  // TODO: Add your control notification handler code here
  CString cstr = GetAllPrinterBins("OKI C7400");
  cstr = GetAllPrinterMedia("OKI C7400");
  cstr = GetAllPrinterPapers("OKI C7400");

}

int CPrintersDlg::GetPrinterNr(int PostNr, int PrinterNr) // return -PostNr wanneer User op Werkpost een lokale mapping heeft (kan ook ander postnummer zijn, zo reroute naar andere post !)
{
  int WorkGroupNr;
  CString Key, Section, Value, ReRouteHistory;

retry:;
  Section.Format("Post-%03d_Settings",PostNr);
  Key.Format("Printer-%03d",PrinterNr);
  Value=theApp.iniFile.getKeyValue(Key,Section); // kijk of klant een eigen printer gekozen heeft ?
  if (Value.Left(1)=="L") return -PostNr;
  else if (Value.Left(7).CompareNoCase("R:Post-")==0) {
    CString cstr;
    cstr.Format("|%03d",PostNr);
    if (ReRouteHistory.Find(cstr)>=0) return PrinterNr; // we zitten in een loop, neem gewoon de default printer !!!
    ReRouteHistory+=cstr;
    PostNr=atol(Value.Mid(7,3));
    cstr.Format("|%03d",PostNr);
    if (ReRouteHistory.Find(cstr)>=0) return PrinterNr; // we zitten in een loop, neem gewoon de default printer !!!
    goto retry;
  }
  else if (Value.GetLength()) {
    PrinterNr=atol(Value);
  }
  else {
    // zo niet, ga dan naar zijn 'workgroup' ... 
    Value=theApp.iniFile.getKeyValue("WorkGroup",Section);
    if (Value.GetLength()) {
      WorkGroupNr=atol(Value);
      Section.Format("WorkGroup-%03d_Settings",WorkGroupNr);
      Key.Format("Printer-%03d",PrinterNr);
      Value=theApp.iniFile.getKeyValue(Key,Section); // kijk of binnen deze workgroup er een eigen printer gekozen werd ?
      if (Value.GetLength()) {
        PrinterNr=atol(Value);
      }
    }
  }

  // check if printer is rerouted to other printer (temporary ?)
  Section.Format("Printer-%03d_Settings",PrinterNr);
  Value=theApp.iniFile.getKeyValue("ReRoutePrinter",Section);
  if (Value.GetLength()) PrinterNr=atol(Value);

  return PrinterNr;
}

CString CPrintersDlg::AddSPLFileToPrintQueue(CString FilePathAndPostNr)
{
  int PostNr=1, SendSplJobToPost=0, HoldPrintJobsOnServer=0, i;
  unsigned char buf[1000];
  int LijstNr=0, PrinterNr=0, PaperNr=0, WorkGroupNr=0, BedrukkingNr=0, bufSize;
  CString RetryDigit="0", CustCode="XYZ", JamaFileRefNr="ABCDEFAB", AfdrukNaam="";
  CString NewFilePath, OldFilePath, RemotePrintInfo="";
  bool PdfFlag=false, PassSpl2JmuFlag=true;

  OldFilePath=FilePathAndPostNr;
  i=FilePathAndPostNr.Find('|');
  if (i>=0) {
    OldFilePath=FilePathAndPostNr.Left(i);
    if (i<FilePathAndPostNr.GetLength()) {
      PostNr=atol(FilePathAndPostNr.Mid(i+1));
    }
  }
  CFile SplFile;
  try {
    if (SplFile.Open(OldFilePath,CFile::modeRead,NULL)) {
      bufSize=SplFile.Read(buf,sizeof(buf));
      SplFile.Close();
    
      JamaFileRefNr=OldFilePath.Right(12).Left(8);
      PrinterNr=buf[15];
      LijstNr=buf[17];
      PaperNr=buf[19];
      BedrukkingNr=buf[21];
      //if (buf[20]>=0 && buf[20]<MAX_SYSFILE) SysExt=Sys[buf[20]].Ext; we moeten niet de SYS file, maar het systeem hebben. Byte 20 is dus terug vrij !
      CustCode=theApp.iniFile.getKeyValue("SerialNr","JamaSettings").Mid(3,3).MakeUpper();
    
      i=24;
      bool FileNameModeFlag=false;
      while (i < bufSize-10) {
        if (buf[i]==0xD0 && buf[i+1]==0xCF) {
          FileNameModeFlag=true;
          i+=2;
          continue;
        }
        if (buf[i]==0xD0 && buf[i+1]==0xCE) {
          PdfFlag=true;
          i+=3;
          continue;
        }

        if (FileNameModeFlag) {
          if (buf[i]==0xD0) FileNameModeFlag=false;
          else {
            if (buf[i]==0xEF) {         // repeat factor
              int RepeatCnt=buf[i+2];
              while (RepeatCnt-->0) {
                AfdrukNaam += buf[i+1];
              }
              i+=2;
            }
            else if (buf[i]<128) AfdrukNaam+=buf[i]; // speciale letters skippen
          }
        }
        i++;
      }
 		  AfdrukNaam.Replace("\"","_");
		  AfdrukNaam.Replace("\\","_");
		  AfdrukNaam.Replace("//","_");
		  AfdrukNaam.Replace("%","_");
		  AfdrukNaam.Replace("&","_");
		  AfdrukNaam.Replace("@","_");
		  AfdrukNaam.Replace("#","_");
		  AfdrukNaam.Replace("$","_");
		  AfdrukNaam.Replace("*","_");
		  AfdrukNaam.Replace("\'","_");
		  AfdrukNaam.Replace("?","_");
		  AfdrukNaam.Replace(",","_");
		  AfdrukNaam.Replace(";","_");
      AfdrukNaam.Replace(":","_");

      CString DestPath=PathSpoolPrint;
      if (PaperNr>0 && PaperNr<255) {  // if PaperNr==0 of 255 dan wordt het PDF en moet de SPL file gewoon in de /print subdir, niet gererout naar de ToClient
        // Zoek WorkGroupNr op in Post-x section
        CString Section, Value, Key;
        Section.Format("Post-%03d_Settings",PostNr);
        Value=theApp.iniFile.getKeyValue("WorkGroup",Section);
        if (Value.GetLength()) WorkGroupNr=atol(Value);
        else WorkGroupNr=0;
        Value=theApp.iniFile.getKeyValue("HoldPrintJobsOnServer",Section);
        if (Value.GetLength()) HoldPrintJobsOnServer=atol(Value);
        else HoldPrintJobsOnServer=0;
        Key.Format("JMM_Document-%03d",LijstNr);
        Value=theApp.iniFile.getKeyValue(Key,Section);
        if (Value.GetLength()) SendSplJobToPost=PostNr;  // er kan ofwel PDF ofwel de naam van een printer staan, in beide gevallen de SPL naar ginder sturen !
                                                         // indien het leeg is, dan gewoon op de JMS afdrukken
        Value=theApp.iniFile.getKeyValue("SendAllPrintToPost",Section);
        if (Value.GetLength()) SendSplJobToPost=atol(Value);
				if (JMSVersion=='M') SendSplJobToPost=0; // moeten door JMS afgedrukt worden !

        PrinterNr=GetPrinterNr(PostNr,PrinterNr); // kijk bij Post of WerkGroup of zij een eigen Printer hebben voor dit nummer, zo negatief, dan naar die post-nr sturen (wordt gemapped !!!)
        if (PrinterNr<0) {
          SendSplJobToPost=-PrinterNr;
          PrinterNr=buf[15]; // printernr terug origineel zetten (om mapping correct te laten doen !)
          RemotePrintInfo=("#M");
        }
        else {
          Section.Format("Printer-%03d_Settings",PrinterNr);
          Value=theApp.iniFile.getKeyValue("NamePrinter",Section);
          if (Value.GetLength()>11 && Value.GetAt(4)=='-' && Value.GetAt(8)=='_' && Value.GetAt(10)==':') { // remote drukpost via geshared printer op JMD !!
            SendSplJobToPost=atol(Value.Mid(5));
            int JamosDriver=atol(theApp.iniFile.getKeyValue("JamosDriver",Section));
            RemotePrintInfo.Format("#%sJ%02d",Value.Mid(9,1),JamosDriver);
          }
        }

        if (SendSplJobToPost) {
          DestPath.Format("%sPost-%03d\\",PathSpoolToClient,SendSplJobToPost);
          CreateDirectory(DestPath,NULL);
          PassSpl2JmuFlag=false;
        }
        else if (HoldPrintJobsOnServer==1) {
          RetryDigit="H";
          PassSpl2JmuFlag=false;
        }
      }

      NewFilePath.Format("%s%s-%03d-%s-%03d-%s-%03d-%03d-%03d-%03d-%s$%s.spl",DestPath,JamaFileRefNr,PrinterNr,RetryDigit,PaperNr,CustCode,WorkGroupNr,PostNr,LijstNr,BedrukkingNr,RemotePrintInfo,AfdrukNaam);
      if (CopyFile(OldFilePath,NewFilePath,FALSE)) _unlink(OldFilePath);
			else LogAdd(106,0,"Could not rename SPL-file, so kept it",OldFilePath);
      OldFilePath=NewFilePath;
      if (SendSplJobToPost) {
				if (PostWnd[SendSplJobToPost-1]==0) {
					LogAdd(107,0,"hWnd for JMH not filled in, so Txmit of SPL is slow, PostNr=",SendSplJobToPost);
				}
				else ::PostMessage(PostWnd[SendSplJobToPost-1],WM_USER+2,0,0); // proc_send2peer ...
        if (JmsExtendedLogging) {
          CString cstr;
          cstr.Format("Txfer to Post-%03d = %s", SendSplJobToPost, OldFilePath);
          LogAdd(0,1,cstr);
        }
      }

      if (theApp.JmsTestConfigFlag) PassSpl2JmuFlag=true;
    }
    else PassSpl2JmuFlag=false;

    if (PassSpl2JmuFlag) {
      ::EnterCriticalSection(&csStrSplFilePath);
			if (PaperNr==255) { // priorteit aan deze file, is nodig als attachment !
				if (strSplFilePath.GetLength()) strSplFilePath=OldFilePath+"|"+strSplFilePath;
				else strSplFilePath=OldFilePath;
			}
			else {
				if (strSplFilePath.GetLength()) strSplFilePath=strSplFilePath+"|"+OldFilePath;
				else strSplFilePath=OldFilePath;
			}
      ::LeaveCriticalSection(&csStrSplFilePath);
      if (JmsExtendedLogging) {
        CString cstr;
        cstr.Format("Queued  PrintJob = %s [%s]", JamaFileRefNr, OldFilePath);
        LogAdd(0,1,cstr);
      }
      else LogAdd(0,1,"Queued  PrintJob", JamaFileRefNr);
      SetEvent(theApp.JMUPrintDocEvent);
    }
  }
  catch (...) {
    LogAdd(80,0,"Fatal Exception while printing",JamaFileRefNr);
  }
  return NewFilePath.Mid(PathSpoolPrint.GetLength()); // enkel de FileName, niet het Path
}

BOOL CPrintersDlg::OnInitDialog()
{
  CDialog::OnInitDialog();

  SetTimer(TIMER_PROC_SPL,TIMER_PROC_SPL_VALUE,NULL);

  pDoc = new CJmuDoc;
  return TRUE;  // return TRUE unless you set the focus to a control
  // EXCEPTION: OCX Property Pages should return FALSE
}

void CPrintersDlg::OnDestroy()
{
  CDialog::OnDestroy();
  delete pDoc;
}

void RunJMUServer(void* dummy)
{
  bool FirstRun=true;
  DWORD dwRet=WAIT_TIMEOUT; 
 
  while (!JMSShuttingDown) {
    theApp.JMUServerWatchDog=0; // reset de watchdog (na 3 minuten geen reset, dan wordt JMUServer herstart in JMSDLG.CPP)
    if (!FirstRun) dwRet = WaitForSingleObject(theApp.JMUPrintDocEvent,60*1000); // wacht 1 minuut of tot event fired is (dan is er printwerk todo)
    else {
      LogAdd(0,1,"JMU-Server starting-up");
      FirstRun=false;
    }
    if (dwRet==WAIT_TIMEOUT && strSplFilePath.GetLength()==0) { // of bij starten van deze thread !
      COleDateTime now = COleDateTime::GetCurrentTime();
      CTime& FileLastWriteTime = CTime();
      CFileFind finder;
	    CString FindFileName=PathSpoolPrint+"*.SPL";
      CString Add2SplFilePath="";
	    BOOL bWorking = finder.FindFile(FindFileName);
      while (bWorking) {
        bWorking=finder.FindNextFile();
        if (finder.IsDirectory()) continue;
        if (!finder.GetLastWriteTime(FileLastWriteTime)) continue;
        CTimeSpan elapsedTime = CTime::GetCurrentTime() - FileLastWriteTime;
        if (elapsedTime.GetTotalSeconds() < 300) continue; // skip files die jonger zijn dan 5 minuten, voor oudere files hebben we eventueel event gemist ! (of herstart)

        if (Add2SplFilePath.GetLength()) Add2SplFilePath+="|";
        Add2SplFilePath+=finder.GetFilePath();
      }
      finder.Close();
      if (Add2SplFilePath.GetLength()) {
        ::EnterCriticalSection(&csStrSplFilePath);
        if (strSplFilePath.GetLength()==0) strSplFilePath=Add2SplFilePath;
        ::LeaveCriticalSection(&csStrSplFilePath);
      }
    }
  
    while (strSplFilePath.GetLength()) {
      CString SplFilePath;
      ::EnterCriticalSection(&csStrSplFilePath);
      int i=strSplFilePath.Find("|");
      if (i==-1) {
        SplFilePath=strSplFilePath;
        strSplFilePath="";
      }
      else {
        SplFilePath=strSplFilePath.Left(i);
        if (i==strSplFilePath.GetLength()-1) {
          strSplFilePath="";
        }
        else strSplFilePath=strSplFilePath.Mid(i+1);
      }
      ::LeaveCriticalSection(&csStrSplFilePath);
      
      CString SplFileName=SplFilePath;
      i=SplFileName.ReverseFind('\\');
      if (i<0) continue;

      SplFileName=SplFileName.Mid(i+1);
      LogAdd(0,1,"Started PrintJob", SplFileName.Left(8));
      int PostNr = atol(SplFileName.Mid(27,3));
      int PrinterNr = atol(SplFileName.Mid(9,3));
      int PaperNr = atol(SplFileName.Mid(15,3));
      int JamosDriver=0;
      CString PrinterName, Section, Value;
      bool ProcessSplFileFlag=true;

      if (PaperNr>0 && PaperNr<255) {
        // bv.: 00000030-000-0-250-EET-000-082-003-000-$Grootboekfiche.spl
        for (i=0; i<5; i++) { // to prevent endless loop in ReRouting, don't use FOREVER
          Section.Format("Printer-%03d_Settings",PrinterNr);
          Value=theApp.iniFile.getKeyValue("ReRoutePrinter",Section);
          // is the printer rerouted to other printer ?
          if (Value.GetLength()==0) break; // if not exit
          if (JmsExtendedLogging) {
            CString cstr;
            cstr.Format("ReRoutePrinter %d (Section=%s)", PrinterNr, Section, Value);
            LogAdd(0,2,cstr);
          }
					PrinterNr=atol(Value);
        }
        PrinterName=theApp.iniFile.getKeyValue("NamePrinter",Section);

        CString RetryDigit=SplFileName.Mid(13,1).MakeUpper();
        if (RetryDigit=="H") ProcessSplFileFlag=false;   // Hold-Jobs niet drukken
        else if (RetryDigit!="0") {
          // misschien hier ooit iets doen om te zien of het printprobleem opgelost is ?
          // zo niet continue
          // zou de tijd uitsparen van pMainDlg->m_dPrintersDlg.pDoc->ReadDocument(SplFilePath) indien printer toch niet klaar is
        }
    
        Value=theApp.iniFile.getKeyValue("PaperTemp",Section);
        if (Value=="") Value=theApp.iniFile.getKeyValue("Paper",Section);
        if (Value!="*" && Value!="") {
          int PaperLoaded=atol(Value);
          if (PaperNr!=PaperLoaded) ProcessSplFileFlag=false;
        }
        if (theApp.JmsTestConfigFlag) ProcessSplFileFlag=true;      // In Test mode alles drukken
        JamosDriver=atol(theApp.iniFile.getKeyValue("JamosDriver",Section));
      }

      if (ProcessSplFileFlag) {
        bool FileInToClient=false;
        bool WindowsPrinter=false;
        if (JamosDriver==0) WindowsPrinter=true;
        if (pMainDlg->m_dPrintersDlg.pDoc->ReadDocument(SplFilePath,PrinterNr,WindowsPrinter)) {
          bool SplProcessedFlag=false;
          if (PaperNr==0 || PaperNr==255) {  // 0-> PDF, 255 -> Print PDF en zet in de PathSpoolFiles om als attachment mee te gaan !
            CString DestPath;
            if (PaperNr==255) DestPath=PathSpoolFiles;
						else if (JMSVersion=='M') {
              DestPath=PathSpool+"\\Received\\";
              FileInToClient=true;
              CreateDirectory(DestPath,NULL);
						}
						else {
              DestPath.Format("%sPost-%03d\\",PathSpoolToClient,PostNr);
              FileInToClient=true;
              CreateDirectory(DestPath,NULL);
            }
            //i=SplFileName.Find('$');
            //if (i>=0) SplFileName=SplFileName.Mid(i+1);  // voorlopig dit uitschakelen, geef de volledige naam door, is nodig voor attachment !
            CString PdfFilePath=DestPath+SplFileName.Left(SplFileName.GetLength()-3)+"PDF";
            CString PdfFilePathOnePdf=pMainDlg->m_dPrintersDlg.pDoc->PdfFilePathOnePdf;
            if (pMainDlg->m_dPrintersDlg.pDoc->Convert2Pdf(SplFilePath,PdfFilePath)) {
              SplProcessedFlag=true;
              if (theApp.JmsTestConfigFlag && PaperNr!=255) {
                if (PdfFilePathOnePdf.GetLength()>0) {
                  if (pMainDlg->m_dPrintersDlg.pDoc->PdfFilePathOnePdf.GetLength()==0) {
                    // de OnePdf werd in deze loop gesloten ...
                    ::ShellExecute(NULL,"open",PdfFilePathOnePdf,NULL,NULL,SW_SHOW);
                  }
                }
                else ::ShellExecute(NULL,"open",PdfFilePath,NULL,NULL,SW_SHOW);
              }
            }
            if (FileInToClient) {
							if (JMSVersion=='M') {
								HWND JMD=FindWindow("THE_JMD",NULL);
 								if (JMD) PostMessage(JMD, WM_USER + 5, 0, 0); // 0x405, 0, 0); // PROC_RECEIVED_FILES -> de JMD moet deze file verwerken !									
							}
							else {
								if (PostWnd[PostNr-1]==0) {
									LogAdd(108,0,"hWnd for JMH not filled in, so Txmit of PDF for PostNr=",PostNr);
								}
								else PostMessage(PostWnd[PostNr-1],WM_USER+2,0,0); // proc_send2peer ...
								if (JmsExtendedLogging) {
									CString cstr;
									cstr.Format("Txfer to Post-%03d = %s", PostNr, DestPath);
									LogAdd(0,1,cstr);
								}
							}
            }
          }
          else {
            if (theApp.JmsTestConfigFlag) {
              char DefPrinterNameBuf[250+1];
              DWORD NameSize=250;
              if (GetDefaultPrinter(DefPrinterNameBuf,&NameSize) && NameSize>1) PrinterName=DefPrinterNameBuf;
              JamosDriver=0;
            }
            if (JamosDriver) {
							if (JmsExtendedLogging) {
								CString cstr;
								cstr.Format("Printing %s (%d pag) on MATRIX (Drv=%d) %s",SplFilePath,pMainDlg->m_dPrintersDlg.pDoc->PageCnt,JamosDriver-1,PrinterName);
								LogAdd(0,2,cstr);
							}
              pMainDlg->m_dPrintersDlg.pDoc->Matrix_SelectDriver(JamosDriver-1);
              if (pMainDlg->m_dPrintersDlg.pDoc->PrintOnMatrix(PrinterName,1,pMainDlg->m_dPrintersDlg.pDoc->PageCnt)) SplProcessedFlag=true;
            }
            else {  // windowsprinter ...
							if (JmsExtendedLogging) {
								CString cstr;
								cstr.Format("Printing %s on %s",SplFilePath,PrinterName);
								LogAdd(0,2,cstr);
							}
              if (pMainDlg->m_dPrintersDlg.pDoc->PrintDocument(SplFilePath,PrinterName)) SplProcessedFlag=true;
            }
            if (!SplProcessedFlag) {
               CString RetryName=SplFilePath;
               RetryName.SetAt(SplFilePath.GetLength()-SplFileName.GetLength()+13,'1'); // RetryDigit = 1 
            }
          }
          if (SplProcessedFlag) {
            CString ProcessedName = SplFilePath.Left(SplFilePath.GetLength()-3)+"spo";
            if (GetFileAttributes(ProcessedName)!=INVALID_FILE_ATTRIBUTES) {
              TRACE("File exists : %s\n",ProcessedName);
              if (_unlink(ProcessedName)==-1) TRACE("Could not delete : %s\n",ProcessedName);
            }
            if (rename(SplFilePath,ProcessedName)!=0) TRACE("Could not rename %s to %s\n",SplFilePath,ProcessedName);
            LogAdd(0,1,"Printed PrintJob", SplFileName.Left(8));
            theApp.JMUServerWatchDog=0; // reset de watchdog (na 3 minuten geen reset, dan wordt JMUServer herstart in JMSDLG.CPP)
          }
          else {
            if (FileInToClient) LogAdd(0,1,"Redirected PrintJob", SplFileName.Left(8));
            else LogAdd(0,1,"Not finished PrintJob", SplFileName.Left(8));
          }
        }
        else LogAdd(93,1,"Could not read PrintJob", SplFileName);
      }
      else LogAdd(0,1,"No need to process PrintJob", SplFileName.Left(8));
    }
  }
  if (JMSShuttingDown) theApp.JMUServerWatchDog=0;
}

CString CPrintersDlg::GetAllPrinterNames()
{
  CString strReturn="";
  // enumerate de printers
  DWORD		cbBuf;
	DWORD		pcReturned ;
	DWORD		index;
	TCHAR		Name[500] ;
	LPPRINTER_INFO_4 pPrinterEnum = NULL ;

	memset(Name, 0, sizeof(TCHAR) * 500) ;
	::EnumPrinters(PRINTER_ENUM_CONNECTIONS | PRINTER_ENUM_LOCAL, NULL, 4, NULL, 0, &cbBuf, &pcReturned) ;
	pPrinterEnum = (LPPRINTER_INFO_4)LocalAlloc(LPTR, cbBuf + 4) ;

	if (!pPrinterEnum) {
		TRACE("Error %1d\n", GetLastError()) ;
		goto clean_up;
  }

	if (!EnumPrinters(PRINTER_ENUM_CONNECTIONS | PRINTER_ENUM_LOCAL, NULL, 4, (LPBYTE)pPrinterEnum,	cbBuf,	&cbBuf,	&pcReturned)) {
			TRACE("Error %1d\n", GetLastError()) ;
			goto clean_up;
  }

	if (pcReturned > 0) {
  	TRACE("Found %1d printers\n", pcReturned) ;
		for (index = 0; index < pcReturned; index++) {
      CString cstr=(pPrinterEnum + index)->pPrinterName;
			TRACE(cstr) ;
      strReturn+=cstr+"|";
      cstr=(pPrinterEnum + index)->pServerName;   // was vroeger anders, vroegen toen level 2 op ! Maar die gaf de networkprinters niet terug !
      cstr.Replace("\r\n"," ");
			strReturn+=cstr+"|";
      cstr="";
      //cstr=(pPrinterEnum + index)->pComment;
      //cstr.Replace("\r\n"," ");
      strReturn+=cstr+"\r\n";
		}
	}
clean_up:
	LocalFree(LocalHandle(pPrinterEnum)) ;

  CStringList* pSharedPrinters = theApp.iniFile.getSectionData("Printer-JMD_Shared");
  for (POSITION pos = pSharedPrinters->GetHeadPosition(); pos != NULL;) {
    CString PrinterLine = pSharedPrinters->GetNext(pos);
    if (PrinterLine.GetLength()>12 && PrinterLine.GetAt(10)=='=') {
      strReturn+=PrinterLine.Left(10)+":"+PrinterLine.Mid(11)+"\r\n";
    }
  }

  return strReturn;
}

CString CPrintersDlg::GetAllPrinterBins(CString PrinterName)
{
  CString strReturn="";
  char BinNames[200][24]; // ruimte voor 200 namen ... zou genoeg moeten zijn !
  WORD BinRef[200];  // ruimte voor 200 WORD's 

  DWORD BinCount=DeviceCapabilities(PrinterName,NULL,DC_BINNAMES,(LPSTR)BinNames,NULL);
  BinCount=DeviceCapabilities(PrinterName,NULL,DC_BINS,(LPSTR)BinRef,NULL);
  if (BinCount<=0) return CString("0|Error\r\n");

  for (int i=0; i<(int)BinCount; i++) {
    CString cstr;
    BinNames[i][23]=0; // we verliezen 1 teken indien hij 24 bytes zou hebben, maar is niet belangrijk, is enkel ter info
    cstr.Format("%d|%s\r\n",BinRef[i],BinNames[i]);
    strReturn+=cstr;
	}
  return strReturn;
}

CString CPrintersDlg::GetAllPrinterMedia(CString PrinterName)
{
  CString strReturn="";
  char MediaNames[200][64]; // ruimte voor 200 namen ... zou genoeg moeten zijn !
  DWORD MediaRef[200];  // ruimte voor 200 DWORD's 

  DWORD MediaCount=DeviceCapabilities(PrinterName,NULL,DC_MEDIATYPENAMES,(LPSTR)MediaNames,NULL);
  MediaCount=DeviceCapabilities(PrinterName,NULL,DC_MEDIATYPES,(LPSTR)MediaRef,NULL);
  if (MediaCount<=0) return CString("0|Error\r\n");

  for (int i=0; i<(int)MediaCount; i++) {
    CString cstr;
    MediaNames[i][63]=0; // we verliezen 1 teken indien hij 64 bytes zou hebben, maar is niet belangrijk, is enkel ter info
    cstr.Format("%d|%s\r\n",MediaRef[i],MediaNames[i]);
    strReturn+=cstr;
	}
  return strReturn;
}

CString CPrintersDlg::GetAllPrinterPapers(CString PrinterName)
{
  CString strReturn="";
  char PaperNames[200][64]; // ruimte voor 200 namen ... zou genoeg moeten zijn !
  WORD PaperRef[200];  // ruimte voor 200 WORD's 

  DWORD MediaCount=DeviceCapabilities(PrinterName,NULL,DC_PAPERNAMES,(LPSTR)PaperNames,NULL);
  MediaCount=DeviceCapabilities(PrinterName,NULL,DC_PAPERS,(LPSTR)PaperRef,NULL);
  if (MediaCount<=0) return CString("0|Error\r\n");

  for (int i=0; i<(int)MediaCount; i++) {
    CString cstr;
    PaperNames[i][63]=0; // we verliezen 1 teken indien hij 64 bytes zou hebben, maar is niet belangrijk, is enkel ter info
    cstr.Format("%d|%s\r\n",PaperRef[i],PaperNames[i]);
    strReturn+=cstr;
	}
  return strReturn;
}
