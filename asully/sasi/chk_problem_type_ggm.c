/* chk_problem_type_ggm.c */
/* chk_problem_type(){} */

#include <stdio.h>
#include <string.h>
#include "includes_ggm.h"
#include "aliasmap.h"

int chk_problem_type(int DSET, int lcoden[], char field[][100][WF_EXPR_LEN], char *GCTNAME, char *dupwarn) {
	/* check if its an 'odd' format.... AM_strobeoffLOopenwindowLOD0,AM_strobeoffLOD0,AM_continue etc */
	/* (0-63) + 64*(0-63)+ 64*64*(0-63)+64*64*64*(0-63) needs about 25 bits, assuming 32bit int.... */
	int i;
	static int warned = 0;
	char find[MAX_EDGES + 1];

	if (strcmp(field[3][2], "ChanSecond") == 0 && warned == 0) {
		fprintf(stderr, "Waveform[%s] using ChanSecond, assuming this is mux,\n",
				field[3][0]);
		fprintf(stderr,
				"see notes in documentation on how to change this so data is chosen from each pin correctly.\n");
		fprintf(stderr, "More waveforms may be listed in %s.\n", TRANSLATION_ERRORS);
		warned = 1;
	}
	if (strcmp(field[3][2], "ChanSecond") == 0) {
		fprintf(fperrors, "Waveform[%s] using ChanSecond, assuming this is mux,\n", field[3][0]);
		fprintf(fperrors,
				"see notes in documentation on how to change this so data is chosen from each pin correctly\n");
	}
	for (i = 0; i < MAX_EDGES; i++) {
		find[i] = lcoden[i];
	}
	find[MAX_EDGES] = '\0';

	fprintf(fpstatus, "PC=%s ", find);
//=========================
//PC=n///
	if (lcoden[0] == FC_NULLEDGE && lcoden[1] == FC_DUMMY
		&& lcoden[2] == FC_DUMMY  && lcoden[3] == FC_DUMMY) {
		fprintf(fpstatus,
				"FOUND [WFM:%s CYLTBL:%s DUPEWARN:%s]%d NO ACTION [%s,%d]\n",
				field[0][0], GCTNAME, dupwarn, DSET, __FUNCTION__, __LINE__);
	}
//PC=////
	else if (lcoden[0] == FC_DUMMY && lcoden[1] == FC_DUMMY
			&& lcoden[2] == FC_DUMMY && lcoden[3] == FC_DUMMY) {
		fprintf(fpstatus,
				"FOUND [WFM:%s CYLTBL:%s DUPEWARN:%s]%d NO ACTION [%s,%d]\n",
				field[0][0], GCTNAME, dupwarn, DSET, __FUNCTION__, __LINE__);
	}
//PC=D///
	else if (lcoden[0] == FC_DRIVEDATA && lcoden[1] == FC_DUMMY
			&& lcoden[2] == FC_DUMMY     && lcoden[3] == FC_DUMMY) {
		fprintf(fpstatus,
				"FOUND [WFM:%s CYLTBL:%s DUPEWARN:%s]%d DRIVEDATA [%s,%d]\n",
				field[0][0], GCTNAME, dupwarn, DSET, __FUNCTION__, __LINE__);
	}
//PC=DD//
	else if (lcoden[0] == FC_DRIVEDATA && lcoden[1] == FC_DRIVEDATA
			&& lcoden[2] == FC_DUMMY     && lcoden[3] == FC_DUMMY) {
		fprintf(fpstatus,
				"FOUND [WFM:%s CYLTBL:%s DUPEWARN:%s]%d DRIVEDATA-DRIVEDATA [%s,%d]\n",
				field[0][0], GCTNAME, dupwarn, DSET, __FUNCTION__, __LINE__);
	}
//PC=DDD/
	else if (lcoden[0] == FC_DRIVEDATA && lcoden[1] == FC_DRIVEDATA
			&& lcoden[2] == FC_DRIVEDATA && lcoden[3] == FC_DUMMY) {
		fprintf(fpstatus,
				"FOUND [WFM:%s CYLTBL:%s DUPEWARN:%s]%d 3-edge DRIVEDATA [%s,%d]\n",
				field[0][0], GCTNAME, dupwarn, DSET, __FUNCTION__, __LINE__);
	}
//PC=DDDD
	else if (lcoden[0] == FC_DRIVEDATA && lcoden[1] == FC_DRIVEDATA
			&& lcoden[2] == FC_DRIVEDATA && lcoden[3] == FC_DRIVEDATA) {
		fprintf(fpstatus,
				"FOUND [WFM:%s CYLTBL:%s DUPEWARN:%s]%d 4-edge DRIVEDATA [%s,%d]\n",
				field[0][0], GCTNAME, dupwarn, DSET, __FUNCTION__, __LINE__);
	}
//=========================
//PC=X///
	else if (lcoden[0] == FC_DRIVEOFF && lcoden[1] == FC_DUMMY
			&& lcoden[2] == FC_DUMMY    && lcoden[3] == FC_DUMMY) {
		fprintf(fpstatus,
				"FOUND [WFM:%s CYLTBL:%s DUPEWARN:%s]%d DRIVEOFF [%s,%d]\n",
				field[0][0], GCTNAME, dupwarn, DSET, __FUNCTION__, __LINE__);
	}
//PC=DX//
	else if (lcoden[0] == FC_DRIVEDATA && lcoden[1] == FC_DRIVEOFF
			&& lcoden[2] == FC_DUMMY     && lcoden[3] == FC_DUMMY) {
		fprintf(fpstatus,
				"FOUND [WFM:%s CYLTBL:%s DUPEWARN:%s]%d DRIVEDATA-DRIVEOFF [%s,%d]\n",
				field[0][0], GCTNAME, dupwarn, DSET, __FUNCTION__, __LINE__);
	}
//PC=XD//
	else if (lcoden[0] == FC_DRIVEOFF && lcoden[1] == FC_DRIVEDATA
			&& lcoden[2] == FC_DUMMY    && lcoden[3] == FC_DUMMY) {
		fprintf(fpstatus,
				"FOUND [WFM:%s CYLTBL:%s DUPEWARN:%s]%d DRIVEOFF-DRIVEDATA [%s,%d]\n",
				field[0][0], GCTNAME, dupwarn, DSET, __FUNCTION__, __LINE__);
	}
//PC=XE//
	else if (lcoden[0] == FC_DRIVEOFF && lcoden[1] == FC_EDGEDATA
			&& lcoden[2] == FC_DUMMY    && lcoden[3] == FC_DUMMY) {
		fprintf(fpstatus,
				"FOUND [WFM:%s CYLTBL:%s DUPEWARN:%s]%d DRIVEOFF-EDGEDATA [%s,%d]\n",
				field[0][0], GCTNAME, dupwarn, DSET, __FUNCTION__, __LINE__);
	}
//PC=XE//
	else if (lcoden[0] == FC_DRIVEOFF && lcoden[1] == FC_EDGEDATA
			&& lcoden[2] == FC_LATCH    && lcoden[3] == FC_DUMMY) {
		fprintf(fpstatus,
				"FOUND [WFM:%s CYLTBL:%s DUPEWARN:%s]%d DRIVEOFF-EDGEDATA-LATCH [%s,%d]\n",
				field[0][0], GCTNAME, dupwarn, DSET, __FUNCTION__, __LINE__);
	}
//PC=E//
	else if (lcoden[0] == FC_EDGEDATA && lcoden[1] == FC_DUMMY
			&& lcoden[2] == FC_DUMMY    && lcoden[3] == FC_DUMMY) {
		fprintf(fpstatus,
				"FOUND [WFM:%s CYLTBL:%s DUPEWARN:%s]%d EDGEDATA [%s,%d]\n",
				field[0][0], GCTNAME, dupwarn, DSET, __FUNCTION__, __LINE__);
	}
//PC=EQ//
	else if (lcoden[0] == FC_EDGEDATA && lcoden[1] == FC_LATCH
			&& lcoden[2] == FC_DUMMY    && lcoden[3] == FC_DUMMY) {
		fprintf(fpstatus,
				"FOUND [WFM:%s CYLTBL:%s DUPEWARN:%s]%d EDGEDATA-LATCH [%s,%d]\n",
				field[0][0], GCTNAME, dupwarn, DSET, __FUNCTION__, __LINE__);
	}
//PC=XF//
	else if (lcoden[0] == FC_DRIVEOFF && lcoden[1] == FC_EDGEFLOAT
			&& lcoden[2] == FC_DUMMY    && lcoden[3] == FC_DUMMY) {
		fprintf(fpstatus,
				"FOUND [WFM:%s CYLTBL:%s DUPEWARN:%s]%d DRIVEOFF-EDGEFLOAT [%s,%d]\n",
				field[0][0], GCTNAME, dupwarn, DSET, __FUNCTION__, __LINE__);
	}
//PC=F///
	else if (lcoden[0] == FC_EDGEFLOAT && lcoden[1] == FC_DUMMY
			&& lcoden[2] == FC_DUMMY     && lcoden[3] == FC_DUMMY) {
		fprintf(fpstatus,
				"FOUND [WFM:%s CYLTBL:%s DUPEWARN:%s]%d EDGEFLOAT [%s,%d]\n",
				field[0][0], GCTNAME, dupwarn, DSET, __FUNCTION__, __LINE__);
	}
//PC=XWk/
	else if (lcoden[0] == FC_DRIVEOFF  && lcoden[1] == FC_WINDOWDATA
			&& lcoden[2] == FC_STROBEOFF && lcoden[3] == FC_DUMMY) {
		fprintf(fpstatus,
				"FOUND [WFM:%s CYLTBL:%s DUPEWARN:%s]%d DRIVEOFF-WINDOWOPEN-WINDOWCLOSE [%s,%d]\n",
				field[0][0], GCTNAME, dupwarn, DSET, __FUNCTION__, __LINE__);
	}
//PC=Wk//
	else if (lcoden[0] == FC_WINDOWDATA && lcoden[1] == FC_STROBEOFF
			&& lcoden[2] == FC_DUMMY      && lcoden[3] == FC_DUMMY) {
		fprintf(fpstatus,
				"FOUND [WFM:%s CYLTBL:%s DUPEWARN:%s]%d WINDOWOPEN-WINDOWCLOSE [%s,%d]\n",
				field[0][0], GCTNAME, dupwarn, DSET, __FUNCTION__, __LINE__);
	}
//PC=fk//
	else if (lcoden[0] == FC_WINDOWFLOAT && lcoden[1] == FC_STROBEOFF
			&& lcoden[2] == FC_DUMMY       && lcoden[3] == FC_DUMMY) {
		fprintf(fpstatus,
				"FOUND [WFM:%s CYLTBL:%s DUPEWARN:%s]%d FLOATOPEN-WINDOWCLOSE [%s,%d]\n",
				field[0][0], GCTNAME, dupwarn, DSET, __FUNCTION__, __LINE__);
	}
//=========================
//PC=Xk//
	else if (lcoden[0] == FC_DRIVEOFF && lcoden[1] == FC_STROBEOFF
			&& lcoden[2] == FC_DUMMY    && lcoden[3] == FC_DUMMY) {
		fprintf(fpstatus,
				"FOUND [WFM:%s CYLTBL:%s DUPEWARN:%s]%d DRIVEOFF-STROBEOFF [%s,%d] needs entry state\n",
				field[0][0], GCTNAME, dupwarn, DSET, __FUNCTION__, __LINE__);
	}
//PC=X/k/
	else if (lcoden[0] == FC_DRIVEOFF  && lcoden[1] == FC_DUMMY
			&& lcoden[2] == FC_STROBEOFF && lcoden[3] == FC_DUMMY) {
		fprintf(fpstatus,
				"FOUND [WFM:%s CYLTBL:%s DUPEWARN:%s]%d DRIVEOFF-STROBEOFF [%s,%d] needs entry state\n",
				field[0][0], GCTNAME, dupwarn, DSET, __FUNCTION__, __LINE__);
	}
//PC=kX//
	else if (lcoden[0] == FC_STROBEOFF && lcoden[1] == FC_DRIVEOFF
			&& lcoden[2] == FC_DUMMY     && lcoden[3] == FC_DUMMY) {
		cellinfo[cellcnt].problemtype = PT_CLOSEOFF;
		fprintf(fpstatus,
				"FOUND [WFM:%s CYLTBL:%s DUPEWARN:%s]%d STROBEOFF-DRIVEOFF [%s,%d] needs entry state\n",
				field[0][0], GCTNAME, dupwarn, DSET, __FUNCTION__, __LINE__);
	}
//PC=k///
	else if (lcoden[0] == FC_STROBEOFF && lcoden[1] == FC_DUMMY
			&& lcoden[2] == FC_DUMMY     && lcoden[3] == FC_DUMMY) {
		cellinfo[cellcnt].problemtype = PT_CLOSE;
		fprintf(fpstatus,
				"FOUND [WFM:%s CYLTBL:%s DUPEWARN:%s]%d STROBEOFF [%s,%d] needs entry state\n",
				field[0][0], GCTNAME, dupwarn, DSET, __FUNCTION__, __LINE__);
	}
//=========================
//PC=WkWk// 
	else if (lcoden[0] == FC_WINDOWDATA && lcoden[1] == FC_STROBEOFF
			&& lcoden[2] == FC_WINDOWDATA && lcoden[3] == FC_STROBEOFF) {
		fprintf(fpstatus,
				"FOUND [WFM:%s CYLTBL:%s DUPEWARN:%s]%d WINDOWOPEN-WINDOWCLOSE-WINDOWOPEN-WINDOWCLOSE [%s,%d] needs FX1 fix\n",
				field[0][0], GCTNAME, dupwarn, DSET, __FUNCTION__, __LINE__);
		if (EVX2==0 || PBSTROBE == 0) fprintf(fperrors,
				"FOUND [WFM:%s CYLTBL:%s DUPEWARN:%s]%d WINDOWOPEN-WINDOWCLOSE-WINDOWOPEN-WINDOWCLOSE [%s,%d] needs FX1 fix\n",
				field[0][0], GCTNAME, dupwarn, DSET, __FUNCTION__, __LINE__);
		if (EVX2==0 || PBSTROBE == 0) fprintf(stderr,
				"\nFOUND [WFM:%s CYLTBL:%s DUPEWARN:%s]%d WINDOWOPEN-WINDOWCLOSE-WINDOWOPEN-WINDOWCLOSE [%s,%d] needs FX1 fix\n",
				field[0][0], GCTNAME, dupwarn, DSET, __FUNCTION__, __LINE__);
		EVX2 = PBSTROBE = 1;
	}
//PC=/WkWk// (5 edge waveform) first driveoff removed...
	else if (lcoden[0] == FC_DUMMY      && lcoden[1] == FC_WINDOWDATA
			&& lcoden[2] == FC_STROBEOFF  && lcoden[3] == FC_WINDOWDATA
			&& lcoden[4] == FC_STROBEOFF ) {
		fprintf(fpstatus,
				"FOUND [WFM:%s CYLTBL:%s DUPEWARN:%s]%d (DRIVEOFF)-WINDOWOPEN-WINDOWCLOSE-WINDOWOPEN-WINDOWCLOSE [%s,%d] needs FX1 fix\n",
				field[0][0], GCTNAME, dupwarn, DSET, __FUNCTION__, __LINE__);
		if (EVX2==0 || PBSTROBE == 0) fprintf(fperrors,
				"FOUND [WFM:%s CYLTBL:%s DUPEWARN:%s]%d (DRIVEOFF)-WINDOWOPEN-WINDOWCLOSE-WINDOWOPEN-WINDOWCLOSE [%s,%d] needs FX1 fix\n",
				field[0][0], GCTNAME, dupwarn, DSET, __FUNCTION__, __LINE__);
		if (EVX2==0 || PBSTROBE == 0) fprintf(stderr,
				"\nFOUND [WFM:%s CYLTBL:%s DUPEWARN:%s]%d (DRIVEOFF)-WINDOWOPEN-WINDOWCLOSE-WINDOWOPEN-WINDOWCLOSE [%s,%d] needs FX1 fix\n",
				field[0][0], GCTNAME, dupwarn, DSET, __FUNCTION__, __LINE__);
		EVX2 = PBSTROBE = 1;
	}
//=========================
//PC=W///
	else if (lcoden[0] == FC_WINDOWDATA && lcoden[1] == FC_DUMMY
			&& lcoden[2] == FC_DUMMY      && lcoden[3] == FC_DUMMY) {
		fprintf(fpstatus,
				"FOUND [WFM:%s CYLTBL:%s DUPEWARN:%s]%d WINDOW OPEN without close[%s,%d] uses multicycle window\n",
				field[0][0], GCTNAME, dupwarn, DSET, __FUNCTION__, __LINE__);
		if ( PBCLOSE == 0 ) fprintf(fperrors,
				"FOUND [WFM:%s CYLTBL:%s DUPEWARN:%s]%d WINDOW OPEN without close[%s,%d] uses multicycle window\n",
				field[0][0], GCTNAME, dupwarn, DSET, __FUNCTION__, __LINE__);
		if ( PBCLOSE == 0 ) fprintf(stderr,
				"\nFOUND [WFM:%s CYLTBL:%s DUPEWARN:%s]%d WINDOW OPEN without close[%s,%d] uses multicycle window\n",
				field[0][0], GCTNAME, dupwarn, DSET, __FUNCTION__, __LINE__);
		PBCLOSE =1; /* EVX2 mode not required for this case.... */
	}
//PC=f///
	else if (lcoden[0] == FC_WINDOWFLOAT && lcoden[1] == FC_DUMMY
			&& lcoden[2] == FC_DUMMY       && lcoden[3] == FC_DUMMY) {
		fprintf(fpstatus,
				"FOUND [WFM:%s CYLTBL:%s DUPEWARN:%s]%d FLOATOPEN without close [%s,%d] uses multicycle window\n",
				field[0][0], GCTNAME, dupwarn, DSET, __FUNCTION__, __LINE__);
		if ( PBCLOSE == 0 ) fprintf(fperrors,
				"FOUND [WFM:%s CYLTBL:%s DUPEWARN:%s]%d FLOATOPEN without close [%s,%d] uses multicycle window\n",
				field[0][0], GCTNAME, dupwarn, DSET, __FUNCTION__, __LINE__);
		if ( PBCLOSE == 0 ) fprintf(stderr,
				"\nFOUND [WFM:%s CYLTBL:%s DUPEWARN:%s]%d FLOATOPEN without close [%s,%d] uses multicycle window\n",
				field[0][0], GCTNAME, dupwarn, DSET, __FUNCTION__, __LINE__);
		PBCLOSE =1; /* EVX2 mode not required for this case.... */
	}
//PC=WW//
	else if (lcoden[0] == FC_WINDOWDATA && lcoden[1] == FC_WINDOWDATA
			&& lcoden[2] == FC_DUMMY      && lcoden[3] == FC_DUMMY) {
		fprintf(fpstatus,
				"\nERROR FOUND [WFM:%s CYLTBL:%s DUPEWARN:%s]%d WINDOW OPEN-WINDOW OPEN without close [%s,%d] needs multiwindow fixup\n",
				field[0][0], GCTNAME, dupwarn, DSET, __FUNCTION__, __LINE__);
		if (EVX2==0 || PBCLOSE == 0) fprintf(fperrors,
				"\nERROR FOUND [WFM:%s CYLTBL:%s DUPEWARN:%s]%d WINDOW OPEN-WINDOW OPEN without close [%s,%d] needs multiwindow fixup\n",
				field[0][0], GCTNAME, dupwarn, DSET, __FUNCTION__, __LINE__);
		if (EVX2==0 || PBCLOSE == 0) fprintf(stderr,
				"\nERROR FOUND [WFM:%s CYLTBL:%s DUPEWARN:%s]%d WINDOW OPEN-WINDOW OPEN without close [%s,%d] needs multiwindow fixup\n",
				field[0][0], GCTNAME, dupwarn, DSET, __FUNCTION__, __LINE__);
		EVX2 = PBCLOSE =1;
	}
//PC=XW//
	else if (lcoden[0] == FC_DRIVEOFF && lcoden[1] == FC_WINDOWDATA
			&& lcoden[2] == FC_DUMMY    && lcoden[3] == FC_DUMMY) {
		cellinfo[cellcnt].problemtype = PT_OFFOPEN;
		fprintf(fpstatus,
				"FOUND [WFM:%s CYLTBL:%s DUPEWARN:%s]%d DRIVEOFF-WINDOW OPEN [%s,%d] uses multicycle window\n",
				field[0][0], GCTNAME, dupwarn, DSET, __FUNCTION__, __LINE__);
		if ( PBCLOSE == 0 ) fprintf(fperrors,
				"FOUND [WFM:%s CYLTBL:%s DUPEWARN:%s]%d DRIVEOFF-WINDOW OPEN [%s,%d] uses multicycle window\n",
				field[0][0], GCTNAME, dupwarn, DSET, __FUNCTION__, __LINE__);
		if ( PBCLOSE == 0 ) fprintf(stderr,
				"\nFOUND [WFM:%s CYLTBL:%s DUPEWARN:%s]%d DRIVEOFF-WINDOW OPEN [%s,%d] uses multicycle window\n",
				field[0][0], GCTNAME, dupwarn, DSET, __FUNCTION__, __LINE__);
		PBCLOSE =1; /* EVX2 mode not required for this case.... */
	}
//PC=kf//
	else if (lcoden[0] == FC_STROBEOFF && lcoden[1] == FC_WINDOWFLOAT
			&& lcoden[2] == FC_DUMMY     && lcoden[3] == FC_DUMMY) {
		cellinfo[cellcnt].problemtype = PT_CLOSEFLOATOPEN;
		fprintf(fpstatus,
				"FOUND [WFM:%s CYLTBL:%s DUPEWARN:%s]%d STROBEOFF-FLOATWINDOW OPEN [%s,%d] needs multiwindow pattern fixup1\n",
				field[0][0], GCTNAME, dupwarn, DSET, __FUNCTION__, __LINE__);
		if (EVX2==0 || PBCLOSE == 0) fprintf(fperrors,
				"FOUND [WFM:%s CYLTBL:%s DUPEWARN:%s]%d STROBEOFF-FLOATWINDOW OPEN [%s,%d] needs multiwindow pattern fixup1\n",
				field[0][0], GCTNAME, dupwarn, DSET, __FUNCTION__, __LINE__);
		if (EVX2==0 || PBCLOSE == 0) fprintf(stderr,
				"\nFOUND [WFM:%s CYLTBL:%s DUPEWARN:%s]%d STROBEOFF-FLOATWINDOW OPEN [%s,%d] needs multiwindow pattern fixup1\n",
				field[0][0], GCTNAME, dupwarn, DSET, __FUNCTION__, __LINE__);
		EVX2 = PBCLOSE =1;
	}
//PC=kW//
	else if (lcoden[0] == FC_STROBEOFF && lcoden[1] == FC_WINDOWDATA
			&& lcoden[2] == FC_DUMMY     && lcoden[3] == FC_DUMMY) {
		cellinfo[cellcnt].problemtype = PT_CLOSEOPEN;
		fprintf(fpstatus,
				"FOUND [WFM:%s CYLTBL:%s DUPEWARN:%s]%d STROBEOFF-WINDOW OPEN [%s,%d] needs multiwindow pattern fixup1\n",
				field[0][0], GCTNAME, dupwarn, DSET, __FUNCTION__, __LINE__);
		if (EVX2==0 || PBCLOSE == 0) fprintf(fperrors,
				"FOUND [WFM:%s CYLTBL:%s DUPEWARN:%s]%d STROBEOFF-WINDOW OPEN [%s,%d] needs multiwindow pattern fixup1\n",
				field[0][0], GCTNAME, dupwarn, DSET, __FUNCTION__, __LINE__);
		if (EVX2==0 || PBCLOSE == 0) fprintf(stderr,
				"\nFOUND [WFM:%s CYLTBL:%s DUPEWARN:%s]%d STROBEOFF-WINDOW OPEN [%s,%d] needs multiwindow pattern fixup1\n",
				field[0][0], GCTNAME, dupwarn, DSET, __FUNCTION__, __LINE__);
		EVX2 = PBCLOSE =1;
	}
//PC=kXW/
	else if (lcoden[0] == FC_STROBEOFF  && lcoden[1] == FC_DRIVEOFF
			&& lcoden[2] == FC_WINDOWDATA && lcoden[3] == FC_DUMMY) {
		cellinfo[cellcnt].problemtype = PT_CLOSEOPEN;
		fprintf(fpstatus,
				"FOUND [WFM:%s CYLTBL:%s DUPEWARN:%s]%d STROBEOFF-DRIVEOFF-WINDOWOPEN [%s,%d] needs multiwindow pattern fixup1\n",
				field[0][0], GCTNAME, dupwarn, DSET, __FUNCTION__, __LINE__);
		if (EVX2==0 || PBCLOSE == 0) fprintf(fperrors,
				"FOUND [WFM:%s CYLTBL:%s DUPEWARN:%s]%d STROBEOFF-DRIVEOFF-WINDOWOPEN [%s,%d] needs multiwindow pattern fixup1\n",
				field[0][0], GCTNAME, dupwarn, DSET, __FUNCTION__, __LINE__);
		if (EVX2==0 || PBCLOSE == 0) fprintf(stderr,
				"\nFOUND [WFM:%s CYLTBL:%s DUPEWARN:%s]%d STROBEOFF-DRIVEOFF-WINDOWOPEN [%s,%d] needs multiwindow pattern fixup1\n",
				field[0][0], GCTNAME, dupwarn, DSET, __FUNCTION__, __LINE__);
		EVX2 = PBCLOSE =1;
	}
//PC=XkW/
	else if (lcoden[0] == FC_DRIVEOFF   && lcoden[1] == FC_STROBEOFF
			&& lcoden[2] == FC_WINDOWDATA && lcoden[3] == FC_DUMMY) {
		cellinfo[cellcnt].problemtype = PT_CLOSEOPEN;
		fprintf(fpstatus,
				"FOUND [WFM:%s CYLTBL:%s DUPEWARN:%s]%d DRIVEOFF-STROBEOFF-WINDOW OPEN [%s,%d] needs multiwindow pattern fixup1\n",
				field[0][0], GCTNAME, dupwarn, DSET, __FUNCTION__, __LINE__);
		if (EVX2==0 || PBCLOSE == 0) fprintf(fperrors,
				"FOUND [WFM:%s CYLTBL:%s DUPEWARN:%s]%d DRIVEOFF-STROBEOFF-WINDOW OPEN [%s,%d] needs multiwindow pattern fixup1\n",
				field[0][0], GCTNAME, dupwarn, DSET, __FUNCTION__, __LINE__);
		if (EVX2==0 || PBCLOSE == 0) fprintf(stderr,
				"\nFOUND [WFM:%s CYLTBL:%s DUPEWARN:%s]%d DRIVEOFF-STROBEOFF-WINDOW OPEN [%s,%d] needs multiwindow pattern fixup1\n",
				field[0][0], GCTNAME, dupwarn, DSET, __FUNCTION__, __LINE__);
		EVX2 = PBCLOSE =1;
	}
//=========================
//PC=kD//
	else if (lcoden[0] == FC_STROBEOFF && lcoden[1] == FC_DRIVEDATA
			&& lcoden[2] == FC_DUMMY     && lcoden[3] == FC_DUMMY) {
		cellinfo[cellcnt].problemtype = PT_CLOSE;
		fprintf(fpstatus,
				"FOUND [WFM:%s CYLTBL:%s DUPEWARN:%s]%d STROBEOFF-DRIVEDATA [%s,%d] needs multiwindow pattern fixup2\n",
				field[0][0], GCTNAME, dupwarn, DSET, __FUNCTION__, __LINE__);
		if (EVX2==0 || PBCLOSE == 0) fprintf(fperrors,
				"FOUND [WFM:%s CYLTBL:%s DUPEWARN:%s]%d STROBEOFF-DRIVEDATA [%s,%d] needs multiwindow pattern fixup2\n",
				field[0][0], GCTNAME, dupwarn, DSET, __FUNCTION__, __LINE__);
		if (EVX2==0 || PBCLOSE == 0) fprintf(stderr,
				"\nFOUND [WFM:%s CYLTBL:%s DUPEWARN:%s]%d STROBEOFF-DRIVEDATA [%s,%d] needs multiwindow pattern fixup2\n",
				field[0][0], GCTNAME, dupwarn, DSET, __FUNCTION__, __LINE__);
		EVX2 = PBCLOSE =1;
	}
//PC=kDD/
	else if (lcoden[0] == FC_STROBEOFF && lcoden[1] == FC_DRIVEDATA
			&& lcoden[2] == FC_DRIVEDATA ) {
		cellinfo[cellcnt].problemtype = PT_CLOSEOPEN;
		fprintf(fpstatus,
				"FOUND [WFM:%s CYLTBL:%s DUPEWARN:%s]%d STROBEOFF-DRIVEDATA-DRIVEDATA [%s,%d] needs multiwindow pattern fixup2\n",
				field[0][0], GCTNAME, dupwarn, DSET, __FUNCTION__, __LINE__);
		if (EVX2==0 || PBCLOSE == 0) fprintf(fperrors,
				"FOUND [WFM:%s CYLTBL:%s DUPEWARN:%s]%d STROBEOFF-DRIVEDATA-DRIVEDATA [%s,%d] needs multiwindow pattern fixup2\n",
				field[0][0], GCTNAME, dupwarn, DSET, __FUNCTION__, __LINE__);
		if (EVX2==0 || PBCLOSE == 0) fprintf(stderr,
				"\nFOUND [WFM:%s CYLTBL:%s DUPEWARN:%s]%d STROBEOFF-DRIVEDATA-DRIVEDATA [%s,%d] needs multiwindow pattern fixup2\n",
				field[0][0], GCTNAME, dupwarn, DSET, __FUNCTION__, __LINE__);
		EVX2 = PBCLOSE =1;
	}
//PC=kDDD/
	else if (lcoden[0] == FC_STROBEOFF && lcoden[1] == FC_DRIVEDATA
			&& lcoden[2] == FC_DRIVEDATA && lcoden[3] == FC_DRIVEDATA) {
		cellinfo[cellcnt].problemtype = PT_CLOSEOPEN;
		fprintf(fpstatus,
				"FOUND [WFM:%s CYLTBL:%s DUPEWARN:%s]%d STROBEOFF-DRIVEDATA-DRIVEDATA-DRIVEDATA [%s,%d] needs multiwindow pattern fixup2\n",
				field[0][0], GCTNAME, dupwarn, DSET, __FUNCTION__, __LINE__);
		if (EVX2==0 || PBCLOSE == 0) fprintf(fperrors,
				"FOUND [WFM:%s CYLTBL:%s DUPEWARN:%s]%d STROBEOFF-DRIVEDATA-DRIVEDATA-DRIVEDATA [%s,%d] needs multiwindow pattern fixup2\n",
				field[0][0], GCTNAME, dupwarn, DSET, __FUNCTION__, __LINE__);
		if (EVX2==0 || PBCLOSE == 0) fprintf(stderr,
				"\nFOUND [WFM:%s CYLTBL:%s DUPEWARN:%s]%d STROBEOFF-DRIVEDATA-DRIVEDATA-DRIVEDATA [%s,%d] needs multiwindow pattern fixup2\n",
				field[0][0], GCTNAME, dupwarn, DSET, __FUNCTION__, __LINE__);
		EVX2 = PBCLOSE =1;
	}
//=========================
	else {
		fprintf(fperrors,
				"FOUND [WFM:%s CYLTBL:%s DUPEWARN:%s]%d undecoded edge[%s] [%s,%d]\n",
				field[0][0], GCTNAME, dupwarn, DSET, find, __FUNCTION__, __LINE__);
		fprintf(fpstatus,
				"FOUND [WFM:%s CYLTBL:%s DUPEWARN:%s]%d undecoded edge[%s] [%s,%d]\n",
				field[0][0], GCTNAME, dupwarn, DSET, find, __FUNCTION__, __LINE__);
		fprintf(stderr,
				"\nFOUND [WFM:%s CYLTBL:%s DUPEWARN:%s]%d undecoded edge[%s] [%s,%d]\n",
				field[0][0], GCTNAME, dupwarn, DSET, find, __FUNCTION__, __LINE__);
		exit(1);
	}
	return (0);
}
