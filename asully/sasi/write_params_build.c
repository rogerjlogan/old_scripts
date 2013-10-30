#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "includes_build.h"

int write_params()
{
	FILE *fpDataggm, *fpSpec;
//  int i,j,ss,bl;
//  int cdtbw,done,el,deep,depth,printhead,cat;
	int uniquecat, uniquedev, uniquetst, uniquetmp, uniquerem;
//  char *ptr,exprbuf[500];

	if (NULL == (fpDataggm = fopen(DATACONTROL, "r"))) {
//		fclose(fpDataggm);
		return (1);
	}

	if (NULL != (fpSpec = fopen(ACTPARAMSTBL, "r"))) {	/* close/exit if it exists, reversed from above */
//		fclose(fpSpec);
		fclose(fpDataggm);
		return (2);
	}

	if (NULL == (fpSpec = fopen(ACTPARAMSTBL, "w"))) {
		fprintf(stderr, "\nCan't open file %s\n", ACTPARAMSTBL);
		exit(1);
	}
	fprintf(fpSpec, "%s\n", ENVISIONTOP);

	uniquecat = uniquedev = uniquetst = uniquetmp = uniquerem = 0;
//  maxstartstop=0;
// 
//  /* read_ggm(fpInhggm);*/ /* already read */
//  read_ggm(fpDataggm);
//  fclose(fpDataggm);
// 
//  for (ss=0,deep='0';ss<maxstartstop;ss++) {/* deep is an ascii character not an integer! */
//      if (startstop[ss].lvl>deep) deep=startstop[ss].lvl;
//      if (startstop[ss].udev>uniquedev) uniquedev=startstop[ss].udev;
//      if (startstop[ss].utst>uniquetst) uniquetst=startstop[ss].utst;
//      if (startstop[ss].utmp>uniquetmp) uniquetmp=startstop[ss].utmp;
//      if (startstop[ss].urem>uniquerem) uniquerem=startstop[ss].urem;
//      if (startstop[ss].ucat>uniquecat) uniquecat=startstop[ss].ucat;
//      }
//    fprintf(fpSpec,"//UNIQUE CAT:%d TMP:%d DEV:%d TST:%d REM:%d\n",
//     uniquecat+1,uniquetmp+1,uniquedev+1,uniquetst+1,uniquerem+1);
//  fprintf(fpSpec,"Spec ENUMCTRL {\n");
//  for (i=0;i<=uniquetmp;i++) {
//      fprintf(fpSpec,"   EC%s_TMP%d = \"select(TITestTemp,  ",(ACDATA)?"D":"T",i);
//      for (ss=0;ss<maxstartstop;ss++) {
//          if (i==startstop[ss].utmp) {
//              for (j=0;j<G_maxtmp;j++) {
//                  fprintf(fpSpec,"%s",(startstop[ss].enumtype[j]=='1')?" TRUE":"FALSE");
//                  if (j!=(G_maxtmp-1)) fputc(',',fpSpec);
//                  }
//              fprintf(fpSpec,")\";\n");
//              break;
//              }
//          }
//      }
//  for (i=0;i<=uniquedev;i++) {
//      fprintf(fpSpec,"   EC%s_DEV%d = \"select(TIDeviceType,",(ACDATA)?"D":"T",i);
//      for (ss=0;ss<maxstartstop;ss++) {
//          if (i==startstop[ss].udev) {
//              for (j=0;j<G_maxdev;j++) {
//                  fprintf(fpSpec,"%s",(startstop[ss].enumtype[j+G_maxtmp]=='1')?" TRUE":"FALSE");
//                  if (j!=(G_maxdev-1)) fputc(',',fpSpec);
//                  }
//              fprintf(fpSpec,")\";\n");
//              break;
//              }
//          }
//      }
//  for (i=0;i<=uniquetst;i++) {
//      fprintf(fpSpec,"   EC%s_TST%d = \"select(TITestType,  ",(ACDATA)?"D":"T",i);
//      for (ss=0;ss<maxstartstop;ss++) {
//          if (i==startstop[ss].utst) {
//              for (j=0;j<G_maxtst;j++) {
//                  fprintf(fpSpec,"%s",(startstop[ss].enumtype[j+G_maxtmp+G_maxdev]=='1')?" TRUE":"FALSE");
//                  if (j!=(G_maxtst-1)) fputc(',',fpSpec);
//                  }
//              fprintf(fpSpec,")\";\n");
//              break;
//              }
//          }
//      }
//  for (i=0;i<=uniquerem;i++) {
//      fprintf(fpSpec,"   EC%s_REM%d = \"",(ACDATA)?"D":"T",i);
//      for (ss=0;ss<maxstartstop;ss++) {
//          if (i==startstop[ss].urem) {
//              for (j=0;j<G_maxrem;j++) {
//                  fprintf(fpSpec,"(%s=%s)",enumstr[j],(startstop[ss].enumtype[j+G_maxtmp+G_maxdev+G_maxtst]=='1')?" TRUE":"FALSE");
//                  if (j!=(G_maxrem-1)) fprintf(fpSpec," AND ");
//                  }
//              fprintf(fpSpec,"\";\n");
//              break;
//              }
//          }
//      }
//  fprintf(fpSpec,"   ParamGlobals {\n");
//  for (i=0;i<=uniquetmp;i++) fprintf(fpSpec,"      EC%s_TMP%d { Type = BOOLEAN; }\n",(ACDATA)?"D":"T",i);
//  for (i=0;i<=uniquedev;i++) fprintf(fpSpec,"      EC%s_DEV%d { Type = BOOLEAN; }\n",(ACDATA)?"D":"T",i);
//  for (i=0;i<=uniquetst;i++) fprintf(fpSpec,"      EC%s_TST%d { Type = BOOLEAN; }\n",(ACDATA)?"D":"T",i);
//  for (i=0;i<=uniquerem;i++) fprintf(fpSpec,"      EC%s_REM%d { Type = BOOLEAN; }\n",(ACDATA)?"D":"T",i);
//  fprintf(fpSpec,"   }\n}\n");
// 
//  for (i=0;i<paramcnt;i++) {
//      paraminfo[i].used=0;
//      }
//  fprintf(fpSpec,"Spec ACTIMING_%s_%d {\n",(ACDATA)?"DATA":"TBL",uniquecat);
//  for (depth=deep;depth>'0';depth--) {/* depth is an ascii character not a integer! */
//      for (cat=0;cat<=uniquecat;cat++) {
//          done=0;
//          printhead=0;
//          cdtbw='?';
//          for (ss=0;ss<maxstartstop && done==0;ss++) {
//              if (startstop[ss].type!=SSSTART) continue;/* is start */
//              if (startstop[ss].lvl==(depth-1)) {cdtbw=startstop[ss].cdtcode;}
//              if (startstop[ss].ucat!=cat) continue;
//              done=0;
//              if (depth!=startstop[ss].lvl) continue;
//              bl=startstop[ss].line;
//              el=startstop[startstop[ss].startpt2stop].line;
//              for (i=0;i<paramcnt;i++) {
//                  if (paraminfo[i].used!=0) continue;
//                  if (paraminfo[i].actline>bl && paraminfo[i].actline<el) {
//                      strcpy(exprbuf,paraminfo[i].param_def);
//                  while(NULL!=(ptr=strstr(exprbuf,"t["))) {*ptr=' ';*(ptr+1)=' ';}
//                  while(NULL!=(ptr=strstr(exprbuf,"]"))) {*ptr=' ';}
//                  while(NULL!=(ptr=strstr(exprbuf,"div"))) {
//                      if (isdigit(*(ptr+3))) {*ptr=' ';*(ptr+1)='/';*(ptr+2)=' ';}
//                      }
//                  while(NULL!=(ptr=strstr(exprbuf,":="))) {*ptr='=';*(ptr+1)='\"';}/* remap ':=' to '="' */
//                      if (printhead==0) {
//                      fprintf(fpSpec,"   Category %c%c {// %d\n",startstop[ss].cdtcode,depth,bl);
//                      if (depth!='1') fprintf(fpSpec,"      Inherit %c%c;\n",cdtbw,depth-1);
//                      printhead=1;
//                      }
//                  fprintf(fpSpec,"      %s\";//",exprbuf);
//                  if (uniquedev>=1 && startstop[ss].udev>0) fprintf(fpSpec,"EC%s_DEV%d ",(ACDATA)?"D":"T",startstop[ss].udev);
//                  if (uniquetst>=1 && startstop[ss].utst>0) fprintf(fpSpec,"EC%s_TST%d ",(ACDATA)?"D":"T",startstop[ss].utst);
//                  if (uniquetmp>=1 && startstop[ss].utmp>0) fprintf(fpSpec,"EC%s_TMP%d ",(ACDATA)?"D":"T",startstop[ss].utmp);
//                  if (uniquerem>=1 && startstop[ss].urem>0) fprintf(fpSpec,"EC%s_REM%d ",(ACDATA)?"D":"T",startstop[ss].urem);
//                  fprintf(fpSpec," %d\n",paraminfo[i].actline);
//                  paraminfo[i].used=1;/* DEV[%d]TMP[%d]TST[%d]REM[%d] %d\n */
//                  }
//              }
//          }
//      if (printhead!=0) fprintf(fpSpec,"   }//%d\n",el);
//          }
//      }
//  fprintf(fpSpec,"   ParamGlobals{\n");
//  fprintf(fpSpec,"   /* You need to add these yourself! */\n");
//  fprintf(fpSpec,"   }\n");
//  fprintf(fpSpec,"}\n");
//  fclose(fpSpec);
	return (0);
}
