char version[] = "KASPARM  01.03 12/03/19 (c) Jamadata Pelt";

#include "p:\jamacon\library\JamaConL.h"

#define FOREVER while(1)

#define   KASSIZE      15000

  
void bcopy(char *pfrom_,char *pto_,int len_);
void update(void);
int upd_firma(void);
int upd_reclame(void);
int upd_munt_vk_prt(void);
int upd_divers(void);
int upd_kaart(void);
int upd_eigentegoedbon(void);
int upd_promo(void);
int upd_factuur(void);
int upd_groep(int grp_beg_);

unsigned char fm_us75[]  = {7,0xC8,75,0,0,0,0};
unsigned char fm_us50[]  = {7,0xC8,50,0,0,0,0};
unsigned char fm_us40[]  = {7,0xC8,40,0,0,0,0};
unsigned char fm_us30[]  = {7,0xC8,30,0,0,0,0};
unsigned char fm_us22[]  = {7,0xC8,22,0,0,0,0};
unsigned char fm_us20[]  = {7,0xC8,20,0,0,0,0};
unsigned char fm_us10[]  = {7,0xC8,10,0,0,0,0};
unsigned char fm_us7[]   = {7,0xC8,7,0,0,0,0};
unsigned char fm_us5U[]  = {7,0xC8,5,0,1,0,0};
unsigned char fm_us1[]   = {7,0xC8,1,0,0,0,0};
unsigned char fm_us1U[]  = {7,0xC8,1,0,1,0,0};
unsigned char fm_us3U[]  = {7,0xC8,3,0,1,0,0};
unsigned char fm_os79[]  = {7,0x88,79,0,0,0,0};
unsigned char fm_os63[]  = {7,0x88,63,0,0,0,0};
unsigned char fm_os60[]  = {7,0x88,60,0,0,0,0};
unsigned char fm_os40[]  = {7,0x88,40,0,0,0,0};
unsigned char fm_os38[]  = {7,0x88,38,0,0,0,0};
unsigned char fm_os30[]  = {7,0x88,30,0,0,0,0};
unsigned char fm_os25[]  = {7,0x88,25,0,0,0,0};
unsigned char fm_os14[]  = {7,0x88,14,0,0,0,0};
unsigned char fm_os10[]  = {7,0x88,10,0,0,0,0};
unsigned char fm_os7[]   = {7,0x88,7,0,0,0,0};
unsigned char fm_os6[]   = {7,0x88,6,0,0,0,0};
unsigned char fm_os3[]   = {7,0x88,3,0,0,0,0};
unsigned char fm_os2[]   = {7,0x88,2,0,0,0,0};
unsigned char fm_uu5[]   = {6,0xD0,5,0,0x60,0};
unsigned char fm_uu4[]   = {6,0xD0,4,0,0x60,0};
unsigned char fm_uu3[]   = {6,0xD0,3,0,0x60,0};
unsigned char fm_uu2[]   = {6,0xD0,2,0,0x60,0};
unsigned char fm_uu2_[]  = {6,0xD0,2,0,0x00,0};
unsigned char fm_uu1[]   = {6,0xD0,1,0,0x60,0};
unsigned char fm_uu1_[]  = {6,0xD0,1,0,0x00,0};
unsigned char fm_ou3[]   = {6,0x90,3,0,0x60,0};
unsigned char fm_ou2[]   = {6,0x90,2,0,0x60,0};
unsigned char fm_ou1[]   = {6,0x90,1,0,0x60,0};
unsigned char fm_ui2[]   = {6,0xD1,2,0,0x60,0};
unsigned char fm_uf60[]  = {6,0xD4,6,0,0x60,0};
unsigned char fm_of6_0[] = {6,0x94,6,0,0x70,0};
unsigned char fm_of3_5[] = {6,0x94,3,5,0x70,0};
unsigned char fm_of4_2[] = {6,0x94,4,2,0x70,0};
unsigned char fm_of40_[] = {6,0x94,4,0,0x60,0};
unsigned char fm_of3_1[] = {6,0x94,3,1,0x70,0};
unsigned char fm_uf5_0[] = {6,0xD4,5,0,0x70,0};
unsigned char fm_uf4_1[] = {6,0xD4,4,1,0x70,0};
unsigned char fm_uf3_5[] = {6,0xD4,3,5,0x70,0};
unsigned char fm_uf2_2[] = {6,0xD4,2,2,0x70,0};
unsigned char fm_uf2_1[] = {6,0xD4,2,1,0x70,0};
unsigned char fm_uf21_[] = {6,0xD4,2,1,0x20,0};
unsigned char fm_ol8[]   = {6,0x93,8,0,0x70,0};
unsigned char fm_ul8[]   = {6,0xD3,8,0,0x70,0};
unsigned char fm_udat[]  = {4,0xC0,1,'/'};
unsigned char fm_odat[]  = {4,0x80,1,'/'};
unsigned char fm_ogrb[]  = {2,0xA8};
unsigned char fm_menu[]  = {7,0x48,1,0,9,0,0};
unsigned char fm_PGNW[] = {15,0xC8,1,0,1,0,'P','P','G','G','N','N','W','W',0};
unsigned char fm_123GN[]= {13,0xC8,1,0,1,0,'1','3','G','G','N','N',0};
unsigned char fm_uJN[]   = {11,0xC8,1,0,1,0,'J','J','N','N',0};
unsigned char fm_uJND[]  = {13,0xC8,1,0,1,0,'D','D','J','J','N','N',0};
unsigned char fm_uJNC[]  = {13,0xC8,1,0,1,0,'C','C','J','J','N','N',0};
unsigned char fm_uAT[]   = {9,0xC8,1,0,1,0,'A','T',0};
unsigned char fm_u04[]   = {9,0xC8,1,0,1,0,'0','4',0};
unsigned char fm_uu01[]  = {10,0xD0,1,0,0x60,0xC0,0,0,1,0};
unsigned char fm_uu04[]  = {10,0xD0,1,0,0x60,0xC0,0,0,4,0};
 
unsigned char sys_data[20000],sys_copy[20000];

void main(int argc, char *argv[])
{
  int len_;
  FILE *fstream_;
     
  if( (fstream_  = fopen("KASSYS.DAT", "rb" )) == NULL ) {
    printf("KASSYS.DAT -> File not found!\n");exit(1);
  }  
 
  len_=fread(sys_data, sizeof( char ), KASSIZE, fstream_);
  if(len_!=KASSIZE) {
    printf("KASSYS.DAT -> Incorrect file!\n");fclose(fstream_);exit(1); 
  }
  bcopy(sys_data,sys_copy,KASSIZE);
  
  moinit(false,1);
  SetProgramName("KeyConen - Kasparm");
  update();
 
  if( (fstream_  = fopen("KASSYS.DAT", "wb" )) == NULL ) {
    printf("Problems to write KASSYS.DAT!\n");exit(1);
  }  
 
  fwrite(sys_data, sizeof( char ), KASSIZE, fstream_);
  fclose(fstream_);
  _moexit(0);
}

void update(void)
{
  int pgm_nr_,key;

  scropen(2,"KasScr.scj");
  pgm_nr_=0;key=0;
  FOREVER{
    bcopy(sys_data,sys_copy,KASSIZE);
    if(key==101) break;
    if(key==102){ pgm_nr_--;if(pgm_nr_<0) pgm_nr_=0;}
    if(key==103 || key==108){pgm_nr_++; if(pgm_nr_>12) break;}

    switch(pgm_nr_){
      case 0 : key=upd_firma();break;
      case 1 : key=upd_reclame();break;
      case 2 : key=upd_munt_vk_prt();break;
			case 3 : key=upd_divers();break;
			case 4 : if(*(short int *)&sys_data[3198]) key=upd_eigentegoedbon(); break;	
      case 5 : if(sys_data[3648]!='\0') key=upd_kaart(); break;
      case 6 : key=upd_promo();break;
      case 7 : if(sys_data[3612]& 0x01 || sys_data[3612]& 0x02) key=upd_factuur(); break;
      case 8 : key=upd_groep(1);break;
      case 9 : key=upd_groep(21);break;
      case 10 : key=upd_groep(41);break;
      case 11: key=upd_groep(61);break;
      case 12: key=upd_groep(81);break;
      default: break;
    }
  } 
  scrclose(2);
}

int upd_firma(void)
{
  int curs=1,k,z,key;

  FOREVER{
    scrget(2,1000);z=1;
    for(k=0;k<10;k++) scrifld(z++,fm_us40,&sys_data[4096+k*41]);
    for(k=0;k<2;k++) scrifld(z++,fm_us40,&sys_data[4506+k*41]);
    key=scrupd(curs,0xA7);
    if(key==106) bcopy(sys_copy,sys_data,KASSIZE);
    return key;
  }
}
  
  
  
int upd_reclame(void)
{
  int curs=1,j,z,key,n;


  FOREVER{
    scrget(2,1001);z=1;
    for(n=0;n<10;n++){
      for(j=0;j<3;j++) scrifld(z++,fm_us20,&sys_data[9216+(j*11*22)+n*22]);
    }
    key=scrupd(curs,0xA7);
    if(key==106) bcopy(sys_copy,sys_data,KASSIZE);
    return key;
  }
}
  
    
int upd_munt_vk_prt(void)
{
  int curs=1,k,z,key,q_digits_[11],lade_nr_[11];
  char v_nam_[11][4],show_zero_[11],auto_lg_[3],ticketprinter_,bredeprinter_;
  float coeff_[11],afrond_[11];

  bcopy(&sys_data[3474],v_nam_[0],4);coeff_[0]=1;lade_nr_[0]=1;afrond_[0]=*(float *)&sys_data[3478];
  q_digits_[0]=sys_data[3482]&0x7F;
  if(sys_data[3482]&0x80) show_zero_[0]='J'; else show_zero_[0]='N';
  for(k=0;k<5;k++){
    bcopy(&sys_data[3098+k*10],v_nam_[1+k],4);
    coeff_[k+1]=*(float *)&sys_data[3102+k*10];
    afrond_[k+1]=*(float *)&sys_data[3484+k*10];
    lade_nr_[1+k]=sys_data[3106+k*10];
    q_digits_[1+k]=sys_data[3107+k*10]&0x7F; 
    if(sys_data[3107+k*10]&0x80) show_zero_[1+k]='J'; else show_zero_[1+k]='N';
  }

  for(k=0;k<3;k++){
    if(*(short unsigned *)&sys_data[3200+k*2]==1) auto_lg_[k]='J'; else auto_lg_[k]='N';
  }
  k=*(short int *)&sys_data[3712];
  if(k==-1) ticketprinter_='G';
  else if(k==3) ticketprinter_='E';
  else if (k == 5) ticketprinter_ = 'P';
  else if(k==11) ticketprinter_='W';
  else ticketprinter_='N'; // default N

  k=*(short int *)&sys_data[3710];
  if(k==-1) bredeprinter_='G';
  else if(k>=0 && k<=2) bredeprinter_='1'+k;
  else bredeprinter_='N'; // default N



  FOREVER{
redo:;
    scrget(2,1002);z=1;
    for(k=0;k<4;k++){ // slechts 3 VM-munten getoond 
      scrifld(z++,fm_us3U,v_nam_[k]);
      if(k==0){scrifld(z++,fm_of3_5,&coeff_[k]);scrifld(z++,fm_ou1,&lade_nr_[k]);}
      else{scrifld(z++,fm_uf3_5,&coeff_[k]);scrifld(z++,fm_uu1,&lade_nr_[k]);}
      scrifld(z++,fm_uf2_2,&afrond_[k]);
      scrifld(z++,fm_uu1,&q_digits_[k]);
      scrifld(z++,fm_uJN,&show_zero_[k]);
    }


    for(k=0;k<3;k++){ // voorlopig enkel verkoper A-> C (rest is reserve)
      scrifld(z++,fm_uJN,&auto_lg_[k]);
      scrifld(z++,fm_uu1_,&sys_data[3220+k*2]);
      scrifld(z++,fm_uu1_,&sys_data[3240+k*2]);
    }
    scrifld(z++,fm_PGNW,&ticketprinter_);
    scrifld(z++,fm_us50,&sys_data[14073]);
    scrifld(z++,fm_123GN,&bredeprinter_);
    scrifld(z++,fm_us50,&sys_data[14153]);

    key=scrupd(curs,0xA7);
    if(key==106) bcopy(sys_copy,sys_data,KASSIZE);
    else{ 
      if(ticketprinter_=='N' && sys_data[14073]=='\0') {
      	ConMessageBox(_T("Geen netwerkshare ingevuld !"),_T("Kassa parameters"),MB_OK |  MB_ICONEXCLAMATION |MB_ICONWARNING);
				curs=35; goto redo;
      }
      if(bredeprinter_=='N' && sys_data[14153]=='\0') {
      	ConMessageBox(_T("Geen netwerkshare ingevuld !"),_T("Kassa parameters"),MB_OK |  MB_ICONEXCLAMATION |MB_ICONWARNING);
				curs=37; goto redo;
      }

      bcopy(v_nam_[0],&sys_data[3474],4);*(float *)&sys_data[3478]=afrond_[0];
      sys_data[3482]=q_digits_[0];
      if(show_zero_[0]=='J') sys_data[3482]|=0x80; else sys_data[3482]&=0x7F;
      for(k=0;k<5;k++){
        bcopy(v_nam_[1+k],&sys_data[3098+k*10],4);
        *(float *)&sys_data[3102+k*10]=coeff_[1+k];
        *(float *)&sys_data[3484+k*10]=afrond_[1+k];
        sys_data[3106+k*10]=lade_nr_[1+k];
        sys_data[3107+k*10]=q_digits_[1+k];if(show_zero_[1+k]=='J') sys_data[3107+k*10]|=0x80; else sys_data[3107+k*10]&=0x7F;
      }
      for(k=0;k<3;k++){
        if(auto_lg_[k]=='J') *(short unsigned *)&sys_data[3200+k*2]=1;
				else *(short unsigned *)&sys_data[3200+k*2]=0;
      }
      if(ticketprinter_=='G') k=-1;
      else if(ticketprinter_=='E') k=3;
	  else if (ticketprinter_ == 'P') k = 5;
      else if(ticketprinter_=='W') k=11;
      else k=51; // default N
      *(short int *)&sys_data[3712]=k;
      if(bredeprinter_=='G') k=-1;
      else if(bredeprinter_>='1' && bredeprinter_<='3') k=bredeprinter_-'1';
      else k=52; // default N
      *(short int *)&sys_data[3710]=k;
    }
    return key;
  }
}
  
int upd_divers(void)
{
  int curs=1,z,key,k;
  char reset_ticket_, calc_btw_, lijn_afrond_, print_wrkbon_, print_ztotaal_, keyb_azerty_, groep_kleur_, promo_kleur_, keep_wrkbon_;
  float btw_afrond_;


  btw_afrond_=*(float *)&sys_data[3470];
	if(*(short unsigned *)&sys_data[4030]) lijn_afrond_='J'; else lijn_afrond_='N';
	if(sys_data[3534]=='\0') sys_data[3534]='J';
	if (sys_data[3535] == '\0') sys_data[3535] = 'N';
  if(*(short unsigned *)&sys_data[3360]==2) print_wrkbon_='D'; 
	else if(*(short unsigned *)&sys_data[3360]==1) print_wrkbon_='J'; 
	else print_wrkbon_='N';	
	if(*(short unsigned *)&sys_data[3606]) reset_ticket_='J'; else reset_ticket_='N';
  if(*(short unsigned *)&sys_data[3630]) calc_btw_='J'; else calc_btw_='N';
  if(*(short unsigned *)&sys_data[3404]) print_ztotaal_='J'; else print_ztotaal_='N';
  if(*(short unsigned *)&sys_data[3402]) keyb_azerty_='J'; else keyb_azerty_='N';
	if(*(short unsigned *)&sys_data[3428]) keep_wrkbon_='J'; else keep_wrkbon_='N';
  groep_kleur_=sys_data[3483]+'0';
	promo_kleur_=sys_data[3419]+'0';
  FOREVER{
redo:;
    scrget(2,1003);z=1;

    scrifld(z++,fm_uf2_2,&btw_afrond_);
    scrifld(z++,fm_uJN,&lijn_afrond_);
		scrifld(z++,fm_uJN,&calc_btw_);
		scrifld(z++,fm_uJNC,&sys_data[3534]);

    scrifld(z++,fm_uu5,&sys_data[3610]);// factuurnummer 
    scrifld(z++,fm_uu2,&sys_data[3708]);// aantal facturen  
    scrifld(z++,fm_uJN,&reset_ticket_);
		scrifld(z++,fm_uJND,&print_wrkbon_);
   	scrifld(z++,fm_uu04,&sys_data[3428]); // aantal schermen niet schrappen scrifld(z++,fm_uJN,&keep_wrkbon_);
   	scrifld(z++,fm_uJN,&print_ztotaal_);
    scrifld(z++,fm_uu4,&sys_data[3660]);// kode alarm 
		scrifld(z++,fm_uJN,&keyb_azerty_);
		scrifld(z++, fm_uJN, &sys_data[3535]); // geen promo bij horecaprijzen
	  scrifld(z++,fm_u04,&promo_kleur_);
		scrifld(z++,fm_u04,&groep_kleur_);
		for(k=0;k<3;k++) scrifld(z++,fm_us10,&sys_data[4040+k*10]); 
		scrifld(z++,fm_uJN,&sys_data[3415]);
    scrifld(z++,fm_uu3,&sys_data[3417]);// maximum bedrag voor aanrekening visa-kosten 
		scrifld(z++,fm_us5U,&sys_data[3406]); // plu kosten-artikel


    key=scrupd(curs,0xA7);
    if(key==106) bcopy(sys_copy,sys_data,KASSIZE);
    else {
      if(reset_ticket_=='J' && print_ztotaal_=='J') {
      	ConMessageBox(_T("Nummering MOET doorlopen indien Z-totaal !"),_T("Kassa parameters"),MB_OK |  MB_ICONEXCLAMATION |MB_ICONWARNING);
				curs=6; goto redo;
      }
 
      *(float *)&sys_data[3470]=btw_afrond_;
      if(lijn_afrond_=='J') *(short unsigned *)&sys_data[4030]=1; else *(short unsigned *)&sys_data[4030]=0;
      if(print_wrkbon_=='J') *(short unsigned *)&sys_data[3360]=1; 
			else if(print_wrkbon_=='D') *(short unsigned *)&sys_data[3360]=2; 
			else *(short unsigned *)&sys_data[3360]=0;
      if(reset_ticket_=='J') *(short unsigned *)&sys_data[3606]=1; else *(short unsigned *)&sys_data[3606]=0;
      if(calc_btw_=='J') *(short unsigned *)&sys_data[3630]=1; else *(short unsigned *)&sys_data[3630]=0;
			if(print_ztotaal_=='J') *(short unsigned *)&sys_data[3404]=1; else *(short unsigned *)&sys_data[3404]=0;
			if(keyb_azerty_=='J') *(short unsigned *)&sys_data[3402]=1; else *(short unsigned *)&sys_data[3402]=0;
			// if(keep_wrkbon_=='J') *(short unsigned *)&sys_data[3428]=1; else *(short unsigned *)&sys_data[3428]=0;
			if(groep_kleur_) sys_data[3483]=groep_kleur_-'0'; 
			if(promo_kleur_) sys_data[3419]=promo_kleur_-'0';
			
     }
    return key;
  }
}


int upd_kaart(void)
{
  int curs=1,k,z,key;
 
  
  FOREVER{
    scrget(2,1004);z=1;
    scrifld(z++,fm_uf5_0,&sys_data[3636]);
    scrifld(z++,fm_uf5_0,&sys_data[3640]);
    scrifld(z++,fm_uf5_0,&sys_data[3644]);
    for(k=0;k<5;k++){
      scrifld(z++,fm_us40,&sys_data[13868+k*41]);
    }
    key=scrupd(curs,0xA7);
    if(key==106) bcopy(sys_copy,sys_data,KASSIZE);
    return key;
  }
}

int upd_eigentegoedbon(void)
{
  int curs=1,k,z,key;
 
  
  FOREVER{
    scrget(2,1008);z=1;
 
    for(k=0;k<5;k++){
      scrifld(z++,fm_us40,&sys_data[14313+k*41]);
    }
    key=scrupd(curs,0xA7);
    if(key==106) bcopy(sys_copy,sys_data,KASSIZE);
    return key;
  }
}


int upd_promo(void)
{
  int curs=1,k,z,key,form_;
  float get1_,get2_,get3_,get4_;
 
  
  FOREVER{
redo:;
    scrget(2,1005);z=1;
    for(k=0;k<20;k++){
      scrifld(z++,fm_uu04,&sys_data[11776+k*25]);
      scrifld(z++,fm_uf4_1,&sys_data[11778+k*25]);
      scrifld(z++,fm_uf4_1,&sys_data[11782+k*25]);
      scrifld(z++,fm_uf4_1,&sys_data[11786+k*25]);
      scrifld(z++,fm_uf4_1,&sys_data[11790+k*25]);
    }
    key=scrupd(curs,0xA7);
    if(key==106) bcopy(sys_copy,sys_data,KASSIZE);
    for(k=0;k<20;k++){
      form_=*(unsigned *)&sys_data[11776+k*25];
      get1_=*(float *)&sys_data[11778+k*25];
      get2_=*(float *)&sys_data[11782+k*25];
      get3_=*(float *)&sys_data[11786+k*25];
      get4_=*(float *)&sys_data[11790+k*25];

      if(form_==1){ // korting%
				if(get1_==0) {errnum=38;curs=2+k*5; goto redo;}
      }
    
      if(form_==2){ // 2+1 gratis
				if(get1_==0) {errnum=38;curs=2+k*5; goto redo;}
				if(get2_==0) {errnum=38;curs=3+k*5; goto redo;}
      }
	
      if(form_==3){ // 2+1 gratis of korting%
				if(get1_==0 && get2_!=0) {errnum=38;curs=2+k*5; goto redo;}
				if(get2_==0 && get1_!=0) {errnum=38;curs=3+k*5; goto redo;}
				if(get3_==0 && get4_!=0) {errnum=38;curs=4+k*5; goto redo;}
				if(get4_==0 && get3_!=0) {errnum=38;curs=5+k*5; goto redo;}
      }
			if(form_==4){ // 2+1 aan 50%
    		if(get1_==0) {errnum=38;curs=2+k*5; goto redo;}
				if(get2_==0) {errnum=38;curs=3+k*5; goto redo;}
				if(get3_==0) {errnum=38;curs=4+k*5; goto redo;}
			}   
    }
    
    return key;
  }
}


int upd_factuur(void)
{
  int curs=1,k,z,key;
 
  
  FOREVER{
    scrget(2,1006);z=1;
    for(k=0;k<15;k++) scrifld(z++,fm_us50,&sys_data[12288+k*51]);// 5 lijnen dummy 
    for(k=0;k<3;k++) scrifld(z++,fm_us75,&sys_data[13308+k*81]); 
    scrifld(z++,fm_uu3,&sys_data[13551]);
    scrifld(z++,fm_uu3,&sys_data[13553]);
    key=scrupd(curs,0xA7);
    if(key==106) bcopy(sys_copy,sys_data,KASSIZE);
    return key;
  }
}


int upd_groep(int grp_beg_)
{
  int curs=1,k,z,key;
  char niet_op_krt_[100];


   
  for(k=grp_beg_;k<grp_beg_+20 && k<100;k++){
    if(sys_data[2912+k]&0x02 || k==99) niet_op_krt_[k]='J'; else niet_op_krt_[k]='N';
  }
  FOREVER{
    scrnum=0;scrget(2,1007);z=1;
    for(k=grp_beg_;k<grp_beg_+20 && k<100; k++){
      scrifld(z++, fm_ou2,(char *)&k);
      scrifld(z++,fm_us20,&sys_data[512+k*24]);
      scrifld(z++,fm_uf2_2,&sys_data[532+k*24]);
      scrifld(z++,fm_uAT,&sys_data[10752+k*10]);
      scrifld(z++,fm_uJN,&niet_op_krt_[k]);
      scrifld(z++,fm_us1U,&sys_data[10754+k*10]);
    }
    key=scrupd(curs,0xA7);
    if(key==106) bcopy(sys_copy,sys_data,KASSIZE);
    else{
      for(k=grp_beg_;k<grp_beg_+20 && k<100;k++){
        if(niet_op_krt_[k]=='J' || k==99) sys_data[2912+k]|=0x02; else sys_data[2912+k]&=0xFD;
      }
    } 
    return key;
  }
}

void bcopy(char *pfrom_,char *pto_,int len_)
{
  int k;

  for(k=0;k<len_;k++) *(pto_+k)=*(pfrom_+k);
}


// Historiek aanpassingen 

// 28/09/07 JG : kasscr.scR vervangen door kasscr.scJ
