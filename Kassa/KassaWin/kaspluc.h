// KasPLU.h: interface for the CKasPLU class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_KASPLU_H__BD2E7B9F_F526_4811_90CF_02C9EDE1ECAE__INCLUDED_)
#define AFX_KASPLU_H__BD2E7B9F_F526_4811_90CF_02C9EDE1ECAE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CKasPLU  
{
public:
	int get_plu(int ix);
	CKasPLU();
	virtual ~CKasPLU();
	int MakeSpecSortTabel(char *pfind_);
  int search(char *search, int SortIx);
  int plu_req(char *ss, int len);
  void plu_upd(int ix);
  void cl_kasplu();
  void rd_kasplu(int line);
  int find_ean(char *ean, int CntFlesInBak=-1);
  int find_plu(char *plu);
  void anew_ean(char *artcode, char *ean_last, bool _stuksflag);
  static int prx_ix;
  static struct art_line art_info;
  int art_used, ext_used, ean_used, art_size;
  int prev_brwsfirst, prev_selected,prev_sortix;
  struct s_cln cln[MAXCLN];
  int clncount;
  static struct art_line *artikel;
  static struct _extra *extra;
  int *ean_tab;
  int *SortIndex[3];
	CString PromoPLUs;

private:
  int PluConRef;
  struct art_line *p_art;
	void CopyNettoChar(char *s, char *d, int len);
  static int _ecompare(char *s1,char *s2, int len);
  static int _ccompare(char *s1,char *s2, int dum);
  static int _ncompare(char *s1, char *s2, int dum);
  static int lcompare(char *s1, char *s2, int dum);
  int get_bcd(char *bcd, int _max);
  int get_string(char *to, int _max);
  double get_getal(void);
  int parse_extra(void);
  int parse_line(void);
  int _read_line(int fref);
  void Sort(int type);
	void AddPromoPlu(char *plu);
  int hex2dec(char byte);
  unsigned char _read_buf[350], *buf_large, last_buf[20];
  int parse_pos, buf_len, buf_used, buf_rdptr, last_ix;
};

#endif // !defined(AFX_KASPLU_H__BD2E7B9F_F526_4811_90CF_02C9EDE1ECAE__INCLUDED_)
