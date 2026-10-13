#pragma once

#include "afxcmn.h"
#include "afxwin.h"

// CTerminalsDlg dialog

class CTerminalsDlg : public CDialog
{
	DECLARE_DYNAMIC(CTerminalsDlg)

public:
	CTerminalsDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CTerminalsDlg();

// Dialog Data
	enum { IDD = IDD_TERMINALSDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
  virtual BOOL OnInitDialog();
  afx_msg void OnDestroy();
  virtual void OnOK();
  virtual void OnCancel();
  afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
};
