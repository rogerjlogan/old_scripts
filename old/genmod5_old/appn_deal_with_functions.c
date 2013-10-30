/* appn_deal_with_functions.c: routines to deal_with_repeats and matches etc... */
/* int deal_with_repeat_DPM(){} */
/* int deal_with_match(){} */
/* int deal_with_repeat_CPM(){} */

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


int deal_with_repeat_DPM(FILE *fpin1,FILE *fpout1,char *ptr,int *repeat_nesting,long *loop_number,
                      char *vector,int *repeat_cnts,char *retbuff){
char vector2[READLINELEN+1],*ptr2,*retptr,newvector[READLINELEN+1];
/* char cbuff[MED_BUFFER_SIZE+1],rbuff[MED_BUFFER_SIZE+1],tmpbuff[MED_BUFFER_SIZE+1]; */
char *cbuff,*rbuff,*tmpbuff;
long repeatcnt,i,ilooprc=0,repeat_size;
long tmpholdloop=0,chksize;
int retval;
if (debug&1) fprintf(fpstatus,"deal_with_repeat_DPM\n");
cbuff=malloc(MED_BUFFER_SIZE+1);
if (cbuff==0) {
   fprintf(stderr,"FATAL_ERROR:Could not get memory,cbuff\n");
   fprintf(fperrors,"FATAL_ERROR:%s:Could not get memory,cbuff[%s]line%ld\n",progstr,infile_orig,readlinenum);
   exit(RET_NOT_ENOUGH_MEMORY);
   }
rbuff=malloc(MED_BUFFER_SIZE+1);
if (rbuff==0) {
   fprintf(stderr,"FATAL_ERROR:Could not get memory,rbuff\n");
   fprintf(fperrors,"FATAL_ERROR:%s:Could not get memory,rbuff[%s]line%ld\n",progstr,infile_orig,readlinenum);
   exit(RET_NOT_ENOUGH_MEMORY);
   }
tmpbuff=malloc(MED_BUFFER_SIZE+1);
if (tmpbuff==0) {
   fprintf(stderr,"FATAL_ERROR:Could not get memory,tmpbuff\n");
   fprintf(fperrors,"FATAL_ERROR:%s:Could not get memory,tmpbuff[%s]line%ld\n",progstr,infile_orig,readlinenum);
   exit(RET_NOT_ENOUGH_MEMORY);
   }

cbuff[0]='\0';
rbuff[0]='\0';
tmpbuff[0]='\0';
tmpholdloop=*loop_number;
( *repeat_nesting )++;

fflush(fpout1);
retptr=get_count_orig(ptr,sizeof("repeat"),&repeatcnt,vector);
*repeat_cnts = repeatcnt;
repeat_size=repeatcnt;
if(debug&8) fprintf(fpstatus,"FYI:rcb_rpt:%ld rpt_nst:%d ",repeat_size,*repeat_nesting);
for (i=0;i<*(repeat_nesting)-1;i++) repeat_size *= repeat_count_buffer[i];
fprintf(fpstatus," final size:%ld\n",repeat_size);
if (FORCEDPM==0 && repeat_size>MAX_LOOP_SIZE) {
   fprintf(fpstatus,"DWRD:returning loop size too big(2)\n");
   return(RET_LOOP_SIZE_TOO_BIG);
   }
fprintf(fpstatus,"We are continuing\n");
if (SCAN && repeatcnt==RET_FOREVER) return(RET_REPEAT_FOREVER_SCAN);
else if (repeatcnt==RET_FOREVER) return(RET_REPEAT_FOREVER);/* cant do repeat forever in DPM */
else if (repeatcnt==0) {
/* this could be bad syntax or not really what we were looking for, ie. inside a comment */
   fprintf(fpstatus,"no count found, passing statement on.<%s>\n",ptr);
   sprintf(tmpbuff,"%s\n",vector);
   strcat(retbuff,tmpbuff);
   ( *repeat_nesting )--;
   return(RET_IGNORING_STATEMENT);
   }
fprintf(fpstatus,"found repeat [%06ld] LEVEL[%d]\n",repeatcnt,*repeat_nesting);
fgets(vector2,READLINELEN-1,fpin1);
readlinenum++;
vector2[strlen(vector2)-1]='\0';
if (NULL==strstr(vector2,"begin")){ /* not begin */
   fprintf(fpstatus,"oops, not a repeat block,just a repeat vector.\n");
   appr_vc+=(repeatcnt-1);
   if (*(repeat_nesting)==1){
      ptr=strchr(vector2,'[');
      expand_vector(newvector,vector2,ptr,__LINE__,__FILE__);
      fprintf(fpout1,"%s\n%s\n",vector,newvector);
      countlines++;
      (*repeat_nesting)--;
      free(cbuff);
      free(rbuff);
      free(tmpbuff);
      return(RET_NORMAL);
      }
   else {
      sprintf(tmpbuff,"%s\n",vector);
      strcat(retbuff,tmpbuff);
      sprintf(tmpbuff,"%s\n",vector2);
      strcat(retbuff,tmpbuff);
      countlines+=2;
      }
   } /* ?? */
else { /* begin */
   ( *loop_number )++;
   cbuff[0]='\0';
   while(fgets(vector2,READLINELEN-1,fpin1) != NULL ){
      if(debug&16) fprintf(fpstatus,"V:[%s]\n",vector2);
      readlinenum++;
      vector2[strlen(vector2)-1]='\0';
      if (NULL!=strstr(vector2,"GCT")) ilooprc++;
      if (0==strstr(vector2,"end")) {/* not at end */
         if (debug&16) fprintf(fpstatus,"continuing search for end!!!!\n");
         if ((ptr2=strstr(vector2,"repeat"))==NULL){ /* not a repeat */
            if (NULL!=(ptr2=strchr(vector2,'['))) {/* probably a vector */
               expand_vector(newvector,vector2,ptr2,__LINE__,__FILE__);
               strcpy(vector2,newvector);
               }
            sprintf(tmpbuff,"%s\n",vector2);
            countlines++;
            strcat(cbuff,tmpbuff);
            }
         else {
            fprintf(fpstatus,"found another repeat inside!!!!\n");
            repeat_count_buffer[*repeat_nesting-1]=*repeat_cnts;
            if(debug&8)fprintf(fpstatus,"FYI:rcb1:%d %d\n",repeat_count_buffer[*repeat_nesting-1],*repeat_nesting);
            rbuff[0]='\0';
            /* the following is somewhat dangerous as it is a recursive call!!! */
            if (debug&1) fprintf(fpstatus,"pre-deal_with_repeat_DPM5\n");
            retval=deal_with_repeat_DPM(fpin1,fpout1,ptr2,repeat_nesting,loop_number,vector2,repeat_cnts,rbuff);
            if (debug&1) fprintf(fpstatus,"post-deal_with_repeat_DPM5\n");
            if (retval==RET_LOOP_SIZE_TOO_BIG) {
               fprintf(fpstatus,"loop size too big(1)\n");
               return(RET_LOOP_SIZE_TOO_BIG);
               }
            strcat(cbuff,rbuff);
            rbuff[0]='\0';
            }
         }
      else { /* found end !!! */
         if (debug&8) fprintf(fpstatus,"FOUND END!!!!\n");
         appr_vc+=(ilooprc*repeatcnt);
         if (*repeat_nesting > 1){/* if not at top level, we must use retbuff */
            rbuff[0]='\0';
            chksize=repeatcnt*(strlen(cbuff)+strlen("(*BOL#%ld Level=%d LOOP=%ld of %ld*) \n")+strlen("(*EOL#%ld LOOP%ld*) \n"));
            if (chksize > MED_BUFFER_SIZE) {
                  fprintf(stderr,"FATAL_ERROR:LOOP expansion[%ld] would exceed buffer size[%d]\n",chksize,MED_BUFFER_SIZE);
                  fprintf(fperrors,"FATAL_ERROR:%s:LOOP expansion would exceed buffer size[%s]line%ld\n",progstr,infile_orig,readlinenum);
                  exit(1);
                  }
            for (i=1;i<=repeatcnt;i++) {
               sprintf(tmpbuff,"(*BOL#%ld Level=%d LOOP=%ld of %ld*) \n",tmpholdloop,*repeat_nesting,i,repeatcnt);
               strcat(rbuff,tmpbuff);
               sprintf(tmpbuff,"%s",cbuff);
               strcat(rbuff,tmpbuff);
               sprintf(tmpbuff,"(*EOL#%ld LOOP%ld*) \n",tmpholdloop,i);
               strcat(rbuff,tmpbuff);
               } /* end for */

            strcpy(retbuff,rbuff);
            }
         else {/* if we are at the top level we can just print. We do this to save memory */
            for (i=1;i<=repeatcnt;i++) {
               fprintf(fpout1,"(*BOL#%ld Level=%d LOOP=%ld of %ld*) \n",tmpholdloop,*repeat_nesting,i,repeatcnt);
               countlines++;
               fprintf(fpout1,"%s",cbuff);
               countlines++;
               fprintf(fpout1,"(*EOL#%ld LOOP%ld*) \n",tmpholdloop,i);
               } /* end for */
            cbuff[0]='\0';
            }
         break; /* terminate line processing at this nesting level */
         } /* else found end !!! */
      } /* end while */
   } /* end if begin */
( *repeat_nesting )--; /* pop back up one level of nesting */
if ( (*repeat_nesting) == 0 ){;
  /* fprintf(fpout1,"%s",retbuff); */ /* I dont think this is needed */
   /* retbuff[0]='\0'; */
   }
free(cbuff);
free(rbuff);
free(tmpbuff);
if (debug&1) fprintf(fpstatus,"deal_with_repeat_DPM done\n");
return(RET_GOOD);
}

/* ============================================================================ */


int deal_with_match(FILE *fpin1,FILE *fpout1,char *ptr,int *repeat_nesting,long *loop_number,
                      char *vector,int *repeat_cnts,char *retbuff,char *patnameptr){
char vector2[READLINELEN+1],vector_prev[READLINELEN+1],*ptr2,*retptr;
char cbuff[MED_BUFFER_SIZE+1];
long repeatcnt=0;
long keep_loop_num;
cbuff[0]='\0';
if(debug&1) fprintf(fpstatus,"deal_with_match\n");
retptr=get_count_orig(ptr,sizeof("match"),&repeatcnt,vector);
if (repeatcnt==0){
   fprintf(fpstatus,"no count found, throwing out match.<%s>\n",ptr);
   return(RET_IGNORING_STATEMENT);
   }
fprintf(fpstatus,"found match [%ld]\n",repeatcnt);
fgets(vector2,READLINELEN-1,fpin1);
readlinenum++;
vector2[strlen(vector2)-1]='\0';
if (0==strstr(vector2,"begin")){ /* not begin */
   fprintf(fpstatus,"oops, not a match block,just a match vector.\n");
   fprintf(fpout1,"%s\n",vector);
   ptr=strchr(vector2,'[');
   expand_vector(newvector,vector2,ptr,__LINE__,__FILE__);
   fprintf(fpout1,"%s\n",vector2);
   countlines+=2;
   return(RET_NORMAL);
   }
else { /* begin */
   ( *loop_number )++;
   keep_loop_num=*loop_number;
   if (repeatcnt>=65535) {
      fprintf(fperrors,"NON_FATAL_ERROR: LOOP COUNT TOO BIG\n");
      fprintf(stderr,"NON_FATAL_ERROR: LOOP COUNT TOO BIG\n");
      }
   fprintf(fpout1,"<LC1 %ld>\n",repeatcnt-1);
   fprintf(fpout1,"<MODE(IFAIL ON,TCI ON)>\n");
   fprintf(fpout1,"$%s_M_%d_%d_%d\n",patnameptr,(int)*repeat_nesting,(int)repeatcnt,(int)*loop_number);
   fprintf(fpout1,"<FLAG(SEQF OFF)>\n");
   fprintf(fpout1,"<COND NZC1>\n");
   lastwascont=0;
   countlines+=5;
   vector_prev[0]='\0';
   while(fgets(vector2,READLINELEN-1,fpin1) != NULL ){
      readlinenum++;
      vector2[strlen(vector2)-1]='\0';
      if (0==strstr(vector2,"end")) {/* not at end */
         if (debug&16) fprintf(fpstatus,"continuing search for end!!!!\n");
         if ((ptr2=strstr(vector2,"repeat"))==0){ /* not a repeat */
            fprintf(fpout1,"%s\n",vector2);
            strcpy(vector_prev,vector2);/* keep previous vector, for match stop strobing */
           countlines++;
            }
         else {
            fprintf(fpstatus,"*** WARNING: found another repeat inside!!!! ***\n");
            fprintf(fpstatus," Microinstructions could be wrong in this case \n");
            /* the following is somewhat dangerous as it is a recursive call!!! */
            if (debug&1) fprintf(fpstatus,"pre-deal_with_repeat_CPM6\n");
            deal_with_repeat_CPM(fpin1,fpout1,ptr2,repeat_nesting,loop_number,vector2,repeat_cnts,cbuff,patnameptr);
            if (debug&1) fprintf(fpstatus,"post-deal_with_repeat_CPM6\n");
            }
         }
      else { /* found end !!! */
         if (debug&8) fprintf(fpstatus,"FOUND END!!!!\n");
         fprintf(fpstatus," Attempting to add <COND SEQF> back in \n");
         fprintf(fpout1,"<DC1,CJMP .+3>\n");
         fprintf(fpout1,"<MODE(IFAIL OFF,TCI OFF)>\n");
         fprintf(fpout1,"%s  (* NSFAPP--this should have strobes*)\n",vector_prev);
//         if (vector_prev[0]=='\0') fprintf(fpout1,"<STOP FAIL>(* removing this STOP FAIL and adding STROBES will only work on VX250/VX500 not on EX or VX4, APS 02/27/06 rev15+ pre_proc *)\n");
//         else fprintf(fpout1,"%s\n<STOP FAIL>(* removing this STOP FAIL and adding STROBES will only work on VX250/VX500 not on EX or VX4, APS 02/27/06 rev15+ pre_proc *)\n",vector_prev);
         fprintf(fpout1,"<COND SEQF>\n");
         fprintf(fpout1,"<RPT MatchPipeline>\n");
         fprintf(fpout1,"<CJMP %s_M_%d_%d_%ld>\n",patnameptr,(int)*repeat_nesting,(int)repeatcnt,keep_loop_num);
         fprintf(fpout1,"<MODE(IFAIL OFF,TCI OFF)>\n");
         lastwascont=0;
         countlines+=7;
         break;
         } /* else found end !!! */
      } /* end while */
   } /* end if begin */
if (debug&1) fprintf(fpstatus,"deal_with_repeat_match done\n");
return(RET_GOOD);
}

/* ============================================================================ */

int deal_with_repeat_CPM(FILE *fpin1,FILE *fpout1,char *ptr,int *repeat_nesting,long *loop_number,
                      char *vector,int *repeat_cnts,char *retbuff,char *patnameptr){
   char vector2[READLINELEN+1],newvector[READLINELEN+1],*ptr2,*retptr;
   char cbuff[MED_BUFFER_SIZE+1];
   long repeatcnt=0;
   static int last_COND=-1,doubleloop=0;
   int tmpholdloop=0,repeat_forever=0;
   if (debug&1) fprintf(fpstatus,"deal_with_repeat_CPM\n");
   if ((*repeat_nesting)==0) retbuff[0]='\0'; /* only wipe when at top level */
   ( *repeat_nesting )++;
   if ((*repeat_nesting)>4) {
      fprintf(stderr,"NON_FATAL_ERROR:Not enough CPM counters available for nesting this deep.\n");
      fprintf(fperrors,"NON_FATAL_ERROR:%s:Not enough CPM counters available for nesting this deep.[%s]line%ld\n",progstr,infile_orig,readlinenum);
      fprintf(stderr,"(NON_FATAL_ERROR):Attempting translation anyway, you will need to figure this one out!!!\n");
      fprintf(fperrors,"(NON_FATAL_ERROR):%s:Attempting translation anyway, you will need to figure this one out!!!\n",progstr);
      }
   fflush(fpout1);
   retptr=get_count_orig(ptr,sizeof("repeat"),&repeatcnt,vector);
   *repeat_cnts = repeatcnt;
   if (repeatcnt==RET_FOREVER) repeat_forever=1;
   else if (repeatcnt==0) {
      fprintf(fpstatus,"no count found, throwing statement out<%s>\n",ptr);
      ( *repeat_nesting )--;
      return(RET_IGNORING_STATEMENT);
      }
   fprintf(fpstatus,"found repeat [%ld] LEVEL[%d]\n",repeatcnt,*repeat_nesting);
   fgets(vector2,READLINELEN-1,fpin1);
   readlinenum++;
   vector2[strlen(vector2)-1]='\0';
   if (0==strstr(vector2,"begin")){ /* not begin */
      if (repeat_forever){
         fprintf(fpout1,"<COND CONT>\n");
         lastwascont=1;
         fprintf(fpout1,"<FLAG (CONT ON)>\n");
         if (tmpholdloop<0) tmpholdloop=12345;
         fprintf(fpout1,"$%s_RF_%d_%d_%d\n",patnameptr,(int)*repeat_nesting,0,tmpholdloop);
         ptr=strchr(vector2,'[');
         expand_vector(newvector,vector2,ptr,__LINE__,__FILE__);
         fprintf(fpout1,"%s\n",newvector);
         fprintf(fpout1,"<CJMP .-1>\n");
         countlines+=5;
         ( *repeat_nesting )--;
         return(RET_NORMAL);
         }
      else {
         fprintf(fpstatus,"oops, not a repeat block,just a repeat vector.\n");
         fprintf(fpout1,"%s\n",vector);
         ptr=strchr(vector2,'[');
         expand_vector(newvector,vector2,ptr,__LINE__,__FILE__);
         fprintf(fpout1,"%s\n",newvector);
         countlines+=2;
         ( *repeat_nesting )--;
         return(RET_NORMAL);
         }
      }
   else { /* begin */
      ( *loop_number )++;
      tmpholdloop=*loop_number;
      if (repeat_forever){
         fprintf(fpout1,"<COND CONT>\n");
         lastwascont=1;
         fprintf(fpout1,"<FLAG(CONT ON)>\n");
         fprintf(fpout1,"$%s_C_%d_%d_%d\n",patnameptr,(int)*repeat_nesting,0,tmpholdloop);
         last_COND=5;/* use this for continuous */
         countlines+=2;
         }
      else {
         if (repeatcnt>65535) {
            fprintf(fpout1,"<LC%d %d>\n<LC%d %d>\n<COND NZC%d>\n",4-(int)*repeat_nesting,10-1,5-(int)*repeat_nesting,(int)repeatcnt/10-1,5-(int)*repeat_nesting);
            if (repeatcnt-10*(int)(repeatcnt/10)) fprintf(fpout1,"(* check me! %d=%d*%d missing loops: %d *)\n",(int)repeatcnt,10,(int)repeatcnt/10,(int)repeatcnt-10*(int)(repeatcnt/10));
            countlines += 4;
            doubleloop |= (1<<(4-(int)*repeat_nesting));
            }
         else {
            fprintf(fpout1,"<LC%d %d>\n<COND NZC%d>\n",5-(int)*repeat_nesting,(int)repeatcnt-1,5-(int)*repeat_nesting);
            countlines += 2;
             doubleloop&=~(1<<(4-(int)*repeat_nesting));
            }
         last_COND=5-(int)*repeat_nesting;
         lastwascont=0;
         fprintf(fpout1,"$%s_R_%d_%d_%d\n",patnameptr,(int)*repeat_nesting,(int)repeatcnt,tmpholdloop);
         countlines++;
         }
      while(fgets(vector2,READLINELEN-1,fpin1) != NULL ){
         readlinenum++;
         vector2[strlen(vector2)-1]='\0';
         if (NULL==strstr(vector2,"end")) {/* not at end */
            if (debug&16) fprintf(fpstatus,"continuing search for end!!!!\n");
            if ((ptr2=strstr(vector2,"repeat"))==0){ /* not a repeat */
               if (NULL!=(ptr=strchr(vector2,'['))) {
                  expand_vector(newvector,vector2,ptr,__LINE__,__FILE__);
                  strcpy(vector2,newvector);
                  }
               fprintf(fpout1,"%s\n",vector2);
               countlines++;
               }
            else {
               fprintf(fpstatus,"found another repeat inside!!!!\n");
               /* the following is somewhat dangerous as it is a recursive call!!! */
               if(debug&1) fprintf(fpstatus,"pre-deal_with_repeat_CPM7\n");
               deal_with_repeat_CPM(fpin1,fpout1,ptr2,repeat_nesting,loop_number,vector2,repeat_cnts,cbuff,patnameptr);
               if(debug&1) fprintf(fpstatus,"post-deal_with_repeat_CPM7\n");
               }
            }
         else { /* found end !!! */
            if (debug&8) fprintf(fpstatus,"FOUND END!!!!\n");
            if (repeat_forever) {
               if (!lastwascont) fprintf(fpout1,"<COND CONT>\"Only needed when COND changed\"\n");
               fprintf(fpout1,"<CJMP %s_C_%d_%d_%d>\n",patnameptr,(int)*repeat_nesting,0,tmpholdloop);
               countlines++; /* no counters needed for repeat forever */
               }
            else {
               if ((doubleloop&(1<<(4-(int)*repeat_nesting)))!=0) {
                  fprintf(fpout1,"<COND NZC%d>\n",5-(int)*repeat_nesting);
                  countlines++;
                  fprintf(fpout1,"<DC%d,CJMP %s_R_%d_%d_%d>\n",5-(int)*repeat_nesting,patnameptr,(int)*repeat_nesting,(int)repeatcnt,tmpholdloop);
                  countlines++;
                  fprintf(fpout1,"<COND NZC%d>\n",4-(int)*repeat_nesting);
                  countlines++;
                  fprintf(fpout1,"<DC%d,CJMP %s_R_%d_%d_%d-2>\n",4-(int)*repeat_nesting,patnameptr,(int)*repeat_nesting,(int)repeatcnt,tmpholdloop);
                  countlines++;
                  fprintf(fpout1,"(* check me! count might be off slightly*)\n");
                  countlines++;
                  doubleloop &= ~(1<<(4-(int)*repeat_nesting));
                  }
               else {
                  if (last_COND!=(5-(int)*repeat_nesting)) {
                     fprintf(fpout1,"<COND NZC%d>\n",5-(int)*repeat_nesting);
                     countlines++;
                     }
                  fprintf(fpout1,"<DC%d,CJMP %s_R_%d_%d_%d>\n",5-(int)*repeat_nesting,patnameptr,(int)*repeat_nesting,(int)repeatcnt,tmpholdloop);
                  countlines++;
                  }
               }
            break;
            } /* else found end !!! */
         } /* end while */
      } /* end if begin */
   ( *repeat_nesting )--;
   if (debug&1) fprintf(fpstatus,"deal_with_repeat_CPM done\n");
   return(RET_GOOD);
   }
