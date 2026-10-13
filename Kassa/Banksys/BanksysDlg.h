// BanksysDlg.h : header file
//

#include <afxmt.h>
#include "MySocket.h"

#if !defined(AFX_BanksysDLG_H__F7EC1C76_EDC7_431C_BBB3_CF519A6A6C78__INCLUDED_)
#define AFX_BanksysDLG_H__F7EC1C76_EDC7_431C_BBB3_CF519A6A6C78__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CBanksysDlg dialog

class CBanksysDlg : public CDialog
{
// Construction
public:
	void SendToKassa(void *p);
	void vic_core_dumpHEX(int len,void *p);
	BOOL SendVIC_debit_request();
	void vic_core_dump4BCD(int getal);
	void vic_core_dump2BCD(int getal);
	int GetBCD(void *s, int len);
	int CBanksysDlg::GetInt(void *s, int len);
	void VICParseReceivedMessage();
	void vic_core_dump(int len, void *str);
	void VICAddField(char *DataElem);
	void VICClearFields();
	BOOL SendVIC_vmc_cancel(int ExecuteAlways);
	void ProcessAllMessages();
	void DumpLog(char *typ, void *s, int len);
	BOOL WriteCom(void *s, int len);
	void SendACK(unsigned char SEQNr);
	void SendWAK();
	void SendNAK();
	BOOL ProcessKissReadFrame(int FrameLen);
	void ComCheck();
	BOOL SendVICMessage(char *vic_msg_code);
	void WriteRegistrySettings();
	void ReadRegistrySettings();
	void StartListening();
	bool OpenComPort();
	int State;
	int OkPressedCount;
	DWORD TickTimeLastByteReceived;
	DWORD TickTimeStarted;
	char Amount[30];
  unsigned char KissReadFrame[MAX_KISS_FRAME_LEN*2];
	unsigned char KissReadSEQNr;
	unsigned char KissPrevAckedSEQNr;
	int KissReadLen;
	unsigned char vic_bit_map[6*8];
	unsigned char vic_core[MAX_KISS_FRAME_LEN];
	int vic_core_len;
	unsigned int vic_tx_id;
	unsigned char KissWriteResponse;
	unsigned char KissWriteAckedSeq;
	unsigned char KissWriteSEQNr;
	unsigned char VICMessageReceived[MAX_KISS_FRAME_LEN];
	int VICMessageReceivedLen;

	void CheckPayCard();
	void ProcCommand(CMySocket *pSesSock, char *cmd);
	CBanksysDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CBanksysDlg)
	enum { IDD = IDD_BANKSYS_DIALOG };
	CString	m_ComPort;
	CString	m_Status;
	BOOL	m_Logging;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBanksysDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
	HANDLE LogRef;
	HANDLE comref;
  CCriticalSection CritComCheck;
	BOOL CheckPayCardBusy;
	BOOL ComCheckBusy;
	BOOL MobielAllowed;
	BOOL VisaMCAllowed;
	BOOL MaaltijdChequeAllowed;
	BOOL EcoChequeAllowed;
	BOOL CadeauChequeAllowed;
	BOOL ConsumptieBonAllowed;
	BOOL AllCardsAllowed;
 
	CMySocket* pSrvSock;

	// Generated message map functions
	//{{AFX_MSG(CBanksysDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnDestroy();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnWindowPosChanging(WINDOWPOS FAR* lpwndpos);
	afx_msg void OnChangeComPort();
	afx_msg void OnTest();
	afx_msg void OnLogging();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BanksysDLG_H__F7EC1C76_EDC7_431C_BBB3_CF519A6A6C78__INCLUDED_)
