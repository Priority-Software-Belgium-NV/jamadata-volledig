// KasUSRc.h: interface for the CKasUSR class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_KASUSR_H__62239C14_442B_4A83_B84D_12FFEA2295F4__INCLUDED_)
#define AFX_KASUSR_H__62239C14_442B_4A83_B84D_12FFEA2295F4__INCLUDED_

#include "kaspluc.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CKasUSR  
{
public:
	char stuks_fl;
	double aantal;
	CKasPLU* pKasPLU;
	void SelKeyConen(int type, void *p);
	CKasUSR();
	virtual ~CKasUSR();

  void get_work(unsigned char *p_niveau, char erase);
  void put_work(unsigned char *p_niveau);
  int find_niveau(unsigned char *p_niveau);
  void cl_kasusr();
  void rd_kasusr(int line);
  int key_size;
  int key_used;
  int xpos;
  int ypos;
  struct s_vrk {
    double aantal;
    int plu_ix;
    char stuks_fl;
    char optie_fl;
  } vrk[MAX_VRK_USR];
  int vrkused;

private:
  int ConUsrRef;
  struct s_user_work {
    char key[MAX_NIVEAU];
    unsigned char tekst[TEKST_COUNT][8];
    char artcode[ARTCODE_LEN];
  } user_work [6][8];
  struct keys {
    char key[MAX_NIVEAU];
    unsigned char tekst[TEKST_COUNT][8];
    char artcode[ARTCODE_LEN];
  } *user_list;
  struct s_ExtraOpties {
    char artcode[ARTCODE_LEN];
    char key[MAX_NIVEAU];
  } ExtraOpties [EXTRA_OPTIES_COUNT];
  int ExtraOptiesUsed;
};

#endif // !defined(AFX_KASUSR_H__62239C14_442B_4A83_B84D_12FFEA2295F4__INCLUDED_)

