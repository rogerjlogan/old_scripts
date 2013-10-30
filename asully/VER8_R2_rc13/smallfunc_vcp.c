#include <stdio.h>
#include <strings.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include "include_vcp.h"

char *get_count(char *ptr, int offset, long *count, int call)
{
	char *retptr;

	*count = 0;
	retptr = ptr + offset;
	while (!isdigit((int) *retptr) && *retptr != 0)
		retptr++;
	while (isdigit((int) *retptr)) {
		*count = *count * 10 + (*retptr - '0');
		retptr++;
	}
	if (*count == 0) {			/* check for 'forever' */
		if (NULL != strstr(ptr, "forever"))
			*count = RET_FOREVER;
	}
	return (retptr);
}


int check_SET(int beginflag, char *mod_vector, const char *SET,
			  int *notgood, int MAX, char SETPTR[])
{
	long t1, t2;
	char *ptr;
	if (beginflag >= 1 && NULL != (ptr = strstr(mod_vector, SET))) {
		t1 = 0;
		ptr = strchr(mod_vector, '[');
		if (ptr == NULL) {
			fprintf(stderr, "%s BAD_ERROR: [%s]", SET, mod_vector);
			fprintf(fperrors, "BAD_ERROR:%s:%s [%s]file[%s]line:%ld\n",
					progstr, SET, mod_vector, infile_orig, readlinenum);
			*notgood = 1;
			return (1);
		}
		else {
			*ptr = '%';
			ptr = get_count(ptr, 1, &t1, 2);
			if (t1 > MAX) {
				fprintf(stderr, "Exceeded MAX%s\n...exiting\n", SET);
				fprintf(fpstatus,
						"Exceeded MAX%s...exiting.file[%s]line:%ld\n", SET,
						infile_orig, readlinenum);
				*notgood = 1;
				return (1);
			}
			if (0)
				fprintf(stderr, "In %s [%ld]\n", SET, t1);
			ptr = strchr(mod_vector, '[');
			if (ptr == NULL)
				return (1);
			ptr++;
			t2 = 0;
			while (*ptr != ']') {
				SETPTR[t1 * VECTORLEN + t2] = *ptr - '0';
				ptr++;
				t2++;
			}
			return (2);
		}
	}
	return (0);
}

int read_gct_dset_info (char *readstr, char *name, char *gctD0, char *gctD1, int *count,int maxv) {
	char *ptrLT, *ptrGT, *ptrOB, *ptrCB, *ptrOB2, *ptrCB2;
	int vectorstart, vectorend, vector2skew, gctend, gctstart;
	int i,j;

		ptrLT = strchr(readstr, '<');	/* waveformtable stuff */
		ptrGT = strchr(readstr, '>');
		ptrOB = strchr(readstr, '[');	/* the char mapper */
		ptrCB = strchr(readstr, ']');
		if (ptrLT == NULL || ptrGT == NULL || ptrOB == NULL || ptrCB == NULL) return(1);			/* anything else isn't a GCT set */
		ptrOB2 = strchr(ptrCB + 1, '[');	/* the char mapper */
		ptrCB2 = strrchr(ptrCB + 1, ']');	/* don't actually use this one, work off ptrOB2-ptrOB skew */
		gctstart = (int) (ptrLT - &readstr[0]) + 1;
		gctend = (int) (ptrGT - &readstr[0]) - 1;
		vectorstart = (int) (ptrOB - &readstr[0]) + 1;
		vectorend = (int) (ptrCB - &readstr[0]) - 1;
		vector2skew = ptrOB2 - ptrOB;
		MOD2_SIZE = vectorend - vectorstart + 1;
		for (j = 0, i = gctstart; i <= gctend; j++, i++) name[j] = readstr[i];
		name[j] = '\0';
		for (j = 0, i = vectorstart; i <= vectorend; j++, i++) {
			gctD0[j] = readstr[i];
			gctD1[j] = readstr[i + vector2skew];
		}
		gctD0[j] = '\0';
		gctD1[j] = '\0';
		(*count )++;
		if (*count > maxv) {
			fprintf(stderr,"Too many [%d] GCT at [%s]\n",*count, name);
			(*count)--;
			}
		return(0);
	}
