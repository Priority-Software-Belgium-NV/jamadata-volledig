#include "stdafx.h"
#include "winspool.h"
#include "JmuDoc.h"
#include "atlimage.h"

#define CONTROL2PDF 1

extern int PrintControl2PDF;

#define DblVsc(in)  (double)(Vscale*in)
#define DblHsc(in)  (double)(Hscale*in)

static unsigned char jama2ansi[128] = {
		225,224,226,228,231, //á,à,â,ä,ç,
		233,232,234,235,     //é,è,ê,ë,
		237,236,238,239,     //í,ì,ì,ï,
		243,242,244,246,		 //ó,ò,ô,ö,
    250,249,251,252,220, //ú,ù,û,ü,Ü,
    175,167,0,0,0,0,0,0,0,  // °,§,
		128                  // EUR
};

CJmuDoc::CJmuDoc(void)
{
  OnePdfFlag=false;
  PdfFilePathOnePdf="";
  SPL=NULL;
  PdfOutputEnabled=true;
  m_EurSignSimulation=FALSE;
  m_FontName="Courier New";
  m_FontBold=false;
  m_FontItalic=false;
  m_PCLFontName="Arial";
  m_PCLScale=100;
  m_PCLFontBold=FALSE;
  m_PCLFontItalic=FALSE;
  bParm=(unsigned char*) Parm;
  pQP=NULL;
}

CJmuDoc::~CJmuDoc(void)
{
	if (SPL!=NULL) {delete [] SPL; SPL=NULL;}
	if (pQP!=NULL) {delete pQP; pQP=NULL;}
}

bool CJmuDoc::PrintDocument(CString SplFilePath, CString WindowsPrinterName)
{
  SpoolFilePath=SplFilePath;

  // normaal binnen 1 job geen 2 verschillende page-orientations, zo wel, dan eventueel jobs opsplitsen
  if (Page2Landscape[1]) PrintDocFullLandscape=true;

  HANDLE printer_handle;
  LPHANDLE printer_handle_pointer(&printer_handle);
  if (!OpenPrinter((LPSTR)(LPCTSTR)WindowsPrinterName, printer_handle_pointer, NULL)) {  // foutieve printer naam ? 
    // Get DefaultPrinter
    char DefPrinterNameBuf[250+1];
    DWORD NameSize=250;
    if (GetDefaultPrinter(DefPrinterNameBuf,&NameSize) && NameSize>1) WindowsPrinterName=DefPrinterNameBuf;
    if (!OpenPrinter((LPSTR)(LPCTSTR)WindowsPrinterName, printer_handle_pointer, NULL)) return false; // kan echt niet afdrukken !
  }
  CString cstr;
  cstr.Format("PrinterOpen: %s",WindowsPrinterName);
  // LogAdd(0,2,cstr);
  size_t devmode_size = DocumentProperties(NULL, printer_handle,(LPSTR)(LPCTSTR)WindowsPrinterName, NULL, NULL, 0);
  DEVMODE * devmode = reinterpret_cast<DEVMODE *>(new char[devmode_size]);
  DocumentProperties(NULL, printer_handle, (LPSTR)(LPCTSTR)WindowsPrinterName, devmode, NULL, DM_OUT_BUFFER);
  devmode->dmSize = sizeof( DEVMODE);
  // overgenomen uit JMU van vroeger 
  devmode->dmPaperSize=DMPAPER_A4;
  devmode->dmYResolution=300;
  devmode->dmPrintQuality=300;  
  // set parameters die in de JMS.ini voor elke JamadataPrinter Instance opgegeven zijn !
  if (PrinterSetMediaRef) devmode->dmMediaType=PrinterSetMediaRef;
  if (PrinterSetBinRef) devmode->dmDefaultSource=PrinterSetBinRef;
  if (PrinterSetPaperRef) devmode->dmPaperSize=PrinterSetPaperRef;

  // nieuwe instellingen 
  if (PrintDocFullLandscape) {
    devmode->dmFields |= DM_ORIENTATION;
    devmode->dmOrientation = DMORIENT_LANDSCAPE;
  }
  if (PrintDocForceBW) devmode->dmColor=DMCOLOR_MONOCHROME;
  if (PrintDocRectoVerso) { // duplex ?? 
    if (PrintDocFullLandscape && PrintDocExtraMarginLeft) devmode->dmDuplex=DMDUP_HORIZONTAL; // anders spiegelen op printer zo Landscape en toch links inbinden (normaal zou het boven zijn)
    else if (!PrintDocFullLandscape && PrintDocExtraMarginOnTop) devmode->dmDuplex=DMDUP_HORIZONTAL; // anders spiegelen op printer zo Portrait en toch boven inbinden (normaal zou het links zijn)
    else devmode->dmDuplex=DMDUP_VERTICAL; // zo de gaten staan waar we ze verwachten (landscape boven, portrait links)
  }

  DocumentProperties(NULL, printer_handle, (LPSTR)(LPCTSTR)WindowsPrinterName, devmode, devmode, DM_IN_BUFFER | DM_OUT_BUFFER);
  ClosePrinter(printer_handle);
  HDC hdcPrn = CreateDC("WINSPOOL",WindowsPrinterName,NULL, devmode); // voor win95/98 e.d. ... moet de WINSPOOL NULL zijn ... maar voor JMS is XP nodig ...
  cstr.Format("CreateDC returned %d",hdcPrn);
  // LogAdd(0,2,cstr);
  delete devmode;

  if (hdcPrn != NULL) {
      CDC *pDC = new CDC;
      pDC->Attach (hdcPrn);      // attach a printer DC
      CalcPrinterParms(pDC);
      pDC->StartDoc(DocumentName);  // begin a new print job
                              // for Win32 use
                              // CDC::StartDoc(LPDOCINFO) override
      for (int PageNr=1; PageNr<=PageCnt; PageNr++) {
        pDC->StartPage();          // begin a new page
        MakeOnePage(pDC,PageNr);
        pDC->EndPage();            // end a page
      }

      pDC->EndDoc();             // end a print job
      pDC->Detach();             // detach the printer DC
      delete pDC;
      DeleteObject(hdcPrn);
      cstr.Format("Printed %s (%d pages) on %s", DocumentName, PageCnt, WindowsPrinterName);
      // LogAdd(0,2,cstr);
      return true;
  }
  else {
    int err=GetLastError();
  }
  return false;
}

void CJmuDoc::CalcPrinterParms(CDC *pDC)
{
  double papscale;
  int i;
  CString s;
 
  /********** volgende code komt uit JMU maar kan hier precies niet ...
  LPDEVMODE pDevMode;
  pDevMode = pInfo->m_pPD->GetDevMode();
  pDevMode->dmPaperSize=DMPAPER_A4;
  pDevMode->dmYResolution=300;
  pDevMode->dmPrintQuality=300;    
  pDC->ResetDC(pDevMode);
  ::GlobalUnlock(pDevMode);
  */

  //CRect size=pInfo->m_rectDraw;
  int iEsc = PASSTHROUGH;
  i= pDC->Escape(QUERYESCSUPPORT, sizeof(int), (LPSTR)&iEsc, NULL);

  pDC->SetMapMode(MM_TEXT);
  Hscale=(double)pDC->GetDeviceCaps(LOGPIXELSX)/RES;
  Vscale=(double)pDC->GetDeviceCaps(LOGPIXELSY)/RES;
  
  // volgende code kijkt of de afprintbare area in de hoogte niet te klein is. En zo ja,
  // dan drukken we de lijnen wat dichter af. Is interessant voor lijsten op kettingpapier ...
  PrintOffset.cx=0; PrintOffset.cy=0;
  Printable.cx=2480; Printable.cy=3507;
  if (!SheetFlag) {
    papscale=(double)pDC->GetDeviceCaps(VERTRES)*RES/pDC->GetDeviceCaps(LOGPIXELSY);
    papscale/=Parm[1];
    if (papscale<1.) Vscale*=papscale;
  }
  else {
    PrintOffset.cx = (int) (.5+pDC->GetDeviceCaps(PHYSICALOFFSETX)/Hscale);
    PrintOffset.cy = (int) (.5+pDC->GetDeviceCaps(PHYSICALOFFSETY)/Vscale);
    Printable.cx = (int)(.5+pDC->GetDeviceCaps(HORZSIZE)/Hscale);
    Printable.cy = (int)(.5+pDC->GetDeviceCaps(VERTSIZE)/Vscale);
  }
  
  InitFnt();
}

/*
  prtnr=-1;
  i=pDoc->FileName.GetLength();
  if (i>0) {
    for (i--; i>=0; i--) {
      if (pDoc->FileName.GetAt(i)=='.') {
        i-=8;
        break;
      }
    }
    prtnr=pDoc->FileName.GetAt(i);
    if (prtnr>='a') prtnr-=('a'+'9');
    else if (prtnr>='A') prtnr-=('A'+'9');
    prtnr-='0';
    if (prtnr<1 || prtnr>10) prtnr=1;
  }
  else prtnr=0;

  AddJmuLog("Begin AppPrinter selecteren");
  if (!myApp->SetAppPrinter(prtnr)) {
    pDoc->DocClear();
    return false;
  }
  AddJmuLog("Done AppPrinter selecteren");

  pInfo->SetMaxPage(pDoc->PageCnt);
  pInfo->SetMinPage(1);

  AddJmuLog("Begin PreparePrinting");
  ret=DoPreparePrinting(pInfo);
  AddJmuLog("Done PreparePrinting");

  if (!ret) {
    if (pDoc->DemoFlag) pDoc->DocClear();
    return ret;
  }

  AddJmuLog("Begin CreateDC");
  if(!dc.CreateDC(pInfo->m_pPD->GetDriverName(), pInfo->m_pPD->GetDeviceName(), pInfo->m_pPD->GetPortName(), NULL))
  {
    AfxMessageBox(_T("Can't create DC in print_loop"));
    return false;
  } 

  PreviewFlag=pInfo->m_bPreview;
  MatrixFlag=false;
  if (MatrixDriver[prtnr-1]>=0) { // dc.GetDeviceCaps(LOGPIXELSX)<=MaxMatrixPrinterDPI) {
    MatrixFlag=true;
  }
  if (MatrixFlag && !PreviewFlag) {
    pMP= new CMatrixPrinter();
    pMP->SelectDriver(MatrixDriver[prtnr-1]);
    printed=pMP->Print(pInfo->m_pPD->GetDeviceName(), pDoc, pInfo->GetFromPage(),pInfo->GetToPage());
    delete pMP;
    pMP=NULL;
    if (printed && ((int)pInfo->GetToPage()>=pDoc->PageCnt)) {
      pDoc->DocPrinted();
    }
    ret=false;
  }
	else if (!PreviewFlag) {
		pInfo->m_bDirect=TRUE;
	}
  dc.DeleteDC();
  AddJmuLog("Done CreateDC");
  return ret;
*/


BOOL CJmuDoc::ReadDocument(LPCTSTR lpszPathName, int PrinterNr, bool WindowsPrinter) 
{
  char fnt;
  long pos, len, totlen, *pLong;
  double LinePos, LineInc;
  int i, Lade;
  bool eMailFlag=false, TemplateFlag=false, Ketting2WindowsPrinter=false;
    
  // set default values
  PdfPrinterFlag=FALSE;
  for (int j=0; j<4; j++) {
    BedrukkingFileName[j]="";
    BedrukkingFlag[j]=false;
  }
  PrintDocRectoVerso=false;
  PrintDocForceBW=false;
  PrintDocExtraMarginLeft=false;
  PrintDocExtraMarginOnTop=false;
  PrintDocFullLandscape=false;
  PrinterSetMediaRef=0;
  PrinterSetBinRef=0;
  PrinterSetPaperRef=0;
  DocLpi=6.;
  BarcodeFlag=false;

  if (!SpoolFile.Open(lpszPathName, CFile::shareDenyNone | CFile::modeRead, NULL)) {
    return false;
  }
  // bv.: 00000030-000-0-250-EET-000-082-003-000-$Grootboekfiche.spl
  //                                         000 is bedrukking nr
  CString FileName=lpszPathName;
  i=FileName.ReverseFind('\\');
  FileName=FileName.Mid(i+1);
  int BedrukkingRef=1; // atol(FileName.Mid(35,3));
  if (BedrukkingRef>0) {
    CString SysExt=FileName.Mid(19,3);
    for (int j=0; j<4; j++) {
#if CONTROL2PDF
  		if(PrintControl2PDF) continue;
#endif
      BedrukkingFileName[j].Format("KeyFact.png");
      BedrukkingFlag[j]=true;
    }
  }

  CString str;
  str="Opening ";
  str+=lpszPathName;
  str+="\n";
  TRACE(str);

  FileName=lpszPathName;
  if (SPL!=NULL) {
		delete [] SPL;
		SPL=NULL;
	}
  totlen=(long)SpoolFile.GetLength();
  SPL= new unsigned char[totlen+100];
  if (SPL==NULL) {
    SpoolFile.Close();
    return false;
  }

  for (i=0; i<MAX_PAGES; i++) {
    Page2Landscape[i]=false;
    Page2Lade[i]=1;
    Page2cpi[i]=0;
  }
  SpoolFile.Read(Parm,sizeof(Parm)); totlen-=sizeof(Parm);
  if (Parm[0]==0) Parm[0]=2850; // probleem van HUE oplossen, die printte ooit af op papiertype 9
  if (Parm[1]==0) Parm[1]=3600; // en dan blokkeerde de hele boel ! Was met leeg papiertype
  /// 

  char *b = (char *)Parm;
  DocLpi=b[16];
  
  if (Parm[11]&0x02) PrintDocRectoVerso=true;
  if (Parm[11]&0x04) PrintDocFullLandscape=true;
  if (Parm[11]&0x08) PrintDocForceBW=true;
  if (Parm[11]&0x10) PrintDocExtraMarginLeft=true;
  if (Parm[11]&0x20) PrintDocExtraMarginOnTop=true;

  SPLLen=0;
  while (totlen>0) {
    len=totlen;
    if (len>128*256) len=128*256;
    len = SpoolFile.Read(SPL+SPLLen, len);
    if (len==0) break;
    SPLLen+=len;
    totlen-=len;
  }  
	SpoolFile.Close();
  
  SheetFlag=true;
  if (bParm[14]==1) SheetFlag=false;
#if CONTROL2PDF
	if(PrintControl2PDF){
  	PdfPrinterFlag=TRUE;
	  SheetFlag=false;
	}
#endif
  if (!SheetFlag && WindowsPrinter) {  // bv. matrixlijst op Laserprinter
    int OldParm1=Parm[1];
    Parm[0]=2480; Parm[1]=3507; Parm[2]=0; Parm[3]=118; Parm[4]=118; Parm[5]=118; Parm[6]=118; bParm[14]=4;
#if CONTROL2PDF
		if(PrintControl2PDF) Parm[1]=3300;
#endif
    DocLpi=(DocLpi*OldParm1)/(Parm[1]-Parm[6]); // parm[4] wordt al gecompenseerd door extra lijnen (zie verder voor PageH)
    Ketting2WindowsPrinter=true;
    SheetFlag=true;
  }
  PageCnt=0;
  Page2Pos[++PageCnt]=0;
  LinePos=0.;
  LineInc=(double)(300./DocLpi);
  Lade=1; DocumentName="";
  for (pos=0; pos<SPLLen; pos++) {
    if (SPL[pos]==0xEF) {
      pos+=(3-1);
      continue;
    }
    if (SPL[pos]==0xFE) { // zou niet meer mogen voorkomen. Wordt omgezet naar 0xEE
      pos+=(2-1);
      continue;
    }
    if (SPL[pos]==0xEE && SPL[pos+1]==1) {
      SheetFlag=true; // HP-PCL code kan alleen op losse vellen, dus voor alle zekerheid de flag correct zetten
      pLong = (long *)&SPL[pos+2];
      for (i=pos+1+sizeof(long); i<pos+100; i++) {
        if (_memicmp(&SPL[i],"\x1B&l1o",5)==0) {
          Page2Landscape[PageCnt]=true;
          break;
        }
      }
      pos+=(*pLong+6-1);
      continue;
    }
    if (SPL[pos]==0xD0) {
		  if (SPL[pos+1]==0xCF) {  // DocumentName in binaire zone
			  for (i=0; i<30; i++) {
				  if (SPL[pos+2+i]==0xD0) break;
          else {
            if (SPL[pos+2+i]==0xEF) {         // repeat factor
              int RepeatCnt=SPL[pos+2+i+2];
              while (RepeatCnt-->0) {
                DocumentName += SPL[pos+2+i+1];
              }
              i+=2;
            }
            else DocumentName += SPL[pos+2+i];
          }
				}
				pos=pos+2+i;
			}
 			else if (SPL[pos+1]==0xCE) {  // Overule om Document in PDF uit te schrijven !
			  PdfFlag=true;
				pos+=2;									// 0xD0  0xCE  0xD0 (3 bytes dus)
				while (SPL[pos]!=0xD0) pos++;
			}
			else if (SPL[pos+1]==0xCD) {  // set OnePDF-flag, zet alles in zelfde PDF tot reset OnePDF
				OnePdfFlag=true;
				pos+=2;									// 0xD0  0xCD  0xD0 (3 bytes dus)
				while (SPL[pos]!=0xD0) pos++;
			}
			else if (SPL[pos+1]==0xCC) {  // Reset OnePDF-flag, zet vanaf nu alles in aparte PDF's
				OnePdfFlag=false;
				pos+=2;									// 0xD0  0xCC  0xD0 (3 bytes dus)
				while (SPL[pos]!=0xD0) pos++;
			}
      continue;

    }
    if (SPL[pos]>=0xF8 && SPL[pos]<=0xFA) {
      Lade=SPL[pos]-0xF7; // 1, 2 of 3.  
			Page2Lade[PageCnt]=Lade;
    }
    if (SPL[pos]>=0xF0 && SPL[pos]<=0xF7) {
      fnt=SPL[pos]-0xF0;
      if (pos<10) {
        Page2cpi[1]=fnt;
      }
    }
    
    if (SPL[pos]==0x0D) { // count the CR (continous paper feed)
      LinePos+=LineInc;
    }
    if (SPL[pos]==0xE7) { // half forward linefeed 
      LinePos+=(LineInc/2.);
    }
    if (SPL[pos]==0xE8) { // half reverse linefeed
      LinePos-=(LineInc/2.);
    }
#if CONTROL2PDF
    if (SPL[pos]==0x0C || (Ketting2WindowsPrinter && (SPL[pos]==0xD2 || (PrintControl2PDF && LinePos>=Parm[1])))) {   // LinePos>=Parm[1])) { // new page on continous papier or NEW PAGE
#else
    if (SPL[pos]==0x0C || (Ketting2WindowsPrinter && (SPL[pos]==0xD2))) {   // LinePos>=Parm[1])) { // new page on continous papier or NEW PAGE
#endif
	  if (PageCnt >= (sizeof(Page2Pos) / sizeof(long))) {
		break;
	  }
      Page2Pos[++PageCnt]=pos+1;
      Page2cpi[PageCnt]=fnt;
			Page2Lade[PageCnt]=Lade;
      LinePos=0;
    }
  }
  if ((SPLLen-Page2Pos[PageCnt])<5) PageCnt--;
  Page2Pos[PageCnt+1]=SPLLen;

  WinLayoutFlag=false;
  if (SheetFlag) {
    if (bParm[14]==4 && !PrintDocFullLandscape) {                            // windows moet layout doen
      PageW=Parm[0]-Parm[3]-Parm[5];
      PageH=Parm[1]-Parm[4]-Parm[6];
      WinLayoutFlag=true;
      if (PrintDocExtraMarginLeft) {
        if (Parm[3]<236) PageW-=(236-Parm[3]); // neem 2 cm linkermarge
      }
      if (PrintDocExtraMarginOnTop) {
        if (Parm[4]<236) PageH-=(236-Parm[4]); // neem 2 cm bovenmarge  ...
      }
    }
    else if (bParm[14]==4 && PrintDocFullLandscape) {                            // windows moet layout doen : LANDSCAPE MODE
      PageH=Parm[0]-Parm[3]-Parm[5];
      PageW=Parm[1]-Parm[4]-Parm[6];
      WinLayoutFlag=true;
      if (PrintDocExtraMarginLeft) {
        if (Parm[4]<236) PageW-=(236-Parm[4]); // neem 2 cm linkermarge
      }
      if (PrintDocExtraMarginOnTop) {
        if (Parm[3]<236) PageH-=(236-Parm[3]); // neem 2 cm bovenmarge  ...
      }
    }
    else {
      PageW=Parm[0]+Parm[2]-Parm[5];  // verschil parm[2] & parm[3] wordt al gecompenseerd door extra spaties
      PageH=Parm[1]-Parm[6];          // parm[4] wordt al gecompenseerd door extra lijnen
    }
  }
  else {
    PageW=Parm[0];
    PageH=Parm[1];
  }
  
	// Set PDF-flag based on prtnr & prtname

	if (PdfOutputEnabled) {
	  if (PdfPrinterFlag) PdfFlag=true;
	}
	else PdfFlag=false; // is belangrijk om de PdfFlag te resetten die de OVL aangezet heeft met 0xD0 0xCE 0xD0

  return TRUE;
}

void CJmuDoc::InitFnt()
{
  bool bUnderline;
  int nWeight, bItalic, i, j, k, charset;
  float d, dpc, _dpc;
  
  setlocale(LC_ALL,".1252");
  for (j=0; j<4; j++) {
    if (j==0 || j==4) dpc=30.;
    else if (j==1 || j==5) dpc=25.;
    else if (j==2 || j==6) dpc=18.;
    else dpc=30.;
    if (WinLayoutFlag && bParm[18]) {
      d=(float)PageW/bParm[18];
      if (bParm[18]==132) {
        if (d>18.) d=18.;       // om te zorgen dat er meer dan 132 tekens op 1 lijn kunnen !!! zoals vroeger dus.
      }
      dpc=d;
    }
    for (i=0; i<8; i++) {
      if (i&1) nWeight=FW_BOLD; else nWeight=FW_REGULAR;
      if (i&2) bUnderline=true; else bUnderline=false;
      if (i&4) _dpc=2*dpc; else _dpc=dpc;
      if (i&8) bItalic=true; else bItalic=false;

			if (m_FontBold) nWeight+=200;
			if (m_FontItalic) bItalic=true;
 
      if (!WinLayoutFlag) {
        dist[j][i]=(_dpc*78./80.);
      }
      else dist[j][i]=_dpc;

      for (k=0; k<=2; k++) {
        charset=ANSI_CHARSET; 
        if (k==1) charset=OEM_CHARSET;
        else if (k==2) charset=SYMBOL_CHARSET;
        fnt[k][j][i].DeleteObject();
				if (k==1) bItalic=false;
        fnt[k][j][i].CreateFont(Vsc((double)(RES/DocLpi)),Hsc(_dpc),0,0,nWeight,bItalic,bUnderline,0,charset,
             OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,
             0 , m_FontName);
      }
    }
  }
}

int CJmuDoc::Hsc(double in)
{
  return (int)(in*Hscale+.5);
}

int CJmuDoc::Vsc(double in)
{
  return (int)(in*Vscale+.5);
}

static unsigned char jamasci[80][2] = {
{ 225,   0},/* 128 */
{ 224,   0},
{ 226,   0},
{ 228,   0},
{ 231,   0},
{ 233,   0},
{ 232,   0},
{ 234,   0},
{ 235,   0},
{ 237,   0},
{ 236,   0},
{ 238,   0},
{ 239,   0},
{ 243,   0},
{ 242,   0},
{ 244,   0},
{ 246,   0},/* 144 */
{ 250,   0},
{ 249,   0},
{ 251,   0},
{ 252,   0},
{ 220,   0},
{ 176,   0},
{ 167,   0},
{ 190,   1},
{ 126,   1},
{ 126,   1},
{ 126,   1},
{ 126,   1},
{ 126,   1},
{ 126,   1},
{ 128,   0},
{ 126,   1},/* 160 */
{ 126,   1},
{ 126,   1},
{ 126,   1},
{ 126,   1},
{ 126,   1},
{ 126,   1},
{ 126,   1},
{ 126,   1},
{ 126,   1},
{ 126,   1},
{ 126,   1},
{ 126,   1},
{ 126,   1},
{ 126,   1},
{ 126,   1},
{ 178,   1},/* 192 */
{ 186,   1},
{ 205,   1},
{ 200,   1},
{ 186,   1},
{ 186,   1},
{ 201,   1},
{ 204,   1},
{ 205,   1},
{ 188,   1},
{ 205,   1},
{ 202,   1},
{ 187,   1},
{ 185,   1},
{ 203,   1},
{ 206,   1},
{ 178,   1},/* 192 */
{ 179,   1},
{ 196,   1},
{ 192,   1},
{ 179,   1},
{ 179,   1},
{ 218,   1},
{ 195,   1},
{ 196,   1},
{ 217,   1},
{ 196,   1},
{ 193,   1},
{ 191,   1},
{ 180,   1},
{ 194,   1},
{ 197,   1}
};

static int CStringGetInt(CString Text, int *pCmdIx)
{
  int result=0;
  if (*pCmdIx < Text.GetLength()) {
    if (Text.Mid(*pCmdIx,1).CompareNoCase("x")==0 || Text.Mid(*pCmdIx,2).CollateNoCase("0x")==0) {
      char* pEndPtr;
      result = strtoul((LPCTSTR)Text.Mid(*pCmdIx+2),&pEndPtr,16);
    }
    else result = atol((LPCTSTR)Text.Mid(*pCmdIx));
    while (*pCmdIx < Text.GetLength()) {
      (*pCmdIx)++;
      char digit = Text.GetAt(*pCmdIx);
      if (digit==',' || digit==';') {
        (*pCmdIx)++;
        break;
      }
    }
  }
  return result;
}

void CJmuDoc::DrawRect(CDC *pDC, int color, double Xpos, double Ypos, double Xlen, double Ylen)
{
  if (pDC==NULL) { // PDF
    double Red=(double)((color/0x10000)&0xFF)/255.;
    double Green=(double)((color/0x100)&0xFF)/255.;
    double Blue=(double)(color&0xFF)/255.;
    pQP->SetFillColor(Red,Green,Blue);
    pQP->DrawBox(Xpos*Hscale,Ypos*Vscale,Xlen*Hscale,Ylen*Vscale,1);
  }
  else {
    CBrush brush, *oldBrush;
    CPen pen, *oldPen;

    brush.DeleteObject();
    pen.DeleteObject();
    COLORREF c = RGB(((color/0x10000)&0xFF),((color/0x100)&0xFF),(color&0xFF));
    brush.CreateSolidBrush(c);
    pen.CreatePen(PS_SOLID, 1, c);
    oldBrush=pDC->SelectObject(&brush);
    oldPen=pDC->SelectObject(&pen);
    pDC->Rectangle((int)(.5+Xpos*Hscale),(int)(.5+Ypos*Vscale),(int)(.5+(Xpos+Xlen)*Hscale),(int)(.5+(Ypos+Ylen)*Vscale));
    pDC->SelectObject(oldBrush);
    pDC->SelectObject(oldPen);
  
    brush.DeleteObject();
    pen.DeleteObject();
  }
}

#define  DUN    3
#define  DIK    5

void CJmuDoc::ExtraExecute(CDC *pDC,CString ExtraCommand, double Xpos, double Ypos, int cpi)
{
  // [kader:511,6,0,12,7,0,12,0,55,0,72,0,77,0,-80;]|

  int CmdIx=0;
  while (CmdIx<ExtraCommand.GetLength()-3) {

    if (ExtraCommand.Mid(0,7).CompareNoCase("[kader:")==0) {
      CmdIx=7;
      int KaderType = CStringGetInt(ExtraCommand,&CmdIx);
      int KaderColor  = CStringGetInt(ExtraCommand,&CmdIx);
      double KaderYOffset = CStringGetInt(ExtraCommand,&CmdIx);
      KaderYOffset*=(double)(RES/DocLpi);
      double KaderYSize = CStringGetInt(ExtraCommand,&CmdIx);
      KaderYSize*=(double)(RES/DocLpi);
      
      int DikteLinks=0;
      if (KaderType&0x01) DikteLinks=DUN;
      if (KaderType&0x10) DikteLinks=DIK;
      int DikteBoven=0;
      if (KaderType&0x02) DikteBoven=DUN;
      if (KaderType&0x20) DikteBoven=DIK;
      int DikteRechts=0;
      if (KaderType&0x04) DikteRechts=DUN;
      if (KaderType&0x40) DikteRechts=DIK;
      int DikteOnder=0;
      if (KaderType&0x08) DikteOnder=DUN;
      if (KaderType&0x80) DikteOnder=DIK;
      int DikteVertikaal=0;
      if (KaderType&0x100) DikteVertikaal=DUN;
      if (KaderType&0x200) DikteVertikaal=DIK;

      int KaderArcering=-1;
      double PosLeft=-1, PosRight=-1, PosLeftArcering=-1, LijnDikte;
      bool LastVertical=false, FirstVertical=true;
      while (true) {
        double KaderXPos = CStringGetInt(ExtraCommand,&CmdIx);
        LijnDikte = DikteVertikaal;
        if (KaderXPos < 0) {
          KaderXPos=-KaderXPos;
          LastVertical=true;
          LijnDikte=DikteRechts;
        }
        if (FirstVertical) LijnDikte=DikteLinks;
        KaderXPos = Xpos + KaderXPos * dist[cpi][0] - LijnDikte/2;
        
        if (FirstVertical) {
          if (KaderType&0x400) KaderXPos-=dist[cpi][0]/2;
          PosLeft=KaderXPos;
          FirstVertical=false;
        }
        if (LastVertical) {
          if (KaderType&0x400) KaderXPos+=dist[cpi][0]/2;
          PosRight=KaderXPos;
        }
        DrawRect(pDC, KaderColor, KaderXPos, Ypos, LijnDikte, KaderYSize); // dikte van de lijn, in het zwart
        if (PosLeftArcering>=0 && KaderArcering>0) {
          DrawRect(pDC, KaderArcering, PosLeftArcering, Ypos, KaderXPos-PosLeftArcering, KaderYSize); // arceer tov vorige linkse lijn
        }
        if (LastVertical) break;
        PosLeftArcering = KaderXPos+LijnDikte;
        KaderArcering =  CStringGetInt(ExtraCommand,&CmdIx);
      }
      // bovenste en onderste lijn nog afdrukken 
      double _Ypos;
      _Ypos=Ypos+KaderYOffset-DikteBoven/2;
      if (pDC==NULL) _Ypos=Ypos-KaderYOffset+DikteBoven/2;
      DrawRect(pDC, KaderColor, PosLeft, _Ypos, PosRight-PosLeft+(DikteLinks+DikteRechts)/2, DikteBoven); // dikte van de lijn, in het zwart
      _Ypos=Ypos+KaderYOffset+KaderYSize-DikteOnder/2;
      if (pDC==NULL) _Ypos=Ypos-KaderYOffset-KaderYSize+DikteOnder/2;
      DrawRect(pDC, KaderColor, PosLeft, _Ypos, PosRight-PosLeft+(DikteLinks+DikteRechts)/2, DikteOnder); // dikte van de lijn, in het zwart
    }
    while (CmdIx<ExtraCommand.GetLength()) {
      if (ExtraCommand.GetAt(CmdIx)==']') break;
      CmdIx++;
    }
  }
}

bool CJmuDoc::MakeOnePage(CDC *pDC, int pagenr)
{
  unsigned char buf[500], b;
  bool ProcBufFlag;
  int k, digit=0, _dist[300], cpi, _cpi, attrib, _attrib, cs, bufix, sumdist, RepeatCnt, XOff, YOff, ret;
  long pos, pageoff, *pLong;
  double xpos, ypos, xsize;
  CFont f;
  CString filename;

  pDC->SetBkMode(TRANSPARENT);
  pDC->SetTextColor(RGB(0,0,0));

  pageoff=0;
  CString str;
  TRACE("Printing page%3d",pagenr);
  if (BedrukkingFlag[Page2Lade[pagenr]]) {
    filename=BedrukkingFileName[Page2Lade[pagenr]];
    if (GetFileAttributes(filename)!=INVALID_FILE_ATTRIBUTES) {
      ret=ImgLayout.Load(filename);
      TRACE("Load of %1s returned : %4d\n",filename,ret);
      if (ret==0) {
        ret=ImgLayout.Draw(pDC->operator HDC(),Hsc(-PrintOffset.cx),Vsc(-PrintOffset.cy), Hsc(ImgLayout.GetWidth()), Vsc(ImgLayout.GetHeight()));
        TRACE("Draw of %1s returned : %4d\n",filename,ret);
        TRACE("Drawn parm (x,%d,%d,%d,%d)\n",Hsc(-PrintOffset.cx),Vsc(-PrintOffset.cy), Hsc(ImgLayout.GetWidth()), Vsc(ImgLayout.GetHeight()));
        ImgLayout.Destroy();
      }
    }
    else {
      TRACE("FileAttributes invalid for %1s\n",filename);
    }
  }
  
  cpi=Page2cpi[pagenr];
  if (cpi>=4) cpi-=4;
  XOff=0; YOff=0; 
  attrib=0; bufix=0; sumdist=0; RepeatCnt=0;

  if (!SheetFlag) {
    XOff=-Parm[2];
    if(XOff<0) XOff=0;
  }
  else if (WinLayoutFlag) {
    XOff=Parm[3]-PrintOffset.cx;
    YOff=Parm[4]-PrintOffset.cy;
    if (PrintDocExtraMarginLeft && pagenr%2==1) {
      if (Parm[3]<236) XOff+=(236-Parm[3]); // De extra marge moet links komen ...
    }
    if (PrintDocExtraMarginOnTop && pagenr%2==1) {
      if (Parm[4]<236) YOff+=(236-Parm[4]); // De extra marge moet bovenaan komen
    }
  }
  CString strlog;
  TRACE("XOff=%6d   YOff=%6d",XOff,YOff);
  TRACE("  cx=%6d     cy=%6d",PrintOffset.cx,PrintOffset.cy);
  TRACE("P[3]=%6d   P[4]=%6d",Parm[3],Parm[4]);


  xpos=XOff; ypos=YOff; sumdist=Hsc(XOff);

  for (pos=Page2Pos[pagenr]; pos<Page2Pos[pagenr+1]; pos++) {
    if (RepeatCnt<=0) {
      b=SPL[pos];
      if (b==0xEF) {
        b=SPL[pos+1];
        RepeatCnt=SPL[pos+2]-1;
        pos+=2;
      }
    }
    else {
      RepeatCnt--;
      pos--;
    }

    if (BarcodeFlag) {
      if (b==0xD0) {
        // end of barcode
        if (BarcodeLen>1) DrawBarcode(pDC,&xpos,&ypos);
        BarcodeFlag=false;
      }
      else if (BarcodeLen<sizeof(BarcodeBuf)) {
        BarcodeBuf[BarcodeLen++]=b;
      }   
      continue;
    }

    if (b==0x0C) break;
    _attrib=attrib; _cpi=cpi; ProcBufFlag=false; cs=0;
    if (b>=' ' && b<0x80) buf[bufix++]=b;
    if (b>=0x80 && b<0xD0) {
      buf[bufix++]=jamasci[b-0x80][0];
      cs=jamasci[b-0x80][1];
      if (cs>0) bufix--;
    }
    if (b>=0xF0 && b<=0xF7) {
      _cpi=b-0xF0;
      if (_cpi>=4) _cpi-=4;
    }
    else switch (b) {
      case 0x0D:
      case 0xD4:
      case 0xE7:
      case 0xE8:
      case 0xE9:
      case 0xEE:
        ProcBufFlag=true;
        break;
      case 0xD0:
        BarcodeFlag=true;
        BarcodeLen=0;
        ProcBufFlag=true;
        break;
      case 0xE1: _attrib=attrib|1; break;
      case 0xE2: _attrib=attrib&0xFE; break;
      case 0xE3: _attrib=attrib|2; break;
      case 0xE4: _attrib=attrib&0xFD; break;
      case 0xE5: _attrib=attrib|4; break;
      case 0xE6: _attrib=attrib&0xFB; break;
    }

    if (_attrib!=attrib || _cpi!=cpi || cs!=0 || ProcBufFlag) {
      pDC->SelectObject(&fnt[0][cpi][attrib]);
      xsize=0.; 
      for (k=0; k<bufix; k++) {
        xsize+=dist[cpi][attrib];
        _dist[k]=(int)(Hsc(xsize+xpos)-sumdist+.5);
        sumdist+=_dist[k];
      }
      if (bufix>0) {
        pDC->ExtTextOut(Hsc(xpos),Vsc(pageoff+ypos),0,NULL,(const char *)&buf[0],bufix,&_dist[0]);
        xpos+=xsize;
      }
      if (cs>0) {
        buf[0]=buf[bufix];
        pDC->SelectObject(&fnt[cs][cpi][attrib]);
        xsize=dist[cpi][attrib];
        _dist[0]=Hsc(xsize+xpos)-sumdist; //(int)(dist[cpi][attrib]+.5);
        pDC->ExtTextOut(Hsc(xpos),Vsc(pageoff+ypos),0,NULL,(const char *)&buf[0],1,&_dist[0]);
        sumdist+=_dist[0];
				xpos+=xsize;
      }
      attrib=_attrib; cpi=_cpi;
      bufix=0;
    }

    if (b==0xD4) {
      CString ExtCommand;
      while (pos<Page2Pos[pagenr+1]) {
        b=SPL[++pos];
        if (b==0xEF) { // rep-factor
          b=SPL[++pos];
          int cnt=SPL[++pos];
          while (cnt--) ExtCommand+=b;
        }
        else ExtCommand+=b;
        if (b=='|') {
          ExtraExecute(pDC,ExtCommand, xpos, ypos, cpi);
          break;
        }
      }
    }
     
    if (b==0xEE && SPL[pos+1]==1) {
      pLong = (long *)&SPL[pos+2];
      DrawPCL(pDC,&SPL[pos+6],*pLong,&xpos,&ypos);
      pos+=(*pLong+6-1);
      continue;
    }

    switch (b) {
      case 0x0D: xpos=XOff; sumdist=Hsc(XOff); ypos+=(double)(RES/DocLpi); break;
      case 0xE7: ypos+=(double)(RES/(2*DocLpi)); break;
      case 0xE8: ypos-=(double)(RES/(2*DocLpi)); break;
      case 0xE9: xpos=XOff; sumdist=Hsc(XOff); break;
    }
  }

  return true;
}

static unsigned char jama2pcl [128] [2] = {
{ 160,   0},/* 128 */
{ 133,   0},
{ 131,   0},
{ 132,   0},
{ 135,   0},
{ 130,   0},
{ 138,   0},
{ 136,   0},
{ 137,   0},
{ 161,   0},
{ 141,   0},
{ 140,   0},
{ 139,   0},
{ 162,   0},
{ 149,   0},
{ 147,   0},
{ 148,   0},/* 144 */
{ 163,   0},
{ 151,   0},
{ 150,   0},
{ 129,   0},
{ 154,   0},
{ 248,   0},
{  21,   0},
{ 190,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 128,   0},
{ 126,   0},/* 160 */
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 178,   0},/* 192 */
{ 186,   0},
{ 205,   0},
{ 200,   0},
{ 186,   0},
{ 186,   0},
{ 201,   0},
{ 204,   0},
{ 205,   0},
{ 188,   0},
{ 205,   0},
{ 202,   0},
{ 187,   0},
{ 185,   0},
{ 203,   0},
{ 206,   0},
{ 178,   0},/* 192 */
{ 179,   0},
{ 196,   0},
{ 192,   0},
{ 179,   0},
{ 179,   0},
{ 218,   0},
{ 195,   0},
{ 196,   0},
{ 217,   0},
{ 196,   0},
{ 193,   0},
{ 191,   0},
{ 180,   0},
{ 194,   0},
{ 197,   0},
{ 126,   0},/* 208 */
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},/* 224 */
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},/* 240 */
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0}
};

void CJmuDoc::DrawPCL(CDC *pDC,unsigned char *pcl, long len, double *pXpos, double *pYpos)
{
  bool escflag, relativeflag, funderl, eurflag, grafflag;
  unsigned char *s, *s_end, digit;
  CString tekst, PCLFontName;
  int i, j, k, xpos, ypos, d, prop, fsize, fweight, fstyle, ix, nWeight, PCLScale;
  int xsave[10], ysave[10], saveix=0, xlen, ylen, rast, bmcmp, bmhor, bmver, rastoff, rastlen;
  CBrush brush, *oldBrush;
  CPen pen, *oldPen;
  CFont pclfnt, *oldFont;
  CBitmap bm, *oldBitmap;
  BITMAP bmInfo;
  TEXTMETRIC tm;
  CDC dcMemory;
	BYTE nPitchAndFamily;

  PCLFontName=m_PCLFontName; PCLScale=m_PCLScale;
	escflag=false; xpos=(int)(*pXpos+.5); ypos=int(*pYpos+.5);
   
	if (WinLayoutFlag) {
    xpos-=Parm[3];
    ypos-=Parm[4];
  }

  rast=100; prop=1; fsize=12; fweight=0; fstyle=0; funderl=false; grafflag=false;
  s=pcl; s_end=&pcl[len-1]; tekst.Empty();
  while (true) {
    while (escflag) {
      if (*s=='*') {
        s++;
        if (*s=='c') {
         next_c:;
          s++;
          d=strtol((const char *)s,(char **)&s,10);
          if (*s=='a' || *s=='A') xlen=d;
          if (*s=='b' || *s=='B') ylen=d;
          if (*s=='g' || *s=='G') rast=d;
          if (*s=='p' || *s=='P') {
            brush.DeleteObject();
            pen.DeleteObject();
            if (d==0) {
              brush.CreateSolidBrush(RGB(0,0,0));
              pen.CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
            }
            else if (d==2) {
              rast=((100-rast)*255)/100;
              brush.CreateSolidBrush(RGB(rast, rast, rast));
              pen.CreatePen(PS_SOLID, 1, RGB(rast, rast, rast));
            }
            oldBrush=pDC->SelectObject(&brush);
            oldPen=pDC->SelectObject(&pen);
            pDC->Rectangle(Hsc(xpos),Vsc(ypos),Hsc(xpos+xlen),Vsc(ypos+ylen));
            pDC->SelectObject(oldBrush);
            pDC->SelectObject(oldPen);
          }
          if (*s>='a' && *s<='z' && *(s+1)>='0' && *(s+1)<='9') goto next_c;
        }
        else if (*s=='*') {  // pseudo PCL code ESC**
         next_j:;
          s++; d=0;
          d=strtol((const char *)s,(char **)&s,10);
          if (*s=='s' || *s=='S') xlen=d;
          if (*s=='t' || *s=='T') ylen=d;
          if (*s=='w' || *s=='W') {
            if (*s=='W') escflag=false;
            s++;
            if (d>0) {
              CFile TempFile; 
              CString TempFileName=SpoolFilePath+".tmp";
              if (TempFile.Open(TempFileName,CFile::modeCreate|CFile::modeWrite,NULL)) {
                TempFile.Write(s,d);
                TempFile.Close();
                int ret=ImgLayout.Load(TempFileName);
                TRACE("Load of %1s returned : %4d",TempFileName,ret);
                ret=ImgLayout.Draw(pDC->GetSafeHdc(), Hsc(xpos),Vsc(ypos), Hsc(xlen), Vsc(ylen));
                TRACE("Draw of %1s returned : %4d",TempFileName,ret);
                ImgLayout.Destroy();
                _unlink(TempFileName);
                //pPicture->LoadPictureData(s,d);
            	  //pPicture->UpdateSizeOnDC(pDC); // Get Picture Dimentions In Pixels
                //pPicture->Show(pDC, CPoint(Hsc(xpos),Vsc(ypos)), CPoint(Hsc(xlen), Vsc(ylen)), 0,0);
              }
            }
            s+=d;
            continue;
          }
          if (*s>='a' && *s<='z' && *(s+1)>='0' && *(s+1)<='9') goto next_j;
        }
        else if (*s=='p') {  //*p
         next_p:;
          s++;
          if (*s=='-' || *s=='+') relativeflag=true;
          else relativeflag=false;
          d=strtol((const char *)s,(char **)&s,10);
          if (*s=='x' || *s=='X') {
            if (relativeflag) xpos+=d;
            else xpos=d-PrintOffset.cx; // +XOff;
          }
          if (*s=='y' || *s=='Y') {
            if (relativeflag) ypos+=d;
            else ypos=d-PrintOffset.cy; // +YOff;
          }
          if (*s>='a' && *s<='z' && *(s+1)>='0' && *(s+1)<='9') goto next_p;
        }
        else if (*s=='r') { // *r grafics
         next_g:;
          s++;
          d=strtol((const char *)s,(char **)&s,10);
          if (*s=='f' || *s=='F') d=d;
          if (*s=='t' || *s=='T') bmver=d;
          if (*s=='s' || *s=='S') bmhor=((d+15)/16)*16;
          if (*s=='a' || *s=='A') {
            grafflag=true;
            rastoff=-1;
            rastlen=bmhor/8;
            ix=0;
          }
          if (*s=='c' || *s=='C') {
            grafflag=false;
            for (; rastoff<bmver; rastoff++) {
              for (ix=0; ix<rastlen; ix++) {
                image[rastlen*rastoff+ix]=0xFF;
              }
            }
            bm.CreateBitmap(bmhor,bmver,1,1,image);
            bm.GetBitmap(&bmInfo);
            dcMemory.CreateCompatibleDC(pDC);
            oldBitmap=dcMemory.SelectObject(&bm);
            pDC->SetStretchBltMode(BLACKONWHITE);
            pDC->StretchBlt(Hsc(xpos),Vsc(ypos),Hsc(bmhor),Vsc(bmver),&dcMemory,0,0,bmhor,bmver,SRCAND);
            dcMemory.SelectObject(oldBitmap);
            bm.DeleteObject();
          }
          if (*s>='a' && *s<='z' && *(s+1)>='0' && *(s+1)<='9') goto next_g;
        }
        else if (*s=='b') {
         next_rd:;
          s++; d=0;
          d=strtol((const char *)s,(char **)&s,10);
          if (*s=='m' || *s=='M') bmcmp=d;
          if (*s=='w' || *s=='W') {
            if (*s=='W') escflag=false;
            rastoff++; ix=0;
            s++;
            if (bmcmp==2) {
              i=0;
              while (i<d) {
                if (s[i]<128) {
                  for (j=0; j<=s[i]; j++) {
                    image[rastoff*rastlen+ix++]=~s[i+1+j];
                  }
                  i+=(s[i]+2);
                }
                if (s[i]>128) {
                  for (j=0; j<=(256-s[i]); j++) {
                    image[rastoff*rastlen+ix++]=~s[i+1];
                  }
                  i+=2;
                }
                if (s[i]==128) {
                  i++;
                }
              }
              for (; ix<rastlen; ix++) image[rastoff*rastlen+ix]=0xFF;
            }
            else if (bmcmp==3) {
              for (ix=0; ix<rastlen; ix++) {
                image[rastoff*rastlen+ix]=image[(rastoff-1)*rastlen+ix];
              }
            }
            s+=d;
            continue; // *s is niet meer de letter W ! opletten dus ...
          }
          if (*s>='a' && *s<='z' && *(s+1)>='0' && *(s+1)<='9') goto next_rd;
        }
      }
      else if (*s=='&') { // & positioning
        s++;
 			  if (*s=='f') {  // Positioning 
          s++;
          d=strtol((const char*)s,(char **)&s,10);
          if (*s=='s' || *s=='S') {
            if (d==0 && saveix<10) {
              xsave[saveix]=xpos; ysave[saveix++]=ypos;
            }
            else if (d==1 && saveix>0) {
              xpos=xsave[--saveix]; ypos=ysave[saveix];
            }
          }
        }
			  if (*s=='n') {
				  s++;
          d=strtol((const char *)s,(char **)&s,10);
				  if (*s=='W' && *(s+1)=='2') {    // Select font ...
					  if (d==0) {
				 		  PCLFontName=m_PCLFontName;
						  PCLScale=m_PCLScale;
						}
					  else {
						  PCLFontName="";
						  for (i=0; i<d; i++) PCLFontName+=*(s+2+i);
						  if (PCLFontName.CompareNoCase("OCRB10")==0) PCLScale=130;
						}
					}
				  s+=(d+2-1); // -1 omdat er iets verder een s++ staat !
				  escflag=false;
        }
      }
      else if (*s=='(') { // font selection
        s++;
        if (*s=='s') { //(s
         next_s:;
          s++;
          d=strtol((const char *)s,(char **)&s,10);
          if (*s=='p' || *s=='P') prop=d;
          if (*s=='v' || *s=='V') fsize=d;
          if (*s=='s' || *s=='S') fstyle=d;
          if (*s=='b' || *s=='B') fweight=500+d*133;
          if (*s>='a' && *s<='z' && *(s+1)>='0' && *(s+1)<='9') goto next_s;
        }   
      }  
      if (*s>='A' && *s<='Z') escflag=false;
      s++;
    }
 
    if (*s>=' ') {
/*
			digit=*s;
      if (digit>=128) {
        digit=jamasci[digit-128][0];
    		if (digit==0) digit=*s;
			}
			tekst+=digit;
*/

			digit=*s;
      if (digit>=128) {
        for (i=0; i<128; i++) if (jama2pcl[i][0]==digit) break;
				if (i<128) {
          digit=jamasci[i][0];
    			if (digit==0) digit=*s;
        }
			}
			tekst+=digit;
		}

    if (s>=s_end || *s==0x1B) {
      if (tekst.GetLength()>0) {
        pclfnt.DeleteObject();
        eurflag=false;
        if (tekst.GetLength()==1 && tekst.GetAt(0)=='C') {
		      for (k=1; k<48; k++) {
			      if (s[k]=='0' && s[k+1]=='B' && s[k+2]=='=' && s[k+3]==0x1B && s[k+4]=='&' && s[k+5]=='f' && s[k+6]=='1') {
				      tekst="";
							tekst.AppendChar(jama2ansi[159-128]);
							eurflag=true;
					    s=&s[k+3];
						  break;
				    } 
				  }
				}
        nWeight=0;
  			if (m_PCLFontBold) nWeight=200;

        // volgende lijn was /.24 maar m_PCLScale gaat op 100 !
				nPitchAndFamily=FF_ROMAN;
				if (prop) nPitchAndFamily|=VARIABLE_PITCH;
        int ret=pclfnt.CreateFont(Vsc(fsize*PCLScale/24),0,0,0,fweight+nWeight,fstyle|m_PCLFontItalic,funderl,0,ANSI_CHARSET,
          OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY, nPitchAndFamily, PCLFontName);


				oldFont=pDC->SelectObject(&pclfnt);
        CString& rFaceName=CString("");
				pDC->GetTextFace(rFaceName);

        if (PCLFontName.CompareNoCase("ocrb10")==0 && rFaceName.CompareNoCase("ocrb10")) {
					tekst="***GEEN ";
					tekst+=PCLFontName;
					tekst+="***";
				}
				
				pDC->GetTextMetrics(&tm);
				if (m_EurSignSimulation && eurflag) {
					pDC->GetTextExtent("C");
			    pDC->TextOut(Hsc(xpos),Vsc(ypos)-tm.tmExternalLeading-tm.tmAscent,"=");
					CSize csize=pDC->GetTextExtent("=");
			    pDC->TextOut(Hsc(xpos)+csize.cx/4,Vsc(ypos)-tm.tmExternalLeading-tm.tmAscent,"C");
				}
				else {
          pDC->TextOut(Hsc(xpos),Vsc(ypos)-tm.tmExternalLeading-tm.tmAscent,tekst);
				}
				pDC->SelectObject(oldFont);
        tekst.Empty();
      }
      if (*s==0x1B) escflag=true;
    }

    if (s++>=s_end) break;
  }
  brush.DeleteObject();
  pen.DeleteObject();
  pclfnt.DeleteObject();
}

void CJmuDoc::add_image(int bit, int count)
{
  int i;
 
  for (i=0; i<count; i++) {
    if (bit) {
      BarImage[BarImageIx]=true;
    }
    else {
      BarImage[BarImageIx]=false;
    }
    BarImageIx++;
  }
}

void CJmuDoc::msi(int type)
{
  if (type==0) {add_image(1,3); add_image(0,9);}
  else {add_image(1,7); add_image(0,5);}
}

struct {
  int bars;
  int spaces;
} code39[60]= {
 
  0x50,0x80,/* space = 20 H */
  0xFF,0xFF,
  0xFF,0xFF,
  0xFF,0xFF,
  0x00,0xE0,
  0x00,0x70,
  0xFF,0xFF,
  0xFF,0xFF,
  0xFF,0xFF,
  0xFF,0xFF,
  0x30,0x80,
  0x00,0xB0,
  0xFF,0xFF,
  0x18,0x80,
  0x90,0X80,
  0x00,0xD0,
  0x30,0x40,/* 0 */
  0x88,0x40,
  0x48,0x40,
  0xC0,0x40,
  0x28,0x40,
  0xA0,0x40,
  0x60,0x40,
  0x18,0x40,
  0x90,0x40,
  0x50,0x40,/* 9 */
  0xFF,0xFF,
  0xFF,0xFF,
  0xFF,0xFF,
  0xFF,0xFF,
  0xFF,0xFF,
  0xFF,0xFF,
  0xFF,0xFF,/* @ -> 40 H */
  0x88,0x20,
  0x48,0x20,
  0xC0,0x20,
  0x28,0x20,
  0xA0,0x20,
  0x60,0x20,
  0x18,0x20,
  0x90,0x20,
  0x50,0x20,
  0x30,0x20,
  0x88,0x10,
  0x48,0x10,
  0xC0,0x10,
  0x28,0x10,
  0xA0,0x10,
  0x60,0x10,
  0x18,0x10,
  0x90,0x10,
  0x50,0x10,
  0x30,0x10,
  0x88,0x80,
  0x48,0x80,
  0xC0,0x80,
  0x28,0x80,
  0xA0,0x80,
  0x60,0x80
};

void CJmuDoc::prt39(char code)
{
  int j;
  int bars, mask, spaces;
 
  bars=0xFF;
  while (true) {
    if (code>='a' && code<='z') code+='A'-'a';
    if (code>=' ' && code<='Z') {
      bars=code39[code-' '].bars;
      spaces=code39[code-' '].spaces;
    }
    if (bars==0xFF) code=' ';
    else break;
  }
  mask=0x80;
  for (j=0; j<5; j++) {
    if (bars&mask) add_image(1,7); else add_image(1,3);
    add_image(0,1);
    if (spaces&mask) add_image(0,8); else add_image(0,4);
    mask=mask>>1;
  }
}
 
void CJmuDoc::DrawBarcode(CDC *pDC, double *pXpos, double *pYpos)
{
  int i, j, bit, xpos, ypos;
  bool current;
  CBrush brush, *oldBrush;
  CPen pen, *oldPen;

  BarImageIx=0;
  if (BarcodeBuf[0]==1) {
    msi(1);
    for (i=1; i<BarcodeLen; i++) {
      bit = 8;
      for (j=0; j<4; j++) {
	      if (BarcodeBuf[i]&bit) msi(1); else msi(0);
	      bit = bit >> 1;
      }
    }
    msi(0); msi(0);
  }
  else if (BarcodeBuf[0]==2) {
    prt39('*');
    for (i=1; i<BarcodeLen; i++) prt39(BarcodeBuf[i]);
    prt39('*');
  }
  if (!BarImageIx) return;

  brush.DeleteObject();
  pen.DeleteObject();
  brush.CreateSolidBrush(RGB(0,0,0));
  pen.CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
  oldBrush=pDC->SelectObject(&brush);
  oldPen=pDC->SelectObject(&pen);
  
  i=0;
  while (i<BarImageIx) {
    current=BarImage[i];
    for (j=i+1; j<BarImageIx; j++) {
      if (current!=BarImage[j]) break;
    }
    if (current) {
      xpos=(int)(*pXpos+.5)+i; ypos=int(*pYpos+.5); 
      pDC->Rectangle(Hsc(xpos),Vsc(ypos),Hsc(xpos+j-i),Vsc(ypos+25));
    }
    i=j;
  }
  
  pDC->SelectObject(oldBrush);
  pDC->SelectObject(oldPen);

  brush.DeleteObject();
  pen.DeleteObject();
}


////////////////////////////////////////////////////
// nu code uit Doc2Pdf

#define QPUNLOCKKEY "jx5yr3618q56bm7zd8qu5wt4y" // trial key was : "j57g79ru43q3ds5sz5wu5gj7y"
#define TEXTSIZE		12. // grootte letter in POINT (1/72 



bool CJmuDoc::Convert2Pdf(CString SplFilePath, CString PdfFilePath)
{
	int PagNr;
  int i, j;
	double d, dpc;
	char buf[100];
	bool IsNewPdfFlag=false;

	if (pQP==NULL) {
		IsNewPdfFlag=true;
		CString DllFileName = QUICK_PDF_DLL_NAME;
		pQP = new QuickPDFDLL0717((LPCTSTR)DllFileName);

		if (pQP==NULL) return false;

 		if (pQP->UnlockKey(QPUNLOCKKEY)!=1) return false;

		Vscale=Hscale=72./RES;

		pQP->SetInformation(2,(LPCTSTR)DocumentName);
		pQP->SetInformation(6,"Jamadata Server by Jamadata-Pelt");
		pQP->SetInformation(5,"Jamadata PDF-Writer");
		unsigned long _size = sizeof(buf);
		if (GetUserName(buf,&_size)) {
			buf[_size]=0;
			pQP->SetInformation(1,buf);
		}

 		FontID[0]=pQP->AddStandardFont(0);
		FontID[1]=pQP->AddStandardFont(1);
		PclFontID=0;
		pQP->SetTextColor(0,0,0);
		pQP->CompressImages(1);
  }

	for (j=0; j<4; j++) {
		TextSize[j]=TEXTSIZE;
    if (j==2) TextSize[j]=TEXTSIZE-2;
    TextSize[j]*=(6./DocLpi);
		if (j==0) dpc=30.;
		else if (j==1) dpc=25.;
		else if (j==2) dpc=18.;
		else dpc=30.;
		if (WinLayoutFlag && bParm[18]) {
			d=(float)PageW/bParm[18];
			if (bParm[18]==132) {
				if (d>18.) d=18.;       // om te zorgen dat er meer dan 132 tekens op 1 lijn kunnen !!! zoals vroeger dus.
			}
			dpc=d;
		}
		dpc*=(RES)/300;
		if (!WinLayoutFlag) {
			dpc*=(78./80.);
			TextSize[j]*=(78./80.);
		}
		TextHorCompr[j]=(dpc*(72./300)*(1000./600))/TextSize[j];
		for (i=0; i<8; i++) {
			if (i&4) dist[j][i]=dpc*2;
			else dist[j][i]=dpc;
		}
		pQP->SetTextSize(TextSize[j]);			
		TextVertShift[j]=TextSize[j]+pQP->GetTextBound(4);
	}

  for (i=1; i<=3; i++) {
		BedrukkingImageID[i]=0;
		BedrukkingName[i]="";
    if (BedrukkingFlag[i]) {
	   	CString filename=BedrukkingFileName[i];
			for (j=1; j<i; j++) {
			  if (filename==BedrukkingName[j]) {
				  BedrukkingImageID[i]=BedrukkingImageID[j];
					break;
				}
			}
			if (j==i) { // not found
		    if (GetFileAttributes(filename)!=INVALID_FILE_ATTRIBUTES) {
					BedrukkingImageID[i]=pQP->AddImageFromFile((LPCTSTR)filename,0);
					CString cstr;
					if (BedrukkingImageID[i]==0) {
						TRACE("Impossible to AddImageFromFile to PDF : %s (ret=0)",filename);
					}
					else {
						TRACE("Succesfully AddImageFromFile into PDF : %s (ret=%X)",filename,BedrukkingImageID[i]);
					}
					BedrukkingName[i]=filename;
					
				}
			}
		}
	}

	int UsedPageCount = pQP->PageCount();

	if (IsNewPdfFlag) {
  	if (PageCnt>1) pQP->InsertPages(2,PageCnt-1);
		UsedPageCount=0;
	}
	else {
  	if (PageCnt) pQP->InsertPages(UsedPageCount+1,PageCnt);
	}

	for (PagNr=1; PagNr<=PageCnt; PagNr++) {
		pQP->SelectPage(UsedPageCount+PagNr);
		WriteOnePage2Pdf(PagNr);
	}

	if (OnePdfFlag) {
    if (PdfFilePathOnePdf.GetLength()==0) PdfFilePathOnePdf=PdfFilePath;
    return true; // nodig om de file te laten wissen ...
  }
	if (PdfFilePathOnePdf.GetLength()) {
    PdfFilePath=PdfFilePathOnePdf;
    PdfFilePathOnePdf="";
  }
  int PdfWritten = pQP->SaveToFile((LPCTSTR)PdfFilePath);
  delete pQP;
	pQP=NULL;
	if (PdfWritten==1) {	
		// ShellExecute(NULL,"OPEN",PdfFilePath,NULL,NULL,SW_SHOW);
#ifndef JMD_WND_CLASS
		// LogAdd(0,1,"PDF successfully written to",PdfFilePath);
#endif
		return true;
	}
  return false;
}

bool CJmuDoc::WriteOnePage2Pdf(int pagenr)
{
  unsigned char buf[800], b;
  bool ProcBufFlag;
  int digit=0, cpi, _cpi, attrib, _attrib, bufix, RepeatCnt, XOff, YOff, ret;
  long pos, *pLong;
  double xpos, ypos, xsize, PageHeight;
  CFont f;
  CString filename;

  cpi=Page2cpi[pagenr];
  if (cpi>=4) cpi-=4;
  XOff=118; YOff=0; // standaard op 1 cm van linkerrand zetten 
  attrib=0; bufix=0; RepeatCnt=0;


  if (!SheetFlag) {
    XOff=-Parm[2];
    if(XOff<0) XOff=0;
  }
  else if (WinLayoutFlag) {
    XOff=Parm[3];
    YOff=Parm[4];

    if (PrintDocExtraMarginLeft && pagenr%2==1) {
      if (XOff<236) XOff=236;
    }
    if (PrintDocExtraMarginOnTop && pagenr%2==1) {
      if (YOff<236) YOff=236; // De extra marge moet bovenaan komen
    }
  }

	xpos=XOff; ypos=YOff; 

	
  if (PrintDocFullLandscape || Page2Landscape[pagenr]) ret = pQP->SetPageSize("A4 Landscape"); 	
  else ret = pQP->SetPageSize("A4");
	PageHeight = pQP->PageHeight();

	if (BedrukkingFlag[Page2Lade[pagenr]]) {
	  CString cstr;
    ret = pQP->SelectImage(BedrukkingImageID[Page2Lade[pagenr]]);
		TRACE("SelectImage ret=%X",ret);
		ret = pQP->ImageHeight();	
		TRACE("ImageHeight=%d pix",ret);
		ret = pQP->ImageWidth();
		TRACE("ImageWidth=%d pix",ret);
		ret = pQP->DrawImage(0.0,pQP->PageHeight(),pQP->PageWidth(),pQP->PageHeight());
		TRACE("DrawImage ret=%X",ret);
	}

	pQP->SelectFont(FontID[0]);
	pQP->SetTextSize(TextSize[0]);
	pQP->SetFontFlags(1,0,0,0,0,0,0,0);
	pQP->SetTextUnderline(0);
	pQP->SetTextScaling(100*TextHorCompr[cpi]);
	
  for (pos=Page2Pos[pagenr]; pos<Page2Pos[pagenr+1]; pos++) {
    if (RepeatCnt<=0) {
      b=SPL[pos];
      if (b==0xEF) {
        b=SPL[pos+1];
        RepeatCnt=SPL[pos+2]-1;
        pos+=2;
      }
    }
    else {
      RepeatCnt--;
      pos--;
    }

    if (BarcodeFlag) {
      if (b==0xD0) {
				double _ypos = PageHeight/Hscale-ypos;
        if (BarcodeLen>1) DrawBarcode2Pdf(&xpos,&_ypos);
				ypos = PageHeight/Hscale-_ypos;
        BarcodeFlag=false;
      }
      else if (BarcodeLen<sizeof(BarcodeBuf)) {
        BarcodeBuf[BarcodeLen++]=b;
      }   
      continue;
    }

    if (b==0x0C) break;
    _attrib=attrib; _cpi=cpi; ProcBufFlag=false; 
    if (b>=' ' && b<0x80 && bufix<(sizeof(buf)-10)) buf[bufix++]=b;
    if (b>=0x80 && b<0xD0 && bufix<(sizeof(buf)-10)) {
      buf[bufix++]=jamasci[b-0x80][0];
    }
    if (b>=0xF0 && b<=0xF7) {
      _cpi=b-0xF0;
      if (_cpi>=4) _cpi-=4;
    }
    else switch (b) {
      case 0x0D:
      case 0xD4:
      case 0xE7:
      case 0xE8:
      case 0xE9:
      case 0xEE:
        ProcBufFlag=true;
        break;
      case 0xD0:
        BarcodeFlag=true;
        BarcodeLen=0;
        ProcBufFlag=true;
        break;
      case 0xE1: _attrib=attrib|1; break;
      case 0xE2: _attrib=attrib&0xFE; break;
      case 0xE3: _attrib=attrib|2; break;
      case 0xE4: _attrib=attrib&0xFD; break;
      case 0xE5: _attrib=attrib|4; break;
      case 0xE6: _attrib=attrib&0xFB; break;
    }

    if (_attrib!=attrib || _cpi!=cpi || ProcBufFlag) {
      xsize=0.; 
      if (bufix>0) {
				xsize = dist[cpi][attrib] * bufix;
			  buf[bufix]=0;
				pQP->DrawText(DblHsc(xpos),PageHeight-TextVertShift[_cpi]-DblVsc(ypos),(const char *)buf);
        xpos+=xsize;
      }
			if (attrib!=_attrib) {
				pQP->SelectFont(FontID[_attrib&1]);
				pQP->SetTextSize(TextSize[_cpi]);
				pQP->SetFontFlags(1,0,0,0,0,0,0,0);
				if (_attrib&2) pQP->SetTextUnderline(1);
				else pQP->SetTextUnderline(0);
				if (_attrib&4) pQP->SetTextScaling(200*TextHorCompr[_cpi]);
				else pQP->SetTextScaling(100*TextHorCompr[_cpi]);
				attrib=_attrib;
			}
			if (cpi!=_cpi) {
				pQP->SetTextSize(TextSize[_cpi]);
			  pQP->SetTextScaling(100*TextHorCompr[_cpi]);
				cpi=_cpi;
			}
      bufix=0;
    }

    if (b==0xD4) {
      CString ExtCommand;
      while (pos<Page2Pos[pagenr+1]) {
        b=SPL[++pos];
        if (b==0xEF) { // rep-factor
          b=SPL[++pos];
          int cnt=SPL[++pos];
          while (cnt--) ExtCommand+=b;
        }
        else ExtCommand+=b;
        if (b=='|') {
          ExtraExecute(NULL,ExtCommand, xpos, PageHeight/Hscale-ypos, cpi);
          break;
        }
      }
    }
     
    if (b==0xEE && SPL[pos+1]==1) {
      pLong = (long *)&SPL[pos+2];
			double _ypos = PageHeight/Hscale-ypos;
      DrawPCL2Pdf(&SPL[pos+6],*pLong,&xpos,&_ypos);
			ypos = PageHeight/Hscale-_ypos;
      pos+=(*pLong+6-1);

			//Font terug op normaal zetten 
			pQP->SelectFont(FontID[attrib&1]);
			pQP->SetTextSize(TextSize[cpi]);
			pQP->SetFontFlags(1,0,0,0,0,0,0,0);
			if (attrib&2) pQP->SetTextUnderline(1);
			else pQP->SetTextUnderline(0);
			if (attrib&4) pQP->SetTextScaling(200*TextHorCompr[_cpi]);
			else pQP->SetTextScaling(100*TextHorCompr[_cpi]);

      continue;
    }

    switch (b) {
      case 0x0D: xpos=XOff; ypos+=(double)(RES/DocLpi); break;
      case 0xE7: ypos+=(double)(RES/(2*DocLpi)); break;
      case 0xE8: ypos-=(double)(RES/(2*DocLpi)); break;
      case 0xE9: xpos=XOff; break;
    }
  }
	pQP->CompressPage();
  return true;
}

void CJmuDoc::DrawBarcode2Pdf(double *pXpos, double *pYpos)
{
  int i, j, bit, xpos, ypos;
  bool current;

  BarImageIx=0;
  if (BarcodeBuf[0]==1) {
    msi(1);
    for (i=1; i<BarcodeLen; i++) {
      bit = 8;
      for (j=0; j<4; j++) {
	      if (BarcodeBuf[i]&bit) msi(1); else msi(0);
	      bit = bit >> 1;
      }
    }
    msi(0); msi(0);
  }
  else if (BarcodeBuf[0]==2) {
    prt39('*');
    for (i=1; i<BarcodeLen; i++) prt39(BarcodeBuf[i]);
    prt39('*');
  }
  if (!BarImageIx) return;

  i=0;
  while (i<BarImageIx) {
    current=BarImage[i];
    for (j=i+1; j<BarImageIx; j++) {
      if (current!=BarImage[j]) break;
    }
    if (current) {
      xpos=(int)(*pXpos+.5)+i; ypos=int(*pYpos+.5); 
			pQP->DrawBox(DblHsc(xpos),DblVsc(ypos),DblHsc(j-i),DblVsc(25),1);
    }
    i=j;
  }
  
}

void CJmuDoc::DrawPCL2Pdf(unsigned char *pcl, long len, double *pXpos, double *pYpos)
{
  bool escflag, relativeflag, funderl, eurflag, grafflag;
  unsigned char *s, *s_end, digit;
  CString tekst, PCLFontName;
  int i, j, k, d, prop, fsize, fweight, fstyle, ix, PCLScale;
	double xpos, ypos, xsave[10], ysave[10], xlen, ylen, drast;
  int saveix=0, rast, bmcmp, bmhor, bmver, rastoff, rastlen;

  PCLFontName=m_PCLFontName; PCLScale=m_PCLScale;
	escflag=false; xpos=*pXpos; ypos=*pYpos;
	if (PclFontID==0) {
		PclFontID=pQP->AddTrueTypeFont((LPCTSTR)m_PCLFontName,1);
	}
   
  if (WinLayoutFlag) {
    xpos-=Parm[3];
    ypos+=Parm[4];
  }

  rast=100; prop=1; fsize=12; fweight=0; fstyle=0; funderl=false; grafflag=false;
  s=pcl; s_end=&pcl[len-1]; tekst.Empty();
  while (true) {
    while (escflag) {
      if (*s=='*') {
        s++;
        if (*s=='c') {
         next_c:;
          s++;
          d=strtol((const char *)s,(char **)&s,10);
          if (*s=='a' || *s=='A') xlen=d;
          if (*s=='b' || *s=='B') ylen=d;
          if (*s=='g' || *s=='G') rast=d;
          if (*s=='p' || *s=='P') {
						if (d==0) drast=0;
						else if (d==2) {
              drast=(100.-rast)/100.;
            }
						pQP->SetFillColor(drast,drast,drast);
						pQP->DrawBox(DblHsc(xpos),DblVsc(ypos),DblHsc(xlen),DblVsc(ylen),1);
          }
          if (*s>='a' && *s<='z' && *(s+1)>='0' && *(s+1)<='9') goto next_c;
        }
        else if (*s=='*') {  // pseudo PCL code ESC**
         next_j:;
          s++; d=0;
          d=strtol((const char *)s,(char **)&s,10);
          if (*s=='s' || *s=='S') xlen=d;
          if (*s=='t' || *s=='T') ylen=d;
          if (*s=='w' || *s=='W') {
            if (*s=='W') escflag=false;
            s++;
            if (d>0) {
/*
              pPicture = new CPicture;
             	pPicture->LoadPictureData(s,d);
            	pPicture->UpdateSizeOnDC(pDC); // Get Picture Dimentions In Pixels
              pPicture->Show(pDC, CPoint(DblHsc(xpos),DblVsc(ypos)), CPoint(DblHsc(xlen), DblVsc(ylen)), 0,0);
              pPicture->FreePictureData();
//             	m_Picture.Show(pDC, CRect(DblHsc(xpos),DblVsc(ypos),)); // Change Original Dimentions
              delete pPicture;
*/
            }
            s+=d;
            continue;
          }
          if (*s>='a' && *s<='z' && *(s+1)>='0' && *(s+1)<='9') goto next_j;
        }
        else if (*s=='p') {  //*p
         next_p:;
          s++;
          if (*s=='-' || *s=='+') relativeflag=true;
          else relativeflag=false;
          d=strtol((const char *)s,(char **)&s,10);
          if (*s=='x' || *s=='X') {
            if (relativeflag) xpos+=d;
            else xpos=d; // +XOff;
          }
          if (*s=='y' || *s=='Y') {
            if (relativeflag) ypos-=d;
            else ypos=pQP->PageHeight()/Vscale-d; // +YOff;
          }
          if (*s>='a' && *s<='z' && *(s+1)>='0' && *(s+1)<='9') goto next_p;
        }
        else if (*s=='r') { // *r grafics
         next_g:;
          s++;
          d=strtol((const char *)s,(char **)&s,10);
          if (*s=='f' || *s=='F') d=d;
          if (*s=='t' || *s=='T') bmver=d;
          if (*s=='s' || *s=='S') bmhor=((d+15)/16)*16;
          if (*s=='a' || *s=='A') {
            grafflag=true;
            rastoff=-1;
            rastlen=bmhor/8;
            ix=0;
          }
          if (*s=='c' || *s=='C') {
            grafflag=false;
            for (; rastoff<bmver; rastoff++) {
              for (ix=0; ix<rastlen; ix++) {
//                image[rastlen*rastoff+ix]=(char)0xFF;
              }
            }
/*
            bm.CreateBitmap(bmhor,bmver,1,1,image);
            bm.GetBitmap(&bmInfo);
            dcMemory.CreateCompatibleDC(pDC);
            oldBitmap=dcMemory.SelectObject(&bm);
            pDC->SetStretchBltMode(BLACKONWHITE);
            pDC->StretchBlt(DblHsc(xpos),DblVsc(ypos),DblHsc(bmhor),DblVsc(bmver),&dcMemory,0,0,bmhor,bmver,SRCAND);
            dcMemory.SelectObject(oldBitmap);
            bm.DeleteObject();
 */
          }
          if (*s>='a' && *s<='z' && *(s+1)>='0' && *(s+1)<='9') goto next_g;
        }
        else if (*s=='b') {
         next_rd:;
          s++; d=0;
          d=strtol((const char *)s,(char **)&s,10);
          if (*s=='m' || *s=='M') bmcmp=d;
          if (*s=='w' || *s=='W') {
            if (*s=='W') escflag=false;
            rastoff++; ix=0;
            s++;
            if (bmcmp==2) {
              i=0;
              while (i<d) {
                if (s[i]<128) {
                  for (j=0; j<=s[i]; j++) {
//                    image[rastoff*rastlen+ix++]=~s[i+1+j];
                  }
                  i+=(s[i]+2);
                }
                if (s[i]>128) {
                  for (j=0; j<=(256-s[i]); j++) {
//                    image[rastoff*rastlen+ix++]=~s[i+1];
                  }
                  i+=2;
                }
                if (s[i]==128) {
                  i++;
                }
              }
//              for (; ix<rastlen; ix++) image[rastoff*rastlen+ix]=(char)0xFF;
            }
            else if (bmcmp==3) {
              for (ix=0; ix<rastlen; ix++) {
//                image[rastoff*rastlen+ix]=image[(rastoff-1)*rastlen+ix];
              }
            }
            s+=d;
            continue; // *s is niet meer de letter W ! opletten dus ...
          }
          if (*s>='a' && *s<='z' && *(s+1)>='0' && *(s+1)<='9') goto next_rd;
        }
      }
      else if (*s=='&') { // & positioning
        s++;
 			  if (*s=='f') {  // Positioning 
          s++;
          d=strtol((const char*)s,(char **)&s,10);
          if (*s=='s' || *s=='S') {
            if (d==0 && saveix<10) {
              xsave[saveix]=xpos; ysave[saveix++]=ypos;
            }
            else if (d==1 && saveix>0) {
              xpos=xsave[--saveix]; ypos=ysave[saveix];
            }
          }
        }
			  if (*s=='n') {
				  s++;
          d=strtol((const char *)s,(char **)&s,10);
				  if (*s=='W' && *(s+1)=='2') {    // Select font ...
					  if (d==0) {
				 		  PCLFontName=m_PCLFontName;
						  PCLScale=m_PCLScale;
						}
					  else {
						  PCLFontName="";
						  for (i=0; i<d; i++) PCLFontName+=*(s+2+i);
						  if (PCLFontName.CompareNoCase("OCRB10")==0) PCLScale=130;
						}
					}
				  s+=(d+2-1); // -1 omdat er iets verder een s++ staat !
				  escflag=false;
        }
      }
      else if (*s=='(') { // font selection
        s++;
        if (*s=='s') { //(s
         next_s:;
          s++;
          d=strtol((const char *)s,(char **)&s,10);
          if (*s=='p' || *s=='P') prop=d;
          if (*s=='v' || *s=='V') fsize=d;
          if (*s=='s' || *s=='S') fstyle=d;
          if (*s=='b' || *s=='B') fweight=500+d*133;
          if (*s>='a' && *s<='z' && *(s+1)>='0' && *(s+1)<='9') goto next_s;
        }   
      }  
      if (*s>='A' && *s<='Z') escflag=false;
      s++;
    }
 
    if (*s>=' ') {

			digit=*s;
      if (digit>=128) {
        for (i=0; i<128; i++) if (jama2pcl[i][0]==digit) break;
				if (i<128) {
          digit=jamasci[i][0];
    			if (digit==0) digit=*s;
        }
			}
			tekst+=digit;
		}

    if (s>=s_end || *s==0x1B) {
      if (tekst.GetLength()>0) {
        eurflag=false;
        if (tekst.GetLength()==1 && tekst.GetAt(0)=='C') {
		      for (k=1; k<48; k++) {
			      if (s[k]=='0' && s[k+1]=='B' && s[k+2]=='=' && s[k+3]==0x1B && s[k+4]=='&' && s[k+5]=='f' && s[k+6]=='1') {
				      tekst="";
							tekst.AppendChar(jama2ansi[159-128]);
							eurflag=true;
					    s=&s[k+3];
						  break;
				    } 
				  }
				}
        
  			CString PDFFontName = PCLFontName;
				if (fweight>700 || m_PCLFontBold) {
				  if (m_PCLFontItalic) PDFFontName+=" [BoldItalic]";
					else PDFFontName+=" [Bold]";
				}
				else if (m_PCLFontItalic) PDFFontName+=" [Italic]";

				int _ID=pQP->AddTrueTypeFont((LPCTSTR)PDFFontName,0);
				pQP->SelectFont(_ID);
				if (!prop) pQP->SetFontFlags(1,0,0,0,0,0,0,0);
				double TextSizePoints = fsize*.9*PCLScale/100.;
				pQP->SetTextSize(TextSizePoints);
				pQP->SetTextScaling(100);
				pQP->DrawText(DblHsc(xpos),DblVsc(ypos)/*-TextSizePoints+pQP->GetTextDescent()*/,(LPCTSTR)tekst);
        tekst.Empty();
      }
      if (*s==0x1B) escflag=true;
    }

    if (s++>=s_end) break;
  }
}


////////////////////////////////////////////////
// Matrix Drivers
// code from MatrixPrinters uit JMU

void CJmuDoc::Matrix_SelectDriver(int nr)
{
  PrinterDriver=nr;

// 0 -> simple

char simple_prtoutt [128] [2] = {
{  97,   0},/* 128 */
{  64,   0},
{  97,   0},
{  97,   0},
{  92,   0},
{ 123,   0},
{ 125,   0},
{ 101,   0},
{ 101,   0},
{ 105,   0},
{ 105,   0},
{ 105,   0},
{ 105,   0},
{ 111,   0},
{ 111,   0},
{ 111,   0},
{ 111,   0},/* 144 */
{ 117,   0},
{ 124,   0},
{ 117,   0},
{ 117,   0},
{  85,   0},
{  91,   0},
{  93,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0}, /* 160 */
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ '@',   0}, /* 176 */
{ '|',   0},
{ '-',   0},
{ '+',   0},
{ '|',   0},
{ '|',   0},
{ '+',   0},
{ '+',   0},
{ '-',   0},
{ '+',   0},
{ '-',   0},
{ '+',   0},
{ '+',   0},
{ '+',   0},
{ '+',   0},
{ '+',   0},
{ '@',   0},/* 192 */
{ '|',   0},
{ '-',   0},
{ '+',   0},
{ '|',   0},
{ '|',   0},
{ '+',   0},
{ '+',   0},
{ '-',   0},
{ '+',   0},
{ '-',   0},
{ '+',   0},
{ '+',   0},
{ '+',   0},
{ '+',   0},
{ '+',   0},
{ 126,   0}, /* 208 */
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0}, /* 224 */
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0}, /* 240 */
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0}
};

cut_delay = -1;
cut_act = "";

//1 iprta
char iprta_prt39[4][21] = {
  {4, 63, 63, 63, 63},/* print narrow bar */
  {8, 63, 63, 63, 63, 63, 63, 63, 63},/* print wide   bar */
  {4,  0,  0,  0},                                    /* print narrow space */
  {8,  0,  0,  0,  0,  0,  0}                           /* print wide space */
};
									
char *iprta_prtactt [] = {
  "",
/* 6 lpi, und, enh, enp off */
/* cancel sub/superscript */
  "\x1B\x47",/* boldface on */
  "\x1B\x48",/* off */
  "\x1B\x2D\x01",/* underline on */
  "\x1B\x2D\xFF",/* off */
  "",/* elongated on */
  "",/* off */
  "\x1BJ\x12",
/* exec half forward line feed */
  "",/* Exec half reverse line feed */
  "\x0D"/* carriage return, no linefeed */
};
 
struct {
  char *progseq;        /* to send to printer to select the pitch */
  int  cincr;           /* increment for one character for active pitch */
  int  bscode[2];       /* to send after backspace char */
} iprta_prtcpit[8] = {
 
    "\x12\x1BI\xFF" ,30, 0, 0,/* 10 pitch */
    "\x1B:\x1BI\xFF",25, 0, 0,/* 12 pitch */
    "\x12\x0F\x1BI\xFF" ,18, 0, 0,/* 16.7 pitch */
    ""              , 0, 0, 0,/* PS pitch */
    "\x12\x1BI\x02" ,30, 0, 0,/* see above */
    "\x1B:\x1BI\x02",25, 0, 0,
    "\x12\x0F\x1BI\x02" ,18, 0, 0,/* identical to dataprocessing mode */
    ""              , 0, 0, 0
};
 
char iprta_prtspec [2][21] = {
  {12, 63, 63, 63, 63,  0,  0,  0,  0,  0,  0,  0,  0},/* narrow bar */
  {12, 63, 63, 63, 63, 63, 63, 63, 63,  0,  0,  0,  0}/* wide bar */
};

unsigned char iprta_prtoutt [128] [2] = {
{ 160,   0},  /* 128 */
{ 133,   0},
{ 131,   0},
{ 132,   0},
{ 135,   0},
{ 130,   0},
{ 138,   0},
{ 136,   0},
{ 137,   0},
{ 161,   0},
{ 141,   0},
{ 140,   0},
{ 139,   0},
{ 162,   0},
{ 149,   0},
{ 147,   0},
{ 148,   0}, /* 144 */
{ 163,   0},
{ 151,   0},
{ 150,   0},
{ 129,   0},
{ 154,   0},
{ 248,   0},
{  21,   0},
{ 190,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0}, /* 160 */
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 178,   0},/* 176 */
{ 186,   0},
{ 205,   0},
{ 200,   0},
{ 186,   0},
{ 186,   0},
{ 201,   0},
{ 204,   0},
{ 205,   0},
{ 188,   0},
{ 205,   0},
{ 202,   0},
{ 187,   0},
{ 185,   0},
{ 203,   0},
{ 206,   0},
{ 178,   0},/* 192 */
{ 179,   0},
{ 196,   0},
{ 192,   0},
{ 179,   0},
{ 179,   0},
{ 218,   0},
{ 195,   0},
{ 196,   0},
{ 217,   0},
{ 196,   0},
{ 193,   0},
{ 191,   0},
{ 180,   0},
{ 194,   0},
{ 197,   0},
{ 126,   0}, /* 208 */
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0}, /* 224 */
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0}, /* 240 */
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0}
};

// 2 -> iprtb
unsigned char iprtb_prt39[4][21] = {
  {4,255,255,255,255},/* print narrow bar */
  {8,255,255,255,255,255,255,255,255},/* print wide   bar */
  {4,  0,  0,  0},                                    /* print narrow space */
  {8,  0,  0,  0,  0,  0,  0}                           /* print wide space */
};
									
char *iprtb_prtactt [] = {
  "",
  "\x1B\x45",/* boldface on */
  "\x1B\x46",/* off */
  "\x1B\x2D\x01",/* underline on */
  "\x1B\x2D\xFF",/* off */
  "\x1BW\x01",/* elongated on */
  "\x1BW\xFF",/* off */
  "\x1BJ\x18",
/* exec half forward line feed */
  "",/* Exec half reverse line feed */
  "\x0D"/* carriage return, no linefeed */
};
 
struct {
  char *progseq;        /* to send to printer to select the pitch */
  int  cincr;           /* increment for one character for active pitch */
  int  bscode[2];       /* to send after backspace char */
} iprtb_prtcpit[8] = {
 
    "\x12" ,30, 0, 0,/* 10 pitch */
    "\x0F" ,18, 0, 0,/* 16.7 pitch */
    ""     , 0, 0, 0,
    ""     , 0, 0, 0,
    "\x12\x1B\x47" ,30, 0, 0,/* see above */
    "\x0F"         ,18, 0, 0,
    ""             , 0, 0, 0,/* identical to dataprocessing mode */
    ""             , 0, 0, 0
};
 
unsigned char iprtb_prtspec [2][21] = {
  {12,255,255,255,255,  0,  0,  0,  0,  0,  0,  0,  0},/* narrow bar */
  {12,255,255,255,255,255,255,255,255,  0,  0,  0,  0}/* wide bar */
};

unsigned char iprtb_prtoutt [128] [2] = {
{ 160,   0},  /* 128 */
{ 133,   0},
{ 131,   0},
{ 132,   0},
{ 135,   0},
{ 130,   0},
{ 138,   0},
{ 136,   0},
{ 137,   0},
{ 161,   0},
{ 141,   0},
{ 140,   0},
{ 139,   0},
{ 162,   0},
{ 149,   0},
{ 147,   0},
{ 148,   0}, /* 144 */
{ 163,   0},
{ 151,   0},
{ 150,   0},
{ 129,   0},
{ 154,   0},
{ 248,   0},
{  21,   0},
{ 190,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0}, /* 160 */
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 178,   0},/* 176 */
{ 186,   0},
{ 205,   0},
{ 200,   0},
{ 186,   0},
{ 186,   0},
{ 201,   0},
{ 204,   0},
{ 205,   0},
{ 188,   0},
{ 205,   0},
{ 202,   0},
{ 187,   0},
{ 185,   0},
{ 203,   0},
{ 206,   0},
{ 178,   0},/* 192 */
{ 179,   0},
{ 196,   0},
{ 192,   0},
{ 179,   0},
{ 179,   0},
{ 218,   0},
{ 195,   0},
{ 196,   0},
{ 217,   0},
{ 196,   0},
{ 193,   0},
{ 191,   0},
{ 180,   0},
{ 194,   0},
{ 197,   0},
{ 126,   0}, /* 208 */
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0}, /* 224 */
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0}, /* 240 */
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0}
};


// 3 -> iprtc
char iprtc_prt39[4][21] = {
  {4, 63, 63, 63, 63},/* print narrow bar */
  {8, 63, 63, 63, 63, 63, 63, 63, 63},/* print wide   bar */
  {4,  0,  0,  0},/* print narrow space */
  {8,  0,  0,  0,  0,  0,  0}/* print wide space */
};
char* iprtc_prtactt [] = {
  "",
  "\x1B\x47",/* boldface on */
  "\x1B\x48",/* off */
  "\x1B\x2D\x01",/* underline on */
  "\x1B\x2D\xFF",/* off */
  "\x1BW\x01",/* elongated on */
  "\x1BW\xFF",/* off */
  "\x1BJ\x12",
  /* exec half forward line feed */
  "",/* Exec half reverse line feed */
  "\x0D"/* carriage return, no linefeed */
};
struct {
  char *progseq;        /* to send to printer to select the pitch */
  int  cincr;           /* increment for one character for active pitch */
  int  bscode[2];       /* to send after backspace char */
} iprtc_prtcpit[8] = {
 
    "\x12\x1BI\xFF" ,30, 0, 0,/* 10 pitch */
    "\x1B:\x1BI\xFF",25, 0, 0,/* 12 pitch */
    "\x12\x0F\x1BI\xFF" ,18, 0, 0,/* 16.7 pitch */
    ""              , 0, 0, 0,/* PS pitch */
    "\x12\x1BI\x02" ,30, 0, 0,/* see above */
    "\x1B:\x1BI\x02",25, 0, 0,
    "\x12\x0F\x1BI\x02" ,18, 0, 0,/* identical to dataprocessing mode */
    ""              , 0, 0, 0
};
char iprtc_prtspec [2][21] = {
  {12, 63, 63, 63, 63,  0,  0,  0,  0,  0,  0,  0,  0},/* narrow bar */
  {12, 63, 63, 63, 63, 63, 63, 63, 63,  0,  0,  0,  0}/* wide bar */
};
unsigned char iprtc_prtoutt [128] [2] = {
{ 160,   0},  /* 128 */
{ 133,   0},
{ 131,   0},
{ 132,   0},
{ 135,   0},
{ 130,   0},
{ 138,   0},
{ 136,   0},
{ 137,   0},
{ 161,   0},
{ 141,   0},
{ 140,   0},
{ 139,   0},
{ 162,   0},
{ 149,   0},
{ 147,   0},
{ 148,   0}, /* 144 */
{ 163,   0},
{ 151,   0},
{ 150,   0},
{ 129,   0},
{ 154,   0},
{ 248,   0},
{  21,   0},
{ 190,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0}, /* 160 */
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 178,   0},/* 176 */
{ 186,   0},
{ 205,   0},
{ 200,   0},
{ 186,   0},
{ 186,   0},
{ 201,   0},
{ 204,   0},
{ 205,   0},
{ 188,   0},
{ 205,   0},
{ 202,   0},
{ 187,   0},
{ 185,   0},
{ 203,   0},
{ 206,   0},
{ 178,   0},/* 192 */
{ 179,   0},
{ 196,   0},
{ 192,   0},
{ 179,   0},
{ 179,   0},
{ 218,   0},
{ 195,   0},
{ 196,   0},
{ 217,   0},
{ 196,   0},
{ 193,   0},
{ 191,   0},
{ 180,   0},
{ 194,   0},
{ 197,   0},
{ 126,   0}, /* 208 */
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0}, /* 224 */
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0}, /* 240 */
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0}
};


//4 iprtd
char iprtd_prt39[4][21] = {
  {4, 63, 63, 63, 63},/* print narrow bar */
  {8, 63, 63, 63, 63, 63, 63, 63, 63},/* print wide   bar */
  {4,  0,  0,  0},                                    /* print narrow space */
  {8,  0,  0,  0,  0,  0,  0}                           /* print wide space */
};
									
char *iprtd_prtactt [] = {
  "",
/* 6 lpi, und, enh, enp off */
/* cancel sub/superscript */
  "\x1B\x47",/* boldface on */
  "\x1B\x48",/* off */
  "\x1B\x2D\x01",/* underline on */
  "\x1B\x2D\xFF",/* off */
  "\x1BW\x01",/* elongated on */
  "\x1BW\xFF",/* off */
  "\x1BJ\x12",
/* exec half forward line feed */
  "",/* Exec half reverse line feed */
  "\x0D"/* carriage return, no linefeed */
};
 
struct {
  char *progseq;        /* to send to printer to select the pitch */
  int  cincr;           /* increment for one character for active pitch */
  int  bscode[2];       /* to send after backspace char */
} iprtd_prtcpit[8] = {
 
    "\x1BI\xFF" ,30, 0, 0,/* 10 pitch */
    "\x1BI\x08",25, 0, 0,/* 12 pitch */
    "\x1BI\x10" ,18, 0, 0,/* 16.7 pitch */
    ""              , 0, 0, 0,/* PS pitch */
    "\x1BI\x02" ,30, 0, 0,/* see above */
    "\x1BI\x0A",25, 0, 0,
    "\x1BI\x12" ,18, 0, 0,/* identical to dataprocessing mode */
    "\x1BI\x03" , 0, 0, 0
};
 
char iprtd_prtspec [2][21] = {
  {12, 63, 63, 63, 63,  0,  0,  0,  0,  0,  0,  0,  0},/* narrow bar */
  {12, 63, 63, 63, 63, 63, 63, 63, 63,  0,  0,  0,  0}/* wide bar */
};

unsigned char iprtd_prtoutt [128] [2] = {
{ 160,   0},  /* 128 */
{ 133,   0},
{ 131,   0},
{ 132,   0},
{ 135,   0},
{ 130,   0},
{ 138,   0},
{ 136,   0},
{ 137,   0},
{ 161,   0},
{ 141,   0},
{ 140,   0},
{ 139,   0},
{ 162,   0},
{ 149,   0},
{ 147,   0},
{ 148,   0}, /* 144 */
{ 163,   0},
{ 151,   0},
{ 150,   0},
{ 129,   0},
{ 154,   0},
{ 248,   0},
{  21,   0},
{ 190,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0}, /* 160 */
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 178,   0},/* 176 */
{ 186,   0},
{ 205,   0},
{ 200,   0},
{ 186,   0},
{ 186,   0},
{ 201,   0},
{ 204,   0},
{ 205,   0},
{ 188,   0},
{ 205,   0},
{ 202,   0},
{ 187,   0},
{ 185,   0},
{ 203,   0},
{ 206,   0},
{ 178,   0},/* 192 */
{ 179,   0},
{ 196,   0},
{ 192,   0},
{ 179,   0},
{ 179,   0},
{ 218,   0},
{ 195,   0},
{ 196,   0},
{ 217,   0},
{ 196,   0},
{ 193,   0},
{ 191,   0},
{ 180,   0},
{ 194,   0},
{ 197,   0},
{ 126,   0}, /* 208 */
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0}, /* 224 */
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0}, /* 240 */
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0}
};

//5 EPSON FX
char *epsonfx_prtactt [] = {
  "\x1B\x46\x1B\x48\x1B\x36",
  "",/* \x1B\x45", */                                       /* boldface on */
  "",/* \x1B\x46", */                                               /* off */
  "\x1B\x2D\x31",/* underline on */
  "\x1B\x2D\x30",/* off */
  "\x1BW1",/* elongated on */
  "\x1BW0",/* off */
  "\x1BJ\x12",/* exec half forward line feed */
  "\x1Bj\x12",/* Exec half reverse line feed */
  "\x0D"/* carriage return, no linefeed */
};
 
struct {
  char *progseq;        /* to send to printer to select the pitch */
  int  cincr;           /* increment for one character for active pitch */
  int  bscode[2];       /* to send after backspace char */
} epsonfx_prtcpit[8] = {
 
    "\x12\x1BP\x1Bx0" ,30, 0, 0,/* 10 pitch */
    "\x12\x1BM\x1Bx0" ,25, 0, 0,/* 12 pitch */
    "\x0F\x1Bx0"      ,18, 0, 0,/* 16 pitch */
    ""                , 0, 0, 0,
    "\x12\x1BP\x1Bx1" ,30, 0, 0,/* see above */
    "\x12\x1BM\x1Bx1" ,25, 0, 0,
    "\x0F\x1Bx0"      ,18, 0, 0,/* identical to dataprocessing mode */
    ""                , 0, 0, 0
};
 
unsigned char epsonfx_prtspec [2][21] = {
 
    {6,255,  0,  0,  0,  0,  0},/* print narrow bar */
    {6,255,255,255,255,  0,  0}/* print wide   bar */
};

unsigned char epsonfx_prtoutt [128] [2] = {
{ 160,   0},  /* 128 */
{ 133,   0},
{ 131,   0},
{ 132,   0},
{ 135,   0},
{ 130,   0},
{ 138,   0},
{ 136,   0},
{ 137,   0},
{ 161,   0},
{ 141,   0},
{ 140,   0},
{ 139,   0},
{ 162,   0},
{ 149,   0},
{ 147,   0},
{ 148,   0}, /* 144 */
{ 163,   0},
{ 151,   0},
{ 150,   0},
{ 129,   0},
{ 154,   0},
{ 248,   0},
{  21,   0},
{ 190,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0}, /* 160 */
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 178,   0},/* 176 */
{ 186,   0},
{ 205,   0},
{ 200,   0},
{ 186,   0},
{ 186,   0},
{ 201,   0},
{ 204,   0},
{ 205,   0},
{ 188,   0},
{ 205,   0},
{ 202,   0},
{ 187,   0},
{ 185,   0},
{ 203,   0},
{ 206,   0},
{ 178,   0},/* 192 */
{ 179,   0},
{ 196,   0},
{ 192,   0},
{ 179,   0},
{ 179,   0},
{ 218,   0},
{ 195,   0},
{ 196,   0},
{ 217,   0},
{ 196,   0},
{ 193,   0},
{ 191,   0},
{ 180,   0},
{ 194,   0},
{ 197,   0},
{ 126,   0}, /* 208 */
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0}, /* 224 */
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0}, /* 240 */
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0}
};

// 6 star10

char *star10_prtactt [] = {
  "\x1B\x46\x1B\x48\x1B\x36",
  "\x1B\x45",/* boldface on */
  "\x1B\x46",/* off */
  "\x1B\x2D\x31",/* underline on */
  "\x1B\x2D\x30",/* off */
  "\x1BW1",/* elongated on */
  "\x1BW0",/* off */
  "\x1BJ\x12",/* exec half forward line feed */
  "\x1Bj\x12",/* Exec half reverse line feed */
  "\x0D"/* carriage return, no linefeed */
};
 
struct {
  char *progseq;        /* to send to printer to select the pitch */
  int  cincr;           /* increment for one character for active pitch */
  int  bscode[2];       /* to send after backspace char */
} star10_prtcpit[8] = {
 
    "\x12\x1BP\x1Bx0" ,30, 0, 0,/* 10 pitch */
    "\x12\x1BM\x1Bx0" ,25, 0, 0,/* 12 pitch */
    "\x0F\x1Bx0"      ,18, 0, 0,/* 16 pitch */
    ""                , 0, 0, 0,
    "\x12\x1BP\x1Bx1" ,30, 0, 0,/* see above */
    "\x12\x1BM\x1Bx1" ,25, 0, 0,
    "\x0F\x1Bx1"      ,18, 0, 0,/* identical to dataprocessing mode */
    ""                , 0, 0, 0
};
 
unsigned char star10_prtspec [2][21] = {
 
    {6,255,  0,  0,  0,  0,  0},/* print narrow bar */
    {6,255,255,255,255,  0,  0}/* print wide   bar */
};

unsigned char star10_prtoutt [128] [2] = {
{ 160,   0},  /* 128 */
{ 133,   0},
{ 131,   0},
{ 132,   0},
{ 135,   0},
{ 130,   0},
{ 138,   0},
{ 136,   0},
{ 137,   0},
{ 161,   0},
{ 141,   0},
{ 140,   0},
{ 139,   0},
{ 162,   0},
{ 149,   0},
{ 147,   0},
{ 148,   0}, /* 144 */
{ 163,   0},
{ 151,   0},
{ 150,   0},
{ 129,   0},
{ 154,   0},
{ 248,   0},
{  21,   0},
{ 190,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0}, /* 160 */
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 178,   0},/* 176 */
{ 186,   0},
{ 205,   0},
{ 200,   0},
{ 186,   0},
{ 186,   0},
{ 201,   0},
{ 204,   0},
{ 205,   0},
{ 188,   0},
{ 205,   0},
{ 202,   0},
{ 187,   0},
{ 185,   0},
{ 203,   0},
{ 206,   0},
{ 178,   0},/* 192 */
{ 179,   0},
{ 196,   0},
{ 192,   0},
{ 179,   0},
{ 179,   0},
{ 218,   0},
{ 195,   0},
{ 196,   0},
{ 217,   0},
{ 196,   0},
{ 193,   0},
{ 191,   0},
{ 180,   0},
{ 194,   0},
{ 197,   0},
{ 126,   0}, /* 208 */
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0}, /* 224 */
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0}, /* 240 */
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0}
};

// 7 : nec_pxx

unsigned char nec_pxx_prt39[4][21] = {
  {9,255,255,  0,255,255,  0,  0,  0,  0},/* print narrow bar */
  {18,255,255,  0,255,255,  0,255,255,  0,255,255,  0,255,255,  0,  0,  0,  0},/* print wide   bar */
  {9,0,0,0,0,0,0},/* print narrow space */
  {18,0,0,0,0,0,0,0,0,0,0,0,0}/* print wide space */
};
 
char *nec_pxx_prtactt [] = {
  "\x1Bt1\x1BR0\x11",
  "\x1B\x47",/* boldface on */
  "\x1B\x48",/* off */
  "\x1B\x2D\x01",/* underline on */
  "\x1B\x2D\xFF",/* off */
  "\x1BW\x01",/* elongated on */
  "\x1BW\xFF",/* off */
  "\x1BJ\x0F",/* exec half forward line feed */
  "\x1Bj\x0F",/* Exec half reverse line feed */
  "\x0D"/* carriage return, no linefeed */
};
 
struct {
  char *progseq;        /* to send to printer to select the pitch */
  int  cincr;           /* increment for one character for active pitch */
  int  bscode[2];       /* to send after backspace char */
} nec_pxx_prtcpit[8] = {
 
    "\x12\x1BP\x1Bx0" ,30, 0, 0,/* 10 pitch */
    "\x12\x1BM\x1Bx0",25, 0, 0,/* 12 pitch */
    "\x12\x1BP\x1Bx0\x0F" ,18, 0, 0,/* 16.7 pitch */
    ""              , 0, 0, 0,/* PS pitch */
    "\x12\x1BP\x1Bx1" ,30, 0, 0,/* see above */
    "\x12\x1BM\x1Bx1",25, 0, 0,
    "\x12\x1BP\x1Bx1\x0F" ,18, 0, 0,/* identical to dataprocessing mode */
    ""              , 0, 0, 0
};
 
unsigned char nec_pxx_prtspec [2][21] = {
 
    {18,255,255,255,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},/* print narrow bar */
    {18,255,255,255,255,255,255,255,255,255,  0,  0,  0,0,0,0,0,0,0}/* print wide   bar */
};

unsigned char nec_pxx_prtoutt [128] [2] = {
{ 160,   0},  /* 128 */
{ 133,   0},
{ 131,   0},
{ 132,   0},
{ 135,   0},
{ 130,   0},
{ 138,   0},
{ 136,   0},
{ 137,   0},
{ 161,   0},
{ 141,   0},
{ 140,   0},
{ 139,   0},
{ 162,   0},
{ 149,   0},
{ 147,   0},
{ 148,   0}, /* 144 */
{ 163,   0},
{ 151,   0},
{ 150,   0},
{ 129,   0},
{ 154,   0},
{ 248,   0},
{  21,   0},
{ 190,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0}, /* 160 */
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 178,   0},/* 176 */
{ 186,   0},
{ 205,   0},
{ 200,   0},
{ 186,   0},
{ 186,   0},
{ 201,   0},
{ 204,   0},
{ 205,   0},
{ 188,   0},
{ 205,   0},
{ 202,   0},
{ 187,   0},
{ 185,   0},
{ 203,   0},
{ 206,   0},
{ 178,   0},/* 192 */
{ 179,   0},
{ 196,   0},
{ 192,   0},
{ 179,   0},
{ 179,   0},
{ 218,   0},
{ 195,   0},
{ 196,   0},
{ 217,   0},
{ 196,   0},
{ 193,   0},
{ 191,   0},
{ 180,   0},
{ 194,   0},
{ 197,   0},
{ 126,   0}, /* 208 */
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0}, /* 224 */
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0}, /* 240 */
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0}
};

// 10 720

char *cbm720_prtactt [] = {
  "\x1B@",
  "\x13",/* boldface on */
  "",/* off */
  "\x1B\x2D\x01",/* underline on */
  "\x1B\x2D\xFF",/* off */
  "\x0E",/* elongated on */
  "\x0F",/* off */
  "",
/* exec half forward line feed */
  "",/* Exec half reverse line feed */
  "\x0D"/* carriage return, no linefeed */
};
 
struct {
  char *progseq;        /* to send to printer to select the pitch */
  int  cincr;           /* increment for one character for active pitch */
  int  bscode[2];       /* to send after backspace char */
} cbm720_prtcpit[8] = {
 
    "" ,30, 0, 0,/* 10 pitch */
    "" , 0, 0, 0,/* 12 pitch */
    "" , 0, 0, 0,/* 16.7 pitch */
    ""              , 0, 0, 0,/* PS pitch */
    "" ,30, 0, 0,/* see above */
    "",  0, 0, 0,
    "" , 0, 0, 0,/* identical to dataprocessing mode */
    ""              , 0, 0, 0
};
 
char cbm720_prtspec [2][21] = {
 
    {0,  0,  0,  0,  0,  0,  0},/* print narrow bar */
    {0,  0,  0,  0,  0,  0,  0}/* print wide   bar */
};

unsigned char cbm720_prtoutt [128] [2] = {
{ 220,   0},/* 128 */
{ 221,   0},
{ 223,   0},
{ 219,   0},
{ 209,   0},
{ 190,   0},
{ 191,   0},
{ 193,   0},
{ 189,   0},
{ 195,   0},
{ 196,   0},
{ 198,   0},
{ 194,   0},
{ 200,   0},
{ 201,   0},
{ 203,   0},
{ 199,   0},/* 144 */
{ 205,   0},
{ 206,   0},
{ 208,   0},
{ 204,   0},
{ 176,   0},
{ 181,   0},
{ 178,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0}, /* 160 */
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ '@',   0},/* 176 */
{ '|',   0},
{ '-',   0},
{ '+',   0},
{ '|',   0},
{ '|',   0},
{ '+',   0},
{ '+',   0},
{ '-',   0},
{ '+',   0},
{ '-',   0},
{ '+',   0},
{ '+',   0},
{ '+',   0},
{ '+',   0},
{ '+',   0},
{ '@',   0},/* 192 */
{ '|',   0},
{ '-',   0},
{ '+',   0},
{ '|',   0},
{ '|',   0},
{ '+',   0},
{ '+',   0},
{ '-',   0},
{ '+',   0},
{ '-',   0},
{ '+',   0},
{ '+',   0},
{ '+',   0},
{ '+',   0},
{ '+',   0},
{ 126,   0}, /* 208 */
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0}, /* 224 */
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0}, /* 240 */
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0}
};

// 11 EPSTCKP

char *epstckp_prtactt [] = {
  "\x1B@",
  "\x1B\x45\x31",/* boldface on */
  "\x1B\x45\x30",/* off */
  "\x1B-1",/* underline on */
  "\x1B-0",/* off */
  "\x1B!\x20",/* elongated on */
  "\x1B!\xFF",/* off */
  "",
/* exec half forward line feed */
  "",/* Exec half reverse line feed */
  "\x0D"/* carriage return, no linefeed */
};
 
struct {
  char *progseq;        /* to send to printer to select the pitch */
  int  cincr;           /* increment for one character for active pitch */
  int  bscode[2];       /* to send after backspace char */
} epstckp_prtcpit[8] = {
 
    "" ,30, 0, 0,/* 10 pitch */
    "" , 0, 0, 0,/* 12 pitch */
    "" , 0, 0, 0,/* 16.7 pitch */
    ""              , 0, 0, 0,/* PS pitch */
    "" ,30, 0, 0,/* see above */
    "",  0, 0, 0,
    "" , 0, 0, 0,/* identical to dataprocessing mode */
    ""              , 0, 0, 0
};
 
char epstckp_prtspec [2][21] = {
 
    {0,  0,  0,  0,  0,  0,  0},/* print narrow bar */
    {0,  0,  0,  0,  0,  0,  0}/* print wide   bar */
};
 
unsigned char epstckp_prtoutt [128] [2] = {
{ 160,   0},/* 128 */
{ 133,   0},
{ 131,   0},
{ 132,   0},
{ 135,   0},
{ 130,   0},
{ 138,   0},
{ 136,   0},
{ 137,   0},
{ 161,   0},
{ 141,   0},
{ 140,   0},
{ 139,   0},
{ 162,   0},
{ 149,   0},
{ 147,   0},
{ 148,   0},/* 144 */
{ 163,   0},
{ 151,   0},
{ 150,   0},
{ 129,   0},
{ 154,   0},
{ 248,   0},
{  21,   0},
{ 190,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},/* 160 */
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 178,   0},/* 192 */
{ 186,   0},
{ 205,   0},
{ 200,   0},
{ 186,   0},
{ 186,   0},
{ 201,   0},
{ 204,   0},
{ 205,   0},
{ 188,   0},
{ 205,   0},
{ 202,   0},
{ 187,   0},
{ 185,   0},
{ 203,   0},
{ 206,   0},
{ 178,   0},/* 192 */
{ 179,   0},
{ 196,   0},
{ 192,   0},
{ 179,   0},
{ 179,   0},
{ 218,   0},
{ 195,   0},
{ 196,   0},
{ 217,   0},
{ 196,   0},
{ 193,   0},
{ 191,   0},
{ 180,   0},
{ 194,   0},
{ 197,   0},
{ 126,   0},/* 208 */
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},/* 224 */
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},/* 240 */
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0}
};

// 12 idp560

char *idp560_prtactt [] = {
  "\x18",
  "\x12",/* boldface on */
  "",/* off */
  "\xFF",/* underline on */
  "",/* off */
  "",/* elongated on */
  "",/* off */
  "",/* Exec half forward line feed */
  "",/* Exec half reverse line feed */
  ""/* cr only, no lf */
};
 
struct {
  char *progseq;        /* to send to printer to select the pitch */
  int  cincr;           /* increment for one character for active pitch */
  int  bscode[2];       /* to send after backspace char */
} idp560_prtcpit[8] = {
 
    ""          ,30, 0, 0,/* 10 pitch  Pica */
    ""          ,30, 0, 0,/* 16.7 pitch */
    ""          , 0, 0, 0,
    ""          , 0, 0, 0,     /* PS pitch */
    ""          ,30, 0, 0,/* see above */
    ""          ,30, 0, 0,
    ""          , 0, 0, 0,/* identical to dataprocessing mode */
    ""          , 0, 0, 0
};
 
unsigned char idp560_prtoutt [128] [2] = {
{  97,   0},/* 128 */
{  64,   0},
{  97,   0},
{  97,   0},
{  92,   0},
{ 123,   0},
{ 125,   0},
{ 101,   0},
{ 101,   0},
{ 105,   0},
{ 105,   0},
{ 105,   0},
{ 105,   0},
{ 111,   0},
{ 111,   0},
{ 111,   0},
{ 111,   0},/* 144 */
{ 117,   0},
{ 124,   0},
{ 117,   0},
{ 117,   0},
{  85,   0},
{  91,   0},
{  93,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0}, /* 160 */
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ '@',   0}, /* 176 */
{ '|',   0},
{ '-',   0},
{ '+',   0},
{ '|',   0},
{ '|',   0},
{ '+',   0},
{ '+',   0},
{ '-',   0},
{ '+',   0},
{ '-',   0},
{ '+',   0},
{ '+',   0},
{ '+',   0},
{ '+',   0},
{ '+',   0},
{ '@',   0},/* 192 */
{ '|',   0},
{ '-',   0},
{ '+',   0},
{ '|',   0},
{ '|',   0},
{ '+',   0},
{ '+',   0},
{ '-',   0},
{ '+',   0},
{ '-',   0},
{ '+',   0},
{ '+',   0},
{ '+',   0},
{ '+',   0},
{ '+',   0},
{ 126,   0}, /* 208 */
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0}, /* 224 */
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0}, /* 240 */
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0},
{ 126,   0}
};

// default code voor simple-matrix. Wordt nadien zonodig aangepast

  int i,j;

  cut_delay = -1;
  cut_act = "";
  linefeed = "\x0A";/* code to send after <CR> */
  for (i=0; i<128; i++) {
    _prtoutt[i][0]=simple_prtoutt[i][0];
    _prtoutt[i][1]=simple_prtoutt[i][1];
  }
  for (i=0; i<10; i++) _prtactt[i]="";
  for (i=0; i<8; i++) {
    _progseq[i]="";
    _cincr[i]=0;
  }
  _cincr[0]=30; _cincr[1]=30; _cincr[4]=30; _cincr[4]=30;
  _prtspec[0][0]=0; _prtspec[1][0]=0;
  for (i=0; i<4; i++) _prt39[i][0]=0;
  for (i=0; i<4; i++) _geldopen[i]="";
  for (i=0; i<3; i++) _ladeselect[i]="";
  switch(PrinterDriver) {
    case 1:
      for (i=0; i<128; i++) {
        _prtoutt[i][0]=iprta_prtoutt[i][0];
        _prtoutt[i][1]=iprta_prtoutt[i][1];
      }
      for (i=0; i<10; i++) _prtactt[i]=iprta_prtactt[i];
      for (i=0; i<8; i++) {
        _progseq[i]=iprta_prtcpit[i].progseq;
        _cincr[i]=iprta_prtcpit[i].cincr;
      }
      for (i=0; i<21; i++) {
        _prtspec[0][i]=iprta_prtspec[0][i];
        _prtspec[1][i]=iprta_prtspec[1][i];
      } 
      for (i=0; i<4; i++) {
        for (j=0; j<21; j++) {
          _prt39[i][j]=iprta_prt39[i][j];
        }
      }
      break;
    case 2:
      for (i=0; i<128; i++) {
        _prtoutt[i][0]=iprtb_prtoutt[i][0];
        _prtoutt[i][1]=iprtb_prtoutt[i][1];
      }
      for (i=0; i<10; i++) _prtactt[i]=iprtb_prtactt[i];
      for (i=0; i<8; i++) {
        _progseq[i]=iprtb_prtcpit[i].progseq;
        _cincr[i]=iprtb_prtcpit[i].cincr;
      }
      for (i=0; i<21; i++) {
        _prtspec[0][i]=iprtb_prtspec[0][i];
        _prtspec[1][i]=iprtb_prtspec[1][i];
      } 
      for (i=0; i<4; i++) {
        for (j=0; j<21; j++) {
          _prt39[i][j]=iprtb_prt39[i][j];
        }
      }
      break;
    case 3:
      for (i=0; i<128; i++) {
        _prtoutt[i][0]=iprtc_prtoutt[i][0];
        _prtoutt[i][1]=iprtc_prtoutt[i][1];
      }
      for (i=0; i<10; i++) _prtactt[i]=iprtc_prtactt[i];
      for (i=0; i<8; i++) {
        _progseq[i]=iprtc_prtcpit[i].progseq;
        _cincr[i]=iprtc_prtcpit[i].cincr;
      }
      for (i=0; i<21; i++) {
        _prtspec[0][i]=iprtc_prtspec[0][i];
        _prtspec[1][i]=iprtc_prtspec[1][i];
      } 
      for (i=0; i<4; i++) {
        for (j=0; j<21; j++) {
          _prt39[i][j]=iprtc_prt39[i][j];
        }
      }
      break;
    case 4:
      for (i=0; i<128; i++) {
        _prtoutt[i][0]=iprtd_prtoutt[i][0];
        _prtoutt[i][1]=iprtd_prtoutt[i][1];
      }
      for (i=0; i<10; i++) _prtactt[i]=iprtd_prtactt[i];
      for (i=0; i<8; i++) {
        _progseq[i]=iprtd_prtcpit[i].progseq;
        _cincr[i]=iprtd_prtcpit[i].cincr;
      }
      for (i=0; i<21; i++) {
        _prtspec[0][i]=iprtd_prtspec[0][i];
        _prtspec[1][i]=iprtd_prtspec[1][i];
      } 
      for (i=0; i<4; i++) {
        for (j=0; j<21; j++) {
          _prt39[i][j]=iprtd_prt39[i][j];
        }
      }
      break;
    case 5:
      for (i=0; i<128; i++) {
        _prtoutt[i][0]=epsonfx_prtoutt[i][0];
        _prtoutt[i][1]=epsonfx_prtoutt[i][1];
      }
      for (i=0; i<10; i++) _prtactt[i]=epsonfx_prtactt[i];
      for (i=0; i<8; i++) {
        _progseq[i]=epsonfx_prtcpit[i].progseq;
        _cincr[i]=epsonfx_prtcpit[i].cincr;
      }
      for (i=0; i<21; i++) {
        _prtspec[0][i]=epsonfx_prtspec[0][i];
        _prtspec[1][i]=epsonfx_prtspec[1][i];
      } 
     break;
    case 6:
      for (i=0; i<128; i++) {
        _prtoutt[i][0]=star10_prtoutt[i][0];
        _prtoutt[i][1]=star10_prtoutt[i][1];
      }
      for (i=0; i<10; i++) _prtactt[i]=star10_prtactt[i];
      for (i=0; i<8; i++) {
        _progseq[i]=star10_prtcpit[i].progseq;
        _cincr[i]=star10_prtcpit[i].cincr;
      }
      for (i=0; i<21; i++) {
        _prtspec[0][i]=star10_prtspec[0][i];
        _prtspec[1][i]=star10_prtspec[1][i];
      } 
      break;
    case 7:
      for (i=0; i<128; i++) {
        _prtoutt[i][0]=nec_pxx_prtoutt[i][0];
        _prtoutt[i][1]=nec_pxx_prtoutt[i][1];
      }
      for (i=0; i<10; i++) _prtactt[i]=nec_pxx_prtactt[i];
      for (i=0; i<8; i++) {
        _progseq[i]=nec_pxx_prtcpit[i].progseq;
        _cincr[i]=nec_pxx_prtcpit[i].cincr;
      }
      for (i=0; i<21; i++) {
        _prtspec[0][i]=nec_pxx_prtspec[0][i];
        _prtspec[1][i]=nec_pxx_prtspec[1][i];
      } 
      for (i=0; i<4; i++) {
        for (j=0; j<21; j++) {
          _prt39[i][j]=nec_pxx_prt39[i][j];
        }
      }
      break;
    case 10:
      for (i=0; i<128; i++) {
        _prtoutt[i][0]=cbm720_prtoutt[i][0];
        _prtoutt[i][1]=cbm720_prtoutt[i][1];
      }
      for (i=0; i<10; i++) _prtactt[i]=cbm720_prtactt[i];
      for (i=0; i<8; i++) {
        _progseq[i]=cbm720_prtcpit[i].progseq;
        _cincr[i]=cbm720_prtcpit[i].cincr;
      }
      for (i=0; i<21; i++) {
        _prtspec[0][i]=cbm720_prtspec[0][i];
        _prtspec[1][i]=cbm720_prtspec[1][i];
      } 
      cut_delay = 5;
      cut_act = "\x1B\x50\xFF";
      _geldopen[0]="\x1C";
      _geldopen[1]="\x1A";
      break;
    case 11:
      for (i=0; i<128; i++) {
        _prtoutt[i][0]=epstckp_prtoutt[i][0];
        _prtoutt[i][1]=epstckp_prtoutt[i][1];
      }
      for (i=0; i<10; i++) _prtactt[i]=epstckp_prtactt[i];
      for (i=0; i<8; i++) {
        _progseq[i]=epstckp_prtcpit[i].progseq;
        _cincr[i]=epstckp_prtcpit[i].cincr;
      }
      for (i=0; i<21; i++) {
        _prtspec[0][i]=epstckp_prtspec[0][i];
        _prtspec[1][i]=epstckp_prtspec[1][i];
      } 
      cut_delay = 5;
      cut_act = "\x1DV1";
      _geldopen[0]="\x1Bp0\x32\xC8";
      _geldopen[1]="\x1Bp1\x32\xC8";
      break;
    case 12:
      for (i=0; i<128; i++) {
        _prtoutt[i][0]=idp560_prtoutt[i][0];
        _prtoutt[i][1]=idp560_prtoutt[i][1];
      }
      for (i=0; i<10; i++) _prtactt[i]=idp560_prtactt[i];
      for (i=0; i<8; i++) {
        _progseq[i]=idp560_prtcpit[i].progseq;
        _cincr[i]=idp560_prtcpit[i].cincr;
      }
      break;
  }           
}

void CJmuDoc::Matrix_graph_init(int count)
{
  int i1, i2;
  RetBufUsed=0;

  i1=count % 256;
  i2=count / 256;
  if (PrinterDriver>=1 && PrinterDriver<=4) {
    Matrix_tkprt("\x1BU1");
    Matrix_prch(0x1B); Matrix_prch('Z'); Matrix_prch(i1); Matrix_prch(i2);    
  } 
  if (PrinterDriver>=5 && PrinterDriver<=6) {
    Matrix_prch(0x1B); Matrix_prch(0x4C); Matrix_prch(i1); Matrix_prch(i2);
  }
  if (PrinterDriver==7) {
    Matrix_prch(0x1B); Matrix_prch('*'); Matrix_prch(39); Matrix_prch(i1); Matrix_prch(i2);
  }
}

void CJmuDoc::Matrix_graph_exit()
{
  RetBufUsed=0;

  if (PrinterDriver>=1 && PrinterDriver<=4) Matrix_tkprt("\x1BU0");
}

void CJmuDoc::Matrix_prt39(char code)
{
  static struct {
    unsigned char bars;
    unsigned char spaces;
  } code39[60]= {
  0x50,0x80,/* space = 20 H */
  0xFF,0xFF,
  0xFF,0xFF,
  0xFF,0xFF,
  0x00,0xE0,
  0x00,0x70,
  0xFF,0xFF,
  0xFF,0xFF,
  0xFF,0xFF,
  0xFF,0xFF,
  0x30,0x80,
  0x00,0xB0,
  0xFF,0xFF,
  0x18,0x80,
  0x90,0X80,
  0x00,0xD0,
  0x30,0x40,/* 0 */
  0x88,0x40,
  0x48,0x40,
  0xC0,0x40,
  0x28,0x40,
  0xA0,0x40,
  0x60,0x40,
  0x18,0x40,
  0x90,0x40,
  0x50,0x40,/* 9 */
  0xFF,0xFF,
  0xFF,0xFF,
  0xFF,0xFF,
  0xFF,0xFF,
  0xFF,0xFF,
  0xFF,0xFF,
  0xFF,0xFF,/* @ -> 40 H */
  0x88,0x20,
  0x48,0x20,
  0xC0,0x20,
  0x28,0x20,
  0xA0,0x20,
  0x60,0x20,
  0x18,0x20,
  0x90,0x20,
  0x50,0x20,
  0x30,0x20,
  0x88,0x10,
  0x48,0x10,
  0xC0,0x10,
  0x28,0x10,
  0xA0,0x10,
  0x60,0x10,
  0x18,0x10,
  0x90,0x10,
  0x50,0x10,
  0x30,0x10,
  0x88,0x80,
  0x48,0x80,
  0xC0,0x80,
  0x28,0x80,
  0xA0,0x80,
  0x60,0x80};

  
  int j;
  unsigned char bars, spaces, mask;
 
  bars=0xFF;
  while (1) {
    if (code>='a' && code<='z') code+='A'-'a';
    if (code>=' ' && code<='Z') {
      bars=code39[code-' '].bars;
      spaces=code39[code-' '].spaces;
    }
    if (bars==0xFF) code=' ';
    else break;
  }
  mask=0x80;
  for (j=0; j<5; j++) {
    if (bars&mask) Matrix_specprt(&_prt39[1][0]); else Matrix_specprt(&_prt39[0][0]);
    if (spaces&mask) Matrix_specprt(&_prt39[3][0]); else Matrix_specprt(&_prt39[2][0]);
    mask=mask>>1;
  }
}

void CJmuDoc::Matrix_PrintByte(int code)
{
  int i, bit, j;
 
  if (spec) {
    if (spec==BARCODE) {
      if (code<0xD0 && bar_len<31) barcode[bar_len++]=code;
      else {
	      if (bar_len>1) {
          if (barcode[0]==1) {
            Matrix_graph_init(((bar_len-1) * 4 + 3) * _prtspec[1][0]);
            Matrix_specprt(_prtspec[1]);
            for (i=1; i<bar_len; i++) {
              bit = 8;
              for (j=0; j<4; j++) {
	              if (barcode[i]&bit) Matrix_specprt(_prtspec[1]); else Matrix_specprt(_prtspec[0]);
	              bit = bit >> 1;
              }
            }
            Matrix_specprt(_prtspec[0]); Matrix_specprt(_prtspec[0]);
            Matrix_graph_exit();
          }
          else if (barcode[0]==2) {
            Matrix_graph_init((_prt39[0][0]*7 + _prt39[1][0]*3) * (bar_len-1+2));
            Matrix_prt39('*');
            for (i=1; i<bar_len; i++) Matrix_prt39(barcode[i]);
            Matrix_prt39('*');
            Matrix_graph_exit();
          }        
        }
        spec = false;
      }
      goto endsr;
    }
    else if (spec==DEVCONTROL) {
      if (!code) spec=false;
    }
    else if (spec==GELDOPEN) {
      i=code-'1';
      if (i>=0 && i<4) {
	      Matrix_tkprt(_geldopen[i]);
      }
      spec=false;
      goto endsr;
    }
    else if (spec=PRTEXTRA) {
      if (code=='|') {
        spec=false;
	      goto endsr;
      }
    }
  }
  if (code<0xD0) {
    if (code==159) code='E';
    Matrix_prchar(code);
  }
  else {
    code-=0xD0;
    if (code<0x10) {
       if (code==0) {
         spec=BARCODE;
         bar_len=0;
       }
       else if (code==3) {
         spec=GELDOPEN;
       }
       else if (code==4) {
	       spec=PRTEXTRA;
       }
    }
    else {
      code-=0x10;
      if (code<0x10) {
	      Matrix_tkprt(_prtactt[code]);
      	switch (code) {
	        case 1:
	        case 2:
	          bolflag = code & 1;
	          break;
	        case 3:
	        case 4:
	          undflag = code & 1;
	          break;
	        case 5:
	          if (*_prtactt[pitch]) {/* only when elongation available */
	            eloflag = true;
	            cincr = _cincr[pitch] * 2;
	          }
	          break;
	        case 6:
	          eloflag = false;
	          cincr = _cincr[pitch];
	          break;
	      }
      }
      else {
	      code-=0x10;
	      if (code<0x08) {
	        Matrix_tkprt(_progseq[code]);
	        cincr = _cincr[code] * (eloflag+1);
	        pitch = code;
	      }
	      else if (code<=0x0A) Matrix_tkprt(_ladeselect[code-8]);
	      else if (code==0x0B) spec=DEVCONTROL; // skip
	      else if (code==0x0D) {
	        if (cut_delay==0) Matrix_tkprt(cut_act);
	        else if (cut_delay>0) {
	          cut2skip=cut_delay; cut_flag=true;
          }
	      }
	    }
    }
  }
  endsr:;
}

void CJmuDoc::Matrix_prch(int byte)
{
  char buf[5];
  int i;
  unsigned long written;

  buf[0]=byte;
  i=WritePrinter(hMatrix, buf, 1, &written);
  if (written!=1) err_flag=true;
  i=i;
}

void CJmuDoc::Matrix_prchar(int byte)
{
  if (byte<128) {
    Matrix_prch(byte);
    if (byte==0x0D) {
      Matrix_tkprt(linefeed);
      if (cut_flag) {
        if (!--cut2skip) {
	        cut_flag=false;
	        Matrix_tkprt(cut_act);
        }
      }
    }
  }
  else {
    byte -= 128;
    Matrix_prch(_prtoutt[byte][0]);
  }
}

void CJmuDoc::Matrix_tkprt(char *pb)
{
  char byte;
 
  while ((byte=*pb++)) {
    if (byte==-1) byte=0;
    Matrix_prch(byte);
  }
}

void CJmuDoc::Matrix_specprt(char *pb)
{
  int len;

  len=*pb++;
  while (len-->0) Matrix_prch(*pb++);
}

bool CJmuDoc::PrintOnMatrix(CString PrinterName, int PageFirst, int PageLast)
{
  int i, pos, RepeatCnt=0, page;
  unsigned char b;
  DOC_INFO_1 di;

  PrinterDriver=0;
  bolflag=false;
  eloflag=false;
  undflag=false;
  cincr=0;
  spec=false;
  cut_flag=false;
	cut2skip=10000;

  i=OpenPrinter((LPSTR)PrinterName.operator LPCTSTR(),&hMatrix,NULL);
  if (i==0) return false; // illegal printername etc. ...

  err_flag=false;
  memset(&di, 0, sizeof(DOC_INFO_1));
  di.pDocName= (char*)(LPCTSTR)DocumentName;
  di.pOutputFile=NULL;
  di.pDatatype="RAW";
  i=StartDocPrinter( hMatrix, 1, (unsigned char *)&di);

  pitch=Page2cpi[PageFirst];
  Matrix_tkprt(_progseq[pitch]);
  for (page=PageFirst; page<=PageLast; page++) {
    StartPagePrinter(hMatrix);
    pos=Page2Pos[page];
		while (true) {
		  if (RepeatCnt<=0 && pos>=Page2Pos[page+1]) break;
		  if (RepeatCnt<=0) {
        b=SPL[pos];
        if (b==0xEF) {
          b=SPL[pos+1];
          RepeatCnt=SPL[pos+2]-1;
          pos+=2;
        }
      }
      else {
        RepeatCnt--;
        pos--;
      }
      Matrix_PrintByte(b);
			pos++;
    }
    EndPagePrinter(hMatrix);
  }
  EndDocPrinter(hMatrix);
  ClosePrinter(hMatrix);
  return !err_flag;
}
