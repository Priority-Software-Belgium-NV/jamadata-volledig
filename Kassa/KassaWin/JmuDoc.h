#pragma once

#include "QuickPDFDLL0717.h"

#define RES 300
#define MAX_PAGES 5000
#define MaxMatrixPrinterDPI 299
#define QUICK_PDF_DLL_NAME	"jamap.dll"

#define  TRANS  1
#define  BARCODE 2
#define  DEVCONTROL 3
#define  INFO 4
#define  GELDOPEN 5
#define  PRTEXTRA 6

class CJmuDoc
{
public:
  CJmuDoc(void);
  virtual ~CJmuDoc(void);

 	// PDF gedeelte
  void DrawBarcode(CDC *pDC, double *pXpos, double *pYpos);
  bool Convert2Pdf(CString SplFilePath, CString PdfFilePath);
  bool WriteOnePage2Pdf(int pagenr);
  void DrawBarcode2Pdf(double *pXpos, double *pYpos);
  void DrawPCL2Pdf(unsigned char *pcl, long len, double *pXpos, double *pYpos);
  double TextSize[4];
  double TextHorCompr[4];
  double TextVertShift[4];
  int	FontID[2]; // 0 is normal, 1 is bold
  int	PclFontID;
  int	BedrukkingImageID[4]; // 3 is aantal lades, value = 1,2,3
  CString BedrukkingName[4];

	//Matrix gedeelte
	bool PrintOnMatrix(CString PrinterName, int PageFirst, int PageLast);
	void Matrix_specprt(char *pb);
	void Matrix_tkprt(char *pb);
	void Matrix_prchar(int byte);
	void Matrix_prch(int byte);
	void Matrix_PrintByte(int code);
	void Matrix_SelectDriver(int nr);
	void Matrix_prt39(char code);
	void Matrix_graph_exit(void);
	void Matrix_graph_init(int count);
  bool err_flag;
  HANDLE hMatrix;
	int PrinterDriver;
	char barcode[31];
	char RetBuf[1000];
  int RetBufUsed;
	char *cut_act;
	int cut_delay;
	char *linefeed;
	char _prtspec [2][21];
	char _prtoutt[128][2];
	int _cincr[8];
	char *_progseq[8];
	char *_prtactt[10];
	char _prt39[4][21];
  char *_geldopen[4];
  char *_ladeselect[3];
  bool bolflag;
  bool eloflag;
  bool undflag;
  int cincr;
  int cut2skip;
  int cut_flag;
  int spec;
	int bar_len;
  int pitch;

  // rest
  CString EMailAddress;
  CString TemplateName;
  BOOL PdfOutputEnabled;
  BOOL PdfPrinterFlag;
  int prtnr;
	bool MatrixFlag;
  bool BarcodeFlag;
  int  BarcodeLen;
  unsigned char BarcodeBuf[50];
  CSize PrintOffset;
  CSize Printable;
  bool BarImage[4000]; // 500 x 8 bits 
  int  BarImageIx;
	void UpdateRegistry();
	unsigned char image[1125000];
	void DrawPCL(CDC *pDC,unsigned char *pcl, long len, double *pXpos, double *pYpos);
  void DrawRect(CDC *pDC, int color, double Xpos, double Ypos, double Xlen, double Ylen);
  void ExtraExecute(CDC *pDC,CString ExtraCommand, double Xpos, double Ypos, int cpi);
	bool MakeOnePage(CDC *pDC, int pagnr);
	CFont fnt[3][8][16];
  double dist[8][16];
	double Hscale, Vscale;
  CImage ImgLayout;
	int Hsc(double in);
  int Vsc(double in);
	void InitFnt();
  void prt39(char code);
  void add_image(int bit, int count);
  void msi(int type);

  CString FileName;
  CString PdfFilePathOnePdf;
	CString DocumentName;
	bool PrintDocument(CString SplFilePath, CString WindowsPrinterName);
  BOOL ReadDocument(LPCTSTR lpszPathName, int PrinterNr, bool WindowsPrinter);
  void CalcPrinterParms(CDC *pDC);
  CString SpoolFilePath;
	bool SheetFlag;
	bool PdfFlag;
	int PrinterNr;
  bool WinLayoutFlag;
  bool PrintDocRectoVerso;
  bool PrintDocForceBW;
  bool PrintDocExtraMarginLeft;
  bool PrintDocExtraMarginOnTop;
  int PrinterSetMediaRef;
  int PrinterSetBinRef;
  int PrinterSetPaperRef;

  bool DemoFlag;
	int PageW;
	int PageH;
	int SPLLen;
	int PageCnt;
	short int Parm[12];
  unsigned char *bParm;
	long Page2Pos[MAX_PAGES];
  unsigned char Page2cpi[MAX_PAGES];
  bool Page2Landscape[MAX_PAGES];
  bool PrintDocFullLandscape;
  double DocLpi;
  int Page2Lade[MAX_PAGES];
 	unsigned char *SPL;
	CFile SpoolFile;

  
  CString BedrukkingFileName[4];
  BOOL BedrukkingFlag[4];
  BOOL BedrukkingAllowed;

  CString m_FontName;
  BOOL m_FontBold;
  BOOL m_FontItalic;
  CString m_PCLFontName;
  BOOL m_PCLFontBold;
  BOOL m_PCLFontItalic;
  int m_PCLScale;
  BOOL m_EurSignSimulation;
  QuickPDFDLL0717 *pQP;
  bool OnePdfFlag;  
};

