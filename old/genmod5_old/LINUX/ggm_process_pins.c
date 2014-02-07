/* ggm_process_pins.c */
/* process_pins(){} */

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

int process_pins(FILE *fpin2,FILE *fpin3,char *infile3,char *muxpin){
char *ptr,*ptr2,*ptr3;
int i,j,k,actuallist;
char readstr[READLINELEN],pinname[READLINELEN+1];
char tempgrpexpand[READLINELEN*20+1],tempgrpexpand2[READLINELEN*20+1];
   fprintf(stdout,"PROCESSING PINS\n");
   maxpin=0;
   while(fgets(readstr,READLINELEN-1,fpin2) != NULL ){
      readstr[strlen(readstr)-1] = '\0';/* remove trailing \n */
      if (isalnum((int)readstr[0])) {
         for (i=0,j=0;i<strlen(readstr);i++) if (isgraph((int)readstr[i])){PIN[maxpin][j]=readstr[i];j++;}
         PIN[maxpin++][j]='\0';
         }
      if (maxpin==NUMPINS) {
         fprintf(stderr,"SE:MAXPIN exceeded\n");
         fprintf(stdout,"SO:** MAXPIN exceeded **\n");
         exit(2);
         }
     }
   fprintf(stdout,"MAXPIN=%d\n",maxpin);
   /* **** */
   for(i=0;i<maxpin;i++) muxpin[i]='.';
   while(fgets(readstr,READLINELEN-1,fpin3) != NULL ){
      readstr[strlen(readstr)-1] = '\0';/* remove trailing \n */
      /* need to strip comments */
      if (strstr(readstr,"(*")!=NULL || strstr(readstr,"*)")!=NULL) {
         fprintf(stderr,"Please strip comments first in [%s]\n",infile3);
         fprintf(stderr,"Use nedit with RegExp search for:\\(\\*([^$]*)\\*\\)\n");
         fprintf(stderr,"and nothing in the replace with\n");
         fprintf(stderr,"Validate afterwards with normal seach for '(*' [the search above doesn't get multilines]\n");
         fprintf(stderr,"Sorry, this is easier than me figuring it out for you :-(\n");
         exit(2);
         }
      if (NULL!=strstr(readstr,"PinListSetNull")) ; /* do nothing */
      else if (NULL!=strstr(readstr,"PinListSet")) {
         strcpy(tempgrpexpand,readstr);
         while ((ptr=strchr(readstr,')'))==NULL) {
            fgets(readstr,READLINELEN-1,fpin3);   
            if (strstr(readstr,"(*")!=NULL || strstr(readstr,"*)")!=NULL) {
               fprintf(stderr,"Please strip comments first!\n");
               fprintf(stderr,"Use nedit with RegExp search for:\\(\\*([^$]*)\\*\\)\n");
               fprintf(stderr,"and nothing in the replace with\n");
               fprintf(stderr,"Sorry, this is easier than me figuring it out for you :-(\n");
               exit(2);
               }
   
            strcat(tempgrpexpand,readstr);
            }
         for (j=i=0;i<strlen(tempgrpexpand);i++) {/* strip whitespace */
            if (isgraph((int)tempgrpexpand[i])){tempgrpexpand2[j]=tempgrpexpand[i];j++;}
            }
         tempgrpexpand2[j]='\0';
         ptr=strchr(tempgrpexpand2,'(');
         ptr2=strchr(tempgrpexpand2,',');
         *ptr2='\0';

         actuallist=maxlists;
         for (i=0;i<maxlists;i++) {
            if (strcmp(pinlist[i].pinlistname,ptr+1)==0) {
               fprintf(stdout,"**** WARNING: duplicate pinlist [%s] [%s]\n",ptr+1,pinlist[i].pinlistname);
               actuallist=i;
               break;
               }
            }
         if (actuallist==maxlists) {
            pinlist[actuallist].pinlistname[0]='\0';
            for (i=0;i<maxpin;i++) pinlist[actuallist].pinlists[i]='.';
            pinlist[actuallist].pinlists[i]='\0';
            pinlist[actuallist].groups[0]='\0';
            strcpy(pinlist[actuallist].pinlistname,ptr+1);/* copy in the groupname */
            }

         while(NULL!=(ptr3=strchr(ptr2+1,','))) {
            *ptr3='\0';
            strcpy(pinname,(ptr2+1));
            for (i=0;i<maxpin;i++) {
               if (strcmp(PIN[i],pinname)==0) {
                  pinlist[actuallist].pinlists[i]='*';
                  break;
                  }
               }
            *ptr2=',';   
            if (i==maxpin && actuallist==maxlists) strcat(pinlist[actuallist].groups,ptr2);/* not a pin */
            ptr2=ptr3;
            }
         ptr3=strchr(ptr2+1,')');
         *ptr3='\0';
         strcpy(pinname,(ptr2+1));
         for (i=0;i<maxpin;i++) {
            if (strcmp(PIN[i],pinname)==0) {
               pinlist[actuallist].pinlists[i]='*';
               break;
               }
            }
         *ptr2=',';   
         if (actuallist==maxlists) {
            if (i==maxpin) strcat(pinlist[actuallist].groups,ptr2); /* not a pin */
            maxlists++;
            if (maxlists==MAXlists) {
               fprintf(stderr,"maxlists exceeded\n");
               exit(2);
               }
            }
         }
   
      else if (NULL!=(ptr2=(strstr(readstr,"PinSetMuxPP"))) ||
               NULL!=(ptr2=(strstr(readstr,"PinSetMuxMP")))) {
         for (j=i=0;i<strlen(readstr);i++) {/* strip whitespace */
            if (isgraph((int)readstr[i])){tempgrpexpand2[j]=readstr[i];j++;}
            } /* end strip white space */
         ptr =strchr(tempgrpexpand2,'(');
         ptr2=strchr(tempgrpexpand2,',');
         if (ptr!=NULL && ptr!=NULL) {
            fprintf(stdout,"found MUX![%s]\n",ptr);
            *ptr2='\0';
            for (i=0;i<maxpin;i++) if (0==strcmp(ptr+1,PIN[i])){
               muxpin[i]='M';
               break;
               }
            }
         } /* else pinsetMux */
   
     }
   /* need final step of replacing all groups with their pins */
   for (i=0;i<maxlists;i++) {
      if (pinlist[i].groups[0]=='\0') continue;
      ptr=strchr(pinlist[i].groups,',');
      ptr2=strchr(ptr+1,',');
      while(ptr!=NULL){
         if (ptr2!=NULL) *ptr2='\0';
   //      fprintf(stdout,"<%s>\n",ptr+1);
         for (j=0;j<maxlists;j++) {
            if (j==i) continue;
            if (strcmp(ptr+1,pinlist[j].pinlistname)==0) {
               for (k=0;k<maxpin;k++) if (pinlist[j].pinlists[k]=='*') {
                  pinlist[i].pinlists[k]='*';
                  }
               }
            }
         if (ptr2!=NULL) {
            *ptr2=',';
            ptr=ptr2; 
            ptr2=strchr(ptr+1,',');
            }
         else ptr=NULL;
         }
      }
   fprintf(stderr,"GOOD! got groups!\n");
   /* **** */
   return(0);
   }
