// AffDisplay.cpp : implementation file
//

#pragma warning(disable: 4996)
// #define WINVER 0x0501  // was 500
// #define _WIN32_WINNT 0x0501  // was 500

#include "stdafx.h"
#include "kassa.h"
#include "AffDisplay.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern char prt_head[10][41];

/////////////////////////////////////////////////////////////////////////////
// CAffDisplay dialog


CAffDisplay::CAffDisplay(CWnd* pParent /*=NULL*/)
	: CDialog(CAffDisplay::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAffDisplay)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	PictureDisplayed=false;
}

CAffDisplay::~CAffDisplay()
{
  if (PictureDisplayed) m_AffFrame.FreePictureData();
	this->DestroyWindow();
}


void CAffDisplay::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAffDisplay)
	DDX_Control(pDX, IDC_LABEL2, m_AffLabel);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAffDisplay, CDialog)
	//{{AFX_MSG_MAP(CAffDisplay)
	ON_WM_PAINT()
	ON_WM_DESTROY()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAffDisplay message handlers

BOOL CAffDisplay::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	if (GetFileAttributes("affiche.jpg")!=INVALID_FILE_ATTRIBUTES) {
	  m_AffFrame.Load("affiche.jpg");
		PictureDisplayed=true;
	}
  else if (GetFileAttributes("affiche.gif")!=INVALID_FILE_ATTRIBUTES) {
	  m_AffFrame.Load("affiche.gif");
		PictureDisplayed=true;
	}
	if (PictureDisplayed) m_AffLabel.ShowWindow(SW_HIDE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CAffDisplay::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	CDC cdc;
	cdc.Attach(dc.GetSafeHdc());

 	CRect AfficheRect;
	GetClientRect(&AfficheRect);
	m_AffFrame.Show(&cdc,&AfficheRect); 
	cdc.Detach();
	// Do not call CDialog::OnPaint() for painting messages
}

void CAffDisplay::OnDestroy() 
{
	CDialog::OnDestroy();
}

void CAffDisplay::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	
  int outtab[] = { /* output convert table JAMASCII -> intern'l video */
 /*  0   1   2   3   4   5   6   7   8   9   A   B   C   D   E   F  */
   126,126,126,126,126,126,126,  7,  8,126, 10,126,126, 13,126,126, /* 0X */
   126,126,126,126,126,126,126,126,126,126,126,126,126,126,126,126, /* 1X */
    32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, /* 2X */
    48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, /* 3X */
    64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, /* 4X */
    80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, /* 5X */
    96, 97, 98, 99,100,101,102,103,104,105,106,107,108,109,110,111, /* 6X */
   112,113,114,115,116,117,118,119,120,121,122,123,124,125,126,127, /* 7X */
   0xE1,0xE0,0xE2,0xE4,0xE7,0xE9,0xE8,0xEA,0xEB,0xED,0xEC,0xEE,0xEF,0xF3,0xF2,0xF4,  // 8x 
   0xF6,0xFA,0xF9,0xFB,0xFC,0xDC,0xBA,0xA7,0x2588,0x2190,0x2192,0x2191,0x2193,0x20,0x20,0x20AC,  // 9X
   126,126,126,126,126,126,126,126,126,126,126,126,126,126,126,126, /* AX */
   0x2592,0x2551,0x2550,0x255a,0x2551,0x2551,0x2554,0x2560,0x2550,0x255D,0x2550,0x2569,0x2557,0x2563,0x2566,0x256C, //BX
   0x2592,0x2551,0x2550,0x255a,0x2551,0x2551,0x2554,0x2560,0x2550,0x255D,0x2550,0x2569,0x2557,0x2563,0x2566,0x256C, //BC
   126,126,126,126,126,126,126,126,126,126,126,126,126,126,126,126, /* DX */
   126,126,126,126,126,126,126,126,126,126,126,126,126,126,126,126, /* EX */
   126,126,126,126,126,126,126,126,126,126,126,126,126,126,126,126};/* FX */

	if (m_AffLabel && !PictureDisplayed) {
	  CRect AffRect;
		CString buf;
		int i, j;
		LOGFONT logFont;

	  GetClientRect(&AffRect);
		AffRect.DeflateRect(0,(int)(AffRect.Height()*.20));
	  m_AffLabel.SetWindowPos(NULL,AffRect.left,AffRect.top,AffRect.Width(),AffRect.Height(),0);
//		m_AffLabel.SetFontSize(AffRect.Width()/(12*2));
//		m_AffLabel.SetFontName("tahoma");
//		m_AffLabel.SetFontBold(false);

		logFont.lfHeight = AffRect.Height()/10;
		logFont.lfWidth = AffRect.Width()/40;
		logFont.lfEscapement = 0;
		logFont.lfOrientation = 0;
		logFont.lfWeight = FW_REGULAR;
		logFont.lfItalic = FALSE;
		logFont.lfUnderline = FALSE;
		logFont.lfStrikeOut = FALSE;
		logFont.lfCharSet = ANSI_CHARSET;
		logFont.lfOutPrecision = 0;
		logFont.lfClipPrecision = 0;
		logFont.lfQuality = PROOF_QUALITY;
		//logFont.lfPitchAndFamily = FF_ROMAN | FIXED_PITCH;
		memcpy(logFont.lfFaceName, "Lucida Console", LF_FACESIZE);

		m_AffLabel.SetFont(logFont);

		m_AffLabel.SetTextColor(RGB(0,0,0));
//		m_AffLabel.SetBkColor(RGB(2,2,2));
//		m_AffLabel.SetBkColor(RGB(64,64,64),RGB(128,128,128), CLabel::Gradient);
//		m_AffLabel.SetBorder(true);
//		m_AffLabel.SetSunken(true);
//		m_AffLabel.SetFont3D(true, CLabel::Raised);
//		m_AffLabel.SetText3DHiliteColor(RGB(255,255,255));
		
	  buf="";
		for (i=0; i<10; i++) {
		  if (prt_head[i][0]!='*') {
				for (j=0; j<41; j++) {
					if (prt_head[i][j]==0) break;
					int byt=outtab[prt_head[i][j]];
					if (byt=='&') buf+="&&";
					else buf+=(unsigned char)byt;
				}
			}
			buf+="\r\n";
		}
		m_AffLabel.SetText(buf);
	}
}




