#include <stdio.h>
#include <strings.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include "include_vcp.h"
#include "aliasmap.h"

/***************************************************************************************/
/***************************************************************************************/
/** WARNING: The code in this rountine for repeat compression is quite complicated.   **/
/**          This routine buffers results from one call to the next.                  **/
/**          Any modifications to this code can result in broken output.              **/
/**          Do not modify this section without fully testing the modifications       **/
/**          thoroughly. Debugging lines are left in the code to help verify the      **/
/**          correct operation, change the value of DEBUG to enable these prints.     **/
/***************************************************************************************/
/***************************************************************************************/
/*                This routine should be synchronized with outputvector_evX2()          */
/***************************************************************************************/
/***************************************************************************************/
int outputvector(FILE * fpout1, char *out_vector, char *wft, char *DMI,
				 long repeatcount, char *comment, char *microinstr, int CPM,int line) {
	char tempstr[MULTILINESIZE + 1], tempstr2[MULTILINESIZE + 1], commentstr[MULTILINESIZE + 1];
	char shortcomment[MULTILINESIZE + 1];
	static char vector_hold[READLINELEN + 1], wft_hold[MAXGCTLEN + 1];
	static char printhold[MULTILINESIZEBIG + 1];
	static long repeat_counter, line_cnt = 0;
	static long VMR = 0, VRE = 0;
	boolean vector_matches_prev, vector_is_vector, vector_is_new, flush_buff;
	boolean vector_is_microinstr, vector_is_label, is_last_vector, wft_is_empty, vector_is_empty;
	int max_repeat, printholdlen;
	static int callcount=0;
	callcount++;
//	fprintf(fpout1,"\"XCC%d\"\n",callcount);
//	if (out_vector[0]!='\0') fprintf(fpout1,"BUFFERED[%s]%ld\n",out_vector,repeatcount);
	if (line_cnt == 0) {
		printhold[0] = '\0';
		printholdlen = 0;
		commentstr[0] = '\0';
		strcpy(vector_hold, NO_VECTOR);
		strcpy(wft_hold, NO_WFT);
		repeat_counter = 0;
	}
	wft_is_empty = (0 == strcmp(wft, NO_WFT));
	vector_is_empty = (0 == strcmp(out_vector, NO_VECTOR));
	is_last_vector = (repeatcount == VECTOR_DONE);
	flush_buff = (repeatcount == VECTOR_FLUSH);
	vector_is_microinstr = (out_vector[0] == AM_continueDRV && (0 == strcmp(wft, DEF_WFT) || wft_is_empty));
	vector_is_label = (out_vector[0] == '$');
	vector_is_vector = (!vector_is_label && !vector_is_microinstr && !wft_is_empty && !vector_is_empty);
	vector_matches_prev = (vector_is_vector && 0 == strcmp(out_vector, vector_hold) && 0 == strcmp(wft, wft_hold));
	vector_is_new = ((vector_is_vector && !vector_matches_prev) || !REPEAT_COMPRESSION);
	max_repeat = ((CPM == 0) ? MAX_RPT_DPM : MAX_RPT_CPM);
	if (DEBUG) fprintf(fpstatus, "===========================================================\n");
	if (DEBUG) fprintf(fpstatus, "OAV[%s]<%s>{%s}\n", out_vector, microinstr, wft);
	if (DEBUG) fprintf(fpstatus, "WE=%d,VE=%d,ILV=%d,VIM=%d,VIL=%d,VIV=%d,VMP=%d,VIN=%d\n",
				wft_is_empty, vector_is_empty, is_last_vector,
				vector_is_microinstr, vector_is_label, vector_is_vector,
				vector_matches_prev, vector_is_new);
	if (flush_buff) {
		if (repeat_counter>1) {
			if (commentstr[0] == '\0') {
				if (printhold[0]!='\0') fprintf(fpout1, "%s <RPT %ld> \"01CC%d\"\n", printhold, repeat_counter,callcount); 
				printhold[0] = '\0';
				printholdlen = 0;
				vector_hold[0] = '\0';
				repeat_counter = 0;
				}
			else {
				if (printhold[0]!='\0') fprintf(fpout1, "%s <RPT %ld>\"VNIR7=%ld %s 02CC%d\"\n", printhold, repeat_counter, VNIR, commentstr,callcount); 
				printhold[0] = '\0';
				printholdlen = 0;
				vector_hold[0] = '\0';
				commentstr[0] = '\0';
				repeat_counter = 0;
				}
			}
		else {
			if (commentstr[0] == '\0') {
				if (printhold[0]!='\0') fprintf(fpout1, "%s \"03CC%d\"\n", printhold,callcount); 
				printhold[0] = '\0';
				printholdlen = 0;
				vector_hold[0] = '\0';
				repeat_counter = 0;
				}
			else { 
				if (printhold[0]!='\0') fprintf(fpout1, "%s \"VNIR7=%ld %s 04CC%d\"\n", printhold, VNIR, commentstr,callcount); 
				printhold[0] = '\0';
				printholdlen = 0;
				vector_hold[0] = '\0';
				commentstr[0] = '\0';
				repeat_counter = 0;
				}
			}
		return(5);
		} /* end flush_buff */

	else if (is_last_vector) {		/* this is to correctly deal with the end label */
		if (!CPM) {
			if (repeat_counter > 1) {
				while (repeat_counter > max_repeat) {
					fprintf(fpout1, "%s <RPT %d> \"05CC%d\"\n", printhold, max_repeat,callcount);	/* it is wrong to have "VNIR+=max_repeat;" here!!! */
					VC++;
					repeat_counter -= max_repeat;
					VRE++;
				}
//				fprintf(fpout1, "%s \"06CC%d\"\n", out_vector,callcount);	/* output the end label */
				fprintf(fpout1, "%s \n", out_vector);	/* output the end label */
				fprintf(fpout1, "%s <RPT %ld>\"VNIR0=%ld 07CC%d\"\n", printhold, repeat_counter, VNIR,callcount);	/* it is wrong to have "VNIR+=max_repeat;" here!!! */
				VC++;
			}
			else {
				pare_comment(shortcomment, commentstr);
				strcpy(commentstr, shortcomment);	/* shorten the comment */
				fprintf(fpout1, "%s \"08CC%d\"\n", out_vector,callcount);
				if (commentstr[0] == '\0' || SUPPRESS_COMMENTS) {
					fprintf(fpout1, "%s\"VNIR1=%ld 09CC%d\"\n", printhold, VNIR,callcount);
					VC++;
				}				/* if there isn't a comment don't print one */
				else {
					fprintf(fpout1, "%s \"VNIR2=%ld%s 10CC%d\"\n", printhold, VNIR, commentstr,callcount);
					VC++;
				}
			}
		}
/* If CPM then we need to spit out the last vector BEFORE the end label because we add the RET */
		if (CPM) {
			if (repeat_counter > 1) {
				while (repeat_counter > max_repeat) {
					fprintf(fpout1, "%s <RPT %d> \"11CC%d\"\n", printhold, max_repeat,callcount);	/* it is wrong to have "VNIR+=max_repeat;" here!!! */
					VC++;
					repeat_counter -= max_repeat;
					VRE++;
				}
				fprintf(fpout1, "%s <RPT %ld> \"12CC%d\"\n ", printhold, repeat_counter,callcount);	/* it is wrong to have "VNIR+=max_repeat;" here!!! */
				VC++;
			}
			else {
				pare_comment(shortcomment, commentstr);
				strcpy(commentstr, shortcomment);	/* shorten the comment */
				if (commentstr[0] == '\0' || SUPPRESS_COMMENTS) {
					fprintf(fpout1, "%s \"13CC%d\"\n", printhold,callcount);
					VC++;
				}				/* if there isn't a comment don't print one */
				else {
					fprintf(fpout1, "%s \"%s 14CC%d\"\n", printhold, commentstr,callcount);
					VC++;
				}
			}
			fprintf(fpout1, "%s \"15CC%d\"\n", out_vector,callcount);	/* output the end label */
			fprintf(fpout1, "* %s * %s %s;<RET>\"REMAP %s to %s 16CC%d\"\n", 
				dummy_vector, REMAP_DEF_WFT, NORMALSGHDR, DEF_WFT, REMAP_DEF_WFT,callcount);	/* output the end label */
			/*         fprintf(fpout1,"* %s * %s %s;<RPT 512>\n",dummy_vector,DEF_WFT,NORMALSGHDR); *//* output the end label */
			VC++;
		}
		if (VNIR < 128 || VC < 32) {
			fprintf(fperrors,
					"NON_fatal_error:%s:File [%-60s] does not have enough vectors[%ld]/cycles[%ld], padding with hold cycles\n",
					progstr, infile_orig, VC, VNIR);
			fprintf(stderr,
					"NON_fatal_error:%s:File [%s] does not have enough vectors[%ld]/cycles[%ld], padding with hold cycles\n",
					progstr, infile_orig, VC, VNIR);
			for (VC = VC; VC <= 32; VC++, VNIR++)
				fprintf(fpout1, "* %s * %s %s;\"pad vector VNIR3=%ld 17CC%d\"\n", 
						dummy_vector, wft_hold, NORMALSGHDR, VNIR, callcount);
			if (VNIR <= 128) {
				fprintf(fpout1, "* %s * %s %s;<RPT %ld>\"pad vector VNIR4=%ld 18CC%d\"\n",
						dummy_vector, wft_hold, NORMALSGHDR, 128 - VNIR, VNIR, callcount);
				VNIR += (128 - (VNIR + (32 - VC)));
			}
		}
/* if shutdown available print it out to close any open strobes, C32 had this issue */
		if (found_shut) {
			fprintf(fpout1, "* %s* %s %s; <RPT 5>\"AUTO_VCP_SHUTDOWN\"\n",vector_shut2,REMAP_DEF_WFT,NORMALSGHDR);
		}
		
		fprintf(fpout1, "\"VNIR5=%ld 19CC%d\"\n}\n", VNIR,callcount);	/* output the end label */
		fprintf(stdout, "\n%ld lines printed\n", line_cnt);
		fprintf(stdout, "[%s] %ld %s vectors successfully processed.\n", infile_orig, VN, (CPM) ? "CPM" : "DPM");
		fprintf(stderr, "[%s] %ld %s vectors successfully processed.\n", infile_orig, VN, (CPM) ? "CPM" : "DPM");
		fprintf(stdout, "Total cycle count:%ld Total Vector count:%ld\n", VNIR, VC);
		fprintf(stdout, "vector count reduced by %ld with repeat compression.\n", VMR);
		fprintf(stdout, "vector count increased by %ld due to repeat expansion.\n", VRE);
		fprintf(stdout, "vector count increased by %ld due to repeat expansion.\n", VRE);
		fprintf(stdout, "[%s] remapped to [%s]shut=[%c]\n", DEF_WFT, REMAP_DEF_WFT, (found_shut == 2) ? 'Y' : 'N');
		fprintf(fpstatus, "RM[%s][%s] remapped to [%s]shut=[%c]\n", infile_orig, DEF_WFT, REMAP_DEF_WFT, (found_shut == 2) ? 'Y' : 'N');
		if (CPM && VN > 4000) {
			fprintf(stderr, "CPM pattern[%s] won't fit[%ld] in CPM you'll need to address this!\n", infile_orig, VN);
			fprintf(fperrors, "CPM pattern[%s] won't fit[%ld] in CPM you'll need to address this!\n", infile_orig, VN);
		}
		return (0);
	}							/* end of vector is last! */
	if ((vector_is_new || vector_is_label || vector_is_microinstr) && printhold[0] != 0) {
		if (DEBUG) fprintf(fpstatus, "OV[%s]<%s>\n", out_vector, microinstr);
		if (DEBUG) fprintf(fpstatus, "~R_C:%ldRC:%ld,H:%s\n", repeat_counter, repeatcount, printhold);
		if (repeat_counter > 1) {
			if (DEBUG) fprintf(fpstatus, "#R_C:%ldRC:%ld,H:%s\n", repeat_counter, repeatcount, printhold);
			strcpy(tempstr2, printhold);
			printhold[0] = '\0';
			printholdlen = 0;
			while (repeat_counter > max_repeat) {
				if ((repeatcount % 2500) == 0) 
					fprintf(fpstatus, "[%ld]MAX REPEAT %d reached...continuing\n", countrpts, max_repeat);
				countrpts++;
				if (DEBUG) fprintf(fpstatus, "$R_C:%ldRC:%ld,H:%s\n", repeat_counter, repeatcount, printhold);
				sprintf(tempstr, "%s <RPT %d>\n", tempstr2, max_repeat);
				VC++;
				if (printholdlen + strlen(tempstr) > MULTILINESIZEBIG) {
					fprintf(fpout1, "%s\"20CC%d\"\n", printhold,callcount);
					printhold[0] = '\0';
					printholdlen = 0;
					fprintf(stderr, "EXCEEDING BUFFERSIZE at %d ... emptying buffer\n", __LINE__);
					fprintf(fperrors, "EXCEEDING BUFFERSIZE at %d ...emptying buffer\n", __LINE__);
				}
				strncat(printhold, tempstr, MULTILINESIZEBIG);
				printholdlen += strlen(tempstr);
				repeat_counter -= max_repeat;
				VRE++;
			}
			sprintf(tempstr, "%s <RPT %ld> ", tempstr2, repeat_counter);
			VC++;
			if (printholdlen + strlen(tempstr) > MULTILINESIZEBIG) {
				fprintf(fpout1, "%s \"21CC%d\"\n", printhold,callcount);
				printhold[0] = '\0';
				printholdlen = 0;
				fprintf(stderr, "EXCEEDING BUFFERSIZE at %d ... emptying buffer\n", __LINE__);
				fprintf(fperrors, "EXCEEDING BUFFERSIZE at %d ...emptying buffer\n", __LINE__);
			}
			strncat(printhold, tempstr, MULTILINESIZEBIG);
			printholdlen += strlen(tempstr);
			if (DEBUG)
				fprintf(fpstatus, "^R_C:%ldRC:%ld,H:%s\n", repeat_counter, repeatcount, printhold);
		}
		pare_comment(shortcomment, commentstr);
		strcpy(commentstr, shortcomment);	/* shorten the comment */
		if (commentstr[0] == '\0' || SUPPRESS_COMMENTS) {
			VC++;
			fprintf(fpout1, "%s \"22CC%d,%d\"\n", printhold,callcount,line);
		}						/* if there isn't a comment don't print one */
		else {
			VC++;
			fprintf(fpout1, "%s \"VNIR7=%ld %s 23CC%d,%d\"\n", printhold, VNIR, commentstr,callcount,line);
		}
		commentstr[0] = '\0';
		printhold[0] = '\0';
		printholdlen = 0;
		repeat_counter = 0;
	}
	if (DEBUG) fprintf(fpstatus, "!R_C:%ldRC:%ld,H:%s\n", repeat_counter, repeatcount, printhold);
	if (vector_is_vector) {
		repeat_counter += repeatcount;
		if (DEBUG) fprintf(fpstatus, "@R_C:%ldRC:%ld,H:%s\n", repeat_counter, repeatcount, printhold);
		if (vector_matches_prev && REPEAT_COMPRESSION) {
			/* looks like we can compress the vector */
			VMR++;
		}
		else {
			/* if (0==strcmp(REMAP_DEF_WFT,DEF_WFT)) strcpy(REMAP_DEF_WFT,wft); *//* get first non-DEF_WFT waveform reference */
			if (found_shut != 2 && strcmp(wft,NO_VECTOR)!=0) strcpy(REMAP_DEF_WFT, wft);	/* modify it to the last reference, iff we don't have shutdowns! */
			sprintf(printhold, "* %s* %s %s;", out_vector, wft, NORMALSGHDR);
		}
		printholdlen = strlen(printhold);
		VN++;
		VNIR++;
		strcpy(vector_hold, out_vector);	/* keep for check repeat compression */
//		fprintf(fpout1,"\\%s\\\n",vector_hold);
		strcpy(wft_hold, wft);
	}

	else if (vector_is_label) {
		sprintf(tempstr, "%s", out_vector);
		strcpy(printhold, tempstr);
		printholdlen = strlen(printhold);
		strcpy(vector_hold, NO_VECTOR);	/* keep for check repeat compression */
		strcpy(wft_hold, NO_WFT);
	}
	else if (vector_is_microinstr) {
		/* we should really try to put something here to combine the microinstruction onto the previous vector */
		if (DEBUG) fprintf(fpstatus, "&R_C:%ldRC:%ld,H:%s\n", repeat_counter, repeatcount, printhold);
		sprintf(tempstr, "* %s* %s %s; %s\"REMAP %s to %s\"", out_vector, REMAP_DEF_WFT, NORMALSGHDR, microinstr, DEF_WFT, REMAP_DEF_WFT);
		strcpy(printhold, tempstr);
		printholdlen = strlen(printhold);
		strcpy(vector_hold, out_vector);	/* keep for check repeat compression */
		strcpy(wft_hold, REMAP_DEF_WFT);
	}
	if (0 != strcmp(DMI, NO_DMI)) {
		if (strlen(DMI) + strlen(commentstr) < MULTILINESIZE)
			strncat(commentstr, DMI, MULTILINESIZE);	/* keep as much as possible */
		strcpy(DMI, NO_DMI);
	}
	if (0 != strcmp(comment, NO_COMMENT)) {	/* there's a comment ... */
		if (strlen(comment) + strlen(commentstr) < MULTILINESIZE)
			strncat(commentstr, comment, MULTILINESIZE);	/* keep as much as possible */
		comment[0] = '\0';		/* strcpy(comment,NO_COMMENT); */
	}
	line_cnt++;
	if (DEBUG) fflush(fpout1);			/* this helps to get as much info out to the file before a crash */
	if (DEBUG) fprintf(fpstatus, "=R_C:%ldRC:%ld,H:%s\n", repeat_counter, repeatcount, printhold);
	repeatcount = 1;
	return (repeatcount);
}
