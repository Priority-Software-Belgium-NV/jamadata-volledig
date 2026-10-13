// Cardfon.h : main header file for the CARDFON application
//

#if !defined(AFX_CARDFON_H__3340FE2A_F0AD_474E_BFAA_C68BD1C85B09__INCLUDED_)
#define AFX_CARDFON_H__3340FE2A_F0AD_474E_BFAA_C68BD1C85B09__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CCardfonApp:
// See Cardfon.cpp for the implementation of this class
//

class CCardfonApp : public CWinApp
{
public:
	CCardfonApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCardfonApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CCardfonApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CARDFON_H__3340FE2A_F0AD_474E_BFAA_C68BD1C85B09__INCLUDED_)
