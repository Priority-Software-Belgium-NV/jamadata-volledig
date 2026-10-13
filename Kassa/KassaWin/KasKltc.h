// KasKRTc.h: interface for the CKasKRT class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_KASKLT_H__BD2E7B9F_F526_4811_90CF_02C9EDE1ECAE__INCLUDED_)
#define AFX_KASKLT_H__BD2E7B9F_F526_4811_90CF_02C9EDE1ECAE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000



class CKasKLT  
{
public:
  CKasKLT();
  virtual ~CKasKLT();
  int SelectKlant(int type=0);
  void dsp_klantinfo(void);
  void sortkasklt(void);
  void op_kasklt(int line);
  bool FAddKlant(void);
  bool FGetKlant(int recnr_);
  bool FKillKlant(int recnr_);
  bool FUpdKlant(int recnr_);
  bool CKasKLT::get_klant(void);
  int klt_used;
  int KlantFileRef;
  void LoadKlantFile(void);
  bool UpdateKlantFiche(int recordnr_, int newklant_); 
  int  FindNextKlant(int pos_,int mode_,char *pfind_); // mode_ : 1=vooruit, -1=achteruit
  bool  CheckDubbeleKlant(int recnr_) ;
private:
  void kltline(char buf[]);
  static int CopyNettoChar(char *s, char *d, int len);
  int copy2JAMASCIstring(unsigned char *buf, int pos, int buflen, unsigned char *s, int len);
  int copystring(char *buf, int pos, int buflen, char *s, int len);
  static int kltcompare(char *p1, char *p2, int dumlen);
  int KltConRef;
  int brwsfirst;
  char SortKeyText[4][20];
  struct s_klant KlantFiche,kaskltnm;
  struct s_klantinfo *klantinfo, *p_klant;
  char *memory;
};
#endif // !defined(AFX_KASPLU_H__BD2E7B9F_F526_4811_90CF_02C9EDE1ECAE__INCLUDED_)
