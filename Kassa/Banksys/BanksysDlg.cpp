// BanksysDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Banksys.h"
#include "BanksysDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CMySocket SesSock;
extern unsigned short int KissTable[256];


/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBanksysDlg dialog

CBanksysDlg::CBanksysDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CBanksysDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CBanksysDlg)
	m_ComPort = _T("");
	m_Status = _T("");
	m_Logging = FALSE;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CBanksysDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBanksysDlg)
	DDX_CBString(pDX, IDC_COMBO1, m_ComPort);
	DDX_Text(pDX, IDC_EDIT1, m_Status);
	DDX_Check(pDX, IDC_DEBUG, m_Logging);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CBanksysDlg, CDialog)
	//{{AFX_MSG_MAP(CBanksysDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DESTROY()
	ON_WM_TIMER()
	ON_WM_WINDOWPOSCHANGING()
	ON_CBN_EDITCHANGE(IDC_COMBO1, OnChangeComPort)
	ON_BN_CLICKED(IDC_TEST, OnTest)
	ON_BN_CLICKED(IDC_DEBUG, OnLogging)
	ON_CBN_SELCHANGE(IDC_COMBO1, OnChangeComPort)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// VIC-Messages contents ID's

struct sVICMessageContents {
  int Nr;
	int Len;
	char *Name;
} VicMessageContents[100] = {
   1, 0,"vic_bit_map",  // lengte niet zo te bepalen
	 2, 4, "term_id",
	 3, 3, "vic_tx_amt",
	 4, 2, "iep_tx_inc",
	 5, 1, "lg_cust",
	 6, 0, "pdv_clct_info", // len niet voorzien (is voor collect)
	 7, 2, "pdv_clct_nr",
	 8, 4, "pdv_gen_tx_nb",
	 9, 4, "pdv_state",
	10, 3, "pur_bal",
	11,24,"card_id_disp",
	12, 1,"tx_type",
	13, 4,"sam_gen_tot",
	16, 1,"vic_card_ind",
	17, 2,"vic_cmd_code",
	18, 4,"vic_config_clct_amt",
	19, 4,"pdv_state_mask",
	20, 2,"vic_to",
	21, 4,"vic_tx_id",
	22, 1,"vic_msg_type",
	23, 2,"curcy",
	25, 1,"vic_cust_ind",
	31, 3,"vmc_type",
	36,-1,"vic_data",
	37, 1,"vic_block_nr",
	38, 1,"vic_more_block_ind",
	39, 0,"vic_action_ind",  // niet verwacht
	44,12,"vic_file_name",   
	45, 1,"pdv_journ_pct_full",
	125, 3,"<tx>vic_tx_amt",
	126, 2,"<tx>curcy",
	131,-1,"CCM_field",
	142,19,"iso2_track",
	143, 2,"operator_nr",
	144, 2,"function_cc",
	145,-1,"ticket_data",
	146, 2,"ecr_nr",
	155,-1,"application_info",
	156, 2,"more_info_ind",
	157,-1,"counter_tab_pa",
	169, 3,"additional_amount",
	170, 2,"transaction_protocol",
	171,16,"vic_bit_map_application_id",
	172, 4,"Transaction_identifier",
	173, 7,"Date_and_time",
	174, 2,"brand_id",
	175, 1,"hardware_type",
	176, 2,"cvm",
	177, 2,"cvc2",
	178,-1,"brand_name",
	179, 1,"vic_version"
};

struct sVICMessageInfo {
  BOOL Used;
	int Len;
	unsigned char *Data;
};

struct sVICReceived{
 char ProtocolId[3];
 char vic_msg_code[3];
 struct sVICMessageInfo Info[400];
} VICReceived;

/////////////////////////////////////////////////////////////////////////////
// CBanksysDlg message handlers

BOOL CBanksysDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	//ShowWindow(SW_HIDE);

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here

 	comref=INVALID_HANDLE_VALUE;
	LogRef=INVALID_HANDLE_VALUE;
	pSrvSock = new CMySocket(this);
	SesSock.m_pBanksysDlg=this;
	CheckPayCardBusy=FALSE;
	ComCheckBusy=FALSE;
	State=0;
	OkPressedCount=0;
	vic_tx_id=246;

	ReadRegistrySettings();
	UpdateData(FALSE);
   
	OnChangeComPort();
  KissWriteSEQNr=0xFF;
	KissReadSEQNr=0xFF;
	KissPrevAckedSEQNr=0xFF; 
	KissReadLen=0;
	memset(KissReadFrame,0,sizeof(KissReadFrame));
	TickTimeLastByteReceived=0;
	TickTimeStarted=GetTickCount();
	VICMessageReceivedLen=0;
	MobielAllowed=FALSE;
	VisaMCAllowed=FALSE;
	AllCardsAllowed=FALSE;
	MaaltijdChequeAllowed = FALSE;
	EcoChequeAllowed = FALSE;
	CadeauChequeAllowed = FALSE;
	ConsumptieBonAllowed = FALSE;
#if _DEBUG
	m_Logging=true;
	UpdateData(FALSE);
#endif
  
  //KissSEQNr=5;
	//SendVICMessage("\xAB",1);

	SetTimer(1,TIMER,0);
	SetTimer(2,COM_CHECK_TIMER,0);

#ifndef _DEBUG
	ShowWindow(SW_MINIMIZE);
#endif

	SendVIC_vmc_cancel(1);

	return TRUE;  // return TRUE  unless you set the focus to a control
}


void CBanksysDlg::StartListening()
{
 	pSrvSock->Create(4999,SOCK_STREAM,NULL);
	pSrvSock->Listen(1);

}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CBanksysDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CBanksysDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CBanksysDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	pSrvSock->Close();
  if (pSrvSock) delete pSrvSock;
}

void CBanksysDlg::ProcCommand(CMySocket *pSock, char *cmd)
{
  TRACE(cmd);
	
	switch (cmd[0]) {
	  case '*':
			memcpy(Amount,&cmd[1],sizeof(Amount));
			State=1;
			break;
		case '?':
			pSock->Send("-Banksys-Terminal: OK\r\n",23,0); // LET OP : AANTAL BYTES MOET KLOPPEN !!! incl. de \r\n
			break;
	}
}

void CBanksysDlg::CheckPayCard()
{
	char buf[100], brand_name[23+1], *p1, *p2, *val, *s;
	int i, j, k,kk;
	double amt;

	if (State==0 && VICMessageReceivedLen) {
	  VICParseReceivedMessage();
	  VICMessageReceivedLen=0;
  }

	if (State==1) {
	  if (!SendVIC_debit_request()) {
			SendToKassa("Transmissie fout...\r\n");
			SesSock.Close();
			SesSock.m_hSocket=INVALID_SOCKET;
			State=0;
		}
		else {
			SendToKassa("!LOCK\r\n");
			SendToKassa("-Wacht op kaart/PIN...\r\n");
		  State=2;
		}
	}

	if (State==2 && VICMessageReceivedLen) {
 
	  VICParseReceivedMessage();
		if (_strcmpi(VICReceived.vic_msg_code,"PD")==0 || _strcmpi(VICReceived.vic_msg_code,"PE")==0) {
		  int termid=GetBCD(VICReceived.Info[2].Data,8);
			int iep_tx_inc=GetBCD(VICReceived.Info[4].Data,4);
			if (iep_tx_inc==5015) {
			  SendToKassa("!CHECK");
				iep_tx_inc=0;
			}
			if (iep_tx_inc==0) {
											// betaling is aanvaard. Druk nu alles af
				for (i=0; i<VICReceived.Info[178].Len; i++) {
				  if (i==(sizeof(brand_name)-1)) break;
					brand_name[i]=VICReceived.Info[178].Data[i];
				}
				brand_name[i]=0;

				if (brand_name[0]==0) { // no brand_name with this SW-release
					if (VICReceived.Info[171].Data[15]&0x01) strcpy_s(brand_name,sizeof(brand_name),":Bancontact");
					if (VICReceived.Info[171].Data[8]&0x40) strcpy_s(brand_name,sizeof(brand_name),":Bancontact");
					if (VICReceived.Info[171].Data[15]&0x02) strcpy_s(brand_name,sizeof(brand_name),":Maestro");
					if (VICReceived.Info[171].Data[15]&0x08) strcpy_s(brand_name,sizeof(brand_name),":Mobiel");
					if (VICReceived.Info[171].Data[15]&0x10) strcpy_s(brand_name,sizeof(brand_name),":Visa");
					if (VICReceived.Info[171].Data[15]&0x20) strcpy_s(brand_name,sizeof(brand_name),":EC/Mastercard");
					if (VICReceived.Info[171].Data[15]&0x40) strcpy_s(brand_name,sizeof(brand_name),":American Express");
					if (VICReceived.Info[171].Data[15]&0x80) strcpy_s(brand_name,sizeof(brand_name),":Diners");
					if (VICReceived.Info[171].Data[13]&0x04) strcpy_s(brand_name,sizeof(brand_name),":Aurora");
					if (VICReceived.Info[171].Data[10]&0x40) strcpy_s(brand_name,sizeof(brand_name),":Visa VPay");
					if (VICReceived.Info[171].Data[8]&0x02)  strcpy_s(brand_name,sizeof(brand_name),":PayFair");
					if (VICReceived.Info[171].Data[8]&0x04)  strcpy_s(brand_name,sizeof(brand_name),":Sodexo");
					if (VICReceived.Info[171].Data[8]&0x08)  strcpy_s(brand_name,sizeof(brand_name),":Edenred");
					if (VICReceived.Info[171].Data[7]&0x04)  strcpy_s(brand_name,sizeof(brand_name),":RES");
					if (VICReceived.Info[171].Data[7]&0x20)  strcpy_s(brand_name,sizeof(brand_name),":ORES");
					if (VICReceived.Info[171].Data[6]&0x10)  strcpy_s(brand_name,sizeof(brand_name),":Smart Pay");
					if (brand_name[i]==0) {
						brand_name[0]=':'; brand_name[1]='x';
						for (int j=0; j<10; j++) {
							sprintf(&brand_name[2+j*2],"%02X",VICReceived.Info[171].Data[6+j]);
						}
						// strcpy_s(brand_name,sizeof(brand_name),":undefined!");
					}
				}

				SendToKassa("Betaling uitgevoerd:\r\n");
				SendToKassa("%---------------------------\r\n");
				
				val="????";  // betaald bedrag
				if (VICReceived.Info[126].Data[0]==0x09 && VICReceived.Info[126].Data[1]==0x78) val="EURO";
				amt=GetInt(VICReceived.Info[125].Data,6)/100.;
				sprintf_s(buf,sizeof(buf),"  %9.2f %s %s\r\n",amt,val,brand_name);
				for (i=2; i<12; i++) {
				  if (buf[i]>' ') {
					  buf[i-2]='%';
						break;
					}
				}
				SendToKassa(&buf[i-2]);

				if (VICReceived.Info[11].Used) {   // cardid info (nr).
				  j=0;
					buf[j++]='%'; // print info !
					buf[j++]=' ';
					for (i=0; i<VICReceived.Info[11].Len; i++) buf[j++]=VICReceived.Info[11].Data[i];
					buf[j++]='\r';
					buf[j++]='\n';
					buf[j++]=0;
					SendToKassa(buf);
				}

				buf[0]='%';			// Terminal ID
				sprintf_s(&buf[1],sizeof(buf)-1," TERMINAL ID: %08d\r\n",termid);
				SendToKassa(buf);
				SendToKassa("%---------------------------\r\n");

				if (VICReceived.Info[145].Len  && !(VICReceived.Info[171].Data[15]&0x01) && !(VICReceived.Info[171].Data[15] & 0x02) && !(VICReceived.Info[171].Data[8]&0x40)) { // geen terminalticket afdrukken bij bancontact/maestro (=niet verplicht)
					j=0; s=(char *)VICReceived.Info[145].Data;
					for (i=0; i<VICReceived.Info[145].Len; i++, s++) {
					  if (j==0) buf[j++]='%';
						if (*s==0x04 || *s==0x0C || *s==0x0E || *s==0x11 || *s==0x13 || *s==0x14 || *s==0x18) continue;
						if (*s==0x1B) {s++; i++; continue;}
						if (*s==0x10) *s=' ';
					  if (*s==0x0B) {
						  s++; i++;
							for (k=0; k<*s; k++) SendToKassa("%\r\n");
							continue;
						}
						
						buf[j++]=*s;
						if (*s=='\n') {
						  buf[j]=0;
							for(kk=1;kk<j;kk++) if(buf[kk]!=' ' && buf[kk]!='\r' && buf[kk]!='\n') break;
							if(kk<j) SendToKassa(buf);
							j=0;
						}
					}
					if (j>1) {
					  buf[j++]='\r'; buf[j++]='\n'; buf[j]=0;
						for(kk=1;kk<j;kk++) if(buf[kk]!=' ' && buf[kk]!='\r' && buf[kk]!='\n') break;
						if(kk<j) SendToKassa(buf);
					}
				}

				i=1;
			  if (VICReceived.Info[171].Data[15]&0x01) i=1;  // bancontact
				if (VICReceived.Info[171].Data[8]&0x40)  i=1;	 // bancontact EMV
			  if (VICReceived.Info[171].Data[15]&0x08) i=3;  // Mobiel
			  if (VICReceived.Info[171].Data[15]&0xF2) i=2;  // VISA / Mastercard / MAESTRO
			  if (VICReceived.Info[171].Data[14]&0x01) i=2;  // JBC
			  if (VICReceived.Info[171].Data[13]&0x04) i=2;  // ??
			  if (VICReceived.Info[171].Data[10]&0x40) i=2;	 // Visa VPay
				if (VICReceived.Info[171].Data[8]&0x02)  i=6;	 // PayFair
				if (VICReceived.Info[171].Data[8]&0x04)  i=4;	 // Sodexo
				if (VICReceived.Info[171].Data[8]&0x08)  i=5;	 // Edenred
				if (VICReceived.Info[171].Data[7]&0x04)  i=7;	 // RES
				if (VICReceived.Info[171].Data[7]&0x20)  i=7;	 // ORES
				if (VICReceived.Info[171].Data[6]&0x10)  i=7;	 // Smart Pay
				sprintf_s(buf,sizeof(buf),"#%1d%23s\r\n",i,brand_name);
				SendToKassa(buf);
			}
			else {
			  p1="TECHNICAL PROBLEM";
				p2="";
				switch (iep_tx_inc) {
				  case 4001: p1="Time-out klant"; p2="Geen kaart ingebracht"; break;
				  case 4002: p1="Time-out klant"; p2="Geen bevestiging"; break;
				  case 4005: p1="Saldo ontoereikend"; p2=""; break;
				  case 4008: p2 = "Invalid message length"; break;
				  case 4009: p1="Terminal niet klaar"; p2="Probeer opnieuw"; break;
				  case 4011: p1="Time-out klant"; p2="Op kaart herlezen"; break;
				  case 5001: p1="Technisch probleem"; p2=""; break;
				  case 5002: p1="Transactie geweigerd"; p2="door host"; break;
				  case 5003: p1="Dubbele transactie"; p2=""; break;
				  case 5004: p1="Technisch probleem"; p2="op de host"; break;
				  case 5006: p1="Stop Klant"; p2=""; break;
				  case 5009: p1="Transactie geweigerd"; p2="door terminal"; break;
				  case 5010: p1="Communicatieprobleem"; p2=""; break;
				  case 5012: p1="Saldo ontoereikend"; p2=""; break;
				  case 5013: p1="Transactie geweigerd"; p2="door terminal"; break;
				  case 5014: p1="Transactie geweigerd"; p2="door de kaart"; break;
				}
				SendToKassa("!UNLOCK\r\n");
				SendToKassa("*** NIET betaald ***\r\n");
				if (*p1) {
  				sprintf_s(buf,sizeof(buf),"%s\r\n",p1);
	  			SendToKassa(buf);
				}
				if (*p2) {
  				sprintf_s(buf,sizeof(buf),"%s\r\n",p2);
	  			SendToKassa(buf);
				}
				sprintf_s(buf,sizeof(buf),"(%d)\r\n",iep_tx_inc);
  			SendToKassa(buf);
			}
		}
		else {
			SendToKassa("!UNLOCK\r\n");
			SendToKassa("Transmissie fout ...\r\n");
		}

		VICMessageReceivedLen=0;

		SesSock.Close();
		SesSock.m_hSocket=INVALID_SOCKET;
		State=0;
	}
}

void CBanksysDlg::OnTimer(UINT nIDEvent) 
{
	if (nIDEvent==1) {

		if (m_Logging && LogRef==INVALID_HANDLE_VALUE) {
		  LogRef=CreateFile("banksys.log",GENERIC_WRITE,0,NULL,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);
			if (LogRef==INVALID_HANDLE_VALUE) m_Logging=false;
		}
		if (!m_Logging && LogRef!=INVALID_HANDLE_VALUE) {
		  CloseHandle(LogRef);
			LogRef=INVALID_HANDLE_VALUE;
		}

	  if (!CheckPayCardBusy) {
		  CheckPayCardBusy=TRUE;
			CheckPayCard();
			CheckPayCardBusy=FALSE;
		}
	}

	if (nIDEvent==2) {
  	CritComCheck.Lock();
		if (!ComCheckBusy) {
		  ComCheckBusy=TRUE;
			CritComCheck.Unlock();
			ComCheck();
			ComCheckBusy=FALSE;
		}
		else CritComCheck.Unlock();
	}

	CDialog::OnTimer(nIDEvent);
}

void CBanksysDlg::OnWindowPosChanging(WINDOWPOS FAR* lpwndpos) 
{
	/*
	if (lpwndpos->flags & SWP_SHOWWINDOW) {
		lpwndpos->flags &= ~SWP_SHOWWINDOW;
		PostMessage(WM_WINDOWPOSCHANGING, 0, (LPARAM)lpwndpos);
		ShowWindow(SW_HIDE);
	}
	else
	*/
		CDialog::OnWindowPosChanging(lpwndpos);
	
}

void CBanksysDlg::OnChangeComPort() 
{
	UpdateData(TRUE);
  pSrvSock->Close();
	if (OpenComPort()) {
		StartListening();
		m_Status="OK. Server active!";
	}
	else {
		m_Status="COM-port illegal!";
	}
	UpdateData(FALSE);
	WriteRegistrySettings();
}

bool CBanksysDlg::OpenComPort()
{
	DCB m_dcb;
	COMMTIMEOUTS commTimeout;

	comref=INVALID_HANDLE_VALUE;
	comref=CreateFile(m_ComPort, GENERIC_WRITE | GENERIC_READ,
					0, // exclusive access
					NULL, // no security
					OPEN_EXISTING,
					0, // no overlapped I/O
					0); // null template 

	if (comref!=INVALID_HANDLE_VALUE) {
	  SetCommMask(comref,0);
    SetupComm(comref, 350, 350); // set buffer sizes
  	GetCommState(comref, &m_dcb);
 		m_dcb.ByteSize = 8;
  	m_dcb.fBinary = TRUE;
		m_dcb.fParity = FALSE;
  	m_dcb.Parity = NOPARITY; 
 		m_dcb.StopBits = ONESTOPBIT;
 		m_dcb.fAbortOnError = TRUE;
		m_dcb.fOutxDsrFlow=FALSE;
		m_dcb.fRtsControl=RTS_CONTROL_DISABLE;
  	m_dcb.BaudRate = CBR_9600;;
		SetCommState(comref, &m_dcb);
		if(GetCommTimeouts(comref, &commTimeout)) {
			commTimeout.ReadIntervalTimeout=5; // max 10 msec tussen 2 character input
			commTimeout.ReadTotalTimeoutConstant=25; // max 25 msec wacht op input
			commTimeout.ReadTotalTimeoutMultiplier=0; 
			commTimeout.WriteTotalTimeoutMultiplier=0;
			commTimeout.WriteTotalTimeoutConstant =1000; // 1 seconden time-out 
			SetCommTimeouts(comref, &commTimeout);
		}
		return true;
	}
	return false;
}


void CBanksysDlg::ReadRegistrySettings()
{
  HKEY hk; 
  char buf[200];
  unsigned long size;

  size=sizeof(buf); 
  if (!RegCreateKey(HKEY_CURRENT_USER,"SOFTWARE\\Jamadata\\Banksys", &hk)) {
		size=sizeof(buf)-1; 
    if (!RegQueryValueEx(hk,"COM-Port",0,0,(unsigned char *)buf,&size)) {
		  buf[size]=0;
			m_ComPort=buf;
		}
		else m_ComPort="Com2";
    if (!RegQueryValueEx(hk,"Logging",0,0,(unsigned char *)buf,&size)) {
			if (buf[0]=='1') m_Logging=true;
		}
    RegCloseKey(hk);
  }
}

void CBanksysDlg::WriteRegistrySettings()
{
  HKEY hk; 
  CString KeyName;
	char buf[100];


  KeyName="SOFTWARE\\Jamadata\\Banksys\\";
  if (!RegCreateKey(HKEY_CURRENT_USER,KeyName, &hk)) {
    RegSetValueEx(hk,"COM-Port",0,REG_SZ,(const unsigned char *)m_ComPort.operator LPCTSTR(),m_ComPort.GetLength());
		buf[0]='0'; buf[1]=0;
		if (m_Logging) buf[0]='1';
		RegSetValueEx(hk,"Logging",0,REG_SZ,(const unsigned char *)buf,1);
		RegCloseKey(hk);
  }  
}

BOOL CBanksysDlg::SendVICMessage(char *vic_msg_code)
{
  int i, j, FrameLen, retry;
	double AnswerTimeOut;
	unsigned char Frame[MAX_KISS_FRAME_LEN], CRC_lsb, CRC_msb, table_index;
	BOOL Acked;
	DWORD TickStartWriteTim;
	
 	DumpLog(" ","",0);
	FrameLen=0;
	Frame[FrameLen++]=STX;
	Frame[FrameLen++]=KissWriteSEQNr;
  Frame[FrameLen++]=0x01;							// always 0x01 0x07
	Frame[FrameLen++]=0x07;
  Frame[FrameLen++]=vic_msg_code[0];  // see vic implementation
	Frame[FrameLen++]=vic_msg_code[1];
	
  for (i=0; i<6; i++) { // 6 keer 8 bytes mogelijk ? 
	  for (j=0; j<8; j++) {
		  Frame[FrameLen++]=vic_bit_map[i*8+j];
		}
		if ((vic_bit_map[i*8]&0x80)==0) break;  // bit 1, bit 65, bit 133, ... geven aan dat er nog een serie van 8 bytes komt
	}
  
	// Copy vic_core 2 Frame maar let op STX, ETX en DLE. Die moeten een pre-DLE (0x10) krijgen (en lengte verhogen !)
  for (i=0; i<vic_core_len; i++) {
	  if (vic_core[i]==STX || vic_core[i]==ETX || vic_core[i]==DLE) Frame[FrameLen++]=DLE;
		Frame[FrameLen++]=vic_core[i];
	}
  Frame[FrameLen++]=ETX;

	CRC_lsb=0; CRC_msb=0;

  for (i=1; i<FrameLen; i++) {
  	table_index = CRC_lsb ^ Frame[i];
    CRC_lsb = CRC_msb ^ (KissTable[table_index]%256);
    CRC_msb = 00 ^ (KissTable[table_index]/256);
	}
	Frame[FrameLen++]=CRC_lsb;
	Frame[FrameLen++]=CRC_msb;

//  DumpLog("O",Frame,FrameLen);	
//	if (len>MAX_KISS_FRAME_LEN-200) return FALSE; // zou niet mogelijk zijn


  AnswerTimeOut=500+((1000*FrameLen*10)/9600)*2;
	if (AnswerTimeOut>900) AnswerTimeOut=900;
	Acked=FALSE;

	for (retry=0; retry<1+ACK_RETRY; retry++) {
	  TickStartWriteTim=GetTickCount();
		KissWriteResponse=0;
		WriteCom(Frame,FrameLen);
		while (!Acked) {
      if (KissWriteResponse==NAK) break; // resent immediatly
			if (KissWriteResponse==ACK) {
			  if (KissWriteAckedSeq==KissWriteSEQNr) Acked=TRUE;
				break;
			}
			if (KissWriteResponse==WAK) TickStartWriteTim=GetTickCount(); // othet party cannot deliver frame tot VIC-layer, restrat wait
  		if ((GetTickCount()-TickStartWriteTim)>AnswerTimeOut) break;
			ProcessAllMessages();
			Sleep(25);
		}
    if (Acked) break;
	}

	if (!Acked) return FALSE;

  if (++KissWriteSEQNr==0xFF) KissWriteSEQNr=0; // xFF mag alleen bij opstarten van het systeem

  return TRUE;
}

void CBanksysDlg::ComCheck()
{
	DWORD readbytes;
	int ix, i;
	unsigned TmpInpBuf[MAX_KISS_FRAME_LEN];
	
	ReadFile(comref,TmpInpBuf,sizeof(TmpInpBuf),&readbytes,NULL);
	if (readbytes) {
	  TickTimeLastByteReceived=GetTickCount();
	  if (readbytes+KissReadLen>sizeof(KissReadFrame)) KissReadLen=0;
		if (readbytes<sizeof(KissReadFrame)) {
  	  memcpy(&KissReadFrame[KissReadLen],TmpInpBuf,readbytes);
			KissReadLen+=readbytes;
		}
	}

	ix=0;
	if (KissReadFrame[0]==NAK || KissReadFrame[0]==WAK) {
	  KissWriteResponse=KissReadFrame[0];
	  ix++;
	  DumpLog("R",KissReadFrame,ix);
	}
	else if (KissReadFrame[0]==ACK && KissReadLen>=2) {
	  KissWriteResponse=ACK;
		KissWriteAckedSeq=KissReadFrame[1];
		ix+=2;
	  DumpLog("R",KissReadFrame,ix);
	}
	else if (KissReadFrame[0]==STX) {
    for (i=2; i<KissReadLen-2; i++) { // vooraan 2 bytes en achteraan moeten 2 CRC bytes staan
		  if (KissReadFrame[i]==ETX && KissReadFrame[i-1]!=DLE) {
  		  DumpLog("R",KissReadFrame,i+3);
			  if (ProcessKissReadFrame(i+3)) ix+=(i+3); // Enkel wissen wanneer Frame naar VICmessage gekopieerd is
				TickTimeLastByteReceived=0; // dus ook wanneer VICmessage nog niet leeg was.
				break;
			}
		}
	}
  if (ix>0) {
	  if (ix>KissReadLen) ix=KissReadLen; // kan normaal nooit
		if (ix<KissReadLen) {
		  memmove(KissReadFrame,&KissReadFrame[ix],KissReadLen-ix);
		}
	  KissReadLen-=ix;
  }

	if (KissReadLen==0) {
		TickTimeLastByteReceived=0;
	}
  else if (TickTimeLastByteReceived) {
 		if ((GetTickCount()-TickTimeLastByteReceived)>200) {
		  SendNAK();
			KissReadLen=0;
			TickTimeLastByteReceived=0;
		}
	}
}

BOOL CBanksysDlg::ProcessKissReadFrame(int FrameLen)  
{
  int i;
	unsigned CRC_lsb, CRC_msb, table_index;

	// STX is already checked

	CRC_lsb=0; CRC_msb=0;

  for (i=1; i<FrameLen-2; i++) {
  	table_index = CRC_lsb ^ KissReadFrame[i];
    CRC_lsb = CRC_msb ^ (KissTable[table_index]%256);
    CRC_msb = 00 ^ (KissTable[table_index]/256);
	}

	if (KissReadFrame[FrameLen-2]!=CRC_lsb || KissReadFrame[FrameLen-1]!=CRC_msb) {
	  SendNAK();
		return FALSE;
	}
	  
  if (KissReadSEQNr==0xFF) { // we restarted ourselfves, use any SEQNR we get ! ???
		KissReadSEQNr=KissReadFrame[1];
	}
	if (KissReadFrame[1]==0xFF) KissReadSEQNr=0xFF; // resync, next is 0

 	if (KissReadFrame[1]==KissReadSEQNr) {
	  if (VICMessageReceivedLen) {
		  SendWAK();  // buffer is nog niet vrij. Stuur continue WAK's naar andere kant
			return FALSE;
		}

		// Copy Frame 2 VicMessage maar let op DLE's, die moeten eruit !
		VICMessageReceivedLen=0;
		for (i=2; i<FrameLen-3; i++) {
			if (KissReadFrame[i]==DLE) i++;
		  VICMessageReceived[VICMessageReceivedLen++]=KissReadFrame[i];
		}
	  DumpLog("I",VICMessageReceived,VICMessageReceivedLen);	
	  SendACK(KissReadSEQNr);
  	if (++KissReadSEQNr==0xFF) KissReadSEQNr=0;
	}
  else if (KissReadFrame[1]==KissPrevAckedSEQNr) {
	  SendACK(KissPrevAckedSEQNr); // Ack was lost, just resend it !
	}

  return TRUE;
}

void CBanksysDlg::SendNAK()
{
  unsigned char byt = NAK;

	WriteCom(&byt,1);
}

void CBanksysDlg::SendWAK()
{
  unsigned char byt = WAK;

	WriteCom(&byt,1);
}

void CBanksysDlg::SendACK(unsigned char SEQNr)
{
  unsigned char byt[2];
	
	byt[0] = ACK;
	byt[1] = SEQNr;

	WriteCom(byt,2);
  KissPrevAckedSEQNr = SEQNr;
}

BOOL CBanksysDlg::WriteCom(void *s, int len)
{
	DWORD written;

	WriteFile(comref,s,len,&written,NULL);
	DumpLog("W",s,len);
  if ((int)written==len) return TRUE;
	return FALSE;
}

void CBanksysDlg::DumpLog(char *type, void *s, int len)
{
  DWORD written;
	unsigned char *byt;
	CString output, cstr;
  int i, msec;

  if (LogRef==INVALID_HANDLE_VALUE) return; 

  byt=(unsigned char *)s;
  output="";
	if (type[0]>' ') {
		if (type[1]==0) {
			msec=GetTickCount()-TickTimeStarted;
			output.Format("%5d-%s(%3d)=",msec,type,len);
		}
		else output.Format("   %-15s ",type);
		for (i=0; i<len; i++) {
			cstr.Format(" %02X",byt[i]);
			output=output+cstr;
		}
	}
	output+="\r\n";
  WriteFile(LogRef,output,output.GetLength(),&written,NULL);
}

void CBanksysDlg::ProcessAllMessages()
{
  MSG msg;

  while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)>0) {
    TranslateMessage(&msg); 
    DispatchMessage(&msg); 
  }
}

BOOL CBanksysDlg::SendVIC_vmc_cancel(int ExecuteAlways)
{
  if (ExecuteAlways) {
	VICClearFields();
	VICAddField("vmc_type");
	return SendVICMessage("VC");
  }
  else return true;

}

BOOL CBanksysDlg::SendVIC_debit_request()
{
  VICClearFields();
	VICAddField("vic_tx_amt");
//	VICAddField("card_id_disp");
	VICAddField("tx_type");
	VICAddField("vic_card_ind");
	VICAddField("vic_to");
	VICAddField("vic_tx_id");
	VICAddField("curcy");
	VICAddField("vic_cust_ind");
	if (MaaltijdChequeAllowed || EcoChequeAllowed || CadeauChequeAllowed || ConsumptieBonAllowed /* || AllCardsAllowed*/) VICAddField("vic_data"); // selectie kaarten
	VICAddField("operator_nr");
	if (!(MaaltijdChequeAllowed || EcoChequeAllowed || CadeauChequeAllowed || ConsumptieBonAllowed))	VICAddField("vic_bit_map_application_id");
	VICAddField("vic_version");
	return SendVICMessage("VD");
}

void CBanksysDlg::VICClearFields()
{
  memset(vic_bit_map,0,sizeof(vic_bit_map));
	memset(&VICReceived,0,sizeof(VICReceived));
	memset(&vic_core,0,sizeof(vic_core));
	vic_core_len=0;
	DumpLog("N","",0);
}

void CBanksysDlg::VICAddField(char *DataElem)
{
  int i,j, MsgIx=-1, prev_vic_core_len=vic_core_len;
	unsigned char buf[100];
	
  for (i=0; i<100; i++) {
	  if (_strcmpi(DataElem,VicMessageContents[i].Name)==0) break;
	}
	if (i<100) MsgIx=VicMessageContents[i].Nr;
  else {
	  CString cstr;
		cstr.Format("VICField name not found:%s !",DataElem);
		AfxMessageBox(cstr,MB_OK,0);
	  return;
	}

  i=(MsgIx-1)%8;
  j=0x80;
	while (i-->0) j/=2;
	i=(MsgIx-1)/8;
	vic_bit_map[i]|=j;
	
	for (i=0; i<6; i++) {											// oontroleer of het in het extended deel is
  	if (MsgIx>64*(i+1)) vic_bit_map[i*8]|=0x80;		// en verleng het b+ veld dan
	}

	switch (MsgIx) {
    case 3:
		  int amt;
			amt=0;
			for (i=0; i<12; i++) {
        if (Amount[i]>='0') break;
			}
			for (; i<12; i++) {
			  if (Amount[i]=='.') continue;
			  amt=amt*10+Amount[i]-'0';
			}
			MobielAllowed=FALSE; VisaMCAllowed=FALSE;AllCardsAllowed=FALSE;	MaaltijdChequeAllowed = FALSE;
			EcoChequeAllowed = FALSE;CadeauChequeAllowed = FALSE;ConsumptieBonAllowed = FALSE;
			if (Amount[12]=='P') MobielAllowed=TRUE;
			if (Amount[12]=='C') VisaMCAllowed=TRUE; // only creditcards
			if (Amount[12] == 'M') MaaltijdChequeAllowed = TRUE; // only maaltijdcheques
			if (Amount[12] == 'E') EcoChequeAllowed = TRUE; // only ecocheques
			if (Amount[12] == 'K') CadeauChequeAllowed = TRUE; // only cadeaucheques
			if (Amount[12] == 'U') ConsumptieBonAllowed = TRUE; // only consumptiebons
			if (Amount[12]=='A') AllCardsAllowed=TRUE; // alles toelaten 
			vic_core_dumpHEX(3,&amt);
			break;
		case 11:
		  vic_core_dump(24,"                         ");
			break;
		case 12:
		  vic_core_dump2BCD(4);
			break;
		case 16:
		  vic_core_dump2BCD(1);
			break;
		case 20:
      unsigned short is;
			is=30;
			vic_core_dumpHEX(2,&is);
			break;
		case 21:
		  vic_tx_id++;
		  vic_core_dumpHEX(4,&vic_tx_id);
			break;
		case 23:
		  vic_core_dump4BCD(978); // EURO
			break;
		case 25:
		  vic_core_dump2BCD(1);
			break;
		case 31:
		  vic_core_dump(3, "\x00\x00\x00");
		  break;
	    case 36:  // vic_data
			for (i = 0; i < 15; i++) buf[i] = 0;
			if (MaaltijdChequeAllowed) { vic_core_dump4BCD(9); buf[2] = 0x08; buf[3] = 0x05; memcpy(&buf[4], "200001#", 7);  vic_core_dump(9, &buf[2]); }
		  	else if (EcoChequeAllowed) { vic_core_dump4BCD(9); buf[2] = 0x08; buf[3] = 0x05; memcpy(&buf[4], "200002#", 7);  vic_core_dump(9, &buf[2]); }
			else if (CadeauChequeAllowed) { vic_core_dump4BCD(9); buf[2] = 0x08; buf[3] = 0x05; memcpy(&buf[4], "200003#", 7);  vic_core_dump(9, &buf[2]); }
			else if (ConsumptieBonAllowed) { vic_core_dump4BCD(9); buf[2] = 0x08; buf[3] = 0x05; memcpy(&buf[4], "200007#", 7);  vic_core_dump(9, &buf[2]); }
			else if (AllCardsAllowed)  { vic_core_dump4BCD(9); buf[2] = 0x08; buf[3] = 0x05; memcpy(&buf[4], "200001#", 7);  vic_core_dump(9, &buf[2]); } // bij betaalautomaat ook maaltijdcheques toelaten
			break;
		case 143:
      vic_core_dump4BCD(24);
			break;
		case 171:
			if (MobielAllowed) {
				for (i=0; i<15; i++) buf[i]=0;
				buf[ 6]=0x10;  // Smart Pay
				buf[15]=8; // Mobiel only
			}
			else if (MaaltijdChequeAllowed || EcoChequeAllowed || CadeauChequeAllowed || ConsumptieBonAllowed) { // alternatieve kaarten
				for (i=0; i<16; i++) buf[i]=0;
				buf[6] = 0x10;  // Smart Pay
				buf[8] = 0x4E;  // Sodexo (4) , Edenred (8), Payfair (2), BC_EMV (40)
			}
			else if (VisaMCAllowed) { // creditcards
			  for (i = 0; i < 16; i++) buf[i] = 0;
			  buf[10] = 0x40;  // V-pay
			  buf[14] = 0xFF;
			  buf[15] = 0xF2;  // all visa & maestro but NO Mobiel 
			}
			else if(AllCardsAllowed){// alles toelaten ook BC/MC
	  		  for (i=0; i<16; i++) buf[i]=0;
			  buf[ 6]=0x10;  // Smart Pay
			  buf[ 7]=0x24;  // RES (4), ORES (20)
			  buf[ 8]=0x4E;  // Sodexo (4) , Edenred (8), Payfair (2), BC_EMV (40)
		      buf[10]=0x40;  // V-pay
			  buf[14]=0xFF;
			  buf[15]=0xF3;  // all visa & maestro & BC but NO Mobiel 
			}
			else { // BC en MC
				for (i=0; i<16; i++) buf[i]=0;
				buf[ 6]=0x10;  // Smart Pay
				buf[ 7]=0x24;  // RES (4), ORES (20)
				buf[ 8]=0x4E;  // Sodexo (4) , Edenred (8), Payfair (2), BC_EMV (40)
				buf[15]=0x01;  // only BC/MisterCash 
			}
			vic_core_dump(16,buf);
			break;
		case 179:
		  vic_core_dump(1,"\x13");  //vic_core_dump2BCD(13); ; //vic_core_dumpHEX(1, "\x13"); //vic_core_dump2BCD(13); //
			break;
	  default:
			CString cstr;
			cstr.Format("VICField output not handled:%4d !",MsgIx);
  		AfxMessageBox(cstr,MB_OK,0);
  	  return;
	}

	DumpLog(DataElem,&vic_core[prev_vic_core_len],vic_core_len-prev_vic_core_len);	
}

void CBanksysDlg::vic_core_dump(int len, void *str)
{
  int i;
	unsigned char *s;

	s=(unsigned char *)str;
	for (i=0; i<len; i++) {
	  vic_core[vic_core_len++]=*s++;
	}
}

void CBanksysDlg::vic_core_dumpHEX(int len, void *p)
{
  int i;
	unsigned char *s;

	s=(unsigned char *)p;
	for (i=0; i<len; i++) {
	  vic_core[vic_core_len++]=*(s+len-1-i);
	}

}

void CBanksysDlg::VICParseReceivedMessage()
{
  int bi, bitmax, bm=0, MsgIx, i, j, VIx;
	CString FieldName;
	
	VICReceived.ProtocolId[0]=VICMessageReceived[0];
	VICReceived.ProtocolId[1]=VICMessageReceived[1];
	VICReceived.ProtocolId[2]=0;
	VICReceived.vic_msg_code[0]=VICMessageReceived[2];
  VICReceived.vic_msg_code[1]=VICMessageReceived[3];
	VICReceived.vic_msg_code[2]=0;
 
  bitmax=64;
	for (i=0; i<6; i++) {
	  if (VICMessageReceived[4+i*8]&0x80) bitmax+=64;
		else break;
	}
	VIx=4+bitmax/8;
	
	bi=3; // zal onmiddelijk op 4 komen !
	for (i=1; i<bitmax; i++) {
    if ((i-1)%8==0) {
  		bi++;
		  bm=0x80;
		}
    if ((i-1)%64==0) {bm/=2; continue;} // deze bits dienen om volgende bloks aan te duiden.

		if (VICMessageReceived[bi]&bm) {
		  MsgIx=i;
			for (j=0; j<100; j++) {
			  if (VicMessageContents[j].Nr==MsgIx) break;
			}
			FieldName="";
			if (j<100) {
			  FieldName=VicMessageContents[j].Name;
				VICReceived.Info[MsgIx].Len=VicMessageContents[j].Len;
			}

			if (VICReceived.Info[MsgIx].Len<=0)  {
				switch (MsgIx) {
					case 36:
						VICReceived.Info[MsgIx].Len=GetBCD(&VICMessageReceived[VIx],4);	// ticket_data
						VIx+=2;
						break;
					case 145:
						VICReceived.Info[MsgIx].Len=GetBCD(&VICMessageReceived[VIx],4);	// ticket_data
						VIx+=2;
						break;
					case 178:
						VICReceived.Info[MsgIx].Len=GetBCD(&VICMessageReceived[VIx],2);	// brand_name
						VIx+=1;
						break;
					default:
						CString cstr;
						cstr.Format("VICField %d received but not handled : %s!",MsgIx,FieldName);
  					AfxMessageBox(cstr,MB_SYSTEMMODAL|MB_ICONSTOP|MB_OK,NULL);
  					break;
				}
			}
		  
			if (VICReceived.Info[MsgIx].Len) {
				DumpLog((char *)FieldName.operator LPCTSTR(),&VICMessageReceived[VIx],VICReceived.Info[MsgIx].Len);
				VICReceived.Info[MsgIx].Used=TRUE;
				VICReceived.Info[MsgIx].Data=&VICMessageReceived[VIx];
				VIx+=VICReceived.Info[MsgIx].Len;
			}
		}
		bm/=2;
	}
	DumpLog(" ","",0);
}

int CBanksysDlg::GetBCD(void *s, int len)
{
  unsigned char *p;
	int res, i;

	res=0;
	if (s==NULL) return 0;
  
	p=(unsigned char *)s;
	for (i=0; i<len/2; i++) {
    res=100*res+10*(p[i]/0x10)+p[i]%0x10;
	}
  return res;
}

int CBanksysDlg::GetInt(void *s, int len)
{
  unsigned char *p;
	int i, res=0;

  if (s==NULL) return 0;
	p=(unsigned char *)s;
	for (i=0; i<len/2; i++) {
    res=res*256+p[i];
	}
	return res;
}

void CBanksysDlg::vic_core_dump4BCD(int getal)
{
  vic_core_dump2BCD(getal/100);
	vic_core_dump2BCD(getal);
}

void CBanksysDlg::vic_core_dump2BCD(int getal)
{
  vic_core[vic_core_len++]=0x10*((getal/10)%10)+(getal%10);
}

void CBanksysDlg::SendToKassa(void *p)
{
  unsigned char *s;
  int len;

	s=(unsigned char *)p;
  len=0;
	while (*s++) len++;
  SesSock.Send(p,len,0);
}

void CBanksysDlg::OnTest() 
{
  int i;
	CString cstr;
	
	CheckPayCardBusy=TRUE;  // zodat de inkomende frames niet gewist worden

  if (SendVIC_vmc_cancel(1)) {
		m_Status="Terminal accepted message";
		UpdateData(FALSE);
		for (i=0; i<10; i++) {
			if (VICMessageReceivedLen) {
  			VICParseReceivedMessage();
				if (_strcmpi(VICReceived.vic_msg_code,"PD")==0) {
					m_Status+="\r\nCorrect reply received";
					cstr.Format("\r\nTerminalID: %08d",GetBCD(VICReceived.Info[2].Data,8));
					m_Status+=cstr;
					break;
				}
			}
  		Sleep(1000);
			ProcessAllMessages();
		}
		if (i==10) {
			m_Status+="\r\nTime-out: No reply received!";
		}
	}
	else {
		m_Status="Terminal not connected!";
	}
	UpdateData(FALSE);

	CheckPayCardBusy=FALSE;
}

void CBanksysDlg::OnLogging() 
{
  UpdateData(TRUE);
	WriteRegistrySettings();
}


