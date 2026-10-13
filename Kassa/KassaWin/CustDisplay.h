#if !defined(AFX_CUSTDISPLAY_H__3709175D_4B8B_4D81_BDC0_029D94526C16__INCLUDED_)
#define AFX_CUSTDISPLAY_H__3709175D_4B8B_4D81_BDC0_029D94526C16__INCLUDED_

#include "resource.h"
#include "label.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CustDisplay.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCustDisplay dialog

class CCustDisplay : public CDialog
{
// Construction
public:
	int lineix;
	int State;
	CCustDisplay(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CCustDisplay)
	enum { IDD = IDD_CUSTDISPLAY };
	CLabel	m_CustLabel;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCustDisplay)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

public:
  // Implementation
	virtual ~CCustDisplay();

protected:

	// Generated message map functions
	//{{AFX_MSG(CCustDisplay)
	afx_msg void OnTimer(UINT nIDEvent);
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CUSTDISPLAY_H__3709175D_4B8B_4D81_BDC0_029D94526C16__INCLUDED_)
