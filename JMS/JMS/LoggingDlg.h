#pragma once
#include "afxwin.h"


// CLoggingDlg dialog

class CLoggingDlg : public CDialog
{
	DECLARE_DYNAMIC(CLoggingDlg)

public:
	CLoggingDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CLoggingDlg();

// Dialog Data
	enum { IDD = IDD_LOGGINGDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CListBox m_listLogging;
};
