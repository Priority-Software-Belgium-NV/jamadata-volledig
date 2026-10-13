#if !defined(AFX_MYSOCKET_H__DA4BF44F_2058_4376_A07B_DB532D0D81C5__INCLUDED_)
#define AFX_MYSOCKET_H__DA4BF44F_2058_4376_A07B_DB532D0D81C5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MySocket.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMySocket command target
class CCardfonDlg;

class CMySocket : public CSocket
{
// Attributes
public:

// Operations
public:
	CMySocket(CCardfonDlg *pDlg);
	virtual ~CMySocket();

// Overrides
public:
	int RecLen;
	char RecBuf[1000];
 	CCardfonDlg *m_pCardfonDlg;
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMySocket)
	public:
	virtual void OnAccept(int nErrorCode);
	virtual void OnReceive(int nErrorCode);
	virtual void OnClose(int nErrorCode);
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(CMySocket)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

// Implementation
protected:
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYSOCKET_H__DA4BF44F_2058_4376_A07B_DB532D0D81C5__INCLUDED_)
