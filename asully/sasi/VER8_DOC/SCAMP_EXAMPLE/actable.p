(**************************************************************************)
(***          TMX370E16D16  Program from Standard Mega1 Shell           ***)
(***                                                                    ***)
(***                    File Name:  actable.p                           ***)
(***                    Revision 1.0     14/11/94    - ALFF             ***)
(***                                                                    ***)
(**************************************************************************)
(***                                                                       ***)
(***       Revision History:                                               ***)
(***  06/29/99  jmt  A8  Added RESET_strobeWF for System fg pattern testing***)
(*****************************************************************************)
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
        (*** TIallACTable.                                        ***)
        (***                                                     ***)
        (***********************************************************)

procedure TIACTableSet (actable : ACTable);

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
        (*** For the TMS370 family the ac correction factors are ***)
        (*** mostly implemented in the TimingAdjust function.    ***)
        (***                                                     ***)
        (***********************************************************)

  case TITestType of
    Final_Screen:
      begin
        dtcf := 300ps; (* Drive timing correction factor   *)
        ctcf := 400ps  (* Compare timing correction factor *)
      end;

    others :
      begin
        dtcf :=  0ps;  (* Drive timing correction factor   *)
        ctcf :=  0ps   (* Compare timing correction factor *)
      end

  end;

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

  with ACDataSheets[ actable ] do begin

    ACTableOpen( actable );

      if resetorigins then begin
          if TIScreenPrint then
             writeln('Resetting origins');
          OriginSet(orgclkin ,0ns);
          OriginSet(orgdbgp ,45 * t[Tcy] div 100);
          OriginSet(orgc8,0ns);
      end;
      (********************************************************************)
      (*         Timing and Waveform set-up for all frequencies           *)
      (********************************************************************)

      PeriodSetAll ( t[Tcy] );


      (********************************************************************)
      (*               Clock input and output waveforms                   *)
      (********************************************************************)

	WaveSetNR (NrWF, 0ns );
 {       EdgeSetOrigin(NrWF,Edge1,orgclkin);}
        EdgeResetOrigin(NrWF,Edge1);

        WaveSetDoubleClk ( OSCIN_driveWF, 0, t[Tcy] div 4,
					t[Tcy] div 2, (t[Tcy] div 4)*3 );


	WaveSetRTZ (OSCIN_singleWF,0ns, t[Tcy] div 2);
        EdgeSetOrigin(OSCIN_singleWF,Edge1,orgclkin);
        EdgeSetOrigin(OSCIN_singleWF,Edge2,orgclkin);

	WaveSetRTO (OSCOUT_singleWF,0ns, t[Tcy] div 2);
        EdgeSetOrigin(OSCOUT_singleWF,Edge1,orgclkin);
        EdgeSetOrigin(OSCOUT_singleWF,Edge2,orgclkin);

        WaveSetDoubleClk ( OSCIN_driveWF, 0, t[Tcy] div 4,
					t[Tcy] div 2, (t[Tcy] div 4)*3 );

        WaveSetStrobe (OSCOUT_strobeWF,
        	   t[Tcy]  div 2  ,
        	   t[Tcy]-10ns  ,
                   t[Tcy]-4ns);

        WaveSetStrobe (CLK_strobeWF,
        	( (8*t[Tcy]) div 10) - t[tClkout]-6ns,
        	( (8*t[Tcy]) div 10) - t[tClkout],
        	( (8*t[Tcy]) div 10) + t[tClkout] ); 
        EdgeSetOriginPinList(CLK_strobeWF,Edge1,orgc8,C8_CLKOUT);
        EdgeSetOriginPinList(CLK_strobeWF,Edge2,orgc8,C8_CLKOUT);
        EdgeSetOriginPinList(CLK_strobeWF,Edge3,orgc8,C8_CLKOUT);
        WaveSetStrobe (CLK_matchWF,
        	( (8*t[Tcy]) div 10) - t[tClkout]-6ns,
        	( (8*t[Tcy]) div 10) - t[tClkout],
        	( (8*t[Tcy]) div 10) + t[tClkout] ); 

      (********************************************************************)
      (*                     Interrupt waveforms                          *)
      (********************************************************************)

	WaveSetNR (EXTINT0_driveWF,0ns);
	WaveSetNR (EXTINT1_driveWF,0ns);
	WaveSetNR (EXTINT2_driveWF,0ns);

    	WaveSetStrobe (EXTINT0_strobeWF,
        	0,
        	( (3*t[Tcy]) div 4) - t[tExtint],
        	( (3*t[Tcy]) div 4) + t[tExtint] );

    	WaveSetStrobe (EXTINT1_strobeWF,
        	0,
        	( (3*t[Tcy]) div 4) - t[tExtint],
        	( (3*t[Tcy]) div 4) + t[tExtint] );

    	WaveSetStrobe (EXTINT2_strobeWF,
        	0,
        	( (3*t[Tcy]) div 4) - t[tExtint],
        	( (3*t[Tcy]) div 4) + t[tExtint] );

      (********************************************************************)
      (*                         Reset waveforms                          *)
      (********************************************************************)
 
	WaveSetNR (RESET_driveWF,t[Tcy] div 2);

    WaveSetStrobe (RESET_strobeWF,
        	( (50*t[Tcy]) div 100),
        	( (75*t[Tcy]) div 100),
        	( (75*t[Tcy]) div 100) + 6ns );


      (********************************************************************)
      (*                 Peripheral module pin waveforms                  *)
      (********************************************************************)
      (********************************************************************)
      (*                        debug Port waveforms                      *)
      (********************************************************************)
	WaveSetClk (DPCLK_driveWF,0ns,t[Tcy] div 2);
                   EdgeSetOrigin(DPCLK_driveWF,Edge1,orgdbgp);
                   EdgeSetOrigin(DPCLK_driveWF,Edge2,orgdbgp);

if (TITestTemp = Temp_N40_Degrees_C) then 
begin
    	WaveSetStrobe (C8DPOUT_strobeWF,
        	( (t[Tcy]) div 4)-6ns,
        	( (t[Tcy]) div 4) ,
        	( (t[Tcy]) div 4) + 2 * t[tDPout] );

    	WaveSetStrobe (C16DPOUT_strobeWF,
        	( (t[Tcy]) div 4)-6ns,
        	( (t[Tcy]) div 4) ,
        	( (t[Tcy]) div 4) + 2 * t[tDPout] );

if PJQPack then
     begin 
   	WaveSetStrobe (C8SHFTCLK_strobeWF,
        	( (3*t[Tcy]) div 4)-6ns,
        	( (3*t[Tcy]) div 4),
        	( (3*t[Tcy]) div 4) + 2 * t[tShft] );

    	WaveSetStrobe (C16SHFTCLK_strobeWF,
        	( (3*t[Tcy]) div 4)-6ns,
        	( (3*t[Tcy]) div 4) ,
        	( (3*t[Tcy]) div 4) + 2*t[tShft] );
     end ;
if not PJQPack then
     begin 
     	WaveSetStrobe (C8SHFTCLK_strobeWF,
        	( (3*t[Tcy]) div 4),
        	( (3*t[Tcy]) div 4)+10ns,
        	( (3*t[Tcy]) div 4)+10ns + 2 * t[tShft] );

    	WaveSetStrobe (C16SHFTCLK_strobeWF,
        	( (3*t[Tcy]) div 4),
        	( (3*t[Tcy]) div 4)+10ns ,
        	( (3*t[Tcy]) div 4)+10ns + 2*t[tShft] );
      end;


end else begin	
         WaveSetStrobe (C8DPOUT_strobeWF,
        	( (t[Tcy]) div 2) - t[tDPout]-6ns,
        	( (t[Tcy]) div 2) - t[tDPout],
        	( (t[Tcy]) div 2) + t[tDPout] );

         WaveSetStrobe (C16DPOUT_strobeWF,
        	( (t[Tcy]) div 2) - t[tDPout]-6ns,
        	( (t[Tcy]) div 2) - t[tDPout],
        	( (t[Tcy]) div 2) + t[tDPout] );

    	WaveSetStrobe (C8SHFTCLK_strobeWF,
        	( (3*t[Tcy]) div 4)-6ns,
        	( (3*t[Tcy]) div 4),
        	( (3*t[Tcy]) div 4) + 2 * t[tShft] );

    	WaveSetStrobe (C16SHFTCLK_strobeWF,
        	( (3*t[Tcy]) div 4)-6ns,
        	( (3*t[Tcy]) div 4) ,
        	( (3*t[Tcy]) div 4) + 2*t[tShft] );


        end;
                   EdgeSetOrigin(C16SHFTCLK_strobeWF,Edge1,orgdbgp);
                   EdgeSetOrigin(C16SHFTCLK_strobeWF,Edge2,orgdbgp);
                   EdgeSetOrigin(C16SHFTCLK_strobeWF,Edge3,orgdbgp);

                   EdgeSetOrigin(C8SHFTCLK_strobeWF,Edge1,orgdbgp);
                   EdgeSetOrigin(C8SHFTCLK_strobeWF,Edge2,orgdbgp);
                   EdgeSetOrigin(C8SHFTCLK_strobeWF,Edge3,orgdbgp);

                   EdgeSetOrigin(C8DPOUT_strobeWF,Edge1,orgdbgp);
                   EdgeSetOrigin(C8DPOUT_strobeWF,Edge2,orgdbgp);
                   EdgeSetOrigin(C8DPOUT_strobeWF,Edge3,orgdbgp);
        
                   EdgeSetOrigin(C16DPOUT_strobeWF,Edge1,orgdbgp);
                   EdgeSetOrigin(C16DPOUT_strobeWF,Edge2,orgdbgp);
                   EdgeSetOrigin(C16DPOUT_strobeWF,Edge3,orgdbgp);


      (********************************************************************)
      (*                       Relay control waveforms                    *)
      (********************************************************************)

    	WaveSetStrobe (C8REL_strobeWF,
        	0,
        	( (3*t[Tcy]) div 4) - t[trel],
        	( (3*t[Tcy]) div 4) + t[trel] );

    	WaveSetStrobe (C16REL_strobeWF,
        	0,
        	( (3*t[Tcy]) div 4) - t[trel],
        	( (3*t[Tcy]) div 4) + t[trel] );


      (********************************************************************)
      (*                         SPI waveforms                            *)
      (********************************************************************)

	WaveSetNR (SPIsomi_driveWF,5ns);
	WaveSetNR (SPIsimo_driveWF,5ns);
	WaveSetNR (SPIclk_driveWF,10ns);
	WaveSetNR (SPIstb_driveWF,10ns);

     	WaveSetStrobe (SPIsomi_strobeWF,
        	0,
        	( (3*t[Tcy]) div 4) - t[tspio],
        	( (3*t[Tcy]) div 4) + t[tspio] );
     	WaveSetStrobe (SPIsimo_strobeWF,
        	0,
        	( (3*t[Tcy]) div 4) - t[tspio],
        	( (3*t[Tcy]) div 4) + t[tspio] );
     	WaveSetStrobe (SPIclk_strobeWF,
        	0,
        	( (3*t[Tcy]) div 4) - t[tspio],
        	( (3*t[Tcy]) div 4) + t[tspio] );
     	WaveSetStrobe (SPIstb_strobeWF,
        	0,
        	( (3*t[Tcy]) div 4) - t[tspio],
        	( (3*t[Tcy]) div 4) + t[tspio] );

      (********************************************************************)
      (*                         SCI waveforms                            *)
      (********************************************************************)

	WaveSetNR (SCIrxd_driveWF,0ns);
	WaveSetNR (SCItxd_driveWF,0ns);
	WaveSetNR (SCIclk_driveWF,0ns);

     	WaveSetStrobe (SCItxd_strobeWF,
        	0,
        	( (3*t[Tcy]) div 4) - t[ttxd],
        	( (3*t[Tcy]) div 4) + t[ttxd] );
     	WaveSetStrobe (SCIrxd_strobeWF,
        	0,
        	( (3*t[Tcy]) div 4) - t[trxd],
        	( (3*t[Tcy]) div 4) + t[trxd] );
     	WaveSetStrobe (SCIclk_strobeWF,
        	0,
        	( (3*t[Tcy]) div 4) - t[tuclk],
        	( (3*t[Tcy]) div 4) + t[tuclk] );
    
      (********************************************************************)
      (*                    Digital I/O pins waveforms                    *)
      (********************************************************************)
	WaveSetNR (PORTA_driveWF,0ns);
	WaveSetNR (PORTB_driveWF,0ns);
	WaveSetNR (PORTC_driveWF,0ns);

     	WaveSetStrobe (PORTA_strobeWF,
        	0,
        	( (3*t[Tcy]) div 4) - t[tsio],
        	( (3*t[Tcy]) div 4) + t[tsio] ); 
     	WaveSetStrobe (PORTB_strobeWF,
        	0,
        	( (3*t[Tcy]) div 4) - t[tsio],
        	( (3*t[Tcy]) div 4) + t[tsio] );
     	WaveSetStrobe (PORTC_strobeWF,
        	0,
        	( (3*t[Tcy]) div 4) - t[tsio],
        	( (3*t[Tcy]) div 4) + t[tsio] ); 

	WaveSetNR (GPIO_driveWF,0ns);

	WaveSetStrobe (GPIO_strobeWF,
        	0,
        	( (3*t[Tcy]) div 4) - t[tsgpio],
        	( (3*t[Tcy]) div 4) + t[tsgpio] );

      (********************************************************************)
      (*                       Scan test waveforms                        *)
      (********************************************************************)
	WaveSetNR (C0_driveWF, t[tscanin]);
	WaveSetNR (C1_driveWF, t[tscanin]);
	WaveSetNR (ScanIn_driveWF, t[tscanin]);
        EdgeSetOriginPinList(C0_driveWF,Edge1,orgc8,C8_C0);
        EdgeSetOriginPinList(C1_driveWF,Edge1,orgc8,C8_C1);
        EdgeSetOriginPinList(ScanIn_driveWF,Edge1,orgc8,C8_SI);

if (TITestTemp <> Temp_125_Degrees_C) then 
     	WaveSetStrobe (ScanOut_strobeWF,
        	5ns,
        	( (3*t[Tcy]) div 4) - t[tscanout],
        	( (3*t[Tcy]) div 4) + t[tscanout] )
else      	WaveSetStrobe (ScanOut_strobeWF,
        	( (5*t[Tcy]) div 10),
        	( (75*t[Tcy]) div 100) ,
        	( (75*t[Tcy]) div 100) + 6ns );
        EdgeSetOriginPinList(ScanOut_strobeWF,Edge1,orgc8,C8_C0);
        EdgeSetOriginPinList(ScanOut_strobeWF,Edge2,orgc8,C8_C0);
        EdgeSetOriginPinList(ScanOut_strobeWF,Edge3,orgc8,C8_C0);


     	WaveSetStrobe (SO_matchWF,
        	0,
        	( (3*t[Tcy]) div 4) - t[tscanout],
        	( (3*t[Tcy]) div 4) + t[tscanout] );

   	WaveSetDelayStrobe (ScanOut_nextcyc_strobeWF,
        	5ns,
        	( (3*t[Tcy]) div 4) - t[tscanout] ,
        	( (3*t[Tcy]) div 4) + t[tscanout] ,1,1,1);
        EdgeSetOriginPinList(ScanOut_nextcyc_strobeWF,Edge1,orgc8,C8_SO);
        EdgeSetOriginPinList(ScanOut_nextcyc_strobeWF,Edge2,orgc8,C8_SO);
        EdgeSetOriginPinList(ScanOut_nextcyc_strobeWF,Edge3,orgc8,C8_SO);

      (********************************************************************)
      (*                   General purpose waveforms                      *)
      (********************************************************************)

	WaveSetNR (TEST_driveWF, (t[Tcy] div 2 + t[Tcy] div 3));
        EdgeSetOriginPinList(TEST_driveWF,Edge1,orgc8,C8_TEST);

	WaveSetNR (OSC_driveWF, (t[Tcy] div 2 + t[Tcy] div 3));
      if actable in [Dut83AC_C16Off] then
	EdgeSet (PLL_driveWF,Edge1,DriveHigh, (t[Tcy] div 2 + t[Tcy] div 3))
        else
	WaveSetNR (PLL_driveWF, (t[Tcy] div 2 + t[Tcy] div 3));

	WaveSetNR (VPP_driveWF, (t[Tcy] div 2 + t[Tcy] div 3));

	WaveSetStrobe (VPP_strobeWF, 0, t[Tcy] div 2 , t[Tcy] div 2 + 10ns );

      	WaveSetContinue (ContinueWF);

      	WaveSetOff (OffWF, 0, 0 );


      	WaveSetRTO (RtoT0WF, t[Tcy], 2 * t[Tcy]); (*ScopeSync*)

      (********************************************************************)
      (*                      CAN module waveforms                        *)
      (********************************************************************)
	WaveSetNR (CAN_driveWF, 0  );

	WaveSetStrobe (CAN_strobeWF, 0,  3 * t[Tcy] div 4 ,  
                                        3 * t[Tcy] div 4 + 10ns );
      (********************************************************************)
      (*                      ADC module waveforms                        *)
      (********************************************************************)
       	WaveSetNR (ADC_driveWF, 0ns);

      (********************************************************************)
      (*                      BRL pins   waveforms                        *)
      (********************************************************************)
       	WaveSetNR (C16BRL1_driveWF, 0ns);
     	WaveSetStrobe (C16BRL1_strobeWF,
        	0,
        	( (3*t[Tcy]) div 4) - t[tbrl1],
        	( (3*t[Tcy]) div 4) + t[tbrl1] );

       	WaveSetNR (C16BRL2_driveWF, 0ns);
     	WaveSetStrobe (C16BRL2_strobeWF,
        	0,
        	( (3*t[Tcy]) div 4) - t[tbrl2],
        	( (3*t[Tcy]) div 4) + t[tbrl2] );

       	WaveSetNR (C8BRL1_driveWF, 0ns);
    	WaveSetStrobe (C8BRL1_strobeWF,
        	0,
        	( (3*t[Tcy]) div 4) - t[tbrl1],
        	( (3*t[Tcy]) div 4) + t[tbrl1] );
 
       	WaveSetNR (C8BRL2_driveWF, 0ns);
    	WaveSetStrobe (C8BRL2_strobeWF,
        	0,
        	( (3*t[Tcy]) div 4) - t[tbrl2],
        	( (3*t[Tcy]) div 4) + t[tbrl2] );

      (********************************************************************)
      (*                   SC trigger module waveforms                    *)
      (********************************************************************)
       	WaveSetNR (TO1_driveWF, 0ns);
    	WaveSetStrobe (TO1_strobeWF,
        	0,
        	( (3*t[Tcy]) div 4) - t[ttrig],
        	( (3*t[Tcy]) div 4) + t[ttrig] );

       	WaveSetNR (TO2_driveWF, 0ns);
    	WaveSetStrobe (TO2_strobeWF,
        	0,
        	( (3*t[Tcy]) div 4) - t[ttrig],
        	( (3*t[Tcy]) div 4) + t[ttrig] );

       	WaveSetNR (TO3_driveWF, 0ns);
    	WaveSetStrobe (TO3_strobeWF,
        	0,
        	( (3*t[Tcy]) div 4) - t[ttrig],
        	( (3*t[Tcy]) div 4) + t[ttrig] );

       	WaveSetNR (TO4_driveWF, 0ns);
    	WaveSetStrobe (TO4_strobeWF,
        	0,
        	( (3*t[Tcy]) div 4) - t[ttrig],
        	( (3*t[Tcy]) div 4) + t[ttrig] );

        WaveSetNR (TRIG_driveWF, 0ns);

      (********************************************************************)
      (*                   Timer  module waveforms                        *)
      (********************************************************************)

       	WaveSetNR (Timer_driveWF, 0ns);

     	WaveSetStrobe (Timer_strobeWF,
        	0,
        	( (3*t[Tcy]) div 4) - t[ttimer],
        	( (3*t[Tcy]) div 4) + t[ttimer] ); 

    ACTableClose

  end

end;    (* TIACTableSet *)

 

        (***********************************************************)
        (***                   ACTableSet                        ***)
        (***********************************************************)
        (***                                                     ***)
        (*** This is the beginning of the ACTableSet procedure.  ***)
        (***                                                     ***)
        (***********************************************************)

begin

    (************************************************************************)
    (*                Set up WaveForms for Dut50AC table                    *)
    (************************************************************************)

  if (actable in [TIallACTable, Dut50AC]) then
    TIACTableSet( Dut50AC );

    (************************************************************************)
    (*                Set up WaveForms for Dut67AC table                    *)
    (************************************************************************)

  if (actable in [TIallACTable, Dut67AC]) then
    TIACTableSet( Dut67AC );

    (************************************************************************)
    (*                Set up WaveForms for Dut83AC table                   *)
    (************************************************************************)

  if (actable in [TIallACTable, Dut83AC]) then
    TIACTableSet( Dut83AC );


    (************************************************************************)
    (*                Set up WaveForms for Dut83AC_C16Off table                   *)
    (************************************************************************)

  if (actable in [TIallACTable, Dut83AC_C16Off]) then
    TIACTableSet( Dut83AC_C16Off );

    (************************************************************************)
    (*                Set up WaveForms for Dut100AC table                   *)
    (************************************************************************)

  if (actable in [TIallACTable, Dut100AC]) then
    TIACTableSet( Dut100AC );


    (************************************************************************)
    (*                Set up WaveForms for Dut200AC table                   *)
    (************************************************************************)

  if (actable in [TIallACTable, Dut200AC]) then
    TIACTableSet ( Dut200AC );


    (************************************************************************)
    (*                Set up WaveForms for OpensAC table                    *)
    (************************************************************************)

  if (actable in [TIallACTable, OpensAC]) then
    TIACTableSet( OpensAC );


    (************************************************************************)
    (*                Set up WaveForms for EasyAC table                     *)
    (************************************************************************)

  if (actable in [TIallACTable, EasyAC]) then
    TIACTableSet( EasyAC );

  if (actable in [TIallACTable, DutLooseAC]) then
    TIACTableSet( DutLooseAC );

  if (actable in [TIallACTable, TIsearchlooseACTable]) then
    TIACTableSet( TIsearchlooseACTable );

  if (actable in [TIallACTable, TIsearchACTable]) then
    TIACTableSet( TIsearchACTable );

  if (actable in [TIallACTable, TIfunctionalACTable]) then
    TIACTableSet( TIfunctionalACTable );


end; (* ACTableSet *)
