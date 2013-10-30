START(ALLENUMS,ALLTABLES);

(* APS: the following function is from sync.p *)
(*      the real actable.p file is listed after this *)


procedure RstCustomWF;

begin

  with ACDataSheets[actablename] do
    begin
START(RUN_SYNC,ALLDEVICES,ALLTEMPS,ALLTESTS,TIparametricACTable,TIcrystalACTable,TInomlooseACTable,TIstressminACTable,TIstressmaxACTable,TIlofrqminACTable,TIlofrqmaxACTable,TIlofrqlooseACTable,TIlofrqmin60ACTable,TIlofrqmax60ACTable,TIlofrqloose60ACTable,TIhifrqmin33ACTable,TIhifrqmax33ACTable,TIhifrqmin40ACTable,TIhifrqmax40ACTable,TIhifrqloose40ACTable,TIhifrqmin50ACTable,TIhifrqmax50ACTable,TIhifrqloose50ACTable,TIhifrqmin60ACTable,TIhifrqmax60ACTable,TIhifrqloose60ACTable,TIsearchACTable,TIsearch40ACTable,TIsearchlevelsACTable,TIsearchlevels40ACTable,TIcharACTable,TIchar33ACTable,TIchar40ACTable);

    case actablename of
      TIparametricACTable,
      TIcrystalACTable,
      TInomlooseACTable,
      TIstressminACTable,
      TIstressmaxACTable,
      TIlofrqminACTable,
      TIlofrqmaxACTable,
      TIlofrqlooseACTable,
      TIlofrqmin60ACTable,
      TIlofrqmax60ACTable,
      TIlofrqloose60ACTable,
      TIhifrqmin33ACTable,
      TIhifrqmax33ACTable,
      TIhifrqmin40ACTable,
      TIhifrqmax40ACTable,
      TIhifrqloose40ACTable,
      TIhifrqmin50ACTable,
      TIhifrqmax50ACTable,
      TIhifrqloose50ACTable,
      TIhifrqmin60ACTable,
      TIhifrqmax60ACTable,
      TIhifrqloose60ACTable,
      TIsearchACTable,
      TIsearch40ACTable,
      TIsearchlevelsACTable,
      TIsearchlevels40ACTable,
      TIcharACTable,
      TIchar33ACTable,
      TIchar40ACTable:
        begin

        EdgeSetDelayData    (RESETdriveWF,Edge1,ChanFirst,
                            DriveData,ThreshVITL,
                            t[tref]+t[true_toffset]+t[twCIH]+t[twCIL]+
                            t[twCIH]-t[tsuRESET]-t[loossetup]+dtcf,0,
                            DriveData,ThreshVITH,
                            t[tref]+t[true_tH1flo]-t[tsuRESETH]-t[loossetup]+dtcf,0);

        EdgeSetDelayData    (CREQdriveWF,Edge1,ChanFirst,
                            DriveData,ThreshVITL,
                            t[tref]+t[true_tH1flo]-t[tsuCREQ],0,
                            DriveData,ThreshVITH,
                            t[tref]+t[true_tH1flo]+t[tsuCREQ],0);

(*bb  changed each edge of CSTRBstrobeWF by -4ns for char33 at 0c problem  for 0 and 1 data*)
       if (actablename = TIchar33ACTable) then
          begin
START(RUN_SYNC,ALLDEVICES,ALLTEMPS,ALLTESTS,TIchar33ACTable);

            EdgeSetDelayData    (CREQstrobeWF,Edge1,ChanFirst,
                            DriveOff,ThreshVITL,t[tref]+
                            t[tdH1HRQLt]+t[loosdelay]-t[tgb]-ctcf-7ns,0,
                            DriveOff,ThreshVITH,t[tref]+
                            t[true_tH1flo]-t[tsuCACK]+t[tdALRQHt]+
                            t[loosdelay]-t[tgb]-ctcf-7ns-4ns,0);
            EdgeSetDelayData    (CREQstrobeWF,Edge2,ChanFirst,
                            StrobeData,ThreshVITL,t[tref]+
                            t[tdH1HRQLt]+t[loosdelay]-t[tgb]-ctcf,0,
                            StrobeData,ThreshVITH,t[tref]+
                            t[true_tH1flo]-t[tsuCACK]+t[tdALRQHt]+
                            t[loosdelay]-t[tgb]-ctcf-4ns,0);
            EdgeSetDelayData    (CREQstrobeWF,Edge3,ChanFirst,
                            StrobeOff,ThreshVITL,t[tref]+
                            t[tdH1HRQLt]+t[loosdelay]-t[tgb]-ctcf+7ns,0,
                            StrobeOff,ThreshVITH,t[tref]+
                            t[true_tH1flo]-t[tsuCACK]+t[tdALRQHt]+
                            t[loosdelay]-t[tgb]-ctcf+7ns-4ns,0);
          end
STOP(RUN_SYNC,ALLDEVICES,ALLTEMPS,ALLTESTS,TIchar33ACTable);

        else
          begin
START(RUN_SYNC,ALLDEVICES,ALLTEMPS,ALLTESTS,TIparametricACTable,TIcrystalACTable,TInomlooseACTable,TIstressminACTable,TIstressmaxACTable,TIlofrqminACTable,TIlofrqmaxACTable,TIlofrqlooseACTable,TIlofrqmin60ACTable,TIlofrqmax60ACTable,TIlofrqloose60ACTable,TIhifrqmin33ACTable,TIhifrqmax33ACTable,TIhifrqmin40ACTable,TIhifrqmax40ACTable,TIhifrqloose40ACTable,TIhifrqmin50ACTable,TIhifrqmax50ACTable,TIhifrqloose50ACTable,TIhifrqmin60ACTable,TIhifrqmax60ACTable,TIhifrqloose60ACTable,TIsearchACTable,TIsearch40ACTable,TIsearchlevelsACTable,TIsearchlevels40ACTable,TIcharACTable,TIchar40ACTable);

            EdgeSetDelayData    (CREQstrobeWF,Edge1,ChanFirst,
                            DriveOff,ThreshVITL,t[tref]+
                            t[tdH1HRQLt]+t[loosdelay]-t[tgb]-ctcf-7ns,0,
                            DriveOff,ThreshVITH,t[tref]+
                            t[true_tH1flo]-t[tsuCACK]+t[tdALRQHt]+
                            t[loosdelay]-t[tgb]-ctcf-7ns,0);
            EdgeSetDelayData    (CREQstrobeWF,Edge2,ChanFirst,
                            StrobeData,ThreshVITL,t[tref]+
                            t[tdH1HRQLt]+t[loosdelay]-t[tgb]-ctcf,0,
                            StrobeData,ThreshVITH,t[tref]+
                            t[true_tH1flo]-t[tsuCACK]+t[tdALRQHt]+
                            t[loosdelay]-t[tgb]-ctcf,0);
            EdgeSetDelayData    (CREQstrobeWF,Edge3,ChanFirst,
                            StrobeOff,ThreshVITL,t[tref]+
                            t[tdH1HRQLt]+t[loosdelay]-t[tgb]-ctcf+7ns,0,
                            StrobeOff,ThreshVITH,t[tref]+
                            t[true_tH1flo]-t[tsuCACK]+t[tdALRQHt]+
                            t[loosdelay]-t[tgb]-ctcf+7ns,0);
STOP(RUN_SYNC,ALLDEVICES,ALLTEMPS,ALLTESTS,TIparametricACTable,TIcrystalACTable,TInomlooseACTable,TIstressminACTable,TIstressmaxACTable,TIlofrqminACTable,TIlofrqmaxACTable,TIlofrqlooseACTable,TIlofrqmin60ACTable,TIlofrqmax60ACTable,TIlofrqloose60ACTable,TIhifrqmin33ACTable,TIhifrqmax33ACTable,TIhifrqmin40ACTable,TIhifrqmax40ACTable,TIhifrqloose40ACTable,TIhifrqmin50ACTable,TIhifrqmax50ACTable,TIhifrqloose50ACTable,TIhifrqmin60ACTable,TIhifrqmax60ACTable,TIhifrqloose60ACTable,TIsearchACTable,TIsearch40ACTable,TIsearchlevelsACTable,TIsearchlevels40ACTable,TIcharACTable,TIchar40ACTable);
         end;

        EdgeSetDelayData    (CREQ2strobeWF,Edge1,ChanFirst,
                            DriveOff,ThreshVITL,t[tref]+
                            t[true_tH1flo]+t[tsuCREQ]+t[tdRQHRQLt]+
                            t[loosdelay]-t[tgb]-ctcf-7ns,0,
                            DriveOff,ThreshVITH,t[tref]+
                            t[true_tH1flo]+t[tsuCREQ]+t[tdRQHRQOt]+
                            t[loosdelay]-t[tgb]-ctcf-7ns,0);
        EdgeSetDelayData    (CREQ2strobeWF,Edge2,ChanFirst,
                            StrobeData,ThreshVITL,t[tref]+
                            t[true_tH1flo]+t[tsuCREQ]+t[tdRQHRQLt]+
                            t[loosdelay]-t[tgb]-ctcf,0,
                            StrobeData,ThreshVITH,t[tref]+
                            t[true_tH1flo]+t[tsuCREQ]+t[tdRQHRQOt]+
                            t[loosdelay]-t[tgb]-ctcf,0);
        EdgeSetDelayData    (CREQ2strobeWF,Edge3,ChanFirst,
                            StrobeOff,ThreshVITL,t[tref]+
                            t[true_tH1flo]+t[tsuCREQ]+t[tdRQHRQLt]+
                            t[loosdelay]-t[tgb]-ctcf+7ns,0,
                            StrobeOff,ThreshVITH,t[tref]+
                            t[true_tH1flo]+t[tsuCREQ]+t[tdRQHRQOt]+
                            t[loosdelay]-t[tgb]-ctcf+7ns,0);

        EdgeSetDelayData    (CRDYstrobeWF,Edge1,ChanFirst,
                            DriveOff,ThreshVITL,t[true_tCSTRBfhi]-t[tCSTRBfhi]+
                            t[tCSTRBLO]+t[tdSLRLr]+t[loosdelay4]-t[tgb]-ctcf-7ns,0,
                            DriveOff,ThreshVITH,t[true_tCSTRBfhi]-t[tCSTRBfhi]+
                            t[tCSTRBHI]+t[tdSHRHr]+t[loosdelay]-t[tgb]-ctcf-7ns,0);
        EdgeSetDelayData    (CRDYstrobeWF,Edge2,ChanFirst,
                            StrobeData,ThreshVITL,t[true_tCSTRBfhi]-t[tCSTRBfhi]+
                            t[tCSTRBLO]+t[tdSLRLr]+t[loosdelay5]-t[tgb]-ctcf,0,
                            StrobeData,ThreshVITH,t[true_tCSTRBfhi]-t[tCSTRBfhi]+
                            t[tCSTRBHI]+t[tdSHRHr]+t[loosdelay]-t[tgb]-ctcf,0);
        EdgeSetDelayData    (CRDYstrobeWF,Edge3,ChanFirst,
                            StrobeOff,ThreshVITL,t[true_tCSTRBfhi]-t[tCSTRBfhi]+
                            t[tCSTRBLO]+t[tdSLRLr]+t[loosdelay5]-t[tgb]-ctcf+7ns,0,
                            StrobeOff,ThreshVITH,t[true_tCSTRBfhi]-t[tCSTRBfhi]+
                            t[tCSTRBHI]+t[tdSHRHr]+t[loosdelay]-t[tgb]-ctcf+6ns,0);

        EdgeSetDelayData    (CDdriveWF,Edge1,ChanFirst,
                            DriveComplement,ThreshVITL,t[true_tCSTRBfhi]-t[tCSTRBfhi]+
                            t[tCSTRBLO]-t[tsuCDr]-t[loossetup]+dtcf-7ns,0,
                            DriveComplement,ThreshVITH,t[true_tCSTRBfhi]-t[tCSTRBfhi]+
                            t[tCSTRBLO]-t[tsuCDr]-t[looscd]-t[loossetup]+dtcf-7ns,0);
        EdgeSetDelayData    (CDdriveWF,Edge2,ChanFirst,
                            DriveData,ThreshVITL,t[true_tCSTRBfhi]-t[tCSTRBfhi]+
                            t[tCSTRBLO]-t[tsuCDr]-t[loossetup]+dtcf,0,
                            DriveData,ThreshVITH,t[true_tCSTRBfhi]-t[tCSTRBfhi]+
                            t[tCSTRBLO]-t[tsuCDr]-t[looscd]-t[loossetup]+dtcf,0);
        EdgeSetDelayData    (CDdriveWF,Edge3,ChanFirst,
                            DriveComplement,ThreshVITL,
                            t[tref]+t[true_tCRDYflo]+t[thCDr]+t[looscd]+t[looshold]-dtcf,0,
                            DriveComplement,ThreshVITH,
                            t[tref]+t[true_tCRDYflo]+t[thCDr]+t[looshold]-dtcf,0);

STOP(RUN_SYNC,ALLDEVICES,ALLTEMPS,ALLTESTS,TIparametricACTable,TIcrystalACTable,TInomlooseACTable,TIstressminACTable,TIstressmaxACTable,TIlofrqminACTable,TIlofrqmaxACTable,TIlofrqlooseACTable,TIlofrqmin60ACTable,TIlofrqmax60ACTable,TIlofrqloose60ACTable,TIhifrqmin33ACTable,TIhifrqmax33ACTable,TIhifrqmin40ACTable,TIhifrqmax40ACTable,TIhifrqloose40ACTable,TIhifrqmin50ACTable,TIhifrqmax50ACTable,TIhifrqloose50ACTable,TIhifrqmin60ACTable,TIhifrqmax60ACTable,TIhifrqloose60ACTable,TIsearchACTable,TIsearch40ACTable,TIsearchlevelsACTable,TIsearchlevels40ACTable,TIcharACTable,TIchar33ACTable,TIchar40ACTable);
        end; (*1st case*)
      TIlofrqedgeACTable,
      TIlofrqedge60ACTable,
      TIhifrqedge40ACTable,
      TIhifrqedge50ACTable,
      TIhifrqedge60ACTable,
      TIspecsetupmin33ACTable,
      TIsearch33ACTable,
      TIsearchlevels33ACTable,
      TIspecholdmin33ACTable,
      TIspecsetupmax33ACTable,
      TIspecholdmax33ACTable,
      TIspecsetupmin25ACTable,
      TIspecholdmin25ACTable,
      TIspecsetupmax25ACTable,
      TIspecholdmax25ACTable:
        begin
START(RUN_SYNC,ALLDEVICES,ALLTEMPS,ALLTESTS,TIlofrqedgeACTable,TIlofrqedge60ACTable,TIhifrqedge40ACTable,TIhifrqedge50ACTable,TIhifrqedge60ACTable,TIspecsetupmin33ACTable,TIsearch33ACTable,TIsearchlevels33ACTable,TIspecholdmin33ACTable,TIspecsetupmax33ACTable,TIspecholdmax33ACTable,TIspecsetupmin25ACTable,TIspecholdmin25ACTable,TIspecsetupmax25ACTable,TIspecholdmax25ACTable);

        EdgeSetDelayData    (RESETdriveWF,Edge1,ChanFirst,
                            DriveData,ThreshVITL,
                            t[tref]+t[true_toffset]+t[twCIH]+t[twCIL]+
                            t[twCIH]-t[tsuRESET]-t[loossetup]+dtcf,0,
                            DriveData,ThreshVITH,
                            t[tref]+t[true_tH1flo]-t[tsuRESETH]-t[loossetup]+dtcf,0);

        EdgeSetDelayData    (CREQdriveWF,Edge1,ChanFirst,
                            DriveData,ThreshVITL,
                            t[tref]+t[true_tH1flo]-t[tsuCREQ],0,
                            DriveData,ThreshVITH,
                            t[tref]+t[true_tH1flo]+t[tsuCREQ],0);

        EdgeSetDelayData    (CREQstrobeWF,Edge1,ChanFirst,
                            DriveOff,ThreshVITL,t[tref]+
                            t[tdH1HRQLt]+t[loosdelay]-t[tgb]-ctcf-7ns,0,
                            DriveOff,ThreshVITH,t[tref]+
                            t[true_tH1flo]-t[tsuCACK]+t[tdALRQHt]+
                            t[loosdelay]-t[tgb]-ctcf-7ns,0);
        EdgeSetDelayData    (CREQstrobeWF,Edge2,ChanFirst,
                            EdgeStrobeData,ThreshVITL,t[tref]+
                            t[tdH1HRQLt]+t[loosdelay]-t[tgb]-ctcf,0,
                            EdgeStrobeData,ThreshVITH,t[tref]+
                            t[true_tH1flo]-t[tsuCACK]+t[tdALRQHt]+
                            t[loosdelay]-t[tgb]-ctcf,0);
        EdgeSetDelayData    (CREQstrobeWF,Edge3,ChanFirst,
                            StrobeLatch,ThreshVITL,t[tref]+
                            t[tdH1HRQLt]+t[loosdelay]-t[tgb]-ctcf+7ns,0,
                            StrobeLatch,ThreshVITH,t[tref]+
                            t[true_tH1flo]-t[tsuCACK]+t[tdALRQHt]+
                            t[loosdelay]-t[tgb]-ctcf+7ns,0);

        EdgeSetDelayData    (CREQ2strobeWF,Edge1,ChanFirst,
                            DriveOff,ThreshVITL,t[tref]+
                            t[true_tH1flo]+t[tsuCREQ]+t[tdRQHRQLt]+
                            t[loosdelay]-t[tgb]-ctcf-7ns,0,
                            DriveOff,ThreshVITH,t[tref]+
                            t[true_tH1flo]+t[tsuCREQ]+t[tdRQHRQOt]+
                            t[loosdelay]-t[tgb]-ctcf-7ns,0);
        EdgeSetDelayData    (CREQ2strobeWF,Edge2,ChanFirst,
                            EdgeStrobeData,ThreshVITL,t[tref]+
                            t[true_tH1flo]+t[tsuCREQ]+t[tdRQHRQLt]+
                            t[loosdelay]-t[tgb]-ctcf,0,
                            EdgeStrobeData,ThreshVITH,t[tref]+
                            t[true_tH1flo]+t[tsuCREQ]+t[tdRQHRQOt]+
                            t[loosdelay]-t[tgb]-ctcf,0);
        EdgeSetDelayData    (CREQ2strobeWF,Edge3,ChanFirst,
                            StrobeLatch,ThreshVITL,t[tref]+
                            t[true_tH1flo]+t[tsuCREQ]+t[tdRQHRQLt]+
                            t[loosdelay]-t[tgb]-ctcf+7ns,0,
                            StrobeLatch,ThreshVITH,t[tref]+
                            t[true_tH1flo]+t[tsuCREQ]+t[tdRQHRQOt]+
                            t[loosdelay]-t[tgb]-ctcf+7ns,0);

        EdgeSetDelayData    (CRDYstrobeWF,Edge1,ChanFirst,
                            DriveOff,ThreshVITL,t[true_tCSTRBfhi]-t[tCSTRBfhi]+
                            t[tCSTRBLO]+t[tdSLRLr]+t[loosdelay4]-t[tgb]-ctcf-7ns,0,
                            DriveOff,ThreshVITH,t[true_tCSTRBfhi]-t[tCSTRBfhi]+
                            t[tCSTRBHI]+t[tdSHRHr]+t[loosdelay]-t[tgb]-ctcf-7ns,0);
        EdgeSetDelayData    (CRDYstrobeWF,Edge2,ChanFirst,
                            EdgeStrobeData,ThreshVITL,t[true_tCSTRBfhi]-t[tCSTRBfhi]+
                            t[tCSTRBLO]+t[tdSLRLr]+t[loosdelay4]-t[tgb]-ctcf,0,
                            EdgeStrobeData,ThreshVITH,t[true_tCSTRBfhi]-t[tCSTRBfhi]+
                            t[tCSTRBHI]+t[tdSHRHr]+t[loosdelay]-t[tgb]-ctcf,0);
        EdgeSetDelayData    (CRDYstrobeWF,Edge3,ChanFirst,
                            StrobeLatch,ThreshVITL,t[true_tCSTRBfhi]-t[tCSTRBfhi]+
                            t[tCSTRBLO]+t[tdSLRLr]+t[loosdelay4]-t[tgb]-ctcf+7ns,0,
                            StrobeLatch,ThreshVITH,t[true_tCSTRBfhi]-t[tCSTRBfhi]+
                            t[tCSTRBHI]+t[tdSHRHr]+t[loosdelay]-t[tgb]-ctcf+7ns,0);

        EdgeSetDelayData    (CDdriveWF,Edge1,ChanFirst,
                            DriveComplement,ThreshVITL,t[true_tCSTRBfhi]-t[tCSTRBfhi]+
                            t[tCSTRBLO]-t[tsuCDr]-t[loossetup]+dtcf-7ns,0,
                            DriveComplement,ThreshVITH,t[true_tCSTRBfhi]-t[tCSTRBfhi]+
                            t[tCSTRBLO]-t[tsuCDr]-t[looscd]-t[loossetup]+dtcf-7ns,0);
        EdgeSetDelayData    (CDdriveWF,Edge2,ChanFirst,
                            DriveData,ThreshVITL,t[true_tCSTRBfhi]-t[tCSTRBfhi]+
                            t[tCSTRBLO]-t[tsuCDr]-t[loossetup]+dtcf,0,
                            DriveData,ThreshVITH,t[true_tCSTRBfhi]-t[tCSTRBfhi]+
                            t[tCSTRBLO]-t[tsuCDr]-t[looscd]-t[loossetup]+dtcf,0);
        EdgeSetDelayData    (CDdriveWF,Edge3,ChanFirst,
                            DriveComplement,ThreshVITL,
                            t[tref]+t[true_tCRDYflo]+t[thCDr]+t[looscd]+t[looshold]-dtcf,0,
                            DriveComplement,ThreshVITH,
                            t[tref]+t[true_tCRDYflo]+t[thCDr]+t[looshold]-dtcf,0);

STOP(RUN_SYNC,ALLDEVICES,ALLTEMPS,ALLTESTS,TIlofrqedgeACTable,TIlofrqedge60ACTable,TIhifrqedge40ACTable,TIhifrqedge50ACTable,TIhifrqedge60ACTable,TIspecsetupmin33ACTable,TIsearch33ACTable,TIsearchlevels33ACTable,TIspecholdmin33ACTable,TIspecsetupmax33ACTable,TIspecholdmax33ACTable,TIspecsetupmin25ACTable,TIspecholdmin25ACTable,TIspecsetupmax25ACTable,TIspecholdmax25ACTable);
        end; (*2nd case*)
    end; (*case*)

    end; (* with *)

end; (* RstCustomWF *)









procedure SccsIdentificationactable;
  var
    SccsId	:   String;
 begin
    SccsId:= '@(#) actable.p 1.7 9/18/93 10:08:05 c TI';
  end;  

(******************************************************************************
			SCCS	INFO

	MODULE		: actable.p
	VERSION NO.	: 1.7
	FILE CREATED	: 9/18/93 10:08:05
	PREVIOUS DELTA  : 9/18/93 10:08:02
	SCCS FILE	: /tmp_mnt/dsp2/hphu/c40/pgm/SCCS/s.actable.p 
	Copyright	: Texas Instruments, Inc.

******************************************************************************)
(***********************************************************************)
(***                                                                 ***)
(***                      SMJ320C40 TEST PROGRAM                     ***)
(***                      ----------------------                     ***)
(***                                                                 ***)
(***  File Name: actable.p                                           ***)
(***  Current Revision: N08                                          ***)
(***                                                                 ***)
(***  Revision History:                                              ***)
(***                                                                 ***)
(***   00  11/27/91  Program generation.                             ***)
(***   01  12/04/91  Converted CDdriveWF to a custom waveform which  ***)
(***                 tests '0' data using spec set-up/loose hold and ***)
(***                 tests '1' data using loose set-up/spec hold due ***)
(***                 to a megaone edge rule violation (6ns minimum). ***)
(***                 This configuration used for spec timings only.  ***)
(***   02  12/12/91  Added more high frequency test capability       ***)
(***   03  02/26/92  Added new clocking drive waveform for TCK pin   ***)
(***                 and new SBC type waveform for the TDI/TMS pins  ***)
(***                 (used for jtag/emulation type testcases)        ***)
(***   04  03/05/92  Changed STATstrobeWF and LOCKstrobeWF back to   ***)
(***                 their orig waveforms for pg2 prelim data sheet  ***)
(***   05  03/25/92  Added JTAGH1strobeWF (edge strobe) for H1/H3    ***)
(***                 to be used during jtag testing which has same   ***)
(***                 timing as TDOstrobeWF (avoids a runtime error)  ***)
(***   06  03/30/92  Added a StrobeOff edge between the drive off    ***)
(***                 and strobe data edges of DBUSstrobeWF so that   ***)
(***                 these data lines can be vtscoped using wavetool ***)
(***   07  04/14/92  Updated waveforms to reflect the 'tmp' data     ***)
(***                 sheet                                           ***)
(***   08  06/11/92  Modified EMUstrobeWF to more realistically test ***)
(***                 and added JTAGABUSstrobeWF used in JTAGEXTE gct ***)
(***   09  09/03/92  Added 50mhz test capability to the program      ***)
(***   10  09/16/92  Added 'tgb' timing g/b to all output waveforms  ***)
(***                 which tightens all strobe edges in conjunction  ***)
(***                 with a vol level relaxation based on rise/fall  ***)
(***                 time char data (affects spec timing tests only) ***)
(***                 Note: this change was required to test around   ***)
(***                 ----  the vol glitches on several output pins   ***)
(***   11  10/21/92  Changed t[loosclock] from 5ns to 8ns for TMP    ***)
(***                 testing (note:  all H1/H3 clock timings are     ***)
(***                 tested to spec during the sync-up routine)      ***)
(***   12  10/21/92  Added new loose timing guardbands for TMP       ***)
(***                 testing (affects spec levels portion of test),  ***)
(***                 Following strobe waveforms have been modified:  ***)
(***                   ABUSV/ABUS/STRB/STAT/DBUS/DBUSWW/CACK/CSTRB   ***)
(***   13  10/22/92  Re-configured the actables for lofrqloose,      ***)
(***                 hifrqloose40, hifrqloose50, and hifrqloose60    ***)
(***                 to include a combination of both window strobes ***)
(***                 and edge strobes in order to test spec levels   ***)
(***                 for the EXPORTRDYPattern (required for TMP),    ***)
(***                 In conjunction, added JTAGVARYstrobeWF to be    ***)
(***                 used in the JTAGEXTE gct (can be either window  ***)
(***                 or edge strobe depending on the actable used)   ***)
(***   14  10/22/92  Added searchlevels and searchlevels40 actables  ***)
(***                 due to changes required for EXPORTRDYPattern    ***)
(***   15  10/23/92  Modified some loose timing guardbands for TMP   ***)
(***                 testing (affects spec levels portion of test),  ***)
(***                 Following strobe waveforms have been modified:  ***)
(***                   STRB/LOCK/DBUSVAL                             ***)
(***   16  10/28/92  Modified some loose timing guardbands for TMP   ***)
(***                 testing (affects spec levels portion of test),  ***)
(***                 Following strobe waveforms have been modified:  ***)
(***                   STRB/RW/STAT/IACK/CSTRB                       ***)
(***   17  10/30/92  Modified some loose timing guardbands for TMP   ***)
(***                 testing (affects spec levels portion of test),  ***)
(***                 Following strobe waveforms have been modified:  ***)
(***                   RW/IACK/CRDY                                  ***)
(***   18  11/13/92  Modified some loose timing guardbands for TMP   ***)
(***                 testing (affects spec levels portion of test),  ***)
(***                 Following strobe waveforms have been modified:  ***)
(***                   TCLK                                          ***)
(***   19  12/02/92  Updated CDdriveWF to reflect the 'tmp' data     ***)
(***                 sheet (no timings were affected)                ***)
(***   20  01/28/93  Changed IIOFstrobeoffWF to for hifrqloose40 to  ***)
(***                 pass 40ns loose timings.  Changed by -1ns.      ***)
(***   21  02/16/93  Modified some loose timing guardbands. Following***)
(***                 strobe waveforms have been modified: CRDY (Edge2***)
(***                 and 3 for 0 data) and DBUSVAL.                  ***) 
(***   22  03/29/93  Added new loose timing guardbands for TMS       ***)
(***                 testing (affects spec levels portion of test),  ***)
(***                 Following strobe waveforms have been modified:  ***)
(***                   ABUS/DBUSVAL/TCLK/DBUS/LOCK/CSTRB/IIOFFWW     ***)
(***   23  05/10/93  Added new loose timing guardbands for TMS test  ***)
(***                 (affects spec levels portion of test).  The     ***)
(***                 follwing strobe waveforms have been modified:   ***)
(***                   ABUS.                                         ***)
(***   24  06/12/93  Changed loosabus from 2ns to 8ns for loose      ***)
(***                 timing corners to fix ABUS problem.             ***) 
(***                                                                 ***)
(***   25  08/06/93  Changed loose guardbands for low frequency      ***)
(***	    PHQ	     levels test.  				     ***)
(***	      	     Changed loose guardband variable for 	     ***)
(*** 		     DBUSWWstrobeWF, CRDYstrobeWF from "loosedelay5" ***)
(***		     to "sp"  when doing levels test.  Changed loose ***)
(***		     guardband variable for CACKstrobeWF, 	     ***)
(***		     ABUSVALstrobe from "loosedelay7" to "sp" when do***)
(***	 	     levels test.  Put in temporarily workaround for ***)
(***		     IIOFstrobeoffWF, CSTRBstrobeWF when schmoo      ***)
(***		     at sub40ns speed.  Added TIlofrqxxx60ACTable    ***)
(***		     to guardband case statement.  Added  	     ***)
(***		     TIlofrqxxx60ACTable  to waveform definition     ***)
(***		     case statement.  Added creation of 	     ***)
(***		     TIlofrqxxx60ACTable.			     ***)
(***   26  08/12/93  Added DBUSWW2strobeWF definition - this is used ***)
(***	    PHQ	     to test around LDBUS glitch problem during      ***)
(***		     levels test.  When 31 GABUS lines switch from   ***)
(***		     all Fs to 0s, there are ground glitches on LDBUS***)
(***		     causing test to fail.  Since these glitches     ***)
(***		     occur in the middle of write cycle and ContWF   ***)
(***		     is assigned to LDBUS, moving strobe will not    ***)
(***		     solve the problem.  Since these glitches are    ***)
(***		     outside of memory interface critical window, we ***)
(***		     can still satisfy mem interface timing by       ***)
(***		     guarantee solid level on LDBUS by sometime      ***) 
(***		     (10ns - will be plenty) before STRB             ***)
(***		     goes inactive.  This waveform is designed to    ***)
(***		     guarantee just that - actually it is ref of H1  ***)
(***		     fall so it is tighter than STRB ref.            ***)
(***		     Changed loose gb back to loosdelay5 (DBUSWWstb) ***)
(***		     when do levels test to avoid EdgeRule violation.***)
(***   27   08/13/93 Modified TInomlooseACTable to have the same     ***)
(***		     loose gb as hifrqloose50/60 table.  TInomloose  ***)
(***		     (100ns) will be the highest frq for levels test.***)
(***		     Fixed ABUSstrobeWF for TIhifrqloose40ACTable.   ***)
(***		     Was strobe at rise/fall transition.	     ***)
(***   28   08/17/93 Modified nomloose to have to same gb as         ***)
(***		     lofrqloose.			             ***)
(***   29   09/21/93 Modified the following waveforms at 40ns loose  ***)
(***                 corners due to timing edge violations: ABUS, CD ***)
(***                 ,DBUS, DBUSWW2, STRB.  All these were strobeWFs ***)
(***                 that violated megaone rules.                    ***)
(***   30   09/29/93 Separated all 40ns tables.  This will help for  ***)
(***                 elimination of edge violations and to allow for ***)
(***                 more control over 40ns timings.                 ***)
(***   31   12/11/93 Modified StrobeOff edge of ABUSWWstrobeWF, move ***)
(***                 back by 4ns, to avoid rise/fall transition at   ***)
(***                 40ns period. ADDRGLPattern exec = 76,           ***)
(***                 EXPORTRDYPattern  exec 86.                      ***)
(***                 Modified StrobeOff edge of TCLKstrobeWF ,move   ***)
(***                 back by 7ns, to avoid SBC confict at exec 3811  ***)
(***                 TIMER1Pattern. Modified this by another 2ns to  ***)
(***                 make -9ns at 90c.                               ***)
(***                 Moved CSTRBstrobe strobeoff edge3 by -1ns to    ***) 
(***                 avoid catching rising edge of next signal.      ***)
(***   32   01/07/94 Changed ABUSWWstrobeWF by removing the 4ns      ***)
(***          BB     offset needed for 50mhz debug.  Now timing tests***)
(***                 correct spec.                                   ***)  
(***   33   05/24/94 Added TIstressminACTable and TIstressmaxACTable ***)
(***          BB     to lists in same setups as nomloose.            ***)
(***   34   06/30/94 Changed IIOFstrobeoffWF to use thH1LIFOI timing ***)
(***          BB     instead of tvH1LIF since the spec is really a   ***)
(***                 disable time and strobe should be turned off    ***)
(***                 at H1 falling.                                  ***)
(***   35   11/10/94 Changed JTAGABUSstrobe and JTAGVARYstrobe to    ***)
(***          BB     strobe data after TCK rising edge.  A half cycle***)
(***                 was added to the timings - t[tcCI].  TCK rising ***)
(***                 edge is used for all timings except TDOstrobe.  ***) 
(***   36   01/26/95 Changed loosclock from 14ns to 5ns for all 33ns ***)
(***          BB     corners.                                        ***)
(***   37   03/14/95 Changed ABUSSWWstrobeWF edge1 (StrobeOff) to    ***)
(***                 turn off previous strobe 1ns earlier due to 25c ***)
(***                 fail for C42.  Only changed for C42 device at   ***)
(***                 hifrqmin40, hifrqmax40.                         ***)
(***   38   04/27/95 Fixed JTAGABUSstrobe to have a DriveOff edge    ***)
(***           BB    as this waveform is used on IO pins.            ***)
(***   39   05/10/95 Changed loosedelay values on ABUSstrobeWF and   ***)
(***           BB    TDOstrobeWF for TIchar40ACTable to help char    ***)
(***                 program.  Changed TDOstrobeWF at hifrqloose40   ***)
(***                 loosdelay to the same change as char40 to avoid ***)
(***                 fail at this corner due large loose variable.   ***)
(***   40   05/10/95 Changed loosdelays for searchlevels33 table in  ***)
(***           BB    order to help 60mhz schmoos.                    ***)
(*** 320C40B4:                                                       ***)
(***   41   07/25/95 Added H1IDLEstrobeWF and H3IDLEstrobeWF to test ***)
(***           BB    H1 and H3 during the POWERDOWNPattern.  The     ***)
(***                 waveforms strobe during the other half of the   ***)
(***                 cycle to insure that H1 stays high and H3 stays ***)
(***                 low.  The normal wf's do not confirm this.      ***)
(***   42   07/25/95 Created new waveform INTIDLEdriveWF for use in  ***)
(***           BB    waking up device from IDLE2 mode in POWERDOWN   ***)
(***                 pattern.  This waveform uses new tsuINTIDLE     ***)
(***                 timing as needed to wake clocks in correct phase.**)
(*** 320C40N00:                                                      ***)
(***   00  12/12/95  Created new military SMJ320C40 50MHz test       ***)
(***          RA     program based on the commercial B4 test program.***)
(*** 320C40N01:                                                      ***)
(***   01   01/24/95 Added new 60mhz ACTables - TIhifrqmin33ACTable  ***)
(***           RA    and TIhifrqmax33ACTable.                        ***)
(***                 Made characterization specific changes for 60mhz***)
(***                 tables only.                                    ***)
(*** 320C40N02:							     ***)
(***   02            Edgestrobe-2 of ABUSWWstrobeWF in               ***)
(***                 TInomlooseACTable moved due to levels problem.  ***)
(*** 320C40N03:      Followed Commercials' StrobeData edge change    ***)
(***       07/18/96  from 'EdgeSet' to 'EdgeSetDelayData' in order   ***)
(***                 to remove the VOH strobe guardband (t[tgb])     ***)
(***                 from the calculation.  The following waveforms  ***)
(***                 have been changed:                              ***)
(***                   STRBstrobeWF, DBUSstrobeWF, DBUSWWstrobeWF,   ***)
(***                   IIOFstrobeWF, IIOFWWstrobeWF,STATstrobeWF,    ***)
(***                   ABUSstrobeWF.  Major                          ***)
(***                                                                 ***)      
(*** 320C40N04:      We decided to remove the 1v/1ns offset for the  ***)
(***       08/01/96  IIOFWWstrobeWF by removing the t[tgb] guard band***)
(***                 for the 40/50/60MHz tests. The use of the       ***)
(***                 EdgeSetDelayData for this waveform was also     ***)
(***                 discontinued.                                   ***)
(***                                                                 ***)
(*** FORMAT:  WHO   MM/DD/YY     COMMENTS AND DETAILED DESCRIPTION   ***)
(***          REV & TYPE: Major/Minor                                ***)
(***  RR  01/05/00   SccsIdentificationactable was inadvertently     ***)
(***  N05 Major      commented out. Removed comments and setup       ***)
(***                 WaveForms for 33ns (60mhz) char ACTable.        ***)
(***  EGM 05/10/00   Removed tgb g/b in Edge1 in IIOFWWstrobeWF for  ***)
(***  N06 Major      TIlofrqmin/maxACTable and added thIF(min) spec  ***)
(***                 here, too.                                      ***)
(***  N07 Major      TIlofrqmin/maxACTable and added thIF(min) spec  ***)
(***                 here, too.                                      ***)
(***  EGM 08/22/00   Added -2ns to CSTRBdriveWF & +2ns to CRDYdriveWF***)
(***  N08 Major      at edge2 for TInomlooseACTable & TIlofrqlooseAC-***)
(***                 Table to reduce noise in CACKX_ (especially     ***)
(***                 CACK5_) and C4DX outputs, respectively, for     ***)
(***                 TM/SM320C40TAB_pg5x devices only.               ***)
(***********************************************************************)


	(***********************************************************)
	(***                 AC Table Definition                 ***)
	(***********************************************************)
	(***                                                     ***)
	(*** The AC Table Definition is the section of the       ***)
	(*** program in which all waveforms necessary for the    ***)
	(*** test are created. These waveforms may be assigned   ***)
	(*** to any Pin List in the CycleTableSet procedure.     ***)
	(*** The AC Table Definition also includes the           ***)
	(*** implementation of all timing correction factors.    ***)
	(*** The ACTableSet procedure will accept a single       ***)
	(*** parameter of type ACTable. This will be the name of ***)
	(*** the AC Table.                                       ***)
	(***                                                     ***)
	(*** In order to assure that the test engineering        ***)
	(*** standard procedures will work with a program, the   ***)
	(*** ACTableSet procedure should include one list of     ***)
	(*** waveforms with frequency dependency built in. Most  ***)
	(*** of the frequency dependencies should be comprehended***)
	(*** in the AC Data Sheet. It is also recommended that   ***)
	(*** the capability to change tester period on-the-fly   ***)
	(*** be avoided, as it precludes the tester from moving  ***)
	(*** timing edges across period boundaries automatically.***)
	(*** If the PeriodSetAll command is used to set all      ***)
	(*** periods in an AC Table to the same value, the tester***)
	(*** will automatically delay edges into subsequent      ***)
	(*** periods, carrying the original data with the edge.  ***)
	(*** WaveSetDelay statements are not necessary.          ***)
	(***                                                     ***)
	(***********************************************************)

procedure ACTableSet;(* actable : ACTable *)

	(***********************************************************)
	(***           Internal Procedure TIACTableSet           ***)
	(***********************************************************)
	(***                                                     ***)
	(*** This internal procedure is called by the procedure  ***)
	(*** ACTableSet, and is the portion of this module that  ***)
	(*** sets up the ACTables. The purpose of creating the   ***)
	(*** TIACTableSet procedure is to allow the ACTableSet   ***)
	(*** procedure to set up the waveforms for all test      ***)
	(*** tables in a single call using the special parameter ***)
	(*** TIallACTable.                                       ***)
	(***                                                     ***)
	(***********************************************************)

 procedure TIACTableSet( actable : ACTable );

  begin

	(***********************************************************)
	(***                                                     ***)
	(*** The ac correction factors as defined by test        ***)
	(*** engineering are defined here. dtcf and ctcf are     ***)
	(*** declared as global variables, and are available     ***)
	(*** to the user through Interactive Pascal. These       ***)
	(*** correction factors are tester dependent, and may    ***)
	(*** not be altered by the programmer.                   ***)
	(***                                                     ***)
	(*** Guardbands as required on a device by device basis  ***)
	(*** should also be declared and implemented in this     ***)
	(*** section. The guardbands used must be thoroughly     ***)
	(*** documented with explanations. Guardbands will       ***)
	(*** differ in probe, final test, and QA programs.       ***)
	(*** In order to assure that a single AC Data Sheet      ***)
	(*** will support the requirement, guardbands must be    ***)
	(*** implemented in a manner similar to the correction   ***)
	(*** factors. Declare variables (they may be global or   ***)
	(*** local) for your guardbands. Set the variable to     ***)
	(*** the correct guardband value in the sections below   ***)
	(*** for probe, final, and QA. Then, add or subtract     ***)
	(*** the guardband variable in the correct expressions   ***)
	(*** in the declaration section below.                   ***)
	(***                                                     ***)
	(***********************************************************)

    case TITestType of
      Probe:
        begin
START(ALLTEMPS,ALLDEVICES,ALLTABLES,ALLTESTS-Final);
          dtcf :=   0ps; (* Drive   timing correction factor from mega1 spec *)
          ctcf :=   0ps; (* Compare timing correction factor from mega1 spec *)
STOP(ALLTEMPS,ALLDEVICES,ALLTABLES,ALLTESTS-Final);
        end;
      Final:
        begin
START(ALLTEMPS,ALLDEVICES,ALLTABLES,Final);
          dtcf := 300ps; (* Drive   timing correction factor from mega1 spec *)
          ctcf := 400ps; (* Compare timing correction factor from mega1 spec *)
STOP(ALLTEMPS,ALLDEVICES,ALLTABLES,Final);
        end;
      QA:
{ APS comment these out since we can cover them above...
        begin
          dtcf :=   0ps; (* Drive   timing correction factor from mega1 spec *)
          ctcf :=   0ps; (* Compare timing correction factor from mega1 spec *)
        end;
      others:
        begin
          dtcf :=   0ps; (* Drive   timing correction factor from mega1 spec *)
          ctcf :=   0ps; (* Compare timing correction factor from mega1 spec *)
        end;
}    end; (*case*)

	(***********************************************************)
	(***                                                     ***)
	(*** Loose timings as required on a device by device     ***)
	(*** basis are set up and implemented in this section.   ***)
	(*** Loose timings declared here should be relaxations on***)
	(*** parameters known to be sensitive on the device.     ***)
	(*** Loose timing parameters will be added/subtracted    ***)
	(*** from parameters only for Levels tests. Spec timings ***)
	(*** will be used for Timing tests.                      ***)
	(*** In order to assure that a single AC Data Sheet      ***)
	(*** will support the requirement, loose timings must be ***)
	(*** implemented in a manner similar to the correction   ***)
	(*** factors. Declare variables (they may be global or   ***)
	(*** local) for your guardbands. Set the variable to     ***)
	(*** the correct guardband value in the sections below   ***)
	(*** for loose timing ACTables and spec timing ACTables. ***)
	(*** Then add or subtract the loose timing variable to   ***)
	(*** parameters as necessary.                            ***)
	(***                                                     ***)
	(***********************************************************)

    with ACDataSheets[ actable ] do
      begin

        t[restrict]   := 14ns; (* min time req'd from stboff to next stbon *)
	case actable of        (* set loosclock to smaller value for schmoo *)
          TIspecsetupmin33ACTable,
          TIspecsetupmax33ACTable,
          TIspecholdmin33ACTable,
          TIspecholdmax33ACTable,
	  TIsearch33ACTable,
	  TIsearchlevels33ACTable,
          TIhifrqmin33ACTable,
          TIhifrqmax33ACTable:
		begin
START(ALLENUMS,TIspecsetupmin33ACTable,TIspecsetupmax33ACTable,TIspecholdmin33ACTable,TIspecholdmax33ACTable,TIsearch33ACTable,TIsearchlevels33ACTable,TIhifrqmin33ACTable,TIhifrqmax33ACTable);
		  t[loosclock] := 5ns;
STOP(ALLENUMS,TIspecsetupmin33ACTable,TIspecsetupmax33ACTable,TIspecholdmin33ACTable,TIspecholdmax33ACTable,TIsearch33ACTable,TIsearchlevels33ACTable,TIhifrqmin33ACTable,TIhifrqmax33ACTable);
		end;
	  others:
START(ALLENUMS,ALLTABLES-TIspecsetupmin33ACTable-TIspecsetupmax33ACTable-TIspecholdmin33ACTable-TIspecholdmax33ACTable-TIsearch33ACTable-TIsearchlevels33ACTable-TIhifrqmin33ACTable-TIhifrqmax33ACTable);
		begin
		  t[loosclock] := 14ns;
STOP(ALLENUMS,ALLTABLES-TIspecsetupmin33ACTable-TIspecsetupmax33ACTable-TIspecholdmin33ACTable-TIspecholdmax33ACTable-TIsearch33ACTable-TIsearchlevels33ACTable-TIhifrqmin33ACTable-TIhifrqmax33ACTable);
		end;
	end; (* case *)

        case actable of
          TIlofrqminACTable,
          TIlofrqmaxACTable,
          TIlofrqedgeACTable,
          TIlofrqmin60ACTable,
          TIlofrqmax60ACTable,
          TIlofrqedge60ACTable,
          TIspecsetupmin25ACTable,
          TIspecsetupmax25ACTable,
          TIspecholdmin25ACTable,
          TIspecholdmax25ACTable,
          TIspecsetupmin33ACTable,
          TIspecsetupmax33ACTable,
          TIspecholdmin33ACTable,
          TIspecholdmax33ACTable,
          TIhifrqmin33ACTable,
          TIhifrqmax33ACTable,
          TIhifrqmin40ACTable,
          TIhifrqmax40ACTable,
          TIhifrqedge40ACTable,
          TIhifrqmin50ACTable,
          TIhifrqmax50ACTable,
          TIhifrqedge50ACTable,
          TIhifrqmin60ACTable,
          TIhifrqmax60ACTable,
          TIhifrqedge60ACTable:
            begin
START(ALLENUMS,TIlofrqminACTable,TIlofrqmaxACTable,TIlofrqedgeACTable,TIlofrqmin60ACTable,TIlofrqmax60ACTable,TIlofrqedge60ACTable,TIspecsetupmin25ACTable,TIspecsetupmax25ACTable,TIspecholdmin25ACTable,TIspecholdmax25ACTable,TIspecsetupmin33ACTable,TIspecsetupmax33ACTable,TIspecholdmin33ACTable,TIspecholdmax33ACTable,TIhifrqmin33ACTable,TIhifrqmax33ACTable,TIhifrqmin40ACTable,TIhifrqmax40ACTable,TIhifrqedge40ACTable,TIhifrqmin50ACTable,TIhifrqmax50ACTable,TIhifrqedge50ACTable,TIhifrqmin60ACTable,TIhifrqmax60ACTable,TIhifrqedge60ACTable);
              t[loossetup]  := 0ns; (* loose timing g/b,setup    timings *)
              t[looshold]   := 0ns; (* loose timing g/b,hold     timings *)
              t[loosdelay]  := 0ns; (* loose timing g/b,delay    timings *)
              t[loosdelay4] := 0ns; (* loose timing g/b,delay    timings *)
              t[loosdelay5] := 0ns; (* loose timing g/b,delay    timings *)
              t[loosdelay6] := 0ns; (* loose timing g/b,delay    timings *)
              t[loosdelay7] := 0ns; (* loose timing g/b,delay    timings *)
              t[loosabus]   := 0ns; (* loose timing g/b,abusWW   timings *)
              t[looscd]     := 3ns; (* loose timing g/b,CD drive timings *)
              t[tgb]        := 1ns; (* spec  timing g/b,all      timings *)
	      sp	    := 0ns;
STOP(ALLENUMS,TIlofrqminACTable,TIlofrqmaxACTable,TIlofrqedgeACTable,TIlofrqmin60ACTable,TIlofrqmax60ACTable,TIlofrqedge60ACTable,TIspecsetupmin25ACTable,TIspecsetupmax25ACTable,TIspecholdmin25ACTable,TIspecholdmax25ACTable,TIspecsetupmin33ACTable,TIspecsetupmax33ACTable,TIspecholdmin33ACTable,TIspecholdmax33ACTable,TIhifrqmin33ACTable,TIhifrqmax33ACTable,TIhifrqmin40ACTable,TIhifrqmax40ACTable,TIhifrqedge40ACTable,TIhifrqmin50ACTable,TIhifrqmax50ACTable,TIhifrqedge50ACTable,TIhifrqmin60ACTable,TIhifrqmax60ACTable,TIhifrqedge60ACTable);            end;

(*    	t[loosabus] is changed from 15ns to 0ns for TInomlooseACTable and  *)
(*	SM320C40TAB_pg5x_60MHz	TIDeviceType 				   *)
	  
	   TInomlooseACTable,
           TIlofrqlooseACTable:
            begin
START(ALLENUMS,TInomlooseACTable,TIlofrqlooseACTable);
              t[loossetup]  := 7ns;
              t[looshold]   := 10ns;
              t[loosdelay]  := 10ns;
              t[loosdelay4] := 11ns;
              t[loosdelay5] := 12ns;
              t[loosdelay6] := 13ns;
              t[loosdelay7] := 14ns;
              t[loosabus]   := 0ns;
              t[looscd]     := 0ns;
              t[tgb]        := 0ns;
	      sp	    := 15ns;
STOP(ALLENUMS,TInomlooseACTable,TIlofrqlooseACTable);
	    end;

 	  TIstressminACTable,
          TIstressmaxACTable,
          TIlofrqloose60ACTable:
            begin
START(ALLENUMS,TIstressminACTable,TIstressmaxACTable,TIlofrqloose60ACTable);
              t[loossetup]  := 7ns;
              t[looshold]   := 10ns;
              t[loosdelay]  := 10ns;
              t[loosdelay4] := 11ns;
              t[loosdelay5] := 12ns;
              t[loosdelay6] := 13ns;
              t[loosdelay7] := 14ns;
              t[loosabus]   := 15ns;
              t[looscd]     := 0ns;
              t[tgb]        := 0ns;
	      sp	    := 15ns;
STOP(ALLENUMS,TIstressminACTable,TIstressmaxACTable,TIlofrqloose60ACTable);
	    end;
	  

	  TIhifrqloose60ACTable,
	  TIhifrqloose50ACTable:
	    begin
START(ALLENUMS,TIhifrqloose60ACTable,TIhifrqloose50ACTable);
              t[loossetup]  := 3ns;
              t[looshold]   := 3ns;
              t[loosdelay]  := 3ns;
              t[loosdelay4] := 4ns;
              t[loosdelay5] := 5ns;
              t[loosdelay6] := 6ns;
              t[loosdelay7] := 7ns;
              t[loosabus]   := 8ns;
              t[looscd]     := 0ns;
              t[tgb]        := 0ns;
	      sp	    := 10ns;
STOP(ALLENUMS,TIhifrqloose60ACTable,TIhifrqloose50ACTable);
	end;

          TIsearchACTable,
          TIsearch40ACTable,
          TIsearchlevelsACTable,
          TIsearchlevels40ACTable:
            begin
START(ALLTEMPS,ALLDEVICES,ALLTESTS,schmooloos,TIsearchACTable,TIsearch40ACTable,TIsearchlevelsACTable,TIsearchlevels40ACTable);
              if (schmooloos) then
                begin
                  t[loossetup]  := 3ns;
                  t[looshold]   := 3ns;
                  t[loosdelay]  := 3ns;
                  t[loosdelay4] := 4ns;
                  t[loosdelay5] := 5ns;
                  t[loosdelay6] := 6ns;
                  t[loosdelay7] := 7ns;
                  t[loosabus]   := 2ns;
                  t[looscd]     := 0ns;
                  t[tgb]        := 0ns;
                  sp	        := 0ns;
STOP(ALLTEMPS,ALLDEVICES,ALLTESTS,schmooloos,TIsearchACTable,TIsearch40ACTable,TIsearchlevelsACTable,TIsearchlevels40ACTable);
                end
              else
                begin
START(ALLTEMPS,ALLDEVICES,ALLTESTS,NOschmooloos,TIsearchACTable,TIsearch40ACTable,TIsearchlevelsACTable,TIsearchlevels40ACTable);
                  t[loossetup]  := 0ns;
                  t[looshold]   := 0ns;
                  t[loosdelay]  := 0ns;
                  t[loosdelay4] := 0ns;
                  t[loosdelay5] := 0ns;
                  t[loosdelay6] := 0ns;
                  t[loosdelay7] := 0ns;
                  t[loosabus]   := 0ns;
                  t[looscd]     := 3ns;
                  t[tgb]        := 1ns;
	 	  sp		:= 0ns;
STOP(ALLTEMPS,ALLDEVICES,ALLTESTS,NOschmooloos,TIsearchACTable,TIsearch40ACTable,TIsearchlevelsACTable,TIsearchlevels40ACTable);
                end;
            end;

          TIchar33ACTable:
                begin
START(ALLENUMS,TIchar33ACTable);
                  t[loossetup]  := 3ns;
                  t[looshold]   := 3ns;
                  t[loosdelay]  := 2ns;
                  t[loosdelay4] := 2ns;
                  t[loosdelay5] := 2ns;
                  t[loosdelay6] := 2ns;
                  t[loosdelay7] := 2ns;
                  t[loosabus]   := 2ns;
                  t[looscd]     := 3ns;
                  t[tgb]        := 1ns;
	 	  sp		:= 0ns;  

STOP(ALLENUMS,TIchar33ACTable);
                end;


	  TIsearch33ACTable,       (* set loose variables to smaller values at 33ns *)
	  TIsearchlevels33ACTable:
            begin
              if (schmooloos) then
START(ALLTEMPS,ALLDEVICES,ALLTESTS,schmooloos,TIsearch33ACTable,TIsearchlevels33ACTable);
                begin
                  t[loossetup]  := 2ns;(*3*)
                  t[looshold]   := 2ns;(*3*)
                  t[loosdelay]  := 2ns;(*3*)
                  t[loosdelay4] := 2ns;(*4*)
                  t[loosdelay5] := 2ns;(*5*)
                  t[loosdelay6] := 2ns;(*6*)
                  t[loosdelay7] := 2ns;(*7*)
                  t[loosabus]   := 2ns;(*2*)
                  t[looscd]     := 0ns;
                  t[tgb]        := 0ns;
		  sp		:= 0ns;
STOP(ALLTEMPS,ALLDEVICES,ALLTESTS,schmooloos,TIsearch33ACTable,TIsearchlevels33ACTable);
                end
              else
                begin
START(ALLTEMPS,ALLDEVICES,ALLTESTS,NOschmooloos,TIsearch33ACTable,TIsearchlevels33ACTable);
                  t[loossetup]  := 0ns;
                  t[looshold]   := 0ns;
                  t[loosdelay]  := 0ns;
                  t[loosdelay4] := 0ns;
                  t[loosdelay5] := 0ns;
                  t[loosdelay6] := 0ns;
                  t[loosdelay7] := 0ns;
                  t[loosabus]   := 0ns;
                  t[looscd]     := 3ns;
                  t[tgb]        := 1ns;
	 	  sp		:= 0ns;
STOP(ALLTEMPS,ALLDEVICES,ALLTESTS,NOschmooloos,TIsearch33ACTable,TIsearchlevels33ACTable);
                end;
            end;
          others:
            begin
START(ALLENUMS,ALLTABLES-TIsearch33ACTable-TIsearchlevels33ACTable-TIchar33ACTable-TIsearchACTable-TIsearch40ACTable-TIsearchlevelsACTable-TIsearchlevels40ACTable-TIhifrqloose60ACTable-TIhifrqloose50ACTable-TIstressminACTable-TIstressmaxACTable-TIlofrqloose60ACTable-TInomlooseACTable-TIlofrqlooseACTable-TIlofrqminACTable-TIlofrqmaxACTable-TIlofrqedgeACTable-TIlofrqmin60ACTable-TIlofrqmax60ACTable-TIlofrqedge60ACTable-TIspecsetupmin25ACTable-TIspecsetupmax25ACTable-TIspecholdmin25ACTable-TIspecholdmax25ACTable-TIspecsetupmin33ACTable-TIspecsetupmax33ACTable-TIspecholdmin33ACTable-TIspecholdmax33ACTable-TIhifrqmin33ACTable-TIhifrqmax33ACTable-TIhifrqmin40ACTable-TIhifrqmax40ACTable-TIhifrqedge40ACTable-TIhifrqmin50ACTable-TIhifrqmax50ACTable-TIhifrqedge50ACTable-TIhifrqmin60ACTable-TIhifrqmax60ACTable-TIhifrqedge60ACTable);
              t[loossetup]  := 3ns;
              t[looshold]   := 3ns;
              t[loosdelay]  := 3ns;
              t[loosdelay4] := 4ns;
              t[loosdelay5] := 5ns;
              t[loosdelay6] := 6ns;
              t[loosdelay7] := 7ns;
              t[loosabus]   := 8ns;
              t[looscd]     := 0ns;
              t[tgb]        := 0ns;
	      sp 	    := 7ns;
STOP(ALLENUMS,ALLTABLES-TIsearch33ACTable-TIsearchlevels33ACTable-TIchar33ACTable-TIsearchACTable-TIsearch40ACTable-TIsearchlevelsACTable-TIsearchlevels40ACTable-TIhifrqloose60ACTable-TIhifrqloose50ACTable-TIstressminACTable-TIstressmaxACTable-TIlofrqloose60ACTable-TInomlooseACTable-TIlofrqlooseACTable-TIlofrqminACTable-TIlofrqmaxACTable-TIlofrqedgeACTable-TIlofrqmin60ACTable-TIlofrqmax60ACTable-TIlofrqedge60ACTable-TIspecsetupmin25ACTable-TIspecsetupmax25ACTable-TIspecholdmin25ACTable-TIspecholdmax25ACTable-TIspecsetupmin33ACTable-TIspecsetupmax33ACTable-TIspecholdmin33ACTable-TIspecholdmax33ACTable-TIhifrqmin33ACTable-TIhifrqmax33ACTable-TIhifrqmin40ACTable-TIhifrqmax40ACTable-TIhifrqedge40ACTable-TIhifrqmin50ACTable-TIhifrqmax50ACTable-TIhifrqedge50ACTable-TIhifrqmin60ACTable-TIhifrqmax60ACTable-TIhifrqedge60ACTable);
            end;
        end; (*case*)

	(***********************************************************)
	(***                                                     ***)
	(*** The AC Tables are defined below. There is a single  ***)
	(*** AC Table set-up. Different AC Tables are created by ***)
	(*** accessing different AC Data Sheets using the "with" ***)
	(*** instruction. Parametric tests will normally access  ***)
	(*** one of the functional AC Tables. It is not normally ***)
	(*** necessary to set up separate AC Tables for          ***)
	(*** parametric testing. The requirements of doing SCHMOO***)
	(*** and SEARCH routines requires that the same AC Table ***)
	(*** set-up be used for all test frequencies. One new AC ***)
	(*** Table will be created each time the ACTableSet is   ***)
	(*** called with a new actable parameter (Table Name).   ***)
	(*** The user is required to call the ACTableSet         ***)
	(*** procedure once for each unique timing set (different***)
	(*** periods, and different parameters, ie. loose timing)***)
	(***                                                     ***)
	(***********************************************************)

        ACTableOpen( actable );


    (*							       *)
    (* Initialize all Origins to 0ns for TIallACTable only     *)
    (*							       *)

        if (actable = TIallACTable) then
          begin
            OriginSet (orgtoffset,   0ns);
            OriginSet (orgtH1flo,    0ns);
            OriginSet (orgtH3flo,    0ns);
            OriginSet (orgtH3rhi,    0ns);
            OriginSet (orgtH1high,   0ns);
            OriginSet (orgtH1low,    0ns);
            OriginSet (orgtH3high,   0ns);
            OriginSet (orgtH3low,    0ns);
            OriginSet (orgtCSTRBfhi, 0ns);
            OriginSet (orgtCRDYflo,  0ns);
          end;


    (*                                                         *)
    (* Timing and Waveform set-up for all frequencies          *)
    (*                                                         *)

        PeriodSetAll (t[tper]);         (* Period for ACTables *)



      case actable of
        TIparametricACTable,
        TIcrystalACTable,
        TIlofrqminACTable,
        TIlofrqmaxACTable,
        TIlofrqmin60ACTable,
        TIlofrqmax60ACTable,
        TIhifrqmin50ACTable,
        TIhifrqmax50ACTable,
        TIhifrqmin60ACTable,
        TIhifrqmax60ACTable,
        TIsearchACTable,
        TIcharACTable:
          begin
START(ALLENUMS,TIparametricACTable,TIcrystalACTable,TIlofrqminACTable,TIlofrqmaxACTable,TIlofrqmin60ACTable,TIlofrqmax60ACTable,TIhifrqmin50ACTable,TIhifrqmax50ACTable,TIhifrqmin60ACTable,TIhifrqmax60ACTable,TIsearchACTable,TIcharACTable);


        WaveSetDoubleClk    (CLKINdriveWF,
                            t[tref]+t[toffset],
                            t[tref]+t[toffset]+t[twCIH],
                            t[tref]+t[toffset]+t[twCIH]+t[twCIL],
                            t[tref]+t[toffset]+t[twCIH]+t[twCIL]+t[twCIH]);
        EdgeSetOrigin       (CLKINdriveWF, Edge1, orgtoffset);
        EdgeSetOrigin       (CLKINdriveWF, Edge2, orgtoffset);
        EdgeSetOrigin       (CLKINdriveWF, Edge3, orgtoffset);
        EdgeSetOrigin       (CLKINdriveWF, Edge4, orgtoffset);

        EdgeSetDelayData    (RESETdriveWF,Edge1,ChanFirst,
                            DriveData,ThreshVITL,
                            t[tref]+t[toffset]+t[twCIH]+t[twCIL]+t[twCIH]-t[tsuRESET]-t[loossetup]+dtcf,0,
                            DriveData,ThreshVITH,
                            t[tref]+t[tH1flo]-t[tsuRESETH]-t[loossetup]+dtcf,0);

        WaveSetEdgeStrobe   (H1strobeWF,
                            0ns,
                            t[tref]+t[loosclock],
                            t[tref]+t[loosclock]+7ns);

        WaveSetEdgeStrobe   (H1HIGHstrobeWF,
                            0ns,
                            t[tref]+t[tH1flo]-t[tfHmax],
                            t[tref]+t[tH1flo]-t[tfHmax]+7ns);
        EdgeSetOrigin       (H1HIGHstrobeWF, Edge2, orgtH1high);
        EdgeSetOrigin       (H1HIGHstrobeWF, Edge3, orgtH1high);

        EdgeSet             (H1LOWstrobeWF,Edge1,DriveOff,
                            0ns);
        EdgeSet             (H1LOWstrobeWF,Edge2,EdgeStrobeLow,
                            t[tref]+t[tcH]-t[trHmax]);
        EdgeSet             (H1LOWstrobeWF,Edge3,StrobeLatch,
                            t[tref]+t[tcH]-t[trHmax]+7ns);
        EdgeSetOrigin       (H1LOWstrobeWF, Edge2, orgtH1low);
        EdgeSetOrigin       (H1LOWstrobeWF, Edge3, orgtH1low);

        WaveSetEdgeStrobe   (H1IDLEstrobeWF,
                            0ns,
                            t[tref]+t[tH1flo]+t[loosclock],
                            t[tref]+t[tH1flo]+t[loosclock]+7ns);

        WaveSetEdgeStrobe   (H3strobeWF,
                            0ns,
                            t[tref]+t[loosclock],
                            t[tref]+t[loosclock]+7ns);

        WaveSetEdgeStrobe   (H3LOWstrobeWF,
                            0ns,
                            t[tref]+t[tH3rhi]-t[trHmax],
                            t[tref]+t[tH3rhi]-t[trHmax]+7ns);
        EdgeSetOrigin       (H3LOWstrobeWF, Edge2, orgtH3low);
        EdgeSetOrigin       (H3LOWstrobeWF, Edge3, orgtH3low);

        EdgeSet             (H3HIGHstrobeWF,Edge1,DriveOff,
                            0ns);
        EdgeSet             (H3HIGHstrobeWF,Edge2,EdgeStrobeHigh,
                            t[tref]+t[tcH]+t[tH3flo]-t[tfHmax]);
        EdgeSet             (H3HIGHstrobeWF,Edge3,StrobeLatch,
                            t[tref]+t[tcH]+t[tH3flo]-t[tfHmax]+7ns);
        EdgeSetOrigin       (H3HIGHstrobeWF, Edge2, orgtH3high);
        EdgeSetOrigin       (H3HIGHstrobeWF, Edge3, orgtH3high);

        WaveSetEdgeStrobe   (H3IDLEstrobeWF,
                            0ns,
                            t[tref]+t[tH1flo]+t[loosclock],
                            t[tref]+t[tH1flo]+t[loosclock]+7ns);

        EdgeSet             (STRBstrobeWF,Edge1,StrobeOff,t[tref]+
                            t[tH1flo]+t[tdH1LS]-t[restrict]-t[loosdelay]+
                            t[tgb]+ctcf);

        (* bb 7/8/96 Changed so that VOH does not have 1ns tgb *)
        EdgeSetDelayData    (STRBstrobeWF,Edge2,ChanFirst,
                            StrobeData,ThreshVITL,
                            t[tref]+t[tH1flo]+t[tdH1LS]+t[loosdelay7]-t[tgb]-ctcf,0,
                            StrobeData,ThreshVITH,
                            t[tref]+t[tH1flo]+t[tdH1LS]+t[loosdelay7]-ctcf,0);
 
        EdgeSetOrigin       (STRBstrobeWF, Edge1, orgtH1flo);
        EdgeSetOrigin       (STRBstrobeWF, Edge2, orgtH1flo);

        EdgeSet             (RWstrobeWF,Edge1,StrobeOff,t[tref]+
                            t[tdH1HRW]-t[restrict]-t[loosdelay]+t[tgb]+ctcf);
        EdgeSet             (RWstrobeWF,Edge2,StrobeData,t[tref]+
                            t[tdH1HRW]+t[loosdelay5]-t[tgb]-ctcf);

        EdgeSet             (ABUSVstrobeWF,Edge1,StrobeOff,t[tref]+
                            t[tH1flo]+t[tdH1LA]-2*t[restrict]-t[loosdelay]+
                            t[tgb]+ctcf+t[tcH]-7ns);
        EdgeSet             (ABUSVstrobeWF,Edge2,StrobeData,t[tref]+
                            t[tH1flo]+t[tdH1LA]-t[restrict]-t[loosdelay]+
                            t[tgb]+ctcf+t[tcH]-7ns);
        EdgeSetOrigin       (ABUSVstrobeWF, Edge1, orgtH1flo);
        EdgeSetOrigin       (ABUSVstrobeWF, Edge2, orgtH1flo);

        EdgeSet             (ABUSstrobeWF,Edge1,StrobeOff,t[tref]+
                            t[tH1flo]+t[tdH1LA]-t[restrict]-t[loosdelay]+
                            t[tgb]+ctcf);

        (* bb 7/8/96 Changed so that VOH does not have 1ns tgb *)
        EdgeSetDelayData    (ABUSstrobeWF,Edge2,ChanFirst,
                            StrobeData,ThreshVITL,
                            t[tref]+t[tH1flo]+t[tdH1LA]+t[loosdelay7]-t[tgb]-ctcf,0,
                            StrobeData,ThreshVITH,
                            t[tref]+t[tH1flo]+t[tdH1LA]+t[loosdelay7]-ctcf,0);
 
        EdgeSetOrigin       (ABUSstrobeWF, Edge1, orgtH1flo);
        EdgeSetOrigin       (ABUSstrobeWF, Edge2, orgtH1flo);

        EdgeSet             (ABUSWWstrobeWF,Edge1,StrobeOff,t[tref]+
                            t[tdH1HA]-t[restrict]-t[loosabus]+t[tgb]+ctcf);
        EdgeSet             (ABUSWWstrobeWF,Edge2,StrobeData,t[tref]+
                            t[tdH1HA]+t[loosabus]-t[tgb]-ctcf);

        EdgeSet             (STATstrobeWF,Edge1,StrobeOff,t[tref]+
                            t[tH1flo]+t[tdH1LSTAT]-t[restrict]-t[loosdelay]+
                            t[tgb]+ctcf);

        (* bb 7/8/96 Changed so that VOH does not have 1ns tgb *)
        EdgeSetDelayData    (STATstrobeWF,Edge2,ChanFirst,
                            StrobeData,ThreshVITL,
                            t[tref]+t[tH1flo]+t[tdH1LSTAT]+t[loosdelay7]-t[tgb]-ctcf,0,
                            StrobeData,ThreshVITH,
                            t[tref]+t[tH1flo]+t[tdH1LSTAT]+t[loosdelay7]-ctcf,0);
 
       EdgeSetOrigin       (STATstrobeWF, Edge1, orgtH1flo);
        EdgeSetOrigin       (STATstrobeWF, Edge2, orgtH1flo);

        EdgeSet             (LOCKstrobeWF,Edge1,StrobeOff,t[tref]+
                            t[tH1flo]+t[tdH1LLOCK]-t[restrict]-t[loosdelay]+
                            t[tgb]+ctcf);
        EdgeSet             (LOCKstrobeWF,Edge2,StrobeData,t[tref]+
                            t[tH1flo]+t[tdH1LLOCK]+t[loosdelay5]-t[tgb]-ctcf);
        EdgeSetOrigin       (LOCKstrobeWF, Edge1, orgtH1flo);
        EdgeSetOrigin       (LOCKstrobeWF, Edge2, orgtH1flo);

        WaveSetSBC          (DBUSdriveWF,
                            t[tref]+t[tH1flo]-t[tsuDR]-t[loossetup]+dtcf-7ns,
                            t[tref]+t[tH1flo]-t[tsuDR]-t[loossetup]+dtcf,
                            t[tref]+t[tH1flo]+t[thDR]+t[looshold]-dtcf);
        EdgeSetOrigin       (DBUSdriveWF, Edge1, orgtH1flo);
        EdgeSetOrigin       (DBUSdriveWF, Edge2, orgtH1flo);
        EdgeSetOrigin       (DBUSdriveWF, Edge3, orgtH1flo);


        EdgeSet             (DBUSstrobeWF,Edge1,DriveOff,t[tref]+
                            t[tH1flo]+t[tvDW]+t[loosdelay7]-t[tgb]-ctcf-
                            t[restrict]-7ns);
        EdgeSet             (DBUSstrobeWF,Edge2,StrobeOff,t[tref]+
                            t[tH1flo]+t[tvDW]+t[loosdelay7]-t[tgb]-ctcf-
                            t[restrict]);

        (* bb 7/8/96 Changed so that VOH does not have 1ns tgb *)
        EdgeSetDelayData    (DBUSstrobeWF,Edge3,ChanFirst,
                            StrobeData,ThreshVITL,
                            t[tref]+t[tH1flo]+t[tvDW]+t[loosdelay7]-t[tgb]-ctcf,0,
                            StrobeData,ThreshVITH,
                            t[tref]+t[tH1flo]+t[tvDW]+t[loosdelay7]-ctcf,0);
 
        EdgeSetOrigin       (DBUSstrobeWF, Edge1, orgtH1flo);
        EdgeSetOrigin       (DBUSstrobeWF, Edge2, orgtH1flo);
        EdgeSetOrigin       (DBUSstrobeWF, Edge3, orgtH1flo);

        EdgeSet             (DBUSstrobeoffWF,Edge1,StrobeOff,t[tref]+
                            t[thDW]-t[loosdelay]+t[tgb]+ctcf);

        EdgeSet             (DBUSWWstrobeWF,Edge1,StrobeOff,t[tref]+
                            t[thDW]-t[loosdelay]+t[tgb]+ctcf);
        (* bb 7/8/96 Changed so that VOH does not have 1ns tgb *)
        EdgeSetDelayData    (DBUSWWstrobeWF,Edge2,ChanFirst,
                            StrobeData,ThreshVITL,
                            t[tref]+t[tH1flo]+t[tvDW]+t[loosdelay5]-t[tgb]-ctcf,0,
                            StrobeData,ThreshVITH,
                            t[tref]+t[tH1flo]+t[tvDW]+t[loosdelay5]-ctcf,0);
  
       EdgeSetOrigin       (DBUSWWstrobeWF, Edge2, orgtH1flo);

	(* New waveform - see comment at top for usage.    PHQ    8/12/93 *) 
	(* No loose gb to guarantee at least 10ns window *)

	(* Calculation for edge placement so that edge rule is not violated *)
	(* StrobeOn-StrobeOff must be at least 3ns.			    *)
	(* This edge will follow either StrobeData edge of DBUSstrobeWF or  *)
	(* DBUSWWstrobeWF.				   PHQ    8/13/93   *)

	SparePicoSeconds1 := t[tref]+t[tH1flo]+t[tvDW]-t[tgb]-ctcf;
			     (* StrobeData edge of DBUSstrobeWF or DBUSWWstrobeWF *)
	if(SparePicoSeconds1 > t[tcH]) then
	   (* Going over next cycle *)
	   SparePicoSeconds2 := (SparePicoSeconds1 - t[tcH]) + 4ns
	else
	  SparePicoSeconds2 := 4ns;

        EdgeSet             (DBUSWW2strobeWF, Edge1, StrobeOff,
	           	     + SparePicoSeconds2);

        EdgeSet             (DBUSWW2strobeWF,Edge2,StrobeData,t[tref]+
                            t[tH1flo]-t[tsuDR2]-ctcf);

        EdgeSetOrigin       (DBUSWW2strobeWF, Edge2, orgtH1flo);


        WaveSetRTO          (RDYdriveWF,
                            t[tref]+t[tH1flo]-t[tsuRDY]-t[loossetup]+dtcf,
                            t[tref]+t[tH1flo]+t[thRDY]+t[looshold]-dtcf);
        EdgeSetOrigin       (RDYdriveWF, Edge1, orgtH1flo);
        EdgeSetOrigin       (RDYdriveWF, Edge2, orgtH1flo);

        WaveSetNR           (ENBdriveWF,
                            t[tref]+t[tENB]);

        WaveSetStrobeZ      (DBUSHIZstrobeWF,
                            0ns,
                            t[tref]+t[tENB]+t[tdENBZ]+t[loosdelay]-ctcf,
                            t[tref]+t[tENB]+t[tdENBZ]+t[loosdelay]+7ns+ctcf);

        WaveSetStrobeZ      (ABUSHIZstrobeWF,
                            0ns,
                            t[tref]+t[tENB]+t[tdENBZ]+t[loosdelay]-ctcf,
                            t[tref]+t[tENB]+t[tdENBZ]+t[loosdelay]+7ns+ctcf);

        WaveSetStrobeZ      (CTRLHIZstrobeWF,
                            0ns,
                            t[tref]+t[tENB]+t[tdENBZ]+t[loosdelay]-ctcf,
                            t[tref]+t[tENB]+t[tdENBZ]+t[loosdelay]+7ns+ctcf);

        EdgeSet             (DBUSVALstrobeWF,Edge1,StrobeOff,t[tref]+
                            t[tENB]+t[tdENBDV]-t[restrict]-t[loosdelay]+
                            t[tgb]+ctcf);
        EdgeSet             (DBUSVALstrobeWF,Edge2,StrobeData,t[tref]+
                            t[tENB]+t[tdENBDV]+t[loosdelay7]-t[tgb]-ctcf);

        WaveSetStrobe    (ABUSVALstrobeWF,
                            0ns,
                            t[tref]+t[tENB]+t[tdENBAV]+t[loosdelay]-
                            t[tgb]-ctcf,
                            t[tref]+t[tENB]+t[tdENBAV]+t[loosdelay]-
                            t[tgb]-ctcf+6ns);


        WaveSetStrobe       (CTRLVALstrobeWF,
                            0ns,
                            t[tref]+t[tENB]+t[tdENBCV]+t[loosdelay]-
                            t[tgb]-ctcf,
                            t[tref]+t[tENB]+t[tdENBCV]+t[loosdelay]-
                            t[tgb]-ctcf+6ns);


        WaveSetSBC          (IIOFdriveWF,
                            t[tref]+t[tH1flo]-t[tsuIF]-t[loossetup]+dtcf-7ns,
                            t[tref]+t[tH1flo]-t[tsuIF]-t[loossetup]+dtcf,
                            t[tref]+t[tH1flo]+t[thIF]+t[looshold]-dtcf);
        EdgeSetOrigin       (IIOFdriveWF, Edge1, orgtH1flo);
        EdgeSetOrigin       (IIOFdriveWF, Edge2, orgtH1flo);
        EdgeSetOrigin       (IIOFdriveWF, Edge3, orgtH1flo);

        EdgeSet             (IIOFstrobeWF,Edge1,DriveOff,t[tref]+
                            t[tH1flo]+t[tvH1LIF]+t[loosdelay]-t[tgb]-ctcf-7ns);

        (* bb 7/8/96 Changed so that VOH does not have 1ns tgb *)
        EdgeSetDelayData    (IIOFstrobeWF,Edge2,ChanFirst,
                            StrobeData,ThreshVITL,
                            t[tref]+t[tH1flo]+t[tvH1LIF]+t[loosdelay]-t[tgb]-ctcf,0,
                            StrobeData,ThreshVITH,
                            t[tref]+t[tH1flo]+t[tvH1LIF]+t[loosdelay]-ctcf,0);
 
        EdgeSetOrigin       (IIOFstrobeWF, Edge1, orgtH1flo);
        EdgeSetOrigin       (IIOFstrobeWF, Edge2, orgtH1flo);

        EdgeSet             (IIOFstrobeoffWF,Edge1,StrobeOff,t[tref]+
                            t[tH1flo]+t[thH1LIFOI]-t[loosdelay]+t[tgb]+ctcf);

        EdgeSetOrigin       (IIOFstrobeoffWF, Edge1, orgtH1flo);

        if ((actable = TIlofrqmaxACTable) or (actable = TIlofrqminACTable)) then
START(ALLENUMS,TIlofrqmaxACTable,TIlofrqminACTable);
           EdgeSet          (IIOFWWstrobeWF,Edge1,StrobeOff,t[tref]+
                            t[tH1flo]+t[tvH1LIF]-t[restrict]-t[loosdelay5]+
                            ctcf+t[thIF])  (*EGM took out tgb g/b and added spec *)
STOP(ALLENUMS,TIlofrqmaxACTable,TIlofrqminACTable);
        else                               (*thIFmin=0ns (IIOFX had rm for adjmt)*)
START(ALLENUMS,ALLTABLES-TIlofrqmaxACTable-TIlofrqminACTable);
           EdgeSet          (IIOFWWstrobeWF,Edge1,StrobeOff,t[tref]+
                            t[tH1flo]+t[tvH1LIF]-t[restrict]-t[loosdelay5]+
                            t[tgb]+ctcf+t[thIF]); (*EGM, added spec thIFmin*)
STOP(ALLENUMS,ALLTABLES-TIlofrqmaxACTable-TIlofrqminACTable);

        EdgeSet             (IIOFWWstrobeWF,Edge2,StrobeData,t[tref]+
                            t[tH1flo]+t[tvH1LIF]+t[loosdelay5]-ctcf);
  
     (*  Took out the Voh/Vol offsets along with the 1ns guardband used  *)
        (* bb 7/8/96 Changed so that VOH does not have 1ns tgb *)

        EdgeSetOrigin       (IIOFWWstrobeWF, Edge1, orgtH1flo);
        EdgeSetOrigin       (IIOFWWstrobeWF, Edge2, orgtH1flo);

        WaveSetNR           (INTdriveWF,
                            t[tref]+t[tH1flo]-t[tsuINT]-t[loossetup]+dtcf);
        EdgeSetOrigin       (INTdriveWF, Edge1, orgtH1flo);

        WaveSetNR           (INTIDLEdriveWF,
                            t[tref]+t[tH1flo]-t[tsuINTIDLE]-t[loossetup]+dtcf);
        EdgeSetOrigin       (INTdriveWF, Edge1, orgtH1flo);

        EdgeSet             (IACKstrobeWF,Edge1,StrobeOff,t[tref]+
                            t[tH1flo]+t[tdH1LIACK]-t[restrict]-t[loosdelay]+
                            t[tgb]+ctcf);
        EdgeSet             (IACKstrobeWF,Edge2,StrobeData,t[tref]+
                            t[tH1flo]+t[tdH1LIACK]+t[loosdelay6]-t[tgb]-ctcf);
        EdgeSetOrigin       (IACKstrobeWF, Edge1, orgtH1flo);
        EdgeSetOrigin       (IACKstrobeWF, Edge2, orgtH1flo);


        EdgeSetDelayData    (CREQdriveWF,Edge1,ChanFirst,
                            DriveData,ThreshVITL,
                            t[tref]+t[tH1flo]-t[tsuCREQ],0,
                            DriveData,ThreshVITH,
                            t[tref]+t[tH1flo]+t[tsuCREQ],0);

        EdgeSetDelayData    (CREQstrobeWF,Edge1,ChanFirst,
                            DriveOff,ThreshVITL,t[tref]+
                            t[tdH1HRQLt]+t[loosdelay]-t[tgb]-ctcf-7ns,0,
                            DriveOff,ThreshVITH,t[tref]+
                            t[tH1flo]-t[tsuCACK]+t[tdALRQHt]+
                            t[loosdelay]-t[tgb]-ctcf-7ns,0);
        EdgeSetDelayData    (CREQstrobeWF,Edge2,ChanFirst,
                            StrobeData,ThreshVITL,t[tref]+
                            t[tdH1HRQLt]+t[loosdelay]-t[tgb]-ctcf,0,
                            StrobeData,ThreshVITH,t[tref]+
                            t[tH1flo]-t[tsuCACK]+t[tdALRQHt]+
                            t[loosdelay]-t[tgb]-ctcf,0);
        EdgeSetDelayData    (CREQstrobeWF,Edge3,ChanFirst,
                            StrobeOff,ThreshVITL,t[tref]+
                            t[tdH1HRQLt]+t[loosdelay]-t[tgb]-ctcf+7ns,0,
                            StrobeOff,ThreshVITH,t[tref]+
                            t[tH1flo]-t[tsuCACK]+t[tdALRQHt]+
                            t[loosdelay]-t[tgb]-ctcf+7ns,0);

        EdgeSetDelayData    (CREQ2strobeWF,Edge1,ChanFirst,
                            DriveOff,ThreshVITL,t[tref]+
                            t[tH1flo]+t[tsuCREQ]+t[tdRQHRQLt]+
                            t[loosdelay]-t[tgb]-ctcf-7ns,0,
                            DriveOff,ThreshVITH,t[tref]+
                            t[tH1flo]+t[tsuCREQ]+t[tdRQHRQOt]+
                            t[loosdelay]-t[tgb]-ctcf-7ns,0);
        EdgeSetDelayData    (CREQ2strobeWF,Edge2,ChanFirst,
                            StrobeData,ThreshVITL,t[tref]+
                            t[tH1flo]+t[tsuCREQ]+t[tdRQHRQLt]+
                            t[loosdelay]-t[tgb]-ctcf,0,
                            StrobeData,ThreshVITH,t[tref]+
                            t[tH1flo]+t[tsuCREQ]+t[tdRQHRQOt]+
                            t[loosdelay]-t[tgb]-ctcf,0);
        EdgeSetDelayData    (CREQ2strobeWF,Edge3,ChanFirst,
                            StrobeOff,ThreshVITL,t[tref]+
                            t[tH1flo]+t[tsuCREQ]+t[tdRQHRQLt]+
                            t[loosdelay]-t[tgb]-ctcf+7ns,0,
                            StrobeOff,ThreshVITH,t[tref]+
                            t[tH1flo]+t[tsuCREQ]+t[tdRQHRQOt]+
                            t[loosdelay]-t[tgb]-ctcf+7ns,0);

        WaveSetNR           (CACKdriveWF,
                            t[tref]+t[tH1flo]-t[tsuCACK]);
        EdgeSetOrigin       (CACKdriveWF, Edge1, orgtH1flo);

        WaveSetStrobe       (CACKstrobeWF,
                            t[tref]+t[tH1flo]-t[tsuCREQ]+t[tdRQLALt]+
                            t[loosdelay7]-t[tgb]-ctcf-7ns,
                            t[tref]+t[tH1flo]-t[tsuCREQ]+t[tdRQLALt]+
                            t[loosdelay7]-t[tgb]-ctcf,
                            t[tref]+t[tH1flo]-t[tsuCREQ]+t[tdRQLALt]+
                            t[loosdelay7]-t[tgb]-ctcf+7ns);
        EdgeSetOrigin       (CACKstrobeWF, Edge1, orgtH1flo);
        EdgeSetOrigin       (CACKstrobeWF, Edge2, orgtH1flo);
        EdgeSetOrigin       (CACKstrobeWF, Edge3, orgtH1flo);

(* CRDY  Edge1 is defined as DriveData here, but in actuality should always   *)
(* end up being a drive-low edge based on pattern data and translation.       *)

        WaveSetRTO          (CRDYdriveWF,
                            t[tCRDYLO],
                            t[tCRDYHI]);

(* special cstrb_ strobe w/o origin used for sync-up only to avoid problems   *)
(* with bsearch.                                                              *)

        WaveSetStrobe       (CSTRB_SYNCstrobeWF,
                            t[tCRDYHI]-t[tcH]+t[tdRHSLw]-7ns,
                            t[tCRDYHI]-t[tcH]+t[tdRHSLw],
                            t[tCRDYHI]-t[tcH]+t[tdRHSLw]+7ns);

        EdgeSetDelayData    (CSTRBstrobeWF,Edge1,ChanFirst,
                            DriveOff,ThreshVITL,t[tCRDYHI]-t[tcH]+
                            t[tdRHSLw]+t[loosdelay7]-t[tgb]-ctcf-7ns,0,
                            DriveOff,ThreshVITH,t[tCRDYLO]+
                            t[tdRLSHw]+t[loosdelay]-t[tgb]-ctcf-7ns,0);
        EdgeSetDelayData    (CSTRBstrobeWF,Edge2,ChanFirst,
                            StrobeData,ThreshVITL,t[tCRDYHI]-t[tcH]+
                            t[tdRHSLw]+t[loosdelay7]-t[tgb]-ctcf,0,
                            StrobeData,ThreshVITH,t[tCRDYLO]+
                            t[tdRLSHw]+t[loosdelay]-t[tgb]-ctcf,0);

        EdgeSetDelayData    (CSTRBstrobeWF,Edge3,ChanFirst,
                            StrobeOff,ThreshVITL,t[tCRDYHI]-t[tcH]+
                            t[tdRHSLw]+t[loosdelay7]-t[tgb]-ctcf+7ns,0,
                            StrobeOff,ThreshVITH,t[tCRDYLO]+
                            t[tdRLSHw]+t[loosdelay]-t[tgb]-ctcf+7ns,0);

        WaveSetStrobe       (CDstrobeWF,
                            t[tref]+t[tCSTRBfhi]-t[tsuCDw]+
                            t[loosdelay]-t[tgb]-ctcf-7ns,
                            t[tref]+t[tCSTRBfhi]-t[tsuCDw]+
                            t[loosdelay]-t[tgb]-ctcf,
                            t[tCRDYLO]+t[thCDw]-t[loosdelay]+t[tgb]+ctcf);
        EdgeSetOrigin       (CDstrobeWF, Edge1, orgtCSTRBfhi);
        EdgeSetOrigin       (CDstrobeWF, Edge2, orgtCSTRBfhi);

(* CSTRB Edge1 is defined as DriveData here, but in actuality should always   *)
(* end up being a drive-low edge based on pattern data and translation.       *)

        WaveSetRTO          (CSTRBdriveWF,
                            t[tCSTRBLO],
                            t[tCSTRBHI]);  
        EdgeSetOrigin       (CSTRBdriveWF, Edge1, orgtCSTRBfhi);
        EdgeSetOrigin       (CSTRBdriveWF, Edge2, orgtCSTRBfhi);

        WaveSetStrobe       (CRDY_SYNCstrobeWF,          (*special crdy_  strobe*)
                            t[tCSTRBLO]+t[tdSLRLr]-7ns,  (*w/o origin used for  *)
                            t[tCSTRBLO]+t[tdSLRLr],      (*sync-up only to avoid*)
                            t[tCSTRBLO]+t[tdSLRLr]+7ns); (*problems with bsearch*)

        EdgeSetDelayData    (CRDYstrobeWF,Edge1,ChanFirst,
                            DriveOff,ThreshVITL,t[tCSTRBLO]+
                            t[tdSLRLr]+t[loosdelay4]-t[tgb]-ctcf-7ns,0,
                            DriveOff,ThreshVITH,t[tCSTRBHI]+
                            t[tdSHRHr]+t[loosdelay]-t[tgb]-ctcf-7ns,0);
        EdgeSetDelayData    (CRDYstrobeWF,Edge2,ChanFirst,
                            StrobeData,ThreshVITL,t[tCSTRBLO]+
                            t[tdSLRLr]+t[loosdelay5]-t[tgb]-ctcf,0,
                            StrobeData,ThreshVITH,t[tCSTRBHI]+
                            t[tdSHRHr]+t[loosdelay]-t[tgb]-ctcf,0);
        EdgeSetDelayData    (CRDYstrobeWF,Edge3,ChanFirst,
                            StrobeOff,ThreshVITL,t[tCSTRBLO]+
                            t[tdSLRLr]+t[loosdelay5]-t[tgb]-ctcf+7ns,0,
                            StrobeOff,ThreshVITH,t[tCSTRBHI]+
                            t[tdSHRHr]+t[loosdelay]-t[tgb]-ctcf+7ns,0);

        EdgeSetDelayData    (CDdriveWF,Edge1,ChanFirst,
                            DriveComplement,ThreshVITL,t[tCSTRBLO]-
                            t[tsuCDr]-t[loossetup]+dtcf-7ns,0,
                            DriveComplement,ThreshVITH,t[tCSTRBLO]-
                            t[tsuCDr]-t[looscd]-t[loossetup]+dtcf-7ns,0);
        EdgeSetDelayData    (CDdriveWF,Edge2,ChanFirst,
                            DriveData,ThreshVITL,t[tCSTRBLO]-
                            t[tsuCDr]-t[loossetup]+dtcf,0,
                            DriveData,ThreshVITH,t[tCSTRBLO]-
                            t[tsuCDr]-t[looscd]-t[loossetup]+dtcf,0);
        EdgeSetDelayData    (CDdriveWF,Edge3,ChanFirst,
                            DriveComplement,ThreshVITL,t[tref]+t[tCRDYflo]+
                            t[thCDr]+t[looscd]+t[looshold]-dtcf,0,
                            DriveComplement,ThreshVITH,t[tref]+t[tCRDYflo]+
                            t[thCDr]+t[looshold]-dtcf,0);


        WaveSetSBC          (TCLKdriveWF,
                            t[tref]+t[tH1flo]-t[tsuTCLK]-t[loossetup]+dtcf-7ns,
                            t[tref]+t[tH1flo]-t[tsuTCLK]-t[loossetup]+dtcf,
                            t[tref]+t[tH1flo]+t[thTCLK]+t[looshold]-dtcf);
        EdgeSetOrigin       (TCLKdriveWF, Edge1, orgtH1flo);
        EdgeSetOrigin       (TCLKdriveWF, Edge2, orgtH1flo);
        EdgeSetOrigin       (TCLKdriveWF, Edge3, orgtH1flo);

        WaveSetStrobe       (TCLKstrobeWF,
                            t[tref]+t[tdTCLK]+t[loosdelay6]-t[tgb]-ctcf-7ns,
                            t[tref]+t[tdTCLK]+t[loosdelay6]-t[tgb]-ctcf,
                            t[tref]+t[tdTCLK]+t[tcH]-t[restrict]-t[loosdelay]+
                            t[tgb]+ctcf);


        WaveSetRTO          (TCKCLKdriveWF,
                            t[tref],
                            t[tref]+t[tcCI]);

        WaveSetNR           (TCKdriveWF,
                            t[tref]);

        WaveSetSBC          (TDITMSdriveWF,
                            t[tref]+t[tcCI]-t[tsuTDITMS]-t[loossetup]+dtcf-7ns,
                            t[tref]+t[tcCI]-t[tsuTDITMS]-t[loossetup]+dtcf,
                            t[tref]+t[tcCI]+t[thTDITMS]+t[looshold]-dtcf);

        WaveSetNR           (JTAGdriveWF,
                            t[tref]+t[tJTAG]);

        WaveSetStrobe       (TDOstrobeWF,
                            0ns,
                            t[tref]+t[tdTDO]+t[loosdelay]-t[tgb]-ctcf,
                            t[tref]+t[tdTDO]+t[loosdelay]-t[tgb]-ctcf+7ns);

        WaveSetEdgeStrobe   (JTAGH1strobeWF,
                            0ns,
                            t[tref]+t[tdTDO]+t[loosdelay]-t[tgb]-ctcf,
                            t[tref]+t[tdTDO]+t[loosdelay]-t[tgb]-ctcf+7ns);


        EdgeSet             (JTAGVARYstrobeWF,Edge1,StrobeOff,t[tref]+
                            t[tdTDO]-t[restrict]-t[loosdelay]+t[tgb]+ctcf);
        EdgeSet             (JTAGVARYstrobeWF,Edge2,StrobeData,t[tref]+
                            t[tdTDO]+t[tcCI]+t[loosdelay]-t[tgb]-ctcf);

        EdgeSet             (JTAGABUSstrobeWF,Edge1,StrobeOff,t[tref]+
                            t[tdTDO]-t[restrict]-t[loosdelay]+t[tgb]+ctcf);
        EdgeSet             (JTAGABUSstrobeWF,Edge2,DriveOff,t[tref]+
                            t[tdTDO]-t[restrict]-t[loosdelay]+t[tgb]+ctcf);
        EdgeSet             (JTAGABUSstrobeWF,Edge3,StrobeData,t[tref]+
                            t[tdTDO]+t[tcCI]+t[loosdelay]-t[tgb]-ctcf);

        WaveSetNR           (EMUdriveWF,
                            t[tref]+t[tEMU]);

        WaveSetStrobe       (EMUstrobeWF,
                            0ns,
                            t[tref]+t[tdEMU]+t[loosdelay]-t[tgb]-ctcf,
                            t[tref]+t[tdEMU]+t[loosdelay]-t[tgb]-ctcf+7ns);


        WaveSetNR           (RESETLOCdriveWF,
                            t[tref]+t[tRESETLOC]);

        WaveSetNR           (ROMENdriveWF,
                            t[tref]+t[tROMEN]);

        WaveSetNR           (NMIdriveWF,
                            t[tref]+t[tNMI]);


        WaveSetContinue     (ContinueWF);

        WaveSetOff          (ALLoffWF,t[tref],t[tref]);

STOP(ALLENUMS,TIparametricACTable,TIcrystalACTable,TIlofrqminACTable,TIlofrqmaxACTable,TIlofrqmin60ACTable,TIlofrqmax60ACTable,TIhifrqmin50ACTable,TIhifrqmax50ACTable,TIhifrqmin60ACTable,TIhifrqmax60ACTable,TIsearchACTable,TIcharACTable);

          end; (*1st case*)
	TInomlooseACTable,
        TIstressminACTable,
        TIstressmaxACTable,
        TIlofrqlooseACTable,
        TIlofrqloose60ACTable,
        TIhifrqloose50ACTable,
        TIhifrqloose60ACTable,
        TIsearchlevelsACTable:
          begin
START(ALLENUMS,TInomlooseACTable,TIstressminACTable,TIstressmaxACTable,TIlofrqlooseACTable,TIlofrqloose60ACTable,TIhifrqloose50ACTable,TIhifrqloose60ACTable,TIsearchlevelsACTable);

        WaveSetDoubleClk    (CLKINdriveWF,
                            t[tref]+t[toffset],
                            t[tref]+t[toffset]+t[twCIH],
                            t[tref]+t[toffset]+t[twCIH]+t[twCIL],
                            t[tref]+t[toffset]+t[twCIH]+t[twCIL]+t[twCIH]);
        EdgeSetOrigin       (CLKINdriveWF, Edge1, orgtoffset);
        EdgeSetOrigin       (CLKINdriveWF, Edge2, orgtoffset);
        EdgeSetOrigin       (CLKINdriveWF, Edge3, orgtoffset);
        EdgeSetOrigin       (CLKINdriveWF, Edge4, orgtoffset);

        EdgeSetDelayData    (RESETdriveWF,Edge1,ChanFirst,
                            DriveData,ThreshVITL,
                            t[tref]+t[toffset]+t[twCIH]+t[twCIL]+t[twCIH]-t[tsuRESET]-t[loossetup]+dtcf,0,
                            DriveData,ThreshVITH,
                            t[tref]+t[tH1flo]-t[tsuRESETH]-t[loossetup]+dtcf,0);

        WaveSetEdgeStrobe   (H1strobeWF,
                            0ns,
                            t[tref]+t[loosclock],
                            t[tref]+t[loosclock]+7ns);

        WaveSetEdgeStrobe   (H1HIGHstrobeWF,
                            0ns,
                            t[tref]+t[tH1flo]-t[tfHmax],
                            t[tref]+t[tH1flo]-t[tfHmax]+7ns);
        EdgeSetOrigin       (H1HIGHstrobeWF, Edge2, orgtH1high);
        EdgeSetOrigin       (H1HIGHstrobeWF, Edge3, orgtH1high);

        EdgeSet             (H1LOWstrobeWF,Edge1,DriveOff,
                            0ns);
        EdgeSet             (H1LOWstrobeWF,Edge2,EdgeStrobeLow,
                            t[tref]+t[tcH]-t[trHmax]);
        EdgeSet             (H1LOWstrobeWF,Edge3,StrobeLatch,
                            t[tref]+t[tcH]-t[trHmax]+7ns);
        EdgeSetOrigin       (H1LOWstrobeWF, Edge2, orgtH1low);
        EdgeSetOrigin       (H1LOWstrobeWF, Edge3, orgtH1low);

        WaveSetEdgeStrobe   (H1IDLEstrobeWF,
                            0ns,
                            t[tref]+t[tH1flo]+t[loosclock],
                            t[tref]+t[tH1flo]+t[loosclock]+7ns);

        WaveSetEdgeStrobe   (H3strobeWF,
                            0ns,
                            t[tref]+t[loosclock],
                            t[tref]+t[loosclock]+7ns);

        WaveSetEdgeStrobe   (H3LOWstrobeWF,
                            0ns,
                            t[tref]+t[tH3rhi]-t[trHmax],
                            t[tref]+t[tH3rhi]-t[trHmax]+7ns);
        EdgeSetOrigin       (H3LOWstrobeWF, Edge2, orgtH3low);
        EdgeSetOrigin       (H3LOWstrobeWF, Edge3, orgtH3low);

        EdgeSet             (H3HIGHstrobeWF,Edge1,DriveOff,
                            0ns);
        EdgeSet             (H3HIGHstrobeWF,Edge2,EdgeStrobeHigh,
                            t[tref]+t[tcH]+t[tH3flo]-t[tfHmax]);
        EdgeSet             (H3HIGHstrobeWF,Edge3,StrobeLatch,
                            t[tref]+t[tcH]+t[tH3flo]-t[tfHmax]+7ns);
        EdgeSetOrigin       (H3HIGHstrobeWF, Edge2, orgtH3high);
        EdgeSetOrigin       (H3HIGHstrobeWF, Edge3, orgtH3high);

        WaveSetEdgeStrobe   (H3IDLEstrobeWF,
                            0ns,
                            t[tref]+t[tH1flo]+t[loosclock],
                            t[tref]+t[tH1flo]+t[loosclock]+7ns);

        WaveSetEdgeStrobe   (STRBstrobeWF,
                            0ns,
                            t[tref]+t[tH1flo]+t[tdH1LS]+t[loosdelay7]-
                            t[tgb]-ctcf,
                            t[tref]+t[tH1flo]+t[tdH1LS]+t[loosdelay7]-
                            t[tgb]-ctcf+7ns);

        EdgeSetOrigin       (STRBstrobeWF, Edge2, orgtH1flo);
        EdgeSetOrigin       (STRBstrobeWF, Edge3, orgtH1flo);

        WaveSetEdgeStrobe   (RWstrobeWF,
                            0ns,
                            t[tref]+t[tdH1HRW]+t[loosdelay5]-t[tgb]-ctcf,
                            t[tref]+t[tdH1HRW]+t[loosdelay5]-t[tgb]-ctcf+7ns);

        WaveSetEdgeStrobe   (ABUSVstrobeWF,
                            0ns,
                            t[tref]+t[tH1flo]+t[tdH1LA]-t[restrict]-
                            t[loosdelay]+t[tgb]+ctcf+t[tcH]-7ns,
                            t[tref]+t[tH1flo]+t[tdH1LA]-t[restrict]-
                            t[loosdelay]+t[tgb]+ctcf+t[tcH]);
        EdgeSetOrigin       (ABUSVstrobeWF, Edge2, orgtH1flo);
        EdgeSetOrigin       (ABUSVstrobeWF, Edge3, orgtH1flo);

        WaveSetEdgeStrobe   (ABUSstrobeWF,
                            0ns,
                            t[tref]+t[tH1flo]+t[tdH1LA]+t[loosdelay7]+
                            t[loosdelay7]-t[tgb]-ctcf,
                            t[tref]+t[tH1flo]+t[tdH1LA]+t[loosdelay7]+
                            t[loosdelay7]-t[tgb]-ctcf+6ns);

        EdgeSetOrigin       (ABUSstrobeWF, Edge2, orgtH1flo);
        EdgeSetOrigin       (ABUSstrobeWF, Edge3, orgtH1flo);


        WaveSetEdgeStrobe   (ABUSWWstrobeWF,
                            0ns,
                            t[tref]+t[tdH1HA]+t[loosabus]-t[tgb]-ctcf+4ns,
                            t[tref]+t[tdH1HA]+t[loosabus]-t[tgb]-ctcf+3ns);

   

        EdgeSet             (STATstrobeWF,Edge1,StrobeOff,t[tref]+
                            t[tH1flo]+t[tdH1LSTAT]-t[restrict]-t[loosdelay]+
                            t[tgb]+ctcf);
        EdgeSet             (STATstrobeWF,Edge2,StrobeData,t[tref]+
                            t[tH1flo]+t[tdH1LSTAT]+t[loosdelay7]-t[tgb]-ctcf);
        EdgeSetOrigin       (STATstrobeWF, Edge1, orgtH1flo);
        EdgeSetOrigin       (STATstrobeWF, Edge2, orgtH1flo);

        EdgeSet             (LOCKstrobeWF,Edge1,StrobeOff,t[tref]+
                            t[tH1flo]+t[tdH1LLOCK]-t[restrict]-t[loosdelay]+
                            t[tgb]+ctcf);
        EdgeSet             (LOCKstrobeWF,Edge2,StrobeData,t[tref]+
                            t[tH1flo]+t[tdH1LLOCK]+t[loosdelay5]-t[tgb]-ctcf);
        EdgeSetOrigin       (LOCKstrobeWF, Edge1, orgtH1flo);
        EdgeSetOrigin       (LOCKstrobeWF, Edge2, orgtH1flo);

        WaveSetSBC          (DBUSdriveWF,
                            t[tref]+t[tH1flo]-t[tsuDR]-t[loossetup]+dtcf-7ns,
                            t[tref]+t[tH1flo]-t[tsuDR]-t[loossetup]+dtcf,
                            t[tref]+t[tH1flo]+t[thDR]+t[looshold]-dtcf);
        EdgeSetOrigin       (DBUSdriveWF, Edge1, orgtH1flo);
        EdgeSetOrigin       (DBUSdriveWF, Edge2, orgtH1flo);
        EdgeSetOrigin       (DBUSdriveWF, Edge3, orgtH1flo);

	SparePicoSeconds1 := t[loosdelay7];

	(* Take away loose gb for FUJISU Screen because looseDC is used anyway. *)
	(* The highest period for levels test will be 100ns - nomlooseACTable   *)

        EdgeSet             (DBUSstrobeWF,Edge1,DriveOff,t[tref]+
                            t[tH1flo]+t[tvDW]+t[loosdelay7]-t[tgb]-ctcf-
                            t[restrict]-7ns);

        EdgeSet             (DBUSstrobeWF,Edge2,StrobeOff,t[tref]+
                            t[tH1flo]+t[tvDW]+t[loosdelay7]-t[tgb]-ctcf-
                            t[restrict]);

        EdgeSet             (DBUSstrobeWF,Edge3,StrobeData,t[tref]+
                            t[tH1flo]+t[tvDW]+t[loosdelay7]-t[tgb]-ctcf);

        EdgeSetOrigin       (DBUSstrobeWF, Edge1, orgtH1flo);
        EdgeSetOrigin       (DBUSstrobeWF, Edge2, orgtH1flo);
        EdgeSetOrigin       (DBUSstrobeWF, Edge3, orgtH1flo);

        EdgeSet             (DBUSstrobeoffWF,Edge1,StrobeOff,t[tref]+
                            t[thDW]-t[loosdelay]+t[tgb]+ctcf);

(* APS:       EdgeSet            (DBUSWWstrobeWF,Edge1,StrobeOff,t[tref]+ *)
(*                                     t[thDW]-t[loosdelay]+t[tgb]+ctcf); *)
(* APS: duplicated this twice below so the entire definition is in each set *)
(* phq - changed "loosedelay5" to "sp"  7/23/93 *)


	(* Take away loose gb for FUJISU Screen because looseDC is used anyway. *)
	(* The highest period for levels test will be 100ns - nomlooseACTable   *)

START(ALLTABLES,ALLENUMS-SM320C40TAB_pg5x_60MHz);

        EdgeSet            (DBUSWWstrobeWF,Edge1,StrobeOff,t[tref]+
                            t[thDW]-t[loosdelay]+t[tgb]+ctcf);
        EdgeSet          (DBUSWWstrobeWF,Edge2,StrobeData,t[tref]+
                          t[tH1flo]+t[tvDW]+sp-t[tgb]-ctcf+3ns);
        EdgeSetOrigin       (DBUSWWstrobeWF, Edge2, orgtH1flo);

STOP(ALLTABLES,ALLENUMS-SM320C40TAB_pg5x_60MHz);

(*	Added 6ns to Edge2 if DeviceType is  SM320C40TAB_pg5x_60MHz  *)

 	if    (TIDeviceType =  SM320C40TAB_pg5x_60MHz) then 
START(ALLTABLES,ALLTEMPS,ALLTESTS,RUN_SYNC,DONT_RUN_SYNC,SM320C40TAB_pg5x_60MHz);

        EdgeSet            (DBUSWWstrobeWF,Edge1,StrobeOff,t[tref]+
                            t[thDW]-t[loosdelay]+t[tgb]+ctcf);
        EdgeSet          (DBUSWWstrobeWF,Edge2,StrobeData,t[tref]+
                          t[tH1flo]+t[tvDW]+sp-t[tgb]-ctcf+6ns);
        EdgeSetOrigin       (DBUSWWstrobeWF, Edge2, orgtH1flo);

STOP(ALLTABLES,ALLTEMPS,ALLTESTS,RUN_SYNC,DONT_RUN_SYNC,SM320C40TAB_pg5x_60MHz);

(* APS        EdgeSetOrigin       (DBUSWWstrobeWF, Edge2, orgtH1flo); *)
(* APS: duplicated this twice below so the entire definition is in each set *)

	(* New waveform - see comment at top for usage.    PHQ    8/12/93 *) 
        (* No loose gb for StrobeData edge to guarantee at least 10ns window *)

	(* Calculation for edge placement so that edge rule is not violated *)
	(* StrobeOn-StrobeOff must be at least 3ns.			    *)
	(* This edge will follow either StrobeData edge of DBUSstrobeWF or  *)
	(* DBUSWWstrobeWF.				   PHQ    8/13/93   *)

	SparePicoSeconds3 := t[tref]+t[tH1flo]+t[tvDW]+sp-t[tgb]-ctcf;
			     (* StrobeData edge of DBUSstrobeWF or DBUSWWstrobeWF *)
	if(SparePicoSeconds3 > t[tcH]) then
	   (* Going over next cycle *)
	   SparePicoSeconds2 := (SparePicoSeconds3 - t[tcH]) + 4ns
	else
	  SparePicoSeconds2 := 4ns;

        EdgeSet             (DBUSWW2strobeWF, Edge1, StrobeOff,
	           	     + SparePicoSeconds2);

        EdgeSet             (DBUSWW2strobeWF,Edge2,StrobeData,t[tref]+
                            t[tH1flo]-t[tsuDR2]-ctcf);


        EdgeSetOrigin       (DBUSWW2strobeWF, Edge2, orgtH1flo);


        WaveSetRTO          (RDYdriveWF,
                            t[tref]+t[tH1flo]-t[tsuRDY]-t[loossetup]+dtcf,
                            t[tref]+t[tH1flo]+t[thRDY]+t[looshold]-dtcf);
        EdgeSetOrigin       (RDYdriveWF, Edge1, orgtH1flo);
        EdgeSetOrigin       (RDYdriveWF, Edge2, orgtH1flo);

        WaveSetNR           (ENBdriveWF,
                            t[tref]+t[tENB]);

        WaveSetStrobeZ      (DBUSHIZstrobeWF,
                            0ns,
                            t[tref]+t[tENB]+t[tdENBZ]+t[loosdelay]-ctcf,
                            t[tref]+t[tENB]+t[tdENBZ]+t[loosdelay]+7ns+ctcf);

        WaveSetEdgeStrobeZ  (ABUSHIZstrobeWF,
                            0ns,
                            t[tref]+t[tENB]+t[tdENBZ]+t[loosdelay]-ctcf,
                            t[tref]+t[tENB]+t[tdENBZ]+t[loosdelay]-ctcf+7ns);

        WaveSetEdgeStrobeZ  (CTRLHIZstrobeWF,
                            0ns,
                            t[tref]+t[tENB]+t[tdENBZ]+t[loosdelay]-ctcf,
                            t[tref]+t[tENB]+t[tdENBZ]+t[loosdelay]-ctcf+7ns);

        EdgeSet             (DBUSVALstrobeWF,Edge1,StrobeOff,t[tref]+
                            t[tENB]+t[tdENBDV]-t[restrict]-t[loosdelay]+
                            t[tgb]+ctcf);
        EdgeSet             (DBUSVALstrobeWF,Edge2,StrobeData,t[tref]+
                            t[tENB]+t[tdENBDV]+t[loosdelay7]-t[tgb]-ctcf);

(* phq - Changed "loosedelay7" to "sp"  8/6/93 *)
        WaveSetEdgeStrobe   (ABUSVALstrobeWF,
                            0ns,
                            t[tref]+t[tENB]+t[tdENBAV]+sp-
                            t[tgb]-ctcf+0ns,
                            t[tref]+t[tENB]+t[tdENBAV]+sp-
                            t[tgb]-ctcf+6ns);

        WaveSetEdgeStrobe   (CTRLVALstrobeWF,
                            0ns,
                            t[tref]+t[tENB]+t[tdENBCV]+t[loosdelay]-
                            t[tgb]-ctcf,
                            t[tref]+t[tENB]+t[tdENBCV]+t[loosdelay]-
                            t[tgb]-ctcf+6ns);


        WaveSetSBC          (IIOFdriveWF,
                            t[tref]+t[tH1flo]-t[tsuIF]-t[loossetup]+dtcf-7ns,
                            t[tref]+t[tH1flo]-t[tsuIF]-t[loossetup]+dtcf,
                            t[tref]+t[tH1flo]+t[thIF]+t[looshold]-dtcf);
        EdgeSetOrigin       (IIOFdriveWF, Edge1, orgtH1flo);
        EdgeSetOrigin       (IIOFdriveWF, Edge2, orgtH1flo);
        EdgeSetOrigin       (IIOFdriveWF, Edge3, orgtH1flo);

        EdgeSet             (IIOFstrobeWF,Edge1,DriveOff,t[tref]+
                            t[tH1flo]+t[tvH1LIF]+t[loosdelay]-t[tgb]-ctcf-7ns);
        EdgeSet             (IIOFstrobeWF,Edge2,StrobeData,t[tref]+
                            t[tH1flo]+t[tvH1LIF]+t[loosdelay]-t[tgb]-ctcf);
        EdgeSetOrigin       (IIOFstrobeWF, Edge1, orgtH1flo);
        EdgeSetOrigin       (IIOFstrobeWF, Edge2, orgtH1flo);

        EdgeSet             (IIOFstrobeoffWF,Edge1,StrobeOff,t[tref]+
                            t[tH1flo]+t[thH1LIFOI]-t[loosdelay]+t[tgb]+ctcf-1ns);
        EdgeSetOrigin       (IIOFstrobeoffWF, Edge1, orgtH1flo);

        EdgeSet             (IIOFWWstrobeWF,Edge1,StrobeOff,t[tref]+
                            t[tH1flo]+t[tvH1LIF]-t[restrict]-t[loosdelay5]+
                            t[tgb]+ctcf);
        EdgeSet             (IIOFWWstrobeWF,Edge2,StrobeData,t[tref]+
                            t[tH1flo]+t[tvH1LIF]+t[loosdelay5]-t[tgb]-ctcf);
        EdgeSetOrigin       (IIOFWWstrobeWF, Edge1, orgtH1flo);
        EdgeSetOrigin       (IIOFWWstrobeWF, Edge2, orgtH1flo);

        WaveSetNR           (INTdriveWF,
                            t[tref]+t[tH1flo]-t[tsuINT]-t[loossetup]+dtcf);
        EdgeSetOrigin       (INTdriveWF, Edge1, orgtH1flo);

        WaveSetNR           (INTIDLEdriveWF,
                            t[tref]+t[tH1flo]-t[tsuINTIDLE]-t[loossetup]+dtcf);
        EdgeSetOrigin       (INTdriveWF, Edge1, orgtH1flo);

        EdgeSet             (IACKstrobeWF,Edge1,StrobeOff,t[tref]+
                            t[tH1flo]+t[tdH1LIACK]-t[restrict]-t[loosdelay]+
                            t[tgb]+ctcf);
        EdgeSet             (IACKstrobeWF,Edge2,StrobeData,t[tref]+
                            t[tH1flo]+t[tdH1LIACK]+t[loosdelay6]-t[tgb]-ctcf);
        EdgeSetOrigin       (IACKstrobeWF, Edge1, orgtH1flo);
        EdgeSetOrigin       (IACKstrobeWF, Edge2, orgtH1flo);


        EdgeSetDelayData    (CREQdriveWF,Edge1,ChanFirst,
                            DriveData,ThreshVITL,
                            t[tref]+t[tH1flo]-t[tsuCREQ],0,
                            DriveData,ThreshVITH,
                            t[tref]+t[tH1flo]+t[tsuCREQ],0);

        EdgeSetDelayData    (CREQstrobeWF,Edge1,ChanFirst,
                            DriveOff,ThreshVITL,t[tref]+
                            t[tdH1HRQLt]+t[loosdelay]-t[tgb]-ctcf-7ns,0,
                            DriveOff,ThreshVITH,t[tref]+
                            t[tH1flo]-t[tsuCACK]+t[tdALRQHt]+
                            t[loosdelay]-t[tgb]-ctcf-7ns,0);
        EdgeSetDelayData    (CREQstrobeWF,Edge2,ChanFirst,
                            StrobeData,ThreshVITL,t[tref]+
                            t[tdH1HRQLt]+t[loosdelay]-t[tgb]-ctcf,0,
                            StrobeData,ThreshVITH,t[tref]+
                            t[tH1flo]-t[tsuCACK]+t[tdALRQHt]+
                            t[loosdelay]-t[tgb]-ctcf,0);
        EdgeSetDelayData    (CREQstrobeWF,Edge3,ChanFirst,
                            StrobeOff,ThreshVITL,t[tref]+
                            t[tdH1HRQLt]+t[loosdelay]-t[tgb]-ctcf+7ns,0,
                            StrobeOff,ThreshVITH,t[tref]+
                            t[tH1flo]-t[tsuCACK]+t[tdALRQHt]+
                            t[loosdelay]-t[tgb]-ctcf+7ns,0);

        EdgeSetDelayData    (CREQ2strobeWF,Edge1,ChanFirst,
                            DriveOff,ThreshVITL,t[tref]+
                            t[tH1flo]+t[tsuCREQ]+t[tdRQHRQLt]+
                            t[loosdelay]-t[tgb]-ctcf-7ns,0,
                            DriveOff,ThreshVITH,t[tref]+
                            t[tH1flo]+t[tsuCREQ]+t[tdRQHRQOt]+
                            t[loosdelay]-t[tgb]-ctcf-7ns,0);
        EdgeSetDelayData    (CREQ2strobeWF,Edge2,ChanFirst,
                            StrobeData,ThreshVITL,t[tref]+
                            t[tH1flo]+t[tsuCREQ]+t[tdRQHRQLt]+
                            t[loosdelay]-t[tgb]-ctcf,0,
                            StrobeData,ThreshVITH,t[tref]+
                            t[tH1flo]+t[tsuCREQ]+t[tdRQHRQOt]+
                            t[loosdelay]-t[tgb]-ctcf,0);
        EdgeSetDelayData    (CREQ2strobeWF,Edge3,ChanFirst,
                            StrobeOff,ThreshVITL,t[tref]+
                            t[tH1flo]+t[tsuCREQ]+t[tdRQHRQLt]+
                            t[loosdelay]-t[tgb]-ctcf+7ns,0,
                            StrobeOff,ThreshVITH,t[tref]+
                            t[tH1flo]+t[tsuCREQ]+t[tdRQHRQOt]+
                            t[loosdelay]-t[tgb]-ctcf+7ns,0);

        WaveSetNR           (CACKdriveWF,
                            t[tref]+t[tH1flo]-t[tsuCACK]);
        EdgeSetOrigin       (CACKdriveWF, Edge1, orgtH1flo);


(* phq - Changed "loosdelay7" to "sp" *)

        WaveSetStrobe       (CACKstrobeWF,
                            t[tref]+t[tH1flo]-t[tsuCREQ]+t[tdRQLALt]+
                            sp-t[tgb]-ctcf-7ns,
                            t[tref]+t[tH1flo]-t[tsuCREQ]+t[tdRQLALt]+
                            sp-t[tgb]-ctcf,
                            t[tref]+t[tH1flo]-t[tsuCREQ]+t[tdRQLALt]+
                            sp-t[tgb]-ctcf+7ns);

        EdgeSetOrigin       (CACKstrobeWF, Edge1, orgtH1flo);
        EdgeSetOrigin       (CACKstrobeWF, Edge2, orgtH1flo);
        EdgeSetOrigin       (CACKstrobeWF, Edge3, orgtH1flo);

(* CRDY  Edge1 is defined as DriveData here, but in actuality should always   *)
(* end up being a drive-low edge based on pattern data and translation.       *)

  if ( ((actable = TIlofrqlooseACTable )or(actable = TInomlooseACTable)) and 
   ((TIDeviceType = SM320C40TAB_pg5x_40MHz)or  (*EGM: to reduce noise on C4DX*)
    (TIDeviceType = SM320C40TAB_pg5x_50MHz)or
    (TIDeviceType = SM320C40TAB_pg5x_60MHz)or
    (TIDeviceType = TMS320C40TAL_pg5x_60MHz)) ) then
START(ALLTEMPS,ALLTESTS,RUN_SYNC,DONT_RUN_SYNC,TIlofrqlooseACTable,TInomlooseACTable,SM320C40TAB_pg5x_40MHz,SM320C40TAB_pg5x_50MHz,SM320C40TAB_pg5x_60MHz,TMS320C40TAL_pg5x_60MHz);
    WaveSetRTO          (CRDYdriveWF, t[tCRDYLO], t[tCRDYHI]+2ns);
STOP(ALLTEMPS,ALLTESTS,RUN_SYNC,DONT_RUN_SYNC,TIlofrqlooseACTable,TInomlooseACTable,SM320C40TAB_pg5x_40MHz,SM320C40TAB_pg5x_50MHz,SM320C40TAB_pg5x_60MHz,TMS320C40TAL_pg5x_60MHz);

  else   
START(ALLTEMPS,ALLTESTS,RUN_SYNC,DONT_RUN_SYNC,TIstressminACTable,TIstressmaxACTable,TIlofrqloose60ACTable,TIhifrqloose50ACTable,TIhifrqloose60ACTable,TIsearchlevelsACTable,SM320C40TAB_pg5x_40MHz,SM320C40TAB_pg5x_50MHz,SM320C40TAB_pg5x_60MHz,TMS320C40TAL_pg5x_60MHz);
    WaveSetRTO          (CRDYdriveWF, t[tCRDYLO], t[tCRDYHI]); 
STOP(ALLTEMPS,ALLTESTS,RUN_SYNC,DONT_RUN_SYNC,TIstressminACTable,TIstressmaxACTable,TIlofrqloose60ACTable,TIhifrqloose50ACTable,TIhifrqloose60ACTable,TIsearchlevelsACTable,SM320C40TAB_pg5x_40MHz,SM320C40TAB_pg5x_50MHz,SM320C40TAB_pg5x_60MHz,TMS320C40TAL_pg5x_60MHz);
(* APS: prior line covers same device list, but other actables *)
(* APS: next line covers remainder device list, and all valid/case actables *)
START(ALLTEMPS,ALLTESTS,RUN_SYNC,DONT_RUN_SYNC,TIlofrqlooseACTable,TInomlooseACTable,TIstressminACTable,TIstressmaxACTable,TIlofrqloose60ACTable,TIhifrqloose50ACTable,TIhifrqloose60ACTable,TIsearchlevelsACTable,ALLDEVICES-SM320C40TAB_pg5x_40MHz-SM320C40TAB_pg5x_50MHz-SM320C40TAB_pg5x_60MHz-TMS320C40TAL_pg5x_60MHz);
    WaveSetRTO          (CRDYdriveWF, t[tCRDYLO], t[tCRDYHI]); 
STOP(ALLTEMPS,ALLTESTS,RUN_SYNC,DONT_RUN_SYNC,TIlofrqlooseACTable,TInomlooseACTable,TIstressminACTable,TIstressmaxACTable,TIlofrqloose60ACTable,TIhifrqloose50ACTable,TIhifrqloose60ACTable,TIsearchlevelsACTable,ALLDEVICES-SM320C40TAB_pg5x_40MHz-SM320C40TAB_pg5x_50MHz-SM320C40TAB_pg5x_60MHz-TMS320C40TAL_pg5x_60MHz);

(* special cstrb_ strobe w/o origin used for sync-up only to avoid problems   *)
(* with bsearch.                                                              *)

        WaveSetStrobe       (CSTRB_SYNCstrobeWF,
                            t[tCRDYHI]-t[tcH]+t[tdRHSLw]-7ns,
                            t[tCRDYHI]-t[tcH]+t[tdRHSLw],
                            t[tCRDYHI]-t[tcH]+t[tdRHSLw]+7ns);

        EdgeSetDelayData    (CSTRBstrobeWF,Edge1,ChanFirst,
                            DriveOff,ThreshVITL,t[tCRDYHI]-t[tcH]+
                            t[tdRHSLw]+t[loosdelay7]-t[tgb]-ctcf-7ns,0,
                            DriveOff,ThreshVITH,t[tCRDYLO]+
                            t[tdRLSHw]+t[loosdelay]-t[tgb]-ctcf-7ns,0);
        EdgeSetDelayData    (CSTRBstrobeWF,Edge2,ChanFirst,
                            StrobeData,ThreshVITL,t[tCRDYHI]-t[tcH]+
                            t[tdRHSLw]+t[loosdelay7]-t[tgb]-ctcf,0,
                            StrobeData,ThreshVITH,t[tCRDYLO]+
                            t[tdRLSHw]+t[loosdelay]-t[tgb]-ctcf,0);
        EdgeSetDelayData    (CSTRBstrobeWF,Edge3,ChanFirst,
                            StrobeOff,ThreshVITL,t[tCRDYHI]-t[tcH]+
                            t[tdRHSLw]+t[loosdelay7]-t[tgb]-ctcf+7ns,0,
                            StrobeOff,ThreshVITH,t[tCRDYLO]+
                            t[tdRLSHw]+t[loosdelay]-t[tgb]-ctcf+7ns,0);

        WaveSetStrobe       (CDstrobeWF,
                            t[tref]+t[tCSTRBfhi]-t[tsuCDw]+
                            t[loosdelay7]-t[tgb]-ctcf-7ns,
                            t[tref]+t[tCSTRBfhi]-t[tsuCDw]+
                            t[loosdelay7]-t[tgb]-ctcf,
                            t[tCRDYLO]+t[thCDw]-t[loosdelay7]+t[tgb]+ctcf);
        EdgeSetOrigin       (CDstrobeWF, Edge1, orgtCSTRBfhi);
        EdgeSetOrigin       (CDstrobeWF, Edge2, orgtCSTRBfhi);

(* CSTRB Edge1 is defined as DriveData here, but in actuality should always   *)
(* end up being a drive-low edge based on pattern data and translation.       *)
   (*EGM: to reduce noise on CACK5_*)
   if ( ((actable = TIlofrqlooseACTable )or(actable = TInomlooseACTable)) and 
    ((TIDeviceType = SM320C40TAB_pg5x_40MHz)or
     (TIDeviceType = SM320C40TAB_pg5x_50MHz)or
     (TIDeviceType = SM320C40TAB_pg5x_60MHz)or
     (TIDeviceType = TMS320C40TAL_pg5x_60MHz)) ) then
START(ALLTEMPS,ALLTESTS,RUN_SYNC,DONT_RUN_SYNC,TIlofrqlooseACTable,TInomlooseACTable,SM320C40TAB_pg5x_40MHz,SM320C40TAB_pg5x_50MHz,SM320C40TAB_pg5x_60MHz,TMS320C40TAL_pg5x_60MHz);
        WaveSetRTO          (CSTRBdriveWF, t[tCSTRBLO], t[tCSTRBHI]-2ns)
STOP(ALLTEMPS,ALLTESTS,RUN_SYNC,DONT_RUN_SYNC,TIlofrqlooseACTable,TInomlooseACTable,SM320C40TAB_pg5x_40MHz,SM320C40TAB_pg5x_50MHz,SM320C40TAB_pg5x_60MHz,TMS320C40TAL_pg5x_60MHz);
   else
START(ALLTEMPS,ALLTESTS,RUN_SYNC,DONT_RUN_SYNC,TIstressminACTable,TIstressmaxACTable,TIlofrqloose60ACTable,TIhifrqloose50ACTable,TIhifrqloose60ACTable,TIsearchlevelsACTable,SM320C40TAB_pg5x_40MHz,SM320C40TAB_pg5x_50MHz,SM320C40TAB_pg5x_60MHz,TMS320C40TAL_pg5x_60MHz);
        WaveSetRTO          (CSTRBdriveWF, t[tCSTRBLO], t[tCSTRBHI]);
STOP(ALLTEMPS,ALLTESTS,RUN_SYNC,DONT_RUN_SYNC,TIstressminACTable,TIstressmaxACTable,TIlofrqloose60ACTable,TIhifrqloose50ACTable,TIhifrqloose60ACTable,TIsearchlevelsACTable,SM320C40TAB_pg5x_40MHz,SM320C40TAB_pg5x_50MHz,SM320C40TAB_pg5x_60MHz,TMS320C40TAL_pg5x_60MHz);
(* APS: prior line covers same device list and remainder of case category *)
(* APS: next line covers remainder device list filtered actables *)
START(ALLTEMPS,ALLTESTS,RUN_SYNC,DONT_RUN_SYNC,TIlofrqlooseACTable,TInomlooseACTable,ALLDEVICES-SM320C40TAB_pg5x_40MHz-SM320C40TAB_pg5x_50MHz-SM320C40TAB_pg5x_60MHz-TMS320C40TAL_pg5x_60MHz);
        WaveSetRTO          (CSTRBdriveWF, t[tCSTRBLO], t[tCSTRBHI]);
STOP(ALLTEMPS,ALLTESTS,RUN_SYNC,DONT_RUN_SYNC,TIlofrqlooseACTable,TInomlooseACTable,ALLDEVICES-SM320C40TAB_pg5x_40MHz-SM320C40TAB_pg5x_50MHz-SM320C40TAB_pg5x_60MHz-TMS320C40TAL_pg5x_60MHz);

        EdgeSetOrigin       (CSTRBdriveWF, Edge1, orgtCSTRBfhi);
        EdgeSetOrigin       (CSTRBdriveWF, Edge2, orgtCSTRBfhi);

        WaveSetStrobe       (CRDY_SYNCstrobeWF,          (*special crdy_  strobe*)
                            t[tCSTRBLO]+t[tdSLRLr]-7ns,  (*w/o origin used for  *)
                            t[tCSTRBLO]+t[tdSLRLr],      (*sync-up only to avoid*)
                            t[tCSTRBLO]+t[tdSLRLr]+7ns); (*problems with bsearch*)

        EdgeSetDelayData    (CRDYstrobeWF,Edge1,ChanFirst,
                            DriveOff,ThreshVITL,t[tCSTRBLO]+
                            t[tdSLRLr]+t[loosdelay4]-t[tgb]-ctcf-7ns,0,
                            DriveOff,ThreshVITH,t[tCSTRBHI]+
                            t[tdSHRHr]+t[loosdelay]-t[tgb]-ctcf-7ns,0);

(* phq - Changed from loosedelay5 to sp   7/31/93 *)

        EdgeSetDelayData    (CRDYstrobeWF,Edge2,ChanFirst,
                            StrobeData,ThreshVITL,t[tCSTRBLO]+
                            t[tdSLRLr]+sp-t[tgb]-ctcf,0,
                            StrobeData,ThreshVITH,t[tCSTRBHI]+
                            t[tdSHRHr]+t[loosdelay]-t[tgb]-ctcf,0);
        EdgeSetDelayData    (CRDYstrobeWF,Edge3,ChanFirst,
                            StrobeOff,ThreshVITL,t[tCSTRBLO]+
                            t[tdSLRLr]+sp-t[tgb]-ctcf+7ns,0,
                            StrobeOff,ThreshVITH,t[tCSTRBHI]+
                            t[tdSHRHr]+t[loosdelay]-t[tgb]-ctcf+7ns,0);

        EdgeSetDelayData    (CDdriveWF,Edge1,ChanFirst,
                            DriveComplement,ThreshVITL,t[tCSTRBLO]-
                            t[tsuCDr]-t[loossetup]+dtcf-7ns,0,
                            DriveComplement,ThreshVITH,t[tCSTRBLO]-
                            t[tsuCDr]-t[looscd]-t[loossetup]+dtcf-7ns,0);
        EdgeSetDelayData    (CDdriveWF,Edge2,ChanFirst,
                            DriveData,ThreshVITL,t[tCSTRBLO]-
                            t[tsuCDr]-t[loossetup]+dtcf,0,
                            DriveData,ThreshVITH,t[tCSTRBLO]-
                            t[tsuCDr]-t[looscd]-t[loossetup]+dtcf,0);
        EdgeSetDelayData    (CDdriveWF,Edge3,ChanFirst,
                            DriveComplement,ThreshVITL,t[tref]+t[tCRDYflo]+
                            t[thCDr]+t[looscd]+t[looshold]-dtcf,0,
                            DriveComplement,ThreshVITH,t[tref]+t[tCRDYflo]+
                            t[thCDr]+t[looshold]-dtcf,0);


        WaveSetSBC          (TCLKdriveWF,
                            t[tref]+t[tH1flo]-t[tsuTCLK]-t[loossetup]+dtcf-7ns,
                            t[tref]+t[tH1flo]-t[tsuTCLK]-t[loossetup]+dtcf,
                            t[tref]+t[tH1flo]+t[thTCLK]+t[looshold]-dtcf);
        EdgeSetOrigin       (TCLKdriveWF, Edge1, orgtH1flo);
        EdgeSetOrigin       (TCLKdriveWF, Edge2, orgtH1flo);
        EdgeSetOrigin       (TCLKdriveWF, Edge3, orgtH1flo);

        WaveSetStrobe       (TCLKstrobeWF,
                            t[tref]+t[tdTCLK]+t[loosdelay6]-t[tgb]-ctcf-7ns,
                            t[tref]+t[tdTCLK]+t[loosdelay6]-t[tgb]-ctcf,
                            t[tref]+t[tdTCLK]+t[tcH]-t[restrict]-t[loosdelay]+
                            t[tgb]+ctcf);


        WaveSetRTO          (TCKCLKdriveWF,
                            t[tref],
                            t[tref]+t[tcCI]);

        WaveSetNR           (TCKdriveWF,
                            t[tref]);

        WaveSetSBC          (TDITMSdriveWF,
                            t[tref]+t[tcCI]-t[tsuTDITMS]-t[loossetup]+dtcf-7ns,
                            t[tref]+t[tcCI]-t[tsuTDITMS]-t[loossetup]+dtcf,
                            t[tref]+t[tcCI]+t[thTDITMS]+t[looshold]-dtcf);

        WaveSetNR           (JTAGdriveWF,
                            t[tref]+t[tJTAG]);

        WaveSetStrobe       (TDOstrobeWF,
                            0ns,
                            t[tref]+t[tdTDO]+t[loosdelay]-t[tgb]-ctcf,
                            t[tref]+t[tdTDO]+t[loosdelay]-t[tgb]-ctcf+7ns);

        WaveSetEdgeStrobe   (JTAGH1strobeWF,
                            0ns,
                            t[tref]+t[tdTDO]+t[tcCI]+t[loosdelay]-t[tgb]-ctcf,
                            t[tref]+t[tdTDO]+t[tcCI]+t[loosdelay]-t[tgb]-ctcf+7ns);

        WaveSetEdgeStrobe   (JTAGVARYstrobeWF,
                            0ns,
                            t[tref]+t[tdTDO]+t[tcCI]+t[loosdelay]-t[tgb]-ctcf,
                            t[tref]+t[tdTDO]+t[tcCI]+t[loosdelay]-t[tgb]-ctcf+7ns);

        EdgeSet             (JTAGABUSstrobeWF,Edge1,StrobeOff,t[tref]+
                            t[tdTDO]-t[restrict]-t[loosdelay]+t[tgb]+ctcf);
        EdgeSet             (JTAGABUSstrobeWF,Edge2,DriveOff,t[tref]+
                            t[tdTDO]-t[restrict]-t[loosdelay]+t[tgb]+ctcf);
        EdgeSet             (JTAGABUSstrobeWF,Edge3,StrobeData,t[tref]+
                            t[tdTDO]+t[tcCI]+t[loosdelay]-t[tgb]-ctcf);

        WaveSetNR           (EMUdriveWF,
                            t[tref]+t[tEMU]);

        WaveSetStrobe       (EMUstrobeWF,
                            0ns,
                            t[tref]+t[tdEMU]+t[loosdelay]-t[tgb]-ctcf,
                            t[tref]+t[tdEMU]+t[loosdelay]-t[tgb]-ctcf+7ns);


        WaveSetNR           (RESETLOCdriveWF,
                            t[tref]+t[tRESETLOC]);

        WaveSetNR           (ROMENdriveWF,
                            t[tref]+t[tROMEN]);

        WaveSetNR           (NMIdriveWF,
                            t[tref]+t[tNMI]);


        WaveSetContinue     (ContinueWF);

        WaveSetOff          (ALLoffWF,t[tref],t[tref]);

STOP(ALLENUMS,TInomlooseACTable,TIstressminACTable,TIstressmaxACTable,TIlofrqlooseACTable,TIlofrqloose60ACTable,TIhifrqloose50ACTable,TIhifrqloose60ACTable,TIsearchlevelsACTable);

          end; (*2nd case*)

(* BB 9/29/93 40ns tables set separately to eliminate edge collisions. *)
        TIhifrqmin33ACTable,
        TIhifrqmax33ACTable,
        TIhifrqmin40ACTable,
        TIhifrqmax40ACTable,
        TIsearch40ACTable,
        TIchar33ACTable,
        TIchar40ACTable:
          begin

START(ALLENUMS,TIhifrqmin33ACTable,TIhifrqmax33ACTable,TIhifrqmin40ACTable,TIhifrqmax40ACTable,TIsearch40ACTable,TIchar33ACTable,TIchar40ACTable);

        WaveSetDoubleClk    (CLKINdriveWF,
                            t[tref]+t[toffset],
                            t[tref]+t[toffset]+t[twCIH],
                            t[tref]+t[toffset]+t[twCIH]+t[twCIL],
                            t[tref]+t[toffset]+t[twCIH]+t[twCIL]+t[twCIH]);
        EdgeSetOrigin       (CLKINdriveWF, Edge1, orgtoffset);
        EdgeSetOrigin       (CLKINdriveWF, Edge2, orgtoffset);
        EdgeSetOrigin       (CLKINdriveWF, Edge3, orgtoffset);
        EdgeSetOrigin       (CLKINdriveWF, Edge4, orgtoffset);

        EdgeSetDelayData    (RESETdriveWF,Edge1,ChanFirst,
                            DriveData,ThreshVITL,
                            t[tref]+t[toffset]+t[twCIH]+t[twCIL]+t[twCIH]-t[tsuRESET]-t[loossetup]+dtcf,0,
                            DriveData,ThreshVITH,
                            t[tref]+t[tH1flo]-t[tsuRESETH]-t[loossetup]+dtcf,0);

        WaveSetEdgeStrobe   (H1strobeWF,
                            0ns,
                            t[tref]+t[loosclock],
                            t[tref]+t[loosclock]+7ns);

        WaveSetEdgeStrobe   (H1HIGHstrobeWF,
                            0ns,
                            t[tref]+t[tH1flo]-t[tfHmax],
                            t[tref]+t[tH1flo]-t[tfHmax]+7ns);
        EdgeSetOrigin       (H1HIGHstrobeWF, Edge2, orgtH1high);
        EdgeSetOrigin       (H1HIGHstrobeWF, Edge3, orgtH1high);

        EdgeSet             (H1LOWstrobeWF,Edge1,DriveOff,
                            0ns);
        EdgeSet             (H1LOWstrobeWF,Edge2,EdgeStrobeLow,
                            t[tref]+t[tcH]-t[trHmax]);
        EdgeSet             (H1LOWstrobeWF,Edge3,StrobeLatch,
                            t[tref]+t[tcH]-t[trHmax]+7ns);
        EdgeSetOrigin       (H1LOWstrobeWF, Edge2, orgtH1low);
        EdgeSetOrigin       (H1LOWstrobeWF, Edge3, orgtH1low);

        WaveSetEdgeStrobe   (H1IDLEstrobeWF,
                            0ns,
                            t[tref]+t[tH1flo]+t[loosclock],
                            t[tref]+t[tH1flo]+t[loosclock]+7ns);

        WaveSetEdgeStrobe   (H3strobeWF,
                            0ns,
                            t[tref]+t[loosclock],
                            t[tref]+t[loosclock]+7ns);

        WaveSetEdgeStrobe   (H3LOWstrobeWF,
                            0ns,
                            t[tref]+t[tH3rhi]-t[trHmax],
                            t[tref]+t[tH3rhi]-t[trHmax]+7ns);
        EdgeSetOrigin       (H3LOWstrobeWF, Edge2, orgtH3low);
        EdgeSetOrigin       (H3LOWstrobeWF, Edge3, orgtH3low);

        EdgeSet             (H3HIGHstrobeWF,Edge1,DriveOff,
                            0ns);
        EdgeSet             (H3HIGHstrobeWF,Edge2,EdgeStrobeHigh,
                            t[tref]+t[tcH]+t[tH3flo]-t[tfHmax]);
        EdgeSet             (H3HIGHstrobeWF,Edge3,StrobeLatch,
                            t[tref]+t[tcH]+t[tH3flo]-t[tfHmax]+7ns);
        EdgeSetOrigin       (H3HIGHstrobeWF, Edge2, orgtH3high);
        EdgeSetOrigin       (H3HIGHstrobeWF, Edge3, orgtH3high);

        WaveSetEdgeStrobe   (H3IDLEstrobeWF,
                            0ns,
                            t[tref]+t[tH1flo]+t[loosclock],
                            t[tref]+t[tH1flo]+t[loosclock]+7ns);

        EdgeSet             (STRBstrobeWF,Edge1,StrobeOff,t[tref]+
                            t[tH1flo]+t[tdH1LS]-t[restrict]-t[loosdelay]+
                            t[tgb]+ctcf);

        (* bb 7/8/96 Changed so that VOH does not have 1ns tgb *)
        EdgeSetDelayData    (STRBstrobeWF,Edge2,ChanFirst,
                            StrobeData,ThreshVITL,
                            t[tref]+t[tH1flo]+t[tdH1LS]+t[loosdelay7]-t[tgb]-ctcf,0,
                            StrobeData,ThreshVITH,
                            t[tref]+t[tH1flo]+t[tdH1LS]+t[loosdelay7]-ctcf,0);
   
        EdgeSetOrigin       (STRBstrobeWF, Edge1, orgtH1flo);
        EdgeSetOrigin       (STRBstrobeWF, Edge2, orgtH1flo);

        EdgeSet             (RWstrobeWF,Edge1,StrobeOff,t[tref]+
                            t[tdH1HRW]-t[restrict]-t[loosdelay]+t[tgb]+ctcf);
        EdgeSet             (RWstrobeWF,Edge2,StrobeData,t[tref]+
                            t[tdH1HRW]+t[loosdelay5]-t[tgb]-ctcf);

        EdgeSet             (ABUSVstrobeWF,Edge1,StrobeOff,t[tref]+
                            t[tH1flo]+t[tdH1LA]-2*t[restrict]-t[loosdelay]+
                            t[tgb]+ctcf+t[tcH]-7ns);
        EdgeSet             (ABUSVstrobeWF,Edge2,StrobeData,t[tref]+
                            t[tH1flo]+t[tdH1LA]-t[restrict]-t[loosdelay]+
                            t[tgb]+ctcf+t[tcH]-7ns);
        EdgeSetOrigin       (ABUSVstrobeWF, Edge1, orgtH1flo);
        EdgeSetOrigin       (ABUSVstrobeWF, Edge2, orgtH1flo);

        EdgeSet             (ABUSstrobeWF,Edge1,StrobeOff,t[tref]+
                            t[tH1flo]+t[tdH1LA]-t[restrict]-t[loosdelay]+
                            t[tgb]+ctcf);

        (* bb 7/8/96 Changed so that VOH does not have 1ns tgb *)
        EdgeSetDelayData    (ABUSstrobeWF,Edge2,ChanFirst,
                            StrobeData,ThreshVITL,
                            t[tref]+t[tH1flo]+t[tdH1LA]+t[loosdelay7]-t[tgb]-ctcf,0,
                            StrobeData,ThreshVITH,
                            t[tref]+t[tH1flo]+t[tdH1LA]+t[loosdelay7]-ctcf,0);
  
        EdgeSetOrigin       (ABUSstrobeWF, Edge1, orgtH1flo);
        EdgeSetOrigin       (ABUSstrobeWF, Edge2, orgtH1flo);

        EdgeSet             (ABUSWWstrobeWF,Edge1,StrobeOff,t[tref]+
                             t[tdH1HA]-t[restrict]-t[loosabus]+t[tgb]+ctcf);

        EdgeSet             (ABUSWWstrobeWF,Edge2,StrobeData,t[tref]+
                            t[tdH1HA]+t[loosabus]-t[tgb]-ctcf);

        EdgeSet             (STATstrobeWF,Edge1,StrobeOff,t[tref]+
                            t[tH1flo]+t[tdH1LSTAT]-t[restrict]-t[loosdelay]+
                            t[tgb]+ctcf);

        (* bb 7/8/96 Changed so that VOH does not have 1ns tgb *)
        EdgeSetDelayData    (STATstrobeWF,Edge2,ChanFirst,
                            StrobeData,ThreshVITL,
                            t[tref]+t[tH1flo]+t[tdH1LSTAT]+t[loosdelay7]-t[tgb]-ctcf,0,
                            StrobeData,ThreshVITH,
                            t[tref]+t[tH1flo]+t[tdH1LSTAT]+t[loosdelay7]-ctcf,0);
 
        EdgeSetOrigin       (STATstrobeWF, Edge1, orgtH1flo);
        EdgeSetOrigin       (STATstrobeWF, Edge2, orgtH1flo);

        EdgeSet             (LOCKstrobeWF,Edge1,StrobeOff,t[tref]+
                            t[tH1flo]+t[tdH1LLOCK]-t[restrict]-t[loosdelay]+
                            t[tgb]+ctcf);
        EdgeSet             (LOCKstrobeWF,Edge2,StrobeData,t[tref]+
                            t[tH1flo]+t[tdH1LLOCK]+t[loosdelay5]-t[tgb]-ctcf);
        EdgeSetOrigin       (LOCKstrobeWF, Edge1, orgtH1flo);
        EdgeSetOrigin       (LOCKstrobeWF, Edge2, orgtH1flo);

        WaveSetSBC          (DBUSdriveWF,
                            t[tref]+t[tH1flo]-t[tsuDR]-t[loossetup]+dtcf-7ns,
                            t[tref]+t[tH1flo]-t[tsuDR]-t[loossetup]+dtcf,
                            t[tref]+t[tH1flo]+t[thDR]+t[looshold]-dtcf);
        EdgeSetOrigin       (DBUSdriveWF, Edge1, orgtH1flo);
        EdgeSetOrigin       (DBUSdriveWF, Edge2, orgtH1flo);
        EdgeSetOrigin       (DBUSdriveWF, Edge3, orgtH1flo);


        EdgeSet             (DBUSstrobeWF,Edge1,DriveOff,t[tref]+
                            t[tH1flo]+t[tvDW]+t[loosdelay7]-t[tgb]-ctcf-
                            t[restrict]-7ns);
        EdgeSet             (DBUSstrobeWF,Edge2,StrobeOff,t[tref]+
                            t[tH1flo]+t[tvDW]+t[loosdelay7]-t[tgb]-ctcf-
                            t[restrict]);

        (* bb 7/8/96 Changed so that VOH does not have 1ns tgb *)
        EdgeSetDelayData    (DBUSstrobeWF,Edge3,ChanFirst,
                            StrobeData,ThreshVITL,
                            t[tref]+t[tH1flo]+t[tvDW]+t[loosdelay7]-t[tgb]-ctcf,0,
                            StrobeData,ThreshVITH,
                            t[tref]+t[tH1flo]+t[tvDW]+t[loosdelay7]-ctcf,0);

        EdgeSetOrigin       (DBUSstrobeWF, Edge1, orgtH1flo);
        EdgeSetOrigin       (DBUSstrobeWF, Edge2, orgtH1flo);
        EdgeSetOrigin       (DBUSstrobeWF, Edge3, orgtH1flo);

        EdgeSet             (DBUSstrobeoffWF,Edge1,StrobeOff,t[tref]+
                            t[thDW]-t[loosdelay]+t[tgb]+ctcf);

        EdgeSet             (DBUSWWstrobeWF,Edge1,StrobeOff,t[tref]+
                            t[thDW]-t[loosdelay]+t[tgb]+ctcf);

        (* bb 7/8/96 Changed so that VOH does not have 1ns tgb *)
        EdgeSetDelayData    (DBUSWWstrobeWF,Edge2,ChanFirst,
                            StrobeData,ThreshVITL,
                            t[tref]+t[tH1flo]+t[tvDW]+t[loosdelay5]-t[tgb]-ctcf,0,
                            StrobeData,ThreshVITH,
                            t[tref]+t[tH1flo]+t[tvDW]+t[loosdelay5]-ctcf,0);
 
        EdgeSetOrigin       (DBUSWWstrobeWF, Edge2, orgtH1flo);

	(* New waveform - see comment at top for usage.    PHQ    8/12/93 *) 
	(* No loose gb to guarantee at least 10ns window *)

	(* Calculation for edge placement so that edge rule is not violated *)
	(* StrobeOn-StrobeOff must be at least 3ns.			    *)
	(* This edge will follow either StrobeData edge of DBUSstrobeWF or  *)
	(* DBUSWWstrobeWF.				   PHQ    8/13/93   *)

	SparePicoSeconds1 := t[tref]+t[tH1flo]+t[tvDW]-t[tgb]-ctcf;
			     (* StrobeData edge of DBUSstrobeWF or DBUSWWstrobeWF *)
	if(SparePicoSeconds1 > t[tcH]) then
	   (* Going over next cycle *)
	   SparePicoSeconds2 := (SparePicoSeconds1 - t[tcH]) + 4ns
	else
	  SparePicoSeconds2 := 4ns;

        EdgeSet             (DBUSWW2strobeWF, Edge1, StrobeOff,
	           	     + SparePicoSeconds2);

        EdgeSet             (DBUSWW2strobeWF,Edge2,StrobeData,t[tref]+
                            t[tH1flo]-t[tsuDR2]-ctcf);

        EdgeSetOrigin       (DBUSWW2strobeWF, Edge2, orgtH1flo);


        WaveSetRTO          (RDYdriveWF,
                            t[tref]+t[tH1flo]-t[tsuRDY]-t[loossetup]+dtcf,
                            t[tref]+t[tH1flo]+t[thRDY]+t[looshold]-dtcf);
        EdgeSetOrigin       (RDYdriveWF, Edge1, orgtH1flo);
        EdgeSetOrigin       (RDYdriveWF, Edge2, orgtH1flo);

        WaveSetNR           (ENBdriveWF,
                            t[tref]+t[tENB]);

        WaveSetStrobeZ      (DBUSHIZstrobeWF,
                            0ns,
                            t[tref]+t[tENB]+t[tdENBZ]+t[loosdelay]-ctcf,
                            t[tref]+t[tENB]+t[tdENBZ]+t[loosdelay]+7ns+ctcf);

        WaveSetStrobeZ      (ABUSHIZstrobeWF,
                            0ns,
                            t[tref]+t[tENB]+t[tdENBZ]+t[loosdelay]-ctcf,
                            t[tref]+t[tENB]+t[tdENBZ]+t[loosdelay]+7ns+ctcf);

        WaveSetStrobeZ      (CTRLHIZstrobeWF,
                            0ns,
                            t[tref]+t[tENB]+t[tdENBZ]+t[loosdelay]-ctcf,
                            t[tref]+t[tENB]+t[tdENBZ]+t[loosdelay]+7ns+ctcf);

        EdgeSet             (DBUSVALstrobeWF,Edge1,StrobeOff,t[tref]+
                            t[tENB]+t[tdENBDV]-t[restrict]-t[loosdelay]+
                            t[tgb]+ctcf);
        EdgeSet             (DBUSVALstrobeWF,Edge2,StrobeData,t[tref]+
                            t[tENB]+t[tdENBDV]+t[loosdelay7]-t[tgb]-ctcf);

        if (actable = TIsearch40ACTable) then    (* schmoo *)
START(ALLENUMS,TIsearch40ACTable);
           WaveSetStrobe    (ABUSVALstrobeWF,
                            0ns,
                            t[tref]+t[tENB]+t[tdENBAV]+t[loosdelay7]-
                            t[tgb]-ctcf,
                            t[tref]+t[tENB]+t[tdENBAV]+t[loosdelay7]-
                            t[tgb]-ctcf+6ns)
STOP(ALLENUMS,TIsearch40ACTable);
	else
START(ALLENUMS,ALLTABLES-TIsearch40ACTable);
           WaveSetStrobe    (ABUSVALstrobeWF,
                            0ns,
                            t[tref]+t[tENB]+t[tdENBAV]+t[loosdelay]-
                            t[tgb]-ctcf,
                            t[tref]+t[tENB]+t[tdENBAV]+t[loosdelay]-
                            t[tgb]-ctcf+6ns);
STOP(ALLENUMS,ALLTABLES-TIsearch40ACTable);


        WaveSetStrobe       (CTRLVALstrobeWF,
                            0ns,
                            t[tref]+t[tENB]+t[tdENBCV]+t[loosdelay]-
                            t[tgb]-ctcf,
                            t[tref]+t[tENB]+t[tdENBCV]+t[loosdelay]-
                            t[tgb]-ctcf+6ns);


        WaveSetSBC          (IIOFdriveWF,
                            t[tref]+t[tH1flo]-t[tsuIF]-t[loossetup]+dtcf-7ns,
                            t[tref]+t[tH1flo]-t[tsuIF]-t[loossetup]+dtcf,
                            t[tref]+t[tH1flo]+t[thIF]+t[looshold]-dtcf);
        EdgeSetOrigin       (IIOFdriveWF, Edge1, orgtH1flo);
        EdgeSetOrigin       (IIOFdriveWF, Edge2, orgtH1flo);
        EdgeSetOrigin       (IIOFdriveWF, Edge3, orgtH1flo);

        EdgeSet             (IIOFstrobeWF,Edge1,DriveOff,t[tref]+
                            t[tH1flo]+t[tvH1LIF]+t[loosdelay]-t[tgb]-ctcf-7ns);
        EdgeSet             (IIOFstrobeWF,Edge2,StrobeData,t[tref]+
                            t[tH1flo]+t[tvH1LIF]+t[loosdelay]-t[tgb]-ctcf);
        EdgeSetOrigin       (IIOFstrobeWF, Edge1, orgtH1flo);
        EdgeSetOrigin       (IIOFstrobeWF, Edge2, orgtH1flo);

(* phq - temporarily work around for sub40ns schmoo *)
        if (actable = TIsearch40ACTable) then
START(ALLENUMS,TIsearch40ACTable);
            EdgeSet         (IIOFstrobeoffWF,Edge1,StrobeOff,t[tref]+
                            t[tH1flo]+t[thH1LIFOI]-t[loosdelay]-5ns +t[tgb]+ctcf)
STOP(ALLENUMS,TIsearch40ACTable);
        else
START(ALLENUMS,ALLTABLES-TIsearch40ACTable);
            EdgeSet         (IIOFstrobeoffWF,Edge1,StrobeOff,t[tref]+
                            t[tH1flo]+t[thH1LIFOI]-t[loosdelay]+t[tgb]+ctcf);
STOP(ALLENUMS,ALLTABLES-TIsearch40ACTable);

        EdgeSetOrigin       (IIOFstrobeoffWF, Edge1, orgtH1flo);

        EdgeSet             (IIOFWWstrobeWF,Edge1,StrobeOff,t[tref]+
                            t[tH1flo]+t[tvH1LIF]-t[restrict]-t[loosdelay5]+
                            t[tgb]+ctcf);
        EdgeSet             (IIOFWWstrobeWF,Edge2,StrobeData,t[tref]+
                            t[tH1flo]+t[tvH1LIF]+t[loosdelay5]-ctcf);
  
(*  Took out the Voh/Vol offsets along with the 1ns guardband used  *)
        (* bb     7/8/96 Changed so that VOH does not have 1ns tgb *)

        EdgeSetOrigin       (IIOFWWstrobeWF, Edge1, orgtH1flo);
        EdgeSetOrigin       (IIOFWWstrobeWF, Edge2, orgtH1flo);

        WaveSetNR           (INTdriveWF,
                            t[tref]+t[tH1flo]-t[tsuINT]-t[loossetup]+dtcf);
        EdgeSetOrigin       (INTdriveWF, Edge1, orgtH1flo);

        WaveSetNR           (INTIDLEdriveWF,
                            t[tref]+t[tH1flo]-t[tsuINTIDLE]-t[loossetup]+dtcf);
        EdgeSetOrigin       (INTdriveWF, Edge1, orgtH1flo);

        EdgeSet             (IACKstrobeWF,Edge1,StrobeOff,t[tref]+
                            t[tH1flo]+t[tdH1LIACK]-t[restrict]-t[loosdelay]+
                            t[tgb]+ctcf);
        EdgeSet             (IACKstrobeWF,Edge2,StrobeData,t[tref]+
                            t[tH1flo]+t[tdH1LIACK]+t[loosdelay6]-t[tgb]-ctcf);
        EdgeSetOrigin       (IACKstrobeWF, Edge1, orgtH1flo);
        EdgeSetOrigin       (IACKstrobeWF, Edge2, orgtH1flo);


        EdgeSetDelayData    (CREQdriveWF,Edge1,ChanFirst,
                            DriveData,ThreshVITL,
                            t[tref]+t[tH1flo]-t[tsuCREQ],0,
                            DriveData,ThreshVITH,
                            t[tref]+t[tH1flo]+t[tsuCREQ],0);

(*bb  changed each edge of CSTRBstrobeWF by -4ns for char33 at 0c problem  for 0 and 1 data*)

       if (actable = TIchar33ACTable) then
          begin
START(ALLENUMS,TIchar33ACTable);
            EdgeSetDelayData    (CREQstrobeWF,Edge1,ChanFirst,
                            DriveOff,ThreshVITL,t[tref]+
                            t[tdH1HRQLt]+t[loosdelay]-t[tgb]-ctcf-7ns,0,
                            DriveOff,ThreshVITH,t[tref]+
                            t[tH1flo]-t[tsuCACK]+t[tdALRQHt]+
                            t[loosdelay]-t[tgb]-ctcf-7ns-4ns,0);
            EdgeSetDelayData    (CREQstrobeWF,Edge2,ChanFirst,
                            StrobeData,ThreshVITL,t[tref]+
                            t[tdH1HRQLt]+t[loosdelay]-t[tgb]-ctcf,0,
                            StrobeData,ThreshVITH,t[tref]+
                            t[tH1flo]-t[tsuCACK]+t[tdALRQHt]+
                            t[loosdelay]-t[tgb]-ctcf-4ns,0);
            EdgeSetDelayData    (CREQstrobeWF,Edge3,ChanFirst,
                            StrobeOff,ThreshVITL,t[tref]+
                            t[tdH1HRQLt]+t[loosdelay]-t[tgb]-ctcf+7ns,0,
                            StrobeOff,ThreshVITH,t[tref]+
                            t[tH1flo]-t[tsuCACK]+t[tdALRQHt]+
                            t[loosdelay]-t[tgb]-ctcf+7ns-4ns,0);
STOP(ALLENUMS,TIchar33ACTable);
           end
        else
START(ALLENUMS,ALLTABLES-TIchar33ACTable);
           begin
             EdgeSetDelayData    (CREQstrobeWF,Edge1,ChanFirst,
                            DriveOff,ThreshVITL,t[tref]+
                            t[tdH1HRQLt]+t[loosdelay]-t[tgb]-ctcf-7ns,0,
                            DriveOff,ThreshVITH,t[tref]+
                            t[tH1flo]-t[tsuCACK]+t[tdALRQHt]+
                            t[loosdelay]-t[tgb]-ctcf-7ns,0);
             EdgeSetDelayData    (CREQstrobeWF,Edge2,ChanFirst,
                            StrobeData,ThreshVITL,t[tref]+
                            t[tdH1HRQLt]+t[loosdelay]-t[tgb]-ctcf,0,
                            StrobeData,ThreshVITH,t[tref]+
                            t[tH1flo]-t[tsuCACK]+t[tdALRQHt]+
                            t[loosdelay]-t[tgb]-ctcf,0);
            EdgeSetDelayData    (CREQstrobeWF,Edge3,ChanFirst,
                            StrobeOff,ThreshVITL,t[tref]+
                            t[tdH1HRQLt]+t[loosdelay]-t[tgb]-ctcf+7ns,0,
                            StrobeOff,ThreshVITH,t[tref]+
                            t[tH1flo]-t[tsuCACK]+t[tdALRQHt]+
                            t[loosdelay]-t[tgb]-ctcf+7ns,0);
STOP(ALLENUMS,ALLTABLES-TIchar33ACTable);
           end;

        EdgeSetDelayData    (CREQ2strobeWF,Edge1,ChanFirst,
                            DriveOff,ThreshVITL,t[tref]+
                            t[tH1flo]+t[tsuCREQ]+t[tdRQHRQLt]+
                            t[loosdelay]-t[tgb]-ctcf-7ns,0,
                            DriveOff,ThreshVITH,t[tref]+
                            t[tH1flo]+t[tsuCREQ]+t[tdRQHRQOt]+
                            t[loosdelay]-t[tgb]-ctcf-7ns,0);
        EdgeSetDelayData    (CREQ2strobeWF,Edge2,ChanFirst,
                            StrobeData,ThreshVITL,t[tref]+
                            t[tH1flo]+t[tsuCREQ]+t[tdRQHRQLt]+
                            t[loosdelay]-t[tgb]-ctcf,0,
                            StrobeData,ThreshVITH,t[tref]+
                            t[tH1flo]+t[tsuCREQ]+t[tdRQHRQOt]+
                            t[loosdelay]-t[tgb]-ctcf,0);
        EdgeSetDelayData    (CREQ2strobeWF,Edge3,ChanFirst,
                            StrobeOff,ThreshVITL,t[tref]+
                            t[tH1flo]+t[tsuCREQ]+t[tdRQHRQLt]+
                            t[loosdelay]-t[tgb]-ctcf+7ns,0,
                            StrobeOff,ThreshVITH,t[tref]+
                            t[tH1flo]+t[tsuCREQ]+t[tdRQHRQOt]+
                            t[loosdelay]-t[tgb]-ctcf+7ns,0);

        WaveSetNR           (CACKdriveWF,
                            t[tref]+t[tH1flo]-t[tsuCACK]);
        EdgeSetOrigin       (CACKdriveWF, Edge1, orgtH1flo);

        WaveSetStrobe       (CACKstrobeWF,
                            t[tref]+t[tH1flo]-t[tsuCREQ]+t[tdRQLALt]+
                            t[loosdelay7]-t[tgb]-ctcf-7ns,
                            t[tref]+t[tH1flo]-t[tsuCREQ]+t[tdRQLALt]+
                            t[loosdelay7]-t[tgb]-ctcf,
                            t[tref]+t[tH1flo]-t[tsuCREQ]+t[tdRQLALt]+
                            t[loosdelay7]-t[tgb]-ctcf+7ns);
        EdgeSetOrigin       (CACKstrobeWF, Edge1, orgtH1flo);
        EdgeSetOrigin       (CACKstrobeWF, Edge2, orgtH1flo);
        EdgeSetOrigin       (CACKstrobeWF, Edge3, orgtH1flo);

(* CRDY  Edge1 is defined as DriveData here, but in actuality should always   *)
(* end up being a drive-low edge based on pattern data and translation.       *)

        WaveSetRTO          (CRDYdriveWF,
                            t[tCRDYLO],
                            t[tCRDYHI]);

(* special cstrb_ strobe w/o origin used for sync-up only to avoid problems   *)
(* with bsearch.                                                              *)

        WaveSetStrobe       (CSTRB_SYNCstrobeWF,
                            t[tCRDYHI]-t[tcH]+t[tdRHSLw]-7ns,
                            t[tCRDYHI]-t[tcH]+t[tdRHSLw],
                            t[tCRDYHI]-t[tcH]+t[tdRHSLw]+7ns);

(*bb  changed each edge of CSTRBstrobeWF by -4ns for char33 at 0c problem  for 0 and 1 data*)

       if (actable = TIchar33ACTable) then
          begin
START(ALLENUMS,TIchar33ACTable);
            EdgeSetDelayData    (CSTRBstrobeWF,Edge1,ChanFirst,
                            DriveOff,ThreshVITL,t[tCRDYHI]-t[tcH]+
                            t[tdRHSLw]+t[loosdelay7]-t[tgb]-ctcf-7ns-4ns,0,
                            DriveOff,ThreshVITH,t[tCRDYLO]+
                            t[tdRLSHw]+t[loosdelay]-t[tgb]-ctcf-7ns-4ns,0);
            EdgeSetDelayData    (CSTRBstrobeWF,Edge2,ChanFirst,
                            StrobeData,ThreshVITL,t[tCRDYHI]-t[tcH]+
                            t[tdRHSLw]+t[loosdelay7]-t[tgb]-ctcf-4ns,0,
                            StrobeData,ThreshVITH,t[tCRDYLO]+
                            t[tdRLSHw]+t[loosdelay]-t[tgb]-ctcf-4ns,0);
 
            EdgeSetDelayData    (CSTRBstrobeWF,Edge3,ChanFirst,
                            StrobeOff,ThreshVITL,t[tCRDYHI]-t[tcH]+
                            t[tdRHSLw]+t[loosdelay]-t[tgb]-ctcf+7ns-4ns,0,
                            StrobeOff,ThreshVITH,t[tCRDYLO]+
                            t[tdRLSHw]+t[loosdelay]-t[tgb]-ctcf+7ns-4ns,0);
STOP(ALLENUMS,TIchar33ACTable);

          end
        else
START(ALLENUMS,ALLTABLES-TIchar33ACTable);
          begin
            EdgeSetDelayData    (CSTRBstrobeWF,Edge1,ChanFirst,
                            DriveOff,ThreshVITL,t[tCRDYHI]-t[tcH]+
                            t[tdRHSLw]+t[loosdelay7]-t[tgb]-ctcf-7ns,0,
                            DriveOff,ThreshVITH,t[tCRDYLO]+
                            t[tdRLSHw]+t[loosdelay]-t[tgb]-ctcf-7ns,0);
            EdgeSetDelayData    (CSTRBstrobeWF,Edge2,ChanFirst,
                            StrobeData,ThreshVITL,t[tCRDYHI]-t[tcH]+
                            t[tdRHSLw]+t[loosdelay7]-t[tgb]-ctcf,0,
                            StrobeData,ThreshVITH,t[tCRDYLO]+
                            t[tdRLSHw]+t[loosdelay]-t[tgb]-ctcf,0);

            EdgeSetDelayData    (CSTRBstrobeWF,Edge3,ChanFirst,
                            StrobeOff,ThreshVITL,t[tCRDYHI]-t[tcH]+
                            t[tdRHSLw]+t[loosdelay]-t[tgb]-ctcf+7ns,0,
                            StrobeOff,ThreshVITH,t[tCRDYLO]+
                            t[tdRLSHw]+t[loosdelay]-t[tgb]-ctcf+7ns,0);
STOP(ALLENUMS,ALLTABLES-TIchar33ACTable);
          end;

       WaveSetStrobe       (CDstrobeWF,
                                t[tref]+t[tCSTRBfhi]-t[tsuCDw]+
                                t[loosdelay]-t[tgb]-ctcf-7ns,
                                t[tref]+t[tCSTRBfhi]-t[tsuCDw]+
                                t[loosdelay]-t[tgb]-ctcf,
                                t[tCRDYLO]+t[thCDw]-t[loosdelay]+t[tgb]+ctcf);

        EdgeSetOrigin       (CDstrobeWF, Edge1, orgtCSTRBfhi);
        EdgeSetOrigin       (CDstrobeWF, Edge2, orgtCSTRBfhi);

(* CSTRB Edge1 is defined as DriveData here, but in actuality should always   *)
(* end up being a drive-low edge based on pattern data and translation.       *)

        WaveSetRTO          (CSTRBdriveWF,
                            t[tCSTRBLO],
                            t[tCSTRBHI]);
        EdgeSetOrigin       (CSTRBdriveWF, Edge1, orgtCSTRBfhi);
        EdgeSetOrigin       (CSTRBdriveWF, Edge2, orgtCSTRBfhi);

        WaveSetStrobe       (CRDY_SYNCstrobeWF,          (*special crdy_  strobe*)
                            t[tCSTRBLO]+t[tdSLRLr]-7ns,  (*w/o origin used for  *)
                            t[tCSTRBLO]+t[tdSLRLr],      (*sync-up only to avoid*)
                            t[tCSTRBLO]+t[tdSLRLr]+7ns); (*problems with bsearch*)

        EdgeSetDelayData    (CRDYstrobeWF,Edge1,ChanFirst,
                            DriveOff,ThreshVITL,t[tCSTRBLO]+
                            t[tdSLRLr]+t[loosdelay4]-t[tgb]-ctcf-7ns,0,
                            DriveOff,ThreshVITH,t[tCSTRBHI]+
                            t[tdSHRHr]+t[loosdelay]-t[tgb]-ctcf-7ns,0);
        EdgeSetDelayData    (CRDYstrobeWF,Edge2,ChanFirst,
                            StrobeData,ThreshVITL,t[tCSTRBLO]+
                            t[tdSLRLr]+t[loosdelay5]-t[tgb]-ctcf,0,
                            StrobeData,ThreshVITH,t[tCSTRBHI]+
                            t[tdSHRHr]+t[loosdelay]-t[tgb]-ctcf,0);

(* bb - 11/16/93 - Changed Edge3 for high data by 1ns to avoid an edge violation in next cycle
                   with ALLOFFWF *)
        EdgeSetDelayData    (CRDYstrobeWF,Edge3,ChanFirst,
                            StrobeOff,ThreshVITL,t[tCSTRBLO]+
                            t[tdSLRLr]+t[loosdelay5]-t[tgb]-ctcf+7ns,0,
                            StrobeOff,ThreshVITH,t[tCSTRBHI]+
                            t[tdSHRHr]+t[loosdelay]-t[tgb]-ctcf+6ns,0);  (* changed from +7ns *)

        EdgeSetDelayData    (CDdriveWF,Edge1,ChanFirst,
                            DriveComplement,ThreshVITL,t[tCSTRBLO]-
                            t[tsuCDr]-t[loossetup]+dtcf-7ns,0,
                            DriveComplement,ThreshVITH,t[tCSTRBLO]-
                            t[tsuCDr]-t[looscd]-t[loossetup]+dtcf-7ns,0);
        EdgeSetDelayData    (CDdriveWF,Edge2,ChanFirst,
                            DriveData,ThreshVITL,t[tCSTRBLO]-
                            t[tsuCDr]-t[loossetup]+dtcf,0,
                            DriveData,ThreshVITH,t[tCSTRBLO]-
                            t[tsuCDr]-t[looscd]-t[loossetup]+dtcf,0);
        EdgeSetDelayData    (CDdriveWF,Edge3,ChanFirst,
                            DriveComplement,ThreshVITL,t[tref]+t[tCRDYflo]+
                            t[thCDr]+t[looscd]+t[looshold]-dtcf,0,
                            DriveComplement,ThreshVITH,t[tref]+t[tCRDYflo]+
                            t[thCDr]+t[looshold]-dtcf,0);


        WaveSetSBC          (TCLKdriveWF,
                            t[tref]+t[tH1flo]-t[tsuTCLK]-t[loossetup]+dtcf-7ns,
                            t[tref]+t[tH1flo]-t[tsuTCLK]-t[loossetup]+dtcf,
                            t[tref]+t[tH1flo]+t[thTCLK]+t[looshold]-dtcf);
        EdgeSetOrigin       (TCLKdriveWF, Edge1, orgtH1flo);
        EdgeSetOrigin       (TCLKdriveWF, Edge2, orgtH1flo);
        EdgeSetOrigin       (TCLKdriveWF, Edge3, orgtH1flo);

(* bb 10/12/93 *)
        WaveSetStrobe       (TCLKstrobeWF,
                            t[tref]+t[tdTCLK]+t[loosdelay6]-t[tgb]-ctcf-7ns,
                            t[tref]+t[tdTCLK]+t[loosdelay6]-t[tgb]-ctcf,
                            t[tref]+t[tdTCLK]+t[tcH]-t[restrict]-t[loosdelay]+
                            t[tgb]+ctcf-9ns);


        WaveSetRTO          (TCKCLKdriveWF,
                            t[tref],
                            t[tref]+t[tcCI]);

        WaveSetNR           (TCKdriveWF,
                            t[tref]);

        WaveSetSBC          (TDITMSdriveWF,
                            t[tref]+t[tcCI]-t[tsuTDITMS]-t[loossetup]+dtcf-7ns,
                            t[tref]+t[tcCI]-t[tsuTDITMS]-t[loossetup]+dtcf,
                            t[tref]+t[tcCI]+t[thTDITMS]+t[looshold]-dtcf);

        WaveSetNR           (JTAGdriveWF,
                            t[tref]+t[tJTAG]);

  if (actable = TIchar40ACTable) or (actable = TIchar33ACTable) then 
START(ALLENUMS,TIsearch40ACTable,TIchar33ACTable);
   WaveSetStrobe   (TDOstrobeWF,    (*bb - added -4ns to each edge for characterization only *)
                    0ns,
                    t[tref]+t[tdTDO]+t[loosdelay5]-t[loosdelay]-t[tgb]-ctcf-4ns,   (* changed loosedelay from 3 to 2*)
                    t[tref]+t[tdTDO]+t[loosdelay5]-t[loosdelay]-t[tgb]-ctcf+7ns-4ns)
STOP(ALLENUMS,TIsearch40ACTable,TIchar33ACTable);
  else
START(ALLENUMS,ALLTABLES-TIsearch40ACTable-TIchar33ACTable);
   WaveSetStrobe   (TDOstrobeWF,
                    0ns,
                    t[tref]+t[tdTDO]+t[loosdelay5]-t[loosdelay]-t[tgb]-ctcf,   (* changed loosedelay from 3 to 2*)
                    t[tref]+t[tdTDO]+t[loosdelay5]-t[loosdelay]-t[tgb]-ctcf+7ns);
STOP(ALLENUMS,ALLTABLES-TIsearch40ACTable-TIchar33ACTable);

        WaveSetEdgeStrobe   (JTAGH1strobeWF,
                            0ns,
                            t[tref]+t[tdTDO]+t[loosdelay]-t[tgb]-ctcf,
                            t[tref]+t[tdTDO]+t[loosdelay]-t[tgb]-ctcf+7ns);

        EdgeSet             (JTAGVARYstrobeWF,Edge1,StrobeOff,t[tref]+
                            t[tdTDO]-t[restrict]-t[loosdelay]+t[tgb]+ctcf);
        EdgeSet             (JTAGVARYstrobeWF,Edge2,StrobeData,t[tref]+
                            t[tdTDO]+t[tcCI]+t[loosdelay]-t[tgb]-ctcf);

        EdgeSet             (JTAGABUSstrobeWF,Edge1,StrobeOff,t[tref]+
                            t[tdTDO]-t[restrict]-t[loosdelay]+t[tgb]+ctcf);
        EdgeSet             (JTAGABUSstrobeWF,Edge2,DriveOff,t[tref]+
                            t[tdTDO]-t[restrict]-t[loosdelay]+t[tgb]+ctcf);
        EdgeSet             (JTAGABUSstrobeWF,Edge3,StrobeData,t[tref]+
                            t[tdTDO]+t[tcCI]+t[loosdelay]-t[tgb]-ctcf);

        WaveSetNR           (EMUdriveWF,
                            t[tref]+t[tEMU]);

        WaveSetStrobe       (EMUstrobeWF,
                            0ns,
                            t[tref]+t[tdEMU]+t[loosdelay]-t[tgb]-ctcf,
                            t[tref]+t[tdEMU]+t[loosdelay]-t[tgb]-ctcf+7ns);


        WaveSetNR           (RESETLOCdriveWF,
                            t[tref]+t[tRESETLOC]);

        WaveSetNR           (ROMENdriveWF,
                            t[tref]+t[tROMEN]);

        WaveSetNR           (NMIdriveWF,
                            t[tref]+t[tNMI]);


        WaveSetContinue     (ContinueWF);

        WaveSetOff          (ALLoffWF,t[tref],t[tref]);
STOP(ALLENUMS,TIhifrqmin33ACTable,TIhifrqmax33ACTable,TIhifrqmin40ACTable,TIhifrqmax40ACTable,TIsearch40ACTable,TIchar33ACTable,TIchar40ACTable);

          end; (*3rd case*)

        TIhifrqloose40ACTable,
        TIsearchlevels40ACTable:
          begin

START(ALLENUMS,TIhifrqloose40ACTable,TIsearchlevels40ACTable);

        WaveSetDoubleClk    (CLKINdriveWF,
                            t[tref]+t[toffset],
                            t[tref]+t[toffset]+t[twCIH],
                            t[tref]+t[toffset]+t[twCIH]+t[twCIL],
                            t[tref]+t[toffset]+t[twCIH]+t[twCIL]+t[twCIH]);
        EdgeSetOrigin       (CLKINdriveWF, Edge1, orgtoffset);
        EdgeSetOrigin       (CLKINdriveWF, Edge2, orgtoffset);
        EdgeSetOrigin       (CLKINdriveWF, Edge3, orgtoffset);
        EdgeSetOrigin       (CLKINdriveWF, Edge4, orgtoffset);

        EdgeSetDelayData    (RESETdriveWF,Edge1,ChanFirst,
                            DriveData,ThreshVITL,
                            t[tref]+t[toffset]+t[twCIH]+t[twCIL]+t[twCIH]-t[tsuRESET]-t[loossetup]+dtcf,0,
                            DriveData,ThreshVITH,
                            t[tref]+t[tH1flo]-t[tsuRESETH]-t[loossetup]+dtcf,0);

        WaveSetEdgeStrobe   (H1strobeWF,
                            0ns,
                            t[tref]+t[loosclock],
                            t[tref]+t[loosclock]+7ns);

        WaveSetEdgeStrobe   (H1HIGHstrobeWF,
                            0ns,
                            t[tref]+t[tH1flo]-t[tfHmax],
                            t[tref]+t[tH1flo]-t[tfHmax]+7ns);
        EdgeSetOrigin       (H1HIGHstrobeWF, Edge2, orgtH1high);
        EdgeSetOrigin       (H1HIGHstrobeWF, Edge3, orgtH1high);

        EdgeSet             (H1LOWstrobeWF,Edge1,DriveOff,
                            0ns);
        EdgeSet             (H1LOWstrobeWF,Edge2,EdgeStrobeLow,
                            t[tref]+t[tcH]-t[trHmax]);
        EdgeSet             (H1LOWstrobeWF,Edge3,StrobeLatch,
                            t[tref]+t[tcH]-t[trHmax]+7ns);
        EdgeSetOrigin       (H1LOWstrobeWF, Edge2, orgtH1low);
        EdgeSetOrigin       (H1LOWstrobeWF, Edge3, orgtH1low);

        WaveSetEdgeStrobe   (H1IDLEstrobeWF,
                            0ns,
                            t[tref]+t[tH1flo]+t[loosclock],
                            t[tref]+t[tH1flo]+t[loosclock]+7ns);

        WaveSetEdgeStrobe   (H3strobeWF,
                            0ns,
                            t[tref]+t[loosclock],
                            t[tref]+t[loosclock]+7ns);

        WaveSetEdgeStrobe   (H3LOWstrobeWF,
                            0ns,
                            t[tref]+t[tH3rhi]-t[trHmax],
                            t[tref]+t[tH3rhi]-t[trHmax]+7ns);
        EdgeSetOrigin       (H3LOWstrobeWF, Edge2, orgtH3low);
        EdgeSetOrigin       (H3LOWstrobeWF, Edge3, orgtH3low);

        EdgeSet             (H3HIGHstrobeWF,Edge1,DriveOff,
                            0ns);
        EdgeSet             (H3HIGHstrobeWF,Edge2,EdgeStrobeHigh,
                            t[tref]+t[tcH]+t[tH3flo]-t[tfHmax]);
        EdgeSet             (H3HIGHstrobeWF,Edge3,StrobeLatch,
                            t[tref]+t[tcH]+t[tH3flo]-t[tfHmax]+7ns);
        EdgeSetOrigin       (H3HIGHstrobeWF, Edge2, orgtH3high);
        EdgeSetOrigin       (H3HIGHstrobeWF, Edge3, orgtH3high);

        WaveSetEdgeStrobe   (H3IDLEstrobeWF,
                            0ns,
                            t[tref]+t[tH1flo]+t[loosclock],
                            t[tref]+t[tH1flo]+t[loosclock]+7ns);

        WaveSetEdgeStrobe   (STRBstrobeWF,
                            0ns,
                            t[tref]+t[tH1flo]+t[tdH1LS]+t[loosdelay6]-
                            t[tgb]-ctcf,
                            t[tref]+t[tH1flo]+t[tdH1LS]+t[loosdelay6]-
                            t[tgb]-ctcf+7ns);

        EdgeSetOrigin       (STRBstrobeWF, Edge2, orgtH1flo);
        EdgeSetOrigin       (STRBstrobeWF, Edge3, orgtH1flo);

        WaveSetEdgeStrobe   (RWstrobeWF,
                            0ns,
                            t[tref]+t[tdH1HRW]+t[loosdelay5]-t[tgb]-ctcf,
                            t[tref]+t[tdH1HRW]+t[loosdelay5]-t[tgb]-ctcf+7ns);

        WaveSetEdgeStrobe   (ABUSVstrobeWF,
                            0ns,
                            t[tref]+t[tH1flo]+t[tdH1LA]-t[restrict]-
                            t[loosdelay]+t[tgb]+ctcf+t[tcH]-7ns,
                            t[tref]+t[tH1flo]+t[tdH1LA]-t[restrict]-
                            t[loosdelay]+t[tgb]+ctcf+t[tcH]);
        EdgeSetOrigin       (ABUSVstrobeWF, Edge2, orgtH1flo);
        EdgeSetOrigin       (ABUSVstrobeWF, Edge3, orgtH1flo);

	   (*BB -  Modifed because strobe w/ loosedelay7 stb was at rise/time transition *)
        WaveSetEdgeStrobe   (ABUSstrobeWF,
                            0ns,
                            t[tref]+t[tH1flo]+t[tdH1LA]+
                            t[loosdelay4]-t[tgb]-ctcf,
                            t[tref]+t[tH1flo]+t[tdH1LA]+
                            t[loosdelay4]-t[tgb]-ctcf+6ns);

        EdgeSetOrigin       (ABUSstrobeWF, Edge2, orgtH1flo);
        EdgeSetOrigin       (ABUSstrobeWF, Edge3, orgtH1flo);

        WaveSetEdgeStrobe   (ABUSWWstrobeWF,
                            0ns,
                            t[tref]+t[tdH1HA]+t[loosabus]-t[tgb]-ctcf,
                            t[tref]+t[tdH1HA]+t[loosabus]-t[tgb]-ctcf+7ns);

        EdgeSet             (STATstrobeWF,Edge1,StrobeOff,t[tref]+
                            t[tH1flo]+t[tdH1LSTAT]-t[restrict]-t[loosdelay]+
                            t[tgb]+ctcf);
        EdgeSet             (STATstrobeWF,Edge2,StrobeData,t[tref]+
                            t[tH1flo]+t[tdH1LSTAT]+t[loosdelay7]-t[tgb]-ctcf);
        EdgeSetOrigin       (STATstrobeWF, Edge1, orgtH1flo);
        EdgeSetOrigin       (STATstrobeWF, Edge2, orgtH1flo);

        EdgeSet             (LOCKstrobeWF,Edge1,StrobeOff,t[tref]+
                            t[tH1flo]+t[tdH1LLOCK]-t[restrict]-t[loosdelay]+
                            t[tgb]+ctcf);
        EdgeSet             (LOCKstrobeWF,Edge2,StrobeData,t[tref]+
                            t[tH1flo]+t[tdH1LLOCK]+t[loosdelay5]-t[tgb]-ctcf);
        EdgeSetOrigin       (LOCKstrobeWF, Edge1, orgtH1flo);
        EdgeSetOrigin       (LOCKstrobeWF, Edge2, orgtH1flo);

        WaveSetSBC          (DBUSdriveWF,
                            t[tref]+t[tH1flo]-t[tsuDR]-t[loossetup]+dtcf-7ns,
                            t[tref]+t[tH1flo]-t[tsuDR]-t[loossetup]+dtcf,
                            t[tref]+t[tH1flo]+t[thDR]+t[looshold]-dtcf);
        EdgeSetOrigin       (DBUSdriveWF, Edge1, orgtH1flo);
        EdgeSetOrigin       (DBUSdriveWF, Edge2, orgtH1flo);
        EdgeSetOrigin       (DBUSdriveWF, Edge3, orgtH1flo);

	SparePicoSeconds1 := t[loosdelay7];

	(* Take away loose gb for FUJISU Screen because looseDC is used anyway. *)
	(* The highest period for levels test will be 100ns - nomlooseACTable   *)

	    t[loosdelay7] := 0ns;        (*need 3ns more taken off, so -3ns was placed in WF*)

        EdgeSet             (DBUSstrobeWF,Edge1,DriveOff,t[tref]+
                            t[tH1flo]+t[tvDW]+t[loosdelay7]-3ns-t[tgb]-ctcf-
                            t[restrict]-7ns);

        EdgeSet             (DBUSstrobeWF,Edge2,StrobeOff,t[tref]+
                            t[tH1flo]+t[tvDW]+t[loosdelay7]-3ns-t[tgb]-ctcf-
                            t[restrict]);

        EdgeSet             (DBUSstrobeWF,Edge3,StrobeData,t[tref]+
                            t[tH1flo]+t[tvDW]+t[loosdelay7]-3ns-t[tgb]-ctcf);

        EdgeSetOrigin       (DBUSstrobeWF, Edge1, orgtH1flo);
        EdgeSetOrigin       (DBUSstrobeWF, Edge2, orgtH1flo);
        EdgeSetOrigin       (DBUSstrobeWF, Edge3, orgtH1flo);

	(*BB -  Put back loose gb *)
	t[loosdelay7] := SparePicoSeconds1;

        EdgeSet             (DBUSstrobeoffWF,Edge1,StrobeOff,t[tref]+
                            t[thDW]-t[loosdelay]+t[tgb]+ctcf);

        EdgeSet             (DBUSWWstrobeWF,Edge1,StrobeOff,t[tref]+
                            t[thDW]-t[loosdelay]+t[tgb]+ctcf);

(* phq - changed "loosedelay5" to "sp"  7/23/93 *)

	SparePicoSeconds1 := sp;

	(* Take away loose gb for FUJISU Screen because looseDC is used anyway. *)
	(* The highest period for levels test will be 100ns - nomlooseACTable   *)

	    sp := 0ns;

        EdgeSet          (DBUSWWstrobeWF,Edge2,StrobeData,t[tref]+
                          t[tH1flo]+t[tvDW]+sp-t[tgb]-ctcf);

        EdgeSetOrigin       (DBUSWWstrobeWF, Edge2, orgtH1flo);



	(* New waveform - see comment at top for usage.    PHQ    8/12/93 *) 
        (* No loose gb for StrobeData edge to guarantee at least 10ns window *)

	(* Calculation for edge placement so that edge rule is not violated *)
	(* StrobeOn-StrobeOff must be at least 3ns.			    *)
	(* This edge will follow either StrobeData edge of DBUSstrobeWF or  *)
	(* DBUSWWstrobeWF.				   PHQ    8/13/93   *)

	SparePicoSeconds3 := t[tref]+t[tH1flo]+t[tvDW]+sp-t[tgb]-ctcf;
			     (* StrobeData edge of DBUSstrobeWF or DBUSWWstrobeWF *)
	if(SparePicoSeconds3 > t[tcH]) then
	   (* Going over next cycle *)
	   SparePicoSeconds2 := (SparePicoSeconds3 - t[tcH]) + 4ns
	else
	  SparePicoSeconds2 := 4ns;

        EdgeSet             (DBUSWW2strobeWF, Edge1, StrobeOff,
	           	     + SparePicoSeconds2);

        EdgeSet             (DBUSWW2strobeWF,Edge2,StrobeData,t[tref]+
                            t[tH1flo]-t[tsuDR2]+t[loosdelay]-ctcf);

        EdgeSetOrigin       (DBUSWW2strobeWF, Edge2, orgtH1flo);

	(* Put back loose gb *)
	sp := SparePicoSeconds1;

        WaveSetRTO          (RDYdriveWF,
                            t[tref]+t[tH1flo]-t[tsuRDY]-t[loossetup]+dtcf,
                            t[tref]+t[tH1flo]+t[thRDY]+t[looshold]-dtcf);
        EdgeSetOrigin       (RDYdriveWF, Edge1, orgtH1flo);
        EdgeSetOrigin       (RDYdriveWF, Edge2, orgtH1flo);

        WaveSetNR           (ENBdriveWF,
                            t[tref]+t[tENB]);

        WaveSetStrobeZ      (DBUSHIZstrobeWF,
                            0ns,
                            t[tref]+t[tENB]+t[tdENBZ]+t[loosdelay]-ctcf,
                            t[tref]+t[tENB]+t[tdENBZ]+t[loosdelay]+7ns+ctcf);

        WaveSetEdgeStrobeZ  (ABUSHIZstrobeWF,
                            0ns,
                            t[tref]+t[tENB]+t[tdENBZ]+t[loosdelay]-ctcf,
                            t[tref]+t[tENB]+t[tdENBZ]+t[loosdelay]-ctcf+7ns);

        WaveSetEdgeStrobeZ  (CTRLHIZstrobeWF,
                            0ns,
                            t[tref]+t[tENB]+t[tdENBZ]+t[loosdelay]-ctcf,
                            t[tref]+t[tENB]+t[tdENBZ]+t[loosdelay]-ctcf+7ns);

        EdgeSet             (DBUSVALstrobeWF,Edge1,StrobeOff,t[tref]+
                            t[tENB]+t[tdENBDV]-t[restrict]-t[loosdelay]+
                            t[tgb]+ctcf);
        EdgeSet             (DBUSVALstrobeWF,Edge2,StrobeData,t[tref]+
                            t[tENB]+t[tdENBDV]+t[loosdelay7]-t[tgb]-ctcf);

(* phq - Changed "loosedelay7" to "sp"  8/6/93 *)
        WaveSetEdgeStrobe   (ABUSVALstrobeWF,
                            0ns,
                            t[tref]+t[tENB]+t[tdENBAV]+sp-
                            t[tgb]-ctcf+0ns,
                            t[tref]+t[tENB]+t[tdENBAV]+sp-
                            t[tgb]-ctcf+6ns);

        WaveSetEdgeStrobe   (CTRLVALstrobeWF,
                            0ns,
                            t[tref]+t[tENB]+t[tdENBCV]+t[loosdelay]-
                            t[tgb]-ctcf,
                            t[tref]+t[tENB]+t[tdENBCV]+t[loosdelay]-
                            t[tgb]-ctcf+6ns);


        WaveSetSBC          (IIOFdriveWF,
                            t[tref]+t[tH1flo]-t[tsuIF]-t[loossetup]+dtcf-7ns,
                            t[tref]+t[tH1flo]-t[tsuIF]-t[loossetup]+dtcf,
                            t[tref]+t[tH1flo]+t[thIF]+t[looshold]-dtcf);
        EdgeSetOrigin       (IIOFdriveWF, Edge1, orgtH1flo);
        EdgeSetOrigin       (IIOFdriveWF, Edge2, orgtH1flo);
        EdgeSetOrigin       (IIOFdriveWF, Edge3, orgtH1flo);

        EdgeSet             (IIOFstrobeWF,Edge1,DriveOff,t[tref]+
                            t[tH1flo]+t[tvH1LIF]+t[loosdelay]-t[tgb]-ctcf-7ns);
        EdgeSet             (IIOFstrobeWF,Edge2,StrobeData,t[tref]+
                            t[tH1flo]+t[tvH1LIF]+t[loosdelay]-t[tgb]-ctcf);
        EdgeSetOrigin       (IIOFstrobeWF, Edge1, orgtH1flo);
        EdgeSetOrigin       (IIOFstrobeWF, Edge2, orgtH1flo);

        EdgeSet             (IIOFstrobeoffWF,Edge1,StrobeOff,t[tref]+
                            t[tH1flo]+t[thH1LIFOI]-t[loosdelay]+t[tgb]+ctcf-1ns);
        EdgeSetOrigin       (IIOFstrobeoffWF, Edge1, orgtH1flo);

        EdgeSet             (IIOFWWstrobeWF,Edge1,StrobeOff,t[tref]+
                            t[tH1flo]+t[tvH1LIF]-t[restrict]-t[loosdelay5]+
                            t[tgb]+ctcf);
        EdgeSet             (IIOFWWstrobeWF,Edge2,StrobeData,t[tref]+
                            t[tH1flo]+t[tvH1LIF]+t[loosdelay5]-t[tgb]-ctcf);
        EdgeSetOrigin       (IIOFWWstrobeWF, Edge1, orgtH1flo);
        EdgeSetOrigin       (IIOFWWstrobeWF, Edge2, orgtH1flo);

        WaveSetNR           (INTdriveWF,
                            t[tref]+t[tH1flo]-t[tsuINT]-t[loossetup]+dtcf);
        EdgeSetOrigin       (INTdriveWF, Edge1, orgtH1flo);

        WaveSetNR           (INTIDLEdriveWF,
                            t[tref]+t[tH1flo]-t[tsuINTIDLE]-t[loossetup]+dtcf);
        EdgeSetOrigin       (INTdriveWF, Edge1, orgtH1flo);

        EdgeSet             (IACKstrobeWF,Edge1,StrobeOff,t[tref]+
                            t[tH1flo]+t[tdH1LIACK]-t[restrict]-t[loosdelay]+
                            t[tgb]+ctcf);
        EdgeSet             (IACKstrobeWF,Edge2,StrobeData,t[tref]+
                            t[tH1flo]+t[tdH1LIACK]+t[loosdelay6]-t[tgb]-ctcf);
        EdgeSetOrigin       (IACKstrobeWF, Edge1, orgtH1flo);
        EdgeSetOrigin       (IACKstrobeWF, Edge2, orgtH1flo);


        EdgeSetDelayData    (CREQdriveWF,Edge1,ChanFirst,
                            DriveData,ThreshVITL,
                            t[tref]+t[tH1flo]-t[tsuCREQ],0,
                            DriveData,ThreshVITH,
                            t[tref]+t[tH1flo]+t[tsuCREQ],0);

        EdgeSetDelayData    (CREQstrobeWF,Edge1,ChanFirst,
                            DriveOff,ThreshVITL,t[tref]+
                            t[tdH1HRQLt]+t[loosdelay]-t[tgb]-ctcf-7ns,0,
                            DriveOff,ThreshVITH,t[tref]+
                            t[tH1flo]-t[tsuCACK]+t[tdALRQHt]+
                            t[loosdelay]-t[tgb]-ctcf-7ns,0);
        EdgeSetDelayData    (CREQstrobeWF,Edge2,ChanFirst,
                            StrobeData,ThreshVITL,t[tref]+
                            t[tdH1HRQLt]+t[loosdelay]-t[tgb]-ctcf,0,
                            StrobeData,ThreshVITH,t[tref]+
                            t[tH1flo]-t[tsuCACK]+t[tdALRQHt]+
                            t[loosdelay]-t[tgb]-ctcf,0);
        EdgeSetDelayData    (CREQstrobeWF,Edge3,ChanFirst,
                            StrobeOff,ThreshVITL,t[tref]+
                            t[tdH1HRQLt]+t[loosdelay]-t[tgb]-ctcf+7ns,0,
                            StrobeOff,ThreshVITH,t[tref]+
                            t[tH1flo]-t[tsuCACK]+t[tdALRQHt]+
                            t[loosdelay]-t[tgb]-ctcf+7ns,0);

        EdgeSetDelayData    (CREQ2strobeWF,Edge1,ChanFirst,
                            DriveOff,ThreshVITL,t[tref]+
                            t[tH1flo]+t[tsuCREQ]+t[tdRQHRQLt]+
                            t[loosdelay]-t[tgb]-ctcf-7ns,0,
                            DriveOff,ThreshVITH,t[tref]+
                            t[tH1flo]+t[tsuCREQ]+t[tdRQHRQOt]+
                            t[loosdelay]-t[tgb]-ctcf-7ns,0);
        EdgeSetDelayData    (CREQ2strobeWF,Edge2,ChanFirst,
                            StrobeData,ThreshVITL,t[tref]+
                            t[tH1flo]+t[tsuCREQ]+t[tdRQHRQLt]+
                            t[loosdelay]-t[tgb]-ctcf,0,
                            StrobeData,ThreshVITH,t[tref]+
                            t[tH1flo]+t[tsuCREQ]+t[tdRQHRQOt]+
                            t[loosdelay]-t[tgb]-ctcf,0);
        EdgeSetDelayData    (CREQ2strobeWF,Edge3,ChanFirst,
                            StrobeOff,ThreshVITL,t[tref]+
                            t[tH1flo]+t[tsuCREQ]+t[tdRQHRQLt]+
                            t[loosdelay]-t[tgb]-ctcf+7ns,0,
                            StrobeOff,ThreshVITH,t[tref]+
                            t[tH1flo]+t[tsuCREQ]+t[tdRQHRQOt]+
                            t[loosdelay]-t[tgb]-ctcf+7ns,0);

        WaveSetNR           (CACKdriveWF,
                            t[tref]+t[tH1flo]-t[tsuCACK]);
        EdgeSetOrigin       (CACKdriveWF, Edge1, orgtH1flo);


(* phq - Changed "loosdelay7" to "sp" *)

        WaveSetStrobe       (CACKstrobeWF,
                            t[tref]+t[tH1flo]-t[tsuCREQ]+t[tdRQLALt]+
                            sp-t[tgb]-ctcf-7ns,
                            t[tref]+t[tH1flo]-t[tsuCREQ]+t[tdRQLALt]+
                            sp-t[tgb]-ctcf,
                            t[tref]+t[tH1flo]-t[tsuCREQ]+t[tdRQLALt]+
                            sp-t[tgb]-ctcf+7ns);

        EdgeSetOrigin       (CACKstrobeWF, Edge1, orgtH1flo);
        EdgeSetOrigin       (CACKstrobeWF, Edge2, orgtH1flo);
        EdgeSetOrigin       (CACKstrobeWF, Edge3, orgtH1flo);

(* CRDY  Edge1 is defined as DriveData here, but in actuality should always   *)
(* end up being a drive-low edge based on pattern data and translation.       *)

        WaveSetRTO          (CRDYdriveWF,
                            t[tCRDYLO],
                            t[tCRDYHI]);

(* special cstrb_ strobe w/o origin used for sync-up only to avoid problems   *)
(* with bsearch.                                                              *)

        WaveSetStrobe       (CSTRB_SYNCstrobeWF,
                            t[tCRDYHI]-t[tcH]+t[tdRHSLw]-7ns,
                            t[tCRDYHI]-t[tcH]+t[tdRHSLw],
                            t[tCRDYHI]-t[tcH]+t[tdRHSLw]+7ns);

        EdgeSetDelayData    (CSTRBstrobeWF,Edge1,ChanFirst,
                            DriveOff,ThreshVITL,t[tCRDYHI]-t[tcH]+
                            t[tdRHSLw]+t[loosdelay7]-t[tgb]-ctcf-7ns,0,
                            DriveOff,ThreshVITH,t[tCRDYLO]+
                            t[tdRLSHw]+t[loosdelay]-t[tgb]-ctcf-7ns,0);
        EdgeSetDelayData    (CSTRBstrobeWF,Edge2,ChanFirst,
                            StrobeData,ThreshVITL,t[tCRDYHI]-t[tcH]+
                            t[tdRHSLw]+t[loosdelay7]-t[tgb]-ctcf,0,
                            StrobeData,ThreshVITH,t[tCRDYLO]+
                            t[tdRLSHw]+t[loosdelay]-t[tgb]-ctcf,0);

(* bb - 10/12/93 moved edge3 for VITL from loos6 to loos4 strobeoff by -2ns to avoid catching a rising edge *)
        EdgeSetDelayData    (CSTRBstrobeWF,Edge3,ChanFirst,
                            StrobeOff,ThreshVITL,t[tCRDYHI]-t[tcH]+
                            t[tdRHSLw]+t[loosdelay4]-t[tgb]-ctcf+7ns,0,
                            StrobeOff,ThreshVITH,t[tCRDYLO]+
                            t[tdRLSHw]+t[loosdelay]-t[tgb]-ctcf+7ns,0);

        WaveSetStrobe       (CDstrobeWF,
                            t[tref]+t[tCSTRBfhi]-t[tsuCDw]+
                            t[loosdelay7]-t[tgb]-ctcf-7ns,
                            t[tref]+t[tCSTRBfhi]-t[tsuCDw]+
                            t[loosdelay7]-t[tgb]-ctcf,
                            t[tCRDYLO]+t[thCDw]-t[loosdelay7]+t[tgb]+ctcf);
        EdgeSetOrigin       (CDstrobeWF, Edge1, orgtCSTRBfhi);
        EdgeSetOrigin       (CDstrobeWF, Edge2, orgtCSTRBfhi);

(* CSTRB Edge1 is defined as DriveData here, but in actuality should always   *)
(* end up being a drive-low edge based on pattern data and translation.       *)

        WaveSetRTO          (CSTRBdriveWF,
                            t[tCSTRBLO],
                            t[tCSTRBHI]);
        EdgeSetOrigin       (CSTRBdriveWF, Edge1, orgtCSTRBfhi);
        EdgeSetOrigin       (CSTRBdriveWF, Edge2, orgtCSTRBfhi);

        WaveSetStrobe       (CRDY_SYNCstrobeWF,          (*special crdy_  strobe*)
                            t[tCSTRBLO]+t[tdSLRLr]-7ns,  (*w/o origin used for  *)
                            t[tCSTRBLO]+t[tdSLRLr],      (*sync-up only to avoid*)
                            t[tCSTRBLO]+t[tdSLRLr]+7ns); (*problems with bsearch*)

        EdgeSetDelayData    (CRDYstrobeWF,Edge1,ChanFirst,
                            DriveOff,ThreshVITL,t[tCSTRBLO]+
                            t[tdSLRLr]+t[loosdelay4]-t[tgb]-ctcf-7ns,0,
                            DriveOff,ThreshVITH,t[tCSTRBHI]+
                            t[tdSHRHr]+t[loosdelay]-t[tgb]-ctcf-7ns,0);

(* phq - Changed from loosedelay5 to sp   7/31/93 *)

        EdgeSetDelayData    (CRDYstrobeWF,Edge2,ChanFirst,
                            StrobeData,ThreshVITL,t[tCSTRBLO]+
                            t[tdSLRLr]+sp-t[tgb]-ctcf,0,
                            StrobeData,ThreshVITH,t[tCSTRBHI]+
                            t[tdSHRHr]+t[loosdelay]-t[tgb]-ctcf,0);
        EdgeSetDelayData    (CRDYstrobeWF,Edge3,ChanFirst,
                            StrobeOff,ThreshVITL,t[tCSTRBLO]+
                            t[tdSLRLr]+sp-t[tgb]-ctcf+7ns,0,
                            StrobeOff,ThreshVITH,t[tCSTRBHI]+
                            t[tdSHRHr]+t[loosdelay]-t[tgb]-ctcf+7ns,0);

        EdgeSetDelayData    (CDdriveWF,Edge1,ChanFirst,
                            DriveComplement,ThreshVITL,t[tCSTRBLO]-
                            t[tsuCDr]-t[loossetup]+dtcf-7ns,0,
                            DriveComplement,ThreshVITH,t[tCSTRBLO]-
                            t[tsuCDr]-t[looscd]-t[loossetup]+dtcf-7ns,0);
        EdgeSetDelayData    (CDdriveWF,Edge2,ChanFirst,
                            DriveData,ThreshVITL,t[tCSTRBLO]-
                            t[tsuCDr]-t[loossetup]+dtcf,0,
                            DriveData,ThreshVITH,t[tCSTRBLO]-
                            t[tsuCDr]-t[looscd]-t[loossetup]+dtcf,0);
        EdgeSetDelayData    (CDdriveWF,Edge3,ChanFirst,
                            DriveComplement,ThreshVITL,t[tref]+t[tCRDYflo]+
                            t[thCDr]+t[looscd]+t[looshold]-dtcf,0,
                            DriveComplement,ThreshVITH,t[tref]+t[tCRDYflo]+
                            t[thCDr]+t[looshold]-dtcf,0);


        WaveSetSBC          (TCLKdriveWF,
                            t[tref]+t[tH1flo]-t[tsuTCLK]-t[loossetup]+dtcf-7ns,
                            t[tref]+t[tH1flo]-t[tsuTCLK]-t[loossetup]+dtcf,
                            t[tref]+t[tH1flo]+t[thTCLK]+t[looshold]-dtcf);
        EdgeSetOrigin       (TCLKdriveWF, Edge1, orgtH1flo);
        EdgeSetOrigin       (TCLKdriveWF, Edge2, orgtH1flo);
        EdgeSetOrigin       (TCLKdriveWF, Edge3, orgtH1flo);

        WaveSetStrobe       (TCLKstrobeWF,
                            t[tref]+t[tdTCLK]+t[loosdelay6]-t[tgb]-ctcf-7ns,
                            t[tref]+t[tdTCLK]+t[loosdelay6]-t[tgb]-ctcf,
                            t[tref]+t[tdTCLK]+t[tcH]-t[restrict]-t[loosdelay]+
                            t[tgb]+ctcf);


        WaveSetRTO          (TCKCLKdriveWF,
                            t[tref],
                            t[tref]+t[tcCI]);

        WaveSetNR           (TCKdriveWF,
                            t[tref]);

        WaveSetSBC          (TDITMSdriveWF,
                            t[tref]+t[tcCI]-t[tsuTDITMS]-t[loossetup]+dtcf-7ns,
                            t[tref]+t[tcCI]-t[tsuTDITMS]-t[loossetup]+dtcf,
                            t[tref]+t[tcCI]+t[thTDITMS]+t[looshold]-dtcf);

        WaveSetNR           (JTAGdriveWF,
                            t[tref]+t[tJTAG]);

        WaveSetStrobe       (TDOstrobeWF,
                            0ns,
                            t[tref]+t[tdTDO]+t[loosdelay5]-t[loosdelay]-t[tgb]-ctcf,       (* changed loosedelay from 3 to 2*)
                            t[tref]+t[tdTDO]+t[loosdelay5]-t[loosdelay]-t[tgb]-ctcf+7ns);

        WaveSetEdgeStrobe   (JTAGH1strobeWF,
                            0ns,
                            t[tref]+t[tdTDO]+t[loosdelay]-t[tgb]-ctcf,
                            t[tref]+t[tdTDO]+t[loosdelay]-t[tgb]-ctcf+7ns);

        WaveSetEdgeStrobe   (JTAGVARYstrobeWF,
                            0ns,
                            t[tref]+t[tdTDO]+t[tcCI]+t[loosdelay]-t[tgb]-ctcf,
                            t[tref]+t[tdTDO]+t[tcCI]+t[loosdelay]-t[tgb]-ctcf+7ns);

        EdgeSet             (JTAGABUSstrobeWF,Edge1,StrobeOff,t[tref]+
                            t[tdTDO]-t[restrict]-t[loosdelay]+t[tgb]+ctcf);
        EdgeSet             (JTAGABUSstrobeWF,Edge2,DriveOff,t[tref]+
                            t[tdTDO]-t[restrict]-t[loosdelay]+t[tgb]+ctcf);
        EdgeSet             (JTAGABUSstrobeWF,Edge3,StrobeData,t[tref]+
                            t[tdTDO]+t[tcCI]+t[loosdelay]-t[tgb]-ctcf);

        WaveSetNR           (EMUdriveWF,
                            t[tref]+t[tEMU]);

        WaveSetStrobe       (EMUstrobeWF,
                            0ns,
                            t[tref]+t[tdEMU]+t[loosdelay]-t[tgb]-ctcf,
                            t[tref]+t[tdEMU]+t[loosdelay]-t[tgb]-ctcf+7ns);


        WaveSetNR           (RESETLOCdriveWF,
                            t[tref]+t[tRESETLOC]);

        WaveSetNR           (ROMENdriveWF,
                            t[tref]+t[tROMEN]);

        WaveSetNR           (NMIdriveWF,
                            t[tref]+t[tNMI]);


        WaveSetContinue     (ContinueWF);

        WaveSetOff          (ALLoffWF,t[tref],t[tref]);

STOP(ALLENUMS,TIhifrqloose40ACTable,TIsearchlevels40ACTable);

          end; (*4th case*)



        TIlofrqedgeACTable,
        TIlofrqedge60ACTable,
        TIhifrqedge40ACTable,
        TIhifrqedge50ACTable,
        TIhifrqedge60ACTable:
          begin

START(ALLENUMS,TIlofrqedgeACTable,TIlofrqedge60ACTable,TIhifrqedge40ACTable,TIhifrqedge50ACTable,TIhifrqedge60ACTable);

        WaveSetDoubleClk    (CLKINdriveWF,
                            t[tref]+t[toffset],
                            t[tref]+t[toffset]+t[twCIH],
                            t[tref]+t[toffset]+t[twCIH]+t[twCIL],
                            t[tref]+t[toffset]+t[twCIH]+t[twCIL]+t[twCIH]);
        EdgeSetOrigin       (CLKINdriveWF, Edge1, orgtoffset);
        EdgeSetOrigin       (CLKINdriveWF, Edge2, orgtoffset);
        EdgeSetOrigin       (CLKINdriveWF, Edge3, orgtoffset);
        EdgeSetOrigin       (CLKINdriveWF, Edge4, orgtoffset);

        EdgeSetDelayData    (RESETdriveWF,Edge1,ChanFirst,
                            DriveData,ThreshVITL,
                            t[tref]+t[toffset]+t[twCIH]+t[twCIL]+t[twCIH]-t[tsuRESET]-t[loossetup]+dtcf,0,
                            DriveData,ThreshVITH,
                            t[tref]+t[tH1flo]-t[tsuRESETH]-t[loossetup]+dtcf,0);

        WaveSetEdgeStrobe   (H1strobeWF,
                            0ns,
                            t[tref]+t[loosclock],
                            t[tref]+t[loosclock]+7ns);

        WaveSetEdgeStrobe   (H1HIGHstrobeWF,
                            0ns,
                            t[tref]+t[tH1flo]-t[tfHmax],
                            t[tref]+t[tH1flo]-t[tfHmax]+7ns);
        EdgeSetOrigin       (H1HIGHstrobeWF, Edge2, orgtH1high);
        EdgeSetOrigin       (H1HIGHstrobeWF, Edge3, orgtH1high);

        EdgeSet             (H1LOWstrobeWF,Edge1,DriveOff,
                            0ns);
        EdgeSet             (H1LOWstrobeWF,Edge2,EdgeStrobeLow,
                            t[tref]+t[tcH]-t[trHmax]);
        EdgeSet             (H1LOWstrobeWF,Edge3,StrobeLatch,
                            t[tref]+t[tcH]-t[trHmax]+7ns);
        EdgeSetOrigin       (H1LOWstrobeWF, Edge2, orgtH1low);
        EdgeSetOrigin       (H1LOWstrobeWF, Edge3, orgtH1low);

        WaveSetEdgeStrobe   (H1IDLEstrobeWF,
                            0ns,
                            t[tref]+t[tH1flo]+t[loosclock],
                            t[tref]+t[tH1flo]+t[loosclock]+7ns);

        WaveSetEdgeStrobe   (H3strobeWF,
                            0ns,
                            t[tref]+t[loosclock],
                            t[tref]+t[loosclock]+7ns);

        WaveSetEdgeStrobe   (H3LOWstrobeWF,
                            0ns,
                            t[tref]+t[tH3rhi]-t[trHmax],
                            t[tref]+t[tH3rhi]-t[trHmax]+7ns);
        EdgeSetOrigin       (H3LOWstrobeWF, Edge2, orgtH3low);
        EdgeSetOrigin       (H3LOWstrobeWF, Edge3, orgtH3low);

        EdgeSet             (H3HIGHstrobeWF,Edge1,DriveOff,
                            0ns);
        EdgeSet             (H3HIGHstrobeWF,Edge2,EdgeStrobeHigh,
                            t[tref]+t[tcH]+t[tH3flo]-t[tfHmax]);
        EdgeSet             (H3HIGHstrobeWF,Edge3,StrobeLatch,
                            t[tref]+t[tcH]+t[tH3flo]-t[tfHmax]+7ns);
        EdgeSetOrigin       (H3HIGHstrobeWF, Edge2, orgtH3high);
        EdgeSetOrigin       (H3HIGHstrobeWF, Edge3, orgtH3high);

        WaveSetEdgeStrobe   (H3IDLEstrobeWF,
                            0ns,
                            t[tref]+t[tH1flo]+t[loosclock],
                            t[tref]+t[tH1flo]+t[loosclock]+7ns);

        WaveSetEdgeStrobe   (STRBstrobeWF,
                            0ns,
                            t[tref]+t[tH1flo]+t[tdH1LS]+t[loosdelay7]-
                            t[tgb]-ctcf,
                            t[tref]+t[tH1flo]+t[tdH1LS]+t[loosdelay7]-
                            t[tgb]-ctcf+7ns);
        EdgeSetOrigin       (STRBstrobeWF, Edge2, orgtH1flo);
        EdgeSetOrigin       (STRBstrobeWF, Edge3, orgtH1flo);

        WaveSetEdgeStrobe   (RWstrobeWF,
                            0ns,
                            t[tref]+t[tdH1HRW]+t[loosdelay5]-t[tgb]-ctcf,
                            t[tref]+t[tdH1HRW]+t[loosdelay5]-t[tgb]-ctcf+7ns);

        WaveSetEdgeStrobe   (ABUSVstrobeWF,
                            0ns,
                            t[tref]+t[tH1flo]+t[tdH1LA]-t[restrict]-
                            t[loosdelay]+t[tgb]+ctcf+t[tcH]-7ns,
                            t[tref]+t[tH1flo]+t[tdH1LA]-t[restrict]-
                            t[loosdelay]+t[tgb]+ctcf+t[tcH]);
        EdgeSetOrigin       (ABUSVstrobeWF, Edge2, orgtH1flo);
        EdgeSetOrigin       (ABUSVstrobeWF, Edge3, orgtH1flo);

        WaveSetEdgeStrobe   (ABUSstrobeWF,
                            0ns,
                            t[tref]+t[tH1flo]+t[tdH1LA]+t[loosdelay7]-
                            t[tgb]-ctcf,
                            t[tref]+t[tH1flo]+t[tdH1LA]+t[loosdelay7]-
                            t[tgb]-ctcf+7ns);
        EdgeSetOrigin       (ABUSstrobeWF, Edge2, orgtH1flo);
        EdgeSetOrigin       (ABUSstrobeWF, Edge3, orgtH1flo);

        WaveSetEdgeStrobe   (ABUSWWstrobeWF,
                            0ns,
                            t[tref]+t[tdH1HA]+t[loosabus]-t[tgb]-ctcf,
                            t[tref]+t[tdH1HA]+t[loosabus]-t[tgb]-ctcf+7ns);

        WaveSetEdgeStrobe   (STATstrobeWF,
                            0ns,
                            t[tref]+t[tH1flo]+t[tdH1LSTAT]+t[loosdelay7]-
                            t[tgb]-ctcf,
                            t[tref]+t[tH1flo]+t[tdH1LSTAT]+t[loosdelay7]-
                            t[tgb]-ctcf+7ns);
        EdgeSetOrigin       (STATstrobeWF, Edge2, orgtH1flo);
        EdgeSetOrigin       (STATstrobeWF, Edge3, orgtH1flo);

        WaveSetEdgeStrobe   (LOCKstrobeWF,
                            0ns,
                            t[tref]+t[tH1flo]+t[tdH1LLOCK]+t[loosdelay4]-
                            t[tgb]-ctcf,
                            t[tref]+t[tH1flo]+t[tdH1LLOCK]+t[loosdelay4]-
                            t[tgb]-ctcf+7ns);
        EdgeSetOrigin       (LOCKstrobeWF, Edge2, orgtH1flo);
        EdgeSetOrigin       (LOCKstrobeWF, Edge3, orgtH1flo);

        WaveSetSBC          (DBUSdriveWF,
                            t[tref]+t[tH1flo]-t[tsuDR]-t[loossetup]+dtcf-7ns,
                            t[tref]+t[tH1flo]-t[tsuDR]-t[loossetup]+dtcf,
                            t[tref]+t[tH1flo]+t[thDR]+t[looshold]-dtcf);
        EdgeSetOrigin       (DBUSdriveWF, Edge1, orgtH1flo);
        EdgeSetOrigin       (DBUSdriveWF, Edge2, orgtH1flo);
        EdgeSetOrigin       (DBUSdriveWF, Edge3, orgtH1flo);

        WaveSetEdgeStrobe   (DBUSstrobeWF,
                            t[tref]+t[tH1flo]+t[tvDW]+t[loosdelay4]-
                            t[tgb]-ctcf-7ns,
                            t[tref]+t[tH1flo]+t[tvDW]+t[loosdelay4]-
                            t[tgb]-ctcf,
                            t[tref]+t[tH1flo]+t[tvDW]+t[loosdelay4]-
                            t[tgb]-ctcf+7ns);
        EdgeSetOrigin       (DBUSstrobeWF, Edge1, orgtH1flo);
        EdgeSetOrigin       (DBUSstrobeWF, Edge2, orgtH1flo);
        EdgeSetOrigin       (DBUSstrobeWF, Edge3, orgtH1flo);

        EdgeSet             (DBUSstrobeoffWF,Edge1,NullEdge,
                            t[tref]+t[thDW]-t[loosdelay]+t[tgb]+ctcf);

        WaveSetEdgeStrobe   (DBUSWWstrobeWF,
                            t[tref]+t[tH1flo]+t[tvDW]+t[loosdelay4]-
                            t[tgb]-ctcf-7ns,
                            t[tref]+t[tH1flo]+t[tvDW]+t[loosdelay4]-
                            t[tgb]-ctcf,
                            t[tref]+t[tH1flo]+t[tvDW]+t[loosdelay4]-
                            t[tgb]-ctcf+7ns);
        EdgeSetOrigin       (DBUSWWstrobeWF, Edge1, orgtH1flo);
        EdgeSetOrigin       (DBUSWWstrobeWF, Edge2, orgtH1flo);
        EdgeSetOrigin       (DBUSWWstrobeWF, Edge3, orgtH1flo);

        WaveSetEdgeStrobe   (DBUSWW2strobeWF,
                            t[tref]+t[tH1flo]+t[tvDW]+t[loosdelay4]-
                            t[tgb]-ctcf-7ns,
                            t[tref]+t[tH1flo]+t[tvDW]+t[loosdelay4]-
                            t[tgb]-ctcf,
                            t[tref]+t[tH1flo]+t[tvDW]+t[loosdelay4]-
                            t[tgb]-ctcf+7ns);
        EdgeSetOrigin       (DBUSWW2strobeWF, Edge1, orgtH1flo);
        EdgeSetOrigin       (DBUSWW2strobeWF, Edge2, orgtH1flo);
        EdgeSetOrigin       (DBUSWW2strobeWF, Edge3, orgtH1flo);

        WaveSetRTO          (RDYdriveWF,
                            t[tref]+t[tH1flo]-t[tsuRDY]-t[loossetup]+dtcf,
                            t[tref]+t[tH1flo]+t[thRDY]+t[looshold]-dtcf);
        EdgeSetOrigin       (RDYdriveWF, Edge1, orgtH1flo);
        EdgeSetOrigin       (RDYdriveWF, Edge2, orgtH1flo);

        WaveSetNR           (ENBdriveWF,
                            t[tref]+t[tENB]);

        WaveSetEdgeStrobeZ  (DBUSHIZstrobeWF,
                            0ns,
                            t[tref]+t[tENB]+t[tdENBZ]+t[loosdelay]-ctcf,
                            t[tref]+t[tENB]+t[tdENBZ]+t[loosdelay]-ctcf+7ns);

        WaveSetEdgeStrobeZ  (ABUSHIZstrobeWF,
                            0ns,
                            t[tref]+t[tENB]+t[tdENBZ]+t[loosdelay]-ctcf,
                            t[tref]+t[tENB]+t[tdENBZ]+t[loosdelay]-ctcf+7ns);

        WaveSetEdgeStrobeZ  (CTRLHIZstrobeWF,
                            0ns,
                            t[tref]+t[tENB]+t[tdENBZ]+t[loosdelay]-ctcf,
                            t[tref]+t[tENB]+t[tdENBZ]+t[loosdelay]-ctcf+7ns);

        WaveSetEdgeStrobe   (DBUSVALstrobeWF,
                            0ns,
                            t[tref]+t[tENB]+t[tdENBDV]+t[loosdelay4]-
                            t[tgb]-ctcf,
                            t[tref]+t[tENB]+t[tdENBDV]+t[loosdelay4]-
                            t[tgb]-ctcf+7ns);

        WaveSetEdgeStrobe   (ABUSVALstrobeWF,
                            0ns,
                            t[tref]+t[tENB]+t[tdENBAV]+t[loosdelay7]-
                            t[tgb]-ctcf,
                            t[tref]+t[tENB]+t[tdENBAV]+t[loosdelay7]-
                            t[tgb]-ctcf+6ns);

        WaveSetEdgeStrobe   (CTRLVALstrobeWF,
                            0ns,
                            t[tref]+t[tENB]+t[tdENBCV]+t[loosdelay]-
                            t[tgb]-ctcf,
                            t[tref]+t[tENB]+t[tdENBCV]+t[loosdelay]-
                            t[tgb]-ctcf+6ns);


        WaveSetSBC          (IIOFdriveWF,
                            t[tref]+t[tH1flo]-t[tsuIF]-t[loossetup]+dtcf-7ns,
                            t[tref]+t[tH1flo]-t[tsuIF]-t[loossetup]+dtcf,
                            t[tref]+t[tH1flo]+t[thIF]+t[looshold]-dtcf);
        EdgeSetOrigin       (IIOFdriveWF, Edge1, orgtH1flo);
        EdgeSetOrigin       (IIOFdriveWF, Edge2, orgtH1flo);
        EdgeSetOrigin       (IIOFdriveWF, Edge3, orgtH1flo);

        WaveSetEdgeStrobe   (IIOFstrobeWF,
                            t[tref]+t[tH1flo]+t[tvH1LIF]+t[loosdelay]-
                            t[tgb]-ctcf-7ns,
                            t[tref]+t[tH1flo]+t[tvH1LIF]+t[loosdelay]-
                            t[tgb]-ctcf,
                            t[tref]+t[tH1flo]+t[tvH1LIF]+t[loosdelay]-
                            t[tgb]-ctcf+7ns);
        EdgeSetOrigin       (IIOFstrobeWF, Edge1, orgtH1flo);
        EdgeSetOrigin       (IIOFstrobeWF, Edge2, orgtH1flo);
        EdgeSetOrigin       (IIOFstrobeWF, Edge3, orgtH1flo);

        EdgeSet             (IIOFstrobeoffWF,Edge1,NullEdge,
                            t[tref]+t[tH1flo]+t[thH1LIFOI]-t[loosdelay]+
                            t[tgb]+ctcf);
        EdgeSetOrigin       (IIOFstrobeoffWF, Edge1, orgtH1flo);

        WaveSetEdgeStrobe   (IIOFWWstrobeWF,
                            t[tref]+t[tH1flo]+t[tvH1LIF]+t[loosdelay]-
                            t[tgb]-ctcf-7ns,
                            t[tref]+t[tH1flo]+t[tvH1LIF]+t[loosdelay]-
                            t[tgb]-ctcf,
                            t[tref]+t[tH1flo]+t[tvH1LIF]+t[loosdelay]-
                            t[tgb]-ctcf+7ns);
        EdgeSetOrigin       (IIOFWWstrobeWF, Edge1, orgtH1flo);
        EdgeSetOrigin       (IIOFWWstrobeWF, Edge2, orgtH1flo);
        EdgeSetOrigin       (IIOFWWstrobeWF, Edge3, orgtH1flo);

        WaveSetNR           (INTdriveWF,
                            t[tref]+t[tH1flo]-t[tsuINT]-t[loossetup]+dtcf);
        EdgeSetOrigin       (INTdriveWF, Edge1, orgtH1flo);

        WaveSetNR           (INTIDLEdriveWF,
                            t[tref]+t[tH1flo]-t[tsuINTIDLE]-t[loossetup]+dtcf);
        EdgeSetOrigin       (INTdriveWF, Edge1, orgtH1flo);

        WaveSetEdgeStrobe   (IACKstrobeWF,
                            0ns,
                            t[tref]+t[tH1flo]+t[tdH1LIACK]+t[loosdelay6]-
                            t[tgb]-ctcf,
                            t[tref]+t[tH1flo]+t[tdH1LIACK]+t[loosdelay6]-
                            t[tgb]-ctcf+7ns);
        EdgeSetOrigin       (IACKstrobeWF, Edge2, orgtH1flo);
        EdgeSetOrigin       (IACKstrobeWF, Edge3, orgtH1flo);


        EdgeSetDelayData    (CREQdriveWF,Edge1,ChanFirst,
                            DriveData,ThreshVITL,
                            t[tref]+t[tH1flo]-t[tsuCREQ],0,
                            DriveData,ThreshVITH,
                            t[tref]+t[tH1flo]+t[tsuCREQ],0);

        EdgeSetDelayData    (CREQstrobeWF,Edge1,ChanFirst,
                            DriveOff,ThreshVITL,t[tref]+
                            t[tdH1HRQLt]+t[loosdelay]-t[tgb]-ctcf-7ns,0,
                            DriveOff,ThreshVITH,t[tref]+
                            t[tH1flo]-t[tsuCACK]+t[tdALRQHt]+
                            t[loosdelay]-t[tgb]-ctcf-7ns,0);
        EdgeSetDelayData    (CREQstrobeWF,Edge2,ChanFirst,
                            EdgeStrobeData,ThreshVITL,t[tref]+
                            t[tdH1HRQLt]+t[loosdelay]-t[tgb]-ctcf,0,
                            EdgeStrobeData,ThreshVITH,t[tref]+
                            t[tH1flo]-t[tsuCACK]+t[tdALRQHt]+
                            t[loosdelay]-t[tgb]-ctcf,0);
        EdgeSetDelayData    (CREQstrobeWF,Edge3,ChanFirst,
                            StrobeLatch,ThreshVITL,t[tref]+
                            t[tdH1HRQLt]+t[loosdelay]-t[tgb]-ctcf+7ns,0,
                            StrobeLatch,ThreshVITH,t[tref]+
                            t[tH1flo]-t[tsuCACK]+t[tdALRQHt]+
                            t[loosdelay]-t[tgb]-ctcf+7ns,0);

        EdgeSetDelayData    (CREQ2strobeWF,Edge1,ChanFirst,
                            DriveOff,ThreshVITL,t[tref]+
                            t[tH1flo]+t[tsuCREQ]+t[tdRQHRQLt]+
                            t[loosdelay]-t[tgb]-ctcf-7ns,0,
                            DriveOff,ThreshVITH,t[tref]+
                            t[tH1flo]+t[tsuCREQ]+t[tdRQHRQOt]+
                            t[loosdelay]-t[tgb]-ctcf-7ns,0);
        EdgeSetDelayData    (CREQ2strobeWF,Edge2,ChanFirst,
                            EdgeStrobeData,ThreshVITL,t[tref]+
                            t[tH1flo]+t[tsuCREQ]+t[tdRQHRQLt]+
                            t[loosdelay]-t[tgb]-ctcf,0,
                            EdgeStrobeData,ThreshVITH,t[tref]+
                            t[tH1flo]+t[tsuCREQ]+t[tdRQHRQOt]+
                            t[loosdelay]-t[tgb]-ctcf,0);
        EdgeSetDelayData    (CREQ2strobeWF,Edge3,ChanFirst,
                            StrobeLatch,ThreshVITL,t[tref]+
                            t[tH1flo]+t[tsuCREQ]+t[tdRQHRQLt]+
                            t[loosdelay]-t[tgb]-ctcf+7ns,0,
                            StrobeLatch,ThreshVITH,t[tref]+
                            t[tH1flo]+t[tsuCREQ]+t[tdRQHRQOt]+
                            t[loosdelay]-t[tgb]-ctcf+7ns,0);

        WaveSetNR           (CACKdriveWF,
                            t[tref]+t[tH1flo]-t[tsuCACK]);
        EdgeSetOrigin       (CACKdriveWF, Edge1, orgtH1flo);

        WaveSetEdgeStrobe   (CACKstrobeWF,
                            t[tref]+t[tH1flo]-t[tsuCREQ]+t[tdRQLALt]+
                            t[loosdelay7]-t[tgb]-ctcf-7ns,
                            t[tref]+t[tH1flo]-t[tsuCREQ]+t[tdRQLALt]+
                            t[loosdelay7]-t[tgb]-ctcf,
                            t[tref]+t[tH1flo]-t[tsuCREQ]+t[tdRQLALt]+
                            t[loosdelay7]-t[tgb]-ctcf+7ns);
        EdgeSetOrigin       (CACKstrobeWF, Edge1, orgtH1flo);
        EdgeSetOrigin       (CACKstrobeWF, Edge2, orgtH1flo);
        EdgeSetOrigin       (CACKstrobeWF, Edge3, orgtH1flo);

(* CRDY  Edge1 is defined as DriveData here, but in actuality should always   *)
(* end up being a drive-low edge based on pattern data and translation.       *)

        WaveSetRTO          (CRDYdriveWF,
                            t[tCRDYLO],
                            t[tCRDYHI]);

(* special cstrb_ strobe w/o origin used for sync-up only to avoid problems   *)
(* with bsearch.                                                              *)

        WaveSetEdgeStrobe   (CSTRB_SYNCstrobeWF,
                            t[tCRDYHI]-t[tcH]+t[tdRHSLw]-7ns,
                            t[tCRDYHI]-t[tcH]+t[tdRHSLw],
                            t[tCRDYHI]-t[tcH]+t[tdRHSLw]+7ns);

        EdgeSetDelayData    (CSTRBstrobeWF,Edge1,ChanFirst,
                            DriveOff,ThreshVITL,t[tCRDYHI]-t[tcH]+
                            t[tdRHSLw]+t[loosdelay6]-t[tgb]-ctcf-7ns,0,
                            DriveOff,ThreshVITH,t[tCRDYLO]+
                            t[tdRLSHw]+t[loosdelay]-t[tgb]-ctcf-7ns,0);
        EdgeSetDelayData    (CSTRBstrobeWF,Edge2,ChanFirst,
                            EdgeStrobeData,ThreshVITL,t[tCRDYHI]-t[tcH]+
                            t[tdRHSLw]+t[loosdelay6]-t[tgb]-ctcf,0,
                            EdgeStrobeData,ThreshVITH,t[tCRDYLO]+
                            t[tdRLSHw]+t[loosdelay]-t[tgb]-ctcf,0);
        EdgeSetDelayData    (CSTRBstrobeWF,Edge3,ChanFirst,
                            StrobeLatch,ThreshVITL,t[tCRDYHI]-t[tcH]+
                            t[tdRHSLw]+t[loosdelay6]-t[tgb]-ctcf+7ns,0,
                            StrobeLatch,ThreshVITH,t[tCRDYLO]+
                            t[tdRLSHw]+t[loosdelay]-t[tgb]-ctcf+7ns,0);

        WaveSetEdgeStrobe   (CDstrobeWF,
                            t[tref]+t[tCSTRBfhi]-t[tsuCDw]+
                            t[loosdelay]-t[tgb]-ctcf-7ns,
                            t[tref]+t[tCSTRBfhi]-t[tsuCDw]+
                            t[loosdelay]-t[tgb]-ctcf,
                            t[tref]+t[tCSTRBfhi]-t[tsuCDw]+
                            t[loosdelay]-t[tgb]-ctcf+7ns);
        EdgeSetOrigin       (CDstrobeWF, Edge1, orgtCSTRBfhi);
        EdgeSetOrigin       (CDstrobeWF, Edge2, orgtCSTRBfhi);
        EdgeSetOrigin       (CDstrobeWF, Edge3, orgtCSTRBfhi);

(* CSTRB Edge1 is defined as DriveData here, but in actuality should always   *)
(* end up being a drive-low edge based on pattern data and translation.       *)

        WaveSetRTO          (CSTRBdriveWF,
                            t[tCSTRBLO],
                            t[tCSTRBHI]);
        EdgeSetOrigin       (CSTRBdriveWF, Edge1, orgtCSTRBfhi);
        EdgeSetOrigin       (CSTRBdriveWF, Edge2, orgtCSTRBfhi);

        WaveSetEdgeStrobe   (CRDY_SYNCstrobeWF,          (*special crdy_  strobe*)
                            t[tCSTRBLO]+t[tdSLRLr]-7ns,  (*w/o origin used for  *)
                            t[tCSTRBLO]+t[tdSLRLr],      (*sync-up only to avoid*)
                            t[tCSTRBLO]+t[tdSLRLr]+7ns); (*problems with bsearch*)

        EdgeSetDelayData    (CRDYstrobeWF,Edge1,ChanFirst,
                            DriveOff,ThreshVITL,t[tCSTRBLO]+
                            t[tdSLRLr]+t[loosdelay4]-t[tgb]-ctcf-7ns,0,
                            DriveOff,ThreshVITH,t[tCSTRBHI]+
                            t[tdSHRHr]+t[loosdelay]-t[tgb]-ctcf-7ns,0);
        EdgeSetDelayData    (CRDYstrobeWF,Edge2,ChanFirst,
                            EdgeStrobeData,ThreshVITL,t[tCSTRBLO]+
                            t[tdSLRLr]+t[loosdelay4]-t[tgb]-ctcf,0,
                            EdgeStrobeData,ThreshVITH,t[tCSTRBHI]+
                            t[tdSHRHr]+t[loosdelay]-t[tgb]-ctcf,0);
        EdgeSetDelayData    (CRDYstrobeWF,Edge3,ChanFirst,
                            StrobeLatch,ThreshVITL,t[tCSTRBLO]+
                            t[tdSLRLr]+t[loosdelay4]-t[tgb]-ctcf+7ns,0,
                            StrobeLatch,ThreshVITH,t[tCSTRBHI]+
                            t[tdSHRHr]+t[loosdelay]-t[tgb]-ctcf+7ns,0);

        EdgeSetDelayData    (CDdriveWF,Edge1,ChanFirst,
                            DriveComplement,ThreshVITL,t[tCSTRBLO]-
                            t[tsuCDr]-t[loossetup]+dtcf-7ns,0,
                            DriveComplement,ThreshVITH,t[tCSTRBLO]-
                            t[tsuCDr]-t[looscd]-t[loossetup]+dtcf-7ns,0);
        EdgeSetDelayData    (CDdriveWF,Edge2,ChanFirst,
                            DriveData,ThreshVITL,t[tCSTRBLO]-
                            t[tsuCDr]-t[loossetup]+dtcf,0,
                            DriveData,ThreshVITH,t[tCSTRBLO]-
                            t[tsuCDr]-t[looscd]-t[loossetup]+dtcf,0);
        EdgeSetDelayData    (CDdriveWF,Edge3,ChanFirst,
                            DriveComplement,ThreshVITL,t[tref]+t[tCRDYflo]+
                            t[thCDr]+t[looscd]+t[looshold]-dtcf,0,
                            DriveComplement,ThreshVITH,t[tref]+t[tCRDYflo]+
                            t[thCDr]+t[looshold]-dtcf,0);


        WaveSetSBC          (TCLKdriveWF,
                            t[tref]+t[tH1flo]-t[tsuTCLK]-t[loossetup]+dtcf-7ns,
                            t[tref]+t[tH1flo]-t[tsuTCLK]-t[loossetup]+dtcf,
                            t[tref]+t[tH1flo]+t[thTCLK]+t[looshold]-dtcf);
        EdgeSetOrigin       (TCLKdriveWF, Edge1, orgtH1flo);
        EdgeSetOrigin       (TCLKdriveWF, Edge2, orgtH1flo);
        EdgeSetOrigin       (TCLKdriveWF, Edge3, orgtH1flo);

        WaveSetEdgeStrobe   (TCLKstrobeWF,
                            t[tref]+t[tdTCLK]+t[loosdelay4]-t[tgb]-ctcf-7ns,
                            t[tref]+t[tdTCLK]+t[loosdelay4]-t[tgb]-ctcf,
                            t[tref]+t[tdTCLK]+t[loosdelay4]-t[tgb]-ctcf+7ns);


        WaveSetRTO          (TCKCLKdriveWF,
                            t[tref],
                            t[tref]+t[tcCI]);

        WaveSetNR           (TCKdriveWF,
                            t[tref]);

        WaveSetSBC          (TDITMSdriveWF,
                            t[tref]+t[tcCI]-t[tsuTDITMS]-t[loossetup]+dtcf-7ns,
                            t[tref]+t[tcCI]-t[tsuTDITMS]-t[loossetup]+dtcf,
                            t[tref]+t[tcCI]+t[thTDITMS]+t[looshold]-dtcf);

        WaveSetNR           (JTAGdriveWF,
                            t[tref]+t[tJTAG]);

        WaveSetEdgeStrobe   (TDOstrobeWF,
                            0ns,
                            t[tref]+t[tdTDO]+t[loosdelay]-t[tgb]-ctcf,
                            t[tref]+t[tdTDO]+t[loosdelay]-t[tgb]-ctcf+7ns);

        WaveSetEdgeStrobe   (JTAGH1strobeWF,
                            0ns,
                            t[tref]+t[tdTDO]+t[loosdelay]-t[tgb]-ctcf,
                            t[tref]+t[tdTDO]+t[loosdelay]-t[tgb]-ctcf+7ns);

        WaveSetEdgeStrobe   (JTAGVARYstrobeWF,
                            0ns,
                            t[tref]+t[tdTDO]+t[tcCI]+t[loosdelay]-t[tgb]-ctcf,
                            t[tref]+t[tdTDO]+t[tcCI]+t[loosdelay]-t[tgb]-ctcf+7ns);

        WaveSetEdgeStrobe   (JTAGABUSstrobeWF,
                            0ns,
                            t[tref]+t[tdTDO]+t[tcCI]+t[loosdelay]-t[tgb]-ctcf,
                            t[tref]+t[tdTDO]+t[tcCI]+t[loosdelay]-t[tgb]-ctcf+7ns);


        WaveSetNR           (EMUdriveWF,
                            t[tref]+t[tEMU]);

        WaveSetEdgeStrobe   (EMUstrobeWF,
                            0ns,
                            t[tref]+t[tdEMU]+t[loosdelay]-t[tgb]-ctcf,
                            t[tref]+t[tdEMU]+t[loosdelay]-t[tgb]-ctcf+7ns);


        WaveSetNR           (RESETLOCdriveWF,
                            t[tref]+t[tRESETLOC]);

        WaveSetNR           (ROMENdriveWF,
                            t[tref]+t[tROMEN]);

        WaveSetNR           (NMIdriveWF,
                            t[tref]+t[tNMI]);


        WaveSetContinue     (ContinueWF);

        WaveSetOff          (ALLoffWF,t[tref],t[tref]);

STOP(ALLENUMS,TIlofrqedgeACTable,TIlofrqedge60ACTable,TIhifrqedge40ACTable,TIhifrqedge50ACTable,TIhifrqedge60ACTable);

          end; (*5th case*)




        TIspecsetupmin25ACTable,
        TIspecsetupmax25ACTable,
        TIsearch25ACTable,
        TIchar25ACTable:
          begin
START(ALLENUMS,TIspecsetupmin25ACTable,TIspecsetupmax25ACTable,TIsearch25ACTable,TIchar25ACTable);


        WaveSetDoubleClk    (CLKINdriveWF,
                            t[tref]+t[toffset],
                            t[tref]+t[toffset]+t[twCIH],
                            t[tref]+t[toffset]+t[twCIH]+t[twCIL],
                            t[tref]+t[toffset]+t[twCIH]+t[twCIL]+t[twCIH]);
        EdgeSetOrigin       (CLKINdriveWF, Edge1, orgtoffset);
        EdgeSetOrigin       (CLKINdriveWF, Edge2, orgtoffset);
        EdgeSetOrigin       (CLKINdriveWF, Edge3, orgtoffset);
        EdgeSetOrigin       (CLKINdriveWF, Edge4, orgtoffset);

        EdgeSetDelayData    (RESETdriveWF,Edge1,ChanFirst,
                            DriveData,ThreshVITL,
                            t[tref]+t[toffset]+t[twCIH]+t[twCIL]+t[twCIH]-t[tsuRESET]-t[loossetup]+dtcf,0,
                            DriveData,ThreshVITH,
                            t[tref]+t[tH1flo]-t[tsuRESETH]-t[loossetup]+dtcf,0);

        WaveSetEdgeStrobe   (H1strobeWF,
                            0ns,
                            t[tref]+t[loosclock],
                            t[tref]+t[loosclock]+7ns);

        WaveSetEdgeStrobe   (H1HIGHstrobeWF,
                            0ns,
                            t[tref]+t[tH1flo]-t[tfHmax],
                            t[tref]+t[tH1flo]-t[tfHmax]+7ns);
        EdgeSetOrigin       (H1HIGHstrobeWF, Edge2, orgtH1high);
        EdgeSetOrigin       (H1HIGHstrobeWF, Edge3, orgtH1high);

        EdgeSet             (H1LOWstrobeWF,Edge1,DriveOff,
                            0ns);
        EdgeSet             (H1LOWstrobeWF,Edge2,EdgeStrobeLow,
                            t[tref]+t[tcH]-t[trHmax]);
        EdgeSet             (H1LOWstrobeWF,Edge3,StrobeLatch,
                            t[tref]+t[tcH]-t[trHmax]+7ns);
        EdgeSetOrigin       (H1LOWstrobeWF, Edge2, orgtH1low);
        EdgeSetOrigin       (H1LOWstrobeWF, Edge3, orgtH1low);

        WaveSetEdgeStrobe   (H1IDLEstrobeWF,
                            0ns,
                            t[tref]+t[tH1flo]+t[loosclock],
                            t[tref]+t[tH1flo]+t[loosclock]+7ns);

        WaveSetEdgeStrobe   (H3strobeWF,
                            0ns,
                            t[tref]+t[loosclock],
                            t[tref]+t[loosclock]+7ns);

        WaveSetEdgeStrobe   (H3LOWstrobeWF,
                            0ns,
                            t[tref]+t[tH3rhi]-t[trHmax],
                            t[tref]+t[tH3rhi]-t[trHmax]+7ns);
        EdgeSetOrigin       (H3LOWstrobeWF, Edge2, orgtH3low);
        EdgeSetOrigin       (H3LOWstrobeWF, Edge3, orgtH3low);

        EdgeSet             (H3HIGHstrobeWF,Edge1,DriveOff,
                            0ns);
        EdgeSet             (H3HIGHstrobeWF,Edge2,EdgeStrobeHigh,
                            t[tref]+t[tcH]+t[tH3flo]-t[tfHmax]);
        EdgeSet             (H3HIGHstrobeWF,Edge3,StrobeLatch,
                            t[tref]+t[tcH]+t[tH3flo]-t[tfHmax]+7ns);
        EdgeSetOrigin       (H3HIGHstrobeWF, Edge2, orgtH3high);
        EdgeSetOrigin       (H3HIGHstrobeWF, Edge3, orgtH3high);

        WaveSetEdgeStrobe   (H3IDLEstrobeWF,
                            0ns,
                            t[tref]+t[tH1flo]+t[loosclock],
                            t[tref]+t[tH1flo]+t[loosclock]+7ns);

        WaveSetEdgeStrobe   (STRBstrobeWF,
                            0ns,
                            t[tref]+t[tH1flo]+t[tdH1LS]+t[loosdelay7]-
                            t[tgb]-ctcf,
                            t[tref]+t[tH1flo]+t[tdH1LS]+t[loosdelay7]-
                            t[tgb]-ctcf+7ns);
        EdgeSetOrigin       (STRBstrobeWF, Edge2, orgtH1flo);
        EdgeSetOrigin       (STRBstrobeWF, Edge3, orgtH1flo);

        WaveSetEdgeStrobe   (RWstrobeWF,
                            0ns,
                            t[tref]+t[tdH1HRW]+t[loosdelay5]-t[tgb]-ctcf,
                            t[tref]+t[tdH1HRW]+t[loosdelay5]-t[tgb]-ctcf+7ns);

        WaveSetEdgeStrobe   (ABUSVstrobeWF,
                            0ns,
                            t[tref]+t[tH1flo]+t[tdH1LA]-t[restrict]-
                            t[loosdelay]+t[tgb]+ctcf+t[tcH]-7ns,
                            t[tref]+t[tH1flo]+t[tdH1LA]-t[restrict]-
                            t[loosdelay]+t[tgb]+ctcf+t[tcH]);
        EdgeSetOrigin       (ABUSVstrobeWF, Edge2, orgtH1flo);
        EdgeSetOrigin       (ABUSVstrobeWF, Edge3, orgtH1flo);

        WaveSetEdgeStrobe   (ABUSstrobeWF,
                            0ns,
                            t[tref]+t[tH1flo]+t[tdH1LA]+t[loosdelay7]-
                            t[tgb]-ctcf,
                            t[tref]+t[tH1flo]+t[tdH1LA]+t[loosdelay7]-
                            t[tgb]-ctcf+7ns);
        EdgeSetOrigin       (ABUSstrobeWF, Edge2, orgtH1flo);
        EdgeSetOrigin       (ABUSstrobeWF, Edge3, orgtH1flo);

        WaveSetEdgeStrobe   (ABUSWWstrobeWF,
                            0ns,
                            t[tref]+t[tdH1HA]+t[loosabus]-t[tgb]-ctcf,
                            t[tref]+t[tdH1HA]+t[loosabus]-t[tgb]-ctcf+7ns);

        WaveSetEdgeStrobe   (STATstrobeWF,
                            0ns,
                            t[tref]+t[tH1flo]+t[tdH1LSTAT]+t[loosdelay7]-
                            t[tgb]-ctcf,
                            t[tref]+t[tH1flo]+t[tdH1LSTAT]+t[loosdelay7]-
                            t[tgb]-ctcf+7ns);
        EdgeSetOrigin       (STATstrobeWF, Edge2, orgtH1flo);
        EdgeSetOrigin       (STATstrobeWF, Edge3, orgtH1flo);

        WaveSetEdgeStrobe   (LOCKstrobeWF,
                            0ns,
                            t[tref]+t[tH1flo]+t[tdH1LLOCK]+t[loosdelay4]-
                            t[tgb]-ctcf,
                            t[tref]+t[tH1flo]+t[tdH1LLOCK]+t[loosdelay4]-
                            t[tgb]-ctcf+7ns);
        EdgeSetOrigin       (LOCKstrobeWF, Edge2, orgtH1flo);
        EdgeSetOrigin       (LOCKstrobeWF, Edge3, orgtH1flo);

        WaveSetSBC          (DBUSdriveWF,
                            t[tref]+t[tH1flo]-t[tsuDR]-t[loossetup]+dtcf-7ns,
                            t[tref]+t[tH1flo]-t[tsuDR]-t[loossetup]+dtcf,
                            t[tref]+t[tH1flo]+t[thDR]+t[looshold]-dtcf);
        EdgeSetOrigin       (DBUSdriveWF, Edge1, orgtH1flo);
        EdgeSetOrigin       (DBUSdriveWF, Edge2, orgtH1flo);
        EdgeSetOrigin       (DBUSdriveWF, Edge3, orgtH1flo);

        WaveSetEdgeStrobe   (DBUSstrobeWF,
                            t[tref]+t[tH1flo]+t[tvDW]+t[loosdelay4]-
                            t[tgb]-ctcf-7ns,
                            t[tref]+t[tH1flo]+t[tvDW]+t[loosdelay4]-
                            t[tgb]-ctcf,
                            t[tref]+t[tH1flo]+t[tvDW]+t[loosdelay4]-
                            t[tgb]-ctcf+7ns);
        EdgeSetOrigin       (DBUSstrobeWF, Edge1, orgtH1flo);
        EdgeSetOrigin       (DBUSstrobeWF, Edge2, orgtH1flo);
        EdgeSetOrigin       (DBUSstrobeWF, Edge3, orgtH1flo);

        EdgeSet             (DBUSstrobeoffWF,Edge1,NullEdge,
                            t[tref]+t[thDW]-t[loosdelay]+t[tgb]+ctcf);

        WaveSetEdgeStrobe   (DBUSWWstrobeWF,
                            t[tref]+t[tH1flo]+t[tvDW]+t[loosdelay4]-
                            t[tgb]-ctcf-7ns,
                            t[tref]+t[tH1flo]+t[tvDW]+t[loosdelay4]-
                            t[tgb]-ctcf,
                            t[tref]+t[tH1flo]+t[tvDW]+t[loosdelay4]-
                            t[tgb]-ctcf+7ns);
        EdgeSetOrigin       (DBUSWWstrobeWF, Edge1, orgtH1flo);
        EdgeSetOrigin       (DBUSWWstrobeWF, Edge2, orgtH1flo);
        EdgeSetOrigin       (DBUSWWstrobeWF, Edge3, orgtH1flo);


        WaveSetEdgeStrobe   (DBUSWW2strobeWF,
                            t[tref]+t[tH1flo]+t[tvDW]+t[loosdelay4]-
                            t[tgb]-ctcf-7ns,
                            t[tref]+t[tH1flo]+t[tvDW]+t[loosdelay4]-
                            t[tgb]-ctcf,
                            t[tref]+t[tH1flo]+t[tvDW]+t[loosdelay4]-
                            t[tgb]-ctcf+7ns);
        EdgeSetOrigin       (DBUSWW2strobeWF, Edge1, orgtH1flo);
        EdgeSetOrigin       (DBUSWW2strobeWF, Edge2, orgtH1flo);
        EdgeSetOrigin       (DBUSWW2strobeWF, Edge3, orgtH1flo);

        WaveSetRTO          (RDYdriveWF,
                            t[tref]+t[tH1flo]-t[tsuRDY]-t[loossetup]+dtcf,
                            t[tref]+t[tH1flo]+t[thRDY]+t[looshold]-dtcf);
        EdgeSetOrigin       (RDYdriveWF, Edge1, orgtH1flo);
        EdgeSetOrigin       (RDYdriveWF, Edge2, orgtH1flo);

        WaveSetNR           (ENBdriveWF,
                            t[tref]+t[tENB]);

        WaveSetEdgeStrobeZ  (DBUSHIZstrobeWF,
                            0ns,
                            t[tref]+t[tENB]+t[tdENBZ]+t[loosdelay]-ctcf,
                            t[tref]+t[tENB]+t[tdENBZ]+t[loosdelay]-ctcf+7ns);

        WaveSetEdgeStrobeZ  (ABUSHIZstrobeWF,
                            0ns,
                            t[tref]+t[tENB]+t[tdENBZ]+t[loosdelay]-ctcf,
                            t[tref]+t[tENB]+t[tdENBZ]+t[loosdelay]-ctcf+7ns);

        WaveSetEdgeStrobeZ  (CTRLHIZstrobeWF,
                            0ns,
                            t[tref]+t[tENB]+t[tdENBZ]+t[loosdelay]-ctcf,
                            t[tref]+t[tENB]+t[tdENBZ]+t[loosdelay]-ctcf+7ns);

        WaveSetEdgeStrobe   (DBUSVALstrobeWF,
                            0ns,
                            t[tref]+t[tENB]+t[tdENBDV]+t[loosdelay4]-
                            t[tgb]-ctcf,
                            t[tref]+t[tENB]+t[tdENBDV]+t[loosdelay4]-
                            t[tgb]-ctcf+7ns);

        WaveSetEdgeStrobe   (ABUSVALstrobeWF,
                            0ns,
                            t[tref]+t[tENB]+t[tdENBAV]+t[loosdelay7]-
                            t[tgb]-ctcf,
                            t[tref]+t[tENB]+t[tdENBAV]+t[loosdelay7]-
                            t[tgb]-ctcf+6ns);

        WaveSetEdgeStrobe   (CTRLVALstrobeWF,
                            0ns,
                            t[tref]+t[tENB]+t[tdENBCV]+t[loosdelay]-
                            t[tgb]-ctcf,
                            t[tref]+t[tENB]+t[tdENBCV]+t[loosdelay]-
                            t[tgb]-ctcf+6ns);


        WaveSetSBC          (IIOFdriveWF,
                            t[tref]+t[tH1flo]-t[tsuIF]-t[loossetup]+dtcf-7ns,
                            t[tref]+t[tH1flo]-t[tsuIF]-t[loossetup]+dtcf,
                            t[tref]+t[tH1flo]+t[thIF]+t[looshold]-dtcf);
        EdgeSetOrigin       (IIOFdriveWF, Edge1, orgtH1flo);
        EdgeSetOrigin       (IIOFdriveWF, Edge2, orgtH1flo);
        EdgeSetOrigin       (IIOFdriveWF, Edge3, orgtH1flo);

        WaveSetEdgeStrobe   (IIOFstrobeWF,
                            t[tref]+t[tH1flo]+t[tvH1LIF]+t[loosdelay]-
                            t[tgb]-ctcf-7ns,
                            t[tref]+t[tH1flo]+t[tvH1LIF]+t[loosdelay]-
                            t[tgb]-ctcf,
                            t[tref]+t[tH1flo]+t[tvH1LIF]+t[loosdelay]-
                            t[tgb]-ctcf+7ns);
        EdgeSetOrigin       (IIOFstrobeWF, Edge1, orgtH1flo);
        EdgeSetOrigin       (IIOFstrobeWF, Edge2, orgtH1flo);
        EdgeSetOrigin       (IIOFstrobeWF, Edge3, orgtH1flo);

        EdgeSet             (IIOFstrobeoffWF,Edge1,NullEdge,
                            t[tref]+t[tH1flo]+t[thH1LIFOI]-t[loosdelay]+
                            t[tgb]+ctcf);
        EdgeSetOrigin       (IIOFstrobeoffWF, Edge1, orgtH1flo);

        WaveSetEdgeStrobe   (IIOFWWstrobeWF,
                            t[tref]+t[tH1flo]+t[tvH1LIF]+t[loosdelay]-
                            t[tgb]-ctcf-7ns,
                            t[tref]+t[tH1flo]+t[tvH1LIF]+t[loosdelay]-
                            t[tgb]-ctcf,
                            t[tref]+t[tH1flo]+t[tvH1LIF]+t[loosdelay]-
                            t[tgb]-ctcf+7ns);
        EdgeSetOrigin       (IIOFWWstrobeWF, Edge1, orgtH1flo);
        EdgeSetOrigin       (IIOFWWstrobeWF, Edge2, orgtH1flo);
        EdgeSetOrigin       (IIOFWWstrobeWF, Edge3, orgtH1flo);

        WaveSetNR           (INTdriveWF,
                            t[tref]+t[tH1flo]-t[tsuINT]-t[loossetup]+dtcf);
        EdgeSetOrigin       (INTdriveWF, Edge1, orgtH1flo);

        WaveSetNR           (INTIDLEdriveWF,
                            t[tref]+t[tH1flo]-t[tsuINTIDLE]-t[loossetup]+dtcf);
        EdgeSetOrigin       (INTdriveWF, Edge1, orgtH1flo);

        WaveSetEdgeStrobe   (IACKstrobeWF,
                            0ns,
                            t[tref]+t[tH1flo]+t[tdH1LIACK]+t[loosdelay6]-
                            t[tgb]-ctcf,
                            t[tref]+t[tH1flo]+t[tdH1LIACK]+t[loosdelay6]-
                            t[tgb]-ctcf+7ns);
        EdgeSetOrigin       (IACKstrobeWF, Edge2, orgtH1flo);
        EdgeSetOrigin       (IACKstrobeWF, Edge3, orgtH1flo);


        EdgeSetDelayData    (CREQdriveWF,Edge1,ChanFirst,
                            DriveData,ThreshVITL,
                            t[tref]+t[tH1flo]-t[tsuCREQ],0,
                            DriveData,ThreshVITH,
                            t[tref]+t[tH1flo]+t[tsuCREQ],0);

        EdgeSetDelayData    (CREQstrobeWF,Edge1,ChanFirst,
                            DriveOff,ThreshVITL,t[tref]+
                            t[tdH1HRQLt]+t[loosdelay]-t[tgb]-ctcf-7ns,0,
                            DriveOff,ThreshVITH,t[tref]+
                            t[tH1flo]-t[tsuCACK]+t[tdALRQHt]+
                            t[loosdelay]-t[tgb]-ctcf-7ns,0);
        EdgeSetDelayData    (CREQstrobeWF,Edge2,ChanFirst,
                            EdgeStrobeData,ThreshVITL,t[tref]+
                            t[tdH1HRQLt]+t[loosdelay]-t[tgb]-ctcf,0,
                            EdgeStrobeData,ThreshVITH,t[tref]+
                            t[tH1flo]-t[tsuCACK]+t[tdALRQHt]+
                            t[loosdelay]-t[tgb]-ctcf,0);
        EdgeSetDelayData    (CREQstrobeWF,Edge3,ChanFirst,
                            StrobeLatch,ThreshVITL,t[tref]+
                            t[tdH1HRQLt]+t[loosdelay]-t[tgb]-ctcf+7ns,0,
                            StrobeLatch,ThreshVITH,t[tref]+
                            t[tH1flo]-t[tsuCACK]+t[tdALRQHt]+
                            t[loosdelay]-t[tgb]-ctcf+7ns,0);

        EdgeSetDelayData    (CREQ2strobeWF,Edge1,ChanFirst,
                            DriveOff,ThreshVITL,t[tref]+
                            t[tH1flo]+t[tsuCREQ]+t[tdRQHRQLt]+
                            t[loosdelay]-t[tgb]-ctcf-7ns,0,
                            DriveOff,ThreshVITH,t[tref]+
                            t[tH1flo]+t[tsuCREQ]+t[tdRQHRQOt]+
                            t[loosdelay]-t[tgb]-ctcf-7ns,0);
        EdgeSetDelayData    (CREQ2strobeWF,Edge2,ChanFirst,
                            EdgeStrobeData,ThreshVITL,t[tref]+
                            t[tH1flo]+t[tsuCREQ]+t[tdRQHRQLt]+
                            t[loosdelay]-t[tgb]-ctcf,0,
                            EdgeStrobeData,ThreshVITH,t[tref]+
                            t[tH1flo]+t[tsuCREQ]+t[tdRQHRQOt]+
                            t[loosdelay]-t[tgb]-ctcf,0);
        EdgeSetDelayData    (CREQ2strobeWF,Edge3,ChanFirst,
                            StrobeLatch,ThreshVITL,t[tref]+
                            t[tH1flo]+t[tsuCREQ]+t[tdRQHRQLt]+
                            t[loosdelay]-t[tgb]-ctcf+7ns,0,
                            StrobeLatch,ThreshVITH,t[tref]+
                            t[tH1flo]+t[tsuCREQ]+t[tdRQHRQOt]+
                            t[loosdelay]-t[tgb]-ctcf+7ns,0);

        WaveSetNR           (CACKdriveWF,
                            t[tref]+t[tH1flo]-t[tsuCACK]);
        EdgeSetOrigin       (CACKdriveWF, Edge1, orgtH1flo);

        WaveSetEdgeStrobe   (CACKstrobeWF,
                            t[tref]+t[tH1flo]-t[tsuCREQ]+t[tdRQLALt]+
                            t[loosdelay7]-t[tgb]-ctcf-7ns,
                            t[tref]+t[tH1flo]-t[tsuCREQ]+t[tdRQLALt]+
                            t[loosdelay7]-t[tgb]-ctcf,
                            t[tref]+t[tH1flo]-t[tsuCREQ]+t[tdRQLALt]+
                            t[loosdelay7]-t[tgb]-ctcf+7ns);
        EdgeSetOrigin       (CACKstrobeWF, Edge1, orgtH1flo);
        EdgeSetOrigin       (CACKstrobeWF, Edge2, orgtH1flo);
        EdgeSetOrigin       (CACKstrobeWF, Edge3, orgtH1flo);

(* CRDY  Edge1 is defined as DriveData here, but in actuality should always   *)
(* end up being a drive-low edge based on pattern data and translation.       *)

        WaveSetRTO          (CRDYdriveWF,
                            t[tCRDYLO],
                            t[tCRDYHI]);

(* special cstrb_ strobe w/o origin used for sync-up only to avoid problems   *)
(* with bsearch.                                                              *)

        WaveSetEdgeStrobe   (CSTRB_SYNCstrobeWF,
                            t[tCRDYHI]-t[tcH]+t[tdRHSLw]-7ns,
                            t[tCRDYHI]-t[tcH]+t[tdRHSLw],
                            t[tCRDYHI]-t[tcH]+t[tdRHSLw]+7ns);

        EdgeSetDelayData    (CSTRBstrobeWF,Edge1,ChanFirst,
                            DriveOff,ThreshVITL,t[tCRDYHI]-t[tcH]+
                            t[tdRHSLw]+t[loosdelay6]-t[tgb]-ctcf-7ns,0,
                            DriveOff,ThreshVITH,t[tCRDYLO]+
                            t[tdRLSHw]+t[loosdelay]-t[tgb]-ctcf-7ns,0);
        EdgeSetDelayData    (CSTRBstrobeWF,Edge2,ChanFirst,
                            EdgeStrobeData,ThreshVITL,t[tCRDYHI]-t[tcH]+
                            t[tdRHSLw]+t[loosdelay6]-t[tgb]-ctcf,0,
                            EdgeStrobeData,ThreshVITH,t[tCRDYLO]+
                            t[tdRLSHw]+t[loosdelay]-t[tgb]-ctcf,0);
        EdgeSetDelayData    (CSTRBstrobeWF,Edge3,ChanFirst,
                            StrobeLatch,ThreshVITL,t[tCRDYHI]-t[tcH]+
                            t[tdRHSLw]+t[loosdelay6]-t[tgb]-ctcf+7ns,0,
                            StrobeLatch,ThreshVITH,t[tCRDYLO]+
                            t[tdRLSHw]+t[loosdelay]-t[tgb]-ctcf+7ns,0);

        WaveSetEdgeStrobe   (CDstrobeWF,
                            t[tref]+t[tCSTRBfhi]-t[tsuCDw]+
                            t[loosdelay]-t[tgb]-ctcf-7ns,
                            t[tref]+t[tCSTRBfhi]-t[tsuCDw]+
                            t[loosdelay]-t[tgb]-ctcf,
                            t[tref]+t[tCSTRBfhi]-t[tsuCDw]+
                            t[loosdelay]-t[tgb]-ctcf+7ns);
        EdgeSetOrigin       (CDstrobeWF, Edge1, orgtCSTRBfhi);
        EdgeSetOrigin       (CDstrobeWF, Edge2, orgtCSTRBfhi);
        EdgeSetOrigin       (CDstrobeWF, Edge3, orgtCSTRBfhi);

(* CSTRB Edge1 is defined as DriveData here, but in actuality should always   *)
(* end up being a drive-low edge based on pattern data and translation.       *)

        WaveSetRTO          (CSTRBdriveWF,
                            t[tCSTRBLO],
                            t[tCSTRBHI]);
        EdgeSetOrigin       (CSTRBdriveWF, Edge1, orgtCSTRBfhi);
        EdgeSetOrigin       (CSTRBdriveWF, Edge2, orgtCSTRBfhi);

        WaveSetEdgeStrobe   (CRDY_SYNCstrobeWF,          (*special crdy_  strobe*)
                            t[tCSTRBLO]+t[tdSLRLr]-7ns,  (*w/o origin used for  *)
                            t[tCSTRBLO]+t[tdSLRLr],      (*sync-up only to avoid*)
                            t[tCSTRBLO]+t[tdSLRLr]+7ns); (*problems with bsearch*)

        EdgeSetDelayData    (CRDYstrobeWF,Edge1,ChanFirst,
                            DriveOff,ThreshVITL,t[tCSTRBLO]+
                            t[tdSLRLr]+t[loosdelay4]-t[tgb]-ctcf-7ns,0,
                            DriveOff,ThreshVITH,t[tCSTRBHI]+
                            t[tdSHRHr]+t[loosdelay]-t[tgb]-ctcf-7ns,0);
        EdgeSetDelayData    (CRDYstrobeWF,Edge2,ChanFirst,
                            EdgeStrobeData,ThreshVITL,t[tCSTRBLO]+
                            t[tdSLRLr]+t[loosdelay4]-t[tgb]-ctcf,0,
                            EdgeStrobeData,ThreshVITH,t[tCSTRBHI]+
                            t[tdSHRHr]+t[loosdelay]-t[tgb]-ctcf,0);
        EdgeSetDelayData    (CRDYstrobeWF,Edge3,ChanFirst,
                            StrobeLatch,ThreshVITL,t[tCSTRBLO]+
                            t[tdSLRLr]+t[loosdelay4]-t[tgb]-ctcf+7ns,0,
                            StrobeLatch,ThreshVITH,t[tCSTRBHI]+
                            t[tdSHRHr]+t[loosdelay]-t[tgb]-ctcf+7ns,0);

        EdgeSetDelayData    (CDdriveWF,Edge1,ChanFirst,
                            DriveComplement,ThreshVITL,t[tCSTRBLO]-
                            t[tsuCDr]-t[loossetup]+dtcf-7ns,0,
                            DriveComplement,ThreshVITH,t[tCSTRBLO]-
                            t[tsuCDr]-t[looscd]-t[loossetup]+dtcf-7ns,0);
        EdgeSetDelayData    (CDdriveWF,Edge2,ChanFirst,
                            DriveData,ThreshVITL,t[tCSTRBLO]-
                            t[tsuCDr]-t[loossetup]+dtcf,0,
                            DriveData,ThreshVITH,t[tCSTRBLO]-
                            t[tsuCDr]-t[looscd]-t[loossetup]+dtcf,0);
        EdgeSetDelayData    (CDdriveWF,Edge3,ChanFirst,
                            DriveComplement,ThreshVITL,t[tref]+t[tCRDYflo]+
                            t[thCDr]+t[looscd]+t[looshold]-dtcf,0,
                            DriveComplement,ThreshVITH,t[tref]+t[tCRDYflo]+
                            t[thCDr]+t[looshold]-dtcf,0);


        WaveSetSBC          (TCLKdriveWF,
                            t[tref]+t[tH1flo]-t[tsuTCLK]-t[loossetup]+dtcf-7ns,
                            t[tref]+t[tH1flo]-t[tsuTCLK]-t[loossetup]+dtcf,
                            t[tref]+t[tH1flo]+t[thTCLK]+t[looshold]-dtcf);
        EdgeSetOrigin       (TCLKdriveWF, Edge1, orgtH1flo);
        EdgeSetOrigin       (TCLKdriveWF, Edge2, orgtH1flo);
        EdgeSetOrigin       (TCLKdriveWF, Edge3, orgtH1flo);

        WaveSetEdgeStrobe   (TCLKstrobeWF,
                            t[tref]+t[tdTCLK]+t[loosdelay4]-t[tgb]-ctcf-7ns,
                            t[tref]+t[tdTCLK]+t[loosdelay4]-t[tgb]-ctcf,
                            t[tref]+t[tdTCLK]+t[loosdelay4]-t[tgb]-ctcf+7ns);


        WaveSetRTO          (TCKCLKdriveWF,
                            t[tref],
                            t[tref]+t[tcCI]);

        WaveSetNR           (TCKdriveWF,
                            t[tref]);

        WaveSetSBC          (TDITMSdriveWF,
                            t[tref]+t[tcCI]-t[tsuTDITMS]-t[loossetup]+dtcf-7ns,
                            t[tref]+t[tcCI]-t[tsuTDITMS]-t[loossetup]+dtcf,
                            t[tref]+t[tcCI]+t[thTDITMS]+t[looshold]-dtcf);

        WaveSetNR           (JTAGdriveWF,
                            t[tref]+t[tJTAG]);

        WaveSetEdgeStrobe   (TDOstrobeWF,
                            0ns,
                            t[tref]+t[tdTDO]+t[loosdelay]-t[tgb]-ctcf,
                            t[tref]+t[tdTDO]+t[loosdelay]-t[tgb]-ctcf+7ns);

        WaveSetEdgeStrobe   (JTAGH1strobeWF,
                            0ns,
                            t[tref]+t[tdTDO]+t[loosdelay]-t[tgb]-ctcf,
                            t[tref]+t[tdTDO]+t[loosdelay]-t[tgb]-ctcf+7ns);

        WaveSetEdgeStrobe   (JTAGVARYstrobeWF,
                            0ns,
                            t[tref]+t[tdTDO]+t[tcCI]+t[loosdelay]-t[tgb]-ctcf,
                            t[tref]+t[tdTDO]+t[tcCI]+t[loosdelay]-t[tgb]-ctcf+7ns);

        WaveSetEdgeStrobe   (JTAGABUSstrobeWF,
                            0ns,
                            t[tref]+t[tdTDO]+t[tcCI]+t[loosdelay]-t[tgb]-ctcf,
                            t[tref]+t[tdTDO]+t[tcCI]+t[loosdelay]-t[tgb]-ctcf+7ns);


        WaveSetNR           (EMUdriveWF,
                            t[tref]+t[tEMU]);

        WaveSetEdgeStrobe   (EMUstrobeWF,
                            0ns,
                            t[tref]+t[tdEMU]+t[loosdelay]-t[tgb]-ctcf,
                            t[tref]+t[tdEMU]+t[loosdelay]-t[tgb]-ctcf+7ns);


        WaveSetNR           (RESETLOCdriveWF,
                            t[tref]+t[tRESETLOC]);

        WaveSetNR           (ROMENdriveWF,
                            t[tref]+t[tROMEN]);

        WaveSetNR           (NMIdriveWF,
                            t[tref]+t[tNMI]);


        WaveSetContinue     (ContinueWF);

        WaveSetOff          (ALLoffWF,t[tref],t[tref]);
STOP(ALLENUMS,TIspecsetupmin25ACTable,TIspecsetupmax25ACTable,TIsearch25ACTable,TIchar25ACTable);


          end; (*6th case*)



        TIspecsetupmin33ACTable,
        TIspecsetupmax33ACTable,
        TIsearchlevels33ACTable,
        TIsearch33ACTable:
          begin

START(ALLENUMS,TIspecsetupmin33ACTable,TIspecsetupmax33ACTable,TIsearchlevels33ACTable,TIsearch33ACTable);

        WaveSetDoubleClk    (CLKINdriveWF,
                            t[tref]+t[toffset],
                            t[tref]+t[toffset]+t[twCIH],
                            t[tref]+t[toffset]+t[twCIH]+t[twCIL],
                            t[tref]+t[toffset]+t[twCIH]+t[twCIL]+t[twCIH]);
        EdgeSetOrigin       (CLKINdriveWF, Edge1, orgtoffset);
        EdgeSetOrigin       (CLKINdriveWF, Edge2, orgtoffset);
        EdgeSetOrigin       (CLKINdriveWF, Edge3, orgtoffset);
        EdgeSetOrigin       (CLKINdriveWF, Edge4, orgtoffset);

        EdgeSetDelayData    (RESETdriveWF,Edge1,ChanFirst,
                            DriveData,ThreshVITL,
                            t[tref]+t[toffset]+t[twCIH]+t[twCIL]+t[twCIH]-t[tsuRESET]-t[loossetup]+dtcf,0,
                            DriveData,ThreshVITH,
                            t[tref]+t[tH1flo]-t[tsuRESETH]-t[loossetup]+dtcf,0);

        WaveSetEdgeStrobe   (H1strobeWF,
                            0ns,
                            t[tref]+t[loosclock],
                            t[tref]+t[loosclock]+7ns);

        WaveSetEdgeStrobe   (H1HIGHstrobeWF,
                            0ns,
                            t[tref]+t[tH1flo]-t[tfHmax],
                            t[tref]+t[tH1flo]-t[tfHmax]+7ns);
        EdgeSetOrigin       (H1HIGHstrobeWF, Edge2, orgtH1high);
        EdgeSetOrigin       (H1HIGHstrobeWF, Edge3, orgtH1high);

        EdgeSet             (H1LOWstrobeWF,Edge1,DriveOff,
                            0ns);
        EdgeSet             (H1LOWstrobeWF,Edge2,EdgeStrobeLow,
                            t[tref]+t[tcH]-t[trHmax]);
        EdgeSet             (H1LOWstrobeWF,Edge3,StrobeLatch,
                            t[tref]+t[tcH]-t[trHmax]+7ns);
        EdgeSetOrigin       (H1LOWstrobeWF, Edge2, orgtH1low);
        EdgeSetOrigin       (H1LOWstrobeWF, Edge3, orgtH1low);

        WaveSetEdgeStrobe   (H1IDLEstrobeWF,
                            0ns,
                            t[tref]+t[tH1flo]+t[loosclock],
                            t[tref]+t[tH1flo]+t[loosclock]+7ns);

        WaveSetEdgeStrobe   (H3strobeWF,
                            0ns,
                            t[tref]+t[loosclock],
                            t[tref]+t[loosclock]+7ns);

        WaveSetEdgeStrobe   (H3LOWstrobeWF,
                            0ns,
                            t[tref]+t[tH3rhi]-t[trHmax],
                            t[tref]+t[tH3rhi]-t[trHmax]+7ns);
        EdgeSetOrigin       (H3LOWstrobeWF, Edge2, orgtH3low);
        EdgeSetOrigin       (H3LOWstrobeWF, Edge3, orgtH3low);

        EdgeSet             (H3HIGHstrobeWF,Edge1,DriveOff,
                            0ns);
        EdgeSet             (H3HIGHstrobeWF,Edge2,EdgeStrobeHigh,
                            t[tref]+t[tcH]+t[tH3flo]-t[tfHmax]);
        EdgeSet             (H3HIGHstrobeWF,Edge3,StrobeLatch,
                            t[tref]+t[tcH]+t[tH3flo]-t[tfHmax]+7ns);
        EdgeSetOrigin       (H3HIGHstrobeWF, Edge2, orgtH3high);
        EdgeSetOrigin       (H3HIGHstrobeWF, Edge3, orgtH3high);

        WaveSetEdgeStrobe   (H3IDLEstrobeWF,
                            0ns,
                            t[tref]+t[tH1flo]+t[loosclock],
                            t[tref]+t[tH1flo]+t[loosclock]+7ns);

        WaveSetEdgeStrobe   (STRBstrobeWF,
                            0ns,
                            t[tref]+t[tH1flo]+t[tdH1LS]+t[loosdelay7]-
                            t[tgb]-ctcf,
                            t[tref]+t[tH1flo]+t[tdH1LS]+t[loosdelay7]-
                            t[tgb]-ctcf+7ns);
        EdgeSetOrigin       (STRBstrobeWF, Edge2, orgtH1flo);
        EdgeSetOrigin       (STRBstrobeWF, Edge3, orgtH1flo);

        WaveSetEdgeStrobe   (RWstrobeWF,
                            0ns,
                            t[tref]+t[tdH1HRW]+t[loosdelay5]-t[tgb]-ctcf,
                            t[tref]+t[tdH1HRW]+t[loosdelay5]-t[tgb]-ctcf+7ns);

        WaveSetEdgeStrobe   (ABUSVstrobeWF,
                            0ns,
                            t[tref]+t[tH1flo]+t[tdH1LA]-t[restrict]-
                            t[loosdelay]+t[tgb]+ctcf+t[tcH]-7ns,
                            t[tref]+t[tH1flo]+t[tdH1LA]-t[restrict]-
                            t[loosdelay]+t[tgb]+ctcf+t[tcH]);
        EdgeSetOrigin       (ABUSVstrobeWF, Edge2, orgtH1flo);
        EdgeSetOrigin       (ABUSVstrobeWF, Edge3, orgtH1flo);

        WaveSetEdgeStrobe   (ABUSstrobeWF,
                            0ns,
                            t[tref]+t[tH1flo]+t[tdH1LA]+t[loosdelay7]-
                            t[tgb]-ctcf,
                            t[tref]+t[tH1flo]+t[tdH1LA]+t[loosdelay7]-
                            t[tgb]-ctcf+7ns);
        EdgeSetOrigin       (ABUSstrobeWF, Edge2, orgtH1flo);
        EdgeSetOrigin       (ABUSstrobeWF, Edge3, orgtH1flo);

        WaveSetEdgeStrobe   (ABUSWWstrobeWF,
                            0ns,
                            t[tref]+t[tdH1HA]+t[loosabus]-t[tgb]-ctcf,
                            t[tref]+t[tdH1HA]+t[loosabus]-t[tgb]-ctcf+7ns);

        WaveSetEdgeStrobe   (STATstrobeWF,
                            0ns,
                            t[tref]+t[tH1flo]+t[tdH1LSTAT]+t[loosdelay7]-
                            t[tgb]-ctcf,
                            t[tref]+t[tH1flo]+t[tdH1LSTAT]+t[loosdelay7]-
                            t[tgb]-ctcf+7ns);
        EdgeSetOrigin       (STATstrobeWF, Edge2, orgtH1flo);
        EdgeSetOrigin       (STATstrobeWF, Edge3, orgtH1flo);

        WaveSetEdgeStrobe   (LOCKstrobeWF,
                            0ns,
                            t[tref]+t[tH1flo]+t[tdH1LLOCK]+t[loosdelay4]-
                            t[tgb]-ctcf,
                            t[tref]+t[tH1flo]+t[tdH1LLOCK]+t[loosdelay4]-
                            t[tgb]-ctcf+7ns);
        EdgeSetOrigin       (LOCKstrobeWF, Edge2, orgtH1flo);
        EdgeSetOrigin       (LOCKstrobeWF, Edge3, orgtH1flo);

        WaveSetSBC          (DBUSdriveWF,
                            t[tref]+t[tH1flo]-t[tsuDR]-t[loossetup]+dtcf-7ns,
                            t[tref]+t[tH1flo]-t[tsuDR]-t[loossetup]+dtcf,
                            t[tref]+t[tH1flo]+t[thDR]+t[looshold]-dtcf);
        EdgeSetOrigin       (DBUSdriveWF, Edge1, orgtH1flo);
        EdgeSetOrigin       (DBUSdriveWF, Edge2, orgtH1flo);
        EdgeSetOrigin       (DBUSdriveWF, Edge3, orgtH1flo);

        WaveSetEdgeStrobe   (DBUSstrobeWF,
                            t[tref]+t[tH1flo]+t[tvDW]+t[loosdelay4]-
                            t[tgb]-ctcf-7ns,
                            t[tref]+t[tH1flo]+t[tvDW]+t[loosdelay4]-
                            t[tgb]-ctcf,
                            t[tref]+t[tH1flo]+t[tvDW]+t[loosdelay4]-
                            t[tgb]-ctcf+7ns);
        EdgeSetOrigin       (DBUSstrobeWF, Edge1, orgtH1flo);
        EdgeSetOrigin       (DBUSstrobeWF, Edge2, orgtH1flo);
        EdgeSetOrigin       (DBUSstrobeWF, Edge3, orgtH1flo);

        EdgeSet             (DBUSstrobeoffWF,Edge1,NullEdge,
                            t[tref]+t[thDW]-t[loosdelay]+t[tgb]+ctcf);

        WaveSetEdgeStrobe   (DBUSWWstrobeWF,
                            t[tref]+t[tH1flo]+t[tvDW]+t[loosdelay4]-
                            t[tgb]-ctcf-7ns,
                            t[tref]+t[tH1flo]+t[tvDW]+t[loosdelay4]-
                            t[tgb]-ctcf,
                            t[tref]+t[tH1flo]+t[tvDW]+t[loosdelay4]-
                            t[tgb]-ctcf+7ns);
        EdgeSetOrigin       (DBUSWWstrobeWF, Edge1, orgtH1flo);
        EdgeSetOrigin       (DBUSWWstrobeWF, Edge2, orgtH1flo);
        EdgeSetOrigin       (DBUSWWstrobeWF, Edge3, orgtH1flo);

        WaveSetEdgeStrobe   (DBUSWW2strobeWF,
                            t[tref]+t[tH1flo]+t[tvDW]+t[loosdelay4]-
                            t[tgb]-ctcf-7ns,
                            t[tref]+t[tH1flo]+t[tvDW]+t[loosdelay4]-
                            t[tgb]-ctcf,
                            t[tref]+t[tH1flo]+t[tvDW]+t[loosdelay4]-
                            t[tgb]-ctcf+7ns);
        EdgeSetOrigin       (DBUSWW2strobeWF, Edge1, orgtH1flo);
        EdgeSetOrigin       (DBUSWW2strobeWF, Edge2, orgtH1flo);
        EdgeSetOrigin       (DBUSWW2strobeWF, Edge3, orgtH1flo);

        WaveSetRTO          (RDYdriveWF,
                            t[tref]+t[tH1flo]-t[tsuRDY]-t[loossetup]+dtcf,
                            t[tref]+t[tH1flo]+t[thRDY]+t[looshold]-dtcf);
        EdgeSetOrigin       (RDYdriveWF, Edge1, orgtH1flo);
        EdgeSetOrigin       (RDYdriveWF, Edge2, orgtH1flo);

        WaveSetNR           (ENBdriveWF,
                            t[tref]+t[tENB]);

        WaveSetEdgeStrobeZ  (DBUSHIZstrobeWF,
                            0ns,
                            t[tref]+t[tENB]+t[tdENBZ]+t[loosdelay]-ctcf,
                            t[tref]+t[tENB]+t[tdENBZ]+t[loosdelay]-ctcf+7ns);

        WaveSetEdgeStrobeZ  (ABUSHIZstrobeWF,
                            0ns,
                            t[tref]+t[tENB]+t[tdENBZ]+t[loosdelay]-ctcf,
                            t[tref]+t[tENB]+t[tdENBZ]+t[loosdelay]-ctcf+7ns);

        WaveSetEdgeStrobeZ  (CTRLHIZstrobeWF,
                            0ns,
                            t[tref]+t[tENB]+t[tdENBZ]+t[loosdelay]-ctcf,
                            t[tref]+t[tENB]+t[tdENBZ]+t[loosdelay]-ctcf+7ns);

        WaveSetEdgeStrobe   (DBUSVALstrobeWF,
                            0ns,
                            t[tref]+t[tENB]+t[tdENBDV]+t[loosdelay4]-
                            t[tgb]-ctcf,
                            t[tref]+t[tENB]+t[tdENBDV]+t[loosdelay4]-
                            t[tgb]-ctcf+7ns);

        WaveSetEdgeStrobe   (ABUSVALstrobeWF,
                            0ns,
                            t[tref]+t[tENB]+t[tdENBAV]+t[loosdelay7]-
                            t[tgb]-ctcf,
                            t[tref]+t[tENB]+t[tdENBAV]+t[loosdelay7]-
                            t[tgb]-ctcf+6ns);

        WaveSetEdgeStrobe   (CTRLVALstrobeWF,
                            0ns,
                            t[tref]+t[tENB]+t[tdENBCV]+t[loosdelay]-
                            t[tgb]-ctcf,
                            t[tref]+t[tENB]+t[tdENBCV]+t[loosdelay]-
                            t[tgb]-ctcf+6ns);


        WaveSetSBC          (IIOFdriveWF,
                            t[tref]+t[tH1flo]-t[tsuIF]-t[loossetup]+dtcf-7ns,
                            t[tref]+t[tH1flo]-t[tsuIF]-t[loossetup]+dtcf,
                            t[tref]+t[tH1flo]+t[thIF]+t[looshold]-dtcf);
        EdgeSetOrigin       (IIOFdriveWF, Edge1, orgtH1flo);
        EdgeSetOrigin       (IIOFdriveWF, Edge2, orgtH1flo);
        EdgeSetOrigin       (IIOFdriveWF, Edge3, orgtH1flo);

        WaveSetEdgeStrobe   (IIOFstrobeWF,
                            t[tref]+t[tH1flo]+t[tvH1LIF]+t[loosdelay]-
                            t[tgb]-ctcf-7ns,
                            t[tref]+t[tH1flo]+t[tvH1LIF]+t[loosdelay]-
                            t[tgb]-ctcf,
                            t[tref]+t[tH1flo]+t[tvH1LIF]+t[loosdelay]-
                            t[tgb]-ctcf+7ns);
        EdgeSetOrigin       (IIOFstrobeWF, Edge1, orgtH1flo);
        EdgeSetOrigin       (IIOFstrobeWF, Edge2, orgtH1flo);
        EdgeSetOrigin       (IIOFstrobeWF, Edge3, orgtH1flo);

        EdgeSet             (IIOFstrobeoffWF,Edge1,NullEdge,
                            t[tref]+t[tH1flo]+t[thH1LIFOI]-t[loosdelay]+
                            t[tgb]+ctcf);
        EdgeSetOrigin       (IIOFstrobeoffWF, Edge1, orgtH1flo);

        WaveSetEdgeStrobe   (IIOFWWstrobeWF,
                            t[tref]+t[tH1flo]+t[tvH1LIF]+t[loosdelay]-
                            t[tgb]-ctcf-7ns,
                            t[tref]+t[tH1flo]+t[tvH1LIF]+t[loosdelay]-
                            t[tgb]-ctcf,
                            t[tref]+t[tH1flo]+t[tvH1LIF]+t[loosdelay]-
                            t[tgb]-ctcf+7ns);
        EdgeSetOrigin       (IIOFWWstrobeWF, Edge1, orgtH1flo);
        EdgeSetOrigin       (IIOFWWstrobeWF, Edge2, orgtH1flo);
        EdgeSetOrigin       (IIOFWWstrobeWF, Edge3, orgtH1flo);

        WaveSetNR           (INTdriveWF,
                            t[tref]+t[tH1flo]-t[tsuINT]-t[loossetup]+dtcf);
        EdgeSetOrigin       (INTdriveWF, Edge1, orgtH1flo);

        WaveSetNR           (INTIDLEdriveWF,
                            t[tref]+t[tH1flo]-t[tsuINTIDLE]-t[loossetup]+dtcf);
        EdgeSetOrigin       (INTdriveWF, Edge1, orgtH1flo);

        WaveSetEdgeStrobe   (IACKstrobeWF,
                            0ns,
                            t[tref]+t[tH1flo]+t[tdH1LIACK]+t[loosdelay6]-
                            t[tgb]-ctcf,
                            t[tref]+t[tH1flo]+t[tdH1LIACK]+t[loosdelay6]-
                            t[tgb]-ctcf+7ns);
        EdgeSetOrigin       (IACKstrobeWF, Edge2, orgtH1flo);
        EdgeSetOrigin       (IACKstrobeWF, Edge3, orgtH1flo);


        EdgeSetDelayData    (CREQdriveWF,Edge1,ChanFirst,
                            DriveData,ThreshVITL,
                            t[tref]+t[tH1flo]-t[tsuCREQ],0,
                            DriveData,ThreshVITH,
                            t[tref]+t[tH1flo]+t[tsuCREQ],0);

        EdgeSetDelayData    (CREQstrobeWF,Edge1,ChanFirst,
                            DriveOff,ThreshVITL,t[tref]+
                            t[tdH1HRQLt]+t[loosdelay]-t[tgb]-ctcf-7ns,0,
                            DriveOff,ThreshVITH,t[tref]+
                            t[tH1flo]-t[tsuCACK]+t[tdALRQHt]+
                            t[loosdelay]-t[tgb]-ctcf-7ns,0);
        EdgeSetDelayData    (CREQstrobeWF,Edge2,ChanFirst,
                            EdgeStrobeData,ThreshVITL,t[tref]+
                            t[tdH1HRQLt]+t[loosdelay]-t[tgb]-ctcf,0,
                            EdgeStrobeData,ThreshVITH,t[tref]+
                            t[tH1flo]-t[tsuCACK]+t[tdALRQHt]+
                            t[loosdelay]-t[tgb]-ctcf,0);
        EdgeSetDelayData    (CREQstrobeWF,Edge3,ChanFirst,
                            StrobeLatch,ThreshVITL,t[tref]+
                            t[tdH1HRQLt]+t[loosdelay]-t[tgb]-ctcf+7ns,0,
                            StrobeLatch,ThreshVITH,t[tref]+
                            t[tH1flo]-t[tsuCACK]+t[tdALRQHt]+
                            t[loosdelay]-t[tgb]-ctcf+7ns,0);

        EdgeSetDelayData    (CREQ2strobeWF,Edge1,ChanFirst,
                            DriveOff,ThreshVITL,t[tref]+
                            t[tH1flo]+t[tsuCREQ]+t[tdRQHRQLt]+
                            t[loosdelay]-t[tgb]-ctcf-7ns,0,
                            DriveOff,ThreshVITH,t[tref]+
                            t[tH1flo]+t[tsuCREQ]+t[tdRQHRQOt]+
                            t[loosdelay]-t[tgb]-ctcf-7ns,0);
        EdgeSetDelayData    (CREQ2strobeWF,Edge2,ChanFirst,
                            EdgeStrobeData,ThreshVITL,t[tref]+
                            t[tH1flo]+t[tsuCREQ]+t[tdRQHRQLt]+
                            t[loosdelay]-t[tgb]-ctcf,0,
                            EdgeStrobeData,ThreshVITH,t[tref]+
                            t[tH1flo]+t[tsuCREQ]+t[tdRQHRQOt]+
                            t[loosdelay]-t[tgb]-ctcf,0);
        EdgeSetDelayData    (CREQ2strobeWF,Edge3,ChanFirst,
                            StrobeLatch,ThreshVITL,t[tref]+
                            t[tH1flo]+t[tsuCREQ]+t[tdRQHRQLt]+
                            t[loosdelay]-t[tgb]-ctcf+7ns,0,
                            StrobeLatch,ThreshVITH,t[tref]+
                            t[tH1flo]+t[tsuCREQ]+t[tdRQHRQOt]+
                            t[loosdelay]-t[tgb]-ctcf+7ns,0);

        WaveSetNR           (CACKdriveWF,
                            t[tref]+t[tH1flo]-t[tsuCACK]);
        EdgeSetOrigin       (CACKdriveWF, Edge1, orgtH1flo);

        WaveSetEdgeStrobe   (CACKstrobeWF,
                            t[tref]+t[tH1flo]-t[tsuCREQ]+t[tdRQLALt]+
                            t[loosdelay7]-t[tgb]-ctcf-7ns,
                            t[tref]+t[tH1flo]-t[tsuCREQ]+t[tdRQLALt]+
                            t[loosdelay7]-t[tgb]-ctcf,
                            t[tref]+t[tH1flo]-t[tsuCREQ]+t[tdRQLALt]+
                            t[loosdelay7]-t[tgb]-ctcf+7ns);
        EdgeSetOrigin       (CACKstrobeWF, Edge1, orgtH1flo);
        EdgeSetOrigin       (CACKstrobeWF, Edge2, orgtH1flo);
        EdgeSetOrigin       (CACKstrobeWF, Edge3, orgtH1flo);

(* CRDY  Edge1 is defined as DriveData here, but in actuality should always   *)
(* end up being a drive-low edge based on pattern data and translation.       *)

        WaveSetRTO          (CRDYdriveWF,
                            t[tCRDYLO],
                            t[tCRDYHI]);

(* special cstrb_ strobe w/o origin used for sync-up only to avoid problems   *)
(* with bsearch.                                                              *)

        WaveSetEdgeStrobe   (CSTRB_SYNCstrobeWF,
                            t[tCRDYHI]-t[tcH]+t[tdRHSLw]-7ns,
                            t[tCRDYHI]-t[tcH]+t[tdRHSLw],
                            t[tCRDYHI]-t[tcH]+t[tdRHSLw]+7ns);

        EdgeSetDelayData    (CSTRBstrobeWF,Edge1,ChanFirst,
                            DriveOff,ThreshVITL,t[tCRDYHI]-t[tcH]+
                            t[tdRHSLw]+t[loosdelay6]-t[tgb]-ctcf-7ns,0,
                            DriveOff,ThreshVITH,t[tCRDYLO]+
                            t[tdRLSHw]+t[loosdelay]-t[tgb]-ctcf-7ns,0);
        EdgeSetDelayData    (CSTRBstrobeWF,Edge2,ChanFirst,
                            EdgeStrobeData,ThreshVITL,t[tCRDYHI]-t[tcH]+
                            t[tdRHSLw]+t[loosdelay6]-t[tgb]-ctcf,0,
                            EdgeStrobeData,ThreshVITH,t[tCRDYLO]+
                            t[tdRLSHw]+t[loosdelay]-t[tgb]-ctcf,0);
        EdgeSetDelayData    (CSTRBstrobeWF,Edge3,ChanFirst,
                            StrobeLatch,ThreshVITL,t[tCRDYHI]-t[tcH]+
                            t[tdRHSLw]+t[loosdelay6]-t[tgb]-ctcf+7ns,0,
                            StrobeLatch,ThreshVITH,t[tCRDYLO]+
                            t[tdRLSHw]+t[loosdelay]-t[tgb]-ctcf+7ns,0);

        WaveSetEdgeStrobe   (CDstrobeWF,
                            t[tref]+t[tCSTRBfhi]-t[tsuCDw]+
                            t[loosdelay]-t[tgb]-ctcf-7ns,
                            t[tref]+t[tCSTRBfhi]-t[tsuCDw]+
                            t[loosdelay]-t[tgb]-ctcf,
                            t[tref]+t[tCSTRBfhi]-t[tsuCDw]+
                            t[loosdelay]-t[tgb]-ctcf+7ns);
        EdgeSetOrigin       (CDstrobeWF, Edge1, orgtCSTRBfhi);
        EdgeSetOrigin       (CDstrobeWF, Edge2, orgtCSTRBfhi);
        EdgeSetOrigin       (CDstrobeWF, Edge3, orgtCSTRBfhi);

(* CSTRB Edge1 is defined as DriveData here, but in actuality should always   *)
(* end up being a drive-low edge based on pattern data and translation.       *)

        WaveSetRTO          (CSTRBdriveWF,
                            t[tCSTRBLO],
                            t[tCSTRBHI]);
        EdgeSetOrigin       (CSTRBdriveWF, Edge1, orgtCSTRBfhi);
        EdgeSetOrigin       (CSTRBdriveWF, Edge2, orgtCSTRBfhi);

        WaveSetEdgeStrobe   (CRDY_SYNCstrobeWF,          (*special crdy_  strobe*)
                            t[tCSTRBLO]+t[tdSLRLr]-7ns,  (*w/o origin used for  *)
                            t[tCSTRBLO]+t[tdSLRLr],      (*sync-up only to avoid*)
                            t[tCSTRBLO]+t[tdSLRLr]+7ns); (*problems with bsearch*)

        EdgeSetDelayData    (CRDYstrobeWF,Edge1,ChanFirst,
                            DriveOff,ThreshVITL,t[tCSTRBLO]+
                            t[tdSLRLr]+t[loosdelay4]-t[tgb]-ctcf-7ns,0,
                            DriveOff,ThreshVITH,t[tCSTRBHI]+
                            t[tdSHRHr]+t[loosdelay]-t[tgb]-ctcf-7ns,0);
        EdgeSetDelayData    (CRDYstrobeWF,Edge2,ChanFirst,
                            EdgeStrobeData,ThreshVITL,t[tCSTRBLO]+
                            t[tdSLRLr]+t[loosdelay4]-t[tgb]-ctcf,0,
                            EdgeStrobeData,ThreshVITH,t[tCSTRBHI]+
                            t[tdSHRHr]+t[loosdelay]-t[tgb]-ctcf,0);
        EdgeSetDelayData    (CRDYstrobeWF,Edge3,ChanFirst,
                            StrobeLatch,ThreshVITL,t[tCSTRBLO]+
                            t[tdSLRLr]+t[loosdelay4]-t[tgb]-ctcf+7ns,0,
                            StrobeLatch,ThreshVITH,t[tCSTRBHI]+
                            t[tdSHRHr]+t[loosdelay]-t[tgb]-ctcf+7ns,0);

        EdgeSetDelayData    (CDdriveWF,Edge1,ChanFirst,
                            DriveComplement,ThreshVITL,t[tCSTRBLO]-
                            t[tsuCDr]-t[loossetup]+dtcf-7ns,0,
                            DriveComplement,ThreshVITH,t[tCSTRBLO]-
                            t[tsuCDr]-t[looscd]-t[loossetup]+dtcf-7ns,0);
        EdgeSetDelayData    (CDdriveWF,Edge2,ChanFirst,
                            DriveData,ThreshVITL,t[tCSTRBLO]-
                            t[tsuCDr]-t[loossetup]+dtcf,0,
                            DriveData,ThreshVITH,t[tCSTRBLO]-
                            t[tsuCDr]-t[looscd]-t[loossetup]+dtcf,0);
        EdgeSetDelayData    (CDdriveWF,Edge3,ChanFirst,
                            DriveComplement,ThreshVITL,t[tref]+t[tCRDYflo]+
                            t[thCDr]+t[looscd]+t[looshold]-dtcf,0,
                            DriveComplement,ThreshVITH,t[tref]+t[tCRDYflo]+
                            t[thCDr]+t[looshold]-dtcf,0);


        WaveSetSBC          (TCLKdriveWF,
                            t[tref]+t[tH1flo]-t[tsuTCLK]-t[loossetup]+dtcf-7ns,
                            t[tref]+t[tH1flo]-t[tsuTCLK]-t[loossetup]+dtcf,
                            t[tref]+t[tH1flo]+t[thTCLK]+t[looshold]-dtcf);
        EdgeSetOrigin       (TCLKdriveWF, Edge1, orgtH1flo);
        EdgeSetOrigin       (TCLKdriveWF, Edge2, orgtH1flo);
        EdgeSetOrigin       (TCLKdriveWF, Edge3, orgtH1flo);

        WaveSetEdgeStrobe   (TCLKstrobeWF,
                            t[tref]+t[tdTCLK]+t[loosdelay4]-t[tgb]-ctcf-7ns,
                            t[tref]+t[tdTCLK]+t[loosdelay4]-t[tgb]-ctcf,
                            t[tref]+t[tdTCLK]+t[loosdelay4]-t[tgb]-ctcf+7ns);


        WaveSetRTO          (TCKCLKdriveWF,
                            t[tref],
                            t[tref]+t[tcCI]);

        WaveSetNR           (TCKdriveWF,
                            t[tref]);

        WaveSetSBC          (TDITMSdriveWF,
                            t[tref]+t[tcCI]-t[tsuTDITMS]-t[loossetup]+dtcf-7ns,
                            t[tref]+t[tcCI]-t[tsuTDITMS]-t[loossetup]+dtcf,
                            t[tref]+t[tcCI]+t[thTDITMS]+t[looshold]-dtcf);

        WaveSetNR           (JTAGdriveWF,
                            t[tref]+t[tJTAG]);

        WaveSetEdgeStrobe   (TDOstrobeWF,
                            0ns,
                            t[tref]+t[tdTDO]+t[loosdelay]-t[tgb]-ctcf,
                            t[tref]+t[tdTDO]+t[loosdelay]-t[tgb]-ctcf+7ns);

        WaveSetEdgeStrobe   (JTAGH1strobeWF,
                            0ns,
                            t[tref]+t[tdTDO]+t[loosdelay]-t[tgb]-ctcf,
                            t[tref]+t[tdTDO]+t[loosdelay]-t[tgb]-ctcf+7ns);

        WaveSetEdgeStrobe   (JTAGVARYstrobeWF,
                            0ns,
                            t[tref]+t[tdTDO]+t[tcCI]+t[loosdelay]-t[tgb]-ctcf,
                            t[tref]+t[tdTDO]+t[tcCI]+t[loosdelay]-t[tgb]-ctcf+7ns);

        WaveSetEdgeStrobe   (JTAGABUSstrobeWF,
                            0ns,
                            t[tref]+t[tdTDO]+t[tcCI]+t[loosdelay]-t[tgb]-ctcf,
                            t[tref]+t[tdTDO]+t[tcCI]+t[loosdelay]-t[tgb]-ctcf+7ns);


        WaveSetNR           (EMUdriveWF,
                            t[tref]+t[tEMU]);

        WaveSetEdgeStrobe   (EMUstrobeWF,
                            0ns,
                            t[tref]+t[tdEMU]+t[loosdelay]-t[tgb]-ctcf,
                            t[tref]+t[tdEMU]+t[loosdelay]-t[tgb]-ctcf+7ns);


        WaveSetNR           (RESETLOCdriveWF,
                            t[tref]+t[tRESETLOC]);

        WaveSetNR           (ROMENdriveWF,
                            t[tref]+t[tROMEN]);

        WaveSetNR           (NMIdriveWF,
                            t[tref]+t[tNMI]);


        WaveSetContinue     (ContinueWF);

        WaveSetOff          (ALLoffWF,t[tref],t[tref]);
STOP(ALLENUMS,TIspecsetupmin33ACTable,TIspecsetupmax33ACTable,TIsearchlevels33ACTable,TIsearch33ACTable);


          end; (*7th case*)


        TIspecholdmin25ACTable,
        TIspecholdmax25ACTable:
          begin
START(ALLENUMS,TIspecholdmin25ACTable,TIspecholdmax25ACTable);


        WaveSetDoubleClk    (CLKINdriveWF,
                            t[tref]+t[toffset],
                            t[tref]+t[toffset]+t[twCIH],
                            t[tref]+t[toffset]+t[twCIH]+t[twCIL],
                            t[tref]+t[toffset]+t[twCIH]+t[twCIL]+t[twCIH]);
        EdgeSetOrigin       (CLKINdriveWF, Edge1, orgtoffset);
        EdgeSetOrigin       (CLKINdriveWF, Edge2, orgtoffset);
        EdgeSetOrigin       (CLKINdriveWF, Edge3, orgtoffset);
        EdgeSetOrigin       (CLKINdriveWF, Edge4, orgtoffset);

        EdgeSetDelayData    (RESETdriveWF,Edge1,ChanFirst,
                            DriveData,ThreshVITL,
                            t[tref]+t[toffset]+t[twCIH]+t[twCIL]+t[twCIH]-t[tsuRESET]-t[loossetup]+dtcf,0,
                            DriveData,ThreshVITH,
                            t[tref]+t[tH1flo]-t[tsuRESETH]-t[loossetup]+dtcf,0);

        WaveSetEdgeStrobe   (H1strobeWF,
                            0ns,
                            t[tref]+t[loosclock],
                            t[tref]+t[loosclock]+7ns);

        WaveSetEdgeStrobe   (H1HIGHstrobeWF,
                            0ns,
                            t[tref]+t[tH1flo]-t[tfHmax],
                            t[tref]+t[tH1flo]-t[tfHmax]+7ns);
        EdgeSetOrigin       (H1HIGHstrobeWF, Edge2, orgtH1high);
        EdgeSetOrigin       (H1HIGHstrobeWF, Edge3, orgtH1high);

        EdgeSet             (H1LOWstrobeWF,Edge1,DriveOff,
                            0ns);
        EdgeSet             (H1LOWstrobeWF,Edge2,EdgeStrobeLow,
                            t[tref]+t[tcH]-t[trHmax]);
        EdgeSet             (H1LOWstrobeWF,Edge3,StrobeLatch,
                            t[tref]+t[tcH]-t[trHmax]+7ns);
        EdgeSetOrigin       (H1LOWstrobeWF, Edge2, orgtH1low);
        EdgeSetOrigin       (H1LOWstrobeWF, Edge3, orgtH1low);

        WaveSetEdgeStrobe   (H1IDLEstrobeWF,
                            0ns,
                            t[tref]+t[tH1flo]+t[loosclock],
                            t[tref]+t[tH1flo]+t[loosclock]+7ns);

        WaveSetEdgeStrobe   (H3strobeWF,
                            0ns,
                            t[tref]+t[loosclock],
                            t[tref]+t[loosclock]+7ns);

        WaveSetEdgeStrobe   (H3LOWstrobeWF,
                            0ns,
                            t[tref]+t[tH3rhi]-t[trHmax],
                            t[tref]+t[tH3rhi]-t[trHmax]+7ns);
        EdgeSetOrigin       (H3LOWstrobeWF, Edge2, orgtH3low);
        EdgeSetOrigin       (H3LOWstrobeWF, Edge3, orgtH3low);

        EdgeSet             (H3HIGHstrobeWF,Edge1,DriveOff,
                            0ns);
        EdgeSet             (H3HIGHstrobeWF,Edge2,EdgeStrobeHigh,
                            t[tref]+t[tcH]+t[tH3flo]-t[tfHmax]);
        EdgeSet             (H3HIGHstrobeWF,Edge3,StrobeLatch,
                            t[tref]+t[tcH]+t[tH3flo]-t[tfHmax]+7ns);
        EdgeSetOrigin       (H3HIGHstrobeWF, Edge2, orgtH3high);
        EdgeSetOrigin       (H3HIGHstrobeWF, Edge3, orgtH3high);

        WaveSetEdgeStrobe   (H3IDLEstrobeWF,
                            0ns,
                            t[tref]+t[tH1flo]+t[loosclock],
                            t[tref]+t[tH1flo]+t[loosclock]+7ns);

        WaveSetEdgeStrobe   (STRBstrobeWF,
                            0ns,
                            t[tref]+t[tH1flo]+t[tdH1LS]+t[loosdelay7]-
                            t[tgb]-ctcf,
                            t[tref]+t[tH1flo]+t[tdH1LS]+t[loosdelay7]-
                            t[tgb]-ctcf+7ns);
        EdgeSetOrigin       (STRBstrobeWF, Edge2, orgtH1flo);
        EdgeSetOrigin       (STRBstrobeWF, Edge3, orgtH1flo);

        WaveSetEdgeStrobe   (RWstrobeWF,
                            0ns,
                            t[tref]+t[tdH1HRW]+t[loosdelay5]-t[tgb]-ctcf,
                            t[tref]+t[tdH1HRW]+t[loosdelay5]-t[tgb]-ctcf+7ns);

        WaveSetEdgeStrobe   (ABUSVstrobeWF,
                            0ns,
                            t[tref]+t[tH1flo]+t[tdH1LA]-t[restrict]-
                            t[loosdelay]+t[tgb]+ctcf+t[tcH]-7ns,
                            t[tref]+t[tH1flo]+t[tdH1LA]-t[restrict]-
                            t[loosdelay]+t[tgb]+ctcf+t[tcH]);
        EdgeSetOrigin       (ABUSVstrobeWF, Edge2, orgtH1flo);
        EdgeSetOrigin       (ABUSVstrobeWF, Edge3, orgtH1flo);

        WaveSetEdgeStrobe   (ABUSstrobeWF,
                            0ns,
                            t[tref]+t[tH1flo]+t[tdH1LA]+t[loosdelay7]-
                            t[tgb]-ctcf,
                            t[tref]+t[tH1flo]+t[tdH1LA]+t[loosdelay7]-
                            t[tgb]-ctcf+7ns);
        EdgeSetOrigin       (ABUSstrobeWF, Edge2, orgtH1flo);
        EdgeSetOrigin       (ABUSstrobeWF, Edge3, orgtH1flo);

        WaveSetEdgeStrobe   (ABUSWWstrobeWF,
                            0ns,
                            t[tref]+t[tdH1HA]+t[loosabus]-t[tgb]-ctcf,
                            t[tref]+t[tdH1HA]+t[loosabus]-t[tgb]-ctcf+7ns);

        WaveSetEdgeStrobe   (STATstrobeWF,
                            0ns,
                            t[tref]+t[tH1flo]+t[tdH1LSTAT]+t[loosdelay7]-
                            t[tgb]-ctcf,
                            t[tref]+t[tH1flo]+t[tdH1LSTAT]+t[loosdelay7]-
                            t[tgb]-ctcf+7ns);
        EdgeSetOrigin       (STATstrobeWF, Edge2, orgtH1flo);
        EdgeSetOrigin       (STATstrobeWF, Edge3, orgtH1flo);

        WaveSetEdgeStrobe   (LOCKstrobeWF,
                            0ns,
                            t[tref]+t[tH1flo]+t[tdH1LLOCK]+t[loosdelay4]-
                            t[tgb]-ctcf,
                            t[tref]+t[tH1flo]+t[tdH1LLOCK]+t[loosdelay4]-
                            t[tgb]-ctcf+7ns);
        EdgeSetOrigin       (LOCKstrobeWF, Edge2, orgtH1flo);
        EdgeSetOrigin       (LOCKstrobeWF, Edge3, orgtH1flo);

        WaveSetSBC          (DBUSdriveWF,
                            t[tref]+t[tH1flo]-t[tsuDR]-t[loossetup]+dtcf-7ns,
                            t[tref]+t[tH1flo]-t[tsuDR]-t[loossetup]+dtcf,
                            t[tref]+t[tH1flo]+t[thDR]+t[looshold]-dtcf);
        EdgeSetOrigin       (DBUSdriveWF, Edge1, orgtH1flo);
        EdgeSetOrigin       (DBUSdriveWF, Edge2, orgtH1flo);
        EdgeSetOrigin       (DBUSdriveWF, Edge3, orgtH1flo);

        WaveSetEdgeStrobe   (DBUSstrobeWF,
                            t[tref]+t[tH1flo]+t[tvDW]+t[loosdelay4]-
                            t[tgb]-ctcf-7ns,
                            t[tref]+t[tH1flo]+t[tvDW]+t[loosdelay4]-
                            t[tgb]-ctcf,
                            t[tref]+t[tH1flo]+t[tvDW]+t[loosdelay4]-
                            t[tgb]-ctcf+7ns);
        EdgeSetOrigin       (DBUSstrobeWF, Edge1, orgtH1flo);
        EdgeSetOrigin       (DBUSstrobeWF, Edge2, orgtH1flo);
        EdgeSetOrigin       (DBUSstrobeWF, Edge3, orgtH1flo);

        EdgeSet             (DBUSstrobeoffWF,Edge1,NullEdge,
                            t[tref]+t[thDW]-t[loosdelay]+t[tgb]+ctcf);

        WaveSetEdgeStrobe   (DBUSWWstrobeWF,
                            t[tref]+t[tH1flo]+t[tvDW]+t[loosdelay4]-
                            t[tgb]-ctcf-7ns,
                            t[tref]+t[tH1flo]+t[tvDW]+t[loosdelay4]-
                            t[tgb]-ctcf,
                            t[tref]+t[tH1flo]+t[tvDW]+t[loosdelay4]-
                            t[tgb]-ctcf+7ns);
        EdgeSetOrigin       (DBUSWWstrobeWF, Edge1, orgtH1flo);
        EdgeSetOrigin       (DBUSWWstrobeWF, Edge2, orgtH1flo);
        EdgeSetOrigin       (DBUSWWstrobeWF, Edge3, orgtH1flo);

        WaveSetEdgeStrobe   (DBUSWW2strobeWF,
                            t[tref]+t[tH1flo]+t[tvDW]+t[loosdelay4]-
                            t[tgb]-ctcf-7ns,
                            t[tref]+t[tH1flo]+t[tvDW]+t[loosdelay4]-
                            t[tgb]-ctcf,
                            t[tref]+t[tH1flo]+t[tvDW]+t[loosdelay4]-
                            t[tgb]-ctcf+7ns);
        EdgeSetOrigin       (DBUSWW2strobeWF, Edge1, orgtH1flo);
        EdgeSetOrigin       (DBUSWW2strobeWF, Edge2, orgtH1flo);
        EdgeSetOrigin       (DBUSWW2strobeWF, Edge3, orgtH1flo);

        WaveSetRTO          (RDYdriveWF,
                            t[tref]+t[tH1flo]-t[tsuRDY]-t[loossetup]+dtcf,
                            t[tref]+t[tH1flo]+t[thRDY]+t[looshold]-dtcf);
        EdgeSetOrigin       (RDYdriveWF, Edge1, orgtH1flo);
        EdgeSetOrigin       (RDYdriveWF, Edge2, orgtH1flo);

        WaveSetNR           (ENBdriveWF,
                            t[tref]+t[tENB]);

        WaveSetEdgeStrobeZ  (DBUSHIZstrobeWF,
                            0ns,
                            t[tref]+t[tENB]+t[tdENBZ]+t[loosdelay]-ctcf,
                            t[tref]+t[tENB]+t[tdENBZ]+t[loosdelay]-ctcf+7ns);

        WaveSetEdgeStrobeZ  (ABUSHIZstrobeWF,
                            0ns,
                            t[tref]+t[tENB]+t[tdENBZ]+t[loosdelay]-ctcf,
                            t[tref]+t[tENB]+t[tdENBZ]+t[loosdelay]-ctcf+7ns);

        WaveSetEdgeStrobeZ  (CTRLHIZstrobeWF,
                            0ns,
                            t[tref]+t[tENB]+t[tdENBZ]+t[loosdelay]-ctcf,
                            t[tref]+t[tENB]+t[tdENBZ]+t[loosdelay]-ctcf+7ns);

        WaveSetEdgeStrobe   (DBUSVALstrobeWF,
                            0ns,
                            t[tref]+t[tENB]+t[tdENBDV]+t[loosdelay4]-
                            t[tgb]-ctcf,
                            t[tref]+t[tENB]+t[tdENBDV]+t[loosdelay4]-
                            t[tgb]-ctcf+7ns);

        WaveSetEdgeStrobe   (ABUSVALstrobeWF,
                            0ns,
                            t[tref]+t[tENB]+t[tdENBAV]+t[loosdelay7]-
                            t[tgb]-ctcf,
                            t[tref]+t[tENB]+t[tdENBAV]+t[loosdelay7]-
                            t[tgb]-ctcf+6ns);

        WaveSetEdgeStrobe   (CTRLVALstrobeWF,
                            0ns,
                            t[tref]+t[tENB]+t[tdENBCV]+t[loosdelay]-
                            t[tgb]-ctcf,
                            t[tref]+t[tENB]+t[tdENBCV]+t[loosdelay]-
                            t[tgb]-ctcf+6ns);


        WaveSetSBC          (IIOFdriveWF,
                            t[tref]+t[tH1flo]-t[tsuIF]-t[loossetup]+dtcf-7ns,
                            t[tref]+t[tH1flo]-t[tsuIF]-t[loossetup]+dtcf,
                            t[tref]+t[tH1flo]+t[thIF]+t[looshold]-dtcf);
        EdgeSetOrigin       (IIOFdriveWF, Edge1, orgtH1flo);
        EdgeSetOrigin       (IIOFdriveWF, Edge2, orgtH1flo);
        EdgeSetOrigin       (IIOFdriveWF, Edge3, orgtH1flo);

        WaveSetEdgeStrobe   (IIOFstrobeWF,
                            t[tref]+t[tH1flo]+t[tvH1LIF]+t[loosdelay]-
                            t[tgb]-ctcf-7ns,
                            t[tref]+t[tH1flo]+t[tvH1LIF]+t[loosdelay]-
                            t[tgb]-ctcf,
                            t[tref]+t[tH1flo]+t[tvH1LIF]+t[loosdelay]-
                            t[tgb]-ctcf+7ns);
        EdgeSetOrigin       (IIOFstrobeWF, Edge1, orgtH1flo);
        EdgeSetOrigin       (IIOFstrobeWF, Edge2, orgtH1flo);
        EdgeSetOrigin       (IIOFstrobeWF, Edge3, orgtH1flo);

        EdgeSet             (IIOFstrobeoffWF,Edge1,NullEdge,
                            t[tref]+t[tH1flo]+t[thH1LIFOI]-t[loosdelay]+
                            t[tgb]+ctcf);
        EdgeSetOrigin       (IIOFstrobeoffWF, Edge1, orgtH1flo);

        WaveSetEdgeStrobe   (IIOFWWstrobeWF,
                            t[tref]+t[tH1flo]+t[tvH1LIF]+t[loosdelay]-
                            t[tgb]-ctcf-7ns,
                            t[tref]+t[tH1flo]+t[tvH1LIF]+t[loosdelay]-
                            t[tgb]-ctcf,
                            t[tref]+t[tH1flo]+t[tvH1LIF]+t[loosdelay]-
                            t[tgb]-ctcf+7ns);
        EdgeSetOrigin       (IIOFWWstrobeWF, Edge1, orgtH1flo);
        EdgeSetOrigin       (IIOFWWstrobeWF, Edge2, orgtH1flo);
        EdgeSetOrigin       (IIOFWWstrobeWF, Edge3, orgtH1flo);

        WaveSetNR           (INTdriveWF,
                            t[tref]+t[tH1flo]-t[tsuINT]-t[loossetup]+dtcf);
        EdgeSetOrigin       (INTdriveWF, Edge1, orgtH1flo);

        WaveSetNR           (INTIDLEdriveWF,
                            t[tref]+t[tH1flo]-t[tsuINTIDLE]-t[loossetup]+dtcf);
        EdgeSetOrigin       (INTdriveWF, Edge1, orgtH1flo);

        WaveSetEdgeStrobe   (IACKstrobeWF,
                            0ns,
                            t[tref]+t[tH1flo]+t[tdH1LIACK]+t[loosdelay6]-
                            t[tgb]-ctcf,
                            t[tref]+t[tH1flo]+t[tdH1LIACK]+t[loosdelay6]-
                            t[tgb]-ctcf+7ns);
        EdgeSetOrigin       (IACKstrobeWF, Edge2, orgtH1flo);
        EdgeSetOrigin       (IACKstrobeWF, Edge3, orgtH1flo);


        EdgeSetDelayData    (CREQdriveWF,Edge1,ChanFirst,
                            DriveData,ThreshVITL,
                            t[tref]+t[tH1flo]-t[tsuCREQ],0,
                            DriveData,ThreshVITH,
                            t[tref]+t[tH1flo]+t[tsuCREQ],0);

        EdgeSetDelayData    (CREQstrobeWF,Edge1,ChanFirst,
                            DriveOff,ThreshVITL,t[tref]+
                            t[tdH1HRQLt]+t[loosdelay]-t[tgb]-ctcf-7ns,0,
                            DriveOff,ThreshVITH,t[tref]+
                            t[tH1flo]-t[tsuCACK]+t[tdALRQHt]+
                            t[loosdelay]-t[tgb]-ctcf-7ns,0);
        EdgeSetDelayData    (CREQstrobeWF,Edge2,ChanFirst,
                            EdgeStrobeData,ThreshVITL,t[tref]+
                            t[tdH1HRQLt]+t[loosdelay]-t[tgb]-ctcf,0,
                            EdgeStrobeData,ThreshVITH,t[tref]+
                            t[tH1flo]-t[tsuCACK]+t[tdALRQHt]+
                            t[loosdelay]-t[tgb]-ctcf,0);
        EdgeSetDelayData    (CREQstrobeWF,Edge3,ChanFirst,
                            StrobeLatch,ThreshVITL,t[tref]+
                            t[tdH1HRQLt]+t[loosdelay]-t[tgb]-ctcf+7ns,0,
                            StrobeLatch,ThreshVITH,t[tref]+
                            t[tH1flo]-t[tsuCACK]+t[tdALRQHt]+
                            t[loosdelay]-t[tgb]-ctcf+7ns,0);

        EdgeSetDelayData    (CREQ2strobeWF,Edge1,ChanFirst,
                            DriveOff,ThreshVITL,t[tref]+
                            t[tH1flo]+t[tsuCREQ]+t[tdRQHRQLt]+
                            t[loosdelay]-t[tgb]-ctcf-7ns,0,
                            DriveOff,ThreshVITH,t[tref]+
                            t[tH1flo]+t[tsuCREQ]+t[tdRQHRQOt]+
                            t[loosdelay]-t[tgb]-ctcf-7ns,0);
        EdgeSetDelayData    (CREQ2strobeWF,Edge2,ChanFirst,
                            EdgeStrobeData,ThreshVITL,t[tref]+
                            t[tH1flo]+t[tsuCREQ]+t[tdRQHRQLt]+
                            t[loosdelay]-t[tgb]-ctcf,0,
                            EdgeStrobeData,ThreshVITH,t[tref]+
                            t[tH1flo]+t[tsuCREQ]+t[tdRQHRQOt]+
                            t[loosdelay]-t[tgb]-ctcf,0);
        EdgeSetDelayData    (CREQ2strobeWF,Edge3,ChanFirst,
                            StrobeLatch,ThreshVITL,t[tref]+
                            t[tH1flo]+t[tsuCREQ]+t[tdRQHRQLt]+
                            t[loosdelay]-t[tgb]-ctcf+7ns,0,
                            StrobeLatch,ThreshVITH,t[tref]+
                            t[tH1flo]+t[tsuCREQ]+t[tdRQHRQOt]+
                            t[loosdelay]-t[tgb]-ctcf+7ns,0);

        WaveSetNR           (CACKdriveWF,
                            t[tref]+t[tH1flo]-t[tsuCACK]);
        EdgeSetOrigin       (CACKdriveWF, Edge1, orgtH1flo);

        WaveSetEdgeStrobe   (CACKstrobeWF,
                            t[tref]+t[tH1flo]-t[tsuCREQ]+t[tdRQLALt]+
                            t[loosdelay7]-t[tgb]-ctcf-7ns,
                            t[tref]+t[tH1flo]-t[tsuCREQ]+t[tdRQLALt]+
                            t[loosdelay7]-t[tgb]-ctcf,
                            t[tref]+t[tH1flo]-t[tsuCREQ]+t[tdRQLALt]+
                            t[loosdelay7]-t[tgb]-ctcf+7ns);
        EdgeSetOrigin       (CACKstrobeWF, Edge1, orgtH1flo);
        EdgeSetOrigin       (CACKstrobeWF, Edge2, orgtH1flo);
        EdgeSetOrigin       (CACKstrobeWF, Edge3, orgtH1flo);

(* CRDY  Edge1 is defined as DriveData here, but in actuality should always   *)
(* end up being a drive-low edge based on pattern data and translation.       *)

        WaveSetRTO          (CRDYdriveWF,
                            t[tCRDYLO],
                            t[tCRDYHI]);

(* special cstrb_ strobe w/o origin used for sync-up only to avoid problems   *)
(* with bsearch.                                                              *)

        WaveSetEdgeStrobe   (CSTRB_SYNCstrobeWF,
                            t[tCRDYHI]-t[tcH]+t[tdRHSLw]-7ns,
                            t[tCRDYHI]-t[tcH]+t[tdRHSLw],
                            t[tCRDYHI]-t[tcH]+t[tdRHSLw]+7ns);

        EdgeSetDelayData    (CSTRBstrobeWF,Edge1,ChanFirst,
                            DriveOff,ThreshVITL,t[tCRDYHI]-t[tcH]+
                            t[tdRHSLw]+t[loosdelay6]-t[tgb]-ctcf-7ns,0,
                            DriveOff,ThreshVITH,t[tCRDYLO]+
                            t[tdRLSHw]+t[loosdelay]-t[tgb]-ctcf-7ns,0);
        EdgeSetDelayData    (CSTRBstrobeWF,Edge2,ChanFirst,
                            EdgeStrobeData,ThreshVITL,t[tCRDYHI]-t[tcH]+
                            t[tdRHSLw]+t[loosdelay6]-t[tgb]-ctcf,0,
                            EdgeStrobeData,ThreshVITH,t[tCRDYLO]+
                            t[tdRLSHw]+t[loosdelay]-t[tgb]-ctcf,0);
        EdgeSetDelayData    (CSTRBstrobeWF,Edge3,ChanFirst,
                            StrobeLatch,ThreshVITL,t[tCRDYHI]-t[tcH]+
                            t[tdRHSLw]+t[loosdelay6]-t[tgb]-ctcf+7ns,0,
                            StrobeLatch,ThreshVITH,t[tCRDYLO]+
                            t[tdRLSHw]+t[loosdelay]-t[tgb]-ctcf+7ns,0);

        WaveSetEdgeStrobe   (CDstrobeWF,
                            t[tref]+t[tCSTRBfhi]-t[tsuCDw]+
                            t[loosdelay]-t[tgb]-ctcf-7ns,
                            t[tref]+t[tCSTRBfhi]-t[tsuCDw]+
                            t[loosdelay]-t[tgb]-ctcf,
                            t[tref]+t[tCSTRBfhi]-t[tsuCDw]+
                            t[loosdelay]-t[tgb]-ctcf+7ns);
        EdgeSetOrigin       (CDstrobeWF, Edge1, orgtCSTRBfhi);
        EdgeSetOrigin       (CDstrobeWF, Edge2, orgtCSTRBfhi);
        EdgeSetOrigin       (CDstrobeWF, Edge3, orgtCSTRBfhi);

(* CSTRB Edge1 is defined as DriveData here, but in actuality should always   *)
(* end up being a drive-low edge based on pattern data and translation.       *)

        WaveSetRTO          (CSTRBdriveWF,
                            t[tCSTRBLO],
                            t[tCSTRBHI]);
        EdgeSetOrigin       (CSTRBdriveWF, Edge1, orgtCSTRBfhi);
        EdgeSetOrigin       (CSTRBdriveWF, Edge2, orgtCSTRBfhi);

        WaveSetEdgeStrobe   (CRDY_SYNCstrobeWF,          (*special crdy_  strobe*)
                            t[tCSTRBLO]+t[tdSLRLr]-7ns,  (*w/o origin used for  *)
                            t[tCSTRBLO]+t[tdSLRLr],      (*sync-up only to avoid*)
                            t[tCSTRBLO]+t[tdSLRLr]+7ns); (*problems with bsearch*)

        EdgeSetDelayData    (CRDYstrobeWF,Edge1,ChanFirst,
                            DriveOff,ThreshVITL,t[tCSTRBLO]+
                            t[tdSLRLr]+t[loosdelay4]-t[tgb]-ctcf-7ns,0,
                            DriveOff,ThreshVITH,t[tCSTRBHI]+
                            t[tdSHRHr]+t[loosdelay]-t[tgb]-ctcf-7ns,0);
        EdgeSetDelayData    (CRDYstrobeWF,Edge2,ChanFirst,
                            EdgeStrobeData,ThreshVITL,t[tCSTRBLO]+
                            t[tdSLRLr]+t[loosdelay4]-t[tgb]-ctcf,0,
                            EdgeStrobeData,ThreshVITH,t[tCSTRBHI]+
                            t[tdSHRHr]+t[loosdelay]-t[tgb]-ctcf,0);
        EdgeSetDelayData    (CRDYstrobeWF,Edge3,ChanFirst,
                            StrobeLatch,ThreshVITL,t[tCSTRBLO]+
                            t[tdSLRLr]+t[loosdelay4]-t[tgb]-ctcf+7ns,0,
                            StrobeLatch,ThreshVITH,t[tCSTRBHI]+
                            t[tdSHRHr]+t[loosdelay]-t[tgb]-ctcf+7ns,0);

        EdgeSetDelayData    (CDdriveWF,Edge1,ChanFirst,
                            DriveComplement,ThreshVITL,t[tCSTRBLO]-
                            t[tsuCDr]-t[loossetup]+dtcf-7ns,0,
                            DriveComplement,ThreshVITH,t[tCSTRBLO]-
                            t[tsuCDr]-t[looscd]-t[loossetup]+dtcf-7ns,0);
        EdgeSetDelayData    (CDdriveWF,Edge2,ChanFirst,
                            DriveData,ThreshVITL,t[tCSTRBLO]-
                            t[tsuCDr]-t[loossetup]+dtcf,0,
                            DriveData,ThreshVITH,t[tCSTRBLO]-
                            t[tsuCDr]-t[looscd]-t[loossetup]+dtcf,0);
        EdgeSetDelayData    (CDdriveWF,Edge3,ChanFirst,
                            DriveComplement,ThreshVITL,t[tref]+t[tCRDYflo]+
                            t[thCDr]+t[looscd]+t[looshold]-dtcf,0,
                            DriveComplement,ThreshVITH,t[tref]+t[tCRDYflo]+
                            t[thCDr]+t[looshold]-dtcf,0);


        WaveSetSBC          (TCLKdriveWF,
                            t[tref]+t[tH1flo]-t[tsuTCLK]-t[loossetup]+dtcf-7ns,
                            t[tref]+t[tH1flo]-t[tsuTCLK]-t[loossetup]+dtcf,
                            t[tref]+t[tH1flo]+t[thTCLK]+t[looshold]-dtcf);
        EdgeSetOrigin       (TCLKdriveWF, Edge1, orgtH1flo);
        EdgeSetOrigin       (TCLKdriveWF, Edge2, orgtH1flo);
        EdgeSetOrigin       (TCLKdriveWF, Edge3, orgtH1flo);

        WaveSetEdgeStrobe   (TCLKstrobeWF,
                            t[tref]+t[tdTCLK]+t[loosdelay4]-t[tgb]-ctcf-7ns,
                            t[tref]+t[tdTCLK]+t[loosdelay4]-t[tgb]-ctcf,
                            t[tref]+t[tdTCLK]+t[loosdelay4]-t[tgb]-ctcf+7ns);


        WaveSetRTO          (TCKCLKdriveWF,
                            t[tref],
                            t[tref]+t[tcCI]);

        WaveSetNR           (TCKdriveWF,
                            t[tref]);

        WaveSetSBC          (TDITMSdriveWF,
                            t[tref]+t[tcCI]-t[tsuTDITMS]-t[loossetup]+dtcf-7ns,
                            t[tref]+t[tcCI]-t[tsuTDITMS]-t[loossetup]+dtcf,
                            t[tref]+t[tcCI]+t[thTDITMS]+t[looshold]-dtcf);

        WaveSetNR           (JTAGdriveWF,
                            t[tref]+t[tJTAG]);

        WaveSetEdgeStrobe   (TDOstrobeWF,
                            0ns,
                            t[tref]+t[tdTDO]+t[loosdelay]-t[tgb]-ctcf,
                            t[tref]+t[tdTDO]+t[loosdelay]-t[tgb]-ctcf+7ns);

        WaveSetEdgeStrobe   (JTAGH1strobeWF,
                            0ns,
                            t[tref]+t[tdTDO]+t[loosdelay]-t[tgb]-ctcf,
                            t[tref]+t[tdTDO]+t[loosdelay]-t[tgb]-ctcf+7ns);

        WaveSetEdgeStrobe   (JTAGVARYstrobeWF,
                            0ns,
                            t[tref]+t[tdTDO]+t[tcCI]+t[loosdelay]-t[tgb]-ctcf,
                            t[tref]+t[tdTDO]+t[tcCI]+t[loosdelay]-t[tgb]-ctcf+7ns);

        WaveSetEdgeStrobe   (JTAGABUSstrobeWF,
                            0ns,
                            t[tref]+t[tdTDO]+t[tcCI]+t[loosdelay]-t[tgb]-ctcf,
                            t[tref]+t[tdTDO]+t[tcCI]+t[loosdelay]-t[tgb]-ctcf+7ns);


        WaveSetNR           (EMUdriveWF,
                            t[tref]+t[tEMU]);

        WaveSetEdgeStrobe   (EMUstrobeWF,
                            0ns,
                            t[tref]+t[tdEMU]+t[loosdelay]-t[tgb]-ctcf,
                            t[tref]+t[tdEMU]+t[loosdelay]-t[tgb]-ctcf+7ns);


        WaveSetNR           (RESETLOCdriveWF,
                            t[tref]+t[tRESETLOC]);

        WaveSetNR           (ROMENdriveWF,
                            t[tref]+t[tROMEN]);

        WaveSetNR           (NMIdriveWF,
                            t[tref]+t[tNMI]);


        WaveSetContinue     (ContinueWF);

        WaveSetOff          (ALLoffWF,t[tref],t[tref]);

STOP(ALLENUMS,TIspecholdmin25ACTable,TIspecholdmax25ACTable);

          end; (*8th case*)


        TIspecholdmin33ACTable,
        TIspecholdmax33ACTable:
          begin

START(ALLENUMS,TIspecholdmin33ACTable,TIspecholdmax33ACTable);

        WaveSetDoubleClk    (CLKINdriveWF,
                            t[tref]+t[toffset],
                            t[tref]+t[toffset]+t[twCIH],
                            t[tref]+t[toffset]+t[twCIH]+t[twCIL],
                            t[tref]+t[toffset]+t[twCIH]+t[twCIL]+t[twCIH]);
        EdgeSetOrigin       (CLKINdriveWF, Edge1, orgtoffset);
        EdgeSetOrigin       (CLKINdriveWF, Edge2, orgtoffset);
        EdgeSetOrigin       (CLKINdriveWF, Edge3, orgtoffset);
        EdgeSetOrigin       (CLKINdriveWF, Edge4, orgtoffset);

        EdgeSetDelayData    (RESETdriveWF,Edge1,ChanFirst,
                            DriveData,ThreshVITL,
                            t[tref]+t[toffset]+t[twCIH]+t[twCIL]+t[twCIH]-t[tsuRESET]-t[loossetup]+dtcf,0,
                            DriveData,ThreshVITH,
                            t[tref]+t[tH1flo]-t[tsuRESETH]-t[loossetup]+dtcf,0);

        WaveSetEdgeStrobe   (H1strobeWF,
                            0ns,
                            t[tref]+t[loosclock],
                            t[tref]+t[loosclock]+7ns);

        WaveSetEdgeStrobe   (H1HIGHstrobeWF,
                            0ns,
                            t[tref]+t[tH1flo]-t[tfHmax],
                            t[tref]+t[tH1flo]-t[tfHmax]+7ns);
        EdgeSetOrigin       (H1HIGHstrobeWF, Edge2, orgtH1high);
        EdgeSetOrigin       (H1HIGHstrobeWF, Edge3, orgtH1high);

        EdgeSet             (H1LOWstrobeWF,Edge1,DriveOff,
                            0ns);
        EdgeSet             (H1LOWstrobeWF,Edge2,EdgeStrobeLow,
                            t[tref]+t[tcH]-t[trHmax]);
        EdgeSet             (H1LOWstrobeWF,Edge3,StrobeLatch,
                            t[tref]+t[tcH]-t[trHmax]+7ns);
        EdgeSetOrigin       (H1LOWstrobeWF, Edge2, orgtH1low);
        EdgeSetOrigin       (H1LOWstrobeWF, Edge3, orgtH1low);

        WaveSetEdgeStrobe   (H1IDLEstrobeWF,
                            0ns,
                            t[tref]+t[tH1flo]+t[loosclock],
                            t[tref]+t[tH1flo]+t[loosclock]+7ns);

        WaveSetEdgeStrobe   (H3strobeWF,
                            0ns,
                            t[tref]+t[loosclock],
                            t[tref]+t[loosclock]+7ns);

        WaveSetEdgeStrobe   (H3LOWstrobeWF,
                            0ns,
                            t[tref]+t[tH3rhi]-t[trHmax],
                            t[tref]+t[tH3rhi]-t[trHmax]+7ns);
        EdgeSetOrigin       (H3LOWstrobeWF, Edge2, orgtH3low);
        EdgeSetOrigin       (H3LOWstrobeWF, Edge3, orgtH3low);

        EdgeSet             (H3HIGHstrobeWF,Edge1,DriveOff,
                            0ns);
        EdgeSet             (H3HIGHstrobeWF,Edge2,EdgeStrobeHigh,
                            t[tref]+t[tcH]+t[tH3flo]-t[tfHmax]);
        EdgeSet             (H3HIGHstrobeWF,Edge3,StrobeLatch,
                            t[tref]+t[tcH]+t[tH3flo]-t[tfHmax]+7ns);
        EdgeSetOrigin       (H3HIGHstrobeWF, Edge2, orgtH3high);
        EdgeSetOrigin       (H3HIGHstrobeWF, Edge3, orgtH3high);

        WaveSetEdgeStrobe   (H3IDLEstrobeWF,
                            0ns,
                            t[tref]+t[tH1flo]+t[loosclock],
                            t[tref]+t[tH1flo]+t[loosclock]+7ns);

        WaveSetEdgeStrobe   (STRBstrobeWF,
                            0ns,
                            t[tref]+t[tH1flo]+t[tdH1LS]+t[loosdelay7]-
                            t[tgb]-ctcf,
                            t[tref]+t[tH1flo]+t[tdH1LS]+t[loosdelay7]-
                            t[tgb]-ctcf+7ns);
        EdgeSetOrigin       (STRBstrobeWF, Edge2, orgtH1flo);
        EdgeSetOrigin       (STRBstrobeWF, Edge3, orgtH1flo);

        WaveSetEdgeStrobe   (RWstrobeWF,
                            0ns,
                            t[tref]+t[tdH1HRW]+t[loosdelay5]-t[tgb]-ctcf,
                            t[tref]+t[tdH1HRW]+t[loosdelay5]-t[tgb]-ctcf+7ns);

        WaveSetEdgeStrobe   (ABUSVstrobeWF,
                            0ns,
                            t[tref]+t[tH1flo]+t[tdH1LA]-t[restrict]-
                            t[loosdelay]+t[tgb]+ctcf+t[tcH]-7ns,
                            t[tref]+t[tH1flo]+t[tdH1LA]-t[restrict]-
                            t[loosdelay]+t[tgb]+ctcf+t[tcH]);
        EdgeSetOrigin       (ABUSVstrobeWF, Edge2, orgtH1flo);
        EdgeSetOrigin       (ABUSVstrobeWF, Edge3, orgtH1flo);

        WaveSetEdgeStrobe   (ABUSstrobeWF,
                            0ns,
                            t[tref]+t[tH1flo]+t[tdH1LA]+t[loosdelay7]-
                            t[tgb]-ctcf,
                            t[tref]+t[tH1flo]+t[tdH1LA]+t[loosdelay7]-
                            t[tgb]-ctcf+7ns);
        EdgeSetOrigin       (ABUSstrobeWF, Edge2, orgtH1flo);
        EdgeSetOrigin       (ABUSstrobeWF, Edge3, orgtH1flo);

        WaveSetEdgeStrobe   (ABUSWWstrobeWF,
                            0ns,
                            t[tref]+t[tdH1HA]+t[loosabus]-t[tgb]-ctcf,
                            t[tref]+t[tdH1HA]+t[loosabus]-t[tgb]-ctcf+7ns);

        WaveSetEdgeStrobe   (STATstrobeWF,
                            0ns,
                            t[tref]+t[tH1flo]+t[tdH1LSTAT]+t[loosdelay7]-
                            t[tgb]-ctcf,
                            t[tref]+t[tH1flo]+t[tdH1LSTAT]+t[loosdelay7]-
                            t[tgb]-ctcf+7ns);
        EdgeSetOrigin       (STATstrobeWF, Edge2, orgtH1flo);
        EdgeSetOrigin       (STATstrobeWF, Edge3, orgtH1flo);

        WaveSetEdgeStrobe   (LOCKstrobeWF,
                            0ns,
                            t[tref]+t[tH1flo]+t[tdH1LLOCK]+t[loosdelay4]-
                            t[tgb]-ctcf,
                            t[tref]+t[tH1flo]+t[tdH1LLOCK]+t[loosdelay4]-
                            t[tgb]-ctcf+7ns);
        EdgeSetOrigin       (LOCKstrobeWF, Edge2, orgtH1flo);
        EdgeSetOrigin       (LOCKstrobeWF, Edge3, orgtH1flo);

        WaveSetSBC          (DBUSdriveWF,
                            t[tref]+t[tH1flo]-t[tsuDR]-t[loossetup]+dtcf-7ns,
                            t[tref]+t[tH1flo]-t[tsuDR]-t[loossetup]+dtcf,
                            t[tref]+t[tH1flo]+t[thDR]+t[looshold]-dtcf);
        EdgeSetOrigin       (DBUSdriveWF, Edge1, orgtH1flo);
        EdgeSetOrigin       (DBUSdriveWF, Edge2, orgtH1flo);
        EdgeSetOrigin       (DBUSdriveWF, Edge3, orgtH1flo);

        WaveSetEdgeStrobe   (DBUSstrobeWF,
                            t[tref]+t[tH1flo]+t[tvDW]+t[loosdelay4]-
                            t[tgb]-ctcf-7ns,
                            t[tref]+t[tH1flo]+t[tvDW]+t[loosdelay4]-
                            t[tgb]-ctcf,
                            t[tref]+t[tH1flo]+t[tvDW]+t[loosdelay4]-
                            t[tgb]-ctcf+7ns);
        EdgeSetOrigin       (DBUSstrobeWF, Edge1, orgtH1flo);
        EdgeSetOrigin       (DBUSstrobeWF, Edge2, orgtH1flo);
        EdgeSetOrigin       (DBUSstrobeWF, Edge3, orgtH1flo);

        EdgeSet             (DBUSstrobeoffWF,Edge1,NullEdge,
                            t[tref]+t[thDW]-t[loosdelay]+t[tgb]+ctcf);

        WaveSetEdgeStrobe   (DBUSWWstrobeWF,
                            t[tref]+t[tH1flo]+t[tvDW]+t[loosdelay4]-
                            t[tgb]-ctcf-7ns,
                            t[tref]+t[tH1flo]+t[tvDW]+t[loosdelay4]-
                            t[tgb]-ctcf,
                            t[tref]+t[tH1flo]+t[tvDW]+t[loosdelay4]-
                            t[tgb]-ctcf+7ns);
        EdgeSetOrigin       (DBUSWWstrobeWF, Edge1, orgtH1flo);
        EdgeSetOrigin       (DBUSWWstrobeWF, Edge2, orgtH1flo);
        EdgeSetOrigin       (DBUSWWstrobeWF, Edge3, orgtH1flo);

        WaveSetEdgeStrobe   (DBUSWW2strobeWF,
                            t[tref]+t[tH1flo]+t[tvDW]+t[loosdelay4]-
                            t[tgb]-ctcf-7ns,
                            t[tref]+t[tH1flo]+t[tvDW]+t[loosdelay4]-
                            t[tgb]-ctcf,
                            t[tref]+t[tH1flo]+t[tvDW]+t[loosdelay4]-
                            t[tgb]-ctcf+7ns);
        EdgeSetOrigin       (DBUSWW2strobeWF, Edge1, orgtH1flo);
        EdgeSetOrigin       (DBUSWW2strobeWF, Edge2, orgtH1flo);
        EdgeSetOrigin       (DBUSWW2strobeWF, Edge3, orgtH1flo);

        WaveSetRTO          (RDYdriveWF,
                            t[tref]+t[tH1flo]-t[tsuRDY]-t[loossetup]+dtcf,
                            t[tref]+t[tH1flo]+t[thRDY]+t[looshold]-dtcf);
        EdgeSetOrigin       (RDYdriveWF, Edge1, orgtH1flo);
        EdgeSetOrigin       (RDYdriveWF, Edge2, orgtH1flo);

        WaveSetNR           (ENBdriveWF,
                            t[tref]+t[tENB]);

        WaveSetEdgeStrobeZ  (DBUSHIZstrobeWF,
                            0ns,
                            t[tref]+t[tENB]+t[tdENBZ]+t[loosdelay]-ctcf,
                            t[tref]+t[tENB]+t[tdENBZ]+t[loosdelay]-ctcf+7ns);

        WaveSetEdgeStrobeZ  (ABUSHIZstrobeWF,
                            0ns,
                            t[tref]+t[tENB]+t[tdENBZ]+t[loosdelay]-ctcf,
                            t[tref]+t[tENB]+t[tdENBZ]+t[loosdelay]-ctcf+7ns);

        WaveSetEdgeStrobeZ  (CTRLHIZstrobeWF,
                            0ns,
                            t[tref]+t[tENB]+t[tdENBZ]+t[loosdelay]-ctcf,
                            t[tref]+t[tENB]+t[tdENBZ]+t[loosdelay]-ctcf+7ns);

        WaveSetEdgeStrobe   (DBUSVALstrobeWF,
                            0ns,
                            t[tref]+t[tENB]+t[tdENBDV]+t[loosdelay4]-
                            t[tgb]-ctcf,
                            t[tref]+t[tENB]+t[tdENBDV]+t[loosdelay4]-
                            t[tgb]-ctcf+7ns);

        WaveSetEdgeStrobe   (ABUSVALstrobeWF,
                            0ns,
                            t[tref]+t[tENB]+t[tdENBAV]+t[loosdelay7]-
                            t[tgb]-ctcf,
                            t[tref]+t[tENB]+t[tdENBAV]+t[loosdelay7]-
                            t[tgb]-ctcf+6ns);

        WaveSetEdgeStrobe   (CTRLVALstrobeWF,
                            0ns,
                            t[tref]+t[tENB]+t[tdENBCV]+t[loosdelay]-
                            t[tgb]-ctcf,
                            t[tref]+t[tENB]+t[tdENBCV]+t[loosdelay]-
                            t[tgb]-ctcf+6ns);


        WaveSetSBC          (IIOFdriveWF,
                            t[tref]+t[tH1flo]-t[tsuIF]-t[loossetup]+dtcf-7ns,
                            t[tref]+t[tH1flo]-t[tsuIF]-t[loossetup]+dtcf,
                            t[tref]+t[tH1flo]+t[thIF]+t[looshold]-dtcf);
        EdgeSetOrigin       (IIOFdriveWF, Edge1, orgtH1flo);
        EdgeSetOrigin       (IIOFdriveWF, Edge2, orgtH1flo);
        EdgeSetOrigin       (IIOFdriveWF, Edge3, orgtH1flo);

        WaveSetEdgeStrobe   (IIOFstrobeWF,
                            t[tref]+t[tH1flo]+t[tvH1LIF]+t[loosdelay]-
                            t[tgb]-ctcf-7ns,
                            t[tref]+t[tH1flo]+t[tvH1LIF]+t[loosdelay]-
                            t[tgb]-ctcf,
                            t[tref]+t[tH1flo]+t[tvH1LIF]+t[loosdelay]-
                            t[tgb]-ctcf+7ns);
        EdgeSetOrigin       (IIOFstrobeWF, Edge1, orgtH1flo);
        EdgeSetOrigin       (IIOFstrobeWF, Edge2, orgtH1flo);
        EdgeSetOrigin       (IIOFstrobeWF, Edge3, orgtH1flo);

        EdgeSet             (IIOFstrobeoffWF,Edge1,NullEdge,
                            t[tref]+t[tH1flo]+t[thH1LIFOI]-t[loosdelay]+
                            t[tgb]+ctcf);
        EdgeSetOrigin       (IIOFstrobeoffWF, Edge1, orgtH1flo);

        WaveSetEdgeStrobe   (IIOFWWstrobeWF,
                            t[tref]+t[tH1flo]+t[tvH1LIF]+t[loosdelay]-
                            t[tgb]-ctcf-7ns,
                            t[tref]+t[tH1flo]+t[tvH1LIF]+t[loosdelay]-
                            t[tgb]-ctcf,
                            t[tref]+t[tH1flo]+t[tvH1LIF]+t[loosdelay]-
                            t[tgb]-ctcf+7ns);
        EdgeSetOrigin       (IIOFWWstrobeWF, Edge1, orgtH1flo);
        EdgeSetOrigin       (IIOFWWstrobeWF, Edge2, orgtH1flo);
        EdgeSetOrigin       (IIOFWWstrobeWF, Edge3, orgtH1flo);

        WaveSetNR           (INTdriveWF,
                            t[tref]+t[tH1flo]-t[tsuINT]-t[loossetup]+dtcf);
        EdgeSetOrigin       (INTdriveWF, Edge1, orgtH1flo);

        WaveSetNR           (INTIDLEdriveWF,
                            t[tref]+t[tH1flo]-t[tsuINTIDLE]-t[loossetup]+dtcf);
        EdgeSetOrigin       (INTdriveWF, Edge1, orgtH1flo);

        WaveSetEdgeStrobe   (IACKstrobeWF,
                            0ns,
                            t[tref]+t[tH1flo]+t[tdH1LIACK]+t[loosdelay6]-
                            t[tgb]-ctcf,
                            t[tref]+t[tH1flo]+t[tdH1LIACK]+t[loosdelay6]-
                            t[tgb]-ctcf+7ns);
        EdgeSetOrigin       (IACKstrobeWF, Edge2, orgtH1flo);
        EdgeSetOrigin       (IACKstrobeWF, Edge3, orgtH1flo);


        EdgeSetDelayData    (CREQdriveWF,Edge1,ChanFirst,
                            DriveData,ThreshVITL,
                            t[tref]+t[tH1flo]-t[tsuCREQ],0,
                            DriveData,ThreshVITH,
                            t[tref]+t[tH1flo]+t[tsuCREQ],0);

        EdgeSetDelayData    (CREQstrobeWF,Edge1,ChanFirst,
                            DriveOff,ThreshVITL,t[tref]+
                            t[tdH1HRQLt]+t[loosdelay]-t[tgb]-ctcf-7ns,0,
                            DriveOff,ThreshVITH,t[tref]+
                            t[tH1flo]-t[tsuCACK]+t[tdALRQHt]+
                            t[loosdelay]-t[tgb]-ctcf-7ns,0);
        EdgeSetDelayData    (CREQstrobeWF,Edge2,ChanFirst,
                            EdgeStrobeData,ThreshVITL,t[tref]+
                            t[tdH1HRQLt]+t[loosdelay]-t[tgb]-ctcf,0,
                            EdgeStrobeData,ThreshVITH,t[tref]+
                            t[tH1flo]-t[tsuCACK]+t[tdALRQHt]+
                            t[loosdelay]-t[tgb]-ctcf,0);
        EdgeSetDelayData    (CREQstrobeWF,Edge3,ChanFirst,
                            StrobeLatch,ThreshVITL,t[tref]+
                            t[tdH1HRQLt]+t[loosdelay]-t[tgb]-ctcf+7ns,0,
                            StrobeLatch,ThreshVITH,t[tref]+
                            t[tH1flo]-t[tsuCACK]+t[tdALRQHt]+
                            t[loosdelay]-t[tgb]-ctcf+7ns,0);

        EdgeSetDelayData    (CREQ2strobeWF,Edge1,ChanFirst,
                            DriveOff,ThreshVITL,t[tref]+
                            t[tH1flo]+t[tsuCREQ]+t[tdRQHRQLt]+
                            t[loosdelay]-t[tgb]-ctcf-7ns,0,
                            DriveOff,ThreshVITH,t[tref]+
                            t[tH1flo]+t[tsuCREQ]+t[tdRQHRQOt]+
                            t[loosdelay]-t[tgb]-ctcf-7ns,0);
        EdgeSetDelayData    (CREQ2strobeWF,Edge2,ChanFirst,
                            EdgeStrobeData,ThreshVITL,t[tref]+
                            t[tH1flo]+t[tsuCREQ]+t[tdRQHRQLt]+
                            t[loosdelay]-t[tgb]-ctcf,0,
                            EdgeStrobeData,ThreshVITH,t[tref]+
                            t[tH1flo]+t[tsuCREQ]+t[tdRQHRQOt]+
                            t[loosdelay]-t[tgb]-ctcf,0);
        EdgeSetDelayData    (CREQ2strobeWF,Edge3,ChanFirst,
                            StrobeLatch,ThreshVITL,t[tref]+
                            t[tH1flo]+t[tsuCREQ]+t[tdRQHRQLt]+
                            t[loosdelay]-t[tgb]-ctcf+7ns,0,
                            StrobeLatch,ThreshVITH,t[tref]+
                            t[tH1flo]+t[tsuCREQ]+t[tdRQHRQOt]+
                            t[loosdelay]-t[tgb]-ctcf+7ns,0);

        WaveSetNR           (CACKdriveWF,
                            t[tref]+t[tH1flo]-t[tsuCACK]);
        EdgeSetOrigin       (CACKdriveWF, Edge1, orgtH1flo);

        WaveSetEdgeStrobe   (CACKstrobeWF,
                            t[tref]+t[tH1flo]-t[tsuCREQ]+t[tdRQLALt]+
                            t[loosdelay7]-t[tgb]-ctcf-7ns,
                            t[tref]+t[tH1flo]-t[tsuCREQ]+t[tdRQLALt]+
                            t[loosdelay7]-t[tgb]-ctcf,
                            t[tref]+t[tH1flo]-t[tsuCREQ]+t[tdRQLALt]+
                            t[loosdelay7]-t[tgb]-ctcf+7ns);
        EdgeSetOrigin       (CACKstrobeWF, Edge1, orgtH1flo);
        EdgeSetOrigin       (CACKstrobeWF, Edge2, orgtH1flo);
        EdgeSetOrigin       (CACKstrobeWF, Edge3, orgtH1flo);

(* CRDY  Edge1 is defined as DriveData here, but in actuality should always   *)
(* end up being a drive-low edge based on pattern data and translation.       *)

        WaveSetRTO          (CRDYdriveWF,
                            t[tCRDYLO],
                            t[tCRDYHI]);

(* special cstrb_ strobe w/o origin used for sync-up only to avoid problems   *)
(* with bsearch.                                                              *)

        WaveSetEdgeStrobe   (CSTRB_SYNCstrobeWF,
                            t[tCRDYHI]-t[tcH]+t[tdRHSLw]-7ns,
                            t[tCRDYHI]-t[tcH]+t[tdRHSLw],
                            t[tCRDYHI]-t[tcH]+t[tdRHSLw]+7ns);

        EdgeSetDelayData    (CSTRBstrobeWF,Edge1,ChanFirst,
                            DriveOff,ThreshVITL,t[tCRDYHI]-t[tcH]+
                            t[tdRHSLw]+t[loosdelay6]-t[tgb]-ctcf-7ns,0,
                            DriveOff,ThreshVITH,t[tCRDYLO]+
                            t[tdRLSHw]+t[loosdelay]-t[tgb]-ctcf-7ns,0);
        EdgeSetDelayData    (CSTRBstrobeWF,Edge2,ChanFirst,
                            EdgeStrobeData,ThreshVITL,t[tCRDYHI]-t[tcH]+
                            t[tdRHSLw]+t[loosdelay6]-t[tgb]-ctcf,0,
                            EdgeStrobeData,ThreshVITH,t[tCRDYLO]+
                            t[tdRLSHw]+t[loosdelay]-t[tgb]-ctcf,0);
        EdgeSetDelayData    (CSTRBstrobeWF,Edge3,ChanFirst,
                            StrobeLatch,ThreshVITL,t[tCRDYHI]-t[tcH]+
                            t[tdRHSLw]+t[loosdelay6]-t[tgb]-ctcf+7ns,0,
                            StrobeLatch,ThreshVITH,t[tCRDYLO]+
                            t[tdRLSHw]+t[loosdelay]-t[tgb]-ctcf+7ns,0);

        WaveSetEdgeStrobe   (CDstrobeWF,
                            t[tref]+t[tCSTRBfhi]-t[tsuCDw]+
                            t[loosdelay]-t[tgb]-ctcf-7ns,
                            t[tref]+t[tCSTRBfhi]-t[tsuCDw]+
                            t[loosdelay]-t[tgb]-ctcf,
                            t[tref]+t[tCSTRBfhi]-t[tsuCDw]+
                            t[loosdelay]-t[tgb]-ctcf+7ns);
        EdgeSetOrigin       (CDstrobeWF, Edge1, orgtCSTRBfhi);
        EdgeSetOrigin       (CDstrobeWF, Edge2, orgtCSTRBfhi);
        EdgeSetOrigin       (CDstrobeWF, Edge3, orgtCSTRBfhi);

(* CSTRB Edge1 is defined as DriveData here, but in actuality should always   *)
(* end up being a drive-low edge based on pattern data and translation.       *)

        WaveSetRTO          (CSTRBdriveWF,
                            t[tCSTRBLO],
                            t[tCSTRBHI]);
        EdgeSetOrigin       (CSTRBdriveWF, Edge1, orgtCSTRBfhi);
        EdgeSetOrigin       (CSTRBdriveWF, Edge2, orgtCSTRBfhi);

        WaveSetEdgeStrobe   (CRDY_SYNCstrobeWF,          (*special crdy_  strobe*)
                            t[tCSTRBLO]+t[tdSLRLr]-7ns,  (*w/o origin used for  *)
                            t[tCSTRBLO]+t[tdSLRLr],      (*sync-up only to avoid*)
                            t[tCSTRBLO]+t[tdSLRLr]+7ns); (*problems with bsearch*)

        EdgeSetDelayData    (CRDYstrobeWF,Edge1,ChanFirst,
                            DriveOff,ThreshVITL,t[tCSTRBLO]+
                            t[tdSLRLr]+t[loosdelay4]-t[tgb]-ctcf-7ns,0,
                            DriveOff,ThreshVITH,t[tCSTRBHI]+
                            t[tdSHRHr]+t[loosdelay]-t[tgb]-ctcf-7ns,0);
        EdgeSetDelayData    (CRDYstrobeWF,Edge2,ChanFirst,
                            EdgeStrobeData,ThreshVITL,t[tCSTRBLO]+
                            t[tdSLRLr]+t[loosdelay4]-t[tgb]-ctcf,0,
                            EdgeStrobeData,ThreshVITH,t[tCSTRBHI]+
                            t[tdSHRHr]+t[loosdelay]-t[tgb]-ctcf,0);
        EdgeSetDelayData    (CRDYstrobeWF,Edge3,ChanFirst,
                            StrobeLatch,ThreshVITL,t[tCSTRBLO]+
                            t[tdSLRLr]+t[loosdelay4]-t[tgb]-ctcf+7ns,0,
                            StrobeLatch,ThreshVITH,t[tCSTRBHI]+
                            t[tdSHRHr]+t[loosdelay]-t[tgb]-ctcf+7ns,0);

        EdgeSetDelayData    (CDdriveWF,Edge1,ChanFirst,
                            DriveComplement,ThreshVITL,t[tCSTRBLO]-
                            t[tsuCDr]-t[loossetup]+dtcf-7ns,0,
                            DriveComplement,ThreshVITH,t[tCSTRBLO]-
                            t[tsuCDr]-t[looscd]-t[loossetup]+dtcf-7ns,0);
        EdgeSetDelayData    (CDdriveWF,Edge2,ChanFirst,
                            DriveData,ThreshVITL,t[tCSTRBLO]-
                            t[tsuCDr]-t[loossetup]+dtcf,0,
                            DriveData,ThreshVITH,t[tCSTRBLO]-
                            t[tsuCDr]-t[looscd]-t[loossetup]+dtcf,0);
        EdgeSetDelayData    (CDdriveWF,Edge3,ChanFirst,
                            DriveComplement,ThreshVITL,t[tref]+t[tCRDYflo]+
                            t[thCDr]+t[looscd]+t[looshold]-dtcf,0,
                            DriveComplement,ThreshVITH,t[tref]+t[tCRDYflo]+
                            t[thCDr]+t[looshold]-dtcf,0);


        WaveSetSBC          (TCLKdriveWF,
                            t[tref]+t[tH1flo]-t[tsuTCLK]-t[loossetup]+dtcf-7ns,
                            t[tref]+t[tH1flo]-t[tsuTCLK]-t[loossetup]+dtcf,
                            t[tref]+t[tH1flo]+t[thTCLK]+t[looshold]-dtcf);
        EdgeSetOrigin       (TCLKdriveWF, Edge1, orgtH1flo);
        EdgeSetOrigin       (TCLKdriveWF, Edge2, orgtH1flo);
        EdgeSetOrigin       (TCLKdriveWF, Edge3, orgtH1flo);

        WaveSetEdgeStrobe   (TCLKstrobeWF,
                            t[tref]+t[tdTCLK]+t[loosdelay4]-t[tgb]-ctcf-7ns,
                            t[tref]+t[tdTCLK]+t[loosdelay4]-t[tgb]-ctcf,
                            t[tref]+t[tdTCLK]+t[loosdelay4]-t[tgb]-ctcf+7ns);


        WaveSetRTO          (TCKCLKdriveWF,
                            t[tref],
                            t[tref]+t[tcCI]);

        WaveSetNR           (TCKdriveWF,
                            t[tref]);

        WaveSetSBC          (TDITMSdriveWF,
                            t[tref]+t[tcCI]-t[tsuTDITMS]-t[loossetup]+dtcf-7ns,
                            t[tref]+t[tcCI]-t[tsuTDITMS]-t[loossetup]+dtcf,
                            t[tref]+t[tcCI]+t[thTDITMS]+t[looshold]-dtcf);

        WaveSetNR           (JTAGdriveWF,
                            t[tref]+t[tJTAG]);

        WaveSetEdgeStrobe   (TDOstrobeWF,
                            0ns,
                            t[tref]+t[tdTDO]+t[loosdelay]-t[tgb]-ctcf,
                            t[tref]+t[tdTDO]+t[loosdelay]-t[tgb]-ctcf+7ns);

        WaveSetEdgeStrobe   (JTAGH1strobeWF,
                            0ns,
                            t[tref]+t[tdTDO]+t[loosdelay]-t[tgb]-ctcf,
                            t[tref]+t[tdTDO]+t[loosdelay]-t[tgb]-ctcf+7ns);

        WaveSetEdgeStrobe   (JTAGVARYstrobeWF,
                            0ns,
                            t[tref]+t[tdTDO]+t[tcCI]+t[loosdelay]-t[tgb]-ctcf,
                            t[tref]+t[tdTDO]+t[tcCI]+t[loosdelay]-t[tgb]-ctcf+7ns);

        WaveSetEdgeStrobe   (JTAGABUSstrobeWF,
                            0ns,
                            t[tref]+t[tdTDO]+t[tcCI]+t[loosdelay]-t[tgb]-ctcf,
                            t[tref]+t[tdTDO]+t[tcCI]+t[loosdelay]-t[tgb]-ctcf+7ns);


        WaveSetNR           (EMUdriveWF,
                            t[tref]+t[tEMU]);

        WaveSetEdgeStrobe   (EMUstrobeWF,
                            0ns,
                            t[tref]+t[tdEMU]+t[loosdelay]-t[tgb]-ctcf,
                            t[tref]+t[tdEMU]+t[loosdelay]-t[tgb]-ctcf+7ns);


        WaveSetNR           (RESETLOCdriveWF,
                            t[tref]+t[tRESETLOC]);

        WaveSetNR           (ROMENdriveWF,
                            t[tref]+t[tROMEN]);

        WaveSetNR           (NMIdriveWF,
                            t[tref]+t[tNMI]);


        WaveSetContinue     (ContinueWF);

        WaveSetOff          (ALLoffWF,t[tref],t[tref]);

STOP(ALLENUMS,TIspecholdmin33ACTable,TIspecholdmax33ACTable);

          end; (*9th case*)



      end; (*case*)


STOP(ALLENUMS,ALLTABLES);












        ACTableClose;

      end; (*with*)

  end; (* TIACTableSet *)


	(***********************************************************)
	(***               ACTableSet                            ***)
	(***********************************************************)
	(***                                                     ***)
	(*** This is the beginning of the ACTableSet procedure.  ***)
	(***                                                     ***)
	(***********************************************************)

begin (*ACTableSet*)

    (*                                                         *)
    (*        Set up WaveForms for TIparametricACTable         *)
    (*                                                         *)

 if (actable in [TIallACTable, TIparametricACTable]) then
  begin
   TIACTableSet( TIparametricACTable );
  end;(*if*)

    (*                                                         *)
    (*        Set up WaveForms for TIcrystalACTable            *)
    (*                                                         *)

 if (actable in [TIallACTable, TIcrystalACTable]) then
  begin
   TIACTableSet( TIcrystalACTable );
  end;(*if*)

    (*                                                         *)
    (*        Set up WaveForms for TInomlooseACTable           *)
    (*                                                         *)

 if (actable in [TIallACTable, TInomlooseACTable]) then
  begin
   TIACTableSet( TInomlooseACTable );
  end;(*if*)

    (*                                                         *)
    (*        Set up WaveForms for TIstressminACTable          *)
    (*                                                         *)

 if (actable in [TIallACTable, TIstressminACTable]) then
  begin
   TIACTableSet( TIstressminACTable );
  end;(*if*)

    (*                                                         *)
    (*        Set up WaveForms for TIstressmaxACTable          *)
    (*                                                         *)

 if (actable in [TIallACTable, TIstressmaxACTable]) then
  begin
   TIACTableSet( TIstressmaxACTable );
  end;(*if*)

    (*                                                         *)
    (*        Set up WaveForms for TIlofrqminACTable           *)
    (*                                                         *)

 if (actable in [TIallACTable, TIlofrqminACTable]) then
  begin
   TIACTableSet( TIlofrqminACTable );
  end;(*if*)

    (*                                                         *)
    (*        Set up WaveForms for TIlofrqmaxACTable           *)
    (*                                                         *)

 if (actable in [TIallACTable, TIlofrqmaxACTable]) then
  begin
   TIACTableSet( TIlofrqmaxACTable );
  end;(*if*)

    (*                                                         *)
    (*        Set up WaveForms for TIlofrqlooseACTable         *)
    (*                                                         *)

 if (actable in [TIallACTable, TIlofrqlooseACTable]) then
  begin
   TIACTableSet( TIlofrqlooseACTable );
  end;(*if*)

    (*                                                         *)
    (*        Set up WaveForms for TIlofrqedgeACTable          *)
    (*                                                         *)

 if (actable in [TIallACTable, TIlofrqedgeACTable]) then
  begin
   TIACTableSet( TIlofrqedgeACTable );
  end;(*if*)

    (*                                                         *)
    (*        Set up WaveForms for TIlofrqmin60ACTable         *)
    (*                                                         *)

 if (actable in [TIallACTable, TIlofrqmin60ACTable]) then
  begin
   TIACTableSet( TIlofrqmin60ACTable );
  end;(*if*)

    (*                                                         *)
    (*        Set up WaveForms for TIlofrqmax60ACTable         *)
    (*                                                         *)

 if (actable in [TIallACTable, TIlofrqmax60ACTable]) then
  begin
   TIACTableSet( TIlofrqmax60ACTable );
  end;(*if*)

    (*                                                         *)
    (*        Set up WaveForms for TIlofrqloose60ACTable       *)
    (*                                                         *)

 if (actable in [TIallACTable, TIlofrqloose60ACTable]) then
  begin
   TIACTableSet( TIlofrqloose60ACTable );
  end;(*if*)

    (*                                                         *)
    (*        Set up WaveForms for TIlofrqedge60ACTable        *)
    (*                                                         *)

 if (actable in [TIallACTable, TIlofrqedge60ACTable]) then
  begin
   TIACTableSet( TIlofrqedge60ACTable );
  end;(*if*)

    (*                                                            *)
    (*        Set up WaveForms for TIspecsetupmin25ACTable        *)
    (*                                                            *)

 if (actable in [TIallACTable, TIspecsetupmin25ACTable]) then
  begin
   TIACTableSet( TIspecsetupmin25ACTable );
  end;(*if*)

    (*                                                            *)
    (*        Set up WaveForms for TIspecsetupmax25ACTable        *)
    (*                                                            *)

 if (actable in [TIallACTable, TIspecsetupmax25ACTable]) then
  begin
   TIACTableSet( TIspecsetupmax25ACTable );
  end;(*if*)

    (*                                                            *)
    (*        Set up WaveForms for TIspecholdmin25ACTable         *)
    (*                                                            *)

 if (actable in [TIallACTable, TIspecholdmin25ACTable]) then
  begin
   TIACTableSet( TIspecholdmin25ACTable );
  end;(*if*)

    (*                                                            *)
    (*        Set up WaveForms for TIspecholdmax25ACTable         *)
    (*                                                            *)

 if (actable in [TIallACTable, TIspecholdmax25ACTable]) then
  begin
   TIACTableSet( TIspecholdmax25ACTable );
  end;(*if*)


    (*                                                         *)
    (*        Set up WaveForms for TIsearch33ACTable           *)
    (*                                                         *)

 if (actable in [TIsearch33ACTable]) then
  begin
   TIACTableSet( TIsearch33ACTable );
  end;(*if*)


    (*                                                         *)
    (*        Set up WaveForms for TIsearchlevels33ACTable     *)
    (*                                                         *)

 if (actable in [TIsearchlevels33ACTable]) then
  begin
   TIACTableSet( TIsearchlevels33ACTable );
  end;(*if*)


    (*                                                            *)
    (*        Set up WaveForms for TIspecsetupmin33ACTable        *)
    (*                                                            *)

 if (actable in [TIallACTable, TIspecsetupmin33ACTable]) then
  begin
   TIACTableSet( TIspecsetupmin33ACTable );
  end;(*if*)

    (*                                                            *)
    (*        Set up WaveForms for TIspecsetupmax33ACTable        *)
    (*                                                            *)

 if (actable in [TIallACTable, TIspecsetupmax33ACTable]) then
  begin
   TIACTableSet( TIspecsetupmax33ACTable );
  end;(*if*)

    (*                                                            *)
    (*        Set up WaveForms for TIspecholdmin33ACTable         *)
    (*                                                            *)

 if (actable in [TIallACTable, TIspecholdmin33ACTable]) then
  begin
   TIACTableSet( TIspecholdmin33ACTable );
  end;(*if*)

    (*                                                            *)
    (*        Set up WaveForms for TIspecholdmax33ACTable         *)
    (*                                                            *)

 if (actable in [TIallACTable, TIspecholdmax33ACTable]) then
  begin
   TIACTableSet( TIspecholdmax33ACTable );
  end;(*if*)
    (*                                                         *)
    (*        Set up WaveForms for TIhifrqmin33ACTable         *)
    (*                                                         *)

 if (actable in [TIallACTable, TIhifrqmin33ACTable]) then
  begin
   TIACTableSet( TIhifrqmin33ACTable );
  end;(*if*)

    (*                                                         *)
    (*        Set up WaveForms for TIhifrqmax33ACTable         *)
    (*                                                         *)

 if (actable in [TIallACTable, TIhifrqmax33ACTable]) then
  begin
   TIACTableSet( TIhifrqmax33ACTable );
  end;(*if*)


    (*                                                         *)
    (*        Set up WaveForms for TIhifrqmin40ACTable         *)
    (*                                                         *)

 if (actable in [TIallACTable, TIhifrqmin40ACTable]) then
  begin
   TIACTableSet( TIhifrqmin40ACTable );
  end;(*if*)

    (*                                                         *)
    (*        Set up WaveForms for TIhifrqmax40ACTable         *)
    (*                                                         *)

 if (actable in [TIallACTable, TIhifrqmax40ACTable]) then
  begin
   TIACTableSet( TIhifrqmax40ACTable );
  end;(*if*)

    (*                                                         *)
    (*        Set up WaveForms for TIhifrqloose40ACTable       *)
    (*                                                         *)

 if (actable in [TIallACTable, TIhifrqloose40ACTable]) then
  begin
   TIACTableSet( TIhifrqloose40ACTable );
  end;(*if*)

    (*                                                         *)
    (*        Set up WaveForms for TIhifrqedge40ACTable        *)
    (*                                                         *)

 if (actable in [TIallACTable, TIhifrqedge40ACTable]) then
  begin
   TIACTableSet( TIhifrqedge40ACTable );
  end;(*if*)

    (*                                                         *)
    (*        Set up WaveForms for TIhifrqmin50ACTable         *)
    (*                                                         *)

 if (actable in [TIallACTable, TIhifrqmin50ACTable]) then
  begin
   TIACTableSet( TIhifrqmin50ACTable );
  end;(*if*)

    (*                                                         *)
    (*        Set up WaveForms for TIhifrqmax50ACTable         *)
    (*                                                         *)

 if (actable in [TIallACTable, TIhifrqmax50ACTable]) then
  begin
   TIACTableSet( TIhifrqmax50ACTable );
  end;(*if*)

    (*                                                         *)
    (*        Set up WaveForms for TIhifrqloose50ACTable       *)
    (*                                                         *)

 if (actable in [TIallACTable, TIhifrqloose50ACTable]) then
  begin
   TIACTableSet( TIhifrqloose50ACTable );
  end;(*if*)

    (*                                                         *)
    (*        Set up WaveForms for TIhifrqedge50ACTable        *)
    (*                                                         *)

 if (actable in [TIallACTable, TIhifrqedge50ACTable]) then
  begin
   TIACTableSet( TIhifrqedge50ACTable );
  end;(*if*)

    (*                                                         *)
    (*        Set up WaveForms for TIhifrqmin60ACTable         *)
    (*                                                         *)

 if (actable in [TIallACTable, TIhifrqmin60ACTable]) then
  begin
   TIACTableSet( TIhifrqmin60ACTable );
  end;(*if*)

    (*                                                         *)
    (*        Set up WaveForms for TIhifrqmax60ACTable         *)
    (*                                                         *)

 if (actable in [TIallACTable, TIhifrqmax60ACTable]) then
  begin
   TIACTableSet( TIhifrqmax60ACTable );
  end;(*if*)

    (*                                                         *)
    (*        Set up WaveForms for TIhifrqloose60ACTable       *)
    (*                                                         *)

 if (actable in [TIallACTable, TIhifrqloose60ACTable]) then
  begin
   TIACTableSet( TIhifrqloose60ACTable );
  end;(*if*)

    (*                                                         *)
    (*        Set up WaveForms for TIhifrqedge60ACTable        *)
    (*                                                         *)

 if (actable in [TIallACTable, TIhifrqedge60ACTable]) then
  begin
   TIACTableSet( TIhifrqedge60ACTable );
  end;(*if*)

    (*                                                         *)
    (*        Set up WaveForms for TIsearchACTable             *)
    (*                                                         *)

 if (actable in [TIsearchACTable]) then
  begin
   TIACTableSet( TIsearchACTable );
  end;(*if*)

    (*                                                         *)
    (*        Set up WaveForms for TIsearch40ACTable           *)
    (*                                                         *)

 if (actable in [TIsearch40ACTable]) then
  begin
   TIACTableSet( TIsearch40ACTable );
  end;(*if*)

    (*                                                         *)
    (*        Set up WaveForms for TIsearchlevelsACTable       *)
    (*                                                         *)

 if (actable in [TIsearchlevelsACTable]) then
  begin
   TIACTableSet( TIsearchlevelsACTable );
  end;(*if*)

    (*                                                         *)
    (*        Set up WaveForms for TIsearchlevels40ACTable     *)
    (*                                                         *)

 if (actable in [TIsearchlevels40ACTable]) then
  begin
   TIACTableSet( TIsearchlevels40ACTable );
  end;(*if*)

    (*                                                         *)
    (*        Set up WaveForms for TIcharACTable               *)
    (*                                                         *)

 if (actable in [TIcharACTable]) then
  begin
   TIACTableSet( TIcharACTable );
  end;(*if*)

    (*                                                           *)
    (*        Set up WaveForms for TIchar25ACTable               *)
    (*                                                           *)

 if (actable in [TIchar25ACTable]) then
  begin
   TIACTableSet( TIchar25ACTable );
  end;(*if*)

    (*                                                           *)
    (*        Set up WaveForms for TIchar33ACTable               *)
    (*                                                           *)

 if (actable in [TIchar33ACTable]) then
  begin
   TIACTableSet( TIchar33ACTable );
  end;(*if*)

    (*                                                         *)
    (*        Set up WaveForms for TIchar40ACTable             *)
    (*                                                         *)

 if (actable in [TIchar40ACTable]) then
  begin
   TIACTableSet( TIchar40ACTable );
  end;(*if*)

end; (*ACTableSet*)

