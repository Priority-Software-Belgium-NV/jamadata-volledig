/*32-01*/
typedef unsigned short uint16;
typedef short int int16;
int16 ovlcall();

/* dr1 */
/* 0.04 22/06/01 */

#if PRINTEXEC
static full_chk()
{
  if((free-skip_off)<22){prtform(0);ft_hdr();}
}
#endif
 
#if PRINTEXEC
static ft_prt()
{
  int16 g,j,k,dd,mm,yy;
  flag prt_ok_;
  float aant_,epx_,lin_bd_,bd_afh_los_=0;
  BEDRAG bedrag_;

#if PR_CLOSED
  k=11;
#if !FLAG248
#if FLAG255
	k=7;
#else
  k=10;
#endif
#endif
  getsysprNew(k,form_dat,&mode,&prtnr);if(prt2pdf==1) PrintPaperNr=0; else if(prt2pdf==2) PrintPaperNr=255;
  if (prtopen(prtnr,form_dat,6,80,mode,0)!=0) {prt_error=YES;goto endsr;}
#endif

  scrget(1,6);scrupd(-3,0);
  PrintPdfNaam();
  ft_hdr();
#if EMPTYBLAD
  prttext("<t1u>Omschrijving<ut31u>Aantal<ut39u>Eh.prijs<ut48u>Acc/Eco<ut61u>Bedrag<ut69u>B%<ut73u>Leeggoed<u>");nextline();
#endif

/*  bonnummers afdrukken bij samengevoegde facturen
#if FLAG248 && BONFILE
  ram2stu(0); if(cmpstr("*Bon",ps_58_16,4)==0) goto skip_bnr;
  copy(s(8,1),buf_8x,fldlen(8,0));j=0;
  for(k=0;k<DIM8;k++){
    if(rec_8[k]==0) break;
    fasinit(8);*u(8,1)=rec_8[k];fasgeti(8);
    ins_lin(j);ram2stu(j);
    fasinit(58);
    mm=*u(8,2);
    copy("*Bon ",ps_58_16,5);stcli_d(ps_58_16+5,(long)mm,5,1);
    copy(" van ",ps_58_16+10,5);
    jddate(*u(8,8),&yy,&mm,&dd);
    stcli_d(ps_58_16+15,(long)dd,2,0);*(ps_58_16+17)='/';
    stcli_d(ps_58_16+18,(long)mm,2,0);*(ps_58_16+20)='/';
    stcli_d(ps_58_16+21,(long)yy,4,0);
    stu2ram(j++);
  }
  copy(buf_8x,s(8,1),fldlen(8,0));
skip_bnr:;
#endif
*/

#if FLAG248 & BONFILE & !MULTIBON
  fasinit(58);
  mm=*u(8,2);
  copy("Bon :",ps_58_16,5);stcli_d(ps_58_16+5,(long)mm,5,1);
  copy(" van ",ps_58_16+10,5);
  jddate(*u(8,8),&yy,&mm,&dd);
  stcli_d(ps_58_16+15,(long)dd,2,0);*(ps_58_16+17)='/';
  stcli_d(ps_58_16+18,(long)mm,2,0);*(ps_58_16+20)='/';
  stcli_d(ps_58_16+21,(long)yy,4,0);
  prt_1_lin();
#endif
  for(k=0;k<max_line;k++){
    ram2stu(k);
    if(test_line()){
#if DEF_INPUT | SPLITS_BON
      if(*pu_58_14==0 || *pf_58_31)/* niet gebruikte lijnen skippen */
#endif
      prt_1_lin();
#if FACT_PROMO
      if(*s(58,93)!='J' && *f(58,94)){
	fasinit(6);*pu_6_1=*pu_58_14;fasgeti(6);
	epx_=*f(58,94);
	fasinit(58); copy("PROMO",s(58,15),5);
	copy(s(6,154),s(58,16),25);
	*pf_58_20=-epx_; if(fldlen(58,23)) *f(58,23)=-epx_;
	prt_1_lin();
	ram2stu(k);
      }
#endif
#if PALET_KORTING
      if(fldlen(58,68) && *f(58,68)){
	bd_afh_los_+=*f(58,68);
	fasinit(6);*pu_6_1=*u(58,69);fasgeti(6);
	aant_=*pf_58_31;epx_=*f(58,67);lin_bd_=*f(58,68);
	fasinit(58);copy(s(6,3),ps_58_16,fldlen(58,16));
	*pf_58_31=aant_;*pf_58_20=epx_;
	if(fldlen(58,23)) *f(58,23)=epx_;
#if KORTTOT
	*pd_58_35=lin_bd_;
#endif
	prt_1_lin();ram2stu(k);
      }
#endif

#if AFHAALVERG
      if(fldlen(58,56) && *f(58,56)){
	bd_afh_los_+=*f(58,56);
	fasinit(6);*pu_6_1=*u(58,57);fasgeti(6);
	aant_=*pf_58_31;epx_=*f(58,55);lin_bd_=*f(58,56);
	fasinit(58);copy(s(6,3),ps_58_16,fldlen(58,16));
	*pf_58_31=aant_;*pf_58_20=epx_;
	if(fldlen(58,23)) *f(58,23)=epx_;
#if KORTTOT
	*pd_58_35=lin_bd_;
#endif
	prt_1_lin();ram2stu(k);
      }
#endif
#if LOSVERGOED
      if(fldlen(58,59) && *f(58,59)){
	bd_afh_los_+=*f(58,59);
	fasinit(6);*pu_6_1=*u(58,60);fasgeti(6);
	aant_=*pf_58_31;epx_=*f(58,58);lin_bd_=*f(58,59);
	fasinit(58);copy(s(6,3),ps_58_16,fldlen(58,16));
	*pf_58_31=aant_;*pf_58_20=epx_;
	if(fldlen(58,23)) *f(58,23)=epx_;
#if KORTTOT
	*pd_58_35=lin_bd_;
#endif
	prt_1_lin();ram2stu(k);
      }
#endif
    }
  }
#if PRTBDR
#if !FLAG248
  if(*s(8,33)!='J') goto punt06;
#endif
#if KORTTOT
  if(tot_kort){
    fasinit(58);copy("     Korting ",ps_58_16,30);
    *pd_58_35=-tot_kort-bd_afh_los_;
    prt_1_lin();
  }
#endif
#if DISKIMME
  if(disk_bd){
    fasinit(58);copy("     Discontobedrag",ps_58_16,30);
    *pd_58_35=-disk_bd;
    prt_1_lin();
  }
#endif
  punt06:;
#endif
  if((free-skip_off)<32 && (free-skip_off)>26) {nextline();nextline();}
  else skip_lin(32);
  prt_ok_=NO;
  for(k=0;k<4;k++){
    if(opm_foot[k][0]!='\0'){
      full_chk();
      prtifld(fm_us75,opm_foot[k],-1);nextline();
      prt_ok_=YES;
    }
  }
  if(prt_ok_)nextline();

  for(k=0;k<2;k++){
    if(fldlen(2,65+k) && *s(2,65+k)){
      prtfld(2,65+k,-1);
      nextline();
    }
  }

  for(k=0;k<2;k++){
    if(*u(8,19+k)){
      full_chk();
      prtifld(fm_us60,std_txt[*u(8,19+k)-1],-1);
      nextline();
    }
  }

#if !FLAG248
  if(*s(8,33)!='J') goto punt02;
#endif
  if(fldlen(8,21) && *f(8,21)){
    fasinit(58);
    for(k=0;k<4;k++){
      full_chk();
      prttext("<t9>");
      if(k==0){prttext("Factuurbedrag");
	*pd_58_35=alg_tot;
      }
      if(k==1){
	bedrag_=0;
	if(disk_bd && (*f(8,21)>(alg_tot/2))){
	  prttext("Disconto");bedrag_=disk_bd;
	  *pd_58_35=disk_bd;
	}
	else goto nok1;
      }
      if(k==2){prttext("Voorschot");
	*pd_58_35=-*f(8,21);
      }
      if(k==3){prttext("Nog te betalen");
	*pd_58_35=alg_tot-*f(8,21)-disk_bd;
      }
      prttext("<t28>");prtfld(58,35,-1);
      nextline();
      nok1:;
    }
  }
  punt02:;
					
#if DISCONTO && (FLAG248 | DISC244)
  if(len2_14 && disk_bd && *s(8,22)!='J'){
    full_chk();
    prtfld(2,14,-1);
    if(taaltxt==1){
      prttext(" % de remise, soit");
      prtifld(fm_obd,&disk_bd,-1); prttext(" ");
      prtifld(fm_os3,ft_munt,-1);
      prttext(" Å deduire ");nextline();
      prttext(" si vous payez avant le ");
      prtifld(fm_udat,&disk_dt,-1);
      nextline();
    }
    else{
      prttext(" % disconto, zijnde");
      prtifld(fm_obd,&disk_bd,-1); prttext(" ");
      prtifld(fm_os3,ft_munt,-1);
      prttext(" af te");nextline();
      prttext("trekken mits betaling voor : ");
      prtifld(fm_udat,&disk_dt,-1);
      nextline();
    }
  }
#endif

/*
#if FLAG244 | !BONFILE
  copy(fm_uf60,fmt,sizeof fm_uf60); fmt[2]=4; j=0;
  for(k=0;k<5;k++){
    if(cent[k].q_bak || cent[k].q_fles) {
      if(j==0) prttext("Aantal "); else prttext(", ");
      j++;
      prtifld(fm_os3,cent[k].eenh,-1);prttext(" :");
      prtifld(fmt,&cent[k].q_bak,-1);
      if(cent[k].q_fles){
	prttext("/");
	prtifld(fmt,&cent[k].q_fles,-1);
      }
    }
  }
  if(j) nextline();
#endif
*/

  skip_lin(20);

#if PRTBDR
#if !FLAG248
  if(*s(8,33)!='J') goto punt03;
#endif
  for(j=0;j<3;j++){
    prttext("<t3>");
    for(k=0;k<BTWDIM-BTWDIV+1;k++){
      if(btw_bas[k]){
	prtblank(2);
	if(j==0){prtblank(4);prtifld(fm_uf21_,&btw_pct[k],-1);
#if EMPTYBLAD
	  prttext(" % ");}
#else
	  prtblank(4);}
#endif
	else{
	  if(j==1) bedrag_=btw_bas[k];
	  if(j==2) bedrag_=btw_bd[k];
	  prtifld(fm_obd,&bedrag_,-1);prtblank(1);
	}
      }
    }
    if(j==0){
#if EMPTYBLAD
      prttext("<t50>Leeggoed:");
 #endif
      bedrag_=tot_leeg;
    }
    else if(j==1){
#if EMPTYBLAD
      prttext("<t50>Goederen:");
#endif
      bedrag_=belastbt;
    }
    else{
#if EMPTYBLAD
      prttext("<t52>B.T.W.:");
#endif
      bedrag_=btw_tot;
    }
    prttext(TABT);prtifld(fm_obd,&bedrag_,-1);
    nextline();nextline();
  }
#if EMPTYBLAD
#if !FLAG248
  prttext("Leeggoed terug :<t49>Subtotaal:");
#else
  prttext("<t48>Te betalen:");
#endif
#endif
  prttext("<t65>");prtifld(fm_os3,ft_munt,-1);
  prttext(TABT);prtifld(fm_obd,&alg_tot,-1);
  nextline();
  punt03:;
#if EMPTYBLAD & !FLAG248 & !FLAG255
  prttext("  Aantal    Prijs    Bedrag");nextline();
  balk();
#if !FLAG248
  if(*s(8,33)=='J')
#endif
    prttext("<t47>Leegg.terug:<t71>-");
  nextline();
  balk();nextline();
  balk();
#if !FLAG248
  if(*s(8,33)=='J')
#endif
    prttext("<t48>Te betalen:");
  nextline();
  balk();nextline();
  prttext("<t21>-------");nextline();
  prttext("<t21>.......");
#endif
#endif

#if FLAG244 & HANDTEKENING
  skip_lin(11);
  if(taaltxt==1) prttext("<t5>Pour accord et reÑu en bon Ötat");
  else prttext("<t5>Voor akkoord en ontvangst in goede staat");
  nextline();
  if(taaltxt==1) prttext("<t5>Signature");
  else prttext("<t5>Handtekening");
#endif


#if PRTBDR
#if !FLAG248
  if(*s(8,33)!='J') goto punt05;
#endif
#if EMPTYBLAD
  skip_lin(9);
  prttext("<t66>Vervaldatum");nextline();
#endif
  skip_lin(8);
  prttext("<t68>");
  if(*s(8,22)=='J') prttext(voldtxt[taaltxt]);
  else prtifld(fm_udat,&verv_dt,-1);
  punt05:;
#endif
  nextline();
#if FLAG248 & LETTERSC
  skip_lin(7);
  if(fldlen(2,40) && *s(2,40)=='J'){
    prttext("Waar en echt verklaard voor de som van :");nextline();
    letschr(alg_tot,3,76);
  }
#endif
  prtform(0);
  SpoolFileNr=prtclose();
  endsr:;
}
#endif

static balk()
{
  prttext("  ...... x ...... = .......");
}

#if PRINTEXEC
static ft_hdr()
{
  int16 g,j,k,stu_;
  char *ps;

  stu_=2;
#if FLAG255
  stu_=1;
#endif
  for(k=0;k<39;k++){
    if(*(s(stu_,3)+k)=='*') break;
  }
  if(k>=38) copy(s(stu_,3),nm_dehr,40);
  else {
    for(g=k+1;g<40;g++) if(*(s(stu_,3)+g)!=' ') break;
    if(g>39) copy(s(stu_,3),nm_dehr,40);
    else {
      for(j=39;j>=g;j--) if(*(s(stu_,3)+j)>' ') break;
      j=j-g+1;
      copy(s(stu_,3)+g,nm_dehr,j);
      nm_dehr[j++]=' ';
      g=40-j;if(g>(k-1)) g=k-1;
      copy(s(stu_,3),&nm_dehr[j],g);
      nm_dehr[j+g]='\0';
    }
  }

  free=999;
#if FIRMAPRT
  if(b2228){
    prttext("<t5><eb>");prtifld(fm_os79,&firma[0],30);prttext("<eb>");nextline();
    prttext("<t5>");prtifld(fm_os79,&firma[31],25);
    if(firma[firm[6].begpos]){
      prttext("<t40>");ps=firm[6].txt[taaltxt];prttext(ps);
      for(j=0;j<9;j++) if(*ps++=='\0') break;
      for(;j<9;j++) prtblank(1);prttext(": ");
      prtifld(fm_os79,&firma[firm[6].begpos],firm[6].lengte);
    }
    nextline();
    prttext("<t5>");prtifld(fm_os79,&firma[57],7);prtblank(2);
    prtifld(fm_os79,&firma[65],20);
    if(firma[firm[7].begpos]){
      prttext("<t40>");ps=firm[7].txt[taaltxt];prttext(ps);
      for(j=0;j<9;j++) if(*ps++=='\0') break;
      for(;j<9;j++) prtblank(1);prttext(": ");
      prtifld(fm_os79,&firma[firm[7].begpos],firm[7].lengte);
    }
    nextline();
    if(free-skip_off>66) nextline();
    for(k=0;k<10;k++){
      if(k==6 || k==7) continue;
      if(firma[firm[k].begpos]){
	prttext("<t5>");ps=firm[k].txt[taaltxt];prttext(ps);
	for(j=0;j<12;j++) if(*ps++=='\0') break;
	for(;j<12;j++) prtblank(1);prttext(": ");
	prtifld(fm_os79,&firma[firm[k].begpos],firm[k].lengte);
	nextline();
      }
    }
  }
#endif

  skip_lin(62);
#if USE_2ADR
  prttext("<t3>");prtfld(8,14,-1);
#endif
  prttext("<t47>");prtifld(fm_us40,nm_dehr,-1);nextline();
#if USE_2ADR
  prttext("<t3>");prtfld(8,15,-1);
#endif
  prttext("<t47>");prtfld(stu_,4,-1);nextline();
#if USE_2ADR
  prttext("<t3>");prtfld(8,16,-1);prtblank(1);prtfld(8,17,-1);
#endif
  prttext("<t47>");prtfld(stu_,5,-1);prtblank(1);prtfld(stu_,6,-1);nextline();
  if(fldlen(stu_,7)>0){
#if USE_2ADR
    prttext("<t3>");prtfld(8,18,-1);
#endif
    prttext("<t47>");prtfld(stu_,7,-1);
    nextline();
  }
  skip_lin(54);
  prttext("<eb>");
  if(alg_tot>=0) prttext(facttxt[taaltxt]); else prttext(credntxt[taaltxt]);
  prttext("<eb>");
#if EMPTYBLAD
  nextline();nextline();
#if FLAG255
  prttext("Referentie<t23>Telefax<t41>Lev.<t55>Nummer<t71>Datum");
#else
  prttext("Referentie<t23>BTW nr.<t41>Klant<t55>Nummer<t71>Datum");
#endif
  nextline();
#endif
  skip_lin(51);
  prtfld(8,25,-1);
#if FLAG255
  prttext("<t23>");prtfld(stu_,9,-1);
#else
  if(*l(stu_,10) && *l(stu_,10)!=999999999L){
    prttext("<t23>BE-0");prtfld(stu_,10,-1);
  }
  else if(fldlen(stu_,22)){
    prttext("<t21>");prtfld(stu_,22,-1);
  }
#endif
  prttext("<t41>");
  k=1; if(klcd) k=2;
  prtfld(stu_,k,-1);
  prttext("<t56>");
#if !FLAG248
  prtfld(8,2,-1);prttext("<t69>");prtfld(8,8,-1);
#else
  prtifld(fm_uu5,&ft_nr,-1);prttext("<t69>");prtifld(fm_udat,&ft_date,-1);
#endif
  nextline();
  skip_lin(47);
}
#endif
 
#if PRINTEXEC
static prt_1_lin()
{
  int16 j,k;
  flag pr_=NO;
 
  if(fldlen(58,42) && *d(58,42)==0) *d(58,42)=*pd_58_35;
  if(*pd_58_35 || *f(58,47)) pr_=YES;
#if AFHAALVERG | LOSVERGOED | PALETKORTING
  if(*pf_58_31 && *pf_58_20) pr_=YES;
#endif
  full_chk();
  prttext("<t1>");
  k=0;
  if(*ps_58_16=='*') k=1;
  prtifld(fm_us30,ps_58_16+k,30-k);
  if(k) prtblank(k);
  prttext("<t31>");
#if QNUL
  if(pr_)
#endif
    prtfld(58,31,-1);
#if PRTBDR | FLAG242
#if !FLAG248
  if(*s(8,33)!='J') goto punt01;
#endif
  k=20;if(fldlen(58,23)) k=23;
  prttext("<t37>");prtfld(58,k,-1);
  prttext("<t48>");prtfld(58,38,-1);
  if(pr_){
    *pf_58_21=*pf_58_21+.49;
    prttext("<t55>");prtfld(58,21,-1);
    *pf_58_21=*pf_58_21-.49;
  }
#endif
#if PRTBDR
  if(pr_){
    k=0; if(fldlen(58,42)) k=7;
    prttext("<t58>");prtfld(58,35+k,-1);
    prttext("<t69>");
    if(btw_kol) {prttext(" ");prtfld(58,33,-1);}
    else {k=*pf_58_24;prtifld(fm_uu2,&k,-1);}
    prttext("<t72>");
    if(*f(58,47)<= -100000.0) *f(58,47)=-*f(58,47);/* dan positief afdrukken */
    prtfld(58,47,-1);
    if(*f(58,47)<= -100000.0) *f(58,47)=-*f(58,47);
  }
  punt01:;
#endif
  nextline();
}
#endif
 
#if SPLITS_TICKET & FLAG244
static print_strook()
{
  int16 k;
  BEDRAG bedrag_;

  getsysprNew(14,form_dat,&mode,&prtnr);if(prt2pdf==1) PrintPaperNr=0; else if(prt2pdf==2) PrintPaperNr=255;
  if (prtopen(prtnr,form_dat,6,80,mode,0)!=0) {prt_error=YES;goto endsr;}
  free=999;

  nextline();
  prttext("<u>Aantal<u> <u>Omschrijving<u>           <u>Totaal<u> <u>Leegg.<u>");nextline();
  for(k=0;k<max_line;k++){
    ram2stu(k);
    if(test_line()){
      if(*u(58,14)==0 || *pf_58_31){/* niet gebruikte lijnen skippen */
	prtfld(58,31,-1);prtblank(1);
	prtfld(58,16,20);
	prtfld(58,35,-1);
	prtfld(58,47,-1);
	nextline();
      }
    }
  }
  nextline();
  prttext("<e>Goederen . :<e>");bedrag_=belastbt;prtifld(fm_obd,&bedrag_,-1);nextline();
  prttext("<e>BTW ...... :<e>");bedrag_=btw_tot;prtifld(fm_obd,&bedrag_,-1);nextline();
  prttext("<e>Leeggoed . :<e>");bedrag_=tot_leeg;prtifld(fm_obd,&bedrag_,-1);nextline();
  prttext("<e>Te betalen :<e>");bedrag_=alg_tot;prtifld(fm_obd,&bedrag_,-1);nextline();
  prtform(0);SpoolFileNr=prtclose();
  endsr:;
}
#endif
