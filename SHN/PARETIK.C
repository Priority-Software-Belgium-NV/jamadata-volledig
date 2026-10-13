/*32-01*/
typedef unsigned short uint16;
typedef short int int16;
int16 ovlcall();

/* dr1 08/06/07 */
/* routine voor afdrukken etiketten */
 
static prt_etik(mode_)
int16 mode_;/* 1= blad moet niet perse vol zijn */
{
  int16 j,k,vt,hz,max_loop,n,p_code_;
  int16 form_dat[8],pr_mode,prtnr;
  float vp_,evp_;
  char str_[50];
									
  copy0("Artikel-etiketten (75/blad)",nm_etiket[0],30); if(tot_etik==0) goto endsr;
  getsysprNew(6,form_dat,&pr_mode,&prtnr);if(prt2pdf==1) PrintPaperNr=0; else if(prt2pdf==2) PrintPaperNr=255;
  if((errnum=prtopen(prtnr,form_dat,6,132,pr_mode,0))!=0) goto endsr;
  scrget(1,6);

  p_code_=71; if(p_fls_bak=='B') p_code_=70;
  n=0;
  while(free>=0 && (tot_etik>=75 || (mode_ && tot_etik>0))){
    if((errnum=prtopen(prtnr,form_dat,6,132,pr_mode,0))!=0) {free=-1;break;}
    mov(x_offset[mode],y_offset[mode]); push();
    for(vt=0;vt<15;vt++){
      if(vt) mov(0,213);
      for(hz=0;hz<5;hz++){
	if(skip_aant>0){skip_aant--;continue;}
	push();
	mov((472+0)*hz,0);
	while(n<DIM_TBE){
	  if(n<DIM_TBE && tbe[n].aantal>0){
	    zeros(str_,sizeof str_);j=0;
	    for(k=0;k<fldlen(6,p_code_);k++){/* enkel cijfers doorsturen */
	      if(tbe[n].eancode[k]=='\0') break;
	      if(tbe[n].eancode[k]>='0' && tbe[n].eancode[k]<='9') str_[j++]=tbe[n].eancode[k];
	    }
	    box(1,185,140,210,45);
	    block(10,185,140,210,45);

	    prtean(5,5,4,80,80,str_);
	    txt(6,5,105,str_,"");
	    zeros(str_,sizeof str_);
	    copy(tbe[n].code,str_,fldlen(6,2));
	    txt(6,200,105,str_,"");
	    zeros(str_,sizeof str_);
	    copy(tbe[n].omschr,str_,25);
	    cnv_char(str_,30);
	    txt(7,5,130,str_,"IB");
	    if(tbe[n].p_fls_bak=='F') vp_=tbe[n].vp_fles; else vp_=tbe[n].vp_prx;
	    k=prx2str(str_,vp_);
	    txt(10,195,180,str_,"B");
	    p_esign(10,195+txt_plen(10,str_),180);
	    tbe[n].aantal--;tot_etik--;break;
	  }
	  else n++;
	}
	pop();
      }
    }
    prt_string("\x0C");
  }
  max_loop=DIM_TBE;tot_etik=0;
  for(k=0;k<DIM_TBE;k++){
    if(max_loop>0) max_loop--; else break;
    if(tbe[k].aantal==0){/* lege plaatsen compressen */
      for(j=k;j<DIM_TBE-1;j++){copy((char *)&tbe[j+1],(char *)&tbe[j],sizeof tbe[0]);}
      zeros((char *)&tbe[DIM_TBE-1],sizeof tbe[0]);
      k--;
    }
    else tot_etik+=tbe[k].aantal;
  }
  if((errnum=prtopen(prtnr,form_dat,6,132,pr_mode,0))!=0) goto endsr;
  prtclose();
  endsr:;
}

#if 0
prt_rayon(mode_)/* rayon-etiketten van 3,39 cm op 7 cm */
int16 mode_;/* 1= blad moet niet perse vol zijn */
{
  int16 j,k,vt,hz,max_loop,n,p_code_;
  int16 form_dat[8],pr_mode,prtnr;
  char str_[50];
  long bd_;
  float evp_;
									
  copy0("Rayon-etiketten (24/blad)",nm_etiket[1],30);if(tot_etik==0) goto endsr;
  getsysprNew(6,form_dat,&pr_mode,&prtnr);if(prt2pdf==1) PrintPaperNr=0; else if(prt2pdf==2) PrintPaperNr=255;
  if((errnum=prtopen(prtnr,form_dat,6,132,pr_mode,0))!=0) goto endsr;
  scrget(1,6);

  p_code_=71; if(p_fls_bak=='B') p_code_=70;
  n=0;
  while(free>=0 && (tot_etik>=24 || (mode_ && tot_etik>0))){
    if((errnum=prtopen(prtnr,form_dat,6,132,pr_mode,0))!=0) {free=-1;break;}
    mov(x_offset[mode],y_offset[mode]); push();
    for(vt=0;vt<8;vt++){
      if(vt) mov(0,354+47);
      for(hz=0;hz<3;hz++){
	if(skip_aant>0){skip_aant--;continue;}
	push();
	j=60; if(hz==2) j=30;
	mov((775+j)*hz,0);
	while(n<DIM_TBE){
	  if(n<DIM_TBE && tbe[n].aantal>0){
	
	    box(1,0,5,700,345);
	    box(1,390,230,300,110);
	    block(10,390,230,300,110);
	
	    zeros(str_,sizeof str_);
	    copy(tbe[n].omschr,str_,20);
	    cnv_char(str_,30);
	    txt(14,5,80,str_,"IB");
	    zeros(str_,sizeof str_);
	    copy(tbe[n].opm,str_,20);
	    cnv_char(str_,30);
	    txt(14,45,145,str_,"B");
	    if(tbe[n].lg_bak){
	      k=prx2str(str_,tbe[n].lg_bak);
	      txt(8,20,200,"Leeggoed bak : ","");
	      txt(8,230,200,str_,"B");
	      p_esign(8,230+txt_plen(8,str_),200);
	    }
	    if(tbe[n].inhoud>0){                             /* prijs/liter */
	      evp_=tbe[n].vp_prx/tbe[n].inhoud;
	      evp_=valu_cnv("EUR","EUR",(double)(evp_),(double)0.01);
	      k=prx2str(str_,evp_);
	      txt(8,400,200,"Prijs/liter : ","");
	      txt(8,535,200,str_,"");
	      p_esign(8,535+txt_plen(8,str_),200);
	    }
	    else if(tbe[n].gewicht>0){                          /* prijs/kg */
	      evp_=tbe[n].vp_prx/tbe[n].gewicht;
	      evp_=valu_cnv("EUR","EUR",(double)(evp_),(double)0.01);
	      k=prx2str(str_,evp_);
	      txt(8,400,200,"Prijs/kg : ","");
	      txt(8,535,200,str_,"");
	      p_esign(8,535+txt_plen(8,str_),200);
	    }

	    if(tbe[n].lg_fles){
	      k=prx2str(str_,tbe[n].lg_fles);
	      txt(8,20,240,"Leeggoed stuk : ","");
	      txt(8,230,240,str_,"B");
	      p_esign(8,230+txt_plen(8,str_),240);
	    }

	    if(tbe[n].vp_fles){
	      k=prx2str(str_,tbe[n].vp_fles);
	      txt(10,20,305,"Prijs/stuk : ","");
	      txt(10,215,305,str_,"B");
	      p_esign(10,215+txt_plen(10,str_),305);
	    }
	    k=prx2str(str_,tbe[n].vp_prx);
	    txt(14,410,305,str_,"B");
	    p_esign(14,410+txt_plen(14,str_),305);
	
	    tbe[n].aantal--;tot_etik--;break;
	  }
	  else n++;
	}
	pop();
      }
    }
    prt_string("\x0C");
  }
  max_loop=DIM_TBE;tot_etik=0;
  for(k=0;k<DIM_TBE;k++){
    if(max_loop>0) max_loop--; else break;
    if(tbe[k].aantal==0){/* lege plaatsen compressen */
      for(j=k;j<DIM_TBE-1;j++){copy((char *)&tbe[j+1],(char *)&tbe[j],sizeof tbe[0]);}
      zeros((char *)&tbe[DIM_TBE-1],sizeof tbe[0]);
      k--;
    }
    else tot_etik+=tbe[k].aantal;
  }
  if((errnum=prtopen(prtnr,form_dat,6,132,pr_mode,0))!=0) goto endsr;
  prtclose();
  endsr:;
}
#endif

static prt_rayon(mode_)/* rayon-kaartjes van 3,1 cm op 9,3 cm */
int16 mode_;/* 1= blad moet niet perse vol zijn */
{
  int16 j,k,vt,hz,max_loop,n,p_code_,bpos_;
  int16 form_dat[8],pr_mode,prtnr,etiketmode_;
  char str_[50],kar_;
  float evp_;
									
  etiketmode_=NO;if(mode==ETIK && (sys4368 & 0x02)==0 && p_fls_bak=='F') etiketmode_=YES;

  copy0("Rayon-kaartjes (16/blad)",nm_etiket[1],30); if(tot_etik==0) goto endsr;
  getsysprNew(6,form_dat,&pr_mode,&prtnr);if(prt2pdf==1) PrintPaperNr=0; else if(prt2pdf==2) PrintPaperNr=255;
  if((errnum=prtopen(prtnr,form_dat,6,132,pr_mode,0))!=0) goto endsr;
  scrget(1,6);

  p_code_=71; if(p_fls_bak=='B') p_code_=70;
  n=0;
  while(free>=0 && (tot_etik>=16 || (mode_ && tot_etik>0))){
    if((errnum=prtopen(prtnr,form_dat,6,132,pr_mode,0))!=0) {free=-1;break;}
    mov(x_offset[mode],y_offset[mode]); push();
    for(vt=0;vt<8;vt++){
      if(vt) mov(0,354+47);
      for(hz=0;hz<2;hz++){
	if(skip_aant>0){skip_aant--;continue;}
	push();
	j=60; if(hz==2) j=30;
	if(hz==1) mov(1150,0);
	while(n<DIM_TBE){
	  if(n<DIM_TBE && tbe[n].aantal>0){
	    etiketmode_=NO;if(mode==ETIK && (sys4368 & 0x02)==0 && tbe[n].p_fls_bak=='F') etiketmode_=YES;
	    box(1,0,5,1100,370);
	    box(1,650,230,430,120);
	    block(10,650,230,430,120);
	
	    zeros(str_,sizeof str_);
	    copy(tbe[n].omschr,str_,30);
	    cnv_char(str_,30);
	    bpos_=cent_txt(16,5,1150,str_);
	    txt(16,bpos_,80,str_,"IB");
	    zeros(str_,sizeof str_);
	    copy(tbe[n].opm,str_,20);
	    cnv_char(str_,30);
	    bpos_=cent_txt(14,5,1150,str_);
//	    txt(14,bpos_,155,str_,"B");
	    fasinit(6);*u(6,1)=tbe[n].recnr;fasgeti(6);

	    txt(14,20,155,str_,"B");
	    p_code_=71; if(*s(6,71)=='\0') p_code_=70;
	    zeros(str_,sizeof str_);j=0;
	    for(k=0;k<fldlen(6,p_code_);k++){   /* enkel cijfers doorsturen */
	      kar_=*(s(6,p_code_)+k);
	      if(kar_=='\0') break;
	      if(kar_>='0' && kar_<='9') str_[20+j++]=kar_;
	    }
	    if(j>=11 && j<13){
	      copy("00000",str_,13-j);
	      copy(&str_[20],&str_[13-j],j);
	    }
	    else copy(&str_[20],str_,j);
	    prtean(670,110,4,80,80,str_);
      if((etiketmode_ && tbe[n].lg_fles) ||(etiketmode_==NO && tbe[n].lg_bak)){
	      k=prx2str(str_,tbe[n].lg_bak);
	      if(tbe[n].p_fls_bak=='B') txt(8,20,200,"Leeggoed bak : ","");
	      else txt(8,20,200,"Leeggoed : ","");
	      txt(8,230,200,str_,"B");
	      p_esign(8,230+txt_plen(8,str_),200);
	    }
	    if(tbe[n].inhoud>0){/* prijs/liter */
	      if(etiketmode_){
		evp_=tbe[n].vp_fles/tbe[n].inhoud;
		if(fldlen(6,31) && *f(6,31)) evp_*=*f(6,31);
	      }
	      else evp_=tbe[n].vp_prx/tbe[n].inhoud;
	      evp_=valu_cnv("EUR","EUR",(double)(evp_),(double)0.01);
	      k=prx2str(str_,evp_);
	      txt(8,720,220,"Prijs/liter : ","");
	      txt(8,900,220,str_,"");
	      p_esign(8,900+txt_plen(8,str_),220);
	    }
	    else if(tbe[n].gewicht>0){/* prijs/kg */
	      if(etiketmode_){
		evp_=tbe[n].vp_fles/tbe[n].gewicht;
		if(fldlen(6,31) && *f(6,31)) evp_*=*f(6,31);
	      }
	      else evp_=tbe[n].vp_prx/tbe[n].gewicht;
	      evp_=valu_cnv("EUR","EUR",(double)(evp_),(double)0.01);
	      k=prx2str(str_,evp_);
	      txt(8,720,220,"Prijs/kg : ","");
	      txt(8,900,220,str_,"");
	      p_esign(8,900+txt_plen(8,str_),220);
	    }

	    if(tbe[n].lg_fles && tbe[n].p_fls_bak!='F'){
	      k=prx2str(str_,tbe[n].lg_fles);
	      txt(8,20,240,"Leeggoed stuk : ","");
	      txt(8,230,240,str_,"B");
	      p_esign(8,230+txt_plen(8,str_),240);
	    }
	    if(tbe[n].vp_fles && tbe[n].p_fls_bak!='F'){
	      k=prx2str(str_,tbe[n].vp_fles);
	      txt(10,20,310,"Prijs/stuk : ","");
	      txt(14,210,310,str_,"B");
	      p_esign(14,210+txt_plen(14,str_),310);
	    }
	    if(etiketmode_) k=prx2str(str_,tbe[n].vp_fles);
	    else k=prx2str(str_,tbe[n].vp_prx);
	    txt(26,670,330,str_,"B");
	    p_esign(26,670+txt_plen(26,str_),330);

	    tbe[n].aantal--;tot_etik--;break;
	  }
	  else n++;
	}
	pop();
      }
    }
    prt_string("\x0C");
  }
  max_loop=DIM_TBE;tot_etik=0;
  for(k=0;k<DIM_TBE;k++){
    if(max_loop>0) max_loop--; else break;
    if(tbe[k].aantal==0){/* lege plaatsen compressen */
      for(j=k;j<DIM_TBE-1;j++){copy((char *)&tbe[j+1],(char *)&tbe[j],sizeof tbe[0]);}
      zeros((char *)&tbe[DIM_TBE-1],sizeof tbe[0]);
      k--;
    }
    else tot_etik+=tbe[k].aantal;
  }
  if((errnum=prtopen(prtnr,form_dat,6,132,pr_mode,0))!=0) goto endsr;
  prtclose();
  endsr:;
}
 
#if 0
prt_rayon(mode_)/* halve A4-bladen (2 per blad) */
int16 mode_;/* 1= blad moet niet perse vol zijn */
{
  int16 j,k,vt,hz,max_loop,n,p_code_;
  int16 form_dat[8],pr_mode,prtnr,bpos_;
  float vp_,evp_;
  char str_[50],kar_;
									
  copy0("Prijsaffiches (halve A4)",nm_etiket[1],30); if(tot_etik==0) goto endsr;
  getsysprNew(6,form_dat,&pr_mode,&prtnr);if(prt2pdf==1) PrintPaperNr=0; else if(prt2pdf==2) PrintPaperNr=255;
  if((errnum=prtopen(prtnr,form_dat,6,132,pr_mode,0))!=0) goto endsr;
  scrget(1,6);

  p_code_=71; if(p_fls_bak=='B') p_code_=70;
  n=0;
  while(free>=0 && (tot_etik>=2 || (mode_ && tot_etik>0))){
    if((errnum=prtopen(prtnr,form_dat,6,132,pr_mode,0))!=0) {free=-1;break;}
    mov(x_offset[mode],y_offset[mode]); push();
    for(vt=0;vt<2;vt++){
      if(vt) mov(0,1600+60);
      for(hz=0;hz<1;hz++){
	push();
	while(n<DIM_TBE){
	  if(n<DIM_TBE && tbe[n].aantal>0){
 
	    box(6,1,50,2250,1600);                       /* kader rond blad */
									
	    box(3,1250,1150,1000,500);/* kader rond prijzenblok */
	    block(10,1250,1150,1000,500);
	
	    zeros(str_,sizeof str_);
	    copy(tbe[n].omschr,str_,25);
	    cnv_char(str_,30);
	    bpos_=cent_txt(40,5,2250,str_);
	    txt(40,bpos_,350,str_,"IB");
	    zeros(str_,sizeof str_);
	    copy(tbe[n].opm,str_,20);
	    cnv_char(str_,30);
	    bpos_=cent_txt(40,5,2250,str_);
	    txt(40,bpos_,600,str_,"B");

#if 0
	    fasinit(6);*u(6,1)=tbe[n].recnr;fasgeti(6);
	    p_code_=71; if(*s(6,71)=='\0') p_code_=70;
	    zeros(str_,sizeof str_);j=0;
	    for(k=0;k<fldlen(6,p_code_);k++){/* enkel cijfers doorsturen */
	      kar_=*(s(6,p_code_)+k);
	      if(kar_=='\0') break;
	      if(kar_>='0' && kar_<='9') str_[20+j++]=kar_;
	    }
	    if(j>=11 && j<13){
	      copy("00000",str_,13-j);
	      copy(&str_[20],&str_[13-j],j);
	    }
	    else copy(&str_[20],str_,j);
	    prtean(1600,800,5,150,150,str_);
#endif
	    if(tbe[n].lg_bak){
	      k=prx2str(str_,tbe[n].lg_bak);
	      txt(20,1250,1100,"Leeggoed bak : ","");
	      txt(20,1850,1100,str_,"B");
	      p_esign(20,1850+txt_plen(20,str_),1100);
	    }
	    if(tbe[n].inhoud>0){/* prijs/liter */
	      evp_=tbe[n].vp_prx/tbe[n].inhoud;
	      evp_=valu_cnv("EUR","EUR",(double)(evp_),(double)0.01);
	      k=prx2str(str_,evp_);
	      txt(12,1750,1200,"Prijs/liter : ","");
	      txt(12,2000,1200,str_,"");
	      p_esign(12,2000+txt_plen(12,str_),1200);
	    }
	    else if(tbe[n].gewicht>0){/* prijs/kg */
	      evp_=tbe[n].vp_prx/tbe[n].gewicht;
	      evp_=valu_cnv("EUR","EUR",(double)(evp_),(double)0.01);
	      k=prx2str(str_,evp_);
	      txt(12,1750,1200,"Prijs/kg : ","");
	      txt(12,2000,1200,str_,"");
	      p_esign(12,2000+txt_plen(12,str_),1200);
	    }

	    if(tbe[n].lg_fles){
	      k=prx2str(str_,tbe[n].lg_fles);
	      txt(20,100,1100,"Leeggoed stuk : ","");
	      txt(20,750,1100,str_,"B");
	      p_esign(20,750+txt_plen(20,str_),1100);
	    }
	    if(tbe[n].vp_fles){
	      k=prx2str(str_,tbe[n].vp_fles);
	      txt(25,100,1500,"Prijs/stuk : ","");
	      txt(30,550,1500,str_,"B");
	      p_esign(30,550+txt_plen(30,str_),1500);
	    }
	    k=prx2str(str_,tbe[n].vp_prx);
	    txt(55,1250,1500,str_,"B");
	    p_esign(55,1250+txt_plen(55,str_),1500);

	    tbe[n].aantal--;tot_etik--;break;
	  }
	  else n++;
	}
	pop();
      }
    }
    prt_string("\x0C");
  }
  max_loop=DIM_TBE;tot_etik=0;
  for(k=0;k<DIM_TBE;k++){
    if(max_loop>0) max_loop--; else break;
    if(tbe[k].aantal==0){/* lege plaatsen compressen */
      for(j=k;j<DIM_TBE-1;j++){copy((char *)&tbe[j+1],(char *)&tbe[j],sizeof tbe[0]);}
      zeros((char *)&tbe[DIM_TBE-1],sizeof tbe[0]);
      k--;
    }
    else tot_etik+=tbe[k].aantal;
  }
  if((errnum=prtopen(prtnr,form_dat,6,132,pr_mode,0))!=0) goto endsr;
  prtclose();
  endsr:;
}
#endif
 
#if 0
prt_affiche(mode_)/* affiche in landscape  */
int16 mode_;/* 1= blad moet niet perse vol zijn */
{
  int16 j,k,vt,hz,max_loop,n,p_code_,bpos_;
  int16 form_dat[8],pr_mode,prtnr;
  char str_[50];
  float evp_;
									
  copy0("Prijsaffiches (A4 liggend)",nm_etiket[2],30);if(tot_etik==0) goto endsr;
  getsysprNew(6,form_dat,&pr_mode,&prtnr);if(prt2pdf==1) PrintPaperNr=0; else if(prt2pdf==2) PrintPaperNr=255;
  if((errnum=prtopen(prtnr,form_dat,6,132,pr_mode,0))!=0) goto endsr;
  scrget(1,6);

  p_code_=71; if(p_fls_bak=='B') p_code_=70;
  n=0;
  while(free>=0 && (tot_etik>=1 || (mode_ && tot_etik>0))){
    if((errnum=prtopen(prtnr,form_dat,6,132,pr_mode,0))!=0) {free=-1;break;}
    sel_orient('L');
    mov(x_offset[mode],y_offset[mode]); push();
    for(vt=0;vt<1;vt++){
      if(vt) mov(0,354+60);
      for(hz=0;hz<1;hz++){
	push();
	mov((885+160)*hz,0);
	while(n<DIM_TBE){
	  if(n<DIM_TBE && tbe[n].aantal>0){
	
	    box(6,1,1,3350,2200);
	    box(3,1800,1650,1550,550);
	    block(10,1800,1650,1550,550);
	
	    zeros(str_,sizeof str_);
	    copy(tbe[n].aff_hdr,str_,13);
	    cnv_char(str_,30);
	    bpos_=cent_txt(90,100,3350,str_);
	    txt(90,bpos_,410,str_,"B");
	
	    zeros(str_,sizeof str_);
	    copy(tbe[n].opm,str_,20);
	    cnv_char(str_,20);
	    bpos_=cent_txt(60,100,3350,str_);
	    txt(60,bpos_,800,str_,"BI");
	
	    zeros(str_,sizeof str_);
	    copy(tbe[n].promo_txt,str_,15);
	    cnv_char(str_,15);
	    bpos_=cent_txt(70,100,3350,str_);
	    txt(70,bpos_,1300,str_,"B");
	
	    if(tbe[n].lg_fles){
	      prx2str(str_,tbe[n].lg_fles);
	      txt(30,200,1550,"Leeggoed : ","");
	      txt(30,820,1550,str_,"B");
	      p_esign(30,820+txt_plen(30,str_),1550);
	    }
	    if(tbe[n].lg_bak){
	      prx2str(str_,tbe[n].lg_bak);
	      txt(30,2000,1550,"Leeggoed : ","");
	      txt(30,2550,1550,str_,"B");
	      p_esign(30,2550+txt_plen(30,str_),1550);
	    }
	    if(tbe[n].vp_fles){
	      prx2str(str_,tbe[n].vp_fles);
	      txt(30,200,2100,"Prijs/stuk : ","");
	      txt(60,580,2100,str_,"B");
	      p_esign(60,580+txt_plen(60,str_),2100);
	    }

	    if(tbe[n].inhoud>0){/* prijs/liter */
	      evp_=tbe[n].vp_prx/tbe[n].inhoud;
	      evp_=valu_cnv("EUR","EUR",(double)(evp_),(double)0.01);
	      k=prx2str(str_,evp_);
	      txt(15,2750,1700,"Prijs/liter : ","");
	      txt(15,3050,1700,str_,"");
	      p_esign(15,3050+txt_plen(15,str_),1700);
	    }
	    else if(tbe[n].gewicht>0){/* prijs/kg */
	      evp_=tbe[n].vp_prx/tbe[n].gewicht;
	      evp_=valu_cnv("EUR","EUR",(double)(evp_),(double)0.01);
	      k=prx2str(str_,evp_);
	      txt(15,2750,1700,"Prijs/kg : ","");
	      txt(15,3050,1700,str_,"");
	      p_esign(15,3050+txt_plen(15,str_),1700);
	    }
	    prx2str(str_,tbe[n].vp_prx);
	    txt(90,1800,2100,str_,"B");
	    p_esign(90,1800+txt_plen(90,str_),2100);

	    tbe[n].aantal--;tot_etik--;break;
	  }
	  else n++;
	}
	pop();
      }
    }
    prt_string("\x0C");
    sel_orient('P');
  }
  max_loop=DIM_TBE;tot_etik=0;
  for(k=0;k<DIM_TBE;k++){
    if(max_loop>0) max_loop--; else break;
    if(tbe[k].aantal==0){/* lege plaatsen compressen */
      for(j=k;j<DIM_TBE-1;j++){copy((char *)&tbe[j+1],(char *)&tbe[j],sizeof tbe[0]);}
      zeros((char *)&tbe[DIM_TBE-1],sizeof tbe[0]);
      k--;
    }
    else tot_etik+=tbe[k].aantal;
  }
  if((errnum=prtopen(prtnr,form_dat,6,132,pr_mode,0))!=0) goto endsr;
  prtclose();
  endsr:;
}
#endif
 
static prt_affiche(mode_)/* AFFICHE in PORTRAIT-mode */
int16 mode_;
{
  int16 j,k,vt,hz,max_loop,n,p_code_,bpos_;
  int16 form_dat[8],pr_mode,prtnr;
  char str_[50],kar_;
  float evp_;
									
  copy0("Prijsaffiches (A4 staand)",nm_etiket[2],30);if(tot_etik==0) goto endsr;
  getsysprNew(6,form_dat,&pr_mode,&prtnr);if(prt2pdf==1) PrintPaperNr=0; else if(prt2pdf==2) PrintPaperNr=255;
  if((errnum=prtopen(prtnr,form_dat,6,132,pr_mode,0))!=0) goto endsr;
  scrget(1,6);

  p_code_=71; if(p_fls_bak=='B') p_code_=70;
  n=0;
  while(free>=0 && (tot_etik>=1 || (mode_ && tot_etik>0))){
    if((errnum=prtopen(prtnr,form_dat,6,132,pr_mode,0))!=0) {free=-1;break;}
    mov(x_offset[mode],y_offset[mode]); push();
    while(n<DIM_TBE){
      if(n<DIM_TBE && tbe[n].aantal>0){
 
	box(6,1,50,2250,3300);/* kader rond blad */

	box(3,250,1900,1750,1000);/* kader rond prijzenblok */
	block(10,250,1900,1750,1000);
 
	zeros(str_,sizeof str_);/* 1-ste omschrijving */
	copy(tbe[n].aff_hdr,str_,13);
	cnv_char(str_,30);
	bpos_=cent_txt(60,100,2200,str_);
	txt(60,bpos_,610,str_,"B");
 
	zeros(str_,sizeof str_);/* 2-de deel omschrijving */
	copy(tbe[n].opm,str_,20);
	cnv_char(str_,20);
	bpos_=cent_txt(50,100,2200,str_);
	txt(50,bpos_,1000,str_,"BI");
	
	zeros(str_,sizeof str_);/* promo-tekst */
	copy(tbe[n].promo_txt,str_,15);
	cnv_char(str_,15);
	bpos_=cent_txt(50,100,2200,str_);
	txt(50,bpos_,1500,str_,"B");

	fasinit(6);*u(6,1)=tbe[n].recnr;fasgeti(6);
	p_code_=71; if(*s(6,71)=='\0') p_code_=70;
	zeros(str_,sizeof str_);j=0;
	for(k=0;k<fldlen(6,p_code_);k++){/* enkel cijfers doorsturen */
	  kar_=*(s(6,p_code_)+k);
	  if(kar_=='\0') break;
	  if(kar_>='0' && kar_<='9') str_[20+j++]=kar_;
	}
	if(j>=11 && j<13){
	  copy("00000",str_,13-j);
	  copy(&str_[20],&str_[13-j],j);
	}
	else copy(&str_[20],str_,j);
	prtean(1500,1700,5,150,150,str_);

 
	k=prx2str(str_,tbe[n].vp_prx);/* prijs per bak */
	txt(90,350,2350,str_,"B");
	p_esign(90,350+txt_plen(90,str_),2350);

	if(tbe[n].vp_fles){/* prijs per fles */
	  k=prx2str(str_,tbe[n].vp_fles);
	  txt(30,400,2700,"Prijs/stuk : ","");
	  txt(50,900,2700,str_,"B");
	  p_esign(50,900+txt_plen(50,str_),2700);
	}

	if(tbe[n].inhoud>0){/* prijs/liter */
	  evp_=tbe[n].vp_prx/tbe[n].inhoud;
	  evp_=valu_cnv("EUR","EUR",(double)(evp_),(double)0.01);
	  k=prx2str(str_,evp_);
	  txt(15,75,3050,"Prijs/liter : ","");
	  txt(15,400,3050,str_,"");
	  p_esign(15,400+txt_plen(15,str_),3050);
	}
	else if(tbe[n].gewicht>0){/* prijs/kg */
	  evp_=tbe[n].vp_prx/tbe[n].gewicht;
	  evp_=valu_cnv("EUR","EUR",(double)(evp_),(double)0.01);
	  k=prx2str(str_,evp_);
	  txt(15,75,3050,"Prijs/kg : ","");
	  txt(15,400,3050,str_,"");
	  p_esign(15,400+txt_plen(15,str_),3050);
	}
	if(tbe[n].lg_fles){/* leeggoed fles */
	  k=prx2str(str_,tbe[n].lg_fles);
	  txt(15,75,3200,"Leeggoed/stuk : ","");
	  txt(25,430,3200,str_,"B");
	  p_esign(25,430+txt_plen(25,str_),3200);
	}
	if(tbe[n].lg_bak){/* leeggoed bak */
	  k=prx2str(str_,tbe[n].lg_bak);
	  txt(15,1100,3200,"Leeggoed/bak : ","");
	  txt(25,1500,3200,str_,"B");
	  p_esign(25,1500+txt_plen(25,str_),3200);
	}
	tbe[n].aantal--;tot_etik--;break;
      }
      else n++;
    }
    pop();
    prt_string("\x0C");
  }
  max_loop=DIM_TBE;tot_etik=0;
  for(k=0;k<DIM_TBE;k++){
    if(max_loop>0) max_loop--; else break;
    if(tbe[k].aantal==0){/* lege plaatsen compressen */
      for(j=k;j<DIM_TBE-1;j++){copy((char *)&tbe[j+1],(char *)&tbe[j],sizeof tbe[0]);}
      zeros((char *)&tbe[DIM_TBE-1],sizeof tbe[0]);
      k--;
    }
    else tot_etik+=tbe[k].aantal;
  }
  if((errnum=prtopen(prtnr,form_dat,6,132,pr_mode,0))!=0) goto endsr;
  prtclose();
  endsr:;
}
