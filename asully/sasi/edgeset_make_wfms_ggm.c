/* ggm_edgeset_make_wfms.c */
/* edgeset_make_wfms(){} */

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

int edgeset_make_wfms(char *cyclebuff,
					  char field[MAX_EDGES + 1][100][WF_EXPR_LEN],
					  int en[MAX_EDGES + 1], int ne, int neST,
					  char org[MAX_EDGES + 1][WF_EXPR_LEN], int DSET,
					  int delay[], int nDELAYDATA[MAX_EDGES + 1])
{
	int i, drv, cmp, edgecnt = 0, dataoff, split, zcnt;
	int fmtexpN[MAX_EDGES + 1], fmtN[MAX_EDGES + 1], fmtDLY[MAX_EDGES + 1];
	char DELAYEXP[100];

/* EdgeSetDelayPinList(wave,edge,edgetype,time,delay,pinlist) */
/* EdgeSetDelayDataPinList(wave,edge,chan,edgetype0,vth0,time0,delay0,edgetype1,vth1,time1,delay1,pinlist) */
	zcnt = 0;
	dataoff = 0;
	if (ne >= 4)
		dataoff = 1;
	for (i = neST; i <= ne; i++) {
		if (delay[i] == 0) { /* EdgeSet or EdgeSetDelay */
			fmtN[i] = 2;
			fmtexpN[i] = 3;
			fmtDLY[i] = 0;
		}
		else if (delay[i] == 1) { /* EdgeSet or EdgeSetDelay */
			fmtN[i] = 2;
			fmtexpN[i] = 3;
			fmtDLY[i] = 4;
		}
		else {
			if (DSET == 1) { /* EdgeSetDelayData second set */
				fmtN[i] = 7;
				fmtexpN[i] = 9;
				fmtDLY[i] = 10;
			}
			else { /* EdgeSetDelayData first set */
				fmtN[i] = 3;
				fmtexpN[i] = 5;
				fmtDLY[i] = 6;
			}
		}
//      if (NULL!=strstr(field[en[i]][fmtN[i]],"DriveOff") ) {dataoff=1;}
		fprintf(fpstatus, "   fN[%d]=%d,fmtexp[%d]=%d,fmtDLY[%d]=%d\n", i,
				fmtN[i], i, fmtexpN[i], i, fmtDLY[i]);
	}
	drv = 0;
	cellinfo[cellcnt].cellexpr[0] = '\0';
	edgecnt = edgecnt;

	for (i = neST; i <= ne; i++) {	/* remap the formats: */
		if (delay[i] == 0) {
			split = 0;
			strcpy(DELAYEXP, "0.000ns");
		}
		else {
			split = 1;
			sprintf(DELAYEXP, "%s*%s", field[en[i]][fmtDLY[i]], tperiod);
		}
//		fprintf(stdout,"processing[%s] [%s][%d][%d]\n", field[0][0], field[en[i]][fmtN[i]],i,en[i]);
		if (NULL != strstr(field[en[i]][fmtN[i]], "DriveData")) {
			if (drv == 0) strcat(cyclebuff, "   Drive {\n      Waveform {\n");	/* }} */
			sprintf(SCATcycle, "         DriveData  @\"%s+%s %s\";\n",
				field[en[i]][fmtexpN[i]], DELAYEXP,
				(en[i] == 0) ? org[1] : (en[i] == 1) ? org[2] : (en[i] == 2) ? org[3] : (en[i] == 3) ? org[4] : "0.000ps");
			strcat(cellinfo[cellcnt].cellexpr, SCATcycle);
			strcat(cyclebuff, SCATcycle);
			drv = 1;
			zcnt++;
		}
		else if (NULL != strstr(field[en[i]][fmtN[i]], "DriveLow")) {
			if (drv == 0) strcat(cyclebuff, "   Drive {\n      Waveform {\n");	/* }} */
			sprintf(SCATcycle, "         DriveLow  @\"%s+%s %s\";\n",
				field[en[i]][fmtexpN[i]], DELAYEXP,
				(en[i] == 0) ? org[1] : (en[i] == 1) ? org[2] : (en[i] == 2) ? org[3] : (en[i] == 3) ? org[4] : "0.000ps");
			strcat(cellinfo[cellcnt].cellexpr, SCATcycle);
			strcat(cyclebuff, SCATcycle);
			drv = 1;
			zcnt++;
		}
		else if (NULL != strstr(field[en[i]][fmtN[i]], "DriveHigh")) {
			if (drv == 0) strcat(cyclebuff, "   Drive {\n      Waveform {\n");	/* }} */
			sprintf(SCATcycle, "         DriveHigh @\"%s+%s %s\";\n",
				field[en[i]][fmtexpN[i]], DELAYEXP,
				(en[i] == 0) ? org[1] : (en[i] == 1) ? org[2] : (en[i] == 2) ? org[3] : (en[i] == 3) ? org[4] : "0.000ps");
			strcat(cellinfo[cellcnt].cellexpr, SCATcycle);
			strcat(cyclebuff, SCATcycle);
			drv = 1;
			zcnt++;
		}
		else if (NULL != strstr(field[en[i]][fmtN[i]], "DriveComplement")) {
			if (drv == 0) strcat(cyclebuff, "   Drive {\n      Waveform {\n");	/* }} */
			sprintf(SCATcycle, "         DriveDataNot @\"%s+%s %s\";\n",
				field[en[i]][fmtexpN[i]], DELAYEXP,
				(en[i] == 0) ? org[1] : (en[i] == 1) ? org[2] : (en[i] == 2) ? org[3] : (en[i] == 3) ? org[4] : "0.000ps");
			strcat(cellinfo[cellcnt].cellexpr, SCATcycle);
			strcat(cyclebuff, SCATcycle);
			drv = 1;
			zcnt++;
		}
		else if (dataoff != 1 && NULL != strstr(field[en[i]][fmtN[i]], "DriveOff")) {
			if (drv == 0) strcat(cyclebuff, "   Drive {\n      Waveform {\n");	/* }} */
			sprintf(SCATcycle, "         DriveOff @\"%s+%s %s\";\n",
				field[en[i]][fmtexpN[i]], DELAYEXP,
				(en[i] == 0) ? org[1] : (en[i] == 1) ? org[2] : (en[i] == 2) ? org[3] : (en[i] == 3) ? org[4] : "0.000ps");
			strcat(cellinfo[cellcnt].cellexpr, SCATcycle);
			strcat(cyclebuff, SCATcycle);
			drv = 1;
			dataoff = 1;
			zcnt++;
		}
/* ?????? */
//		else if (dataoff != 1 && NULL != strstr(field[en[i]][fmtN[i]], "StrobeOff") && dataoff == 0) {	/* this covers all of the StrobeOff types */
//			if (drv == 0) strcat(cyclebuff, "   Drive {\n      EntryState DriveOff;\n      Waveform {\n");	/* }} */
//			sprintf(SCATcycle, "          @\"%s+%s %s\";\n",
//					field[en[i]][fmtexpN[i]], DELAYEXP,
//					(en[i] == 0) ? org[1] : (en[i] ==
//											 1) ? org[2] : (en[i] ==
//															2) ? org[3]
//					: (en[i] == 3) ? org[4] : "0.000ps");
//			sprintf(SCATcycle, "         EntryState DriveOff;\n");
//			SCATcycle[0]='\0';
//			strcat(cellinfo[cellcnt].cellexpr, SCATcycle);
//			strcat(cyclebuff, SCATcycle);
//			dataoff = 1;
//			drv = 1;
//			zcnt++;
//		}
		else if (NULL != strstr(field[en[i]][fmtN[i]], "NullEdge")) {
			if (drv == 0) strcat(cyclebuff, "   Drive {\n      EntryState DriveOn;\n      Waveform {\n");	/* }} */
			sprintf(SCATcycle, "          @\"%s+%s %s\";\n",
				field[en[i]][fmtexpN[i]], DELAYEXP,
				(en[i] == 0) ? org[1] : (en[i] == 1) ? org[2] : (en[i] == 2) ? org[3] : (en[i] == 3) ? org[4] : "0.000ps");
			strcat(cellinfo[cellcnt].cellexpr, SCATcycle);
			strcat(cyclebuff, SCATcycle);
			drv = 1;
			zcnt++;
		}
	}
/* this instead of the ?????? block above!!! */
	if (drv == 0) {
		strcat(cyclebuff, "   Drive {\n      EntryState DriveOff;\n      Waveform {\n");	/* }} */
		drv = 1;
		}
	/* { { */
	if (drv) strcat(cyclebuff, "      }\n   }\n");
	cmp = 0;
	for (i = neST; i <= ne; i++) {	/* remap the formats: */
		if (delay[i] == 0) {
			split = 0;
			strcpy(DELAYEXP, "0.000ns");
		}
		else {
			split = 1;
			sprintf(DELAYEXP, "%s*%s", field[en[i]][fmtDLY[i]], tperiod);
		}
		if (NULL != strstr(field[en[i]][fmtN[i]], "EdgeStrobeData")) {
			if (cmp == 0) strcat(cyclebuff, "   Compare {\n      Waveform {\n");	/* }} */
			sprintf(SCATcycle, "         CompareData @\"%s+%s %s\";\n",
				field[en[i]][fmtexpN[i]], DELAYEXP,
				(en[i] == 0) ? org[1] : (en[i] == 1) ? org[2] : (en[i] == 2) ? org[3] : (en[i] == 3) ? org[4] : "0.000ps");
			strcat(cellinfo[cellcnt].cellexpr, SCATcycle);
			strcat(cyclebuff, SCATcycle);
			cmp = 1;
			zcnt++;
		}
		else if (NULL != strstr(field[en[i]][fmtN[i]], "EdgeStrobeLow")) {
			if (cmp == 0) strcat(cyclebuff, "   Compare {\n      Waveform {\n");	/* }} */
			sprintf(SCATcycle, "         CompareLow  @\"%s+%s %s\";\n",
				field[en[i]][fmtexpN[i]], DELAYEXP,
				(en[i] == 0) ? org[1] : (en[i] == 1) ? org[2] : (en[i] == 2) ? org[3] : (en[i] == 3) ? org[4] : "0.000ps");
			strcat(cellinfo[cellcnt].cellexpr, SCATcycle);
			strcat(cyclebuff, SCATcycle);
			cmp = 1;
			zcnt++;
		}
		else if (NULL != strstr(field[en[i]][fmtN[i]], "EdgeStrobeHigh")) {
			if (cmp == 0) strcat(cyclebuff, "   Compare {\n      Waveform {\n");	/* }} */
			sprintf(SCATcycle, "         CompareHigh @\"%s+%s %s\";\n",
				field[en[i]][fmtexpN[i]], DELAYEXP,
				(en[i] == 0) ? org[1] : (en[i] == 1) ? org[2] : (en[i] == 2) ? org[3] : (en[i] == 3) ? org[4] : "0.000ps");
			strcat(cellinfo[cellcnt].cellexpr, SCATcycle);
			strcat(cyclebuff, SCATcycle);
			cmp = 1;
			zcnt++;
		}
		else if (NULL != strstr(field[en[i]][fmtN[i]], "EdgeStrobeComplement")) {
			if (cmp == 0) strcat(cyclebuff, "   Compare {\n      Waveform {\n");	/* }} */
			sprintf(SCATcycle, "         CompareDataNot @\"%s+%s %s\";\n",
				field[en[i]][fmtexpN[i]], DELAYEXP,
				(en[i] == 0) ? org[1] : (en[i] == 1) ? org[2] : (en[i] == 2) ? org[3] : (en[i] == 3) ? org[4] : "0.000ps");
			strcat(cellinfo[cellcnt].cellexpr, SCATcycle);
			strcat(cyclebuff, SCATcycle);
			cmp = 1;
			zcnt++;
		}
		else if (NULL != strstr(field[en[i]][fmtN[i]], "EdgeStrobeZ")) {
			if (cmp == 0) strcat(cyclebuff, "   Compare {\n      Waveform {\n");	/* }} */
			sprintf(SCATcycle, "         CompareFloat @\"%s+%s %s\";\n",
				field[en[i]][fmtexpN[i]], DELAYEXP,
				(en[i] == 0) ? org[1] : (en[i] == 1) ? org[2] : (en[i] == 2) ? org[3] : (en[i] == 3) ? org[4] : "0.000ps");
			strcat(cellinfo[cellcnt].cellexpr, SCATcycle);
			strcat(cyclebuff, SCATcycle);
			cmp = 1;
			zcnt++;
		}
		else if (NULL != strstr(field[en[i]][fmtN[i]], "StrobeComplement")) {
			if (cmp == 0) strcat(cyclebuff, "   Compare {\n      Waveform {\n");	/* }} */
			sprintf(SCATcycle, "         CompareOpenDataNot @\"%s+%s %s\";\n",
				field[en[i]][fmtexpN[i]], DELAYEXP,
				(en[i] == 0) ? org[1] : (en[i] == 1) ? org[2] : (en[i] == 2) ? org[3] : (en[i] == 3) ? org[4] : "0.000ps");
			strcat(cellinfo[cellcnt].cellexpr, SCATcycle);
			strcat(cyclebuff, SCATcycle);
			cmp = 1;
			zcnt++;
		}
		else if (NULL != strstr(field[en[i]][fmtN[i]], "StrobeZ")) {
			if (cmp == 0) strcat(cyclebuff, "   Compare {\n      Waveform {\n");	/* }} */
			sprintf(SCATcycle, "         CompareOpenFloat @\"%s+%s %s\";\n",
				field[en[i]][fmtexpN[i]], DELAYEXP,
				(en[i] == 0) ? org[1] : (en[i] == 1) ? org[2] : (en[i] == 2) ? org[3] : (en[i] == 3) ? org[4] : "0.000ps");
			strcat(cellinfo[cellcnt].cellexpr, SCATcycle);
			strcat(cyclebuff, SCATcycle);
			cmp = 1;
			zcnt++;
		}
		else if (NULL != strstr(field[en[i]][fmtN[i]], "StrobeLatch")) {
			if (cmp == 0) strcat(cyclebuff, "   Compare {\n      Waveform {\n");	/* }} */
			sprintf(SCATcycle, "          @\"%s+%s %s\";\n",
				field[en[i]][fmtexpN[i]], DELAYEXP,
				(en[i] == 0) ? org[1] : (en[i] == 1) ? org[2] : (en[i] == 2) ? org[3] : (en[i] == 3) ? org[4] : "0.000ps");
			strcat(cellinfo[cellcnt].cellexpr, SCATcycle);
			strcat(cyclebuff, SCATcycle);
			cmp = 1;
			zcnt++;
		}
		else if (NULL != strstr(field[en[i]][fmtN[i]], "StrobeOffData") ||
				 NULL != strstr(field[en[i]][fmtN[i]], "StrobeOffComplement")
				 || NULL != strstr(field[en[i]][fmtN[i]], "StrobeOffHigh")
				 || NULL != strstr(field[en[i]][fmtN[i]], "StrobeOffLow")
				 || NULL != strstr(field[en[i]][fmtN[i]], "StrobeOff")) {
			if (cmp == 0) strcat(cyclebuff, "   Compare {\n         EntryState CompareOpenData;\n      Waveform {\n");	/* }} */
			sprintf(SCATcycle, "         CompareClose @\"%s+%s %s\";\n",
				field[en[i]][fmtexpN[i]], DELAYEXP,
				(en[i] == 0) ? org[1] : (en[i] == 1) ? org[2] : (en[i] == 2) ? org[3] : (en[i] == 3) ? org[4] : "0.000ps");
			strcat(cellinfo[cellcnt].cellexpr, SCATcycle);
			strcat(cyclebuff, SCATcycle);
			cmp = 1;
			zcnt++;
		}
		else if (NULL != strstr(field[en[i]][fmtN[i]], "StrobeHigh")) {
			if (cmp == 0) strcat(cyclebuff, "   Compare {\n      Waveform {\n");	/* }} */
			sprintf(SCATcycle, "         CompareOpenHigh @\"%s+%s %s\";\n",
				field[en[i]][fmtexpN[i]], DELAYEXP,
				(en[i] == 0) ? org[1] : (en[i] == 1) ? org[2] : (en[i] == 2) ? org[3] : (en[i] == 3) ? org[4] : "0.000ps");
			strcat(cellinfo[cellcnt].cellexpr, SCATcycle);
			strcat(cyclebuff, SCATcycle);
			cmp = 1;
			zcnt++;
		}
		else if (NULL != strstr(field[en[i]][fmtN[i]], "StrobeLow")) {
			if (cmp == 0) strcat(cyclebuff, "   Compare {\n      Waveform {\n");	/* }} */
			sprintf(SCATcycle, "         CompareOpenLow @\"%s+%s %s\";\n",
				field[en[i]][fmtexpN[i]], DELAYEXP,
				(en[i] == 0) ? org[1] : (en[i] == 1) ? org[2] : (en[i] == 2) ? org[3] : (en[i] == 3) ? org[4] : "0.000ps");
			strcat(cellinfo[cellcnt].cellexpr, SCATcycle);
			strcat(cyclebuff, SCATcycle);
			cmp = 1;
			zcnt++;
		}
		else if (NULL != strstr(field[en[i]][fmtN[i]], "StrobeData")) {
			if (cmp == 0) strcat(cyclebuff, "   Compare {\n      Waveform {\n");	/* }} */
			sprintf(SCATcycle, "         CompareOpenData @\"%s+%s %s\";\n",
				field[en[i]][fmtexpN[i]], DELAYEXP,
				(en[i] == 0) ? org[1] : (en[i] == 1) ? org[2] : (en[i] == 2) ? org[3] : (en[i] == 3) ? org[4] : "0.000ps");
			strcat(cellinfo[cellcnt].cellexpr, SCATcycle);
			strcat(cyclebuff, SCATcycle);
			cmp = 1;
			zcnt++;
		}
	}
	/* { { */
	if (cmp) strcat(cyclebuff, "      }\n   }\n");
	if ((zcnt-1) != ne ) {
		fprintf(stderr,"OOPS didn't get the right number of drive/compare edges[%d][%d][%s]!!!\n",zcnt,ne,field[0][0]);
		}
/* ADD DEBUG PRINTS HERE for waveform processing analysis */
//	if (strstr(field[0][0],"DBUSstrobeWF")!=NULL) {
//		fprintf(stdout,"<%s>\n",cyclebuff);
//		}
	return (0);
}

/* this is called by process_edgeset_waveform() and process_edgesetdelay_waveform(), code was common */
int break_up_edges(int actablelines, int en[], int enable_edge[],
				 char name[][FINDME_SIZE + 1], char *findme, int which, int *forward) {
	/* findme & which are inputs, findme is the string we're processing for EdgeSet..., which says where in the actable.p file */
	/* outputs are en, enable_edge */
	int ne, i, edgenum, nonmatching_line;
	char findmejustname[FINDME_SIZE + 1];
	char *ptrOP, *ptrC, *ptrEDGE;

	ne = 0;

	ptrOP = strchr(findme, '(');	/* ) */
	if (ptrOP != NULL) strcpy(findmejustname, ptrOP);
	else strcpy(findmejustname, findme);
	ptrC = strchr(findmejustname, ',');
	if (ptrC != NULL) *(ptrC + 1) = '\0';		/* keep the comma */
	/* leave it otherwise */

	nonmatching_line = 0;

	for (i = 0; (which + i) < actablelines; i++) {
		/* go from here to end of file, terminating when different cell is reached */
		if (strstr(acwaves[which + i].w, findmejustname) == NULL) {	/* not matching what we're looking for */
			if (nonmatching_line == 0) nonmatching_line = i;
			if (strstr(acwaves[which + i].w, "WaveSet") != NULL ||
				strstr(acwaves[which + i].w, "EdgeSet") != NULL) {
				break;			/* terminate when we find the !wrong! waveform */
				}
			continue;
		}
		ptrEDGE = strstr(acwaves[which + i].w, ",Edge");
		if (ptrEDGE == NULL) {
				continue;/* not an Edge???? */
			}
		else ptrEDGE += sizeof(",Edge") - 1;	/* point at edge number */
		edgenum = *ptrEDGE - '0' - 1;
		en[edgenum] = edgenum;
		enable_edge[edgenum] = 1;
		strcpy(name[edgenum], acwaves[which + i].w);
		if (edgenum > ne) ne = edgenum;
	}
	*forward = nonmatching_line;	/* first nonmatching_line */
	for (i = 0; i <= ne; i++) fprintf(fpstatus, "   BUP[%d]=%s,%s\n", i, name[i], __FUNCTION__);
	fflush(fpstatus);
	return (ne);
}

int reduce_expressions(int ne, int en[], char name[][FINDME_SIZE + 1], char field[][100][WF_EXPR_LEN]) {
	int i, j, k, done, sl, eb, done2;
	char hold, *ptr0, *ptr1, *ptr1C, *tptr, type[WF_EXPR_LEN];

	for (i = 0; i <= ne; i++) {
		j = 0;
		ptr0 = strchr(name[en[i]], '(');
		if (ptr0 == NULL) continue;
		hold = *ptr0;
		*ptr0 = '\0';
		strcpy(type, name[en[i]]);
		*ptr0 = hold;
		ptr0++;
		eb = 0;
		done = 0;
		sl = strlen(name[en[i]]);
		while (!done) {
			ptr1 = strchr(ptr0, ',');
			ptr1C = strrchr(ptr0, ')');
			if (NULL == ptr1 && NULL == ptr1C) {
				done = 1;
				break;
			}
			if (ptr1 == NULL && ptr1C != NULL) ptr1 = ptr1C;
			if (ptr1C < ptr1 && ptr1C != NULL) {
				ptr1 = ptr1C;
				done = 1;
			}					/* this is for the case when it finds a ',' after a ')'. e.g.: */
			if (ptr1 == NULL) break;			/* in case there is nothing useful */
			if (ptr1 > name[en[i]] + sl) break;			/* in case there is nothing useful */
			hold = *ptr1;
			*ptr1 = '\0';
			strcpy(field[en[i]][j], ptr0);
			*ptr1 = hold;
			done2 = 0;
			while (NULL != (tptr = strstr(field[en[i]][j], "div")) && done2 == 0) {
				for (k = 3; k < strlen(tptr); k++) {
					if (*(tptr + k) == '+' ||*(tptr + k) == '-' || *(tptr + k) == ',' || *(tptr + k) == ')') break;
					if (!isdigit(*(tptr + k))) done2 = 1;
				}
				if (done2 == 0) {
					fprintf(fpstatus, "replacing \"div\" in %s   ", field[en[i]][j]);
					fprintf(fpstatus, "with \"/\"\n");
					*tptr = ' ';	/* d */
					*(tptr + 1) = ' ';	/* i */
					*(tptr + 2) = '/';	/* v */
				}
				else {			/* change it so we can keep processing */
					fprintf(stdout, "replacing \"div\" in %s   ", field[en[i]][j]);
					fprintf(stdout, "with \"DIV\"\n");
					*tptr = 'D';	/* d */
					*(tptr + 1) = 'I';	/* i */
					*(tptr + 2) = 'V';	/* v */
				}
			}
			while (NULL != (tptr = strstr(field[en[i]][j], "t["))) {
				*tptr = ' ';	/* t */
				*(tptr + 1) = ' ';	/* [ */
			}
			while (NULL != (tptr = strstr(field[en[i]][j], "]"))) {
				*tptr = ' ';	/* ] */
			}
			ptr0 = ptr1 + 1;
			j++;
			if (done) break;
		}
	}
	return (0);
}
