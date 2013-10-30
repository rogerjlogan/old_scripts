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
#include "includes_appn.h"

int expand_vector(char *newvector, char *vector, char *ptr, int callfrom, char *file)
{
	char bitchar,bitexpand[360];
//  char hexword[MXFIELD],hexword2[MXFIELD];
	char localvector[READLINELEN + 1], preXvector[READLINELEN + 1], tempv2[READLINELEN + 1];
	char *ptr2, *ptrBC, *newptr, *cmmaptr, *bgptr, *tv2ptr, *ptrR, *ptrW, *ptrCM, *ptrBF, *ptrMP;
	int i, j, k, howmany,w;
#define alphaHEXhex 16+6+2
	char hexletter[alphaHEXhex + 1] = { "0123456789ABCDEFabcdefXx" };	/* 'X' & 'x' might come from defines, assume '0' */
	char hexbits[alphaHEXhex][5] = { "0000", "0001", "0010", "0011", "0100", "0101", "0110", "0111", "1000", "1001",	/* 0-9 */
		"1010", "1011", "1100", "1101", "1110", "1111",	/* A-F */
		"1010", "1011", "1100", "1101", "1110", "1111",	/* a-f */
//		"A0A0", "B0BB", "CC00", "DD0D", "EEE0", "FFFF",	/* A-F */
//		"a0a0", "b0bb", "cc00", "dd0d", "eee0", "ffff",	/* a-f */
		"0000", "0000"
	};							/* X & x from defines, !assume! 0 */
	int trace = 0;

	if (fields==1) {
		strcpy(newvector,vector);
		return(1);
		}

	/* do not mess with original vector */
	strcpy(preXvector, vector);
	newptr = preXvector + (ptr - vector);	/* get offset */

	ptrBC = strrchr(preXvector, '[');	/* verify that the ptr we were given was really the one we wanted (i.e. its not in a comment) */
	if ((ptr - vector) != (ptrBC - preXvector)) {
		fprintf(fpstatus, "You gave expand_vector an open bracket that was in a comment! Caller:[%s][%d]\n", file, callfrom);
		fprintf(fpstatus, "OVCTR:[%s]\n       ", vector);
		for (i = 0; i < (ptr - vector) && i < 1000; i++) fputc('-', fpstatus);
		fputc('^', fpstatus);
		fputc('\n', fpstatus);
		fprintf(fpstatus, "fixing:\n       ");
		for (i = 0; i < (ptrBC - preXvector); i++) fputc('-', fpstatus);
		fputc('^', fpstatus);
		fputc('\n', fpstatus);
		newptr = preXvector + (ptrBC - preXvector);	/* get offset */
	}
	ptrR = ptrW = (ptrBC + 1);
	while (*ptrR != '\0') {
		if (!isspace(*(ptrR))) *(ptrW++) = *ptrR;
		ptrR++;
	}
	*ptrW = '\0';
//  if (ptrR!=ptrW) {
//      fprintf(fpstatus,"SPACES replaced\nI[%s]\nO[%s]\n",vector,preXvector);
//      }

/* The following block of code will pad out any 'x' or 'X' fields to */
/*  the correct number of digits before processing. */
	tempv2[0] = '\0';
	cmmaptr = newptr + 1;
	bgptr = newptr + 1;
	tv2ptr = tempv2;			/* put the GCT (MDI) in first */
	tv2ptr += strlen(tempv2);
//  fprintf(fpstatus,"BGPTR[%s]tv2[%s]\n",bgptr,tv2ptr);
	for (i = 0; i < fields; i++) {
		if ((cmmaptr = strchr(bgptr, ',')) != NULL) {
			if (*(cmmaptr - 1) == 'x' || *(cmmaptr - 1) == 'X') {
				howmany = (phd_sp[i] - phd_st[i] + 1);
				for (j = 0; j < howmany; j++) *(tv2ptr++) = 'x';
				*(tv2ptr) = '\0';
			}
			else {
				*cmmaptr = '\0';
				strcat(tempv2, bgptr);
				tv2ptr += strlen(bgptr);
				*cmmaptr = ',';
			}
			*(tv2ptr++) = ',';
			*(tv2ptr) = '\0';
			bgptr = cmmaptr + 1;
		}
		else if (i == (fields - 1) && (cmmaptr = strchr(bgptr, ']')) != NULL) {
			if (*(cmmaptr - 1) == 'x' || *(cmmaptr - 1) == 'X') {
				howmany = (phd_sp[i] - phd_st[i] + 1);
				for (j = 0; j < howmany; j++) *(tv2ptr++) = 'x';
				*(tv2ptr) = '\0';
			}
			else {
				*cmmaptr = '\0';
				strcat(tempv2, bgptr);
				tv2ptr += strlen(bgptr);
				*cmmaptr = ']';	/* this is the last field! */
			}
			*(tv2ptr++) = ']';
			*(tv2ptr++) = ';';	/* this is the last field! */
			*(tv2ptr) = '\0';
			bgptr = cmmaptr + 1;
		}
	}
	if (fields > 1) {
		*(newptr + 1) = '\0';	/* reset back to beginning of the vector, after the gct */
		strcat(preXvector, tempv2);
		newptr = preXvector + (ptr - vector);	/* get offset */
	}

	bitchar = *(newptr + 1);
	*(newptr + 1) = '\0';
	strcpy(localvector, preXvector);
	*(newptr + 1) = bitchar;

//  fprintf(fpstatus,"IN [%s]\nOUT[%s]LV[%s]\n",vector,preXvector,localvector);

	if (fields > 1) {
		ptrBF = newptr + 1;
		for (i = 0; i < fields; i++) {
			ptrCM = strchr(ptrBF, ',');
			if (ptrCM == NULL) ptrCM = strchr(ptrBF, ']');
			if (ptrCM == NULL) {
				fprintf(stderr,
						"[%s]not enough fields provided, looking for Field[%d]at line[%ld]\ncallingfile[%s]callingline[%d]!\n",
						infile_orig, i + 1, readlinenum, file, callfrom);
				fprintf(fperrors,
						"[%s]not enough fields provided, looking for Field[%d]at line[%ld]\ncallingfile[%s]callingline[%d]!\nOVCTR:%s\nNVCTR:%s\n",
						infile_orig, i + 1, readlinenum, file, callfrom, vector, localvector);
				break;
			}
			else {
				for (j = 0; j < fieldcount[i]; j++)
					localvector[(ptr - vector) + 1 + fieldstart[i] + j] = '0';	/* pad out first */
				localvector[(ptr - vector) + 1 + fieldstart[i] + j] = '\0';
				*ptrCM = '\0';
				if (strlen(ptrBF) > fieldcount[i] && fieldtype[i] == 'B') {
//                  fprintf(stderr,"[%s] has too many characters in binary field[%d] line[%ld],Exp[%d]Got[%d],truncating\n",infile_orig,i+1,readlinenum,fieldcount[i],strlen(ptrBF));
//                  fprintf(fperrors,"[%s] has too many characters in binary field[%d] line[%ld],Exp[%d]Got[%d],truncating\n",infile_orig,i+1,readlinenum,fieldcount[i],strlen(ptrBF));
				}
				if (strlen(ptrBF) > (fieldcount[i] / 4) && fieldtype[i] == 'H') {
//                  fprintf(stderr,"[%s] has too many characters in hex field[%d] line[%ld],Exp[%d]Got[%d]truncating\n",infile_orig,i+1,readlinenum,(fieldcount[i]/4),strlen(ptrBF));
//                  fprintf(fperrors,"[%s] has too many characters in hex field[%d] line[%ld],Exp[%d]Got[%d],truncating\n",infile_orig,i+1,readlinenum,(fieldcount[i]/4),strlen(ptrBF));
				}
				if (fieldtype[i] == 'B') {
					ptrMP = (ptrCM - 1);
					for (j = (strlen(ptrBF) - 1); j >= 0; j--, ptrMP--) {
						localvector[(ptr - vector) + 1 + fieldstart[i] + j] = (*ptrMP == 'x' || *ptrMP == 'X') ? '0' : *ptrMP;
					}
				}
				else {			/* hex */
					ptrMP = (ptrCM - 1);
					if (trace) fputc('\n',stdout);
					w=fieldcount[i];
					bitexpand[w] = bitexpand[w+1] = '\0';
					if (trace) fprintf(stdout,"(%d)",strlen(ptrBF));
					for (j = ((strlen(ptrBF) - 1) * 4); j >= 0; j -= 4, ptrMP--) {
						if (trace) fputc(*ptrMP,stdout);
						ptr2 = strchr(hexletter, *ptrMP);
						if (ptr2 == NULL) {
							fprintf(stderr, "NON-HEX CHAR![%c]\n", *ptrMP);
							fprintf(fperrors, "FATAL-ERROR:NON-HEX CHAR![%c] in [%s]\n", *ptrMP, infile_orig);
							RESULT_BAD = 2;
							ptr2 = hexletter;
						}
						else {
							k=3;
							if (trace) fprintf(stdout,"{%d,%d,%d,%d}",fieldcount[i],fieldcount[i]-k-j,k >= 0,((fieldcount[i] - k - j) > 0));
							for (k = 3; k >= 0 && w>0; k--) {
								w--;
								localvector[(ptr - vector) + 1 + fieldstart[i] + w] = hexbits[ptr2 - hexletter][k];
//								if (trace) localvector[(ptr - vector) + 1 + fieldstart[i] + w] = *ptrMP;
								bitexpand[w] = hexbits[ptr2 - hexletter][k];
								if (trace) fprintf(stdout,"<%c>",hexbits[ptr2-hexletter][k]);
							}
						}
					if (trace) fprintf(stdout,"(%s)",bitexpand);
					} /* j= each char */
				} /* hex */
				if (i == (fields - 1)) *ptrCM = ']';
				else *ptrCM = ',';
				ptrBF = ptrCM + 1;
			}
		} /* field  */
	
	}
//    for (i=0;i<fields;i++) {
//       bitchar=*(newptr+1+phd_sp[i]+1);
//       if (bitchar!=',' && bitchar!=']') {
//          fprintf(stderr,"[%s]OOPS! we're misaligned[approxvector:%ld]Field[%d][%c]callingfile[%s]callingline[%d]!\n",infile_orig,readlinenum,i+1,bitchar,file,callfrom);
//          fprintf(fperrors,          "[%s]Misalign:[approxvector:%ld]Field[%d][%c]callingfile[%s]callingline[%d]!\nOVCTR:%s\nNVCTR:%s\n",infile_orig,readlinenum,i+1,bitchar,file,callfrom,vector,localvector);
//          RESULT_BAD=1;
//          }
//       *(newptr+1+phd_sp[i]+1)='\0';
//       /* FIXME: APS need to put something in here to prepad fields with '0' */
//       strcpy(hexword,newptr+1+phd_st[i]);
//       *(newptr+1+phd_sp[i]+1)=bitchar;
//       if (fieldtype[i]=='B') strcat(localvector,hexword);
//       else { /* hex */
//          hexword[0]='\0';
//          for (j=0;j<(int)((fieldcount[i]+3)/4);j++) {/* this is to round 4/4->1,5/4->2,6/4->2,7/4->2 */
//             ptr2=strchr(hexletter,*(newptr+1+phd_st[i]+j));
//             if (ptr2==NULL) {
//                fprintf(stderr,"NON-HEX CHAR![%c]\n",*(newptr+1+phd_st[i]+j));
//                fprintf(fperrors,"FATAL-ERROR:NON-HEX CHAR![%c] in [%s]\n",*(newptr+1+phd_st[i]+j),infile_orig);
//                RESULT_BAD=2;
//                  ptr2=hexletter;
//                }
//             strcat(hexword,hexbits[ptr2-hexletter]);
//             }
//          /* take the last fieldcount[i] bits of hexword */
//          strcpy(hexword2,hexword+(strlen(hexword)-fieldcount[i]));
//          strcat(localvector,hexword2);
//          }
//       }
	newptr = strrchr(preXvector, ']');
	if (newptr != NULL) {
		strcat(localvector, newptr);
	}
	strcpy(newvector, localvector);
//  fprintf(fpstatus,"__%s__\n",newvector);
//  fprintf(fpstatus,"{{%s}}\n",preXvector);
//  fprintf(fpstatus,"<<%s>>\n",vector);
	return (0);
}
