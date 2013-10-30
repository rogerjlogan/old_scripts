/* gct_gen_mod_process_waveforms.c process_waveforms(){} */

#include <stdio.h>
#include <strings.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "ggm_includes.h"


int process_waveforms(FILE *fpwaves,int *fmtcnt,int *which,char *pin,int used_line[],int DSET,int CNT,char *tperiod,int *code0,int *code1) {
   int j,eb,done,sl,wtlookup,edgelookup;
   char org1[100],org2[100],org3[100],org4[100];
   char *name,*ptr0,*ptr1,*ptr1C,*tptr,*pelse,field[20][60],type[60],copybuf[1000],dupwarn[100],hold;
   name=acwaves->w[*which];
   if (CNT!=0) sprintf(dupwarn,"_MULTIPLE_DEF%03d",CNT);
   else                 dupwarn[0]='\0';
   fprintf(fpwaves,"//%s\n",name);fflush(fpwaves);
   if (NULL==strstr(name,"WaveSet") && NULL==strstr(name,"EdgeSet")) return(-1);
   j=0;
   ptr0=strchr(name,'(');
   if (ptr0==NULL) return(-1);
   hold=*ptr0;
   *ptr0='\0';
   strcpy(type,name);
   *ptr0=hold;
   ptr0++;
   eb=0;
   if (NULL!=(pelse=strstr(name,")elsebegin"))) {
      eb=1;
      fprintf(fpwaves,"//Warning 'elsebegin' in waveform definition!!! FIXME!!!\n");
      fprintf(stderr, "//Warning 'elsebegin' in waveform definition!!! FIXME!!!\n");
      *(pelse+1)='\0';
      }
   else if (NULL!=(pelse=strstr(name,")else"))) {
      fprintf(fpwaves,"//Warning 'else' in waveform definition!!! FIXME!!!\n");
      fprintf(stderr, "//Warning 'else' in waveform definition!!! FIXME!!!\n");
      *(pelse+1)='\0';
      }
   done=0;sl=strlen(name);
   while(!done){
      ptr1=strchr(ptr0,',');
      ptr1C=strrchr(ptr0,')');
      if (ptr1==NULL && ptr1C==NULL) {done=1;break;}
      if (ptr1==NULL && ptr1C!=NULL) ptr1=ptr1C;
      if (ptr1C<ptr1 && ptr1C!=NULL) {ptr1=ptr1C;done=1;} /* this is for the case when it finds a ',' after a ')'. e.g.: */
         //WaveSetNR(INT_CLKSTPdriveWF,0ns)elseWaveSetNR(INT_CLKSTPdriveWF,t[tcCI]-t[tsuINTCLKSTP]+dtcf+1ns)
      if (ptr1==NULL) break; /* in case there is nothing useful */
      if (ptr1>name+sl) break; /* in case there is nothing useful */
      hold=*ptr1;
      *ptr1='\0';
      strcpy(field[j],ptr0);
      *ptr1=hold;
      while (NULL!=(tptr=strstr(field[j],"div"))) {
         *tptr=' ';    /* d */
         *(tptr+1)=' ';/* i */
         *(tptr+2)='/';/* v */
         }
      while (NULL!=(tptr=strstr(field[j],"t["))) {
         *tptr=' ';    /* t */
         *(tptr+1)=' ';/* [ */
         }
      while (NULL!=(tptr=strstr(field[j],"]"))) {
         *tptr=' ';    /* ] */
         }
      ptr0=ptr1+1;
      j++;
      if(done) break;
      }
/*DSET0 DSET1
l/h    *L/H drive             0x02
X/.*   x/, driveoffcompareoff 0x09 9=8+1
z/Z    y/Y driveoff only      0x01    
e/E*   k/K EndWindow          0x08
0/1*   o/i EdgeStrobe         0x03
w/W*   v/V WindowStrobe       0x04
f/F*   g/G FloatStrobe        0x05
u/U*   t/T FloatWindow        0x06
-          Continue           0x07
d          CPM/DPM
s/D        scan out/in
*/
/* need to search origin array also!!!!! */
   org1[0]=org2[0]=org3[0]=org4[0]='\0';
   find_origin(field[0],org1,org2,org3,org4);
   wtlookup=(strstr(wavetypefull,type)-wavetypefull);
   cellinfo[cellcnt].filepos=ftell(fpwaves);
   cellinfo[cellcnt].actline=*which;
   strcpy(cellinfo[cellcnt].wftname,GCTNAME);
   strcpy(cellinfo[cellcnt].cellname,field[0]);
   strcpy(cellinfo[cellcnt].pin,pin);
   cellinfo[cellcnt].multidefnum=CNT;
   cellinfo[cellcnt].formatnum=wtlookup;
   if (0==strcmp(type,"WaveSetClk")) {/* Drives Dominate to DSET1 when DSET==3, i.e. same */
      if (DSET==0) *code0=0x02;
      if (DSET==1) *code1=0x02;
      if (DSET==3) *code0=*code1=0x02;
      edgelookup=(strstr(edgetypefull,"DriveData ")-edgetypefull);
      cellinfo[cellcnt].formats[0]=edgelookup;
      edgelookup=(strstr(edgetypefull,"DriveLow ")-edgetypefull);
      cellinfo[cellcnt].formats[1]=edgelookup;
      cellinfo[cellcnt].formats[2]=cellinfo[cellcnt].formats[3]=-1;
      cellcnt++;
      if(cellcnt>MAXCELLS) {
         fprintf(stderr,"Too many Cells for buffer, source line[%d]\n",__LINE__);
         exit(1);
         }
      fprintf(fpwaves,"Cell \"%s\" %c/%c %s_DSET%01d%s {\n\tData %c/%c;\n",pin,(DSET==0)?'l':'L',(DSET==0)?'h':'H',field[0],DSET,dupwarn,'6','7');
      fprintf(fpwaves,"\tDrive {\n\t\tWaveform {DriveData @\"%s%s\";DriveLow @\"%s%s\";}\n\t}\n",field[1],org1,field[2],org2);
      fprintf(fpwaves,"}\n");
      }
   else if (0==strcmp(type,"WaveSetContinue")) {/* Drives Dominate to DSET1 when DSET==3, i.e. same */
      if (DSET==0) *code0=0x07;
      if (DSET==1) *code1=0x07;
      if (DSET==3) *code0=*code1=0x07;
      cellinfo[cellcnt].formats[0]=cellinfo[cellcnt].formats[1]=cellinfo[cellcnt].formats[2]=cellinfo[cellcnt].formats[3]=-1;
      cellcnt++;
      if(cellcnt>MAXCELLS) {
         fprintf(stderr,"Too many Cells for buffer, source line[%d]\n",__LINE__);
         exit(1);
         }
      fprintf(fpwaves,"Cell \"%s\" %c %s_DSET%01d%s {\n\tData %c;\n",pin,'-',field[0],DSET,dupwarn,'6');
      fprintf(fpwaves,"\tDrive {\n      EntryState DriveOn;}\n");
      fprintf(fpwaves,"}\n");
      }
   else if (0==strcmp(type,"WaveSetDoubleClk")) {/* Drives Dominate to DSET1 when DSET==3, i.e. same */
      if (DSET==0) *code0=0x02;
      if (DSET==1) *code1=0x02;
      if (DSET==3) *code0=*code1=0x02;
      edgelookup=(strstr(edgetypefull,"DriveData ")-edgetypefull);
      cellinfo[cellcnt].formats[2]=cellinfo[cellcnt].formats[0]=edgelookup;
      edgelookup=(strstr(edgetypefull,"DriveLow ")-edgetypefull);
      cellinfo[cellcnt].formats[3]=cellinfo[cellcnt].formats[1]=edgelookup;
      cellcnt++;
      if(cellcnt>MAXCELLS) {
         fprintf(stderr,"Too many Cells for buffer, source line[%d]\n",__LINE__);
         exit(1);
         }
      fprintf(fpwaves,"Cell \"%s\" %c/%c %s_DSET%01d%s {\n\tData %c/%c;\n",pin,(DSET==0)?'l':'L',(DSET==0)?'h':'H',field[0],DSET,dupwarn,'6','7');
      fprintf(fpwaves,"\tDrive {\n\t\tWaveform {DriveData @\"%s%s\";DriveLow @\"%s%s\";DriveData @\"%s%s\";DriveLow @\"%s%s\";}\n\t}\n",field[1],org1,field[2],org2,field[3],org3,field[4],org4);
      fprintf(fpwaves,"}\n");
      }
   else if (0==strcmp(type,"WaveSetNR")) {/* Drives Dominate to DSET1 when DSET==3, i.e. same */
      if (DSET==0) *code0=0x02;
      if (DSET==1) *code1=0x02;
      if (DSET==3) *code0=*code1=0x02;
      edgelookup=(strstr(edgetypefull,"DriveData ")-edgetypefull);
      cellinfo[cellcnt].formats[0]=edgelookup;
      cellinfo[cellcnt].formats[1]=cellinfo[cellcnt].formats[2]=cellinfo[cellcnt].formats[3]=-1;
      cellcnt++;
      if(cellcnt>MAXCELLS) {
         fprintf(stderr,"Too many Cells for buffer, source line[%d]\n",__LINE__);
         exit(1);
         }
      fprintf(fpwaves,"Cell \"%s\" %c/%c %s_DSET%01d%s {\n\tData %c/%c;\n",pin,(DSET==0)?'l':'L',(DSET==0)?'h':'H',field[0],DSET,dupwarn,'6','7');
      fprintf(fpwaves,"\tDrive {\n\t\tWaveform {DriveData @\"%s%s\";}\n\t}\n",field[1],org1);
      fprintf(fpwaves,"}\n");
      }
   else if (0==strcmp(type,"WaveSetOff")) {/* DriveOFF&Compare Dominate to DSET0 when DSET==3, i.e. same */
      if (DSET==0) *code0=0x09;
      if (DSET==1) *code1=0x09;
      if (DSET==3) *code0=*code1=0x09;
      fprintf(fpwaves,"Cell \"%s\" %c/%c %s_DSET%01d%s {\n\tData %c/%c;\n",pin,(DSET==1)?'x':'X',(DSET==1)?',':'.',field[0],DSET,dupwarn,'2','3');
      edgelookup=(strstr(edgetypefull,"DriveOff ")-edgetypefull);
      cellinfo[cellcnt].formats[0]=edgelookup;
      cellinfo[cellcnt].formats[1]=cellinfo[cellcnt].formats[2]=cellinfo[cellcnt].formats[3]=-1;
      cellcnt++;
      if(cellcnt>MAXCELLS) {
         fprintf(stderr,"Too many Cells for buffer, source line[%d]\n",__LINE__);
         exit(1);
         }
      fprintf(fpwaves,"\tDrive {\n\t\tWaveform {DriveOff @\"%s%s\";}\n\t}\n",field[1],org1);
      fprintf(fpwaves,"}\n");
      }
   else if (0==strcmp(type,"WaveSetRTO")) {/* Drives Dominate to DSET1 when DSET==3, i.e. same */
      if (DSET==0) *code0=0x02;
      if (DSET==1) *code1=0x02;
      if (DSET==3) *code0=*code1=0x02;
      edgelookup=(strstr(edgetypefull,"DriveData ")-edgetypefull);
      cellinfo[cellcnt].formats[0]=edgelookup;
      edgelookup=(strstr(edgetypefull,"DriveHigh ")-edgetypefull);
      cellinfo[cellcnt].formats[1]=edgelookup;
      cellinfo[cellcnt].formats[2]=cellinfo[cellcnt].formats[3]=-1;
      cellcnt++;
      if(cellcnt>MAXCELLS) {
         fprintf(stderr,"Too many Cells for buffer, source line[%d]\n",__LINE__);
         exit(1);
         }
      fprintf(fpwaves,"Cell \"%s\" %c/%c %s_DSET%01d%s {\n\tData %c/%c;\n",pin,(DSET==0)?'l':'L',(DSET==0)?'h':'H',field[0],DSET,dupwarn,'6','7');
      fprintf(fpwaves,"\tDrive {\n\t\tWaveform {DriveData @\"%s%s\";DriveHigh @\"%s%s\";}\n\t}\n",field[1],org1,field[2],org2);
      fprintf(fpwaves,"}\n");
      }
   else if (0==strcmp(type,"WaveSetRTZ")) {/* Drives Dominate to DSET1 when DSET==3, i.e. same */
      if (DSET==0) *code0=0x02;
      if (DSET==1) *code1=0x02;
      if (DSET==3) *code0=*code1=0x02;
      edgelookup=(strstr(edgetypefull,"DriveData ")-edgetypefull);
      cellinfo[cellcnt].formats[0]=edgelookup;
      edgelookup=(strstr(edgetypefull,"DriveLow ")-edgetypefull);
      cellinfo[cellcnt].formats[1]=edgelookup;
      cellinfo[cellcnt].formats[2]=cellinfo[cellcnt].formats[3]=-1;
      cellcnt++;
      if(cellcnt>MAXCELLS) {
         fprintf(stderr,"Too many Cells for buffer, source line[%d]\n",__LINE__);
         exit(1);
         }
      fprintf(fpwaves,"Cell \"%s\" %c/%c %s_DSET%01d%s {\n\tData %c/%c;\n",pin,(DSET==0)?'l':'L',(DSET==0)?'h':'H',field[0],DSET,dupwarn,'6','7');
      fprintf(fpwaves,"\tDrive {\n\t\tWaveform {DriveData @\"%s%s\";DriveLow @\"%s%s\";}\n\t}\n",field[1],org1,field[2],org2);
      fprintf(fpwaves,"}\n");
      }
   else if (0==strcmp(type,"WaveSetSBC")) {/* Drives Dominate to DSET1 when DSET==3, i.e. same */
      if (DSET==0) *code0=0x02;
      if (DSET==1) *code1=0x02;
      if (DSET==3) *code0=*code1=0x02;
      edgelookup=(strstr(edgetypefull,"DriveComplement ")-edgetypefull);
      cellinfo[cellcnt].formats[2]=cellinfo[cellcnt].formats[0]=edgelookup;
      edgelookup=(strstr(edgetypefull,"DriveData ")-edgetypefull);
      cellinfo[cellcnt].formats[1]=edgelookup;
      cellinfo[cellcnt].formats[3]=-1;
      cellcnt++;
      if(cellcnt>MAXCELLS) {
         fprintf(stderr,"Too many Cells for buffer, source line[%d]\n",__LINE__);
         exit(1);
         }
      fprintf(fpwaves,"Cell \"%s\" %c/%c %s_DSET%01d%s {\n\tData %c/%c;\n",pin,(DSET==0)?'l':'L',(DSET==0)?'h':'H',field[0],DSET,dupwarn,'6','7');
      fprintf(fpwaves,"\tDrive {\n\t\tWaveform {DriveDataNot @\"%s%s\";DriveData @\"%s%s\";DriveDataNot @\"%s%s\";}\n   }\n",field[1],org1,field[2],org2,field[3],org3);
      fprintf(fpwaves,"}\n");
      }
   else if (0==strcmp(type,"WaveSetStrobe")) {/* DriveOFF&Compare Dominate to DSET0 when DSET==3, i.e. same */
      if (DSET==0) *code0=0x04;
      if (DSET==1) *code1=0x04;
      if (DSET==3) *code0=*code1=0x04;
      edgelookup=(strstr(edgetypefull,"DriveOff")-edgetypefull);
      cellinfo[cellcnt].formats[0]=edgelookup;
      edgelookup=(strstr(edgetypefull,"StrobeData ")-edgetypefull);
      cellinfo[cellcnt].formats[1]=edgelookup;
      edgelookup=(strstr(edgetypefull,"StrobeOff ")-edgetypefull);
      cellinfo[cellcnt].formats[2]=edgelookup;
      cellinfo[cellcnt].formats[3]=-1;
      cellcnt++;
      if(cellcnt>MAXCELLS) {
         fprintf(stderr,"Too many Cells for buffer, source line[%d]\n",__LINE__);
         exit(1);
         }
      fprintf(fpwaves,"Cell \"%s\" %c/%c %s_DSET%01d%s {\n\tData %c/%c;\n",pin,(DSET==1)?'v':'w',(DSET==1)?'V':'W',field[0],DSET,dupwarn,'0','1');
      fprintf(fpwaves,"\tDrive {\n\t\tWaveform {DriveOff @\"%s%s\";}\n\t}\n",field[1],org1);
      fprintf(fpwaves,"\tCompare {\n\t\tWaveform { CompareOpenData @\"%s%s\";CompareClose @\"%s%s\";}\n\t}\n",field[2],org2,field[3],org3);
      fprintf(fpwaves,"}\n");
      }
   else if (0==strcmp(type,"WaveSetEdgeStrobe")) {/* DriveOFF&Compare Dominate to DSET0 when DSET==3, i.e. same */
      if (DSET==0) *code0=0x03;
      if (DSET==1) *code1=0x03;
      if (DSET==3) *code0=*code1=0x03;
      edgelookup=(strstr(edgetypefull,"DriveOff ")-edgetypefull);
      cellinfo[cellcnt].formats[0]=edgelookup;
      edgelookup=(strstr(edgetypefull,"EdgeStrobeData ")-edgetypefull);
      cellinfo[cellcnt].formats[1]=edgelookup;
      cellinfo[cellcnt].formats[2]=cellinfo[cellcnt].formats[3]=-1;
      cellcnt++;
      if(cellcnt>MAXCELLS) {
         fprintf(stderr,"Too many Cells for buffer, source line[%d]\n",__LINE__);
         exit(1);
         }
      fprintf(fpwaves,"Cell \"%s\" %c/%c %s_DSET%01d%s {\n\tData %c/%c;\n",pin,(DSET==1)?'o':'0',(DSET==1)?'i':'1',field[0],DSET,dupwarn,'0','1');
      fprintf(fpwaves,"\tDrive {\n\t\tWaveform {DriveOff @\"%s%s\";}\n\t}\n",field[1],org1);
      fprintf(fpwaves,"\tCompare {\n\t\tWaveform { CompareData @\"%s%s\";}\n\t}\n",field[2],org2);
      fprintf(fpwaves,"}\n");
      }
   else if (0==strcmp(type,"WaveSetStrobeZ")) {/* Single Data */ /* DriveOFF&Compare Dominate to DSET0 when DSET==3, i.e. same */
      if (DSET==0) *code0=0x06;
      if (DSET==1) *code1=0x06;
      if (DSET==3) *code0=*code1=0x06;
      edgelookup=(strstr(edgetypefull,"DriveOff ")-edgetypefull);
      cellinfo[cellcnt].formats[0]=edgelookup;
      edgelookup=(strstr(edgetypefull,"StrobeZ ")-edgetypefull);
      cellinfo[cellcnt].formats[1]=edgelookup;
      edgelookup=(strstr(edgetypefull,"StrobeOff ")-edgetypefull);
      cellinfo[cellcnt].formats[2]=edgelookup;
      cellinfo[cellcnt].formats[3]=-1;
      cellcnt++;
      if(cellcnt>MAXCELLS) {
         fprintf(stderr,"Too many Cells for buffer, source line[%d]\n",__LINE__);
         exit(1);
         }
      fprintf(fpwaves,"Cell \"%s\" %c/%c %s_DSET%01d%s {\n\tData %c/%c;\n",pin,(DSET==1)?'t':'u',(DSET==1)?'T':'U',field[0],DSET,dupwarn,'0','1');
      fprintf(fpwaves,"\tDrive {\n\t\tWaveform {DriveOff @\"%s%s\";}\n\t}\n",field[1],org1);
      fprintf(fpwaves,"\tCompare {\n\t\tWaveform { CompareOpenFloat @\"%s%s\";CompareClose @\"%s%s\";}\n\t}\n",field[2],org2,field[3],org3);
      fprintf(fpwaves,"}\n");
      }
   else if (0==strcmp(type,"WaveSetEdgeStrobeZ")) {/* Single Data */ /* DriveOFF&Compare Dominate to DSET0 when DSET==3, i.e. same */
      if (DSET==0) *code0=0x05;
      if (DSET==1) *code1=0x05;
      if (DSET==3) *code0=*code1=0x05;
      edgelookup=(strstr(edgetypefull,"DriveOff ")-edgetypefull);
      cellinfo[cellcnt].formats[0]=edgelookup;
      edgelookup=(strstr(edgetypefull,"EdgeStrobeZ ")-edgetypefull);
      cellinfo[cellcnt].formats[1]=edgelookup;
      cellinfo[cellcnt].formats[2]=cellinfo[cellcnt].formats[3]=-1;
      cellcnt++;
      if(cellcnt>MAXCELLS) {
         fprintf(stderr,"Too many Cells for buffer, source line[%d]\n",__LINE__);
         exit(1);
         }
      fprintf(fpwaves,"Cell \"%s\" %c/%c %s_DSET%01d%s {\n\tData %c/%c;\n",pin,(DSET==1)?'g':'f',(DSET==1)?'G':'F',field[0],DSET,dupwarn,'0','1');
      fprintf(fpwaves,"\tDrive {\n\t\tWaveform {DriveOff @\"%s%s\";}\n\t}\n",field[1],org1);
      fprintf(fpwaves,"\tCompare {\n\t\tWaveform { CompareFloat @\"%s%s\";}\n\t}\n",field[2],org2);
      fprintf(fpwaves,"}\n");
      }
   else if (0==strcmp(type,"WaveSetDelayClk")) {/* Drives Dominate to DSET1 when DSET==3, i.e. same */
      if (DSET==0) *code0=0x02;
      if (DSET==1) *code1=0x02;
      if (DSET==3) *code0=*code1=0x02;
      edgelookup=(strstr(edgetypefull,"DriveData ")-edgetypefull);
      cellinfo[cellcnt].formats[0]=edgelookup;
      edgelookup=(strstr(edgetypefull,"DriveLow ")-edgetypefull);
      cellinfo[cellcnt].formats[1]=edgelookup;
      cellinfo[cellcnt].formats[2]=cellinfo[cellcnt].formats[3]=-1;
      cellcnt++;
      if(cellcnt>MAXCELLS) {
         fprintf(stderr,"Too many Cells for buffer, source line[%d]\n",__LINE__);
         exit(1);
         }
      fprintf(fpwaves,"Cell \"%s\" %c/%c %s_DSET%01d%s {\n\tData %c/%c;\n",pin,(DSET==0)?'l':'L',(DSET==0)?'h':'H',field[0],DSET,dupwarn,'6','7');
      fprintf(fpwaves,"\tDrive {\n\t\tWaveform {DriveData @\"%s%s+%s*%s\";DriveLow @\"%s%s+%s*%s\";}\n\t}\n",field[1],org1,field[3],tperiod,field[2],org2,field[4],tperiod);
      fprintf(fpwaves,"}\n");
      }
/* no wavesetdelaycontinue */
   else if (0==strcmp(type,"WaveSetDelayDoubleClk")) {/* Drives Dominate to DSET1 when DSET==3, i.e. same */
      if (DSET==0) *code0=0x02;
      if (DSET==1) *code1=0x02;
      if (DSET==3) *code0=*code1=0x02;
      edgelookup=(strstr(edgetypefull,"DriveData ")-edgetypefull);
      cellinfo[cellcnt].formats[2]=cellinfo[cellcnt].formats[0]=edgelookup;
      edgelookup=(strstr(edgetypefull,"DriveLow ")-edgetypefull);
      cellinfo[cellcnt].formats[3]=cellinfo[cellcnt].formats[1]=edgelookup;
      cellcnt++;
      if(cellcnt>MAXCELLS) {
         fprintf(stderr,"Too many Cells for buffer, source line[%d]\n",__LINE__);
         exit(1);
         }
      fprintf(fpwaves,"Cell \"%s\" %c/%c %s_DSET%01d%s {\n\tData %c/%c;\n",pin,(DSET==0)?'l':'L',(DSET==0)?'h':'H',field[0],DSET,dupwarn,'6','7');
      fprintf(fpwaves,"\tDrive {\n\t\tWaveform {DriveData @\"%s%s+%s*%s\";DriveLow @\"%s%s+%s*%s\";DriveData @\"%s%s+%s*%s\";DriveLow @\"%s%s+%s*%s\";}\n\t}\n",field[1],org1,field[5],tperiod,field[2],org2,field[6],tperiod,field[3],org3,field[7],tperiod,field[4],org4,field[8],tperiod);
      fprintf(fpwaves,"}\n");
      }
   else if (0==strcmp(type,"WaveSetDelayNR")) {/* Drives Dominate to DSET1 when DSET==3, i.e. same */
      if (DSET==0) *code0=0x02;
      if (DSET==1) *code1=0x02;
      if (DSET==3) *code0=*code1=0x02;
      edgelookup=(strstr(edgetypefull,"DriveData ")-edgetypefull);
      cellinfo[cellcnt].formats[0]=edgelookup;
      cellinfo[cellcnt].formats[1]=cellinfo[cellcnt].formats[2]=cellinfo[cellcnt].formats[3]=-1;
      cellcnt++;
      if(cellcnt>MAXCELLS) {
         fprintf(stderr,"Too many Cells for buffer, source line[%d]\n",__LINE__);
         exit(1);
         }
      fprintf(fpwaves,"Cell \"%s\" %c/%c %s_DSET%01d%s {\n\tData %c/%c;\n",pin,(DSET==0)?'l':'L',(DSET==0)?'h':'H',field[0],DSET,dupwarn,'6','7');
      fprintf(fpwaves,"\tDrive {\n\t\tWaveform {DriveData @\"%s%s+%s*%s\";}\n\t}\n",field[1],org1,field[2],tperiod);
      fprintf(fpwaves,"}\n");
      }
   else if (0==strcmp(type,"WaveSetDelayOff")) {/* DriveOFF&Compare Dominate to DSET0 when DSET==3, i.e. same */
      if (DSET==0) *code0=0x09;
      if (DSET==1) *code1=0x09;
      if (DSET==3) *code0=*code1=0x09;
      fprintf(fpwaves,"Cell \"%s\" %c/%c %s_DSET%01d%s {\n\tData %c/%c;\n",pin,(DSET==1)?'x':'X',(DSET==1)?',':'.',field[0],DSET,dupwarn,'2','3');
      edgelookup=(strstr(edgetypefull,"DriveOff ")-edgetypefull);
      cellinfo[cellcnt].formats[0]=edgelookup;
      cellinfo[cellcnt].formats[1]=cellinfo[cellcnt].formats[2]=cellinfo[cellcnt].formats[3]=-1;
      cellcnt++;
      if(cellcnt>MAXCELLS) {
         fprintf(stderr,"Too many Cells for buffer, source line[%d]\n",__LINE__);
         exit(1);
         }
      fprintf(fpwaves,"\tDrive {\n\t\tWaveform {DriveOff @\"%s%s+%s*%s\";}\n\t}\n",field[1],org1,field[2],tperiod);
      fprintf(fpwaves,"}\n");
      }
   else if (0==strcmp(type,"WaveSetDelayRTO")) {/* Drives Dominate to DSET1 when DSET==3, i.e. same */
      if (DSET==0) *code0=0x02;
      if (DSET==1) *code1=0x02;
      if (DSET==3) *code0=*code1=0x02;
      edgelookup=(strstr(edgetypefull,"DriveData ")-edgetypefull);
      cellinfo[cellcnt].formats[0]=edgelookup;
      edgelookup=(strstr(edgetypefull,"DriveHigh ")-edgetypefull);
      cellinfo[cellcnt].formats[1]=edgelookup;
      cellinfo[cellcnt].formats[2]=cellinfo[cellcnt].formats[3]=-1;
      cellcnt++;
      if(cellcnt>MAXCELLS) {
         fprintf(stderr,"Too many Cells for buffer, source line[%d]\n",__LINE__);
         exit(1);
         }
      fprintf(fpwaves,"Cell \"%s\" %c/%c %s_DSET%01d%s {\n\tData %c/%c;\n",pin,(DSET==0)?'l':'L',(DSET==0)?'h':'H',field[0],DSET,dupwarn,'6','7');
      fprintf(fpwaves,"\tDrive {\n\t\tWaveform {DriveData @\"%s%s+%s*%s\";DriveHigh @\"%s%s+%s*%s\";}\n\t}\n",field[1],org1,field[3],tperiod,field[2],org2,field[4],tperiod);
      fprintf(fpwaves,"}\n");
      }
   else if (0==strcmp(type,"WaveSetDelayRTZ")) {/* Drives Dominate to DSET1 when DSET==3, i.e. same */
      if (DSET==0) *code0=0x02;
      if (DSET==1) *code1=0x02;
      if (DSET==3) *code0=*code1=0x02;
      edgelookup=(strstr(edgetypefull,"DriveData ")-edgetypefull);
      cellinfo[cellcnt].formats[0]=edgelookup;
      edgelookup=(strstr(edgetypefull,"DriveLow ")-edgetypefull);
      cellinfo[cellcnt].formats[1]=edgelookup;
      cellinfo[cellcnt].formats[2]=cellinfo[cellcnt].formats[3]=-1;
      cellcnt++;
      if(cellcnt>MAXCELLS) {
         fprintf(stderr,"Too many Cells for buffer, source line[%d]\n",__LINE__);
         exit(1);
         }
      fprintf(fpwaves,"Cell \"%s\" %c/%c %s_DSET%01d%s {\n\tData %c/%c;\n",pin,(DSET==0)?'l':'L',(DSET==0)?'h':'H',field[0],DSET,dupwarn,'6','7');
      fprintf(fpwaves,"\tDrive {\n\t\tWaveform {DriveData @\"%s%s+%s*%s\";DriveLow @\"%s%s+%s*%s\";}\n\t}\n",field[1],org1,field[3],tperiod,field[2],org2,field[4],tperiod);
      fprintf(fpwaves,"}\n");
      }
   else if (0==strcmp(type,"WaveSetDelaySBC")) {/* Drives Dominate to DSET1 when DSET==3, i.e. same */
      if (DSET==0) *code0=0x02;
      if (DSET==1) *code1=0x02;
      if (DSET==3) *code0=*code1=0x02;
      edgelookup=(strstr(edgetypefull,"DriveComplement ")-edgetypefull);
      cellinfo[cellcnt].formats[2]=cellinfo[cellcnt].formats[0]=edgelookup;
      edgelookup=(strstr(edgetypefull,"DriveData ")-edgetypefull);
      cellinfo[cellcnt].formats[1]=edgelookup;
      cellinfo[cellcnt].formats[3]=-1;
      cellcnt++;
      if(cellcnt>MAXCELLS) {
         fprintf(stderr,"Too many Cells for buffer, source line[%d]\n",__LINE__);
         exit(1);
         }
      fprintf(fpwaves,"Cell \"%s\" %c/%c %s_DSET%01d%s {\n\tData %c/%c;\n",pin,(DSET==0)?'l':'L',(DSET==0)?'h':'H',field[0],DSET,dupwarn,'6','7');
      fprintf(fpwaves,"\tDrive {\n\t\tWaveform {DriveDataNot @\"%s%s+%s*%s\";DriveData @\"%s%s+%s*%s\";DriveDataNot @\"%s%s+%s*%s\";}\n   }\n",field[1],org1,field[4],tperiod,field[2],org2,field[5],tperiod,field[3],org3,field[6],tperiod);
      fprintf(fpwaves,"}\n");
      }
   else if (0==strcmp(type,"WaveSetDelayStrobe")) {/* DriveOFF&Compare Dominate to DSET0 when DSET==3, i.e. same */
      if (DSET==0) *code0=0x04;
      if (DSET==1) *code1=0x04;
      if (DSET==3) *code0=*code1=0x04;
      edgelookup=(strstr(edgetypefull,"DriveOff")-edgetypefull);
      cellinfo[cellcnt].formats[0]=edgelookup;
      edgelookup=(strstr(edgetypefull,"StrobeData ")-edgetypefull);
      cellinfo[cellcnt].formats[1]=edgelookup;
      edgelookup=(strstr(edgetypefull,"StrobeOff ")-edgetypefull);
      cellinfo[cellcnt].formats[2]=edgelookup;
      cellinfo[cellcnt].formats[3]=-1;
      cellcnt++;
      if(cellcnt>MAXCELLS) {
         fprintf(stderr,"Too many Cells for buffer, source line[%d]\n",__LINE__);
         exit(1);
         }
      fprintf(fpwaves,"Cell \"%s\" %c/%c %s_DSET%01d%s {\n\tData %c/%c;\n",pin,(DSET==1)?'v':'w',(DSET==1)?'V':'W',field[0],DSET,dupwarn,'0','1');
      fprintf(fpwaves,"\tDrive {\n\t\tWaveform {DriveOff @\"%s%s+%s*%s\";}\n\t}\n",field[1],org1,field[4],tperiod);
      fprintf(fpwaves,"\tCompare {\n\t\tWaveform { CompareOpenData @\"%s%s+%s*%s\";CompareClose @\"%s%s+%s*%s\";}\n\t}\n",field[2],org2,field[5],tperiod,field[3],org3,field[6],tperiod);
      fprintf(fpwaves,"}\n");
      }
   else if (0==strcmp(type,"WaveSetDelayEdgeStrobe")) {/* DriveOFF&Compare Dominate to DSET0 when DSET==3, i.e. same */
      if (DSET==0) *code0=0x03;
      if (DSET==1) *code1=0x03;
      if (DSET==3) *code0=*code1=0x03;
      edgelookup=(strstr(edgetypefull,"DriveOff ")-edgetypefull);
      cellinfo[cellcnt].formats[0]=edgelookup;
      edgelookup=(strstr(edgetypefull,"EdgeStrobeData ")-edgetypefull);
      cellinfo[cellcnt].formats[1]=edgelookup;
      cellinfo[cellcnt].formats[2]=cellinfo[cellcnt].formats[3]=-1;
      cellcnt++;
      if(cellcnt>MAXCELLS) {
         fprintf(stderr,"Too many Cells for buffer, source line[%d]\n",__LINE__);
         exit(1);
         }
      fprintf(fpwaves,"Cell \"%s\" %c/%c %s_DSET%01d%s {\n\tData %c/%c;\n",pin,(DSET==1)?'o':'0',(DSET==1)?'i':'1',field[0],DSET,dupwarn,'0','1');
      fprintf(fpwaves,"\tDrive {\n\t\tWaveform {DriveOff @\"%s%s+%s*%s\";}\n\t}\n",field[1],org1,field[3],tperiod);
      fprintf(fpwaves,"\tCompare {\n\t\tWaveform { CompareData @\"%s%s+%s*%s\";}\n\t}\n",field[2],org2,field[4],tperiod);
      fprintf(fpwaves,"}\n");
      }
   else if (0==strcmp(type,"WaveSetDelayStrobeZ")) {/* Single Data */ /* DriveOFF&Compare Dominate to DSET0 when DSET==3, i.e. same */
      if (DSET==0) *code0=0x06;
      if (DSET==1) *code1=0x06;
      if (DSET==3) *code0=*code1=0x06;
      edgelookup=(strstr(edgetypefull,"DriveOff ")-edgetypefull);
      cellinfo[cellcnt].formats[0]=edgelookup;
      edgelookup=(strstr(edgetypefull,"StrobeZ ")-edgetypefull);
      cellinfo[cellcnt].formats[1]=edgelookup;
      edgelookup=(strstr(edgetypefull,"StrobeOff ")-edgetypefull);
      cellinfo[cellcnt].formats[2]=edgelookup;
      cellinfo[cellcnt].formats[3]=-1;
      cellcnt++;
      if(cellcnt>MAXCELLS) {
         fprintf(stderr,"Too many Cells for buffer, source line[%d]\n",__LINE__);
         exit(1);
         }
      fprintf(fpwaves,"Cell \"%s\" %c/%c %s_DSET%01d%s {\n\tData %c/%c;\n",pin,(DSET==1)?'t':'u',(DSET==1)?'T':'U',field[0],DSET,dupwarn,'0','1');
      fprintf(fpwaves,"\tDrive {\n\t\tWaveform {DriveOff @\"%s%s+%s*%s\";}\n\t}\n",field[1],org1,field[4],tperiod);
      fprintf(fpwaves,"\tCompare {\n\t\tWaveform { CompareOpenFloat @\"%s%s+%s*%s\";CompareClose @\"%s%s+%s*%s\";}\n\t}\n",field[2],org2,field[5],tperiod,field[3],org3,field[6],tperiod);
      fprintf(fpwaves,"}\n");
      }
   else if (0==strcmp(type,"WaveSetDelayEdgeStrobeZ")) {/* Single Data */ /* DriveOFF&Compare Dominate to DSET0 when DSET==3, i.e. same */
      if (DSET==0) *code0=0x05;
      if (DSET==1) *code1=0x05;
      if (DSET==3) *code0=*code1=0x05;
      edgelookup=(strstr(edgetypefull,"DriveOff ")-edgetypefull);
      cellinfo[cellcnt].formats[0]=edgelookup;
      edgelookup=(strstr(edgetypefull,"EdgeStrobeZ ")-edgetypefull);
      cellinfo[cellcnt].formats[1]=edgelookup;
      cellinfo[cellcnt].formats[2]=cellinfo[cellcnt].formats[3]=-1;
      cellcnt++;
      if(cellcnt>MAXCELLS) {
         fprintf(stderr,"Too many Cells for buffer, source line[%d]\n",__LINE__);
         exit(1);
         }
      fprintf(fpwaves,"Cell \"%s\" %c/%c %s_DSET%01d%s {\n\tData %c/%c;\n",pin,(DSET==1)?'g':'f',(DSET==1)?'G':'F',field[0],DSET,dupwarn,'0','1');
      fprintf(fpwaves,"\tDrive {\n\t\tWaveform {DriveOff @\"%s%s+%s*%s\";}\n\t}\n",field[1],org1,field[3],tperiod);
      fprintf(fpwaves,"\tCompare {\n\t\tWaveform { CompareFloat @\"%s%s+%s*%s\";}\n\t}\n",field[2],org2,field[4],tperiod);
      fprintf(fpwaves,"}\n");
      }
   else if (0==strcmp(type,"EdgeSetDelayData")) {
      process_edgesetdelay_waveform(fpwaves,fmtcnt,which,pin,used_line,DSET,CNT,tperiod,code0,code1);
      }
   else if (0==strcmp(type,"EdgeSet")) {         
      process_edgeset_waveform(fpwaves,fmtcnt,which,pin,used_line,DSET,CNT,tperiod,code0,code1);
      }
   if (NULL!=pelse) {
      fprintf(fpwaves,"//Warning 'else' in waveform definition!!! FIXME!!!\n");
      fprintf(stderr, "//Warning 'else' in waveform definition!!! FIXME!!!\n");
      strcpy(copybuf,pelse+5+eb*5);/* +5=>")else"); +5+eb*5 => ")elsebegin  */
      strcpy(name,copybuf);/* replace the line with second part of the line and re-call the function */
      process_waveforms(fpwaves,fmtcnt,which,pin,used_line,DSET,CNT+100,tperiod,code0,code1); /* self referencing call!!!! */
      /* FIXME: APS should copy the first part and 
              add the second to the end of the list
              before calling again now pointing at the end */
      }
   return(0);
   }
