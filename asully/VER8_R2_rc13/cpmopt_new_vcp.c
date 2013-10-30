#include <stdio.h>
#include <strings.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "include_vcp.h"

#define MAXCPMLINES 64000
int cpmoptimize(char *pattern)
{
	FILE *fpin, *fpout;
	char *filebuffer, *curptr, *endptr, *ptrst, *ptrsp;
	TD_FILETABLE *filetbl[MAXCPMLINES];
	int i, j;
	off_t filesize;
	struct stat statbuf;
	int ret, done;
	int numcpmlines;

	ret = stat(pattern, &statbuf);
	if (ret == 0)
		filesize = statbuf.st_size;
	else {
		fprintf(stderr, "Can't determine filesize for [%s]\n", pattern);
		fprintf(fperrors, "Can't determine filesize for [%s]\n", pattern);
		exit(1);
	}
	if (NULL == (fpin1 = fopen(pattern, "r"))) {
		fprintf(stderr,
				"\nFATAL_ERROR:Uncompressed input file [%s] not found.\n",
				pattern);
		fprintf(fperrors,
				"\nFATAL_ERROR:%s:Uncompressed input file [%s] not found.\n",
				compilestr, pattern);
		exit(1);
	}

	curptr = filebuffer = malloc((size_t) (filesize + 1));
	if (filebuffer == NULL) {
		fprintf(stderr,
				"Could not allocate memory for [%s] file in memory\n",
				pattern);
		fprintf(fperrors,
				"Could not allocate memory for [%s] file in memory\n",
				pattern);
		exit(1);
	}
	fprintf(fpstatus, "allocated [%ld] bytes for patbuf\n", filesize);
	filetbl = calloc(MAXCPMLINES, sizeof(TD_FILETABLE));
	if (filetbl == NULL) {
		fprintf(stderr,
				"Could not allocate memory for [%s] filetbl in memory\n",
				pattern);
		fprintf(fperrors,
				"Could not allocate memory for [%s] filetbl in memory\n",
				pattern);
		exit(1);
	}
	fprintf(fpstatus, "allocated [%ld] bytes for filetbl\n",
			MAXCPMLINES * sizeof(TD_FILETABLE));

	fread(patbuf, (size_t) filesize, 1, fpin1);
	fclose(fpin1);
	*(filebuffer + filesize) = '\0';	/* make sure it is terminated! */
	numcpmlines = 0;
	done = 0;
	while (NULL != (endptr = strchr(curptr, '\n'))) {
		if (*curptr == '*') {	/* its a vector if it starts with '*' */
			filetbl[numcpmlines]->vect = curptr;
			ptrst = strchr(curptr + 1, '*');	/* find the end of the vector (+1 to get past first '*') */
			/* for now we'll assume that there MUST be a second '*' */
			ptrst++;
			filetbl[numcpmlines]->vecte = ptrst;
			while (*ptrst == ' ')
				ptrst++;		/* get past any spaces */
			filetbl[numcpmlines]->wftref = ptrst;
			ptrsp = ptrst;
			while (*ptrsp != ' ')
				ptrsp++;		/* search until we find a space */
			ptrst = ptrsp;
			while (*ptrst == ' ')
				ptrst++;		/* get past any spaces */
			filetbl[numcpmlines]->sighdr = ptrst;
			ptrsp = ptrst;
			while (*ptrsp != ';')
				ptrsp++;		/* search until we find a semicolon */
			ptrst = ptrsp;
		}
		else {					/* its a comment */
		}
		return (0);
	}
