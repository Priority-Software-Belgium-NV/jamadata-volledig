// CardfonDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Cardfon.h"
#include "CardfonDlg.h"

#define TIMER				 100
#define ACK_RETRY			 3
#define MAX_PAY_TIME 180

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CMySocket SesSock;

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
// CCardfonDlg dialog

CCardfonDlg::CCardfonDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCardfonDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCardfonDlg)
	m_ComPort = _T("");
	m_Status = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCardfonDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCardfonDlg)
	DDX_CBString(pDX, IDC_COMBO1, m_ComPort);
	DDX_Text(pDX, IDC_EDIT1, m_Status);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CCardfonDlg, CDialog)
	//{{AFX_MSG_MAP(CCardfonDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DESTROY()
	ON_WM_TIMER()
	ON_WM_WINDOWPOSCHANGING()
	ON_CBN_EDITCHANGE(IDC_COMBO1, OnChangeComPort)
	ON_CBN_SELCHANGE(IDC_COMBO1, OnChangeComPort)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCardfonDlg message handlers

BOOL CCardfonDlg::OnInitDialog()
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
	pSrvSock = new CMySocket(this);
	SesSock.m_pCardfonDlg=this;
	State=0;

	ReadRegistrySettings();
	UpdateData(FALSE);
   
	OnChangeComPort();

	SetTimer(1,TIMER,0);

#ifndef _DEBUG
	ShowWindow(SW_MINIMIZE);
#endif

	return TRUE;  // return TRUE  unless you set the focus to a control
}


void CCardfonDlg::StartListening()
{
 	pSrvSock->Create(4999,SOCK_STREAM,NULL);
	pSrvSock->Listen(1);

}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CCardfonDlg::OnPaint() 
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
HCURSOR CCardfonDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CCardfonDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	pSrvSock->Close();
  if (pSrvSock) delete pSrvSock;
}

void CCardfonDlg::ProcCommand(CMySocket *pSock, char *cmd)
{
  TRACE(cmd);
	
	switch (cmd[0]) {
	  case '*':
			memcpy(Amount,&cmd[1],sizeof(Amount));
			State=1;
			break;
		case '?':
			pSock->Send("Cardfone gevonden\r\n",19,0);
			break;
	}
}

#define		STX		0x02
#define		ETX		0x03
#define		EOT		0x04
#define		ENQ		0x05
#define		ACK		0x06
#define		NAK		0x15

void CCardfonDlg::CheckPayCard()
{
 	unsigned char *o, byte, lrc;
	char buf[100], *p;
	int i;
	double bd_;
	DWORD written, readbytes;
	time_t tim;

	if (State==1) {
	  byte=ACK;
		WriteFile(comref,&byte,1,&written,NULL); // om eventuele hangende boodschap te wissen.
		ReadFile(comref,OmniResponse,sizeof(OmniResponse),&readbytes,NULL);
		bd_=0;
		for(i=0;i<12;i++){
			if(Amount[i]=='.') break;
			if(Amount[i]>='0' && Amount[i]<='9') bd_=bd_*10+Amount[i]-'0';
		}
		if(bd_>99999){ // bedrag moet <100000 zijn 
			SesSock.Send("Ongeldig bedrag!\r\n",22,0);
			SesSock.Send("*** NIET betaald ***\r\n",22,0);
			ReadFile(comref,OmniResponse,sizeof(OmniResponse),&readbytes,NULL);
			State=999;
		}
		else{
			ResponseLen=0;
			memcpy(OmniSend,"#00C100000000100000000000                    0000000000501EUR##",sizeof(OmniSend));
			OmniSend[0]=STX; OmniSend[61]=ETX;
			o=&OmniSend[14];
			for (i=0; i<12; i++) {
				if (Amount[i]=='.') i++;
				if (Amount[i]>'0') *o=Amount[i];
				o++;
			}
			OmniSend[62]=0;
			for (i=1; i<62; i++) OmniSend[62]^=OmniSend[i];
			SendAcked=false;
			SendAckRetry=ACK_RETRY+1;
			SendTime=0;
			State=2;
		}
	}

	if (State==2) {
		if (SendAcked) {
			SesSock.Send("!LOCK\r\n",7,0);
			SesSock.Send("Wacht op kaart/PIN..\r\n",22,0);
			State=3;RubbishRetry=0;
		}
		else {
			time(&tim);
			if (difftime(tim,SendTime)>=3) {   // 3 seconds timeout
				if (SendAckRetry<=0) {
					SesSock.Send("Geen communicatie...\r\n",22,0);
					SesSock.Send("*** NIET betaald ***\r\n",22,0);
					ReadFile(comref,OmniResponse,sizeof(OmniResponse),&readbytes,NULL);
					State=999;
				}
				else {
					SendAckRetry--;
					time(&SendTime);
	  			WriteFile(comref,OmniSend,63,&written,NULL); 
				}
			}
		}
	}

	if (State>1) {

ReRead:;
		ReadFile(comref,&byte,1,&readbytes,NULL);
		if (readbytes==1) {
			if (byte==ACK) {
				SendAcked=true;
			}
			else if (byte==NAK) {
				 SendTime=0;
			}
			else if (byte==ENQ) {
				byte=ACK;
				WriteFile(comref,&byte,1,&written,NULL);
			}
			else if (State==3 || State==4) {
			  OmniResponse[ResponseLen++]=byte;
				if (OmniResponse[ResponseLen-2]==ETX || ResponseLen>30 || OmniResponse[0]!=STX || (ResponseLen>1 && ResponseLen<6 && memcmp((char *)&OmniResponse[1],"00D1",ResponseLen-1)!=0)) {
					lrc=0;
			    for (i=1; i<ResponseLen-1; i++) lrc^=OmniResponse[i];
					if(lrc!=OmniResponse[ResponseLen-1] || !(ResponseLen==30 && OmniResponse[0]==STX && memcmp((char *)&OmniResponse[1],"00D1",4)==0)){ // geen geldig antwoord
						if(RubbishRetry<3){ // 3 keer proberen
  						ResponseLen=0;
	  					byte=NAK;
  	  			  WriteFile(comref,&byte,1,&written,0);
							RubbishRetry++;
						}
						else{
  						//SesSock.Send("!CHECK\r\n",8,0);
  //						SesSock.Send("!UNLOCK\r\n",9,0);
	  					SesSock.Send("***Betaling onzeker!***\r\n",25,0);
	//						SesSock.Send("*** NIET betaald ***\r\n",22,0);
							State=999;
						}
					}
					else{
  					byte=ACK;
    				WriteFile(comref,&byte,1,&written,0);
		  			State=4;
					}
				}
			}
			goto ReRead;
		}
	}

	if (State==4) {
		if (ResponseLen==30 && OmniResponse[0]==STX && memcmp((char *)&OmniResponse[1],"00D1",4)==0) { // message received !
			if (OmniResponse[27]=='0') { // betaling OK
				p="#1          Onbekend";
				if (memcmp((char *)&OmniResponse[25],"  ",2)==0) p="#1        Bancontact";
				if (memcmp((char *)&OmniResponse[25],"MA",2)==0) p="#1           Maestro";  // was 2, maar dan komt alles in credicard Jaak 10/09/2018
				if (memcmp((char *)&OmniResponse[25],"AU",2)==0) p="#1            Aurora";
				if (memcmp((char *)&OmniResponse[25],"CC",2)==0) p="#1      Comfort Card";
				if (memcmp((char *)&OmniResponse[25],"VI",2)==0) p="#2              VISA";
				if (memcmp((char *)&OmniResponse[25],"EC",2)==0) p="#2        MasterCard";
				if (memcmp((char *)&OmniResponse[25],"MX",2)==0) p="#2  American Express";
				if (memcmp((char *)&OmniResponse[25],"DC",2)==0) p="#2       Diners Club";
				if (memcmp((char *)&OmniResponse[25],"JC",2)==0) p="#2          JCB-card";
				if (memcmp((char *)&OmniResponse[25],"SE",2)==0) p="#4     Sodexo e-Pass";
				if (memcmp((char *)&OmniResponse[25],"ER",2)==0) p="#5           Edenred";
				if (memcmp((char *)&OmniResponse[25],"PF",2)==0) p="#6           Payfair";
				SesSock.Send("Betaling uitgevoerd:\r\n",22,0);
				sprintf_s(buf,sizeof(buf),"%20s\r\n",p);
				SesSock.Send(buf,22,0);
			}
			else if (OmniResponse[27]=='A') { // Terminal is niet klaar
  			SesSock.Send("!UNLOCK\r\n",9,0);
			  SesSock.Send("Terminal is bezig...\r\n",22,0);
				SesSock.Send("*** NIET betaald ***\r\n",22,0);
			  State=999;
			}
			else if (OmniResponse[27]=='7' || OmniResponse[27]=='8') { // 0 of >99999
//			  SesSock.Send("!UNLOCK\r\n",9,0);
			  SesSock.Send("Ongeldig bedrag!\r\n",18,0);
				SesSock.Send("*** NIET betaald ***\r\n",22,0);
				ReadFile(comref,OmniResponse,sizeof(OmniResponse),&readbytes,NULL);
			  State=999;
			}
			else {
				p="Onbekende kaart";
				if (memcmp((char *)&OmniResponse[25],"00",2)==0) p="Geen kaart";
				if (memcmp((char *)&OmniResponse[25],"  ",2)==0) p="Bancontact";
				if (memcmp((char *)&OmniResponse[25],"MA",2)==0) p="Maestro";
				if (memcmp((char *)&OmniResponse[25],"AU",2)==0) p="Aurora";
				if (memcmp((char *)&OmniResponse[25],"CC",2)==0) p="Comfort Card";
				if (memcmp((char *)&OmniResponse[25],"VI",2)==0) p="VISA";
				if (memcmp((char *)&OmniResponse[25],"EC",2)==0) p="MasterCard";
				if (memcmp((char *)&OmniResponse[25],"MX",2)==0) p="American Express";
				if (memcmp((char *)&OmniResponse[25],"DC",2)==0) p="Diners Club";
				if (memcmp((char *)&OmniResponse[25],"JC",2)==0) p="JCB-card";
				if (memcmp((char *)&OmniResponse[25],"SE",2)==0) p="Sodexo e-Pass";
				if (memcmp((char *)&OmniResponse[25],"ER",2)==0) p="Edenred";
				if (memcmp((char *)&OmniResponse[25],"PF",2)==0) p="Payfair";
				sprintf_s(buf,sizeof(buf),"FOUT:%-15s\r\n",p);
				SesSock.Send("!UNLOCK\r\n",9,0);
				SesSock.Send("*** NIET betaald ***\r\n",22,0);
				if (*p) {
  				sprintf_s(buf,sizeof(buf),"%20s\r\n",p);
	  			SesSock.Send(buf,22,0);
				}
			}
			State=999;
		}
		else {
 			SesSock.Send("!UNLOCK\r\n",9,0);
  		SesSock.Send("Transmissie fout ...\r\n",22,0);
		}
  }

	if (State==999) {
		SesSock.Close();
		SesSock.m_hSocket=INVALID_SOCKET;
		State=1000;
	}
	if (State==1000) {
		byte=EOT;
  	WriteFile(comref,&byte,1,&written,0);
		State=0;
	}
}

void CCardfonDlg::OnTimer(UINT nIDEvent) 
{
	if (nIDEvent==1 && State) CheckPayCard();
	
	CDialog::OnTimer(nIDEvent);
}

void CCardfonDlg::OnWindowPosChanging(WINDOWPOS FAR* lpwndpos) 
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

void CCardfonDlg::OnChangeComPort() 
{
	UpdateData(TRUE);
	if (comref>=0) CloseHandle(comref);
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

bool CCardfonDlg::OpenComPort()
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
    SetupComm(comref, 350, 350); // set buffer sizes
  	GetCommState(comref, &m_dcb);
 		m_dcb.ByteSize = 7;
  	m_dcb.fBinary = TRUE;
		m_dcb.fParity = FALSE;
  	m_dcb.Parity = 2; // zo overgenomen uit status na hun testprogramma
 		m_dcb.StopBits = 0;
 		m_dcb.fAbortOnError = TRUE;
		m_dcb.fOutxDsrFlow=FALSE;
		m_dcb.fRtsControl=1;
  	m_dcb.BaudRate = 9600;
		SetCommState(comref, &m_dcb);
		if(GetCommTimeouts(comref, &commTimeout)) {
			commTimeout.ReadIntervalTimeout=100; // max 0,1 seconde tussen 2 character input
			commTimeout.ReadTotalTimeoutConstant=1000; // max 1 seconde wacht op input
			commTimeout.ReadTotalTimeoutMultiplier=0; 
			commTimeout.WriteTotalTimeoutMultiplier=0;
			commTimeout.WriteTotalTimeoutConstant =1000; // 1 seconden time-out 
			SetCommTimeouts(comref, &commTimeout);
		}
		return true;
	}
	return false;
}


void CCardfonDlg::ReadRegistrySettings()
{
  HKEY hk; 
  char buf[200];
  unsigned long size;

  size=sizeof(buf); 
  if (!RegCreateKey(HKEY_CURRENT_USER,"SOFTWARE\\Jamadata\\Cardfon", &hk)) {
    if (!RegQueryValueEx(hk,"COM-Port",0,0,(unsigned char *)buf,&size)) m_ComPort=buf;
    RegCloseKey(hk);
  }
}

void CCardfonDlg::WriteRegistrySettings()
{
  HKEY hk; 
  CString KeyName;


  KeyName="SOFTWARE\\Jamadata\\Cardfon\\";
  if (!RegCreateKey(HKEY_CURRENT_USER,KeyName, &hk)) {
    
    RegSetValueEx(hk,"COM-Port",0,REG_SZ,(const unsigned char *)m_ComPort.operator LPCTSTR(),m_ComPort.GetLength());
    RegCloseKey(hk);
  }  
}



