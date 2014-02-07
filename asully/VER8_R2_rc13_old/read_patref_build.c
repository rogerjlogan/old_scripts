#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "common_includes.h"
#include "includes_build.h"

int read_pat_ref() {
	FILE *fppatref;
	char readstr[READLINELEN + 1];
	int i;
	char *ptrST,*ptrSP,hold,*ptrEND;

	if (NULL == (fppatref = fopen(PAT_REF_FILE, "r"))) {
		fprintf(stderr, "\nNON-FATAL_ERROR:Could not open %s for output\n",PAT_REF_FILE);
		fprintf(stderr, "NOT generating PatternSequence\n");
		maxref = 0;
		return(0);
	}
	Gwftref = (WFTREF *) calloc(MAXREF, sizeof(WFTREF));
	if (Gwftref == NULL) {
		fprintf(stderr,"Could not allocate memory for Gwftref, source[%s,%d,%s]\n", __FILE__, __LINE__, __FUNCTION__);
		exit(1);
	}
	fprintf(stderr,"MAXREFS[%d]\n",maxref);
	while (fgets(readstr, READLINELEN - 1, fppatref) != NULL) {
		readstr[strlen(readstr) - 1] = '\0';	/* remove trailing \n */
		ptrST=readstr;
		ptrEND=readstr+strlen(readstr);
		while ((ptrST=strchr(ptrST,'|')) != NULL) {
			ptrST++;
			ptrSP = strchr(ptrST,' ');
			if (ptrSP == NULL) ptrSP = strchr(ptrST,'|');
			if (ptrSP == NULL) ptrSP = ptrEND;/* if no SPACE and not found, end at ptrEND... */
			hold = *ptrSP;
			*ptrSP='\0';
			for (i=0;i<maxref;i++) {
				if (strcmp(ptrST,Gwftref[i].wftref) == 0) break;
				}
			if (i == maxref) {
				strcpy(Gwftref[maxref].wftref,ptrST);
				maxref++;
				if (maxref>MAXREF) {
					fprintf(stderr,"Too many wftrefs\n");
					maxref--;
					}
				}
			*ptrSP = hold;
			if (ptrSP<ptrEND) ptrST = ptrSP+1;
			else break;
			}
		}
	fprintf(stderr,"MAXREFS[%d]\n",maxref);
	return(maxref);
	}
