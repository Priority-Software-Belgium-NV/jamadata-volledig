/*32-01*/
typedef unsigned short uint16;
typedef short int int16;
int16 ovlcall();

/* gemeenschappelijke variabelen (215.dr1 en 2215.ovl) */
#if OVLE
extern struct{
#else
static struct{
#endif
  char data_begin;
  uint16 tab_read;
  int16 p_max_grp,p_max_lev,slev_used,sgrp_used,sklt_used,klt_st_used,safsp_used;
  int16 fl_afspraak;
  uint16 prx_klt,inq_klt,inq_merk,dt_p_beg,dt_p_end;
  char selp_bf[4][500],selp_des[40],*selp_fld;
  flag selp_use,selp_ge,selp_le;
  struct{
    uint16 rec;
    char select;
  } tb[500];
} seldata;
