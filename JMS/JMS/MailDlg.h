#pragma once


// CMailDlg dialog

class CMailDlg : public CDialog
{
	DECLARE_DYNAMIC(CMailDlg)

public:
	CMailDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CMailDlg();

// Dialog Data
	enum { IDD = IDD_MAILDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	void SendTestMail(void);
	afx_msg void OnBnClickedbtnsendtestmail();
	bool SendMail(char* FileName);
	CString IpNumber;
	int MailProfileNr;
protected:
	virtual void OnOK();
public:
  CString CheckEmailAddress(CString EmailAddress);
  virtual BOOL OnInitDialog();
  CString MailSubDir;
  CString MailSubDirTemp;
	CString MakeMailKeyword(char *keyword_);
  void ScanMailDir(void);
  bool ScanMailDirBusy;
  bool SelectImapFolder(CString FolderName);
  CString GetTemplateNames(void);
  CString GetTemplateMergeFields(CString TemplateRef);
	CString GetMailEnveloppes(CString Cmd, unsigned short OrigId);
	CString GetMailMessage(CString Cmd, unsigned short OrigId);
  CString MergeTemplateAndMail(CString Cmd, unsigned short OrigId);
  CString ViewMail(CString Cmd, unsigned short OrigId);
  void FindAllMergeFields(CString& strReturn, CString Text);
};
