#include <stdio.h>
#include <strings.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <dirent.h>
#include "includes_ggm.h"
#include "aliasmap.h"
#include "chksum.cksum"

/********************************/
/*                              */
/*      main() function         */
/*                              */
/********************************/
int main(int argc, char *argv[])
{

/*******************************************/
/*  VARIABLES                              */
/*******************************************/
/* file variables */
	FILE *fpin_pin, *fpin_device, *fp_mod_file, *fpwaves, *fpinherit;
	int filein1 = 0, filein2 = 0, filein3 = 0, filein4 = 0;
	char infile1[FILENAMELEN];
	char infile2[FILENAMELEN];
	char infile3[FILENAMELEN];
	char infile4[FILENAMELEN];
	char outfile1[FILENAMELEN];
	char pattern[FILENAMELEN];
	char inhfile[FILENAMELEN];

/* buffers */
	char mydate[101];
	char progstr[MEMOSTRLEN], datestr[MEMOSTRLEN], timestr[MEMOSTRLEN], compilestr[MEMOSTRLEN];	/* concaternated strings */
	char muxpin[READLINELEN + 1];
	char *ptr;
	time_t generictime;
/* control parameters */

/* temporary variables */
	int i, j, ret, maxcyclen;
	int actablelines;
	DIR *directoryscan;

	directoryscan=opendir(".Trash");
	if (directoryscan==NULL) {
		if (errno==ENOENT) {
			fprintf(stderr,"Creating directory %s\n",TRASH);
			i=mkdir(TRASH,0777);
			if (i==0) fprintf(stderr,"created directory [%s]\n",TRASH);
			else {
				fprintf(stderr,"Can't create directory [%s]\n",TRASH);
				exit(1);
				}
			}
		}
	else {
		fprintf(stderr,"Directory exists!!!\n");
		closedir (directoryscan);
			}

	if (NULL == (fperrors = fopen(TRANSLATION_ERRORS, "w"))) {
		/* we're going to open it write instead of append!!!, probably a good assumption since */
		/* this recreates the .mod file and any pattern information could be wrong anyway */
		fprintf(stderr,
				"\nFATAL_ERROR:%s:Could not open %s for output, source[%s,%d,%s]\n",
				progstr, TRANSLATION_ERRORS, __FILE__, __LINE__,
				__FUNCTION__);
		exit(1);
	}
	if (NULL == (fpstatus = fopen(TRANSLATION_STATUS, "w"))) {
		fprintf(stderr,
				"\nFATAL_ERROR:%s:Could not open %s for output, source[%s,%d,%s]\n",
				progstr, TRANSLATION_STATUS, __FILE__, __LINE__,
				__FUNCTION__);
		exit(1);
	}

	strcpy(tperiod, "DUMMY_TPERIOD_FIXME");
/* convert this to a long string for direct searching */
	for (i = 0; i < SIZE_WAVETYPES - 1; i++) {
		if (*(&wavetypes[0][0] + i) == '\0')
			wavetypefull[i] = ' ';
		else
			wavetypefull[i] = *(&wavetypes[0][0] + i);
	}
	wavetypefull[i - 1] = '\0';

	for (i = 0; i < SIZE_EDGETYPE - 1; i++) {
		if (*(&edgetypes[0][0] + i) == '\0')
			edgetypefull[i] = ' ';
		else
			edgetypefull[i] = *(&edgetypes[0][0] + i);
	}
	edgetypefull[i - 1] = '\0';

/***************************************************/
/* command line stuff */
/***************************************************/
	cyclebuff = malloc(CYCBUFFSIZE);
	if (cyclebuff == NULL) {
		fprintf(stderr,
				"Could not allocate memory for cyclebuff, exiting, source[%s,%d,%s]\n",
				__FILE__, __LINE__, __FUNCTION__);
		fprintf(fperrors,
				"Could not allocate memory for cyclebuff, exiting\n");
		exit(1);
	}
	for (i = 0; i < CYCBUFFSIZE; i++)
		*(cyclebuff + i) = '\0';
	fprintf(fpstatus,
			"allocated [%d] bytes for cyclebuff @%p, source[%s,%d,%s]\n",
			CYCBUFFSIZE, cyclebuff, __FILE__, __LINE__, __FUNCTION__);


// this is for strcat to the cyclebuff....
	SCATcycle = malloc(CYCBUFFSIZE);
	if (cyclebuff == NULL) {
		fprintf(stderr,
				"Could not allocate memory for SCATcycle, exiting, source[%s,%d,%s]\n",
				__FILE__, __LINE__, __FUNCTION__);
		fprintf(fperrors,
				"Could not allocate memory for SCATcycle, exiting\n");
		exit(1);
	}
	for (i = 0; i < CYCBUFFSIZE; i++)
		*(SCATcycle + i) = '\0';
	fprintf(fpstatus,
			"allocated [%d] bytes for SCATcycle @%p, source[%s,%d,%s]\n",
			CYCBUFFSIZE, SCATcycle, __FILE__, __LINE__, __FUNCTION__);

	REMOVEDUPE = malloc(CYCBUFFSIZE);
/* we do this strictly for the cell optimization in remove_dupe_cells() */
/* The function gets called for each cycle table entry, and as this is a */
/* reasonable sized buffer we don't want to allocate it every time */
	if (cyclebuff == NULL) {
		fprintf(stderr,
				"Could not allocate memory for REMOVEDUPE, exiting, source[%s,%d,%s]\n",
				__FILE__, __LINE__, __FUNCTION__);
		fprintf(fperrors,
				"Could not allocate memory for REMOVEDUPE, exiting\n");
		exit(1);
	}
	for (i = 0; i < CYCBUFFSIZE; i++)
		*(REMOVEDUPE + i) = '\0';
	fprintf(fpstatus,
			"allocated [%d] bytes for SCATcycle @%p, source[%s,%d,%s]\n",
			CYCBUFFSIZE, SCATcycle, __FILE__, __LINE__, __FUNCTION__);

	pinlist = (PINLIST *) calloc(MAXlists, sizeof(PINLIST));
	if (pinlist == NULL) {
		fprintf(stderr,
				"Could not allocate memory for pinlist, exiting, source[%s,%d,%s]\n",
				__FILE__, __LINE__, __FUNCTION__);
		fprintf(fperrors,
				"Could not allocate memory for pinlist, exiting\n");
		exit(1);
	}
	fprintf(fpstatus,
			"allocated [%d] bytes for PINLIST @%p, source[%s,%d,%s]\n",
			(MAXlists) * (sizeof(PINLIST)), pinlist, __FILE__, __LINE__,
			__FUNCTION__);

	cycsets = calloc(MAXCYCSETS, sizeof(CYCSETMD));
	if (cycsets == NULL) {
		fprintf(stderr,
				"Could not allocate memory for cycsets, exiting, source[%s,%d,%s]\n",
				__FILE__, __LINE__, __FUNCTION__);
		fprintf(fperrors,
				"Could not allocate memory for cycsets, exiting\n");
		exit(1);
	}
	fprintf(fpstatus,
			"allocated [%d] bytes for cycsets @%p, source[%s,%d,%s]\n",
			(MAXCYCSETS) * sizeof(CYCSETMD), cycsets, __FILE__, __LINE__,
			__FUNCTION__);
	maxcycset = 0;

	cellinfo = (CELL_INFO *) calloc(MAXCELLS, sizeof(CELL_INFO));
	if (cellinfo == NULL) {
		fprintf(stderr,
				"Could not allocate memory for cellinfo, exiting, source[%s,%d,%s]\n",
				__FILE__, __LINE__, __FUNCTION__);
		fprintf(fperrors,
				"Could not allocate memory for cellinfo, exiting\n");
		exit(1);
	}
	fprintf(fpstatus,
			"allocated [%d] bytes for CELL_INFO @%p, source[%s,%d,%s]\n",
			(MAXCELLS) * (sizeof(CELL_INFO)), cellinfo, __FILE__, __LINE__,
			__FUNCTION__);
	cellcnt = 0;

	paraminfo = (PARAM_INFO *) calloc(MAX_PARAMS, sizeof(PARAM_INFO));
	if (paraminfo == NULL) {
		fprintf(stderr,
				"Could not allocate memory for param_info, exiting, source[%s,%d,%s]\n",
				__FILE__, __LINE__, __FUNCTION__);
		fprintf(fperrors,
				"Could not allocate memory for param_info, exiting\n");
		exit(1);
	}
	fprintf(fpstatus,
			"allocated [%d] bytes for PARAM_INFO @%p, source[%s,%d,%s]\n",
			(MAX_PARAMS) * (sizeof(PARAM_INFO)), paraminfo, __FILE__,
			__LINE__, __FUNCTION__);
	paramcnt = 0;

	EOCNT = 0;
	if (argc > 1) {
		if (strchr((char *) argv[1], '-') != NULL) {
			if (strchr((char *) argv[1], 'f') != NULL && argc >= 3)
				filein1 = 1;
			if (strchr((char *) argv[1], 'p') != NULL && argc >= 4)
				filein2 = 1;
			if (strchr((char *) argv[1], 'd') != NULL && argc >= 5)
				filein3 = 1;
			if (strchr((char *) argv[1], 'a') != NULL && argc >= 6)
				filein4 = 1;
			if (strchr((char *) argv[1], 'n') != NULL )
				NOPUSHCYC = 1;
			if (strchr((char *) argv[1], 'm') != NULL )
				NOMUX = 1;
		}
	}

	strcpy(progstr, __FILE__);
	strcpy(datestr, __DATE__);
	strcpy(timestr, __TIME__);
	strcpy(compilestr, argv[0]);
	fprintf(stderr,
			"\n\n\nThis code is supplied under the LTX-Credence Shareware License.\n");
	fprintf(stderr,
			"Please see the LSLV1.2 file in the document directory for a full text.\n\n\n");
	if (argc == 1) {
		fprintf(stderr, "\n%s: %s\n", progstr, compilestr);
		fprintf(stderr, "%s by Anthony Sully\n", datestr);
		fprintf(stderr, "options are:\n");
		fprintf(stderr, "f => cycletbl_mod file follows\n");
		fprintf(stderr, "p => pin file follows\n");
		fprintf(stderr, "d => device.p follows (optional)\n\n");
		fprintf(stderr, "a => actable.p follows (optional)\n\n");
		fprintf(stderr, "\nUsage:%s -fpda cyctbl.p pinlist.txt device_mod.p actable_markers.p\n", argv[0]);
		exit(0);
	}

/*****************/
/*  FILE STUFF   */
/*****************/
	for (i = 0; i < FILENAMELEN; i++)
		infile1[i] = infile2[i] = infile3[i] = infile4[i] = '\0';
/* open input file */
	if (filein1) {
		strcpy(infile1, (char *) argv[2]);
		if (strstr(infile1,"mod8")!=NULL) {
			fprintf(stderr,"OOPS! [%s] cycletble file cannot contain \"mod8\"\n",infile1);
			exit(1);
			}
		}
/* open pin file */
	if (filein2) strcpy(infile2, (char *) argv[3]);
/* open device.p file */
	if (filein3) strcpy(infile3, (char *) argv[4]);
/* open actable_mod.p file */
	if (filein4) strcpy(infile4, (char *) argv[5]);
//for(i=0;i<140;i++) fprintf(fp_mod_file,"[%d][%c]\n",i,i);
	infile1[FILENAMELEN - 1] = '\0';
	if (filein1 == 0) {
		fprintf(stderr, "Inline syntax:\n%s -fpda %s %s %s %s\n", argv[0],
				infile1, infile2, infile3, infile4);
	}

	strcpy(outfile1, infile1);
	i = 0;
	while (NULL != (ptr = strchr(outfile1, '/'))) {
		i = (ptr - outfile1);
		outfile1[i] = ' ';
		i++;
	}
	j = 0;
	while (NULL == strchr(". ", outfile1[i]) && i < strlen(outfile1))
		pattern[j++] = outfile1[i++];
	pattern[j] = '\0';

	ACDATA = ACTABLE = 0;
	if (NULL != strstr(infile4, "data")) {
		ACDATA = 1;
		fprintf(stdout, "*** Processing as acdata file ***\n");
	}
	if (NULL != strstr(infile4, "table"))
		ACTABLE = 1;

	if (NULL == (fpin_pin = fopen(infile2, "r"))) {
		fprintf(stderr, "\npin file [%s] not found, source[%s,%d,%s]\n",
				infile2, __FILE__, __LINE__, __FUNCTION__);
		fprintf(fperrors, "\npin file [%s] not found\n", infile2);
		exit(1);
	}
	fprintf(stderr, "pin file <%s> opened, source[%s,%d,%s]\n", infile2,
			__FILE__, __LINE__, __FUNCTION__);

	if (NULL == (fpin_device = fopen(infile3, "r"))) {
		fprintf(stderr, "\ndevice file [%s] not found, source[%s,%d,%s]\n",
				infile3, __FILE__, __LINE__, __FUNCTION__);
		fprintf(fperrors, "\ndevice file [%s] not found\n", infile3);
		exit(1);
	}
	fprintf(stderr, "device file <%s> opened, source[%s,%d,%s]\n", infile3,
			__FILE__, __LINE__, __FUNCTION__);

	sprintf(outfile1, "%s%s", pattern, MODVER);
	if (NULL == (fp_mod_file = fopen(outfile1, "w+"))) {
		fprintf(stderr, "\nCould not open output file [%s] for output, source[%s,%d,%s]\n",
				outfile1, __FILE__, __LINE__, __FUNCTION__);
		fprintf(fperrors, "\nCould not open output file [%s] for output\n", outfile1);
		exit(1);
	}

	fprintf(fp_mod_file, "#USE_SIGNAL_HEADER:SH0\n");
	fprintf(fp_mod_file, "# Codes are defined in aliasmap.h (FC_xxxxxxxx)\n");
	fprintf(fp_mod_file, "#aliasmap %lld %d\n", CKS_aliasmap_h, FS_aliasmap_h);
	fprintf(fp_mod_file, "#chk_problem_type %lld %d\n", CKS_chk_problem_type_ggm_c, FS_chk_problem_type_ggm_c);
	fprintf(fp_mod_file, "#compact_cycletbl %lld %d\n", CKS_compact_cycletbl_ggm_c, FS_compact_cycletbl_ggm_c);
	fprintf(fp_mod_file, "#edgeset_make_wfms %lld %d\n", CKS_edgeset_make_wfms_ggm_c, FS_edgeset_make_wfms_ggm_c);
	fprintf(fp_mod_file, "#find_origin %lld %d\n", CKS_find_origin_ggm_c, FS_find_origin_ggm_c);
	fprintf(fp_mod_file, "#gct_gen_mod8 %lld %d\n", CKS_gct_gen_mod8_ggm_c, FS_gct_gen_mod8_ggm_c);
	fprintf(fp_mod_file, "#global %lld %d\n", CKS_global_ggm_c, FS_global_ggm_c);
	fprintf(fp_mod_file, "#includes %lld %d\n", CKS_includes_ggm_h, FS_includes_ggm_h);
	fprintf(fp_mod_file, "#common_includes %lld %d\n", CKS_common_includes_h, FS_common_includes_h);
	fprintf(fp_mod_file, "#make_hexmuxlist %lld %d\n", CKS_make_hexmuxlist_ggm_c, FS_make_hexmuxlist_ggm_c);
	fprintf(fp_mod_file, "#make_scan_headers_ggm %lld %d\n", CKS_make_scan_headers_ggm_c, FS_make_scan_headers_ggm_c);
	fprintf(fp_mod_file, "#modify_waveforms %lld %d\n", CKS_modify_waveforms_ggm_c, FS_modify_waveforms_ggm_c);
	fprintf(fp_mod_file, "#parse_actable %lld %d\n", CKS_parse_actable_ggm_c, FS_parse_actable_ggm_c);
	fprintf(fp_mod_file, "#parse_cyctbl %lld %d\n", CKS_parse_cyctbl_ggm_c, FS_parse_cyctbl_ggm_c);
	fprintf(fp_mod_file, "#process_all_edgesets %lld %d\n", CKS_process_all_edgesets_ggm_c, FS_process_all_edgesets_ggm_c);
	fprintf(fp_mod_file, "#process_waveforms %lld %d\n", CKS_process_waveforms_ggm_c, FS_process_waveforms_ggm_c);
	fprintf(fp_mod_file, "#purge_actable %lld %d\n", CKS_purge_actable_ggm_c, FS_purge_actable_ggm_c);
	fprintf(fp_mod_file, "#read_cycletbl %lld %d\n", CKS_read_cycletbl_ggm_c, FS_read_cycletbl_ggm_c);
	fprintf(fp_mod_file, "#resolve_list %lld %d\n", CKS_resolve_list_ggm_c, FS_resolve_list_ggm_c);
	fprintf(fp_mod_file, "#separate_actable %lld %d\n", CKS_separate_actable_ggm_c, FS_separate_actable_ggm_c);
	fprintf(fp_mod_file, "#get_pins\" %lld %d\n", CKS_get_pins_ggm_c, FS_get_pins_ggm_c);

	if (NULL == (fpwaves = fopen(WFTMODVER, "w"))) {
		fprintf(stderr, "\nCan't open file [%s], source[%s,%d,%s]\n", WFTMODVER, __FILE__, __LINE__, __FUNCTION__);
		fprintf(fperrors, "\nCan't open file [%s]\n", WFTMODVER);
		exit(1);
	}
	strcpy(inhfile, WFTINHVER);
	if (ACDATA) strcpy(inhfile, "/dev/null");

	if (NULL == (fpinherit = fopen(inhfile, "w+"))) { /* now write/read, so we can rewind and fix the PUSHBACK CYCLE Periods */
		fprintf(stderr, "\nCan't open file [%s], source[%s,%d,%s]\n", inhfile, __FILE__, __LINE__, __FUNCTION__);
		fprintf(fperrors, "\nCan't open file [%s]\n", inhfile);
		exit(1);
	}

	if (NULL == (fppreopt = fopen(WFTMODVERpre, "w"))) {
		fprintf(stderr, "\nCan't open file [%s], source[%s,%d,%s]\n", WFTMODVERpre, __FILE__, __LINE__, __FUNCTION__);
		fprintf(fperrors, "\nCan't open file [%s]\n", WFTMODVERpre);
		exit(1);
	}

	fprintf(fpwaves, "%s\n\n", ENVISIONTOP);
	fprintf(fpinherit, "%s\n\n", ENVISIONTOP);
	generictime = time(0);
	strcpy(mydate, ctime(&generictime));
	mydate[strlen(mydate) - 1] = '\0';
	fprintf(fpwaves, "//Original run date:%s\n//Compile date:%s\n", mydate, datestr);
	fprintf(fpinherit, "//Original date:%s\n//Compile date:%s\n", mydate, datestr);

	get_pins(fpin_pin, fpin_device, infile3, muxpin);
	orgcnt = 0;

	acwaves = NULL;
	actablelines = parse_actable(infile4, fpwaves);
	fprintf(fpstatus, "ACWAVES@=%p, source[%s,%d,%s]\n", acwaves, __FILE__, __LINE__, __FUNCTION__);
	fflush(stdout);

/***************************************************/
/* BEGIN MAIN LOOP */
/***************************************************/

	maxcyclen = read_cycletbl(infile1);

	fprintf(stderr, "Found %d CycleSetMDs, source[%s,%d,%s]\n", maxcycset, __FILE__, __LINE__, __FUNCTION__);
	fprintf(stderr, "Found %d VectorMapSets, source[%s,%d,%s]\n", maxvmsets, __FILE__, __LINE__, __FUNCTION__);
	ret = compact_cycletbl();
	fprintf(stderr, "reduced total CycleSetMDs to %d, source[%s,%d,%s]\n",
			maxcycset - ret, __FILE__, __LINE__, __FUNCTION__);
	parse_cyctbl(actablelines, infile4, fpwaves, fpinherit, fp_mod_file, maxcyclen, muxpin);

	fprintf(stderr, "worse case cell count=%d, source[%s,%d,%s]\n", worstcasecellcnt, __FILE__, __LINE__, __FUNCTION__);
	make_hexmuxlist(fp_mod_file, muxpin, maxcyclen);
	make_scan_headers(fp_mod_file, muxpin);
	if (EVX2 && NOPUSHCYC == 0) fprintf(fp_mod_file, "#USE_PATTERNMODE_EVX2\n");
	else if (EVX2 && NOPUSHCYC == 1) {
		fprintf(fp_mod_file, "#DISABLED_PATTERNMODE_EVX2\n");
		fprintf(fperrors,"EVX2.0:Needed PATTERNMODE evX2 but GCT_GEN_MOD called explictly with -n (no evX2).\n");
		fprintf(fperrors,"EVX2.1:This will mean multicycle windows will not be handled properly!\n");
		fprintf(fperrors,"EVX2.2:Improper use of this option can mean bad devices may pass!\n");
		fprintf(fperrors,"EVX2.3:Seriously consider removing the \'-n\' option from GCT_GEN_MOD\n");
		}
	write_paramsINHC();
	fclose(fpwaves);
	fclose(fpin_pin);
	fclose(fpstatus);
	fclose(fperrors);
	free(acwaves);
	purge_actable(fpinherit, fp_mod_file, muxpin);
	fclose(fp_mod_file);
	fclose(fpinherit);
	return (0);
}
