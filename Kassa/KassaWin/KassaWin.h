
// KassaWin.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CKassaWinApp:
// See KassaWin.cpp for the implementation of this class
//

class CKassaWinApp : public CWinApp
{
public:
	CKassaWinApp();

// Overrides
public:
	virtual BOOL InitInstance();
	int ErrorLevel;

// Implementation

	DECLARE_MESSAGE_MAP()
	virtual int ExitInstance();
};

extern CKassaWinApp theApp;