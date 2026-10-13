#pragma once

#include "JmuDoc.h"

// CPrintersDlg dialog

class CPrintersDlg : public CDialog
{
	DECLARE_DYNAMIC(CPrintersDlg)

public:
	CPrintersDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CPrintersDlg();
// Dialog Data
	enum { IDD = IDD_PRINTERSDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()


public:
  afx_msg void OnBnClickedButton1();
  int GetPrinterNr(int PostNr, int PrinterNr);
  CString AddSPLFileToPrintQueue(CString FilePathAndPostNr);
  virtual BOOL OnInitDialog();
  CString GetAllPrinterNames();
  CString GetAllPrinterBins(CString PrinterName);
  CString GetAllPrinterMedia(CString PrinterName);
  CString GetAllPrinterPapers(CString PrinterName);
  CJmuDoc* pDoc;
  afx_msg void OnDestroy();
};
