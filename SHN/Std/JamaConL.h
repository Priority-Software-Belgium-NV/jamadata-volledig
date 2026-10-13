// JamaConL.h : Header file
//

/* #if defined(_WIN32_WCE)

// copyied from stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__A9DB83DB_A9FD_11D0_BFD1_444553540000__INCLUDED_)
#define AFX_STDAFX_H__A9DB83DB_A9FD_11D0_BFD1_444553540000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers

// Windows Header Files:
#include <windows.h>

// Local Header Files

// TODO: reference additional headers your program requires here

//{{AFX_INSERT_LOCATION}}
// Microsoft eMbedded Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__A9DB83DB_A9FD_11D0_BFD1_444553540000__INCLUDED_)

#else if // de w32 stdafx.h versie ...
*/

// copied from stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__07F2A0BA_7FCF_4F00_AA78_1767834E62E2__INCLUDED_)
#define AFX_STDAFX_H__07F2A0BA_7FCF_4F00_AA78_1767834E62E2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers

#include <stdio.h>
#include "afxsock.h"

// TODO: reference additional headers your program requires here

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__07F2A0BA_7FCF_4F00_AA78_1767834E62E2__INCLUDED_)

/* #endif */

#include "AfxTempl.h"

//  KASSA

#define PANEL_WITH_EDGE     1
#define PANEL_HOR_SMALLER   2
#define PANEL_VER_SMALLER   4

extern "C" __declspec(dllimport) void _disp_exit(char *s);
extern "C" __declspec(dllimport) void disp_clr(int x_pos,int y_pos,int x_len,int y_len);
extern "C" __declspec(dllimport) void closestr(char *str);
extern "C" __declspec(dllimport) void cls();
//extern "C" __declspec(dllimport) void screen_refresh();
extern "C" __declspec(dllimport) void disp_vid(int x, int y, void *s, int attr);
extern "C" __declspec(dllimport) void disp_key(int x_pos,int y_pos,int x_len,int y_len,int key_numb, COLORREF color=0);
extern "C" __declspec(dllimport) void disp_ikey(int x_pos,int y_pos,int x_len,int y_len,int key_numb,char *ps, COLORREF color=0);
extern "C" __declspec(dllimport) char* GetPtrTxtKey(int key_numb);
extern "C" __declspec(dllimport) void disp_panel(int x_pos,int y_pos,int x_len,int y_len,int style, COLORREF color);

/*
extern "C" __declspec(dllimport) int  pen_scan(int text_fl);
extern "C" __declspec(dllimport) void pen_reset();
extern "C" __declspec(dllimport) bool pen_down();
*/
extern "C" __declspec(dllimport) void get_pos(int *px, int *py);
extern "C" __declspec(dllimport) void beep_ok();
extern "C" __declspec(dllimport) void beep_bad();
extern "C" __declspec(dllimport) void beep_tick();

// CONFUNC

extern "C" __declspec(dllimport) int  mspos_h, mspos_v, vdpos_h, vdpos_v, vdlen_h, vdlen_v, vdmax_h, vdmax_v;
extern "C" __declspec(dllimport) bool IsOk;
extern "C" __declspec(dllimport) int  attribute;
extern "C" __declspec(dllimport) bool TouchPanelFlag;
extern "C" __declspec(dllimport) void beep();
extern "C" __declspec(dllimport) void con_derr(char *pbuf);
extern "C" __declspec(dllimport) void con_cerr();
extern "C" __declspec(dllimport) void curson(int type);
extern "C" __declspec(dllimport) void cursof();
extern "C" __declspec(dllimport) void curs_do();
extern "C" __declspec(dllimport) void curs_ho();
extern "C" __declspec(dllimport) void curs_le();
extern "C" __declspec(dllimport) void curs_ri();
extern "C" __declspec(dllimport) void curs_up();
extern "C" __declspec(dllimport) int kbchar();
extern "C" __declspec(dllimport) int kbcharnw();
extern "C" __declspec(dllimport) int kbtest(bool CheckOnly=false);
extern "C" __declspec(dllimport) void kbflush();

extern "C" __declspec(dllimport) int WndAdd(bool NoKBInput=false);
extern "C" __declspec(dllimport) void WndSelect(int WndIx);
extern "C" __declspec(dllimport) void WndShowWindow(int WndIx, int nCmdShow);
extern "C" __declspec(dllimport) void WndSetWindowPos(int WndIx, char InConsoleFlag, int x, int y, int cx, int cy, UINT nFlags );

extern "C" __declspec(dllimport) void moinit(int OptionFlag,int console,CWnd *pMainWnd=NULL); 
#define OptionDAO	2
#define OptionSTO 4
#define OptionAddExtraSTO 8

extern "C" __declspec(dllimport) void _moexit(int code);
extern "C" __declspec(dllimport) void tkdsp(char *s);
extern "C" __declspec(dllimport) void tkdspnl(char *s);
extern "C" __declspec(dllimport) void unkbchar(int code);
extern "C" __declspec(dllimport) int vdchar(int byte);
extern "C" __declspec(dllimport) int rdchar();
extern "C" __declspec(dllimport) void vdposp(int v,int h);

#define CON_STYLE_NOBACKGROUND      1     // bit 1

extern "C" __declspec(dllimport) void SetProgramName(char *str);
extern "C" __declspec(dllimport) void ConTitle(char *str);
extern "C" __declspec(dllimport) void ConLook(int look);
extern "C" __declspec(dllimport) HWND ConGetWndInfo(CString& AppName);
extern "C" __declspec(dllimport) int ConSelect(int nr);
extern "C" __declspec(dllimport) void ConSizeWindow(int hlen, int vlen);
extern "C" __declspec(dllimport) int PlatformType(int type);
extern "C" __declspec(dllimport) void ConFullScreenLock(bool LockFlag);
extern "C" __declspec(dllimport) int ConStyle(int style);
extern "C" __declspec(dllimport) void ConRefresh();
extern "C" __declspec(dllimport) void ConWaitCursor(bool ON);
extern "C" __declspec(dllimport) void SplashShow();
extern "C" __declspec(dllimport) void SplashHide();
extern "C" __declspec(dllimport) void SplashText(char *str);
extern "C" __declspec(dllimport) void InfoCls();
extern "C" __declspec(dllimport) void InfoDisp(const char *s);
extern "C" __declspec(dllimport) void InfoHide();
extern "C" __declspec(dllimport) void InfoSetup(int xpos, int ypos, int xlen, int ylen);
extern "C" __declspec(dllimport) void InfoShow();
extern "C" __declspec(dllimport) int ConMessageBox(LPCTSTR lpszText, LPCTSTR lpszCaption, UINT nType);
extern "C" __declspec(dllimport) void UpdateScreenProperties();

#define JAMALINKBUFSIZE 12500

// KBLIN.C

extern "C" __declspec(dllimport) int kblin_s(char *pbuf,int cntbf,char *pgeldig,char *pexit, char *pmask,int opt1);
extern "C" __declspec(dllimport) int kblin(char *pbuf,int cntbf);
extern "C" __declspec(dllimport) int kbjn(int i,char *pexit,int opt1);

// OUDE LATTICE CALLS

extern "C" __declspec(dllimport) unsigned getfa(char *s);
extern "C" __declspec(dllimport) unsigned chgfa(char *name, unsigned fa);
extern "C" __declspec(dllimport) long getft(int ref);
extern "C" __declspec(dllimport) unsigned chgft(int ref, long ft);
extern "C" __declspec(dllimport) int strmfn(char *file, char *drive, char *path, char *node, char *ext);
extern "C" __declspec(dllimport) int strsfn(char *file, char *drive, char *path, char *node, char *ext);
extern "C" __declspec(dllimport) int strmfe(char *newname,char *oldname,char *ext);
extern "C" __declspec(dllimport) int setbrk();
extern "C" __declspec(dllimport) int rstbrk();
extern "C" __declspec(dllimport) char *getml(long size);
extern "C" __declspec(dllimport) int rlsml(char *s,long l);
extern "C" __declspec(dllimport) void movmem(void *s,void *d,unsigned len);
extern "C" __declspec(dllimport) void getcd(int pathlen, char *path);
extern "C" __declspec(dllimport) int dopen(char *name,int oflag);
extern "C" __declspec(dllimport) int dclose(int ref);
extern "C" __declspec(dllimport) int dcreat(char *name,int mode);
extern "C" __declspec(dllimport) int dwrite(int ref,void *buf,int len);
extern "C" __declspec(dllimport) int dread(int ref,void *buf,int len);
extern "C" __declspec(dllimport) long dseek(int ref,long rpos,int mode);
extern "C" __declspec(dllimport) int dflush(int ref);
extern "C" __declspec(dllimport) int CopyFileIfDifferent(char *source, char *dest);  // ret= -1 File niet gevonden, 0= identiek, 1=gekopieerd
#if defined(_WIN32_WCE)
extern "C" __declspec(dllimport) int remove(char *name);
extern "C" __declspec(dllimport) int rename(char *oldname, char *newname);
#endif
extern "C" __declspec(dllimport) unsigned stci_d(char *s,int in,int outlen);
extern "C" __declspec(dllimport) unsigned stcd_i(char *s,int *r);
extern "C" __declspec(dllimport) int stcd_li(char *s,long *li);
extern "C" __declspec(dllimport) void stcli_d (char *s,long l,int digits,char lzerosup);
extern "C" __declspec(dllimport) int stcd_df(char *s,double *df);
extern "C" __declspec(dllimport) void stcdf_d (char *s,double df,int digits,char lzerosup);
extern "C" __declspec(dllimport) int cstr2arr(CString cstr, void *pd, int MaxLen);
extern "C" __declspec(dllimport) void zeros(void *pd, int len);
extern "C" __declspec(dllimport) void bcopy(void *ps, void *pd, int len);

// BFILIO

extern "C" __declspec(dllimport) void bclose(int f_nr);
extern "C" __declspec(dllimport) void berr(int f_nr,int funr);
extern "C" __declspec(dllimport) int bgetc(int f_nr);
extern "C" __declspec(dllimport) int bkill(char *fil_name);
extern "C" __declspec(dllimport) long blof(int f_nr);
extern "C" __declspec(dllimport) int bopen(char *fil_name,int mode,int fil);
extern "C" __declspec(dllimport) int bputc(int f_nr,int byte);
extern "C" __declspec(dllimport) int bread(int f_nr,char *bf,int len);
extern "C" __declspec(dllimport) long bseek(int f_nr,long lpos,int mode);
extern "C" __declspec(dllimport) long btell(int f_nr);
extern "C" __declspec(dllimport) int bwrite(int f_nr,char *bf,int len);

// CFILIO

extern "C" __declspec(dllimport) void c_close(int fint);
extern "C" __declspec(dllimport) void c_end(int fint);
extern "C" __declspec(dllimport) int c_getc(int fint);
extern "C" __declspec(dllimport) int c_open(char *filename,int mod1,int mod2,int repcd);
extern "C" __declspec(dllimport) int c_putc(int fint,int byte);

// SORT

extern "C" __declspec(dllimport) void jsort(void *p,long c,int s,int (*cm)(char *, char *, int));

// DatFunc1
																							
extern "C" __declspec(dllimport) unsigned datejd(int jj,int mm,int dd);
extern "C" __declspec(dllimport) void jddate(unsigned jd,short int *jj,short int *mm,short int *dd);
extern "C" __declspec(dllimport) unsigned dateadd(unsigned jd,char *verv);
extern "C" __declspec(dllimport) unsigned dateget();

// DatFunc2

extern "C" __declspec(dllimport) unsigned datechk(char *ps);
extern "C" __declspec(dllimport) int datefm(char *ps,unsigned jd,int fm);

// GrbFunc

extern "C" __declspec(dllimport) void grb_deco(void *s,void *r);
extern "C" __declspec(dllimport) void grb_comp(void *s,void *r);

// RekFunc

extern "C" __declspec(dllimport) void rek_deco(char *s,unsigned char *r,int sepflag);
extern "C" __declspec(dllimport) int rek_comp(char *s,unsigned char *r);

// BTWFunc

extern "C" __declspec(dllimport) void btw_deco(char *s,long *pl,int sepflag);
extern "C" __declspec(dllimport) int btw_comp(char *s,long *pl);

// PRTUTIL

extern "C" __declspec(dllimport) int _prtfree; 
extern "C" __declspec(dllimport) int _pagenum;

extern "C" __declspec(dllimport) void setform(short int *pform);
extern "C" __declspec(dllimport) void sethead(int count,char *ph[]);
extern "C" __declspec(dllimport) void setfoot(int count,char *pf[]);
extern "C" __declspec(dllimport) void print(char *pb);
extern "C" __declspec(dllimport) void printnl(char *pb);
extern "C" __declspec(dllimport) void formfeed();
extern "C" __declspec(dllimport) void formskip();
extern "C" __declspec(dllimport) void _skip_marge();
extern "C" __declspec(dllimport) void setlpi(int lpi);
extern "C" __declspec(dllimport) void setlade(int nr);
extern "C" __declspec(dllimport) void setcpi(int cpi,int type);
extern "C" __declspec(dllimport) void setacpi(int col,int type);
extern "C" __declspec(dllimport) void setlmarg(int value);
extern "C" __declspec(dllimport) int _prterr(char err);
extern "C" __declspec(dllimport) void prtstring(char *s);
extern "C" __declspec(dllimport) void prtendit();

// PRTFUNC

extern "C" __declspec(dllimport) void prtchar(int code);
extern "C" __declspec(dllimport) void prtsel(int number);
 
// FrmtNum

extern "C" __declspec(dllimport) int frmtnum(char *ptxt,int type,double *adresfl,int qvoor,int qna,int opt1);

// KBNUM_S

extern "C" __declspec(dllimport) int kbnum_s(int type,void *adresfl,int qvoor,int qna,char *pexit,int opt1,void *plim);

// PCLutil

extern "C" __declspec(dllimport) void PCLprt_string(char *string);
extern "C" __declspec(dllimport) void PCLpush();
extern "C" __declspec(dllimport) void PCLpop();
extern "C" __declspec(dllimport) void PCLmov(int x_pos,int y_pos);
extern "C" __declspec(dllimport) void PCLsel_prop(int size,int stroke_weight,int style);
extern "C" __declspec(dllimport) void PCLtxt(int size,int x_pos,int y_pos,char *ps_,char *attr);
extern "C" __declspec(dllimport) void PCLbox(int dikte,int x_pos,int y_pos,int x_len,int y_len);
extern "C" __declspec(dllimport) void PCLblock(int rast,int x_pos,int y_pos,int x_len,int y_len);
extern "C" __declspec(dllimport) int  PCLean8c(char *p);
extern "C" __declspec(dllimport) void PCLprtean8(int x_pos,int y_pos,int x_size,int y_size,int yl_size,char *s);
extern "C" __declspec(dllimport) void PCLlogo(int x_pos,int y_pos,char *s,int size);
extern "C" __declspec(dllimport) int  PCLean13c(char *p);
extern "C" __declspec(dllimport) void PCLprtean(int x_pos,int y_pos,int x_size,int y_size,int yl_size,char *s);
extern "C" __declspec(dllimport) void PCLprtCode39(int x_pos,int y_pos,int x_size,int y_size,char *s);
extern "C" __declspec(dllimport) int  PCLcent_txt(int dikte_,int bpos_,int epos_,char *ps_);

//DataMngr

extern "C" __declspec(dllimport) int fieldspc(int str, int ele, void *ppointer, void *fm);
extern "C" __declspec(dllimport) int address(int str, int ele, void *ppointer);
extern "C" __declspec(dllimport) double *d(int str,int ele);
extern "C" __declspec(dllimport) float *f(int str,int ele);
extern "C" __declspec(dllimport) short int *is(int str,int ele);
extern "C" __declspec(dllimport) short int *i(int str,int ele);
extern "C" __declspec(dllimport) long *l(int str,int ele);
extern "C" __declspec(dllimport) char *s(int str,int ele);
extern "C" __declspec(dllimport) short unsigned *us(int str,int ele);
extern "C" __declspec(dllimport) short unsigned *u(int str,int ele);
extern "C" __declspec(dllimport) int cmpstr(char *p1,char *p2,int len);
extern "C" __declspec(dllimport) int fldlen(int str,int ele);
extern "C" __declspec(dllimport) long val(char *s);
extern "C" __declspec(dllimport) int mdbadd(int str);
extern "C" __declspec(dllimport) int mdbaddi(int str);
extern "C" __declspec(dllimport) int mdbclos(int str);
extern "C" __declspec(dllimport) int mdbflush(int str);
extern "C" __declspec(dllimport) int mdbgetu(int str);
extern "C" __declspec(dllimport) int mdbgeti(int str);
extern "C" __declspec(dllimport) int mdbinfo(int str,int mode);
extern "C" __declspec(dllimport) void mdbinit(int str);
extern "C" __declspec(dllimport) int mdbkeyi(int str,int key,int mode);
extern "C" __declspec(dllimport) int mdbkeyu(int str,int key,int mode);
extern "C" __declspec(dllimport) int mdbskip(int str,int key,int ele);
extern "C" __declspec(dllimport) int mdbkill(int str);
extern "C" __declspec(dllimport) int mdbksfu(int str);
extern "C" __declspec(dllimport) int mdbopen(char *name,int mode);
extern "C" __declspec(dllimport) int mdbseqi(int str,int chan,int count);
extern "C" __declspec(dllimport) int mdbseqo(int str,int chan,int count);
extern "C" __declspec(dllimport) int mdbunlck(int str);
extern "C" __declspec(dllimport) int mdbupd(int str);
extern "C" __declspec(dllimport) int mdbupdi(int str);

#ifdef UseJMS
extern "C"  int fasadd(int str);
extern "C"  int fasaddi(int str);
extern "C"  int fasclos(int str);
extern "C"  int fasflush(int str);
extern "C"  int fasgetu(int str);
extern "C"  int fasgeti(int str);
extern "C"  int fasinfo(int str,int mode);
extern "C"  void fasinit(int str);
extern "C"  int faskeyi(int str,int key,int mode);
extern "C"  int faskeyu(int str,int key,int mode);
extern "C"  int faskill(int str);
extern "C"  int fasksfu(int str);
extern "C"  int fasopen(char *name,int mode);
extern "C"  int fasseqi(int str,int chan,int count);
extern "C"  int fasseqo(int str,int chan,int count);
extern "C"  int fasunlck(int str);
extern "C"  int fasupd(int str);
extern "C"  int fasupdi(int str);
#else
extern "C" __declspec(dllimport) int fasadd(int str);
extern "C" __declspec(dllimport) int fasaddi(int str);
extern "C" __declspec(dllimport) int fasclos(int str);
extern "C" __declspec(dllimport) int fasflush(int str);
extern "C" __declspec(dllimport) int fasgetu(int str);
extern "C" __declspec(dllimport) int fasgeti(int str);
extern "C" __declspec(dllimport) int fasinfo(int str,int mode);
extern "C" __declspec(dllimport) void fasinit(int str);
extern "C" __declspec(dllimport) int faskeyi(int str,int key,int mode);
extern "C" __declspec(dllimport) int faskeyu(int str,int key,int mode);
extern "C" __declspec(dllimport) int faskill(int str);
extern "C" __declspec(dllimport) int fasksfu(int str);
extern "C" __declspec(dllimport) int fasopen(char *name,int mode);
extern "C" __declspec(dllimport) int fasseqi(int str,int chan,int count);
extern "C" __declspec(dllimport) int fasseqo(int str,int chan,int count);
extern "C" __declspec(dllimport) int fasunlck(int str);
extern "C" __declspec(dllimport) int fasupd(int str);
extern "C" __declspec(dllimport) int fasupdi(int str);
#endif

// NIEUWE

extern "C" __declspec(dllimport) void KeyboardSet(int state, int immediate=FALSE);
extern "C" __declspec(dllimport) void BarcodeSet(int state, char *prefix, char *suffix, int AltSTX=-1);
extern "C" __declspec(dllimport) void conv_getal(double getal, char *s, int len, char points, int digits);
extern "C" __declspec(dllimport) BOOL TicketPrintNetwork(char *pPrintServer, char *pBuf, int len);  // Return TRUE als het prima afgedrukt is !
extern "C" __declspec(dllimport) BOOL MakeShare(CString LocalName, CString ShareName, CString UserName, CString PassWord, CString DomainName);  // RET TRUE of YES als het gelukt is !
extern "C" __declspec(dllimport) BOOL UseSerialScanner(int port, int baud, char parity, int databits, int stopbits);  // RET TRUE of YES als het gelukt is !
extern "C" __declspec(dllimport) void ExecJamaLink(char *ServerOrTerminal, char *ThisWindowName, int ThisWindowsNumber, char *ServerCallName, char *ServerWindowsName=NULL, void (*pExitRoutine)(int)=NULL);
extern "C" __declspec(dllimport) void SetProcessFileCallBack(void (*pProcessFileCallBack)(char *s));

/*
// WRKMNGR

extern "C" __declspec(dllimport) int wrkextra(int functie,int refnr_1,int volgnr_1,int refnr_2,int volgnr_2,int aantal);
extern "C" __declspec(dllimport) unsigned wrkdread(int refnr,int volgnr,char *addr);
extern "C" __declspec(dllimport) unsigned wrknread(int refnr,int volgnr,char *addr);
extern "C" __declspec(dllimport) int wrkwrite(int refnr,int volgnr,char *addr,unsigned len);
*/

// SCRPRTH

extern "C" __declspec(dllimport) char* GetPtrInfo();
extern "C" __declspec(dllimport) void (*pOvlExitRout)(short int nr);
extern "C" __declspec(dllimport) void scraddf(int fld,int v,int h,int attr);
extern "C" __declspec(dllimport) void scraddfield(int fld,int h,int v,int attr);
extern "C" __declspec(dllimport)  void scraddpicto(int nr, int fld, int h, int v, int hlen, int vlen, int PicNr, int ButNr, int ButCol, char *pAltText);
extern "C" __declspec(dllimport)  void scrchat(int fld, int att);
extern "C" __declspec(dllimport)  void scrclose(char ref);
extern "C" __declspec(dllimport) void scrclrf();
extern "C" __declspec(dllimport) void scrinq(int byte);
extern "C" __declspec(dllimport)  void screrr(int errnum);
extern "C" __declspec(dllimport) void scrfld(int fld,int str,int ele);
extern "C" __declspec(dllimport) int scrofld(int fld,int str,int ele,int len);
extern "C" __declspec(dllimport)  int scrget(int ref,int screen);
extern "C" __declspec(dllimport)  void scrifld(int fld,void *desc,void *inf);
extern "C" __declspec(dllimport)  int scropen(char ref,void *pname);
extern "C" __declspec(dllimport)  int scrupd(int fld,int funcbmap);
extern "C" __declspec(dllimport)  void scrwait();
extern "C" __declspec(dllimport)  void prtblank(int count);
extern "C" __declspec(dllimport)  void prtbuf(int numb);
extern "C" __declspec(dllimport)  int prtclose();
extern "C" __declspec(dllimport) void prtfld(int str,int elet,int len);
extern "C" __declspec(dllimport)  void prtifld(void *desc,void *inf,int len);
extern "C" __declspec(dllimport)  void prtinfo(int tab_ix, int mode);
extern "C" __declspec(dllimport)  int prtform(int type);
extern "C" __declspec(dllimport)  int prtline();
extern "C" __declspec(dllimport)  void prtnew();
extern "C" __declspec(dllimport)  int prtopen(int prtnr,short int *pform,int lpi,int charcnt,int mode,int headcnt);
extern "C" __declspec(dllimport)  int prtpage(int page);
extern "C" __declspec(dllimport)  void prttab(int tab_ix,int str,int elet,int blanks,int len);
extern "C" __declspec(dllimport)  void prtitab(int tab_ix, void *desc, void *inf,int blanks,int len);
extern "C" __declspec(dllimport)  void prttext(char *s);
extern "C" __declspec(dllimport)  void prttitle(int tab_ix,char *s,int mode);

#ifdef UseJMS 
extern "C" void sysclose();
extern "C" bool sysget(int pos,int len,void *d);
extern "C" void sysput(int pos,int len,void *s);
extern "C" int sysopen(void *ext,void *path);
extern "C" void sysfget(int pos,int len,void *d);
extern "C" void sysfput(int pos,int len,void *s);
extern "C" void sysflush();
#else
extern "C" __declspec(dllimport) void sysclose();
extern "C" __declspec(dllimport) bool sysget(int pos,int len,void *d);
extern "C" __declspec(dllimport) void sysput(int pos,int len,void *s);
extern "C" __declspec(dllimport) int sysopen(void *ext,void *path);
extern "C" __declspec(dllimport) void sysfget(int pos,int len,void *d);
extern "C" __declspec(dllimport) void sysfput(int pos,int len,void *s);
extern "C" __declspec(dllimport) void sysflush();
#endif

//Nieuwe
extern "C" __declspec(dllimport) void prtsetup(int number, char *UNC, int driver);
//	UNC : \\share\printer
//		   	IP-nr:9100
//				DNS-name:9100
//
//	driver :	0 -> Simple
//	    			1 -> iPrtA
//						2 -> iPrtB
//						3 -> iPrtC
//						4 -> iPrtD
//						5 -> Epson FX
//						6 -> Star 10
//						7 -> Nec Pxx
//						8 -> 
//	  				9 -> HP PCL3
//					 10 -> CBM-720 (Citizen)
//					 11 -> EPSON TICKETPRINTER
//					 12 -> iDP-560 (Citizen)

extern "C" __declspec(dllimport) short int errnum;
extern "C" __declspec(dllimport) short int scrnum;
extern "C" __declspec(dllimport) short int fldcurs;
extern "C" __declspec(dllimport) int ExtraSTOSize;
extern "C" __declspec(dllimport) bool Windows95;
extern "C" __declspec(dllimport) bool Windows98;
extern "C" __declspec(dllimport) bool WindowsME;
extern "C" __declspec(dllimport) bool WindowsNT;
extern "C" __declspec(dllimport) bool Windows2000;
extern "C" __declspec(dllimport) bool WindowsXP;
extern "C" __declspec(dllimport) bool WindowsVISTA;

extern "C" __declspec(dllimport) unsigned char PrintListNr;
extern "C" __declspec(dllimport) unsigned char PrinterNr;
extern "C" __declspec(dllimport) unsigned char PrintPaperNr;
extern "C" __declspec(dllimport) unsigned char PrintOverlayRef;
extern "C" __declspec(dllimport) unsigned short int PrintJobBits;
extern "C" __declspec(dllimport) short int  sys_ref;

#if defined(_WIN32_WCE)

extern int _fmode;
extern int errno;


#define O_RDONLY       0x0000  /* open for reading only */
#define O_WRONLY       0x0001  /* open for writing only */
#define O_RDWR         0x0002  /* open for reading and writing */
#define O_APPEND       0x0008  /* writes done at eof */
#define O_CREAT        0x0100  /* create and open file */
#define O_TRUNC        0x0200  /* open and truncate */
#define O_EXCL         0x0400  /* open only if file doesn't already exist */
#define O_TEXT         0x4000  /* file mode is text (translated) */
#define O_BINARY       0x8000  /* file mode is binary (untranslated) */

#define _S_IFMT         0170000         /* file type mask */
#define _S_IFDIR        0040000         /* directory */
#define _S_IFCHR        0020000         /* character special */
#define _S_IFIFO        0010000         /* pipe */
#define _S_IFREG        0100000         /* regular */
#define _S_IREAD        0000400         /* read permission, owner */
#define _S_IWRITE       0000200         /* write permission, owner */
#define _S_IEXEC        0000100         /* execute/search permission, owner */

extern "C" __declspec(dllexport) int _open(const char *filename, int oflag, int pmode);
extern "C" __declspec(dllexport) int _creat( const char *filename, int pmode);
extern "C" __declspec(dllexport) int _close(int handle);
extern "C" __declspec(dllexport) int _read(int handle, void *buffer, unsigned int count);
extern "C" __declspec(dllexport) int _write(int handle, const void *buffer, unsigned int count);
extern "C" __declspec(dllexport) long _lseek(int handle, long offset, int origin);
extern "C" __declspec(dllexport) int unlink( const char *filename);
extern "C" __declspec(dllexport) void _makepath(char *path, const char *drive, const char *dir, const char *fname, const char *ext);
extern "C" __declspec(dllexport) void _splitpath(const char *path, char *drive, char *dir, char *fname, char *ext);
/*
extern "C" __declspec(dllexport) BOOL DosDateTimeToFileTime(
  WORD wFatDate,          // 16-bit MS-DOS date
  WORD wFatTime,          // 16-bit MS-DOS time
  LPFILETIME lpFileTime   // file time
);
extern "C" __declspec(dllexport) BOOL FileTimeToDosDateTime(
  CONST FILETIME *lpFileTime, // file time
  LPWORD lpFatDate,           // MS-DOS date
  LPWORD lpFatTime            // MS-DOS time
);
*/
#endif 
