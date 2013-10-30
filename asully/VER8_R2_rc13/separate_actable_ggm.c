#include <string.h>
#include <stdlib.h>
#include "includes_ggm.h"

#define CELLBUFFSIZE 50000
/* uses cyclebuff as input */
int separate_actable(char *actablebuf, char *inheritbuf, char *actablelist, struct MODCODE *mc)
{
	int i, slc, bc, done, sll, sp1, sp2, q1, q2, cl;
	char *cycptr, *crptr, *lcrptr, *ncrptr, holdchar, *cnstptr;
	char linebuf[READLINELEN + 1];
	char cellname[READLINELEN + 1], tcellname[READLINELEN + 1];
	char cellbuff[CELLBUFFSIZE + 1];
	slc = strlen(cyclebuff);
	cycptr = cyclebuff;
	/* set the last char to '\0' and validate before return */
	linebuf[READLINELEN] = cellbuff[CELLBUFFSIZE] = tcellname[READLINELEN] = cellname[READLINELEN] = '\0';
	while ((crptr = strchr(cycptr, '\n')) != NULL) {
		holdchar = *(crptr + 1);	/* we've decided to keep the '\n' */
		*(crptr + 1) = '\0';
		strncpy(linebuf, cycptr, READLINELEN);
		*(crptr + 1) = holdchar;
		if (strstr(linebuf, "Cell \"") != NULL) {
//         fprintf(stdout,"linebuf[%s]\n",linebuf);
			strncpy(cellname, linebuf, READLINELEN);
			done = bc = 0;
			cellbuff[0] = '\0';
			lcrptr = crptr;
			while (!done) {
				sll = strlen(linebuf);
				for (i = 0; i < sll; i++) if (linebuf[i] == '{') bc++;
				for (i = 0; i < sll; i++) if (linebuf[i] == '}') bc--;
				if (bc > 0) {
					strncat(cellbuff, linebuf, CELLBUFFSIZE);
					ncrptr = strchr(lcrptr + 1, '\n');
					if (ncrptr == NULL) fprintf(stderr, "ERROR:we haven't finished cyclebuff, source[%s,%d,%s]\n",
							__FILE__, __LINE__, __FUNCTION__);
					holdchar = *(ncrptr + 1);	/* we've decided to keep the '\n' */
					*(ncrptr + 1) = '\0';
					strncpy(linebuf, lcrptr, READLINELEN);
					*(ncrptr + 1) = holdchar;
					lcrptr = ncrptr + 1;
				}
				else if (bc == 0) {	/* we have the cell */
					strncat(cellbuff, linebuf, CELLBUFFSIZE);
					sp1 = 0, sp2 = 0, q1 = 0, q2 = 0;
					/* find the actual cellname (not including pins and alias) */
					cl = strlen(cellname);
					for (i = 0; (i < cl) && (sp2 == 0); i++) {
						if (q1 == 0 && cellname[i] == '\"') {
							q1 = 1;
							continue;
						}
						if (q1 == 1 && q2 == 0 && cellname[i] == '\"') {
							q2 = 1;
							continue;
						}
						if (q2 == 1 && sp1 == 0 && cellname[i] == ' ') {
							sp1 = 1;
							continue;
						}
						if (sp1 == 1 && sp2 == 0 && cellname[i] == ' ') {
							sp2 = 1;
							cnstptr = cellname + i + 1;
							break;
						}
					}
					if (sp2 == 1) {
						snprintf(tcellname, READLINELEN, "|%s", cnstptr);
					}
					else {
						fprintf(stderr,
								"BAD Inherit %s %d %d %d %d, source[%s,%d,%s]\n",
								cellname, q1, q2, sp1, sp2, __FILE__,
								__LINE__, __FUNCTION__);
						exit(1);
					}
					if (strstr(actablelist, tcellname) != NULL) {	/* exists */
						/* just need to add to the inherit */
						strncat(actablebuf, cellbuff, actablebufsize);	/* add it to the actable file */
						add_to_inherit(cellname, cnstptr, inheritbuf);
					}
					else {		/* doesn't exist, new cell */
						strncat(actablelist, tcellname, actablelistsize);	/* add it to the list */
						strncat(actablebuf, cellbuff, actablebufsize);	/* add it to the actable file */
						add_to_inherit(cellname, cnstptr, inheritbuf);
					}
					done = 1;
				}				/* bc==0 */
			}					/* finding end of cell, !done */
			cycptr = ncrptr + 1;
		}						/* end of found Cell line */
		else {
			strncat(actablebuf, linebuf, actablebufsize);
//         fprintf(stdout,"%s",linebuf);
			cycptr = crptr + 1;
		}
	}							/* while we're active in the buffer */
//   fprintf(stdout,"DONE!!!\n");
	/* set the last char to '\0' and validate before return */
	if (linebuf[READLINELEN] != '\0')
		fprintf(stderr, "WARNING:linebuff maxed[%s], source[%s,%d,%s]\n",
				linebuf, __FILE__, __LINE__, __FUNCTION__);
	if (cellbuff[CELLBUFFSIZE] != '\0')
		fprintf(stderr, "WARNING:cellbuff maxed[%s], source[%s,%d,%s]\n",
				cellbuff, __FILE__, __LINE__, __FUNCTION__);
	if (tcellname[READLINELEN] != '\0')
		fprintf(stderr, "WARNING:tcellname maxed[%s], source[%s,%d,%s]\n",
				tcellname, __FILE__, __LINE__, __FUNCTION__);
	if (cellname[READLINELEN] != '\0')
		fprintf(stderr, "WARNING:cellname maxed[%s], source[%s,%d,%s]\n",
				cellname, __FILE__, __LINE__, __FUNCTION__);
	return (0);
}

int add_to_inherit(char *cellname, char *cnstptr, char *inheritbuf)
{
#define TBUFFSIZE CELLBUFFSIZE
	char tbuff[TBUFFSIZE + 1], *cnend;
	int cl, bw;
	tbuff[TBUFFSIZE] = '\0';
	cl = strlen(cellname);
	if (cl >= TBUFFSIZE)
		fprintf(stderr,
				"WARNING:cellname,tbuff maxed2[%s], source[%s,%d,%s]\n",
				cellname, __FILE__, __LINE__, __FUNCTION__);
//   fprintf(stdout,"CN[%s]\n",cellname);
	cnend = strchr(cnstptr, ' ');
	if (cnend == NULL) {
		fprintf(stderr,
				"NO SPACE found in [%s]Cell[%s]\n, source[%s,%d,%s]\n",
				cnstptr, cellname, __FILE__, __LINE__, __FUNCTION__);
		exit(1);
	}
	*cnend = '\0';
	bw = snprintf(tbuff, TBUFFSIZE, "   %s {  Inherit ACTABLE.%s; }\n",
				  cellname, cnstptr);
	if (bw == TBUFFSIZE)
		fprintf(stderr,
				"WARNING:WROTE TOO MANY BYTES, tbuff [%s], source[%s,%d,%s]\n",
				tbuff, __FILE__, __LINE__, __FUNCTION__);
	*cnend = ' ';
	strncat(inheritbuf, tbuff, inheritbufsize);
	if (tbuff[TBUFFSIZE] != '\0')
		fprintf(stderr, "WARNING:tbuff maxed[%s], source[%s,%d,%s]\n",
				tbuff, __FILE__, __LINE__, __FUNCTION__);
	return (0);
}
