// MySocket.cpp : implementation file
//

#include "stdafx.h"
#include "Cardfon.h"
#include "CardfonDlg.h"
#include "MySocket.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CMySocket SesSock;

/////////////////////////////////////////////////////////////////////////////
// CMySocket

CMySocket::CMySocket(CCardfonDlg *pDlg)
{
	m_pCardfonDlg=pDlg;
	RecLen=0;
}

CMySocket::~CMySocket()
{
}


// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(CMySocket, CSocket)
	//{{AFX_MSG_MAP(CMySocket)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0

/////////////////////////////////////////////////////////////////////////////
// CMySocket member functions

void CMySocket::OnAccept(int nErrorCode) 
{
	CMySocket *pClientSock;

	if (SesSock.m_hSocket==INVALID_SOCKET) {
		Accept(SesSock);
	}
	else {
  	pClientSock = new CMySocket(m_pCardfonDlg);
  	Accept(*pClientSock);
		pClientSock->Send("!BUSY\r\n",7,0);
		Sleep(1000);
		pClientSock->Close();
		Sleep(1000);
		delete pClientSock;
	}
}

void CMySocket::OnReceive(int nErrorCode) 
{
	int i, Len;
	char cmdbuf[100];

	Len=Receive(&RecBuf[RecLen],sizeof(RecBuf)-RecLen,0);
	if (Len>0) RecLen+=Len;
	i=0;
	while (i<RecLen) {
		if (RecBuf[i]=='\n') {
			i++;
  		memcpy(cmdbuf,RecBuf,i);
	  	cmdbuf[i]=0;
			if (i<RecLen) {
				memmove(&RecBuf[0],&RecBuf[i],RecLen-i);
			}
			RecLen-=i; i=0;
 			m_pCardfonDlg->ProcCommand(this, cmdbuf);
		}
		else i++;
	}
}

void CMySocket::OnClose(int nErrorCode) 
{
 	int i=1;
	m_hSocket=INVALID_SOCKET;
	CSocket::OnClose(nErrorCode);
}
