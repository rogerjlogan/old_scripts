/* This program is covered by the GNU GPL license. Please see the file: COPYING.gz for the license info. */
/* original author: anthony_sully@ltx.com */

/*  vector_convert_polaris7.c     */
/* May  99 Anthony Sully, LTX Corp: Original file created for C6201 translation */
/* Feb. 00 Anthony Sully, LTX Corp. Enhanced code to deal with waveforms better for C6202 */
/* Oct. 00 Anthony Sully, LTX Corp. Minor tweaks for C6203 */
/* Sept.02 Anthony Sully, LTX Corp. Reorganized code for readability and added enhancements
                                    required for Venus (microcontroller group) translation.
                                    Created input preprocessing program (pre_proc.c) to deal
                                    with the repeat block compression and match loops that
                                    microcontroller group patterns use. This implies that
                                    the translator can now generate dpm and/or cpm patterns
                                    based on the input from pre_proc.c */
/* 09/23/02 Anthony Sully, LTX Corp. Tweaked the character choices to match Dale's choices
                                    for the alternate Dset o/i/l/h */
/* 09/28/02 Anthony Sully, LTX Corp. 1) Added option for removing the input .proc input file
                                    automatically (-r) on success. As a safety feature it
                                    will not delete the file if it contains .vpl
                                    2) Modified program to create a running log file 
                                   'translation_errors.txt' of all this the program is not 
                                    happy about. This file will be created if it does not exist
                                    and appended to if it does exist. It will give the file name
                                    of the offending pattern and the line number of the problem,
                                    if appropriate. This file should be reviewed after translation
                                    completes. 
                                    3) Started adding these comments for rev. information.
                                    4) Modified alias assignments so they are defines for consistency.
                                    5) Added option (-a) to pad with two characters. This is intended
                                    to be used with DUT-to-PM or scope triggers and may be useful for
                                    ADC or Flash testing. This also changes the signal header to
                                    PADSGHDR. 
                                    6) Removed default signal header and default waveformtables as
                                    we are being explicit on each vector anyway. */
/* 10/01/02 Anthony Sully, LTX Corp Changed where the end label is placed for CPM patterns */
/* 10/08/02 Anthony Sully, LTX Corp Found a problem with repeat expansion. The max repeat prints
                                    were not printing although the remainder was. Turned out that
                                    the exceeding max repeat code was in the wrong place (although
                                    the code itself was correct. Tried one pattern that had this
                                    problem and it did seem to fix the failure. Again, this is in
                                    the nasty code so be careful if you touch it!!!! Updated to
                                    vector_convert_polaris3.c */
/* 10/09/02 Anthony Sully, LTX Corp A similar problem was found where the last vector was not printing
                                    its repeat. This was fixed so the RPT would be printed and if the
                                    repeat exceeded the max repeat the max repeats would be printed
                                    then the end label then the remainder RPT. This was also fixed
                                    for the CPM portion of the code. */
/* 10/12/02 Anthony Sully, LTX Corp. Created new version 4 which includes the capability to
                                     create a CPM calling DPM pattern if a match is found and
                                     the vectors before this vector total at least 100. This
                                     adds complexity but will help in reducing CPM usage which
                                     appears to be a big issue. If this situation is setup
                                     by pre_proc4.c then vector_convert_polaris4.c knows to
                                     translate the DPM_%s file first to get the number of
                                     vectors for DPM call. 
                                     After translating the DPM it will rescan the DPM_%s.proc file
                                     to get the MSET/DSET information and then proceed to generate
                                     the CPM pattern. Similar modifications where also made
                                     to pre_proc4.c to setup this option. All that the user needs
                                     to do is add the DPM_%s patterns to the PatternMap.
                                     Modified the name of the uncompressed file to use the name of
                                     the source file with a .tmpgunzip tacked on the end. This
                                     makes the file unique.
                                     Also fixed a problem where the last vector of a DPM pattern
                                     was being repeated, once with a RPT and once without.
                                     Modified final print to indicate what type of vectors 
                                     (CPM or DPM) were generated when giving the count. */
/* 10/18/02 Anthony Sully, LTX Corp. (rev.5) Added two new options (-o and -O) which will try to
                                     optimize the CPM microinstructions and waveformtable references.
                                     (-O is for 'fixing' uncompressed pre-existing cpm patterns and
                                     can also be used on scan cpm patterns to remove the HOLD_CYCLE
                                     wfts). The waveformtable ref. optimization finds the first
                                     non-DEF_WFT, non-ScanCycle, and non-HOLD_CYCLE waveformtable
                                     ref. and replaces any of the DEF_WFT or HOLD_CYCLE references
                                     with that. The general optimization tries to reduce redundant CPM
                                     vectors by replacing small loops with RPTs and moving
                                     microinstructions onto real vectors. The idea was to reduce
                                     problems in match loops not to necessarily reduce the size of CPM.
                                     It also attempts to preserve the comments in the right place. At
                                     the moment it preserves both the original pattern and the new
                                     pattern. The original will be moved to __patternname.evo (and
                                     compressed if the VCP was given the compressed option). Also,
                                     fixed the program so sources can be located in a remote secure
                                     directory. All new files will be created in the local directory. */
/* 10/27/02 Anthony Sully, LTX Corp. Undefined code for RPTP optimization as it does not work correctly
                                     unless the pipeline is pre-filled with fails. */
/* 11/02/02 Anthony Sully, LTX Corp. Fixed compile script and includes so date can be brought in with
                                     gcc or cc */
/* 01/25/03 Anthony Sully, LTX Corp. Modified CPM pattern generation: If CPM pattern has only RPT microinstructions
                                     in the first MAXCPMTODPMLINES then that many will be buffered into DPM memory.
                                     Set up the CPM to call those DPM vectors. Separated MAXCPMTODPMLINES and
                                     MAXCPMOPTLINES. Now upto MAXCPMOPTLINES(1000) vectors can be optimized in dpm.
                                     Vectors upto the first non-DPM microinstruction will be buffered in blocks of
                                     MAXCPMTODPMLINES(100). Separating them gets better compression. Fixed various
                                     subtle problems with CPM patterns (pass through of end;, labels with negative
                                     numbers etc, (some of which was actually fixed in pre_proc6.c).
                                     Updated vector_convert_polaris to rev.6 */
/* 01/29/03 Anthony Sully, LTX Corp. Fixed comment close search in optimize routine to truncate at the end of the
                                     string if the comment did not close due to a long comment */
/* 03/10/03 Anthony Sully, LTX Corp. Modified error messages to give clues as to what happened. There are now four
                                     classes of ERRORS: 
                                     FATAL_ERRORS -- cause immediate exit of program (usually file problems)
                                     BAD_ERRORS -- fatal errors that could produce corrupted output files
                                     NON_FATAL_ERRORS -- errors that generate files with useful output
                                     FYI -- informational warnings. */
/* 03/29/03 Anthony Sully, LTX Corp. Added optimization for CJMP with previous vector RPT added GNU GPL license info.
                                     Found an issue with optimization where if the pattern already had
                                     CPM_CALLING_DPM and then decided that it might be able to optimize it could
                                     damage the original DPM pattern. To fix this I now keep the original DPM
                                     as DPM_ and the DPM optimization happen in DPMO_ (this was noticed in 
                                     venus:DPM_HET_PROG_PSA.vpl) Added translation of shutdown vectors. Due to the
                                     fact that these vectors are not usually needed the translated vectors are written
                                     to the fperrors file (this is also because this file has global visibility).
                                     Added username, hostname, and pwd to pattern header.
                                     Changed date get to 'C' functions instead of unix date. Modified CJMP optimization
                                     to not care whether there was a DC4 or not. This would fix issues if continuous
                                     patterns were used or if another. Increased the size of printhold in
                                     the outputvector function to allow for large repeat expansions. */

/* 04/10/03 Anthony Sully, LTX Corp. Fixed problems with DPM_COUNT so the filename is now unique */
/* 05/05/03 Anthony Sully, LTX Corp. Fixed problem with optimization where the DC?,CJMP optimization was taking
                                     precedence over the CJMP .-1 optimization because the DC? was not looked for.
                                     Added the DC? part of the search back in and this fixed the venus haltpat
                                     problem. This then brought up the fact that if there is a .-anything it
                                     should be optimized as well (the reason I took out the DC4 part). Fixed this
                                     as well. */

/* 09/24/03 Anthony Sully, LTX Corp. Added support for user defined signal header (in cycletbl_mod.mod2),
                                     gct_gen_mod2. This is needed because some devices may have patterns with
                                     different widths. Added code to check that the cycletbl file has the same
                                     number of pins as the polaris pattern, exit if not the same. Same update
                                     to vector_convert_scan as well. Also, fixed an issue where a empty line
                                     in a shutdown loop was causing a sigsegv. Turned out a pointer was not
                                     checked against NULL. Added NULL check to all valid strstr and strchr ptr
                                     assignments. */
/* 02/25/04 Anthony Sully, LTX Corp. modified how files are renamed and removed to use 'C' calls instead of system() */

/* 03/23/04 Anthony Sully, LTX Corp. added some error messages for rename() and remove() files */

/* 07/26/04 Anthony Sully, LTX Corp. Found issue with commented out match. Comment open gets left pending
                                     in DPM pattern, CPM pattern doesn't know it should be commented. 
                                     Made DPM_COUNT more unique. Added pending comment count to DPM_COUNT file.*/
/* 01/31/05 Anthony Sully, LTX Corp. Based on user input, modified how optimized cpm start label was named.
                                     Originally, the newly optimized start label was $patname_begin_real_st
                                     and the preoptimized label was $patname_begin. NOW: optimized start
                                     label is $patname_begin and the original is $patname_begin_orig. */
/* 02/06/05 Anthony Sully, LTX Corp. Added a line to remove the annoying DpM_CoUnT_* files. Added warning for files
                                     that don't contain enough vectors and cycles. 
                                     Updated as vector_convert_polaris9.c */
/* 03/10/05 Anthony Sully, LTX Corp. Pattern from T3 with various issues, some wrong, some suboptimal:
                                     6) Move the status messages to a temp file instead of stdout
                                     See nsf_auto_pre_proc10.c
                                     Bill also identified an issue with T3 where the cpm to dpm optimization
                                     was creating more than 65535 cycles in dpm and the optimization
                                     step wasn't treating large count correctly in cpm. This is fixed. 
                                     Short patterns now pad to meet the 16vector/64cycle rule for HFi and by
                                     extrapolation HF. */
/* 06/05/05 Anthony Sully, LTX Corp. Fixed some minor issues for repeat padding and removed the repeat 512
                                     after the RET as envision now processes this automatically in the thread.
                                     Found some serious flaws (they had been noted already) in the optimization
                                     routines. 1) It was not checking that the CJMP opt3 was jumping to the
                                     immediately previous vector label. 2) It was only optimizing DC4,CJMP not
                                     DC3,CJMP etc. Both of these issues were fixed.
                                     Added the preprocess revision at the top of the file also.
                                     Optimized CPM patterns will have this at the end. Unoptimized CPM will
                                     have it at the top. DPM will also have it at the top. Not sure about
                                     DPMO_%s patterns. (check the cpm in this case!)
                                     Updated to vector_convert_polaris11.c */
/* 07/14/05 Anthony Sully, LTX Corp. Changed behavior on EXCEEDING BUFFER SIZE statements (around line 900).
                                     Previous action was to exit. New action is to empty the buffer and
                                     continue. Updated to rev.12 */
/* 07/27/05 Anthony Sully, LTX Corp. moved the "optpreprocrev" print statement in the CPM optimization 
                                     before the final brace print as enVision appears unhappy with it after
                                     the closing brace. No update to revision.  */
/* 07/30/05 Anthony Sully, LTX Corp. Found errors in the June05 update (for padding out CPM/DPM) that the
                                     repeat count (VNIR) for DPM was off if the last DPM vector had a repeat.
                                     This has been fixed and VNIR is now shown in the comments. Also found
                                     that in the optimization routines it was adding an extra SDP to the
                                     "MODE(IFAIL ON,...)" optimization. Updated to rev.13.0  */

/* 09/14/05 Anthony Sully, LTX Corp. Bumped max GCTs from 30 to 100. Added addition check for is_microinstruction
                                     wft_is_empty. Added preremove of DPM_COUNT file. */

/* 11/20/05 Anthony Sully, LTX Corp. Added command line option to generate dpm count file for cpm requested dpm
                                     translation. Did not bump file rev but did bump internal rev to 14.1 */

/* 05/11/06 Anthony Sully, LTX Corp. Joel had an issue with match loops not getting translated. It turned out
                                     that due to a waveform table being passed in with the microinstruction
                                     it did not recognize it as a microinstruction. I don't quite understand
                                     how anything worked without this fix but the fix was to change the
                                     vector_is_microinstr from wft_is_empty to (0==strcmp(wft,DEF_WFT) ||
                                     wft_is_empty). Updated to 15.0 */
/* 06/29/08 Anthony Sully, LTX Corp. Added support for reading DEBUG_PROC environment variable */
/* 07/21/08 Anthony Sully, LTX Corp. Moved shutdown detect to after the comment check stuff */
/* 08/09/08 Anthony Sully, LTX Corp. New character set, again. New rev.17 Now VCP_NEW */

/* begin main function */

#include <stdio.h>
#include <strings.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include "include_vcp.h"
#include "aliasmap.h"
#include "chksum.cksum"

int main(int argc, char *argv[], char *envp[])
{

/* file variables */
	FILE *fpin1, *fpout1, *fpin2;
	time_t generictime;
	int filein1 = 0, filein2 = 0;
	char infile_local[FILENAMELEN];
	char outfile1[FILENAMELEN];
	char pattern[FILENAMELEN];
/* mode settings */

/* buffers */
	char printstring[MULTILINESIZE + 1], vector[READLINELEN];
	char mod_vector[MULTILINESIZE], pb_vector[MULTILINESIZE];
	char keep_vector[MULTILINESIZE];
	char vector_shutpre[MULTILINESIZE];
	char out_vector1[READLINELEN], comment[MULTILINESIZE + 1], WFT[MAXGCTLEN + 1];
	char DMI[15];				/* only do repeat compression in VX125 mode */
	char readstr[READLINELEN];

	char *MSETPTR, *DSETPTR, *ISETPTR;
/* concaternated strings */

/* control parameters */
	int commentflag, beginflag, vectorflag = 0, commentON, commentcount, newcommentcount, errorflag;
	int notgood = 0, rv, remove_pre = 0, CPMOPTIMIZE = 0, writecount = 0, NO_BACKGROUND_GZIP = 0;
	int maxgctDSET, scnt = 0, dropcnt = 0;

/* temporary variables */
	int i, j;
	long t1, repeatdec, cpmcallingdpmcount, RPTCNT;
	char tempstr[READLINELEN + 1], *ptr, *ptr1, *retptr;
	char *ptrOPEN, *ptrCLOSE;
	char *ptrBV, *ptrEV, *ptrZ, *ptrf;
	char preprocessrev[READLINELEN + 1];
	int vl, foundmdi = 0;
	char muxpins[READLINELEN + 1], muxcopy[READLINELEN + 1], muxcopy1[READLINELEN + 1];
	int muxcount, shutdown_proc;

	for (i=0;i<NUMPINS;i++) {priorstate[i]=FC_NULLEDGE; priorvect[i] = '0';}
	priorstate[i]='\0';
	strcpy(REMAP_DEF_WFT, DEF_WFT);

	if (getenv("DEBUG_PROC") == NULL) DEBUG = FALSE;
	else {
		strcpy(env, getenv("DEBUG_PROC"));
		DEBUG = TRUE;
		fprintf(stderr, "Turning on DEBUG!\n");
	}
	if (getenv("PROC_NO_BACKGROUND_GZIP") != NULL) NO_BACKGROUND_GZIP = 1;

	strcpy(NORMALSGHDR, DFLTSGHDR);
/* command line stuff */
	if (argc > 1) {
		if (strchr((char *) argv[1], '-') != NULL) {
			if (strchr((char *) argv[1], 's') != NULL) QUIET = TRUE;
			if (strchr((char *) argv[1], 'f') != NULL && argc >= 3) filein1 = 1;
			if (strchr((char *) argv[1], 'g') != NULL && argc >= 4) filein2 = 1;
			if (strchr((char *) argv[1], 'z') != NULL) gzip = 1;
			if (strchr((char *) argv[1], 'r') != NULL) remove_pre = 1;
			if (strchr((char *) argv[1], 'o') != NULL) CPMOPTIMIZE = 1;
			if (strchr((char *) argv[1], 'O') != NULL) CPMOPTIMIZE = 2;
			if (strchr((char *) argv[1], 'c') != NULL) writecount = 1;
		}
		else QUIET = 0;
	}
	if (argc == 1) QUIET = 0;
	strcpy(progstr, __FILE__);
	strcpy(datestr, __DATE__);
	strcpy(timestr, __TIME__);
	if (getenv("PWD") != NULL) strcpy(pwd, getenv("PWD"));
	if (getenv("hostname") != NULL) strcpy(hostname, getenv("hostname"));
	else if (getenv("HOSTNAME") != NULL) strcpy(hostname, getenv("HOSTNAME"));
/* the following works for CDE, don't know about others */
	else if (NULL != getenv("SESSION_SVR")) strcpy(hostname, getenv("SESSION_SVR"));
	else strcpy(hostname, "UNKNOWN_HOSTNAME");

	if (getenv("USER") != NULL) strcpy(username, getenv("USER"));
	strcpy(compilestr, argv[0]);
	generictime = time(0);
	strcpy(mydate, ctime(&generictime));
	mydate[strlen(mydate) - 1] = '\0';
	fprintf(stderr, "\n\n\nThis code is supplied under the LTX-Credence Shareware License.\n");
	fprintf(stderr, "Please see the LSLV1.2 file in the document directory for a full text.\n\n\n");
	if (!QUIET) {
		fprintf(stderr, "\n%s: %s\n", progstr, compilestr);
		fprintf(stderr, "%s by Anthony Sully\n", datestr);
		fprintf(stderr, "options are: -s => silent\n");
		fprintf(stderr, "f => pattern file\n");
		fprintf(stderr, "g => GCT mod file\n");
		fprintf(stderr, "z => run gzip on output pattern file\n");
		fprintf(stderr, "r => remove input file (i.e. .proc file)\n");
		fprintf(stderr, "o => post process any CPM patterns to optimize vectors/microinstructions\n");
		fprintf(stderr, "O(caps) => optimize CPM pattern only (no translation)\n");
		fprintf(stderr, "c => write dpm count to a file for cpm processing\n");
		fprintf(stderr, "\nUsage:%s -fzgor PAT.proc cycletbl.mod2\n", compilestr);
	}
	if (NULL == (fperrors = fopen(TRANSLATION_ERRORS, "a"))) {
		fprintf(stderr, "\nFATAL_ERROR:Could not open %s for output\n", TRANSLATION_ERRORS);
		exit(1);
	}
	if (NULL == (fpstatus = fopen(TRANSLATION_STATUS, "a"))) {
		fprintf(stderr, "\nFATAL_ERROR:Could not open %s for output\n", TRANSLATION_STATUS);
		exit(1);
	}

/* open pattern input file */
	if (filein1) strcpy(infile_orig, (char *) argv[2]);
	else {
		fprintf(stderr, "Enter input PATTERN file: ");
		fgets(infile_orig, FILENAMELEN, stdin);
		infile_orig[strlen(infile_orig) - 1] = '\0';	/* fgets gives the \n so clear it!! */
	}
	strcpy(infile_local, infile_orig);
	t1 = 0;
	while (NULL != (ptr = strchr(infile_local, '/'))) {
		t1 = (ptr - infile_local);
		infile_local[t1] = ' ';
		t1++;
	}
	j = 0;
	while (NULL == strchr(". ", infile_local[t1]) && t1 < strlen(infile_local)) pattern[j++] = infile_local[t1++];
	pattern[j] = '\0';
	fprintf(stderr, "\npattern_name:%s\n", pattern);
	if (!QUIET) fprintf(fpstatus, "\npattern_name:%s\n", pattern);

	if (CPMOPTIMIZE == 2) {
		CPM = 2;
		goto CPMOPTIMIZE_ONLY;
	}

	t1 = strlen(infile_local);
	if ((infile_orig[t1 - 3] == '.' && infile_orig[t1 - 2] == 'g' && infile_orig[t1 - 1] == 'z') || (infile_orig[t1 - 2] == '.' && infile_orig[t1 - 1] == 'Z')) {	/* compressed input file */
		if (NULL != (fpin1 = fopen(infile_orig, "r"))) {
			fclose(fpin1);
			sprintf(tempgunzipname, "%s.tmpgunzip", pattern);
			sprintf(tempstr, "gunzip -c %s >%s", infile_orig, tempgunzipname);
			fprintf(fpstatus, "%s\n", tempstr);
			system(tempstr);	/* unzip to temporary file */
			if (NULL == (fpin1 = fopen(tempgunzipname, "r"))) {
				fprintf(stderr, "\nFATAL_ERROR:Uncompressed input file [%s] not found\n", tempgunzipname);
				fprintf(fperrors, "\nFATAL_ERROR:%s:Uncompressed input file [%s] not found\n", progstr, tempgunzipname);
				exit(1);
			}
			gunzip = 1;
		}
		else {
			fprintf(stderr, "\nFATAL_ERROR:Input file [%s] not found\n", infile_orig);
			fprintf(fperrors, "\nFATAL_ERROR:%s:Input file [%s] not found\n", progstr, infile_orig);
			exit(1);
		}
	}
	else {
		if (NULL == (fpin1 = fopen(infile_orig, "r"))) {
			fprintf(stderr, "\nFATAL_ERROR:Input file [%s] not found\n", infile_orig);
			fprintf(fperrors, "\nFATAL_ERROR:%s:Input file [%s] not found\n", progstr, infile_orig);
			exit(1);
		}
	}
	if (!QUIET) fprintf(stderr, "input file1 ok\n");
	infile_local[0] = '\0';
	if (filein2) strcpy(infile_local, (char *) argv[3]);
	else {
		fprintf(stderr, "Enter input gct summary file: ");
		fgets(infile_local, FILENAMELEN, stdin);
		infile_local[strlen(infile_local) - 1] = '\0';	/* fgets gives the \n so clear it!! */
	}
	if (NULL == (fpin2 = fopen(infile_local, "r"))) {
		fprintf(stderr, "\nFATAL_ERROR:Input file [%s] not found\n", infile_local);
		fprintf(fperrors, "\nFATAL_ERROR:%s:Input file [%s] not found\n", progstr, infile_local);
		exit(1);
	}
	if (!QUIET) fprintf(stderr, "input file2 ok\n");

	if (1) {					/* pattern output file */
		sprintf(outfile1, "%s.evo", pattern);
		if (NULL == (fpout1 = fopen(outfile1, "w"))) {
			fprintf(stderr, "\nFATAL_ERROR:Could not open output file [%s] for output\n", outfile1);
			fprintf(fperrors, "\nFATAL_ERROR:%s:Could not open output file [%s] for output\n", progstr, outfile1);
			exit(1);
		}
	}
/* allocate buffer */
	pbset = (PBSET *) calloc(MAXMODGCT, sizeof(PBSET));
	if (pbset  == NULL) {
		fprintf(stderr, "FATAL_ERROR:Could not allocate pbset\n");
		fprintf(fperrors, "FATAL_ERROR:%s:Could not allocate pbset[%s]\n", progstr, infile_orig);
		exit(6);
		}

/* get ALT D-set information */
	maxgctDSET = maxpb = 0;
	muxpins[0] = '\0';
	while (fgets(readstr, READLINELEN - 1, fpin2) != NULL) {
		readstr[strlen(readstr) - 1] = '\0';	/* remove trailing \n */
		if (NULL != strstr(readstr, "#USE_SIGNAL_HEADER:")) {
			strcpy(NORMALSGHDR, readstr + strlen("#USE_SIGNAL_HEADER:"));
			fprintf(fpstatus, "*** USER DEFINED SIGNAL HEADER:<%s> ***\n", NORMALSGHDR);
			continue;
		}
		if (NULL != strstr(readstr, "#USE_PATTERNMODE_EVX2")) {
			EVX2 = 1;
			fprintf(fpstatus, "*** PATTERNMODE EVX2! ***\n");
			fprintf(stdout, "*** PATTERNMODE EVX2! ***\n");
			continue;
		}
		if (NULL != strstr(readstr, "#DISABLED_PATTERNMODE_EVX2")) {
			NOEVX2=1;
			fprintf(fpstatus, "*** waveforms might have needed PATTERNMODE EVX2! ***\n");
			fprintf(stdout, "*** waveforms might have needed PATTERNMODE EVX2! ***\n");
			continue;
		}
		if (NULL != strstr(readstr, "#REMOVE_MUX")) {
			NOMUX = 1;
			fprintf(fpstatus, "*** REMOVING MUXPINS! ***\n");
			fprintf(stdout, "*** REMOVING MUXPINS! ***\n");
			continue;
		}
		if (strstr(readstr,"#PB<") != NULL) {
			/* its a pushback line */
			read_gct_dset_info(readstr,pbset[maxpb].WFTREF,pbset[maxpb].DSET0,pbset[maxpb].DSET1,&maxpb, MAXMODGCT);
			continue;
			}

		if (readstr[0] == '#') continue;			/* comment */
		if (readstr[0] == 'H') continue;			/* nothing to do if hexproc */
		if (readstr[0] == 'F') {
			ptrZ = readstr;
			while (*ptrZ != '\0') {
				if (*ptrZ == '.') dropcnt++;
				ptrZ++;
			}
			fprintf(stdout, "DROPCNT[%d]\n", dropcnt);
			continue;
		}
		if (readstr[0] == 'M') {
			ptr = strchr(readstr, '[');
			strcpy(muxpins, ptr + 1);
			continue;
		}
		if (readstr[0] == 'P') {
			continue;
		}						/* PINGROUP, these are really comments */
		if (readstr[0] == '/') {
			strcpy(pinhead[pinheadcount], readstr);
			pinheadcount++;
			continue;
		}						/* pinheader info */

		read_gct_dset_info(readstr,SETS.GCTMODNAME[maxgctDSET],SETS.VECTMOD[0][maxgctDSET],SETS.VECTMOD[1][maxgctDSET],&maxgctDSET, MAXMODGCT);
	}

fprintf(stderr,"GCT=%d,PB=%d\n",maxgctDSET,maxpb);

	if (muxpins[0] != '\0') {
		for (j = 0; j < maxgctDSET; j++) {
			if (DEBUG)
				fprintf(stdout, "GCTIN0[%s]\nGCTIN1[%s]\nMUXPIN<%s>{%d}\n", SETS.VECTMOD[0][j], SETS.VECTMOD[1][j], muxpins, MOD2_SIZE);
			for (muxcount = i = 0; i < strlen(muxpins); i++) {
				muxcopy[i + muxcount] = SETS.VECTMOD[0][j][i];
				muxcopy1[i + muxcount] = SETS.VECTMOD[1][j][i];
				if (muxpins[i] == 'M') {
					muxcount++;
					if (NOMUX == 0) {
						muxcopy[i + muxcount] = SETS.VECTMOD[0][j][i];
						muxcopy1[i + muxcount] = SETS.VECTMOD[1][j][i];
					}
					else {
						muxcopy[i + muxcount] = FC_NOMUX;
						muxcopy1[i + muxcount] = FC_NOMUX;
						}
				}
			}
			muxcopy[i + muxcount] = '\0';
			muxcopy1[i + muxcount] = '\0';
			strcpy(SETS.VECTMOD[0][j], muxcopy);
			strcpy(SETS.VECTMOD[1][j], muxcopy1);
			if (DEBUG) fprintf(stdout, "GCTOUT0[%s]\nGCTOUT0[%s]\n", SETS.VECTMOD[0][j], SETS.VECTMOD[1][j]);
		}						/* end maxgctDSET */
		for (j = 0; j < maxpb; j++) {
			if (DEBUG)
				fprintf(stdout, "PBIN0[%s]\nPBIN1[%s]\n", pbset[j].DSET0, pbset[j].DSET1);
			for (muxcount = i = 0; i < strlen(muxpins); i++) {
				muxcopy[i + muxcount] = pbset[j].DSET0[i];
				muxcopy1[i + muxcount] = pbset[j].DSET1[i];
				if (muxpins[i] == 'M') {
					muxcount++;
					if (NOMUX == 0) {
						muxcopy[i + muxcount] = pbset[j].DSET0[i];
						muxcopy1[i + muxcount] = pbset[j].DSET0[i];
					}
					else {
						muxcopy[i + muxcount] = AM_NOMUX;
						muxcopy1[i + muxcount] = AM_NOMUX;
					}
				}
			}
			muxcopy[i + muxcount] = '\0';
			muxcopy1[i + muxcount] = '\0';
			strcpy(pbset[j].DSET0, muxcopy);
			strcpy(pbset[j].DSET1, muxcopy1);
//			fprintf(stdout,"ABC[%s]\n",muxcopy);
		}		/* end maxpb */
	}
	MOD2_SIZE += muxcount;
	MOD2_SIZE -= dropcnt;
	fprintf(stdout, "MOD_SIZE{%d}\n", MOD2_SIZE);

/* create a dummy vector for microinstruction only lines, base it on sizeof GCT pin file */
	for (j = 0, i = 0; i < MOD2_SIZE; i++) {
		dummy_vector[i] = AM_continueDRV;
		cpmdpm_vector[i] = AM_cpmdpm;
		EVX2VECT[i] = AM_DONOTHINGPAD;
		if (muxpins[i+j] == 'M') {
			if (NOMUX == 0) {
				dummy_vector[i+1] = AM_continueDRV;
				cpmdpm_vector[i+1] = AM_cpmdpm;
				EVX2VECT[i+1] = AM_DONOTHINGPAD;
			}
			else {
				dummy_vector[i+1] = AM_NOMUX;
				cpmdpm_vector[i+1] = AM_NOMUX;
				EVX2VECT[i+1] = AM_NOMUX;
			}
			i++;
			j--;
		}
	}
// 	for (i = 1; i <= muxcount; j++, i++) {
// 		fprintf(stderr, "ADDING %d MUXPINS[%d]\n", muxcount, i);
// 		dummy_vector[j] = AM_continueDRV;
// 		cpmdpm_vector[j] = AM_cpmdpm;
// 	}
	EVX2VECT[i] = '\0';
	dummy_vector[i] = '\0';
	cpmdpm_vector[i] = '\0';
//	fprintf(stdout,"CPM[%s]\n",cpmdpm_vector);
//	fprintf(stdout,"D[%s]\n",dummy_vector);
//	fprintf(stdout,"EVX2[%s]\n",EVX2VECT);
	fclose(fpin2);

/* allocate buffers */

	MSETPTR = (char *) malloc((unsigned) (VECTORLEN * MAXMSET));
	DSETPTR = (char *) malloc((unsigned) (VECTORLEN * MAXDSET));
	ISETPTR = (char *) malloc((unsigned) (VECTORLEN * MAXISET));
	if (MSETPTR == NULL) fprintf(stderr, "FATAL_ERROR:Could not allocate msetptr\n");
	if (MSETPTR == NULL) fprintf(fperrors, "FATAL_ERROR:%s:Could not allocate msetptr[%s]\n", progstr, infile_orig);
	if (DSETPTR == NULL) fprintf(stderr, "FATAL_ERROR:Could not allocate dsetptr\n");
	if (DSETPTR == NULL) fprintf(fperrors, "FATAL_ERROR:%s:Could not allocate dsetptr[%s]\n", progstr, infile_orig);
	if (ISETPTR == NULL) fprintf(stderr, "FATAL_ERROR:Could not allocate isetptr\n");
	if (ISETPTR == NULL) fprintf(fperrors, "FATAL_ERROR:%s:Could not allocate isetptr[%s]\n", progstr, infile_orig);
	if (MSETPTR == NULL || DSETPTR == NULL || ISETPTR == NULL) exit(6);
	if (!QUIET) fprintf(stderr, "Memory allocated ok\n");

	SETS.MSETPTR = MSETPTR;
	SETS.DSETPTR = DSETPTR;
	SETS.maxgctDSET = maxgctDSET;
	SETS.ISETPTR = ISETPTR;
	SETS.WFT = WFT;
/* SETS.GCTMODNAME=GCTMODNAME;
SETS.VECTMOD=VECTMOD; */

/* the following will initialize any unused mset to the default values */
	for (i = 0; i < MAXMSET; i++)
		for (j = 0; j < MAXPINS; j++) MSETPTR[i * VECTORLEN + j] = DSETPTR[i * VECTORLEN + j] = 1;
	for (i = 0; i < MAXISET; i++)
		for (j = 0; j < MAXPINS; j++) ISETPTR[i * VECTORLEN + j] = 0;
   /***********************************************/
	/*                                             */
	/*    do some initial setup and checks         */
	/*                                             */
   /***********************************************/
	fgets(vector, READLINELEN - 1, fpin1);
	readlinenum++;
	printstring[0] = '\0';
	comment[0] = '\0';
	beginflag = 0;
	errorflag = 0;
	commentON = 0;
	repeatdec = 1;
	commentcount = 0;
	if (strstr(vector, "(*-FLAG-This must be a CPM pattern-*)") != 0) {
		CPM = 1;
	}
	if (strstr(vector, "(*-FLAG-This must be a CPM_CALLING_DPM pattern-*)") != 0) {
		CPM = 2;
		/* cannot use the -r here, use -z if requested on this program call */
		/* added 'c' option to write dpm count */
		sprintf(tempstr, "%s -fgc%c DPM_%s %s", compilestr, (gzip) ? 'z' : ' ', argv[2], argv[3]);
		fprintf(stderr, "Running %s on the dpm portion\n", compilestr);
		system(tempstr);
		fprintf(fpstatus, "Returning from [%s]\n", tempstr);
		sprintf(tempstr, "%s_DPM_%s", DPM_COUNT_file, pattern);
		if (NULL == (tempfile = fopen(tempstr, "r"))) {
			fprintf(stderr, "\nFATAL_ERROR:Could not open %s for input\n", tempstr);
			fprintf(fperrors, "\nFATAL_ERROR:%s:Could not open %s for input\n", progstr, tempstr);
			exit(1);
		}
		fscanf(tempfile, "%ld,%d\n", &cpmcallingdpmcount, &newcommentcount);
		if (newcommentcount > 0)
			fprintf(stderr, "There were %d pending DPM comments!!!\n", newcommentcount);
		commentcount += newcommentcount;
		if (commentcount > 0) commentON = 1;
		fclose(tempfile);
		fprintf(stderr, "CPM calling DPM count=%ld[%s]\n", cpmcallingdpmcount, tempstr);
		/* remove count file: */
		remove(tempstr);
		sprintf(tempstr, "DPM_%s", argv[2]);
		if (NULL == (tempfile = fopen(tempstr, "r"))) {
			fprintf(stderr, "\nFATAL_ERROR:Could not open %s for input again\n", tempstr);
			fprintf(fperrors, "\nFATAL_ERROR:%s:Could not open %s for input again[%s]\n", progstr, tempstr, infile_orig);
			exit(1);
		}
		beginflag = 1;
		while (fgets(vector, READLINELEN - 1, tempfile) != NULL) {
			if (strstr(vector, "{SHUTDOWN_B") != NULL) {
				fprintf(stdout, "FOUND SHUTDOWN_B!\n");
				shutdown_proc = 1;
				continue;
				/* search until we find the "//SHUTDOWN_E", the last "SHUTDOWN__" will be saved... */
			}					/* process shutdown vector */
			if (strstr(vector, "{SHUTDOWN__") != NULL && shutdown_proc == 1) {
				if (strchr(vector, '(') != NULL
					&& strchr(vector, ')') != NULL
					&& strchr(vector, '[') != NULL
					&& strchr(vector, ']') != NULL) {
					/* probably a shutdown vector */
					ptrBV = strchr(vector, ':');
					if (ptrBV == NULL) continue;
					ptrEV = strchr(vector, '\"');
					if (ptrEV == NULL) continue;
					*ptrEV = '\0';
					strcpy(vector_shutpre, ptrBV + 1);
					fprintf(fpstatus, "[%s]vectshutpre[%s]\n", infile_orig, vector_shutpre);
//					vector_convert(&beginflag, vector_shutpre, vector_shut1, &SETS, vector_shut2, DMI, pb_vector);
//					fprintf(stdout,"V2[%s]\n",vector_shut2);
/* XYZ */
					found_shut = 1;
/* can't do anything here because we don't know the MSETS/DSETS/ISETS yet... */
				}
				/* search until we find the "//SHUTDOWN_E", the last "SHUTDOWN__" will be saved... */
				continue;
			}					/* process shutdown vector */
			if (strstr(vector, "{SHUTDOWN_E") != NULL && shutdown_proc == 1) {
				fprintf(stdout, "FOUND SHUTDOWN_E!\n");
				shutdown_proc = 0;
				continue;
				/* search until we find the "//SHUTDOWN_E", the last "SHUTDOWN__" will be saved... */
			}					/* process shutdown vector */
			if (NULL != (ptrOPEN = strstr(vector, "(*")) && NULL != (ptrCLOSE = strstr(vector, "*)"))) {
				while (ptrOPEN != (ptrCLOSE + 1)) *ptrOPEN++ = ' ';	/* wipe out comment with spaces */
			}
			rv = check_SET(beginflag, vector, "MSet", &notgood, MAXMSET, MSETPTR);
			if (1 == rv) break;
			if (2 == rv) {
				scnt++;
				continue;
			}
			rv = check_SET(beginflag, vector, "DSet", &notgood, MAXDSET, DSETPTR);
			if (1 == rv) break;
			if (2 == rv) {
				scnt++;
				continue;
			}
			rv = check_SET(beginflag, vector, "ISet", &notgood, MAXISET, ISETPTR);
			if (1 == rv) break;
			if (0 == rv) {		/* assume that we've found enough of the Isets to convert shutdown */
				if (foundmdi == 1) foundmdi = 2;
			}
			if (2 == rv) {
				foundmdi = 1;
				continue;
			}
			if (found_shut == 1 && foundmdi == 2) {
				/* must have mdi information to convert shutdown vector! */
//          fprintf(stdout,"//Shutdown pre[%s]\n",vector_shutpre);
				strcpy(vector_shut1, vector_shutpre);
				vector_convert(&beginflag, vector_shutpre, vector_shut1, &SETS, vector_shut2, DMI, pb_vector);
//          fprintf(stdout,"//Shutdown Vector[%s]\n",vector_shut2);
				strcpy(dummy_vector, vector_shut2);
				strcpy(REMAP_DEF_WFT, SETS.WFT);
				fprintf(stdout, "SETTING [DEF_WFT] based on shutdown2[%s]\n", REMAP_DEF_WFT);
				found_shut = 2;
			}
		}
		fclose(tempfile);
		fprintf(fpstatus, "\nSuccessfully got Mset/Dset total=[%d] and final Iset Info from %s\n", scnt, tempstr);
		fprintf(stderr, "\nSuccessfully got Mset/Dset total=[%d] and final Iset Info from %s\n", scnt, tempstr);
		beginflag = 1;
		vectorflag = 1;
	}
	fprintf(fpout1, "enVisionObject:\"bl8:R5.7\";\n\n");
	fprintf(fpout1, "Pattern %s {\n", pattern);
	if (!CPM) {
		fprintf(fpout1, "    Type Dpm;\n");
		fprintf(stdout, "#DPM PATTERN[%s]\n", pattern);
		fprintf(fpstatus, "#DPM PATTERN[%s]\n", pattern);
	}
	if (CPM) {
		fprintf(fpout1, "    Type Cpm;\n");
		fprintf(stdout, "#CPM PATTERN[%s]\n", pattern);
		fprintf(fpstatus, "#CPM PATTERN[%s]\n", pattern);
	}
	if (EVX2) {
		fprintf(fpout1, "    PatternMode evX2;\n");
		fprintf(stdout, "#PatternMode evX2[%s]\n", pattern);
		fprintf(fpstatus, "#PatternMode evX2[%s]\n", pattern);
	}
	if (NOEVX2) {
		fprintf(fpout1, "\" waveforms might have needed PatternMode evX2;\"\n");
		fprintf(stdout, "#PatternMode evX2 DISABLED!![%s]\n", pattern);
		fprintf(fpstatus, "#PatternMode evX2 DISABLED!![%s]\n", pattern);
	}
/* fprintf(fpout1,"    Default WaveformTable %s;\n",DEF_WFT); */
/* fprintf(fpout1,"    Default SignalHeader %s;\n",DFLTSGHDR); */

	fprintf(fpout1, "\" Pattern convertor: %s REV:%2.1f:%s by Anthony Sully compile_date:%s@%s\"\n",
			compilestr, REV, progstr, __DATE__, __TIME__);
	fprintf(fpout1, "\"      Pattern converted on:%s by:%s on host:%s \"\n\"      in pwd:%s\"\n",
			mydate, username, hostname, pwd);
	fprintf(fpout1, "\"                                     \"\n");
	fprintf(fpout1, "\"See aliasmap.h for alias assignments \"\n");
	fprintf(fpout1, "\"                                     \"\n");
	fprintf(fpout1, "//main_vcp %lld %d\n", CKS_main_vcp_c, FS_main_vcp_c);
	fprintf(fpout1, "//alias_vcpvcs %lld %d\n", CKS_alias_vcpvcs_c, FS_alias_vcpvcs_c);
	fprintf(fpout1, "//aliasmap %lld %d\n", CKS_aliasmap_h, FS_aliasmap_h);
	fprintf(fpout1, "//comments_shutdown %lld %d\n", CKS_comments_shutdown_vcp_c, FS_comments_shutdown_vcp_c);
	fprintf(fpout1, "//convert_vcp %lld %d\n", CKS_convert_vcp_c, FS_convert_vcp_c);
	fprintf(fpout1, "//cpmopt_new %lld %d\n", CKS_cpmopt_new_vcp_c, FS_cpmopt_new_vcp_c);
	fprintf(fpout1, "//cpmopt_vcp %lld %d\n", CKS_cpmopt_vcp_c, FS_cpmopt_vcp_c);
	fprintf(fpout1, "//global %lld %d\n", CKS_global_vcp_c, FS_global_vcp_c);
	fprintf(fpout1, "//include %lld %d\n", CKS_include_vcp_h, FS_include_vcp_h);
	fprintf(fpout1, "//common includes %lld %d\n", CKS_common_includes_h, FS_common_includes_h);
	fprintf(fpout1, "//outvector %lld %d\n", CKS_outvector_vcp_c, FS_outvector_vcp_c);
	fprintf(fpout1, "//outvector_evX2 %lld %d\n", CKS_outvector_evX2_vcp_c, FS_outvector_evX2_vcp_c);
	fprintf(fpout1, "//smallfunc %lld %d\n", CKS_smallfunc_vcp_c, FS_smallfunc_vcp_c);
	if (found_shut == 1) fprintf(fpout1, "\"Shutdown[%s]\"\n", vector_shut2);
	chksumout(fpout1, "//", "");

	for (i = 0; i < pinheadcount; i++) fprintf(fpout1, "\" %s\"\n", &pinhead[i][2]);	/* get past // */
	VC = 0;

	fprintf(fpout1, "$%s_begin\n", pattern);
	if (CPM == 2) {
/* these are now dealt with directly in the out functions */
//   fprintf(fpout1,"* %s* %s %s; <LDA DPM_%s_begin>\n",dummy_vector,DEF_WFT,NORMALSGHDR,pattern);
//   fprintf(fpout1,"* %s* %s %s; <RPT 64>\n",dummy_vector,DEF_WFT,NORMALSGHDR);VNIR+=64;
//   VC += 2;
//   while (cpmcallingdpmcount>MAX_RPT_CPM) {
//      fprintf(fpout1,"* %s * %s %s;<RPT %ld,SDP>\n",cpmdpm_vector,DEF_WFT,NORMALSGHDR,(long)MAX_RPT_CPM);VNIR+=MAX_RPT_CPM;
//      VC++;
//      cpmcallingdpmcount-=MAX_RPT_CPM;
//      }
//   fprintf(fpout1,"* %s * %s %s;<RPT %ld,SDP>\n",cpmdpm_vector,DEF_WFT,NORMALSGHDR,cpmcallingdpmcount);VNIR+=cpmcallingdpmcount;
//   VC++;
	}
	if (!CPM) {
		vector[strlen(vector) - 1] = '\0';	/* remove trailing \n */
		fprintf(fpout1, "\"%s\"\n", vector);
		VC++;
	}
   /***********************************************/
	/*                                             */
	/*    begin main loop for file processing      */
	/*                                             */
   /***********************************************/
	shutdown_proc = 0;
	while (fgets(vector, READLINELEN - 1, fpin1) != NULL) {
		if (strstr(vector, "{SHUTDOWN_B") != NULL) {
			fprintf(stdout, "FOUND SHUTDOWN_B!\n");
			shutdown_proc = 1;
			continue;
			/* search until we find the "//SHUTDOWN_E", the last "SHUTDOWN__" will be saved... */
		}						/* process shutdown vector */
		if (strstr(vector, "{SHUTDOWN__") != NULL && shutdown_proc == 1) {
			if (strchr(vector, '(') != NULL && strchr(vector, ')') != NULL
				&& strchr(vector, '[') != NULL
				&& strchr(vector, ']') != NULL) {
				/* probably a shutdown vector */
				ptrBV = strchr(vector, ':');
				if (ptrBV == NULL) continue;
				ptrEV = strchr(vector, '\"');
				if (ptrEV == NULL) continue;
				*ptrEV = '\0';
				strcpy(vector_shutpre, ptrBV + 1);
				fprintf(fpstatus, "[%s]vectshutpre[%s]\n", infile_orig, vector_shutpre);
				found_shut = 1;
/* can't do anything here because we don't know the MSETS/DSETS/ISETS yet... */
			}
			/* search until we find the "//SHUTDOWN_E", the last "SHUTDOWN__" will be saved... */
			continue;
		}						/* process shutdown vector */
		if (strstr(vector, "{SHUTDOWN_E") != NULL && shutdown_proc == 1) {
			fprintf(stdout, "FOUND SHUTDOWN_E!\n");
			strcpy(vector_shut1, vector_shutpre);
			fprintf(stdout, "[%s]vectshutpre[%s]-->%s\n", infile_orig, vector_shutpre,SETS.GCTMODNAME[1]);
			vector_convert(&beginflag, vector_shutpre, vector_shut1, &SETS, vector_shut2, DMI, pb_vector);
			fprintf(stdout,"V2[%s] WFT[%s]\n",vector_shut2,SETS.WFT);
			strcpy(dummy_vector, vector_shut2);
			strcpy(REMAP_DEF_WFT, SETS.WFT);
			fprintf(stdout,"REMAP [%s] to [%s] based on shutdown vector\n",DEF_WFT,SETS.WFT);
			fprintf(stdout,"using shutdown vector for hold vector\n");
			strcpy(dummy_vector, vector_shut2);
/* ZYX2 */
			shutdown_proc = 0;
			continue;
			/* search until we find the "//SHUTDOWN_E", the last "SHUTDOWN__" will be saved... */
		}						/* process shutdown vector */
		if (strstr(vector, "{-FLAG-preprocessed with") != 0) {
			strcpy(preprocessrev, vector);
			preprocessrev[strlen(preprocessrev) - 1] = '\0';	/* remove the carriage return */
			fprintf(fpout1, "\"%s\"\n", preprocessrev);
			preprocessrev[0] = '\0';
			continue;
		}
		readlinenum++;
		if ((readlinenum % 2500) == 0) {
			fprintf(fpstatus, "Reading line %ld\n", readlinenum);
			fflush(fpstatus);
		}
		commentflag = 0;
		vector[strlen(vector) - 1] = '\0';	/* remove trailing \n */
		strcpy(mod_vector, vector);
		vl = strlen(mod_vector);
		if (vector[0] == '$') {	/* label was passed in */
			outputvector(fpout1, vector, NO_WFT, NO_DMI, NO_REPEAT, NO_COMMENT, NO_MICROINSTR, CPM,__LINE__);
			continue;
		}
		if (vector[0] == '<') {	/* microinstruction was passed in */
			ptrZ = vector;		/* replace my stupid comment numbers {1},{2}, etc */
			while ((ptrf = strchr(ptrZ, '{')) != NULL) {
				*ptrf = '"';
				ptrZ = ptrf + 1;
			}
			while ((ptrf = strchr(ptrZ, '}')) != NULL) {
				*ptrf = '"';
				ptrZ = ptrf + 1;
			}

			if (strstr(vector, "SDP") != NULL) {
				if (!EVX2) {
					outputvector(fpout1, vector, NO_VECTOR, NO_DMI, VECTOR_FLUSH, NO_COMMENT, NO_MICROINSTR, CPM,__LINE__);
					fprintf(fpout1, "* %s* %s %s; %s \n", cpmdpm_vector, REMAP_DEF_WFT, NORMALSGHDR, vector);
					VC++;
					}
				else       {
					outputvector_evX2(fpout1, NO_VECTOR, NO_WFT, NO_DMI, VECTOR_FLUSH, NO_COMMENT, NO_MICROINSTR, CPM, pb_vector,__LINE__);
					fprintf(fpout1, "* %s* %s %s; %s\n* %s* %s %s; \n",
							EVX2VECT, PUSHBACK_CYCLE, NORMALSGHDR , vector, cpmdpm_vector, REMAP_DEF_WFT, NORMALSGHDR);
					VC++;
					}
			}
			else if ((strstr(vector, "LDA") != NULL)    ||
						(strstr(vector, "CJMP") != NULL)   ||
						(strstr(vector, "JMP") != NULL)    ||
						(strstr(vector, "LC") != NULL)     ||
						(strstr(vector, "SWCDPM") != NULL) ||
						(strstr(vector, "SWCCPM") != NULL) ||
						(strstr(vector, "MODE") != NULL)   ||
						(strstr(vector, "DC") != NULL)     ||
						(strstr(vector, "STOP") != NULL)   ||
						(strstr(vector, "COND") != NULL)   ||
						(strstr(vector, "FLAG (CONT ON)") != NULL)   ||
						(strstr(vector, "FLAG(SEQF OFF)") != NULL)  ||
						(strstr(vector, "RPT DpmPipeline") != NULL) ||
						(strstr(vector, "RPT MatchPipeline") != NULL)) {
				if (!EVX2) {
					outputvector(fpout1, NO_VECTOR, NO_WFT, NO_DMI, VECTOR_FLUSH, NO_COMMENT, NO_MICROINSTR, CPM,__LINE__);
					fprintf(fpout1, "* %s* %s %s; %s\n", dummy_vector, REMAP_DEF_WFT, NORMALSGHDR, vector);
					VC++;
					}
				else       {
					outputvector_evX2(fpout1, NO_VECTOR, NO_WFT, NO_DMI, VECTOR_FLUSH, NO_COMMENT, NO_MICROINSTR, CPM, pb_vector,__LINE__);
					fprintf(fpout1, "* %s* %s %s; %s\n* %s* %s %s;\n", 
							EVX2VECT, PUSHBACK_CYCLE, NORMALSGHDR , vector, cpmdpm_vector, REMAP_DEF_WFT, NORMALSGHDR);
					VC++;
					}
			}
			else if (strstr(vector, "<RPT ") != NULL) {
				/* actually just print the line 'n' times, its easier */
				/* we'll support the repeat microinstruction by placing it in FRONT of the vector! */
				fprintf(stderr, "We don't support this use of RPT\n[%s]\n", vector);
				fprintf(fperrors, "We don't support this use of RPT\n[%s]\n", vector);
				exit(1);
				ptr = strchr(vector, '>');
				get_count(vector, sizeof("<RPT"), &RPTCNT, __LINE__);
				/* FIXME: APS parse the vector up into its pieces */
				if (EVX2) outputvector_evX2(fpout1, ptr + 1, REMAP_DEF_WFT, NO_DMI, RPTCNT, NO_COMMENT, vector, CPM, pb_vector,__LINE__);
				else      outputvector     (fpout1, ptr + 1, REMAP_DEF_WFT, NO_DMI, RPTCNT, NO_COMMENT, vector, CPM,__LINE__);
			}
			else {
				if (EVX2) outputvector_evX2(fpout1, dummy_vector, REMAP_DEF_WFT, NO_DMI, NO_REPEAT, NO_COMMENT, vector, CPM, pb_vector,__LINE__);
				else      outputvector     (fpout1, dummy_vector, REMAP_DEF_WFT, NO_DMI, NO_REPEAT, NO_COMMENT, vector, CPM,__LINE__);
			}
			VC++;
			mod_vector[0]='\0';
			continue;
		}
		for (i = 0; i < vl; i++) {	/* simplify comments */
			if (mod_vector[i] == '(' && mod_vector[i + 1] == '*') {
				mod_vector[i] = '{';
				mod_vector[i + 1] = ' ';
			}
			else if (mod_vector[i] == '*' && mod_vector[i + 1] == ')') {
				mod_vector[i] = '}';
				mod_vector[i + 1] = ' ';
			}
			else if (mod_vector[i] == '*')
				mod_vector[i] = 'x';
			else if (mod_vector[i] == '"')
				mod_vector[i] = '#';
		}
		if (vl == 0)
			continue;			/* empty line */
		if (DEBUG) fprintf(fpstatus, "V:%s\n", mod_vector);
		/* moved shutdown detect to after the comment check stuff */
		/* if we have an open comment and there is nothing to close it then add whatever we found to 'comment' */
		if (commentON && NULL == strchr(mod_vector, '}')) {
			strncat(comment, mod_vector, MULTILINESIZE);
			continue;
		}
		/* otherwise lets see if we can close it */
		else if (commentON) {
			if (1 ==
				deal_with_comment(fpout1, mod_vector, comment, &commentcount, &commentflag, &commentON, vectorflag));
			continue;
		}
/* this means there is a comment and we are not currently inside a block */
		while (NULL != (ptr1 = strchr(mod_vector, '{')) && commentON == 0) {
			if (1 == deal_with_comment(fpout1, mod_vector, comment, &commentcount, &commentflag, &commentON, vectorflag));
			continue;
		}
		if (commentON) {		/* need more lines */
			strcpy(keep_vector, mod_vector);
			continue;
		}
//   if (NULL!=(ptr=strstr(mod_vector,"Shutdown")) || NULL!=(ptr=strstr(mod_vector,"ShutDown")) ) {
//      deal_with_shutdown(mod_vector,ptr,fpin1);
//      }/* end if shutdown */
		if (DEBUG)
			fprintf(fpstatus, "comment=<%s>", comment);
		if (beginflag >= 1 && NULL != (ptr = strstr(mod_vector, "begin"))) {
			if (CPM && readlinenum < 5);
			else {
				fprintf(stderr,"NON_FATAL_ERROR:found internal begin around proc line[%ld]...ignoring. Run pre_proc  or  check file for two patterns in one\n",
						readlinenum);
				fprintf(fperrors,"NON_FATAL_ERROR:%s:found internal begin...proc ignoring[%s]line:%ld. Run pre_proc or check file for two patterns in one\n",
						progstr, infile_orig, readlinenum);
				notgood = -1;
				continue;
			}
		}
		if (beginflag == 0 && NULL != (ptr = strstr(mod_vector, "begin"))) {
			beginflag = 1;
			if (DEBUG) fprintf(fpstatus, "found begin\n");
			outputvector(fpout1, NO_VECTOR, NO_WFT, NO_DMI, NO_REPEAT, comment, NO_MICROINSTR, CPM,__LINE__);
			continue;
		}
		if (beginflag >= 1 && NULL != (ptr = strstr(mod_vector, "end"))) {
			if (DEBUG) fprintf(fpstatus, "found end\n");
			continue;
		}
		if (NULL != (ptr = strstr(mod_vector, "ScanIn")) ||
			NULL != (ptr = strstr(mod_vector, "ScanOut")) ||
			NULL != (ptr = strstr(mod_vector, "ScanTest")) ||
			NULL != (ptr = strstr(mod_vector, "ChainLength"))) {
			fprintf(stderr, "BAD_ERROR: Scan pattern!!!...exiting\n");
			fprintf(fperrors,
					"BAD_ERROR:%s: Scan pattern!!!...exiting[%s]line:%ld\n", progstr, infile_orig, readlinenum);
			notgood = 1;
			break;
		}
		if (beginflag >= 1 && NULL != (ptr = strstr(mod_vector, "repeat forever"))) {
			fprintf(stderr, "BAD_ERROR:found repeat forever...exiting. This should have been caught with PRE_PROC\n");
			fprintf(fperrors, "BAD_ERROR:%s:found repeat forever...[%s]line:%ld This should have been caught with PRE_PROC\n", progstr, infile_orig, readlinenum);
			notgood = 1;
			break;
		}
		if (beginflag >= 1 && NULL != (ptr = strstr(mod_vector, "repeat"))) {
			retptr = get_count(ptr, sizeof("repeat"), &repeatdec, 1);
			fprintf(fpstatus, "found repeat [%ld]\n", repeatdec);
			VNIR = VNIR + repeatdec - 1;
			continue;
		}
		rv = check_SET(beginflag, mod_vector, "MSet", &notgood, MAXMSET, MSETPTR);
		if (1 == rv) break;
		if (2 == rv) continue;
		rv = check_SET(beginflag, mod_vector, "DSet", &notgood, MAXDSET, DSETPTR);
		if (1 == rv) break;
		if (2 == rv) continue;
		rv = check_SET(beginflag, mod_vector, "ISet", &notgood, MAXISET, ISETPTR);
		if (1 == rv) break;
		if (0 == rv) {			/* assume that we've found enough of the Isets to convert shutdown */
			if (foundmdi == 1) foundmdi = 2;
		}
		if (2 == rv) {
			foundmdi = 1;
			continue;
		}
		if (found_shut == 1 && foundmdi == 2) {
			/* must have mdi information to convert shutdown vector! */
			fprintf(fpout1, "\"Shutdown pre[%s]\"\n", vector_shutpre);
			strcpy(vector_shut1, vector_shutpre);
			vector_convert(&beginflag, vector_shutpre, vector_shut1, &SETS, vector_shut2, DMI, pb_vector);
			fprintf(fpout1, "\"Shutdown Vector[%s]\"\n", vector_shut2);
			found_shut = 2;
			strcpy(dummy_vector, vector_shut2);
			strcpy(REMAP_DEF_WFT, SETS.WFT);
			fprintf(stdout, "SETTING [DEF_WFT] based on shutdown1[%s]\n", REMAP_DEF_WFT);
		}


		if (commentON == 0 && beginflag >= 1
			&& NULL != strchr(mod_vector, '[')
			&& NULL != strchr(mod_vector, ']')
			&& NULL != strchr(mod_vector, '[')
			&& NULL != strchr(mod_vector, '[')) {
			vectorflag = 1;
			vector_convert(&beginflag, vector, mod_vector, &SETS, out_vector1, DMI, pb_vector);
//			fprintf(fpout1,"mdv!!!%s~~~%ld#$\n",out_vector1,repeatdec);
			if (EVX2) repeatdec = outputvector_evX2(fpout1, out_vector1, WFT, DMI, repeatdec, comment, NO_MICROINSTR, CPM, pb_vector,__LINE__);
			else      repeatdec = outputvector     (fpout1, out_vector1, WFT, DMI, repeatdec, comment, NO_MICROINSTR, CPM,__LINE__);

		}

	}							/* end of while vector */

   /********************/
	/* End of main loop */
   /********************/

	sprintf(vector, "$%s_end", pattern);
	if (EVX2) outputvector_evX2(fpout1, vector, NO_WFT, NO_DMI, VECTOR_DONE, NO_COMMENT, NO_MICROINSTR, CPM, pb_vector,__LINE__);
	else      outputvector     (fpout1, vector, NO_WFT, NO_DMI, VECTOR_DONE, NO_COMMENT, NO_MICROINSTR, CPM,__LINE__);

	if (commentON) fprintf(stderr, "[%d] COMMENT(s) PENDING!!!\n", commentcount);
	fclose(fpin1);
	fclose(fpout1);
	if (gunzip) {
		if (0 != remove(tempgunzipname)) perror("Error removing ungzipped temp file");
	}
  CPMOPTIMIZE_ONLY:
	if (notgood == 1) {
		sprintf(tempstr, "%s.evo", pattern);
		if (0 != remove(tempstr)) fprintf(fperrors, "Error removing BAD evo file[%s]\n", tempstr);
		else fprintf(fperrors, "Removed BAD evo file[%s]\n", tempstr);
		sprintf(tempstr, "%s.proc", pattern);
		if (0 != remove(tempstr)) fprintf(fperrors, "Error removing proc file[%s]\n", tempstr);
		else fprintf(fperrors, "Removed BAD *.proc file[%s]\n", tempstr);
		fprintf(stderr, "BAD_ERROR: File %s was not successful!!! \n", infile_orig);
		fprintf(fperrors, "BAD_ERROR:%s: File [%s] was not successful!!! \n", progstr, infile_orig);
	}
	else {
		if (notgood == -1) {
			fprintf(stderr, "NON_FATAL_ERROR: File %s had internal begin!!!\n",infile_orig);
			fprintf(fperrors, "NON_FATAL_ERROR:%s: File [%s] had internal beginl!!!\n", progstr, infile_orig);
		}
		if (CPMOPTIMIZE && CPM) {
			i = cpmoptimize(pattern);
			if (gzip && i == 0) {
				if (NO_BACKGROUND_GZIP) sprintf(readstr, "gzip -f __%s.evo", pattern);
				else sprintf(readstr, "gzip -f __%s.evo &", pattern);
				system(readstr);	/* gzip old cpm file */
			}
		}
		if (gzip) {
			if (NO_BACKGROUND_GZIP) sprintf(tempstr, "gzip -f %s.evo", pattern);
			else sprintf(tempstr, "gzip -f %s.evo &", pattern);
			system(tempstr);	/* gzip new cpm pattern */
		}
		sprintf(tempstr, "%s_DPM_%s", DPM_COUNT_file, pattern);
		if (CPM == 2)
			if (0 != remove(tempstr)) perror("Can't remove *_DPM_* file");
		if (CPM == 0 && writecount) {
			sprintf(tempstr, "%s_%s", DPM_COUNT_file, pattern);
			if (NULL == (tempfile = fopen(tempstr, "w"))) {
				fprintf(stderr, "\nFATAL_ERROR: Could not open %s for output\n", tempstr);
				fprintf(fperrors, "\nFATAL_ERROR:%s: Could not open %s for output\n", progstr, tempstr);
				exit(1);
			}
			fprintf(tempfile, "%ld,%d\n", VNIR, commentcount);
			fclose(tempfile);
		}
		if (remove_pre && DEBUG == FALSE) {
			if (NULL == strstr(infile_orig, ".vpl")) {
				fprintf(fpstatus, "removing [%s]\n", infile_orig);
				if (0 != remove(infile_orig)) perror("Error removing .proc file");
				if (CPM == 2) {
					sprintf(tempstr, "DPM_%s", infile_orig);
					if (0 != remove(tempstr)) perror("Error removing DPM_*.proc file");
				}
			}
			else {
				fprintf(fpstatus, "File [%s] contains .vpl, not removing!!!\n", infile_orig);
			}
		}
	}
	if (NULL == (fppatref = fopen(PAT_REF_FILE, "a"))) {
		fprintf(stderr, "\nCould not open %s for output[%s,%d,%s]\n",
				PAT_REF_FILE, __FILE__, __LINE__, __FUNCTION__);
		fprintf(fperrors, "\nCould not open %s for output[%s,%d,%s]\n",
				PAT_REF_FILE, __FILE__, __LINE__, __FUNCTION__);
	}
	else {
		fprintf(fppatref, "PATREF:[%-30s]:", pattern); // was -30.30s
		for (i = 0; i < maxgctDSET; i++) {
			if (SETS.used[i] == 1)
				fprintf(fppatref, "|%-25s", SETS.GCTMODNAME[i]); // was -25.25s
		}
		fputc('\n', fppatref);
		fclose(fppatref);
	}
	fclose(fpstatus);
	fclose(fperrors);

	return (0);
}
