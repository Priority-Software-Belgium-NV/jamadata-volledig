
// JMSDlg.h : header file
//

#pragma once
#include "afxcmn.h"
#include "DataBaseDlg.h"
#include "PrintersDlg.h"
#include "TerminalsDlg.h"
#include "MailDlg.h"
#include "LoggingDlg.h"

#define TIMER1MIN 8
#define VALTIMER1MIN 60

#define TIMER5MIN 9
#define VALTIMER5MIN 300

// CJMSDlg dialog
class CJMSDlg : public CDialog
{
	// Construction
public:
	CJMSDlg(CWnd* pParent = NULL);	// standard constructor
	CDataBaseDlg m_dDataBaseDlg;
	CTerminalsDlg m_dTerminalsDlg;
	CPrintersDlg m_dPrintersDlg;
	CMailDlg m_dMailDlg;
	CLoggingDlg m_dLoggingDlg;
	CUtilitysDlg m_dUtilitysDlg;
	CRect m_rJMSRect;
	CTime NextAutoZipBackup;


	// Dialog Data
	enum { IDD = IDD_JMWSERVER_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CTabCtrl m_cTab;
	afx_msg void OnTcnSelchangeTabseldlg(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	void ShowWindowNumber(int Number);
	void ProcessAllMessages(void);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnClose();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	virtual void OnFinalRelease();
	int m_PrevTabSelected;
	bool ControlledByJMTflag;
	//	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	CString SendHTTPPost(CString strCommand, CString strMessage, CString strFileName = "");
	bool CreateZipFromFasBack(char *ext);
	bool CreateZipSnapShotFromFasBack(char *ext, CString FileList, CString PathZip, int LifeTimeMinutes);
	void CreateFullJamadataBackup(bool IncludeWorkFiles, int PostNr);
	bool CreateAndMaintainZipArchiveFTKopie(CString ZipFilePath);
	bool IsValidZipArchive(char *FilePath);
	bool AreSnapShotsIdentical(CString FilePath1, CString FilePath2);
	CString CJMSDlg::CmdWebrequestJson(CString Cmd); // WebrequestJson url|Method|User|PW|HeaderKey|HeaderValue|Body|FilePath|Boundary
	CString CJMSDlg::GetPipeItem(CString Pipe, int Index);
	CString CJMSDlg::CmdViesGetVat(CString Cmd);
	CString CJMSDlg::CmdFtpUpload(CString Cmd);
	CString CJMSDlg::CmdFtpDownload(CString Cmd);
	CString CJMSDlg::CmdFtpDirectory(CString Cmd);
	CString CJMSDlg::CmdFtpDelete(CString Cmd);
	CString CJMSDlg::CmdIbanityShowLicence(CString Cmd);
	CString CJMSDlg::CmdIbanityCheckVAT(CString Cmd);
	CString CJMSDlg::CmdIbanityCheckGLN(CString Cmd);
	CString CJMSDlg::CmdIbanityUBLUpload(CString Cmd);
	CString CJMSDlg::CmdIbanityUBLStatus(CString Cmd);
	CString CJMSDlg::CmdPeppolExportDocuments(CString Cmd);
	CString CJMSDlg::CmdPeppolGetDocumentStatus(CString Cmd);
	CString CJMSDlg::CmdPeppolLookup(CString Cmd);
	CString CJMSDlg::CmdPeppolMarkDocumentAsExported(CString Cmd);
	CString CJMSDlg::CmdPeppolSendDocument(CString Cmd);
	CString CJMSDlg::CmdPepPolCheckVAT(CString Cmd);
	CString CJMSDlg::CmdPepPolUBLUpload(CString Cmd);
	CString CJMSDlg::CmdPepPolUBLStatus(CString Cmd);
	CString CJMSDlg::CmdJsonToXml(CString Cmd);
	CString CJMSDlg::CmdXmlToJson(CString Cmd);
	CString CJMSDlg::CmdSFtpUpload(CString Cmd);
	CString CJMSDlg::CmdSFtpUpload2(CString Cmd);
	CString CJMSDlg::CmdSFtpDownload(CString Cmd);
	CString CJMSDlg::CmdSFtpDownload2(CString Cmd);
	CString CJMSDlg::CmdSFtpDirectory(CString Cmd);
	CString CJMSDlg::CmdSFtpDirectory2(CString Cmd);
	CString CJMSDlg::CmdSFtpDelete(CString Cmd);
	CString CJMSDlg::CmdSFtpDelete2(CString Cmd);
	bool CreateZipArchiveJamaSubDir(CString JamaSubDir, CString ZipFilePath);
	bool CreateZipFromFileList(CString FileList, CString ZipFilePath);
	bool CreateZipFromFile(CString FilePath, CString ZipFilePath);
	bool CreateZipFromPath(CString Path, CString ZipFilePath);
	bool ZipExtractAll(CString ZipFilePath, CString ZipSubDir, bool OverwriteExistingFiles = false);
	//  virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
  //  afx_msg void OnWindowPosChanging(WINDOWPOS* lpwndpos);
	virtual BOOL OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	afx_msg void OnEndSession(BOOL bEnding);
	CString GetJMSExeVersion(void);
};
#pragma once


// CJMPassword dialog

class CJMPassword : public CDialog
{
	DECLARE_DYNAMIC(CJMPassword)

public:
	CJMPassword(CWnd* pParent = NULL);   // standard constructor
	virtual ~CJMPassword();

	// Dialog Data
	enum { IDD = IDD_JMPASSWORD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	//	afx_msg void OnEnChangeJmpasswordtext();
	CString m_PWEntered;
	afx_msg void OnEnUpdateJmpasswordtext();
	afx_msg void OnEnKillfocusJmpasswordtext();
};
