/* gct_gen_mod_process_edgeset.c */
/* process_edgeset_waveform(){} */

#include <stdio.h>
#include <strings.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "ggm_includes.h"


int process_edgeset_waveform(FILE *fpwaves,int *fmtcnt,int *which,char *pin,int used_line[],int DSET,int CNT,char *tperiod,int *code0,int *code1){
   int i,j,eb,done,sl,ne,inc,en[4],en1[4],drv=0,cmp=0,wtlookup,edgelookup,edgecnt;
   char org1[100],org2[WF_EXPR_LEN],org3[WF_EXPR_LEN],org4[WF_EXPR_LEN];
   char hold,temp[1000];
   int c01,c02,c11,c12,c31,c32;
   char *ptr0,*ptr1,*ptr1C,*tptr,field[4][20][WF_EXPR_LEN],type[WF_EXPR_LEN],dupwarn[WF_EXPR_LEN];
   static char name[4][1000];
   strcpy(temp,acwaves->w[*which]);
   ne=0;/* FIXME: APS we should verify that the next edge is the same waveform name */
   for(i=0;i<4;i++) inc=en1[i]=en[i]=0;
   if (NULL!=strstr(temp,"Edge1")) {
      strcpy(name[0],temp);en1[0]=1;en[0]=0;ne=1;
      strcpy(temp,acwaves->w[*which+1]);
      if (NULL!=strstr(temp,"Edge2")) {
         strcpy(name[1],temp);en1[ne]=1;en[ne]=1;ne++;inc++;
         strcpy(temp,acwaves->w[*which+2]);
         if (NULL!=strstr(temp,"Edge3")) {
            strcpy(name[2],temp);en1[ne]=1;en[ne]=2;ne++;inc++;
            strcpy(temp,acwaves->w[*which+3]);
            if (NULL!=strstr(temp,"Edge4")) {
               strcpy(name[3],temp);en1[ne]=1;en[ne]=3;ne++;inc++;
               }
            }
         }
      }
   else if (NULL!=strstr(temp,"Edge2")) {/* use previous Edge1 */
      strcpy(name[1],temp);en1[1]=1;en[1]=1;ne=2;en1[0]=1;en[0]=0;
      strcpy(temp,acwaves->w[*which+1]);
      if (NULL!=strstr(temp,"Edge3")) {
         strcpy(name[2],temp);en1[ne]=1;en[ne]=2;ne++;inc++;
         strcpy(temp,acwaves->w[*which+2]);
         if (NULL!=strstr(temp,"Edge4")) {
            strcpy(name[3],temp);en1[ne]=1;en[ne]=3;ne++;inc++;
            }
         }
      }
   else if (NULL!=strstr(temp,"Edge3")) {/* use previous Edge1 & Edge2 */
      strcpy(name[2],temp);en1[1]=1;en[1]=1;ne=2;en1[0]=1;en[0]=0;en1[1]=1;en[1]=1;
      strcpy(temp,acwaves->w[*which+1]);/* inc will be one shy... */
      if (NULL!=strstr(temp,"Edge4")) {/* chances are we don't have an isolated Edge4 */
         strcpy(name[3],temp);en1[ne]=1;en[ne]=3;ne++;inc++;
         }
      }
   
   if (CNT!=0) sprintf(dupwarn,"_MULTIPLE_DEF%03d",CNT);
   else                 dupwarn[0]='\0';
   for (i=0;i<ne;i++) fprintf(fpwaves,"//ES:%s\n",name[en[i]]);
   fflush(fpwaves);
   for (i=0;i<ne;i++) {
      j=0;
      ptr0=strchr(name[en[i]],'(');
      if (ptr0==NULL) continue;
      hold=*ptr0;
      *ptr0='\0';
      strcpy(type,name[en[i]]);
      *ptr0=hold;
      ptr0++;
      eb=0;
      done=0;
      sl=strlen(name[en[i]]);
      while(!done) {
         ptr1=strchr(ptr0,',');
         ptr1C=strrchr(ptr0,')');
         if (NULL==ptr1 && NULL==ptr1C) {done=1;break;}
         if (ptr1==NULL && ptr1C!=NULL) ptr1=ptr1C;
         if (ptr1C<ptr1 && ptr1C!=NULL) {ptr1=ptr1C;done=1;} /* this is for the case when it finds a ',' after a ')'. e.g.: */
         if (ptr1==NULL) break; /* in case there is nothing useful */
         if (ptr1>name[en[i]]+sl) break; /* in case there is nothing useful */
         hold=*ptr1;
         *ptr1='\0';
         strcpy(field[en[i]][j],ptr0);
         *ptr1=hold;
         while (NULL!=(tptr=strstr(field[en[i]][j],"div"))) {
            *tptr=' ';    /* d */
            *(tptr+1)=' ';/* i */
            *(tptr+2)='/';/* v */
            }
         while (NULL!=(tptr=strstr(field[en[i]][j],"t["))) {
            *tptr=' ';    /* t */
            *(tptr+1)=' ';/* [ */
            }
         while (NULL!=(tptr=strstr(field[en[i]][j],"]"))) {
            *tptr=' ';    /* ] */
            }
         ptr0=ptr1+1;
         j++;
         if(done) break;
         }
      }
   c01='X';c02='.';c11='x';c12=',';
   if (DSET==0) *code0=0x01;
   if (DSET==1) *code1=0x01;
   if (DSET==3) *code0=*code1=0x01;
   for (i=ne-1;i>=0;i--) {/* run it backwards assuming the first edges dominate! */
      if (0==strcmp(field[en[i]][2],"DriveHigh") ||
          0==strcmp(field[en[i]][2],"DriveLow" ) ||
          0==strcmp(field[en[i]][2],"DriveData") ||
          0==strcmp(field[en[i]][2],"DriveComplement")) {
         c01='l';c02='h';c31=c11='L';c32=c12='H'; 
         if (DSET==0) *code0=0x02;
         if (DSET==1) *code1=0x02;
         if (DSET==3) *code0=*code1=0x02;
         }
      else if (0==strcmp(field[en[i]][2],"EdgeStrobeLow") ||
          0==strcmp(field[en[i]][2],"EdgeStrobeHigh") ||
          0==strcmp(field[en[i]][2],"EdgeStrobeData") ||
          0==strcmp(field[en[i]][2],"EdgeStrobeComplement")) {
         c31=c01='0';c32=c02='1';c11='o';c12='i';
         if (DSET==0) *code0=0x03;
         if (DSET==1) *code1=0x03;
         if (DSET==3) *code0=*code1=0x03;
         }
      else if (0==strcmp(field[en[i]][2],"EdgeStrobeZ") ) {/* but this should have one value... but we'll give it two */
         c01='f';c02='g';c11='F';c12='G';
         if (DSET==0) *code0=0x05;
         if (DSET==1) *code1=0x05;
         if (DSET==3) *code0=*code1=0x05;
         }
      else if (0==strcmp(field[en[i]][2],"StrobeLow") ||
          0==strcmp(field[en[i]][2],"StrobeHigh") ||
          0==strcmp(field[en[i]][2],"StrobeData") ||
          0==strcmp(field[en[i]][2],"StrobeComplement")) {
         c31=c01='w';c32=c02='W';c11='v';c12='V';
         if (DSET==0) *code0=0x04;
         if (DSET==1) *code1=0x04;
         if (DSET==3) *code0=*code1=0x04;
         }
      else if (0==strcmp(field[en[i]][2],"StrobeZ") ) { /* but this should have one value..., but we'll give it two */
         c31=c01='u';c32=c02='t';c11='U';c12='T';
         if (DSET==0) *code0=0x06;
         if (DSET==1) *code1=0x06;
         if (DSET==3) *code0=*code1=0x06;
         }
      else if (0==strcmp(field[en[i]][2],"StrobeOffLow") ||
          0==strcmp(field[en[i]][2],"StrobeOffHigh") ||
          0==strcmp(field[en[i]][2],"StrobeOffData") ||
          0==strcmp(field[en[i]][2],"StrobeOff") ||
          0==strcmp(field[en[i]][2],"StrobeOffComplement")) {
         c31=c01='e';c32=c02='E';c11='k';c12='K';
         if (DSET==0) *code0=0x08;
         if (DSET==1) *code1=0x08;
         if (DSET==3) *code0=*code1=0x08;
          }
      }/* DriveOFF&Compare Dominate to DSET0 when DSET==3, i.e. same Drives dominate to DSET1*/

   wtlookup=-2;
   cellinfo[cellcnt].filepos=ftell(fpwaves);
   cellinfo[cellcnt].actline=*which;
   strcpy(cellinfo[cellcnt].wftname,GCTNAME);
   strcpy(cellinfo[cellcnt].cellname,field[0][0]);
   strcpy(cellinfo[cellcnt].pin,pin);
   cellinfo[cellcnt].multidefnum=CNT;
   cellinfo[cellcnt].formatnum=wtlookup;
   edgecnt=0; for(i=0;i<4;i++) cellinfo[cellcnt].formats[i]=-1;
   fprintf(fpwaves,"Cell \"%s\" %c/%c %s_DSET%01d%s {\n\tData %c/%c;\n",pin,(DSET==0)?c01:(DSET==1)?c11:c31,(DSET==0)?c02:(DSET==1)?c12:c32,field[0][0],DSET,dupwarn,'0','1');
   drv=0;
   org1[0]=org2[0]=org3[0]=org4[0]='\0';
   for(i=0;i<ne;i++) find_origin(field[en[i]][0],org1,org2,org3,org4);
   for (i=0;i<ne;i++) {/* remap the formats: */
      if (NULL!=strstr(field[en[i]][2],"DriveHigh")) {
         edgelookup=(strstr(edgetypefull,"DriveHigh ")-edgetypefull);
         cellinfo[cellcnt].formats[edgecnt]=edgelookup;edgecnt++;
         if (drv==0) fprintf(fpwaves,"\tDrive {\n\t\tWaveform {\n");
         fprintf(fpwaves,"\t\t\tDriveHigh @\"%s%s\";\n",field[en[i]][3],(en[i]==0)?org1:(en[i]==1)?org2:(en[i]==2)?org3:(en[i]==3)?org4:"0.000ps");
         drv=1;
         }
      else if (NULL!=strstr(field[en[i]][2],"DriveLow")) {
         edgelookup=(strstr(edgetypefull,"DriveLow ")-edgetypefull);
         cellinfo[cellcnt].formats[edgecnt]=edgelookup;edgecnt++;
         if (drv==0) fprintf(fpwaves,"\tDrive {\n\t\tWaveform {\n");
         fprintf(fpwaves,"\t\t\tDriveLow @\"%s%s\";\n",field[en[i]][3],(en[i]==0)?org1:(en[i]==1)?org2:(en[i]==2)?org3:(en[i]==3)?org4:"0.000ps");
         drv=1;
         }
      else if (NULL!=strstr(field[en[i]][2],"DriveData")) {
         edgelookup=(strstr(edgetypefull,"DriveData ")-edgetypefull);
         cellinfo[cellcnt].formats[edgecnt]=edgelookup;edgecnt++;
         if (drv==0) fprintf(fpwaves,"\tDrive {\n\t\tWaveform {\n");
         fprintf(fpwaves,"\t\t\tDriveData @\"%s%s\";\n",field[en[i]][3],(en[i]==0)?org1:(en[i]==1)?org2:(en[i]==2)?org3:(en[i]==3)?org4:"0.000ps");
         drv=1;
         }
      else if (NULL!=strstr(field[en[i]][2],"DriveComplement")) {
         edgelookup=(strstr(edgetypefull,"DriveComplement ")-edgetypefull);
         cellinfo[cellcnt].formats[edgecnt]=edgelookup;edgecnt++;
         if (drv==0) fprintf(fpwaves,"\tDrive {\n\t\tWaveform {\n");
         fprintf(fpwaves,"\t\t\tDriveDataNot @\"%s%s\";\n",field[en[i]][3],(en[i]==0)?org1:(en[i]==1)?org2:(en[i]==2)?org3:(en[i]==3)?org4:"0.000ps");
         drv=1;
         }
      else if (NULL!=strstr(field[en[i]][2],"DriveOff")) {
         edgelookup=(strstr(edgetypefull,"DriveOff ")-edgetypefull);
         cellinfo[cellcnt].formats[edgecnt]=edgelookup;edgecnt++;
         if (drv==0) fprintf(fpwaves,"\tDrive {\n\t\tWaveform {\n");
         fprintf(fpwaves,"\t\t\tDriveOff @\"%s%s\";\n",field[en[i]][3],(en[i]==0)?org1:(en[i]==1)?org2:(en[i]==2)?org3:(en[i]==3)?org4:"0.000ps");
         drv=1;
         }
      }
   if (drv) fprintf(fpwaves,"\t\t}\n\t}\n");
   cmp=0;
   for (i=0;i<ne;i++) {/* remap the formats: */
     if (NULL!=strstr(field[en[i]][2],"EdgeStrobeHigh")) {
         edgelookup=(strstr(edgetypefull,"EdgeStrobeHigh ")-edgetypefull);
         cellinfo[cellcnt].formats[edgecnt]=edgelookup;edgecnt++;
        if (cmp==0) fprintf(fpwaves,"\tCompare {\n\t\tWaveform {\n");
        fprintf(fpwaves,"\t\t\tCompareHigh @\"%s%s\";\n",field[en[i]][3],(en[i]==0)?org1:(en[i]==1)?org2:(en[i]==2)?org3:(en[i]==3)?org4:"0.000ps");
        cmp=1;
        }
     else if (NULL!=strstr(field[en[i]][2],"EdgeStrobeLow")) {
         edgelookup=(strstr(edgetypefull,"EdgeStrobeLow ")-edgetypefull);
         cellinfo[cellcnt].formats[edgecnt]=edgelookup;edgecnt++;
        if (cmp==0) fprintf(fpwaves,"\tCompare {\n\t\tWaveform {\n");
        fprintf(fpwaves,"\t\t\tCompareLow @\"%s%s\";\n",field[en[i]][3],(en[i]==0)?org1:(en[i]==1)?org2:(en[i]==2)?org3:(en[i]==3)?org4:"0.000ps");
        cmp=1;
        }
     else if (NULL!=strstr(field[en[i]][2],"EdgeStrobeData")) {
         edgelookup=(strstr(edgetypefull,"EdgeStrobeData ")-edgetypefull);
         cellinfo[cellcnt].formats[edgecnt]=edgelookup;edgecnt++;
        if (cmp==0) fprintf(fpwaves,"\tCompare {\n\t\tWaveform {\n");
        fprintf(fpwaves,"\t\t\tCompareData @\"%s%s\";\n",field[en[i]][3],(en[i]==0)?org1:(en[i]==1)?org2:(en[i]==2)?org3:(en[i]==3)?org4:"0.000ps");
        cmp=1;
        }
     else if (NULL!=strstr(field[en[i]][2],"EdgeStrobeComplement")) {
         edgelookup=(strstr(edgetypefull,"EdgeStrobeComplement ")-edgetypefull);
         cellinfo[cellcnt].formats[edgecnt]=edgelookup;edgecnt++;
        if (cmp==0) fprintf(fpwaves,"\tCompare {\n\t\tWaveform {\n");
        fprintf(fpwaves,"\t\t\tCompareDataNot @\"%s%s\";\n",field[en[i]][3],(en[i]==0)?org1:(en[i]==1)?org2:(en[i]==2)?org3:(en[i]==3)?org4:"0.000ps");
        cmp=1;
        }
     else if (NULL!=strstr(field[en[i]][2],"EdgeStrobeZ")) {
         edgelookup=(strstr(edgetypefull,"EdgeStrobeZ ")-edgetypefull);
         cellinfo[cellcnt].formats[edgecnt]=edgelookup;edgecnt++;
        if (cmp==0) fprintf(fpwaves,"\tCompare {\n\t\tWaveform {\n");
        fprintf(fpwaves,"\t\t\tCompareFloat @\"%s%s\";\n",field[en[i]][3],(en[i]==0)?org1:(en[i]==1)?org2:(en[i]==2)?org3:(en[i]==3)?org4:"0.000ps");
        cmp=1;
        }
     else if (NULL!=strstr(field[en[i]][2],"StrobeComplement")) {
         edgelookup=(strstr(edgetypefull,"StrobeComplement ")-edgetypefull);
         cellinfo[cellcnt].formats[edgecnt]=edgelookup;edgecnt++;
        if (cmp==0) fprintf(fpwaves,"\tCompare {\n\t\tWaveform {\n");
        fprintf(fpwaves,"\t\t\tCompareOpenDataNot @\"%s%s\";\n",field[en[i]][3],(en[i]==0)?org1:(en[i]==1)?org2:(en[i]==2)?org3:(en[i]==3)?org4:"0.000ps");/* not sure envision can do this??? */
        cmp=1;
        }
     else if (NULL!=strstr(field[en[i]][2],"StrobeZ")) {
         edgelookup=(strstr(edgetypefull,"StrobeZ ")-edgetypefull);
         cellinfo[cellcnt].formats[edgecnt]=edgelookup;edgecnt++;
        if (cmp==0) fprintf(fpwaves,"\tCompare {\n\t\tWaveform {\n");
        fprintf(fpwaves,"\t\t\tCompareOpenFloat @\"%s%s\";\n",field[en[i]][3],(en[i]==0)?org1:(en[i]==1)?org2:(en[i]==2)?org3:(en[i]==3)?org4:"0.000ps");
        cmp=1;
        }
     else if (NULL!=strstr(field[en[i]][2],"StrobeLatch")) ;/* call this NULL for now */
     else if (NULL!=strstr(field[en[i]][2],"StrobeOffData") ||
              NULL!=strstr(field[en[i]][2],"StrobeOffComplement") ||
              NULL!=strstr(field[en[i]][2],"StrobeOffHigh") ||
              NULL!=strstr(field[en[i]][2],"StrobeOffLow") ||
              NULL!=strstr(field[en[i]][2],"StrobeOff") ) {
         edgelookup=(strstr(edgetypefull,"StrobeOff ")-edgetypefull);
         cellinfo[cellcnt].formats[edgecnt]=edgelookup;edgecnt++;
        if (cmp==0) fprintf(fpwaves,"\tCompare {\n\t\tWaveform {\n");
        fprintf(fpwaves,"\t\t\tCompareClose @\"%s%s\";\n",field[en[i]][3],(en[i]==0)?org1:(en[i]==1)?org2:(en[i]==2)?org3:(en[i]==3)?org4:"0.000ps");
        cmp=1;
        }
     else if (NULL!=strstr(field[en[i]][2],"StrobeHigh")) {
         edgelookup=(strstr(edgetypefull,"StrobeHigh ")-edgetypefull);
         cellinfo[cellcnt].formats[edgecnt]=edgelookup;edgecnt++;
        if (cmp==0) fprintf(fpwaves,"\tCompare {\n\t\tWaveform {\n");
        fprintf(fpwaves,"\t\t\tCompareOpenHigh @\"%s%s\";\n",field[en[i]][3],(en[i]==0)?org1:(en[i]==1)?org2:(en[i]==2)?org3:(en[i]==3)?org4:"0.000ps");
        cmp=1;
        }
     else if (NULL!=strstr(field[en[i]][2],"StrobeLow")) {
         edgelookup=(strstr(edgetypefull,"StrobeLow ")-edgetypefull);
         cellinfo[cellcnt].formats[edgecnt]=edgelookup;edgecnt++;
        if (cmp==0) fprintf(fpwaves,"\tCompare {\n\t\tWaveform {\n");
        fprintf(fpwaves,"\t\t\tCompareOpenLow @\"%s%s\";\n",field[en[i]][3],(en[i]==0)?org1:(en[i]==1)?org2:(en[i]==2)?org3:(en[i]==3)?org4:"0.000ps");
        cmp=1;
        }
     else if (NULL!=strstr(field[en[i]][2],"StrobeData")) {
         edgelookup=(strstr(edgetypefull,"StrobeData ")-edgetypefull);
         cellinfo[cellcnt].formats[edgecnt]=edgelookup;edgecnt++;
        if (cmp==0) fprintf(fpwaves,"\tCompare {\n\t\tWaveform {\n");
        fprintf(fpwaves,"\t\t\tCompareOpenData @\"%s%s\";\n",field[en[i]][3],(en[i]==0)?org1:(en[i]==1)?org2:(en[i]==2)?org3:(en[i]==3)?org4:"0.000ps");
        cmp=1;
        }
      }
   if (cmp) fprintf(fpwaves,"\t\t}\n\t}\n");
   fprintf(fpwaves,"}\n");
   *which+=inc;/* only inc++ if we had to read forward */
   cellcnt++;
   if (cellcnt>MAXCELLS) {fprintf(stderr,"Too many cells. source line[%d]\n",__LINE__);exit(1);}
   return(ne);
   }
