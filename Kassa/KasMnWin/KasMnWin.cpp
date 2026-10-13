
// KasMnWin.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "KasMnWin.h"
#include "TlHelp32.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CKasMnWinApp

BEGIN_MESSAGE_MAP(CKasMnWinApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CKasMnWinApp construction

CKasMnWinApp::CKasMnWinApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

bool IsKassaRunning()
{
  bool KassaFound=false;  
	HANDLE handle = NULL;
  try
  {
    // Create snapshot of the processes
    handle = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    PROCESSENTRY32 info;
    info.dwSize = sizeof(PROCESSENTRY32);
    // Get the first process
    int loop = Process32First(handle, &info);
    // If we failed to get the first process, throw an exception
    while (loop) {
			if (info.th32ProcessID!=GetCurrentProcessId()) {
	      if (_strcmpi(info.szExeFile,"KASSA.exe")==0) KassaFound=true;
				if (_strcmpi(info.szExeFile,"KASMENU.exe")==0) KassaFound=true;
			}
		  loop=Process32Next(handle,&info);
		}
  }
	catch (...)
	{
	}
  // Release handle of the snapshot
  CloseHandle(handle);
  return KassaFound;
}

// The one and only CKasMnWinApp object

CKasMnWinApp theApp;

int main(int argc, char *argv[]);

// CKasMnWinApp initialization

BOOL CKasMnWinApp::InitInstance()
{
	// InitCommonControlsEx() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// Set this to include all the common control classes you want to use
	// in your application.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	if (!AfxSocketInit())
	{
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		return FALSE;
	}


	// Create the shell manager, in case the dialog contains
	// any shell tree view or shell list view controls.
	CShellManager *pShellManager = new CShellManager;

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization
	SetRegistryKey(_T("KasMenu"));
	ErrorLevel=0;

	if (IsKassaRunning()) ErrorLevel=1;
	else main(1,0);

	// Delete the shell manager created above.
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}



int CKasMnWinApp::ExitInstance()
{
	return ErrorLevel;
}
