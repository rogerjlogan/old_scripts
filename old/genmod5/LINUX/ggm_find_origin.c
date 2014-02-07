/* gct_gen_mod_find_origin.c */
/* find_origin(){} */

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

int find_origin(char *WF,char *org1,char *org2,char *org3,char *org4) {
   int j,done,sl,eb,n,ESO,OS,ESOP,ERO,EOy;
   char *name,*ptr0,*ptr1,*ptr1C,*tptr,field[4][WF_EXPR_LEN],type[WF_EXPR_LEN],hold;
   for (n=0;n<orgcnt;n++) {
      name=origins->w[n];
      j=0;
      ptr0=strchr(name,'(');
      if (ptr0==NULL) return(-1);
      hold=*ptr0;
      *ptr0='\0';
      strcpy(type,name);
      *ptr0=hold;
      ptr0++;
      eb=0;
      done=0;
      sl=strlen(name);
      ESO=OS=ESOP=ERO=0;
      if (0==strcmp(type,"EdgeSetOriginPinList")) ESOP=1;
      else if (0==strcmp(type,"EdgeSetOrigin")) ESO=1;
      else if (0==strcmp(type,"EdgeResetOrigin")) ERO=1;
      else if (0==strcmp(type,"OriginSet")) OS=1;
      while(!done) {
         ptr1=strchr(ptr0,',');
         ptr1C=strrchr(ptr0,')');
         if (ptr1==NULL && ptr1C==NULL) {done=1;break;}
         if (ptr1==NULL && ptr1C!=NULL) ptr1=ptr1C;
         if (ptr1C<ptr1 && ptr1C!=NULL) {ptr1=ptr1C;done=1;} /* this is for the case when it finds a ',' after a ')'. e.g.: */
            //WaveSetNR(INT_CLKSTPdriveWF,0ns)elseWaveSetNR(INT_CLKSTPdriveWF,t[tcCI]-t[tsuINTCLKSTP]+dtcf+1ns)
         if (ptr1==NULL) break; /* in case there is nothing useful */
         if (ptr1>name+sl) break; /* in case there is nothing useful */
         hold=*ptr1;
         *ptr1='\0';
         strcpy(field[j],ptr0);
         *ptr1=hold;
         while (NULL!=(tptr=strstr(field[j],"div"))) {
            *tptr=' ';    /* d */
            *(tptr+1)=' ';/* i */
            *(tptr+2)='/';/* v */
            }
         while (NULL!=(tptr=strstr(field[j],"t["))) {
            *tptr=' ';    /* t */
            *(tptr+1)=' ';/* [ */
            }
         while (NULL!=(tptr=strstr(field[j],"]"))) {
            *tptr=' ';    /* ] */
            }
         ptr0=ptr1+1;
         j++;
         if(done) break;
         }
      sprintf(type,"ENORG_%s",WF);
         EOy=0;
      if (0==strcmp(field[0],WF) && (ESO||ESOP) ) {/* OS set means assign value only so we ignore */
         if (0==strcmp(field[1],"Edge1")) {
            sprintf(org1,"+%s*%s",field[2],type);
            EOy=1;
            }
         if (0==strcmp(field[1],"Edge2")) {
            sprintf(org2,"+%s*%s",field[2],type);
            EOy=1;
            }
         if (0==strcmp(field[1],"Edge3")) {
            sprintf(org3,"+%s*%s",field[2],type);
            EOy=1;
            }
         if (0==strcmp(field[1],"Edge4")) {
            sprintf(org4,"+%s*%s",field[2],type);
            EOy=1;
            }
         }
      if (EOy) {
         for (j=0;j<EOCNT;j++) if (0==strcmp(EO[j],type)) break;/* already exists!!! */
         if (j==EOCNT) {
            strcpy(EO[EOCNT],type);
            EOCNT++;
            if (EOCNT>=MAXORIGINS) {fprintf(stderr,"Too many origins!!!,holding...\n");EOCNT=MAXORIGINS-1;}
            }
         }
      }
   return(0);
   }
