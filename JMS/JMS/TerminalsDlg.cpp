// TerminalsDlg.cpp : implementation file
//

#include "stdafx.h"
#include "JMS.h"
#include "TerminalsDlg.h"

// CTerminalsDlg dialog

IMPLEMENT_DYNAMIC(CTerminalsDlg, CDialog)

CTerminalsDlg::CTerminalsDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTerminalsDlg::IDD, pParent)
{

}

CTerminalsDlg::~CTerminalsDlg()
{
}

void CTerminalsDlg::DoDataExchange(CDataExchange* pDX)
{
  CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CTerminalsDlg, CDialog)

ON_WM_DESTROY()
ON_WM_SHOWWINDOW()
END_MESSAGE_MAP()


// CTerminalsDlg message handlers

BOOL CTerminalsDlg::OnInitDialog()
{
  CDialog::OnInitDialog();

  // TODO:  Add extra initialization here



  return TRUE;  // return TRUE unless you set the focus to a control
  // EXCEPTION: OCX Property Pages should return FALSE
}


void CTerminalsDlg::OnDestroy()
{
  CDialog::OnDestroy();
}

void CTerminalsDlg::OnOK()
{
}


void CTerminalsDlg::OnCancel()
{
}


void CTerminalsDlg::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialog::OnShowWindow(bShow, nStatus);
  if (bShow==SW_HIDE) return;
}
