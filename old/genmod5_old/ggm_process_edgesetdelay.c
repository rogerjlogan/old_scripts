/* gct_gen_mod_process_edgesetdelay.c */
/* process_edgesetdelay_waveform(){} */

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

int process_edgesetdelay_waveform(FILE *fpwaves,int *fmtcnt,int *which,char *pin,int used_line[],int DSET,int CNT,char *tperiod,int *code0,int *code1){
   int i,j,eb,done,sl,ne,en[4],en1[4],drv=0,cmp=0,inc,wtlookup,edgecnt;
   char hold,temp[1000];
   int c01,c02,c11,c12,c31,c32;
   char org1[100],org2[100],org3[100],org4[100];
   char *ptr0,*ptr1,*ptr1C,*tptr,field[4][20][60],type[60],dupwarn[100];
   static char name[4][1000];
   strcpy(temp,acwaves->w[*which+0]);
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
   for (i=0;i<ne;i++) fprintf(fpwaves,"//ESD:%s\n",name[en[i]]);
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
/* need to search origin array also!!!!! */
   org1[0]=org2[0]=org3[0]=org4[0]='\0';
   find_origin(field[en[i]][0],org1,org2,org3,org4);
   c01='X';c02='.';c11='x';c12=',';
   if (DSET==0) *code0=0x01;
   if (DSET==1) *code1=0x01;
   if (DSET==3) *code0=*code1=0x01;

   for (i=ne-1;i>=0;i--) {/* assume that first edges dominate!!! same drives dominate to DSET1 */
      if (0==strcmp(field[en[i]][3],"DriveHigh") ||
          0==strcmp(field[en[i]][3],"DriveLow" ) ||
          0==strcmp(field[en[i]][3],"DriveData") ||
          0==strcmp(field[en[i]][3],"DriveComplement")) {
         c01='l';c02='h';c31=c11='L';c32=c12='H';
         if (DSET==0) *code0=0x02;
         if (DSET==1) *code1=0x02;
         if (DSET==3) *code0=*code1=0x02;
         }
      else if (0==strcmp(field[en[i]][3],"EdgeStrobeLow") ||
          0==strcmp(field[en[i]][3],"EdgeStrobeHigh") ||
          0==strcmp(field[en[i]][3],"EdgeStrobeData") ||
          0==strcmp(field[en[i]][3],"EdgeStrobeComplement")) {
         c31=c01='0';c32=c02='1';c11='o';c12='i';
         if (DSET==0) *code0=0x03;
         if (DSET==1) *code1=0x03;
         if (DSET==3) *code0=*code1=0x03;
         }
      else if (0==strcmp(field[en[i]][3],"EdgeStrobeZ") ) { /* but this should have one value... */
         c01='f';c02='g';c11='F';c12='G';
         if (DSET==0) *code0=0x05;
         if (DSET==1) *code1=0x05;
         if (DSET==3) *code0=*code1=0x05;
         }
      else if (0==strcmp(field[en[i]][3],"StrobeLow") ||
          0==strcmp(field[en[i]][3],"StrobeHigh") ||
          0==strcmp(field[en[i]][3],"StrobeData") ||
          0==strcmp(field[en[i]][3],"StrobeComplement")) {
         c31=c01='w';c32=c02='W';c11='v';c12='V';
         if (DSET==0) *code0=0x04;
         if (DSET==1) *code1=0x04;
         if (DSET==3) *code0=*code1=0x04;
         }
      else if (0==strcmp(field[en[i]][3],"StrobeZ") ) { /* but this should have one value... */
         c31=c01='u';c32=c02='t';c11='U';c12='T';
         if (DSET==0) *code0=0x06;
         if (DSET==1) *code1=0x06;
         if (DSET==3) *code0=*code1=0x06;
         }
      else if (0==strcmp(field[en[i]][3],"StrobeOffLow") ||
          0==strcmp(field[en[i]][3],"StrobeOffHigh") ||
          0==strcmp(field[en[i]][3],"StrobeOffData") ||
          0==strcmp(field[en[i]][3],"StrobeOffComplement")) {
         c31=c01='e';c32=c02='E';c11='k';c12='K';
         if (DSET==0) *code0=0x08;
         if (DSET==1) *code1=0x08;
         if (DSET==3) *code0=*code1=0x08;
         }
      }/* drives dominate to DSET1 if same, strobes and offs to DSET0 */

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
   for (i=0;i<ne;i++) {/* remap the formats: */
      if ((NULL!=strstr(field[en[i]][3],"DriveData") && NULL!=strstr(field[en[i]][7],"DriveData")) ||
          (NULL!=strstr(field[en[i]][3],"DriveLow") && NULL!=strstr(field[en[i]][7],"DriveHigh")) ) {
#define SPLITDRIVE 0x1000
         cellinfo[cellcnt].formats[edgecnt]=SPLITDRIVE;edgecnt++;
         if (drv==0) fprintf(fpwaves,"\tDrive {\n\t\tWaveform {\n");
         fprintf(fpwaves,"\t\t\tDriveLowIfZero @\"%s+%s*%s%s\";\n",field[en[i]][5],field[en[i]][6],tperiod,(en[i]==0)?org1:(en[i]==1)?org2:(en[i]==2)?org3:(en[i]==3)?org4:"0.000ps");
         fprintf(fpwaves,"\t\t\tDriveHighIfOne @\"%s+%s*%s%s\";\n",field[en[i]][9],field[en[i]][10],tperiod,(en[i]==0)?org1:(en[i]==1)?org2:(en[i]==2)?org3:(en[i]==3)?org4:"0.000ps");
         drv=1;
         }
      else if (NULL!=strstr(field[en[i]][3],"DriveComplement") ) {
#define SPLITDRIVECOMP 0x1001
         cellinfo[cellcnt].formats[edgecnt]=SPLITDRIVECOMP;edgecnt++;
         if (drv==0) fprintf(fpwaves,"\tDrive {\n\t\tWaveform {\n");
         fprintf(fpwaves,"\t\t\tDriveDataNot @\"%s+%s*%s%s\";\n",field[en[i]][5],field[en[i]][6],tperiod,(en[i]==0)?org1:(en[i]==1)?org2:(en[i]==2)?org3:(en[i]==3)?org4:"0.000ps");
         fprintf(fpwaves,"//FIXME:unsupported dual time\n");
         fprintf(fpwaves,"//\t\t\tDriveDataNot @\"%s+%s*%s%s\";\n",field[en[i]][9],field[en[i]][10],tperiod,(en[i]==0)?org1:(en[i]==1)?org2:(en[i]==2)?org3:(en[i]==3)?org4:"0.000ps");
         drv=1;
         }
      else if (NULL!=strstr(field[en[i]][3],"DriveOff") ) {
#define SPLITDRIVEOFF 0x1002
         cellinfo[cellcnt].formats[edgecnt]=SPLITDRIVEOFF;edgecnt++;
         if (drv==0) fprintf(fpwaves,"\tDrive {\n\t\tWaveform {\n");
         fprintf(fpwaves,"\t\t\tDriveOff @\"%s+%s*%s%s\";\n",field[en[i]][5],field[en[i]][6],tperiod,(en[i]==0)?org1:(en[i]==1)?org2:(en[i]==2)?org3:(en[i]==3)?org4:"0.000ps");
         fprintf(fpwaves,"//FIXME:unsupported dual time\n");
         fprintf(fpwaves,"//\t\t\tDriveOff @\"%s+%s*%s%s\";\n",field[en[i]][9],field[en[i]][10],tperiod,(en[i]==0)?org1:(en[i]==1)?org2:(en[i]==2)?org3:(en[i]==3)?org4:"0.000ps");
         drv=1;
         }
      }
   if (drv) fprintf(fpwaves,"\t\t}\n\t}\n");
   cmp=0;
   for (i=0;i<ne;i++) {/* remap the formats: */
     if ((NULL!=strstr(field[en[i]][3],"EdgeStrobeData") && NULL!=strstr(field[en[i]][7],"EdgeStrobeData")) ||
         (NULL!=strstr(field[en[i]][3],"EdgeStrobeLow") && NULL!=strstr(field[en[i]][7],"EdgeStrobeHigh")) ) {
#define SPLITEDGECOMPARE 0x1003
         cellinfo[cellcnt].formats[edgecnt]=SPLITEDGECOMPARE;edgecnt++;
        if (cmp==0) fprintf(fpwaves,"\tCompare {\n\t\tWaveform {\n");
        fprintf(fpwaves,"\t\t\tCompareLowIfZero @\"%s+%s*%s%s\";\n",field[en[i]][5],field[en[i]][6],tperiod,(en[i]==0)?org1:(en[i]==1)?org2:(en[i]==2)?org3:(en[i]==3)?org4:"0.000ps");
        fprintf(fpwaves,"\t\t\tCompareHighIfOne @\"%s+%s*%s%s\";\n",field[en[i]][9],field[en[i]][10],tperiod,(en[i]==0)?org1:(en[i]==1)?org2:(en[i]==2)?org3:(en[i]==3)?org4:"0.000ps");
        cmp=1;
        }
     else if (NULL!=strstr(field[en[i]][3],"EdgeStrobeComplement")) {
#define SPLITWINDOWCOMPARE 0x1004
         cellinfo[cellcnt].formats[edgecnt]=SPLITWINDOWCOMPARE;edgecnt++;
        if (cmp==0) fprintf(fpwaves,"\tCompare {\n\t\tWaveform {\n");
        fprintf(fpwaves,"\t\t\tCompareDataNot @\"%s+%s*%s%s\";\n",field[en[i]][5],field[en[i]][6],tperiod,(en[i]==0)?org1:(en[i]==1)?org2:(en[i]==2)?org3:(en[i]==3)?org4:"0.000ps");
        fprintf(fpwaves,"//FIXME:unsupported dual time\n");
        fprintf(fpwaves,"//\t\t\tCompareDataNot @\"%s+%s*%s%s\";\n",field[en[i]][9],field[en[i]][10],tperiod,(en[i]==0)?org1:(en[i]==1)?org2:(en[i]==2)?org3:(en[i]==3)?org4:"0.000ps");
        cmp=1;
        }
     else if (NULL!=strstr(field[en[i]][3],"EdgeStrobeZ")) {
#define SPLITEDGECOMPAREZ 0x1005
         cellinfo[cellcnt].formats[edgecnt]=SPLITEDGECOMPAREZ;edgecnt++;
        if (cmp==0) fprintf(fpwaves,"\tCompare {\n\t\tWaveform {\n");
        fprintf(fpwaves,"\t\t\tCompareFloat @\"%s+%s*%s%s\";\n",field[en[i]][5],field[en[i]][6],tperiod,(en[i]==0)?org1:(en[i]==1)?org2:(en[i]==2)?org3:(en[i]==3)?org4:"0.000ps");
        fprintf(fpwaves,"//FIXME:unsupported dual time\n");
        fprintf(fpwaves,"//\t\t\tCompareFloat @\"%s+%s*%s%s\";\n",field[en[i]][9],field[en[i]][10],tperiod,(en[i]==0)?org1:(en[i]==1)?org2:(en[i]==2)?org3:(en[i]==3)?org4:"0.000ps");
        cmp=1;
        }
     else if (NULL!=strstr(field[en[i]][3],"StrobeComplement")) {
#define SPLITCOMPARECOMPLEMENT 0x1006
         cellinfo[cellcnt].formats[edgecnt]=SPLITCOMPARECOMPLEMENT;edgecnt++;
        if (cmp==0) fprintf(fpwaves,"\tCompare {\n\t\tWaveform {\n");
        fprintf(fpwaves,"\t\t\tCompareOpenDataNot @\"%s+%s*%s%s\";\n",field[en[i]][5],field[en[i]][6],tperiod,(en[i]==0)?org1:(en[i]==1)?org2:(en[i]==2)?org3:(en[i]==3)?org4:"0.000ps");
        fprintf(fpwaves,"//FIXME:unsupported dual time\n");
        fprintf(fpwaves,"//\t\t\tCompareOpenDataNot @\"%s+%s*%s%s\";\n",field[en[i]][9],field[en[i]][10],tperiod,(en[i]==0)?org1:(en[i]==1)?org2:(en[i]==2)?org3:(en[i]==3)?org4:"0.000ps");
        cmp=1;
        }
     else if (NULL!=strstr(field[en[i]][3],"StrobeZ")) {
#define SPLITCOMPAREZ 0x1007
         cellinfo[cellcnt].formats[edgecnt]=SPLITCOMPAREZ;edgecnt++;
        if (cmp==0) fprintf(fpwaves,"\tCompare {\n\t\tWaveform {\n");
        fprintf(fpwaves,"\t\t\tCompareOpenFloat @\"%s+%s*%s%s\";\n",field[en[i]][5],field[en[i]][6],tperiod,(en[i]==0)?org1:(en[i]==1)?org2:(en[i]==2)?org3:(en[i]==3)?org4:"0.000ps");
        fprintf(fpwaves,"//FIXME:unsupported dual time\n");
        fprintf(fpwaves,"//\t\t\tCompareOpenFloat @\"%s+%s*%s%s\";\n",field[en[i]][9],field[en[i]][10],tperiod,(en[i]==0)?org1:(en[i]==1)?org2:(en[i]==2)?org3:(en[i]==3)?org4:"0.000ps");
        cmp=1;
        }
     else if (NULL!=strstr(field[en[i]][3],"StrobeLatch")) ;/* call this NULL for now */
     else if (NULL!=strstr(field[en[i]][3],"StrobeOffData")||
              NULL!=strstr(field[en[i]][3],"StrobeOffComplement")||
              NULL!=strstr(field[en[i]][3],"StrobeOffHigh")||
              NULL!=strstr(field[en[i]][3],"StrobeOffLow")||
              NULL!=strstr(field[en[i]][3],"StrobeOff")) {
#define SPLITCOMPAREOFF 0x1008
         cellinfo[cellcnt].formats[edgecnt]=SPLITCOMPAREOFF;edgecnt++;
        if (cmp==0) fprintf(fpwaves,"\tCompare {\n\t\tWaveform {\n");
        fprintf(fpwaves,"\t\t\tCompareClose @\"%s+%s*%s%s\";\n",field[en[i]][5],field[en[i]][6],tperiod,(en[i]==0)?org1:(en[i]==1)?org2:(en[i]==2)?org3:(en[i]==3)?org4:"0.000ps");
        fprintf(fpwaves,"//FIXME:unsupported dual time...!\n");
        fprintf(fpwaves,"//\t\t\tCompareClose @\"%s+%s*%s%s\";\n",field[en[i]][9],field[en[i]][10],tperiod,(en[i]==0)?org1:(en[i]==1)?org2:(en[i]==2)?org3:(en[i]==3)?org4:"0.000ps");
        cmp=1;
        }
     else if (NULL!=strstr(field[en[i]][3],"StrobeHigh")) {
#define SPLITCOMPAREHIGH 0x1009
         cellinfo[cellcnt].formats[edgecnt]=SPLITCOMPAREHIGH;edgecnt++;
        if (cmp==0) fprintf(fpwaves,"\tCompare {\n\t\tWaveform {\n");
        fprintf(fpwaves,"\t\t\tCompareOpenHigh @\"%s+%s*%s%s\";\n",field[en[i]][5],field[en[i]][6],tperiod,(en[i]==0)?org1:(en[i]==1)?org2:(en[i]==2)?org3:(en[i]==3)?org4:"0.000ps");
        fprintf(fpwaves,"//FIXME:unsupported dual time...!\n");
        fprintf(fpwaves,"//\t\t\tCompareOpenHigh @\"%s+%s*%s%s\";\n",field[en[i]][9],field[en[i]][10],tperiod,(en[i]==0)?org1:(en[i]==1)?org2:(en[i]==2)?org3:(en[i]==3)?org4:"0.000ps");
        cmp=1;
        }
     else if (NULL!=strstr(field[en[i]][3],"StrobeLow")) {
#define SPLITCOMPARELOW 0x1010
         cellinfo[cellcnt].formats[edgecnt]=SPLITCOMPARELOW;edgecnt++;
        if (cmp==0) fprintf(fpwaves,"\tCompare {\n\t\tWaveform {\n");
        fprintf(fpwaves,"\t\t\tCompareOpenLow @\"%s+%s*%s%s\";\n",field[en[i]][5],field[en[i]][6],tperiod,(en[i]==0)?org1:(en[i]==1)?org2:(en[i]==2)?org3:(en[i]==3)?org4:"0.000ps");
        fprintf(fpwaves,"//FIXME:unsupported dual time...!\n");
        fprintf(fpwaves,"//\t\t\tCompareOpenHigh @\"%s+%s*%s%s\";\n",field[en[i]][9],field[en[i]][10],tperiod,(en[i]==0)?org1:(en[i]==1)?org2:(en[i]==2)?org3:(en[i]==3)?org4:"0.000ps");
        cmp=1;
        }
     else if (NULL!=strstr(field[en[i]][3],"StrobeData")) {
#define SPLITCOMPAREDATA 0x1011
         cellinfo[cellcnt].formats[edgecnt]=SPLITCOMPAREDATA;edgecnt++;
        if (cmp==0) fprintf(fpwaves,"\tCompare {\n\t\tWaveform {\n");
        fprintf(fpwaves,"\t\t\tCompareOpenData @\"%s+%s*%s%s\";\n",field[en[i]][5],field[en[i]][6],tperiod,(en[i]==0)?org1:(en[i]==1)?org2:(en[i]==2)?org3:(en[i]==3)?org4:"0.000ps");
        fprintf(fpwaves,"//FIXME:unsupported dual time...!\n");
        fprintf(fpwaves,"//\t\t\tCompareOpenData @\"%s+%s*%s%s\";\n",field[en[i]][9],field[en[i]][10],tperiod,(en[i]==0)?org1:(en[i]==1)?org2:(en[i]==2)?org3:(en[i]==3)?org4:"0.000ps");
        cmp=1;
        }
      }
   if (cmp) fprintf(fpwaves,"\t\t}\n\t}\n");
   fprintf(fpwaves,"}\n");
   *which += inc;
   cellcnt++;
   if (cellcnt>MAXCELLS) {fprintf(stderr,"Too many cells. source line[%d]\n",__LINE__);exit(1);}
   return(ne);
   }
