
long fileoutinhst, fileoutend, fileininhst;
int wftpending;
char *ptr, *ptr1, *ptr2, *ptr3, *ptr4, *ptr5;
int k, l;
int ininherit;
int sizehead;
char fullwftname[READLINELEN + 1];
char tstr[NUMPINS + 1], newstr[NUMPINS + 1];
char hexproc[READLINELEN + 1], fieldset[READLINELEN + 1];
char tempgrpexpand2[READLINELEN * 20 + 1];
char readstr[READLINELEN];
char pinheader[PINSIZE][NUMPINS];

int move_push_close(int modify, char *tbuf);
int swap_alias(char *buffer, int *wfmcode0, int *wfmcode1);
int add_open_add_full_window(int modify, char *tbuf, char *newcells);
int process_edgeset_waveform(int actablelines, char *GCTNAME, char *cyclebuff, long *tell, int which,
		 int *forward, char *pin, int DSET, int CNT, int *modcode, char name[][FINDME_SIZE + 1], int en[], int enable_edge[]);

/* this is called by process_edgeset_waveform() and process_edgesetdelay_waveform(), code was common */
int old_break_up_edges(int en[], int en1[], int *startfrom, char name[][1000], char *findme, int which, int *forward)
{
	/* findme & which are inputs, findme is the string we're processing for EdgeSet..., which says where in the actable.p file */
	/* outputs are en, en1, and startfrom (which edge does the call startfrom) */
	int ne, i, inc, new_ne;
	char name0[FINDME_SIZE + 1], namei[FINDME_SIZE + 1], *ptrOP, *ptrC,
		temp[FINDME_SIZE + 1];

	ne = 0;
	if (strstr(findme, "Edge6") != 0) {
		fprintf(fperrors, "We can't handle 6 edges! [Edge6]\n");
		fprintf(stderr,
				"We can't handle 6 edges! [Edge6] source[%s,%d,%s]\n",
				__FILE__, __LINE__, __FUNCTION__);
		exit(1);
	}
	for (i = 0; i < MAX_EDGES; i++)
		inc = en1[i] = en[i] = 0;
	if (NULL != strstr(findme, "Edge1")) {
		*startfrom = 0;
		ne = 1;
		strcpy(name[*startfrom], findme);
		en1[0] = 1;
		en[0] = 0;
		strcpy(temp, acwaves[which + 1].w);
		if (NULL != strstr(temp, "Edge2")) {
			strcpy(name[1], temp);
			en1[ne] = 1;
			en[ne] = 1;
			ne++;
			inc++;
			strcpy(temp, acwaves[which + 2].w);
			if (NULL != strstr(temp, "Edge3")) {
				strcpy(name[2], temp);
				en1[ne] = 1;
				en[ne] = 2;
				ne++;
				inc++;
				strcpy(temp, acwaves[which + 3].w);
				if (NULL != strstr(temp, "Edge4")) {
					strcpy(name[3], temp);
					en1[ne] = 1;
					en[ne] = 3;
					ne++;
					inc++;
					strcpy(temp, acwaves[which + 4].w);
					if (NULL != strstr(temp, "Edge5")) {
						strcpy(name[4], temp);
						en1[ne] = 1;
						en[ne] = 4;
						ne++;
						inc++;
					}
				}
			}
		}
	}
	else if (NULL != strstr(findme, "Edge2")) {	/* use previous Edge1 */
		fprintf(fpstatus,
				"\nstarting with Edge2[%s]\np[%s], source[%s,%d,%s]\n",
				findme, name[0], __FILE__, __LINE__, __FUNCTION__);
		*startfrom = 1;
		ne = 2;
		strcpy(name[*startfrom], findme);
		en1[1] = 1;
		en[1] = 1;
		en1[0] = 1;
		en[0] = 0;
		strcpy(temp, acwaves[which + 1].w);
		if (NULL != strstr(temp, "Edge3")) {
			strcpy(name[2], temp);
			en1[ne] = 1;
			en[ne] = 2;
			ne++;
			inc++;
			strcpy(temp, acwaves[which + 2].w);
			if (NULL != strstr(temp, "Edge4")) {
				strcpy(name[3], temp);
				en1[ne] = 1;
				en[ne] = 3;
				ne++;
				inc++;
				strcpy(temp, acwaves[which + 3].w);
				if (NULL != strstr(temp, "Edge5")) {
					strcpy(name[4], temp);
					en1[ne] = 1;
					en[ne] = 4;
					ne++;
					inc++;
				}
			}
		}
	}
	else if (NULL != strstr(findme, "Edge3")) {	/* use previous Edge1 & Edge2 */
		fprintf(fpstatus,
				"\nstarting with Edge3[%s]\np[%s], source[%s,%d,%s]\n",
				findme, name[0], __FILE__, __LINE__, __FUNCTION__);
		*startfrom = 2;
		ne = 3;
		strcpy(name[*startfrom], findme);
		en1[2] = 1;
		en[2] = 1;
		en1[1] = 1;
		en[1] = 0;
		en1[0] = 1;
		en[0] = 1;
		strcpy(temp, acwaves[which + 1].w);	/* inc will be one shy... */
		if (NULL != strstr(temp, "Edge4")) {	/* chances are we don't have an isolated Edge4 */
			strcpy(name[3], temp);
			en1[ne] = 1;
			en[ne] = 3;
			ne++;
			inc++;
			strcpy(temp, acwaves[which + 2].w);	/* inc will be one shy... */
			if (NULL != strstr(temp, "Edge5")) {	/* chances are we don't have an isolated Edge4 */
				strcpy(name[4], temp);
				en1[ne] = 1;
				en[ne] = 4;
				ne++;
				inc++;
			}
		}
	}
	else if (NULL != strstr(findme, "Edge4")) {	/* use previous Edge1 & Edge2 & Edge3 */
		fprintf(fpstatus,
				"\nstarting with Edge4[%s]\np[%s], source[%s,%d,%s]\n",
				findme, name[0], __FILE__, __LINE__, __FUNCTION__);
		*startfrom = 3;
		ne = 4;
		strcpy(name[*startfrom], findme);
		en1[3] = 1;
		en[3] = 1;
		en1[2] = 1;
		en[2] = 0;
		en1[1] = 1;
		en[1] = 1;
		en1[0] = 1;
		en[0] = 1;
		strcpy(temp, acwaves[which + 1].w);	/* inc will be one shy... */
		if (NULL != strstr(temp, "Edge5")) {	/* chances are we don't have an isolated Edge4 */
			strcpy(name[4], temp);
			en1[ne] = 1;
			en[ne] = 4;
			ne++;
			inc++;
		}
	}
	ptrC = strchr(findme, ',');
	if (ptrC != NULL)
		*ptrC = '\0';
	ptrOP = strchr(findme, '(');
	if (ptrOP != NULL)
		strcpy(name0, ptrOP);
	if (ptrC != NULL)
		*ptrC = ',';			/* set it back */
	else
		strcpy(name0, findme);
	for (new_ne = -1, i = 0; i < ne; i++) {
		ptrC = strchr(name[i], ',');
		if (ptrC != NULL)
			*ptrC = '\0';
		ptrOP = strchr(name[i], '(');
		if (ptrOP != NULL)
			strcpy(namei, ptrOP);
		else
			strcpy(namei, name[i]);
		if (ptrC != NULL)
			*ptrC = ',';		/* set it back */
		if (strcmp(name0, namei) != 0) {
			fprintf(stdout,
					"\nstartfrom=%d,ne=%d, truncating edges to %d since [%s]!=[%s], source[%s,%d,%s]\n",
					*startfrom, ne, i, name0, namei, __FILE__, __LINE__,
					__FUNCTION__);
			if (new_ne == -1)
				new_ne = i;
			continue;
		}
	}
	if (new_ne != -1) {			/* if we had to find more edges... */
		ne = new_ne;
		which = new_ne;
		if (new_ne > 1)
			*forward = new_ne - 1;	/* how many lines did we read forward? */
	}
	return (ne);
}

int add_open_add_full_window(int modify, char *tbuf, char *newcells)
{
	int i, bad;
	char *ptrE[MAXCELLS], *ptrOP[MAXCELLS];	/* pointer to end of each cell */
	char *ptrCMPC, *ptrOPQ, *ptrCLQ, *ptrSP1, *ptrSP2, *ptrCAT, *ptrBRACE;
	char swapcell[10000], swapafter[10000], swapbefore[10000];
	char swapopen[1000], swapremainder[1000], addopen[1000], cat[100],
		cellname[100], cellpins[1000];
	char lnewcell[10000], modcell[10000];
	char hold;
	bad = 0;
	ptrOP[0] = ptrE[0] = tbuf;	/* this will point at the first comment */
	for (i = 1; i <= cellcnt; i++) {
		ptrOP[i] = strstr(ptrE[i - 1], "Cell ");	/* first open, we're assuming one space in front!! */
		ptrE[i] = strstr(ptrE[i - 1], "\n}\n");
		if (ptrE[i] == NULL || ptrOP[i] == NULL) {
			bad = 1;
			goto BADAOP;
		}
		ptrE[i] += 3;			/* move it past */
//      fprintf(stdout,"CELL%d#%d[%s]\n",modify,i,ptrOP[i]);
	}
	hold = *(ptrOP[modify]);
	*(ptrOP[modify]) = '\0';
	strcpy(swapbefore, tbuf);
	*(ptrOP[modify]) = hold;

	hold = *(ptrE[modify] + 1);
	*(ptrE[modify] + 1) = '\0';
	strcpy(swapcell, ptrOP[modify]);
	*(ptrE[modify] + 1) = hold;
	fprintf(stdout, "swapcell***[%s]***\n", swapcell);
	strcpy(swapafter, ptrE[modify] + 1);

////ES:EdgeSet(DBUSstrobeoffWF,Edge1,StrobeOff,t[tref]+t[thDW]-t[loosdelay]+t[tgb]+ctcf)
//Cell "GDBUS" e/E DBUSstrobeoffWF_DSET0eE_cat_BEKR {
//    Data 2/3;
//    Drive {
//        Waveform {
//            DriveOff @"  tref +  thDW -  loosdelay +  tgb +ctcf+0.000ns ";
//        }
//    }
//    Compare {
//        Waveform {
//            CompareClose @"  tref +  thDW -  loosdelay +  tgb +ctcf+0.000ns ";
//        }
//    }
//}
//
	ptrOPQ = strchr(swapcell, '\"');
	if (ptrOPQ == NULL) {
		bad = 2;
		goto BADAOP;
	}
	ptrCLQ = strchr(ptrOPQ + 1, '\"');
	if (ptrCLQ == NULL) {
		bad = 3;
		goto BADAOP;
	}

	hold = *ptrCLQ;
	*ptrCLQ = '\0';
	strcpy(cellpins, ptrOPQ + 1);
	*ptrCLQ = hold;

	ptrSP1 = strchr(ptrCLQ, ' ');
	if (ptrSP1 == NULL) {
		bad = 4;
		goto BADAOP;
	}
	ptrSP2 = strchr(ptrSP1 + 1, ' ');
	if (ptrSP2 == NULL) {
		bad = 5;
		goto BADAOP;
	}
	ptrCAT = strstr(ptrSP2, "_cat");
	if (ptrCAT == NULL) {
		bad = 6;
		goto BADAOP;
	}
	ptrBRACE = strchr(ptrCAT + 1, '{');	/* } */
	if (ptrBRACE == NULL) {
		bad = 7;
		goto BADAOP;
	}

	hold = *ptrCAT;
	*ptrCAT = '\0';
	strcpy(cellname, ptrSP2 + 1);
	*ptrCAT = hold;

	hold = *(ptrBRACE - 1);
	*(ptrBRACE - 1) = '\0';
	strcpy(cat, ptrCAT + sizeof("_cat"));
	*(ptrBRACE - 1) = hold;

	ptrCMPC = strstr(swapcell, "CompareClose");
	if (ptrCMPC == NULL) {
		bad = 8;
		goto BADAOP;
	}

	*ptrCMPC = '\0';
	strcpy(swapopen, swapcell);
	*ptrCMPC = 'C';

	strcpy(swapremainder, ptrCMPC);	/* everything after & including CompClose */

	sprintf(addopen, "CompareOpen @\"t_0_open1\";");

	/* first swapcell, then CompOpen;\n          then CompClose then +t_Per_Push"; then cell remainder */
	sprintf(modcell, "%s%s\n         %s", swapopen, addopen, swapremainder);
//   fprintf(stdout,"swapopen:<%s>\n",swapopen);
//   fprintf(stdout,"addopen:[%s]\n",addopen);
	fprintf(stdout, "swapremainder:(%s)\n", swapremainder);
	sprintf(lnewcell,
			"Cell \"%s\" a/A %s_FULLCYC_cat_%s {\n   Data 0/1;\n   Compare {\n      Waveform {\n         CompareOpen @\"t_0_open2\";\n         CompareClose @\"t_per_close2\";\n      }\n   }\n}\n",
			cellpins, cellname, cat);
	sprintf(tbuf, "%s//====BADDOPEN====\n%s%s//===EADDOPEN===\n",
			swapbefore, modcell, swapafter);
	fprintf(stdout, "tbuf:[%s]\n", tbuf);
	strcat(newcells, lnewcell);
	if (!bad)
		return (0);

  BADAOP:fprintf(stderr,
			"Bad=%d, <add>We didn't find what we were looking for in the cell[%d] out2[%60.60s]\n",
			bad, modify, swapcell);
	exit(1);
	return (-1);
}

int move_push_close(int modify, char *tbuf)
{
	int i, bad;
	char *ptrE[MAXCELLS], *ptrOP[MAXCELLS];	/* pointer to end of each cell */
	char *ptrSEMIC, *ptrCMPC, *ptrSEMIO, *ptrCMPO, *ptrOPQ;
	char swapcell[10000], swapafter[10000], swapbefore[10000];
	char swapclose[1000], swapopen[1000], swapremainder[1000],
		swapcloseinsideq[1000];
	char modcell[10000];
	char hold;
	bad = 0;
	ptrOP[0] = ptrE[0] = tbuf;	/* this will point at the first comment */
	for (i = 1; i <= cellcnt; i++) {
		ptrOP[i] = strstr(ptrE[i - 1], "Cell ");	/* first open, we're assuming one space in front!! */
		ptrE[i] = strstr(ptrE[i - 1], "\n}\n");
		if (ptrE[i] == NULL || ptrOP[i] == NULL) {
			bad = 1;
			goto BAD;
		}
		ptrE[i] += 3;			/* move it past */
//      fprintf(stdout,"CELL%d#%d[%s]\n",modify,i,ptrOP[i]);
	}
	hold = *(ptrOP[modify]);
	*(ptrOP[modify]) = '\0';
	strcpy(swapbefore, tbuf);
	*(ptrOP[modify]) = hold;

	hold = *(ptrE[modify] + 1);
	*(ptrE[modify] + 1) = '\0';
	strcpy(swapcell, ptrOP[modify]);
	*(ptrE[modify] + 1) = hold;

	strcpy(swapafter, ptrE[modify] + 1);
//swapcell:
//Cell "LOCK_" w/W/X/. LOCKstrobeWF_DSET0wW_cat_BEKR {
//  Data 0/1/2/3;
//  Drive {
//      Waveform {
//          DriveOff @"  tref +  tH1flo +  tdH1LLOCK -  restrict -  loosdelay +  tgb +ctcf+0.000ns +orgtH1flo";
//      }
//  }
//  Compare {
//      Waveform {
//          CompareClose @"  tref +  tH1flo +  tdH1LLOCK -  restrict -  loosdelay +  tgb +ctcf+0.000ns +orgtH1flo";
//          CompareOpenData @"  tref +  tH1flo +  tdH1LLOCK +  loosdelay5 -  tgb -ctcf+0.000ns +orgtH1flo";
//      }
//  }
//}

	ptrCMPC = strstr(swapcell, "CompareClose");
	if (ptrCMPC == NULL) {
		bad = 2;
		goto BAD;
	}
	ptrSEMIC = strchr(ptrCMPC, ';');
	ptrCMPO = strstr(swapcell, "CompareOpenData");
	if (ptrCMPO == NULL) {
		bad = 3;
		goto BAD;
	}
	ptrSEMIO = strchr(ptrCMPO, ';');
	if (ptrSEMIO == NULL || ptrSEMIC == NULL) {
		bad = 4;
		goto BAD;
	}

	strcpy(swapremainder, ptrSEMIO);	/* everything after & including CompOpenData semicolon */
	*ptrSEMIO = '\0';

	*(ptrSEMIC - 1) = '\0';		/* !!!!!!!!!!!! wipe out the closing quote !!!!!!!!!! */

	strcpy(swapclose, ptrCMPC);	/* the whole CompClose expr. not incl. the semicolon or the quote */
	*(ptrSEMIO) = '\0';
	strcpy(swapopen, ptrCMPO);	/* the whole compOpen expr */
	*ptrCMPC = '\0';
	/* swapcell is the front portion of the cell */
	ptrOPQ = strchr(swapclose, '\"');
	if (ptrOPQ == NULL) {
		bad = 4;
		goto BAD;
	}
	*ptrOPQ = '\0';
	/* now have the open and close of the close expr */
	strcpy(swapcloseinsideq, ptrOPQ + 1);

	/* first swapcell, then CompOpen;\n          then CompClose then +t_Per_Push"; then cell remainder */
	sprintf(modcell, "%s%s;\n         %s\"0.0*(%s)+t_Per_End\"%s", swapcell,
			swapopen, swapclose, swapcloseinsideq, swapremainder);

	sprintf(tbuf, "%s//====swapb====\n%s%s//===swape===\n", swapbefore,
			modcell, swapafter);

	if (!bad)
		return (0);

  BAD:fprintf(stderr,
			"Bad=%d, <move>We didn't find what we were looking for in the cell[%d] out2[%60.60s]\n",
			bad, modify, swapcell);
	exit(1);
	return (-1);
}

int swap_alias(char *buffer, int *wfmcodeD0, int *wfmcodeD1)
{
	int i;
	char *curptr, *ptrCELL, *ptrQ1, *ptrQ2, *ptrSP1, *ptrSP2;

/* the goal of this function is to migrate edge (0/1) & window(w/W) cells into a combined */
/* definition format so we can have one pattern: */
/* 0/w  =>2
   1/W  =>3
   x/X  =>x/X (stays the same)
   ./,  =>./,
   -    =>4   not sure if this should be 4 or 6......
   p/P  =>4/5 for multicycle strobing
   e/E  =>6/7 (which will be mask for 0/1 and strobe close for e/E)
*/

	curptr = buffer;
	for (i = 0; i < cellcnt; i++) {
		ptrQ1 = ptrQ2 = ptrSP1 = ptrSP2 = NULL;	/* initialize for easy decisions... */
		ptrCELL = strstr(curptr, "Cell");	/* find a Cell */
		if (ptrCELL != NULL)
			ptrQ1 = strchr(ptrCELL, '\"');	/* find the pingroup start */
		if (ptrQ1 != NULL)
			ptrQ2 = strchr(ptrQ1 + 1, '\"');	/* find the pingroup end */
		if (ptrQ2 != NULL) {
			ptrSP1 = ptrQ2 + 1;
			while (*ptrSP1 == ' ')
				ptrSP1++;		/* find the first non-space */
			ptrSP2 = ptrSP1;
			while (*ptrSP2 != ' ')
				ptrSP2++;		/* find the first space after the aliases */
		}
		else
			continue;
		while (ptrSP1 < ptrSP2) {
/* alias0 */
/* edge,window */
			if (*ptrSP1 == '0' && cellinfo[i].alias0 == '0') {
				cellinfo[i].alias0 = *ptrSP1 = '2';
				strcat(buffer, "//0changed 0=>2\n");
				*wfmcodeD0 = 'A';
			}					/* compare window or edge low */
			else if (*ptrSP1 == '1' && cellinfo[i].alias0 == '1') {
				cellinfo[i].alias0 = *ptrSP1 = '3';
				strcat(buffer, "//0changed 1=>3\n");
				*wfmcodeD0 = 'A';
			}					/* compare window or edge high */
			else if (*ptrSP1 == 'w' && cellinfo[i].alias0 == 'w') {
				cellinfo[i].alias0 = *ptrSP1 = '2';
				strcat(buffer, "//0changed w=>2\n");
				*wfmcodeD0 = 'A';
			}					/* compare window or edge low */
			else if (*ptrSP1 == 'W' && cellinfo[i].alias0 == 'W') {
				cellinfo[i].alias0 = *ptrSP1 = '3';
				strcat(buffer, "//0changed W=>3\n");
				*wfmcodeD0 = 'A';
			}					/* compare window or edge high */
			else if (*ptrSP1 == 'o' && cellinfo[i].alias0 == 'o') {
				cellinfo[i].alias0 = *ptrSP1 = 'a';
				strcat(buffer, "//0changed o=>a\n");
				*wfmcodeD0 = 'A';
			}					/* compare window or edge low */
			else if (*ptrSP1 == 'i' && cellinfo[i].alias0 == 'i') {
				cellinfo[i].alias0 = *ptrSP1 = 'A';
				strcat(buffer, "//0changed i=>A\n");
				*wfmcodeD0 = 'A';
			}					/* compare window or edge high */
			else if (*ptrSP1 == 'v' && cellinfo[i].alias0 == 'v') {
				cellinfo[i].alias0 = *ptrSP1 = 'a';
				strcat(buffer, "//0changed v=>a\n");
				*wfmcodeD0 = 'A';
			}					/* compare window or edge low */
			else if (*ptrSP1 == 'V' && cellinfo[i].alias0 == 'V') {
				cellinfo[i].alias0 = *ptrSP1 = 'A';
				strcat(buffer, "//0changed V=>A\n");
				*wfmcodeD0 = 'A';
			}					/* compare window or edge high */
/* continue,continuestrobe */
			else if (*ptrSP1 == '-' && cellinfo[i].alias0 == '-') {
				cellinfo[i].alias0 = *ptrSP1 = '4';
				strcat(buffer, "//0changed -=>4\n");
				*wfmcodeD0 = 'C';
			}					/* continue comparing window */
			else if (*ptrSP1 == 'p' && cellinfo[i].alias0 == 'p') {
				cellinfo[i].alias0 = *ptrSP1 = '4';
				strcat(buffer, "//0changed p=>4\n");
				*wfmcodeD0 = 'C';
			}					/* continue comparing window */
			else if (*ptrSP1 == 'P' && cellinfo[i].alias0 == 'P') {
				cellinfo[i].alias0 = *ptrSP1 = '5';
				strcat(buffer, "//0changed P=>5\n");
				*wfmcodeD0 = 'C';
			}					/* continue comparing window */
/* driveoff,close window */
			else if (*ptrSP1 == 'z' && cellinfo[i].alias0 == 'z') {
				cellinfo[i].alias0 = *ptrSP1 = '6';
				strcat(buffer, "//0changed z=>6\n");
				*wfmcodeD0 = 'B';
			}					/* end strobe low */
			else if (*ptrSP1 == 'Z' && cellinfo[i].alias0 == 'Z') {
				cellinfo[i].alias0 = *ptrSP1 = '7';
				strcat(buffer, "//0changed Z=>7\n");
				*wfmcodeD0 = 'B';
			}					/* end strobe high */
			else if (*ptrSP1 == 'e' && cellinfo[i].alias0 == 'e') {
				cellinfo[i].alias0 = *ptrSP1 = '6';
				strcat(buffer, "//0changed e=>6\n");
				*wfmcodeD0 = 'B';
			}					/* end strobe low */
			else if (*ptrSP1 == 'E' && cellinfo[i].alias0 == 'E') {
				cellinfo[i].alias0 = *ptrSP1 = '7';
				strcat(buffer, "//0changed E=>7\n");
				*wfmcodeD0 = 'B';
			}					/* end strobe high */
			else if (*ptrSP1 == 'y' && cellinfo[i].alias0 == 'y') {
				cellinfo[i].alias0 = *ptrSP1 = 'b';
				strcat(buffer, "//0changed y=>b\n");
				*wfmcodeD0 = 'B';
			}					/* end strobe low */
			else if (*ptrSP1 == 'Y' && cellinfo[i].alias0 == 'Y') {
				cellinfo[i].alias0 = *ptrSP1 = 'B';
				strcat(buffer, "//0changed Y=>B\n");
				*wfmcodeD0 = 'B';
			}					/* end strobe high */
			else if (*ptrSP1 == 'k' && cellinfo[i].alias0 == 'k') {
				cellinfo[i].alias0 = *ptrSP1 = 'b';
				strcat(buffer, "//0changed k=>b\n");
				*wfmcodeD0 = 'B';
			}					/* end strobe low */
			else if (*ptrSP1 == 'K' && cellinfo[i].alias0 == 'K') {
				cellinfo[i].alias0 = *ptrSP1 = 'B';
				strcat(buffer, "//0changed K=>B\n");
				*wfmcodeD0 = 'B';
			}					/* end strobe high */
/* floatedge,floatwindow */
			else if (*ptrSP1 == 'f' && cellinfo[i].alias0 == 'f') {
				cellinfo[i].alias0 = *ptrSP1 = '8';
				strcat(buffer, "//0changed f=>8\n");
				*wfmcodeD0 = 'D';
			}					/* continue comparing window */
			else if (*ptrSP1 == 'F' && cellinfo[i].alias0 == 'F') {
				cellinfo[i].alias0 = *ptrSP1 = '9';
				strcat(buffer, "//0changed F=>9\n");
				*wfmcodeD0 = 'D';
			}					/* continue comparing window */
			else if (*ptrSP1 == 'u' && cellinfo[i].alias0 == 'u') {
				cellinfo[i].alias0 = *ptrSP1 = '8';
				strcat(buffer, "//0changed u=>8\n");
				*wfmcodeD0 = 'D';
			}					/* continue comparing window */
			else if (*ptrSP1 == 'U' && cellinfo[i].alias0 == 'U') {
				cellinfo[i].alias0 = *ptrSP1 = '9';
				strcat(buffer, "//0changed U=>9\n");
				*wfmcodeD0 = 'D';
			}					/* continue comparing window */
			else if (*ptrSP1 == 'g' && cellinfo[i].alias0 == 'g') {
				cellinfo[i].alias0 = *ptrSP1 = 'h';
				strcat(buffer, "//0changed g=>h\n");
				*wfmcodeD0 = 'D';
			}					/* continue comparing window */
			else if (*ptrSP1 == 'G' && cellinfo[i].alias0 == 'G') {
				cellinfo[i].alias0 = *ptrSP1 = 'H';
				strcat(buffer, "//0changed G=>H\n");
				*wfmcodeD0 = 'D';
			}					/* continue comparing window */
			else if (*ptrSP1 == 't' && cellinfo[i].alias0 == 't') {
				cellinfo[i].alias0 = *ptrSP1 = 'h';
				strcat(buffer, "//0changed t=>h\n");
				*wfmcodeD0 = 'D';
			}					/* continue comparing window */
			else if (*ptrSP1 == 'T' && cellinfo[i].alias0 == 'T') {
				cellinfo[i].alias0 = *ptrSP1 = 'H';
				strcat(buffer, "//0changed T=>H\n");
				*wfmcodeD0 = 'D';
			}					/* continue comparing window */
/* alias1 */
/* edge,window */
			if (*ptrSP1 == '0' && cellinfo[i].alias1 == '0') {
				cellinfo[i].alias1 = *ptrSP1 = '2';
				strcat(buffer, "//1changed 0=>2\n");
				*wfmcodeD0 = 'A';
			}					/* compare window or edge low */
			else if (*ptrSP1 == '1' && cellinfo[i].alias1 == '1') {
				cellinfo[i].alias1 = *ptrSP1 = '3';
				strcat(buffer, "//1changed 1=>3\n");
				*wfmcodeD0 = 'A';
			}					/* compare window or edge high */
			else if (*ptrSP1 == 'w' && cellinfo[i].alias1 == 'w') {
				cellinfo[i].alias1 = *ptrSP1 = '2';
				strcat(buffer, "//1changed w=>2\n");
				*wfmcodeD0 = 'A';
			}					/* compare window or edge low */
			else if (*ptrSP1 == 'W' && cellinfo[i].alias1 == 'W') {
				cellinfo[i].alias1 = *ptrSP1 = '3';
				strcat(buffer, "//1changed W=>3\n");
				*wfmcodeD0 = 'A';
			}					/* compare window or edge high */
			else if (*ptrSP1 == 'o' && cellinfo[i].alias1 == 'o') {
				cellinfo[i].alias1 = *ptrSP1 = 'a';
				strcat(buffer, "//1changed o=>a\n");
				*wfmcodeD0 = 'A';
			}					/* compare window or edge low */
			else if (*ptrSP1 == 'i' && cellinfo[i].alias1 == 'i') {
				cellinfo[i].alias1 = *ptrSP1 = 'A';
				strcat(buffer, "//1changed i=>A\n");
				*wfmcodeD0 = 'A';
			}					/* compare window or edge high */
			else if (*ptrSP1 == 'v' && cellinfo[i].alias1 == 'v') {
				cellinfo[i].alias1 = *ptrSP1 = 'a';
				strcat(buffer, "//1changed v=>a\n");
				*wfmcodeD0 = 'A';
			}					/* compare window or edge low */
			else if (*ptrSP1 == 'V' && cellinfo[i].alias1 == 'V') {
				cellinfo[i].alias1 = *ptrSP1 = 'A';
				strcat(buffer, "//1changed V=>A\n");
				*wfmcodeD0 = 'A';
			}					/* compare window or edge high */
/* continue,continuestrobe */
			else if (*ptrSP1 == '-' && cellinfo[i].alias1 == '-') {
				cellinfo[i].alias1 = *ptrSP1 = '4';
				strcat(buffer, "//1changed -=>4\n");
				*wfmcodeD0 = 'C';
			}					/* continue comparing window */
			else if (*ptrSP1 == 'p' && cellinfo[i].alias1 == 'p') {
				cellinfo[i].alias1 = *ptrSP1 = '4';
				strcat(buffer, "//1changed p=>4\n");
				*wfmcodeD0 = 'C';
			}					/* continue comparing window */
			else if (*ptrSP1 == 'P' && cellinfo[i].alias1 == 'P') {
				cellinfo[i].alias1 = *ptrSP1 = '5';
				strcat(buffer, "//1changed P=>5\n");
				*wfmcodeD0 = 'C';
			}					/* continue comparing window */
/* driveoff,close window */
			else if (*ptrSP1 == 'z' && cellinfo[i].alias1 == 'z') {
				cellinfo[i].alias1 = *ptrSP1 = '6';
				strcat(buffer, "//1changed z=>6\n");
				*wfmcodeD0 = 'B';
			}					/* end strobe low */
			else if (*ptrSP1 == 'Z' && cellinfo[i].alias1 == 'Z') {
				cellinfo[i].alias1 = *ptrSP1 = '7';
				strcat(buffer, "//1changed Z=>7\n");
				*wfmcodeD0 = 'B';
			}					/* end strobe high */
			else if (*ptrSP1 == 'e' && cellinfo[i].alias1 == 'e') {
				cellinfo[i].alias1 = *ptrSP1 = '6';
				strcat(buffer, "//1changed e=>6\n");
				*wfmcodeD0 = 'B';
			}					/* end strobe low */
			else if (*ptrSP1 == 'E' && cellinfo[i].alias1 == 'E') {
				cellinfo[i].alias1 = *ptrSP1 = '7';
				strcat(buffer, "//1changed E=>7\n");
				*wfmcodeD0 = 'B';
			}					/* end strobe high */
			else if (*ptrSP1 == 'y' && cellinfo[i].alias1 == 'y') {
				cellinfo[i].alias1 = *ptrSP1 = 'b';
				strcat(buffer, "//1changed y=>b\n");
				*wfmcodeD0 = 'B';
			}					/* end strobe low */
			else if (*ptrSP1 == 'Y' && cellinfo[i].alias1 == 'Y') {
				cellinfo[i].alias1 = *ptrSP1 = 'B';
				strcat(buffer, "//1changed Y=>B\n");
				*wfmcodeD0 = 'B';
			}					/* end strobe high */
			else if (*ptrSP1 == 'k' && cellinfo[i].alias1 == 'k') {
				cellinfo[i].alias1 = *ptrSP1 = 'b';
				strcat(buffer, "//1changed k=>b\n");
				*wfmcodeD0 = 'B';
			}					/* end strobe low */
			else if (*ptrSP1 == 'K' && cellinfo[i].alias1 == 'K') {
				cellinfo[i].alias1 = *ptrSP1 = 'B';
				strcat(buffer, "//1changed K=>B\n");
				*wfmcodeD0 = 'B';
			}					/* end strobe high */
/* floatedge,floatwindow */
			else if (*ptrSP1 == 'f' && cellinfo[i].alias1 == 'f') {
				cellinfo[i].alias1 = *ptrSP1 = '8';
				strcat(buffer, "//1changed f=>8\n");
				*wfmcodeD0 = 'D';
			}					/* continue comparing window */
			else if (*ptrSP1 == 'F' && cellinfo[i].alias1 == 'F') {
				cellinfo[i].alias1 = *ptrSP1 = '9';
				strcat(buffer, "//1changed F=>9\n");
				*wfmcodeD0 = 'D';
			}					/* continue comparing window */
			else if (*ptrSP1 == 'u' && cellinfo[i].alias1 == 'u') {
				cellinfo[i].alias1 = *ptrSP1 = '8';
				strcat(buffer, "//1changed u=>8\n");
				*wfmcodeD0 = 'D';
			}					/* continue comparing window */
			else if (*ptrSP1 == 'U' && cellinfo[i].alias1 == 'U') {
				cellinfo[i].alias1 = *ptrSP1 = '9';
				strcat(buffer, "//1changed U=>9\n");
				*wfmcodeD0 = 'D';
			}					/* continue comparing window */
			else if (*ptrSP1 == 'g' && cellinfo[i].alias1 == 'g') {
				cellinfo[i].alias1 = *ptrSP1 = 'h';
				strcat(buffer, "//1changed g=>h\n");
				*wfmcodeD0 = 'D';
			}					/* continue comparing window */
			else if (*ptrSP1 == 'G' && cellinfo[i].alias1 == 'G') {
				cellinfo[i].alias1 = *ptrSP1 = 'H';
				strcat(buffer, "//1changed G=>H\n");
				*wfmcodeD0 = 'D';
			}					/* continue comparing window */
			else if (*ptrSP1 == 't' && cellinfo[i].alias1 == 't') {
				cellinfo[i].alias1 = *ptrSP1 = 'h';
				strcat(buffer, "//1changed t=>h\n");
				*wfmcodeD0 = 'D';
			}					/* continue comparing window */
			else if (*ptrSP1 == 'T' && cellinfo[i].alias1 == 'T') {
				cellinfo[i].alias1 = *ptrSP1 = 'H';
				strcat(buffer, "//1changed T=>H\n");
				*wfmcodeD0 = 'D';
			}					/* continue comparing window */


			ptrSP1++;

		}
		curptr = ptrSP2;
	}

	return (0);
}

int process_cycletbl()
{
	int device_pingroup;
	int wWeEdash, reverse;
	char plen, plens, int gctstart, gctend, pinstart, pinend;
	int START_WFMT = 0;
	int ininherit;
	char newwavetable[50];
	char *ptr0, *ptr3, int tell;

	for (1 == 1) {
		if (roger == -1)
			continue;			/* skip if something wrong with the group! */
		device_pingroup = -1;
		plen = strlen(PINNAME);
		plens = strlen(PIN[pin]);


		return (0);
	}
	int write_cycl_mod() {
		char VectorMapSet[READLINELEN + 1];
		char *ptrSCAN, *ptr2, *ptr3, *ptr1, *ptr;
		int i, plen, pin, flag_group;
		int fieldcount;
		char readstr2[READLINELEN * 20 + 1];
		char hex_or_bin;;
		char PINNAME[PINSIZE];
		char PINBINARY[NUMPINS + 1];
//    if (NULL!=(ptrSCAN=(strstr(readstr,"Scan")))) {
//       if (strstr(readstr,"ScanInOrderVM")!=NULL || strstr(readstr,"ScanInVM")!=NULL ){
//          ptr2=ptr3=NULL;
//          ptr1=strchr(readstr,',');/* first comma */
//          if (ptr1!=NULL) ptr2=strchr(ptr1+1,',');/* second */
//          if (ptr2!=NULL) ptr3=strchr(ptr2+1,',');/* third comma */
//          for (i=0,ptr=ptr2+1;ptr<ptr3;ptr++) if (*ptr!=' ') {PINNAME[i]=*ptr;i++;}
//          PINNAME[i]='\0';
//          plen=strlen(PINNAME);
//          for (pin=0;pin<maxpin;pin++) {
//             if (strstr(PIN[pin],PINNAME)==PIN[pin] && flag_group==0 ) break;/* check that the pinname matches(or is a substring of the pinfile pin */
//             if (strstr(PIN[pin],PINNAME)==PIN[pin] && flag_group==1 &&(PIN[pin][plen]=='0' || PIN[pin][plen]=='1'|| PIN[pin][plen]=='2' || PIN[pin][plen]=='3'|| PIN[pin][plen]=='m')) break;/* check that the pinname matches(or is a substring of the pinfile pin */
//             }
//          fprintf(fpout1,"?SCANINPIN:%s %d\n",PINNAME,pin+1);
//          }
//       else if (strstr(readstr,"ScanOutOrderVM")!=NULL || strstr(readstr,"ScanOutVM")!=NULL ){
//          ptr2=ptr3=NULL;
//          ptr1=strchr(readstr,',');/* first comma */
//          if (ptr1!=NULL) ptr2=strchr(ptr1+1,',');/* second */
//          if (ptr2!=NULL) ptr3=strchr(ptr2+1,',');/* third comma */
//          for (i=0,ptr=ptr2+1;ptr<ptr3;ptr++) if (*ptr!=' ') {PINNAME[i]=*ptr;i++;}
//          PINNAME[i]='\0';
//          plen=strlen(PINNAME);
//          for (pin=0;pin<maxpin;pin++) {
//             if (strstr(PIN[pin],PINNAME)==PIN[pin] && flag_group==0 ) break;/* check that the pinname matches(or is a substring of the pinfile pin */
//             if (strstr(PIN[pin],PINNAME)==PIN[pin] && flag_group==1 &&(PIN[pin][plen]=='0' || PIN[pin][plen]=='1'|| PIN[pin][plen]=='2' || PIN[pin][plen]=='3'|| PIN[pin][plen]=='m')) break;/* check that the pinname matches(or is a substring of the pinfile pin */
//             }
//          fprintf(fpout1,"?SCANOUTPIN:%s %d\n",PINNAME,pin+1);
//          }
		else {					/* normal entry */
			if (NULL != strstr(readstr, "Hex"))
				hex_or_bin = 'H';
			else if (NULL != strstr(readstr, "Binary"))
				hex_or_bin = 'B';
			ptr = strchr(readstr, ',');
			ptr0 = strchr(readstr, '(');
			if (ptr != NULL)
				ptr2 = strchr(ptr + 1, ',');
			else
				ptr2 = NULL;
			if (ptr2 != NULL)
				ptr3 = strchr(ptr2 + 1, ',');
			else
				ptr3 = NULL;
			if (ptr0 != NULL && ptr != NULL) {
				*ptr = '\0';
				if (strstr(ptr0 + 1, "Scan") != NULL);	/* shouldn't hit this now... if its a scan then skip it here */
				else if (VectorMapSet[0] == '\0')
					strcpy(VectorMapSet, ptr0 + 1);
				else if (0 != strcmp(VectorMapSet, ptr0 + 1)) {
					fprintf(stderr,
							"************\nMultiple VectorMapSets not supported in [%s]\n",
							infile1);
					fprintf(stderr,
							"Please request support or split the file!!!\n*************\n");
					fprintf(fperrors,
							"************\nMultiple VectorMapSets not supported in [%s]\n",
							infile1);
					fprintf(fperrors,
							"Please request support or split the file!!!\n*************\n");
					exit(7);
				}
				*ptr = ',';
			}
			if (ptr2 != NULL && ptr3 != NULL) {
				*ptr3 = '\0';
				strcpy(readstr2, ptr2 + 1);
				*ptr3 = ',';
			}
			for (i = 0; i < maxlists; i++)
				if (0 == strcmp(readstr2, pinlist[i].pinlistname)) {
					for (j = 0; j < maxpin; j++)
						if (pinlist[i].pinlists[j] == '*') {
							hexproc[j] = hex_or_bin;
							fieldset[j] = fieldcount;
						}
					break;
				}
			if (i == maxlists) {	/* not a group */
				for (j = 0; j < maxpin; j++) {
					if (0 == strcmp(readstr2, PIN[j])) {
						hexproc[j] = hex_or_bin;
						fieldset[j] = fieldcount;
						break;
					}
				}
			}
			fieldcount++;
		}


/* The following block of code will take the inherit waveformtable
   section and rebuild the true waveformtable pattern control data
   from the sub-component waveformtables. To do this we rewind the
   input file so it points back to the inherit begin and rewind the
   output file to the first sub-component wft start. We then parse
   each row in the output file for its non-zero settings. When we are
   done processing each column of the input inheritance list through
   the each read line of the output file, we then set the pointer back
   to the end of the output file and write the correct pattern control
   data. */

		if (ininherit == -1) {
			fflush(fp_mod_file);
			fileoutend = ftell(fp_mod_file);
			fseek(fpin1, fileininhst, SEEK_SET);
			while (fgets(readstr, READLINELEN - 1, fpin1) != NULL) {
				readstr[strlen(readstr) - 1] = '\0';	/* remove trailing \n */
				for (j = i = 0; i < strlen(readstr); i++) {	/* strip whitespace */
					if (isgraph((int) readstr[i])) {
						tempgrpexpand2[j] = readstr[i];
						j++;
					}
				}				/* end strip white space */
				if (NULL != (ptr2 = (strstr(tempgrpexpand2, "#endinheritlist")))) {	/* don't forget we stripped whitespace!!!! */
					fprintf(stderr, "Exiting inherit table![%d]\n", i);
					ininherit = -2;
					break;
				}
				else {
					ptr1 = strchr(tempgrpexpand2, '[');
					ptr2 = strchr(tempgrpexpand2, ']');
					if (ptr1 == NULL || ptr2 == NULL) {
						continue;	/* skip if not what we are looking for */
					}
					*ptr1 = '\0';
					strcpy(fullwftname, tempgrpexpand2);
//         fprintf(fpstatus,"wft[%s]\n",fullwftname);
					*ptr1 = '[';

					for (i = 0; i < strlen(hexproc); i++)
						newstr[i] = ' ';	/* initialize it to all ' ' */
					newstr[i] = '\0';

					fseek(fp_mod_file, fileoutinhst, SEEK_SET);
					for (i = 0, ptr = ptr1 + 1; ptr < ptr2; ptr++, i++) {
						if (*ptr == 'X') {
							fgets(tstr, READLINELEN - 1, fp_mod_file);	/* assume file is good */
							ptr3 = strchr(tstr, '[');
							ptr4 = strchr(tstr, ']');
							for (j = 0, ptr5 = ptr3 + 1; ptr5 < ptr4;
								 ptr5++, j++) {
								if (*ptr5 != '0')
									newstr[j] = *ptr5;
							}	/* for ptr5 in fp_mod_file */
						}
						else {	/* not enabled by inherit list,just read to advance */
							fgets(tstr, READLINELEN - 1, fp_mod_file);	/* assume file is good */
						}
					}
					/* newstr is now ready, restore pointer and write */
					fseek(fp_mod_file, fileoutend, SEEK_SET);
					fprintf(fp_mod_file, "<%s>[%s]\n", fullwftname,
							newstr);
					fileoutend = ftell(fp_mod_file);
				}				/* end else is valid inherit line */
			}					/* end while readstr on fpin1 */
		}						/* endif ininherit */
/*   fseek(fp_mod_file); actually the fp_mod_file pointer will be left in the right place */

		fprintf(fp_mod_file, "H[%s]\n", hexproc);
		fprintf(fp_mod_file, "F[%s]\n", fieldset);
		fprintf(fp_mod_file, "M[%s]\n", muxpin);
		for (i = 0; i < maxlists; i++) {
			fprintf(fp_mod_file, "PINGROUP[%s]", pinlist[i].pinlists);
			fprintf(fp_mod_file, "(*%s*)", pinlist[i].pinlistname);
			fprintf(fp_mod_file, "{%s}\n", pinlist[i].groups);
		}

		for (sizehead = i = 0; i < maxpin; i++)
			if (strlen(PIN[i]) > sizehead)
				sizehead = strlen(PIN[i]);
		if (sizehead < PINSIZE) {
			for (i = 0; i < maxpin; i++) {
				for (j = 0; j < strlen(PIN[i]); j++)
					pinheader[j][i] = PIN[i][j];
				for (; j < sizehead; j++)
					pinheader[j][i] = ' ';
			}
			for (j = 0; j < sizehead; j++) {
				pinheader[j][maxpin] = '\0';
			}
			for (k = i = 0; i < maxpin; i++) {
				if (muxpin[i] == 'M') {
					for (l = maxpin + k; l > i + k; l--)
						for (j = 0; j < sizehead; j++)
							pinheader[j][l] = pinheader[j][l - 1];
					k++;
				}
			}
			for (j = 0; j < sizehead; j++)
				fprintf(fp_mod_file, "//%s\n", pinheader[j]);
		}
		if (wftpending == 1) {
			if (ininherit == 0) {
				fprintf(fpwaves,
						"Cell \"ALLPINS\" d CPM_CALLING_DPM {\n   Data 3 Other;\n   Drive {\n      EntryState DriveOn;\n   }\n}\n");
				fprintf(fpwaves,
						"Cell \"ALLPINS\" - HOLD_STATE {\n   Data 6;\n   Drive {\n      EntryState DriveOn;\n   }\n}\n");
			}
			fprintf(fpwaves, "}\n");	/* close out the final waveformtable */
		}
/* removed this as we now identify the START/STOP points and use the appropriate origin.(finally!!, but we do need start stops */
		if (maxstartstop == 0) {
			fprintf(fpwaves,
					"Spec EN_ORG {\n   Comment=\"You should really add this to the ACTABLE Spec\";\n   Category DEF_EN_ORG {\n");
			for (i = 0; i < EOCNT; i++)
				fprintf(fpwaves, "      %s = \"1\";\n", EO[i]);
			fprintf(fpwaves, "   }\n   ParamGlobals {\n");
			for (i = 0; i < EOCNT; i++)
				fprintf(fpwaves, "      %s { Type = SCALAR; }\n", EO[i]);
			fprintf(fpwaves, "   }\n}\n");
			fprintf(fpwaves,
					"Mask MASK_EN_ORG {\n   Comment=\"You should really add this to the ACTABLE Mask\";\n");
			for (i = 0; i < EOCNT; i++)
				fprintf(fpwaves, "   %s = Typ;\n", EO[i]);
			fprintf(fpwaves, "}\n");
		}

		if (maxstartstop != 0) {
			fprintf(fpwaves,
					"//START/STOP markers used to select Origins so you should be ok. EN_ORG Spec and ENORG Params NOT created!\n");
			fprintf(stderr,
					"START/STOP markers used to select Origins, good!\n");
		}
		else
			fprintf(stderr,
					"Origins could not be properly bounded, bad!\n");
	}



/* FIXME APS: there should be a check for all contiguous b/e @ same lvl for no overlap */
	for (i = 0; i < maxstartstop; i++) {
		if (startstop[i].type == SSSTART) {
			for (j = (i + 1); j < maxstartstop; j++) {
				if (startstop[i].cdtcode == startstop[j].cdtcode)
					continue;
				if (startstop[j].type == SSSTART) {
					if (startstop[j].lvl == startstop[i].lvl) {
						for (goodtbl = k = 0; k < maxactablenames; k++) {
							if (cattype[i][k] == cattype[j][k]) {
								goodtbl = 1;
								break;
							}
						}		/* end for maxcat */
						for (gcedev = k = 0; k < maxenums; k++) {
							if (ALLDEVICE[k] == '+'
								&& enumtype[i][k] == enumtype[j][k]) {
								gcedev = 1;
								break;
							}
						}		/* end for maxenums */
						for (gcetmp = k = 0; k < maxenums; k++) {
							if (ALLTEMP[k] == '+'
								&& enumtype[i][k] == enumtype[j][k]) {
								gcetmp = 1;
								break;
							}
						}		/* end for maxenums */
						for (gcetst = k = 0; k < maxenums; k++) {
							if (ALLTEST[k] == '+'
								&& enumtype[i][k] == enumtype[j][k]) {
								gcetst = 1;
								break;
							}
						}		/* end for maxenums */
						for (goodenum = k = 0; k < maxenums; k++) {
							if (enumtype[i][k] == enumtype[j][k] &&
								ALLDEVICE[k] == '.' && ALLTEMP[k] == '.'
								&& ALLTEST[k] == '.') {
								goodenum = 1;
								break;
							}
						}		/* end for maxenums */
						if (maxactablenames == 0)
							goodtbl = 1;
						if (maxdev == 0)
							gcedev = 1;
						if (maxtest == 0)
							gcetst = 1;
						if (maxtemp == 0)
							gcetmp = 1;
						if ((maxenums - maxdev - maxtest - maxtemp) == 0)
							goodenum = 1;
						if (goodtbl == 1 && goodenum == 1 && gcedev == 1
							&& gcetst == 1 && gcetmp == 1) {
							fprintf(fpstatus,
									"   LVL[%d]UC[%c] overlaps with UC[%c]\n",
									startstop[i].lvl, startstop[i].cdtcode,
									startstop[j].cdtcode);
						}
						else
							break;	/* non-contiguous, goto next i */
					}			/* end matching levels */
					else
						break;	/* hit different level, exit for j, goto next i */
				}				/* end if j maxstartstop[j] is b */
			}					/* end for j maxstartstop */
		}						/* end if maxstartstop[i] is b */
	}							/* end for i maxstartstop */
