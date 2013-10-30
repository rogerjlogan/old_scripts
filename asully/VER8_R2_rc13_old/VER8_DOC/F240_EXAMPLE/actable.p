(***********************************************************************)
(***                                                                 ***)
(***                     320X240 TEST PROGRAM                        ***)
(***                     --------------------                        ***)
(***                                                                 ***)
(***                    File Name:  actable.p                        ***)
(***                                                                 ***)
(***                                                                 ***)
(***   Revision History:                                             ***)
(***    A0   RS     01/01/97    First cut @ TMX320F240 PG1.0         ***)
(***    A1   DDD    04/01/97    First cut @ TMX320F240 PG1.1         ***)
(***    B0   RS     07/01/97    First cut @ TMX320F240 PG2.0 (probe) ***)
(***    B2   RS     10/01/97    First cut @ TMX320F240 PG2.0 (QA)    ***)
(***    B3   DDD    11/01/97    First cut @ TMP320F240 PG2.0         ***)
(***    C0   RS     03/25/98    First cut @ TMP320F240 PG3.1         ***)
(***	C2   RS	    05/15/98	First cut @ TMS320F240 PG3.2	     ***)
(***	C3   RS	    06/01/98	First cut @ TMX320C240 PG1.0	     ***)
(***				Added C240 code to F240 C2 Program   ***)
(***	C4   RS	    07/01/98	First cut @ TMX320C240 PG1.1	     ***)
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

procedure ACTableSet; (* actable : ACTable *)

        (***********************************************************)
        (***        Internal Procedure TIACTableSet              ***)
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
        dtcf:=	TIdtcf	;  (* Drive timing correction factor from mega1spec   *)
        ctcf:=	TIctcf	;  (* Compare timing correction factor from mega1spec *)
        tgdb:=	500ps	;  (* FT vs QA timing guard band against tester miscorrelation *)
      end;
    Final,FT2,FT3,Q100_FT1,
    Q100_FT2,Q100_FT3,Engineering:
      begin
        dtcf:=	TIdtcf	;  (* Drive timing correction factor from mega1spec   *)
        ctcf:=	TIctcf	;  (* Compare timing correction factor from mega1spec *)
        tgdb:=	500ps	;  (* FT vs QA timing guard band against tester miscorrelation *)
      end;
    QA:
      begin
        dtcf:=	TIdtcf	;  (* Drive timing correction factor from mega1spec   *)
        ctcf:=	TIctcf	;  (* Compare timing correction factor from mega1spec *)
        tgdb:=	  0ps	;  (* FT vs QA timing guard band against tester miscorrelation *)
      end;
    others:
      begin
        dtcf:=	TIdtcf	;  (* Drive timing correction factor from mega1spec   *)
        ctcf:=	TIctcf	;  (* Compare timing correction factor from mega1spec *)
        tgdb:=	500ps	;  (* FT vs QA timing guard band against tester miscorrelation *)
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
        (*** parametric testing. The requirements of doing SHMOO ***)
        (*** and SEARCH routines requires that the same AC Table ***)
        (*** set-up be used for all test frequencies. One new AC ***)
        (*** Table will be created each time the ACTableSet is   ***)
        (*** called with a new actable parameter (Table Name).   ***)
        (*** The user is required to call the ACTableSet         ***)
        (*** procedure once for each unique timing set (different***)
        (*** periods, and different parameters, ie. loose timing)***)
        (***                                                     ***)
        (***********************************************************)

 with ACDataSheets[ actable ] do
  begin

   ACTableOpen( actable );

  (*    Initialize all Origins to default values for TIallACTable only      *)

   OriginSet(orgclkin,0ns);
   OriginSet(orgclkoutll,0ns);
   OriginSet(orgclkoutlh,0ns);
   OriginSet(orgwenll,0ns);
   OriginSet(orgabusron,0ns);
   OriginSet(orgabusroff,0ns);
   OriginSet(orgabuswon,0ns);
   OriginSet(orgabuswoff,0ns);
   OriginSet(orgdbusdon,0ns);
   OriginSet(orgdbusdoff,0ns);
   OriginSet(orgdbusson,0ns);
   OriginSet(orgdbussoff,0ns);
   OriginSet(orgreadyon,0ns);
   OriginSet(orgreadyoff,0ns);

  (*    Allow 8ns between a StrobeOff and a Strobe edge *)
  (*          4ns between a Strobe and a StrobeOff edge *)
  (*    on following pins                               *)

   PinStrobeModeSet(ALLIOS,PinStrobeFast);
   PinStrobeModeSet(ALLOUTS,PinStrobeFast);

  (*                                                                        *)
  (*             Timing and Waveform set-up for all frequencies             *)
  (*                                                                        *)

        PeriodSetAll       (t[tper]);                   

        (* Data in vpl generally is 01 for CLKIN *)

        EdgeSetDelayData   (CLKINdriveWF,Edge1,ChanFirst,       
                                DriveData,ThreshVITL,           
                                t[tref]+t[tH],0,
                                DriveData,ThreshVITH,
                                t[tref]+t[tH],0);
        EdgeSetDelayData   (CLKINdriveWF,Edge2,ChanSecond,      
                                DriveData,ThreshVITL,           
                                t[tref]+t[tper],0,
                                DriveData,ThreshVITH,
                                t[tref]+t[tper],0);
        EdgeSetOrigin      (CLKINdriveWF,Edge1,orgclkin);
        EdgeSetOrigin      (CLKINdriveWF,Edge2,orgclkin);

        WaveSetDoubleClk   (CLKINdrive2WF,
                                t[tref]+t[tper]-t[tH],                  (* DriveData *)
                                t[tref]+t[tper]-t[twCIL],               (* DriveLow  *)
                                t[tref]+t[tper],                        (* DriveData *)
                                t[tref]+t[tper]+t[tH]-t[twCIL]);        (* DriveLow  *)
        EdgeSetOrigin      (CLKINdrive2WF,Edge1,orgclkin);
        EdgeSetOrigin      (CLKINdrive2WF,Edge2,orgclkin);
        EdgeSetOrigin      (CLKINdrive2WF,Edge3,orgclkin);
        EdgeSetOrigin      (CLKINdrive2WF,Edge4,orgclkin);

        WaveSetClk         (CLKINscan_drvWF,
                                t[tref]+t[tH],
                                t[tref]+t[tper]);
        EdgeSetOrigin      (CLKINscan_drvWF,Edge1,org_scan_clkin);
        EdgeSetOrigin      (CLKINscan_drvWF,Edge2,org_scan_clkin);

                (* waveform for driving clkin during PLL test *)

        EdgeSetDelayData   (PLLdriveWF,Edge1,ChanFirst, 
                                DriveLow,ThreshVITL,            
                                t[tref]+t[tH],0,
                                DriveHigh,ThreshVITL,
                                t[tref]+t[tH],0);
        EdgeSetDelayData   (PLLdriveWF,Edge2,ChanSecond,        
                                DriveLow,ThreshVITL,            
                                t[tref]+t[tper],0,
                                DriveHigh,ThreshVITL,
                                t[tref]+t[tper],0);
        EdgeSetOrigin      (PLLdriveWF,Edge1,orgpll);
        EdgeSetOrigin      (PLLdriveWF,Edge2,orgpll);

                (* waveform for strobeing PLL O/P in PMT test mode *)

{       EdgeSetDelay       (PLL_CAP1strobeWF,Edge1,DriveOff,t[tref],0);}
        EdgeSetDelayData   (PLL_CAP1strobeWF,Edge1,ChanFirst,
                                StrobeLow,ThreshVITL,           
                                t[tref]+t[tper]-4ns,0,
                                StrobeHigh,ThreshVITL,
                                t[tref]+t[tH]-4ns,0);
        EdgeSetDelayData   (PLL_CAP1strobeWF,Edge2,ChanFirst,
                                StrobeOffLow,ThreshVITL,                
                                t[tref]+t[tper],0,
                                StrobeOffHigh,ThreshVITL,
                                t[tref]+t[tH],0);

                (* waveform for strobing CLKOUT1 during PLL test *)

        EdgeSet            (PLL_CLKOUT1strobeWF,Edge1,StrobeLow,
                                t[tref]);
        EdgeSet            (PLL_CLKOUT1strobeWF,Edge2,StrobeOffLow,
                                t[tref]+t[tH]-t[tloosjitter]);
        EdgeSet            (PLL_CLKOUT1strobeWF,Edge3,StrobeHigh,
                                t[tref]+t[tH]);
        EdgeSet            (PLL_CLKOUT1strobeWF,Edge4,StrobeOffHigh,     
                                t[tref]+t[tper]-t[tloosjitter]);

(*  THESE WAVEFORMS are for ADCINS, ADCIOS, ADCSOC, LVDOVRD, OSCBYPN, PMTMODE, VREFHI (not characterized) *)

        WaveSetNR          (F240driveWF,t[tref]+t[tH]);
        EdgeSetOrigin      (F240driveWF,Edge1,orgclkoutlh);

        WaveSetStrobe      (F240strobeWF,
                                t[tref]+t[tH],
                                t[tref]+t[tH]+10ns,
                                t[tref]+t[tH]+t[tper]-10ns);
        EdgeSetOrigin      (F240strobeWF,Edge1,orgclkoutlh);
        EdgeSetOrigin      (F240strobeWF,Edge2,orgclkoutlh);
        EdgeSetOrigin      (F240strobeWF,Edge3,orgclkoutlh);

        EdgeSetDelayData   (LVDdriveWF,Edge1,ChanFirst,                 
                                DriveLow,ThreshVITL,                    
                                t[tref],0,
                                DriveHigh,ThreshVITL,
                                t[tref]+t[tper]-t[tH],0);
        EdgeSetOrigin      (LVDdriveWF,Edge1,orgclkoutll);

        WaveSetNR          (LVDdriveLWF,t[tref]);
        EdgeSetOrigin      (LVDdriveLWF,Edge1,orgclkoutll);

        WaveSetNR          (LVDdriveHWF,t[tref]+t[tper]-t[tH]);
        EdgeSetOrigin      (LVDdriveHWF,Edge1,orgclkoutll);

                        (* CLKOUT waveform for sync-up *)

        EdgeSetDelay       (CLKOUT1strobe2WF,Edge1,DriveOff,t[tref],0);
        EdgeSetDelayData   (CLKOUT1strobe2WF,Edge2,ChanSecond,
                                StrobeLow,ThreshVITL,           
                                t[tref]+t[tper]-4ns,0,
                                StrobeHigh,ThreshVITL,
                                t[tref]+t[tper]-4ns,0);
        EdgeSetDelayData   (CLKOUT1strobe2WF,Edge3,ChanSecond,
                                StrobeOffLow,ThreshVITL,                
                                t[tref]+t[tper],0,
                                StrobeOffHigh,ThreshVITL,
                                t[tref]+t[tper],0);
        EdgeSetOrigin      (CLKOUT1strobe2WF,Edge1,orgclkoutll);
        EdgeSetOrigin      (CLKOUT1strobe2WF,Edge2,orgclkoutll);
        EdgeSetOrigin      (CLKOUT1strobe2WF,Edge3,orgclkoutll);

        EdgeSet            (CLKOUT1_scan_strbWF,Edge1,StrobeHigh,
                                t[tref]+(t[tH] div 2)+13ns);
        EdgeSet            (CLKOUT1_scan_strbWF,Edge2,StrobeOff,
                                t[tref]+(t[tH] div 2)+16ns);
        EdgeSet            (CLKOUT1_scan_strbWF,Edge3,StrobeData,
                                t[tref]+t[tH]+(t[tH] div 2)+15ns);
        EdgeSet            (CLKOUT1_scan_strbWF,Edge4,StrobeOff,        
                                t[tref]+t[tH]+(t[tH] div 2)+18ns);
        EdgeSetOrigin      (CLKOUT1_scan_strbWF,Edge1,orgclkoutll);
        EdgeSetOrigin      (CLKOUT1_scan_strbWF,Edge2,orgclkoutll);
        EdgeSetOrigin      (CLKOUT1_scan_strbWF,Edge3,orgclkoutll);
        EdgeSetOrigin      (CLKOUT1_scan_strbWF,Edge4,orgclkoutll);

        WaveSetStrobe      (xRDNFstrobe2WF,               (* used by sync in HACK gct *)
                                t[tref]+t[tH],
                                t[tref]+t[tH]+t[tper]-4ns,
                                t[tref]+t[tH]+t[tper]+8ns);

  case actable of
  TIlofrqACTable,
  TIlofrqpllACTable,
  TIhifrqACTable,         
  TIveryhifrqACTable,         
  TIsearchACTable:
    begin
        WaveSetNR          (ABUSdriveWF,t[tref]+t[tH]);
        EdgeSetOrigin      (ABUSdriveWF,Edge1,orgclkoutll);

        WaveSetStrobe      (ABUSRDstrobeWF,
                                t[tref]+t[tH],
                                t[tref]+t[tH]+15ns,
                                t[tref]+t[tper]-5ns);
        EdgeSetOrigin      (ABUSRDstrobeWF,Edge1,orgclkoutef);
        EdgeSetOrigin      (ABUSRDstrobeWF,Edge2,orgclkoutef);
        EdgeSetOrigin      (ABUSRDstrobeWF,Edge3,orgclkoutef);

        WaveSetStrobe      (xABUSRDstrobeWF,
                                t[tref],
                                t[tref]+t[tdABUSRD]-ctcf-tgdb,
                                t[tref]+t[tper]+t[thzABUSRD]+ctcf+tgdb);
        EdgeSetOrigin      (xABUSRDstrobeWF,Edge1,orgclkoutef);
        EdgeSetOrigin      (xABUSRDstrobeWF,Edge2,orgclkoutef);
        EdgeSetOrigin      (xABUSRDstrobeWF,Edge3,orgclkoutef);

        WaveSetStrobe      (ABUSWRstrobeWF,
                                t[tref]+t[tH],
                                t[tref]+t[tH]+15ns,
                                t[tref]+t[tper]-5ns);
        EdgeSetOrigin      (ABUSWRstrobeWF,Edge1,orgclkouter);
        EdgeSetOrigin      (ABUSWRstrobeWF,Edge2,orgclkouter);
        EdgeSetOrigin      (ABUSWRstrobeWF,Edge3,orgclkouter);

        WaveSetStrobe      (xABUSWRstrobeWF,
                                t[tref]+t[tH],
                                t[tref]+t[tH]+t[tdABUSWR]-ctcf-tgdb,
                                t[tref]+t[tH]+t[tper]+t[thzABUSWR]+ctcf+tgdb);
        EdgeSetOrigin      (xABUSWRstrobeWF,Edge1,orgclkouter);
        EdgeSetOrigin      (xABUSWRstrobeWF,Edge2,orgclkouter);
        EdgeSetOrigin      (xABUSWRstrobeWF,Edge3,orgclkouter);

        WaveSetStrobe      (ACTRLstrobeWF,
                                t[tref]+t[tH],
                                t[tref]+t[tH]+10ns,
                                t[tref]+t[tper]-10ns);
        EdgeSetOrigin      (ACTRLstrobeWF,Edge1,orgclkouter);
        EdgeSetOrigin      (ACTRLstrobeWF,Edge2,orgclkouter);
        EdgeSetOrigin      (ACTRLstrobeWF,Edge3,orgclkouter);

        WaveSetStrobe      (xACTRLFRDstrobeWF,
                                t[tref]+t[tH],
                                t[tref]+t[tH]+10ns,
                                t[tref]+t[tper]-10ns);
        EdgeSetOrigin      (xACTRLFRDstrobeWF,Edge1,orgclkoutef);
        EdgeSetOrigin      (xACTRLFRDstrobeWF,Edge2,orgclkoutef);
        EdgeSetOrigin      (xACTRLFRDstrobeWF,Edge3,orgclkoutef);

        WaveSetStrobe      (xACTRLLRDstrobeWF,
                                t[tref],
                                t[tref]+t[tdACTRLLRD]-ctcf-tgdb,
                                t[tref]+t[tper]+t[thzACTRLLRD]+ctcf+tgdb);
        EdgeSetOrigin      (xACTRLLRDstrobeWF,Edge1,orgclkoutef);
        EdgeSetOrigin      (xACTRLLRDstrobeWF,Edge2,orgclkoutef);
        EdgeSetOrigin      (xACTRLLRDstrobeWF,Edge3,orgclkoutef);

        WaveSetStrobe      (xACTRLRRDstrobeWF,
                                t[tref],
                                t[tref]+t[tdACTRLHRD]-ctcf-tgdb,
                                t[tref]+t[tper]+t[thzACTRLHRD]+ctcf+tgdb);
        EdgeSetOrigin      (xACTRLRRDstrobeWF,Edge1,orgclkoutef);
        EdgeSetOrigin      (xACTRLRRDstrobeWF,Edge2,orgclkoutef);
        EdgeSetOrigin      (xACTRLRRDstrobeWF,Edge3,orgclkoutef);

        WaveSetStrobe      (xACTRLFWRstrobeWF,
                                t[tref]+t[tH],
                                t[tref]+t[tH]+10ns,
                                t[tref]+t[tH]+t[tper]-10ns);
        EdgeSetOrigin      (xACTRLFWRstrobeWF,Edge1,orgclkouter);
        EdgeSetOrigin      (xACTRLFWRstrobeWF,Edge2,orgclkouter);
        EdgeSetOrigin      (xACTRLFWRstrobeWF,Edge3,orgclkouter);

        WaveSetStrobe      (xACTRLLWRstrobeWF,
                                t[tref]+t[tH],
                                t[tref]+t[tH]+t[tdACTRLLWR]-ctcf-tgdb,
                                t[tref]+t[tH]+t[tper]+t[thzACTRLLWR]+ctcf+tgdb);
        EdgeSetOrigin      (xACTRLLWRstrobeWF,Edge1,orgclkouter);
        EdgeSetOrigin      (xACTRLLWRstrobeWF,Edge2,orgclkouter);
        EdgeSetOrigin      (xACTRLLWRstrobeWF,Edge3,orgclkouter);

        WaveSetStrobe      (xACTRLRWRstrobeWF,
                                t[tref]+t[tH],
                                t[tref]+t[tH]+t[tdACTRLHWR]-ctcf-tgdb,
                                t[tref]+t[tH]+t[tper]+t[thzACTRLHWR]+ctcf+tgdb);
        EdgeSetOrigin      (xACTRLRWRstrobeWF,Edge1,orgclkouter);
        EdgeSetOrigin      (xACTRLRWRstrobeWF,Edge2,orgclkouter);
        EdgeSetOrigin      (xACTRLRWRstrobeWF,Edge3,orgclkouter);

        EdgeSet            (BIONdriveWF,Edge1,DriveData,
                                t[tref]+t[tper]-t[tsuBION]+dtcf+tgdb);
        EdgeSet            (BIONdriveWF,Edge2,DriveHigh,
                                t[tref]+t[tper]+t[thdBION]-dtcf-tgdb);
        EdgeSetOrigin      (BIONdriveWF,Edge1,orgclkoutll);
        EdgeSetOrigin      (BIONdriveWF,Edge2,orgclkoutel);

        WaveSetStrobe      (BRNstrobeWF,
                                t[tref],
                                t[tref]+t[tH]+10ns,
                                t[tref]+t[tper]-10ns);
        EdgeSetOrigin      (BRNstrobeWF,Edge1,orgclkouter);
        EdgeSetOrigin      (BRNstrobeWF,Edge2,orgclkouter);
        EdgeSetOrigin      (BRNstrobeWF,Edge3,orgclkouter);

        WaveSetStrobe      (xBRNFRDstrobeWF,
                                t[tref],
                                t[tref]+t[tH]+10ns,
                                t[tref]+t[tper]-10ns);
        EdgeSetOrigin      (xBRNFRDstrobeWF,Edge1,orgclkoutef);
        EdgeSetOrigin      (xBRNFRDstrobeWF,Edge2,orgclkoutef);
        EdgeSetOrigin      (xBRNFRDstrobeWF,Edge3,orgclkoutef);

        WaveSetStrobe      (xBRNLRDstrobeWF,
                                t[tref],
                                t[tref]+t[tdBRNLRD]-ctcf-tgdb,
                                t[tref]+t[tper]+t[thzBRNLRD]+ctcf+tgdb);
        EdgeSetOrigin      (xBRNLRDstrobeWF,Edge1,orgclkoutef);
        EdgeSetOrigin      (xBRNLRDstrobeWF,Edge2,orgclkoutef);
        EdgeSetOrigin      (xBRNLRDstrobeWF,Edge3,orgclkoutef);

        WaveSetStrobe      (xBRNRRDstrobeWF,
                                t[tref],
                                t[tref]+t[tdBRNHRD]-ctcf-tgdb,
                                t[tref]+t[tper]+t[thzBRNHRD]+ctcf+tgdb);
        EdgeSetOrigin      (xBRNRRDstrobeWF,Edge1,orgclkoutef);
        EdgeSetOrigin      (xBRNRRDstrobeWF,Edge2,orgclkoutef);
        EdgeSetOrigin      (xBRNRRDstrobeWF,Edge3,orgclkoutef);

        WaveSetStrobe      (xBRNFWRstrobeWF,
                                t[tref]+t[tH],
                                t[tref]+t[tH]+10ns,
                                t[tref]+t[tH]+t[tper]-10ns);
        EdgeSetOrigin      (xBRNFWRstrobeWF,Edge1,orgclkouter);
        EdgeSetOrigin      (xBRNFWRstrobeWF,Edge2,orgclkouter);
        EdgeSetOrigin      (xBRNFWRstrobeWF,Edge3,orgclkouter);

        WaveSetStrobe      (xBRNLWRstrobeWF,
                                t[tref]+t[tH],
                                t[tref]+t[tH]+t[tdBRNLWR]-ctcf-tgdb,
                                t[tref]+t[tH]+t[tper]+t[thzBRNLWR]+ctcf+tgdb);
        EdgeSetOrigin      (xBRNLWRstrobeWF,Edge1,orgclkouter);
        EdgeSetOrigin      (xBRNLWRstrobeWF,Edge2,orgclkouter);
        EdgeSetOrigin      (xBRNLWRstrobeWF,Edge3,orgclkouter);

        WaveSetStrobe      (xBRNRWRstrobeWF,
                                t[tref]+t[tH],
                                t[tref]+t[tH]+t[tdBRNHWR]-ctcf-tgdb,
                                t[tref]+t[tH]+t[tper]+t[thzBRNHWR]+ctcf+tgdb);
        EdgeSetOrigin      (xBRNRWRstrobeWF,Edge1,orgclkouter);
        EdgeSetOrigin      (xBRNRWRstrobeWF,Edge2,orgclkouter);
        EdgeSetOrigin      (xBRNRWRstrobeWF,Edge3,orgclkouter);

        EdgeSet            (CAPdriveWF,Edge1,DriveData,
                                t[tref]+t[tper]-t[tsuCAP]+dtcf+tgdb);
        EdgeSet            (CAPdriveWF,Edge2,DriveComplement,
                                t[tref]+t[tper]+t[thdCAP]-dtcf-tgdb);
        EdgeSetOrigin      (CAPdriveWF,Edge1,orgclkoutll);
        EdgeSetOrigin      (CAPdriveWF,Edge2,orgclkoutel);

        EdgeSetDelay       (CLKOUT1strobeWF,Edge1,DriveOff,t[tref],0);
        EdgeSetDelayData   (CLKOUT1strobeWF,Edge2,ChanFirst,    
                                StrobeLow,ThreshVITL,           
                                t[tref]+t[tQ]-4ns,0,
                                StrobeHigh,ThreshVITL,
                                t[tref]+t[tQ]-4ns,0);
        EdgeSetDelayData   (CLKOUT1strobeWF,Edge3,ChanFirst,    
                                StrobeOffLow,ThreshVITL,                
                                t[tref]+t[tQ]+0ns,0,
                                StrobeOffHigh,ThreshVITL,
                                t[tref]+t[tQ]+0ns,0);
        EdgeSetDelayData   (CLKOUT1strobeWF,Edge4,ChanSecond,   
                                StrobeLow,ThreshVITL,           
                                t[tref]+t[tH]+t[tQ]-4ns,0,
                                StrobeHigh,ThreshVITL,
                                t[tref]+t[tH]+t[tQ]-4ns,0);
        EdgeSetDelayData   (CLKOUT1strobeWF,Edge5,ChanSecond,   
                                StrobeOffLow,ThreshVITL,                
                                t[tref]+t[tH]+t[tQ]+0ns,0,
                                StrobeOffHigh,ThreshVITL,
                                t[tref]+t[tH]+t[tQ]+0ns,0);
        EdgeSetOrigin      (CLKOUT1strobeWF,Edge1,orgclkoutef);
        EdgeSetOrigin      (CLKOUT1strobeWF,Edge2,orgclkoutef);
        EdgeSetOrigin      (CLKOUT1strobeWF,Edge3,orgclkoutef);
        EdgeSetOrigin      (CLKOUT1strobeWF,Edge4,orgclkouter);
        EdgeSetOrigin      (CLKOUT1strobeWF,Edge5,orgclkouter);

        EdgeSetDelay       (SYSCLKstrobeWF,Edge1,DriveOff,t[tref],0);
        EdgeSetDelayData   (SYSCLKstrobeWF,Edge2,ChanFirst,    
                                StrobeLow,ThreshVITL,           
                                t[tref]+t[tQ]-4ns,0,
                                StrobeHigh,ThreshVITL,
                                t[tref]+t[tQ]-4ns,0);
        EdgeSetDelayData   (SYSCLKstrobeWF,Edge3,ChanFirst,    
                                StrobeOffLow,ThreshVITL,                
                                t[tref]+t[tQ]+0ns,0,
                                StrobeOffHigh,ThreshVITL,
                                t[tref]+t[tQ]+0ns,0);
        EdgeSetDelayData   (SYSCLKstrobeWF,Edge4,ChanSecond,   
                                StrobeLow,ThreshVITL,           
                                t[tref]+t[tH]+t[tQ]-4ns,0,
                                StrobeHigh,ThreshVITL,
                                t[tref]+t[tH]+t[tQ]-4ns,0);
        EdgeSetDelayData   (SYSCLKstrobeWF,Edge5,ChanSecond,   
                                StrobeOffLow,ThreshVITL,                
                                t[tref]+t[tH]+t[tQ]+0ns,0,
                                StrobeOffHigh,ThreshVITL,
                                t[tref]+t[tH]+t[tQ]+0ns,0);
        EdgeSetOrigin      (SYSCLKstrobeWF,Edge1,orgclkoutef);
        EdgeSetOrigin      (SYSCLKstrobeWF,Edge2,orgclkoutef);
        EdgeSetOrigin      (SYSCLKstrobeWF,Edge3,orgclkoutef);
        EdgeSetOrigin      (SYSCLKstrobeWF,Edge4,orgclkouter);
        EdgeSetOrigin      (SYSCLKstrobeWF,Edge5,orgclkouter);

        EdgeSetDelay       (WDCLKstrobeWF,Edge1,DriveOff,t[tref],0);
        EdgeSetDelayData   (WDCLKstrobeWF,Edge2,ChanFirst,    
                                StrobeLow,ThreshVITL,           
                                t[tref]+t[tQ]-4ns,0,
                                StrobeHigh,ThreshVITL,
                                t[tref]+t[tQ]-4ns,0);
        EdgeSetDelayData   (WDCLKstrobeWF,Edge3,ChanFirst,    
                                StrobeOffLow,ThreshVITL,                
                                t[tref]+t[tQ]+0ns,0,
                                StrobeOffHigh,ThreshVITL,
                                t[tref]+t[tQ]+0ns,0);
        EdgeSetDelayData   (WDCLKstrobeWF,Edge4,ChanSecond,   
                                StrobeLow,ThreshVITL,           
                                t[tref]+t[tH]+t[tQ]-4ns,0,
                                StrobeHigh,ThreshVITL,
                                t[tref]+t[tH]+t[tQ]-4ns,0);
        EdgeSetDelayData   (WDCLKstrobeWF,Edge5,ChanSecond,   
                                StrobeOffLow,ThreshVITL,                
                                t[tref]+t[tH]+t[tQ]+0ns,0,
                                StrobeOffHigh,ThreshVITL,
                                t[tref]+t[tH]+t[tQ]+0ns,0);
        EdgeSetOrigin      (WDCLKstrobeWF,Edge1,orgclkoutef);
        EdgeSetOrigin      (WDCLKstrobeWF,Edge2,orgclkoutef);
        EdgeSetOrigin      (WDCLKstrobeWF,Edge3,orgclkoutef);
        EdgeSetOrigin      (WDCLKstrobeWF,Edge4,orgclkouter);
        EdgeSetOrigin      (WDCLKstrobeWF,Edge5,orgclkouter);

        EdgeSet            (DBUSdriveWF,Edge1,DriveData,
                                t[tref]+t[tper]-20ns);
        EdgeSet            (DBUSdriveWF,Edge2,DriveComplement,
                                t[tref]+t[tper]+10ns);
        EdgeSetOrigin      (DBUSdriveWF,Edge1,orgclkoutll);
        EdgeSetOrigin      (DBUSdriveWF,Edge2,orgclkoutel);

        WaveSetStrobe      (DBUSstrobeWF,
                                t[tref]+t[tH],
                                t[tref]+t[tper]-15ns,
                                t[tref]+t[tper]-10ns);
        EdgeSetOrigin      (DBUSstrobeWF,Edge1,orgclkouter);
        EdgeSetOrigin      (DBUSstrobeWF,Edge2,orgclkouter);
        EdgeSetOrigin      (DBUSstrobeWF,Edge3,orgclkouter);

        EdgeSet            (xDBUSRDdriveWF,Edge1,DriveData,
                                t[tref]+t[tper]-t[tsuDBUSRD]+dtcf+tgdb);
        EdgeSet            (xDBUSRDdriveWF,Edge2,DriveComplement,
                                t[tref]+t[tper]+t[thdDBUSRD]-dtcf-tgdb);
        EdgeSetOrigin      (xDBUSRDdriveWF,Edge1,orgclkoutll);
        EdgeSetOrigin      (xDBUSRDdriveWF,Edge2,orgclkoutel);

        EdgeSet            (xDBUSWRdriveWF,Edge1,DriveComplement,
                                t[tref]+t[tH]);
        EdgeSet            (xDBUSWRdriveWF,Edge2,DriveData,
                                t[tref]+t[tH]+7ns);
        EdgeSetOrigin      (xDBUSWRdriveWF,Edge1,orgclkoutll);
        EdgeSetOrigin      (xDBUSWRdriveWF,Edge2,orgclkoutel);

        WaveSetStrobe      (xDBUSWRstrobeWF,
                                t[tref],
                                t[tref]+t[tdDBUSWR]-ctcf-tgdb,
                                t[tref]+t[tper]+t[thzDBUSWR]+ctcf+tgdb);
        EdgeSetOrigin      (xDBUSWRstrobeWF,Edge1,orgclkoutef);
        EdgeSetOrigin      (xDBUSWRstrobeWF,Edge2,orgclkoutef);
        EdgeSetOrigin      (xDBUSWRstrobeWF,Edge3,orgclkoutef);

        EdgeSet            (GPIOFdriveWF,Edge1,DriveData,
                                t[tref]+t[tH]-t[tsuGPIOF]+dtcf+tgdb);
        EdgeSet            (GPIOFdriveWF,Edge2,DriveComplement,
                                t[tref]+t[tH]+t[thdGPIOF]-dtcf-tgdb);
        EdgeSetOrigin      (GPIOFdriveWF,Edge1,orgclkoutlh);
        EdgeSetOrigin      (GPIOFdriveWF,Edge2,orgclkouteh);

        WaveSetStrobe      (GPIOFstrobeWF,
                                t[tref],
                                t[tref]+t[tdGPIOF]-ctcf-tgdb,
                                t[tref]+t[tper]+t[thzGPIOF]+ctcf+tgdb);
        EdgeSetOrigin      (GPIOFstrobeWF,Edge1,orgclkoutef);
        EdgeSetOrigin      (GPIOFstrobeWF,Edge2,orgclkoutef);
        EdgeSetOrigin      (GPIOFstrobeWF,Edge3,orgclkoutef);

        EdgeSet            (GPIOSdriveWF,Edge1,DriveData,
                                t[tref]+t[tH]-t[tsuGPIOS]+dtcf+tgdb);
        EdgeSet            (GPIOSdriveWF,Edge2,DriveComplement,
                                t[tref]+t[tH]+t[thdGPIOS]-dtcf-tgdb);
        EdgeSetOrigin      (GPIOSdriveWF,Edge1,orgclkoutlh);
        EdgeSetOrigin      (GPIOSdriveWF,Edge2,orgclkouteh);

        WaveSetStrobe      (GPIOSstrobeWF,
                                t[tref],
                                t[tref]+t[tdGPIOS]-ctcf-tgdb,
                                t[tref]+t[tper]+t[thzGPIOS]+ctcf+tgdb);
        EdgeSetOrigin      (GPIOSstrobeWF,Edge1,orgclkoutef);
        EdgeSetOrigin      (GPIOSstrobeWF,Edge2,orgclkoutef);
        EdgeSetOrigin      (GPIOSstrobeWF,Edge3,orgclkoutef);

        EdgeSet            (INTNdriveWF,Edge1,DriveData,
                                t[tref]+t[tH]-t[tsuINTN]+dtcf+tgdb);
        EdgeSet            (INTNdriveWF,Edge2,DriveHigh,
                                t[tref]+t[tH]+t[thdINTN]-dtcf-tgdb);
        EdgeSetOrigin      (INTNdriveWF,Edge1,orgclkoutlh);
        EdgeSetOrigin      (INTNdriveWF,Edge2,orgclkouteh);

        WaveSetNR          (MPMCNdriveWF,t[tref]+t[tH]-t[tH]);
        EdgeSetOrigin      (MPMCNdriveWF,Edge1,orgclkoutlh);

(* removed this WF to avoid glitches on PSN and STRBN *)
{
        EdgeSet            (MPMCNdriveWF,Edge1,DriveData,
                                t[tref]+t[tH]-t[tsuMPMCN]+dtcf+tgdb);
        EdgeSet            (MPMCNdriveWF,Edge2,DriveHigh,
                                t[tref]+t[tH]+t[thdMPMCN-dtcf-tgdb);
        EdgeSetOrigin      (MPMCNdriveWF,Edge1,orgclkoutlh);
        EdgeSetOrigin      (MPMCNdriveWF,Edge2,orgclkouteh);
}
        EdgeSet            (NMINdriveWF,Edge1,DriveData,
                                t[tref]+t[tH]-t[tsuNMIN]+dtcf+tgdb);
        EdgeSet            (NMINdriveWF,Edge2,DriveHigh,
                                t[tref]+t[tH]+t[thdNMIN]-dtcf-tgdb);
        EdgeSetOrigin      (NMINdriveWF,Edge1,orgclkoutlh);
        EdgeSetOrigin      (NMINdriveWF,Edge2,orgclkouteh);

        EdgeSet            (PDPINTdriveWF,Edge1,DriveData,
                                t[tref]+t[tper]-t[tsuPDPINT]+dtcf+tgdb);
        EdgeSet            (PDPINTdriveWF,Edge2,DriveHigh,
                                t[tref]+t[tper]+t[thdPDPINT]-dtcf-tgdb);
        EdgeSetOrigin      (PDPINTdriveWF,Edge1,orgclkoutll);
        EdgeSetOrigin      (PDPINTdriveWF,Edge2,orgclkoutel);

        WaveSetStrobe      (PWMstrobeWF,
                                t[tref]+t[tH],
                                t[tref]+t[tH]+t[tdPWM]-ctcf-tgdb,
                                t[tref]+t[tH]+t[tper]+t[thzPWM]+ctcf+tgdb);
        EdgeSetOrigin      (PWMstrobeWF,Edge1,orgclkouter);
        EdgeSetOrigin      (PWMstrobeWF,Edge2,orgclkouter);
        EdgeSetOrigin      (PWMstrobeWF,Edge3,orgclkouter);

        WaveSetStrobe      (RDNLstrobeWF,
                                t[tref],
                                t[tref]+t[tH]+t[tH]-14ns,
                                t[tref]+t[tH]+t[tH]-10ns);
        EdgeSetOrigin      (RDNLstrobeWF,Edge1,orgclkoutef);
        EdgeSetOrigin      (RDNLstrobeWF,Edge2,orgclkoutef);
        EdgeSetOrigin      (RDNLstrobeWF,Edge3,orgclkoutef);

        WaveSetStrobe      (RDNHstrobeWF,
                                t[tref],
                                t[tref]+t[tH]+t[tH]-14ns,
                                t[tref]+t[tH]+t[tH]-10ns);
        EdgeSetOrigin      (RDNHstrobeWF,Edge1,orgclkoutef);
        EdgeSetOrigin      (RDNHstrobeWF,Edge2,orgclkoutef);
        EdgeSetOrigin      (RDNHstrobeWF,Edge3,orgclkoutef);

        WaveSetStrobe      (xRDNFstrobeWF,
                                t[tref],
                                t[tref]+t[tH]+t[tH]-14ns, 
                                t[tref]+t[tH]+t[tH]-10ns);
        EdgeSetOrigin      (xRDNFstrobeWF,Edge1,orgclkoutef);
        EdgeSetOrigin      (xRDNFstrobeWF,Edge2,orgclkoutef);
        EdgeSetOrigin      (xRDNFstrobeWF,Edge3,orgclkoutef);

        WaveSetStrobe      (xRDNLstrobeWF,
                                t[tref],
                                t[tref]+t[tdRDNL]-ctcf-tgdb,
                                t[tref]+t[tper]+t[thzRDNL]+ctcf+tgdb);
        EdgeSetOrigin      (xRDNLstrobeWF,Edge1,orgclkoutef);
        EdgeSetOrigin      (xRDNLstrobeWF,Edge2,orgclkoutef);
        EdgeSetOrigin      (xRDNLstrobeWF,Edge3,orgclkoutef);

        WaveSetStrobe      (xRDNRstrobeWF,
                                t[tref],
                                t[tref]+t[tH]+t[tdRDNH]-ctcf-tgdb,
                                t[tref]+t[tH]+t[tH]+t[thzRDNH]+ctcf+tgdb);
        EdgeSetOrigin      (xRDNRstrobeWF,Edge1,orgclkoutef);
        EdgeSetOrigin      (xRDNRstrobeWF,Edge2,orgclkoutef);
        EdgeSetOrigin      (xRDNRstrobeWF,Edge3,orgclkoutef);

        EdgeSet            (READYdriveWF,Edge1,DriveData,
                                t[tref]+t[tH]-t[tsuREADY]+dtcf+tgdb);
        EdgeSet            (READYdriveWF,Edge2,DriveHigh,
                                t[tref]+t[tH]+t[thdREADY]-dtcf-tgdb);
        EdgeSetOrigin      (READYdriveWF,Edge1,orgclkoutlh);
        EdgeSetOrigin      (READYdriveWF,Edge2,orgclkouteh);

        WaveSetStrobe      (RNWLstrobeWF,
                                t[tref]+t[tH],
                                t[tref]+t[tH]+30ns,
                                t[tref]+t[tH]+t[tper]-12ns);
        EdgeSetOrigin      (RNWLstrobeWF,Edge1,orgclkouter);
        EdgeSetOrigin      (RNWLstrobeWF,Edge2,orgclkouter);
        EdgeSetOrigin      (RNWLstrobeWF,Edge3,orgclkouter);

        WaveSetStrobe      (RNWHstrobeWF,
                                t[tref]+t[tH],
                                t[tref]+t[tH]+30ns,
                                t[tref]+t[tH]+t[tper]-12ns);
        EdgeSetOrigin      (RNWHstrobeWF,Edge1,orgclkouter);
        EdgeSetOrigin      (RNWHstrobeWF,Edge2,orgclkouter);
        EdgeSetOrigin      (RNWHstrobeWF,Edge3,orgclkouter);

        WaveSetStrobe      (xRNWFstrobeWF,
                                t[tref]+t[tH],
                                t[tref]+t[tH]+30ns,
                                t[tref]+t[tH]+t[tper]-12ns);
        EdgeSetOrigin      (xRNWFstrobeWF,Edge1,orgclkouter);
        EdgeSetOrigin      (xRNWFstrobeWF,Edge2,orgclkouter);
        EdgeSetOrigin      (xRNWFstrobeWF,Edge3,orgclkouter);

        WaveSetStrobe      (xRNWLstrobeWF,
                                t[tref]+t[tH],
                                t[tref]+t[tH]+t[tdRNWL]-ctcf-tgdb,
                                t[tref]+t[tH]+t[tper]+t[thzRNWL]+ctcf+tgdb);
        EdgeSetOrigin      (xRNWLstrobeWF,Edge1,orgclkouter);
        EdgeSetOrigin      (xRNWLstrobeWF,Edge2,orgclkouter);
        EdgeSetOrigin      (xRNWLstrobeWF,Edge3,orgclkouter);

        WaveSetStrobe      (xRNWRstrobeWF,
                                t[tref]+t[tH],
                                t[tref]+t[tH]+t[tdRNWH]-ctcf-tgdb,
                                t[tref]+t[tH]+t[tper]+t[thzRNWH]+ctcf+tgdb);
        EdgeSetOrigin      (xRNWRstrobeWF,Edge1,orgclkouter);
        EdgeSetOrigin      (xRNWRstrobeWF,Edge2,orgclkouter);
        EdgeSetOrigin      (xRNWRstrobeWF,Edge3,orgclkouter);

        WaveSetNR          (RSNdriveLWF,t[tref]+t[tper]-t[tH]);
        EdgeSetOrigin      (RSNdriveLWF,Edge1,orgclkoutll);

        WaveSetNR          (RSNdriveHWF,t[tref]);
        EdgeSetOrigin      (RSNdriveHWF,Edge1,orgclkoutll);

        WaveSetStrobe      (RSNstrobeWF,
                                t[tref],
                                t[tref]+t[tdRSN]-ctcf-tgdb,
                                t[tref]+t[tper]+t[thzRSN]+ctcf+tgdb);
        EdgeSetOrigin      (RSNstrobeWF,Edge1,orgclkoutef);
        EdgeSetOrigin      (RSNstrobeWF,Edge2,orgclkoutef);
        EdgeSetOrigin      (RSNstrobeWF,Edge3,orgclkoutef);

        EdgeSet            (SCIRXDdriveWF,Edge1,DriveData,
                                t[tref]+t[tH]-t[tsuSCIRXD]+dtcf+tgdb);
        EdgeSet            (SCIRXDdriveWF,Edge2,DriveComplement,
                                t[tref]+t[tH]+t[thdSCIRXD]-dtcf-tgdb);
        EdgeSetOrigin      (SCIRXDdriveWF,Edge1,orgclkoutlh);
        EdgeSetOrigin      (SCIRXDdriveWF,Edge2,orgclkouteh);

        WaveSetStrobe      (SCITXDstrobeWF,
                                t[tref],
                                t[tref]+t[tdSCITXD]-ctcf-tgdb,
                                t[tref]+t[tper]+t[thzSCITXD]+ctcf+tgdb);
        EdgeSetOrigin      (SCITXDstrobeWF,Edge1,orgclkoutef);
        EdgeSetOrigin      (SCITXDstrobeWF,Edge2,orgclkoutef);
        EdgeSetOrigin      (SCITXDstrobeWF,Edge3,orgclkoutef);

        EdgeSet            (SPICLKdriveWF,Edge1,DriveData,
                                t[tref]+t[tH]-t[tsuSPICLK]+dtcf+tgdb);
        EdgeSet            (SPICLKdriveWF,Edge2,DriveComplement,
                                t[tref]+t[tH]+t[thdSPICLK]-dtcf-tgdb);
        EdgeSetOrigin      (SPICLKdriveWF,Edge1,orgclkoutlh);
        EdgeSetOrigin      (SPICLKdriveWF,Edge2,orgclkouteh);

        WaveSetStrobe      (SPICLKstrobeWF,
                                t[tref],
                                t[tref]+t[tdSPICLK]-ctcf-tgdb,
                                t[tref]+t[tper]+t[thzSPICLK]+ctcf+tgdb);
        EdgeSetOrigin      (SPICLKstrobeWF,Edge1,orgclkoutef);
        EdgeSetOrigin      (SPICLKstrobeWF,Edge2,orgclkoutef);
        EdgeSetOrigin      (SPICLKstrobeWF,Edge3,orgclkoutef);

        EdgeSet            (SPISIMOdriveWF,Edge1,DriveData,
                                t[tref]+t[tH]-t[tsuSPISIMO]+dtcf+tgdb);
        EdgeSet            (SPISIMOdriveWF,Edge2,DriveComplement,
                                t[tref]+t[tH]+t[thdSPISIMO]-dtcf-tgdb);
        EdgeSetOrigin      (SPISIMOdriveWF,Edge1,orgclkoutlh);
        EdgeSetOrigin      (SPISIMOdriveWF,Edge2,orgclkouteh);

        WaveSetStrobe      (SPISIMOstrobeWF,
                                t[tref],
                                t[tref]+t[tdSPISIMO]-ctcf-tgdb,
                                t[tref]+t[tper]+t[thzSPISIMO]+ctcf+tgdb);
        EdgeSetOrigin      (SPISIMOstrobeWF,Edge1,orgclkoutef);
        EdgeSetOrigin      (SPISIMOstrobeWF,Edge2,orgclkoutef);
        EdgeSetOrigin      (SPISIMOstrobeWF,Edge3,orgclkoutef);

        EdgeSet            (SPISOMIdriveWF,Edge1,DriveData,
                                t[tref]+t[tH]-t[tsuSPISOMI]+dtcf+tgdb);
        EdgeSet            (SPISOMIdriveWF,Edge2,DriveComplement,
                                t[tref]+t[tH]+t[thdSPISOMI]-dtcf-tgdb);
        EdgeSetOrigin      (SPISOMIdriveWF,Edge1,orgclkoutlh);
        EdgeSetOrigin      (SPISOMIdriveWF,Edge2,orgclkouteh);

        WaveSetStrobe      (SPISOMIstrobeWF,
                                t[tref],
                                t[tref]+t[tdSPISOMI]-ctcf-tgdb,
                                t[tref]+t[tper]+t[thzSPISOMI]+ctcf+tgdb);
        EdgeSetOrigin      (SPISOMIstrobeWF,Edge1,orgclkoutef);
        EdgeSetOrigin      (SPISOMIstrobeWF,Edge2,orgclkoutef);
        EdgeSetOrigin      (SPISOMIstrobeWF,Edge3,orgclkoutef);

        EdgeSet            (SPISTEdriveWF,Edge1,DriveData,
                                t[tref]+t[tH]-t[tsuSPISTE]+dtcf+tgdb);
        EdgeSet            (SPISTEdriveWF,Edge2,DriveHigh,
                                t[tref]+t[tH]+t[thdSPISTE]-dtcf-tgdb);
        EdgeSetOrigin      (SPISTEdriveWF,Edge1,orgclkoutlh);
        EdgeSetOrigin      (SPISTEdriveWF,Edge2,orgclkouteh);

        WaveSetStrobe      (STRBNLstrobeWF,
                                t[tref],
                                t[tref]+30ns,
                                t[tref]+t[tper]-10ns);
        EdgeSetOrigin      (STRBNLstrobeWF,Edge1,orgclkoutef);
        EdgeSetOrigin      (STRBNLstrobeWF,Edge2,orgclkoutef);
        EdgeSetOrigin      (STRBNLstrobeWF,Edge3,orgclkoutef);

        WaveSetStrobe      (STRBNHstrobeWF,
                                t[tref],
                                t[tref]+30ns,
                                t[tref]+t[tper]-10ns);
        EdgeSetOrigin      (STRBNHstrobeWF,Edge1,orgclkoutef);
        EdgeSetOrigin      (STRBNHstrobeWF,Edge2,orgclkoutef);
        EdgeSetOrigin      (STRBNHstrobeWF,Edge3,orgclkoutef);

        WaveSetStrobe      (xSTRBNFstrobeWF,
                                t[tref],
                                t[tref]+30ns,
                                t[tref]+t[tper]-10ns);
        EdgeSetOrigin      (xSTRBNFstrobeWF,Edge1,orgclkoutef);
        EdgeSetOrigin      (xSTRBNFstrobeWF,Edge2,orgclkoutef);
        EdgeSetOrigin      (xSTRBNFstrobeWF,Edge3,orgclkoutef);

        WaveSetStrobe      (xSTRBNLstrobeWF,
                                t[tref],
                                t[tref]+t[tdSTRBNL]-ctcf-tgdb,
                                t[tref]+t[tper]+t[thzSTRBNL]+ctcf+tgdb);
        EdgeSetOrigin      (xSTRBNLstrobeWF,Edge1,orgclkoutef);
        EdgeSetOrigin      (xSTRBNLstrobeWF,Edge2,orgclkoutef);
        EdgeSetOrigin      (xSTRBNLstrobeWF,Edge3,orgclkoutef);

        WaveSetStrobe      (xSTRBNRstrobeWF,
                                t[tref],
                                t[tref]+t[tdSTRBNH]-ctcf-tgdb,
                                t[tref]+t[tper]+t[thzSTRBNH]+ctcf+tgdb);
        EdgeSetOrigin      (xSTRBNRstrobeWF,Edge1,orgclkoutef);
        EdgeSetOrigin      (xSTRBNRstrobeWF,Edge2,orgclkoutef);
        EdgeSetOrigin      (xSTRBNRstrobeWF,Edge3,orgclkoutef);

        EdgeSet            (TMRCLKdriveWF,Edge1,DriveData,
                                t[tref]+t[tper]-t[tsuTMRCLK]+dtcf+tgdb);
        EdgeSet            (TMRCLKdriveWF,Edge2,DriveComplement,
                                t[tref]+t[tper]+t[thdTMRCLK]-dtcf-tgdb);
        EdgeSetOrigin      (TMRCLKdriveWF,Edge1,orgclkoutll);
        EdgeSetOrigin      (TMRCLKdriveWF,Edge2,orgclkoutel);

        EdgeSet            (TMRDIRdriveWF,Edge1,DriveData,
                                t[tref]+t[tper]-t[tsuTMRDIR]+dtcf+tgdb);
        EdgeSet            (TMRDIRdriveWF,Edge2,DriveComplement,
                                t[tref]+t[tper]+t[thdTMRDIR]-dtcf-tgdb);
        EdgeSetOrigin      (TMRDIRdriveWF,Edge1,orgclkoutll);
        EdgeSetOrigin      (TMRDIRdriveWF,Edge2,orgclkoutel);

        WaveSetStrobe      (WENLstrobeWF,
                                t[tref],
                                t[tref]+30ns,
                                t[tref]+t[tper]-10ns);
        EdgeSetOrigin      (WENLstrobeWF,Edge1,orgclkoutef);
        EdgeSetOrigin      (WENLstrobeWF,Edge2,orgclkoutef);
        EdgeSetOrigin      (WENLstrobeWF,Edge3,orgclkoutef);

        WaveSetStrobe      (WENHstrobeWF,
                                t[tref],
                                t[tref]+30ns,
                                t[tref]+t[tper]-10ns);
        EdgeSetOrigin      (WENHstrobeWF,Edge1,orgclkoutef);
        EdgeSetOrigin      (WENHstrobeWF,Edge2,orgclkoutef);
        EdgeSetOrigin      (WENHstrobeWF,Edge3,orgclkoutef);

        WaveSetStrobe      (xWENFstrobeWF,
                                t[tref],
                                t[tref]+30ns,
                                t[tref]+t[tper]-10ns);
        EdgeSetOrigin      (xWENFstrobeWF,Edge1,orgclkoutef);
        EdgeSetOrigin      (xWENFstrobeWF,Edge2,orgclkoutef);
        EdgeSetOrigin      (xWENFstrobeWF,Edge3,orgclkoutef);

        WaveSetStrobe      (xWENLstrobeWF,
                                t[tref],
                                t[tref]+t[tdWENL]-ctcf-tgdb,
                                t[tref]+t[tper]+t[thzWENL]+ctcf+tgdb);
        EdgeSetOrigin      (xWENLstrobeWF,Edge1,orgclkoutef);
        EdgeSetOrigin      (xWENLstrobeWF,Edge2,orgclkoutef);
        EdgeSetOrigin      (xWENLstrobeWF,Edge3,orgclkoutef);

        WaveSetStrobe      (xWENRstrobeWF,
                                t[tref],
                                t[tref]+t[tdWENH]-ctcf-tgdb,
                                t[tref]+t[tper]+t[thzWENH]+ctcf+tgdb);
        EdgeSetOrigin      (xWENRstrobeWF,Edge1,orgclkoutef);
        EdgeSetOrigin      (xWENRstrobeWF,Edge2,orgclkoutef);
        EdgeSetOrigin      (xWENRstrobeWF,Edge3,orgclkoutef);

        WaveSetStrobe      (XFstrobeWF,
                                t[tref]+t[tH],
                                t[tref]+t[tH]+t[tdXF]-ctcf-tgdb,
                                t[tref]+t[tH]+t[tper]+t[thzXF]+ctcf+tgdb);
        EdgeSetOrigin      (XFstrobeWF,Edge1,orgclkouter);
        EdgeSetOrigin      (XFstrobeWF,Edge2,orgclkouter);
        EdgeSetOrigin      (XFstrobeWF,Edge3,orgclkouter);

        WaveSetStrobe      (XTAL2strobeWF, 
                                t[tref]+t[tH], 
                                t[tref]+t[tH]+30ns,
                                t[tref]+t[tH]+t[tper]-10ns);
        EdgeSetOrigin      (XTAL2strobeWF,Edge1,orgclkin);
        EdgeSetOrigin      (XTAL2strobeWF,Edge2,orgclkin);
        EdgeSetOrigin      (XTAL2strobeWF,Edge3,orgclkin);
    end;  (* end SpecACTables *)

  TIlofrqlooseACTable,
  TIhifrqlooseACTable,         
  TIveryhifrqlooseACTable,         
  TIsearchlooseACTable,
  TIscanACTable,
 TIPMT100ACTable:
    begin
        WaveSetNR          (ABUSdriveWF,t[tref]+t[tH]);
        EdgeSetOrigin      (ABUSdriveWF,Edge1,orgclkoutll);

        WaveSetStrobe      (ABUSRDstrobeWF,
                                t[tref]+t[tH],
                                t[tref]+t[tper]-14ns,
                                t[tref]+t[tper]-10ns);
        EdgeSetOrigin      (ABUSRDstrobeWF,Edge1,orgclkoutef);
        EdgeSetOrigin      (ABUSRDstrobeWF,Edge2,orgclkoutef);
        EdgeSetOrigin      (ABUSRDstrobeWF,Edge3,orgclkoutef);

        WaveSetStrobe      (xABUSRDstrobeWF,
                                t[tref]-5ns,
                                t[tref]+t[tper]-14ns,
                                t[tref]+t[tper]-10ns);
        EdgeSetOrigin      (xABUSRDstrobeWF,Edge1,orgclkoutef);
        EdgeSetOrigin      (xABUSRDstrobeWF,Edge2,orgclkoutef);
        EdgeSetOrigin      (xABUSRDstrobeWF,Edge3,orgclkoutef);

        WaveSetStrobe      (ABUSWRstrobeWF,
                                t[tref]+t[tH],
                                t[tref]+t[tper]-14ns,
                                t[tref]+t[tper]-10ns);
        EdgeSetOrigin      (ABUSWRstrobeWF,Edge1,orgclkouter);
        EdgeSetOrigin      (ABUSWRstrobeWF,Edge2,orgclkouter);
        EdgeSetOrigin      (ABUSWRstrobeWF,Edge3,orgclkouter);

        WaveSetStrobe      (xABUSWRstrobeWF,
                                t[tref]+t[tH]-5ns,
                                t[tref]+t[tH]+t[tper]-14ns,
                                t[tref]+t[tH]+t[tper]-10ns);
        EdgeSetOrigin      (xABUSWRstrobeWF,Edge1,orgclkouter);
        EdgeSetOrigin      (xABUSWRstrobeWF,Edge2,orgclkouter);
        EdgeSetOrigin      (xABUSWRstrobeWF,Edge3,orgclkouter);

        WaveSetStrobe      (ACTRLstrobeWF,
                                t[tref]+t[tH],
                                t[tref]+t[tper]-14ns,
                                t[tref]+t[tper]-10ns);
        EdgeSetOrigin      (ACTRLstrobeWF,Edge1,orgclkouter);
        EdgeSetOrigin      (ACTRLstrobeWF,Edge2,orgclkouter);
        EdgeSetOrigin      (ACTRLstrobeWF,Edge3,orgclkouter);

        WaveSetStrobe      (xACTRLFRDstrobeWF,
                                t[tref]+t[tH],
                                t[tref]+t[tper]-14ns,
                                t[tref]+t[tper]-10ns);
        EdgeSetOrigin      (xACTRLFRDstrobeWF,Edge1,orgclkoutef);
        EdgeSetOrigin      (xACTRLFRDstrobeWF,Edge2,orgclkoutef);
        EdgeSetOrigin      (xACTRLFRDstrobeWF,Edge3,orgclkoutef);

        WaveSetStrobe      (xACTRLLRDstrobeWF,
                                t[tref]-5ns,
                                t[tref]+t[tper]-14ns,
                                t[tref]+t[tper]-10ns);
        EdgeSetOrigin      (xACTRLLRDstrobeWF,Edge1,orgclkoutef);
        EdgeSetOrigin      (xACTRLLRDstrobeWF,Edge2,orgclkoutef);
        EdgeSetOrigin      (xACTRLLRDstrobeWF,Edge3,orgclkoutef);

        WaveSetStrobe      (xACTRLRRDstrobeWF,
                                t[tref]-5ns,
                                t[tref]+t[tper]-14ns,
                                t[tref]+t[tper]-10ns);
        EdgeSetOrigin      (xACTRLRRDstrobeWF,Edge1,orgclkoutef);
        EdgeSetOrigin      (xACTRLRRDstrobeWF,Edge2,orgclkoutef);
        EdgeSetOrigin      (xACTRLRRDstrobeWF,Edge3,orgclkoutef);

        WaveSetStrobe      (xACTRLFWRstrobeWF,
                                t[tref]+t[tH],
                                t[tref]+t[tper]-14ns,
                                t[tref]+t[tper]-10ns);
        EdgeSetOrigin      (xACTRLFWRstrobeWF,Edge1,orgclkouter);
        EdgeSetOrigin      (xACTRLFWRstrobeWF,Edge2,orgclkouter);
        EdgeSetOrigin      (xACTRLFWRstrobeWF,Edge3,orgclkouter);

        WaveSetStrobe      (xACTRLLWRstrobeWF,
                                t[tref]+t[tH]-5ns,
                                t[tref]+t[tH]+t[tper]-14ns,
                                t[tref]+t[tH]+t[tper]-10ns);
        EdgeSetOrigin      (xACTRLLWRstrobeWF,Edge1,orgclkouter);
        EdgeSetOrigin      (xACTRLLWRstrobeWF,Edge2,orgclkouter);
        EdgeSetOrigin      (xACTRLLWRstrobeWF,Edge3,orgclkouter);

        WaveSetStrobe      (xACTRLRWRstrobeWF,
                                t[tref]+t[tH]-5ns,
                                t[tref]+t[tH]+t[tper]-14ns,
                                t[tref]+t[tH]+t[tper]-10ns);
        EdgeSetOrigin      (xACTRLRWRstrobeWF,Edge1,orgclkouter);
        EdgeSetOrigin      (xACTRLRWRstrobeWF,Edge2,orgclkouter);
        EdgeSetOrigin      (xACTRLRWRstrobeWF,Edge3,orgclkouter);

        EdgeSet            (BIONdriveWF,Edge1,DriveHigh,
                                t[tref]+t[tH]);
        EdgeSet            (BIONdriveWF,Edge2,DriveData,
                                t[tref]+t[tH]+7ns);
        EdgeSetOrigin      (BIONdriveWF,Edge1,orgclkoutll);
        EdgeSetOrigin      (BIONdriveWF,Edge2,orgclkoutel);

        WaveSetStrobe      (BRNstrobeWF,
                                t[tref]+t[tH],
                                t[tref]+t[tper]-14ns,
                                t[tref]+t[tper]-10ns);
        EdgeSetOrigin      (BRNstrobeWF,Edge1,orgclkouter);
        EdgeSetOrigin      (BRNstrobeWF,Edge2,orgclkouter);
        EdgeSetOrigin      (BRNstrobeWF,Edge3,orgclkouter);

        WaveSetStrobe      (xBRNFRDstrobeWF,
                                t[tref]+t[tH],
                                t[tref]+t[tper]-14ns,
                                t[tref]+t[tper]-10ns);
        EdgeSetOrigin      (xBRNFRDstrobeWF,Edge1,orgclkoutef);
        EdgeSetOrigin      (xBRNFRDstrobeWF,Edge2,orgclkoutef);
        EdgeSetOrigin      (xBRNFRDstrobeWF,Edge3,orgclkoutef);

        WaveSetStrobe      (xBRNLRDstrobeWF,
                                t[tref]-5ns,
                                t[tref]+t[tper]-14ns,
                                t[tref]+t[tper]-10ns);
        EdgeSetOrigin      (xBRNLRDstrobeWF,Edge1,orgclkoutef);
        EdgeSetOrigin      (xBRNLRDstrobeWF,Edge2,orgclkoutef);
        EdgeSetOrigin      (xBRNLRDstrobeWF,Edge3,orgclkoutef);

        WaveSetStrobe      (xBRNRRDstrobeWF,
                                t[tref]-5ns,
                                t[tref]+t[tper]-14ns,
                                t[tref]+t[tper]-10ns);
        EdgeSetOrigin      (xBRNRRDstrobeWF,Edge1,orgclkoutef);
        EdgeSetOrigin      (xBRNRRDstrobeWF,Edge2,orgclkoutef);
        EdgeSetOrigin      (xBRNRRDstrobeWF,Edge3,orgclkoutef);

        WaveSetStrobe      (xBRNFWRstrobeWF,
                                t[tref]+t[tH],
                                t[tref]+t[tper]-14ns,
                                t[tref]+t[tper]-10ns);
        EdgeSetOrigin      (xBRNFWRstrobeWF,Edge1,orgclkouter);
        EdgeSetOrigin      (xBRNFWRstrobeWF,Edge2,orgclkouter);
        EdgeSetOrigin      (xBRNFWRstrobeWF,Edge3,orgclkouter);

        WaveSetStrobe      (xBRNLWRstrobeWF,
                                t[tref]+t[tH]-5ns,
                                t[tref]+t[tH]+t[tper]-14ns,
                                t[tref]+t[tH]+t[tper]-10ns);
        EdgeSetOrigin      (xBRNLWRstrobeWF,Edge1,orgclkouter);
        EdgeSetOrigin      (xBRNLWRstrobeWF,Edge2,orgclkouter);
        EdgeSetOrigin      (xBRNLWRstrobeWF,Edge3,orgclkouter);

        WaveSetStrobe      (xBRNRWRstrobeWF,
                                t[tref]+t[tH]-5ns,
                                t[tref]+t[tH]+t[tper]-14ns,
                                t[tref]+t[tH]+t[tper]-10ns);
        EdgeSetOrigin      (xBRNRWRstrobeWF,Edge1,orgclkouter);
        EdgeSetOrigin      (xBRNRWRstrobeWF,Edge2,orgclkouter);
        EdgeSetOrigin      (xBRNRWRstrobeWF,Edge3,orgclkouter);

        EdgeSet            (CAPdriveWF,Edge1,DriveComplement,
                                t[tref]+t[tH]);
        EdgeSet            (CAPdriveWF,Edge2,DriveData,
                                t[tref]+t[tH]+7ns);
        EdgeSetOrigin      (CAPdriveWF,Edge1,orgclkoutll);
        EdgeSetOrigin      (CAPdriveWF,Edge2,orgclkoutel);

        EdgeSetDelay       (CLKOUT1strobeWF,Edge1,DriveOff,0ns,0);
        EdgeSetDelayData   (CLKOUT1strobeWF,Edge2,ChanFirst,    
                                StrobeLow,ThreshVITL,           
                                t[tref]+t[tQ]-4ns,0,
                                StrobeHigh,ThreshVITL,
                                t[tref]+t[tQ]-4ns,0);
        EdgeSetDelayData   (CLKOUT1strobeWF,Edge3,ChanFirst,    
                                StrobeOffLow,ThreshVITL,                
                                t[tref]+t[tQ]+0ns,0,
                                StrobeOffHigh,ThreshVITL,
                                t[tref]+t[tQ]+0ns,0);
        EdgeSetDelayData   (CLKOUT1strobeWF,Edge4,ChanSecond,   
                                StrobeLow,ThreshVITL,           
                                t[tref]+t[tH]+t[tQ]-4ns,0,
                                StrobeHigh,ThreshVITL,
                                t[tref]+t[tH]+t[tQ]-4ns,0);
        EdgeSetDelayData   (CLKOUT1strobeWF,Edge5,ChanSecond,   
                                StrobeOffLow,ThreshVITL,                
                                t[tref]+t[tH]+t[tQ]+0ns,0,
                                StrobeOffHigh,ThreshVITL,
                                t[tref]+t[tH]+t[tQ]+0ns,0);
        EdgeSetOrigin      (CLKOUT1strobeWF,Edge1,orgclkoutef);
        EdgeSetOrigin      (CLKOUT1strobeWF,Edge2,orgclkoutef);
        EdgeSetOrigin      (CLKOUT1strobeWF,Edge3,orgclkoutef);
        EdgeSetOrigin      (CLKOUT1strobeWF,Edge4,orgclkouter);
        EdgeSetOrigin      (CLKOUT1strobeWF,Edge5,orgclkouter);

        EdgeSetDelay       (SYSCLKstrobeWF,Edge1,DriveOff,t[tref],0);
        EdgeSetDelayData   (SYSCLKstrobeWF,Edge2,ChanFirst,    
                                StrobeLow,ThreshVITL,           
                                t[tref]+t[tQ]-4ns,0,
                                StrobeHigh,ThreshVITL,
                                t[tref]+t[tQ]-4ns,0);
        EdgeSetDelayData   (SYSCLKstrobeWF,Edge3,ChanFirst,    
                                StrobeOffLow,ThreshVITL,                
                                t[tref]+t[tQ]+0ns,0,
                                StrobeOffHigh,ThreshVITL,
                                t[tref]+t[tQ]+0ns,0);
        EdgeSetDelayData   (SYSCLKstrobeWF,Edge4,ChanSecond,   
                                StrobeLow,ThreshVITL,           
                                t[tref]+t[tH]+t[tQ]-4ns,0,
                                StrobeHigh,ThreshVITL,
                                t[tref]+t[tH]+t[tQ]-4ns,0);
        EdgeSetDelayData   (SYSCLKstrobeWF,Edge5,ChanSecond,   
                                StrobeOffLow,ThreshVITL,                
                                t[tref]+t[tH]+t[tQ]+0ns,0,
                                StrobeOffHigh,ThreshVITL,
                                t[tref]+t[tH]+t[tQ]+0ns,0);
        EdgeSetOrigin      (SYSCLKstrobeWF,Edge1,orgclkoutef);
        EdgeSetOrigin      (SYSCLKstrobeWF,Edge2,orgclkoutef);
        EdgeSetOrigin      (SYSCLKstrobeWF,Edge3,orgclkoutef);
        EdgeSetOrigin      (SYSCLKstrobeWF,Edge4,orgclkouter);
        EdgeSetOrigin      (SYSCLKstrobeWF,Edge5,orgclkouter);

        EdgeSetDelay       (WDCLKstrobeWF,Edge1,DriveOff,t[tref],0);
        EdgeSetDelayData   (WDCLKstrobeWF,Edge2,ChanFirst,    
                                StrobeLow,ThreshVITL,           
                                t[tref]+t[tQ]-4ns,0,
                                StrobeHigh,ThreshVITL,
                                t[tref]+t[tQ]-4ns,0);
        EdgeSetDelayData   (WDCLKstrobeWF,Edge3,ChanFirst,    
                                StrobeOffLow,ThreshVITL,                
                                t[tref]+t[tQ]+0ns,0,
                                StrobeOffHigh,ThreshVITL,
                                t[tref]+t[tQ]+0ns,0);
        EdgeSetDelayData   (WDCLKstrobeWF,Edge4,ChanSecond,   
                                StrobeLow,ThreshVITL,           
                                t[tref]+t[tH]+t[tQ]-4ns,0,
                                StrobeHigh,ThreshVITL,
                                t[tref]+t[tH]+t[tQ]-4ns,0);
        EdgeSetDelayData   (WDCLKstrobeWF,Edge5,ChanSecond,   
                                StrobeOffLow,ThreshVITL,                
                                t[tref]+t[tH]+t[tQ]+0ns,0,
                                StrobeOffHigh,ThreshVITL,
                                t[tref]+t[tH]+t[tQ]+0ns,0);
        EdgeSetOrigin      (WDCLKstrobeWF,Edge1,orgclkoutef);
        EdgeSetOrigin      (WDCLKstrobeWF,Edge2,orgclkoutef);
        EdgeSetOrigin      (WDCLKstrobeWF,Edge3,orgclkoutef);
        EdgeSetOrigin      (WDCLKstrobeWF,Edge4,orgclkouter);
        EdgeSetOrigin      (WDCLKstrobeWF,Edge5,orgclkouter);

        EdgeSet            (DBUSdriveWF,Edge1,DriveComplement,
                                t[tref]+t[tH]);
        EdgeSet            (DBUSdriveWF,Edge2,DriveData,
                                t[tref]+t[tH]+7ns);
        EdgeSetOrigin      (DBUSdriveWF,Edge1,orgclkoutll);
        EdgeSetOrigin      (DBUSdriveWF,Edge2,orgclkoutel);

        WaveSetStrobe      (DBUSstrobeWF,
                                t[tref]+t[tH],
                                t[tref]+t[tper]-14ns,
                                t[tref]+t[tper]-10ns);
        EdgeSetOrigin      (DBUSstrobeWF,Edge1,orgclkouter);
        EdgeSetOrigin      (DBUSstrobeWF,Edge2,orgclkouter);
        EdgeSetOrigin      (DBUSstrobeWF,Edge3,orgclkouter);

        EdgeSet            (xDBUSRDdriveWF,Edge1,DriveComplement,
                                t[tref]+t[tH]);
        EdgeSet            (xDBUSRDdriveWF,Edge2,DriveData,
                                t[tref]+t[tH]+7ns);
        EdgeSetOrigin      (xDBUSRDdriveWF,Edge1,orgclkoutll);
        EdgeSetOrigin      (xDBUSRDdriveWF,Edge2,orgclkoutel);

        EdgeSet            (xDBUSWRdriveWF,Edge1,DriveComplement,
                                t[tref]+t[tH]);
        EdgeSet            (xDBUSWRdriveWF,Edge2,DriveData,
                                t[tref]+t[tH]+7ns);
        EdgeSetOrigin      (xDBUSWRdriveWF,Edge1,orgclkoutll);
        EdgeSetOrigin      (xDBUSWRdriveWF,Edge2,orgclkoutel);

        WaveSetStrobe      (xDBUSWRstrobeWF,
                                t[tref]-5ns,
                                t[tref]+t[tper]-14ns,
                                t[tref]+t[tper]-10ns);
        EdgeSetOrigin      (xDBUSWRstrobeWF,Edge1,orgclkoutef);
        EdgeSetOrigin      (xDBUSWRstrobeWF,Edge2,orgclkoutef);
        EdgeSetOrigin      (xDBUSWRstrobeWF,Edge3,orgclkoutef);

        EdgeSet            (GPIOFdriveWF,Edge1,DriveComplement,
                                t[tref]);
        EdgeSet            (GPIOFdriveWF,Edge2,DriveData,
                                t[tref]+7ns);
        EdgeSetOrigin      (GPIOFdriveWF,Edge1,orgclkoutlh);
        EdgeSetOrigin      (GPIOFdriveWF,Edge2,orgclkouteh);

        WaveSetStrobe      (GPIOFstrobeWF,
                                t[tref],
                                t[tref]+t[tper]-14ns,
                                t[tref]+t[tper]-10ns);
        EdgeSetOrigin      (GPIOFstrobeWF,Edge1,orgclkoutef);
        EdgeSetOrigin      (GPIOFstrobeWF,Edge2,orgclkoutef);
        EdgeSetOrigin      (GPIOFstrobeWF,Edge3,orgclkoutef);

        EdgeSet            (GPIOSdriveWF,Edge1,DriveComplement,
                                t[tref]);
        EdgeSet            (GPIOSdriveWF,Edge2,DriveData,
                                t[tref]+7ns);
        EdgeSetOrigin      (GPIOSdriveWF,Edge1,orgclkoutlh);
        EdgeSetOrigin      (GPIOSdriveWF,Edge2,orgclkouteh);

        WaveSetStrobe      (GPIOSstrobeWF,
                                t[tref],
                                t[tref]+t[tper]-14ns,
                                t[tref]+t[tper]-10ns);
        EdgeSetOrigin      (GPIOSstrobeWF,Edge1,orgclkoutlf);
        EdgeSetOrigin      (GPIOSstrobeWF,Edge2,orgclkoutlf);
        EdgeSetOrigin      (GPIOSstrobeWF,Edge3,orgclkoutlf);

        EdgeSet            (INTNdriveWF,Edge1,DriveHigh,
                                t[tref]);
        EdgeSet            (INTNdriveWF,Edge2,DriveData,
                                t[tref]+7ns);
        EdgeSetOrigin      (INTNdriveWF,Edge1,orgclkoutlh);
        EdgeSetOrigin      (INTNdriveWF,Edge2,orgclkouteh);

  (* MPMC *)

        WaveSetNR          (MPMCNdriveWF,t[tref]+t[tH]-t[tH]);
        EdgeSetOrigin      (MPMCNdriveWF,Edge1,orgclkoutlh);

(* removed this WF to avoid glitches on PSN and STRBN *)
{
        EdgeSet            (MPMCNdriveWF,Edge1,DriveHigh,
                                t[tref]);
        EdgeSet            (MPMCNdriveWF,Edge2,DriveData,
                                t[tref]+7ns);
        EdgeSetOrigin      (MPMCNdriveWF,Edge1,orgclkoutlh);
        EdgeSetOrigin      (MPMCNdriveWF,Edge2,orgclkouteh);
}
        EdgeSet            (NMINdriveWF,Edge1,DriveHigh,
                                t[tref]);
        EdgeSet            (NMINdriveWF,Edge2,DriveData,
                                t[tref]+7ns);
        EdgeSetOrigin      (NMINdriveWF,Edge1,orgclkoutlh);
        EdgeSetOrigin      (NMINdriveWF,Edge2,orgclkouteh);

        EdgeSet            (PDPINTdriveWF,Edge1,DriveHigh,
                                t[tref]+t[tH]);
        EdgeSet            (PDPINTdriveWF,Edge2,DriveData,
                                t[tref]+t[tH]+7ns);
        EdgeSetOrigin      (PDPINTdriveWF,Edge1,orgclkoutll);
        EdgeSetOrigin      (PDPINTdriveWF,Edge2,orgclkoutel);

        WaveSetStrobe      (PWMstrobeWF,
                                t[tref]+t[tH]-5ns,
                                t[tref]+t[tH]+t[tper]-14ns,
                                t[tref]+t[tH]+t[tper]-10ns);
        EdgeSetOrigin      (PWMstrobeWF,Edge1,orgclkouter);
        EdgeSetOrigin      (PWMstrobeWF,Edge2,orgclkouter);
        EdgeSetOrigin      (PWMstrobeWF,Edge3,orgclkouter);

        WaveSetStrobe      (RDNLstrobeWF,
                                t[tref]-5ns,
                                t[tref]+t[tH]+t[tH]-14ns,
                                t[tref]+t[tH]+t[tH]-10ns);
        EdgeSetOrigin      (RDNLstrobeWF,Edge1,orgclkoutef);
        EdgeSetOrigin      (RDNLstrobeWF,Edge2,orgclkoutef);
        EdgeSetOrigin      (RDNLstrobeWF,Edge3,orgclkoutef);

        WaveSetStrobe      (RDNHstrobeWF,
                                t[tref]-5ns,
                                t[tref]+t[tH]+t[tH]-14ns,
                                t[tref]+t[tH]+t[tH]-10ns);
        EdgeSetOrigin      (RDNHstrobeWF,Edge1,orgclkoutef);
        EdgeSetOrigin      (RDNHstrobeWF,Edge2,orgclkoutef);
        EdgeSetOrigin      (RDNHstrobeWF,Edge3,orgclkoutef);

        WaveSetStrobe      (xRDNFstrobeWF,
                                t[tref]-5ns,
                                t[tref]+t[tH]+t[tH]-14ns, 
                                t[tref]+t[tH]+t[tH]-10ns);
        EdgeSetOrigin      (xRDNFstrobeWF,Edge1,orgclkoutef);
        EdgeSetOrigin      (xRDNFstrobeWF,Edge2,orgclkoutef);
        EdgeSetOrigin      (xRDNFstrobeWF,Edge3,orgclkoutef);

        WaveSetStrobe      (xRDNLstrobeWF,
                                t[tref]-5ns,
                                t[tref]+t[tper]-14ns,
                                t[tref]+t[tper]-10ns);
        EdgeSetOrigin      (xRDNLstrobeWF,Edge1,orgclkoutef);
        EdgeSetOrigin      (xRDNLstrobeWF,Edge2,orgclkoutef);
        EdgeSetOrigin      (xRDNLstrobeWF,Edge3,orgclkoutef);

        WaveSetStrobe      (xRDNRstrobeWF,
                                t[tref]-5ns,
                                t[tref]+t[tH]+t[tH]-14ns,
                                t[tref]+t[tH]+t[tH]-10ns);
        EdgeSetOrigin      (xRDNRstrobeWF,Edge1,orgclkoutef);
        EdgeSetOrigin      (xRDNRstrobeWF,Edge2,orgclkoutef);
        EdgeSetOrigin      (xRDNRstrobeWF,Edge3,orgclkoutef);

        EdgeSet            (READYdriveWF,Edge1,DriveHigh,
                                t[tref]);
        EdgeSet            (READYdriveWF,Edge2,DriveData,
                                t[tref]+7ns);
        EdgeSetOrigin      (READYdriveWF,Edge1,orgclkoutlh);
        EdgeSetOrigin      (READYdriveWF,Edge2,orgclkouteh);

        WaveSetStrobe      (RNWLstrobeWF,
                                t[tref]+t[tH]-5ns,
                                t[tref]+t[tH]+t[tper]-14ns,
                                t[tref]+t[tH]+t[tper]-10ns);
        EdgeSetOrigin      (RNWLstrobeWF,Edge1,orgclkouter);
        EdgeSetOrigin      (RNWLstrobeWF,Edge2,orgclkouter);
        EdgeSetOrigin      (RNWLstrobeWF,Edge3,orgclkouter);

        WaveSetStrobe      (RNWHstrobeWF,
                                t[tref]+t[tH]-5ns,
                                t[tref]+t[tH]+t[tper]-14ns,
                                t[tref]+t[tH]+t[tper]-10ns);
        EdgeSetOrigin      (RNWHstrobeWF,Edge1,orgclkouter);
        EdgeSetOrigin      (RNWHstrobeWF,Edge2,orgclkouter);
        EdgeSetOrigin      (RNWHstrobeWF,Edge3,orgclkouter);

        WaveSetStrobe      (xRNWFstrobeWF,
                                t[tref]+t[tH]-5ns,
                                t[tref]+t[tH]+t[tper]-14ns,
                                t[tref]+t[tH]+t[tper]-10ns);
        EdgeSetOrigin      (xRNWFstrobeWF,Edge1,orgclkouter);
        EdgeSetOrigin      (xRNWFstrobeWF,Edge2,orgclkouter);
        EdgeSetOrigin      (xRNWFstrobeWF,Edge3,orgclkouter);

        WaveSetStrobe      (xRNWLstrobeWF,
                                t[tref]+t[tH]-5ns,
                                t[tref]+t[tH]+t[tper]-14ns,
                                t[tref]+t[tH]+t[tper]-10ns);
        EdgeSetOrigin      (xRNWLstrobeWF,Edge1,orgclkouter);
        EdgeSetOrigin      (xRNWLstrobeWF,Edge2,orgclkouter);
        EdgeSetOrigin      (xRNWLstrobeWF,Edge3,orgclkouter);

        WaveSetStrobe      (xRNWRstrobeWF,
                                t[tref]+t[tH]-5ns,
                                t[tref]+t[tH]+t[tper]-14ns,
                                t[tref]+t[tH]+t[tper]-10ns);
        EdgeSetOrigin      (xRNWRstrobeWF,Edge1,orgclkouter);
        EdgeSetOrigin      (xRNWRstrobeWF,Edge2,orgclkouter);
        EdgeSetOrigin      (xRNWRstrobeWF,Edge3,orgclkouter);

        WaveSetNR          (RSNdriveLWF,t[tref]+t[tper]-t[tH]);
        EdgeSetOrigin      (RSNdriveLWF,Edge1,orgclkoutll);

        WaveSetNR          (RSNdriveHWF,t[tref]);
        EdgeSetOrigin      (RSNdriveHWF,Edge1,orgclkoutll);

        WaveSetStrobe      (RSNstrobeWF,
                                t[tref]-5ns,
                                t[tref]+t[tper]-14ns,
                                t[tref]+t[tper]-10ns);
        EdgeSetOrigin      (RSNstrobeWF,Edge1,orgclkoutef);
        EdgeSetOrigin      (RSNstrobeWF,Edge2,orgclkoutef);
        EdgeSetOrigin      (RSNstrobeWF,Edge3,orgclkoutef);

        EdgeSet            (SCIRXDdriveWF,Edge1,DriveComplement,
                                t[tref]);
        EdgeSet            (SCIRXDdriveWF,Edge2,DriveData,
                                t[tref]+7ns);
        EdgeSetOrigin      (SCIRXDdriveWF,Edge1,orgclkoutlh);
        EdgeSetOrigin      (SCIRXDdriveWF,Edge2,orgclkouteh);

        WaveSetStrobe      (SCITXDstrobeWF,
                                t[tref]-5ns,
                                t[tref]+t[tper]-14ns,
                                t[tref]+t[tper]-10ns);
        EdgeSetOrigin      (SCITXDstrobeWF,Edge1,orgclkoutef);
        EdgeSetOrigin      (SCITXDstrobeWF,Edge2,orgclkoutef);
        EdgeSetOrigin      (SCITXDstrobeWF,Edge3,orgclkoutef);

        EdgeSet            (SPICLKdriveWF,Edge1,DriveComplement,
                                t[tref]);
        EdgeSet            (SPICLKdriveWF,Edge2,DriveData,
                                t[tref]+7ns);
        EdgeSetOrigin      (SPICLKdriveWF,Edge1,orgclkoutlh);
        EdgeSetOrigin      (SPICLKdriveWF,Edge2,orgclkouteh);

        WaveSetStrobe      (SPICLKstrobeWF,
                                t[tref]-5ns,
                                t[tref]+t[tper]-14ns,
                                t[tref]+t[tper]-10ns);
        EdgeSetOrigin      (SPICLKstrobeWF,Edge1,orgclkoutef);
        EdgeSetOrigin      (SPICLKstrobeWF,Edge2,orgclkoutef);
        EdgeSetOrigin      (SPICLKstrobeWF,Edge3,orgclkoutef);

        EdgeSet            (SPISIMOdriveWF,Edge1,DriveComplement,
                                t[tref]);
        EdgeSet            (SPISIMOdriveWF,Edge2,DriveData,
                                t[tref]+7ns);
        EdgeSetOrigin      (SPISIMOdriveWF,Edge1,orgclkoutlh);
        EdgeSetOrigin      (SPISIMOdriveWF,Edge2,orgclkouteh);

        WaveSetStrobe      (SPISIMOstrobeWF,
                                t[tref]-5ns,
                                t[tref]+t[tper]-14ns,
                                t[tref]+t[tper]-10ns);
        EdgeSetOrigin      (SPISIMOstrobeWF,Edge1,orgclkoutef);
        EdgeSetOrigin      (SPISIMOstrobeWF,Edge2,orgclkoutef);
        EdgeSetOrigin      (SPISIMOstrobeWF,Edge3,orgclkoutef);

        EdgeSet            (SPISOMIdriveWF,Edge1,DriveComplement,
                                t[tref]);
        EdgeSet            (SPISOMIdriveWF,Edge2,DriveData,
                                t[tref]+7ns);
        EdgeSetOrigin      (SPISOMIdriveWF,Edge1,orgclkoutlh);
        EdgeSetOrigin      (SPISOMIdriveWF,Edge2,orgclkouteh);

        WaveSetStrobe      (SPISOMIstrobeWF,
                                t[tref]-5ns,
                                t[tref]+t[tper]-14ns,
                                t[tref]+t[tper]-10ns);
        EdgeSetOrigin      (SPISOMIstrobeWF,Edge1,orgclkoutef);
        EdgeSetOrigin      (SPISOMIstrobeWF,Edge2,orgclkoutef);
        EdgeSetOrigin      (SPISOMIstrobeWF,Edge3,orgclkoutef);

        EdgeSet            (SPISTEdriveWF,Edge1,DriveHigh,
                                t[tref]);
        EdgeSet            (SPISTEdriveWF,Edge2,DriveData,
                                t[tref]+7ns);
        EdgeSetOrigin      (SPISTEdriveWF,Edge1,orgclkoutlh);
        EdgeSetOrigin      (SPISTEdriveWF,Edge2,orgclkouteh);

        WaveSetStrobe      (STRBNLstrobeWF,
                                t[tref]-5ns,
                                t[tref]+t[tper]-14ns,
                                t[tref]+t[tper]-10ns);
        EdgeSetOrigin      (STRBNLstrobeWF,Edge1,orgclkoutef);
        EdgeSetOrigin      (STRBNLstrobeWF,Edge2,orgclkoutef);
        EdgeSetOrigin      (STRBNLstrobeWF,Edge3,orgclkoutef);

        WaveSetStrobe      (STRBNHstrobeWF,
                                t[tref]-5ns,
                                t[tref]+t[tper]-14ns,
                                t[tref]+t[tper]-10ns);
        EdgeSetOrigin      (STRBNHstrobeWF,Edge1,orgclkoutef);
        EdgeSetOrigin      (STRBNHstrobeWF,Edge2,orgclkoutef);
        EdgeSetOrigin      (STRBNHstrobeWF,Edge3,orgclkoutef);

        WaveSetStrobe      (xSTRBNFstrobeWF,
                                t[tref]-5ns,
                                t[tref]+t[tper]-14ns,
                                t[tref]+t[tper]-10ns);
        EdgeSetOrigin      (xSTRBNFstrobeWF,Edge1,orgclkoutef);
        EdgeSetOrigin      (xSTRBNFstrobeWF,Edge2,orgclkoutef);
        EdgeSetOrigin      (xSTRBNFstrobeWF,Edge3,orgclkoutef);

        WaveSetStrobe      (xSTRBNLstrobeWF,
                                t[tref]-5ns,
                                t[tref]+t[tper]-14ns,
                                t[tref]+t[tper]-10ns);
        EdgeSetOrigin      (xSTRBNLstrobeWF,Edge1,orgclkoutef);
        EdgeSetOrigin      (xSTRBNLstrobeWF,Edge2,orgclkoutef);
        EdgeSetOrigin      (xSTRBNLstrobeWF,Edge3,orgclkoutef);

        WaveSetStrobe      (xSTRBNRstrobeWF,
                                t[tref]-5ns,
                                t[tref]+t[tper]-14ns,
                                t[tref]+t[tper]-10ns);
        EdgeSetOrigin      (xSTRBNRstrobeWF,Edge1,orgclkoutef);
        EdgeSetOrigin      (xSTRBNRstrobeWF,Edge2,orgclkoutef);
        EdgeSetOrigin      (xSTRBNRstrobeWF,Edge3,orgclkoutef);

        EdgeSet            (TMRCLKdriveWF,Edge1,DriveComplement,
                                t[tref]+t[tH]);
        EdgeSet            (TMRCLKdriveWF,Edge2,DriveData,
                                t[tref]+t[tH]+7ns);
        EdgeSetOrigin      (TMRCLKdriveWF,Edge1,orgclkoutll);
        EdgeSetOrigin      (TMRCLKdriveWF,Edge2,orgclkoutel);

        EdgeSet            (TMRDIRdriveWF,Edge1,DriveComplement,
                                t[tref]+t[tH]);
        EdgeSet            (TMRDIRdriveWF,Edge2,DriveData,
                                t[tref]+t[tH]+7ns);
        EdgeSetOrigin      (TMRDIRdriveWF,Edge1,orgclkoutll);
        EdgeSetOrigin      (TMRDIRdriveWF,Edge2,orgclkoutel);

        WaveSetStrobe      (WENLstrobeWF,
                                t[tref]-5ns,
                                t[tref]+t[tper]-14ns,
                                t[tref]+t[tper]-10ns);
        EdgeSetOrigin      (WENLstrobeWF,Edge1,orgclkoutef);
        EdgeSetOrigin      (WENLstrobeWF,Edge2,orgclkoutef);
        EdgeSetOrigin      (WENLstrobeWF,Edge3,orgclkoutef);

        WaveSetStrobe      (WENHstrobeWF,
                                t[tref]-5ns,
                                t[tref]+t[tper]-14ns,
                                t[tref]+t[tper]-10ns);
        EdgeSetOrigin      (WENHstrobeWF,Edge1,orgclkoutef);
        EdgeSetOrigin      (WENHstrobeWF,Edge2,orgclkoutef);
        EdgeSetOrigin      (WENHstrobeWF,Edge3,orgclkoutef);

        WaveSetStrobe      (xWENFstrobeWF,
                                t[tref]-5ns,
                                t[tref]+t[tper]-14ns,
                                t[tref]+t[tper]-10ns);
        EdgeSetOrigin      (xWENFstrobeWF,Edge1,orgclkoutef);
        EdgeSetOrigin      (xWENFstrobeWF,Edge2,orgclkoutef);
        EdgeSetOrigin      (xWENFstrobeWF,Edge3,orgclkoutef);

        WaveSetStrobe      (xWENLstrobeWF,
                                t[tref]-5ns,
                                t[tref]+t[tper]-14ns,
                                t[tref]+t[tper]-10ns);
        EdgeSetOrigin      (xWENLstrobeWF,Edge1,orgclkoutef);
        EdgeSetOrigin      (xWENLstrobeWF,Edge2,orgclkoutef);
        EdgeSetOrigin      (xWENLstrobeWF,Edge3,orgclkoutef);

        WaveSetStrobe      (xWENRstrobeWF,
                                t[tref]-5ns,
                                t[tref]+t[tper]-14ns,
                                t[tref]+t[tper]-10ns);
        EdgeSetOrigin      (xWENRstrobeWF,Edge1,orgclkoutef);
        EdgeSetOrigin      (xWENRstrobeWF,Edge2,orgclkoutef);
        EdgeSetOrigin      (xWENRstrobeWF,Edge3,orgclkoutef);

        WaveSetStrobe      (XFstrobeWF,
                                t[tref]+t[tH]-5ns,
                                t[tref]+t[tH]+t[tper]-14ns,
                                t[tref]+t[tH]+t[tper]-10ns);
        EdgeSetOrigin      (XFstrobeWF,Edge1,orgclkouter);
        EdgeSetOrigin      (XFstrobeWF,Edge2,orgclkouter);
        EdgeSetOrigin      (XFstrobeWF,Edge3,orgclkouter);

        WaveSetStrobe      (XTAL2strobeWF, 
                                t[tref]+t[tH], 
                                t[tref]+t[tH]+t[tper]-14ns,
                                t[tref]+t[tH]+t[tper]-10ns);
        EdgeSetOrigin      (XTAL2strobeWF,Edge1,orgclkin);
        EdgeSetOrigin      (XTAL2strobeWF,Edge2,orgclkin);
        EdgeSetOrigin      (XTAL2strobeWF,Edge3,orgclkin);
    end;  (* end loose AC Tables *)

  TIsearchlooseACTable2:
    begin
        WaveSetNR          (ABUSdriveWF,t[tref]+t[tH]);
        EdgeSetOrigin      (ABUSdriveWF,Edge1,orgclkoutll);

        WaveSetStrobe      (ABUSRDstrobeWF,
                                t[tref]+t[tH],
                                t[tref]+t[tper]-14ns,
                                t[tref]+t[tper]-10ns);
        EdgeSetOrigin      (ABUSRDstrobeWF,Edge1,orgclkoutef);
        EdgeSetOrigin      (ABUSRDstrobeWF,Edge2,orgclkoutef);
        EdgeSetOrigin      (ABUSRDstrobeWF,Edge3,orgclkoutef);

{       EdgeSet            (ABUSRDstrobeWF,Edge1,DriveOff,
                                t[tref]+t[tH]);
        EdgeSetOrigin      (ABUSRDstrobeWF,Edge1,orgclkoutef);
}
        WaveSetStrobe      (xABUSRDstrobeWF,
                                t[tref],
                                t[tref]+30ns,
                                t[tref]+t[tper]-10ns);
        EdgeSetOrigin      (xABUSRDstrobeWF,Edge1,orgclkoutef);
        EdgeSetOrigin      (xABUSRDstrobeWF,Edge2,orgclkoutef);
        EdgeSetOrigin      (xABUSRDstrobeWF,Edge3,orgclkoutef);

        WaveSetStrobe      (ABUSWRstrobeWF,
                                t[tref]+t[tH],
                                t[tref]+t[tper]-14ns,
                                t[tref]+t[tper]-10ns);
        EdgeSetOrigin      (ABUSWRstrobeWF,Edge1,orgclkouter);
        EdgeSetOrigin      (ABUSWRstrobeWF,Edge2,orgclkouter);
        EdgeSetOrigin      (ABUSWRstrobeWF,Edge3,orgclkouter);

{       EdgeSet            (ABUSWRstrobeWF,Edge1,DriveOff,
                                t[tref]+t[tH]);
        EdgeSetOrigin      (ABUSWRstrobeWF,Edge1,orgclkouter);
}
        WaveSetStrobe      (xABUSWRstrobeWF,
                                t[tref]+t[tH],
                                t[tref]+t[tH]+30ns,
                                t[tref]+t[tH]+t[tper]-10ns);
        EdgeSetOrigin      (xABUSWRstrobeWF,Edge1,orgclkouter);
        EdgeSetOrigin      (xABUSWRstrobeWF,Edge2,orgclkouter);
        EdgeSetOrigin      (xABUSWRstrobeWF,Edge3,orgclkouter);

        WaveSetStrobe      (ACTRLstrobeWF,
                                t[tref]+t[tH],
                                t[tref]+t[tH]+10ns,
                                t[tref]+t[tper]-10ns);
        EdgeSetOrigin      (ACTRLstrobeWF,Edge1,orgclkouter);
        EdgeSetOrigin      (ACTRLstrobeWF,Edge2,orgclkouter);
        EdgeSetOrigin      (ACTRLstrobeWF,Edge3,orgclkouter);

        WaveSetStrobe      (xACTRLFRDstrobeWF,
                                t[tref]+t[tH],
                                t[tref]+t[tH]+10ns,
                                t[tref]+t[tper]-10ns);
        EdgeSetOrigin      (xACTRLFRDstrobeWF,Edge1,orgclkoutef);
        EdgeSetOrigin      (xACTRLFRDstrobeWF,Edge2,orgclkoutef);
        EdgeSetOrigin      (xACTRLFRDstrobeWF,Edge3,orgclkoutef);

        WaveSetStrobe      (xACTRLLRDstrobeWF,
                                t[tref],
                                t[tref]+30ns,
                                t[tref]+t[tper]-10ns);
        EdgeSetOrigin      (xACTRLLRDstrobeWF,Edge1,orgclkoutef);
        EdgeSetOrigin      (xACTRLLRDstrobeWF,Edge2,orgclkoutef);
        EdgeSetOrigin      (xACTRLLRDstrobeWF,Edge3,orgclkoutef);

        WaveSetStrobe      (xACTRLRRDstrobeWF,
                                t[tref],
                                t[tref]+30ns,
                                t[tref]+t[tper]-10ns);
        EdgeSetOrigin      (xACTRLRRDstrobeWF,Edge1,orgclkoutef);
        EdgeSetOrigin      (xACTRLRRDstrobeWF,Edge2,orgclkoutef);
        EdgeSetOrigin      (xACTRLRRDstrobeWF,Edge3,orgclkoutef);

        WaveSetStrobe      (xACTRLFWRstrobeWF,
                                t[tref]+t[tH],
                                t[tref]+t[tH]+10ns,
                                t[tref]+t[tper]-10ns);
        EdgeSetOrigin      (xACTRLFWRstrobeWF,Edge1,orgclkouter);
        EdgeSetOrigin      (xACTRLFWRstrobeWF,Edge2,orgclkouter);
        EdgeSetOrigin      (xACTRLFWRstrobeWF,Edge3,orgclkouter);

        WaveSetStrobe      (xACTRLLWRstrobeWF,
                                t[tref]+t[tH],
                                t[tref]+t[tH]+30ns,
                                t[tref]+t[tH]+t[tper]-10ns);
        EdgeSetOrigin      (xACTRLLWRstrobeWF,Edge1,orgclkouter);
        EdgeSetOrigin      (xACTRLLWRstrobeWF,Edge2,orgclkouter);
        EdgeSetOrigin      (xACTRLLWRstrobeWF,Edge3,orgclkouter);

        WaveSetStrobe      (xACTRLRWRstrobeWF,
                                t[tref]+t[tH],
                                t[tref]+t[tH]+30ns,
                                t[tref]+t[tH]+t[tper]-10ns);
        EdgeSetOrigin      (xACTRLRWRstrobeWF,Edge1,orgclkouter);
        EdgeSetOrigin      (xACTRLRWRstrobeWF,Edge2,orgclkouter);
        EdgeSetOrigin      (xACTRLRWRstrobeWF,Edge3,orgclkouter);

        EdgeSet            (BIONdriveWF,Edge1,DriveData,
                                t[tref]+t[tH]);
        EdgeSet            (BIONdriveWF,Edge2,DriveHigh,
                                t[tref]+t[tH]+t[tper]-7ns);
        EdgeSetOrigin      (BIONdriveWF,Edge1,orgclkoutll);
        EdgeSetOrigin      (BIONdriveWF,Edge2,orgclkoutel);

        WaveSetStrobe      (BRNstrobeWF,
                                t[tref]+t[tH],
                                t[tref]+t[tH]+10ns,
                                t[tref]+t[tper]-10ns);
        EdgeSetOrigin      (BRNstrobeWF,Edge1,orgclkouter);
        EdgeSetOrigin      (BRNstrobeWF,Edge2,orgclkouter);
        EdgeSetOrigin      (BRNstrobeWF,Edge3,orgclkouter);

        WaveSetStrobe      (xBRNFRDstrobeWF,
                                t[tref]+t[tH],
                                t[tref]+t[tH]+10ns,
                                t[tref]+t[tper]-10ns);
        EdgeSetOrigin      (xBRNFRDstrobeWF,Edge1,orgclkoutef);
        EdgeSetOrigin      (xBRNFRDstrobeWF,Edge2,orgclkoutef);
        EdgeSetOrigin      (xBRNFRDstrobeWF,Edge3,orgclkoutef);

        WaveSetStrobe      (xBRNLRDstrobeWF,
                                t[tref],
                                t[tref]+30ns,
                                t[tref]+t[tper]-10ns);
        EdgeSetOrigin      (xBRNLRDstrobeWF,Edge1,orgclkoutef);
        EdgeSetOrigin      (xBRNLRDstrobeWF,Edge2,orgclkoutef);
        EdgeSetOrigin      (xBRNLRDstrobeWF,Edge3,orgclkoutef);

        WaveSetStrobe      (xBRNRRDstrobeWF,
                                t[tref],
                                t[tref]+30ns,
                                t[tref]+t[tper]-10ns);
        EdgeSetOrigin      (xBRNRRDstrobeWF,Edge1,orgclkoutef);
        EdgeSetOrigin      (xBRNRRDstrobeWF,Edge2,orgclkoutef);
        EdgeSetOrigin      (xBRNRRDstrobeWF,Edge3,orgclkoutef);

        WaveSetStrobe      (xBRNFWRstrobeWF,
                                t[tref]+t[tH],
                                t[tref]+t[tH]+10ns,
                                t[tref]+t[tper]-10ns);
        EdgeSetOrigin      (xBRNFWRstrobeWF,Edge1,orgclkouter);
        EdgeSetOrigin      (xBRNFWRstrobeWF,Edge2,orgclkouter);
        EdgeSetOrigin      (xBRNFWRstrobeWF,Edge3,orgclkouter);

        WaveSetStrobe      (xBRNLWRstrobeWF,
                                t[tref]+t[tH],
                                t[tref]+t[tH]+30ns,
                                t[tref]+t[tH]+t[tper]-10ns);
        EdgeSetOrigin      (xBRNLWRstrobeWF,Edge1,orgclkouter);
        EdgeSetOrigin      (xBRNLWRstrobeWF,Edge2,orgclkouter);
        EdgeSetOrigin      (xBRNLWRstrobeWF,Edge3,orgclkouter);

        WaveSetStrobe      (xBRNRWRstrobeWF,
                                t[tref]+t[tH],
                                t[tref]+t[tH]+30ns,
                                t[tref]+t[tH]+t[tper]-10ns);
        EdgeSetOrigin      (xBRNRWRstrobeWF,Edge1,orgclkouter);
        EdgeSetOrigin      (xBRNRWRstrobeWF,Edge2,orgclkouter);
        EdgeSetOrigin      (xBRNRWRstrobeWF,Edge3,orgclkouter);

        EdgeSet            (CAPdriveWF,Edge1,DriveData,
                                t[tref]+t[tH]);
        EdgeSet            (CAPdriveWF,Edge2,DriveComplement,
                                t[tref]+t[tH]+t[tper]-7ns);
        EdgeSetOrigin      (CAPdriveWF,Edge1,orgclkoutll);
        EdgeSetOrigin      (CAPdriveWF,Edge2,orgclkoutel);

        EdgeSetDelay       (CLKOUT1strobeWF,Edge1,DriveOff,t[tref]+10ns,0);
        EdgeSetDelayData   (CLKOUT1strobeWF,Edge2,ChanFirst,    
                                StrobeLow,ThreshVITL,           
                                t[tref]+t[tQ]-0ns,0,
                                StrobeHigh,ThreshVITL,
                                t[tref]+t[tQ]-0ns,0);
        EdgeSetDelayData   (CLKOUT1strobeWF,Edge3,ChanFirst,    
                                StrobeOffLow,ThreshVITL,                
                                t[tref]+t[tQ]+4ns,0,
                                StrobeOffHigh,ThreshVITL,
                                t[tref]+t[tQ]+4ns,0);
        EdgeSetDelayData   (CLKOUT1strobeWF,Edge4,ChanSecond,   
                                StrobeLow,ThreshVITL,           
                                t[tref]+t[tH]+t[tQ]-0ns,0,
                                StrobeHigh,ThreshVITL,
                                t[tref]+t[tH]+t[tQ]-0ns,0);
        EdgeSetDelayData   (CLKOUT1strobeWF,Edge5,ChanSecond,   
                                StrobeOffLow,ThreshVITL,                
                                t[tref]+t[tH]+t[tQ]+4ns,0,
                                StrobeOffHigh,ThreshVITL,
                                t[tref]+t[tH]+t[tQ]+4ns,0);
        EdgeSetOrigin      (CLKOUT1strobeWF,Edge1,orgclkoutef);
        EdgeSetOrigin      (CLKOUT1strobeWF,Edge2,orgclkoutef);
        EdgeSetOrigin      (CLKOUT1strobeWF,Edge3,orgclkoutef);
        EdgeSetOrigin      (CLKOUT1strobeWF,Edge4,orgclkouter);
        EdgeSetOrigin      (CLKOUT1strobeWF,Edge5,orgclkouter);

        EdgeSetDelay       (SYSCLKstrobeWF,Edge1,DriveOff,t[tref],0);
        EdgeSetDelayData   (SYSCLKstrobeWF,Edge2,ChanFirst,    
                                StrobeLow,ThreshVITL,           
                                t[tref]+t[tQ]-0ns,0,
                                StrobeHigh,ThreshVITL,
                                t[tref]+t[tQ]-0ns,0);
        EdgeSetDelayData   (SYSCLKstrobeWF,Edge3,ChanFirst,    
                                StrobeOffLow,ThreshVITL,                
                                t[tref]+t[tQ]+4ns,0,
                                StrobeOffHigh,ThreshVITL,
                                t[tref]+t[tQ]+4ns,0);
        EdgeSetDelayData   (SYSCLKstrobeWF,Edge4,ChanSecond,   
                                StrobeLow,ThreshVITL,           
                                t[tref]+t[tH]+t[tQ]-0ns,0,
                                StrobeHigh,ThreshVITL,
                                t[tref]+t[tH]+t[tQ]-0ns,0);
        EdgeSetDelayData   (SYSCLKstrobeWF,Edge5,ChanSecond,   
                                StrobeOffLow,ThreshVITL,                
                                t[tref]+t[tH]+t[tQ]+4ns,0,
                                StrobeOffHigh,ThreshVITL,
                                t[tref]+t[tH]+t[tQ]+4ns,0);
        EdgeSetOrigin      (SYSCLKstrobeWF,Edge1,orgclkoutef);
        EdgeSetOrigin      (SYSCLKstrobeWF,Edge2,orgclkoutef);
        EdgeSetOrigin      (SYSCLKstrobeWF,Edge3,orgclkoutef);
        EdgeSetOrigin      (SYSCLKstrobeWF,Edge4,orgclkouter);
        EdgeSetOrigin      (SYSCLKstrobeWF,Edge5,orgclkouter);

        EdgeSetDelay       (WDCLKstrobeWF,Edge1,DriveOff,t[tref],0);
        EdgeSetDelayData   (WDCLKstrobeWF,Edge2,ChanFirst,    
                                StrobeLow,ThreshVITL,           
                                t[tref]+t[tQ]-0ns,0,
                                StrobeHigh,ThreshVITL,
                                t[tref]+t[tQ]-0ns,0);
        EdgeSetDelayData   (WDCLKstrobeWF,Edge3,ChanFirst,    
                                StrobeOffLow,ThreshVITL,                
                                t[tref]+t[tQ]+4ns,0,
                                StrobeOffHigh,ThreshVITL,
                                t[tref]+t[tQ]+4ns,0);
        EdgeSetDelayData   (WDCLKstrobeWF,Edge4,ChanSecond,   
                                StrobeLow,ThreshVITL,           
                                t[tref]+t[tH]+t[tQ]-0ns,0,
                                StrobeHigh,ThreshVITL,
                                t[tref]+t[tH]+t[tQ]-0ns,0);
        EdgeSetDelayData   (WDCLKstrobeWF,Edge5,ChanSecond,   
                                StrobeOffLow,ThreshVITL,                
                                t[tref]+t[tH]+t[tQ]+4ns,0,
                                StrobeOffHigh,ThreshVITL,
                                t[tref]+t[tH]+t[tQ]+4ns,0);
        EdgeSetOrigin      (WDCLKstrobeWF,Edge1,orgclkoutef);
        EdgeSetOrigin      (WDCLKstrobeWF,Edge2,orgclkoutef);
        EdgeSetOrigin      (WDCLKstrobeWF,Edge3,orgclkoutef);
        EdgeSetOrigin      (WDCLKstrobeWF,Edge4,orgclkouter);
        EdgeSetOrigin      (WDCLKstrobeWF,Edge5,orgclkouter);

        EdgeSet            (DBUSdriveWF,Edge1,DriveData,
                                t[tref]+t[tH]);
        EdgeSet            (DBUSdriveWF,Edge2,DriveComplement,
                                t[tref]+t[tH]+t[tper]-7ns);
        EdgeSetOrigin      (DBUSdriveWF,Edge1,orgclkoutll);
        EdgeSetOrigin      (DBUSdriveWF,Edge2,orgclkoutel);

        WaveSetStrobe      (DBUSstrobeWF,
                                t[tref]+t[tH],
                                t[tref]+t[tH]+10ns,
                                t[tref]+t[tper]-10ns);
        EdgeSetOrigin      (DBUSstrobeWF,Edge1,orgclkouter);
        EdgeSetOrigin      (DBUSstrobeWF,Edge2,orgclkouter);
        EdgeSetOrigin      (DBUSstrobeWF,Edge3,orgclkouter);

        EdgeSet            (xDBUSRDdriveWF,Edge1,DriveData,
                                t[tref]+t[tH]);
        EdgeSet            (xDBUSRDdriveWF,Edge2,DriveComplement,
                                t[tref]+t[tH]+t[tper]-7ns);
        EdgeSetOrigin      (xDBUSRDdriveWF,Edge1,orgclkoutll);
        EdgeSetOrigin      (xDBUSRDdriveWF,Edge2,orgclkoutel);

        EdgeSet            (xDBUSWRdriveWF,Edge1,DriveComplement,
                                t[tref]+t[tH]);
        EdgeSet            (xDBUSWRdriveWF,Edge2,DriveData,
                                t[tref]+t[tH]+7ns);
        EdgeSetOrigin      (xDBUSWRdriveWF,Edge1,orgclkoutll);
        EdgeSetOrigin      (xDBUSWRdriveWF,Edge2,orgclkoutel);

        WaveSetStrobe      (xDBUSWRstrobeWF,
                                t[tref],
                                t[tref]+30ns,
                                t[tref]+t[tper]-10ns);
        EdgeSetOrigin      (xDBUSWRstrobeWF,Edge1,orgclkoutef);
        EdgeSetOrigin      (xDBUSWRstrobeWF,Edge2,orgclkoutef);
        EdgeSetOrigin      (xDBUSWRstrobeWF,Edge3,orgclkoutef);

        EdgeSet            (GPIOFdriveWF,Edge1,DriveData,
                                t[tref]);
        EdgeSet            (GPIOFdriveWF,Edge2,DriveComplement,
                                t[tref]+t[tper]-7ns);
        EdgeSetOrigin      (GPIOFdriveWF,Edge1,orgclkoutlh);
        EdgeSetOrigin      (GPIOFdriveWF,Edge2,orgclkouteh);

        WaveSetStrobe      (GPIOFstrobeWF,
                                t[tref],
                                t[tref]+30ns,
                                t[tref]+t[tper]-10ns);
        EdgeSetOrigin      (GPIOFstrobeWF,Edge1,orgclkoutef);
        EdgeSetOrigin      (GPIOFstrobeWF,Edge2,orgclkoutef);
        EdgeSetOrigin      (GPIOFstrobeWF,Edge3,orgclkoutef);

        EdgeSet            (GPIOSdriveWF,Edge1,DriveData,
                                t[tref]);
        EdgeSet            (GPIOSdriveWF,Edge2,DriveComplement,
                                t[tref]+t[tper]-7ns);
        EdgeSetOrigin      (GPIOSdriveWF,Edge1,orgclkoutlh);
        EdgeSetOrigin      (GPIOSdriveWF,Edge2,orgclkouteh);

        WaveSetStrobe      (GPIOSstrobeWF,
                                t[tref],
                                t[tref]+30ns,
                                t[tref]+t[tper]-10ns);
        EdgeSetOrigin      (GPIOSstrobeWF,Edge1,orgclkoutlf);
        EdgeSetOrigin      (GPIOSstrobeWF,Edge2,orgclkoutlf);
        EdgeSetOrigin      (GPIOSstrobeWF,Edge3,orgclkoutlf);

        EdgeSet            (INTNdriveWF,Edge1,DriveData,
                                t[tref]);
        EdgeSet            (INTNdriveWF,Edge2,DriveHigh,
                                t[tref]+t[tper]-7ns);
        EdgeSetOrigin      (INTNdriveWF,Edge1,orgclkoutlh);
        EdgeSetOrigin      (INTNdriveWF,Edge2,orgclkouteh);

  (* MPMC *)

        WaveSetNR          (MPMCNdriveWF,t[tref]+t[tH]-t[tH]);
        EdgeSetOrigin      (MPMCNdriveWF,Edge1,orgclkoutlh);

(* removed this WF to avoid glitches on PSN and STRBN *)
{
        EdgeSet            (MPMCNdriveWF,Edge1,DriveData,
                                t[tref]);
        EdgeSet            (MPMCNdriveWF,Edge2,DriveHigh,
                                t[tref]+t[tper]-7ns);
        EdgeSetOrigin      (MPMCNdriveWF,Edge1,orgclkoutlh);
        EdgeSetOrigin      (MPMCNdriveWF,Edge2,orgclkouteh);
}
        EdgeSet            (NMINdriveWF,Edge1,DriveData,
                                t[tref]);
        EdgeSet            (NMINdriveWF,Edge2,DriveHigh,
                                t[tref]+t[tper]-7ns);
        EdgeSetOrigin      (NMINdriveWF,Edge1,orgclkoutlh);
        EdgeSetOrigin      (NMINdriveWF,Edge2,orgclkouteh);

        EdgeSet            (PDPINTdriveWF,Edge1,DriveData,
                                t[tref]+t[tH]);
        EdgeSet            (PDPINTdriveWF,Edge2,DriveHigh,
                                t[tref]+t[tH]+t[tper]-7ns);
        EdgeSetOrigin      (PDPINTdriveWF,Edge1,orgclkoutll);
        EdgeSetOrigin      (PDPINTdriveWF,Edge2,orgclkoutel);

        WaveSetStrobe      (PWMstrobeWF,
                                t[tref]+t[tH],
                                t[tref]+t[tH]+30ns,
                                t[tref]+t[tH]+t[tper]-10ns);
        EdgeSetOrigin      (PWMstrobeWF,Edge1,orgclkouter);
        EdgeSetOrigin      (PWMstrobeWF,Edge2,orgclkouter);
        EdgeSetOrigin      (PWMstrobeWF,Edge3,orgclkouter);

        WaveSetStrobe      (RDNLstrobeWF,
                                t[tref],
                                t[tref]+t[tH]+t[tH]-14ns,
                                t[tref]+t[tH]+t[tH]-10ns);
        EdgeSetOrigin      (RDNLstrobeWF,Edge1,orgclkoutef);
        EdgeSetOrigin      (RDNLstrobeWF,Edge2,orgclkoutef);
        EdgeSetOrigin      (RDNLstrobeWF,Edge3,orgclkoutef);

        WaveSetStrobe      (RDNHstrobeWF,
                                t[tref],
                                t[tref]+t[tH]+t[tH]-14ns,
                                t[tref]+t[tH]+t[tH]-10ns);
        EdgeSetOrigin      (RDNHstrobeWF,Edge1,orgclkoutef);
        EdgeSetOrigin      (RDNHstrobeWF,Edge2,orgclkoutef);
        EdgeSetOrigin      (RDNHstrobeWF,Edge3,orgclkoutef);

        WaveSetStrobe      (xRDNFstrobeWF,
                                t[tref],
                                t[tref]+t[tH]+t[tH]-14ns, 
                                t[tref]+t[tH]+t[tH]-10ns);
        EdgeSetOrigin      (xRDNFstrobeWF,Edge1,orgclkoutef);
        EdgeSetOrigin      (xRDNFstrobeWF,Edge2,orgclkoutef);
        EdgeSetOrigin      (xRDNFstrobeWF,Edge3,orgclkoutef);

        WaveSetStrobe      (xRDNLstrobeWF,
                                t[tref],
                                t[tref]+30ns,
                                t[tref]+t[tper]-10ns);
        EdgeSetOrigin      (xRDNLstrobeWF,Edge1,orgclkoutef);
        EdgeSetOrigin      (xRDNLstrobeWF,Edge2,orgclkoutef);
        EdgeSetOrigin      (xRDNLstrobeWF,Edge3,orgclkoutef);

        WaveSetStrobe      (xRDNRstrobeWF,
                                t[tref],
                                t[tref]+t[tH]+t[tH]-14ns,
                                t[tref]+t[tH]+t[tH]-10ns);
        EdgeSetOrigin      (xRDNRstrobeWF,Edge1,orgclkoutef);
        EdgeSetOrigin      (xRDNRstrobeWF,Edge2,orgclkoutef);
        EdgeSetOrigin      (xRDNRstrobeWF,Edge3,orgclkoutef);

        EdgeSet            (READYdriveWF,Edge1,DriveData,
                                t[tref]);
        EdgeSet            (READYdriveWF,Edge2,DriveHigh,
                                t[tref]+t[tper]-7ns);
        EdgeSetOrigin      (READYdriveWF,Edge1,orgclkoutlh);
        EdgeSetOrigin      (READYdriveWF,Edge2,orgclkouteh);

        WaveSetStrobe      (RNWLstrobeWF,
                                t[tref]+t[tH],
                                t[tref]+t[tH]+30ns,
                                t[tref]+t[tH]+t[tper]-12ns);
        EdgeSetOrigin      (RNWLstrobeWF,Edge1,orgclkouter);
        EdgeSetOrigin      (RNWLstrobeWF,Edge2,orgclkouter);
        EdgeSetOrigin      (RNWLstrobeWF,Edge3,orgclkouter);

        WaveSetStrobe      (RNWHstrobeWF,
                                t[tref]+t[tH],
                                t[tref]+t[tH]+30ns,
                                t[tref]+t[tH]+t[tper]-12ns);
        EdgeSetOrigin      (RNWHstrobeWF,Edge1,orgclkouter);
        EdgeSetOrigin      (RNWHstrobeWF,Edge2,orgclkouter);
        EdgeSetOrigin      (RNWHstrobeWF,Edge3,orgclkouter);

        WaveSetStrobe      (xRNWFstrobeWF,
                                t[tref]+t[tH],
                                t[tref]+t[tH]+30ns,
                                t[tref]+t[tH]+t[tper]-12ns);
        EdgeSetOrigin      (xRNWFstrobeWF,Edge1,orgclkouter);
        EdgeSetOrigin      (xRNWFstrobeWF,Edge2,orgclkouter);
        EdgeSetOrigin      (xRNWFstrobeWF,Edge3,orgclkouter);

        WaveSetStrobe      (xRNWLstrobeWF,
                                t[tref]+t[tH],
                                t[tref]+t[tH]+30ns,
                                t[tref]+t[tH]+t[tper]-12ns);
        EdgeSetOrigin      (xRNWLstrobeWF,Edge1,orgclkouter);
        EdgeSetOrigin      (xRNWLstrobeWF,Edge2,orgclkouter);
        EdgeSetOrigin      (xRNWLstrobeWF,Edge3,orgclkouter);

        WaveSetStrobe      (xRNWRstrobeWF,
                                t[tref]+t[tH],
                                t[tref]+t[tH]+30ns,
                                t[tref]+t[tH]+t[tper]-12ns);
        EdgeSetOrigin      (xRNWRstrobeWF,Edge1,orgclkouter);
        EdgeSetOrigin      (xRNWRstrobeWF,Edge2,orgclkouter);
        EdgeSetOrigin      (xRNWRstrobeWF,Edge3,orgclkouter);

        WaveSetNR          (RSNdriveLWF,t[tref]+t[tper]-t[tH]);
        EdgeSetOrigin      (RSNdriveLWF,Edge1,orgclkoutll);

        WaveSetNR          (RSNdriveHWF,t[tref]);
        EdgeSetOrigin      (RSNdriveHWF,Edge1,orgclkoutll);

        WaveSetStrobe      (RSNstrobeWF,
                                t[tref],
                                t[tref]+t[tper]-10ns-4ns,
                                t[tref]+t[tper]-10ns);
        EdgeSetOrigin      (RSNstrobeWF,Edge1,orgclkoutef);
        EdgeSetOrigin      (RSNstrobeWF,Edge2,orgclkoutef);
        EdgeSetOrigin      (RSNstrobeWF,Edge3,orgclkoutef);

        EdgeSet            (SCIRXDdriveWF,Edge1,DriveData,
                                t[tref]);
        EdgeSet            (SCIRXDdriveWF,Edge2,DriveComplement,
                                t[tref]+t[tper]-7ns);
        EdgeSetOrigin      (SCIRXDdriveWF,Edge1,orgclkoutlh);
        EdgeSetOrigin      (SCIRXDdriveWF,Edge2,orgclkouteh);

        WaveSetStrobe      (SCITXDstrobeWF,
                                t[tref],
                                t[tref]+30ns,
                                t[tref]+t[tper]-10ns);
        EdgeSetOrigin      (SCITXDstrobeWF,Edge1,orgclkoutef);
        EdgeSetOrigin      (SCITXDstrobeWF,Edge2,orgclkoutef);
        EdgeSetOrigin      (SCITXDstrobeWF,Edge3,orgclkoutef);

        EdgeSet            (SPICLKdriveWF,Edge1,DriveData,
                                t[tref]);
        EdgeSet            (SPICLKdriveWF,Edge2,DriveComplement,
                                t[tref]+t[tper]-7ns);
        EdgeSetOrigin      (SPICLKdriveWF,Edge1,orgclkoutlh);
        EdgeSetOrigin      (SPICLKdriveWF,Edge2,orgclkouteh);

        WaveSetStrobe      (SPICLKstrobeWF,
                                t[tref],
                                t[tref]+30ns,
                                t[tref]+t[tper]-10ns);
        EdgeSetOrigin      (SPICLKstrobeWF,Edge1,orgclkoutef);
        EdgeSetOrigin      (SPICLKstrobeWF,Edge2,orgclkoutef);
        EdgeSetOrigin      (SPICLKstrobeWF,Edge3,orgclkoutef);

        EdgeSet            (SPISIMOdriveWF,Edge1,DriveData,
                                t[tref]);
        EdgeSet            (SPISIMOdriveWF,Edge2,DriveComplement,
                                t[tref]+t[tper]-7ns);
        EdgeSetOrigin      (SPISIMOdriveWF,Edge1,orgclkoutlh);
        EdgeSetOrigin      (SPISIMOdriveWF,Edge2,orgclkouteh);

        WaveSetStrobe      (SPISIMOstrobeWF,
                                t[tref],
                                t[tref]+30ns,
                                t[tref]+t[tper]-10ns);
        EdgeSetOrigin      (SPISIMOstrobeWF,Edge1,orgclkoutef);
        EdgeSetOrigin      (SPISIMOstrobeWF,Edge2,orgclkoutef);
        EdgeSetOrigin      (SPISIMOstrobeWF,Edge3,orgclkoutef);

        EdgeSet            (SPISOMIdriveWF,Edge1,DriveData,
                                t[tref]);
        EdgeSet            (SPISOMIdriveWF,Edge2,DriveComplement,
                                t[tref]+t[tper]-7ns);
        EdgeSetOrigin      (SPISOMIdriveWF,Edge1,orgclkoutlh);
        EdgeSetOrigin      (SPISOMIdriveWF,Edge2,orgclkouteh);

        WaveSetStrobe      (SPISOMIstrobeWF,
                                t[tref],
                                t[tref]+30ns,
                                t[tref]+t[tper]-10ns);
        EdgeSetOrigin      (SPISOMIstrobeWF,Edge1,orgclkoutef);
        EdgeSetOrigin      (SPISOMIstrobeWF,Edge2,orgclkoutef);
        EdgeSetOrigin      (SPISOMIstrobeWF,Edge3,orgclkoutef);

        EdgeSet            (SPISTEdriveWF,Edge1,DriveData,
                                t[tref]);
        EdgeSet            (SPISTEdriveWF,Edge2,DriveHigh,
                                t[tref]+t[tper]-7ns);
        EdgeSetOrigin      (SPISTEdriveWF,Edge1,orgclkoutlh);
        EdgeSetOrigin      (SPISTEdriveWF,Edge2,orgclkouteh);

        WaveSetStrobe      (STRBNLstrobeWF,
                                t[tref],
                                t[tref]+30ns,
                                t[tref]+t[tper]-10ns);
        EdgeSetOrigin      (STRBNLstrobeWF,Edge1,orgclkoutef);
        EdgeSetOrigin      (STRBNLstrobeWF,Edge2,orgclkoutef);
        EdgeSetOrigin      (STRBNLstrobeWF,Edge3,orgclkoutef);

        WaveSetStrobe      (STRBNHstrobeWF,
                                t[tref],
                                t[tref]+30ns,
                                t[tref]+t[tper]-10ns);
        EdgeSetOrigin      (STRBNHstrobeWF,Edge1,orgclkoutef);
        EdgeSetOrigin      (STRBNHstrobeWF,Edge2,orgclkoutef);
        EdgeSetOrigin      (STRBNHstrobeWF,Edge3,orgclkoutef);

        WaveSetStrobe      (xSTRBNFstrobeWF,
                                t[tref],
                                t[tref]+30ns,
                                t[tref]+t[tper]-10ns);
        EdgeSetOrigin      (xSTRBNFstrobeWF,Edge1,orgclkoutef);
        EdgeSetOrigin      (xSTRBNFstrobeWF,Edge2,orgclkoutef);
        EdgeSetOrigin      (xSTRBNFstrobeWF,Edge3,orgclkoutef);

        WaveSetStrobe      (xSTRBNLstrobeWF,
                                t[tref],
                                t[tref]+30ns,
                                t[tref]+t[tper]-10ns);
        EdgeSetOrigin      (xSTRBNLstrobeWF,Edge1,orgclkoutef);
        EdgeSetOrigin      (xSTRBNLstrobeWF,Edge2,orgclkoutef);
        EdgeSetOrigin      (xSTRBNLstrobeWF,Edge3,orgclkoutef);

        WaveSetStrobe      (xSTRBNRstrobeWF,
                                t[tref],
                                t[tref]+30ns,
                                t[tref]+t[tper]-10ns);
        EdgeSetOrigin      (xSTRBNRstrobeWF,Edge1,orgclkoutef);
        EdgeSetOrigin      (xSTRBNRstrobeWF,Edge2,orgclkoutef);
        EdgeSetOrigin      (xSTRBNRstrobeWF,Edge3,orgclkoutef);

        EdgeSet            (TMRCLKdriveWF,Edge1,DriveData,
                                t[tref]+t[tH]);
        EdgeSet            (TMRCLKdriveWF,Edge2,DriveComplement,
                                t[tref]+t[tH]+t[tper]-7ns);
        EdgeSetOrigin      (TMRCLKdriveWF,Edge1,orgclkoutll);
        EdgeSetOrigin      (TMRCLKdriveWF,Edge2,orgclkoutel);

        EdgeSet            (TMRDIRdriveWF,Edge1,DriveData,
                                t[tref]+t[tH]);
        EdgeSet            (TMRDIRdriveWF,Edge2,DriveComplement,
                                t[tref]+t[tH]+t[tper]-7ns);
        EdgeSetOrigin      (TMRDIRdriveWF,Edge1,orgclkoutll);
        EdgeSetOrigin      (TMRDIRdriveWF,Edge2,orgclkoutel);

        WaveSetStrobe      (WENLstrobeWF,
                                t[tref],
                                t[tref]+30ns,
                                t[tref]+t[tper]-10ns);
        EdgeSetOrigin      (WENLstrobeWF,Edge1,orgclkoutef);
        EdgeSetOrigin      (WENLstrobeWF,Edge2,orgclkoutef);
        EdgeSetOrigin      (WENLstrobeWF,Edge3,orgclkoutef);

        WaveSetStrobe      (WENHstrobeWF,
                                t[tref],
                                t[tref]+30ns,
                                t[tref]+t[tper]-10ns);
        EdgeSetOrigin      (WENHstrobeWF,Edge1,orgclkoutef);
        EdgeSetOrigin      (WENHstrobeWF,Edge2,orgclkoutef);
        EdgeSetOrigin      (WENHstrobeWF,Edge3,orgclkoutef);

        WaveSetStrobe      (xWENFstrobeWF,
                                t[tref],
                                t[tref]+30ns,
                                t[tref]+t[tper]-10ns);
        EdgeSetOrigin      (xWENFstrobeWF,Edge1,orgclkoutef);
        EdgeSetOrigin      (xWENFstrobeWF,Edge2,orgclkoutef);
        EdgeSetOrigin      (xWENFstrobeWF,Edge3,orgclkoutef);

        WaveSetStrobe      (xWENLstrobeWF,
                                t[tref],
                                t[tref]+30ns,
                                t[tref]+t[tper]-10ns);
        EdgeSetOrigin      (xWENLstrobeWF,Edge1,orgclkoutef);
        EdgeSetOrigin      (xWENLstrobeWF,Edge2,orgclkoutef);
        EdgeSetOrigin      (xWENLstrobeWF,Edge3,orgclkoutef);

        WaveSetStrobe      (xWENRstrobeWF,
                                t[tref],
                                t[tref]+30ns,
                                t[tref]+t[tper]-10ns);
        EdgeSetOrigin      (xWENRstrobeWF,Edge1,orgclkoutef);
        EdgeSetOrigin      (xWENRstrobeWF,Edge2,orgclkoutef);
        EdgeSetOrigin      (xWENRstrobeWF,Edge3,orgclkoutef);

        WaveSetStrobe      (XFstrobeWF,
                                t[tref]+t[tH],
                                t[tref]+t[tH]+30ns,
                                t[tref]+t[tH]+t[tper]-10ns);
        EdgeSetOrigin      (XFstrobeWF,Edge1,orgclkouter);
        EdgeSetOrigin      (XFstrobeWF,Edge2,orgclkouter);
        EdgeSetOrigin      (XFstrobeWF,Edge3,orgclkouter);

        WaveSetStrobe      (XTAL2strobeWF, 
                                t[tref]+t[tH], 
                                t[tref]+t[tH]+30ns,
                                t[tref]+t[tH]+t[tper]-10ns);
        EdgeSetOrigin      (XTAL2strobeWF,Edge1,orgclkin);
        EdgeSetOrigin      (XTAL2strobeWF,Edge2,orgclkin);
        EdgeSetOrigin      (XTAL2strobeWF,Edge3,orgclkin);
    end;  (* end TIsearchlooseACTable2 *)

  end;  (* end case actable *)

  (* CLKMOD *)

        WaveSetNR          (NRdrive,0ns);                       

        WaveSetNR          (CLKMODdriveWF,t[tref]);                     

  (* EMU / JTAG  *)

        WaveSetNR          (EMUdriveWF,t[tref]+t[tH]);

        WaveSetStrobe      (EMUstrobeWF,
                                t[tref]+t[tH],
                                t[tref]+t[tH]+t[tper]-14ns,
                                t[tref]+t[tH]+t[tper]-10ns);
        EdgeSetOrigin      (EMUstrobeWF,Edge1,orgclkouter);
        EdgeSetOrigin      (EMUstrobeWF,Edge2,orgclkouter);
        EdgeSetOrigin      (EMUstrobeWF,Edge3,orgclkouter);

        WaveSetRTO         (TCKdriveWF,
                                t[tref],
                                t[tref]+t[tH]);
        EdgeSetOrigin      (TCKdriveWF,Edge1,orgscan);
        EdgeSetOrigin      (TCKdriveWF,Edge2,orgscan);

        WaveSetNR          (TRSTdriveWF,t[tref]);
        EdgeSetOrigin      (TRSTdriveWF,Edge1,orgscan);

        WaveSetNR          (TMSdriveWF,t[tref]);
        EdgeSetOrigin      (TMSdriveWF,Edge1,orgscan);

        WaveSetNR          (TDIdriveWF,t[tref]);
        EdgeSetOrigin      (TDIdriveWF,Edge1,orgscan);

        WaveSetStrobe      (TDOstrobeWF,
                                t[tref],
                                t[tref]+t[tper]-14ns,
                                t[tref]+t[tper]-10ns);
        EdgeSetOrigin      (TDOstrobeWF,Edge1,orgscan);
        EdgeSetOrigin      (TDOstrobeWF,Edge2,orgscan);
        EdgeSetOrigin      (TDOstrobeWF,Edge3,orgscan);

        EdgeSet            (OFFdriveL,Edge1,DriveLow,0ns);              (* Drive EMU1/OFF_ for trilkg *)
        EdgeSet            (OFFdriveH,Edge1,DriveHigh,0ns);

        WaveSetContinue    (ContinueWF);
        WaveSetContinue    (Continue_drive);

        WaveSetOff         (AllOff,0ns,0ns);


  (* SHUT-DOWN VECTOR WAVEFORMS *)

        (* INPUTS *)

        EdgeSet            (CLKINresumeWF,Edge1,DriveLow,
                                t[tref]+t[tH]);

        EdgeSet            (CLKMODresumeWF,Edge1,DriveLow,t[tper]-6ns);

        EdgeSet            (INSresumeWF,Edge1,DriveLow,t[tper]-6ns);

        EdgeSet            (RSNresumeWF,Edge1,DriveHigh,t[tper]-6ns);

        EdgeSet            (LVDresumeWF,Edge1,DriveHigh,t[tper]-6ns);

        EdgeSet            (TRSTresumeWF,Edge1,DriveOff,t[tper]-6ns);   (* Pull Down *)

        EdgeSet            (INUPSresumeWF,Edge1,DriveOff,t[tper]-6ns);  (* Pull UP   *)

        (* OUTPUTS *)

        EdgeSet            (OUTSresumeWF,Edge1,StrobeOff,t[tper]-6ns);
        WaveSetContinue    (XTAL2resumeWF);

        (* I/O's *)

        EdgeSet            (EMU0resumeWF,Edge1,DriveOff,t[tper]-6ns);   (* Pull UP *)
        EdgeSet            (EMU1resumeWF,Edge1,DriveLow,t[tper]-6ns);   (* OFF ! *)

        EdgeSet            (IOSresumeWF,Edge1,StrobeOff,t[tper]-6ns);
        EdgeSet            (IOSresumeWF,Edge2,DriveOff,t[tper]-6ns);            

        EdgeSet            (IOSdriveL,Edge1,StrobeOff,t[tper]-6ns);
        EdgeSet            (IOSdriveL,Edge2,DriveLow,t[tper]-6ns);              

        WaveSetContinue    (SYNCresumeWF);

      (**********************)
      (* PMT Input Waveform *)
      (**********************)
      EdgeSet           (PmtTESTdriveWF,Edge1,StrobeOff,0ns); (*Use for LVDOVRD*)
      EdgeSet           (PmtTESTdriveWF,Edge2,DriveHigh,0ns);
                
      WaveSetNR         (PmtTABUSdriveWF,  0ns);
      WaveSetNR         (PmtTTCRdriveWF,   0ns);
      WaveSetNR         (PmtTSPdriveWF,    0ns);
      WaveSetNR         (PmtTWRITEdriveWF, 0ns);
      WaveSetNR         (PmtTERASEdriveWF, 0ns);
      WaveSetNR         (PmtTVER1driveWF,  0ns);
      WaveSetNR         (PmtTVER0driveWF,  0ns);
      WaveSetNR         (PmtTRESETdriveWF, 0ns);

      WaveSetNR         (PmtTFOENABdriveWF,0ns);
      WaveSetNR         (PmtTCEdriveWF,    0ns);
      WaveSetNR         (PmtTLPdriveWF,    0ns);
      WaveSetNR         (PmtTEXEdriveWF,   0ns);
      WaveSetNR         (PmtTPMTdriveWF,   0ns);
      WaveSetNR         (NonFlashdriveWF,  0ns);

      (***********************)
      (* PMT Output Waveform *)
      (***********************)
      WaveSetStrobe (NonFlashstrobeWF, 0ns,t[tsNonFlash],
                                           t[tsNonFlash]+3ns);

      (********************)
      (* PMT I/O Waveform *)
      (********************)
      WaveSetNR         (PmtEMU0driveWF,   0ns);
      WaveSetStrobe (PmtEMU0strobeWF,  0ns,t[tsNonFlash],
                                           t[tsNonFlash]+3ns);

      WaveSetNR         (PmtEMU1driveWF,   0ns);
      WaveSetStrobe (PmtEMU1strobeWF,  0ns,t[tsNonFlash],
                                           t[tsNonFlash]+3ns);

      WaveSetNR         (PmtTDBUSdriveWF,  t[tdPmtTDBUS]);

      WaveSetStrobe (PmtTDBUSstrobeWF, 0ns,t[tsPmtTDBUS],
                                           t[tsPmtTDBUS]+3ns);

   ACTableClose;

  end; (*with*)

 end; (* TIACTableSet *)


        (***********************************************************)
        (***                   ACTableSet                        ***)
        (***********************************************************)
        (***                                                     ***)
        (*** This is the beginning of the ACTableSet procedure.  ***)
        (***                                                     ***)
        (***********************************************************)

begin (*ACTableSet*)

    (* Set-up waveforms *)

case actable of
  TIsearchACTable       :   TIACTableSet( TIsearchACTable );
  TIsearchlooseACTable   :   TIACTableSet( TIsearchlooseACTable );
  TIsearchlooseACTable2  :   TIACTableSet( TIsearchlooseACTable2 );
  others                :   begin
                              TIACTableSet( TIlofrqACTable );
                              TIACTableSet( TIlofrqpllACTable);
                              TIACTableSet( TIhifrqACTable );
                              TIACTableSet( TIveryhifrqACTable );
                              TIACTableSet( TIsearchACTable );
                              TIACTableSet( TIlofrqlooseACTable );
                              TIACTableSet( TIhifrqlooseACTable );
                              TIACTableSet( TIveryhifrqlooseACTable );
                              TIACTableSet( TIsearchlooseACTable );
                              TIACTableSet( TIsearchlooseACTable2 );
                              TIACTableSet( TIPMT100ACTable );
                            end;
end; (*case *)

end;  (*ACTableSet*)
