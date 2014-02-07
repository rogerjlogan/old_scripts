#include <stdio.h>
#include <strings.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include "include_vcp.h"


int deal_with_shutdown(char *line, char *ptr, FILE * fpin1, char *pb_vector)
{
	int beginflag = 2, counter = 0;
	char vector[READLINELEN + 1], mod_vector[READLINELEN + 1], outvector1[READLINELEN + 1];
	char DMI[15];
	if ((ptr - line) <= 7) {	/* Shutdown SUBROUTINE */
		if (DEBUG + TRUE) fprintf(fpstatus, "INSIDE Shutdown:%s\n", line);
		fgets(vector, READLINELEN - 1, fpin1);
		readlinenum++;
		if (NULL != (ptr = strstr(vector, "begin"))) {
			fprintf(stderr, "\nFYI:%s,%s:Shutdown vectors available in %s\n\n", compilestr, infile_orig, TRANSLATION_STATUS);
			if (DEBUG) fprintf(fpstatus, "Throwing out Shutdown:%s", vector);
			while (fgets(vector, READLINELEN - 1, fpin1) != NULL) {
				readlinenum++;
				counter++;
				if (DEBUG) fprintf(fpstatus, "Throwing out Shutdown:%s", vector);
				if (NULL != (ptr = strstr(vector, "end"))) break;
				strcpy(mod_vector, vector);
				vector_convert(&beginflag, vector, mod_vector, &SETS, outvector1, DMI, pb_vector);
				if (outvector1[0] != '\0')
					fprintf(fperrors, "FYI:%s,%s:SHUTDOWN%d:[%s]\n", compilestr, infile_orig, counter, outvector1);
			}					/* end while */
		}						/* end if begin */
	}							/* end ptr<7 */
	return (0);
}

/***************************************************************************************/

int deal_with_comment(FILE * fpout1, char *mod_vector, char *comment, int *commentcount, int *commentflag, int *commentON, int vectorflag)
{
	int i, vl, j, commentstart = -1, commentend = 0;
/* seek until comment end*/
	vl = strlen(mod_vector);
	for (i = 0; i <= vl; i++) {
		if (mod_vector[i] == '{' && commentstart == -1) {
			(*commentcount)++;
			commentstart = i;
		}
		else if (mod_vector[i] == '{' && commentstart != -1) {
			(*commentcount)++;
		}
		if (mod_vector[i] == '}') {
			(*commentcount)--;
			commentend = i;
		}
	}

	if (*commentcount == 0) {	/* we can close the comment. there will be no pending comments */
		*commentflag = 1;
		if (commentend != -1) mod_vector[commentend] = '\0';	/* temporarily mark the final comment close with an end later we will restore it to space */
		if (commentstart != -1) mod_vector[commentstart] = ' ';
		else commentstart = 0;	/* set the comment to start at the beginning if there was not comment open */
		i = 0;
		while (mod_vector[commentstart] == ' ' && i < 3) {
			commentstart++;
			i++;
		}						/* remove leading space accounting for comment markers */
		*commentON = 0;
		if ((commentend - commentstart) + strlen(comment) > MULTILINESIZE) {
			if (1) fprintf(fpstatus, "BIG COMMENT <%s>\n", comment);
			if (0) fprintf(fpstatus, "found BIG COMMENT\n");
			comment[0] = '\0';	/* wipe out anything we had here */
		}
		strncat(comment, &mod_vector[commentstart], MULTILINESIZE);
		if (vectorflag == 0) {
			fprintf(fpout1, "//%s\n", comment);
			comment[0] = '\0';
		}
		/* the idea here is to blank the line out where the comment was */
		for (j = commentstart; j <= commentend; j++) mod_vector[j] = ' ';	/* this actually writes over the \0 we wrote above */
	}
	else {						/* the comment needs to remain open */
		*commentON = 1;
		mod_vector[commentstart] = ' ';
		if ((vl - commentstart) + strlen(comment) > MULTILINESIZE) {
			if (1) fprintf(fpstatus, "BIG COMMENT <%s>\n", comment);
			if (0) fprintf(fpstatus, "found BIG COMMENT\n");
			comment[0] = '\0';
		}
		strncat(comment, &mod_vector[commentstart], MULTILINESIZE);
		for (j = commentstart; j <= vl; j++) mod_vector[j] = ' ';	/* this actually writes over the \0 we wrote above */
	}
	return (0);
}



int pare_comment(char *newcomment, char *oldcomment)
{
	int nc;
	char *ptrF1, *ptrF2, *ptrFL, *ptrT;
//   fprintf(stderr,"In pare!\n");
//   fflush(stderr);
	newcomment[0] = '\0';
	nc = 0;
	ptrF1 = strstr(oldcomment, "RPTDPM");
	if (ptrF1 != NULL) {
		while (*ptrF1 != ' ' && *ptrF1 != '\0') ptrF1++;			/* find first space */
		ptrF2 = strstr(ptrF1, "RPTDPM");	/* look for second */
		if (ptrF2 != NULL) {	/* find last */
			ptrFL = ptrF2;
			ptrFL += 6;
			while (NULL != (ptrT = strstr(ptrFL, "RPTDPM"))) {
				ptrFL = ptrT;
				ptrFL += 6;
			}
			if (ptrFL != ptrF2 + 6) {
				while (*ptrFL != ' ' && *ptrFL != '\0') ptrFL++;	/* find first space */
				for (ptrT = oldcomment; ptrT < ptrF2; ptrT++) {
					newcomment[nc] = *ptrT;
					nc++;
					newcomment[nc] = '\0';
				}
				for (ptrT = ptrFL; *ptrT != '\0' && nc < MULTILINESIZE; ptrT++) {
					newcomment[nc] = *ptrT;
					nc++;
					newcomment[nc] = '\0';
				}
			}
			else strcpy(newcomment, oldcomment);
		}
		else strcpy(newcomment, oldcomment);
	}
	else strcpy(newcomment, oldcomment);
//   fprintf(stderr,"Out pare!\n");
//   fflush(stderr);
	return (0);
}
