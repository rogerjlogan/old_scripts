/* output patterns appn_out_pats.c */
/* output_dpm(); */
/* output_cpm(); */
/* output_cpm_dpm(); */

#include <stdio.h>
#include <strings.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "appn_includes.h"
static int beginC=0;
static int RPTC=0;
int output_dpm(int *SUPER_CNT,struct LOOP_LINES *SUPER){
   int i,DPMexiti,DPMexitlvl,lvl,cc,firstbegin;
   firstbegin=lvl=0;cc=1;
   for (i=0;i<*SUPER_CNT;i++) {
      while(SUPER[i].dummy && i<*SUPER_CNT) {fprintf(fpout1,"{%s !DPMd!}\n",SUPER[i].comment);i++;}
      if (SUPER[i].label[0]!='\0') {
         fprintf(fpout1,"$%s\n",SUPER[i].label); /* this is base level labels */
         }
      if (SUPER[i].shutdownvect) {
         if (SUPER[i].begin==1)    fprintf(fpstatus,"SHUTDOWN_B[%s]%d:%s \"%s\"\n",infile_orig,SUPER[i].shutdownvect,SUPER[i].vector,SUPER[i].comment);
         else if (SUPER[i].end==1) fprintf(fpstatus,"SHUTDOWN_E[%s]%d:%s \"%s\"\n",infile_orig,SUPER[i].shutdownvect,SUPER[i].vector,SUPER[i].comment);
         else                      fprintf(fpstatus,"SHUTDOWN__[%s]%d:%s \"%s\"\n",infile_orig,SUPER[i].shutdownvect,SUPER[i].vector,SUPER[i].comment);
         }
      else if (SUPER[i].begin==1) {/* loop */
         if (firstbegin==0) {
            firstbegin=1;
            beginC++;
            lvl++; /* need this for the pattern start */
            fprintf(fpout1,"begin\n");
            continue;
            }
         out_begin_dpm(SUPER,i,lvl,&DPMexiti,&DPMexitlvl,&cc);
         i=DPMexiti;
         lvl=DPMexitlvl;
         }
      else if (SUPER[i].end==1 && lvl==1) {/* end main */
         lvl--;
         fprintf(fpout1,"end\n");
         continue;
         }
      else if (SUPER[i].repeatcnt>0) {
         out_rpt_dpm(SUPER,SUPER[i].repeatcnt,i,lvl,&DPMexiti,&DPMexitlvl,&cc);
         i=DPMexiti;
         }
      else if (SUPER[i].VectorType==VT_SET) {
         fprintf(fpout1,"%s {%s !DPMvs!}\n",SUPER[i].vector,SUPER[i].comment);
         }
      else if (SUPER[i].VectorType==VT_Vector) {
         fprintf(fpout1,"%s {VN%dVC%d %s !DPMv!}\n",SUPER[i].vector,SUPER[i].vc,cc,SUPER[i].comment);
         cc++;
         }
      }
   fflush(fperrors);
   fflush(fpstatus);
   return(0);
   }

int out_rpt_dpm(struct LOOP_LINES *SUPER,int rpt,int at,int lvl,int *exitat,int *exitlvl,int *cc){
   int i,Rexitat,Rexitlvl;/* FIXME:APS need to add label support */
   if (SUPER[at].repeatcnt<2) {fprintf(stderr,"REPEAT[%d] misdirected!\n",rpt);}
   RPTC++;
//   fprintf(fpout1,"REPEAT#%d,LN%d\n",RPTC,at+1);
   at++;/* at comes in pointing at the repeat */
   while(SUPER[at].dummy) {fprintf(fpout1,"{%s !RPTDPMd!}\n",SUPER[at].comment);at++;}
   if (SUPER[at].label[0]!='\0') {
      fprintf(fpout1,"$%s\n",SUPER[at].label); /* this is base level labels */
      }
   if (SUPER[at].begin==1) {/* loop */
//      fprintf(fpout1,"PRINT BLOCK %d times\n",rpt);
      for (i=1;i<=rpt;i++) {
         out_begin_dpm(SUPER,at,lvl,&Rexitat,&Rexitlvl,cc);
         }
      if (SUPER[Rexitat].end!=1) fprintf(stderr,"rpt[%d]-begin-end loop did not exit on end!\n",rpt);
      at=Rexitat;/* this will point at the end */
      }
   else if (SUPER[at].VectorType==VT_Vector) {
      for (i=1;i<=rpt;i++) {
         fprintf(fpout1,"%s {VN%dVC%d RPTDPM:%dof%d %s}\n",SUPER[at].vector,SUPER[at].vc,*cc,i,rpt,SUPER[at].comment);
         (*cc)++;
         }
      }
   else {
      fprintf(fpout1,"{%s!RPTDPMnotV!}\n",SUPER[at].comment);
      }
   *exitat=at;
   *exitlvl=lvl;
//   fprintf(fpout1,"DONERPT%d,LN%d,LVL%d\n",rpt,*exitat+1,*exitlvl);
   return(0);
   }

int out_begin_dpm(struct LOOP_LINES *SUPER,int at,int lvl,int *exitat,int *exitlvl,int *cc){
   int i,Bexitat,Bexitlvl,begin,end,count; /* FIXME: APS need to add label support */
   if (SUPER[at].begin!=1) {fprintf(stderr,"BEGIN[%d,%d] misdirected!\n",lvl,at);}
   beginC++;
   if (SUPER[at].label[0]!='\0') {
      fprintf(fpout1,"$%s\n",SUPER[at].label); /* this is base level labels */
      }
//   fprintf(fpout1,"BEGINC%d,LN%d\n",beginC,at+1);
   lvl++;
   begin=at;
   end=SUPER[at].beginpointtoend;
   count=end-begin;
   for (i=1;i<count;i++){/* get past current begin! */
      if (SUPER[at+i].dummy) {fprintf(fpout1,"{%s !BEGINDPMc!}\n",SUPER[at+i].comment);}
      else if (SUPER[at+i].begin==1) { /* loop */
         out_begin_dpm(SUPER,at+i,lvl,&Bexitat,&Bexitlvl,cc);
         i=Bexitat-begin+1;
         if (lvl!=Bexitlvl) fprintf(stderr,"ERROR:LEVEL Changed at %d[%s\"%s\"]\n",at+i,SUPER[at+i].vector,SUPER[at+i].comment);
         }
      else if (SUPER[at+i].repeatcnt>0) {
         out_rpt_dpm(SUPER,SUPER[at+i].repeatcnt,at+i,lvl,&Bexitat,&Bexitlvl,cc);
         i=Bexitat-begin;
         if (lvl!=Bexitlvl) fprintf(stderr,"ERROR:LEVEL Changed at %d[%s\"%s\"]\n",at+i,SUPER[at+i].vector,SUPER[at+i].comment);
         }
      else if (SUPER[at+i].VectorType==VT_Vector) {
         fprintf(fpout1,"%s {VN%dVC%d %s !BEGINDPML%d_%d!}\n",SUPER[at+i].vector,SUPER[at+i].vc,*cc,SUPER[at+i].comment,lvl,i);
         (*cc)++;
         }
      else {
         fprintf(fpout1,"{%s !BEGINDPM%d_%d!}\n",SUPER[at+i].comment,lvl,i);
         }
      }
   lvl--;
   *exitlvl=lvl;
   *exitat=end;/* decided best place to point is the end, so increment in the caller */
//   fprintf(fpout1,"\"DONEBEGIN,LN%d,LVL%d,%s to %s\"\n",*exitat+1,*exitlvl,SUPER[begin].comment,SUPER[end].comment);
   return(0);
   }

int output_cpm(int *SUPER_CNT,struct LOOP_LINES  *SUPER) {
   int i;
   for (i=0;i<*SUPER_CNT;i++) {
      if (SUPER[i].VectorType==VT_Vector || SUPER[i].VectorType==VT_SET) { 
         if (fields!=0) {
            fprintf(fpout1,"%s {%s}\n",SUPER[i].vector,SUPER[i].comment);
            countlines++;
            }
         }
      if (SUPER[i].repeatcnt!=0 ) {
         }
      } /* end main for */
   fflush(fperrors);
   fflush(fpstatus);
   return(i);
   } /* output_cpm */

int output_cpm_dpm(int *SUPER_CNT,struct LOOP_LINES  *SUPER) {
   int i;
   for (i=0;i<*SUPER_CNT;i++) {
      if (SUPER[i].VectorType==VT_Vector || SUPER[i].VectorType==VT_SET) { 
         if (fields!=0) {
            fprintf(fpout1,"%s {%s}\n",SUPER[i].vector,SUPER[i].comment);
            countlines++;
            }
         }
      if (SUPER[i].repeatcnt!=0 ) {
         }
      } /* end main for */
   fflush(fperrors);
   fflush(fpstatus);
   return(i);
   } /* output_cpm_dpm */
   
int output_scan(char *outfile1,char *CYCLETBL,int *SUPER_CNT,struct LOOP_LINES  *SUPER) {
   char tempstr[READLINELEN+1];
   fprintf(fperrors,"FYI:%s:AUTO LAUNCHING vector_convert_scan on pattern[%s]\n",progstr,outfile1);
   fprintf(stderr,"FYI:AUTO LAUNCHING vector_convert_scan on pattern[%s]\n",outfile1);
   fflush(fperrors);
   sprintf(tempstr,"%s %s %s",VECTOR_CONVERT_SCAN,outfile1,CYCLETBL);
   fprintf(stderr,"FYI:[%s]\n",tempstr);
   fflush(fperrors);
   fflush(fpstatus);
   system(tempstr); /* call VCS */
   fprintf(fpstatus,"Back from VCS \n");
   return(0);
   }
   
