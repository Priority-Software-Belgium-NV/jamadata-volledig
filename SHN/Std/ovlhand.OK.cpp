#define _WIN32_WINNT 0x0501

#define  UseJMS	true
#include "JamaConL.h"
#include "Nb30.h"
 
#define YES             1
#define NO              0

#define BUF_LEN 1024 + 8  // is zelfde waarde als in COMNETB.PRC

extern "C" void RunOvlSystem();
extern "C" void EndOvl();
extern "C" void ovlexit(short int nr);
extern "C" void ovlreset(short int dum);

//******************************************
// NETBIOS FUNCTIONS
//******************************************

#define RTO      0/* no time-out may occur */
#define STO    100/* time - out of 50 sec. */
#define MAX_LANANR 255
#define LSN_ADJ 32/* Max. 32 LSN in table -> zie RESET adapter */
#define MAX_ADPTCNT 20
#define NCB_CNT 5

extern "C" short int procid;
extern "C" short int prc_num[3];
extern "C" short int ThisPostNr;
extern "C" short int ThisScreenNr;
extern "C" short int OvlNumber;
extern "C" short int JMC4TEST;

char this_name[16];
int num_name=0;
int  adpt_cnt;/* aantal adapters found */
int  adpt_nr[MAX_ADPTCNT];/* echte nummers van de adapters */
bool EnableEnhancedFlag=false;
bool NoMessageBoxes=false;

NCB  ncb[NCB_CNT], work_ncb, *p_ncb;
int  ncb_cnt=NCB_CNT;/* maximaal aantal te gebruiken NCB's */
char ncb_used[NCB_CNT], *p_used;

int lana_num=0, lsn=0;

void fill_ncb(NCB *pncb)
{
	memset(pncb, 0, sizeof(NCB));
  pncb->ncb_rto=RTO;
  pncb->ncb_sto=STO;
	memcpy(pncb->ncb_name,this_name,16);
  pncb->ncb_num=num_name;
}

void find_adapter()
{
  int i;
 	
  for (i=0; i<MAX_LANANR; i++) {
    fill_ncb(&work_ncb);
    work_ncb.ncb_lana_num=i;
    work_ncb.ncb_command=NCBRESET;
		work_ncb.ncb_callname[0]=LSN_ADJ;
		work_ncb.ncb_callname[2]=LSN_ADJ*2;
    int ret=Netbios(&work_ncb);
    if (ret==NRC_GOODRET) {
      adpt_nr[adpt_cnt++]=i;
		}
  }
}

int add_name(int lana_num)
{
  fill_ncb(&work_ncb);
  work_ncb.ncb_lana_num=lana_num;
  work_ncb.ncb_command=0x30;/* work_ncb.command=0xB0; */
  Netbios(&work_ncb);/* exec_wait(&work_ncb);  */
  if (work_ncb.ncb_retcode) {
    if (work_ncb.ncb_retcode==0x0D || work_ncb.ncb_retcode==0x16) {
				//error !
		}
    return NO;
  }
  num_name=work_ncb.ncb_num;
  return YES;
}

void hang_up()
{
  int i;
 
  for (i=0; i<ncb_cnt; i++) {
		if (ncb_used[i]) {
			fill_ncb(&work_ncb);
			work_ncb.ncb_lsn=ncb[i].ncb_lsn;
			work_ncb.ncb_lana_num=ncb[i].ncb_lana_num;
			work_ncb.ncb_command=0x12;  // hang-up
			Netbios(&work_ncb);
		}
	}
		
	for (i=0; i<adpt_cnt; i++) {
		fill_ncb(&work_ncb);
		work_ncb.ncb_command=0x31;  // delete name
		work_ncb.ncb_lana_num=adpt_nr[i];
		Netbios(&work_ncb);
	}

	// now wait for all netbios-thread that are pending, to terminate
	int max_try=60; // wacht maximaal 60 seconden !
	while (max_try-->0) {
		int count=0;
		for (i=0; i<ncb_cnt; i++) {
			if (ncb_used[i]) count++;
			//pMainDlg->ProcessAllMessages();
		}
  	Sleep(1000);
		if (count==0) {
			break;
		}
	}
}

void StartNetbios()
{
	int k;
	int ncb_nr=0;
  
	CString ThisPostName;
	ThisPostName.Format("n.post.%d                  ",ThisPostNr);
	memcpy(this_name,ThisPostName,15);
	this_name[15]=0;
  find_adapter();
  for (int j=0; j<adpt_cnt; j++) {
		add_name(adpt_nr[j]);
	}
 
	fill_ncb(&ncb[ncb_nr]);
  sprintf((char *)ncb[ncb_nr].ncb_callname,"n.post.%-5d",0);
  for (k=0; k<15; k++) {
    if ((ncb[ncb_nr].ncb_callname[k]==0) || (ncb[ncb_nr].ncb_callname[k]==' ')) break;
  }
  for (; k<15; k++) ncb[ncb_nr].ncb_callname[k]=' ';
  ncb[ncb_nr].ncb_callname[15]=0;
 
	for (int j=0; j<adpt_cnt; j++) {
		ncb[ncb_nr].ncb_lana_num=adpt_nr[j];
		ncb[ncb_nr].ncb_command=0x10;
		Netbios(&ncb[ncb_nr]);
		if (ncb[ncb_nr].ncb_retcode==NRC_GOODRET) {
      lsn=ncb[ncb_nr].ncb_lsn;
			lana_num=ncb[ncb_nr].ncb_lana_num;
			break;
		}
	}
}

//*********************************************
// Memory Mapped File / Shared Memory for IPC
//*********************************************

struct s_SharedMem {
	bool Used;
	unsigned char TaskBuf[BUF_LEN];
} *pSharedMem=NULL;

HANDLE SharedMemMutex;
HANDLE JMSProcEvent, JMSDoneEvent, OVLProcEvent, OVLDoneEvent;
HANDLE hMMFile;

void CreateSharedMem(int MMFIx)
{
	CString strSharedMemMutex;
	strSharedMemMutex.Format("JMwSharedMemoryMutex-%d",MMFIx);
  SharedMemMutex = CreateMutex(NULL,FALSE,strSharedMemMutex);
	CString strJMSProcEvent;
	strJMSProcEvent.Format("JMwJMSProcEvent-%d",MMFIx);	JMSProcEvent = CreateEvent( 
        NULL,               // default security attributes
        FALSE,              // auto-reset event
        FALSE,              // initial state is nonsignaled
        strJMSProcEvent     // object name
        );
	
  if (JMSProcEvent == NULL) 
  { 
        //LogAdd(35,0,"Cannot make JMSProcEvent");
        return;
  }

	CString strJMSDoneEvent;
	strJMSDoneEvent.Format("JMwJMSDoneEvent-%d",MMFIx);
	JMSDoneEvent = CreateEvent(         NULL,               // default security attributes
        FALSE,              // auto-reset event
        FALSE,              // initial state is nonsignaled
        strJMSDoneEvent     // object name
        );
	
  if (JMSDoneEvent == NULL) 
  { 
		//LogAdd(35,0,"Cannot make JMSProcEvent");
		return;
  }

	CString strJMwOVLProcEvent;
	strJMwOVLProcEvent.Format("JMwOVLProcEvent-%d",MMFIx);
	OVLProcEvent = CreateEvent(        NULL,               // default security attributes
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
	strJMwOVLDoneEvent.Format("JMwOVLDoneEvent-%d",MMFIx);
	OVLDoneEvent = CreateEvent( 
		    NULL,               // default security attributes
        FALSE,              // auto-reset event
        FALSE,              // initial state is nonsignaled
        strJMwOVLDoneEvent  // object name
        );
	
  if (OVLDoneEvent == NULL) 
  { 
		//LogAdd(35,0,"Cannot make JMSProcEvent");
		return;
  }

	int size=sizeof(s_SharedMem);
	CString strJMwSharedMemoryFile;
	strJMwSharedMemoryFile.Format("JMwSharedMemoryFile-%d",MMFIx);
	hMMFile = OpenFileMapping(
                   FILE_MAP_ALL_ACCESS,   // read/write access
                   FALSE,                 // do not inherit the name
         			     strJMwSharedMemoryFile);					 // Name of mapping object. 

	if (hMMFile==NULL) {
		hMMFile = CreateFileMapping(INVALID_HANDLE_VALUE,    // Current file handle. 
					NULL,                              // Default security. 
					PAGE_READWRITE,                    // Read/write permission. 
					0,                                 
					size,
					strJMwSharedMemoryFile);					 // Name of mapping object. 
	}
	int ret = GetLastError();

	pSharedMem = (struct s_SharedMem *)MapViewOfFile(hMMFile, // Handle to mapping object. 
      FILE_MAP_ALL_ACCESS,               // Read/write permission 
      0,                                 // Max. object size. 
      0,                                 // Size of hFile. 
      size);                                // Map entire file. 
 
  ret = GetLastError();

	if (hMMFile == NULL) {
		//LogAdd(35,0,"Cannot make Memory Mapped File");
		return;
	}

	/*
	while (true) {
		// wait for a netbios-packet to be received 
		DWORD dwWaitResult;

    dwWaitResult = WaitForSingleObject(JMSProcEvent,INFINITE);    // indefinite wait
		if (dwWaitResult==WAIT_OBJECT_0) {
			memcpy(Thd[THREAD_MMF_OFFSET].ComBuf,pSharedMem->TaskBuf,BUF_LEN);
			ComBufExec(THREAD_MMF_OFFSET);
			if (Thd[THREAD_MMF_OFFSET].ReplyLength) {
				// sent the reply that is prepared
				memcpy(pSharedMem->TaskBuf,Thd[THREAD_MMF_OFFSET].ComBuf,Thd[THREAD_MMF_OFFSET].ReplyLength+8);
				SetEvent(JMSDoneEvent);
			}
		}
	}
	*/
}

UNALIGNED struct sComBuf {
	short unsigned DestId;
  short unsigned OrigId;
	short unsigned Len;
	unsigned char Function;
	unsigned char Type;
	char Info[BUF_LEN];
};

void DoExit(int ResetFlagFromProcId)
{
  if (ResetFlagFromProcId) ovlreset(ResetFlagFromProcId);
  _moexit(1);
  EndOvl();
  UnmapViewOfFile(pSharedMem);
  CloseHandle(SharedMemMutex);
  CloseHandle(JMSProcEvent);
  CloseHandle(JMSDoneEvent);
  CloseHandle(OVLProcEvent);
  CloseHandle(OVLDoneEvent);
  CloseHandle(hMMFile);

	if (!NoMessageBoxes) AfxMessageBox("JMwServer not listening ... OVL closed !",MB_OK);
	exit(1);
}

extern "C" void EDBsendtask(short int destprc,short int type,short int function,char *info,short int len)
{
	if (lsn>0) {
    char buf[2000];
	  struct sComBuf *pComBuf = (struct sComBuf *)buf;

		pComBuf->DestId=destprc;
		pComBuf->OrigId=63;
		pComBuf->Len = len;
		pComBuf->Function=(unsigned char) function;
		pComBuf->Type = (unsigned char) type;
		if (len>0) memcpy(pComBuf->Info,info,len);
	
		fill_ncb(&ncb[0]);
		ncb[0].ncb_command=0x14;  // send with wait
		ncb[0].ncb_lana_num=lana_num;
		ncb[0].ncb_lsn=lsn;
		ncb[0].ncb_length=pComBuf->Len+8;
		ncb[0].ncb_buffer=(PUCHAR)buf;
		Netbios(&ncb[0]);
		if (ncb[0].ncb_retcode!=NRC_GOODRET) {
      int error=1;	
		}
		return;
	}
 
	struct sComBuf *pComBuf = (struct sComBuf *)pSharedMem->TaskBuf;

	pComBuf->DestId=19;
	pComBuf->OrigId=procid;
	pComBuf->Len = len;
	pComBuf->Function=(unsigned char) function;
	pComBuf->Type = (unsigned char) type;
  if (len>0) memcpy(pComBuf->Info,info,len);
  SetEvent(JMSProcEvent);
	DWORD dwWaitResult = WaitForSingleObject(JMSDoneEvent, 60000); // 60 seconds to end of execution
 	if (dwWaitResult == WAIT_OBJECT_0) return;
	else { 
		// nog na te kijken ... server antwoordt niet !
    DoExit(0);
	}

}

extern "C" void gettask(short int *reqproc,short int *type,short int *function,char *info,short int *ilength)
{
	if (lsn>0) {
    char buf[2000];
	  struct sComBuf *pComBuf = (struct sComBuf *)buf;

		fill_ncb(&ncb[0]);
		ncb[0].ncb_command=0x15;  // receive with wait
		ncb[0].ncb_lana_num=lana_num;
		ncb[0].ncb_lsn=lsn;
		ncb[0].ncb_length=sizeof(buf);
		ncb[0].ncb_buffer=(PUCHAR)buf;
		Netbios(&ncb[0]);
		if (ncb[0].ncb_retcode!=NRC_GOODRET) {
      int error=1;	
		}

		*reqproc = pComBuf->OrigId;
		*type = pComBuf->Type;
		*function = pComBuf->Function;
		*ilength = pComBuf->Len;
		if (*ilength > 0) memcpy(info,pComBuf->Info,*ilength);
	 
		return;
	}
	
	
	struct sComBuf *pComBuf = (struct sComBuf *)pSharedMem->TaskBuf;

	DWORD dwWaitResult = WaitForSingleObject( 
      OVLProcEvent, // event handle
      INFINITE);    // indefinite wait

	if (dwWaitResult == WAIT_OBJECT_0) {
		*reqproc = pComBuf->OrigId;
		*type = pComBuf->Type;
		*function = pComBuf->Function;
		*ilength = pComBuf->Len;
		if (*ilength > 0) memcpy(info,pComBuf->Info,*ilength);
	}
	else {
		printf("error on wait for single object bij gettask !\r\n");
	}
}

CString JmsCmd(CString Cmd)
{
  if (Cmd.GetLength()<=BUF_LEN-1) {
    EDBsendtask(5,10,100,(char *)(LPCTSTR)Cmd,Cmd.GetLength()+1);
  }
  else {
    EDBsendtask(5,10,101,(char *)(LPCTSTR)Cmd,BUF_LEN-1);
    Cmd=Cmd.Mid(BUF_LEN-1);
    while (Cmd.GetLength()>BUF_LEN-1) {
      EDBsendtask(5,10,102,(char *)(LPCTSTR)Cmd,BUF_LEN-1);
      Cmd=Cmd.Mid(BUF_LEN-1);
    }
    EDBsendtask(5,10,103,(char *)(LPCTSTR)Cmd,Cmd.GetLength()+1);
  }
  // wait for reply (must be 105/106, when multiple answers, the last is 105, the frame before are all 106)
  short int reqproc, type, function, ilength;
  char info[BUF_LEN];
  CString strReply="";
  while (true) {
    gettask(&reqproc,&type,&function,info,&ilength);
    if (type!=10 || ilength<0 || ilength>=BUF_LEN) break;
    info[ilength]=0;
    strReply+=info;
    if (function==105) break;
    EDBsendtask(5,10,104,"",1);
  }
  return strReply;
}

extern "C" void SvcErr(int nr, char *text)
{
	CString cstr;

	//OvlError|19|240|De waarde van Test=1 en had =0 moeten zijn
	cstr.Format("OvlError|%d|%d|%s",OvlNumber,nr,text);
	JmsCmd(cstr);
}

extern "C" char SplLastPrinted[250];

void ProcessSplFile(char* FilePath)
{
  CString Cmd;
  Cmd.Format("ProcessSplFile|%s|%d",FilePath,ThisPostNr);
  CString Reply=JmsCmd(Cmd);
  sprintf_s(SplLastPrinted,sizeof(SplLastPrinted),"%s",Reply);
}

extern "C" unsigned short jamin1[];

extern "C" void jamint()
{
	if (jamin1[0]>=0xF0 && jamin1[0]<=0xFF) {
		if (jamin1[0]==0xF0) {
			jamin1[1]=0; // busycount = 0
		}
		return; // con e.d. ...
	}
	if (jamin1[0]==0x1A) {
		switch (jamin1[1]) {
			case 0x00:
				DWORD TickCount = GetTickCount();
				TickCount = TickCount/55;
				jamin1[3]=(unsigned short) (TickCount/0x10000L);
				jamin1[4]=TickCount%0x10000L;
				return;
		}
	}
	else if (jamin1[0]==0x21) {
	}

	char buf[100];
  sprintf(buf,"Jamint int-%2X and AX=%04X not emulated ... please add !",jamin1[0],jamin1[1]);
	AfxMessageBox(buf,MB_OK);
}

// nieuwe versie van routines die vaak in OVL's gebruikt worden (moet wegvallen OVLxxxx.C)

extern "C" void getsysprNew(short int lsttype, short int *form_dat, short int *pmode, short int *pprt) 
{
  char LstBuf[16];
  short int papnr, i, j,pdflandscape_=0;
  CString Cmd, Reply;

	if(lsttype==99) pdflandscape_=1;
  if (lsttype<1 || lsttype>30) lsttype=1; // if invalid #, use 1
  sysget(18000+(lsttype-1)*16,16,LstBuf);
  PrintListNr=lsttype;
  PrintPaperNr=LstBuf[0];
  PrintOverlayRef=LstBuf[1];
  PrintJobBits=*(unsigned short *)&LstBuf[2];
  PrinterNr=LstBuf[9];
  if (PrinterNr==0) {
    CString Cmd;
    Cmd.Format("GetIniKeyValue|Document-%03d_Settings|Printer",PrintListNr);
    CString Reply=JmsCmd(Cmd);
    PrinterNr=atol(Reply);
  }
  *pprt=1;   // doe of de printout op printer 1 komt (speelt geen rol meer)
  *pmode=1;  // doe of de printmode op 1 staat (speelt geen rol meer)
  
  form_dat[0]=2480; form_dat[1]=3507; form_dat[2]=0; form_dat[3]=118; form_dat[4]=118; form_dat[5]=118; form_dat[6]=118; form_dat[7]=4;
  

	if (pdflandscape_){// print op PDF, in LANDSCAPE is standaard Windows Layout
		form_dat[0]=3507; form_dat[1]=2400; form_dat[3]=0;form_dat[6]=0; form_dat[7]=2;
		form_dat[0]=4000;
		PrintJobBits|=0x04; PrintPaperNr=0;
		goto AdjustAndReturn;   
	}
  if (PrintPaperNr==0) goto AdjustAndReturn;   // print op PDF, is standaard Windows Layout
  Cmd.Format("GetIniKeyValue|Paper-%03d_Settings|LayoutData",PrintPaperNr);
  Reply=JmsCmd(Cmd).MakeUpper();
  if (Reply.GetLength()==0) goto AdjustAndReturn;  // gebruik de standaard windows layout
  // bv.:  2850|3600|-200|200|0|240|300|L
  j=0;
  for (i=0; i<7; i++) {
    form_dat[i]=atol(Reply.Mid(j));
    j=Reply.Find('|',j);
    if (j==-1) break;
    j++;
  }
  if (j==-1) goto AdjustAndReturn;
 
  switch (Reply.GetAt(j)) {
    case 'R':
      form_dat[7]=0;
      break;
    case 'K':
      form_dat[7]=1;
      break;
    case 'S':
      form_dat[7]=2;
      break;
    case 'E':
      form_dat[7]=3;
      break;
    case 'L':
      form_dat[7]=5;
      break;
  // W moet 4 geven, maar dat is de default (zie hoger)
  //sysget(2384+papnr*16,16,form_dat);
  }
AdjustAndReturn:;
  if (form_dat[7]!=1 && (lsttype>=7 && lsttype<=30 && lsttype!=13)) {
    form_dat[6]=0;
  }
}

extern "C" void getsyspr(short int lsttype,short int *form_dat, short int *pmode, short int *pprt)
{
  char Old2New[20]={1,1,2,2,2,2,2,3,2,10,2,5,4,2,9,5,5,2,2,2};
  
  if (lsttype>=1 && lsttype<=20) lsttype=Old2New[lsttype-1];  // remap to new type (1->20)
  else lsttype=1;
  getsysprNew(lsttype,form_dat,pmode,pprt);
}



// CopyHtml() - Copies given HTML to the clipboard.
// The HTML/BODY blanket is provided, so you only need to
// call it like CallHtml("<b>This is a test</b>");

void CopyHTML(char *html) {
    // Create temporary buffer for HTML header...
    char *buf = new char [400 + strlen(html)];
    if(!buf) return;

    // Get clipboard id for HTML format...
    static int cfid = 0;
    if(!cfid) cfid = RegisterClipboardFormat("HTML Format");

    // Create a template string for the HTML header...
    strcpy(buf,
        "Version:0.9\r\n"
        "StartHTML:00000000\r\n"
        "EndHTML:00000000\r\n"
        "StartFragment:00000000\r\n"
        "EndFragment:00000000\r\n"
        "<html><body>\r\n"
        "<!--StartFragment -->\r\n");

    // Append the HTML...
    strcat(buf, html);
    strcat(buf, "\r\n");
    // Finish up the HTML format...
    strcat(buf,
        "<!--EndFragment-->\r\n"
        "</body>\r\n"
        "</html>");

    // Now go back, calculate all the lengths, and write out the
    // necessary header information. Note, wsprintf() truncates the
    // string when you overwrite it so you follow up with code to replace
    // the 0 appended at the end with a '\r'...
    char *ptr = strstr(buf, "StartHTML");
    wsprintf(ptr+10, "%08u", strstr(buf, "<html>") - buf);
    *(ptr+10+8) = '\r';

    ptr = strstr(buf, "EndHTML");
    wsprintf(ptr+8, "%08u", strlen(buf));
    *(ptr+8+8) = '\r';

    ptr = strstr(buf, "StartFragment");
    wsprintf(ptr+14, "%08u", strstr(buf, "<!--StartFrag") - buf);
    *(ptr+14+8) = '\r';

    ptr = strstr(buf, "EndFragment");
    wsprintf(ptr+12, "%08u", strstr(buf, "<!--EndFrag") - buf);
    *(ptr+12+8) = '\r';

    // Now you have everything in place ready to put on the
    // clipboard.

    // Open the clipboard...
    if(OpenClipboard(0)) {
        
        // Empty what's in there...
        EmptyClipboard();
        
        // Allocate global memory for transfer...
        HGLOBAL hText = GlobalAlloc(GMEM_MOVEABLE |GMEM_DDESHARE, strlen(buf)+4);
        
        // Put your string in the global memory...
        char *ptr = (char *)GlobalLock(hText);
        strcpy(ptr, buf);
        GlobalUnlock(hText);
        
        ::SetClipboardData(cfid, hText);
        
        CloseClipboard();
        // Free memory...
        GlobalFree(hText);
        
    }

    // Clean up...
    delete [] buf;
}

int WINAPI WinMain(	HINSTANCE hInstance,
					HINSTANCE hPrevInstance,
					LPTSTR    lpCmdLine,
					int       nCmdShow)
{
	/*
	OpenClipboard(0);
  EmptyClipboard(); 

	CString msg = "Hallo\r\n";
	msg = "Version:0.9\r\n";
	msg+= "StartHTML:71\r\n";
	msg+= "EndHTML:170\r\n";
	msg+= "StartFragment:140\r\n";
	msg+= "EndFragment:160\r\n";
	msg+= "StartSelection:140\r\n";
	msg+= "EndSelection:160\r\n";
	msg+= "<!DOCTYPE>\r\n";
	msg+= "<HTML>\r\n";
	msg+= "<HEAD>\r\n";
	msg+= "<TITLE>The HTML Clipboard</TITLE>\r\n";
	msg+= "<BASE HREF=\"http://sample/specs\">\r\n";
	msg+= "</HEAD>\r\n";
	msg+= "<BODY>\r\n";
	msg+= "<!--StartFragment -->\r\n";
	msg+= "<P>The Fragment</P>\r\n";
	msg+= "<!--EndFragment -->\r\n";
	msg+= "</BODY>\r\n";
	msg+= "</HTML>\r\n";

	UINT format = ::RegisterClipboardFormat("HTML Format");
	CSharedFile sf(GMEM_MOVEABLE|GMEM_SHARE|GMEM_ZEROINIT);
	sf.Write(msg,msg.GetLength());
	//sf.Close();
/*
size_t size = sizeof(TCHAR)*(1+msg.GetLength());
	HGLOBAL hResult = GlobalAlloc(GMEM_MOVEABLE, size);
	LPTSTR lptstrCopy = (LPTSTR)GlobalLock(hResult);
	memcpy(lptstrCopy, msg.GetBuffer(), size);
	GlobalUnlock(hResult);
	if ( ::SetClipboardData( format, hResult ) == NULL ) {

	if (::SetClipboardData(CF_TEXT,sf.Detach())) {
	  bool fail=true;
	}
	CloseClipboard();

*/
  //_CrtSetBreakAlloc(564); //om het 564 alloc na te kijken ..
  //_CrtSetBreakAlloc(551); //om het 558 alloc na te kijken ..
	
	prc_num[1]=1; // Laat F1 voor EXIT toe ...
	if (__argc>=4) {
    NoMessageBoxes=true;
		prc_num[1]=0; // vanuit JMS
	}

	ThisPostNr=1; ThisScreenNr=1;
	if (__argc>=3) {
		int parm=atoi(__argv[2]);
		if (parm>=1 && parm<=4) ThisScreenNr=parm;
    parm=atoi(__argv[1]);
		if (parm>=1 && parm<=100) ThisPostNr=parm;
	}
	if (__argc==3 && ThisPostNr==1 && ThisScreenNr==4) {
		JMC4TEST=1;
		__argc=1; // JMC 1 4 om de kassa te testen ...
	}

	//CopyHTML("<pre>test\r\nikke\r\n</pre>");
  if (__argc>=3) {
    moinit(1|OptionSTO|OptionAddExtraSTO,-1);  // -2 om scherm te 'hiden' 
	}
	else {
		moinit(1|OptionSTO|OptionAddExtraSTO,0);  // -2 om scherm te 'hiden' -1 om visible te zijn (in JMS)
	}

	SetProgramName("Jama-Code");
	CString ConsoleTitle;
	if (__argc>=4) {
		ConsoleTitle=__argv[3];
		ConTitle((char *)(LPCTSTR)ConsoleTitle);
	}
	if (__argc==1 && ThisPostNr==1 && ThisScreenNr==4) ConTitle("JMC FOR KASSA");

  int MMFIx=0+(ThisPostNr-1)*5+ThisScreenNr; // Off + 0 is JMH, +1 ... +4 voor de JMC's (per screen)
  procid=MMFIx;

	errnum=1;
  CreateSharedMem(MMFIx);

  cls();
	if (__argc>=4 && ConsoleTitle.Left(3).CompareNoCase("JMD")!=0) {
		CString JmhName;
		JmhName.Format("JMH - Jamadata Hub - Post-%03d",ThisPostNr);
		ExecJamaLink("S","",MMFIx,NULL,(char *)(LPCTSTR)JmhName,&DoExit); // terminal nummer niet belangrijk ... windows title werd hierboven al ingesteld
		//Sleep(5000); // wacht 1 second om de JMS dit venster te laten vinden, anders start de communicatie maar weet hij niet van wie het pakket komt !
  }
  if (__argc==1 || (__argc==3 && ThisPostNr==1 && ThisScreenNr==1) || __argc>3) { // standalone gebruik (om te testen) of JMC in JMD
    pOvlExitRout=&ovlexit;
    closestr("#");
  }
	if (__argc==3 && ThisPostNr==1 && ThisScreenNr==1) {
		WndShowWindow(0,SW_SHOW);
	}
  SetProcessFileCallBack(&ProcessSplFile);
  RunOvlSystem();
  if (pSharedMem) {
    UnmapViewOfFile(pSharedMem);
    CloseHandle(SharedMemMutex);
    CloseHandle(JMSProcEvent);
    CloseHandle(JMSDoneEvent);
    CloseHandle(OVLProcEvent);
    CloseHandle(OVLDoneEvent);
    CloseHandle(hMMFile);
  }
	_moexit(0);
	return 0;
}
