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

/* begin main function */
int main(int argc, char *argv[])
{
	/* file variables */
	FILE *fpin1, *fpin2, *fperrors, *fpstatus;
	gzFile *fpout;
	char infile1[FILENAMELEN], infile2[FILENAMELEN], outfile[FILENAMELEN];
	char tinfile1[FILENAMELEN], tinfile2[FILENAMELEN];
	char G_progstr[MEMOSTRLEN], G_datestr[MEMOSTRLEN],
		G_timestr[MEMOSTRLEN];
	char G_compilestr[MEMOSTRLEN];	/* concaternated strings */
	char command[MEMOSTRLEN], readline[READLINELEN + 1],
		tempbuf[READLINELEN + 1], comment[READLINELEN + 1];
	char *F1BUF, *F2BUF;
	char *ptrZ, *ptrCR, *ptrNCR, *ptrOP, *ptrCL;
	int gzin1 = 0, gzin2 = 0, beginend = 0, started = 0, found, sbrtcnt =
		0;
	int i, j, k;
	off_t bytes2read1, bytes2read2;
	struct stat stat1, stat2;
	typedef struct SUBRT {
#define maxparams 10
#define maxparamlen 100
#define maxlines 1000
		char *name;
		int numparams, numlines, containsmatch;
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
	F1BUF[bytes2read1] = '\0';
	F2BUF[bytes2read2] = '\0';
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
	while ((ptrOP = strstr(ptrCR, "(*")) != NULL) {
		ptrCL = strstr(ptrOP, "*)");
		if (ptrCL != NULL) {
			for (; ptrOP <= (ptrCL + 1); ptrOP++)
				*ptrOP = ' ';
			ptrCR = ptrCL + 1;
		}
	}
	ptrCR = F2BUF;
	while ((ptrOP = strchr(ptrCR, '{')) != NULL) {
		ptrCL = strchr(ptrOP, '}');
		if (ptrCL != NULL) {
			for (; ptrOP <= ptrCL; ptrOP++)
				*ptrOP = ' ';
			ptrCR = ptrCL + 1;
		}
	}

/* step 1: replace all carriage returns with '\0' and save in SUBRT.lines[] */
	ptrCR = F2BUF;
	maxsbrt = -1;				/* initialize to -1 so we can increment when we get the first one */
	while ((ptrNCR = strchr(ptrCR, '\n')) != NULL) {
/* step 1: replace all carriage returns with '\0' and save in subrt.lines[] */
		*ptrNCR = '\0';
/* step 2: save the name of the subroutine and its start */
		if (strstr(ptrCR, "external hardware subroutine") != NULL
			|| strstr(ptrCR, "external hardware Subroutine") != NULL);
		else if (strstr(ptrCR, "subroutine") != NULL
				 || strstr(ptrCR, "Subroutine") != NULL) {
			maxsbrt++;
			subrt[maxsbrt].numlines = subrt[maxsbrt].containsmatch = 0;
			subrt[maxsbrt].name = ptrCR + sizeof("subroutine");	/* this is a ptr */
			beginend = started = 0;
			subrt[maxsbrt].numparams = i = 0;
			ptrZ = ptrOP = strchr(ptrCR, '(');
			if (ptrOP != NULL) {
				ptrZ--;
				*ptrOP = '\0';
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
				*(ptrZ--) = '\0';
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
//  for (i=0;i<=maxsbrt;i++) {
//      fprintf(stdout,"SBR[%d]NL=%d\n",i,subrt[i].numlines);
//      gzprintf(fpout,"{N[%s]ML[%d]NP[%d]B[%s]E[%s]}\n",
//          subrt[i].name,subrt[i].numlines,subrt[i].numparams,subrt[i].begin,subrt[i].end);
//      if (subrt[i].numparams>=0) {
//          for (j=0;j<=subrt[i].numparams;j++) {
//              gzprintf(fpout,"{P%d[%s]}\n",j,subrt[i].paramnames[j]);
//              }
//          }
//      for (j=0;j<subrt[i].numlines;j++) {
//          if (subrt[i].lines[j][0]!='\0') gzprintf(fpout,"{S[%d]L[%d]S[%s]}\n",i,j,subrt[i].lines[j]);
//          }
//      }
	ptrCR = F1BUF;
	while ((ptrNCR = strchr(ptrCR, '\n')) != NULL
		   && ptrCR < (F1BUF + bytes2read1)) {
		*ptrNCR = '\0';

		strcpy(tempbuf, ptrCR);
		ptrCR = tempbuf;
		while ((ptrOP = strstr(ptrCR, "(*")) != NULL) {
			ptrCL = strstr(ptrOP, "*)");
			if (ptrCL != NULL) {
				for (; ptrOP <= (ptrCL + 1); ptrOP++)
					*ptrOP = ' ';
				ptrCR = ptrCL + 1;
			}
		}
		ptrCR = tempbuf;
		while ((ptrOP = strchr(ptrCR, '{')) != NULL) {
			ptrCL = strchr(ptrOP, '}');
			if (ptrCL != NULL) {
				for (; ptrOP <= ptrCL; ptrOP++)
					*ptrOP = ' ';
				ptrCR = ptrCL + 1;
			}
		}

		if (strstr(ptrCR, "external subroutine") != NULL ||
			strstr(ptrCR, "external hardware subroutine") != NULL) {
			gzprintf(fpout, "{%s}\n", ptrCR);
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
				/* wipe comments (in readline) before checking */
				ptrOP = strstr(readline, "(*");
				if (ptrOP != NULL)
					ptrCL = strstr(readline, "*)");
				if (ptrOP != NULL && ptrCL != NULL)
					while (ptrOP <= (ptrCL + 1))
						*(ptrOP++) = ' ';
				ptrOP = strchr(readline, '{');
				if (ptrOP != NULL)
					ptrCL = strchr(readline, '}');
				if (ptrOP != NULL && ptrCL != NULL)
					while (ptrOP <= ptrCL)
						*(ptrOP++) = ' ';
				if (strstr(readline, subrt[i].name) != NULL) {
					gzprintf(fpout, "{Next is subroutine [%s]}\nbegin\n",
							 subrt[i].name);
					for (j = 0; j < subrt[i].numlines; j++) {
						if (subrt[i].numparams == -1) {
							gzprintf(fpout, "%s\n", subrt[i].lines[j]);
							found = 1;
						}
						for (k = 0; k <= subrt[i].numparams; k++) {
							if (strstr
								(subrt[i].lines[j],
								 subrt[i].paramnames[k]) == NULL) {
								if (subrt[i].lines[j][0] != '\0')
									gzprintf(fpout, "%s\n",
											 subrt[i].lines[j]);
							}
							else {	/* its a parameter */
								found = 1;
								ptrOP = strchr(ptrCR, '(');
								ptrCL = strstr(ptrCR, ");");
								if (ptrCL != NULL)
									*ptrCL = '\0';
								if (ptrOP != NULL && ptrCL != NULL)
									gzprintf(fpout, "%s;\n", ptrOP + 1);
							}	/* end else */
						}		/* k */
					}			/* j */
					gzprintf(fpout, "end;\n");
				}				/* is subrt */
			}					/* for subrt */
			if (found != 1)
				gzprintf(fpout, "%s\n", ptrCR);
		}						/* else */
		ptrCR = (ptrNCR + 1);
	}							/* while */
	fprintf(stdout, "SUBROUTINES USED[%d]\n", sbrtcnt);

//
	gzclose(fpout);
	free(F1BUF);
	free(F2BUF);
	return (0);
}
