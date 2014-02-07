/* remove_dupe_cells() */
/* move_push_close() */
/* swap_alias() */

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
#include "aliasmap.h"

int remove_dupe_cells(char *cyclebuff, struct MODCODE *mc)
{
	int i, j, k, first, fmt, second, unique, rem, RDL, done, cdtlen;
	/* these are the primary modes: */
	/* these are the secondary masked modes: */
	char *ptrE[MAXCELLS], *ptrOP[MAXCELLS];	/* pointer to end of each cell */
	char val, tbuf[20000], tbuf2[20000], newcells[20000];
	char alias_1;
	newcells[0] = '\0';
	fprintf(fppreopt, "//%s\ncells[%d] %s\n", cyclebuff, cellcnt, __FUNCTION__);
	for (first = 0; first < cellcnt; first++) cellinfo[first].dupnum = -1;
	for (first = 0; first < cellcnt - 1; first++) {
		if (cellinfo[first].dupnum != -1) continue;			/* already found as duplicate */
		for (second = first + 1; second < cellcnt; second++) {
			if (cellinfo[first].alias1 == AM_BOGUS || cellinfo[first].alias1 == AM_BOGUS) {
				fprintf(fpstatus, "   f[%d]s[%d]names[%s,%s] cellinfo1.A0=%c cellinfo1.A1=%c cellinfo2.A0=%c cellinfo2.A1=%c\n",
						first, second, cellinfo[first].cellname,
						cellinfo[second].cellname, cellinfo[first].alias0,
						cellinfo[first].alias1, cellinfo[second].alias0,
						cellinfo[second].alias1);
			}
			unique = 0;
			for (fmt = 0; fmt < 4; fmt++) {
				if (cellinfo[first].formats[fmt] != cellinfo[second].formats[fmt]) {
					unique = 1;
					break;
				}
			}					/* fmt */
			if (strcmp(cellinfo[first].cellname, cellinfo[second].cellname) != 0) {
				unique = 1;
			}
			else if (strcmp(cellinfo[first].pin, cellinfo[second].pin) != 0) {
				unique = 1;
			}
			else if (strcmp(cellinfo[first].cellexpr, cellinfo[second].cellexpr) != 0) {
				unique = 1;
			}
			else if (cellinfo[first].alias0 != cellinfo[second].alias0) {
				unique = 1;
			}
			else if (cellinfo[first].alias1 != cellinfo[second].alias1) {
				unique = 1;
			}
			if (unique == 0) {
//            if (cellinfo[first].alias1==AM_BOGUS || cellinfo[second].alias1==AM_BOGUS) fprintf(fpstatus,"   NOT UNIQUE![%d,%d]\n",first,second);
				cellinfo[second].dupnum = first;
				fprintf(fppreopt, "found dup cell[%d],[%d],%s,%s\n", first,
						second, cellinfo[first].cellname, cellinfo[second].cellname);
				cdtlen = strlen(cellinfo[first].cdtstr);
				if (strchr(cellinfo[first].cdtstr, cellinfo[second].cdtcode) == NULL) {
					cellinfo[first].cdtstr[cdtlen++] = cellinfo[second].cdtcode;
					cellinfo[first].cdtstr[cdtlen] = '\0';	/* terminate */
//               fprintf(fpstatus,"   CF[%c][%s],CS[%c][%s]f[%d]s[%d]\n",cellinfo[first].cdtcode,cellinfo[first].cdtstr,cellinfo[second].cdtcode,cellinfo[second].cdtstr,first,second);
				}
				for (k = 0; k < mc->D0cnt; k++) {	/* remove modcodes which are dupes */
					if (mc->cellcntD0[k] == second) {
						mc->ALLD0[k] = MC_DUPE;
//                  fprintf(fpstatus,"   Killing k[%d],d0cnt=%d\n",k,mc->cellcntD0[k]);
					}			/* ==second */
				}				/* k */
				for (k = 0; k < mc->D1cnt; k++) {	/* remove modcodes which are dupes */
					if (mc->cellcntD1[k] == second) {
						mc->ALLD1[k] = MC_DUPE;
//                  fprintf(fpstatus,"   Killing k[%d],d1cnt=%d\n",k,mc->cellcntD1[k]);
					}			/* ==second */
				}				/* k */
			}					/* unique==0 */
		}						/* second */
	}							/* first */
	REMOVEDUPE[0] = '\0';
//fprintf(fppreopt,"CB[%s]\n",cyclebuff);
	/* first find the start and end of each cell */
	/* assume the cell starts with the first '{' */
	/* and ends with \n}\n */
	ptrOP[0] = ptrE[0] = cyclebuff;	/* this will point at the first comment */
	for (i = 1; i <= cellcnt; i++) {
		ptrOP[i] = strchr(ptrE[i - 1] + 1, '{');	/* first open, we're assuming one space in front!! */
		ptrE[i] = strstr(ptrE[i - 1] + 1, "\n}\n");
		if (ptrE[i] == NULL || ptrOP[i] == NULL) {
			fprintf(stderr, "RAMTIS:ERROR CELL doesn't match cellcnt[%d]!=[%d], source[%s,%d,%s]\n",
					i, cellcnt, __FILE__, __LINE__, __FUNCTION__);
			exit(1);
		}
		ptrE[i] += 3;			/* move it past */
	}
	tbuf2[0] = '\0';
	for (i = 0; i < cellcnt; i++) {
		alias_1 = cellinfo[i].alias1;
		if (alias_1 == AM_BOGUS) alias_1 = ' ';
		if (cellinfo[i].dupnum == -1) {
			fprintf(fppreopt, "//CELL%d PERSIST %s %s %c%c\n", i,
					cellinfo[i].cellname, cellinfo[i].pin,
					cellinfo[i].alias0, alias_1);
		}
		else {
			fprintf(fppreopt, "//CELL%d DUPE#%d %s %s %c%c\n", i,
					cellinfo[i].dupnum, cellinfo[i].cellname,
					cellinfo[i].pin, cellinfo[i].alias0, alias_1);
		}
		rem = 0;
		if (cellinfo[i].dupnum == -1) {	/* not a duplicate */
			val = *(ptrOP[i + 1] - 1);
			*(ptrOP[i + 1] - 1) = '\0';	/* this terminates over the space */
			strcat(REMOVEDUPE, ptrE[i]);
			*(ptrOP[i + 1] - 1) = val;
			/* add any cdt which have been removed due to duplication */
			for (second = 1; second < cellcnt; second++) {	/* don't need to check cell 0 */
				if (cellinfo[second].dupnum != i || cellinfo[second].dupnum == -1 || second == i) continue;
				RDL = strlen(REMOVEDUPE);
				for (j = RDL; j > 0; j--) if (REMOVEDUPE[j] == '_') break;
				if (strchr(REMOVEDUPE + j, *(ptrOP[second + 1] - 2)) != NULL) {
//               fprintf(stdout,"It exists[%c] in %s\n",*(ptrOP[second+1]-2),REMOVEDUPE);
				}
				else {
					REMOVEDUPE[RDL] = *(ptrOP[second + 1] - 2);	/* add the dupe cdt to the replacing cdt */
					REMOVEDUPE[RDL + 1] = '\0';	/* re-terminate */
					rem++;
					fprintf(fppreopt, "//ADD cat [%c]\n",
							*(ptrOP[second + 1] - 2));
				}
			}
			val = *(ptrE[i + 1]);
			*(ptrE[i + 1]) = '\0';
			strcat(REMOVEDUPE, ptrOP[i + 1] - 1);	/* this starts at the space and adds the remainder */
			*(ptrE[i + 1]) = val;
		}
		if (rem > 0) {
			fprintf(fppreopt, "//removed %d cells to %s.%s%c%c\n",
					rem, cellinfo[i].wftname, cellinfo[i].cellname,
					cellinfo[i].alias0, cellinfo[i].alias1);
			strcat(tbuf2, tbuf);
		}
	}
	/* cell data now in tbuf2 */
	done = 0;
	unique = 0;
	for (first = 0; first < cellcnt && !done; first++) {
		if (cellinfo[first].dupnum == -1) {	/* not a duplicate */
			unique++;
			continue;
		}
		else {					/* first is a duplicate, looking for second as non-dupe */
			done = 1;
			for (second = first + 1; second < cellcnt; second++) {
				if (cellinfo[second].dupnum == -1) {	/* not a duplicate */
					unique++;
					done = 0;	/* if we find one then we are not done */
					rem = cellinfo[first].dupnum;
					fprintf(fppreopt, "//f[%d] s[%d]\n", first, second);
					cellinfo[first].filepos = cellinfo[second].filepos;
					cellinfo[first].multidefnum = cellinfo[second].multidefnum;
					cellinfo[first].formatnum = cellinfo[second].formatnum;
					cellinfo[first].actline = cellinfo[second].actline;
					for (i = 0; i < MAX_EDGES; i++) cellinfo[first].formats[i] = cellinfo[second].formats[i];
					cellinfo[first].dupnum = -1;	/* no longer a dupe */
					cellinfo[first].cdtcode = cellinfo[second].cdtcode;
					strcpy(cellinfo[first].cdtstr, cellinfo[second].cdtstr);
					cellinfo[first].alias0 = cellinfo[second].alias0;
					cellinfo[first].alias1 = cellinfo[second].alias1;
					strcpy(cellinfo[first].wftname, cellinfo[second].wftname);
					strcpy(cellinfo[first].cellname, cellinfo[second].cellname);
					strcpy(cellinfo[first].pin, cellinfo[second].pin);
					strcpy(cellinfo[first].cellexpr, cellinfo[second].cellexpr);
					cellinfo[first].problemtype = cellinfo[second].problemtype;
					cellinfo[second].dupnum = rem;	/* mark the old cell as a dupe */
					for (i = 0; i < mc->D0cnt; i++)
						if (mc->cellcntD0[i] == second) {
							mc->cellcntD0[i] = first;
						}
					for (i = 0; i < mc->D1cnt; i++)
						if (mc->cellcntD1[i] == second) {
							mc->cellcntD1[i] = first;
						}
//               fprintf(fpstatus,"   DONE%d,%d[%s,%s]\n",first,second,cellinfo[first].cdtstr,cellinfo[second].cdtstr);
					break;
				}				/* second dupnum==-1 */
				else {
				}				/* else duplicate */
			}					/* second */
		}						/* else first dupnam==-1 */
	}
	cellcnt = unique;
	/* done compacting Cells and their data */
	strcpy(cyclebuff, REMOVEDUPE);
	strcat(cyclebuff, tbuf2);
	strcat(cyclebuff, newcells);
//   strcat(cyclebuff,"//END NEW CELLS\n");
	fprintf(fppreopt, "//END NEW CELLS\n");
	if (cellcnt > worstcasecellcnt)
		worstcasecellcnt = cellcnt;

	if (mc->D0cnt > 0) {
		for (i = 0; i < mc->D0cnt; i++) {	/* compare all to [0], assuming [0] is not a DUPE */
			fprintf(fpstatus, "   STATE0[%d,%d][%c%c%c%c]%c\n", i,
					mc->cellcntD0[i],
					cellinfo[mc->cellcntD0[i]].formats[0],
					cellinfo[mc->cellcntD0[i]].formats[1],
					cellinfo[mc->cellcntD0[i]].formats[2],
					cellinfo[mc->cellcntD0[i]].formats[3], mc->ALLD0[i]);
			if (i == 0) continue;
			if (mc->ALLD0[i] == MC_DUPE) continue;		/* skip, its duplicated */
			if (mc->ALLD0[0] == FC_WINDOWDATA && mc->ALLD0[i] == FC_EDGEDATA) continue;		/* this is Window and Edge, this is ok */
			if (mc->ALLD0[i] == FC_WINDOWDATA && mc->ALLD0[0] == FC_EDGEDATA) continue;		/* this is Window and Edge, this is ok */
			if (mc->ALLD0[i] != mc->ALLD0[0]) {
				fprintf(fpstatus, "AdvisoryA0[%04d]:Inconsistent DSET0 format type[%c][%c] for [%d,%d]\n",
						WARNING, mc->ALLD0[0], mc->ALLD0[i], 0, i);
				fprintf(fpstatus, "AdvisoryA1[%04d]:WFT[%s]Cell[%s]PIN[%s]CDT[%s] source[%s,%d,%s]\n",
						WARNING, cellinfo[mc->cellcntD0[i]].wftname,
						cellinfo[mc->cellcntD0[i]].cellname,
						cellinfo[mc->cellcntD0[i]].pin,
						cellinfo[mc->cellcntD0[i]].cdtstr, __FILE__, __LINE__, __FUNCTION__);
				fprintf(fpstatus, "AdvisoryA2[%04d]:FM1[", WARNING);
				for (j = 0; j < MAX_EDGES; j++) fputc(cellinfo[mc->cellcntD0[0]].formats[j], fpstatus);
				fprintf(fpstatus, "]FM2[");
				for (j = 0; j < MAX_EDGES; j++) fputc(cellinfo[mc->cellcntD0[i]].formats[j], fpstatus);
				fprintf(fpstatus, "]\n");
				WARNING++;
			}
		}
	}
	if (mc->D1cnt > 0) {
		for (i = 0; i < mc->D1cnt; i++) {	/* compare all to [0], assuming [0] is not a DUPE */
			fprintf(fpstatus, "   STATE1[%d,%d][%c%c%c%c]%c\n", i,
					mc->cellcntD0[i],
					cellinfo[mc->cellcntD1[i]].formats[0],
					cellinfo[mc->cellcntD1[i]].formats[1],
					cellinfo[mc->cellcntD1[i]].formats[2],
					cellinfo[mc->cellcntD1[i]].formats[3], mc->ALLD1[i]);
			if (i == 0) continue;
			if (mc->ALLD1[i] == MC_DUPE) continue;		/* skip, its duplicated */
			if (mc->ALLD1[0] == FC_WINDOWDATA && mc->ALLD1[i] == FC_EDGEDATA) continue;		/* this is Window and Edge, this is ok */
			if (mc->ALLD1[i] == FC_WINDOWDATA && mc->ALLD1[0] == FC_EDGEDATA) continue;		/* this is Window and Edge, this is ok */
			if (mc->ALLD1[i] != mc->ALLD1[0]) {
				fprintf(fpstatus, "AdvisoryB0[%04d]:Inconsistent DSET1 format type[%c][%c] for [%d,%d]\n",
						WARNING, mc->ALLD1[0], mc->ALLD1[i], 0, i);
				fprintf(fpstatus, "AdvisoryB1[%04d]:WFT[%s]Cell[%s]PIN[%s]CDT[%s] source[%s,%d,%s]\n",
						WARNING, cellinfo[mc->cellcntD1[i]].wftname,
						cellinfo[mc->cellcntD1[i]].cellname,
						cellinfo[mc->cellcntD1[i]].pin,
						cellinfo[mc->cellcntD1[i]].cdtstr, __FILE__, __LINE__, __FUNCTION__);
				fprintf(fpstatus, "AdvisoryB2[%04d]:FM1[", WARNING);
				for (j = 0; j < MAX_EDGES; j++) fputc(cellinfo[mc->cellcntD1[0]].formats[j], fpstatus);
				fprintf(fpstatus, "]FM2[");
				for (j = 0; j < MAX_EDGES; j++) fputc(cellinfo[mc->cellcntD1[i]].formats[j], fpstatus);
				fprintf(fpstatus, "]\n");
				WARNING++;
			}
		}
	}
	mc->D0c = mc->ALLD0[0];
	/* if both pointed to the same cell and there is only one cell the make them both point */
	/* at the D0 cell entry. This normally happens with a full ContinueWF */
	if (mc->ALLD1[0] == MC_DUPE) mc->D1c = mc->D0c;
	else mc->D1c = mc->ALLD1[0];

	cellcnt = 0;
	return (0);
}

int mod_add_close_ESD(char field[][100][WF_EXPR_LEN],
					  char org[][WF_EXPR_LEN], int nDELAYDATA[], int en[],
					  int ne, int neST, int formatpick[], int delay[])
{
	int i, j;
	/* Now modify the waveforms if necessary */
	if (strcmp(field[en[ne]][2], "ChanFirst") == 0) {	/* edgesetdelay */
		ne++;
		en[ne] = ne;
		formatpick[en[ne]] = 3;
		nDELAYDATA[en[ne]] = 0;
		delay[en[ne]] = 1;
		strcpy(field[en[ne]][0], field[1][0]);
		sprintf(field[en[ne]][1], "Edge%d", ne + 1);	/* ne starts at 0, 0=>Edge1, 1=>Edge2, 2=>Edge3 */
		strcpy(field[en[ne]][2], "ChanFirst");
		strcpy(field[en[ne]][3], "StrobeOff");
		strcpy(field[en[ne]][4], "ThreshVITL");
		strcpy(field[en[ne]][5], "tPeriodENDmod");
		strcpy(field[en[ne]][6], "0");
		strcpy(field[en[ne]][7], "StrobeOff");
		strcpy(field[en[ne]][8], "ThreshVITH");
		strcpy(field[en[ne]][9], "tPeriodENDmod");
		strcpy(field[en[ne]][10], "0");
		strcpy(org[en[ne]], org[0]);
	}
	else {						/* normal edgeset */
		ne++;
		en[ne] = ne;
		formatpick[en[ne]] = 2;
		nDELAYDATA[en[ne]] = 0;
		delay[en[ne]] = 0;
		strcpy(field[en[ne]][0], field[1][0]);
		sprintf(field[en[ne]][1], "Edge%d", ne + 1);	/* ne starts at 0, 0=>Edge1, 1=>Edge2, 2=>Edge3 */
		strcpy(field[en[ne]][2], "StrobeOff");
		strcpy(field[en[ne]][3], "tPeriodENDmod");
		strcpy(field[en[ne]][4], "");
		strcpy(field[en[ne]][5], "");
		strcpy(org[en[ne]], org[0]);
	}
	for (i = neST; i <= ne; i++) {
		fprintf(fpstatus, "   ne=%d,en[]=%d, [file:%s,%s]\n", ne, en[i], __FILE__, __FUNCTION__);
		for (j = 0; j < ((formatpick[en[i]] == 3) ? MF_EDGESETDATA : MF_EDGESET); j++)
			fprintf(fpstatus, "   field[%d][%d]=[%s]\n", en[i], j, field[en[i]][j]);
	}
	return (ne);
}
