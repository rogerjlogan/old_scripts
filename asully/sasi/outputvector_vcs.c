#include <stdio.h>
#include <string.h>
#include "include_vcs.h"


void outputvector(FILE * fpout1, int *lastitem, char *out_vector,
				  char *pattern, char *WFT, char *DMI, long VN,
				  int repeatcount, char *errorstr, char *comment)
{
	char tempstr[READLINELEN + 1], printstr[READLINELEN + MAXERRORLEN + 1];
	int i;
	printstr[0] = '\0';
	if (*lastitem == STRING && out_vector[0] != '\0')
		strcpy(printstr, "\"");

	if (out_vector[0] != '\0') {
		/*   sprintf(tempstr,"\n*%s00* %s_wft ; ",out_vector,pattern); *//* now using default waveform table in header */
		sprintf(tempstr, "\n*%s* %s %s; ", out_vector, WFT, G_NORMALSGHDR);
		/* added scope sync pins at end of vector APS 6/12/99 */
		strcat(printstr, tempstr);
		out_vector[0] = '\0';
		*lastitem = VECTOR;
	}
	if (repeatcount > 1) {
		sprintf(tempstr, " <RPT %d> ", repeatcount);
		strcat(printstr, tempstr);
	}
	if (DMI[0] != '\0') {
		sprintf(tempstr, "\" V%ld:P%ld:C%ld %s", G_vectorcount - 1, VN, G_cyclecount + 65, DMI);	/* +65 because of LDA and RPT 64 */
		strcat(printstr, tempstr);	/* \""); */
		DMI[0] = '\0';
		*lastitem = STRING;
	}
	if (errorstr[0] != '\0') {
		if (*lastitem != STRING)
			strcat(printstr, "\"");
		strcat(printstr, errorstr);
		*lastitem = STRING;
		errorstr[0] = '\0';
	}
	if (comment[0] != '\0') {
		if (*lastitem != STRING)
			strcat(printstr, "\"");
		for (i = 0; i < strlen(comment); i++)
			if (comment[i] == '"' || comment[i] == '\'')
				comment[i] = '~';
		strcat(printstr, comment);
		comment[0] = '\0';
		*lastitem = STRING;
	}
	if (repeatcount == -99)
		strcpy(out_vector, printstr);
	else
		fprintf(fpout1, "%s", printstr);
}
