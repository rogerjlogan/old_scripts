/* ggm_process_waveforms.c process_waveforms(){} */

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

int process_waveforms(int actablelines, char *GCTNAME, char *cyclebuff, long *tell, int which, 
		int *forward, char *pin, int DSET, int CNT, int *modcode) {
	int i, j, eb, done, sl, wtlookup, eloc, laststart, ret, found;
	char org[MAX_EDGES + 1][WF_EXPR_LEN], cx, cX, tpin[PINSIZE];
	char *ptr0, *ptr1, *ptr1C, *tptr, *pelse, field[1][100][WF_EXPR_LEN];
	char type[WF_EXPR_LEN], copybuf[1000], dupwarn[WF_EXPR_LEN], hold;
	char fmtc1, fmtc2, fmtc3, fmtc4, am0, am1, am6, am7;
	char name[MAX_EDGES + 1][FINDME_SIZE + 1];
	int en[MAX_EDGES + 1], enable_edge[MAX_EDGES + 1];

	for (i = 0; i <= MAX_EDGES; i++) {
		en[i] = enable_edge[i] = 0;
		name[i][0] = '\0';
	}

	am6 = am7 = AM_BOGUS;
	
	strcpy(name[0], acwaves[which].w);
//  fprintf(stdout,"W[%s]%s\n",name[0],acwaves[which-1].w);
	eloc = acwaves[which].loc;
	laststart = acwaves[which + 0].laststart;
	if (CNT != 0) sprintf(dupwarn, "_MULTIPLE_DEF%03d", CNT);
	else dupwarn[0] = '\0';
	if (strstr(name[0], "WaveSet") != NULL) {
		sprintf(SCATcycle, "//DSET%d:%s\n", DSET, name[0]);
		strcat(cyclebuff, SCATcycle);
	}
	if (NULL == strstr(name[0], "WaveSet") && NULL == strstr(name[0], "EdgeSet"))
		return (-1);
	if (NULL != (pelse = strstr(name[0], ")elsebegin"))) {
		eb = 1;
		strcat(cyclebuff, "//Warning 'elsebegin' in waveform definition!!! FIXME!!!\n");
		fprintf(stderr, "//Warning 'elsebegin' in waveform definition!!! FIXME!!!, source[%s,%d,%s]\n", __FILE__, __LINE__, __FUNCTION__);
		fprintf(fperrors, "//Warning 'elsebegin' in waveform definition!!! FIXME!!!\n");
		*(pelse + 1) = '\0';
	}
	else if (NULL != (pelse = strstr(name[0], ")else"))) {
		strcat(cyclebuff, "//Warning 'else' in waveform definition!!! FIXME!!!\n");
		fprintf(stderr, "//Warning 'else' in waveform definition!!! FIXME!!!, source[%s,%d,%s]\n", __FILE__, __LINE__, __FUNCTION__);
		fprintf(fperrors, "//Warning 'else' in waveform definition!!! FIXME!!!\n");
		*(pelse + 1) = '\0';
	}
	j = 0;
	ptr0 = strchr(name[0], '(');
	if (ptr0 == NULL) return (-1);
	hold = *ptr0;
	*ptr0 = '\0';
	strcpy(type, name[0]);
	*ptr0 = hold;
	ptr0++;
	eb = 0;
	done = 0;
	sl = strlen(name[0]);
	while (!done) {
		ptr1 = strchr(ptr0, ',');
		ptr1C = strrchr(ptr0, ')');
		if (ptr1 == NULL && ptr1C == NULL) {
			done = 1;
			break;
		}
		if (ptr1 == NULL && ptr1C != NULL) ptr1 = ptr1C;
		if (ptr1C < ptr1 && ptr1C != NULL) {
			ptr1 = ptr1C;
			done = 1;
		}						/* this is for the case when it finds a ',' after a ')'. e.g.: */
		//WaveSetNR(INT_CLKSTPdriveWF,0ns)elseWaveSetNR(INT_CLKSTPdriveWF,t[tcCI]-t[tsuINTCLKSTP]+dtcf+1ns)
		if (ptr1 == NULL) break;				/* in case there is nothing useful */
		if (ptr1 > name[0] + sl) break;				/* in case there is nothing useful */
		hold = *ptr1;
		*ptr1 = '\0';
		strcpy(field[0][j], ptr0);
		*ptr1 = hold;
		while (NULL != (tptr = strstr(field[0][j], "div"))) {
			*tptr = ' ';		/* d */
			*(tptr + 1) = ' ';	/* i */
			*(tptr + 2) = '/';	/* v */
		}
		while (NULL != (tptr = strstr(field[0][j], "t["))) {
			*tptr = ' ';		/* t */
			*(tptr + 1) = ' ';	/* [ */
		}
		while (NULL != (tptr = strstr(field[0][j], "]"))) {
			*tptr = ' ';		/* ] */
		}
		ptr0 = ptr1 + 1;
		j++;
		if (done)
			break;
	}
/* need to search origin array also!!!!! */
	for (i = 0; i <= MAX_EDGES; i++)
		org[i][0] = '\0';
	ret = find_origin(&field[0][0][0], org, laststart, __FILE__);
	if (ret < 0) {
		exit(1);
	}
	wtlookup = (strstr(wavetypefull, type) - wavetypefull);
	cellinfo[cellcnt].filepos = *tell + strlen(cyclebuff);
	found = 0;
/* find which start/stop pair it lies between */
	for (i = 0; i < maxstartstop; i++) {	/* if we don't find it then it gets left at the multidef from above */
/* WAS: (APS 0/4/27/2009)  this exists in process_edgesets too! */
/*      if (startstop[i].type==SSSTART && startstop[i].loc<acwaves[which+0].loc) { */
/* NEW: */
		if (startstop[i].type == SSSTART
			&& startstop[i].loc <= acwaves[which + 0].loc
			&& startstop[startstop[i].startpt2stop].loc >= acwaves[which + 0].loc) {
			dupwarn[0] = cellinfo[cellcnt].cdtcode = startstop[i].cdtcode;
			cellinfo[cellcnt].cdtstr[0] = startstop[i].cdtcode;
//         fprintf(stdout,"FOUND[%s,%s,%c,%d], source[%s,%d,%s]\n",GCTNAME,field[0][0],
//             cellinfo[cellcnt].cdtstr[0],acwaves[which+0].loc,__FILE__,__LINE__,__FUNCTION__);
			cellinfo[cellcnt].cdtstr[1] = '\0';
			dupwarn[1] = '\0';
			found++;
			}
		}
	if (found == 0) {
		fprintf(stderr, "START/STOP NOT FOUND![%s,%s,%c,%d], source[%s,%d,%s]\n",
				GCTNAME, field[0][0], cellinfo[cellcnt].cdtstr[0], acwaves[which + 0].loc, __FILE__, __LINE__, __FUNCTION__);
		exit(1);
		}
	cellinfo[cellcnt].actline = which;
	strcpy(cellinfo[cellcnt].wftname, GCTNAME);
	strcpy(cellinfo[cellcnt].cellname, field[0][0]);
	strcpy(cellinfo[cellcnt].pin, pin);
	cellinfo[cellcnt].multidefnum = CNT;
	cellinfo[cellcnt].formatnum = wtlookup;
	cellinfo[cellcnt].cellexpr[0] = '\0';

	if (MUXFLAG && NOMUX == 0) sprintf(tpin, "%s-MUXSECONDARYPINS", pin);
	else strcpy(tpin, pin);

	if (0 == strcmp(type, "WaveSetClk")) {
		fmtc1 = FC_DRIVEDATA;
		fmtc2 = FC_DRIVELO;
		fmtc3 = fmtc4 = FC_NULLEDGE;
		*modcode = FC_DRIVEDATA;
		if (DSET == 0) {
			am0 = AM_driveLOD0;
			am1 = AM_driveHID0;
		}
		if (DSET == 1) {
			am0 = AM_driveLOD1;
			am1 = AM_driveHID1;
		}
		cellinfo[cellcnt].formats[0] = fmtc1;
		cellinfo[cellcnt].formats[1] = fmtc2;
		cellinfo[cellcnt].formats[2] = fmtc3;
		cellinfo[cellcnt].formats[3] = fmtc4;
		cellinfo[cellcnt].problemtype = PT_NOPROBLEM;
		cellinfo[cellcnt].alias0 = am0;
		cellinfo[cellcnt].alias1 = am1;
		sprintf(SCATcycle, "Cell \"%s\" %c/%c %s_DSET%01d%c%c%c%c_cat_%s {\n   Data %c/%c;\n",
				tpin, am0, am1, field[0][0], DSET, fmtc1, fmtc2, fmtc3,
				fmtc4, dupwarn, '6', '7');
		strcat(cyclebuff, SCATcycle);
		strcat(cyclebuff, "   Drive {\n      Waveform {");
		sprintf(SCATcycle, "DriveData @\"%s%s\";DriveLow @\"%s%s\";}\n   }\n",
				field[0][1], org[1], field[0][2], org[2]);
		strcat(cellinfo[cellcnt].cellexpr, SCATcycle);
		strcat(cyclebuff, SCATcycle);
		strcat(cyclebuff, "}\n");
		cellcnt++;
		if (cellcnt > MAXCELLS) {
			fprintf(stderr, "Too many Cells for buffer, source[%s,%d,%s]\n", __FILE__, __LINE__, __FUNCTION__);
			fprintf(fperrors, "Too many Cells for buffer, source[%s,%d,%s]\n", __FILE__, __LINE__, __FUNCTION__);
			exit(1);
		}
	}
	else if (0 == strcmp(type, "WaveSetContinue")) {
		/* we might need a cell which continues strobing but we'll add that once we have the complete cyclesetMD info */
		/* so print a note... */
		fprintf(fpstatus, "   FOUND [%s_%s_%s]%d POTENTIAL CONTINUE TO STROBEFULLCYCLE [%s]\n",
				field[0][0], GCTNAME, dupwarn, DSET, __FUNCTION__);
		fmtc1 = fmtc2 = fmtc3 = fmtc4 = FC_NULLEDGE;
		*modcode = FC_NULLEDGE;
		if (DSET == 0) {
			am0 = AM_continueLO;
			am1 = AM_continue;
		}
		if (DSET == 1) {
			am0 = AM_continueLO;
			am1 = AM_continue;
		}
		cellinfo[cellcnt].formats[0] = fmtc1;
		cellinfo[cellcnt].formats[1] = fmtc2;
		cellinfo[cellcnt].formats[2] = fmtc3;
		cellinfo[cellcnt].formats[3] = fmtc4;
		cellinfo[cellcnt].problemtype = PT_CONTINUE;
		cellinfo[cellcnt].alias0 = am0;
		cellinfo[cellcnt].alias1 = AM_BOGUS;
	  /**** this is special use pin instead of filtered MUXSECONDARYPINS tpin ****/
		sprintf(SCATcycle, "Cell \"%s\" %c %s_DSET%01d%c%c%c%cL_cat_%s {\n   Data %c;\n",
				pin, am0, field[0][0], DSET, fmtc1, fmtc2, fmtc3, fmtc4, dupwarn, '0');
		strcat(cyclebuff, SCATcycle);
		strcat(cyclebuff,                 "   Drive {   EntryState DriveOff;}\n   Compare {   EntryState CompareOpenLow;}\n");
		strcpy(cellinfo[cellcnt].cellexpr,"   Drive {   EntryState DriveOff;}\n   Compare {   EntryState CompareOpenLow;}\n");
		strcat(cyclebuff, "}\n");
		cellcnt++;
		if (cellcnt > MAXCELLS) {
			fprintf(stderr, "Too many Cells for buffer, source[%s,%d,%s]\n", __FILE__, __LINE__, __FUNCTION__);
			fprintf(fperrors, "Too many Cells for buffer, source[%s,%d,%s]\n", __FILE__, __LINE__, __FUNCTION__);
			exit(1);
			}
		cellinfo[cellcnt].cdtstr[0] = startstop[i].cdtcode;
		cellinfo[cellcnt].cdtstr[1] = '\0';
		cellinfo[cellcnt].filepos = *tell + strlen(cyclebuff);
		cellinfo[cellcnt].actline = which;
		strcpy(cellinfo[cellcnt].wftname, GCTNAME);
		strcpy(cellinfo[cellcnt].cellname, field[0][0]);
		strcpy(cellinfo[cellcnt].pin, pin);
		cellinfo[cellcnt].multidefnum = CNT;
		cellinfo[cellcnt].formatnum = wtlookup;
		cellinfo[cellcnt].formats[0] = fmtc1;
		cellinfo[cellcnt].formats[1] = fmtc2;
		cellinfo[cellcnt].formats[2] = fmtc3;
		cellinfo[cellcnt].formats[3] = fmtc4;
		cellinfo[cellcnt].problemtype = PT_CONTINUE;
		cellinfo[cellcnt].alias0 = AM_BOGUS;
		cellinfo[cellcnt].alias1 = am1;
	  /**** this is special use pin instead of filtered MUXSECONDARYPINS tpin ****/
		sprintf(SCATcycle, "Cell \"%s\" %c %s_DSET%01d%c%c%c%cH_cat_%s {\n   Data %c;\n",
				pin, am1, field[0][0], DSET, fmtc1, fmtc2, fmtc3, fmtc4, dupwarn, '1');
		strcat(cyclebuff, SCATcycle);
		strcat(cyclebuff, 					 "   Drive {   EntryState DriveOff;}\n   Compare {   EntryState CompareOpenHigh;}\n");
		strcpy(cellinfo[cellcnt].cellexpr,"   Drive {   EntryState DriveOff;}\n   Compare {   EntryState CompareOpenHigh;}\n");
		strcat(cyclebuff, "}\n");
		cellcnt++;
		if (cellcnt > MAXCELLS) {
			fprintf(stderr, "Too many Cells for buffer, source[%s,%d,%s]\n", __FILE__, __LINE__, __FUNCTION__);
			fprintf(fperrors, "Too many Cells for buffer, source[%s,%d,%s]\n", __FILE__, __LINE__, __FUNCTION__);
			exit(1);
		}
/* continue drive will come from the generic/COMMON_WFT */
	}
	else if (0 == strcmp(type, "WaveSetDoubleClk")) {
		fmtc1 = FC_DRIVEDATA;
		fmtc2 = FC_DRIVELO;
		fmtc3 = FC_DRIVEDATA;
		fmtc4 = FC_DRIVELO;
		*modcode = FC_DRIVEDATA;
		if (DSET == 0) {
			am0 = AM_driveLOD0;
			am1 = AM_driveHID0;
		}
		if (DSET == 1) {
			am0 = AM_driveLOD1;
			am1 = AM_driveHID1;
		}
		cellinfo[cellcnt].formats[0] = fmtc1;
		cellinfo[cellcnt].formats[1] = fmtc2;
		cellinfo[cellcnt].formats[2] = fmtc3;
		cellinfo[cellcnt].formats[3] = fmtc4;
		cellinfo[cellcnt].problemtype = PT_NOPROBLEM;
		cellinfo[cellcnt].alias0 = am0;
		cellinfo[cellcnt].alias1 = am1;
		sprintf(SCATcycle, "Cell \"%s\" %c/%c %s_DSET%01d%c%c%c%c_cat_%s {\n   Data %c/%c;\n",
				tpin, am0, am1, field[0][0], DSET, fmtc1, fmtc2, fmtc3, fmtc4, dupwarn, '6', '7');
		strcat(cyclebuff, SCATcycle);
		strcat(cyclebuff, "   Drive {\n      Waveform {");
		sprintf(SCATcycle, "DriveData @\"%s%s\";DriveLow @\"%s%s\";DriveData @\"%s%s\";DriveLow @\"%s%s\";}\n   }\n",
				field[0][1], org[1], field[0][2], org[2], field[0][3], org[3], field[0][4], org[4]);
		strcat(cellinfo[cellcnt].cellexpr, SCATcycle);
		strcat(cyclebuff, SCATcycle);
		strcat(cyclebuff, "}\n");
		cellcnt++;
		if (cellcnt > MAXCELLS) {
			fprintf(stderr, "Too many Cells for buffer, source[%s,%d,%s]\n", __FILE__, __LINE__, __FUNCTION__);
			fprintf(fperrors, "Too many Cells for buffer, source[%s,%d,%s]\n", __FILE__, __LINE__, __FUNCTION__);
			exit(1);
		}
	}
	else if (0 == strcmp(type, "WaveSetNR")) {
		fmtc1 = FC_DRIVEDATA;
		fmtc2 = fmtc3 = fmtc4 = FC_NULLEDGE;
		*modcode = FC_DRIVEDATA;
		if (DSET == 0) {
			am0 = AM_driveLOD0;
			am1 = AM_driveHID0;
		}
		if (DSET == 1) {
			am0 = AM_driveLOD1;
			am1 = AM_driveHID1;
		}
		cellinfo[cellcnt].formats[0] = fmtc1;
		cellinfo[cellcnt].formats[1] = fmtc2;
		cellinfo[cellcnt].formats[2] = fmtc3;
		cellinfo[cellcnt].formats[3] = fmtc4;
		cellinfo[cellcnt].problemtype = PT_NOPROBLEM;
		cellinfo[cellcnt].alias0 = am0;
		cellinfo[cellcnt].alias1 = am1;
		sprintf(SCATcycle, "Cell \"%s\" %c/%c %s_DSET%01d%c%c%c%c_cat_%s {\n   Data %c/%c;\n",
				tpin, am0, am1, field[0][0], DSET, fmtc1, fmtc2, fmtc3, fmtc4, dupwarn, '6', '7');
		strcat(cyclebuff, SCATcycle);
		strcat(cyclebuff, "   Drive {\n      Waveform {");
		sprintf(SCATcycle, "DriveData @\"%s%s\";}\n   }\n", field[0][1], org[1]);
		strcat(cellinfo[cellcnt].cellexpr, SCATcycle);
		strcat(cyclebuff, SCATcycle);
		strcat(cyclebuff, "}\n");
		cellcnt++;
		if (cellcnt > MAXCELLS) {
			fprintf(stderr, "Too many Cells for buffer, source[%s,%d,%s]\n", __FILE__, __LINE__, __FUNCTION__);
			fprintf(fperrors, "Too many Cells for buffer, source[%s,%d,%s]\n", __FILE__, __LINE__, __FUNCTION__);
			exit(1);
		}
	}
	else if (0 == strcmp(type, "WaveSetOff")) {
		/* this is DriveOff,StrobeOff */
		/* this has potential to kill an existing open window strobe: */
		fprintf(fpstatus, "   FOUND [%s_%s_%s]%d POTENTIAL KILL TO WINDOWSTROBE [%s]\n",
				field[0][0], GCTNAME, dupwarn, DSET, __FUNCTION__);
		fmtc1 = FC_DRIVEOFF;
		fmtc2 = FC_STROBEOFF;
		fmtc3 = fmtc4 = FC_NULLEDGE;
		*modcode = FC_DRVSTRBOFF;
		if (DSET == 0) {
			am0 = AM_strobeoffLOD0;
			am1 = AM_strobeoffHID0;
			am6 = AM_driveoffLOD0;
			am7 = AM_driveoffHID0;
		}
		if (DSET == 1) {
			am0 = AM_strobeoffLOD1;
			am1 = AM_strobeoffHID1;
			am6 = AM_driveoffLOD1;
			am7 = AM_driveoffHID1;
		}
		cx = (DSET == 0) ? AM_maskD0 : AM_maskD1;
		cX = (DSET == 0) ? AM_maskHID0 : AM_maskHID1;
		cellinfo[cellcnt].alias0 = am0;
		cellinfo[cellcnt].alias1 = am1;
		sprintf(SCATcycle, "Cell \"%s\" %c/%c/%c/%c/%c/%c %s_DSET%01d%c%c%c%c_cat_%s {\n   Data %c/%c/%c/%c/%c/%c;\n",
				tpin, am0, am1, cx, cX, am6, am7, field[0][0], DSET, fmtc1, fmtc2, fmtc3, fmtc4, dupwarn, '0', '1', '2', '3','6','7');
		strcat(cyclebuff, SCATcycle);
		cellinfo[cellcnt].formats[0] = fmtc1;
		cellinfo[cellcnt].formats[1] = fmtc2;
		cellinfo[cellcnt].formats[2] = fmtc3;
		cellinfo[cellcnt].formats[3] = fmtc4;
		cellinfo[cellcnt].problemtype = PT_CLOSE;
		strcat(cyclebuff, "   Drive {\n      Waveform {");
		sprintf(SCATcycle, "DriveOff @\"%s%s\";}\n   }\n", field[0][1], org[1]);
		strcat(cellinfo[cellcnt].cellexpr, SCATcycle);
		strcat(cyclebuff, SCATcycle);
		strcat(cyclebuff, "   Compare {\n         EntryState CompareOpenData;\n      Waveform {");
		sprintf(SCATcycle, "\n         CompareClose @\"%s%s\";}\n   }\n", field[0][2], org[1]);
		strcat(cellinfo[cellcnt].cellexpr, SCATcycle);
		strcat(cyclebuff, SCATcycle);
		strcat(cyclebuff, "}\n");
		cellcnt++;
		if (cellcnt > MAXCELLS) {
			fprintf(stderr, "Too many Cells for buffer, source[%s,%d,%s]\n", __FILE__, __LINE__, __FUNCTION__);
			fprintf(fperrors, "Too many Cells for buffer, source[%s,%d,%s]\n", __FILE__, __LINE__, __FUNCTION__);
			exit(1);
		}
	}
	else if (0 == strcmp(type, "WaveSetRTO")) {
		fmtc1 = FC_DRIVEDATA;
		fmtc2 = FC_DRIVEHI;
		fmtc3 = fmtc4 = FC_NULLEDGE;
		*modcode = FC_DRIVEDATA;
		if (DSET == 0) {
			am0 = AM_driveLOD0;
			am1 = AM_driveHID0;
		}
		if (DSET == 1) {
			am0 = AM_driveLOD1;
			am1 = AM_driveHID1;
		}
		cellinfo[cellcnt].formats[0] = fmtc1;
		cellinfo[cellcnt].formats[1] = fmtc2;
		cellinfo[cellcnt].formats[2] = fmtc3;
		cellinfo[cellcnt].formats[3] = fmtc4;
		cellinfo[cellcnt].problemtype = PT_NOPROBLEM;
		cellinfo[cellcnt].alias0 = am0;
		cellinfo[cellcnt].alias1 = am1;
		sprintf(SCATcycle, "Cell \"%s\" %c/%c %s_DSET%01d%c%c%c%c_cat_%s {\n   Data %c/%c;\n",
				tpin, am0, am1, field[0][0], DSET, fmtc1, fmtc2, fmtc3, fmtc4, dupwarn, '6', '7');
		strcat(cyclebuff, SCATcycle);
		strcat(cyclebuff, "   Drive {\n      Waveform {");
		sprintf(SCATcycle, "DriveData @\"%s%s\";DriveHigh @\"%s%s\";}\n   }\n",
				field[0][1], org[1], field[0][2], org[2]);
		strcat(cellinfo[cellcnt].cellexpr, SCATcycle);
		strcat(cyclebuff, SCATcycle);
		strcat(cyclebuff, "}\n");
		cellcnt++;
		if (cellcnt > MAXCELLS) {
			fprintf(stderr, "Too many Cells for buffer, source[%s,%d,%s]\n", __FILE__, __LINE__, __FUNCTION__);
			fprintf(fperrors, "Too many Cells for buffer, source[%s,%d,%s]\n", __FILE__, __LINE__, __FUNCTION__);
			exit(1);
		}
	}
	else if (0 == strcmp(type, "WaveSetRTZ")) {
		fmtc1 = FC_DRIVEDATA;
		fmtc2 = FC_DRIVELO;
		fmtc3 = fmtc4 = FC_NULLEDGE;
		*modcode = FC_DRIVEDATA;
		if (DSET == 0) {
			am0 = AM_driveLOD0;
			am1 = AM_driveHID0;
		}
		if (DSET == 1) {
			am0 = AM_driveLOD1;
			am1 = AM_driveHID1;
		}
		cellinfo[cellcnt].formats[0] = fmtc1;
		cellinfo[cellcnt].formats[1] = fmtc2;
		cellinfo[cellcnt].formats[2] = fmtc3;
		cellinfo[cellcnt].formats[3] = fmtc4;
		cellinfo[cellcnt].problemtype = PT_NOPROBLEM;
		cellinfo[cellcnt].alias0 = am0;
		cellinfo[cellcnt].alias1 = am1;
		sprintf(SCATcycle, "Cell \"%s\" %c/%c %s_DSET%01d%c%c%c%c_cat_%s {\n   Data %c/%c;\n",
				tpin, am0, am1, field[0][0], DSET, fmtc1, fmtc2, fmtc3, fmtc4, dupwarn, '6', '7');
		strcat(cyclebuff, SCATcycle);
		strcat(cyclebuff, "   Drive {\n      Waveform {");
		sprintf(SCATcycle, "DriveData @\"%s%s\";DriveLow @\"%s%s\";}\n   }\n",
				field[0][1], org[1], field[0][2], org[2]);
		strcat(cellinfo[cellcnt].cellexpr, SCATcycle);
		strcat(cyclebuff, SCATcycle);
		strcat(cyclebuff, "}\n");
		cellcnt++;
		if (cellcnt > MAXCELLS) {
			fprintf(stderr, "Too many Cells for buffer, source[%s,%d,%s]\n", __FILE__, __LINE__, __FUNCTION__);
			fprintf(fperrors, "Too many Cells for buffer, source[%s,%d,%s]\n", __FILE__, __LINE__, __FUNCTION__);
			exit(1);
		}
	}
	else if (0 == strcmp(type, "WaveSetSBC")) {
		fmtc1 = FC_DRIVECOMP;
		fmtc2 = FC_DRIVEDATA;
		fmtc3 = FC_DRIVECOMP;
		fmtc4 = FC_NULLEDGE;
		*modcode = FC_DRIVEDATA;
		if (DSET == 0) {
			am0 = AM_driveLOD0;
			am1 = AM_driveHID0;
		}
		if (DSET == 1) {
			am0 = AM_driveLOD1;
			am1 = AM_driveHID1;
		}
		cellinfo[cellcnt].formats[0] = fmtc1;
		cellinfo[cellcnt].formats[1] = fmtc2;
		cellinfo[cellcnt].formats[2] = fmtc3;
		cellinfo[cellcnt].formats[3] = fmtc4;
		cellinfo[cellcnt].problemtype = PT_NOPROBLEM;
		cellinfo[cellcnt].alias0 = am0;
		cellinfo[cellcnt].alias1 = am1;
		sprintf(SCATcycle, "Cell \"%s\" %c/%c %s_DSET%01d%c%c%c%c_cat_%s {\n   Data %c/%c;\n",
				tpin, am0, am1, field[0][0], DSET, fmtc1, fmtc2, fmtc3, fmtc4, dupwarn, '6', '7');
		strcat(cyclebuff, SCATcycle);
		strcat(cyclebuff, "   Drive {\n      Waveform {");
		sprintf(SCATcycle, "DriveDataNot @\"%s%s\";DriveData @\"%s%s\";DriveDataNot @\"%s%s\";}\n   }\n",
				field[0][1], org[1], field[0][2], org[2], field[0][3], org[3]);
		strcat(cellinfo[cellcnt].cellexpr, SCATcycle);
		strcat(cyclebuff, SCATcycle);
		strcat(cyclebuff, "}\n");
		cellcnt++;
		if (cellcnt > MAXCELLS) {
			fprintf(stderr, "Too many Cells for buffer, source[%s,%d,%s]\n", __FILE__, __LINE__, __FUNCTION__);
			fprintf(fperrors, "Too many Cells for buffer, source[%s,%d,%s]\n", __FILE__, __LINE__, __FUNCTION__);
			exit(1);
		}
	}
	else if (0 == strcmp(type, "WaveSetStrobe")) {
		fmtc1 = FC_DRIVEOFF;
		fmtc2 = FC_WINDOWDATA;
		fmtc3 = FC_STROBEOFF;
		fmtc4 = FC_NULLEDGE;
		*modcode = FC_WINDOWDATA;
		if (DSET == 0) {
			am0 = AM_windowLOD0;
			am1 = AM_windowHID0;
		}
		if (DSET == 1) {
			am0 = AM_windowLOD1;
			am1 = AM_windowHID1;
		}
		cellinfo[cellcnt].formats[0] = fmtc1;
		cellinfo[cellcnt].formats[1] = fmtc2;
		cellinfo[cellcnt].formats[2] = fmtc3;
		cellinfo[cellcnt].formats[3] = fmtc4;
		cellinfo[cellcnt].problemtype = PT_NOPROBLEM;
		cellinfo[cellcnt].alias0 = am0;
		cellinfo[cellcnt].alias1 = am1;
		cx = (DSET == 0) ? AM_maskD0 : AM_maskD1;
		cX = (DSET == 0) ? AM_maskHID0 : AM_maskHID1;
		sprintf(SCATcycle, "Cell \"%s\" %c/%c/%c/%c %s_DSET%01d%c%c%c%c_cat_%s {\n   Data %c/%c/%c/%c;\n",
				tpin, am0, am1, cx, cX, field[0][0], DSET, fmtc1, fmtc2, fmtc3, fmtc4, dupwarn, '0', '1', '2', '3');
		strcat(cyclebuff, SCATcycle);
		strcat(cyclebuff, "   Drive {\n      Waveform {");
		sprintf(SCATcycle, "DriveOff @\"%s%s\";}\n   }\n", field[0][1], org[1]);
		strcat(cellinfo[cellcnt].cellexpr, SCATcycle);
		strcat(cyclebuff, SCATcycle);
		strcat(cyclebuff, "   Compare {\n      Waveform {\n");
		sprintf(SCATcycle, "         CompareOpenData @\"%s%s\";\n         CompareClose @\"%s%s\";}\n   }\n",
				field[0][2], org[2], field[0][3], org[3]);
		strcat(cellinfo[cellcnt].cellexpr, SCATcycle);
		strcat(cyclebuff, SCATcycle);
		strcat(cyclebuff, "}\n");
		cellcnt++;
		if (cellcnt > MAXCELLS) {
			fprintf(stderr, "Too many Cells for buffer, source[%s,%d,%s]\n", __FILE__, __LINE__, __FUNCTION__);
			fprintf(fperrors, "Too many Cells for buffer, source[%s,%d,%s]\n", __FILE__, __LINE__, __FUNCTION__);
			exit(1);
		}
	}
	else if (0 == strcmp(type, "WaveSetEdgeStrobe")) {
		fmtc1 = FC_DRIVEOFF;
		fmtc2 = FC_EDGEDATA;
		fmtc3 = FC_LATCH;
		fmtc4 = FC_NULLEDGE;
		*modcode = FC_EDGEDATA;
		if (DSET == 0) {
			am0 = AM_edgestbLOD0;
			am1 = AM_edgestbHID0;
		}
		if (DSET == 1) {
			am0 = AM_edgestbLOD1;
			am1 = AM_edgestbHID1;
		}
		cellinfo[cellcnt].formats[0] = fmtc1;
		cellinfo[cellcnt].formats[1] = fmtc2;
		cellinfo[cellcnt].formats[2] = fmtc3;
		cellinfo[cellcnt].formats[3] = fmtc4;
		cellinfo[cellcnt].problemtype = PT_NOPROBLEM;
		cellinfo[cellcnt].alias0 = am0;
		cellinfo[cellcnt].alias1 = am1;
		cx = (DSET == 0) ? AM_maskD0 : AM_maskD1;
		cX = (DSET == 0) ? AM_maskHID0 : AM_maskHID1;
		sprintf(SCATcycle, "Cell \"%s\" %c/%c/%c/%c %s_DSET%01d%c%c%c%c_cat_%s {\n   Data %c/%c/%c/%c;\n",
				tpin, am0, am1, cx, cX, field[0][0], DSET, fmtc1, fmtc2, fmtc3, fmtc4, dupwarn, '0', '1', '2', '3');
		strcat(cyclebuff, SCATcycle);
		strcat(cyclebuff, "   Drive {\n      Waveform {");
		sprintf(SCATcycle, "DriveOff @\"%s%s\";}\n   }\n", field[0][1], org[1]);
		strcat(cellinfo[cellcnt].cellexpr, SCATcycle);
		strcat(cyclebuff, SCATcycle);
		strcat(cyclebuff, "   Compare {\n      Waveform {");
		sprintf(SCATcycle, " CompareData @\"%s%s\";}\n   }\n", field[0][2], org[2]);
		strcat(cellinfo[cellcnt].cellexpr, SCATcycle);
		strcat(cyclebuff, SCATcycle);
		strcat(cyclebuff, "}\n");
		cellcnt++;
		if (cellcnt > MAXCELLS) {
			fprintf(stderr, "Too many Cells for buffer, source[%s,%d,%s]\n", __FILE__, __LINE__, __FUNCTION__);
			fprintf(fperrors, "Too many Cells for buffer, source[%s,%d,%s]\n", __FILE__, __LINE__, __FUNCTION__);
			exit(1);
		}
	}
	else if (0 == strcmp(type, "WaveSetStrobeZ")) {
		fmtc1 = FC_DRIVEOFF;
		fmtc2 = FC_WINDOWFLOAT;
		fmtc3 = FC_STROBEOFF;
		fmtc4 = FC_NULLEDGE;
		*modcode = FC_WINDOWFLOAT;
		if (DSET == 0) {
			am0 = AM_windowfloatD0;
			am1 = AM_windowfloatD0;
		}
		if (DSET == 1) {
			am0 = AM_windowfloatD1;
			am1 = AM_windowfloatD1;
		}
		cellinfo[cellcnt].formats[0] = fmtc1;
		cellinfo[cellcnt].formats[1] = fmtc2;
		cellinfo[cellcnt].formats[2] = fmtc3;
		cellinfo[cellcnt].formats[3] = fmtc4;
		cellinfo[cellcnt].problemtype = PT_NOPROBLEM;
		cellinfo[cellcnt].alias0 = am0;
		cellinfo[cellcnt].alias1 = am1;
		cx = (DSET == 0) ? AM_maskD0 : AM_maskD1;
		cX = (DSET == 0) ? AM_maskHID0 : AM_maskHID1;
		sprintf(SCATcycle, "Cell \"%s\" %c/%c %s_DSET%01d%c%c%c%c_cat_%s {\n   Data %c/%c;\n",
				tpin, am0, cx, field[0][0], DSET, fmtc1, fmtc2, fmtc3, fmtc4, dupwarn, '0', '2');
		strcat(cyclebuff, SCATcycle);
		strcat(cyclebuff, "   Drive {\n      Waveform {");
		sprintf(SCATcycle, "DriveOff @\"%s%s\";}\n   }\n", field[0][1], org[1]);
		strcat(cellinfo[cellcnt].cellexpr, SCATcycle);
		strcat(cyclebuff, SCATcycle);
		strcat(cyclebuff, "   Compare {\n      Waveform {");
		sprintf(SCATcycle, " CompareOpenFloat @\"%s%s\";\n         CompareClose @\"%s%s\";}\n   }\n",
				field[0][2], org[2], field[0][3], org[3]);
		strcat(cellinfo[cellcnt].cellexpr, SCATcycle);
		strcat(cyclebuff, SCATcycle);
		strcat(cyclebuff, "}\n");
		cellcnt++;
		if (cellcnt > MAXCELLS) {
			fprintf(stderr, "Too many Cells for buffer, source[%s,%d,%s]\n", __FILE__, __LINE__, __FUNCTION__);
			fprintf(fperrors, "Too many Cells for buffer, source[%s,%d,%s]\n", __FILE__, __LINE__, __FUNCTION__);
			exit(1);
		}
	}
	else if (0 == strcmp(type, "WaveSetEdgeStrobeZ")) {
		fmtc1 = FC_DRIVEOFF;
		fmtc2 = FC_EDGEDATA;
		fmtc3 = FC_LATCH;
		fmtc4 = FC_NULLEDGE;
		*modcode = FC_EDGEFLOAT;
		if (DSET == 0) {
			am0 = AM_edgefloatD0;
			am1 = AM_edgefloatD0;
		}
		if (DSET == 1) {
			am0 = AM_edgefloatD1;
			am1 = AM_edgefloatD1;
		}
		cellinfo[cellcnt].formats[0] = fmtc1;
		cellinfo[cellcnt].formats[1] = fmtc2;
		cellinfo[cellcnt].formats[2] = fmtc3;
		cellinfo[cellcnt].formats[3] = fmtc4;
		cellinfo[cellcnt].problemtype = PT_NOPROBLEM;
		cellinfo[cellcnt].alias0 = am0;
		cellinfo[cellcnt].alias1 = am1;
		cx = (DSET == 0) ? AM_maskD0 : AM_maskD1;
		cX = (DSET == 0) ? AM_maskHID0 : AM_maskHID1;
		sprintf(SCATcycle, "Cell \"%s\" %c/%c %s_DSET%01d%c%c%c%c_cat_%s {\n   Data %c/%c;\n",
				tpin, am0, cx, field[0][0], DSET, fmtc1, fmtc2, fmtc3, fmtc4, dupwarn, '0', '2');
		strcat(cyclebuff, SCATcycle);
		strcat(cyclebuff, "   Drive {\n      Waveform {");
		sprintf(SCATcycle, "DriveOff @\"%s%s\";}\n   }\n", field[0][1], org[1]);
		strcat(cellinfo[cellcnt].cellexpr, SCATcycle);
		strcat(cyclebuff, SCATcycle);
		strcat(cyclebuff, "   Compare {\n      Waveform {");
		sprintf(SCATcycle, " CompareFloat @\"%s%s\";}\n   }\n", field[0][2], org[2]);
		strcat(cellinfo[cellcnt].cellexpr, SCATcycle);
		strcat(cyclebuff, SCATcycle);
		strcat(cyclebuff, "}\n");
		cellcnt++;
		if (cellcnt > MAXCELLS) {
			fprintf(stderr, "Too many Cells for buffer, source[%s,%d,%s]\n", __FILE__, __LINE__, __FUNCTION__);
			fprintf(fperrors, "Too many Cells for buffer, source[%s,%d,%s]\n", __FILE__, __LINE__, __FUNCTION__);
			exit(1);
		}
	}
	else if (0 == strcmp(type, "WaveSetDelayClk")) {
		fmtc1 = FC_DRIVEDATA;
		fmtc2 = FC_DRIVELO;
		fmtc3 = fmtc4 = FC_NULLEDGE;
		*modcode = FC_DRIVEDATA;
		if (DSET == 0) {
			am0 = AM_driveLOD0;
			am1 = AM_driveHID0;
		}
		if (DSET == 1) {
			am0 = AM_driveLOD1;
			am1 = AM_driveHID1;
		}
		cellinfo[cellcnt].formats[0] = fmtc1;
		cellinfo[cellcnt].formats[1] = fmtc2;
		cellinfo[cellcnt].formats[2] = fmtc3;
		cellinfo[cellcnt].formats[3] = fmtc4;
		cellinfo[cellcnt].problemtype = PT_NOPROBLEM;
		cellinfo[cellcnt].alias0 = am0;
		cellinfo[cellcnt].alias1 = am1;
		sprintf(SCATcycle,
				"Cell \"%s\" %c/%c %s_DSET%01d%c%c%c%c_cat_%s {\n   Data %c/%c;\n",
				tpin, am0, am1, field[0][0], DSET, fmtc1, fmtc2, fmtc3, fmtc4, dupwarn, '6', '7');
		strcat(cyclebuff, SCATcycle);
		strcat(cyclebuff, "   Drive {\n      Waveform {");
		sprintf(SCATcycle,
				"DriveData @\"%s%s+%s*%s\";DriveLow @\"%s%s+%s*%s\";}\n   }\n",
				field[0][1], org[1], field[0][3], tperiod, field[0][2], org[2], field[0][4], tperiod);
		strcat(cellinfo[cellcnt].cellexpr, SCATcycle);
		strcat(cyclebuff, SCATcycle);
		strcat(cyclebuff, "}\n");
		cellcnt++;
		if (cellcnt > MAXCELLS) {
			fprintf(stderr, "Too many Cells for buffer, source[%s,%d,%s]\n", __FILE__, __LINE__, __FUNCTION__);
			fprintf(fperrors, "Too many Cells for buffer, source[%s,%d,%s]\n", __FILE__, __LINE__, __FUNCTION__);
			exit(1);
		}
	}
/* no wavesetdelaycontinue */
	else if (0 == strcmp(type, "WaveSetDelayDoubleClk")) {
		fmtc1 = FC_DRIVEDATA;
		fmtc2 = FC_DRIVELO;
		fmtc3 = FC_DRIVEDATA;
		fmtc3 = FC_DRIVELO;
		*modcode = FC_DRIVEDATA;
		if (DSET == 0) {
			am0 = AM_driveLOD0;
			am1 = AM_driveHID0;
		}
		if (DSET == 1) {
			am0 = AM_driveLOD1;
			am1 = AM_driveHID1;
		}
		cellinfo[cellcnt].formats[0] = fmtc1;
		cellinfo[cellcnt].formats[1] = fmtc2;
		cellinfo[cellcnt].formats[2] = fmtc3;
		cellinfo[cellcnt].formats[3] = fmtc4;
		cellinfo[cellcnt].problemtype = PT_NOPROBLEM;
		cellinfo[cellcnt].alias0 = am0;
		cellinfo[cellcnt].alias1 = am1;
		sprintf(SCATcycle, "Cell \"%s\" %c/%c %s_DSET%01d%c%c%c%c_cat_%s {\n   Data %c/%c;\n",
				tpin, am0, am1, field[0][0], DSET, fmtc1, fmtc2, fmtc3, fmtc4, dupwarn, '6', '7');
		strcat(cyclebuff, SCATcycle);
		strcat(cyclebuff, "   Drive {\n      Waveform {");
		sprintf(SCATcycle, "DriveData @\"%s%s+%s*%s\";DriveLow @\"%s%s+%s*%s\";DriveData @\"%s%s+%s*%s\";DriveLow @\"%s%s+%s*%s\";}\n   }\n",
				field[0][1], org[1], field[0][5], tperiod, field[0][2], org[2], 
				field[0][6], tperiod, field[0][3], org[3], field[0][7], tperiod, 
				field[0][4], org[4], field[0][8], tperiod);
		strcat(cellinfo[cellcnt].cellexpr, SCATcycle);
		strcat(cyclebuff, SCATcycle);
		strcat(cyclebuff, "}\n");
		cellcnt++;
		if (cellcnt > MAXCELLS) {
			fprintf(stderr, "Too many Cells for buffer, source[%s,%d,%s]\n", __FILE__, __LINE__, __FUNCTION__);
			fprintf(fperrors, "Too many Cells for buffer, source[%s,%d,%s]\n", __FILE__, __LINE__, __FUNCTION__);
			exit(1);
		}
	}
	else if (0 == strcmp(type, "WaveSetDelayNR")) {
		fmtc1 = FC_DRIVEDATA;
		fmtc2 = fmtc3 = fmtc4 = FC_NULLEDGE;
		*modcode = FC_DRIVEDATA;
		if (DSET == 0) {
			am0 = AM_driveLOD0;
			am1 = AM_driveHID0;
		}
		if (DSET == 1) {
			am0 = AM_driveLOD1;
			am1 = AM_driveHID1;
		}
		cellinfo[cellcnt].formats[0] = fmtc1;
		cellinfo[cellcnt].formats[1] = fmtc2;
		cellinfo[cellcnt].formats[2] = fmtc3;
		cellinfo[cellcnt].formats[3] = fmtc4;
		cellinfo[cellcnt].problemtype = PT_NOPROBLEM;
		cellinfo[cellcnt].alias0 = am0;
		cellinfo[cellcnt].alias1 = am1;
		sprintf(SCATcycle, "Cell \"%s\" %c/%c %s_DSET%01d%c%c%c%c_cat_%s {\n   Data %c/%c;\n",
				tpin, am0, am1, field[0][0], DSET, fmtc1, fmtc2, fmtc3, fmtc4, dupwarn, '6', '7');
		strcat(cyclebuff, SCATcycle);
		strcat(cyclebuff, "   Drive {\n      Waveform {");
		sprintf(SCATcycle, "DriveData @\"%s%s+%s*%s\";}\n   }\n", field[0][1], org[1], field[0][2], tperiod);
		strcat(cellinfo[cellcnt].cellexpr, SCATcycle);
		strcat(cyclebuff, SCATcycle);
		strcat(cyclebuff, "}\n");
		cellcnt++;
		if (cellcnt > MAXCELLS) {
			fprintf(stderr, "Too many Cells for buffer, source[%s,%d,%s]\n", __FILE__, __LINE__, __FUNCTION__);
			fprintf(fperrors, "Too many Cells for buffer, source[%s,%d,%s]\n", __FILE__, __LINE__, __FUNCTION__);
			exit(1);
		}
	}
	else if (0 == strcmp(type, "WaveSetDelayOff")) {
		/* this has potential to kill an existing open window strobe: */
		fprintf(fpstatus, "   FOUND [%s_%s_%s]%d POTENTIAL KILL TO WINDOWSTROBE [%s]\n",
			field[0][0], GCTNAME, dupwarn, DSET, __FUNCTION__);
		fmtc1 = FC_DRIVEOFF;
		fmtc2 = FC_STROBEOFF;
		fmtc3 = fmtc4 = FC_NULLEDGE;
		*modcode = FC_DRIVEOFF;
		if (DSET == 0) {
			am0 = AM_strobeoffLOD0;
			am1 = AM_strobeoffHID0;
			am6 = AM_driveoffLOD0;
			am7 = AM_driveoffHID0;
		}
		if (DSET == 1) {
			am0 = AM_strobeoffLOD1;
			am1 = AM_strobeoffHID1;
			am6 = AM_driveoffLOD1;
			am7 = AM_driveoffHID1;
		}
		cx = (DSET == 0) ? AM_maskD0 : AM_maskD1;
		cX = (DSET == 0) ? AM_maskHID0 : AM_maskHID1;
		cellinfo[cellcnt].alias0 = am0;
		cellinfo[cellcnt].alias1 = am1;
		sprintf(SCATcycle, "Cell \"%s\" %c/%c/%c/%c/%c/%c %s_DSET%01d%c%c%c%c_cat_%s {\n   Data %c/%c/%c/%c/%c/%c;\n",
				tpin, am0, am1, cx, cX, am6, am7, field[0][0], DSET, 
				fmtc1, fmtc2, fmtc3, fmtc4, dupwarn, '0', '1', '2', '3', '6', '7');
		strcat(cyclebuff, SCATcycle);
		cellinfo[cellcnt].formats[0] = fmtc1;
		cellinfo[cellcnt].formats[1] = fmtc2;
		cellinfo[cellcnt].formats[2] = fmtc3;
		cellinfo[cellcnt].formats[3] = fmtc4;
		cellinfo[cellcnt].problemtype = PT_CLOSE;
		strcat(cyclebuff, "   Drive {\n      Waveform {");
		sprintf(SCATcycle, "DriveOff @\"%s%s+%s*%s\";}\n   }\n", field[0][1], org[1], field[0][2], tperiod);
		strcat(cellinfo[cellcnt].cellexpr, SCATcycle);
		strcat(cyclebuff, SCATcycle);
		strcat(cyclebuff, "}\n");
		cellcnt++;
		if (cellcnt > MAXCELLS) {
			fprintf(stderr, "Too many Cells for buffer, source[%s,%d,%s]\n", __FILE__, __LINE__, __FUNCTION__);
			fprintf(fperrors, "Too many Cells for buffer, source[%s,%d,%s]\n", __FILE__, __LINE__, __FUNCTION__);
			exit(1);
		}
	}
	else if (0 == strcmp(type, "WaveSetDelayRTO")) {
		fmtc1 = FC_DRIVEDATA;
		fmtc2 = FC_DRIVEHI;
		fmtc3 = fmtc4 = FC_NULLEDGE;
		*modcode = FC_DRIVEDATA;
		if (DSET == 0) {
			am0 = AM_driveLOD0;
			am1 = AM_driveHID0;
		}
		if (DSET == 1) {
			am0 = AM_driveLOD1;
			am1 = AM_driveHID1;
		}
		cellinfo[cellcnt].formats[0] = fmtc1;
		cellinfo[cellcnt].formats[1] = fmtc2;
		cellinfo[cellcnt].formats[2] = fmtc3;
		cellinfo[cellcnt].formats[3] = fmtc4;
		cellinfo[cellcnt].problemtype = PT_NOPROBLEM;
		cellinfo[cellcnt].alias0 = am0;
		cellinfo[cellcnt].alias1 = am1;
		sprintf(SCATcycle, "Cell \"%s\" %c/%c %s_DSET%01d%c%c%c%c_cat_%s {\n   Data %c/%c;\n",
				tpin, am0, am1, field[0][0], DSET, fmtc1, fmtc2, fmtc3, fmtc4, dupwarn, '6', '7');
		strcat(cyclebuff, SCATcycle);
		strcat(cyclebuff, "   Drive {\n      Waveform {");
		sprintf(SCATcycle, "DriveData @\"%s%s+%s*%s\";DriveHigh @\"%s%s+%s*%s\";}\n   }\n",
				field[0][1], org[1], field[0][3], tperiod, field[0][2], org[2], field[0][4], tperiod);
		strcat(cellinfo[cellcnt].cellexpr, SCATcycle);
		strcat(cyclebuff, SCATcycle);
		strcat(cyclebuff, "}\n");
		cellcnt++;
		if (cellcnt > MAXCELLS) {
			fprintf(stderr, "Too many Cells for buffer, source[%s,%d,%s]\n", __FILE__, __LINE__, __FUNCTION__);
			fprintf(fperrors, "Too many Cells for buffer, source[%s,%d,%s]\n", __FILE__, __LINE__, __FUNCTION__);
			exit(1);
		}
	}
	else if (0 == strcmp(type, "WaveSetDelayRTZ")) {
		fmtc1 = FC_DRIVEDATA;
		fmtc2 = FC_DRIVELO;
		fmtc3 = fmtc4 = FC_NULLEDGE;
		*modcode = FC_DRIVEDATA;
		if (DSET == 0) {
			am0 = AM_driveLOD0;
			am1 = AM_driveHID0;
		}
		if (DSET == 1) {
			am0 = AM_driveLOD1;
			am1 = AM_driveHID1;
		}
		cellinfo[cellcnt].formats[0] = fmtc1;
		cellinfo[cellcnt].formats[1] = fmtc2;
		cellinfo[cellcnt].formats[2] = fmtc3;
		cellinfo[cellcnt].formats[3] = fmtc4;
		cellinfo[cellcnt].problemtype = PT_NOPROBLEM;
		cellinfo[cellcnt].alias0 = am0;
		cellinfo[cellcnt].alias1 = am1;
		sprintf(SCATcycle, "Cell \"%s\" %c/%c %s_DSET%01d%c%c%c%c_cat_%s {\n   Data %c/%c;\n",
				tpin, am0, am1, field[0][0], DSET, fmtc1, fmtc2, fmtc3, fmtc4, dupwarn, '6', '7');
		strcat(cyclebuff, SCATcycle);
		strcat(cyclebuff, "   Drive {\n      Waveform {");
		sprintf(SCATcycle, "DriveData @\"%s%s+%s*%s\";DriveLow @\"%s%s+%s*%s\";}\n   }\n",
				field[0][1], org[1], field[0][3], tperiod, field[0][2], org[2], field[0][4], tperiod);
		strcat(cellinfo[cellcnt].cellexpr, SCATcycle);
		strcat(cyclebuff, SCATcycle);
		strcat(cyclebuff, "}\n");
		cellcnt++;
		if (cellcnt > MAXCELLS) {
			fprintf(stderr, "Too many Cells for buffer, source[%s,%d,%s]\n", __FILE__, __LINE__, __FUNCTION__);
			fprintf(fperrors, "Too many Cells for buffer, source[%s,%d,%s]\n", __FILE__, __LINE__, __FUNCTION__);
			exit(1);
		}
	}
	else if (0 == strcmp(type, "WaveSetDelaySBC")) {
		fmtc1 = FC_DRIVECOMP;
		fmtc2 = FC_DRIVEDATA;
		fmtc3 = FC_DRIVECOMP;
		fmtc4 = FC_NULLEDGE;
		*modcode = FC_DRIVEDATA;
		if (DSET == 0) {
			am0 = AM_driveLOD0;
			am1 = AM_driveHID0;
		}
		if (DSET == 1) {
			am0 = AM_driveLOD1;
			am1 = AM_driveHID1;
		}
		cellinfo[cellcnt].formats[0] = fmtc1;
		cellinfo[cellcnt].formats[1] = fmtc2;
		cellinfo[cellcnt].formats[2] = fmtc3;
		cellinfo[cellcnt].formats[3] = fmtc4;
		cellinfo[cellcnt].problemtype = PT_NOPROBLEM;
		cellinfo[cellcnt].alias0 = am0;
		cellinfo[cellcnt].alias1 = am1;
		sprintf(SCATcycle, "Cell \"%s\" %c/%c %s_DSET%01d%c%c%c%c_cat_%s {\n   Data %c/%c;\n",
				tpin, am0, am1, field[0][0], DSET, fmtc1, fmtc2, fmtc3, fmtc4, dupwarn, '6', '7');
		strcat(cyclebuff, SCATcycle);
		strcat(cyclebuff, "   Drive {\n      Waveform {");
		sprintf(SCATcycle, "DriveDataNot @\"%s%s+%s*%s\";DriveData @\"%s%s+%s*%s\";DriveDataNot @\"%s%s+%s*%s\";}\n   }\n",
				field[0][1], org[1], field[0][4], tperiod, field[0][2], org[2], 
				field[0][5], tperiod, field[0][3], org[3], field[0][6], tperiod);
		strcat(cellinfo[cellcnt].cellexpr, SCATcycle);
		strcat(cyclebuff, SCATcycle);
		strcat(cyclebuff, "}\n");
		cellcnt++;
		if (cellcnt > MAXCELLS) {
			fprintf(stderr, "Too many Cells for buffer, source[%s,%d,%s]\n", __FILE__, __LINE__, __FUNCTION__);
			fprintf(fperrors, "Too many Cells for buffer, source[%s,%d,%s]\n", __FILE__, __LINE__, __FUNCTION__);
			exit(1);
		}
	}
	else if (0 == strcmp(type, "WaveSetDelayStrobe")) {
		fmtc1 = FC_DRIVEOFF;
		fmtc2 = FC_WINDOWDATA;
		fmtc3 = FC_STROBEOFF;
		fmtc4 = FC_NULLEDGE;
		*modcode = FC_WINDOWDATA;
		if (DSET == 0) {
			am0 = AM_windowLOD0;
			am1 = AM_windowHID0;
		}
		if (DSET == 1) {
			am0 = AM_windowLOD1;
			am1 = AM_windowHID1;
		}
		cellinfo[cellcnt].formats[0] = fmtc1;
		cellinfo[cellcnt].formats[1] = fmtc2;
		cellinfo[cellcnt].formats[2] = fmtc3;
		cellinfo[cellcnt].formats[3] = fmtc4;
		cellinfo[cellcnt].problemtype = PT_NOPROBLEM;
		cellinfo[cellcnt].alias0 = am0;
		cellinfo[cellcnt].alias1 = am1;
		cx = (DSET == 0) ? AM_maskD0 : AM_maskD1;
		cX = (DSET == 0) ? AM_maskHID0 : AM_maskHID1;
		sprintf(SCATcycle, "Cell \"%s\" %c/%c/%c/%c %s_DSET%01d%c%c%c%c_cat_%s {\n   Data %c/%c/%c/%c;\n",
				tpin, am0, am1, cx, cX, field[0][0], DSET, fmtc1, fmtc2, fmtc3, fmtc4, dupwarn, '0', '1', '2', '3');
		strcat(cyclebuff, SCATcycle);
		strcat(cyclebuff, "   Drive {\n      Waveform {");
		sprintf(SCATcycle, "DriveOff @\"%s%s+%s*%s\";}\n   }\n", field[0][1], org[1], field[0][4], tperiod);
		strcat(cellinfo[cellcnt].cellexpr, SCATcycle);
		strcat(cyclebuff, SCATcycle);
		strcat(cyclebuff, "   Compare {\n      Waveform {\n");
		sprintf(SCATcycle, "         CompareOpenData @\"%s%s+%s*%s\";\n         CompareClose @\"%s%s+%s*%s\";}\n   }\n",
				field[0][2], org[2], field[0][5], tperiod, field[0][3], org[3], field[0][6], tperiod);
		strcat(cellinfo[cellcnt].cellexpr, SCATcycle);
		strcat(cyclebuff, SCATcycle);
		strcat(cyclebuff, "}\n");
		cellcnt++;
		if (cellcnt > MAXCELLS) {
			fprintf(stderr, "Too many Cells for buffer, source[%s,%d,%s]\n", __FILE__, __LINE__, __FUNCTION__);
			fprintf(fperrors, "Too many Cells for buffer, source[%s,%d,%s]\n", __FILE__, __LINE__, __FUNCTION__);
			exit(1);
		}
	}
	else if (0 == strcmp(type, "WaveSetDelayEdgeStrobe")) {
		fmtc1 = FC_DRIVEOFF;
		fmtc2 = FC_EDGEDATA;
		fmtc3 = FC_LATCH;
		fmtc4 = FC_NULLEDGE;
		*modcode = FC_EDGEDATA;
		if (DSET == 0) {
			am0 = AM_edgestbLOD0;
			am1 = AM_edgestbHID0;
		}
		if (DSET == 1) {
			am0 = AM_edgestbLOD1;
			am1 = AM_edgestbHID1;
		}
		cellinfo[cellcnt].formats[0] = fmtc1;
		cellinfo[cellcnt].formats[1] = fmtc2;
		cellinfo[cellcnt].formats[2] = fmtc3;
		cellinfo[cellcnt].formats[3] = fmtc4;
		cellinfo[cellcnt].problemtype = PT_NOPROBLEM;
		cellinfo[cellcnt].alias0 = am0;
		cellinfo[cellcnt].alias1 = am1;
		cx = (DSET == 0) ? AM_maskD0 : AM_maskD1;
		cX = (DSET == 0) ? AM_maskHID0 : AM_maskHID1;
		sprintf(SCATcycle, "Cell \"%s\" %c/%c/%c/%c %s_DSET%01d%c%c%c%c_cat_%s {\n   Data %c/%c/%c/%c;\n",
				tpin, am0, am1, cx, cX, field[0][0], DSET, fmtc1, fmtc2, fmtc3, fmtc4, dupwarn, '0', '1', '2', '3');
		strcat(cyclebuff, SCATcycle);
		strcat(cyclebuff, "   Drive {\n      Waveform {");
		sprintf(SCATcycle, "DriveOff @\"%s%s+%s*%s\";}\n   }\n", field[0][1], org[1], field[0][3], tperiod);
		strcat(cellinfo[cellcnt].cellexpr, SCATcycle);
		strcat(cyclebuff, SCATcycle);
		strcat(cyclebuff, "   Compare {\n      Waveform {");
		sprintf(SCATcycle, " CompareData @\"%s%s+%s*%s\";}\n   }\n", field[0][2], org[2], field[0][4], tperiod);
		strcat(cellinfo[cellcnt].cellexpr, SCATcycle);
		strcat(cyclebuff, SCATcycle);
		strcat(cyclebuff, "}\n");
		cellcnt++;
		if (cellcnt > MAXCELLS) {
			fprintf(stderr, "Too many Cells for buffer, source[%s,%d,%s]\n", __FILE__, __LINE__, __FUNCTION__);
			fprintf(fperrors, "Too many Cells for buffer, source[%s,%d,%s]\n", __FILE__, __LINE__, __FUNCTION__);
			exit(1);
		}
	}
	else if (0 == strcmp(type, "WaveSetDelayStrobeZ")) {
		fmtc1 = FC_DRIVEOFF;
		fmtc2 = FC_WINDOWFLOAT;
		fmtc3 = FC_STROBEOFF;
		fmtc4 = FC_NULLEDGE;
		*modcode = FC_WINDOWFLOAT;
		if (DSET == 0) {
			am0 = AM_windowfloatD0;
			am1 = AM_windowfloatD0;
		}
		if (DSET == 1) {
			am0 = AM_windowfloatD1;
			am1 = AM_windowfloatD1;
		}
		cellinfo[cellcnt].formats[0] = fmtc1;
		cellinfo[cellcnt].formats[1] = fmtc2;
		cellinfo[cellcnt].formats[2] = fmtc3;
		cellinfo[cellcnt].formats[3] = fmtc4;
		cellinfo[cellcnt].problemtype = PT_NOPROBLEM;
		cellinfo[cellcnt].alias0 = am0;
		cellinfo[cellcnt].alias1 = am1;
		cx = (DSET == 0) ? AM_maskD0 : AM_maskD1;
		cX = (DSET == 0) ? AM_maskHID0 : AM_maskHID1;
		sprintf(SCATcycle, "Cell \"%s\" %c/%c %s_DSET%01d%c%c%c%c_cat_%s {\n   Data %c/%c;\n",
				tpin, am0, cx, field[0][0], DSET, fmtc1, fmtc2, fmtc3, fmtc4, dupwarn, '0', '2');
		strcat(cyclebuff, SCATcycle);
		strcat(cyclebuff, "   Drive {\n      Waveform {");
		sprintf(SCATcycle, "DriveOff @\"%s%s+%s*%s\";}\n   }\n", field[0][1], org[1], field[0][4], tperiod);
		strcat(cellinfo[cellcnt].cellexpr, SCATcycle);
		strcat(cyclebuff, SCATcycle);
		strcat(cyclebuff, "   Compare {\n      Waveform {");
		sprintf(SCATcycle, " CompareOpenFloat @\"%s%s+%s*%s\";\n         CompareClose @\"%s%s+%s*%s\";}\n   }\n",
				field[0][2], org[2], field[0][5], tperiod, field[0][3], org[3], field[0][6], tperiod);
		strcat(cellinfo[cellcnt].cellexpr, SCATcycle);
		strcat(cyclebuff, SCATcycle);
		strcat(cyclebuff, "}\n");
		cellcnt++;
		if (cellcnt > MAXCELLS) {
			fprintf(stderr, "Too many Cells for buffer, source[%s,%d,%s]\n", __FILE__, __LINE__, __FUNCTION__);
			fprintf(fperrors, "Too many Cells for buffer, source[%s,%d,%s]\n", __FILE__, __LINE__, __FUNCTION__);
			exit(1);
		}
	}
	else if (0 == strcmp(type, "WaveSetDelayEdgeStrobeZ")) {
		fmtc1 = FC_DRIVEOFF;
		fmtc2 = FC_EDGEFLOAT;
		fmtc3 = FC_LATCH;
		fmtc4 = FC_NULLEDGE;
		*modcode = FC_EDGEFLOAT;
		if (DSET == 0) {
			am0 = AM_edgefloatD0;
			am1 = AM_edgefloatD0;
		}
		if (DSET == 1) {
			am0 = AM_edgefloatD1;
			am1 = AM_edgefloatD1;
		}
		cellinfo[cellcnt].formats[0] = fmtc1;
		cellinfo[cellcnt].formats[1] = fmtc2;
		cellinfo[cellcnt].formats[2] = fmtc3;
		cellinfo[cellcnt].formats[3] = fmtc4;
		cellinfo[cellcnt].problemtype = PT_NOPROBLEM;
		cellinfo[cellcnt].alias0 = am0;
		cellinfo[cellcnt].alias1 = am1;
		cx = (DSET == 0) ? AM_maskD0 : AM_maskD1;
		cX = (DSET == 0) ? AM_maskHID0 : AM_maskHID1;
		sprintf(SCATcycle, "Cell \"%s\" %c/%c %s_DSET%01d%c%c%c%c_cat_%s {\n   Data %c/%c;\n",
				tpin, am0, cx, field[0][0], DSET, fmtc1, fmtc2, fmtc3, fmtc4, dupwarn, '0', '2');
		strcat(cyclebuff, SCATcycle);
		strcat(cyclebuff, "   Drive {\n      Waveform {");
		sprintf(SCATcycle, "DriveOff @\"%s%s+%s*%s\";}\n   }\n", field[0][1], org[1], field[0][3], tperiod);
		strcat(cellinfo[cellcnt].cellexpr, SCATcycle);
		strcat(cyclebuff, SCATcycle);
		sprintf(SCATcycle, "   Compare {\n      Waveform { CompareFloat @\"%s%s+%s*%s\";}\n   }\n", 
			field[0][2], org[2], field[0][4], tperiod);
		strcat(cellinfo[cellcnt].cellexpr, SCATcycle);
		strcat(cyclebuff, SCATcycle);
		strcat(cyclebuff, "}\n");
		cellcnt++;
		if (cellcnt > MAXCELLS) {
			fprintf(stderr, "Too many Cells for buffer, source[%s,%d,%s]\n", __FILE__, __LINE__, __FUNCTION__);
			fprintf(fperrors, "Too many Cells for buffer, source[%s,%d,%s]\n", __FILE__, __LINE__, __FUNCTION__);
			exit(1);
		}
	}
	else if (0 == strcmp(type, "EdgeSetDelayData") || 0 == strcmp(type, "EdgeSetDelay") || 0 == strcmp(type, "EdgeSet")) {	/* these actually all fall into the last row, but its separate for clarity */
		process_edgesetdelay_waveform(actablelines, GCTNAME, cyclebuff, tell, 
			which, forward, pin, DSET, CNT, modcode, name, en, enable_edge);
	}
	if (MUXFLAG && NOMUX == 0 && strstr(type, "WaveSet") != NULL && strstr(type, "WaveSetContinue") == NULL) {
		/* NOTE: THIS IS SPECIFIC TO MUX PINS ONLY!!!!, so alias should carry over */
		/* FIXME:APS We should probably do something if it is a muxed compare though */
		/* we don't need to duplicate it if it is a continue */
		/* all wavesets will assume normal edges from only channel '0' */
		/* this means the muxpin should produce null edges */
		fmtc1 = FC_NULLEDGE;
		fmtc2 = FC_NULLEDGE;
		fmtc3 = FC_NULLEDGE;
		fmtc4 = FC_NULLEDGE;
		cellinfo[cellcnt].formats[0] = fmtc1;
		cellinfo[cellcnt].formats[1] = fmtc2;
		cellinfo[cellcnt].formats[2] = fmtc3;
		cellinfo[cellcnt].formats[3] = fmtc4;
		cellinfo[cellcnt].problemtype = PT_NOPROBLEM;
		cx = (DSET == 0) ? AM_driveoffLOD0 : AM_driveoffLOD1;
		cX = (DSET == 0) ? AM_driveoffHID0 : AM_driveoffHID1;
		if (am0 == AM_strobeoffLOD0 || am0 == AM_strobeoffLOD1) am0 = cx;
		if (am1 == AM_strobeoffHID0 || am1 == AM_strobeoffHID1) am1 = cX;

		cellinfo[cellcnt].alias0 = am0;
		cellinfo[cellcnt].alias1 = am1;
		cellinfo[cellcnt].actline = which;
		strcpy(cellinfo[cellcnt].wftname, GCTNAME);
		strcpy(cellinfo[cellcnt].cellname, field[0][0]);
		sprintf(cellinfo[cellcnt].pin, "%s-MUXPRIMARYPINS", pin);
		cellinfo[cellcnt].multidefnum = CNT;
		cellinfo[cellcnt].formatnum = wtlookup;
		cellinfo[cellcnt].cellexpr[0] = '\0';
		sprintf(SCATcycle, "Cell \"%s-MUXPRIMARYPINS\" %c/%c %s_DSETMUX%01d%c%c%c%c_cat_%s {\n   Data %c/%c;\n",
				pin, am0, am1, field[0][0], DSET, fmtc1, fmtc2, fmtc3, fmtc4, dupwarn, '6', '7');
		strcat(cyclebuff, SCATcycle);
		strcat(cyclebuff, "   Drive {\n      EntryState DriveOn;}\n");
		strcat(cyclebuff, "}\n");
		cellcnt++;
		if (cellcnt > MAXCELLS) {
			fprintf(stderr, "Too many Cells for buffer, source[%s,%d,%s]\n", __FILE__, __LINE__, __FUNCTION__);
			fprintf(fperrors, "Too many Cells for buffer, source[%s,%d,%s]\n", __FILE__, __LINE__, __FUNCTION__);
			exit(1);
		}
	}

	if (NULL != pelse) {
		strcat(cyclebuff, "//Warning 'else' in waveform definition!!! FIXME!!!\n");
		fprintf(stderr, "//Warning 'else' in waveform definition!!! FIXME!!!, source[%s,%d,%s]\n", __FILE__, __LINE__, __FUNCTION__);
		strcpy(copybuf, pelse + 5 + eb * 5);	/* +5=>")else"); +5+eb*5 => ")elsebegin  */
		strcpy(name[0], copybuf);	/* replace the line with second part of the line and re-call the function */
		process_waveforms(actablelines, GCTNAME, cyclebuff, tell, which, forward, pin, DSET, CNT + 100, modcode);	/* self referencing call!!!! */
		/* FIXME: APS should copy the first part and 
		   add the second to the end of the list
		   before calling again now pointing at the end */
	}
	return (0);
}
