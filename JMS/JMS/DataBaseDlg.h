#pragma once
#include "afxwin.h"


#define TIMER10SEC 10
#define VALTIMER10SEC 10

// CDataBaseDlg dialog

class CDataBaseDlg : public CDialog
{
	DECLARE_DYNAMIC(CDataBaseDlg)

public:
	CDataBaseDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDataBaseDlg();

// Dialog Data
	enum { IDD = IDD_DATABASEDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnexport2fas();
protected:
	virtual void OnOK();
public:
	CComboBox m_cboImportList;
	afx_msg void OnBnClickedBtnimport();
	afx_msg void OnCbnSetfocusCboimportlist();
	afx_msg void OnCbnSelchangeCboimportlist();
//	CButton m_btnImport;
	CListBox m_lstDBAvailable;
	CListBox m_lstDBMounted;
	afx_msg void OnBnClickedBtnmount();
	afx_msg void OnBnClickedBtnunmount();
//	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnBnClickedBtnrefresh();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
//	CButton m_btnBackup;
//	CButton m_btnCompact;
	CButton m_btnExport2Fas;
	virtual BOOL OnInitDialog();
	bool m_UpAndRunning;
//	afx_msg void OnLbnSelchangeLstavailabledb();
	CButton m_btnCheck;
	afx_msg void OnBnClickedBtncheck();
	CComboBox m_cboSysSelect;
	afx_msg void OnLbnSelchangeLstmounteddb();
	afx_msg void OnLbnSelchangeLstavailabledb();
	CButton m_btnMount;
	CButton m_btnUnMount;
	CButton m_btnZipBackup;
	afx_msg void OnBnClickedBtnzipbackup();
	CComboBox m_cboAutoZipTime;
	afx_msg void OnCbnSelchangeAutoziptime();
	afx_msg void DoAutoZipBackup();
  afx_msg void OnBnClickedBtndump2copy();
  CButton m_btnDump2Copy;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};


// CUtilitysDlg dialog

class CUtilitysDlg : public CDialog
{
	DECLARE_DYNAMIC(CUtilitysDlg)

public:
	CUtilitysDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CUtilitysDlg();

// Dialog Data
	enum { IDD = IDD_UTILITYSDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_cboSysSelect;
	CComboBox m_cboSysValType;
	CEdit m_edtSysPos;
	CEdit m_edtSysValue;
	virtual BOOL OnInitDialog();
	afx_msg void OnCbnSelchangeCbosysselect();
	afx_msg void OnCbnSelchangeCboupsystype();
	afx_msg void OnEnKillfocusEditsyspos();
	afx_msg void OnBnClickedBtnsysupdate();
	CEdit m_edtStringLen;
	void UpdateSysValue(bool ForceUpdate=false);
	int m_SysType;
	int m_SysPos;
	int m_SysLen;
	char m_DataBaseName[20];
	int m_Prev_SysType;
	int m_Prev_SysPos;
	int m_Prev_SysLen;
	char m_Prev_DataBaseName[20];
	afx_msg void OnEnKillfocusEditstringlen();
	afx_msg void OnEnSetfocusEditsysvalue();
	bool UpdateSysfile(char* DataBaseName, int Type, int Pos, int Len, char* buf);
	void ExecCmdLine(CString CmdLine);
protected:
	virtual void OnOK();
public:
//	afx_msg void OnCbnSetfocusCbosysselect();
	CListBox m_lstSlaveTables;
	CListBox m_lstMasterTables;
	CComboBox m_cboSlaveDB;
	CComboBox m_cboMasterDB;
	afx_msg void OnBnClickedBtnlink();
	afx_msg void OnBnClickedBtnunlink();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnCbnSelchangeCbomasterdb();
	afx_msg void OnCbnSelchangeCboslavedb();
};
