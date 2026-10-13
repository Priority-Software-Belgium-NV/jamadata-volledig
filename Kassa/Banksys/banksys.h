// Banksys.h : main header file for the Banksys application
//

#if !defined(AFX_Banksys_H__3340FE2A_F0AD_474E_BFAA_C68BD1C85B09__INCLUDED_)
#define AFX_Banksys_H__3340FE2A_F0AD_474E_BFAA_C68BD1C85B09__INCLUDED_

#define		STX		0x02
#define		ETX		0x03
#define		DLE		0x10
#define		EOT		0x04
#define		ENQ		0x05
#define		ACK		0x06
#define   WAK		0x13
#define		NAK		0x15

#define TIMER									100
#define MAX_KISS_FRAME_LEN	 5000+100+1000
#define COM_CHECK_TIMER				 66
#define ACK_RETRY								3
#define MAX_PAY_TIME	  			 90

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CBanksysApp:
// See Banksys.cpp for the implementation of this class
//

class CBanksysApp : public CWinApp
{
public:
	CBanksysApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBanksysApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CBanksysApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_Banksys_H__3340FE2A_F0AD_474E_BFAA_C68BD1C85B09__INCLUDED_)
