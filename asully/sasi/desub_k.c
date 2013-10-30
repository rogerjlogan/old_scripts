#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <zlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "common_includes.h"
#define READLINELEN 65535
#define FILENAMELEN 1000

#define KEEP_YES 1
#define KEEP_NO 0
/* function prototypes: */
int remove_comments(char *inout, char *comment, int keep, char *stophere);
char *find_close(char *ptrCR, char *ptrNCR, char *comment, char *stophere);
int remove_multispace(char *ptrCR, char *pbuf);

/* globals: */
FILE *fperrors, *fpstatus;

/* begin main function */
int main(int argc, char *argv[])
{
/* file variables */
	FILE *fpin1, *fpin2;
	gzFile *fpout;
	char infile1[FILENAMELEN], infile2[FILENAMELEN], outfile[FILENAMELEN];
	char tinfile1[FILENAMELEN], tinfile2[FILENAMELEN];
	char G_progstr[MEMOSTRLEN], G_datestr[MEMOSTRLEN],
		G_timestr[MEMOSTRLEN];
	char G_compilestr[MEMOSTRLEN];	/* concaternated strings */
	char command[MEMOSTRLEN], readline[READLINELEN + 1],
		commentbuf[READLINELEN + 1], tempstr[READLINELEN + 1];
	char pbuf[READLINELEN + 1];
	char *F1BUF, *F2BUF;
	char *ptrZ, *ptrCR, *ptrNCR, *ptrOP, *ptrCL, *ptrcommaSTART,
		*ptrcommaSTOP, *ptrVALFUNC;
	int gzin1 = 0, gzin2 = 0, beginend = 0, started = 0, found;
	int multiline, sbrtcnt = 0, pprint, good;
	int i, j, k, m;
	off_t bytes2read1, bytes2read2;
	struct stat stat1, stat2;
	typedef struct SUBRT {
#define maxparams 10
#define maxparamlen 100
#define maxlines 1000
		char *name;
		int numparams, numlines, containsmatch, used;
		char paramnames[maxparams][maxparamlen + 1];
		char *begin, *end;
		char *lines[maxlines];
	} SUBRT;
#define MAXSBRT 20
	SUBRT subrt[MAXSBRT];
	int maxsbrt;

	strcpy(G_compilestr, argv[0]);
	strcpy(G_progstr, __FILE__);
	strcpy(G_datestr, __DATE__);
	strcpy(G_timestr, __TIME__);
	fprintf(stderr, "%s: %s\n", G_progstr, G_compilestr);
	fprintf(stderr, "%s by Anthony Sully\n", G_datestr);

	fprintf(stderr,
			"\n\n\nThis code is supplied under the LTX-Credence Shareware License.\n");
	fprintf(stderr,
			"Please see the LSLV1.2 file in the document directory for a full text.\n\n\n");
	if (argc == 3) {
		strcpy(infile1, (char *) argv[1]);
		strcpy(infile2, (char *) argv[2]);
	}
	else {
		fprintf(stderr, "Syntax: %s patfile subroutinefile\n",
				G_compilestr);
		exit(1);
	}
	if (NULL == (fperrors = fopen(TRANSLATION_ERRORS, "a"))) {
		fprintf(stderr, "\nFATAL_ERROR:%s:Could not open %s for output\n",
				G_compilestr, TRANSLATION_ERRORS);
		exit(1);
	}
	if (NULL == (fpstatus = fopen(TRANSLATION_STATUS, "a"))) {	/* replaces the fpstatus messages */
		fprintf(stderr,
				"\nFATAL_ERROR:%s:Could not open %s for append output[%s,%d,%s]\n",
				G_compilestr, TRANSLATION_STATUS, __FILE__, __LINE__,
				__FUNCTION__);
		exit(1);
	}

	strcpy(tinfile1, infile1);	/* if neither .gz or .Z then fall through */
	if ((ptrZ = strstr(infile1, ".Z")) != NULL) {
		*ptrZ = '\0';
		sprintf(command, "uncompress -c %s > /tmp/%s", tinfile1, infile1);
		system(command);
		sprintf(tinfile1, "/tmp/%s", infile1);
		gzin1 = 1;
	}
	else if ((ptrZ = strstr(infile1, ".gz")) != NULL) {
		*ptrZ = '\0';
		sprintf(command, "gunzip -c %s > /tmp/%s", tinfile1, infile1);
		system(command);
		sprintf(tinfile1, "/tmp/%s", infile1);
		gzin1 = 1;
	}

	strcpy(tinfile2, infile2);	/* if neither .gz or .Z then fall through */
	if ((ptrZ = strstr(infile2, ".Z")) != NULL) {
		*ptrZ = '\0';
		sprintf(command, "uncompress -c %s > /tmp/%s", tinfile2, infile2);
		system(command);
		sprintf(tinfile2, "/tmp/%s", infile2);
		gzin2 = 1;
	}
	else if ((ptrZ = strstr(infile2, ".gz")) != NULL) {
		*ptrZ = '\0';
		sprintf(command, "gunzip -c %s > /tmp/%s", tinfile2, infile2);
		system(command);
		sprintf(tinfile2, "/tmp/%s", infile2);
		gzin2 = 1;
	}

	stat(tinfile1, &stat1);
	stat(tinfile2, &stat2);
	bytes2read1 = stat1.st_size;
	bytes2read2 = stat2.st_size;
	fprintf(stdout, "BytesreadMain[%ld] BytereadSUBRT[%ld]\n", bytes2read1,
			bytes2read2);
	F1BUF = malloc(bytes2read1 + 20);	/* allow some slop for '\0' at eof */
	F2BUF = malloc(bytes2read2 + 20);	/* allow some slop for '\0' at eof */
	if (F1BUF == NULL || F2BUF == NULL) {
		fprintf(stderr, "can't allocate requested memory!\n");
		exit(1);
	}

	if (NULL == (fpin1 = fopen(tinfile1, "r"))) {
		fprintf(stderr, "Can't open first file[%s]\n", tinfile1);
		exit(1);
	}
	if (NULL == (fpin2 = fopen(tinfile2, "r"))) {
		fprintf(stderr, "Can't open second file[%s]\n", tinfile2);
		exit(1);
	}
	fread(F1BUF, bytes2read1, 1, fpin1);
	fread(F2BUF, bytes2read2, 1, fpin2);
	F1BUF[bytes2read1] = '\n';
	F2BUF[bytes2read2] = '\n';
	F1BUF[bytes2read1 + 1] = '\0';
	F2BUF[bytes2read2 + 1] = '\0';
	fclose(fpin1);
	fclose(fpin2);
	if (gzin1) {
		remove(tinfile1);
	}
	if (gzin2) {
		remove(tinfile2);
	}

	sprintf(outfile, "%s_.gz", infile1);
	if (NULL == (fpout = gzopen(outfile, "w"))) {
		fprintf(stderr, "can't open output file[%s]\n", outfile);
		exit(1);
	}
/* step 0: erase comments */

	ptrCR = F2BUF;
	remove_comments(ptrCR, commentbuf, KEEP_NO, F2BUF + bytes2read2);

/* step 1: replace all carriage returns with '\0' and save in SUBRT.lines[] */

/****************** first run with subroutines file *******************/
	ptrCR = F2BUF;
	maxsbrt = -1;				/* initialize to -1 so we can increment when we get the first one */
	while ((ptrNCR = strchr(ptrCR, '\n')) != NULL) {
		*ptrNCR = '\0';

/* step 2: save the name of the subroutine and its start */
		if (strstr(ptrCR, "external hardware subroutine") != NULL ||
			strstr(ptrCR, "external hardware Subroutine") != NULL);
		else if (strstr(ptrCR, "subroutine") != NULL
				 || strstr(ptrCR, "Subroutine") != NULL) {
			maxsbrt++;
			subrt[maxsbrt].numlines = subrt[maxsbrt].containsmatch = 0;
			subrt[maxsbrt].name = ptrCR + sizeof("subroutine");	/* this is a ptr */
			beginend = started = 0;
			subrt[maxsbrt].numparams = i = subrt[maxsbrt].used = 0;
			ptrZ = ptrOP = strchr(ptrCR, '(');
			if (ptrOP != NULL) {
				*ptrOP = '\0';
				*(ptrZ--) = '\0';
				ptrOP++;
				ptrCL = strchr(ptrOP, ')');
				if (ptrCL != NULL)
					ptrCL--;
			}
			while (ptrOP <= ptrCL && ptrOP != NULL && ptrCL != NULL) {
				if (*ptrOP == ',') {
					subrt[maxsbrt].paramnames[subrt[maxsbrt].
											  numparams][i++] = ';';
					subrt[maxsbrt].paramnames[subrt[maxsbrt].
											  numparams][i] = '\0';
					subrt[maxsbrt].numparams++;
					i = 0;
					ptrOP++;	/* get past ',' */
				}
				if (!isspace(*ptrOP)) {
					subrt[maxsbrt].paramnames[subrt[maxsbrt].
											  numparams][i++] = *(ptrOP++);
				}
				ptrCR = ptrOP;
				while (isspace(*ptrZ))
					*(ptrZ--) = '\0';	/* blank out any terminating spaces */
			}
			subrt[maxsbrt].paramnames[subrt[maxsbrt].numparams][i++] = ';';
			subrt[maxsbrt].paramnames[subrt[maxsbrt].numparams][i] = '\0';
			if (i <= 1)
				subrt[maxsbrt].numparams--;	/* so, if there are no parameters i=-1 */
		}
		else if (beginend == 0 && started == 0) {
			if (strstr(ptrCR, "begin") != NULL) {
				subrt[maxsbrt].numlines = 0;
				subrt[maxsbrt].begin = ptrCR;
				started = 1;
				beginend = 1;
			}
		}
		else if (strstr(ptrCR, "begin") != NULL) {
			beginend++;
			subrt[maxsbrt].lines[subrt[maxsbrt].numlines] = ptrCR;
			subrt[maxsbrt].numlines++;
		}
		else if (beginend == 1 && strstr(ptrCR, "end") != NULL) {
			beginend--;
			subrt[maxsbrt].end = ptrCR;
/* done with this subroutine */
		}
		else if (beginend != 1 && strstr(ptrCR, "end") != NULL) {
			beginend--;
			subrt[maxsbrt].lines[subrt[maxsbrt].numlines] = ptrCR;
			subrt[maxsbrt].numlines++;
		}
		else if (strstr(ptrCR, "match") != NULL) {
			fprintf(stdout, "Warning, subroutine[%s] contains match!\n",
					subrt[maxsbrt].name);
			fprintf(stdout,
					"         this will force CPM for all patterns that use it!\n");
			fprintf(fpstatus, "Warning, subroutine[%s] contains match!\n",
					subrt[maxsbrt].name);
			fprintf(fpstatus,
					"         this will force CPM for all patterns that use it!\n");
			subrt[maxsbrt].containsmatch = 1;
			subrt[maxsbrt].lines[subrt[maxsbrt].numlines] = ptrCR;
			subrt[maxsbrt].numlines++;
		}
		else {
			subrt[maxsbrt].lines[subrt[maxsbrt].numlines] = ptrCR;
			subrt[maxsbrt].numlines++;
		}
		ptrCR = ptrNCR + 1;
	}
	fprintf(stdout, "SUBROUTINES AVAILABLE[%d]\n", maxsbrt);

/****************** now run with pattern to translate *******************/
	ptrCR = F1BUF;
	while ((ptrNCR = strchr(ptrCR, '\n')) != NULL
		   && ptrCR < (F1BUF + bytes2read1)) {
		*ptrNCR = '\0';
		commentbuf[0] = '\0';
		multiline =
			remove_comments(ptrCR, commentbuf, KEEP_YES,
							F1BUF + bytes2read1);
//              fprintf(stdout,"***[%s]<%s>%p,%p\n",ptrCR,commentbuf,ptrCR,ptrNCR);
		if (multiline) {
			ptrNCR = strchr(ptrCR, '\n');
			if (ptrNCR != NULL)
				*ptrNCR = '\0';
		}
		ptrNCR =
			find_close(ptrCR, ptrNCR, commentbuf, F1BUF + bytes2read1);
//              fprintf(stdout,"V[%s]\n",ptrCR);
//              fprintf(stdout,"***[%s]<%s>%p,%p\n",ptrCR,commentbuf,ptrCR,ptrNCR);
/* now we can process with comments removed */
		if (strstr(ptrCR, "external subroutine") != NULL ||
			strstr(ptrCR, "external hardware subroutine") != NULL) {
			gzprintf(fpout, "{%s comment[%s]}\n", ptrCR, commentbuf);
//                      fprintf(stdout,"{%s comment[%s]}\n",ptrCR,commentbuf);
/* now we only print the subroutines that we actually use! */
			for (i = 0; i <= maxsbrt; i++) {
				if (strstr(ptrCR, subrt[i].name) != NULL) {
					sbrtcnt++;
					if (subrt[i].containsmatch == 1) {
						fprintf(stderr,
								"Pattern[%s] uses match subroutine[%s] (forces CPM)\n",
								infile1, subrt[i].name);
						fprintf(stdout,
								"Pattern[%s] uses match subroutine[%s] (forces CPM)\n",
								infile1, subrt[i].name);
						fprintf(fperrors,
								"Pattern[%s] uses match subroutine[%s] (forces CPM)\n",
								infile1, subrt[i].name);
						fprintf(fperrors,
								"   You may want to attempt this with threading instead.\n");
					}
					fprintf(stdout, "SBR[%s][%d]NL=%d\n", subrt[i].name, i,
							subrt[i].numlines);
					subrt[i].used = 1;
					gzprintf(fpout, "{N[%s]ML[%d]NP[%d]B[%s]E[%s]}\n",
							 subrt[i].name, subrt[i].numlines,
							 subrt[i].numparams, subrt[i].begin,
							 subrt[i].end);
					if (subrt[i].numparams >= 0) {
						for (j = 0; j <= subrt[i].numparams; j++) {
							gzprintf(fpout, "{P%d[%s]}\n", j,
									 subrt[i].paramnames[j]);
						}
					}
					for (j = 0; j < subrt[i].numlines; j++) {
						if (subrt[i].lines[j][0] != '\0')
							gzprintf(fpout, "{S[%d]L[%d]S[%s]}\n", i, j,
									 subrt[i].lines[j]);
					}
				}
			}
		}
		else {
			for (found = i = 0; i <= maxsbrt; i++) {
				strcpy(readline, ptrCR);
				if ((ptrVALFUNC = strstr(readline, subrt[i].name)) != NULL) {
					ptrVALFUNC += strlen(subrt[i].name);
					good = 0;
					fprintf(fpstatus,
							"Validating if this is[%s] a function call...",
							subrt[i].name);
					while (*ptrVALFUNC != '\n') {
						if (isspace(*ptrVALFUNC)) {
							ptrVALFUNC++;
						}
						if (*ptrVALFUNC == '(') {
							good = 1;
							fprintf(fpstatus, "Yes\n");
							break;
						}
						else {
							good = 0;
							fprintf(fpstatus, "No\n");
							break;
						}
					}
					if (good) {
						if (subrt[i].used == 0 || subrt[i].used == -1) {
							subrt[i].used = -1;
							fprintf(stderr,
									"Pattern[%s] uses subroutine[%s] but does not\n",
									infile1, subrt[i].name);
							fprintf(stderr,
									" reference it with \"external subroutine\"; not installing subroutine\n");
							fprintf(fperrors,
									"Pattern[%s] uses subroutine[%s] but does not\n",
									infile1, subrt[i].name);
							fprintf(fperrors,
									" reference it with \"external subroutine\"; not expanding this subroutine\n");
							continue;
						}
//                                              fprintf(stdout,"Next is subroutine [%s]\n",subrt[i].name);
						gzprintf(fpout,
								 "{Next is subroutine [%s] comment[%s]}\nbegin\n",
								 subrt[i].name, commentbuf);
						for (j = 0; j < subrt[i].numlines; j++) {
							if (subrt[i].numparams == -1) {
								gzprintf(fpout, "%s\n", subrt[i].lines[j]);
								found = 1;
							}
							else {
								pprint = 0;
								ptrOP = strchr(ptrCR, '(');	/* ) */
/* ( */ ptrcommaSTOP = ptrCL =
									strstr(ptrCR, ");");
								if (ptrCL != NULL)
									*ptrCL = '\0';
								for (k = 0; k <= subrt[i].numparams; k++) {
									if (strstr(subrt[i].lines[j], subrt[i].paramnames[k]) != NULL) {	/* its a parameter */
										ptrcommaSTART = ptrOP + 1;
										for (m = 0; m <= k; m++) {
											ptrcommaSTOP =
												strchr(ptrcommaSTART, ']');
											if (ptrcommaSTOP != NULL) {
												*(ptrcommaSTOP + 1) = '\0';
												if (m != k)
													ptrcommaSTART =
														ptrcommaSTOP + 2;
											}
										}
										pprint++;
										found = 1;
										remove_multispace(ptrcommaSTART,
														  pbuf);
										sprintf(tempstr, "%s;{%s}\n", pbuf,
												subrt[i].lines[j]);
										gzprintf(fpout, "%s", tempstr);
									}
								}	/* k */
								if (pprint == 0) {
									remove_multispace(subrt[i].lines[j],
													  pbuf);
									gzprintf(fpout, "%s\n", pbuf);
								}
							}
						}		/* j */
						gzprintf(fpout, "end;\n");
					}
				}				/* is subrt */
			}					/* for subrt */
			remove_multispace(ptrCR, pbuf);
			if (found != 1)
				gzprintf(fpout, "%s %c%s%c\n", pbuf,
						 (commentbuf[0] == '\0') ? ' ' : '{', commentbuf,
						 (commentbuf[0] == '\0') ? ' ' : '}');
		}						/* else */
		ptrCR = (ptrNCR + 1);
	}							/* while */
	fprintf(stdout, "SUBROUTINES USED[%d] ", sbrtcnt);
	for (i = 0; i < maxsbrt; i++)
		if (subrt[i].used == 1)
			fprintf(stdout, ",%s", subrt[i].name);
	fputc('\n', stdout);
	fprintf(stdout, "SUBROUTINES called but not declared: ");
	for (i = 0; i < maxsbrt; i++)
		if (subrt[i].used == -1)
			fprintf(stdout, ",%s", subrt[i].name);
	fputc('\n', stdout);

//
	gzclose(fpout);
	free(F1BUF);
	free(F2BUF);
	return (0);
}

int remove_comments(char *inout, char *comment, int KEEP, char *stophere)
{
	char *ptrCR, *ptrOP, *ptrCL, *ptrCCP, *ptrNEW, *ptrTEMP;
	int removedp = 0, removedb = 0, len, multiline = 0;
	ptrCR = inout;
	ptrCCP = comment;
	len = 0;
	ptrTEMP = NULL;
	while ((ptrOP = strstr(ptrCR, "(*")) != NULL) {	/* ) */
/* (* */ ptrCL = strstr(ptrOP, "*)");
		if (ptrCL != NULL) {
			*(ptrOP++) = ' ';
			*(ptrOP++) = ' ';
			for (; ptrOP < ptrCL && ptrOP < stophere; ptrOP++) {
				*ptrCCP++ = *ptrOP;
				*ptrOP = ' ';
			}
			if (KEEP == KEEP_NO)
				ptrCCP = comment;	/* reset it if we are not keeping it */
			*(ptrOP++) = ' ';
			*(ptrOP++) = ' ';
			removedp++;
			ptrCR = ptrCL + 2;
//                   if (*ptrCR=='\0') break;
			if (ptrCR >= stophere)
				break;
		}
//           else {fprintf(stdout,"Couldn't find close(**) [%s]\n",ptrOP);exit(1);}
		else {
			len = strlen(ptrCR);
			ptrNEW = ptrCR + len;
			if (ptrNEW >= stophere)
				break;
			*ptrNEW = '\n';		/* put carriage returns back in if we hit end of line */
			ptrTEMP = strchr(ptrNEW + 1, '\n');
			if (ptrTEMP != NULL)
				*ptrTEMP = '\0';
			fprintf(fpstatus,
					"Opening up comment1 of len[%d] for more lines, len[%d]...\n",
					len, strlen(ptrCR));
			multiline = 1;
		}
	}
	ptrCR = inout;
	len = 0;
	while ((ptrOP = strchr(ptrCR, '{')) != NULL) {	/* } */
/* } */ ptrCL = strchr(ptrOP, '}');
		if (ptrCL != NULL) {
//                    fprintf(stdout,"removing[%s]\n",ptrOP);
			*(ptrOP++) = ' ';
			for (; ptrOP < ptrCL && ptrOP < stophere; ptrOP++) {
				*ptrCCP++ = *ptrOP;
				*ptrOP = ' ';
			}
			if (KEEP == KEEP_NO)
				ptrCCP = comment;	/* reset it if we are not keeping it */
			*(ptrOP++) = ' ';
			removedb++;
			ptrCR = ptrCL + 1;
//                    if (*ptrCR=='\0') break;
			if (ptrCR >= stophere)
				break;
		}
		else {
			len = strlen(ptrCR);
			ptrNEW = ptrCR + len;
			if (ptrNEW >= stophere)
				break;
			fprintf(fpstatus,
					"Opening up comment2 of len[%d] for more lines, len[%d]...\n",
					len, strlen(ptrCR));
			*ptrNEW = '\n';		/* put carriage returns back in if we hit end of line */
			ptrTEMP = strchr(ptrNEW + 1, '\n');
			if (ptrTEMP != NULL)
				*ptrTEMP = '\0';
			multiline = 1;
		}
	}
	if (KEEP == KEEP_NO)
		ptrCCP = comment;		/* reset it if we are not keeping it */
	*ptrCCP = '\0';
	if (ptrTEMP != NULL && *ptrTEMP == '\0') {	/* put the CR back in if we closed properly */
//            fprintf(stdout,"Comment[%s]\n",inout);
		*ptrTEMP = '\n';
	}
//    fprintf(stdout,"replaced [%d] paren comments, [%d] brace comments\n",removedp,removedb);
//    fprintf(stdout,"[%s]\n",inout);
	return (multiline);
}

char *find_close(char *ptrST, char *ptrCR, char *comment, char *stophere)
{
	static int openparen = 0, linecnt = 0;
	int found = 0;
	char *ptrOP, *ptrZ, *ptrNEWCR;
	ptrNEWCR = ptrCR;
//    fprintf(stdout,"PTST[%p],ptrCR[%p],stop[%p],IN[%d]\n",ptrST,ptrCR,stophere,openparen);
	ptrOP = ptrST;
	while ((ptrZ = strchr(ptrOP, '(')) != NULL) {
		found = 1;
		openparen++;
		ptrOP = ptrZ + 1;
	}
	ptrOP = ptrST;
	while ((ptrZ = strchr(ptrOP, ')')) != NULL) {
		openparen--;
		ptrOP = ptrZ + 1;
	}
	if (openparen != 0) {
		*ptrCR = ' ';
		ptrNEWCR = strchr(ptrCR, '\n');
		linecnt++;
		if (ptrNEWCR == NULL) {
			while (isspace(*ptrCR) && ptrCR < stophere)
				ptrCR++;
			if (ptrCR != stophere) {
				fprintf(stderr, "ERROR, no carriage return[%s]\n", ptrCR);
				exit(1);
			}
		}
		else {
			*ptrNEWCR = '\0';
			remove_comments(ptrCR, comment, KEEP_YES, stophere);
			ptrNEWCR = find_close(ptrCR, ptrNEWCR, comment, stophere) + 1;
		}
	}
	if (openparen == 0 && linecnt > 0) {
/* fprintf(stdout,"subr call [%d] lines\n",1+linecnt); */
		linecnt = 0;
	}
//    fprintf(stdout,"PTST[%p],ptrCR[%p],stop[%p],OUT[%d]\n",ptrST,ptrCR,stophere,openparen);
	return (ptrNEWCR);
}

int remove_multispace(char *ptrCR, char *pbuf)
{
	char *ptr;
	int active = 0;
	ptr = ptrCR;
	while (*ptr != '\0') {
		if (*ptr == ' ' || *ptr == '   ') {
			pbuf[active++] = *(ptr++);
			while (*ptr == ' ' || *ptr == '   ')
				ptr++;
		}
		else {
			pbuf[active++] = *(ptr++);
		}
	}
	pbuf[active] = '\0';
	return (0);
}
