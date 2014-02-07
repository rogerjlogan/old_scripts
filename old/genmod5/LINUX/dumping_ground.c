
int output_dpm_try2(int *SUPER_CNT,struct LOOP_LINES  *SUPER) {
   int i,lvl,firstbegin=0;
   int i1,i2,i3,i4;
   int j1,j2,j3,j4,j5;
   int count1,count2,count3,count4,count5;
   int rptst1,rptst2,rptst3,rptst4;
   int rptsp1,rptsp2,rptsp3,rptsp4;
   for (lvl=i=0;i<*SUPER_CNT;i++) { /* 0 */
      if (SUPER[i].shutdownvect) {/* don't output normally */
         if(SUPER[i].VectorType==VT_Vector) {
            fprintf(fpstatus,"SHUTDOWN VECTOR[%s]:[%s]\n",infile_orig,SUPER[i].vector);
            continue;
            }
         }
      if (firstbegin==0 && SUPER[i].begin==1) {fprintf(fpout1,"begin\n");firstbegin=1;}
      fprintf(stdout,"RPTC[%d]R0[%d]R1[%d]R2[%d]R3[%d]R4[%d]\n",SUPER[i].repeatcnt,
         SUPER[i].repeat[0],SUPER[i].repeat[1],SUPER[i].repeat[2],SUPER[i].repeat[3],SUPER[i].repeat[4]);
      if (SUPER[i].repeat[0]>0) {/* 1 */
         count1=SUPER[i].repeat[0];
         if (SUPER[i+1].begin==1) { /* 2 */ /* repeat block lvl=1 */
            rptst1=i+2;rptsp1=SUPER[i+1].beginpointtoend;
            for (j1=1;j1<=count1;j1++) { /* 3 */
               for (i1=rptst1;i1<rptsp1;i1++) { /* 4 */
                  if (SUPER[i1].repeat[1]>0) { /* 5 */
                     count2=SUPER[i1].repeat[1];
                     if (SUPER[i1+1].begin==1) { /* 6 */ /* its a begin loop lvl=2 */
                        rptst2=i1+2;rptsp2=SUPER[i1+1].beginpointtoend;
                        for (j2=1;j2<=count2;j2++) { /* 7 */
                           for (i2=rptst2;i2<rptsp2;i2++) { /* 8 */
                              if (SUPER[i2].repeat[2]>0) { /* 9 */
                                 count3=SUPER[i2].repeat[2];
                                 if (SUPER[i2+1].begin==1) { /* 10 */ /* its a begin loop lvl=3 */
                                    rptst3=i2+2;rptsp3=SUPER[i2+1].beginpointtoend;
                                    for (j3=1;j3<=count3;j3++) { /* 11 */
                                       for (i3=rptst3;i3<rptsp3;i3++) { /* 12 */
                                          if (SUPER[i3].repeat[3]>0) { /* 13 */
                                             count4=SUPER[i3].repeat[3];
                                             if (SUPER[i3+1].begin==1) { /* 14 */
                                                rptst4=i3+2;rptsp4=SUPER[i3+1].beginpointtoend;
                                                for (j4=1;j4<=count4;j4++) { /* 15 */
                                                   for (i4=rptst4;i4<rptsp4;i4++) { /* 16 */
                                                      if (SUPER[i4].repeat[4]>0) { /* 17 */
                                                         count5=SUPER[i4].repeat[4];
                                                         for (j5=1;j5<=count5;j5++) fprintf(fpout1,"%s \"V%05d->LC%05d of %05d\"\n",SUPER[i4].vector,i4,j5,count5);
                                                         } /* 17 */
                                                      } /* 16 */
                                                   i3=i4;
                                                   } /* 15 */
                                                } /* 14 */
                                             else { /* level 4 not begin, repeat only */
                                                for (j4=1;j4<=count4;j4++) {
                                                   fprintf(fpout1,"%s \"<4A>V%05d->LC%05d of %05d\"\n",SUPER[i3+1].vector,i3,j4,count4);
                                                   }
                                                }
                                             i3++;
                                             } /* 13 */
                                          else {/* level 4 not repeat */
                                             if (SUPER[i3].VectorType==VT_Vector || SUPER[i3].VectorType==VT_SET) {
                                                fprintf(fpout1,"%s \"<4B> %s \"\n",SUPER[i3].vector,SUPER[i3].comment);
                                                }
                                             } 
                                          } /* 12 */
                                       i2=i3;/* finished second inner loop, set i2 past end of loop */
                                       } /* 11 */
                                    } /* 10 */
                                 else { /* level 3 not begin, repeat only */
                                    for (j3=1;j3<=count3;j3++) {
                                       fprintf(fpout1,"%s \"<3A>V%05d->LC%05d of %05d\"\n",SUPER[i2+1].vector,i2,j3,count3);
                                       }
                                    }
                                 i2++;
                                 } /* 9 */
                              else { /* level 3 not repeat */
                                 if (SUPER[i2].VectorType==VT_Vector || SUPER[i2].VectorType==VT_SET) {
                                    fprintf(fpout1,"%s \"<3B> %s \"\n",SUPER[i2].vector,SUPER[i2].comment);
                                    }
                                 }
                              } /* 8 */
                           i1=i2;/* finished first inner loop, set i1 past end of loop */
                           } /* 7 */
                        } /* 6 */
                     else {/* level 2 not begin, repeat only */
                        for (j2=1;j2<=count2;j2++) {
                           fprintf(fpout1,"%s \"<2A>V%05d->LC%05d of %05d\"\n",SUPER[i1+1].vector,i1,j2,count2);
                           }
                        }
                     i1++;
                     } /* 5 */
                  else {/* level 2 not repeat */
                     if (SUPER[i1].VectorType==VT_Vector || SUPER[i1].VectorType==VT_SET) {
                        fprintf(fpout1,"%s \"<2B> %s \"\n",SUPER[i1].vector,SUPER[i1].comment);
                        }
                     }
                  } /* 4 */
               i=i1;/* finished outer loop, set i past end of loop */
               } /* 3 */
            } /* 2 */
         else {/* not begin, repeat only */
            for (j1=1;j1<=count1;j1++) {
               fprintf(fpout1,"%s \"<1A>V%05d->LC%05d of %05d\"\n",SUPER[i+1].vector,i,j1,count1);
               }
            }
         i++;
         } /* 1 */
      else { /* no repeat */
         if (SUPER[i].VectorType==VT_Vector || SUPER[i].VectorType==VT_SET) {
            fprintf(fpout1,"%s \"<1B> %s \"\n",SUPER[i].vector,SUPER[i].comment);
            }
         }
      } /* 0 */

   fprintf(fpout1,"end;\n");/* close! */
   fflush(fperrors);
   fflush(fpstatus);
   return(i);
   } /* output_dpm */

int output_dpm_old(int *SUPER_CNT,struct LOOP_LINES  *SUPER) {
   int i,j,k,l,lvl,begin=0;
   for (lvl=i=0;i<*SUPER_CNT;i++) {
      if (begin==0 && SUPER[i].begin==1) {fprintf(fpout1,"begin\n");begin=1;}/* start real data */
      if (SUPER[i].repeatcnt && SUPER[i+1].begin==1) {/* its a loop */
         for (j=0;j<SUPER[i].repeatcnt;j++){/* FIXME: APS work with single loop first..., add nested later */
            for (l=0,k=*SUPER_CNT+1;k<SUPER[*SUPER_CNT+1].beginpointtoend;l++,k++) {
               fprintf(fpout1,"%s \"V%05d->LC%05d of %05d\"\n",SUPER[i].vector,l,j,SUPER[i].repeatcnt);
               countlines++;
               }
            }
         }
      else if (SUPER[i].repeatcnt>0) {/* its a vector */
         for (j=0;j<SUPER[i].repeatcnt;j++) {
            fprintf(fpout1,"%s \"LC%05d of %05d\"\n",SUPER[i].vector,j,SUPER[i].repeatcnt);
            countlines++;
            }
         }
      if (SUPER[i].VectorType==VT_Vector || SUPER[i].VectorType==VT_SET) { 
         if (fields!=0) {
            fprintf(fpout1,"%s \"%s\"\n",SUPER[i].vector,SUPER[i].comment);
            countlines++;
            }
         }
      if (SUPER[i].repeatcnt!=0 ) {
         }
      } /* end main for */
   fprintf(fpout1,"end;\n");/* close! */
   fflush(fperrors);
   fflush(fpstatus);
   return(i);
   } /* output_dpm */
