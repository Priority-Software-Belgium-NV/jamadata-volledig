#if !defined(AFX_AFFDISPLAY_H__5D498CA5_8260_4017_82FB_AB350F5A8B90__INCLUDED_)
#define AFX_AFFDISPLAY_H__5D498CA5_8260_4017_82FB_AB350F5A8B90__INCLUDED_

#include "Picture.h"	// Added by ClassView
#include "resource.h"
#include "label.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AffDisplay.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAffDisplay dialog

class CAffDisplay : public CDialog
{
// Construction
public:
	BOOL PictureDisplayed;
	CPicture m_AffFrame;
	CLabel	m_AffLabel;
	CAffDisplay(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CAffDisplay)
	enum { IDD = IDD_AFFDISPLAY };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAffDisplay)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

public:
  // Implementation
	virtual ~CAffDisplay();

protected:

	// Generated message map functions
	//{{AFX_MSG(CAffDisplay)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnDestroy();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_AFFDISPLAY_H__5D498CA5_8260_4017_82FB_AB350F5A8B90__INCLUDED_)
