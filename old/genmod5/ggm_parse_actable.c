/* gct_gen_mod_parse_actable.c parse_actable() {} */

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

int parse_actable(char *fname,int used_line[],char *tperiod) {
FILE *fpin;
char *cstptr,*cendptr,*actablein,*mytable,*ptrOP,*ptrCL,*ptrfind,holdch;
char *ptrELSE,*ptrBEGIN,*ptrCOLON,*ptrTHEN;
int   iELSE,iBEGIN,iCOLON,iTHEN;
char readstr[READLINELEN+1],readstr2[READLINELEN+1];
int i,j,ret,sp,fmcnt,pos,discardwhendone;
struct stat statbuf;
off_t filesize;

ret=stat(fname,&statbuf);
if (ret==0) filesize=statbuf.st_size;
else {
   fprintf(stderr,"Can't determine filesize for [%s]\n",fname);
   exit(1);
   }

if (NULL==(fpin=fopen(fname,"r"))) {
   fprintf(stderr,"\nInput file [%s] not found\n",fname);
   exit(1);
   }

acwaves=(ACWAVES *)calloc(ACTABLELINES+1,ACTABLELEN+1);
if (acwaves==NULL) {
   fprintf(stderr,  "Could not allocate memory for acwaves in [%s]\n",fname);
   exit(1);
   }
fprintf(stderr,"allocated [%d] bytes for acwaves @%p\n",(ACTABLELINES+1)*(ACTABLELEN+1),acwaves);

origins=(ACWAVES *)calloc(ACTABLELINES+1,ACTABLELEN+1);
if (origins==NULL) {
   fprintf(stderr,  "Could not allocate memory for origins in [%s]\n",fname);
   exit(1);
   }
fprintf(stderr,"allocated [%d] bytes for origins @%p\n",(ACTABLELINES+1)*(ACTABLELEN+1),origins);

actablenames=(ACTABLENAMES *)calloc(MAXACTABLES+1,MAXACTABLENAMELEN+1);
if (origins==NULL) {
   fprintf(stderr,  "Could not allocate memory for actablenames in [%s]\n",fname);
   exit(1);
   }
fprintf(stderr,"allocated [%d] bytes for actablenames @%p\n",(MAXACTABLES+1)*(MAXACTABLENAMELEN+1),actablenames);
maxactablenames=0;

actablein=malloc((size_t)(filesize+1));
if (actablein==NULL) {
   fprintf(stderr,  "Could not allocate memory for [%s] file in memory\n",fname);
   exit(1);
   }
fprintf(stderr,"allocated [%ld] bytes for actablein\n",filesize);

for (i=0;i<ACTABLELINES;i++) used_line[i]=0;

fread(actablein,(size_t)filesize,1,fpin);
fclose(fpin);

actablein[filesize]='\0';/* just to make sure */
pos=0;
mytable=actablein;

/* Clear the comments */
while (pos<filesize && (cstptr=strstr(mytable,"(*"))!=NULL) {
   cendptr=strstr(mytable,"*)");
   while(cstptr<=(cendptr+1)) { /* +1 => get '(' through the ')' */
      *cstptr++=' ';
      pos=cstptr-actablein;
      }
   mytable=cendptr+1;
   }
fprintf(stderr,"END (**)%d->%ld\n",mytable-actablein,(long)filesize);

mytable=actablein;
while (pos<filesize && (cstptr=strstr(mytable,"{"))!=NULL) {
   cendptr=strstr(mytable,"}");
   while(cstptr<=(cendptr)) { /* no +1 for '{' '}' */
      *cstptr++=' ';
      pos=cstptr-actablein;
      }
   mytable=cendptr+1;
   }
fprintf(stderr,"END {}%d->%ld\n",mytable-actablein,(long)filesize);

discardwhendone=0;
fmcnt=sp=pos=0;
readstr[0]='\0';
while(pos<filesize) {
   if (isspace(actablein[pos])) {pos++;} /* don't store if white space */
   else if (actablein[pos]!=';') {
      readstr[sp]=actablein[pos];
      sp++;pos++;readstr[sp]='\0';/* keep it permanently terminated, for debug etc */
      }
   else if (actablein[pos]==';') {/* found end of statement */
      /* first look for 'control' statements */
      ptrELSE=strstr(readstr,"else");
      ptrTHEN=strstr(readstr,"then");
      ptrBEGIN=strstr(readstr,"begin");
      ptrCOLON=strchr(readstr,':');
      iELSE=iBEGIN=iCOLON=iTHEN=4;
      /* sort them, what remains should =4 */
      if (ptrELSE!=NULL  && ptrTHEN!=NULL)  if (ptrELSE<ptrTHEN)   iTHEN--;
      if (ptrELSE!=NULL  && ptrBEGIN!=NULL) if (ptrELSE<ptrBEGIN)  iBEGIN--;
      if (ptrELSE!=NULL  && ptrCOLON!=NULL) if (ptrELSE<ptrCOLON)  iCOLON--;
      if (ptrTHEN!=NULL  && ptrELSE!=NULL)  if (ptrTHEN<ptrELSE)   iELSE--;
      if (ptrTHEN!=NULL  && ptrBEGIN!=NULL) if (ptrTHEN<ptrBEGIN)  iBEGIN--;
      if (ptrTHEN!=NULL  && ptrCOLON!=NULL) if (ptrTHEN<ptrCOLON)  iCOLON--;
      if (ptrBEGIN!=NULL && ptrELSE!=NULL)  if (ptrBEGIN<ptrELSE)  iELSE--;
      if (ptrBEGIN!=NULL && ptrTHEN!=NULL)  if (ptrBEGIN<ptrTHEN)  iTHEN--;
      if (ptrBEGIN!=NULL && ptrCOLON!=NULL) if (ptrBEGIN<ptrCOLON) iCOLON--;
      if (ptrCOLON!=NULL && ptrELSE!=NULL)  if (ptrCOLON<ptrELSE)  iELSE--;
      if (ptrCOLON!=NULL && ptrTHEN!=NULL)  if (ptrCOLON<ptrTHEN)  iTHEN--;
      if (ptrCOLON!=NULL && ptrBEGIN!=NULL) if (ptrCOLON<ptrBEGIN) iBEGIN--;
      if (NULL!=(ptrfind=strstr(readstr,"end"))) {
         /* end is generally isolated... */
         strcpy(acwaves->w[fmcnt],"end");/* just write 'end' */
         fmcnt++;
         sp=0;readstr[0]='\0';
         pos++;/* should advance */
         }
      else if (NULL!=ptrTHEN && iTHEN==4){
         *ptrTHEN='\0';
         if (readstr[0]!='\0' && readstr[0]!='\n') {
            strcpy(acwaves->w[fmcnt],readstr);/* write whatever is in front of 'then' */
            fmcnt++;
            }
         strcpy(acwaves->w[fmcnt],"then");/* write the 'then' */
         fmcnt++;
         strcpy(readstr2,ptrTHEN+sizeof("then")-1);/* keep whatever is after 'then' for further processing */
//         fprintf(stdout,"RtS[%s]RS2[%s]%d\n",readstr,readstr2,sp);
         strcpy(readstr,readstr2);
         sp=strlen(readstr);/* should still point at a ';' */
         /* no advance */
         }
      else if (NULL!=ptrELSE && iELSE==4){
//         fprintf(stdout,"ReeS[%s]%d\n",readstr,sp);
         *ptrELSE='\0';
         if (readstr[0]!='\0' && readstr[0]!='\n') {
            strcpy(acwaves->w[fmcnt],readstr);/* write whatever is in front of 'else' */
            fmcnt++;
            }
         strcpy(acwaves->w[fmcnt],"else");/* write the 'else' */
         fmcnt++;
         strcpy(readstr2,ptrELSE+sizeof("else")-1);/* keep whatever is after 'else' for further processing */
         strcpy(readstr,readstr2);
         sp=strlen(readstr);/* should still point at a ';' */
         /* no advance */
         }
      else if (NULL!=ptrBEGIN && iBEGIN==4){
         *ptrBEGIN='\0';
         if (readstr[0]!='\0' && readstr[0]!='\n') {
            strcpy(acwaves->w[fmcnt],readstr);/* write whatever is in front of 'begin' */
            fmcnt++;
            }
         strcpy(acwaves->w[fmcnt],"begin");/* write the 'begin' */
         fmcnt++;
         strcpy(readstr2,ptrBEGIN+sizeof("begin")-1);/* keep whatever is after 'begin' for further processing */
         strcpy(readstr,readstr2);
         sp=strlen(readstr);/* should still point at a ';' */
//         fprintf(stdout,"RbS[%s]RS2[%s]%d\n",readstr,readstr2,sp);
         /* no advance */
         }
      else if (NULL!=ptrCOLON && iCOLON==4){ /* end of case define */
         if (*(ptrCOLON+1)=='=') {/* then its not what we are looking for, change it and reprocess */
            *ptrCOLON='~';
            continue;/* no advance */
            }
         holdch=*(ptrCOLON+1);
         *(ptrCOLON+1)='\0';
         if (readstr[0]!='\0' && readstr[0]!='\n') {
            strcpy(acwaves->w[fmcnt],readstr);/* write whatever is in front of 'then' */
            fmcnt++;
            }
         *(ptrCOLON+1)=holdch;
         strcpy(readstr2,ptrCOLON+1);/* keep whatever is after ':' for further processing */
//         fprintf(stdout,"R:S[%s]RS2[%s]%d\n",readstr,readstr2,sp);
         strcpy(readstr,readstr2);
         sp=strlen(readstr);/* should still point at a ';' */
         /* no advance */
         }
      /* now..., the rest of the story... */
      else if (NULL!=(ptrfind=strstr(readstr,"Origin"))){
         strcpy(origins->w[orgcnt],readstr);
         orgcnt++;
         if (orgcnt>=ACTABLELINES) {
            fprintf(stderr,"Too many origins %d in [%s], near [%s]\n",orgcnt,fname,readstr);
            exit(1);
            }
         readstr[0]='\0';sp=0;/* clear the string, i.e. don't print it */
         pos++;/* advance */
         }
      else if (NULL!=(ptrfind=strstr(readstr,"PeriodSetAll"))){
         ptrOP=strchr(ptrfind,'(');
         ptrCL=strchr(ptrfind,')');
         j=0;
         if (ptrOP!=NULL && ptrCL!=NULL) {
            ptrOP++;
            while(ptrOP<ptrCL) {
               tperiod[j]=*ptrOP;
               if (*ptrOP=='[') {/* wipe out t[ */
                  tperiod[j-1]=' ';
                  tperiod[j]=' ';
                  }
               else if (*ptrOP==']') {/* wipe out ] */
                  tperiod[j]=' ';
                  }
               j++;ptrOP++;
               }
            }
         tperiod[j]='\0';
         readstr[0]='\0';sp=0;/* clear the string, i.e. don't print it */
         pos++;/* advance */
         }
      else if (NULL!=(ptrfind=strstr(readstr,"TIACTableSet"))){
         ptrOP=strchr(readstr,'(');
         ptrCL=strchr(readstr,')');
         j=0;
         if (ptrOP!=NULL && ptrCL!=NULL) {
            ptrOP++;
            while(ptrOP<ptrCL) {
               actablenames->name[maxactablenames][j]=*ptrOP;
               j++;
               ptrOP++;
               }
            }
         actablenames->name[maxactablenames][j]='\0';
         maxactablenames++;
         if (maxactablenames>=MAXACTABLES) {
            fprintf(stderr,"Too many actables %d in [%s], near [%s]\n",maxactablenames,fname,readstr);
            exit(1);
            }
         readstr[0]='\0';sp=0;/* clear the string, i.e. don't print it */
         pos++;/* advance */
         }
      else if (NULL!=(ptrfind=strstr(readstr,"~="))) {
         /* this was changed above from ':=', assignment, ignore... */
         readstr[0]='\0';sp=0;/* clear the string, i.e. don't print it */
         pos++;/* advance */
         }
      else {/* write it to acwaves */
         if (readstr[0]!='\0'&& readstr[0]!='\n') {
            strcpy(acwaves->w[fmcnt],readstr);
            fmcnt++;
            if (fmcnt>=ACTABLELINES) {
               fprintf(stderr,"Too many lines %d in [%s], near [%s]\n",fmcnt,fname,readstr);
               exit(1);
               }
            }
         readstr[0]='\0';sp=0;/* clear the string, i.e. don't print it */
         pos++;/* advance */
         }
      }/* found end of statement */
   }/* while */
fprintf(stderr,"Completely processed %d items from %s\n",fmcnt,fname);
if (DEBUG) for (i=0;i<fmcnt;i++) fprintf(stdout,"%s\n",acwaves->w[i]);
fprintf(stdout,"-------------------------------------\n");
free(actablein);
return(fmcnt);
}
