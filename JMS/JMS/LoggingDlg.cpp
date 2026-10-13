// LoggingDlg.cpp : implementation file
//

#include "stdafx.h"
#include "JMS.h"
#include "LoggingDlg.h"


// CLoggingDlg dialog

IMPLEMENT_DYNAMIC(CLoggingDlg, CDialog)

CLoggingDlg::CLoggingDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CLoggingDlg::IDD, pParent)
{

}

CLoggingDlg::~CLoggingDlg()
{
}

void CLoggingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LstLogging, m_listLogging);
}


BEGIN_MESSAGE_MAP(CLoggingDlg, CDialog)
END_MESSAGE_MAP()


// CLoggingDlg message handlers
