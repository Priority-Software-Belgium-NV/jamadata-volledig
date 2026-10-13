// KasSYS.h: interface for the CKasSYS class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_KASSYS_H__BD2E7B9F_F526_4811_90CF_02C9EDE1ECAE__INCLUDED_)
#define AFX_KASSYS_H__BD2E7B9F_F526_4811_90CF_02C9EDE1ECAE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CKasSYS  
{
public:
	CKasSYS();
	virtual ~CKasSYS();
  static void rd_kassys(int line);
	static void cl_kassys();
  static void upd_sys(void);
  static void writmem(long lpos, void *s, unsigned len);
private:
  static void readmem(long lpos, void *s, unsigned len);
};

#endif // !defined(AFX_KASSYS_H__BD2E7B9F_F526_4811_90CF_02C9EDE1ECAE__INCLUDED_)

