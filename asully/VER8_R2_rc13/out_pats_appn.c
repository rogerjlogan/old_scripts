/* output patterns appn_out_pats.c */
/* output_dpm(); */
/* output_cpm(); */
/* output_cpm_dpm(); */

#include <stdio.h>
#include <strings.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "includes_appn.h"
#include "chksum.cksum"

static int beginC = 0;
static int RPTC = 0;

int output_dpm(int *SUPER_CNT, struct LOOP_LINES *SUPER)
{
	int i, DPMexiti, DPMexitlvl, lvl, cc, firstbegin;
	firstbegin = lvl = 0;
	cc = 1;
	for (i = 0; i < *SUPER_CNT; i++) {
		while (SUPER[i].dummy && i < *SUPER_CNT) {
			fprintf(fpout1, "{%s !DPMd!}\n", SUPER[i].comment);
			i++;
		}
		if (SUPER[i].label[0] != '\0') {
			fprintf(fpout1, "$%s\n", SUPER[i].label);	/* this is base level labels */
		}
		if (SUPER[i].shutdownvect) {
			if (SUPER[i].begin == 1)
				fprintf(fpout1, "{SHUTDOWN_B[%s]%d:%s \"%s\"}\n",
						infile_orig, SUPER[i].shutdownvect,
						SUPER[i].vector, SUPER[i].comment);
			else if (SUPER[i].end == 1)
				fprintf(fpout1, "{SHUTDOWN_E[%s]%d:%s \"%s\"}\n",
						infile_orig, SUPER[i].shutdownvect,
						SUPER[i].vector, SUPER[i].comment);
			else
				fprintf(fpout1, "{SHUTDOWN__[%s]%d:%s \"%s\"}\n",
						infile_orig, SUPER[i].shutdownvect,
						SUPER[i].vector, SUPER[i].comment);
		}
		else if (SUPER[i].repeatcnt > 0) {
			/* need to process this first in case its a repeat nnn begin on same line */
//         fprintf(fpout1,"{REPEAT}\n");
			out_rpt_dpm(SUPER, SUPER[i].repeatcnt, i, lvl, &DPMexiti, &DPMexitlvl, &cc);
			i = DPMexiti;
		}
		else if (SUPER[i].begin == 1) {	/* loop */
//         fprintf(fpout1,"{BEGIN}\n");
			if (firstbegin == 0) {
				firstbegin = 1;
				beginC++;
				lvl++;			/* need this for the pattern start */
				fprintf(fpout1, "begin\n");
				continue;
			}
			out_begin_dpm(SUPER, i, lvl, &DPMexiti, &DPMexitlvl, &cc);
			i = DPMexiti;
			lvl = DPMexitlvl;
		}
		else if (SUPER[i].end == 1 && lvl == 1) {	/* end main */
			lvl--;
			fprintf(fpout1, "end\n");
			continue;
		}
		else if (SUPER[i].VectorType == VT_SET) {
			fprintf(fpout1, "%s {%s !nSETS!}\n", SUPER[i].vector, SUPER[i].comment);
			fprintf(stdout, "****[%d]%s {%s !nSETS!}\n",i, SUPER[i].vector, SUPER[i].comment);
		}
		else if (SUPER[i].VectorType == VT_VECTOR) {
			fprintf(fpout1, "%s {VN%dVC%d %s !DPMv!}\n", SUPER[i].vector,
					SUPER[i].vc, cc, SUPER[i].comment);
			cc++;
		}
	}
	/* can't close fpout1 here since it gets called by out_cpm_dpm(), close in main or in cpm_dpm */
	fflush(fperrors);
	fflush(fpstatus);
	return (cc);
}

int out_rpt_dpm(struct LOOP_LINES *SUPER, int rpt, int at, int lvl,
				int *exitat, int *exitlvl, int *cc)
{
	int i, Rexitat, Rexitlvl;
	if (SUPER[at].repeatcnt < 2) {
		fprintf(stderr, "REPEAT[%d] misdirected![%s]\n", rpt, infile_orig);
		fprintf(fperrors, "REPEAT[%d] misdirected![%s]\n", rpt, infile_orig);
	}
	RPTC++;
//   fprintf(fpout1,"REPEAT#%d,LN%d\n",RPTC,at+1);
	/* the following will validate there isn't a begin on the repeat line and move to the next line */
	/* if the begin is on the same line then don't advance! 08/27/08 */
	if (SUPER[at].begin == 0) at++;			/* at comes in pointing at the repeat */
	while (SUPER[at].dummy) {
		fprintf(fpout1, "{%s !RPTDPMd!}\n", SUPER[at].comment);
		at++;
	}
	if (SUPER[at].label[0] != '\0') {
		fprintf(fpout1, "$%s\n", SUPER[at].label);	/* this is base level labels */
	}
	if (SUPER[at].begin == 1) {	/* loop */
//      fprintf(fpout1,"PRINT BLOCK %d times\n",rpt);
		for (i = 1; i <= rpt; i++) {
			out_begin_dpm(SUPER, at, lvl, &Rexitat, &Rexitlvl, cc);
		}
		if (SUPER[Rexitat].end != 1) {
			fprintf(stderr, "rpt[%d]-begin-end loop did not exit on end!\n", rpt);
			fprintf(fperrors, "rpt[%d]-begin-end loop did not exit on end!\n", rpt);
		}
		at = Rexitat;			/* this will point at the end */
	}
	else if (SUPER[at].VectorType == VT_VECTOR) {
		for (i = 1; i <= rpt; i++) {
			fprintf(fpout1, "%s {VN%dVC%d RPTDPM:%dof%d %s}\n",
					SUPER[at].vector, SUPER[at].vc, *cc, i, rpt, SUPER[at].comment);
			(*cc)++;
		}
	}
	else if (SUPER[at].VectorType == VT_SET) {
		for (i = 1; i <= rpt; i++) {
			fprintf(fpout1, "%s {VN%dVC%d RPTDPM:%dof%d %s}\n",
					SUPER[at].vector, SUPER[at].vc, *cc, i, rpt, SUPER[at].comment);
			(*cc)++;
		}
	}
	else {
		fprintf(fpout1, "{%s!RPTDPMnotV!}\n", SUPER[at].comment);
	}
	*exitat = at;
	*exitlvl = lvl;
//   fprintf(fpout1,"DONERPT%d,LN%d,LVL%d\n",rpt,*exitat+1,*exitlvl);
	return (0);
}

int out_begin_dpm(struct LOOP_LINES *SUPER, int at, int lvl, int *exitat,
				  int *exitlvl, int *cc)
{
	int i, Bexitat, Bexitlvl, begin, end, count;	/* FIXME: APS need to add label support */
	if (SUPER[at].begin != 1) {
		fprintf(stderr, "BEGIN[%d,%d] misdirected!\n", lvl, at);
		fprintf(fperrors, "BEGIN[%d,%d] misdirected!\n", lvl, at);
	}
	beginC++;
	if (SUPER[at].label[0] != '\0') {
		fprintf(fpout1, "$%s\n", SUPER[at].label);	/* this is base level labels */
	}
//   fprintf(fpout1,"BEGINC%d,LN%d\n",beginC,at+1);
	lvl++;
	begin = at;
	end = SUPER[at].beginpointtoend;
	count = end - begin;
	for (i = 1; i < count; i++) {	/* get past current begin! */
		if (SUPER[at + i].dummy) {
			fprintf(fpout1, "{%s !BEGINDPMc!}\n", SUPER[at + i].comment);
		}
		if (SUPER[at+i].VectorType == VT_SCAN) {
			fprintf(stderr, "SCAN NOT supported in DPM LOOPS...@ %d %d {%s %s %d}\n%s\n", at,i,__FUNCTION__,__FILE__,__LINE__,SUPER[at+i].vector);
			fprintf(fperrors, "SCAN NOT supported in DPM LOOPS...@ %d %d {%s %s %d}\n%s\n", at,i,__FUNCTION__,__FILE__,__LINE__,SUPER[at+i].vector);
			exit(1);
		}
		else if (SUPER[at + i].begin == 1) {	/* loop */
			out_begin_dpm(SUPER, at + i, lvl, &Bexitat, &Bexitlvl, cc);
			i = Bexitat - begin + 1;
			if (lvl != Bexitlvl) {
				fprintf(stderr, "ERROR:LEVEL Changed at %d[%s\"%s\"]\n",
						at + i, SUPER[at + i].vector,
						SUPER[at + i].comment);
				fprintf(fperrors, "ERROR:LEVEL Changed at %d[%s\"%s\"]\n",
						at + i, SUPER[at + i].vector,
						SUPER[at + i].comment);
			}
		}
		else if (SUPER[at + i].repeatcnt > 0) {
			out_rpt_dpm(SUPER, SUPER[at + i].repeatcnt, at + i, lvl, &Bexitat, &Bexitlvl, cc);
			i = Bexitat - begin;
			if (lvl != Bexitlvl) {
				fprintf(stderr, "ERROR:LEVEL Changed at %d[%s\"%s\"]\n",
						at + i, SUPER[at + i].vector,
						SUPER[at + i].comment);
				fprintf(fperrors, "ERROR:LEVEL Changed at %d[%s\"%s\"]\n",
						at + i, SUPER[at + i].vector,
						SUPER[at + i].comment);
			}
		}
		else if (SUPER[at + i].VectorType == VT_VECTOR) {
			fprintf(fpout1, "%s {VN%dVC%d %s !BEGINDPML%d_%d_%d!}\n",
					SUPER[at + i].vector, SUPER[at + i].vc, *cc,
					SUPER[at + i].comment, at, lvl, i);
			(*cc)++;
		}
		else if (SUPER[at + i].VectorType == VT_SET) {
			fprintf(fpout1, "%s {VN%dVC%d %s !BEGINDPML%d_%d_%d!}\n",
					SUPER[at + i].vector, SUPER[at + i].vc, *cc,
					SUPER[at + i].comment, at, lvl, i);
			(*cc)++;
		}
		else {
			fprintf(fpout1, "{%s !BEGINDPM%d_%d!}\n", SUPER[at + i].comment, lvl, i);
		}
	}
	lvl--;
	*exitlvl = lvl;
	*exitat = end;				/* decided best place to point is the end, so increment in the caller */
//   fprintf(fpout1,"\"DONEBEGIN,LN%d,LVL%d,%s to %s\"\n",*exitat+1,*exitlvl,SUPER[begin].comment,SUPER[end].comment);
	return (0);
}

int output_cpm_dpm(int *SUPER_CNT, struct LOOP_LINES *SUPER, int force_cpm)
{
	int i, j, cc = 0, ccmaj, ccrem, countlines = 0, short_end = 0;
	int match_loop, first = 0;
	int terminate_match_cnt = -1, rpt, lvl = 0;
	int rptendat[4] =	{ -1, -1, -1, -1 };
	int rptbeginN[4] = {	-1, -1, -1, -1};
	char outfilec[200], old[200], new[200];
	FILE *fpout_cpm;
	int table[MX_INSTR], tblvc[MX_INSTR], maxinstr = 0;
	/* first locate the "instructions" */
	if (*SUPER_CNT < 0) {
		fprintf(stderr, "SUPER_CNT[%d]<0\n", *SUPER_CNT);
		exit(1);
	}
	for (i = 0; i < *SUPER_CNT; i++) {
		if (SUPER[i].repeatforever == 1) {
			tblvc[maxinstr] = SUPER[i].vc;
			table[maxinstr++] = i;
		}
		else if (SUPER[i].matchcnt > 0) {
			tblvc[maxinstr] = SUPER[i].vc;
			table[maxinstr++] = i;
		}
		else if (SUPER[i].repeatcnt > 0 && force_cpm) {
			tblvc[maxinstr] = SUPER[i].vc;
			table[maxinstr++] = i;
		}
		if (maxinstr >= MX_INSTR) {
			fprintf(fperrors, "Too many instructions[%d] in pattern[%s]\n", maxinstr, infile_orig);
			fprintf(stderr, "Too many instructions[%d] in pattern[%s]\n", maxinstr, infile_orig);
			exit(1);
		}
	}
	for (i = 0; i < maxinstr; i++) fprintf(fpstatus, "ti[%d]vc[%d]\n", table[i], tblvc[i]);
	sprintf(outfilec, "%s_cpm.proc", infile_base);
	if (NULL == (fpout_cpm = fopen(outfilec, "w"))) {
		fprintf(stderr, "\nFATAL_ERROR:Could not create output file [%s]\n", outfilec);
		fprintf(fperrors, "\nFATAL_ERROR:%s:Could not create output file [%s]\n", progstr, outfilec);
		exit(1);
	}
	/* second push as much as possible before the "instruction" into dpm */
	if ((table[0] > 1 && maxinstr > 0) || force_cpm) {
		short_end = table[0] ;/*APS:02/18/2010 was - 1;  but this was adding an extra vector to the front of the CPM */
		if (tblvc[0] < 16) {
			short_end = 0;
			fprintf(fpstatus, "CPM header short in [%s] so all in CPM\n", infile_orig);
			fprintf(fpout_cpm, "(*-FLAG-This must be a CPM pattern-*)            \n");
			fprintf(fpout_cpm, "{standalone CPM}\n");
		}
		else {
			cc = output_dpm(&short_end, SUPER);
			fprintf(fpout_cpm, "(*-FLAG-This must be a CPM_CALLING_DPM pattern-*)\n");
			fprintf(fpout_cpm, "{CPM calling DPM}\n");
		}
	}
	else {
		fprintf(fpout_cpm, "(*-FLAG-This must be a CPM pattern-*)            \n");
		fprintf(fpout_cpm, "{standalone CPM}\n");
	}
	/* the CPM_CALLING_DPM !MUST! be the first line! */
	fprintf(fpout_cpm, "{-FLAG-preprocessed with %s REV:%2.1f:%s by Anthony Sully compile_date:%s@%s}\n",
			compilestr, REV, progstr, __DATE__, __TIME__);
	fprintf(fpout_cpm, "begin\n");
	for (i = 0; i <= *SUPER_CNT; i++) {
		if (SUPER[i].shutdownvect) {
			if (SUPER[i].begin == 1)
				fprintf(fpout_cpm, "{SHUTDOWN_B[%s]%d:%s \"%s\"}\n",
						infile_orig, SUPER[i].shutdownvect,
						SUPER[i].vector, SUPER[i].comment);
			else if (SUPER[i].end == 1) {
				fprintf(fpout_cpm, "{SHUTDOWN_E[%s]%d:%s \"%s\"}\n",
						infile_orig, SUPER[i].shutdownvect,
						SUPER[i].vector, SUPER[i].comment);
				break;
			}
			else
				fprintf(fpout_cpm, "{SHUTDOWN__[%s]%d:%s \"%s\"}\n",
						infile_orig, SUPER[i].shutdownvect,
						SUPER[i].vector, SUPER[i].comment);
		}
	}
	for (i = short_end; i <= *SUPER_CNT; i++) {	/* i<=table[maxinstr-1] */
//      fprintf(fpout_cpm,"{==%d==}\n",i);
		if (short_end != 0 && first == 0) {	/* if the header is short, keep it all in CPM */
			fprintf(fpout_cpm, "<LDA DPM_%s_begin>\n", infile_base);
			fprintf(fpout_cpm, "<RPT DpmPipeline,SWCDPM>\n");
			if (cc < 65535) fprintf(fpout_cpm, "<RPT %d,SDP>\n", cc - 1);
			else {
				ccmaj = cc / 65535;
				ccrem = cc - ccmaj * 65535;
				for (j = 0; j < ccmaj; j++) {
					fprintf(fpout_cpm, "<RPT %d,SDP>\n", 65535);
					countlines++;
				}
				if (ccrem > 0) fprintf(fpout_cpm, "<RPT %d,SDP>\n", ccrem);
			}
			fprintf(fpout_cpm, "<SWCCPM>\n");	/* got to have this because we might switch */
			countlines += 4;
			first = 1;
		}
		else {					/* short, FIXME: APS need to deal with repeats, and repeat begins here, and shutdowns */
			if (first == 0) {	/* only output the header the first time */
				for (j = 0; j < table[0]; j++) {
					if (SUPER[j].repeatcnt > 1) {
						fprintf(fpout_cpm, "repeat %d {%s}\n", SUPER[j].repeatcnt, SUPER[j].comment);
						countlines++;
					}
					else if (SUPER[j].VectorType == VT_VECTOR && SUPER[j].shutdownvect == 0) {
						fprintf(fpout_cpm, "%s {%s}\n", SUPER[j].vector, SUPER[j].comment);
						countlines++;
					}
					else if (SUPER[j].VectorType == VT_SET) {
						fprintf(fpout_cpm, "%s {%s}\n", SUPER[j].vector, SUPER[j].comment);
					}
					else if (SUPER[j].comment[0] != '\0') {
						fprintf(fpout_cpm, "{%s}\n", SUPER[j].comment);
					}
				}
				first = 1;
				i = j;
			}					/* end first */
		}
		if (i == terminate_match_cnt && match_loop != -1) {
			fprintf(fpout_cpm, "%s {%s}\n", SUPER[i].vector, SUPER[i].comment);
			fprintf(fpout_cpm, "<COND NZC4>{1}\n");
			fprintf(fpout_cpm, "<DC4,CJMP .+4>{2}\n");
			fprintf(fpout_cpm, "<MODE(IFAIL OFF,TCI OFF)>{3}\n");
			fprintf(fpout_cpm, "<STOP FAIL>{4 NEED A REAL STROBING VECTOR loop exit pass/fail}\n");	/* for fail to match test */
			fprintf(fpout_cpm, "<JMP .+4>{5 After strobing fail vector}\n");
			fprintf(fpout_cpm, "<RPT MatchPipeline>{6}\n");
			fprintf(fpout_cpm, "<COND SEQF>{7}\n");
			fprintf(fpout_cpm, "<CJMP %s_M%d>{8}\n", infile_base, match_loop);	/* FIXME: APS fix this in VCP_NEW as well */
			fprintf(fpout_cpm, "<MODE(IFAIL OFF,TCI OFF)>{9}\n");
			countlines += 10;
			terminate_match_cnt = match_loop = -1;
		}
		else if (i == rptendat[lvl]) {
			fprintf(fpout_cpm, "<COND NZC%d>\n", lvl);
			fprintf(fpout_cpm, "<DC%d,CJMP %s_RL%d>\n", lvl, infile_base, rptbeginN[lvl]);
			countlines += 2;
			rptendat[lvl] = -1;
			lvl--;
			if (lvl < 0) {
				lvl = 0;
				fprintf(fpstatus, "Over exited the loop in [%s] at %d\n", infile_orig, i);
			}
		}
		else if (SUPER[i].repeatforever == 1) {
			fprintf(stdout,"REPEAT FOREVER *********************************\n");
			/* The DPM pattern original gets label: %s_begin in the .proc file */
			/* The .proc files for CPM & DPM get swapped so CPM is the master */
			/* VCP will fix the label to be DPM_%s_begin, thus.... */
			fprintf(fpout_cpm, "<FLAG (CONT ON)>\n");
			i++;				/* move past the repeat forever statement */
			while (SUPER[i].dummy) {
				fprintf(fpout_cpm, "{%s !CPMd!}\n", SUPER[i].comment);
				i++;
			}
			if (SUPER[i].begin == 1) {	/* its a repeat forever loop */
				fprintf(fpout_cpm, "$%s_RF%d\n", infile_base, i);
				for (j = i; j < SUPER[i].beginpointtoend; j++) {
					if (SUPER[j].VectorType == VT_VECTOR) {
						fprintf(fpout_cpm, "%s {CPMDPMrvb %s}\n", SUPER[j].vector, SUPER[j].comment);
						countlines++;
					}
				}
				fprintf(fpout_cpm, "<COND CONT>\n");
				fprintf(fpout_cpm, "<CJMP %s_RF%d>\n", infile_base, i);
				i = j;
			}
			else if (SUPER[i].VectorType == VT_VECTOR || SUPER[i].VectorType == VT_SET) {	/* its a repeat forever vector */
				fprintf(fpout_cpm, "%s {CPMDPMrfv %s}\n", SUPER[i].vector, SUPER[i].comment);
				fprintf(fpout_cpm, "<COND CONT>\n");
				fprintf(fpout_cpm, "<CJMP .-2>\n");
				countlines += 3;
			}
		}
		else if (SUPER[i].matchcnt != 0) {
			fprintf(fpout_cpm, "<LC4 %d>\n", SUPER[i].matchcnt - 1);
			fprintf(fpout_cpm, "<MODE(IFAIL ON,TCI ON)>\n");
			fprintf(fpout_cpm, "$%s_M%d\n", infile_base, i);
			match_loop = i;
			fprintf(fpout_cpm, "<FLAG(SEQF OFF)>\n");
			countlines += 3;
			/* need to determine if repeat vector or begin loop */
			if (SUPER[i].begin) {	/* its a begin loop start on the match line */
				/* until pass; syntax parsed out by align_until function */
				terminate_match_cnt = SUPER[i].beginpointtoend;
				fprintf(fpout_cpm, "{terminate at %d to %d}\n", i, terminate_match_cnt);
				/* until end */
			}
			else {
				i++;
				while (SUPER[i].dummy) {
					fprintf(fpout_cpm, "{%s !MATCHd!}\n", SUPER[i].comment);
					i++;
				}
				if (SUPER[i].begin) {	/* its a begin loop start but not on match line */
					/* until pass; syntax parsed out by align_until function */
					terminate_match_cnt = SUPER[i].beginpointtoend;
					fprintf(fpout_cpm, "{terminate2 at %d to %d}\n", i, terminate_match_cnt);
					/* until end */
				}
				else if (SUPER[i].VectorType == VT_VECTOR) {	/* repeat vector */
					fprintf(fpout_cpm, "%s {%s}\n", SUPER[i].vector, SUPER[i].comment);
					fprintf(fpout_cpm, "<COND NZC4>{1A}\n");
					fprintf(fpout_cpm, "<DC4,CJMP .+4>{2A}\n");
					fprintf(fpout_cpm, "<MODE(IFAIL OFF,TCI OFF)>{3A}\n");
//               fprintf(fpout_cpm,"%s <STOP FAIL>{ADDED BY CONVERSION for pass/fail test %s}\n",SUPER[i].vector,SUPER[i].comment);/* for fail to match test */
					fprintf(fpout_cpm, "<STOP FAIL>{4A ADDED BY CONVERSION for pass/fail test %s}\n", SUPER[i].comment);	/* for fail to match test */
					fprintf(fpout_cpm, "<JMP .+4>{5A After failing strobe vector}\n");
					fprintf(fpout_cpm, "<RPT MatchPipeline>{6A}\n");
					fprintf(fpout_cpm, "<COND SEQF>{7A}\n");
					fprintf(fpout_cpm, "<CJMP %s_M%d>{8A}\n", infile_base, match_loop);	/* FIXME: APS fix this in VCP_NEW as well */
					fprintf(fpout_cpm, "<MODE(IFAIL OFF,TCI OFF)>{9A}\n");
					countlines += 10;
					terminate_match_cnt = match_loop = -1;
				}
				else {			/* uh oh  not begin or vector???? */
					fprintf(fpstatus, "Match without vector or begin in [%s][%d]\n", infile_orig, i);
					fprintf(stderr, "Match without vector or begin in [%s][%d]\n", infile_orig, i);
				}
			}
		}						/* end match look */
		else if (SUPER[i].repeatcnt > 1) {	/* cpm repeat */
			rpt = SUPER[i].repeatcnt;
			while (SUPER[i].dummy) {
				fprintf(fpout_cpm, "{%s !REPEATd!}\n", SUPER[i].comment);
				i++;
			}
			if (SUPER[i].begin) {	/* its a repeat nnn begin on the same line */
				lvl++;
				fprintf(fpout_cpm, "<LC%d %d>\n$%s_RL%d", lvl, rpt - 1, infile_base, i);
				rptendat[lvl] = SUPER[i].beginpointtoend;
				rptbeginN[lvl] = i;
				countlines++;
			}
			else {
				i++;			/* move past the repeat line */
				if (SUPER[i].begin) {	/* its a repeat begin */
					lvl++;
					fprintf(fpout_cpm, "{repeat->begin}\n<LC%d %d>\n$%s_RL%d\n",
							lvl, rpt - 1, infile_base, i);
					rptendat[lvl] = SUPER[i].beginpointtoend;
					rptbeginN[lvl] = i;
					countlines++;
				}
				if (SUPER[i].VectorType == VT_VECTOR) {	/* its just a repeat */
					lvl++;
					/* try polaris repeat statement 'rpt' times */
					fprintf(fpout_cpm, "repeat %d\n", rpt);
					fprintf(fpout_cpm, "%s {%s}\n", SUPER[i].vector, SUPER[i].comment);
					countlines++;
//               fprintf(fpout_cpm,"<LC%d %d>\n$%s_RL%d\n",lvl,rpt-1,infile_base,i);
//               fprintf(fpout_cpm,"%s {%s}\n",SUPER[i].vector,SUPER[i].comment);
//               fprintf(fpout_cpm,"<COND NZC%d>\n<DC%d,CJMP .-2>\n",lvl,lvl);
					lvl--;
				}
			}
		}						/* end cpm repeat look */
		else {
			if (SUPER[i].VectorType == VT_VECTOR) {
				fprintf(fpout_cpm, "%s {X%s}\n", SUPER[i].vector, SUPER[i].comment);
				countlines++;
			}
			else if (SUPER[i].comment[0] != '\0') {
				fprintf(fpout_cpm, "{%s}\n", SUPER[i].comment);
			}
		}
	}							/* end main for */
//   for (i=i;i<*SUPER_CNT;i++) {/* FIXME: APS need to check for repeats */
//      if (SUPER[i].VectorType==VT_VECTOR || SUPER[i].VectorType==VT_SET) {
//         fprintf(fpout_cpm,"%s {CPMDPMf %s}\n",SUPER[i].vector,SUPER[i].comment);
//         countlines++;
//         }
//      else {
//         fprintf(fpout_cpm,"{%s}\n",SUPER[i].comment);
//         countlines++;
//         }
//      }
	fprintf(fpstatus, "CPM SIZE of [%s]=[%d]\n", infile_base, countlines);
	chksumout(fpout_cpm, "(*", "*)");
	fprintf(fpout_cpm, "end;\n");
	fclose(fpout_cpm);
	chksumout(fpout1, "(*", "*)");
	fprintf(fpout1, "end;\n");
	fclose(fpout1);
	/* make the DPM => infile_base_DPM */
	if (short_end != 0) {
		sprintf(old, "%s.proc", infile_base);
		sprintf(new, "DPM_%s.proc", infile_base);
		if (rename(old, new)) {
			fprintf(fperrors, "Error renaming [%s] to [%s]\n", old, new);
			fprintf(stderr, "Error renaming [%s] to [%s]\n", old, new);
		}
	}
	else {
		sprintf(old, "%s.proc", infile_base);
		if (remove(old)) {
			fprintf(fperrors, "Error removing unused DPM [%s]\n", old);
			fprintf(stderr, "Error removing unused[%s] \n", old);
		}
	}
	/* make the CPM => infile_base_proc */
	sprintf(old, "%s_cpm.proc", infile_base);
	sprintf(new, "%s.proc", infile_base);
	if (rename(old, new)) {
		fprintf(fperrors, "Error renaming [%s] to [%s]\n", old, new);
		fprintf(stderr, "Error renaming [%s] to [%s]\n", old, new);
	}
	fflush(fperrors);
	fflush(fpstatus);
	return (i);
}								/* output_cpm_dpm */

int output_scan(char *outfile1, char *CYCLETBL, int *SUPER_CNT, struct LOOP_LINES *SUPER) {
	char tempstr[READLINELEN + 1];
   int DPMexiti, DPMexitlvl, lvl, cc, firstbegin;
	int i;
	firstbegin = lvl = 0;
	fprintf(fpout1, "(*-FLAG-This must be a SCAN pattern-*)\n");
	fprintf(fpstatus, "FYI:%s:AUTO LAUNCHING vector_convert_scan on pattern[%s]\n", progstr, outfile1);
	fprintf(stderr, "FYI:AUTO LAUNCHING vector_convert_scan on pattern[%s]\n", outfile1);
	fflush(fperrors);
	for (i = 0; i < *SUPER_CNT; i++) {
		if (SUPER[i].repeatcnt > 0) {
			/* need to process this first in case its a repeat nnn begin on same line */
//         fprintf(fpout1,"{REPEAT}\n");
			out_rpt_dpm(SUPER, SUPER[i].repeatcnt, i, lvl, &DPMexiti, &DPMexitlvl, &cc);
			i = DPMexiti;
		}
		else if (SUPER[i].VectorType == VT_SCAN) {
			fprintf(fpout1, "%s\n", SCANV[SUPER[i].scannum].vector);
			}
		else if (SUPER[i].VectorType == VT_SCANCONTROL) {
			fprintf(fpout1, "%s\n", SUPER[i].vector);
			}
		else if (SUPER[i].VectorType == VT_VECTOR) {
			fprintf(fpout1, "%s\n", SUPER[i].vector);
			}
		else if (SUPER[i].VectorType == VT_SET) {
			fprintf(fpout1, "%s\n", SUPER[i].vector);
			}
		else if (SUPER[i].begin > 0) {
			fprintf(fpout1, "%s\n", "begin");
			}
		else if (SUPER[i].end > 0) {
			fprintf(fpout1, "%s\n", "end;");
			}
		else if (SUPER[i].shutdownvect) {
			if (SUPER[i].begin == 1)
				fprintf(fpout1, "{SHUTDOWN_B[%s]%d:%s \"%s\"}\n",
						infile_orig, SUPER[i].shutdownvect,
						SUPER[i].vector, SUPER[i].comment);
			else if (SUPER[i].end == 1)
				fprintf(fpout1, "{SHUTDOWN_E[%s]%d:%s \"%s\"}\n",
						infile_orig, SUPER[i].shutdownvect,
						SUPER[i].vector, SUPER[i].comment);
			else
				fprintf(fpout1, "{SHUTDOWN__[%s]%d:%s \"%s\"}\n",
						infile_orig, SUPER[i].shutdownvect,
						SUPER[i].vector, SUPER[i].comment);
		}
	}
	chksumout(fpout1, "(*", "*)");
	fclose(fpout1);
	/* careful, these are free'd in the main routine if its parallel */
	free(SUPER);
	free(SCANV);

	fflush(fperrors);
	fflush(fpstatus);
	sprintf(tempstr, "%s %s %s", VECTOR_CONVERT_SCAN, outfile1, CYCLETBL);
	fprintf(stderr, "FYI:[%s]\n", tempstr);
	system(tempstr);			/* call VCS */
	fprintf(fpstatus, "Back from VCS \n");
	return (0);
}

int output_scan_cpm(char *outfile1, char *CYCLETBL, int *SUPER_CNT, struct LOOP_LINES *SUPER) {
	char tempstr[READLINELEN + 1];
	int i, repeatpending=0,repeatwhere=0;
	fprintf(fpout1, "(*-FLAG-This must be a SCAN pattern-*)\n");
	fprintf(fpstatus, "FYI:%s:AUTO LAUNCHING vector_convert_scan on pattern[%s]\n", progstr, outfile1);
	fprintf(stderr, "FYI:AUTO LAUNCHING vector_convert_scan on pattern[%s]\n", outfile1);
	fflush(fperrors);
	for (i = 0; i < *SUPER_CNT; i++) {
		if (SUPER[i].VectorType == VT_SCAN) {
			fprintf(fpout1, "%s\n", SCANV[SUPER[i].scannum].vector);
			}
		else if (SUPER[i].repeatforever) {
			fprintf(fpout1,"repeat forever\n");
			repeatpending=1;
			repeatwhere=i;
			}
		else if (SUPER[i].VectorType == VT_SCANCONTROL) {
			fprintf(fpout1, "%s\n", SUPER[i].vector);
			}
		else if (SUPER[i].VectorType == VT_VECTOR) {
			if (repeatpending) {
				fprintf(fpout1,"\"COND CONT\"\n");
				fprintf(fpout1,"\"FLAG(CONT ON)\"\n");
				fprintf(fpout1,"\"RF_LBL_%d\"\n",repeatwhere);
				}
			fprintf(fpout1, "%s\n", SUPER[i].vector);
			if (repeatpending) {
				fprintf(fpout1,"\"CJMP .\"\n");
				repeatpending = repeatwhere =0;
				}
			}
		else if (SUPER[i].VectorType == VT_SET) {
			fprintf(fpout1, "%s\n", SUPER[i].vector);
			}
		else if (SUPER[i].begin > 0) {
			fprintf(fpout1, "%s\n", "begin");
			if (repeatpending==1) {
				fprintf(fpout1,"<COND CONT>\n");
				fprintf(fpout1,"<FLAG(CONT ON)>\n");
				fprintf(fpout1,"<RF_LBL_%d>\n",repeatwhere);
				}
			}
		else if (SUPER[i].end > 0) {
			fprintf(fpout1, "%s\n", "end;");
			if (repeatpending==1) {
				fprintf(fpout1,"<CJMP RF_LBL_%d>\n",repeatwhere);
				repeatpending = repeatwhere =0;
				}
			}
		else if (SUPER[i].shutdownvect) {
			if (SUPER[i].begin == 1)
				fprintf(fpout1, "{SHUTDOWN_B[%s]%d:%s \"%s\"}\n",
						infile_orig, SUPER[i].shutdownvect,
						SUPER[i].vector, SUPER[i].comment);
			else if (SUPER[i].end == 1)
				fprintf(fpout1, "{SHUTDOWN_E[%s]%d:%s \"%s\"}\n",
						infile_orig, SUPER[i].shutdownvect,
						SUPER[i].vector, SUPER[i].comment);
			else
				fprintf(fpout1, "{SHUTDOWN__[%s]%d:%s \"%s\"}\n",
						infile_orig, SUPER[i].shutdownvect,
						SUPER[i].vector, SUPER[i].comment);
		}
	}
	chksumout(fpout1, "(*", "*)");
	fclose(fpout1);
	/* careful, these are free'd in the main routine if its parallel */
	free(SUPER);
	free(SCANV);

	fflush(fperrors);
	fflush(fpstatus);
	sprintf(tempstr, "%s %s %s", VECTOR_CONVERT_SCAN_CPM, outfile1, CYCLETBL);
	fprintf(stderr, "FYI:[%s]\n", tempstr);
	system(tempstr);			/* call VCS */
	fprintf(fpstatus, "Back from VCS \n");
	return (0);
}
