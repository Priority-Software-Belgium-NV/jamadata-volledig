// CardfonDlg.h : header file
//

#include "MySocket.h"

#if !defined(AFX_CARDFONDLG_H__F7EC1C76_EDC7_431C_BBB3_CF519A6A6C78__INCLUDED_)
#define AFX_CARDFONDLG_H__F7EC1C76_EDC7_431C_BBB3_CF519A6A6C78__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CCardfonDlg dialog

class CCardfonDlg : public CDialog
{
// Construction
public:
	void WriteRegistrySettings();
	void ReadRegistrySettings();
	void StartListening();
	bool OpenComPort();
	int State;
	char Amount[30];
	unsigned char OmniSend[350];
	bool SendAcked;
	time_t SendTime;
	int SendAckRetry,RubbishRetry;
	unsigned char OmniResponse[350];
	int  ResponseLen;

	void CheckPayCard();
	void ProcCommand(CMySocket *pSesSock, char *cmd);
	CCardfonDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CCardfonDlg)
	enum { IDD = IDD_CARDFON_DIALOG };
	CString	m_ComPort;
	CString	m_Status;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCardfonDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
	HANDLE comref;
	CMySocket* pSrvSock;

	// Generated message map functions
	//{{AFX_MSG(CCardfonDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnDestroy();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnWindowPosChanging(WINDOWPOS FAR* lpwndpos);
	afx_msg void OnChangeComPort();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CARDFONDLG_H__F7EC1C76_EDC7_431C_BBB3_CF519A6A6C78__INCLUDED_)
