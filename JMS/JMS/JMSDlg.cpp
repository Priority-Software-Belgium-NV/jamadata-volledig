
// JMSDlg.cpp : implementation file
//

#include <iostream>
#include <fstream>
#include <sys/stat.h>

#include "stdafx.h"

#include "JMS.h"
#include "JMSDlg.h"

#ifndef JMSVIEWER
// #using <ionic.zip.dll>
#using <system.dll>
using namespace Ionic::Zip;
using namespace System;
using namespace System::Diagnostics;
using namespace System::Net;
using namespace System::IO;
using namespace JMSNet;
using namespace JMSEasySystems;
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

void CreateAndUpdateCopy(int dummy);

// CJMSDlg dialog


CJMSDlg::CJMSDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CJMSDlg::IDD, pParent)
	, m_PrevTabSelected(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CJMSDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TabSelDlg, m_cTab);
}

BEGIN_MESSAGE_MAP(CJMSDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_NOTIFY(TCN_SELCHANGE, IDC_TabSelDlg, &CJMSDlg::OnTcnSelchangeTabseldlg)
	ON_WM_SHOWWINDOW()
	ON_WM_SIZE()
	ON_WM_CLOSE()
	ON_WM_TIMER()
//	ON_WM_CHAR()
// ON_WM_COPYDATA()
//ON_WM_WINDOWPOSCHANGING()
ON_WM_ENDSESSION()
END_MESSAGE_MAP()


// CJMSDlg message handlers

BOOL CJMSDlg::OnInitDialog()
{
	CDialog::OnInitDialog();



	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog

	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon


	// volgende stukje is nodig om klein icoon goed te zetten ... was fout in MFC bij dialogs

  HICON hSmallIcon = (HICON) ::LoadImage ( AfxGetResourceHandle(), 
                                         MAKEINTRESOURCE(IDR_MAINFRAME),
                                         IMAGE_ICON, 16, 16, LR_DEFAULTCOLOR );
  SetIcon ( hSmallIcon, FALSE );

  // grootte instellen van de sub-dialogen

  CRect tabRect;
  m_cTab.GetWindowRect(tabRect);

  // Set the size and location of the child windows based on the tab control
  m_rJMSRect.left = 13;
  m_rJMSRect.top = 44;
  m_rJMSRect.right = tabRect.Width() - 7;
  m_rJMSRect.bottom = tabRect.Height() - 38;

  // Create the child windows for the main window class
	m_dLoggingDlg.Create(IDD_LOGGINGDLG, this);   // moet eerst gecreeerd worden om logging info te kunnen tonen ...
  m_dPrintersDlg.Create(IDD_PRINTERSDLG, this);
  // m_dTerminalsDlg.Create(this); // "THEJMS","dummy", WS_CHILD | WS_VISIBLE, CRect(0,0,100,100), this,0,NULL);
  // m_dTerminalsDlg.UpdateWindow();
  m_dTerminalsDlg.Create(IDD_TERMINALSDLG,this); //  (IDD_TERMINALSDLG);
  m_dMailDlg.Create(IDD_MAILDLG, this);
	m_dUtilitysDlg.Create(IDD_UTILITYSDLG, this);
  m_dDataBaseDlg.Create(IDD_DATABASEDLG, this); // als laatste zetten omdat die onmiddellijk begint met DB te Mounten

  // This is redundant with the default value, considering what OnShowWindow does
  ShowWindowNumber(0);
  // Set the titles for each tab
  TCITEM tabItem;
  tabItem.mask = TCIF_TEXT;

	tabItem.pszText = _T("  &Logging   ");
	m_cTab.InsertItem(0, &tabItem);
#ifndef JMSVIEWER
	if (JMSVersion=='M') {
		SetWindowText("Mono database");
	}
	else {
		tabItem.pszText = _T("  &DataBase   ");
		m_cTab.InsertItem(1, &tabItem);
		tabItem.pszText = _T("  &Printers   ");
		m_cTab.InsertItem(2, &tabItem);
		tabItem.pszText = _T("  &Terminals    ");
		m_cTab.InsertItem(3, &tabItem);
		tabItem.pszText = _T("  &Mail    ");
		m_cTab.InsertItem(4, &tabItem);
		tabItem.pszText = _T(" JM ");
		m_cTab.InsertItem(5, &tabItem);
	}
#endif

	m_PrevTabSelected=0;
  ControlledByJMTflag=false;

  // Start de nodige programma's 

	SetTimer(TIMER1MIN,VALTIMER1MIN*1000,NULL);
	SendMessage(WM_TIMER,TIMER1MIN,0);
  SetTimer(TIMER5MIN,VALTIMER5MIN*1000,NULL);
	
	_beginthread(EDBStart, 0, NULL ); /// EDBStart(); in een aparte thread om vlotter te blijven werken

  void RemoveOldFilesFromSpool();

  if (theApp.JmsExternalControlled) {
    ShowWindow(SW_SHOWDEFAULT);
    ShowWindow(SW_MINIMIZE);
    ShowWindow(SW_HIDE);
    UpdateWindow();

  }

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CJMSDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

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

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CJMSDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CJMSDlg::OnTcnSelchangeTabseldlg(NMHDR *pNMHDR, LRESULT *pResult)
{
  if (m_dDataBaseDlg.m_UpAndRunning==false) {
		ShowWindowNumber(0);
		return;
	}

	// Get the number of the currently selected tab, and show its window
  ShowWindowNumber(m_cTab.GetCurFocus());

  // Do something with the "formal parameters" so 
  // the compiler is happy in warning level 4
   pNMHDR = NULL;
   pResult = NULL;
	//*pResult = 0;
}

void CJMSDlg::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialog::OnShowWindow(bShow, nStatus);
}

void CJMSDlg::ShowWindowNumber(int Number)
{
	    // This example uses four windows
     int windowCount = 6;

     // Validate the parameter
     if ((Number >= 0) && (Number < windowCount))
     {
			 if (Number==5) {
					CJMPassword pw(this);
					pw.DoModal();
					SYSTEMTIME systime;
					GetLocalTime(&systime);              
					CString PWNow;
					switch (systime.wMonth) {
						case 1: PWNow="NAJ"; break;
						case 2: PWNow="BEF"; break;
						case 3: PWNow="AAM"; break;
						case 4: PWNow="RPA"; break;
						case 5: PWNow="IEM"; break;
						case 6: PWNow="NUJ"; break;
						case 7: PWNow="LUJ"; break;
						case 8: PWNow="GUA"; break;
						case 9: PWNow="PES"; break;
						case 10: PWNow="TKO"; break;
						case 11: PWNow="VON"; break;
						case 12: PWNow="CED"; break;
					}
					switch (systime.wDayOfWeek) {
						case 0: PWNow+="OZ"; break;
						case 1: PWNow+="AM"; break;
						case 2: PWNow+="ID"; break;
						case 3: PWNow+="OW"; break;
						case 4: PWNow+="OD"; break;
						case 5: PWNow+="RV"; break;
						case 6: PWNow+="AZ"; break;
					}
					if (pw.m_PWEntered!=PWNow) {
						m_cTab.SetCurSel(m_PrevTabSelected);
						return;
					}
					ShellExecute(NULL, "runas", "C:\\Windows\\system32\\cmd.exe", 0, 0, SW_SHOWNORMAL);
			 }


          // Create and assign pointers to each window
          CWnd *m_dPointer[6];

					m_dPointer[0] = &m_dLoggingDlg;
          m_dPointer[1] = &m_dDataBaseDlg;
          m_dPointer[2] = &m_dPrintersDlg;
          m_dPointer[3] = &m_dTerminalsDlg;
					m_dPointer[4] = &m_dMailDlg;
					m_dPointer[5] = &m_dUtilitysDlg;

          // Hide every window except for the chosen one
          for (int count = 0; count < windowCount; count++)
          {
               if (count != Number)
               {
                    m_dPointer[count]->ShowWindow(SW_HIDE);
               }
               else if (count == Number)
               {
                    // Show the chosen window and set it's location
										m_dPointer[count]->ShowWindow(SW_SHOW);
                    m_dPointer[count]->SetWindowPos(&wndTop, m_rJMSRect.left,
                         m_rJMSRect.top, m_rJMSRect.right,
                         m_rJMSRect.bottom, SWP_SHOWWINDOW);
                    m_cTab.SetCurSel(count);
               }
          }
     }
		 m_PrevTabSelected=Number;

}

void CJMSDlg::ProcessAllMessages(void)
{
	MSG msg;

  while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)>0) {
    TranslateMessage(&msg); 
    DispatchMessage(&msg); 
  }
}

void CJMSDlg::OnSize(UINT nType, int cx, int cy)
{
  if ((nType==SIZE_MINIMIZED || nType==SIZE_MAXIMIZED) && ControlledByJMTflag && IsWindowVisible()) ShowWindow(SW_HIDE);
  else CDialog::OnSize(nType, cx, cy);
}

void CJMSDlg::OnClose()
{
  if (ControlledByJMTflag && IsWindowVisible()) {
    ShowWindow(SW_HIDE);
    return;
  }
  if (!JMSShuttingDown) {
	  if (EDBStop(false)) {
		  CDialog::OnClose();
	  }
  }
}

void CJMSDlg::OnEndSession(BOOL bEnding)
{
  LogAdd(0,0,"End Session received, shutting down JMS");
  EDBStop(true);
  DestroyWindow();
}

void CJMSDlg::OnTimer(UINT_PTR nIDEvent)
{
  if (nIDEvent==TIMER1MIN) {

    if (JMSShuttingDown) return;

    if (!theApp.JmsTestConfigFlag) {

      if (WindowsXP) SetThreadExecutionState(ES_SYSTEM_REQUIRED); // om het systeem wakker te houden (cf. DMS ?)

      if (strSessionId.GetLength()==0) {
				_beginthread(HttpStart, 0, 0); // voor het geval de eerste HttpStart niet gelukt is (en sessionID niet ingevuld is)
			}
			else {
				_beginthread(HttpHB, 0, NULL);
			}

      if (theApp.UCServerWatchDog >= 2) { // 2 minuten geen activiteit ... want die zet deze counter terug op 0
        TerminateThread(theApp.UCServerhThread,0);
        CloseHandle(theApp.UCServerhThread);
        LogAdd(65,0,"UCServer watchdog timed out, so killed and restarted !");
        theApp.UCServerhThread=(HANDLE)-1L;
      }
      if (theApp.UCServerhThread == (HANDLE)-1L) {
        theApp.UCServerhThread = (HANDLE)_beginthread(RunUCServer, 0, 0);
        theApp.UCServerWatchDog=0;
      }
      else theApp.UCServerWatchDog++;

			if (JMSVersion!='M' || CustCode=="ALS" || StdInMono) {
				if (theApp.MailServerWatchDog >= 5) { // 5 minuten geen activiteit ... want die zet deze counter terug op 0
					TerminateThread(theApp.MailServerhThread,0);
					CloseHandle(theApp.MailServerhThread);
					LogAdd(101,0,"MailServer watchdog timed out, so killed and restarted !");
					theApp.MailServerhThread=(HANDLE)-1L;
				}
				if (theApp.MailServerhThread == (HANDLE)-1L) {
					theApp.MailServerhThread = (HANDLE)_beginthread(RunMailServer, 0, 0);
					theApp.MailServerWatchDog=0;
				}
				else theApp.MailServerWatchDog++;
			}

			if (pMainDlg->m_dDataBaseDlg.m_UpAndRunning) {
				if (theApp.CreateAndUpdateWatchDog >= 60) { // 60 minuten geen activiteit ... want die zet deze counter terug op 0
					TerminateThread(theApp.CreateAndUpdateThread,0);
					CloseHandle(theApp.CreateAndUpdateThread);
					LogAdd(103,0,"CreateAndUpdateThread watchdog timed out, so killed and restarted !");
					theApp.CreateAndUpdateThread=(HANDLE)-1L;
				}
				if (theApp.CreateAndUpdateThread == (HANDLE)-1L) {
					theApp.CreateAndUpdateThread = (HANDLE)_beginthread((void(*)(void*))CreateAndUpdateCopy, 0, (void*)0);
					theApp.CreateAndUpdateWatchDog=0;
				}
				else theApp.CreateAndUpdateWatchDog++;
			}
    }

    if (theApp.JMUServerWatchDog >= 3) { // 3 minuten geen activiteit ... want die zet deze counter terug op 0
      TerminateThread(theApp.JMUServerhThread,0);
      CloseHandle(theApp.JMUServerhThread);
      LogAdd(80,0,"JMUServer watchdog timed out, so killed and restarted !");
      theApp.JMUServerhThread=(HANDLE)-1L;
    }
    if (theApp.JMUServerhThread == (HANDLE)-1L) {
      theApp.JMUServerhThread = (HANDLE)_beginthread(RunJMUServer, 0, 0);
      theApp.JMUServerWatchDog=0;
    }
    else theApp.JMUServerWatchDog++;

  }
  else if (nIDEvent==TIMER5MIN) {
		if (theApp.RemoveOldThread != (HANDLE)-1L) {
			LogAdd(105,0,"Thread RemoveOldFilesFromSpool was still running after 5 minutes, so killed that thread");
			TerminateThread(theApp.RemoveOldThread,0);
			CloseHandle(theApp.RemoveOldThread);
			theApp.RemoveOldThread=(HANDLE)-1L;
		}
		theApp.RemoveOldThread=(HANDLE)_beginthread(RemoveOldFilesFromSpool, 0, 0); // beveiliging dat OnTimer niet vastloopt door opruiming ...
	}

  else CDialog::OnTimer(nIDEvent);
}

void CJMSDlg::OnFinalRelease()
{
	CDialog::OnFinalRelease();
}

// CJMPassword dialog

IMPLEMENT_DYNAMIC(CJMPassword, CDialog)

CJMPassword::CJMPassword(CWnd* pParent /*=NULL*/)
	: CDialog(CJMPassword::IDD, pParent)
	, m_PWEntered(_T(""))
{

}

CJMPassword::~CJMPassword()
{
}

void CJMPassword::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_JMPASSWORDTEXT, m_PWEntered);
	DDV_MaxChars(pDX, m_PWEntered, 10);
}


BEGIN_MESSAGE_MAP(CJMPassword, CDialog)
//	ON_EN_CHANGE(IDC_JMPASSWORDTEXT, &CJMPassword::OnEnChangeJmpasswordtext)
	ON_EN_UPDATE(IDC_JMPASSWORDTEXT, &CJMPassword::OnEnUpdateJmpasswordtext)
	ON_EN_KILLFOCUS(IDC_JMPASSWORDTEXT, &CJMPassword::OnEnKillfocusJmpasswordtext)
END_MESSAGE_MAP()


// CJMPassword message handlers

//void CJMPassword::OnEnChangeJmpasswordtext()
//{
//	// TODO:  If this is a RICHEDIT control, the control will not
//	// send this notification unless you override the CDialog::OnInitDialog()
//	// function and call CRichEditCtrl().SetEventMask()
//	// with the ENM_CHANGE flag ORed into the mask.
//
//	// TODO:  Add your control notification handler code here
//  OnOK();
//}

void CJMPassword::OnEnUpdateJmpasswordtext()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function to send the EM_SETEVENTMASK message to the control
	// with the ENM_UPDATE flag ORed into the lParam mask.

	// TODO:  Add your control notification handler code here
	//OnOK();
}

void CJMPassword::OnEnKillfocusJmpasswordtext()
{
	// TODO: Add your control notification handler code here
	OnOK();
}

CString CJMSDlg::SendHTTPPost(CString strCommand, CString strMessage, CString strFileName)
{
	// test
	strJama360SerialNr="jmsOPV4298";
	strJama360Password="gk04Qkq71X";
	CString strResponse;
	CFile fTrack;

#ifndef JMSVIEWER
	int FileLen;
	System::String^ HTTPBoundary = "----------------------------" + System::DateTime::Now.Ticks.ToString("x"); 

  if (strFileName.GetLength()==0 || (FALSE == fTrack.Open(strFileName, CFile::modeRead | CFile::shareDenyWrite)))
	{
		FileLen=0;
	}
  else {
		FileLen=(int)fTrack.GetLength();
  }

	try
  {
		  HttpWebRequest^ webRequest = dynamic_cast<HttpWebRequest^>(WebRequest::Create("http://svc.jamadata360.be/svc.aspx"));
      webRequest->Method = "POST";
			webRequest->Timeout = 30000; // 30 seconds
      webRequest->ContentType = "application/x-www-form-urlencoded";
      StreamWriter^ requestWriter = gcnew StreamWriter(webRequest->GetRequestStream());
      requestWriter->Close();
      HttpWebResponse^ response = dynamic_cast<HttpWebResponse^>(webRequest->GetResponse());
      StreamReader^ responseReader = gcnew StreamReader(response->GetResponseStream());
      System::String^ responseData = responseReader->ReadToEnd();
      responseReader->Close();

			int viewStateNamePosition = responseData->IndexOf("__VIEWSTATE");
      int viewStateValuePosition = responseData->IndexOf("value=\"", viewStateNamePosition);
      int viewStateStartPosition = viewStateValuePosition + 7; // valueDelimiter.Length;
      int viewStateEndPosition = responseData->IndexOf("\"", viewStateStartPosition);
      System::String^ viewState =  responseData->Substring(viewStateStartPosition, viewStateEndPosition - viewStateStartPosition);

      int eventValidationNamePosition = responseData->IndexOf("__EVENTVALIDATION");
      int eventValidationValuePosition = responseData->IndexOf("value=\"", eventValidationNamePosition);
      int eventValidationStartPosition = eventValidationValuePosition + 7; // valueDelimiter.Length;
      int eventValidationEndPosition = responseData->IndexOf("\"", eventValidationStartPosition);
      System::String^ eventValidation =  responseData->Substring(eventValidationStartPosition, eventValidationEndPosition - eventValidationStartPosition);

      // extract the viewstate value and build out POST data
			System::String^ controlNames = "__VIEWSTATE={0}&__EVENTVALIDATION={1}&boxSerialNr={2}&boxPassword={3}&boxCMD={4}&boxMessage={5}&";
			if (FileLen) controlNames += "BtnUpload=Upload";
			else controlNames += "btnSubmit=Submit";
      System::String^ postData = System::String::Format(controlNames, viewState, eventValidation,
				gcnew System::String(strJama360SerialNr), gcnew System::String(strJama360Password), 
				gcnew System::String(strCommand), gcnew System::String(strMessage));
			
			// now post to the login form
      webRequest = dynamic_cast<HttpWebRequest^>(WebRequest::Create("http://svc.jamadata360.be/svc.aspx"));
      webRequest->Method = "POST";
			webRequest->ContentType = "multipart/form-data; boundary=" + HTTPBoundary;
			webRequest->KeepAlive = true;
      requestWriter = gcnew StreamWriter(webRequest->GetRequestStream());

			if (FileLen) {
				System::String^ FileFormat = "--{0}\r\nContent-Disposition: form-data; name=\"filUpload\"; filename=\"{1}\"\r\nContent-Type: image/gif\r\nContent-Transfer-Encoding: binary\r\n\r\n";
				requestWriter->Write(System::String::Format(FileFormat, HTTPBoundary, gcnew System::String(strFileName)));
				DWORD dwReadLength = -1;
			  DWORD dwChunkLength=32768;
	      void* pBuffer = new char[dwChunkLength+100];
				while (0 != dwReadLength) {
					dwReadLength = fTrack.Read(pBuffer, dwChunkLength);
					if (0 != dwReadLength) {
						requestWriter->Write("Test\r\n",6);
					}
				}
				requestWriter->Write("\r\n",2);
				delete pBuffer;
			}

			System::String^ FieldFormat = "--{0}\r\nContent-Disposition: form-data; name=\"{1}\"\r\n\r\n{2}\r\n";
			System::String^ ButtonFormat = "--{0}\r\nContent-Disposition: form-data; name=\"{1}\"\r\n\r\n\"{2}\"\r\n--{0}--\r\n";
			requestWriter->Write(System::String::Format(FieldFormat,HTTPBoundary,"__VIEWSTATE",gcnew System::String(viewState)));
			requestWriter->Write(System::String::Format(FieldFormat,HTTPBoundary,"__EVENTVALIDATION",gcnew System::String(eventValidation)));
			requestWriter->Write(System::String::Format(FieldFormat,HTTPBoundary,"boxSerialNr",gcnew System::String(strJama360SerialNr)));
			requestWriter->Write(System::String::Format(FieldFormat,HTTPBoundary,"boxPassword",gcnew System::String(strJama360Password)));
			if (FileLen) {
				requestWriter->Write(System::String::Format(ButtonFormat,HTTPBoundary,"btnUpload","Upload"));
			}
			else {
  			requestWriter->Write(System::String::Format(FieldFormat,HTTPBoundary,"boxCMD",gcnew System::String(strCommand)));
	  		requestWriter->Write(System::String::Format(FieldFormat,HTTPBoundary,"boxMessage",gcnew System::String(strMessage)));
				requestWriter->Write(System::String::Format(ButtonFormat,HTTPBoundary,"btnSubmit","Submit"));
			}
      requestWriter->Close();
      response = dynamic_cast<HttpWebResponse^>(webRequest->GetResponse());
      responseReader = gcnew StreamReader(response->GetResponseStream());
      strResponse = responseReader->ReadToEnd();
      responseReader->Close();
      // Display what was read
      TRACE(strResponse);
  }
  catch (...) { // WebException^ ex) {
		//int i=0;
  }
#endif

	return strResponse;
}

CString CJMSDlg::CmdFtpUpload(CString Cmd) // "CmdFtpUpload|users.telenet.be|W486229|PnSU94|d:\\test.png
{
	CString strReturn = "@%!";

	int i1 = Cmd.Find("|");
	if (i1 < 0) return strReturn;
	CString Server = Cmd.Mid(0, i1);
	int i2 = Cmd.Find("|", i1 + 1);
	if (i2 < 0) return strReturn;
	CString User = Cmd.Mid(i1 + 1, i2 - i1 - 1);
	int i3 = Cmd.Find("|", i2 + 1);
	if (i3 < 0) return strReturn;
	CString Pw = Cmd.Mid(i2 + 1, i3 - i2 - 1);
	CString FileName = Cmd.Mid(i3 + 1);

	SVC ^svc = gcnew SVC();
	if (svc->FtpUpload(gcnew System::String(Server), gcnew System::String(User), gcnew System::String(Pw), gcnew System::String(FileName))) strReturn = "Uploaded";
	else strReturn = "Error";

	return strReturn;

}

CString CJMSDlg::CmdSFtpUpload(CString Cmd) // "CmdSFtpUpload|users.telenet.be|W486229|PnSU94|d:\\test.png|22
{
	CString strReturn = "@%!";

	int i1 = Cmd.Find("|");
	if (i1 < 0) return strReturn;
	CString Server = Cmd.Mid(0, i1);
	int i2 = Cmd.Find("|", i1 + 1);
	if (i2 < 0) return strReturn;
	CString User = Cmd.Mid(i1 + 1, i2 - i1 - 1);
	int i3 = Cmd.Find("|", i2 + 1);
	if (i3 < 0) return strReturn;
	CString Pw = Cmd.Mid(i2 + 1, i3 - i2 - 1);
	int i4 = Cmd.Find("|", i3 + 1);
	if (i4 < 0) return strReturn;
	int i5 = Cmd.Find("|", i4 + 1);
	CString FileName = Cmd.Mid(i3 + 1, i4 - i3 - 1);
	CString PortNr = "";
	if (i5 < 0) PortNr = Cmd.Mid(i4 + 1); else PortNr = Cmd.Mid(i4 + 1, i5 - i4 - 1);
	CString FtpFileName = "";
	if (i5 > 0) FtpFileName = Cmd.Mid(i5 + 1);

	SVC ^svc = gcnew SVC();
	if (svc->SFtpUpload(gcnew System::String(Server), gcnew System::String(User), gcnew System::String(Pw), gcnew System::String(FileName), gcnew System::String(PortNr), gcnew System::String(FtpFileName))) strReturn = "Uploaded";
	else strReturn = "Error";

	return strReturn;

}

//CString CJMSDlg::CmdSFtpUpload(CString Cmd) // "CmdSFtpUpload|users.telenet.be|W486229|PnSU94|d:\\test.png|22
//{
//	CString strReturn = "@%!";
//
//	int i1 = Cmd.Find("|");
//	if (i1 < 0) return strReturn;
//	CString Server = Cmd.Mid(0, i1);
//	int i2 = Cmd.Find("|", i1 + 1);
//	if (i2 < 0) return strReturn;
//	CString User = Cmd.Mid(i1 + 1, i2 - i1 - 1);
//	int i3 = Cmd.Find("|", i2 + 1);
//	if (i3 < 0) return strReturn;
//	CString Pw = Cmd.Mid(i2 + 1, i3 - i2 - 1);
//	int i4 = Cmd.Find("|", i3 + 1);
//	if (i4 < 0) return strReturn;
//	CString FileName = Cmd.Mid(i3 + 1, i4 - i3 - 1);
//	CString PortNr = Cmd.Mid(i4 + 1);
//
//	SVC ^svc = gcnew SVC();
//	if (svc->SFtpUpload(gcnew System::String(Server), gcnew System::String(User), gcnew System::String(Pw), gcnew System::String(FileName), gcnew System::String(PortNr))) strReturn = "Uploaded";
//	else strReturn = "Error";
//
//	return strReturn;
//}

CString CJMSDlg::CmdSFtpUpload2(CString Cmd) // "CmdSFtpUpload|users.telenet.be|W486229|PnSU94|d:\\test.png|22
{
  CString strReturn = "@%!";

  int i1 = Cmd.Find("|");
  if (i1 < 0) return strReturn;
  CString Server = Cmd.Mid(0, i1);
  int i2 = Cmd.Find("|", i1 + 1);
  if (i2 < 0) return strReturn;
  CString User = Cmd.Mid(i1 + 1, i2 - i1 - 1);
  int i3 = Cmd.Find("|", i2 + 1);
  if (i3 < 0) return strReturn;
  CString Pw = Cmd.Mid(i2 + 1, i3 - i2 - 1);
  int i4 = Cmd.Find("|", i3 + 1);
  if (i4 < 0) return strReturn;
  int i5 = Cmd.Find("|", i4 + 1);
  CString FileName = Cmd.Mid(i3 + 1, i4 - i3 - 1);
  CString PortNr = "";
  if(i5<0) PortNr = Cmd.Mid(i4 + 1); else PortNr = Cmd.Mid(i4 + 1, i5 - i4 - 1);
  CString FtpFileName = "";
  if (i5 > 0) FtpFileName=Cmd.Mid(i5 + 1);

  SVC ^svc = gcnew SVC();
  if (svc->SFtpUpload(gcnew System::String(Server), gcnew System::String(User), gcnew System::String(Pw), gcnew System::String(FileName), gcnew System::String(PortNr), gcnew System::String(FtpFileName))) strReturn = "Uploaded";
  else strReturn = "Error";

  return strReturn;
}


CString CJMSDlg::CmdFtpDownload(CString Cmd) // "users.telenet.be|W486229|PnSU94|test.png"
{
	CString strReturn = "@%!";

	int i1 = Cmd.Find("|");
	if (i1 < 0) return strReturn;
	CString Server = Cmd.Mid(0, i1);
	int i2 = Cmd.Find("|", i1 + 1);
	if (i2 < 0) return strReturn;
	CString User = Cmd.Mid(i1 + 1, i2 - i1 - 1);
	int i3 = Cmd.Find("|", i2 + 1);
	if (i3 < 0) return strReturn;
	CString Pw = Cmd.Mid(i2 + 1, i3 - i2 - 1);
	CString FileName = Cmd.Mid(i3 + 1);
	SVC ^svc = gcnew SVC();
	strReturn = svc->FtpDownload(gcnew System::String(Server), gcnew System::String(User), gcnew System::String(Pw), gcnew System::String(FileName));
	
	return strReturn;
}

CString CJMSDlg::CmdSFtpDownload(CString Cmd) // "users.telenet.be|W486229|PnSU94|test.png"
{
  CString strReturn = "@%!";

  int i1 = Cmd.Find("|");
  if (i1 < 0) return strReturn;
  CString Server = Cmd.Mid(0, i1);
  int i2 = Cmd.Find("|", i1 + 1);
  if (i2 < 0) return strReturn;
  CString User = Cmd.Mid(i1 + 1, i2 - i1 - 1);
  int i3 = Cmd.Find("|", i2 + 1);
  if (i3 < 0) return strReturn;
  CString Pw = Cmd.Mid(i2 + 1, i3 - i2 - 1);
  int i4 = Cmd.Find("|", i3 + 1);
  if (i4 < 0) return strReturn;
  CString FileName = Cmd.Mid(i3 + 1, i4 - i3 - 1);
  CString PortNr = Cmd.Mid(i4 + 1);
  SVC ^svc = gcnew SVC();
  strReturn = svc->SFtpDownload(gcnew System::String(Server), gcnew System::String(User), gcnew System::String(Pw), gcnew System::String(FileName), gcnew System::String(PortNr));

  return strReturn;
}

CString CJMSDlg::CmdSFtpDownload2(CString Cmd) // "users.telenet.be|W486229|PnSU94|test.png"
{
	CString strReturn = "@%!";

	int i1 = Cmd.Find("|");
	if (i1 < 0) return strReturn;
	CString Server = Cmd.Mid(0, i1);
	int i2 = Cmd.Find("|", i1 + 1);
	if (i2 < 0) return strReturn;
	CString User = Cmd.Mid(i1 + 1, i2 - i1 - 1);
	int i3 = Cmd.Find("|", i2 + 1);
	if (i3 < 0) return strReturn;
	CString Pw = Cmd.Mid(i2 + 1, i3 - i2 - 1);
	int i4 = Cmd.Find("|", i3 + 1);
	if (i4 < 0) return strReturn;
	CString FileName = Cmd.Mid(i3 + 1, i4 - i3 - 1);
	CString PortNr = Cmd.Mid(i4 + 1);
	SVC ^svc = gcnew SVC();
	strReturn = svc->SFtpDownload2(gcnew System::String(Server), gcnew System::String(User), gcnew System::String(Pw), gcnew System::String(FileName), gcnew System::String(PortNr));

	return strReturn;
}

CString CJMSDlg::CmdFtpDirectory(CString Cmd) // "users.telenet.be|W486229|PnSU94"
{
	CString strReturn = "@%!";

	int i1 = Cmd.Find("|");
	if (i1 < 0) return strReturn;
	CString Server = Cmd.Mid(0, i1);
	int i2 = Cmd.Find("|", i1 + 1);
	if (i2 < 0) return strReturn;
	CString User = Cmd.Mid(i1 + 1, i2 - i1 - 1);
	CString Pw = Cmd.Mid(i2 + 1);
	SVC ^svc = gcnew SVC();
	strReturn = svc->FtpDirectory(gcnew System::String(Server), gcnew System::String(User), gcnew System::String(Pw));

	return strReturn;
}

CString CJMSDlg::CmdSFtpDirectory(CString Cmd) // "users.telenet.be|W486229|PnSU94"
{
  CString strReturn = "@%!";

  int i1 = Cmd.Find("|");
  if (i1 < 0) return strReturn;
  CString Server = Cmd.Mid(0, i1);
  int i2 = Cmd.Find("|", i1 + 1);
  if (i2 < 0) return strReturn;
  CString User = Cmd.Mid(i1 + 1, i2 - i1 - 1);
  int i3 = Cmd.Find("|", i2 + 1);
  if (i3 < 0) return strReturn;
  CString Pw = Cmd.Mid(i2 + 1, i3 - i2 - 1);
  CString PortNr = Cmd.Mid(i3 + 1);
  SVC ^svc = gcnew SVC();
  strReturn = svc->SFtpDirectory(gcnew System::String(Server), gcnew System::String(User), gcnew System::String(Pw), gcnew System::String(PortNr));

  return strReturn;
}

CString CJMSDlg::CmdSFtpDirectory2(CString Cmd)
{
	CString strReturn = "@%!";

	int i1 = Cmd.Find("|");

	if (i1 < 0)
		return strReturn;

	CString Server = Cmd.Mid(0, i1);

	int i2 = Cmd.Find("|", i1 + 1);

	if (i2 < 0)
		return strReturn;

	CString Port = Cmd.Mid(i1 + 1, i2 - i1 - 1);

	int i3 = Cmd.Find("|", i2 + 1);

	if (i3 < 0)
		return strReturn;

	CString User = Cmd.Mid(i2 + 1, i3 - i2 - 1);

	int i4 = Cmd.Find("|", i3 + 1);

	if (i4 < 0)
		return strReturn;

	CString PW = Cmd.Mid(i3 + 1, i4 - i3 - 1);
	CString Directory = Cmd.Mid(i4 + 1);
	SVC ^svc = gcnew SVC();
	strReturn = svc->SFtpDirectory(gcnew System::String(Server), gcnew System::String(User), gcnew System::String(PW), gcnew System::String(Port), gcnew System::String(Directory));
	return strReturn;
}

CString CJMSDlg::CmdFtpDelete(CString Cmd) // "users.telenet.be|W486229|PnSU94|test.png"
{
	CString strReturn = "@%!";

	int i1 = Cmd.Find("|");
	if (i1 < 0) return strReturn;
	CString Server = Cmd.Mid(0, i1);
	int i2 = Cmd.Find("|", i1 + 1);
	if (i2 < 0) return strReturn;
	CString User = Cmd.Mid(i1 + 1, i2 - i1 - 1);
	int i3 = Cmd.Find("|", i2 + 1);
	if (i3 < 0) return strReturn;
	CString Pw = Cmd.Mid(i2 + 1, i3 - i2 - 1);
	CString FileName = Cmd.Mid(i3 + 1);
	SVC ^svc = gcnew SVC();
	strReturn = svc->FtpDelete(gcnew System::String(Server), gcnew System::String(User), gcnew System::String(Pw), gcnew System::String(FileName));

	return strReturn;
}

CString CJMSDlg::CmdSFtpDelete(CString Cmd) // "users.telenet.be|W486229|PnSU94|test.png"
{
  CString strReturn = "@%!";

  int i1 = Cmd.Find("|");
  if (i1 < 0) return strReturn;
  CString Server = Cmd.Mid(0, i1);
  int i2 = Cmd.Find("|", i1 + 1);
  if (i2 < 0) return strReturn;
  CString User = Cmd.Mid(i1 + 1, i2 - i1 - 1);
  int i3 = Cmd.Find("|", i2 + 1);
  if (i3 < 0) return strReturn;
  CString Pw = Cmd.Mid(i2 + 1, i3 - i2 - 1);
  int i4 = Cmd.Find("|", i3 + 1);
  if (i4 < 0) return strReturn;
  CString FileName = Cmd.Mid(i3 + 1, i4 - i3 - 1);
  CString PortNr = Cmd.Mid(i4 + 1);
  SVC ^svc = gcnew SVC();
  strReturn = svc->SFtpDelete(gcnew System::String(Server), gcnew System::String(User), gcnew System::String(Pw), gcnew System::String(FileName), gcnew System::String(PortNr));

  return strReturn;
}

CString CJMSDlg::CmdSFtpDelete2(CString Cmd) // "users.telenet.be|W486229|PnSU94|test.png"
{
	CString strReturn = "@%!";

	int i1 = Cmd.Find("|");
	if (i1 < 0) return strReturn;
	CString Server = Cmd.Mid(0, i1);
	int i2 = Cmd.Find("|", i1 + 1);
	if (i2 < 0) return strReturn;
	CString User = Cmd.Mid(i1 + 1, i2 - i1 - 1);
	int i3 = Cmd.Find("|", i2 + 1);
	if (i3 < 0) return strReturn;
	CString Pw = Cmd.Mid(i2 + 1, i3 - i2 - 1);
	int i4 = Cmd.Find("|", i3 + 1);
	if (i4 < 0) return strReturn;
	CString FileName = Cmd.Mid(i3 + 1, i4 - i3 - 1);
	CString PortNr = Cmd.Mid(i4 + 1);
	SVC ^svc = gcnew SVC();
	strReturn = svc->SFtpDelete2(gcnew System::String(Server), gcnew System::String(User), gcnew System::String(Pw), gcnew System::String(FileName), gcnew System::String(PortNr));

	return strReturn;
}

CString CJMSDlg::CmdWebrequestJson(CString Cmd) { // WebrequestJson Url|Method|User|PW|HeaderKey|HeaderValue|Message|FileName|ForceUnchangedInput|ForceUnchangedOutput
//	Cmd = "https://sandbox-api.codabox.com/v2/peppol/receiver/check-presence/|POST|PL-3fdaead4-82ab-4f31-bb0e-2fd|BYUzx86Dw4|X-Software-Company|8ce88971-32b0-433c-a080-17ee2710baa9|{\"scheme_id\":\"BE:CBE\",\"value\":\"0886886638\"}||false|false"; //teststring for PeppolCheckVAT with json
	//Cmd = "https://sandbox-api.codabox.com/v2/peppol/receiver/check-presence/|POST|PL-3fdaead4-82ab-4f31-bb0e-2fd|BYUzx86Dw4|X-Software-Company|8ce88971-32b0-433c-a080-17ee2710baa9|<scheme_id>BE:CBE</scheme_id><value>0886886638</value>||false|false"; //teststring for PeppolCheckVAT with xml

	CString strReturn = "@%!";

	CString Url = GetPipeItem(Cmd, 1);
	CString Method = GetPipeItem(Cmd, 2);
	CString User = GetPipeItem(Cmd, 3);
	CString PW = GetPipeItem(Cmd, 4);
	CString HeaderKey = GetPipeItem(Cmd, 5);
	CString HeaderValue = GetPipeItem(Cmd, 6);
	CString Message = GetPipeItem(Cmd, 7);
	CString FileName = GetPipeItem(Cmd, 8);
	bool ForceUnchangedInput = false;
	if (GetPipeItem(Cmd, 9) == "true") { ForceUnchangedInput = true; };
	bool ForceUnchangedOutput = false;
	if (GetPipeItem(Cmd, 10) == "true") { ForceUnchangedOutput = true; };

		if (Url == "@%!" ||
			Method == "@%!" ||
			User == "@%!" ||
			PW == "@%!" ||
			HeaderKey == "@%!" ||
			HeaderValue == "@%!" ||
			Message == "@%!" ||
			FileName == "@%!")
		{
			return strReturn;
		}

		ServicePointManager::SecurityProtocol = (SecurityProtocolType)(SecurityProtocolType)48 | (SecurityProtocolType)192 |
			(SecurityProtocolType)768 | (SecurityProtocolType)3072;

	SVC ^svc = gcnew SVC();
	System::String ^Reply = gcnew System::String("");
	System::Boolean ret = svc->WebrequestJson(gcnew System::String(Url),
		gcnew System::String(Method),
		gcnew System::String(User),
		gcnew System::String(PW),
		gcnew System::String(HeaderKey),
		gcnew System::String(HeaderValue),
		gcnew System::String(Message),
		gcnew System::String(FileName),
		ForceUnchangedInput,
		ForceUnchangedOutput,
		Reply);
	strReturn = Reply;
	if (ret==false) LogAdd(99, 0, strReturn);
	if (ret == false || strReturn == "") strReturn = "@%!" + strReturn;

	return strReturn;
}


CString CJMSDlg::GetPipeItem(CString Pipe, int Index){
	// handy way of fetching the nth item in a pipe
	int front = 0;
	int back = 0;
	CString Result = "@%!";
	int itemNr = 0;

	while(back > -1 && Result == "@%!"){
		if(back != 0){
			front = back + 1;
		}

		back = Pipe.Find("|", front);
		if(back > 0){
			itemNr++;
			if(itemNr == Index){
				Result = Pipe.Mid(front, (back - front));
			}
		}else if(front > 0 && back == -1){
			//front is not 0, so we have passed at least ONE item
			//assume this means it's the last item in the Pipe
			itemNr++;
			if(itemNr == Index){
				Result = Pipe.Mid(front);
			}
		}
	}

	return Result;
}

CString CJMSDlg::CmdIbanityShowLicence(CString Cmd) // "c05eb410-6149-4f28-aa91-92e8e748894d|YES"
{
  CString strReturn = "@%!";
  CString CBE,debug_;

  int i1 = Cmd.Find("|");
  if (i1 < 0) {
	CBE = Cmd; debug_ = "NO";
  }
  else {
	CBE = Cmd.Mid(0, i1);
	int i2 = Cmd.Find("|", i1 + 1);
	if (i2 < 0) debug_=Cmd.Mid(i1 + 1);
	else debug_=Cmd.Mid(i1 + 1, i2 - i1 - 1);
  }
 
  SVC ^svc = gcnew SVC();
  System::String ^Reply = gcnew System::String("");
	System::Boolean ret = svc->IbanityShowLicence(gcnew System::String(CBE), Reply, gcnew System::String(debug_));
  strReturn = Reply;

  if (strReturn == "") strReturn = "@%!";
  return strReturn;
}

CString CJMSDlg::CmdIbanityCheckVAT(CString Cmd) // "0886.886.638|yes"
{
  CString strReturn = "@%!";
  CString CBE, debug_;

  int i1 = Cmd.Find("|");
  if (i1 < 0) {
	CBE = Cmd; debug_ = "NO";
  }
  else {
	CBE = Cmd.Mid(0, i1);
	int i2 = Cmd.Find("|", i1 + 1);
	if (i2 < 0) debug_=Cmd.Mid(i1 + 1);
	else debug_=Cmd.Mid(i1 + 1, i2 - i1 - 1);
  }


  SVC ^svc = gcnew SVC();
  System::String ^Reply = gcnew System::String("");
  System::Boolean ret = svc->IbanityCheckVAT(gcnew System::String(CBE), Reply, gcnew System::String(debug_));
  strReturn = Reply;

  if (strReturn == "") strReturn = "@%!";
  return strReturn;
}

CString CJMSDlg::CmdIbanityCheckGLN(CString Cmd) // "5419980470454|YES"
{
	CString strReturn = "@%!";
	CString CBE, debug_;

	int i1 = Cmd.Find("|");
	if (i1 < 0) {
	  CBE = Cmd; debug_ = "NO";
	}
	else {
	  CBE = Cmd.Mid(0, i1);
	  int i2 = Cmd.Find("|", i1 + 1);
	  if (i2 < 0) debug_=Cmd.Mid(i1 + 1);
	  else debug_=Cmd.Mid(i1 + 1, i2 - i1 - 1);
	}

	SVC ^svc = gcnew SVC();
	System::String ^Reply = gcnew System::String("");
	System::Boolean ret = svc->IbanityCheckGLN(gcnew System::String(CBE), Reply, gcnew System::String(debug_));
	strReturn = Reply;

	if (strReturn == "") strReturn = "@%!";
	return strReturn;
}

CString CJMSDlg::CmdIbanityUBLUpload(CString Cmd) // c05eb410-6149-4f28-aa91-92e8e748894d|0640501449|1|C:\\vs\\tst\jamatest\\factubl\\FAS-2017-003201.xml|YES
{
	CString strReturn = "@%!",debug_;

	int i1 = Cmd.Find("|");
	if (i1 < 0) return strReturn;
	CString Licence = Cmd.Mid(0, i1);
	int i2 = Cmd.Find("|", i1 + 1);
	if (i2 < 0) return strReturn;
	CString VAT = Cmd.Mid(i1 + 1, i2 - i1 - 1);
	int i3 = Cmd.Find("|", i2 + 1);
	if (i3 < 0) return strReturn;
	CString CNflag = Cmd.Mid(i2 + 1, i3 - i2 - 1);
	CString UBLFileName = Cmd.Mid(i3 + 1);
	int i4 = Cmd.Find("|", i3 + 1);
	if (i4 < 0) {
	  UBLFileName = Cmd.Mid(i3 + 1); debug_ = "NO";
	}
	else {
	  UBLFileName = Cmd.Mid(i3 + 1, i4 - i3 - 1);
	  int i5 = Cmd.Find("|", i4 + 1);
	  if (i5 < 0) debug_=Cmd.Mid(i4 + 1);
	  else debug_=Cmd.Mid(i4 + 1, i5 - i4 - 1);
	}

	SVC ^svc = gcnew SVC(gcnew System::String(PathJamaRoot + "ToGeel\\"));
	System::String ^Reply = gcnew System::String("");
	System::Boolean ret = svc->IbanityUBLUpload(gcnew System::String(Licence), gcnew System::String(VAT), gcnew System::String(CNflag), gcnew System::String(UBLFileName), Reply, gcnew System::String(debug_));
	strReturn = Reply;

	if (strReturn == "") strReturn = "@%!";
	return strReturn;
}

CString CJMSDlg::CmdIbanityUBLStatus(CString Cmd) // PL-3fdaead4-82ab-4f31-bb0e-2fd|9c1f4aed-4f64-43bf-8968-41da138a4b54|YES
{
  CString strReturn = "@%!",debug_;

  int i1 = Cmd.Find("|");
  if (i1 < 0) return strReturn;
  CString Licence = Cmd.Mid(0, i1);
  int i2 = Cmd.Find("|", i1 + 1);
  if (i2 < 0) return strReturn;
  CString UBLId = Cmd.Mid(i1 + 1, i2 - i1 - 1);
  CString CNflag = Cmd.Mid(i2 + 1);

  int i3 = Cmd.Find("|", i2 + 1);
  if (i3 < 0) {
	CNflag = Cmd.Mid(i2 + 1); debug_ = "NO";
  }
  else {
	CNflag = Cmd.Mid(i2 + 1, i3 - i2 - 1);
	int i4 = Cmd.Find("|", i3 + 1);
	if (i4 < 0) debug_=Cmd.Mid(i3 + 1);
	else debug_=Cmd.Mid(i3 + 1, i4 - i3 - 1);
  }


  SVC ^svc = gcnew SVC();
  System::String ^Reply = gcnew System::String("");
  System::Boolean ret = svc->IbanityUBLStatus(gcnew System::String(Licence), gcnew System::String(UBLId), gcnew System::String(CNflag), Reply, gcnew System::String(debug_));
  strReturn = Reply;

  if (strReturn == "") strReturn = "@%!";
  return strReturn;
}

CString CJMSDlg::CmdPeppolSendDocument(CString Cmd)
{
	CString retVal = "NOK - Malformed command";

	int i1 = Cmd.Find("|");

	if (i1 < 0)
		return retVal;

	CString provider = Cmd.Mid(0, i1);

	int i2 = Cmd.Find("|", i1 + 1);

	if (i2 < 0)
		return retVal;

	CString userId = Cmd.Mid(i1 + 1, i2 - i1 - 1);

	int i3 = Cmd.Find("|", i2 + 1);

	if (i3 < 0)
		return retVal;

	CString password = Cmd.Mid(i2 + 1, i3 - i2 - 1);

	int i4 = Cmd.Find("|", i3 + 1);

	if (i4 < 0)
		return retVal;

	CString apiKey = Cmd.Mid(i3 + 1, i4 - i3 - 1);

	int i5 = Cmd.Find("|", i4 + 1);

	if (i5 < 0)
		return retVal;

	CString vatCode = Cmd.Mid(i4 + 1, i5 - i4 - 1);

	int i6 = Cmd.Find("|", i5 + 1);

	if (i6 < 0)
		return retVal;

	CString cnFlag = Cmd.Mid(i5 + 1, i6 - i5 - 1);

	int i7 = Cmd.Find("|", i6 + 1);

	if (i7 < 0)
		return retVal;

	CString ublFileName = Cmd.Mid(i6 + 1, i7 - i6 - 1);

	if (ublFileName.Trim().GetLength() == 0)
		return retVal;

	std::ifstream file(ublFileName);

	if (!file.good())
		return "NOK - File " + ublFileName + " does not exist.";

	CString debug = Cmd.Mid(i7 + 1);

	// Codabox
	if (provider == "0") {
		SVC ^svc = gcnew SVC(gcnew System::String(PathJamaRoot + "ToGeel\\"));
		System::String ^reply = gcnew System::String("");
		System::Boolean ret = svc->IbanityUBLUpload(gcnew System::String(apiKey), gcnew System::String(vatCode), gcnew System::String(cnFlag), gcnew System::String(ublFileName), reply, gcnew System::String(debug));
		retVal = reply;

		if (!ret || retVal == "")
			return "NOK";

		return "OK - " + retVal;
	}

	// EasySystems
	if (provider == "1")
		return EasySystems::SendDocument(gcnew String(userId), gcnew String(apiKey), gcnew String(ublFileName), gcnew String(debug));

	return "NOK - Invalid provider";
}

CString CJMSDlg::CmdPeppolGetDocumentStatus(CString Cmd)
{
	CString retVal = "NOK - Malformed command";

	int i1 = Cmd.Find("|");

	if (i1 < 0)
		return retVal;

	CString provider = Cmd.Mid(0, i1);

	int i2 = Cmd.Find("|", i1 + 1);

	if (i2 < 0)
		return retVal;

	CString userId = Cmd.Mid(i1 + 1, i2 - i1 - 1);

	int i3 = Cmd.Find("|", i2 + 1);

	if (i3 < 0)
		return retVal;

	CString password = Cmd.Mid(i2 + 1, i3 - i2 - 1);

	int i4 = Cmd.Find("|", i3 + 1);

	if (i4 < 0)
		return retVal;

	CString apiKey = Cmd.Mid(i3 + 1, i4 - i3 - 1);

	int i5 = Cmd.Find("|", i4 + 1);

	if (i5 < 0)
		return retVal;

	CString documentId = Cmd.Mid(i4 + 1, i5 - i4 - 1);

	int i6 = Cmd.Find("|", i5 + 1);

	if (i6 < 0)
		return retVal;

	CString cnFlag = Cmd.Mid(i5 + 1, i6 - i5 - 1);

	CString debug = Cmd.Mid(i6 + 1);

	// Codabox
	if (provider == "0") {
		SVC ^svc = gcnew SVC();
		System::String ^reply = gcnew System::String("");
		System::Boolean ret = svc->IbanityUBLStatus(gcnew System::String(apiKey), gcnew System::String(documentId), gcnew System::String(cnFlag), reply, gcnew System::String(debug));
		retVal = reply;

		if (!ret || retVal == "")
			return "NOK";

		return "OK - " + retVal;
	}

	// EasySystems
	if (provider == "1")
		return EasySystems::GetDocumentStatus(gcnew String(userId), gcnew String(apiKey), gcnew String(documentId), gcnew String(debug));

	return "NOK - Invalid provider";
}

CString CJMSDlg::CmdPeppolExportDocuments(CString Cmd)
{
	CString retVal = "NOK - Malformed command";

	int i1 = Cmd.Find("|");

	if (i1 < 0)
		return retVal;

	CString provider = Cmd.Mid(0, i1);

	int i2 = Cmd.Find("|", i1 + 1);

	if (i2 < 0)
		return retVal;

	CString userId = Cmd.Mid(i1 + 1, i2 - i1 - 1);

	int i3 = Cmd.Find("|", i2 + 1);

	if (i3 < 0)
		return retVal;

	CString password = Cmd.Mid(i2 + 1, i3 - i2 - 1);

	int i4 = Cmd.Find("|", i3 + 1);

	if (i4 < 0)
		return retVal;

	CString apiKey = Cmd.Mid(i3 + 1, i4 - i3 - 1);

	int i5 = Cmd.Find("|", i4 + 1);

	if (i5 < 0)
		return retVal;

	CString exportFolder = Cmd.Mid(i4 + 1, i5 - i4 - 1);
	if (exportFolder.Trim().GetLength() == 0) {
	  return retVal;
	}
	struct stat ef;

	if (stat(exportFolder, &ef) != 0)
		return "NOK - Folder " + exportFolder + " does not exist.";

	int i6 = Cmd.Find("|", i5 + 1);

	if (i6 < 0)
		return retVal;

	CString markAsExported = Cmd.Mid(i5 + 1, i6 - i5 - 1);
	int i7 = Cmd.Find("|", i6 + 1);

	CString debug = "";
	CString StartDateTime = "";
	if (i7 < 0)  debug = Cmd.Mid(i6 + 1);
	else {
	  debug = Cmd.Mid(i6 + 1, i7 - i6 - 1);
	  int i8 = Cmd.Find("|", i7 + 1);
	  if (i8 < 0)  StartDateTime = Cmd.Mid(i7 + 1);
	  else StartDateTime = Cmd.Mid(i7 + 1, i8 - i7 - 1);
	}

	// Codabox
	if (provider == "0") {
	  SVC ^svc = gcnew SVC();
	  System::String ^Reply = gcnew System::String("");
	   System::Boolean ret = svc->IbanityDownload(gcnew String(userId), gcnew String(password), gcnew String(apiKey), gcnew String(exportFolder), gcnew String(markAsExported), Reply, gcnew String(debug), gcnew String(StartDateTime));
	  retVal = Reply;
	  if (!ret) return "NOK - " + retVal; else return "OK - " + retVal;
	}

	// EasySystems
	if (provider == "1"){
		return EasySystems::ExportDocuments(gcnew String(userId), gcnew String(apiKey), gcnew String(exportFolder), gcnew String(markAsExported), gcnew String(debug));
	}
	return "NOK - Invalid provider";
}

CString CJMSDlg::CmdPeppolMarkDocumentAsExported(CString Cmd)
{
	CString retVal = "NOK - Malformed command";

	int i1 = Cmd.Find("|");

	if (i1 < 0)
		return retVal;

	CString provider = Cmd.Mid(0, i1);

	int i2 = Cmd.Find("|", i1 + 1);

	if (i2 < 0)
		return retVal;

	CString userId = Cmd.Mid(i1 + 1, i2 - i1 - 1);

	int i3 = Cmd.Find("|", i2 + 1);

	if (i3 < 0)
		return retVal;

	CString password = Cmd.Mid(i2 + 1, i3 - i2 - 1);

	int i4 = Cmd.Find("|", i3 + 1);

	if (i4 < 0)
		return retVal;

	CString apiKey = Cmd.Mid(i3 + 1, i4 - i3 - 1);

	int i5 = Cmd.Find("|", i4 + 1);

	if (i5 < 0)
		return retVal;

	CString documentId = Cmd.Mid(i4 + 1, i5 - i4 - 1);

	CString debug = Cmd.Mid(i5 + 1);

	// Codabox
	if (provider == "0")
		return "NOK - Not yet supported for Codabox";

	// EasySystems
	if (provider == "1")
		return EasySystems::MarkDocumentAsExported(gcnew String(userId), gcnew String(apiKey), gcnew String(documentId), gcnew String(debug));

	return "NOK - Invalid provider";
}

CString CJMSDlg::CmdPeppolLookup(CString Cmd)
{
	CString retVal = "NOK - Malformed command";

	int i1 = Cmd.Find("|");

	if (i1 < 0)
		return retVal;

	CString provider = Cmd.Mid(0, i1);

	int i2 = Cmd.Find("|", i1 + 1);

	if (i2 < 0)
		return retVal;

	CString userId = Cmd.Mid(i1 + 1, i2 - i1 - 1);

	int i3 = Cmd.Find("|", i2 + 1);

	if (i3 < 0)
		return retVal;

	CString password = Cmd.Mid(i2 + 1, i3 - i2 - 1);

	int i4 = Cmd.Find("|", i3 + 1);

	if (i4 < 0)
		return retVal;

	CString apiKey = Cmd.Mid(i3 + 1, i4 - i3 - 1);

	int i5 = Cmd.Find("|", i4 + 1);

	if (i5 < 0)
		return retVal;

	CString scheme = Cmd.Mid(i4 + 1, i5 - i4 - 1);

	int i6 = Cmd.Find("|", i5 + 1);

	if (i6 < 0)
		return retVal;

	CString lookupCode = Cmd.Mid(i5 + 1, i6 - i5 - 1);

	CString debug = Cmd.Mid(i6 + 1);

	// Codabox
	if (provider == "0") {
		SVC ^svc = gcnew SVC();
		System::String ^Reply = gcnew System::String("");
		System::Boolean ret = false;

		if (scheme == "0088") {
			ret = svc->IbanityCheckGLN(gcnew System::String(lookupCode), Reply, gcnew System::String(debug));
			retVal = Reply;
		}
		else if (scheme == "0208" || scheme == "9925") {
			ret = svc->IbanityCheckVAT(gcnew System::String(lookupCode), Reply, gcnew System::String(debug));
			retVal = Reply;
		}

		if (!ret || retVal == "")
			return "NOK";

		return "OK - " + retVal;
	}

	// EasySystems
	if (provider == "1")
		return EasySystems::Lookup(gcnew String(userId), gcnew String(apiKey), gcnew String(scheme), gcnew String(lookupCode), gcnew String(debug));

	return "NOK - Invalid provider";
}

CString CJMSDlg::CmdPepPolCheckVAT(CString Cmd) // "PL-3fdaead4-82ab-4f31-bb0e-2fd|BYUzx86Dw4|0886.886.638"
{
	CString strReturn = "@%!";

	int i1 = Cmd.Find("|");
	if (i1 < 0) return strReturn;
	CString CodaBoxUser = Cmd.Mid(0, i1);
	int i2 = Cmd.Find("|", i1 + 1);
	if (i2 < 0) return strReturn;
	CString CodaBoxPW = Cmd.Mid(i1 + 1, i2 - i1 - 1);
	CString CBE = Cmd.Mid(i2 + 1);

	SVC ^svc = gcnew SVC();
	System::String ^Reply = gcnew System::String("");
	System::Boolean ret = svc->PepPolCheckVAT(gcnew System::String(CodaBoxUser), gcnew System::String(CodaBoxPW), gcnew System::String(CBE), Reply);
	strReturn = Reply;

	if (strReturn == "") strReturn = "@%!";
	return strReturn;
}
 
CString CJMSDlg::CmdPepPolUBLUpload(CString Cmd) // PL-3fdaead4-82ab-4f31-bb0e-2fd|BYUzx86Dw4|056b7dc6-620b-4930-99d7-2e33f2c66acf|C:\\p-drive overpelt\\jms\\curl\\FAS-2017-003201.xml
{
	CString strReturn = "@%!";

	int i1 = Cmd.Find("|");
	if (i1 < 0) return strReturn;
	CString CodaBoxUser = Cmd.Mid(0, i1);
	int i2 = Cmd.Find("|", i1 + 1);
	if (i2 < 0) return strReturn;
	CString CodaBoxPW = Cmd.Mid(i1 + 1, i2 - i1 - 1);
	int i3 = Cmd.Find("|", i2 + 1);
	if (i3 < 0) return strReturn;
	CString UserLicense = Cmd.Mid(i2 + 1, i3 - i2 - 1);
	CString UBLFileName = Cmd.Mid(i3 + 1);

	SVC ^svc = gcnew SVC();
	System::String ^Reply = gcnew System::String("");
	System::Boolean ret = svc->PepPolUBLUpload(gcnew System::String(CodaBoxUser), gcnew System::String(CodaBoxPW), gcnew System::String(UserLicense), gcnew System::String(UBLFileName), Reply);
	strReturn = Reply;

	if (strReturn == "") strReturn = "@%!";
	return strReturn;
}

CString CJMSDlg::CmdPepPolUBLStatus(CString Cmd) // PL-3fdaead4-82ab-4f31-bb0e-2fd|BYUzx86Dw4|9c1f4aed-4f64-43bf-8968-41da138a4b54
{
	CString strReturn = "@%!";

	int i1 = Cmd.Find("|");
	if (i1 < 0) return strReturn;
	CString CodaBoxUser = Cmd.Mid(0, i1);
	int i2 = Cmd.Find("|", i1 + 1);
	if (i2 < 0) return strReturn;
	CString CodaBoxPW = Cmd.Mid(i1 + 1, i2 - i1 - 1);
	CString UBLId = Cmd.Mid(i2 + 1);

	SVC ^svc = gcnew SVC();
	System::String ^Reply = gcnew System::String("");
	System::Boolean ret = svc->PepPolUBLStatus(gcnew System::String(CodaBoxUser), gcnew System::String(CodaBoxPW), gcnew System::String(UBLId), Reply);
	strReturn = Reply;

	if (strReturn == "") strReturn = "@%!";
	return strReturn;
}

CString CJMSDlg::CmdJsonToXml(CString Cmd) {
	CString strReturn = "@%!";

	SVC ^svc = gcnew SVC();
	System::String ^Reply = svc->JsonToXml(gcnew System::String(Cmd));
	strReturn = Reply;

	return strReturn;
}

CString CJMSDlg::CmdXmlToJson(CString Cmd) {
	CString strReturn = "@%!";

	SVC ^svc = gcnew SVC();
	System::String ^Reply = svc->XmlToJson(gcnew System::String(Cmd));
	strReturn = Reply;

	return strReturn;
}



bool CJMSDlg::CreateZipSnapShotFromFasBack(char *ext, CString FileList, CString PathZip, int LifeTimeMinutes)
{
#ifndef JMSVIEWER
	CString ZipPathName, ZipTempPathName, ZipFileName, cstr;
  char FileName[250];
	ZipFile ^zip;

  ZipFileName="SnapShot-";
	ZipFileName+=ext;
  COleDateTime KillAt = COleDateTime::GetCurrentTime();
  COleDateTimeSpan Minutes(0,0,LifeTimeMinutes,0);
  KillAt+=Minutes;
	cstr.Format("-%02d%02d%02d-%02d%02d",KillAt.GetYear()%100,KillAt.GetMonth(),KillAt.GetDay(),KillAt.GetHour(),KillAt.GetMinute());
	ZipFileName+=cstr;
	ZipFileName+=".zip";
	ZipFileName.MakeLower();
	ZipPathName=PathZip+ZipFileName;
	ZipTempPathName=PathSpoolTemp+ZipFileName;
	
	int pos=0;
  try {
		zip = gcnew ZipFile;
		zip->ParallelDeflateThreshold=-1;
	  while (pos<FileList.GetLength()) {
      if (JMSShuttingDown) break;
      int i=FileList.Find("|",pos);
      if (i==-1) i=FileList.GetLength();
      sprintf(FileName,"%s", (char *)(LPCTSTR)FileList.Mid(pos,i-pos));
      pos=i+1;
		  System::String^ name = gcnew System::String(FileName);
		  zip->UpdateFile(name,"");
	  }  
    if (!JMSShuttingDown) zip->Save(gcnew System::String(ZipTempPathName));
    zip->~ZipFile();
		BOOL ret=CopyFile(ZipTempPathName,ZipPathName,FALSE);
		if (ret==0) {
			CString cstr;
			cstr.Format("Cannot copy %s to %s, LastError=%d",ZipTempPathName,ZipPathName,GetLastError());
			LogAdd(117,0,cstr);
		}
		_unlink(ZipTempPathName);
  }
  catch (...) {
    zip->~ZipFile();
    LogAdd(48,0,"Fatal Exception in Create Snapshot");
    return false;
  }
#endif
  return true;
}

char FullJamadataBackupStatus[300];
int  FullJamadataBackupTotalEntries=0;
int  FullJamadataBackupDoneEntries=0;
int  FullJamadataBackupPostReq=0;
bool FullJamadataBackupIncludeWorkFiles=false;
bool FullJamadataBackupBusy=false;

#ifndef JMSVIEWER
static System::Void AddProgressRout(System::Object^  sender, Ionic::Zip::AddProgressEventArgs^  e)
{
  int i=0;

	try {
		switch (e->EventType) {
			case ZipProgressEventType::Adding_AfterAddEntry:
				CString cstr;
				cstr.Format("Adding : %s",e->CurrentEntry->FileName);
				LogSpec("JMSback",(char *)(LPCTSTR)cstr);
  			sprintf_s((char *)FullJamadataBackupStatus,(size_t)MAX_PATH+35,(LPCTSTR)cstr);
				break;
		}
	}
	catch (...)
	{
	}
}

static System::Void SaveProgressRout(System::Object^  sender, Ionic::Zip::SaveProgressEventArgs^  e)
{
  int i=0;
  CString cstr;
	CFile fil;

	try {
		switch (e->EventType) {
			case ZipProgressEventType::Saving_EntryBytesRead:
				cstr.Format("Saving %3.0f%% of file [%d/%d] : %s ",(((float) e->BytesTransferred) / (0.01 * e->TotalBytesToTransfer)),FullJamadataBackupDoneEntries, FullJamadataBackupTotalEntries, e->CurrentEntry->FileName);
				strcpy((char *)FullJamadataBackupStatus,(LPCTSTR)cstr);
				break;
			case ZipProgressEventType::Saving_AfterWriteEntry:
				cstr.Format("Saving %3.0f%% of file [%d/%d] : %s ", (float)100.0, FullJamadataBackupDoneEntries, FullJamadataBackupTotalEntries, e->CurrentEntry->FileName);
				strcpy((char *)FullJamadataBackupStatus,(LPCTSTR)cstr);
				break;
			case ZipProgressEventType::Saving_BeforeWriteEntry:
				cstr.Format("Zipping : %s", e->CurrentEntry->FileName);
				LogSpec("jmsback",(char *)(LPCTSTR)cstr);

				if (e->EntriesSaved>0) FullJamadataBackupDoneEntries=e->EntriesSaved+1;
				if (e->EntriesTotal>0) FullJamadataBackupTotalEntries=e->EntriesTotal;
				break;
		}
	}
	catch (...) 
	{
	}
}

extern bool JmsExtendedLogging;

static void FullJamadataBackup(void* dummy)
{
	ZipFile ^zip;
	
	if (FullJamadataBackupBusy) return;
	FullJamadataBackupBusy=true;

	LogSpec("JMSback","C"); // als er nog een JMSBack log is, dan was het een crash ! Dus rename hem !!!
	strcpy((char *)FullJamadataBackupStatus,"Starting compression ...");
	CString cstr;
	int pos=0;
	FullJamadataBackupTotalEntries=0;
	FullJamadataBackupDoneEntries=0;
	CString FullJamadataBackupFileName="backup-";
  COleDateTime Now = COleDateTime::GetCurrentTime();
	cstr.Format("%02d%02d%02d-%02d%02d",Now.GetYear()%100,Now.GetMonth(),Now.GetDay(),Now.GetHour(),Now.GetMinute());
	FullJamadataBackupFileName+=cstr;
	FullJamadataBackupFileName+=".zip";
	CString FullJamadataBackupFilePath=PathSpoolFiles+FullJamadataBackupFileName;
	FullJamadataBackupFilePath.MakeLower();
	try {
		if (GetFileAttributes(FullJamadataBackupFilePath)!=INVALID_FILE_ATTRIBUTES) _unlink(FullJamadataBackupFilePath);
		zip = gcnew ZipFile(gcnew System::String(FullJamadataBackupFilePath));
		zip->ParallelDeflateThreshold=-1;
    zip->UseZip64WhenSaving = Zip64Option::AsNecessary;
		zip->Comment = gcnew System::String("Test");
		zip->AddProgress+= gcnew EventHandler<AddProgressEventArgs^>(&AddProgressRout);
		zip->SaveProgress += gcnew EventHandler<SaveProgressEventArgs^>(&SaveProgressRout);
		if (GetFileAttributes(PathJamaRoot+"div")!=INVALID_FILE_ATTRIBUTES) zip->AddDirectory(gcnew System::String(PathJamaRoot+"div"), gcnew System::String("Div"));
		if (GetFileAttributes(PathJamaRoot+"fas")!=INVALID_FILE_ATTRIBUTES) zip->AddDirectory(gcnew System::String(PathJamaRoot+"fas"), gcnew System::String("Fas"));
		if (GetFileAttributes(PathJamaRoot+"FtKopie")!=INVALID_FILE_ATTRIBUTES) zip->AddDirectory(gcnew System::String(PathJamaRoot+"FtKopie"), gcnew System::String("FtKopie"));
    if (GetFileAttributes(PathJamaRoot+"JamaPDA")!=INVALID_FILE_ATTRIBUTES) zip->AddDirectory(gcnew System::String(PathJamaRoot+"JamaPDA"), gcnew System::String("JamaPDA"));
    if (GetFileAttributes(PathJamaRoot+"Kassa")!=INVALID_FILE_ATTRIBUTES) zip->AddDirectory(gcnew System::String(PathJamaRoot+"Kassa"), gcnew System::String("Kassa"));
    if (GetFileAttributes(PathJamaRoot+"Mail")!=INVALID_FILE_ATTRIBUTES) zip->AddDirectory(gcnew System::String(PathJamaRoot+"Mail"), gcnew System::String("Mail"));
    if (GetFileAttributes(PathJamaRoot+"Offerte")!=INVALID_FILE_ATTRIBUTES) zip->AddDirectory(gcnew System::String(PathJamaRoot+"Offerte"), gcnew System::String("Offerte"));
	if (GetFileAttributes(PathJamaRoot + "AkKopie") != INVALID_FILE_ATTRIBUTES) zip->AddDirectory(gcnew System::String(PathJamaRoot + "AkKopie"), gcnew System::String("AkKopie"));
    if (GetFileAttributes(PathJamaRoot+"Prog")!=INVALID_FILE_ATTRIBUTES) zip->AddDirectory(gcnew System::String(PathJamaRoot+"Prog"), gcnew System::String("Prog"));
		strcpy((char *)FullJamadataBackupStatus,"Starting compression ...");
		if (!JMSShuttingDown) zip->RemoveSelectedEntries(gcnew System::String("kastest.*"));
    if (!JMSShuttingDown) zip->RemoveSelectedEntries(gcnew System::String("???.???.old"));
    if (!JMSShuttingDown) zip->RemoveSelectedEntries(gcnew System::String("???.???.res"));
    if (!JMSShuttingDown) zip->RemoveSelectedEntries(gcnew System::String("prog\\*.prv"));
    if (!JMSShuttingDown) zip->RemoveSelectedEntries(gcnew System::String("prog\\*.old"));
    if (!JMSShuttingDown) zip->RemoveSelectedEntries(gcnew System::String("prog\\*.flg"));
    if (!JMSShuttingDown) zip->RemoveSelectedEntries(gcnew System::String("prog\\*.OK"));
		if (!JMSShuttingDown) zip->RemoveSelectedEntries(gcnew System::String("prog\\tools\\xp\\*.*"));
		if (!JMSShuttingDown) zip->RemoveSelectedEntries(gcnew System::String("prog\\tools\\*.*"));
		if (!FullJamadataBackupIncludeWorkFiles) {
			CString WorkFilesList=theApp.iniFile.getKeyValue("WorkFiles","DataBaseSettings"); // WorkFiles=BON|TMP|
			for (int i=0; i<WorkFilesList.GetLength(); i++) {
				int j = WorkFilesList.Find("|",i);
				CString WorkFile=WorkFilesList.Mid(i);
				if (j>0) {
					WorkFile=WorkFilesList.Mid(i,j-i);
					i=j+1;
				}
				else i+=WorkFile.GetLength();
				zip->RemoveSelectedEntries(gcnew System::String("fas\\"+WorkFile+".???"));
				zip->RemoveSelectedEntries(gcnew System::String("fas\\log\\"+WorkFile+".???.log\\*"));
				zip->RemoveSelectedEntries(gcnew System::String("fas\\log\\"+WorkFile+".???.log"));
				zip->RemoveSelectedEntries(gcnew System::String("fas\\fsd\\"+WorkFile+".???.fsd"));
			}
		}
		if (!JMSShuttingDown) zip->Save();
    zip->~ZipFile();
		LogSpec("JMSBack","D"); // wis de log van de JMSBack, alles is goed verlopen
		if (theApp.JmsTestConfigFlag) {
			::ShellExecute(NULL,"open",PathSpoolFiles,NULL,NULL,SW_SHOW);
			sprintf_s(FullJamadataBackupStatus,sizeof(FullJamadataBackupStatus),"Done|%s", (char *)(LPCTSTR)FullJamadataBackupFilePath);
		}
		else {
			CString DestPath;
			int PostNr=FullJamadataBackupPostReq;
      DestPath.Format("%sPost-%03d\\",PathSpoolToClient,PostNr);
			if (JMSVersion=='M') DestPath=PathSpool+"Received\\";
      CreateDirectory(DestPath,NULL);
			CString DestFilePath=DestPath+FullJamadataBackupFileName;
			_unlink(DestFilePath);
			MoveFile(FullJamadataBackupFilePath,DestFilePath);
			sprintf_s(FullJamadataBackupStatus,sizeof(FullJamadataBackupStatus),"Done|%s", (char *)(LPCTSTR)DestFilePath);
			if (JMSVersion=='M') {
				HWND JMD=FindWindow("THE_JMD",NULL);
 				if (JMD) PostMessage(JMD, WM_USER + 5, 0, 0); // 0x405, 0, 0); // PROC_RECEIVED_FILES -> de JMD moet deze file verwerken !									
			}
			else {
				if (PostWnd[PostNr-1]==0) {
					LogAdd(109,0,"hWnd for JMH not filled in, so Txmit of XLS slow for PostNr=",PostNr);
				}
				else PostMessage(PostWnd[PostNr-1],WM_USER+2,0,0); // proc_send2peer ...
				if (JmsExtendedLogging) {
					CString cstr;
					cstr.Format("Txfer to Post-%03d = %s", PostNr, FullJamadataBackupFileName);
					LogAdd(0,1,cstr);
				}
			}
		}
  }
  catch (ZipException^ ex) {
    zip->~ZipFile();
    LogAdd(11,0,"Fatal Exception in CreateFullJamadataBackup",ex->Message);
		ex->~ZipException();
		strcpy(FullJamadataBackupStatus,"Bad");
  }
	FullJamadataBackupBusy=false;
}
#endif

void CJMSDlg::CreateFullJamadataBackup(bool IncludeWorkFiles, int PostNr)
{
#ifndef JMSVIEWER
	FullJamadataBackupIncludeWorkFiles=IncludeWorkFiles;
	FullJamadataBackupPostReq=PostNr;
	_beginthread(FullJamadataBackup, 0, NULL );	
	Sleep(1000); // om thread te laten starten !
#endif
}

bool CJMSDlg::IsValidZipArchive(char *FilePath)
{
	bool ret=true;
#ifndef JMSVIEWER
	ZipFile ^zip;

	try {
		zip = gcnew ZipFile(gcnew System::String(FilePath));
	}
	catch (...) {
		CString cstr;
		if (_unlink(FilePath)==0) {
			cstr.Format("Invalid Snapshot found and deleted : %s",FilePath);
			LogAdd(115,0,cstr);
		}
		else {
			cstr.Format("Invalid Snapshot, impossible to delete [Open?damaged?] : %s",FilePath);
			LogAdd(114,0,cstr);
		}
    ret=false;
	}
	try {
		if (zip) zip->~ZipFile();
	}
	catch (...) {}
#endif
  return ret;
}

bool CJMSDlg::AreSnapShotsIdentical(CString FilePath1, CString FilePath2)
{
	bool ret=true;
#ifndef JMSVIEWER
	ZipFile ^zip1, ^zip2;

	if (GetFileAttributes(FilePath1)==INVALID_FILE_ATTRIBUTES || GetFileAttributes(FilePath2)==INVALID_FILE_ATTRIBUTES) return false;
	try {
		zip1 = ZipFile::Read(gcnew System::String(FilePath1));
		zip2 = gcnew ZipFile(gcnew System::String(FilePath2));
		zip1->ParallelDeflateThreshold=-1;
		zip2->ParallelDeflateThreshold=-1;
		if (zip1->Count!=zip2->Count) ret=false;
		else {
			System::Collections::Generic::IEnumerator<ZipEntry ^>^ e2 = zip2->EntriesSorted->GetEnumerator(); // dit is de oude manier, maar kan hier niet anders
			for each(ZipEntry^ entry1 in zip1->EntriesSorted) { // dit is de nieuwe manier om een loop te maken 
				e2->MoveNext();
				ZipEntry^ entry2 = e2->Current;
				// Nu compare
				if (entry1->FileName!=entry2->FileName || entry1->UncompressedSize!=entry2->UncompressedSize) {
					ret=false;
					break;
				}
				if (entry1->FileName->Length>3 && entry1->FileName->Substring(entry1->FileName->Length-3)->ToUpper()=="BAK") {
					if (entry1->ModifiedTime!=entry2->ModifiedTime) ret=false;
				}
				else {
					if (entry1->Crc!=entry2->Crc) ret=false;
				}
				if (ret==false) break;
			}
		}
	}
	catch (...) {
		CString cstr;
		cstr.Format("Fatal Exception in Comparing Snapshots (%s,%s)",FilePath1,FilePath2);
    LogAdd(110,0,cstr);
    ret=false;
	}
  try {
		if (zip1) zip1->~ZipFile();
	}
	catch (...) {}
  try {
		if (zip2) zip2->~ZipFile();
	}
	catch (...) {}
#endif
  return ret;
}

bool CJMSDlg::CreateAndMaintainZipArchiveFTKopie(CString ZipFilePath)
{
#ifndef JMSVIEWER
	ZipFile ^zip;

  COleDateTime now = COleDateTime::GetCurrentTime();

  for (int yr=now.GetYear(); yr>now.GetYear()-8; yr--) {
		pMainDlg->ProcessAllMessages();
    CString ZipFilePathYear;
    ZipFilePathYear.Format("%s-%02d%s",ZipFilePath.Left(ZipFilePath.GetLength()-4),yr%100,ZipFilePath.Right(4));
    
    FILETIME ftLastAdded2Zip, ftNextLastAdded2Zip;
    memset(&ftLastAdded2Zip,0,sizeof(FILETIME));
    memset(&ftNextLastAdded2Zip,0,sizeof(FILETIME));
    WIN32_FIND_DATA ZipFileData;
    bool NewZipFile=true;
    bool ZipFileOpen=false;
    HANDLE hFind;
    if ((hFind=FindFirstFile(ZipFilePathYear,&ZipFileData))!=INVALID_HANDLE_VALUE) {
      FindClose(hFind);
      if (now.GetYear()-yr>=2) continue; // wanneer de ZIP bestaat, dan enkel bijwerken voor year en year-1 ... 
                                         // de oudere files kunnen/mogen niet gewijzigd zijn
                                         // indien de backup niet bestaat, dan wordt hij toch aangemaakt (als het nodig is)
      ftNextLastAdded2Zip.dwHighDateTime=ftLastAdded2Zip.dwHighDateTime = ZipFileData.ftLastWriteTime.dwHighDateTime;
	    ftNextLastAdded2Zip.dwLowDateTime=ftLastAdded2Zip.dwLowDateTime = ZipFileData.ftLastWriteTime.dwLowDateTime;
      NewZipFile=false;
    }

    try {
      CFileFind FileFinder;
	    CString File2Find;
      File2Find.Format("%sFtKopie\\*.%02d*",PathJamaRoot,yr%100);
	    BOOL bWorking = FileFinder.FindFile(File2Find);
      int Count=0;
	    while (bWorking) {
        if (JMSShuttingDown) break;
		    bWorking = FileFinder.FindNextFile();
        if (FileFinder.IsDirectory()) continue;

        FILETIME ftFileLastUpdated;
        if (FileFinder.GetLastWriteTime(&ftFileLastUpdated)) {
          if (ftFileLastUpdated.dwHighDateTime > ftLastAdded2Zip.dwHighDateTime ||
                (ftFileLastUpdated.dwHighDateTime==ftLastAdded2Zip.dwHighDateTime && ftFileLastUpdated.dwLowDateTime > ftLastAdded2Zip.dwLowDateTime)) {
    		    System::String^ name = gcnew System::String(FileFinder.GetFilePath());
            if (!ZipFileOpen) {
              if (NewZipFile) zip = gcnew ZipFile;
              else zip = gcnew ZipFile(gcnew System::String(ZipFilePathYear));
              ZipFileOpen=true;
              zip->UseZip64WhenSaving = Zip64Option::AsNecessary;
							zip->ParallelDeflateThreshold=-1;
            }
	    	    zip->UpdateFile(name,"");
            if (ftFileLastUpdated.dwHighDateTime > ftNextLastAdded2Zip.dwHighDateTime ||
                  (ftFileLastUpdated.dwHighDateTime==ftNextLastAdded2Zip.dwHighDateTime && ftFileLastUpdated.dwLowDateTime > ftNextLastAdded2Zip.dwLowDateTime)) {
              ftNextLastAdded2Zip.dwHighDateTime=ftFileLastUpdated.dwHighDateTime;
              ftNextLastAdded2Zip.dwLowDateTime=ftFileLastUpdated.dwLowDateTime;
            }
            Count++;
          }
        }
      }
      FileFinder.Close();

      if (ZipFileOpen) {
        if (!JMSShuttingDown) {
					CString ZipTempPathName = PathSpoolTemp + "FtKopie.zip";
					zip->Save(gcnew System::String(ZipTempPathName));
					zip->~ZipFile();
					
					CFile file;
          file.Open(ZipTempPathName,CFile::modeWrite,NULL);
          SetFileTime(file.m_hFile,NULL,NULL, &ftNextLastAdded2Zip);
          file.Close();

					pMainDlg->ProcessAllMessages();
					BOOL ret=CopyFile(ZipTempPathName,ZipFilePathYear,FALSE);
					if (ret==0) {
						CString cstr;
						cstr.Format("Cannot copy %s to %s, LastError=%d",ZipTempPathName,ZipFilePathYear,GetLastError());
						LogAdd(118,0,cstr);
					}
					_unlink(ZipTempPathName);
  
          if (Count) {
            CString cstr;
            cstr.Format("Updated/Added %d files ",Count);
            LogAdd(0,0,cstr,ZipFilePathYear);
          }
        }
        zip->~ZipFile();
      }
    }
    catch(...)
    {
      zip->~ZipFile();
      LogAdd(47,0,"Fatal Execption in CreateZip FtKopie");
      return false;
    }
  }
#endif
  return true;
}

bool CJMSDlg::ZipExtractAll(CString ZipFilePath,CString ZipSubDir,bool OverwriteExistingFiles)
{
#ifndef JMSVIEWER
	ZipFile ^zip;

  System::String^ zipdir = gcnew System::String(ZipSubDir);
  System::String^ zipname = gcnew System::String(ZipFilePath);
    
  try {
    zip = gcnew ZipFile(zipname);
		zip->ParallelDeflateThreshold=-1;
    if (OverwriteExistingFiles) zip->ExtractExistingFile=ExtractExistingFileAction::OverwriteSilently;
    zip->ExtractAll(zipdir);
    zip->~ZipFile();
  }
  catch (...) {
    zip->~ZipFile();
    LogAdd(63,0,"Fatal Exception in unzipping",ZipFilePath);
    return false;
  }
#endif
  return true;
}

bool CJMSDlg::CreateZipArchiveJamaSubDir(CString JamaSubDir, CString ZipFilePath)
{
#ifndef JMSVIEWER
	ZipFile ^zip;

  CString PathJamaSubDir = PathJamaRoot + JamaSubDir + "\\";
    
  zip = gcnew ZipFile;
  zip->ParallelDeflateThreshold=-1;
  zip->UseZip64WhenSaving = Zip64Option::AsNecessary;
  try {
    System::String^ subdirname = gcnew System::String(PathJamaSubDir);
 	  zip->AddDirectory(subdirname,"");
    zip->RemoveSelectedEntries(gcnew System::String("*.flg"));
    zip->RemoveSelectedEntries(gcnew System::String("*.OK"));
    zip->RemoveSelectedEntries(gcnew System::String("*.STA"));
		zip->RemoveSelectedEntries(gcnew System::String("JAMACON.SER"));

		CString ZipTempPathName = PathSpoolTemp + JamaSubDir + ".zip";
		zip->Save(gcnew System::String(ZipTempPathName));
		zip->~ZipFile();
			
		BOOL ret=CopyFile(ZipTempPathName,ZipFilePath,FALSE);
		if (ret==0) {
			CString cstr;
			cstr.Format("Cannot copy %s to %s, LastError=%d",ZipTempPathName,ZipFilePath,GetLastError());
			LogAdd(119,0,cstr);
		}
		_unlink(ZipTempPathName);
  }
  catch (...) {
    zip->~ZipFile();
    LogAdd(63,0,"Fatal Exception in Zipping JamaSubDir");
    return false;
  }
#endif
  return true;
}

bool CJMSDlg::CreateZipFromFile(CString FilePath, CString ZipFilePath)
{
#ifndef JMSVIEWER
	ZipFile ^zip;

  zip = gcnew ZipFile;
  zip->ParallelDeflateThreshold=-1;
  try {
    System::String^ FileName= gcnew System::String(FilePath);
    System::String^ ZipFileName= gcnew System::String(ZipFilePath);
 	  zip->UpdateFile(FileName,"");
    zip->Save(ZipFileName);
    zip->~ZipFile();
  }
  catch (...) {
    zip->~ZipFile();
    LogAdd(64,0,"Fatal Exception in Zipping SubDir",FilePath);
    return false;
  }
#endif
  return true;
}

bool CJMSDlg::CreateZipFromFileList(CString FileList, CString ZipFilePath)
{
#ifndef JMSVIEWER
	ZipFile ^zip;
  char FileName[MAX_PATH];

  zip = gcnew ZipFile;
  zip->ParallelDeflateThreshold=-1;
  try {
    System::String^ ZipFileName= gcnew System::String(ZipFilePath);
    int pos=0;
	  while (pos<FileList.GetLength()) {
      if (JMSShuttingDown) break;
      int i=FileList.Find("|",pos);
      if (i==-1) i=FileList.GetLength();
      sprintf(FileName,"%s", (char *)(LPCTSTR)FileList.Mid(pos,i-pos));
      pos=i+1;
		  System::String^ name = gcnew System::String(FileName);
		  zip->UpdateFile(name,"");
	  }  
    zip->Save(ZipFileName);
    zip->~ZipFile();
  }
  catch (...) {
    zip->~ZipFile();
    LogAdd(89,0,"Fatal Exception in Zipping FileList");
    return false;
  }
#endif
  return true;
}

bool CJMSDlg::CreateZipFromPath(CString Path, CString ZipFilePath)
{
#ifndef JMSVIEWER
 	ZipFile ^zip;

  zip = gcnew ZipFile;
	zip->ParallelDeflateThreshold=-1;
  try {
    System::String^ ZipFileName= gcnew System::String(ZipFilePath);
    System::String^ subdirname = gcnew System::String(Path);
 	  zip->AddDirectory(subdirname,"");
    zip->Save(ZipFileName);
    zip->~ZipFile();
  }
  catch (...) {
    zip->~ZipFile();
    LogAdd(68,0,"Fatal Exception in Zipping subdir",Path);
    return false;
  }
#endif
  return true;
}

BOOL CJMSDlg::OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
  if (message==WM_USER+11) {
    ControlledByJMTflag=true;
    *pResult = theApp.ProgDidSomeWork;
    if (theApp.ProgDidSomeWork>0) theApp.ProgDidSomeWork=0;
    return TRUE;
  }
  else return CDialog::OnWndMsg(message, wParam, lParam, pResult);
}

CString CJMSDlg::GetJMSExeVersion(void)
{
  CString strReturn="";
#ifndef JMSVIEWER
  try {
    FileVersionInfo^ myFileVersionInfo =
    FileVersionInfo::GetVersionInfo("JMS.exe");
    strReturn=myFileVersionInfo->FileVersion;
  }
  catch (...) {}
#endif
  return strReturn;

}
