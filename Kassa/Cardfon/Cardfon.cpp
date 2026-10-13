// Cardfon.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "Cardfon.h"
#include "CardfonDlg.h"
#include <process.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCardfonApp

BEGIN_MESSAGE_MAP(CCardfonApp, CWinApp)
	//{{AFX_MSG_MAP(CCardfonApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCardfonApp construction

CCardfonApp::CCardfonApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CCardfonApp object

CCardfonApp theApp;
CMySocket SesSock(NULL);

/////////////////////////////////////////////////////////////////////////////
// CCardfonApp initialization

BOOL CCardfonApp::InitInstance()
{
#if !defined (_DEBUG)
  TCHAR ModBuf[MAX_PATH];
  DWORD LenModBuf;
  CString ProgramName;
    
  LenModBuf=MAX_PATH;
  GetModuleFileName(NULL,ModBuf,LenModBuf); ModBuf[LenModBuf]=0;
  ProgramName = ModBuf; ProgramName.MakeUpper();
  if (ProgramName.Find(_T("X.EXE"))<0) {
    int k=ProgramName.Find(_T(".EXE"));
		CString XName=ProgramName.Left(k)+_T("X.EXE");
    CopyFile(ProgramName,XName,false);
    
    _execl(XName,XName,NULL); // normaal zou die hier niet meer van terugkomen
    return FALSE;
  }
#endif
	
	HWND hWnd = FindWindow(NULL,"cardfon");
  if (hWnd) {
    return FALSE;
  }

	if (!AfxSocketInit())
	{
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		return FALSE;
	}

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

	CCardfonDlg dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
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

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}
