
// KasMnWin.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CKasMnWinApp:
// See KasMnWin.cpp for the implementation of this class
//

class CKasMnWinApp : public CWinApp
{
public:
	CKasMnWinApp();
	int ErrorLevel;

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
	virtual int ExitInstance();
};

extern CKasMnWinApp theApp;