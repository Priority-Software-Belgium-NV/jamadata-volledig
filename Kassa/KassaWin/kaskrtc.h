// KasKRTc.h: interface for the CKasKRT class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_KASKRT_H__BD2E7B9F_F526_4811_90CF_02C9EDE1ECAE__INCLUDED_)
#define AFX_KASKRT_H__BD2E7B9F_F526_4811_90CF_02C9EDE1ECAE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CKasKRT  
{
public:
  CKasKRT();
  virtual ~CKasKRT();
  void sel_kltkrt(int type=0);
  void dsp_krtinfo(int type);
  void prtkrtfull(int count);
  int updkltkrt(void);
  void cl_kaskrt();
  void sortkltkrt(void);
  void op_kaskrt(int line);
  bool FGetKaart(int recnr_);
  bool FKillKaart(int recnr_);
  bool FUpdKaart(int recnr_);
	struct s_kaskrtnm KaartFiche;
  int krt_used;
  int  LoadBestBon(int recordnr_); // 0=false, 1=bestaande bon opgeladen, 2=nieuwe bon
  void ReloadKaartFile(void);
  int MakeAllBestXml(int inq_kltrec_); // 0 = geen selectie
  bool UpdateKaartFiche(int recordnr_); 
  void SortBestTab(int sortmode_); // 0 = klantnr, 1=datum
  int  FindNextKlant(int pos_,int only_bestelling_,int mode_); // mode_ : 1=vooruit, -1=achteruit
  bool HeeftBestelling(unsigned int klantnr_);
  void MenuBestelLijsten(void);
  void PrintArtikelCumuul(void);
  void PrintBstTitel(char *s, char *s2);
  void PrintLijstBestelTicketten(void);
  void PrintPickBestelTicketten(void);
  bool Ticket2Xml(void);
  void Xml2Ticket(void);
  bool AdjustTicketAndSaveToXml(void);
  bool MakeVoorschotTicket(void);

private:
  void krtline(char buf[]);
  static int CopyNettoChar(char *s, char *d, int len);
  int copy2JAMASCIstring(unsigned char *buf, int pos, int buflen, unsigned char *s, int len);
  int copystring(char *buf, int pos, int buflen, char *s, int len);
  static int krtcompare(char *p1, char *p2, int dumlen);
  void rd_kltkrt(int ix);
  int KrtConRef;
  int brwsfirst;
  int krtref;
  struct s_kaskrtnm kaskrtnm;
  struct s_krtinfo *krtinfo, *p_krt;
  char *memory;
};
   

#endif // !defined(AFX_KASPLU_H__BD2E7B9F_F526_4811_90CF_02C9EDE1ECAE__INCLUDED_)
