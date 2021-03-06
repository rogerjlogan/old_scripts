#include <stdio.h>
#include <strings.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include <malloc.h>
#include <sys/param.h>
#include <sys/types.h>
#include <sys/utsname.h>

#define TRUE  1
#define FALSE 0
#define DEBUG FALSE

#define FILENAMELEN 120
#define MAXLINES 512
#define ONELINELEN 500
#define READLINELEN 100000
#define MEMOSTRLEN 256
#define EXT ".evo"

/*function prototypes */
int get_string(char *srcstr,char *rtnstr,int rtnlen,char *delim,int colno);
int set_dataset(char *dcsetstr,char *oline,int dcleak,int prtmode,FILE *fpout);
int get_value(char *srcstr,char *result);

/********************************/
/*                              */
/*      main() function         */
/*                              */
/********************************/
int main (int argc,char *argv[]){

/*******************************************/
/*  VARIABLES                              */
/*******************************************/
/* file variables */
FILE *fpin,*fpout;
int filein=0;
char c;
char infile[FILENAMELEN];
char outfile[FILENAMELEN];
char pattern[FILENAMELEN];

/* buffers */
char readstr[READLINELEN],tmpstr[READLINELEN];
char line[MAXLINES][ONELINELEN];
char progstr[MEMOSTRLEN],datestr[MEMOSTRLEN],timestr[MEMOSTRLEN],compilestr[MEMOSTRLEN];/* concatenated strings */

/* temporary variables */
int i,j,k,strip,lidx;
char *ptr;

/*process variables*/
char dct[READLINELEN],dcsetstr[64];
char tmpstr1[READLINELEN];
int dctopen,cell,dcsetopen,dcleak,colctr,numlines,numtables;

strcpy(progstr,__FILE__);
strcpy(datestr,__DATE__);
strcpy(timestr,__TIME__);
strcpy(compilestr,argv[0]);

if (argc==2) filein = 1;
else {
   fprintf(stderr,"\n%s: %s\n",progstr,compilestr);
   fprintf(stderr,"%s by Roger Logan\n",datestr);
   fprintf(stderr,"Remove all comments from <dctable.p> and make sure no parenthesis\n");
   fprintf(stderr,"exist within formulas.  Also, be sure to remove all \'if\' conditions\n");
   fprintf(stderr,"as well as any other formating, since these will be ignored.\n");
   fprintf(stderr,"\n%s <dctable.p>\n\n",compilestr);
   exit(0);
   }

/*****************/
/*  FILE STUFF   */
/*****************/

/* open input file */
if (filein) strcpy(infile,(char *) argv[1]);

strcpy(outfile,infile);
i=0;
while (NULL!=(ptr=strchr(outfile,'/'))){
   i=(ptr-outfile);
   outfile[i]=' ';i++;
   }
/*Copy output file name (taken from input file name) to new output file*/
j=0;
while(NULL==strchr(". ",outfile[i]) && i<strlen(outfile) ) pattern[j++]=outfile[i++];
pattern[j]='\0';
if (NULL==(fpin=fopen(infile,"r"))) {
   fprintf(stderr,"\nInput file [%s] not found\n",infile);
   exit(0);
}
fprintf(stderr,"input file1<%s> ok\n",infile);
sprintf(outfile,"%s%s",pattern,EXT);
   if (NULL==(fpout=fopen(outfile,"w"))) {
      fprintf(stderr,"\nCould not open output file [%s] for output\n",outfile);
      exit(0);
      }
fprintf (fpout,"enVision:\"bl8:R11.1.0.WW1111:S3.5\"; /* 5.7 */\n");
/***************************************************/
/* BEGIN MAIN LOOP */
/***************************************************/
i=0;
while((c=getc(fpin))!=EOF) readstr[i++]=c;
readstr[i+1]='\0';
for (strip=j=i=0;i<strlen(readstr);i++) {/* strip whitespace */
    if (isgraph((int)readstr[i])){readstr[j]=readstr[i];j++;} else strip++;
} readstr[strlen(readstr)-strip] = '\0';/* end strip white space */
for(i=j=k=0;i<strlen(readstr);i++) {
    line[j][k++]=readstr[i];
    if (readstr[i]==';') {line[j++][k]='\0';k=0;}
}
dctopen=FALSE;
cell=FALSE;
dcsetopen = FALSE;
dcleak = TRUE;
colctr=0;
numlines=j;
for(numtables=lidx=0;lidx<numlines;lidx++) {
    if(NULL!=(ptr=strstr(line[lidx],"DCTableOpen"))) {
        numtables++;ptr=ptr+strlen("DCTableOpen")+1;
        strcpy(dct,ptr);
        ptr=strchr(dct,')');*ptr='\0';
        dctopen=TRUE;
        colctr=0;
        fprintf(fpout,"\n%s %s {\n", "Levels", dct);
    } else if (NULL!=(ptr=strstr(line[lidx],"DCTableClose"))) {
        dctopen=FALSE;
        dcsetopen = FALSE;
        fprintf(fpout,"}\n");
    } else {
        cell = FALSE;
        if (strcmp(line[lidx],"DCTableSetNoACCal") == 0) dcleak = FALSE;
        if (!dcsetopen) {
            get_string(line[lidx], tmpstr, 20, "(", 1);
            if ((strcmp(tmpstr,"DCSetIO"        ) == 0) ||
                (strcmp(tmpstr,"DCSetInput"     ) == 0) ||
                (strcmp(tmpstr,"DCSetOutput"    ) == 0)) {
                cell =  TRUE;
                dcleak = FALSE;
                dcsetopen = TRUE;
                tmpstr1[0] = '\0';
                strcpy(tmpstr1, line[lidx]);
            }
            if ((strcmp(tmpstr,"DCSetLeakIO"    ) == 0) ||
                (strcmp(tmpstr,"DCSetLeakInput" ) == 0) ||
                (strcmp(tmpstr,"DCSetLeakOutput") == 0) ||
                (strcmp(tmpstr,"DCSetPTUIIO"    ) == 0) ||
                (strcmp(tmpstr,"DCSetPTUIInput" ) == 0) ||
                (strcmp(tmpstr,"DCSetPTUIOutput") == 0)) {
                cell = TRUE;
                dcleak = TRUE;
                dcsetopen = TRUE;
                tmpstr1[0] = '\0';
                strcpy(tmpstr1, line[lidx]);
            }
        }
        if (cell) {
            strcat(tmpstr1, line[lidx]);
            if (line[lidx][strlen(line[lidx])-1] == ';') {
                dcsetopen = FALSE;
                get_string(tmpstr1, dcsetstr, 64, "(", 1);
                get_string(tmpstr1, tmpstr, 1024, "(", 2);
                get_string(tmpstr, tmpstr1, 1024, ")", 1);
                get_string(tmpstr, tmpstr1, 256, ",", 1);
                fprintf(fpout,"//%s\n",line[lidx]);
                fprintf(fpout,"  %s%2d%s\n", "Column[", colctr++, "]{");
                set_dataset(dcsetstr, tmpstr, dcleak, FALSE,fpout);
                fprintf(fpout,"  }\n");
                if (dcleak == TRUE) {
                  fprintf(fpout,"  %s%2d%s\n", "Column[", colctr++, "]{");
                  set_dataset(dcsetstr, tmpstr, dcleak, TRUE,fpout);
                  fprintf(fpout,"  }\n");
                }
            }
        }
    }
}/* end for */


fclose(fpin);
fclose(fpout);
fprintf(stdout,"SUCCESSFULLY CREATED %s%s\n",pattern,EXT);
return(0);
}

int get_string(char *srcstr,char *rtnstr,int rtnlen,char *delim,int colno) {
    char ostr[2048];
    int idx,sidx,ridx;
    ostr[0] = '\0';
    ridx    = 0;
    idx     = 1;
    for (sidx=0;sidx<=strlen(srcstr);sidx++) {
        if (srcstr[sidx]!=delim[0]) {
            if (idx==colno) {
                if (srcstr[sidx]!=0)
                    ostr[ridx++]=srcstr[sidx];
            }
        } else if (idx++>colno)
                sidx=strlen(srcstr)+1;
    }
    if (ridx >= rtnlen)
        ostr[rtnlen-1] = '\0';
    else
        ostr[ridx] = '\0';
    strcpy(rtnstr, ostr);
    return(0);
} /* get_string */

int set_dataset(char *dcsetstr,char *oline,int dcleak,int prtmode,FILE *fpout) {
    int dcin, dcout, iload, vload, ptui;
    char pinlist[MEMOSTRLEN], vil[MEMOSTRLEN], vih[MEMOSTRLEN], vol[MEMOSTRLEN], voh[MEMOSTRLEN];
    char vitl[MEMOSTRLEN], vith[MEMOSTRLEN], vcomm[MEMOSTRLEN], iol[MEMOSTRLEN], ioh[MEMOSTRLEN], tmpval[MEMOSTRLEN], tmpval1[MEMOSTRLEN];
    char irange[MEMOSTRLEN];
    
    dcin = FALSE;
    dcout = FALSE;
    iload = FALSE;
    vload = FALSE;
    ptui = FALSE;

    get_string(oline, pinlist, 256, ",", 1);
    if ((strcmp(dcsetstr, "DCSetIO") == 0) || (strcmp(dcsetstr, "DCSetLeakIO") == 0)) {
        get_string(oline, tmpval, 256, ",", 2);
        get_value(tmpval, vil);
        get_string(oline, tmpval, 256, ",", 3);
        get_value(tmpval, vih);
        get_string(oline, tmpval, 256, ",", 4);
        get_value(tmpval, vol);
        get_string(oline, tmpval, 256, ",", 5);
        get_value(tmpval, voh);
        get_string(oline, tmpval, 256, ",", 6);
        get_value(tmpval, vitl);
        get_string(oline, tmpval, 256, ",", 7);
        get_value(tmpval, vith);
        get_string(oline, tmpval, 256, ",", 8);
        get_value(tmpval, vcomm);
        get_string(oline, tmpval, 256, ",", 9);
        get_value(tmpval, iol);
        get_string(oline, tmpval, 256, ",", 10);
        get_string(tmpval, tmpval1, 256, ")", 1);
        get_value(tmpval1, ioh);
        dcin = TRUE;
        dcout = TRUE;
        iload = (dcleak)?FALSE:TRUE;
        vload = (dcleak)?FALSE:TRUE;
    }
    if ((strcmp(dcsetstr, "DCSetPTUIIO") == 0)) {
        get_string(oline, tmpval, 256, ",", 2);
        get_value(tmpval, vil);
        get_string(oline, tmpval, 256, ",", 3);
        get_value(tmpval, vih);
        get_string(oline, tmpval, 256, ",", 4);
        get_value(tmpval, vol);
        get_string(oline, tmpval, 256, ",", 5);
        get_value(tmpval, voh);
        get_string(oline, tmpval, 256, ",", 6);
        get_value(tmpval, vitl);
        get_string(oline, tmpval, 256, ",", 7);
        get_value(tmpval, vith);
        get_string(oline, tmpval, 256, ",", 8);
        get_value(tmpval, vcomm);
        get_string(oline, tmpval, 256, ",", 9);
        get_value(tmpval, iol);
        get_string(oline, tmpval, 256, ",", 10);
        get_value(tmpval, ioh);
        get_string(oline, tmpval, 256, ",", 11);
        get_string(tmpval, tmpval1, 256, ")", 1);
        get_value(tmpval1, irange);
        dcin = TRUE;
        dcout = TRUE;
        iload = (dcleak)?FALSE:TRUE;
        vload = (dcleak)?FALSE:TRUE;
        ptui = TRUE;
    }
    if (strcmp(dcsetstr, "DCSetInput") == 0) {
        get_string(oline, tmpval, 256, ",", 2);
        get_value(tmpval, vil);
        get_string(oline, tmpval, 256, ",", 3);
        get_value(tmpval, vih);
        get_string(oline, tmpval, 256, ",", 4);
        get_value(tmpval, vitl);
        get_string(oline, tmpval, 256, ",", 5);
        get_string(tmpval, tmpval1, 256, ")", 1);
        get_value(tmpval1, vith);
        dcin = TRUE;
    }
    if (strcmp(dcsetstr, "DCSetLeakInput") == 0) {
        get_string(oline, tmpval, 256, ",", 2);
        get_value(tmpval, vil);
        get_string(oline, tmpval, 256, ",", 3);
        get_value(tmpval, vih);
        get_string(oline, tmpval, 256, ",", 4);
        get_value(tmpval, vitl);
        get_string(oline, tmpval, 256, ",", 5);
        get_value(tmpval, vith);
        get_string(oline, tmpval, 256, ",", 6);
        get_value(tmpval, vcomm);
        get_string(oline, tmpval, 256, ",", 7);
        get_value(tmpval, iol);
        get_string(oline, tmpval, 256, ",", 8);
        get_string(tmpval, tmpval1, 256, ")", 1);
        get_value(tmpval1, ioh);
        dcin = TRUE;
        iload = (dcleak)?FALSE:TRUE;
        vload = (dcleak)?FALSE:TRUE;
    }
    if (strcmp(dcsetstr, "DCSetPTUIInput") == 0) {
        get_string(oline, tmpval, 256, ",", 2);
        get_value(tmpval, vil);
        get_string(oline, tmpval, 256, ",", 3);
        get_value(tmpval, vih);
        get_string(oline, tmpval, 256, ",", 4);
        get_value(tmpval, vitl);
        get_string(oline, tmpval, 256, ",", 5);
        get_value(tmpval, vith);
        get_string(oline, tmpval, 256, ",", 6);
        get_value(tmpval, vcomm);
        get_string(oline, tmpval, 256, ",", 7);
        get_value(tmpval, iol);
        get_string(oline, tmpval, 256, ",", 8);
        get_value(tmpval, ioh);
        get_string(oline, tmpval, 256, ",", 9);
        get_string(tmpval, tmpval1, 256, ")", 1);
        get_value(tmpval1, irange);
        ptui = TRUE;
        dcin = TRUE;
        iload = (dcleak)?FALSE:TRUE;
        vload = (dcleak)?FALSE:TRUE;
    }
    if (strcmp(dcsetstr, "DCSetLeakOutput") == 0) {
        get_string(oline, tmpval, 256, ",", 2);
        get_value(tmpval, vol);
        get_string(oline, tmpval, 256, ",", 3);
        get_value(tmpval, voh);
        get_string(oline, tmpval, 256, ",", 4);
        get_value(tmpval, vcomm);
        get_string(oline, tmpval, 256, ",", 5);
        get_value(tmpval, iol);
        get_string(oline, tmpval, 256, ",", 6);
        get_string(tmpval, tmpval1, 256, ")", 1);
        get_value(tmpval1, ioh);
        dcin = TRUE;
        iload = (dcleak)?FALSE:TRUE;
        vload = (dcleak)?FALSE:TRUE;
    }
    if (strcmp(dcsetstr, "DCSetPTUIOutput") == 0) {
        get_string(oline, tmpval, 256, ",", 2);
        get_value(tmpval, vol);
        get_string(oline, tmpval, 256, ",", 3);
        get_value(tmpval, voh);
        get_string(oline, tmpval, 256, ",", 4);
        get_value(tmpval, vcomm);
        get_string(oline, tmpval, 256, ",", 5);
        get_value(tmpval, iol);
        get_string(oline, tmpval, 256, ",", 6);
        get_value(tmpval, ioh);
        get_string(oline, tmpval, 256, ",", 7);
        get_string(tmpval, tmpval1, 256, ")", 1);
        get_value(tmpval1, irange);
        ptui = TRUE;
        dcin = TRUE;
        iload = (dcleak)?FALSE:TRUE;
        vload = (dcleak)?FALSE:TRUE;
    }
    if (strcmp(dcsetstr, "DCSetOutput") == 0) {
        get_string(oline, tmpval, 256, ",", 2);
        get_value(tmpval, vol);
        get_string(oline, tmpval, 256, ",", 3);
        get_value(tmpval, voh);
        get_string(oline, tmpval, 256, ",", 4);
        get_value(tmpval, vcomm);
        get_string(oline, tmpval, 256, ",", 5);
        get_value(tmpval, iol);
        get_string(oline, tmpval, 256, ",", 6);
        get_string(tmpval, tmpval1, 256, ")", 1);
        get_value(tmpval1, ioh);
        dcout = TRUE;
        iload = TRUE;
        vload = TRUE;
    }
    if (prtmode) {
        fprintf(fpout,"    %s\n", "LevelsColumnType = evDCTestType;");
        fprintf(fpout,"    %s%30s\"%s\"%s\n", "Group"  , "= Expr { String = ", pinlist, ";}");
        fprintf(fpout,"    %s%28s\"%s\"%s\n", "ExecSeq", "= Expr { String = ", "0", ";}");
        fprintf(fpout,"    %s%25s\"%s\"%s\n", "evForceValue", "= Expr { String = ", vcomm, ";}");
        fprintf(fpout,"    %s%25s\"%s\"%s\n", "evLowLimit", "= Expr { String = ", iol, ";}");
        fprintf(fpout,"    %s%24s\"%s\"%s\n", "evHighLimit", "= Expr { String = ", ioh, ";}");
        if (ptui) {
          fprintf(fpout,"    %s%21s\"%s%s\"%s\n", "evMeasureRange", "= Expr { String = ", irange, " * 1.2", ";}");
        } else {
          fprintf(fpout,"    %s%21s\"%s%s\"%s\n", "evMeasureRange", "= Expr { String = ", ioh, " * 1.2", ";}");
        }
    } else {
        fprintf(fpout,"    %s\n", "LevelsColumnType = evDigitalType;");
        fprintf(fpout,"    %s%30s\"%s\"%s\n", "Group"  , "= Expr { String = ", pinlist, ";}");
        fprintf(fpout,"    %s%28s\"%s\"%s\n", "ExecSeq", "= Expr { String = ", "0", ";}");
        if (dcin) {
          fprintf(fpout,"    %s%32s\"%s\"%s\n", "Vil", "= Expr { String = ", vil, ";}");
          fprintf(fpout,"    %s%32s\"%s\"%s\n", "Vih", "= Expr { String = ", vih, ";}");
        }
        if (dcout) {
          fprintf(fpout,"    %s%32s\"%s\"%s\n", "Vol", "= Expr { String = ", vol, ";}");
          fprintf(fpout,"    %s%32s\"%s\"%s\n", "Voh", "= Expr { String = ", voh, ";}");
        }
        if (vload)
            fprintf(fpout,"    %s%31s\"%s\"%s\n", "Vref", "= Expr { String = ", vcomm, ";}");
        if (iload) {
          fprintf(fpout,"    %s%32s\"%s\"%s\n", "Iol", "= Expr { String = ", iol, ";}");
          fprintf(fpout,"    %s%32s\"%s\"%s\n", "Ioh", "= Expr { String = ", ioh, ";}");
        }
        fprintf(fpout,"    %s%28s\"%s\"%s\n", "ClampLo", "= Expr { String = ", "-50mV" , ";}");
        fprintf(fpout,"    %s%28s\"%s\"%s\n", "ClampHi", "= Expr { String = ", "Vdd_PS+50mV" , ";}");
    } /* dcleak = FALSE */
  return(0);
}

int get_value(char *srcstr,char *result) {
    char tmpstr[256], *ptr;
    int i,j,strip;
    strcpy(tmpstr, srcstr);
    while (NULL!=(ptr=strstr(tmpstr,"v["))){
        *ptr = ' ';
        *(ptr+1) = ' ';
    }
    while (NULL!=(ptr=strstr(tmpstr,"i["))){
        *ptr = ' ';
        *(ptr+1) = ' ';
    }
    while (NULL!=(ptr=strstr(tmpstr,"]")))
        *ptr = ' ';
    
    /* strip whitespace */
    for (strip=j=i=0;i<strlen(tmpstr);i++) {
        if (isgraph((int)tmpstr[i])){tmpstr[j]=tmpstr[i];j++;} else strip++;
    } tmpstr[strlen(tmpstr)-strip] = '\0';/*end strip whitespace */

    strcpy(result, tmpstr);
    return(0);
}
