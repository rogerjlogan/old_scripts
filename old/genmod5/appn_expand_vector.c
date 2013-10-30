/* appn_expand_vector.c export_vector(){} */

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

int expand_vector(char *newvector,char *vector,char *ptr,int callfrom,char *file){
   char bitchar,hexword[MXFIELD],hexword2[MXFIELD],localvector[READLINELEN+1],tvector[READLINELEN+1];
   char *ptr2,*ptrBC,*newptr;
   int i,j;
   #define alphaHEXhex 16+6+2
   char hexletter[alphaHEXhex+1]={"0123456789ABCDEFabcdefXx"};/* 'X' & 'x' might come from defines, assume '0' */
   char hexbits[alphaHEXhex][5]={"0000","0001","0010","0011","0100","0101","0110","0111","1000","1001",/* 0-9 */
                        "1010","1011","1100","1101","1110","1111", /* A-F */
                        "1010","1011","1100","1101","1110","1111", /* a-f */
                        "0000","0000"}; /* X & x from defines, !assume! 0 */
   
   /* do not mess with original vector */
   strcpy(tvector,vector);
   newptr=tvector+(ptr-vector);/* get offset */
   
   ptrBC=strrchr(tvector,'['); /* verify that the ptr we were given was really the one we wanted (i.e. its not in a comment) */
   if ((ptr-vector)!=(ptrBC-tvector)) {
      fprintf(fpstatus,"You gave expand_vector an open bracket that was in a comment! Caller:[%s][%d]\n",file,callfrom);
      fprintf(fpstatus,"OVCTR:[%s]\n       ",vector);
      for(i=0;i<(ptr-vector)&&i<1000;i++) fputc('-',fpstatus);fputc('^',fpstatus);fputc('\n',fpstatus);
      fprintf(fpstatus,"fixing:\n       ");
      for(i=0;i<(ptrBC-tvector);i++) fputc('-',fpstatus);fputc('^',fpstatus);fputc('\n',fpstatus);
      newptr=tvector+(ptrBC-tvector);/* get offset */
      }
   
   localvector[0]='\0';
   
   bitchar=*(newptr+1);
   *(newptr+1)='\0';
   
   strcpy(localvector,tvector);
   
   *(newptr+1)=bitchar;
   
// fprintf(fpstatus,"PV%s\nNV[%s]",localvector,newptr+1);
   for (i=0;i<fields;i++) {
      bitchar=*(newptr+1+phd_sp[i]+1);
      if (bitchar!=',' && bitchar!=']') {
         fprintf(stderr,"OOPS![%d][%c],we're misaligned! Report this number[%s][%d]!\n",i,bitchar,file,callfrom);
         fprintf(fpstatus,"@[%d]Report this number[%s][%d]!\nOVCTR:%s\nNVCTR:%s\n",i,file,callfrom,vector,localvector);
         exit(7);
         }
      *(newptr+1+phd_sp[i]+1)='\0';
      /* FIXME: APS need to put something in here to prepad fields with '0' */
      strcpy(hexword,newptr+1+phd_st[i]);
      *(newptr+1+phd_sp[i]+1)=bitchar;
      if (fieldtype[i]=='B') strcat(localvector,hexword);
      else { /* hex */
         hexword[0]='\0';
         for (j=0;j<(int)((fieldcount[i]+3)/4);j++) {/* this is to round 4/4->1,5/4->2,6/4->2,7/4->2 */
            ptr2=strchr(hexletter,*(newptr+1+phd_st[i]+j));
            if (ptr2==NULL) {
               fprintf(stderr,"NON-HEX CHAR![%c]\n",*(newptr+1+phd_st[i]+j));
               fprintf(fperrors,"FATAL-ERROR:NON-HEX CHAR![%c] in [%s]\n",*(newptr+1+phd_st[i]+j),infile_orig);
               exit(6);
               }
            strcat(hexword,hexbits[ptr2-hexletter]);
            }
         /* take the last fieldcount[i] bits of hexword */
         strcpy(hexword2,hexword+(strlen(hexword)-fieldcount[i]));
         strcat(localvector,hexword2);
         }
      }
   newptr=strrchr(tvector,']');
   if (newptr!=NULL) {
      strcat(localvector,newptr);
      }
   strcpy(newvector,localvector);
// fprintf(fpstatus,"{{%s}}\n",tvector);
// fprintf(fpstatus,"<<%s>>\n",vector);
   return(0); 
   }
