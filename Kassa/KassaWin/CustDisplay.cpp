// CustDisplay.cpp : implementation file
//

#pragma warning(disable: 4996)
// #define WINVER 0x0501  // was 500
// #define _WIN32_WINNT 0x0501  // was 500

#include "stdafx.h"
#include "kassa.h"
#include "CustDisplay.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern char reclame[6][11][22];

/////////////////////////////////////////////////////////////////////////////
// CCustDisplay dialog


CCustDisplay::CCustDisplay(CWnd* pParent /*=NULL*/)
	: CDialog(CCustDisplay::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCustDisplay)
	//}}AFX_DATA_INIT
	State=0;
	lineix=0;
}

CCustDisplay::~CCustDisplay()
{
	this->DestroyWindow();
}

void CCustDisplay::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCustDisplay)
	DDX_Control(pDX, IDC_LABEL, m_CustLabel);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCustDisplay, CDialog)
	//{{AFX_MSG_MAP(CCustDisplay)
	ON_WM_TIMER()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCustDisplay message handlers

void CCustDisplay::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	if (nIDEvent==1) {
		if (++State==4) State=0;

		if (State==0) m_CustLabel.SetText("");
	  if (State==1) {
			char b;
			CString cstr;
			int j, ir_rec_nr, lineix_onentry;
 
			cstr=""; lineix_onentry=lineix;
		retry:;
			ir_rec_nr=lineix/10;
			for (j=0; j<20; j++) {
				b=reclame[ir_rec_nr][lineix%10][j];
				if (!b) break;
				else cstr+=b;
			}
			lineix++;
			if (cstr.GetLength()>0) cstr+="\r\n";
			for (j=0; j<20; j++) {
				b=reclame[ir_rec_nr][lineix%10][j];
				if (!b) break;
				else cstr+=b;
			}
			if (++lineix>=30) lineix=0;
			if (cstr.GetLength()) m_CustLabel.SetText(cstr);
			else {
				if (lineix!=lineix_onentry) goto retry;
				m_CustLabel.SetText("Bedankt voor uw bezoek\r\nen tot de volgende keer!");
			}				  
		}
	}
  else CDialog::OnTimer(nIDEvent);
}

BOOL CCustDisplay::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	SetTimer(1,1000,NULL);

		CRect CustRect;
 		GetClientRect(&CustRect);
		m_CustLabel.SetWindowPos(NULL,CustRect.left,CustRect.top,CustRect.Width(),CustRect.Height(),0);
		m_CustLabel.SetFontName("Arial");
		m_CustLabel.SetFontBold(true);
		m_CustLabel.SetTextColor(RGB(0,0,0));
	  m_CustLabel.SetText("");
		m_CustLabel.SetBkColor(RGB(0,0,128));
//		m_CustLabel.SetBkColor(RGB(0,0,128),RGB(0,0,255), CLabel::Gradient);
		m_CustLabel.SetBorder(false);
		m_CustLabel.SetSunken(false);
		m_CustLabel.SetFont3D(true, CLabel::Raised);
		m_CustLabel.SetText3DHiliteColor(RGB(255,255,0));



	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CCustDisplay::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	
	if (m_CustLabel) {
	  CRect CustRect;
	  GetClientRect(&CustRect);
    m_CustLabel.SetWindowPos(NULL,CustRect.left,CustRect.top,CustRect.Width(),CustRect.Height(),0);

		int FontSize1 = CustRect.Width() / 18;
		int FontSize2 = (int) (CustRect.Height() / 3.2);
		int FontSize=FontSize2;
		if (FontSize1<FontSize) FontSize = FontSize1;

		m_CustLabel.SetFontSize(FontSize);
	}
}
