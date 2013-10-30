/* ggm_process_edgesetdelay.c */
/* process_edgesetdelay_waveform(){} */

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

int process_edgesetdelay_waveform(int actablelines, char *GCTNAME, char *cyclebuff, long *tell, 
				  int which, int *forward, char *pin, int DSET, int CNT, int *modcode, 
				  char name[][FINDME_SIZE + 1], int en[], int enable_edge[]) {
  int CHANSECOND[MAX_EDGES + 1];
  int edgecnt, splitcell = 0, found;
  int i, j, ne, neST = 0, wtlookup;
  int holdlen, ret, delay[MAX_EDGES + 1], formatpick[MAX_EDGES + 1],
    nDELAYDATA[MAX_EDGES + 1];
  int D0L=999, D0H=999, D1L=999, D1H=999, DbL=999, DbH=999, cxL=999, cxH=999, A0=999, A1=999, Z0=999, Z1=999;
  int lcode0[MAX_EDGES + 1], lcode1[MAX_EDGES + 1];
  int cellisdrv, cellisNOTstrb, eloc, laststart;
  char findme[FINDME_SIZE + 1], ALIASSTR[MAX_EDGES + 1], tpin[PINSIZE];
  char org[MAX_EDGES + 1][WF_EXPR_LEN];
  char field[MAX_EDGES + 1][100][WF_EXPR_LEN], dupwarn[WF_EXPR_LEN];
  static int WINLEFTPEND = 0;
  int startStopInd;
  /* FIXME: APS since pinlist is last we can ignore it... for now */
  /* EdgeSet         (wave,edge,edgetype,time) */
  /* EdgeSetDelay    (wave,edge,edgetype,time,delay) */
  /* EdgeSetDelayData(wave,edge,chan,edgetype0,vth0,time0,delay0,edgetype1,vth1,time1,delay1) */
  /* EdgeSetPinList(wave,edge,edgetype,time,pinlist) */
  /* EdgeSetDelayPinList(wave,edge,edgetype,time,delay,pinlist) */
  /* EdgeSetDelayDataPinList(wave,edge,chan,edgetype0,vth0,time0,delay0,edgetype1,vth1,time1,delay1,pinlist) */
  for (i=0; i < MAX_EDGES+1; i++)
    for (j=0; j<100; j++)
      field[i][j][0]  = '\0';
	
  strcpy(findme, acwaves[which + 0].w);
  eloc = acwaves[which + 0].loc;
  laststart = acwaves[which + 0].laststart;

  if (MUXFLAG && NOMUX == 0) sprintf(tpin, "%s-MUXSECONDARYPINS", pin);
  else strcpy(tpin, pin);

  /*   This is now done in process_waveforms() */
  //   for (i=0;i<=MAX_EDGES;i++) { en[i]=enable_edge[i]=0; name[i][0]='\0'; }

  ne = break_up_edges(actablelines, en, enable_edge, name, findme, which, forward);

  for (splitcell = i = 0; i <= ne; i++) {
    if (strstr(name[i], "EdgeSetDelayData") != NULL) {
      formatpick[i] = 3;
      nDELAYDATA[i] = 0;
      splitcell = 1;
    }
    else {					/* This is for EdgeSet() with No delay, or just EdgeSetDelay() */
      formatpick[i] = 2;
      nDELAYDATA[i] = 1;
    }
    delay[i] = 0;
    if (strstr(name[i], "Delay") != NULL) delay[i] = 1;
    if (strstr(name[i], "DelayData") != NULL) delay[i] = 2;
    ALIASSTR[i] = 'n';
    for (j = 0; j < MF_EDGESETDATA; j++) field[en[i]][j][0] = '\0';
    lcode1[i] = lcode0[i] = FC_NULLEDGE;
  }
  ALIASSTR[i] = '\0';

  *modcode = FC_NULLEDGE;

  if (CNT != 0) sprintf(dupwarn, "_MULTIPLE_DEF%03d", CNT);
  else dupwarn[0] = '\0';

  reduce_expressions(ne, en, name, field);
  neST = 0;
  if (ne >= 4) {				/* we can only deal with four */
    if (strstr(field[en[0]][formatpick[0]], "DriveOff") != NULL) {
      /* move everything forward. FIXME: APS Not sure if this is valid in all cases. */
      fprintf(fpstatus,"AdvisoryC0[%04d]:Warning we have more than four edges on wfm[%s]\n", WARNING, field[en[0]][0]);
      fprintf(fpstatus,"AdvisoryC1[%04d]:Since the first is a DriveOff we'll ignore it and move everything forward.\n", WARNING);
      fprintf(fpstatus,"AdvisoryC2[%04d]:This assumption needs to be validated!\n", WARNING);
      fprintf(fpstatus, "AdvisoryC3[%04d]:Sourced from %s,%d,%s\n",
	      WARNING, __FILE__, __LINE__, __FUNCTION__);
      WARNING++;
      neST = 1;
    }
    else {
      fprintf(fpstatus,"AdvisoryD0[%04d]:Can't represent a 5+ edge waveform [%s]\n", WARNING, field[en[0]][0]);
      fprintf(fpstatus,"AdvisoryD1[%04d]:You'll need to look at this one...\n", WARNING);
      fprintf(fpstatus, "AdvisoryD2[%04d]:Sourced from %s,%d,%s\n",
	      WARNING, __FILE__, __LINE__, __FUNCTION__);
    }
  }

  for (i = neST; i <= ne; i++) {
    if (nDELAYDATA[i] == 1) sprintf(SCATcycle, "//ES[%d]:%s\n", ne, name[en[i]]);
    else if (nDELAYDATA[i] == 0) sprintf(SCATcycle, "//ESD[%d]:%s\n", ne, name[en[i]]);
    strcat(cyclebuff, SCATcycle);
    if (NULL != strstr(field[i][2], "ChanSecond")) CHANSECOND[i] = 1;
    else CHANSECOND[i] = 0;
  }

  /* need to search origin array also!!!!! */
  for (i = 0; i <= MAX_EDGES; i++) org[i][0] = '\0';
  for (i = neST; i <= ne; i++) {
    ret = find_origin(&field[en[i]][0][0], org, laststart, __FILE__);
    if (ret == -1) {
      fprintf(stderr,"element=%d,GCT=%s,Cellname=%s,cellname[elem]=%s,PIN=[%s],  from source[%s,%d,%s]\n",
	      en[i], GCTNAME, field[0][0], field[en[i]][0], pin,
	      __FILE__, __LINE__, __FUNCTION__);
      exit(1);
    }
  }

  D0L = AM_driveoffLOD0;
  D0H = AM_driveoffHID0;		/* Default */
  D1L = AM_driveoffLOD1;
  D1H = AM_driveoffHID1;		/* this is DriveOff DSET0 should be z/Z */
  lcode0[0] = lcode0[1] = lcode0[2] = lcode0[3] = lcode0[4] = FC_DUMMY;
  lcode1[0] = lcode1[1] = lcode1[2] = lcode1[3] = lcode1[4] = FC_DUMMY;

  /* Process the "Offs" first so drives and strobes later can change the settings. */

  for (i = neST; i <= ne; i++) {	/* was: (i=ne-1;i>=0;i--) */

    if (0 == strcmp(field[en[i]][formatpick[i]], "DriveOff")) {
      D0L = AM_driveoffLOD0;
      D0H = AM_driveoffHID0;
      DbL = D1L = AM_driveoffLOD1;
      DbH = D1H = AM_driveoffHID1;
      if (*modcode == FC_NULLEDGE) *modcode = FC_DRIVEOFF;
      if (DSET == 0) lcode0[i] = FC_DRIVEOFF;
      if (DSET == 1) lcode1[i] = FC_DRIVEOFF;
    }
    else if (0 == strcmp(field[en[i]][formatpick[i]], "StrobeOff")) {
      D0L = AM_strobeoffLOD0;
      D0H = AM_strobeoffHID0;
      DbL = D1L = AM_strobeoffLOD1;
      DbH = D1H = AM_strobeoffHID1;
      if (*modcode == FC_NULLEDGE) *modcode = FC_STROBEOFF;
      if (DSET == 0) lcode0[i] = FC_STROBEOFF;
      if (DSET == 1) lcode1[i] = FC_STROBEOFF;
    }
  }

  cellisNOTstrb = 1;
  cellisdrv = 0;
  nDELAYDATA[0] = nDELAYDATA[1] = nDELAYDATA[2] = nDELAYDATA[3] = nDELAYDATA[4] = 0;

  for (i = neST; i <= ne; i++) {	/* was: (i=ne-1;i>=0;i--) */
    /* assume that first edges dominate!!! same drives dominate to DSET1 */

    if (strstr(name[i], "EdgeSetDelayData") != NULL) {
      formatpick[i] = 3;
      nDELAYDATA[i] = 0;
    }
    else {
      formatpick[i] = 2;
      nDELAYDATA[i] = 1;
    }						/* this is for EdgeSet with No delay, or just EdgeSetDelay()  */

    if (0 == strcmp(field[en[i]][formatpick[i]], "DriveHigh") ||
	0 == strcmp(field[en[i]][formatpick[i]], "DriveLow") ||
	0 == strcmp(field[en[i]][formatpick[i]], "DriveData") ||
	0 == strcmp(field[en[i]][formatpick[i]], "DriveComplement")) {
      D0L = AM_driveLOD0;
      D0H = AM_driveHID0;
      DbL = D1L = AM_driveLOD1;
      DbH = D1H = AM_driveHID1;
      *modcode = FC_DRIVEDATA;
      if (DSET == 0) lcode0[i] = FC_DRIVEDATA;	/* these will overwrite offs */
      if (DSET == 1) lcode1[i] = FC_DRIVEDATA;
      cellisdrv = 1;
    }
    else if (0 == strcmp(field[en[i]][formatpick[i]], "NullEdge")) {
      DbL = D0L = D1L = AM_continueLO;
      DbH = D0H = D1H = AM_continue;
      if (*modcode == FC_NULLEDGE) *modcode = FC_NULLEDGE;
      lcode0[i] = lcode1[i] = FC_NULLEDGE;
    }
    //       else if (0==strcmp(field[en[i]][formatpick[i]],"StrobeLatch")) {
    //          DbL=D0L=DbH=D0H=D1L=D1H=AM_continue;
    //          if (*modcode==FC_NULLEDGE)  *modcode=FC_NULLEDGE;
    //          lcode0[i]=lcode1[i]=FC_NULLEDGE;
    //          }
    else if (0 == strcmp(field[en[i]][formatpick[i]], "EdgeStrobeLow")
	     || 0 == strcmp(field[en[i]][formatpick[i]], "EdgeStrobeHigh")
	     || 0 == strcmp(field[en[i]][formatpick[i]], "EdgeStrobeData")
	     || 0 == strcmp(field[en[i]][formatpick[i]], "EdgeStrobeComplement")) {
      DbL = D0L = AM_edgestbLOD0;
      DbH = D0H = AM_edgestbHID0;
      D1L = AM_edgestbLOD1;
      D1H = AM_edgestbHID1;
      *modcode = FC_EDGEDATA;
      if (DSET == 0) lcode0[i] = FC_EDGEDATA;	/* these will overwrite offs */
      if (DSET == 1) lcode1[i] = FC_EDGEDATA;
      cellisNOTstrb = 0;
    }
    else if (0 == strcmp(field[en[i]][formatpick[i]], "EdgeStrobeZ")) {	/* but this should have one value..., but we'll give it two */
      D0L = AM_edgefloatD0;
      D0H = AM_edgefloatD0;
      D1L = AM_edgefloatD1;
      D1H = AM_edgefloatD1;
      *modcode = lcode0[i] = FC_EDGEFLOAT;
      if (DSET == 0) lcode0[i] = FC_EDGEFLOAT;	/* these will overwrite offs */
      if (DSET == 1) lcode1[i] = FC_EDGEFLOAT;
      cellisNOTstrb = 0;
    }
    else if (0 == strcmp(field[en[i]][formatpick[i]], "StrobeLow") ||
	     0 == strcmp(field[en[i]][formatpick[i]], "StrobeHigh") ||
	     0 == strcmp(field[en[i]][formatpick[i]], "StrobeData") ||
	     0 == strcmp(field[en[i]][formatpick[i]], "StrobeComplement")) {
      DbL = D0L = AM_windowLOD0;
      DbH = D0H = AM_windowHID0;
      D1L = AM_windowLOD1;
      D1H = AM_windowHID1;
      *modcode = FC_WINDOWOPEN; /* initially leave this pending for close by strobeoffs */
      if (DSET == 0) lcode0[i] = FC_WINDOWDATA;
      if (DSET == 1) lcode1[i] = FC_WINDOWDATA;
      cellisNOTstrb = 0;
    }
    else if (0 == strcmp(field[en[i]][formatpick[i]], "StrobeZ")) {	/* but this should have one value..., but we'll give it two */
      DbL = D0L = AM_windowfloatD0;
      DbH = D0H = AM_windowfloatD0;
      D1L = AM_windowfloatD1;
      D1H = AM_windowfloatD1;
      *modcode = FC_WINDOWOPENZ; /* initially leave this pending for close by strobeoffs */
      if (DSET == 0) {
	lcode0[i] = FC_WINDOWFLOAT;
      }
      if (DSET == 1) {
	lcode1[i] = FC_WINDOWFLOAT;
      }
      cellisNOTstrb = 0;
    }
    else if ((0 == strcmp(field[en[i]][formatpick[i]], "StrobeOffLow")
	      || 0 == strcmp(field[en[i]][formatpick[i]], "StrobeOffHigh")
	      || 0 == strcmp(field[en[i]][formatpick[i]], "StrobeOffData")
	      || 0 == strcmp(field[en[i]][formatpick[i]], "StrobeOffComplement")
	      || 0 == strcmp(field[en[i]][formatpick[i]], "StrobeOff"))) {
      if (DSET == 0) lcode0[i] = FC_STROBEOFF;
      if (DSET == 1) lcode1[i] = FC_STROBEOFF;
      if (*modcode == FC_WINDOWOPEN) *modcode = FC_WINDOWDATA; /* close the window! */
      else if (*modcode == FC_WINDOWOPENZ) *modcode = FC_WINDOWFLOAT; /* close the window! */
      if (DbL != AM_windowLOD0 && DbL != AM_windowfloatD0) {	/* if its already a window strobe then don't erase it ! */
	DbL = D0L = AM_strobeoffLOD0;
	DbH = D0H = AM_strobeoffHID0;
	D1L = AM_strobeoffLOD1;
	D1H = AM_strobeoffHID1;
	if (*modcode == FC_NULLEDGE) *modcode = FC_STROBEOFF;
	//				else {
	//					fprintf(stdout,"FC_STROBEOFF=%c SET to STROBEOFF\n",*modcode);
	//					*modcode = FC_STROBEOFF;
	//					}
      }					/* this is for strobeoff as compare which could be masked */
      cellisNOTstrb = 0;
      //cellisNOTstrb=1;/* assume if its !ONLY! strobe off then it has been preset before entering */
    }
  }							/* drives dominate to DSET1 if same, strobes and offs to DSET0 */

  wtlookup = -2;
  holdlen = *tell + strlen(cyclebuff);

  /* WAS: (APS 0/4/27/2009) */
  //   for (i=0;i<maxstartstop;i++) { /* if we don't find it then it gets left at the multidef from above */
  //      if (startstop[i].type==SSSTART && startstop[i].loc<acwaves[which+0].loc) {
  //         dupwarn[0]=startstop[i].cdtcode;
  //         dupwarn[1]='\0';
  //         }
  //      }
  /* NEW:  this exists in process_edgesets too! */
  found = 0;
  /* find which start/stop pair it lies between */
  for (i = 0; i < maxstartstop; i++) {	/* if we don't find it then it gets left at the multidef from above */
    if (startstop[i].type == SSSTART
	&& startstop[i].loc <= acwaves[which + 0].loc
	&& startstop[startstop[i].startpt2stop].loc >= acwaves[which + 0].loc) {
      dupwarn[0] = cellinfo[cellcnt].cdtcode = startstop[i].cdtcode;
      cellinfo[cellcnt].cdtstr[0] = startstop[i].cdtcode;
      startStopInd = i;
      //         fprintf(stdout,"FOUND[%s,%s,%c,%d], source[%s,%d,%s]\n",GCTNAME,field[0][0],
      //             cellinfo[cellcnt].cdtstr[0],acwaves[which+0].loc,__FILE__,__LINE__,__FUNCTION__);
      cellinfo[cellcnt].cdtstr[1] = '\0';
      dupwarn[1] = '\0';
      found++;
    }
  }
  if (found == 0) {
    fprintf(stderr, "NOT FOUND![%s,%s,%c,%d], source[%s,%d,%s]\n",
	    GCTNAME, field[0][0], cellinfo[cellcnt].cdtstr[0],
	    acwaves[which + 0].loc, __FILE__, __LINE__, __FUNCTION__);
    exit(1);
  }

  edgecnt = 0;
  for (i = 0; i < MAX_EDGES; i++) {
    cellinfo[cellcnt].formats[i] = -1;
  }

  if (DSET == 0) chk_problem_type(0, lcode0, field, GCTNAME, dupwarn);
  if (DSET == 1) chk_problem_type(1, lcode1, field, GCTNAME, dupwarn);

  if (DSET == 0) {
    for (i = 0; i <= ne; i++) ALIASSTR[i] = (lcode0[i] == FC_DUMMY) ? FC_ASCII : lcode0[i];
    ALIASSTR[i] = '\0';
  }
  else {						/* (DSET==1) */
    for (i = 0; i <= ne; i++) ALIASSTR[i] = (lcode1[i] == FC_DUMMY) ? FC_ASCII : lcode1[i];
    ALIASSTR[i] = '\0';
  }
  if (*modcode == FC_WINDOWOPEN || *modcode == FC_WINDOWOPENZ) {
    fprintf(fpstatus,"CELL[%s]%c window left pending\n",field[0][0],*modcode);
    if (WINLEFTPEND == 0) {
      fprintf(stdout,"CELL[%s]%c window left pending\n",field[0][0],*modcode);
      fprintf(stdout,"*********\nSupressing future wintype prints to stdout (remainder logged to %s)\n**********\n",TRANSLATION_STATUS);
      WINLEFTPEND = 1;
    }
  }
  if (cellisdrv) cellisNOTstrb = 1;
  if (D0H == AM_continue || D0L == AM_continueLO) {
    cellinfo[cellcnt].filepos = holdlen;
    cellinfo[cellcnt].cdtstr[0] = cellinfo[cellcnt].cdtcode = startstop[startStopInd].cdtcode;
    cellinfo[cellcnt].cdtstr[1] = '\0';
    cellinfo[cellcnt].actline = which;
    strcpy(cellinfo[cellcnt].wftname, GCTNAME);
    strcpy(cellinfo[cellcnt].cellname, field[0][0]);
    strcpy(cellinfo[cellcnt].pin, tpin);
    cellinfo[cellcnt].multidefnum = CNT;
    cellinfo[cellcnt].formatnum = wtlookup;
    for (i = 0; i < MAX_EDGES; i++) {
      cellinfo[cellcnt].formats[i] = (DSET == 0) ? lcode0[i] : lcode1[i];
    }
    cellinfo[cellcnt].problemtype = PT_NOPROBLEM;
    cellinfo[cellcnt].alias0 = A0 = AM_continueLO;
    cellinfo[cellcnt].alias1 = A1 = AM_BOGUS;
    sprintf(SCATcycle,"Cell \"%s\" %c %s_ADSET%01d%s_cat_%s {\n   Data %c;\n", pin,
	    A0,field[0][0], DSET, ALIASSTR, dupwarn,'0');
    strcat(cyclebuff, SCATcycle);
    sprintf(SCATcycle,"   Compare {   \n       EntryState CompareLow;\n      }\n");
    strcpy(cellinfo[cellcnt].cellexpr,"   Compare {   \n       EntryState CompareOpenLow;\n      }\n");
    strcat(cyclebuff, SCATcycle);
    //		edgeset_make_wfms(cyclebuff, field, en, ne, neST, org, 0, delay, nDELAYDATA);
    strcat(cyclebuff, "}\n");
    cellcnt++;
    /* --- */
    cellinfo[cellcnt].filepos = holdlen;
    cellinfo[cellcnt].cdtstr[0] = cellinfo[cellcnt].cdtcode = startstop[startStopInd].cdtcode;
    cellinfo[cellcnt].cdtstr[1] = '\0';
    cellinfo[cellcnt].actline = which;
    strcpy(cellinfo[cellcnt].wftname, GCTNAME);
    strcpy(cellinfo[cellcnt].cellname, field[0][0]);
    strcpy(cellinfo[cellcnt].pin, tpin);
    cellinfo[cellcnt].multidefnum = CNT;
    cellinfo[cellcnt].formatnum = wtlookup;
    for (i = 0; i < MAX_EDGES; i++) {
      cellinfo[cellcnt].formats[i] = (DSET == 0) ? lcode0[i] : lcode1[i];
    }
    cellinfo[cellcnt].problemtype = PT_NOPROBLEM;
    cellinfo[cellcnt].alias0 = A0 = AM_continue;
    cellinfo[cellcnt].alias1 = A1 = AM_BOGUS;
    sprintf(SCATcycle,"Cell \"%s\" %c %s_BDSET%01d%s_cat_%s {\n   Data %c;\n", pin,
	    A0,field[0][0], DSET, ALIASSTR, dupwarn,'1');
    strcat(cyclebuff, SCATcycle);
    sprintf(SCATcycle,"   Compare {   \n       EntryState CompareOpenHigh;\n      }\n");
    strcpy(cellinfo[cellcnt].cellexpr,"   Compare {   \n       EntryState CompareOpenHigh;\n      }\n");
    strcat(cyclebuff, SCATcycle);
    //		edgeset_make_wfms(cyclebuff, field, en, ne, neST, org, 0, delay,
    //						  nDELAYDATA);
    strcat(cyclebuff, "}\n");
    cellcnt++;
    /* --- */
    /* continue Drive is dealt with in the generic/COMMON_WFT table */
  }
  else if (cellisNOTstrb) {	/* drive */

    /* ok, here we've decided for code simplicity to update the primary cell and */
    /* the splitHi cell but increment by one if combined, and increment by two if */
    /* split. control variable is splitcell. */
    cellinfo[cellcnt].filepos = cellinfo[cellcnt + 1].filepos = holdlen;
    cellinfo[cellcnt].cdtstr[0] = cellinfo[cellcnt].cdtcode = startstop[startStopInd].cdtcode;
    cellinfo[cellcnt].cdtstr[1] = '\0';
    cellinfo[cellcnt + 1].cdtstr[0] = cellinfo[cellcnt + 1].cdtcode = startstop[startStopInd].cdtcode;
    cellinfo[cellcnt + 1].cdtstr[1] = '\0';
    cellinfo[cellcnt].actline = cellinfo[cellcnt + 1].actline = which;
    strcpy(cellinfo[cellcnt].wftname, GCTNAME);
    strcpy(cellinfo[cellcnt + 1].wftname, GCTNAME);
    strcpy(cellinfo[cellcnt].cellname, field[0][0]);
    strcpy(cellinfo[cellcnt + 1].cellname, field[0][0]);
    strcpy(cellinfo[cellcnt].pin, tpin);
    strcpy(cellinfo[cellcnt + 1].pin, tpin);
    cellinfo[cellcnt].multidefnum = cellinfo[cellcnt + 1].multidefnum = CNT;
    cellinfo[cellcnt].formatnum = cellinfo[cellcnt + 1].formatnum = wtlookup;
    for (i = 0; i < MAX_EDGES; i++) {
      cellinfo[cellcnt].formats[i] = (DSET == 0) ? lcode0[i] : lcode1[i];
      cellinfo[cellcnt + 1].formats[i] = (DSET == 0) ? lcode0[i] : lcode1[i];
    }
    cellinfo[cellcnt].problemtype = cellinfo[cellcnt + 1].problemtype = PT_NOPROBLEM;
    cellinfo[cellcnt].alias0 = A0 = (DSET == 0) ? D0L : (DSET == 1) ? D1L : DbL;
    cellinfo[cellcnt + 1].alias0 = A1 = (DSET == 0) ? D0H : (DSET == 1) ? D1H : DbH;

    if (splitcell) cellinfo[cellcnt].alias1 = cellinfo[cellcnt + 1].alias1 = AM_BOGUS;	/* bogus value */
    else cellinfo[cellcnt].alias1 = A1 = (DSET == 0) ? D0H : (DSET == 1) ? D1H : DbH;

    if (splitcell)
      sprintf(SCATcycle,"Cell \"%s\" %c %s_ADSET%01d%s_cat_%s {\n   Data %c;\n",
	      tpin, A0, field[0][0], DSET, ALIASSTR, dupwarn,
	      cellisdrv * 4 + 2 + '0');
    else
      sprintf(SCATcycle,"Cell \"%s\" %c/%c %s_DSET%01d%s_cat_%s {\n   Data %c/%c;\n",
	      tpin, A0, A1, field[0][0], DSET, ALIASSTR, dupwarn,
	      cellisdrv * 4 + 2 + '0', cellisdrv * 4 + 2 + '1');

    strcat(cyclebuff, SCATcycle);
    edgeset_make_wfms(cyclebuff, field, en, ne, neST, org, 0, delay, nDELAYDATA);
    strcat(cyclebuff, "}\n");

    if (splitcell) {
      cellcnt++;
      sprintf(SCATcycle,"Cell \"%s\" %c %s_BDSET%01d%s_cat_%s {\n   Data %c;\n",
	      tpin, A1, field[0][0], DSET, ALIASSTR, dupwarn, cellisdrv * 4 + 2 + '1');
      strcat(cyclebuff, SCATcycle);
      edgeset_make_wfms(cyclebuff, field, en, ne, neST, org, 1, delay, nDELAYDATA);
      strcat(cyclebuff, "}\n");
    }
    cellcnt++;
  }

  else {						/* strobe */

    cxL = (DSET == 0) ? AM_maskD0 : AM_maskD1;
    cxH = (DSET == 0) ? AM_maskHID0 : AM_maskHID1;

    cellinfo[cellcnt].filepos = cellinfo[cellcnt + 1].filepos = holdlen;
    cellinfo[cellcnt].cdtstr[0] = cellinfo[cellcnt].cdtcode = startstop[startStopInd].cdtcode;
    cellinfo[cellcnt].cdtstr[1] = '\0';
    cellinfo[cellcnt + 1].cdtstr[0] = cellinfo[cellcnt + 1].cdtcode = startstop[startStopInd].cdtcode;
    cellinfo[cellcnt + 1].cdtstr[1] = '\0';
    cellinfo[cellcnt].actline = cellinfo[cellcnt + 1].actline = which;
    strcpy(cellinfo[cellcnt].wftname, GCTNAME);
    strcpy(cellinfo[cellcnt + 1].wftname, GCTNAME);
    strcpy(cellinfo[cellcnt].cellname, field[0][0]);
    strcpy(cellinfo[cellcnt + 1].cellname, field[0][0]);
    strcpy(cellinfo[cellcnt].pin, tpin);
    strcpy(cellinfo[cellcnt + 1].pin, tpin);
    cellinfo[cellcnt].multidefnum = cellinfo[cellcnt + 1].multidefnum = CNT;
    cellinfo[cellcnt].formatnum = cellinfo[cellcnt + 1].formatnum = wtlookup;
    for (i = 0; i < MAX_EDGES; i++) {
      cellinfo[cellcnt].formats[i] = (DSET == 0) ? lcode0[i] : lcode1[i];
      cellinfo[cellcnt + 1].formats[i] = (DSET == 0) ? lcode0[i] : lcode1[i];
    }
    cellinfo[cellcnt].problemtype = cellinfo[cellcnt + 1].problemtype = PT_NOPROBLEM;
    cellinfo[cellcnt].alias0 = A0 = (DSET == 0) ? D0L : (DSET == 1) ? D1L : DbL;
    cellinfo[cellcnt + 1].alias0 = A1 = (DSET == 0) ? D0H : (DSET == 1) ? D1H : DbH;
    Z0 = (DSET == 0) ? AM_driveoffLOD0:AM_driveoffLOD1;
    Z1 = (DSET == 0) ? AM_driveoffHID0:AM_driveoffHID1;
    if (splitcell) {
      cellinfo[cellcnt].alias1 = cxL;
      cellinfo[cellcnt + 1].alias1 = cxH;
      if (A0 == AM_strobeoffLOD0 || A0 == AM_strobeoffLOD1) {
	sprintf(SCATcycle,"Cell \"%s\" %c/%c/%c %s_ADSET%01d%s_cat_%s {\n   Data %c/%c/%c;\n",
		tpin, A0, cxL, Z0,  field[0][0], DSET, ALIASSTR, dupwarn, '0', '2', '6');
      }
      else {
	sprintf(SCATcycle,"Cell \"%s\" %c/%c %s_ADSET%01d%s_cat_%s {\n   Data %c/%c;\n",
		tpin, A0, cxL, field[0][0], DSET, ALIASSTR, dupwarn, '0', '2');
      }
    }

    else {
      cellinfo[cellcnt].alias1 = A1 = (DSET == 0) ? D0H : (DSET == 1) ? D1H : DbH;
      if (A0 == AM_strobeoffLOD0 || A0 == AM_strobeoffLOD1) {
	sprintf(SCATcycle,"Cell \"%s\" %c/%c/%c/%c/%c/%c %s_DSET%01d%s_cat_%s {\n   Data %c/%c/%c/%c/%c/%c;\n",
		tpin, A0, A1, cxL, cxH, Z0, Z1, field[0][0], DSET, ALIASSTR, dupwarn, '0', '1', '2', '3', '6', '7');
      }
      else {
	sprintf(SCATcycle,"Cell \"%s\" %c/%c/%c/%c %s_DSET%01d%s_cat_%s {\n   Data %c/%c/%c/%c;\n",
		tpin, A0, A1, cxL, cxH, field[0][0], DSET, ALIASSTR, dupwarn, '0', '1', '2', '3');
      }
    }

    strcat(cyclebuff, SCATcycle);

    /* Now modify the waveforms if necessary */

    edgeset_make_wfms(cyclebuff, field, en, ne, neST, org, 0, delay, nDELAYDATA);
    strcat(cyclebuff, "}\n");

    if (splitcell) {
      cellcnt++;
      if (A0 == AM_strobeoffLOD0 || A0 == AM_strobeoffLOD1) {
	sprintf(SCATcycle,"Cell \"%s\" %c/%c/%c %s_BDSET%01d%s_cat_%s {\n   Data %c/%c/%c;\n",
		tpin, A1, cxH, Z1, field[0][0], DSET, ALIASSTR, dupwarn, '1', '3', '7');
      }
      else {
	sprintf(SCATcycle,"Cell \"%s\" %c/%c %s_BDSET%01d%s_cat_%s {\n   Data %c/%c;\n",
		tpin, A1, cxH, field[0][0], DSET, ALIASSTR, dupwarn, '1', '3');
      }
      strcat(cyclebuff, SCATcycle);

      /* Now modify the waveforms if necessary */

      edgeset_make_wfms(cyclebuff, field, en, ne, neST, org, 1, delay, nDELAYDATA);
      strcat(cyclebuff, "}\n");
    }
    cellcnt++;
  }

  if (cellcnt > MAXCELLS) {
    fprintf(stderr, "Too many cells., source[%s,%d,%s]\n", __FILE__,__LINE__, __FUNCTION__);
    fprintf(fperrors, "Too many cells., source[%s,%d,%s]\n", __FILE__,__LINE__, __FUNCTION__);
    exit(1);
  }

  if (MUXFLAG && NOMUX == 0) {				/* FIXME: APS need more checks here, specifically ChanFirst,ChanSecond... */
    /* all wavesets will assume normal edges from only channel '0' */
    /* this means the muxpin should produce null edges */
    cellinfo[cellcnt].filepos = holdlen;
    cellinfo[cellcnt].cdtstr[0] = cellinfo[cellcnt].cdtcode = startstop[startStopInd].cdtcode;
    cellinfo[cellcnt].cdtstr[1] = '\0';
    cellinfo[cellcnt].actline = which;
    strcpy(cellinfo[cellcnt].wftname, GCTNAME);
    strcpy(cellinfo[cellcnt].cellname, field[0][0]);
    sprintf(cellinfo[cellcnt].pin, "%s-MUXPRIMARYPINS", pin);
    cellinfo[cellcnt].multidefnum = CNT;
    cellinfo[cellcnt].formatnum = wtlookup;
    for (i = 0; i < MAX_EDGES; i++) {
      cellinfo[cellcnt].formats[i] = FC_NULLEDGE;
    }
    cellinfo[cellcnt].problemtype = PT_NOPROBLEM;
    cellinfo[cellcnt].alias0 = A0;
    cellinfo[cellcnt].alias1 = A1;
    cellinfo[cellcnt].cellexpr[0] = '\0';	/* either use edgeset_make_wfms or '\0' */

    if (cellisNOTstrb) {
      sprintf(SCATcycle,"Cell \"%s-MUXPRIMARYPINS\" %c/%c %s_DSETMUX%01d%s_cat_%s {\n   Data %c/%c;\n",
	      pin, A0, A1, field[0][0], DSET, ALIASSTR, dupwarn, '6', '7');
    }
    else {
      sprintf(SCATcycle,"Cell \"%s-MUXPRIMARYPINS\" %c/%c/%c/%c %s_DSETMUX%01d%s_cat_%s {\n   Data %c/%c/%c/%c;\n",
	      pin, A0, A1, cxL, cxH, field[0][0], DSET, ALIASSTR,
	      dupwarn, '0', '1', '2', '3');
    }
    strcat(cyclebuff, SCATcycle);
    strcat(cyclebuff, "   Drive {\n      EntryState DriveOn;}\n");
    strcat(cyclebuff, "}\n");

    cellcnt++;
    if (cellcnt > MAXCELLS) {
      fprintf(stderr,"Too many Cells for buffer, source[%s,%d,%s]\n",__FILE__, __LINE__, __FUNCTION__);
      fprintf(fperrors,"Too many Cells for buffer, source[%s,%d,%s]\n",__FILE__, __LINE__, __FUNCTION__);
      exit(1);
    }
  }

  return (ne);
}
