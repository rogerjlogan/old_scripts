/* compact_cycletbl() {} */

#include <stdio.h>
#include <strings.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "includes_ggm.h"

int compact_cycletbl() {
	int cyc, tbl, row1, row2, count, errcnt = 0;
	char tbuf[READLINELEN + 1], PINBINARY[NUMPINS + 1];
	int pinorder[NUMPINS];

	maxtbl = 0;
	cyctbl = (CYCTBL *) calloc(MAXCYCTBL, sizeof(CYCTBL));
	if (cyctbl == NULL) {
		fprintf(stderr, "Could not allocate memory for cyctbl, exiting, source[%s,%d,%s]\n",
				__FILE__, __LINE__, __FUNCTION__);
		fprintf(fperrors, "Could not allocate memory for cyctbl, exiting\n");
		exit(1);
	}
	fprintf(fpstatus, "allocated [%d] bytes for CYCTBL @%p,source[%s,%d,%s]\n",
			(MAXCYCTBL) * (sizeof(CYCTBL)), cyctbl, __FILE__, __LINE__,
			__FUNCTION__);

	/* make index table */
	for (cyc = 0; cyc < maxcycset; cyc++) {
		for (tbl = 0; tbl < maxtbl; tbl++) {
			if (strcmp(cycsets[cyc].tblname, cyctbl[tbl].tblname) == 0) {
				cyctbl[tbl].rows[cyctbl[tbl].maxrow] = cyc;
				cyctbl[tbl].valid[cyctbl[tbl].maxrow] = 1;
				cyctbl[tbl].maxrow++;
				if (cyctbl[tbl].maxrow >= MAXCYCROWS) {
					fprintf(stderr, "Not enough CycTblRows[%d],source[%s,%d,%s]\n",
							cyctbl[tbl].maxrow, __FILE__, __LINE__,
							__FUNCTION__);
					exit(1);
				}
				break;
			}					/* if tblname==tblname */
		}						/* tbl loop */
		if (tbl == maxtbl) {	/* then we didn't find the tbl, so add it */
			strcpy(cyctbl[maxtbl].tblname, cycsets[cyc].tblname);
			cyctbl[maxtbl].rows[0] = cyc;
			cyctbl[maxtbl].valid[0] = 1;
			cyctbl[maxtbl].maxrow = 1;	/* point to next row */
			maxtbl++;
		}
	}							/* cyc loop */
	fprintf(stderr, "prescanned %d cycsets and %d cyctbls,source[%s,%d,%s]\n",
			maxcycset, maxtbl, __FILE__, __LINE__, __FUNCTION__);

	count = 0;
	for (tbl = 0; tbl < maxtbl; tbl++) {
		for (row1 = 0; row1 < (cyctbl[tbl].maxrow - 1); row1++) {
			if (cyctbl[tbl].valid[row1] == 0) continue;		/* skip if no good */
			for (row2 = row1 + 1; row2 < cyctbl[tbl].maxrow; row2++) {
				if (cyctbl[tbl].valid[row2] == 0) continue;	/* skip if no good */
				if (0 == strcmp(cycsets[cyctbl[tbl].rows[row1]].pin,
									 cycsets[cyctbl[tbl].rows[row2]].pin) &&
					(0 != strcmp(cycsets[cyctbl[tbl].rows[row1]].dset0,
									 cycsets[cyctbl[tbl].rows[row2]].dset0) || 
					0 != strcmp(cycsets[cyctbl[tbl].rows[row1]].dset1,
									cycsets[cyctbl[tbl].rows[row2]].dset1))) {
					/* this says the pin is the same but the dset information is not the same, i.e. duplicate DIFFERENT definitions */
					errcnt++;
					fprintf(fperrors, "*** cycletable entries with different dset selections: *** source [%s,%d,%s]\n",
							__FILE__, __LINE__, __FUNCTION__);
					fprintf(fperrors, "cycleset[%s]   pin[%s]\n",
							cycsets[cyctbl[tbl].rows[row1]].tblname,
							cycsets[cyctbl[tbl].rows[row1]].pin);
					fprintf(fperrors, "DSET0A[%s]<->DSET0B[%s]   DSET1A[%s]<->DSET1B[%s]\n\n",
							cycsets[cyctbl[tbl].rows[row1]].dset0,
							cycsets[cyctbl[tbl].rows[row2]].dset0,
							cycsets[cyctbl[tbl].rows[row1]].dset1,
							cycsets[cyctbl[tbl].rows[row2]].dset1);
				}
				if (0 == strcmp(cycsets[cyctbl[tbl].rows[row1]].dset0,
									 cycsets[cyctbl[tbl].rows[row2]].dset0)
					&& 0 == strcmp(cycsets[cyctbl[tbl].rows[row1]].dset1,
								   cycsets[cyctbl[tbl].rows[row2]].
								   dset1)) {
					sprintf(tbuf, "+%s", cycsets[cyctbl[tbl].rows[row2]].pin);
					strcat(cycsets[cyctbl[tbl].rows[row1]].pin, tbuf);
					cyctbl[tbl].valid[row2] = 0;
					count++;
				}
			}					/* row2 */

			if (strchr(cycsets[cyctbl[tbl].rows[row1]].pin, '+') == NULL) continue;		/* if its not a group then no need to compress */
			resolve_list(cycsets[cyctbl[tbl].rows[row1]].pin, PINBINARY, '*', '.', pinorder);
//         fprintf(stdout,"PB[%s][%s]\n",cycsets[cyctbl[tbl].rows[row1]].pin,PINBINARY);
			for (row2 = 0; row2 < maxlists; row2++) {
//            fprintf(stdout,"[%s]<=>[%s]\n",PINBINARY,pinlist[row2].pinlists);
				if (strcmp(PINBINARY, pinlist[row2].pinlists) == 0) {
					fprintf(fpstatus, "   PINREPLACE[%s]=[%s]\n",
							cycsets[cyctbl[tbl].rows[row1]].pin, pinlist[row2].pinlistname);
					strcpy(cycsets[cyctbl[tbl].rows[row1]].pin, pinlist[row2].pinlistname);
					break;
				}
			}
		}						/* row1 */
	}							/* tbl */
	if (errcnt > 0) {
		fprintf(stderr, "\n*** %d cycletable entries with different dset selections: see %s *** source [%s,%d,%s]\n\n",
				errcnt, TRANSLATION_ERRORS, __FILE__, __LINE__, __FUNCTION__);
	}
	return (count);
}
