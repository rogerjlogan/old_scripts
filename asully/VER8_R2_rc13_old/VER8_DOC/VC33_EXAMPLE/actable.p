(***********************************************************************)
(***                                                                 ***)
(***                       320VC33 TEST PROGRAM                      ***)
(***                       --------------------                      ***)
(***                                                                 ***)
(***                        File Name:  actable.p                    ***)
(***                        Revision :  00 20021011                  ***)
(***                                                                 ***)
(***     Revision History:                                           ***)
(***     00 SC 08/18/99  Program generation.                         ***)
(***     01 SC 08/18/99  Defined EXTCLKdriveWF                       ***)
(***     02 SC 08/18/99  Defined CLKMDSELdriveWF as NR at 2.0ns      ***)
(***     03 SC 08/18/99  Defined EDGEMDdriveWF as NR at 2.0ns        ***)
(***     04 SC 08/18/99  Defined RSVdriveWF as NR at 2.0ns           ***)
(***     05 SC 08/18/99  Defined TCKdriveWF as RTO                   ***)
(***     06 SC 08/20/99  Defined loose setup for TIhifrqloose13ACTable *)
(***     07 SC 09/30/99  Defined TIhifrqloose16ACTable               ***)
(***     08 SC 11/16/99  Defined PinStrobeModeSet-PinStrobeFast with ***)
(***                     with pingroup instead of individual         ***)
(***                     declaration.                                ***)
(***     09 SC 12/02/99  Defined RDY_driveWF as NR                   ***)
(***                                                                 ***)
(***     10 SC 01/25/00  Defined CLKINdriveWF as NR if actable       ***)
(***                     := other                                    ***)
(***     11 SC 03/17/00  Initialize TIvboxloACTable                  ***)
(***     12 SC 03/30/00  Changed RDY_driveWF to RTO for char and     ***)
(***                     spec timing test                            ***)
(***     13 SC 04/11/00  Initialize TIvboxhiACTable                  ***)
(***     14 SC 05/13/00  Set XFStrobeWF placement based on H1 falling **)
(***     15 SC 05/20/00  Redefined FSXstrobeWF as WaveSetStrobe with ***)
(***                     orgtdH1HCLKXH origin                        ***)
(***     16 SC 07/05/00  Modified DRdriveWF to RTZ to test both      ***)
(***                     tsuDRCLKRL and thDRCLKRL                    ***)
(***     17 TD 09/18/00  Adjusted the Edge2,Edge3 of H3strobeWF      ***)
(***     18 SC 10/07/00  Defined FSXGPIOstrobeWF setup for 10ns table **)
(***     19 SC 10/07/00  Defined DXGPIOstrobeWF setup for 10ns table ***)
(***     20 SC 10/12/00  Added TIhifrqloose10ACTable to XFdriveWF    ***)
(***     21 SC 10/12/00  Adjusted TCLKstrobeWF Edge3 from +4ns to +3ns *)
(***                     for 90Mhz debug.                            ***)
(***     22 SC 10/12/00  Added TIhifrqloose10ACTable to RW_strobeWF  ***)
(***                     for 90Mhz debug.                            ***)
(***     23 SC 10/19/00  Renamed TIhifrqloose10ACTable to            ***)
(***                     TIhifrqloose11ACTable to reflect 90Mhz test ***)
(***     24 SC 10/20/00  Changed orgtoffset_im reference to orgH1H   ***)
(***                     to more accurately describe origin ref      ***)
(***     25 SC 10/21/00  Defined RW_strobeWF setup for TIvboxloACTable *)
(***     26 SC 10/21/00  Defined SH1strobeWF and SH3strobeWF for     ***)
(***                     TIvboxloACTable                             ***)
(***     27 SC 10/21/00  Defined IACK_strobeWF for TIvboxloACTable   ***)
(***     28 SC 10/21/00  Defined TCLKstrobeWF for TIvboxloACTable    ***)
(**      29 SC 11/02/00  Added 1.5ns to H1strobeWF for loose13 and   ***)
(***                     loose16ACTable for functional stability     ***)
(***     30 SC 11/20/00  Adjusted edge3 of XFstrobeWF to comply with ***)
(***                     P100 minimum stobe requirements.            ***)
(***     31 SC 02/10/01  Adjusted CLKRdriveWF to EXTCLKR for 25C, 0C,***)
(***                     and -40C for PG1.2 material.                ***)
(***     32 SC 02/15/01  Defined DXstrobeWF for TIhifrqloose10ACTable **)
(***     33 SC 02/16/01  Defined CLKXstrobeWF for TIhifrqloose10ACTable*)
(***     34 SC 03/27/02  Adjusted edge 3 of RW_strobeWF base on lot  ***)
(***                     probed on 11/29/01.                         ***)
(***********************************************************************)
(***********************************************************************)
(***                                                                 ***)
(*** VC33PGE00  20021011  Major  Curtis Woods                        ***)
(***  - Initial revision. Program generated from the commercial pro- ***)
(***    gram 320VC33B3.                                              ***)
(***                                                                 ***)
(***********************************************************************)


	(***********************************************************)
	(***		     AC Table Definition		 ***)
	(***********************************************************)
	(***							 ***)
	(*** The AC Table Definition is the section of the	 ***)
	(*** program in which all waveforms necessary for the	 ***)
	(*** test are created. These waveforms may be assigned	 ***)
	(*** to any Pin List in the CycleTableSet procedure.	 ***)
	(*** The AC Table Definition also includes the		 ***)
	(*** implementation of all timing correction factors.	 ***)
	(*** The ACTableSet procedure will accept a single	 ***)
	(*** parameter of type ACTable. This will be the name of ***)
	(*** the AC Table.					 ***)
	(***							 ***)
	(*** In order to assure that the test engineering	 ***)
	(*** standard procedures will work with a program, the	 ***)
	(*** ACTableSet procedure should include one list of	 ***)
	(*** waveforms with frequency dependency built in. Most  ***)
	(*** of the frequency dependencies should be comprehended***)
	(*** in the AC Data Sheet. It is also recommended that	 ***)
	(*** the capability to change tester period on-the-fly	 ***)
	(*** be avoided, as it precludes the tester from moving  ***)
	(*** timing edges across period boundaries automatically.***)
	(*** If the PeriodSetAll command is used to set all	 ***)
	(*** periods in an AC Table to the same value, the tester***)
	(*** will automatically delay edges into subsequent	 ***)
	(*** periods, carrying the original data with the edge.  ***)
	(*** WaveSetDelay statements are not necessary. 	 ***)
	(***							 ***)
	(***********************************************************)

procedure ACTableSet; (* actable : ACTable *)

	(***********************************************************)
	(***	    Internal Procedure TIACTableSet		 ***)
	(***********************************************************)
	(***							 ***)
	(*** This internal procedure is called by the procedure  ***)
	(*** ACTableSet, and is the portion of this module that  ***)
	(*** sets up the ACTables. The purpose of creating the	 ***)
	(*** TIACTableSet procedure is to allow the ACTableSet	 ***)
	(*** procedure to set up the waveforms for all test	 ***)
	(*** tables in a single call using the special parameter ***)
	(*** TIallACTable.					 ***)
	(***							 ***)
	(***********************************************************)

 procedure TIACTableSet( actable : ACTable );
 var supplyvtype   : SupplyVType;
     vccvoltage	   : MicroVolts;
     save_cycletable : CycleTable;
     save_actable    : ACTable;
     save_dctable    : DCTable;
     
 begin

	(***********************************************************)
	(***							 ***)
	(*** The ac correction factors as defined by test	 ***)
	(*** engineering are defined here. dtcf and ctcf are	 ***)
	(*** declared as global variables, and are available	 ***)
	(*** to the user through Interactive Pascal. These	 ***)
	(*** correction factors are tester dependent, and may	 ***)
	(*** not be altered by the programmer.			 ***)
	(***							 ***)
	(*** Guardbands as required on a device by device basis  ***)
	(*** should also be declared and implemented in this	 ***)
	(*** section. The guardbands used must be thoroughly	 ***)
	(*** documented with explanations. Guardbands will	 ***)
	(*** differ in probe, final test, and QA programs.	 ***)
	(*** In order to assure that a single AC Data Sheet	 ***)
	(*** will support the requirement, guardbands must be	 ***)
	(*** implemented in a manner similar to the correction	 ***)
	(*** factors. Declare variables (they may be global or	 ***)
	(*** local) for your guardbands. Set the variable to	 ***)
	(*** the correct guardband value in the sections below	 ***)
	(*** for probe, final, and QA. Then, add or subtract	 ***)
	(*** the guardband variable in the correct expressions	 ***)
	(*** in the declaration section below.			 ***)
	(***							 ***)
	(***********************************************************)

   case TITestType of
     Probe:
       begin
         dtcf:=600ps;  (*Drive timing correction factor from mega1spec  *)
         ctcf:=800ps;  (*Compare timing correction factor from mega1spec*)
       end;
     Final_Handler,
     Final_Handtest,
     PRE_Burnin_Handler,
     PRE_Burnin_Handtest:
       begin
	 dtcf:=400ps;  (*Drive timing correction factor from mega1spec  *)
	 ctcf:=400ps;  (*Compare timing correction factor from mega1spec*)
       end;
     QA_Handler,
     QA_Handtest:
       begin
	 dtcf:=	400ps;  (*Drive timing correction factor from mega1spec  *)
	 ctcf:=	400ps;  (*Compare timing correction factor from mega1spec*)
       end;
   end; (*case*)

	(***********************************************************)
	(***							 ***)
	(*** Loose timings as required on a device by device	 ***)
	(*** basis are set up and implemented in this section.	 ***)
	(*** Loose timings declared here should be relaxations on***)
	(*** parameters known to be sensitive on the device.	 ***)
	(*** Loose timing parameters will be added/subtracted	 ***)
	(*** from parameters only for Levels tests. Spec timings ***)
	(*** will be used for Timing tests.			 ***)
	(*** In order to assure that a single AC Data Sheet	 ***)
	(*** will support the requirement, loose timings must be ***)
	(*** implemented in a manner similar to the correction	 ***)
	(*** factors. Declare variables (they may be global or	 ***)
	(*** local) for your guardbands. Set the variable to	 ***)
	(*** the correct guardband value in the sections below	 ***)
	(*** for loose timing ACTables and spec timing ACTables. ***)
	(*** Then add or subtract the loose timing variable to	 ***)
	(*** parameters as necessary.				 ***)
	(***							 ***)
	(***********************************************************)

   with ACDataSheets[ actable ] do
   begin
     case actable of
       TInomlooseACTable,
       TIstressACTable,			(*Added TIstressACTable*)	 	
       TIparametricACTable:
	 begin
	   loosesetup	:=  4ns;
	   loosehold	:=  5ns;
	   loosestbdly	:=  15ns;
	   looseoffdly	:=  5ns;
	   looseclock	:=  10ns;
           loosetclk    := 15ns;
	   schmo	:=  1;
           looseRW_     := 10ns;
           loosewrtbgnAdly:= 10ns;
           looseDBUSMdly:=  7ns;
         end;

       TIlofrqminACTable,
       TIlofrqmaxACTable,
       TIlofrqlooseACTable:
         begin
           loosesetup	:=  4ns;
           loosehold	:=  5ns;
           loosestbdly	:= 15ns;
           looseoffdly	:= 10ns;
           looseclock	:= 10ns;
           loosetclk    := 15ns;
           schmo	:=  1;
           looseRW_     := 10ns;
           loosewrtbgnAdly:= 10ns;
           looseDBUSMdly  :=  10ns;
         end;

       TIhifrqlooseACTable:
	 begin
	   loosesetup	:=  4ns;
	   loosehold	:=  5ns;
	   loosestbdly	:=  8ns;
	   looseoffdly	:=  5ns;
	   looseclock	:=  4ns;
           loosetclk    :=  8ns;
	   schmo	:=  1;
           looseRW_     :=  10ns;
           loosewrtbgnAdly:= 10ns;
           looseDBUSMdly:=  10ns;
         end;

       TIhifrqspec16ACTable,
       TIhifrqloose16ACTable,
       TIhifrqloose16DIV2ACTable:
         begin
           loosesetup   :=  1ns;
           loosehold    :=  2ns;
           loosestbdly  :=  0ns;
           looseoffdly  :=  2ns;
           looseclock   :=  0ns;
           loosetclk    :=  3ns;
           t[tscanadj]  :=  0ns;
           schmo        :=  1;
           looseRW_     :=  4ns;
           loosewrtbgnAdly:= 4ns;
           looseDBUSMdly:=  3ns;
         end;

       TIhifrqspec13ACTable,
       TIhifrqloose13ACTable,
       TIhifrqloose13DIV2ACTable:
         begin
           loosesetup   :=  1ns;
           loosehold    :=  2ns;
           loosestbdly  :=  0ns;
           looseoffdly  :=  2ns;
           looseclock   :=  0ns;
           loosetclk    :=  3ns;
           t[tscanadj]  :=  0ns;
           schmo        :=  1;
           looseRW_     :=  4ns;
           loosewrtbgnAdly:= 4ns;
           looseDBUSMdly:=  3ns;
         end;

       TIhifrqloose10ACTable:
         begin
           loosesetup   :=  1ns;
           loosehold    :=  2ns;
           loosestbdly  :=  0ns;
           looseoffdly  :=  2ns;
           looseclock   :=  0ns;
           loosetclk    :=  3ns;
           t[tscanadj]  :=  0ns;
           schmo        :=  1;
           looseRW_     :=  4ns;
           loosewrtbgnAdly:= 4ns;
           looseDBUSMdly:=  3ns;
         end;

        TIvboxloACTable:
         begin
           loosesetup   :=  0ns; {5ns;}
           loosehold    :=  0ns; {5ns;}
           loosestbdly  :=  0ns; {8ns;}
           looseoffdly  :=  0ns; {5ns;}
           looseclock   :=  0ns; {10ns;}
           loosetclk    :=  0ns; {8ns;}
           schmo        :=  1;
           looseRW_       :=  0ns;
           loosewrtbgnAdly:=  0ns; {18ns;}
           looseDBUSMdly  :=  0ns; {2ns;}
         end;

        others:
	 begin
           loosesetup	:=  0ns; {5ns;}
	   loosehold	:=  0ns; {5ns;}
	   loosestbdly	:=  0ns; {8ns;}
	   looseoffdly	:=  0ns; {5ns;}
	   looseclock	:=  0ns; {10ns;}
           loosetclk    :=  0ns; {8ns;}
	   schmo	:=  1;
	   looseRW_       :=  0ns;
           loosewrtbgnAdly:=  0ns; {18ns;}
	   looseDBUSMdly  :=  0ns; {2ns;}
         end;
     end; (* case *)

     case TITestType of 
       Probe : sp:=7ns;
       others: sp:=0ns;
     end; (* case *) 

	(***********************************************************)
	(***							 ***)
	(*** The AC Tables are defined below. There is a single  ***)
	(*** AC Table set-up. Different AC Tables are created by ***)
	(*** accessing different AC Data Sheets using the "with" ***)
	(*** instruction. Parametric tests will normally access  ***)
	(*** one of the functional AC Tables. It is not normally ***)
	(*** necessary to set up separate AC Tables for 	 ***)
	(*** parametric testing. The requirements of doing SHMOO ***)
	(*** and SEARCH routines requires that the same AC Table ***)
	(*** set-up be used for all test frequencies. One new AC ***)
	(*** Table will be created each time the ACTableSet is	 ***)
	(*** called with a new actable parameter (Table Name).	 ***)
	(*** The user is required to call the ACTableSet	 ***)
	(*** procedure once for each unique timing set (different***)
	(*** periods, and different parameters, ie. loose timing)***)
	(***							 ***)
	(***********************************************************)

     ACTableOpen( actable );

   PinStrobeModeSet(IOPINS,PinStrobeFast);
   PinStrobeModeSet(OUTPUTS,PinStrobeFast);

     (*	        						    *)
     (*	 Timing and Waveform set-up for all frequencies 	    *)
     (*								    *)
{
     if characterize then
     begin
       SetupGet(save_cycletable,save_actable,save_dctable);
       OriginSet(orgtoffset,SyncTime[save_actable,VDDvalue, orgtoffset]);
       OriginSet(orgtdH1HCLKXH,SyncTime[save_actable,VDDvalue,orgtdH1HCLKXH]);
       OriginSet(orgtdH1HCLKXL,SyncTime[save_actable,VDDvalue,orgtdH1HCLKXL]);
       OriginSet(orgtdH1HCLKRL,SyncTime[save_actable,VDDvalue,orgtdH1HCLKRL]);
     end
     else
     begin
       OriginSet(orgtoffset,0ns);
       OriginSet(orgtdH1HCLKXH,0ns);
       OriginSet(orgtdH1HCLKXL,0ns);
       OriginSet(orgtdH1HCLKRL,0ns);
     end;
}
     PeriodSetAll (t[tper]);	  (* Period for functional ACTable  *)

	     (* CLOCK RELATED TIMINGS -- INCLUDES ANY DUTY CYCLE ON CLOCKIN *)

     case actable of
	  TIhifrqloose13DIV2ACTable,
          TIhifrqloose16DIV2ACTable:
              begin
	        WaveSetDoubleClk    (CLKINdriveWF,
	                            0ns,
	                            t[twCIH],
	                            t[twCIH]+t[twCIL],
	                            2*t[twCIH]+t[twCIL]);
	        EdgeSetOrigin       (CLKINdriveWF, Edge1, orgtoffset);
	        EdgeSetOrigin       (CLKINdriveWF, Edge2, orgtoffset);
	        EdgeSetOrigin       (CLKINdriveWF, Edge3, orgtoffset);
	        EdgeSetOrigin       (CLKINdriveWF, Edge4, orgtoffset);

	        WaveSetDoubleClk    (EXTCLKdriveWF,
	                            0ns,
	                            t[twCIH],
	                            t[twCIH]+t[twCIL],
	                            2*t[twCIH]+t[twCIL]);
	        EdgeSetOrigin       (EXTCLKdriveWF, Edge1, orgtoffset);
	        EdgeSetOrigin       (EXTCLKdriveWF, Edge2, orgtoffset);
	        EdgeSetOrigin       (EXTCLKdriveWF, Edge3, orgtoffset);
	        EdgeSetOrigin       (EXTCLKdriveWF, Edge4, orgtoffset);
              end;

          TIhifrqloose10ACTable:
              begin
                WaveSetDoubleClk    (CLKINdriveWF,
                                    0ns,
                                    0ns,
                                    (t[tcH]) div 2,
                                    (t[tcH]) div 2);
                EdgeSetOrigin       (CLKINdriveWF, Edge1, orgtoffset);
                EdgeSetOrigin       (CLKINdriveWF, Edge2, orgtoffset);
                EdgeSetOrigin       (CLKINdriveWF, Edge3, orgtoffset);
                EdgeSetOrigin       (CLKINdriveWF, Edge4, orgtoffset);

                WaveSetDoubleClk    (EXTCLKdriveWF,                   (*** &&&&&&& EXTCLK ADJUSTED FOR DEBUG &&&&&&*)
                                    0.4ns,
                                    1.4ns,
                                    ((t[tcH]) div 2) +2.0ns,
                                    3.0ns);
                EdgeSetOrigin       (EXTCLKdriveWF, Edge1, orgtoffset);
                EdgeSetOrigin       (EXTCLKdriveWF, Edge2, orgtoffset);
                EdgeSetOrigin       (EXTCLKdriveWF, Edge3, orgtoffset);
                EdgeSetOrigin       (EXTCLKdriveWF, Edge4, orgtoffset);
              end;


          TIhifrqspec13ACTable,
          TIhifrqloose13ACTable:
              begin
                WaveSetDoubleClk    (CLKINdriveWF,
                                    0ns,
                                    0ns,
                                    (t[tcH]) div 2,
                                    (t[tcH]) div 2);
                EdgeSetOrigin       (CLKINdriveWF, Edge1, orgtoffset);
                EdgeSetOrigin       (CLKINdriveWF, Edge2, orgtoffset);
                EdgeSetOrigin       (CLKINdriveWF, Edge3, orgtoffset);
                EdgeSetOrigin       (CLKINdriveWF, Edge4, orgtoffset);

                WaveSetDoubleClk    (EXTCLKdriveWF,                   (*** &&&&&&& EXTCLK ADJUSTED FOR DEBUG &&&&&&*)
                                    0.4ns,
                                    1.4ns,
                                    ((t[tcH]) div 2) +2.0ns,
                                    3.0ns);
                EdgeSetOrigin       (EXTCLKdriveWF, Edge1, orgtoffset);
                EdgeSetOrigin       (EXTCLKdriveWF, Edge2, orgtoffset);
                EdgeSetOrigin       (EXTCLKdriveWF, Edge3, orgtoffset);
                EdgeSetOrigin       (EXTCLKdriveWF, Edge4, orgtoffset);
              end;

          TIhifrqspec16ACTable,
          TIhifrqloose16ACTable:
              begin
                WaveSetDoubleClk    (EXTCLKdriveWF,                   (*** &&&&&&& EXTCLK ADJUSTED FOR DEBUG &&&&&&*)
                                    0.4ns,
                                    1.4ns+2ns,
                                    ((t[tcH]) div 2) +2.0ns+2ns,
                                    3.0ns+2ns);
                EdgeSetOrigin       (EXTCLKdriveWF, Edge1, orgtoffset);
                EdgeSetOrigin       (EXTCLKdriveWF, Edge2, orgtoffset);
                EdgeSetOrigin       (EXTCLKdriveWF, Edge3, orgtoffset);
                EdgeSetOrigin       (EXTCLKdriveWF, Edge4, orgtoffset);

                WaveSetNR           (CLKINdriveWF, t[tcCI]);           (***&& Adjusted for PLL lock-up   &&**)

              end;

          others:
             begin
                WaveSetNR           (CLKINdriveWF, 70.0ns);           (***&& Adjusted for PLL lock-up   &&**)


	        WaveSetDoubleClk    (EXTCLKdriveWF,                   (*** &&&&&&& EXTCLK ADJUSTED FOR DEBUG &&&&&&*)
	                            0.4ns,
                                    1.4ns,
                                    ((t[tcH]) div 2) +2.0ns,
                                    3.0ns);
	        EdgeSetOrigin       (EXTCLKdriveWF, Edge1, orgtoffset);
	        EdgeSetOrigin       (EXTCLKdriveWF, Edge2, orgtoffset);
	        EdgeSetOrigin       (EXTCLKdriveWF, Edge3, orgtoffset);
	        EdgeSetOrigin       (EXTCLKdriveWF, Edge4, orgtoffset);
 
             end;


	   end; (* case *)

        case actable of
          TIIDDQACTable:

            WaveSetEdgeStrobe   (H1strobeWF,
                            0,
                            3ns,
                            9ns);

	  TIhifrqloose16DIV2ACTable:
           begin
            WaveSetEdgeStrobe   (H1strobeWF,
                            0.0ns,
                            t[tcCI]-7ns,
                            t[tcCI]-6ns);
            EdgeSetOrigin       (H1strobeWF,Edge1,orgH1L);
            EdgeSetOrigin       (H1strobeWF,Edge2,orgH1L);
            EdgeSetOrigin       (H1strobeWF,Edge3,orgH1L);
           end;

          TIhifrqloose10ACTable:
           begin
            WaveSetEdgeStrobe   (H1strobeWF,
                            1.0ns,
                            t[tcCI]+1ns,
                            t[tcCI]+3.5ns);
            EdgeSetOrigin       (H1strobeWF,Edge1,orgH1L);
            EdgeSetOrigin       (H1strobeWF,Edge2,orgH1L);
            EdgeSetOrigin       (H1strobeWF,Edge3,orgH1L);
           end;

          TIhifrqloose13ACTable,
          TIhifrqloose16ACTable:
	   begin
	    WaveSetEdgeStrobe   (H1strobeWF,
			    1.0ns,
			    t[tcCI]+1.5ns+1.5ns,
			    t[tcCI]+4.5ns+1.5ns);
     	    EdgeSetOrigin	(H1strobeWF,Edge1,orgH1L);
 	    EdgeSetOrigin	(H1strobeWF,Edge2,orgH1L);
	    EdgeSetOrigin	(H1strobeWF,Edge3,orgH1L);
           end;

          TIvboxloACTable:
           begin
            WaveSetEdgeStrobe   (H1strobeWF,
                            0ns,
                            t[tper]-15ns ,
                            t[tper]-10ns ); 
            EdgeSetOrigin       (H1strobeWF,Edge1,orgH1L);
            EdgeSetOrigin       (H1strobeWF,Edge2,orgH1L);
            EdgeSetOrigin       (H1strobeWF,Edge3,orgH1L);

           end;

          TInomlooseACTable:
           begin 
            WaveSetEdgeStrobe   (H1strobeWF,
                            0ns,
                            t[tcCI]+3ns +5ns,   (** added +5ns for probe **)
                            t[tcCI]+8ns +5ns);  (** added +5ns for probe **)
            EdgeSetOrigin       (H1strobeWF,Edge1,orgH1L);
            EdgeSetOrigin       (H1strobeWF,Edge2,orgH1L);
            EdgeSetOrigin       (H1strobeWF,Edge3,orgH1L);
           end;

          TIvboxhiACTable:
           begin
            WaveSetEdgeStrobe   (H1strobeWF,
                            0ns,
                            t[tcCI]+3ns,
                            t[tcCI]+8ns);
            EdgeSetOrigin       (H1strobeWF,Edge1,orgH1L);
            EdgeSetOrigin       (H1strobeWF,Edge2,orgH1L);
            EdgeSetOrigin       (H1strobeWF,Edge3,orgH1L);
           end;

          others:
           begin
            WaveSetEdgeStrobe   (H1strobeWF,
                            1.0ns,
                            t[tcCI]+2ns,
                            t[tcCI]+5ns);
            EdgeSetOrigin       (H1strobeWF,Edge1,orgH1L);
            EdgeSetOrigin       (H1strobeWF,Edge2,orgH1L);
            EdgeSetOrigin       (H1strobeWF,Edge3,orgH1L);
           end;



        end; (* case *)
     
       case actable of 
         TIhifrqloose10ACTable:
            WaveSetEdgeStrobe       (SH1strobeWF,       (* for sync-up *)
                                    0ns,
                                    t[tcCI] - 4ns,
                                    t[tcCI] - 2ns);
         TIvboxloACTable:
            WaveSetEdgeStrobe       (SH1strobeWF,       (* for sync-up *)
                                    0ns,
                                    t[tcCI] + 20ns,
                                    t[tcCI] + 25ns);

         TInomlooseACTable:
            WaveSetEdgeStrobe       (SH1strobeWF,       (* for sync-up *)
                                    0ns,
                                    t[tcCI] + 15ns,
                                    t[tcCI] + 20ns);
         TIvboxhiACTable:
            WaveSetEdgeStrobe       (SH1strobeWF,       (* for sync-up *)
                                    0ns,
                                    t[tcCI] + 15ns,
                                    t[tcCI] + 20ns);

         others:
            WaveSetEdgeStrobe       (SH1strobeWF,       (* for sync-up *)
                                    0ns,
                                    t[tcCI] - 5ns,
                                    t[tcCI] - 3ns);

       end;      

        WaveSetEdgeStrobe       (SyncH1HstrobeWF,   (* for sync-up *)
                            0ns,
                            2ns,
                            8ns);


       case actable of
         TIhifrqloose10ACTable:
            WaveSetEdgeStrobe       (SyncH1LstrobeWF,   (* for sync-up *)
                                     0ns,
                                     t[tcH]-9ns,
                                     t[tcH]-6ns);
       others:
        WaveSetEdgeStrobe       (SyncH1LstrobeWF,   (* for sync-up *)
                                      0ns,
                                      t[tcH]-12ns,
                                      t[tcH]-6ns);
       end;


        case actable of
          TIIDDQACTable:

            WaveSetEdgeStrobe   (H3strobeWF,
                            t[tcCI],
                            t[tcCI]+4ns,
                            t[tcCI]+9ns);

	  TInomlooseACTable:
            WaveSetEdgeStrobe   (H3strobeWF,
                            t[tcCI],
                            t[tcCI]+20ns,
                            t[tcCI]+25ns);

          TIvboxhiACTable:
            WaveSetEdgeStrobe   (H3strobeWF,
                            t[tcCI],
                            t[tcCI]+20ns,
                            t[tcCI]+25ns);

          TIvboxloACTable:
            WaveSetEdgeStrobe   (H3strobeWF,
                            t[tcCI],
                            t[tcCI]+30ns,
                            t[tcCI]+35ns);


          TIhifrqloose16DIV2ACTable:
           begin
            WaveSetEdgeStrobe   (H3strobeWF,
                            0ns,
                            t[tcCI] - 2ns,
                            t[tcCI]+ 3ns);
            EdgeSetOrigin           (H3strobeWF, Edge1, orgH1L);
            EdgeSetOrigin           (H3strobeWF, Edge2, orgH1L);
            EdgeSetOrigin           (H3strobeWF, Edge3, orgH1L);
           end;

          TIhifrqloose10ACTable:
           begin
              WaveSetEdgeStrobe   (H3strobeWF,
                               0ns,
                               1.5ns,
                               4.5ns);
               EdgeSetOrigin           (H3strobeWF, Edge1, orgH1L);
               EdgeSetOrigin           (H3strobeWF, Edge2, orgH1L);
               EdgeSetOrigin           (H3strobeWF, Edge3, orgH1L);
            end;

          TIhifrqloose13ACTable,
          TIhifrqloose16ACTable:
           begin
              WaveSetEdgeStrobe   (H3strobeWF,
                               0ns,
                               3.5ns,
                               6.5ns);
               EdgeSetOrigin           (H3strobeWF, Edge1, orgH1L);
               EdgeSetOrigin           (H3strobeWF, Edge2, orgH1L);
               EdgeSetOrigin           (H3strobeWF, Edge3, orgH1L);
(* 092200 tdinh
   remove the H3strobeWF at low temp*)
{           if (TITestTemp = Temp_0_Degrees_C) then
               begin 
                   WaveSetEdgeStrobe   (H3strobeWF,
                                    0ns,
                                    1ns,
                                    4ns);
                   EdgeSetOrigin           (H3strobeWF, Edge1, orgH1L);
                   EdgeSetOrigin           (H3strobeWF, Edge2, orgH1L);
                   EdgeSetOrigin           (H3strobeWF, Edge3, orgH1L);
                end;
}
           end;
          others:
           begin
            WaveSetEdgeStrobe   (H3strobeWF,
                            0ns,
                            t[tcCI] - 4ns, 
                            t[tcCI] - 1ns);
   	    EdgeSetOrigin	    (H3strobeWF, Edge1, orgH1L);	
	    EdgeSetOrigin	    (H3strobeWF, Edge2, orgH1L);	
 	    EdgeSetOrigin	    (H3strobeWF, Edge3, orgH1L);	
           end;


        end; (* case *)

       case actable of
         TIhifrqloose10ACTable:
           WaveSetEdgeStrobe       (SH3strobeWF,       (* for sync-up *)
                                    0ns,
                                    t[tcCI]-4ns,
                                    t[tcCI]-2ns  );
         TIvboxloACTable:
            WaveSetEdgeStrobe       (SH3strobeWF,       (* for sync-up *)
                                    0ns,
                                    t[tcCI] + 20ns,
                                    t[tcCI] + 25ns);


         TInomlooseACTable:
            WaveSetEdgeStrobe       (SH3strobeWF,       (* for sync-up *)
                                    0ns,
                                    t[tcCI] + 15ns,
                                    t[tcCI] + 20ns);

         TIvboxhiACTable:
            WaveSetEdgeStrobe       (SH3strobeWF,       (* for sync-up *)
                                    0ns,
                                    t[tcCI] + 15ns,
                                    t[tcCI] + 20ns);


         others:
           WaveSetEdgeStrobe       (SH3strobeWF,       (* for sync-up *) 
                                    0ns,
                                    t[tcCI]-5ns,
                                    t[tcCI]-3ns  );
       end;

       case actable of
         TIhifrqloose10ACTable:
             WaveSetEdgeStrobe       (SyncH3HstrobeWF,   (* for sync-up *)
                                      0ns,
                                      t[tcH]-9ns,
                                      t[tcH]-6ns);

         others:
             WaveSetEdgeStrobe       (SyncH3HstrobeWF,   (* for sync-up *)
                                      0ns,
                                      t[tcH]-12ns,
                                      t[tcH]-6ns);
       end;

        WaveSetEdgeStrobe       (SyncH3LstrobeWF,   (* for sync-up *)
                            0ns,
                            2ns,
                            8ns);
{
        WaveSetNR           (INT_driveWF,
			    0ns);
}
        WaveSetNR           (INT_driveWF,
                            t[tcCI]-t[tcCI]); 

        if schmoo then
          WaveSetNR         (INT_CLKSTPdriveWF,
                            0ns)
        else
          WaveSetNR         (INT_CLKSTPdriveWF,
                            t[tcCI]-t[tsuINTCLKSTP]+dtcf+1ns); (* added 1ns for 10Mhz eval *)

        EdgeSet             (INT_BdriveWF, Edge1, DriveData,
                            t[tcCI]-t[tsuINT]-loosesetup+dtcf);
        EdgeSet             (INT_BdriveWF, Edge2, DriveHigh,
                            t[tcH]+t[tcCI]-t[tsuINT]-loosesetup+dtcf);

        WaveSetNR           (MCBLdriveWF,
                            t[tMCMP]);

        WaveSetNR           (SHZ_driveWF,
                            t[tMCMP]);
{
       case actable of
         TIhifrqloose10ACTable,
         TIhifrqloose13ACTable,
         TIhifrqloose16ACTable:

}
           WaveSetStrobe       (SHZ_ABUSstrobeWF,
                                0ns,1ns,5ns);
{
           EdgeSetDelayData    (SHZ_ABUSstrobeWF,
                                Edge1, ChanFirst,
                                StrobeData, ThreshVITL,
                                t[tcH]-9ns,0,
                                StrobeData, ThreshVITH,
                                t[tcH]-9ns,0);

 
        others:
           EdgeSetDelayData    (SHZ_ABUSstrobeWF,
                                Edge1, ChanFirst,
                                StrobeData, ThreshVITL,
		   	        t[tcH]-12ns,0,
                                StrobeData, ThreshVITH,
			        t[tcH]-12ns,0);
      end;

        EdgeSetDelayData    (SHZ_ABUSstrobeWF,
                            Edge2, ChanFirst,
                            StrobeOff, ThreshVITL,
			    t[tcH]-5ns,0,
                            StrobeOff, ThreshVITH,
			    t[tcH]-5ns,0);
}
	case actable of
          TIIDDQACTable,
	  TIstressACTable:

            WaveSetNR       (TCLKdriveWF,
                             t[tsuTCLK]-1ns); 

	  others:

            WaveSetRTO      (TCLKdriveWF,
                            t[tsuTCLK],
                            (9*t[tcH]) div 10 );

       end; (* case *)

       case actable of
          TIvboxloACTable:
            WaveSetStrobe  (TCLKstrobeWF,
                            0ns,
                            t[tdTCLK]+20ns,
                            t[tdTCLK]+30ns);
          others:
            WaveSetStrobe  (TCLKstrobeWF,
                            0ns,
                            t[tdTCLK]+loosetclk+ctcf,
                            t[tdTCLK]+loosetclk+3ns+ctcf);
       end;

        WaveSetStrobe       (STCLKstrobeWF,
                            0ns,
                            t[tcCI],
                            t[tcH]-7ns);

        case actable of
          TIIDDQACTable,
	  TIstressACTable:

            WaveSetNR       (TIMGPIOdriveWF,
                            t[tcCI]-t[tsuTCLKGPIO]-loosesetup+dtcf);
          others:
            WaveSetNR       (TIMGPIOdriveWF,
                            t[tcCI]-t[tsuTCLKGPIO]-loosesetup+dtcf);

        end; (* case *)
        WaveSetStrobe       (TIMGPIOstrobeWF,
                            0ns,
                            t[tdTCLKGPIO]+loosestbdly-ctcf,
                            t[tdTCLKGPIO]+loosestbdly+10ns+ctcf);

	EdgeSet      (DUMPclkWF,Edge1,DriveHigh,0ns);
	EdgeSet      (DUMPclkWF,Edge2,DriveLow,t[twCIH]);
	EdgeSet      (DUMPclkWF,Edge3,DriveHigh,t[twCIH]+t[twCIL]);
	EdgeSet      (DUMPclkWF,Edge4,DriveLow,2*t[twCIH]+t[twCIL]);
	EdgeSetOrigin(DUMPclkWF,Edge1,orgH1L);  
	EdgeSetOrigin(DUMPclkWF,Edge2,orgH1L);  
	EdgeSetOrigin(DUMPclkWF,Edge3,orgH1L);  
	EdgeSetOrigin(DUMPclkWF,Edge4,orgH1L);  


        EdgeSetDelayData(TESTdriveWF,
                           Edge1, ChanFirst,
                           DriveData, ThreshVITH,
		           t[tTEST],0,
                           DriveData, ThreshVITL,
		           t[tTEST],0);

        EdgeSetDelayData(TEST1driveWF,
                           Edge1, ChanFirst,
                           DriveData, ThreshVITH,
		           t[tTEST],0,
                           DriveData, ThreshVITL,
		           t[tTEST],0);
 

       case actable of
         TIhifrqloose10ACTable:
           WaveSetStrobe       (TESTstrobeWF,
                                t[tcCI],
                                t[tcH]-9ns,
                                t[tcH]);

         others:
           WaveSetStrobe       (TESTstrobeWF,
                                t[tcCI],
                                t[tcH]-10ns,
                                t[tcH]);
        end;

        WaveSetContinue     (ContinueWF);

        WaveSetOff          (ALLoffWF,6ns,6ns); (*Replaced 15ns with 6ns for schmoo to run to 20ns *)

        WaveSetNR           (RESETHIGH_driveWF,
                            t[tcCI]-t[tsuRESETHH1L]+dtcf);

        WaveSetNR           (RESET_driveWF,
                            t[tsuRESET_]+dtcf);
        EdgeSetOrigin       (RESET_driveWF,Edge1,orgH1L);



           WaveSetStrobe       (IACK_strobeWF,
                                0ns,
                                t[tdH1HIACKL],
                                t[tdH1HIACKL] + 4ns);
           EdgeSetOrigin       (IACK_strobeWF,Edge2,orgH1H);
           EdgeSetOrigin       (IACK_strobeWF,Edge3,orgH1H);

        case actable of
          TIvboxloACTable:
             WaveSetStrobe       (RW_strobeWF,
                                  0ns,
                                  t[tdH1HRWLmax]+20ns, 
                                  t[tdH1HRWLmax]+30ns);


          TInomlooseACTable:
             WaveSetStrobe       (RW_strobeWF,
                                  0ns,
                                  t[tdH1HRWLmax]+15ns +5ns, (** added +5ns for probe **)
                                  t[tdH1HRWLmax]+18ns +5ns);(** added +5ns for probe **)

            TIvboxhiACTable:
             WaveSetStrobe       (RW_strobeWF,
                                  0ns,
                                  t[tdH1HRWLmax]+15ns,
                                  t[tdH1HRWLmax]+18ns);


          TIhifrqloose10ACTable,
          TIhifrqloose13ACTable:
             begin
               WaveSetStrobe       (RW_strobeWF,
                                    0ns,
                                    t[tdH1HRWLmax]+ctcf,
                                    t[tdH1HRWLmax]+ctcf+1.5ns); (* based on probe lot on 112901 *)
               EdgeSetOrigin       (RW_strobeWF,Edge2,orgH1H);
               EdgeSetOrigin       (RW_strobeWF,Edge3,orgH1H);
             end;

          TIhifrqloose16ACTable:
             begin
               WaveSetStrobe       (RW_strobeWF,
                                    0ns,
                                    t[tdH1HRWLmax]-1.0ns,
                                    t[tdH1HRWLmax]-1.0ns+3.0ns);
               EdgeSetOrigin       (RW_strobeWF,Edge2,orgH1H);
               EdgeSetOrigin       (RW_strobeWF,Edge3,orgH1H);
             end;

          others:
             WaveSetStrobe       (RW_strobeWF,
                                  0ns,
                                  t[tdH1HRWLmax],
                                  t[tdH1HRWLmax]+2ns);
        end;   


{
        WaveSetNR           (HOLD_driveWF,0ns);
}
        WaveSetNR           (HOLD_driveWF,
                            t[tcCI]-t[tsuHOLD_min]-dtcf); 

        EdgeSet             (HOLD_BdriveWF, Edge1, DriveHigh,
                            t[tcCI]-t[tsuHOLD_min]-loosesetup+dtcf);

        EdgeSetDelayData    (HOLDA_strobeWF,
                            Edge1, ChanFirst,
                            StrobeData, ThreshVITL,
                            t[tcCI]+t[tvHOLDA_]+loosestbdly+2ns-ctcf,0,
                            StrobeData, ThreshVITH,
                            t[tcCI]+t[tvHOLDA_]+loosestbdly+2ns-ctcf,0);

        case actable of
          TIIDDQACTable:

            EdgeSetDelayData  (HOLDA_strobeWF,
                            Edge2, ChanFirst,
                            StrobeOff, ThreshVITL,
                            t[tcCI]+t[tvHOLDA_]+loosestbdly+6ns,0,
                            StrobeOff, ThreshVITH,
                            t[tcCI]+t[tvHOLDA_]+loosestbdly+6ns,0);
          others:
            EdgeSetDelayData  (HOLDA_strobeWF,
                            Edge2, ChanFirst,
                            StrobeOff, ThreshVITL,
			    ((9*t[tcH]) div 10 )-ctcf,0,
                            StrobeOff, ThreshVITH,
			    ((9*t[tcH]) div 10 )-ctcf,0);
        end; (* case *)

        WaveSetStrobe       (HOLDSTRB_HstrobeWF,
                            t[tcCI]+t[tdH1LSHH]+loosestbdly-ctcf,
                            t[tcCI]+t[tdH1LSHH]+loosestbdly-ctcf,
                            ((9*t[tcH]) div 10)+ctcf);

        WaveSetStrobe       (HOLDSTRB_strobeWF,
                            t[tcCI]+t[tenH1LS]+loosestbdly+ctcf,
                            t[tcCI]+t[tenH1LS]+loosestbdly+ctcf,
                            ((9*t[tcH]) div 10)+ctcf);

        EdgeSet             (HOLDABUSstrobeWF, Edge1, StrobeOff,
                            t[tcCI]-2ns-looseoffdly+ctcf);

        EdgeSet             (HOLDABUSstrobeWF, Edge2, StrobeData,
                            t[tcCI]+t[tenH1LA]+loosestbdly-ctcf);

	WaveSetStrobe	    (HOLDRW_strobeWF,
                            t[tcCI]+t[tenH1LRW]+loosestbdly-ctcf,
                            t[tcCI]+t[tenH1LRW]+loosestbdly-ctcf,
                            ((9*t[tcH]) div 10)+ctcf);

        case actable of 
          TIhifrqloose13ACTable,
          TIhifrqloose16ACTable: 
           begin
             WaveSetRTO( RDY_driveWF,
              t[tcCI]-t[tsuRDYmin],
              t[tcCI]);
              EdgeSetOrigin       (RDY_driveWF,Edge2,orgH1L);
           end;
        others:
        WaveSetNR       (RDY_driveWF,
                             t[tcCI]);
        end;

        WaveSetNR           (RDY_driveNRWF,
                            t[tcH]-t[tsuRDYmin]-loosesetup+dtcf); 


        case actable of
          TIhifrqloose10ACTable:
           begin
               EdgeSet             (ABUSstrobeWF, Edge1, StrobeData, t[tdH1LAmax]);
               EdgeSet             (ABUSstrobeWF, Edge2, StrobeOff, t[tdH1LAmax]+4ns);
               EdgeSetOrigin       (ABUSstrobeWF,Edge1,orgH1L);
               EdgeSetOrigin       (ABUSstrobeWF,Edge2,orgH1L);


               EdgeSet             (ABUSbstrobeWF, Edge1, StrobeData,t[tdH1LAmax]);
               EdgeSet             (ABUSbstrobeWF, Edge2, StrobeOff, t[tdH1LAmax]+1ns);


               EdgeSet             (HOLDABUSstrobeWF, Edge1, StrobeData,t[tenH1LA]+ctcf);
               EdgeSet             (HOLDABUSstrobeWF, Edge2, StrobeOff, t[tenH1LA]+3ns+ctcf);
               EdgeSetOrigin       (HOLDABUSstrobeWF,Edge1,orgH1L);
               EdgeSetOrigin       (HOLDABUSstrobeWF,Edge2,orgH1L);

               WaveSetStrobe       (HOLDRW_strobeWF,
                                   0ns,
                                   t[tenH1LRW],
                                   t[tenH1LRW]+4ns);
               EdgeSetOrigin       (HOLDRW_strobeWF,Edge2,orgH1L);
               EdgeSetOrigin       (HOLDRW_strobeWF,Edge3,orgH1L);


               WaveSetStrobe       (HOLDSTRB_strobeWF,
                                   0ns,
                                   t[tenH1LS]+ctcf,
                                   t[tenH1LS]+4ns+ctcf);
               EdgeSetOrigin       (HOLDSTRB_strobeWF,Edge2,orgH1L);
               EdgeSetOrigin       (HOLDSTRB_strobeWF,Edge3,orgH1L);


           end;

          TIhifrqloose13ACTable,
          TIhifrqloose16ACTable:  
           begin
               EdgeSet             (ABUSstrobeWF, Edge1, StrobeData, t[tdH1LAmax]);
               EdgeSet             (ABUSstrobeWF, Edge2, StrobeOff, t[tdH1LAmax]+4ns);
               EdgeSetOrigin       (ABUSstrobeWF,Edge1,orgH1L);
               EdgeSetOrigin       (ABUSstrobeWF,Edge2,orgH1L);

               EdgeSet             (ABUSbstrobeWF, Edge1, StrobeData,t[tdH1LAmax]);
               EdgeSet             (ABUSbstrobeWF, Edge2, StrobeOff, t[tdH1LAmax]+1ns);

               EdgeSet             (HOLDABUSstrobeWF, Edge1, StrobeData,t[tenH1LA]+ctcf);
               EdgeSet             (HOLDABUSstrobeWF, Edge2, StrobeOff, t[tenH1LA]+3ns+ctcf);
               EdgeSetOrigin       (HOLDABUSstrobeWF,Edge1,orgH1L);
               EdgeSetOrigin       (HOLDABUSstrobeWF,Edge2,orgH1L);

               WaveSetStrobe       (HOLDRW_strobeWF,
                                   0ns,
                                   t[tenH1LRW],
                                   t[tenH1LRW]+4ns);
               EdgeSetOrigin       (HOLDRW_strobeWF,Edge2,orgH1L);
               EdgeSetOrigin       (HOLDRW_strobeWF,Edge3,orgH1L);


               WaveSetStrobe       (HOLDSTRB_strobeWF,
                                   0ns, 
                                   t[tenH1LS]+ctcf,
                                   t[tenH1LS]+4ns+ctcf);
               EdgeSetOrigin       (HOLDSTRB_strobeWF,Edge2,orgH1L);
               EdgeSetOrigin       (HOLDSTRB_strobeWF,Edge3,orgH1L);


            end;

         TIvboxhiACTable:
            begin
               EdgeSet             (ABUSstrobeWF, Edge1, StrobeData, t[tcCI]+t[tdH1LAmax]);
               EdgeSet             (ABUSstrobeWF, Edge2, StrobeOff, t[tcCI]+t[tdH1LAmax] +4ns);
               EdgeSetOrigin       (ABUSstrobeWF,Edge1,orgH1L);
               EdgeSetOrigin       (ABUSstrobeWF,Edge2,orgH1L);

               EdgeSet             (ABUSbstrobeWF, Edge1, StrobeOff,8ns);

            end;

        TIvboxloACTable:
            begin
              EdgeSet             (ABUSstrobeWF, Edge1, StrobeData,t[tcCI]-20ns);
              EdgeSet             (ABUSstrobeWF, Edge2, StrobeOff,t[tcCI]-10ns);
              EdgeSetOrigin       (ABUSstrobeWF,Edge1,orgH1L);
              EdgeSetOrigin       (ABUSstrobeWF,Edge2,orgH1L);

              EdgeSet             (ABUSbstrobeWF, Edge1, StrobeOff,8ns);
             end;

          others:
            begin
              EdgeSet       (ABUSstrobeWF, Edge1, StrobeOff,t[tcCI]);

              EdgeSet       (ABUSstrobeWF, Edge2, StrobeData,
                            t[tcCI]+t[tdH1LAmax]+loosestbdly+sp-ctcf+3ns+10ns); (** added +10ns for probe **) 
  

        EdgeSet             (ABUSbstrobeWF, Edge1, StrobeOff,
                            8ns);

            end;
        end; (* of case *)


        EdgeSet             (ABUSwrtendstrobeWF, Edge1, StrobeOff,
                            t[tcCI]+ctcf);


       
       case actable of
         TIhifrqloose10ACTable:
          begin
             EdgeSet             (ABUSwrtbgnstrobeWF, Edge1, StrobeData,
                                  t[tdH1HAWmax]+loosewrtbgnAdly); 
             EdgeSet             (ABUSwrtbgnstrobeWF, Edge2, StrobeOff,
                                 t[tdH1HAWmax]+loosewrtbgnAdly-ctcf+5ns); 
          end;
         others:
          begin
              EdgeSet             (ABUSwrtbgnstrobeWF, Edge1, StrobeData,
                                   t[tdH1HAWmax]+loosewrtbgnAdly-ctcf+10ns ); (** added +10ns for probe **)
              EdgeSet             (ABUSwrtbgnstrobeWF, Edge2, StrobeOff,
                                 t[tdH1HAWmax]+loosewrtbgnAdly-ctcf+2ns+10ns); (** added +10ns for probe **)
          end;
        end;

        WaveSetNR( CLKMDSELdriveWF, 2.0ns );
        WaveSetNR( EDGEMDdriveWF,   2.0ns );
        WaveSetNR( RSVdriveWF,      2.0ns );

        WaveSetRTO          (TCKdriveWF,
                            0ns,
                            t[tcCI]);

       case actable of
         TIhifrqloose10ACTable:
            WaveSetNR        (TDITMSdriveWF,
                              t[tcCI]-t[tsuTDITMS]+1ns);
         others:
            WaveSetNR	     (TDITMSdriveWF,
		  	      t[tcCI]-t[tsuTDITMS]-1ns);
      end;


        WaveSetNR           (JTAGdriveWF,
                            t[tJTAG]);

        WaveSetStrobe       (TDOstrobeWF,
                            0ns,
                            t[tdTDO]+10ns,
                            t[tdTDO]+15ns);



        case actable of
          TIstressACTable:
            WaveSetNR       (DBUSdriveWF,
                            7ns);
          TIIDDQACTable:

            WaveSetNR       (DBUSdriveWF,
                            t[tcCI]-t[tsuDRmin]);


(* Nanoseconds were added to the DBUS hold time (above/below) to adjust   *)
(* for tester error as measured with a Tektronix 644A digital scope on    *)
(* both MT011 and PL061.  960722 K.Delling                                *)
{

Graphical representaion of tester error.

             ----------                         ----------  H1
            /.         \                       /.
           / .          \                     / .
          /  .           \                   /  .
   ------/------         -\-----------------/-------------  DBUS    
        /    .  \       /  \               /    .
       /     .   ------x    x <--H1L      /     .
      /      .         |    |\           /      .
   ---       .         |    | -----------       .
             .         |    |                   .
             .         |<-->| -3ns              .
            0ns        |    |                 t[tcH]
			thDR 


Graphical representation of thDR with WF adjustment (+3ns).

             ----------                         ----------  H1
            /.         \                       /.
           / .          \                     / .
          /  .           \                   /  . 
   ------/------          \   --------------/-------------  DBUS    
        /    .  \          \ /             /    .
       /     .   -----------x <--H1L      /     .
      /      .              |\           /      .
   ---      0ns             | -----------     t[tcH]
                            |                
                         -->|<-- 0ns (data sheet)
                            |         ^^^^^^^^^^
			   thDR 
}

          TIhifrqloose10ACTable:
           begin
             WaveSetRTO( DBUSdriveWF,t[tcCI]-t[tsuDRmin]-dtcf, t[tcCI]+1ns+dtcf );

             EdgeSet             (DBUSstrobeWF, Edge1, DriveOff,2ns);
             EdgeSet             (DBUSstrobeWF, Edge2, StrobeData,t[tvDWmax]);
             EdgeSet             (DBUSstrobeWF, Edge3, StrobeOff,t[tvDWmax]+t[tcCI]);
             EdgeSetOrigin       (DBUSstrobeWF,Edge2,orgH1L);
             EdgeSetOrigin       (DBUSstrobeWF,Edge3,orgH1L);

           end;


          TIhifrqloose16ACTable,
          TIhifrqloose16DIV2ACTable,
	  TIhifrqloose13ACTable,
          TIhifrqloose13DIV2ACTable:
           begin
             WaveSetRTO( DBUSdriveWF,t[tcCI]-t[tsuDRmin]-dtcf-1ns, t[tcCI]+1ns+dtcf ); 


        EdgeSet             (DBUSstrobeWF, Edge1, DriveOff,2ns);
        EdgeSet             (DBUSstrobeWF, Edge2, StrobeData,t[tvDWmax]);
        EdgeSet             (DBUSstrobeWF, Edge3, StrobeOff,t[tvDWmax]+t[tcCI]);
        EdgeSetOrigin       (DBUSstrobeWF,Edge2,orgH1L);
        EdgeSetOrigin       (DBUSstrobeWF,Edge3,orgH1L);

           end;

          others:
            begin
             WaveSetRTO( DBUSdriveWF, 0ns, t[tper] - 10ns +1ns );  (* && Change to RTO waveform for characterization -- 3/30/00 -- SC *) 
                                                                   (* Added +1ns for 10Mhz eval *)


        EdgeSet             (DBUSstrobeWF, Edge1, DriveOff,2ns);
        EdgeSet             (DBUSstrobeWF, Edge2, StrobeData,t[tcCI] + t[tvDWmax]+5ns);
        EdgeSet             (DBUSstrobeWF, Edge3, StrobeOff,t[tcCI] + t[tvDWmax] +15ns);
        EdgeSetOrigin       (DBUSstrobeWF,Edge2,orgH1L);
        EdgeSetOrigin       (DBUSstrobeWF,Edge3,orgH1L);

           end;
         end; (* end case *)

        EdgeSetDelayData    (DBUSendstrobeWF,
                            Edge1, ChanFirst,
                            StrobeOff, ThreshVITL,
                            t[tcH]+t[thDWmin]-looseoffdly+ctcf,0,
                            StrobeOff, ThreshVITH,
                            t[tcH]+t[thDWmin]-looseoffdly+ctcf,0);


        case actable of
           TIIDDQACTable:
            begin

        EdgeSet             (DBUSstrobeWF, Edge1, DriveOff,2ns);
        EdgeSet             (DBUSstrobeWF, Edge2, StrobeData,t[tcCI] + t[tvDWmax]+5ns);
        EdgeSet             (DBUSstrobeWF, Edge3, StrobeOff,t[tcCI] + t[tvDWmax] +15ns);

              WaveSetStrobe (STRB_strobeWF,
                        t[tcCI] - 2ns,
                        t[tcCI]+t[tdH1LSLmax]+4ns+loosestbdly,
                        t[tcCI]+t[tdH1LSLmax]+6ns+loosestbdly);

              WaveSetStrobe (STRB_astrobeWF,
                        t[tcCI] - 2ns,
                        t[tcCI]+t[tdH1LSLmax]+4ns+loosestbdly,
                        t[tcCI]+t[tdH1LSLmax]+6ns+loosestbdly);
            end;
           TIvboxhiACTable:
             begin
              WaveSetStrobe (STRB_strobeWF,
                        t[tcCI] - 2ns,
                        t[tcCI]+t[tdH1LSLmax]+9ns+loosestbdly,
                        t[tcCI]+t[tdH1LSLmax]+11ns+loosestbdly);

                WaveSetStrobe (STRB_astrobeWF,
                        t[tcCI] - 2ns,
                        t[tcCI]+t[tdH1LSLmax]+4ns+loosestbdly,
                        t[tcCI]+t[tdH1LSLmax]+5ns+loosestbdly);

             end;

           TInomlooseACTable:
             begin
              WaveSetStrobe (STRB_strobeWF,
                        t[tcCI] - 2ns,
                        t[tcCI]+t[tdH1LSLmax]+9ns+loosestbdly,
                        t[tcCI]+t[tdH1LSLmax]+11ns+loosestbdly);

                WaveSetStrobe (STRB_astrobeWF,
                        t[tcCI] - 2ns,
                        t[tcCI]+t[tdH1LSLmax]+4ns+loosestbdly,
                        t[tcCI]+t[tdH1LSLmax]+5ns+loosestbdly);

             end;


           TIvboxloACTable:
             begin
              WaveSetStrobe (STRB_strobeWF,
                        t[tcCI] - 2ns,
                        t[tdH1LSLmax],
                        t[tdH1LSLmax]+8ns);
                 EdgeSetOrigin(STRB_strobeWF, Edge2, orgH1L);
                 EdgeSetOrigin(STRB_strobeWF, Edge3, orgH1L);


                WaveSetStrobe (STRB_astrobeWF,
                        t[tcCI] - 2ns,
                        t[tcCI]+t[tdH1LSLmax]+4ns+loosestbdly,
                        t[tcCI]+t[tdH1LSLmax]+5ns+loosestbdly);

             end;


           TIhifrqloose10ACTable:
              begin

                 WaveSetStrobe (STRB_strobeWF,
                        t[tcCI] - 4ns,
                        t[tdH1LSHmax]+ctcf,
                        t[tdH1LSHmax]+2ns);
                 EdgeSetOrigin(STRB_strobeWF, Edge2, orgH1L);
                 EdgeSetOrigin(STRB_strobeWF, Edge3, orgH1L);

                 WaveSetStrobe (STRB_astrobeWF,
                        t[tcCI] - 4ns,
                        t[tenH1LS]+ctcf,
                        t[tenH1LS]+2ns);
                 EdgeSetOrigin(STRB_astrobeWF, Edge2, orgH1L);
                 EdgeSetOrigin(STRB_astrobeWF, Edge3, orgH1L);
              end;


           TIhifrqloose13ACTable,
           TIhifrqloose16ACTable:
              begin

                 WaveSetStrobe (STRB_strobeWF,
                        t[tcCI] - 4ns,
                        t[tdH1LSHmax]+ctcf,
                        t[tdH1LSHmax]+2ns);
                 EdgeSetOrigin(STRB_strobeWF, Edge2, orgH1L);
                 EdgeSetOrigin(STRB_strobeWF, Edge3, orgH1L);

                 WaveSetStrobe (STRB_astrobeWF,
                        t[tcCI] - 4ns,
                        t[tenH1LS]+ctcf,
                        t[tenH1LS]+2ns);
                 EdgeSetOrigin(STRB_astrobeWF, Edge2, orgH1L);
                 EdgeSetOrigin(STRB_astrobeWF, Edge3, orgH1L);
              end;

           others:
             begin
               WaveSetStrobe (STRB_strobeWF,
                        t[tcCI] - 2ns,
                        t[tcCI]+t[tdH1LSLmax]+4ns+loosestbdly,
                        t[tcCI]+t[tdH1LSLmax]+5ns+loosestbdly);

                WaveSetStrobe (STRB_astrobeWF,
                        t[tcCI] - 2ns,
                        t[tcCI]+t[tdH1LSLmax]+4ns+loosestbdly,
                        t[tcCI]+t[tdH1LSLmax]+5ns+loosestbdly);
             end;
           end; (* end case *)





{
        EdgeSetDelayData    (STRB_astrobeWF,
                            Edge1, ChanFirst,
                            StrobeData, ThreshVITL,
                            t[tcCI]+t[tdH1LSLmax]+loosestbdly-ctcf,0,
                            StrobeData, ThreshVITH,
                            t[tcCI]+t[tdH1LSHmax]+loosestbdly-ctcf,0);

        EdgeSetDelayData    (STRB_astrobeWF,
                            Edge2, ChanFirst,
                            StrobeOff, ThreshVITL,
			    (2*t[tcCI])-ctcf,0,
                            StrobeOff, ThreshVITH,
                            (2*t[tcCI])-ctcf,0);
}
        EdgeSetDelayData    (STRB_bstrobeWF,
                            Edge1, ChanFirst,
                            StrobeData, ThreshVITL,
                            t[tcCI]+t[tdH1LSLmax]+loosestbdly-ctcf,0,
                            StrobeData, ThreshVITH,
                            t[tcCI]+t[tdH1LSHmax]+loosestbdly-ctcf,0);

        EdgeSetDelayData    (STRB_bstrobeWF,
                            Edge2, ChanFirst,
                            StrobeOff, ThreshVITL,
			    (5*t[tcCI]) div 2,0,
                            StrobeOff, ThreshVITH,
                            (5*t[tcCI]) div 2,0);

{kad 960208 added case for 60MHz tables}
	case actable of
          TIstressACTable:
            WaveSetNR       (XFdriveWF,
                            t[tcCI]-t[tsuXF]+dtcf);


          TIIDDQACTable:

            WaveSetNR       (XFdriveWF,
                            t[tcCI]-t[tsuXF]+dtcf);

          TIhifrqloose10ACTable,
          TIhifrqloose16ACTable,
          TIhifrqloose16DIV2ACTable, 
	  TIhifrqloose13ACTable,
          TIhifrqloose13DIV2ACTable:
           begin
            WaveSetRTO     (XFdriveWF,t[tcCI]-t[tsuXF], t[tcCI]);



          end;
          others:
	
        WaveSetNR           (XFdriveWF,
                            20ns);


        end; (* case *)

        WaveSetNR           (XFNRdriveWF,
                            20ns);

        WaveSetStrobe       (XFOIstrobeWF,
                            0ns,
                            t[tcCI]-ctcf-2ns,
                            t[tcCI]+ctcf);

       if actable = TInomlooseACTable then
        WaveSetStrobe       (XFstrobeWF,
                             t[tcCI]-ctcf,
                             t[tcCI]+t[tvH3HXF]+loosestbdly-ctcf,
                             t[tcCI]+t[tvH3HXF]+loosestbdly+ctcf+6ns-2ns)
        else
           begin
             WaveSetStrobe       (XFstrobeWF,
                                 0ns,
                                 t[tvH3HXF]+1ns+ctcf,
                                 t[tvH3HXF]+4ns+ctcf);
             EdgeSetOrigin   (XFstrobeWF, Edge2, orgH1L);
             EdgeSetOrigin   (XFstrobeWF, Edge3, orgH1L);
           end;

        WaveSetStrobe       (XFIOstrobeWF,
                            0ns,
                            0.5ns,
                            t[tdH3HXFIO]);
             EdgeSetOrigin   (XFIOstrobeWF, Edge2, orgH1L);
             EdgeSetOrigin   (XFIOstrobeWF, Edge3, orgH1L);


        if actable = TIstressACTable then
          WaveSetNR         (XF1SIGIdriveWF,
                            t[tcCI]-t[tsuXF1SIGI]-loosesetup+dtcf)
        else 
          WaveSetSBC        (XF1SIGIdriveWF,
			    0ns,
                            t[tcCI]-t[tsuXF1SIGI]-loosesetup+dtcf,
                            t[tcCI]+t[thXF1SIGI]+loosehold-dtcf);

        EdgeSetDelayData    (XF0SIGIstrobeWF,
                            Edge1, ChanFirst,
			    StrobeData, ThreshVITL,
                            t[tcCI]+t[tdH3HXF0L]+loosestbdly-ctcf,0,
			    StrobeData, ThreshVITH,
                            t[tcCI]+t[tdH3HXF0H]+loosestbdly-ctcf,0);

        EdgeSetDelayData    (XF0SIGIstrobeWF,
                            Edge2, ChanFirst,
			    StrobeOff, ThreshVITL,
                            t[tcCI]+t[tdH3HXF0L]+loosestbdly-ctcf+6ns,0,
			    StrobeOff, ThreshVITH,
                            t[tcCI]+t[tdH3HXF0H]+loosestbdly-ctcf+6ns,0);

        if actable = TIstressACTable then
          WaveSetNR         (XF1LDIIdriveWF,
                            t[tcCI]-t[tsuXF1LDII]-loosesetup+dtcf)
        else 
          WaveSetSBC        (XF1LDIIdriveWF,
			    0ns,
                            t[tcCI]-t[tsuXF1LDII]-loosesetup+dtcf,
                            t[tcCI]+t[thXF1LDII]+loosehold-dtcf);

        EdgeSetDelayData    (XF0LDIIstrobeWF,
                            Edge1, ChanFirst,
			    StrobeData, ThreshVITL,
                            t[tcCI]+t[tdH3HXF0L]+loosestbdly-ctcf,0,
			    StrobeData, ThreshVITH,
                            t[tcCI]+t[tdH3HXF0L]+loosestbdly-ctcf,0);

        EdgeSetDelayData    (XF0LDIIstrobeWF,
                            Edge2, ChanFirst,
			    StrobeOff, ThreshVITL,
                            t[tcCI]+t[tcH]-loosestbdly+ctcf,0,
			    StrobeOff, ThreshVITH,
                            t[tcCI]+t[tcH]-loosestbdly+ctcf,0);

        EdgeSetDelayData    (XF0STIIstrobeWF,
                            Edge1, ChanFirst,
			    StrobeData, ThreshVITL,
                            t[tcCI]+t[tdH3HXF0H]+loosestbdly-ctcf,0,
			    StrobeData, ThreshVITH,
                            t[tcCI]+t[tdH3HXF0H]+loosestbdly-ctcf,0);

        EdgeSetDelayData    (XF0STIIstrobeWF,
                            Edge2, ChanFirst,
			    StrobeOff, ThreshVITL,
                            t[tcCI]+t[tcH]-loosestbdly+ctcf,0,
			    StrobeOff, ThreshVITH,
                            t[tcCI]+t[tcH]-loosestbdly+ctcf,0);


              WaveSetNR           (CLKRdriveWF,
                                  t[EXTCLKR] );

        WaveSetStrobe       (CLKRstrobeWF,
                            t[tdH1HCLKR]+loosestbdly-1ns-ctcf,
                            t[tdH1HCLKR]+loosestbdly+2ns-ctcf,
                            t[tcCI]);

        EdgeSet(SCLKRstrobeWF,Edge1,StrobeData,t[tcCI]);
        EdgeSet(SCLKRstrobeWF,Edge2,StrobeOffData,t[tcCI]+6ns);

        WaveSetStrobe       (SyncCLKRHstrobeWF, (* for sync-up *)
                            t[tdH1HCLKR]+loosestbdly-1ns-ctcf,
                            t[tdH1HCLKR]+7ns+loosestbdly-ctcf,
                            t[tdH1HCLKR]+14ns+loosestbdly-ctcf);
        WaveSetStrobe       (SyncCLKRLstrobeWF, (* for sync-up *)
                            t[tdH1HCLKR]+loosestbdly-1ns-ctcf,
                            t[tdH1HCLKR]+7ns+loosestbdly-ctcf,
                            t[tdH1HCLKR]+14ns+loosestbdly-ctcf);


        
        EdgeSet             (FSRdriveWF,Edge1,DriveData,t[tdH1HCLKR]+t[thFSRCLKRL]);
{
        EdgeSetDelayData    (FSRECLKRdriveWF,
                            Edge1, ChanFirst,
                            DriveData, ThreshVITH,
                            t[EXTCLKR]-t[tsuFSRECLKRL]+dtcf,0,
                            DriveData, ThreshVITL,
                            t[EXTCLKR]+t[thFSRECLKRL]-dtcf,0);
}

        EdgeSetDelayData    (FSRECLKRdriveWF,
                            Edge1, ChanFirst,
                            DriveData, ThreshVITH,
                            t[tsuFSRECLKRL]+dtcf,0,
                            DriveData, ThreshVITL,
                            t[thFSRECLKRL]-dtcf,0);

        WaveSetStrobe       (FSRstrobeWF,
                            t[tdSPGPIO]+loosestbdly-ctcf,
                            t[tdSPGPIO]+loosestbdly-ctcf,
                            t[tdSPGPIO]+loosestbdly+10ns-ctcf);
       
            WaveSetSBC        (DRthdriveWF,
                              t[tcH]+t[tdH1HCLKR]-t[tsuDRCLKRL]-loosesetup-7ns+dtcf,
                              t[tcH]+t[tdH1HCLKR]-t[tsuDRCLKRL]-loosesetup+dtcf,
                              t[tcH]+t[tdH1HCLKR]+t[thDRCLKRL]+loosehold-dtcf);
            EdgeSetOrigin     (DRthdriveWF,Edge1,orgtdH1HCLKRL);
            EdgeSetOrigin     (DRthdriveWF,Edge2,orgtdH1HCLKRL);
            EdgeSetOrigin     (DRthdriveWF,Edge3,orgtdH1HCLKRL);

            WaveSetRTZ        (DRdriveWF,
                               t[tcH]-t[tsuDRCLKRL],
                               t[tper]+1ns);        


        if actable = TIstressACTable then
          WaveSetNR       (DRECLKRdriveWF,
                          t[EXTCLKR]+t[tcH]-t[tsuDRECLKRL]-loosesetup+dtcf)

        else
          WaveSetSBC      (DRECLKRdriveWF,
                          t[EXTCLKR]+t[tcH]-t[tsuDRECLKRL]-loosesetup-7ns+dtcf,
                          t[EXTCLKR]+t[tcH]-t[tsuDRECLKRL]-loosesetup+dtcf,
                          t[EXTCLKR]+t[tcH]+t[thDRECLKRL]+loosehold-dtcf);

        WaveSetStrobe       (DRstrobeWF,
                            t[tdSPGPIO]+loosestbdly-ctcf,
                            t[tdSPGPIO]+loosestbdly-ctcf,
                            t[tdSPGPIO]+loosestbdly+10ns-ctcf);

        WaveSetNR           (CLKXdriveWF,
                            t[EXTCLKX]);

        if actable = TIhifrqloose10ACTable then
               WaveSetStrobe       (CLKXstrobeWF,
                                   t[tdH1HCLKX]-2ns,
                                   t[tdH1HCLKX]+2ns,
                                   t[tdH1HCLKX]+5ns)

        else if actable = TIhifrqloose13ACTable then
               WaveSetStrobe       (CLKXstrobeWF,
                                   t[tdH1HCLKX]-2ns,
                                   t[tdH1HCLKX]+3ns,
                                   t[tdH1HCLKX]+6ns)

        else
               WaveSetStrobe       (CLKXstrobeWF,
                                   t[tdH1HCLKX]+loosestbdly-2ns,
                                   t[tdH1HCLKX]+loosestbdly+1ns,
                                   t[tcCI]);


(*XXX*)        EdgeSet(SCLKXstrobeWF,Edge1,StrobeData,t[tcCI]);
               EdgeSet(SCLKXstrobeWF,Edge2,StrobeOffData,t[tcCI]+6ns);

        WaveSetStrobe       (SyncCLKXHstrobeWF,             (* for sync-up *)
                            t[tdH1HCLKX]+loosestbdly-1ns-ctcf,
                            t[tdH1HCLKX]+7ns+loosestbdly-ctcf,
                            t[tdH1HCLKX]+14ns+loosestbdly-ctcf);
        WaveSetStrobe       (SyncCLKXLstrobeWF,              (* for sync-up *)
                            t[tdH1HCLKX]+loosestbdly-1ns-ctcf,
                            t[tdH1HCLKX]+7ns+loosestbdly-ctcf,
                            t[tdH1HCLKX]+14ns+loosestbdly-ctcf);

(* zxc ?? vvv *)
        WaveSetNR           (FSXdriveWF,
                            t[tMCMP]);

        WaveSetNR           (FSXadriveWF,
                            t[tdH1HCLKX]-t[tsuEFSXCLKXHmin]+dtcf);
        EdgeSetOrigin	    (FSXadriveWF,Edge1,orgtdH1HCLKXH);

        if TITestType=Probe then
          EdgeSet 	    (FSXbdriveWF, Edge1, DriveLow,
			     t[tdH1HCLKX] + t[thEFSXCLKXL]+3ns +dtcf)
        else
          EdgeSet 	    (FSXbdriveWF, Edge1, DriveLow,
			     t[tdH1HCLKX] + t[thEFSXCLKXL] +dtcf);
        EdgeSetOrigin	    (FSXbdriveWF,Edge1,orgtdH1HCLKXL);



        WaveSetStrobe       (FSXstrobeWF,
                            0ns,
                            t[tdCLKXHFSXL]+2ns,       (* added +2ns to edge 2&3 for split lot *)     
                            t[tdCLKXHFSXL]+2ns +1ns);     
        EdgeSetOrigin       (FSXstrobeWF,Edge1,orgtdH1HCLKXH);
        EdgeSetOrigin       (FSXstrobeWF,Edge2,orgtdH1HCLKXH);
        EdgeSetOrigin       (FSXstrobeWF,Edge3,orgtdH1HCLKXH);


{
        WaveSetStrobe       (FSXstrobeWF,
                            0ns,
                            1ns,
                            2ns);           (* adjusted based on faster split lot during char *)
        EdgeSetOrigin       (FSXstrobeWF,Edge1,orgtdH1HCLKXH);
        EdgeSetOrigin       (FSXstrobeWF,Edge2,orgtdH1HCLKXH);
        EdgeSetOrigin       (FSXstrobeWF,Edge3,orgtdH1HCLKXH);
}
        EdgeSetDelayData    (FSXECLKXstrobeWF,
                            Edge1, ChanFirst,
                            DriveOff, ThreshVITL,
                            t[EXTCLKX]+t[tdECLKXHFSXL]-5ns-ctcf,0,
                            DriveOff, ThreshVITH,
                            t[EXTCLKX]+t[tdECLKXHFSXH]-5ns-ctcf,0);

        EdgeSetDelayData    (FSXECLKXstrobeWF,
                            Edge2, ChanFirst,
                            StrobeData, ThreshVITL,
                            t[EXTCLKX]+t[tdECLKXHFSXL]-ctcf,0,
                            StrobeData, ThreshVITH,
                            t[EXTCLKX]+t[tdECLKXHFSXH]-ctcf,0);

        EdgeSetDelayData    (FSXECLKXstrobeWF,
                            Edge3, ChanFirst,
                            StrobeOff, ThreshVITL,
                            t[EXTCLKX]+(9*t[tcH] div 10) + ctcf,0,
                            StrobeOff, ThreshVITH,
                            t[EXTCLKX]+(9*t[tcH] div 10) + ctcf,0);

        WaveSetNR           (DXdriveWF,
                            t[tsuSPGPIO]
                            (* t[tMCMP]*) );

        EdgeSet             (EXTDXdriveWF, Edge1, StrobeOff,
                            0ns + ctcf);
        EdgeSet             (EXTDXdriveWF, Edge2, DriveData,
                            t[tMCMP] + ctcf);

        case actable of
         TInomlooseACTable:
          begin
           WaveSetStrobe       (DXstrobeWF,
                               0ns,
                               t[tdCLKXHDX]+10ns,
                               t[tdCLKXHDX]+12ns);
           EdgeSetOrigin            (DXstrobeWF,Edge1,orgtdH1HCLKXH);
           EdgeSetOrigin            (DXstrobeWF,Edge2,orgtdH1HCLKXH);
           EdgeSetOrigin            (DXstrobeWF,Edge3,orgtdH1HCLKXH);
          end;
         TIhifrqloose10ACTable:
          begin
           WaveSetStrobe       (DXstrobeWF,
                                0ns,
                                t[tdCLKXHDX],
                                t[tdCLKXHDX]+3ns);
           EdgeSetOrigin            (DXstrobeWF,Edge1,orgtdH1HCLKXH);
           EdgeSetOrigin            (DXstrobeWF,Edge2,orgtdH1HCLKXH);
           EdgeSetOrigin            (DXstrobeWF,Edge3,orgtdH1HCLKXH);
          end;
        others:
          begin
           WaveSetStrobe       (DXstrobeWF,
                               0ns,
                               t[tdCLKXHDX]+2ns, 
                               t[tdCLKXHDX]+5ns); 
	   EdgeSetOrigin	    (DXstrobeWF,Edge1,orgtdH1HCLKXH);	
	   EdgeSetOrigin	    (DXstrobeWF,Edge2,orgtdH1HCLKXH);	
     	   EdgeSetOrigin	    (DXstrobeWF,Edge3,orgtdH1HCLKXH);	
          end;
       end; (* end case *)



        WaveSetStrobe       (DXastrobeWF,
                            t[tdH1HCLKX]-t[tsuEFSXCLKXHmin]+t[tdFSXDXV]
                              -7ns-ctcf,
                            t[tdH1HCLKX]-t[tsuEFSXCLKXHmin]+t[tdFSXDXV],
                            t[tdH1HCLKX]-t[tsuEFSXCLKXHmin]+t[tdFSXDXV]
                              +15ns+ctcf);
	EdgeSetOrigin	    (DXastrobeWF,Edge1,orgtdH1HCLKXH);
	EdgeSetOrigin	    (DXastrobeWF,Edge2,orgtdH1HCLKXH);
	EdgeSetOrigin	    (DXastrobeWF,Edge3,orgtdH1HCLKXH);

        WaveSetStrobe       (DXECLKXstrobeWF,
                            t[EXTCLKX]+t[tdECLKXHDX]-5ns-ctcf,
                            t[EXTCLKX]+t[tdECLKXHDX]-ctcf,
                            t[EXTCLKX]+t[tdECLKXHDX]-ctcf+6ns);
(*Replaced 9*t[tcH] div 10 + ctcf with t[EXTCLKX]+t[tdECLKXHDX]-ctcf
for schmoo routine to run to 20ns. *)
 (*   DEFINE waveforms for external serial port clock timings *)


	EdgeSet 	    (EXSPCLKXdrive1WF, Edge1, DriveHigh,
			    t[tcH] div 2 + t[tECLKXHduty] + dtcf);
	EdgeSet 	    (EXSPCLKXdrive2WF, Edge1, DriveLow,
			    3*t[tcH] div 4 + t[tECLKXLduty]+ dtcf);
	EdgeSet 	    (EXSPCLKXdrive4WF, Edge1, DriveHigh,
			    t[tECLKXHduty] + dtcf);
	EdgeSet 	    (EXSPCLKXdrive5WF, Edge1, DriveLow,
			    t[tcH] div 4 + t[tECLKXLduty] + dtcf);

	EdgeSet 	    (EXSPCLKRdrive1WF, Edge1, DriveHigh,
			    t[tcH] div 2 + t[tECLKRHduty] +dtcf);
	EdgeSet 	    (EXSPCLKRdrive2WF, Edge1, DriveLow,
			    3*t[tcH] div 4 + t[tECLKRLduty] + dtcf);
	EdgeSet 	    (EXSPCLKRdrive4WF, Edge1, DriveHigh,
			    t[tECLKRHduty] + dtcf);
	EdgeSet 	    (EXSPCLKRdrive5WF, Edge1, DriveLow,
			    t[tcH] div 4 + t[tECLKRLduty] + dtcf);

	EdgeSet 	    (SPCLKXdrive1WF, Edge1, DriveHigh,
			    0ns + t[tECLKXHduty] + dtcf);
	EdgeSet 	    (SPCLKXdrive2WF, Edge1, DriveLow,
			    t[tcH] div 4 + t[tECLKXLduty]+ dtcf);
	EdgeSet 	    (SPCLKXdrive4WF, Edge1, DriveHigh,
			    t[tcH] div 2 + t[tECLKXHduty] + dtcf); (* this was 0ns *)
	EdgeSet 	    (SPCLKXdrive5WF, Edge1, DriveLow,
			    3*t[tcH] div 4 + t[tECLKXLduty] + dtcf);

	EdgeSet 	    (SPCLKRdrive1WF, Edge1, DriveHigh,
			    0ns + t[tECLKRHduty] +dtcf);
	EdgeSet 	    (SPCLKRdrive2WF, Edge1, DriveLow,
			    t[tcH] div 4 + t[tECLKRLduty] + dtcf);
	EdgeSet 	    (SPCLKRdrive4WF, Edge1, DriveHigh,
			    t[tcH] div 2 + t[tECLKRHduty] + dtcf); (* this was 0ns *)
	EdgeSet 	    (SPCLKRdrive5WF, Edge1, DriveLow,
			    3*t[tcH] div 4 + t[tECLKRLduty] + dtcf);

	  WaveSetNR	    (EXFSXdrive1WF,
			    t[tcH] div 2 + t[tECLKXHduty] - 
                                           t[tsuEFSXHECLKXHmin] + dtcf); 

        case actable of
          TIIDDQACTable:

            WaveSetNR	    (EXFSXadrive1WF, 0ns);

          others:
            WaveSetNR	    (EXFSXadrive1WF,
			    t[tcH] div 2 + t[tECLKXHduty] - 1ns + dtcf); 
        end; (* case *)


	  EdgeSet 	    (EXFSXdrive2WF, Edge1, DriveLow,
			    3*t[tcH] div 4 + t[tECLKXLduty] + 
                                             t[thEFSXECLKXL] + dtcf);

	EdgeSet 	    (EXFSXdrive5WF, Edge1, DriveHigh,
			    0ns + dtcf); 

	WaveSetRTZ	    (EXFSRFdrive2WF,
			    3*t[tcH] div 4 + t[tECLKRLduty] - 
                                             t[tsuFSRECLKRL]+dtcf,
			    3*t[tcH] div 4 + t[tECLKRLduty] +
                                             t[thFSRECLKRL]-dtcf);

	EdgeSet 	    (EXFSRdrive1WF,Edge1,DriveData,
			    5*t[tcH] div 4 + t[tECLKRLduty] - 
                                             t[tsuFSRECLKRL]+dtcf);

	EdgeSet 	    (EXFSRdrive2WF,Edge1,DriveLow,
			    t[tcH] div 4 + t[tECLKRLduty] +
                                           t[thFSRECLKRL]+dtcf);

	EdgeSet 	    (EXDXstrobe1WF, Edge1, StrobeOff,
			    t[tcH] div 2 + ctcf);
	EdgeSet 	    (EXDXstrobe1WF, Edge2, StrobeData,
			    t[tcH] div 2 + t[tECLKXHduty] + 
                                           t[tdECLKXHDX] - ctcf);


	EdgeSet 	    (EXDXAstrobe1WF, Edge1, StrobeOff,
			    t[tcH] div 2 + ctcf);
	EdgeSet 	    (EXDXAstrobe1WF, Edge2, StrobeData,
			    t[tcH] div 2 + t[tECLKXHduty] - t[tsuEFSXHECLKXHmin] 
                            + t[tdFSXDXV] - ctcf);

	EdgeSet 	    (EXDXAastrobe1WF, Edge1, StrobeOff,
			    t[tcH] div 2 + ctcf);
	EdgeSet 	    (EXDXAastrobe1WF, Edge2, StrobeData,
			    t[tcH] div 2 + t[tECLKXHduty] + t[tdECHDXV] - ctcf);


	EdgeSet 	    (EXTDXstrobe1WF, Edge1, DriveOff,
			    0ns + ctcf);
	EdgeSet 	    (EXTDXstrobe1WF, Edge2, StrobeOff,
			    0ns + ctcf);
	EdgeSet 	    (EXTDXstrobe1WF, Edge3, StrobeData,
			    0ns + t[tECLKXHduty] + 
                                           t[tdECLKXHDX] - ctcf);

	EdgeSet 	    (EXTDXAstrobe1WF, Edge1, DriveOff,
			    0ns + ctcf);
	EdgeSet 	    (EXTDXAstrobe1WF, Edge2, StrobeOff,
			    0ns + ctcf);
	EdgeSet 	    (EXTDXAstrobe1WF, Edge3, StrobeData,
			    0ns + t[tECLKXHduty] - t[tsuEFSXHECLKXHmin] 
                            + t[tdFSXDXV] - ctcf);

	EdgeSet 	    (EXTDXAastrobe1WF, Edge1, DriveOff,
			    0ns + ctcf);
	EdgeSet 	    (EXTDXAastrobe1WF, Edge2, StrobeOff,
			    0ns + ctcf);
	EdgeSet 	    (EXTDXAastrobe1WF, Edge3, StrobeData,
			    0ns + t[tECLKXHduty] + t[tdECHDXV] - ctcf);
        case actable of 
            TIstressACTable:
                WaveSetNR	    (EXDRdrive2WF,
	             		    3*t[tcH] div 4 + t[tECLKRLduty] -
                                             t[tsuDRECLKRL] + dtcf);
            TIhifrqloose10ACTable:
              WaveSetSBC            (EXDRdrive2WF,
                                     3*t[tcH] div 4 + t[tECLKRLduty] -
                                             t[tsuDRECLKRL] -5ns + dtcf+3ns,
                                     3*t[tcH] div 4 + t[tECLKRLduty] -
                                             t[tsuDRECLKRL] + dtcf,
                                     3*t[tcH] div 4 + t[tECLKRLduty] +
                                             t[thDRECLKRL] - dtcf);
            others:
              WaveSetSBC	    (EXDRdrive2WF,
	               		     3*t[tcH] div 4 + t[tECLKRLduty] -
                                             t[tsuDRECLKRL] -5ns + dtcf,
			             3*t[tcH] div 4 + t[tECLKRLduty] -
                                             t[tsuDRECLKRL] + dtcf,
			             3*t[tcH] div 4 + t[tECLKRLduty] +
                                             t[thDRECLKRL] - dtcf);
        end;

        case actable of
          TIIDDQACTable:
          begin
            EdgeSet            (EXTDRdrive2WF,Edge1,DriveData,
                                0ns+dtcf);
            EdgeSet            (EXTDRdrive2WF,Edge2,DriveComplement,
                                t[tcH] div 4 + t[tECLKRLduty] +
                                t[thDRECLKRL] - dtcf);
          end;
           TIhifrqloose10ACTable:
          begin
            EdgeSet            (EXTDRdrive2WF,Edge1,DriveData,
                                t[tcH] div 4 + t[tECLKRLduty] -
                                t[tsuDRECLKRL] +3ns + dtcf);
            EdgeSet            (EXTDRdrive2WF,Edge2,DriveComplement,
                                t[tcH] div 4 + t[tECLKRLduty] +
                                t[thDRECLKRL] - dtcf);
          end;
          others:
          begin
            EdgeSet            (EXTDRdrive2WF,Edge1,DriveData,
                                t[tcH] div 4 + t[tECLKRLduty] -
                                t[tsuDRECLKRL] +2ns + dtcf);
            EdgeSet            (EXTDRdrive2WF,Edge2,DriveComplement,
                                t[tcH] div 4 + t[tECLKRLduty] +
                                t[thDRECLKRL] - dtcf);
          end;
        end; (* case *)



        case actable of
          TIIDDQACTable:

            WaveSetNR	    (EXFSRVdrive2WF, 0ns);

          TIhifrqloose16ACTable,
          TIhifrqloose16DIV2ACTable,
          TIhifrqloose13ACTable,
          TIhifrqloose13DIV2ACTable: 

            WaveSetNR	    (EXFSRVdrive2WF,
			    3*t[tcH] div 4 - t[tsuFSRECLKRL] - 2ns + dtcf);

          TIhifrqloose10ACTable:
            WaveSetNR       (EXFSRVdrive2WF,
                            3*t[tcH] div 4 - t[tsuFSRECLKRL] - 2ns + dtcf);

          others:
            WaveSetNR	    (EXFSRVdrive2WF,
			    3*t[tcH] div 4 + t[tECLKRLduty] -
                                             t[tsuFSRECLKRL] - 27ns + dtcf +21ns); (* added +21ns for 10mhz Eval *)
        end; (* end case *)

        if actable = TIstressACTable then
          WaveSetNR	    (EXDRdrive5WF,
                            t[tcH] div 4 + t[tECLKRLduty]
                            + 3ns - t[tsuDRECLKRL]+dtcf)
        else
          WaveSetSBC	    (EXDRdrive5WF,
			    0ns+dtcf,
                            t[tcH] div 4 + t[tECLKRLduty]
                            + 3ns - t[tsuDRECLKRL]+dtcf,
			    t[tcH] div 4 + t[tECLKRLduty] + t[thDRECLKRL]-dtcf);

        case actable of
          TIIDDQACTable:

          begin
        EdgeSet             (EXTDRdrive5WF, Edge1, DriveData,
                            0ns+dtcf);
        EdgeSet             (EXTDRdrive5WF, Edge2, DriveComplement,
                            3*t[tcH] div 4 + t[tECLKRLduty] +
                            t[thDRECLKRL]-dtcf);
          end;
          others:
          begin
        EdgeSet             (EXTDRdrive5WF, Edge1, DriveData,
                            3*t[tcH] div 4 + t[tECLKRLduty] -
                            t[tsuDRECLKRL]+dtcf);
        EdgeSet             (EXTDRdrive5WF, Edge2, DriveComplement,
                            3*t[tcH] div 4 + t[tECLKRLduty] +
                            t[thDRECLKRL]-dtcf);
          end;
        end; (* case *)

	EdgeSet 	    (EXDXstrobe4WF, Edge1, StrobeOff,
			    0ns + ctcf);
	EdgeSet 	    (EXDXstrobe4WF, Edge2, StrobeData,
			    t[tdECLKXHDX] + t[tECLKXHduty] - ctcf);

	EdgeSet 	    (EXTDXstrobe4WF, Edge1, DriveOff,
			    0ns + ctcf);
	EdgeSet 	    (EXTDXstrobe4WF, Edge2, StrobeOff,
			    t[tcH] div 2+ t[tECLKXHduty] + ctcf);
	EdgeSet 	    (EXTDXstrobe4WF, Edge3, StrobeData,
			    t[tcH] div 2 + t[tdECLKXHDX] + t[tECLKXHduty] - ctcf);

	EdgeSet 	    (TDDXZstrobeWF, Edge1, StrobeOff,
                            t[tcH] div 2 + t[tdDXZ]);

          WaveSetNR         (DRGPIOdriveWF,
                            t[tsuSPGPIO]-2ns);       (**** && Define as NR WF &&&***)

          WaveSetNR         (DXGPIOdriveWF,
                            t[tsuSPGPIO]-2ns);       (**** && Define as NR WF &&&***)

          WaveSetNR         (FSRGPIOdriveWF,
                            t[tsuSPGPIO]-2ns);       (**** && Define as NR WF &&&***)

          WaveSetNR         (FSXGPIOdriveWF,
                            t[tsuSPGPIO]-2ns);       (**** && Define as NR WF &&&***)

          WaveSetNR         (CLKRGPIOdriveWF,
                            t[tsuSPGPIO]-2ns);       (**** && Define as NR WF &&&***)

          WaveSetNR         (CLKXGPIOdriveWF,
                            t[tsuSPGPIO]-2ns);       (**** && Define as NR WF &&&***)



	WaveSetStrobe       (DRGPIOstrobeWF,
			    0ns,
			    t[tdSPGPIO] + loosestbdly - ctcf,
			    t[tdSPGPIO] + loosestbdly + 20ns + ctcf);


  case actable of
    TIhifrqloose10ACTable:
          WaveSetStrobe       (DXGPIOstrobeWF,
                            0ns,
                            5ns,
                            8ns);
    others:
	 WaveSetStrobe       (DXGPIOstrobeWF,
			    0ns,
			    t[tdSPGPIO] + loosestbdly - ctcf +6ns,    (*& added +6ns for 60Mhz debug &*)
			    t[tdSPGPIO] + loosestbdly + 8ns + ctcf);  (*& changed from +20ns to +8ns for 6\0Mhz debug &*)

    end;
	WaveSetStrobe       (FSRGPIOstrobeWF,
			    0ns,
			    t[tdSPGPIO] + loosestbdly - ctcf,
			    t[tdSPGPIO] + loosestbdly + 20ns + ctcf);


        case actable of
          TIhifrqloose10ACTable:
            WaveSetStrobe   (FSXGPIOstrobeWF,
                            0ns,
                            5ns,
                            8ns);
          others:
       	    WaveSetStrobe   (FSXGPIOstrobeWF,
			    0ns,
			    t[tdSPGPIO] + loosestbdly - ctcf+6ns,     (*& added +6ns for 60Mhz debug &*) 
			    t[tdSPGPIO] + loosestbdly + 8ns + ctcf);  (*& changed from +20ns to +8ns for 60Mhz debug &*)
          end;

	WaveSetStrobe       (CLKRGPIOstrobeWF,
			    0ns,
			    t[tdSPGPIO] + loosestbdly - ctcf,
			    t[tdSPGPIO] + loosestbdly + 5ns + ctcf);

	WaveSetStrobe       (CLKXGPIOstrobeWF,
			    0ns,
			    t[tdSPGPIO] + loosestbdly + ctcf,
			    t[tdSPGPIO] + loosestbdly + 5ns + ctcf);


 (*   DEFINE EDGE STROBES for characterization useage  *)

        WaveSetStrobe       (HOLDTRstrobeWF,
                            0ns,
                            7ns,
			    14ns);

   ACTableClose;

  end; (*with*)
 end;  (* TIACTableSet *)


	(***********************************************************)
	(***		       ACTableSet			 ***)
	(***********************************************************)
	(***							 ***)
	(*** This is the beginning of the ACTableSet procedure.  ***)
	(***							 ***)
	(***********************************************************)



begin (*ACTableSet*)

 if (actable in [TIallACTable, TIhifrqloose10ACTable]) then
  begin
   TIACTableSet( TIhifrqloose10ACTable );
  end;(*if*)


 if (actable in [TIallACTable, TIhifrqspec13ACTable]) then
  begin
   TIACTableSet( TIhifrqspec13ACTable );
  end;(*if*)


 if (actable in [TIallACTable, TIhifrqloose13ACTable]) then
  begin
   TIACTableSet( TIhifrqloose13ACTable );
  end;(*if*)

 if (actable in [TIallACTable, TIhifrqloose13DIV2ACTable]) then
  begin
   TIACTableSet( TIhifrqloose13DIV2ACTable );
  end;(*if*)

 if (actable in [TIallACTable, TIhifrqspec16ACTable]) then
  begin
   TIACTableSet( TIhifrqspec16ACTable );
  end;(*if*)

 if (actable in [TIallACTable, TIhifrqloose16ACTable]) then
  begin
   TIACTableSet( TIhifrqloose16ACTable );
  end;(*if*)

 if (actable in [TIallACTable, TIhifrqloose16DIV2ACTable]) then
  begin
   TIACTableSet( TIhifrqloose16DIV2ACTable );
  end;(*if*)


 if (actable in [TIallACTable, TIparametricACTable]) then
  begin
   TIACTableSet( TIparametricACTable );
  end;(*if*)

    (*									    *)
    (*		      Set up WaveForms for TIstressACTable		    *)
    (*									    *)

 if (actable in [TIallACTable, TIstressACTable]) then
  begin
   TIACTableSet( TIstressACTable );
  end;(*if*)

 if (actable in [TIallACTable, TIlofrqmaxACTable]) then
  begin
   TIACTableSet( TIlofrqmaxACTable );
  end;(*if*)

 if (actable in [TIallACTable, TIlofrqlooseACTable]) then
  begin
   TIACTableSet( TIlofrqlooseACTable );
  end;(*if*)

 if (actable in [TIallACTable, TIhifrqminACTable]) then
  begin
   TIACTableSet( TIhifrqminACTable );
  end;(*if*)

 if (actable in [TIallACTable, TIhifrqmaxACTable]) then
  begin
   TIACTableSet( TIhifrqmaxACTable );
  end;(*if*)

 if (actable in [TIallACTable, TIhifrqlooseACTable]) then
  begin
   TIACTableSet( TIhifrqlooseACTable );
  end;(*if*)

 if (actable in [TIallACTable, TInomlooseACTable]) then
  begin
   TIACTableSet( TInomlooseACTable );
  end;(*if*)


 if (actable in [TIallACTable, TIvboxloACTable]) then
  begin
   TIACTableSet( TIvboxloACTable );
  end;(*if*)

 if (actable in [TIallACTable, TIvboxhiACTable]) then
  begin
   TIACTableSet( TIvboxhiACTable );
  end;(*if*)

 if (actable in [TIallACTable, TIIDDQACTable]) then
  begin
   TIACTableSet( TIIDDQACTable );
  end;(*if*)

end;  (*ACTableSet*)

