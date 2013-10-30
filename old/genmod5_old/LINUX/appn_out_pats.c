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

int output_dpm(int *SUPER_CNT,struct LOOP_LINES  *SUPER) {
   int i,j,k,l,lvl,begin=0;
   for (lvl=i=0;i<*SUPER_CNT;i++) {
      if (begin==0 && SUPER[i].begin==1) {fprintf(fpout1,"begin\n");begin=1;}/* start real data */
      if (SUPER[i].repeathere && SUPER[i+1].begin==1) {/* its a loop */
         for (j=0;j<SUPER[i].repeatcnt;j++){/* FIXME: APS work with single loop first..., add nested later */
            for (l=0,k=*SUPER_CNT+1;k<SUPER[*SUPER_CNT+1].beginpointtoend;l++,k++) {
               fprintf(fpout1,"%s \"V%05d->LC%05d of %05d\"\n",SUPER[i].vector,l,j,SUPER[i].repeatcnt);
               countlines++;
               }
            }
         }
      else if (SUPER[i].repeathere) {/* its a vector */
         for (j=0;j<SUPER[i].repeatcnt;j++) {
            fprintf(fpout1,"%s \"LC%05d of %05d\"\n",SUPER[i].vector,j,SUPER[i].repeatcnt);
            countlines++;
            }
         }
      if (SUPER[i].VectorType==VT_Vector || SUPER[i].VectorType==VT_SET) { 
         if (fields!=0) {
            fprintf(fpout1,"%s \"%s\"\n",SUPER[i].vector,SUPER[i].comment);
            countlines++;
            }
         }
      if (SUPER[i].repeatcnt!=0 ) {
         }
      } /* end main for */
   fprintf(fpout1,"end;\n");/* close! */
   fflush(fperrors);
   fflush(fpstatus);
   return(i);
   } /* output_dpm */

int output_dpm_old(int *SUPER_CNT,struct LOOP_LINES  *SUPER) {
   int i,lvl,firstbegin=0;
   int i1,i2,i3,i4;
   int j1,j2,j3,j4;
   int count1,count2,count3,count4;
   int rptst1,rptst2,rptst3,rptst4;
   int rptsp1,rptsp2,rptsp3,rptsp4;
   for (lvl=i=0;i<*SUPER_CNT;i++) {
      if (SUPER[i].shutdownvect) {/* don't output normally */
         if(SUPER[i].VectorType==VT_Vector) {
            fprintf(fpstatus,"SHUTDOWN VECTOR[%s]:[%s]\n",infile_orig,SUPER[i].vector);
            continue;
            }
         }
      if (firstbegin==0 && SUPER[i].begin==1) fprintf(fpout1,"begin\n");
      if (SUPER[i].repeat[lvl]>0 && SUPER[i].repeathere==1) {
         if (SUPER[i+1].begin==1) { /* repeat block lvl=1 */
            rptst1=i+2;rptsp1=SUPER[i+1].beginpointtoend;
            count1=SUPER[i].repeat[1];
            for (j1=1;j1<=count1;j1++) {
               for (i1=rptst1;i1<rptsp1;i1++) {
                  if (SUPER[i1].repeat[2]>0 && SUPER[i1].repeathere==1) {
                     if (SUPER[i1+1].begin==1) {/* its a begin loop lvl=2 */
                        rptst2=i1+2;rptsp2=SUPER[i1+1].beginpointtoend;
                        count2=SUPER[i1].repeat[2];
                        for (j2=1;j2<=count2;j2++) {
                           for (i2=rptst2;i2<rptsp2;i2++) {
                              if (SUPER[i2].repeat[2]>0 && SUPER[i2].repeathere==1) {
                                 if (SUPER[i2+1].begin==1) {/* its a begin loop lvl=3 */
                                    rptst3=i2+2;rptsp3=SUPER[i2+1].beginpointtoend;
                                    count3=SUPER[i2].repeat[3];
                                    for (j3=1;j3<=count3;j3++) {
                                       for (i3=rptst3;i3<rptsp3;i3++) {
                                          if (SUPER[i3].repeat[3]>0 && SUPER[i3].repeathere==1) {
                                             if (SUPER[i3+1].begin==1) {
                                                rptst4=i3+2;rptsp4=SUPER[i3+1].beginpointtoend;
                                                count3=SUPER[i3].repeat[4];
                                                for (j4=1;j4<=count4;j4++) {
                                                   for (i4=rptst4;i4<rptsp4;i4++) {
                                                      if (SUPER[i4].repeat[4]>0 && SUPER[i4].repeathere==1) {
                                                         fprintf(fpout1,"%s \"V%05d->LC%05d of %05d\"\n",SUPER[i1].vector,i1,j1,count1);
                                                         }
                                                      }
                                                   }
                                                }
                                             else { /* level 4 not begin */
                                                for (j4=1;j4<=count4;j4++) {
                                                   fprintf(fpout1,"%s \"V%05d->LC%05d of %05d\"\n",SUPER[i4].vector,i4,j4,count4);
                                                   }
                                                }
                                             }
                                          else {/* level 4 not repeat */
                                             if (SUPER[i4].VectorType==VT_Vector || SUPER[i4].VectorType==VT_SET) {
                                                fprintf(fpout1,"%s \" %s \"\n",SUPER[i4].vector,SUPER[i4].comment);
                                                }
                                             } 
                                          }
                                       }
                                    }
                                 else { /* level 3 not begin */
                                    for (j3=1;j3<=count3;j3++) {
                                       fprintf(fpout1,"%s \"V%05d->LC%05d of %05d\"\n",SUPER[i3].vector,i3,j3,count3);
                                       }
                                    }
                                 }
                              else { /* level 3 not repeat */
                                 if (SUPER[i3].VectorType==VT_Vector || SUPER[i3].VectorType==VT_SET) {
                                    fprintf(fpout1,"%s \" %s \"\n",SUPER[i3].vector,SUPER[i3].comment);
                                    }
                                 }
                              }
                           }
                        }
                     else {/* level 2 not begin */
                        for (j2=1;j2<=count2;j2++) {
                           fprintf(fpout1,"%s \"V%05d->LC%05d of %05d\"\n",SUPER[i2].vector,i2,j2,count2);
                           }
                        }
                     }
                  else {/* level 2 not repeat */
                     if (SUPER[i2].VectorType==VT_Vector || SUPER[i2].VectorType==VT_SET) {
                        fprintf(fpout1,"%s \" %s \"\n",SUPER[i2].vector,SUPER[i2].comment);
                        }
                     }
                  }
               }
            }
         else {/* repeat only */
            for (j1=1;j1<=count1;j1++) {
               fprintf(fpout1,"%s \"V%05d->LC%05d of %05d\"\n",SUPER[i1].vector,i1,j1,count1);
               }
            }
         }
      else { /* no repeat */
         if (SUPER[i1].VectorType==VT_Vector || SUPER[i1].VectorType==VT_SET) {
            fprintf(fpout1,"%s \" %s \"\n",SUPER[i1].vector,SUPER[i1].comment);
            }
         }
      }

   fprintf(fpout1,"end;\n");/* close! */
   fflush(fperrors);
   fflush(fpstatus);
   return(i);
   } /* output_dpm */
   
int output_cpm(int *SUPER_CNT,struct LOOP_LINES  *SUPER) {
   int i;
   for (i=0;i<*SUPER_CNT;i++) {
      if (SUPER[i].VectorType==VT_Vector || SUPER[i].VectorType==VT_SET) { 
         if (fields!=0) {
            fprintf(fpout1,"%s %s\n",SUPER[i].vector,SUPER[i].comment);
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
            fprintf(fpout1,"%s %s\n",SUPER[i].vector,SUPER[i].comment);
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
   
