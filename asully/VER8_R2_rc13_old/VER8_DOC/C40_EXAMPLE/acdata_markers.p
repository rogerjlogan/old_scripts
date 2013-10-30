
procedure SccsIdentificationacdata;
  var
    SccsId	:   String;
  begin
    SccsId:= '@(#) acdata.p 1.6 9/20/93 11:05:26 c TI';
  end;

(******************************************************************************
			SCCS	INFO

	MODULE		: acdata.p
	VERSION NO.	: 1.6
	FILE CREATED	: 9/20/93 11:05:26
	PREVIOUS DELTA  : 9/20/93 11:05:24
	SCCS FILE	: /tmp_mnt/dsp2/hphu/c40/pgm/SCCS/s.acdata.p 
	Copyright	: Texas Instruments, Inc.

******************************************************************************)
(***********************************************************************)
(***                                                                 ***)
(***                      SMJ320C40 TEST PROGRAM                     ***)
(***                      ----------------------                     ***)
(***                                                                 ***)
(***  File Name: acdata.p                                            ***)
(***  Current Revision: N09                                          ***)
(***                                                                 ***)
(***  Revision History:                                              ***)
(***                                                                 ***)
(***   00  04/19/91  Program generation.                             ***)
(***   01  05/01/91  Changed the following timing specs:             ***)
(***                 (req'd to test around glitch problem)           ***)
(***                  t[tdH1LSTAT] from  9ns to 18ns                 ***)
(***                  t[tdH3HLOCK] from 11ns to 17ns                 ***)
(***   02  09/11/91  Updated test types to include IDSEngr           ***)
(***   03  10/01/91  Modified jtag/scan timings                      ***)
(***   04  11/27/91  Updated timings to reflect final preliminary    ***)
(***                 data sheet values                               ***)
(***   05  12/12/91  Added more high frequency test capability       ***)
(***   06  02/26/92  Added new timings for jtag/emulation testing    ***)
(***   07  03/05/92  Changed the following timing specs:             ***)
(***                 (req'd for pg2 preliminary data sheet)          ***)
(***                  t[tdH1LSTAT] from 18ns to  9ns                 ***)
(***                  t[tdH3HLOCK] from 17ns to 11ns                 ***)
(***   08  03/23/92  Changed the following timing:                   ***)
(***                  t[tdH1LAV] from 13ns to 22ns                   ***)
(***                 (so as not to fail due to voltage glitch since  ***)
(***                  this is not a specified data sheet timing)     ***)
(***   09  07/21/92  Updated timings to reflect the 'tmp' data sheet ***)
(***   10  09/03/92  Added 50mhz test capability to the program      ***)
(***   11  09/16/92  Moved 'tgb' timing from acdata.p to actable.p   ***)
(***   12  10/21/92  Changed the following timing specs for TMP:     ***)
(***                  t[tdH1HA]   from  9ns to 13ns                  ***)
(***                  t[tsuIF]    from  8ns to 10ns                  ***)
(***                  t[tvH1LIF]  from 14ns to 15ns                  ***)
(***                  t[tdALRQHt] from 20ns to 21ns                  ***)
(***   13  10/22/92  Added searchlevels and searchlevels40 actables  ***)
(***                 due to changes required for EXPORTRDYPattern    ***)
(***   14  10/23/92  Changed the following timing specs for TMP:     ***)
(***                  t[tdENBAV] from 16ns to 17ns                   ***)
(***   15  10/28/92  Changed the following timing specs for TMP:     ***)
(***                  t[tsuIF]    from 10ns to 11ns                  ***)
(***                  t[tdALRQHt] from 21ns to 22ns                  ***)
(***   16  10/30/92  Changed the following timing specs for TMP:     ***)
(***                  t[tdENBAV] from 17ns to 18ns                   ***)
(***                  t[tvH1LIF] from 15ns to 16ns                   ***)
(***   17  11/13/92  Changed the following timing specs for TMP:     ***)
(***                  t[tdHLHHmin] from 0ns to -1ns (sync problem)   ***)
(***                  t[tdHLHHmax] from 5ns to  4ns (range the same) ***)
(***   18  11/21/92  Updated the reset (tristate) timings to reflect ***)
(***                 the 'tmp' data sheet                            ***)
(***   19  12/02/92  Changed the following timing specs for TMP:     ***)
(***                  t[thCDw] from 2ns to 3ns                       ***)
(***   20  04/04/93  Added 45ns frequency for hifrqloose40 for       ***)
(***                 320c40 at preburnin to screen for Fujitsu units ***)
(***   21  05/10/93  Changed the following timing specs for TMS:     ***)
(***                  t[thCDw] from 3ns to 2ns (.75um material data) ***)
(***   22  06/12/93  Changed the following timinf specs for TMS:     ***)
(***                  t[suRESETH] from 11ns to 13ns                  ***)
(***   23  08/06/93  Added 50ns slow IO datasheet.  Changed period   ***)
(***	   PHQ	     for TIhifrqxxx60ACTable to 50ns.  Added         ***)
(***		     datasheet for TIlofrqxxx60ACTable.  Changed     ***)
(***		     FUJUSU screen at pre_burn from 45ns to 43ns.    ***)
(***                                                                 ***)
(***   24  08/11/93  Changed min clkin-h1/h3 to 2ns for probe and    ***)
(***		     PG3.x devices.  Changed clk-h1 range for SlowIO ***)
(***                 device from 5-13ns to 4-12ns.                   ***)
(***   25  08/12/93  Added tsuDR2 timing parameter for level test.   ***)
(***   26  09/10/93  Changed CLKINHH1 and CLKINHH3min spec from 3ns  ***)
(***                 to 2ns for probe only.  This eliminates GED     ***)
(***                 fallout on fast lots.                           ***)
(***   27  12/11/93  Updated 50Mhz data sheet to match current data  ***)
(***                 book.  Timings that differ from current data    ***)
(***                 sheet:          New Spec     Data Book          ***)
(***                      tdH1LS        9             7              ***)
(***                      tdH1LA        9             7              ***)
(***                      tsuIF        11             8              ***)
(***                      tdH1LSTAT     8             7              ***)
(***                      tdH1LLOCK     8             7              ***)
(***   28  01/19/93  Changed tsuDR to 10ns from 12ns to ensure memory***)
(***                 access requirements.                            ***)
(***   29  05/24/94  Changed CLKINHH1max and CLKINHH3max to 14ns for ***)
(***                 low voltage screen as this spec does not need to***)
(***                 be tested at 3v.  This allows part to sync-up   ***)
(***                 at this low voltage.                            ***)
(***   30  06/23/94  Corrected the tsuTDITMS and tdTDO timing to     ***)
(***                 match data book value for 40ns corners.         ***)
(***                   t[tsuTDITMS] := 10ns                          ***)
(***                   t[tdTDO]     := 15ns;                         ***)
(***   31  06/30/94  Added thH1LIFOI timing to all data sheets for   ***)
(***                 use when IIOF changes from output to input. Spec***)
(***                 needed to disable strobe when H1 falls and data ***)
(***                 on IIOF is invalid.                             ***)
(***   32  01/26/94  Added 60mhz tables.                             ***)
(***   33  04/27/95  Changed limit for TMS320C40TAB50 device on      ***)
(***         HC      parmeter tvH1LIF from 14ns to 16ns.             ***)
(***   34  05/09/95  Changed thCDw timing back to 2ns to match 60mhz ***)
(***          BB     spec as fix is now in place for patterns.       ***)
(***   35  05/10/95  Changed limit fro TMS320C40TAB50 device on      ***)
(***          BB     parameter tvH1LIF to 15ns per military request. ***)
(***   36  05/15/95  Changed 33ns 'max' corners to have 67% duty     ***)
(***          BB     cycle.                                          ***)
(*** 320C40B4:                                                       ***)
(***   37  07/25/95  Added tsuINTIDLE timing used to wake device from***)
(***                 IDLE2 with clocks in correct phase for test.    ***)
(*** 320C40N00:                                                      ***)
(***   00  12/12/95  Created new military SMJ320C40 50MHz test       ***)
(***          RA     program based on the commercial B4 test program.***)
(*** 320C40N01:                                                      ***)
(***   01  01/24/96  Added 60MHz tables to the list of 60MHz timing. ***)
(***          RA     tables=TIhifrqmin33ACTable/TIhifrqmax33ACTable. ***)
(***                 Changed tdTDO strobe edge from 15 to 12ns       ***)
(*** 320C40N02:                                                      ***)
(***   02  04/29/96  Commercial chg tsuINTIDLE 18ns due to marginal  ***)
(***          RR     devices waking up with clock out-of-phase.      ***)
(***                 Chg's in the N02 program are applicable.        ***)
(***                 Put the following AC paramters to the Mil spec: ***)
(***                 Loosened tdH1STAT, tdH1LS, and tdH1LA for 9 to  ***) 
(***                 10ns for 40/50MHz test;                         ***)
(***                 Loosen tdENBDV from 21 to 22ns and tdENBAV from ***)
(***                 18 to 21ns for all speeds; tightened thCDw from ***)
(***                 2 to 1ns for all speeds per errata; Loosen tsuIF***)
(***                 from 11 to 14ns for TAB only errata on all speeds;*)  
(***                 Loosen tsuRESETH from 11 to 13ns per errata;    ***)
(***                 Loosen tsuDR from 10 to 15ns and tsuRDY from    ***)
(***                 20 to 25ns. Added TMS (commercial) 50MHz AC     ***)
(***                 parameters for TMS320C40TAL50 product.          ***)
(*** 320C40N05:      Tightened t[tsuDR] AND t[tsuRDY] to 10          ***)
(*** 05 11/14/96 RA  and 20ns respectively for 50MHz test(per errata).**)  
(*** 320C40N09:      Set tvH1LIF from 18ns to 14ns as per datasheet  ***)
(***    2/23/00 EGM  for 60Mhz (33.3ns).                             ***)
(***********************************************************************)


	(***********************************************************)
	(***               AC Data Sheet Definition              ***)
	(***********************************************************)
	(***                                                     ***)
	(*** The AC Data Sheet consists of a series of calls to  ***)
	(*** a single timing set-up procedure called TITimingSet.***)
	(*** TITimingSet procedure creates an AC Data Sheet each ***)
	(*** time it is called. TITimingSet may be called with   ***)
	(*** any value of period, and will create the correct    ***)
	(*** AC Data Sheet for that period. This is possible on  ***)
	(*** the MegaOne, since the tester can automatically     ***)
	(*** move timing edges anywhere required over four (4)   ***)
	(*** tester periods, with no restrictions. Thus, the     ***)
	(*** usual problems of "dead regions" for timings do not ***)
	(*** exist here.                                         ***)
	(***                                                     ***)
	(*** In order to provide for multiple frequency tests    ***)
	(*** using a single TI Timing Set, the procedure         ***)
	(*** ACDataSheetSet will accept two parameters passed    ***)
	(*** to it. These parameters are the period, and name of ***)
	(*** an AC Table (if the name TIallACTable is passed, all***)
	(*** AC Tables required for the test will be created).   ***)
	(*** The user will then generate the required timing     ***)
	(*** parameters in the TITimingSet procedure, in terms of***)
	(*** this tester period. Typically, timings will be      ***)
	(*** based on a quarter-phase or half-phase of this base ***)
	(*** period (Q or H).                                    ***)
	(***                                                     ***)
	(*** All required timing parameters must be declared in  ***)
	(*** this DataSheet. This includes any timing parameters ***)
	(*** that will be measured before executing any tests.   ***)
	(*** (The most common example is CLKIN to CLKOUT delay). ***)
	(*** Use a minimum or maximum value for such parameters. ***)
	(*** Provision will be made for measurement of these     ***)
	(*** parameters, but an initial value must be declared.  ***)
	(***                                                     ***)
	(***********************************************************)

procedure ACDataSheetSet;(*actable : ACTable*)

  var
    lfgb, hfgb : PicoSeconds;


 procedure TITimingSet(actable : ACTable);
START(ALLENUMS,ALLTABLES);
	(***********************************************************)
	(***           Internal Procedure TITimingSet            ***)
	(***********************************************************)
	(***                                                     ***)
	(*** TITimingSet is internal to this module,and consists ***)
	(*** of a list of timing parameters and expressions      ***)
	(*** that includes all of the AC parameters required     ***)
	(*** for the test. These values can normally be found in ***)
	(*** the device specification. This is the most device   ***)
	(*** specific area in programming the tester. As such,   ***)
	(*** we will present a general strategy, and provide an  ***)
	(*** example.                                            ***)
	(***                                                     ***)
	(*** In order to create the various AC DataSheets needed ***)
	(*** for testing multiple frequencies, and also allow    ***)
	(*** for the use of a SCHMOO or SEARCH on device period, ***)
	(*** it is required that timing set-ups for any period   ***)
	(*** be set-up through a single procedure. This is the   ***)
	(*** reason for creating the procedure TITimingSet. It   ***)
	(*** is a procedure that will be used to set timing      ***)
	(*** parameters for all frequencies of device operation. ***)
	(***                                                     ***)
	(*** All required timing parameters must be declared in  ***)
	(*** this TimingSet. This includes any timing parameters ***)
	(*** that will be measured before executing any tests.   ***)
	(*** (The most common example is CLKIN to CLKOUT delay). ***)
	(*** Use a minimum or maximum value for such parameters. ***)
	(*** Provision will be made for measurement of these     ***)
	(*** parameters, but an initial value must be declared.  ***)
	(***                                                     ***)
	(***********************************************************)

 begin

	(***********************************************************)
	(***                                                     ***)
	(*** Guardbands as required on a device by device basis  ***)
	(*** should be declared and implemented in this section. ***)
	(*** Guardbands declared here should be guardbands on    ***)
	(*** parameters known to be sensitive on the device.     ***)
	(*** Correction factors will be implemented in the       ***)
	(*** ACTableSet procedure. All guardbands used must be   ***)
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
      begin	           (* Device specific guardbands for probe  *)
      end;
    Final:
      begin	           (* Device specific guardbands for final  *)
      end;
    QA:
      begin	           (* Device specific guardbands for qa     *)
      end;
    others:
      begin	           (* Device specific guardbands for others *)
      end;
  end; (*case*)

	(***********************************************************)
	(***                                                     ***)
	(*** The declaration of all AC parameters used in the    ***)
	(*** test program is done here. The names should be those***)
	(*** used in the data book or specification.             ***)
	(***                                                     ***)
	(*** NOTE THAT PARAMETERS USED IN THIS SECTION MUST BE   ***)
	(*** DECLARED IN THE TimeParameter SECTION OF Global.h   ***)
	(***                                                     ***)
	(*** Any guardbands required by your test program        ***)
	(*** should be explicity added to or subtracted from     ***)
	(*** the expression in which the parameter to be         ***)
	(*** guardbanded is defined. Data book parameters and    ***)
	(*** variables will be used in this section. Use         ***)
	(*** variables for guardbands. Guardband values must be  ***)
	(*** assigned to variables in the preceding section.     ***)
	(***                                                     ***)
	(*** In order for the Binary Search and Schmoo Plot      ***)
	(*** developed by test engineering to work correctly,    ***)
	(*** it is required that a single AC Table be created.   ***)
	(*** All frequency dependencies must be included in the  ***)
	(*** AC parameter assignment.                            ***)
	(***                                                     ***)
	(***********************************************************)

  with ACDataSheets[ actable ] do
    begin

   (**************************************************************************)
   (* Timing Parameters for CLKIN, H1 and H3                                 *)
   (**************************************************************************)

      t[tref]        := 10ns;            (* reference time / H1 rising edge  *)
                                         (* used to avoid pgm'ing neg time   *)

      t[tclockdelay] :=  5ns;            (* Default CLKIN to H1 delay        *)
      t[tsyncdelay]  :=  5ns;            (* Default syncdelay                *)

      t[tcCI]  := period div 2;                    (* CLKIN cycle time       *)
      t[twCIH] := (duty * t[tcCI] div 100);        (* CLKIN hi dur, any duty *)
      t[twCIL] := t[tcCI]-t[twCIH];                (* CLKIN lo dur, any duty *)

      t[tcH]  := period;                 (* H1/H3  cycle time, dut period    *)
      t[tper] := period;                 (* tester cycle time, pattern rate  *)

      t[toffset]   :=  0ns;            (* offset for double-clock CLKIN, def *)
      t[tH1flo]    :=  t[tcCI];        (* H1 falling edge lo-level, def      *)
      t[tH3flo]    :=  0ns;            (* H3 falling edge lo-level, def      *)
      t[tH3rhi]    :=  t[tcCI];        (* H3 rising  edge hi-level, def      *)
      t[tCSTRBfhi] :=  5ns;            (* CSTRB falling edge hi-level, def   *)
      t[tCRDYflo]  := 10ns;            (* CRDY falling edge lo-level, def    *)

   (*                                                                        *)
   (* DEFAULT VALUES FOR TIMING PARAMETERS THAT ARE USED IN WAVEFORMS THAT   *)
   (* REFERENCE A USER-DEFINED ORIGIN (ORIGINS ARE CALCULATED IN SYNC.P)     *)
   (*                                                                        *)

      t[true_toffset]   :=  0ns;
      t[true_tH1flo]    :=  t[tcCI];
      t[true_tH3flo]    :=  0ns;
      t[true_tH3rhi]    :=  t[tcCI];
      t[true_tCSTRBfhi] :=  5ns;
      t[true_tCRDYflo]  := 10ns;
      t[tsuDR2]		:= 10ns;   (* Guaranteed solid level between this time          *)
				   (* and STRB_ - actually H1 - goes inactive           *)
				   (* in write cycle.  This is used to test around      *)
				   (* glitch on LDBUS when 31 GABUS lines swith from Fs *)
				   (* to 0s.  Within this time, memory interface timing *)
				   (* is still satisfied.    PHQ    8/12/93             *)

      case actable of
(**************************************************************************)
(******* Set Timing Spec limits for 40Mhz(50ns) or loose AC waveforms *****) 
(**************************************************************************)
        TIparametricACTable,
        TIcrystalACTable,
        TInomlooseACTable,
        TIstressminACTable,
        TIstressmaxACTable,
        TIlofrqminACTable,
        TIlofrqmaxACTable,
        TIlofrqlooseACTable,
        TIlofrqedgeACTable,
        TIhifrqmin50ACTable,
        TIhifrqmax50ACTable,
        TIhifrqloose50ACTable,
        TIhifrqedge50ACTable,
        TIsearchACTable,
        TIsearchlevelsACTable,
        TIcharACTable:
          begin
START(ALLENUMS,TIparametricACTable,TIcrystalACTable,TInomlooseACTable,TIstressminACTable,TIstressmaxACTable,TIlofrqminACTable,TIlofrqmaxACTable,TIlofrqlooseACTable,TIlofrqedgeACTable,TIhifrqmin50ACTable,TIhifrqmax50ACTable,TIhifrqloose50ACTable,TIhifrqedge50ACTable,TIsearchACTable,TIsearchlevelsACTable,TIcharACTable);
            t[tfH]       := 3ns;         (* H1/H3 fall time, def             *)
            t[tfHmax]    := 3ns;         (* H1/H3 fall time, max             *)
            t[twHLmin]   := t[tcCI]-6ns; (* H1/H3 low pulse duration, min    *)
            t[twHL]      := t[tcCI];     (* H1/H3 low pulse duration, def    *)
            t[twHLmax]   := t[tcCI]+6ns; (* H1/H3 low pulse duration, max    *)
            t[twHHmin]   := t[tcCI]-6ns; (* H1/H3 high pulse duration, min   *)
            t[twHH]      := t[tcCI];     (* H1/H3 high pulse duration, def   *)
            t[twHHmax]   := t[tcCI]+6ns; (* H1/H3 high pulse duration, max   *)
            t[trH]       := 4ns;         (* H1/H3 rise time, def             *)
            t[trHmax]    := 4ns;         (* H1/H3 rise time, max             *)

            t[tdHLHHmin] :=-1ns;     (* H1(H3) low to H3(H1) high delay, min *)
            t[tdHLHH]    := 4ns;     (* H1(H3) low to H3(H1) high delay, def *)
            t[tdHLHHmax] := 4ns;     (* H1(H3) low to H3(H1) high delay, max *)

	    if (TITestType = Probe) then
  	      begin
START(ALLTEMPS,ALLDEVICES,Probe,DONT_RUN_SYNC,RUN_SYNC,schmooloos,NOschmooloos,TIparametricACTable,TIcrystalACTable,TInomlooseACTable,TIstressminACTable,TIstressmaxACTable,TIlofrqminACTable,TIlofrqmaxACTable,TIlofrqlooseACTable,TIlofrqedgeACTable,TIhifrqmin50ACTable,TIhifrqmax50ACTable,TIhifrqloose50ACTable,TIhifrqedge50ACTable,TIsearchACTable,TIsearchlevelsACTable,TIcharACTable);
                t[tdCLKINHH1min] :=  2ns;    (* CLKIN high to H1, min            *)
                t[tdCLKINHH3min] :=  2ns;    (* CLKIN high to H3, min            *)
STOP(ALLTEMPS,ALLDEVICES,Probe,DONT_RUN_SYNC,RUN_SYNC,schmooloos,NOschmooloos,TIparametricACTable,TIcrystalACTable,TInomlooseACTable,TIstressminACTable,TIstressmaxACTable,TIlofrqminACTable,TIlofrqmaxACTable,TIlofrqlooseACTable,TIlofrqedgeACTable,TIhifrqmin50ACTable,TIhifrqmax50ACTable,TIhifrqloose50ACTable,TIhifrqedge50ACTable,TIsearchACTable,TIsearchlevelsACTable,TIcharACTable);
	      end
	    else
	      begin
START(ALLTEMPS,ALLDEVICES,ALLTESTS-Probe,DONT_RUN_SYNC,RUN_SYNC,schmooloos,NOschmooloos,TIparametricACTable,TIcrystalACTable,TInomlooseACTable,TIstressminACTable,TIstressmaxACTable,TIlofrqminACTable,TIlofrqmaxACTable,TIlofrqlooseACTable,TIlofrqedgeACTable,TIhifrqmin50ACTable,TIhifrqmax50ACTable,TIhifrqloose50ACTable,TIhifrqedge50ACTable,TIsearchACTable,TIsearchlevelsACTable,TIcharACTable);
                t[tdCLKINHH1min] :=  2ns;    (* CLKIN high to H1, min            *)
                t[tdCLKINHH3min] :=  2ns;    (* CLKIN high to H3, min            *)
STOP(ALLTEMPS,ALLDEVICES,ALLTESTS-Probe,DONT_RUN_SYNC,RUN_SYNC,schmooloos,NOschmooloos,TIparametricACTable,TIcrystalACTable,TInomlooseACTable,TIstressminACTable,TIstressmaxACTable,TIlofrqminACTable,TIlofrqmaxACTable,TIlofrqlooseACTable,TIlofrqedgeACTable,TIhifrqmin50ACTable,TIhifrqmax50ACTable,TIhifrqloose50ACTable,TIhifrqedge50ACTable,TIsearchACTable,TIsearchlevelsACTable,TIcharACTable);
	      end;

            if (actable = TIstressminACTable) then   (* not testing spec during low vdd stress *)
              begin
START(ALLTEMPS,ALLDEVICES,ALLTESTS,DONT_RUN_SYNC,RUN_SYNC,schmooloos,NOschmooloos,TIstressminACTable);
                t[tdCLKINHH1max] := 14ns;    (* CLKIN high to H1, set loose for sync-up *)
                t[tdCLKINHH3max] := 14ns;    (* CLKIN high to H3, set loose for sync-up *)
STOP(ALLTEMPS,ALLDEVICES,ALLTESTS,DONT_RUN_SYNC,RUN_SYNC,schmooloos,NOschmooloos,TIstressminACTable);
              end
            else
              begin
START(ALLTEMPS,ALLDEVICES,ALLTESTS,DONT_RUN_SYNC,RUN_SYNC,schmooloos,NOschmooloos,TIparametricACTable,TIcrystalACTable,TInomlooseACTable,TIstressmaxACTable,TIlofrqminACTable,TIlofrqmaxACTable,TIlofrqlooseACTable,TIlofrqedgeACTable,TIhifrqmin50ACTable,TIhifrqmax50ACTable,TIhifrqloose50ACTable,TIhifrqedge50ACTable,TIsearchACTable,TIsearchlevelsACTable,TIcharACTable);
                t[tdCLKINHH1max] := 12ns;    (* CLKIN high to H1, max            *)
                t[tdCLKINHH3max] := 12ns;    (* CLKIN high to H3, max            *)
STOP(ALLTEMPS,ALLDEVICES,ALLTESTS,DONT_RUN_SYNC,RUN_SYNC,schmooloos,NOschmooloos,TIparametricACTable,TIcrystalACTable,TInomlooseACTable,TIstressmaxACTable,TIlofrqminACTable,TIlofrqmaxACTable,TIlofrqlooseACTable,TIlofrqedgeACTable,TIhifrqmin50ACTable,TIhifrqmax50ACTable,TIhifrqloose50ACTable,TIhifrqedge50ACTable,TIsearchACTable,TIsearchlevelsACTable,TIcharACTable);
              end;

   (**************************************************************************)
   (* Timing Parameters for Global and Local External Memory Ports           *)
   (**************************************************************************)

            t[tdH1LS]    := 10ns;    (* H1 low to STRB_ delay, max           *)
            t[tdH1HRW]   :=  9ns;    (* H1 high to RW_ delay, max            *)
            t[tdH1LA]    := 10ns;    (* H1 low to ADDRESS/PAGE valid, max    *)
            t[tdH1LAV]   := 22ns;    (* H1 low to ADDRESS valid, max         *)
                                     (* after reset, coming out of tristate  *)
            t[tsuDR]     := 15ns;    (* DATA valid before H1 low (read), min *)
            t[thDR]      :=  0ns;    (* DATA hold time after H1 low (read)   *)
            t[tsuRDY]    := 25ns;    (* RDY valid before H1 low, min         *)
            t[thRDY]     :=  0ns;    (* RDY hold time after H1 low, min      *)
            t[tdH1LSTAT] := 10ns;    (* H1 low to STAT valid, max            *)

            t[tvDW]      := 16ns;    (* DATA valid after H1 low (write), max *)
            t[thDW]      :=  0ns;    (* DATA hold time after H1 high (write) *)

            t[tdH1HA]    := 13ns;    (* H1 high to ADDRESS valid, max        *)
                                     (* on back-to-back write cycles (write) *)

            t[tdH1LLOCK] := 11ns;    (* H1 low to LOCK_, max                 *)
                                     (* when executing an interlocked instr  *)

            t[tENB]      :=  0ns;    (* DE_/AE_/CE_ start time               *)
            t[tdENBZ]    := 15ns;    (* DE_/AE_/CE_ to D/A/RW_/STRB_/PAGE hiz*)
            t[tdENBDV]   := 22ns;    (* DE_ to DATA valid                    *)
            t[tdENBAV]   := 21ns;    (* AE_ to ADDR valid                    *)
            t[tdENBCV]   := 21ns;    (* CE_ to CTRL valid                    *)

   (**************************************************************************)
   (* Timing Parameters for IIOF(3-0) When Configured as General Purpose I/O *)
   (**************************************************************************)
                    
            t[tvH1LIF] := 18ns;      (* H1 low to IIOF (output) valid, max   *)
                                     (* when IIOF is configured as an output *)


            t[thIF]    :=  0ns;      (* IIOF (input) hold after H1 low, min  *)
                                     (* when IIOF changes from output to inp *)

            t[tdH1LIF] := 16ns;      (* H1 low to IIOF (output) valid, max   *)
                                     (* when IIOF changes from input  to out *)

            t[thH1LIFOI] := 0ns;     (* H1 low to IIOF (output) disable, min *)
                                     (* when IIOF changes form Output to inp *)
                                     (* to disable strobe when invalid       *)

   (**************************************************************************)
   (* Timing Parameters for Reset                                            *)
   (**************************************************************************)

            t[tsuRESET]     := 11ns; (* RS_ low  setup before CLKIN low, min *)
            t[tsuRESETH]    := 13ns; (* RS_ high setup before H1 low, min    *)

            t[tdisH1HD]     := 13ns; (* H1 high to DATA three state, max     *)
            t[tdisH3HA]     :=  9ns; (* H3 high to ADDR three state, max     *)
            t[tdH3HCTRLH]   :=  9ns; (* H3 high to control signals high, max *)

            t[tdisRESETLAS] := 21ns; (* RS_ low to asynchronous reset signals*)
                                     (* three state, max                     *)

            t[tRESETLOC]    :=  0ns; (* RESETLOC1,0 start time               *)

   (**************************************************************************)
   (* Timing Parameters for IIOF(3-0) When Configured as Interrupt Pins      *)
   (**************************************************************************)

            t[tsuINT] := 11ns;       (* IIOF (int) setup before H1 low, min  *)

            t[tsuINTIDLE] := 18ns;   (* IIOF (int) setup before H1 low, min  *)
                                     (* to wake clocks from IDLE2 in correct phase. *)

            t[twINT]  := t[tcH];     (* IIOF (int) pulse width, min          *)
                                     (* to guarantee an interrupt is seen    *)

   (**************************************************************************)
   (* Timing Parameters for IACK_                                            *)
   (**************************************************************************)

            t[tdH1LIACK] := 9ns;     (* H1 low to IACK_, max                 *)

   (**************************************************************************)
   (* Timing Parameters for Communication Ports (Fifos)                      *)
   (**************************************************************************)

   (*                                                                        *)
   (* Communication Port Drive Timings / Timings for Pins Configured as Input*)
   (*                                                                        *)

            t[tsuCREQ]  := 10ns;                 (* CREQ drive wrt    H1 low *)
            t[tsuCACK]  := 10ns;                 (* CACK drive before H1 low *)

            t[tCRDYLO]  := t[tref]+t[tcCI];              (* after H3 rising  *)
            t[tCRDYHI]  := t[tref]+t[tcH];               (* after H1 rising  *)

            t[tCSTRBLO] := t[tref]+t[tCSTRBfhi];         (* after H1 rising  *)
            t[tCSTRBHI] := t[tref]+t[tCSTRBfhi]+t[tcCI]; (* after H3 rising  *)

   (*                                                                        *)
   (* Communication Port Byte-Transfer Cycle Timing                          *)
   (*                                                                        *)

            t[tdRHSLw]   := 12ns;    (* CRDY high to CSTRB low (write), max  *)

            t[tdRLSHw]   := 12ns;    (* CRDY low to CSTRB high (write), max  *)

            t[tsuCDw]    :=  2ns;    (* CD valid before CSTRB (write), min   *)

            t[thCDw]     :=  1ns;    (* CD hold after CRDY low (write), min  *)

            t[tdSLRLr]   := 10ns;    (* CSTRB low to CRDY low (read), max    *)

            t[tdSHRHr]   := 10ns;    (* CSTRB high to CRDY high (read), max  *)

            t[tsuCDr]    :=  0ns;    (* CD valid before CSTRB (read), min    *)

            t[thCDr]     :=  2ns;    (* CD held valid after CRDY low (read)  *)

   (*                                                                        *)
   (* Communication Port Token Transfer Sequence                             *)
   (*                                                                        *)

            t[tdH1HRQLt] := 28ns;    (* H1 high to CREQ low, max             *)
                                     (* for token request                    *)

            t[tdALRQHt]  := 22ns;    (* CACK low to CREQ high, max           *)
                                     (* for token request acknowledge        *)

            t[tdRQHRQLt] :=  8ns;    (* CREQ high to CREQ low, max           *)
                                     (* for the next token request           *)

            t[tdRQHRQOt] := 22ns;    (* CREQ high to CREQ, max               *)
                                     (* change from input to output hi-level *)

            t[tdRQLALt]  := 22ns;    (* CREQ low to CACK low, min            *)
                                     (* for token request acknowledge        *)

   (**************************************************************************)
   (* Timing Parameters for Timer Pins                                       *)
   (**************************************************************************)

            t[tsuTCLK] := 10ns;      (* TCLK setup before H1 low, min        *)
            t[thTCLK]  :=  0ns;      (* TCLK hold after H1 low, min          *)
            t[tdTCLK]  := 13ns;      (* TCLK valid after H1 high, max        *)

   (**************************************************************************)
   (* Timing Parameters for ROMEN                                            *)
   (**************************************************************************)

            t[tROMEN] := 0ns;        (* ROMEN start time                     *)

   (**************************************************************************)
   (* Timing Parameters for NMI_                                             *)
   (**************************************************************************)

            t[tNMI] := 0ns;          (* NMI_ start time                      *)

   (**************************************************************************)
   (* Timing Parameters for Jtag/Emulation                                   *)
   (**************************************************************************)

            t[tsuTDITMS] := 10ns;    (* TDI/TMS setup to TCK high, min       *)
            t[thTDITMS]  :=  5ns;    (* TDI/TMS hold from TCK high, min      *)
            t[tdTDO]     := 15ns;    (* TCK low to TDO valid, max            *)
            t[tJTAG]     :=  7ns;    (* TRS start time                       *)

            t[tdEMU]     := 20ns;    (* TCK low to EMU valid, max            *)
            t[tEMU]      :=  0ns;    (* EMU0/EMU1 start time                 *)
STOP(ALLENUMS,TIparametricACTable,TIcrystalACTable,TInomlooseACTable,TIstressminACTable,TIstressmaxACTable,TIlofrqminACTable,TIlofrqmaxACTable,TIlofrqlooseACTable,TIlofrqedgeACTable,TIhifrqmin50ACTable,TIhifrqmax50ACTable,TIhifrqloose50ACTable,TIhifrqedge50ACTable,TIsearchACTable,TIsearchlevelsACTable,TIcharACTable);

          end;

(*************************************************************************)
(** phq - Timing for off-spec parts.  Still 50ns cycle time but slower IO*)
(** EGM- Set timing spec limits for AC waveforms <40Mhz (60ns) 7/24/1993 *)
(*************************************************************************)
 	TIhifrqmin60ACTable,
	TIhifrqmax60ACTable,
	TIhifrqloose60ACTable,
        TIhifrqedge60ACTable,
 	TIlofrqmin60ACTable,
	TIlofrqmax60ACTable,
	TIlofrqloose60ACTable,
        TIlofrqedge60ACTable:

	  begin
START(ALLENUMS,TIhifrqmin60ACTable,TIhifrqmax60ACTable,TIhifrqloose60ACTable,TIhifrqedge60ACTable,TIlofrqmin60ACTable,TIlofrqmax60ACTable,TIlofrqloose60ACTable,TIlofrqedge60ACTable);
            t[tfH]       := 3ns;         (* H1/H3 fall time, def             *)
            t[tfHmax]    := 3ns;         (* H1/H3 fall time, max             *)
            t[twHLmin]   := t[tcCI]-6ns; (* H1/H3 low pulse duration, min    *)
            t[twHL]      := t[tcCI];     (* H1/H3 low pulse duration, def    *)
            t[twHLmax]   := t[tcCI]+6ns; (* H1/H3 low pulse duration, max    *)
            t[twHHmin]   := t[tcCI]-6ns; (* H1/H3 high pulse duration, min   *)
            t[twHH]      := t[tcCI];     (* H1/H3 high pulse duration, def   *)
            t[twHHmax]   := t[tcCI]+6ns; (* H1/H3 high pulse duration, max   *)
            t[trH]       := 4ns;         (* H1/H3 rise time, def             *)
            t[trHmax]    := 4ns;         (* H1/H3 rise time, max             *)

            t[tdHLHHmin] :=-1ns;     (* H1(H3) low to H3(H1) high delay, min *)
            t[tdHLHH]    := 4ns;     (* H1(H3) low to H3(H1) high delay, def *)
            t[tdHLHHmax] := 4ns;     (* H1(H3) low to H3(H1) high delay, max *)

            t[tdCLKINHH1min] :=  2ns;    (* CLKIN high to H1, min            *)
            t[tdCLKINHH1max] := 10ns;    (* CLKIN high to H1, max            *)
            t[tdCLKINHH3min] :=  2ns;    (* CLKIN high to H3, min            *)
            t[tdCLKINHH3max] := 10ns;    (* CLKIN high to H3, max            *)

   (**************************************************************************)
   (* Timing Parameters for Global and Local External Memory Ports           *)
   (**************************************************************************)

            t[tdH1LS]    := 10ns;    (* H1 low to STRB_ delay, max           *)
            t[tdH1HRW]   :=  9ns;    (* H1 high to RW_ delay, max            *)
            t[tdH1LA]    := 10ns;    (* H1 low to ADDRESS/PAGE valid, max    *)
            t[tdH1LAV]   := 22ns;    (* H1 low to ADDRESS valid, max         *)
                                     (* after reset, coming out of tristate  *)
            t[tsuDR]     := 15ns;    (* DATA valid before H1 low (read), min *)
            t[thDR]      :=  0ns;    (* DATA hold time after H1 low (read)   *)
            t[tsuRDY]    := 25ns;    (* RDY valid before H1 low, min         *)
            t[thRDY]     :=  0ns;    (* RDY hold time after H1 low, min      *)
            t[tdH1LSTAT] := 10ns;    (* H1 low to STAT valid, max            *)

            t[tvDW]      := 16ns;    (* DATA valid after H1 low (write), max *)
            t[thDW]      :=  0ns;    (* DATA hold time after H1 high (write) *)

            t[tdH1HA]    := 13ns;    (* H1 high to ADDRESS valid, max        *)
                                     (* on back-to-back write cycles (write) *)

            t[tdH1LLOCK] := 11ns;    (* H1 low to LOCK_, max                 *)
                                     (* when executing an interlocked instr  *)

            t[tENB]      :=  0ns;    (* DE_/AE_/CE_ start time               *)
            t[tdENBZ]    := 15ns;    (* DE_/AE_/CE_ to D/A/RW_/STRB_/PAGE hiz*)
            t[tdENBDV]   := 22ns;    (* DE_ to DATA valid                    *)
            t[tdENBAV]   := 21ns;    (* AE_ to ADDR valid                    *)
            t[tdENBCV]   := 21ns;    (* CE_ to CTRL valid                    *)

   (**************************************************************************)
   (* Timing Parameters for IIOF(3-0) When Configured as General Purpose I/O *)
   (**************************************************************************)
            t[tvH1LIF] := 18ns;      (* H1 low to IIOF (output) valid, max   *)
                                     (* when IIOF is configured as an output *)

            t[tsuIF]   := 11ns;      (* IIOF (input) setup before H1 low, min*)
            t[thIF]    :=  0ns;      (* IIOF (input) hold after H1 low, min  *)
                                     (* when IIOF changes from output to inp *)

            t[tdH1LIF] := 16ns;      (* H1 low to IIOF (output) valid, max   *)
                                     (* when IIOF changes from input  to out *)

            t[thH1LIFOI] := 0ns;     (* H1 low to IIOF (output) disable, min *)
                                     (* when IIOF changes form Output to inp *)
                                     (* to disable strobe when invalid       *)

   (**************************************************************************)
   (* Timing Parameters for Reset                                            *)
   (**************************************************************************)

            t[tsuRESET]     := 11ns; (* RS_ low  setup before CLKIN low, min *)
            t[tsuRESETH]    := 13ns; (* RS_ high setup before H1 low, min    *)

            t[tdisH1HD]     := 13ns; (* H1 high to DATA three state, max     *)
            t[tdisH3HA]     :=  9ns; (* H3 high to ADDR three state, max     *)
            t[tdH3HCTRLH]   :=  9ns; (* H3 high to control signals high, max *)

            t[tdisRESETLAS] := 21ns; (* RS_ low to asynchronous reset signals*)
                                     (* three state, max                     *)

            t[tRESETLOC]    :=  0ns; (* RESETLOC1,0 start time               *)

   (**************************************************************************)
   (* Timing Parameters for IIOF(3-0) When Configured as Interrupt Pins      *)
   (**************************************************************************)

            t[tsuINT] := 11ns;       (* IIOF (int) setup before H1 low, min  *)

            t[tsuINTIDLE] := 15ns;   (* IIOF (int) setup before H1 low, min  *)
                                     (* to wake clocks from IDLE2 in correct phase. *)

            t[twINT]  := t[tcH];     (* IIOF (int) pulse width, min          *)
                                     (* to guarantee an interrupt is seen    *)

   (**************************************************************************)
   (* Timing Parameters for IACK_                                            *)
   (**************************************************************************)

            t[tdH1LIACK] := 9ns;     (* H1 low to IACK_, max                 *)

   (**************************************************************************)
   (* Timing Parameters for Communication Ports (Fifos)                      *)
   (**************************************************************************)

   (*                                                                        *)
   (* Communication Port Drive Timings / Timings for Pins Configured as Input*)
   (*                                                                        *)

            t[tsuCREQ]  := 10ns;                 (* CREQ drive wrt    H1 low *)
            t[tsuCACK]  := 10ns;                 (* CACK drive before H1 low *)

            t[tCRDYLO]  := t[tref]+t[tcCI];              (* after H3 rising  *)
            t[tCRDYHI]  := t[tref]+t[tcH];               (* after H1 rising  *)

            t[tCSTRBLO] := t[tref]+t[tCSTRBfhi];         (* after H1 rising  *)
            t[tCSTRBHI] := t[tref]+t[tCSTRBfhi]+t[tcCI]; (* after H3 rising  *)

   (*                                                                        *)
   (* Communication Port Byte-Transfer Cycle Timing                          *)
   (*                                                                        *)

            t[tdRHSLw]   := 12ns;    (* CRDY high to CSTRB low (write), max  *)

            t[tdRLSHw]   := 12ns;    (* CRDY low to CSTRB high (write), max  *)

            t[tsuCDw]    :=  2ns;    (* CD valid before CSTRB (write), min   *)

            t[thCDw]     :=  1ns;    (* CD hold after CRDY low (write), min  *)

            t[tdSLRLr]   := 10ns;    (* CSTRB low to CRDY low (read), max    *)

            t[tdSHRHr]   := 10ns;    (* CSTRB high to CRDY high (read), max  *)

            t[tsuCDr]    :=  0ns;    (* CD valid before CSTRB (read), min    *)

            t[thCDr]     :=  2ns;    (* CD held valid after CRDY low (read)  *)

   (*                                                                        *)
   (* Communication Port Token Transfer Sequence                             *)
   (*                                                                        *)

            t[tdH1HRQLt] := 28ns;    (* H1 high to CREQ low, max             *)
                                     (* for token request                    *)

            t[tdALRQHt]  := 25ns;    (* CACK low to CREQ high, max           *)
                                     (* for token request acknowledge        *)

            t[tdRQHRQLt] :=  8ns;    (* CREQ high to CREQ low, max           *)
                                     (* for the next token request           *)

            t[tdRQHRQOt] := 22ns;    (* CREQ high to CREQ, max               *)
                                     (* change from input to output hi-level *)

            t[tdRQLALt]  := 25ns;    (* CREQ low to CACK low, min            *)
                                     (* for token request acknowledge        *)

   (**************************************************************************)
   (* Timing Parameters for Timer Pins                                       *)
   (**************************************************************************)

            t[tsuTCLK] := 10ns;      (* TCLK setup before H1 low, min        *)
            t[thTCLK]  :=  0ns;      (* TCLK hold after H1 low, min          *)
            t[tdTCLK]  := 13ns;      (* TCLK valid after H1 high, max        *)

   (**************************************************************************)
   (* Timing Parameters for ROMEN                                            *)
   (**************************************************************************)

            t[tROMEN] := 0ns;        (* ROMEN start time                     *)

   (**************************************************************************)
   (* Timing Parameters for NMI_                                             *)
   (**************************************************************************)

            t[tNMI] := 0ns;          (* NMI_ start time                      *)

   (**************************************************************************)
   (* Timing Parameters for Jtag/Emulation                                   *)
   (**************************************************************************)

            t[tsuTDITMS] := 10ns;    (* TDI/TMS setup to TCK high, min       *)
            t[thTDITMS]  :=  5ns;    (* TDI/TMS hold from TCK high, min      *)
            t[tdTDO]     := 15ns;    (* TCK low to TDO valid, max            *)
            t[tJTAG]     :=  7ns;    (* TRS start time                       *)

            t[tdEMU]     := 20ns;    (* TCK low to EMU valid, max            *)
            t[tEMU]      :=  0ns;    (* EMU0/EMU1 start time                 *)
STOP(ALLENUMS,TIhifrqmin60ACTable,TIhifrqmax60ACTable,TIhifrqloose60ACTable,TIhifrqedge60ACTable,TIlofrqmin60ACTable,TIlofrqmax60ACTable,TIlofrqloose60ACTable,TIlofrqedge60ACTable);

	  end;

(**************************************************************************)
(******* Set Timing Spec limits for 50Mhz AC waveforms      ***************) 
(**************************************************************************)
        TIhifrqmin40ACTable,
        TIhifrqmax40ACTable,
        TIhifrqloose40ACTable,
        TIhifrqedge40ACTable,
        TIsearch40ACTable,
        TIsearchlevels40ACTable,
        TIchar40ACTable:
          begin
START(ALLENUMS,TIhifrqmin40ACTable,TIhifrqmax40ACTable,TIhifrqloose40ACTable,TIhifrqedge40ACTable,TIsearch40ACTable,TIsearchlevels40ACTable,TIchar40ACTable);
            t[tfH]       := 3ns;         (* H1/H3 fall time, def             *)
            t[tfHmax]    := 3ns;         (* H1/H3 fall time, max             *)
            t[twHLmin]   := t[tcCI]-6ns; (* H1/H3 low pulse duration, min    *)
            t[twHL]      := t[tcCI];     (* H1/H3 low pulse duration, def    *)
            t[twHLmax]   := t[tcCI]+6ns; (* H1/H3 low pulse duration, max    *)
            t[twHHmin]   := t[tcCI]-6ns; (* H1/H3 high pulse duration, min   *)
            t[twHH]      := t[tcCI];     (* H1/H3 high pulse duration, def   *)
            t[twHHmax]   := t[tcCI]+6ns; (* H1/H3 high pulse duration, max   *)
            t[trH]       := 4ns;         (* H1/H3 rise time, def             *)
            t[trHmax]    := 4ns;         (* H1/H3 rise time, max             *)

            t[tdHLHHmin] :=-1ns;     (* H1(H3) low to H3(H1) high delay, min *)
            t[tdHLHH]    := 4ns;     (* H1(H3) low to H3(H1) high delay, def *)
            t[tdHLHHmax] := 4ns;     (* H1(H3) low to H3(H1) high delay, max *)

            t[tdCLKINHH1min] :=  2ns;    (* CLKIN high to H1, min            *)
            t[tdCLKINHH1max] := 10ns;    (* CLKIN high to H1, max            *)
            t[tdCLKINHH3min] :=  2ns;    (* CLKIN high to H3, min            *)
            t[tdCLKINHH3max] := 10ns;    (* CLKIN high to H3, max            *)

   (**************************************************************************)
   (* Timing Parameters for Global and Local External Memory Ports           *)
   (**************************************************************************)
if (TIDeviceType = TMS320C40TAL_pg3x_50MHz) then;

START(ALLTEMPS,ALLTESTS,TMS320C40TAL_pg3x_50MHz,DONT_RUN_SYNC,RUN_SYNC,schmooloos,NOschmooloos,TIhifrqmin40ACTable,TIhifrqmax40ACTable,TIhifrqloose40ACTable,TIhifrqedge40ACTable,TIsearch40ACTable,TIsearchlevels40ACTable,TIchar40ACTable);

(*bb-book*) t[tdH1LS]    :=  9ns;     (* H1 low to STRB_ delay, max           *)

STOP(ALLTEMPS,ALLTESTS,TMS320C40TAL_pg3x_50MHz,DONT_RUN_SYNC,RUN_SYNC,schmooloos,NOschmooloos,TIhifrqmin40ACTable,TIhifrqmax40ACTable,TIhifrqloose40ACTable,TIhifrqedge40ACTable,TIsearch40ACTable,TIsearchlevels40ACTable,TIchar40ACTable);

else

START(ALLTEMPS,ALLTESTS,ALLDEVICES-TMS320C40TAL_pg3x_50MHz,DONT_RUN_SYNC,RUN_SYNC,schmooloos,NOschmooloos,TIhifrqmin40ACTable,TIhifrqmax40ACTable,TIhifrqloose40ACTable,TIhifrqedge40ACTable,TIsearch40ACTable,TIsearchlevels40ACTable,TIchar40ACTable);

(*Mil-50*)  t[tdH1LS]    := 10ns;     (* H1 low to STRB_ delay, max           *)

STOP(ALLTEMPS,ALLTESTS,ALLDEVICES-TMS320C40TAL_pg3x_50MHz,DONT_RUN_SYNC,RUN_SYNC,schmooloos,NOschmooloos,TIhifrqmin40ACTable,TIhifrqmax40ACTable,TIhifrqloose40ACTable,TIhifrqedge40ACTable,TIsearch40ACTable,TIsearchlevels40ACTable,TIchar40ACTable);

            t[tdH1HRW]   :=  9ns;    (* H1 high to RW_ delay, max            *)

(*bb-book*) t[tdH1LA]    :=  9ns;    (* H1 low to ADDRESS/PAGE valid, max    *)

            t[tdH1LAV]   := 22ns;    (* H1 low to ADDRESS valid, max         *)
                                     (* after reset, coming out of tristate  *)

            t[tsuDR]     := 10ns;    (* DATA valid before H1 low (read), min *)

            t[thDR]      :=  0ns;    (* DATA hold time after H1 low (read)   *)
 
            t[tsuRDY]    := 20ns;    (* RDY valid before H1 low, min         *)
 
            t[thRDY]     :=  0ns;    (* RDY hold time after H1 low, min      *)

if (TIDeviceType = TMS320C40TAL_pg3x_50MHz) then   
START(TMS320C40TAL_pg3x_50MHz,ALLTEMPS,ALLTESTS,DONT_RUN_SYNC,RUN_SYNC,schmooloos,NOschmooloos,TIhifrqmin40ACTable,TIhifrqmax40ACTable,TIhifrqloose40ACTable,TIhifrqedge40ACTable,TIsearch40ACTable,TIsearchlevels40ACTable,TIchar40ACTable);
(*bb-1/19*) t[tdH1LSTAT] :=  8ns;     (* H1 low to STAT valid, max            *)
STOP(TMS320C40TAL_pg3x_50MHz,ALLTEMPS,ALLTESTS,DONT_RUN_SYNC,RUN_SYNC,schmooloos,NOschmooloos,TIhifrqmin40ACTable,TIhifrqmax40ACTable,TIhifrqloose40ACTable,TIhifrqedge40ACTable,TIsearch40ACTable,TIsearchlevels40ACTable,TIchar40ACTable);
else
START(ALLTEMPS,ALLTESTS,ALLDEVICES-TMS320C40TAL_pg3x_50MHz,DONT_RUN_SYNC,RUN_SYNC,schmooloos,NOschmooloos,TIhifrqmin40ACTable,TIhifrqmax40ACTable,TIhifrqloose40ACTable,TIhifrqedge40ACTable,TIsearch40ACTable,TIsearchlevels40ACTable,TIchar40ACTable);
(*Mil-50*)  t[tdH1LSTAT] := 10ns;    (* H1 low to STAT valid, max            *)
STOP(ALLTEMPS,ALLTESTS,ALLDEVICES-TMS320C40TAL_pg3x_50MHz,DONT_RUN_SYNC,RUN_SYNC,schmooloos,NOschmooloos,TIhifrqmin40ACTable,TIhifrqmax40ACTable,TIhifrqloose40ACTable,TIhifrqedge40ACTable,TIsearch40ACTable,TIsearchlevels40ACTable,TIchar40ACTable);
 

            t[tvDW]      := 16ns;    (* DATA valid after H1 low (write), max *)
            t[thDW]      :=  0ns;    (* DATA hold time after H1 high (write) *)

if (TIDeviceType = TMS320C40TAL_pg3x_50MHz) then   
START(TMS320C40TAL_pg3x_50MHz,ALLTEMPS,ALLTESTS,DONT_RUN_SYNC,RUN_SYNC,schmooloos,NOschmooloos,TIhifrqmin40ACTable,TIhifrqmax40ACTable,TIhifrqloose40ACTable,TIhifrqedge40ACTable,TIsearch40ACTable,TIsearchlevels40ACTable,TIchar40ACTable);
(*bb-book*) t[tdH1HA]    :=  9ns;     (* H1 high to ADDRESS valid, max        *)
                                     (* on back-to-back write cycles (write) *)
STOP(TMS320C40TAL_pg3x_50MHz,ALLTEMPS,ALLTESTS,DONT_RUN_SYNC,RUN_SYNC,schmooloos,NOschmooloos,TIhifrqmin40ACTable,TIhifrqmax40ACTable,TIhifrqloose40ACTable,TIhifrqedge40ACTable,TIsearch40ACTable,TIsearchlevels40ACTable,TIchar40ACTable);

else
START(ALLTEMPS,ALLTESTS,ALLDEVICES-TMS320C40TAL_pg3x_50MHz,DONT_RUN_SYNC,RUN_SYNC,schmooloos,NOschmooloos,TIhifrqmin40ACTable,TIhifrqmax40ACTable,TIhifrqloose40ACTable,TIhifrqedge40ACTable,TIsearch40ACTable,TIsearchlevels40ACTable,TIchar40ACTable);
(*bb-book*) t[tdH1HA]    := 13ns;    (* H1 high to ADDRESS valid, max        *)
                                     (* on back-to-back write cycles (write) *)
STOP(ALLTEMPS,ALLTESTS,ALLDEVICES-TMS320C40TAL_pg3x_50MHz,DONT_RUN_SYNC,RUN_SYNC,schmooloos,NOschmooloos,TIhifrqmin40ACTable,TIhifrqmax40ACTable,TIhifrqloose40ACTable,TIhifrqedge40ACTable,TIsearch40ACTable,TIsearchlevels40ACTable,TIchar40ACTable);

if (TIDeviceType = TMS320C40TAL_pg3x_50MHz) then   
START(TMS320C40TAL_pg3x_50MHz,ALLTEMPS,ALLTESTS,DONT_RUN_SYNC,RUN_SYNC,schmooloos,NOschmooloos,TIhifrqmin40ACTable,TIhifrqmax40ACTable,TIhifrqloose40ACTable,TIhifrqedge40ACTable,TIsearch40ACTable,TIsearchlevels40ACTable,TIchar40ACTable);
(*bb-1/19*) t[tdH1LLOCK] :=  8ns;     (* H1 low to LOCK_, max                 *)
                                     (* when executing an interlocked instr  *)
STOP(TMS320C40TAL_pg3x_50MHz,ALLTEMPS,ALLTESTS,DONT_RUN_SYNC,RUN_SYNC,schmooloos,NOschmooloos,TIhifrqmin40ACTable,TIhifrqmax40ACTable,TIhifrqloose40ACTable,TIhifrqedge40ACTable,TIsearch40ACTable,TIsearchlevels40ACTable,TIchar40ACTable);
else
START(ALLTEMPS,ALLTESTS,ALLDEVICES-TMS320C40TAL_pg3x_50MHz,DONT_RUN_SYNC,RUN_SYNC,schmooloos,NOschmooloos,TIhifrqmin40ACTable,TIhifrqmax40ACTable,TIhifrqloose40ACTable,TIhifrqedge40ACTable,TIsearch40ACTable,TIsearchlevels40ACTable,TIchar40ACTable);
(*bb-1/19*) t[tdH1LLOCK] :=  9ns;    (* H1 low to LOCK_, max                 *)
                                     (* when executing an interlocked instr  *)
STOP(ALLTEMPS,ALLTESTS,ALLDEVICES-TMS320C40TAL_pg3x_50MHz,DONT_RUN_SYNC,RUN_SYNC,schmooloos,NOschmooloos,TIhifrqmin40ACTable,TIhifrqmax40ACTable,TIhifrqloose40ACTable,TIhifrqedge40ACTable,TIsearch40ACTable,TIsearchlevels40ACTable,TIchar40ACTable);

            t[tENB]      :=  0ns;    (* DE_/AE_/CE_ start time               *)
            t[tdENBZ]    := 15ns;    (* DE_/AE_/CE_ to D/A/RW_/STRB_/PAGE hiz*)

if (TIDeviceType = TMS320C40TAL_pg3x_50MHz) then  
begin 
START(TMS320C40TAL_pg3x_50MHz,ALLTEMPS,ALLTESTS,DONT_RUN_SYNC,RUN_SYNC,schmooloos,NOschmooloos,TIhifrqmin40ACTable,TIhifrqmax40ACTable,TIhifrqloose40ACTable,TIhifrqedge40ACTable,TIsearch40ACTable,TIsearchlevels40ACTable,TIchar40ACTable);
            t[tdENBDV]   := 21ns;    (* DE_ to DATA valid                    *)
(* bb *)    t[tdENBAV]   := 18ns;    (* AE_ to ADDR valid                    *)
STOP(TMS320C40TAL_pg3x_50MHz,ALLTEMPS,ALLTESTS,DONT_RUN_SYNC,RUN_SYNC,schmooloos,NOschmooloos,TIhifrqmin40ACTable,TIhifrqmax40ACTable,TIhifrqloose40ACTable,TIhifrqedge40ACTable,TIsearch40ACTable,TIsearchlevels40ACTable,TIchar40ACTable);
end
else
begin 
START(ALLTEMPS,ALLTESTS,ALLDEVICES-TMS320C40TAL_pg3x_50MHz,DONT_RUN_SYNC,RUN_SYNC,schmooloos,NOschmooloos,TIhifrqmin40ACTable,TIhifrqmax40ACTable,TIhifrqloose40ACTable,TIhifrqedge40ACTable,TIsearch40ACTable,TIsearchlevels40ACTable,TIchar40ACTable);
            t[tdENBDV]   := 22ns;    (* DE_ to DATA valid                    *)
(*Mil *)    t[tdENBAV]   := 21ns;    (* AE_ to ADDR valid                    *)
STOP(ALLTEMPS,ALLTESTS,ALLDEVICES-TMS320C40TAL_pg3x_50MHz,DONT_RUN_SYNC,RUN_SYNC,schmooloos,NOschmooloos,TIhifrqmin40ACTable,TIhifrqmax40ACTable,TIhifrqloose40ACTable,TIhifrqedge40ACTable,TIsearch40ACTable,TIsearchlevels40ACTable,TIchar40ACTable);
end;
            t[tdENBCV]   := 21ns;    (* CE_ to CTRL valid                    *)


   (**************************************************************************)
   (* Timing Parameters for IIOF(3-0) When Configured as General Purpose I/O *)
   (**************************************************************************)

if (TIDeviceType = TMS320C40TAL_pg3x_50MHz) then  
START(TMS320C40TAL_pg3x_50MHz,ALLTEMPS,ALLTESTS,DONT_RUN_SYNC,RUN_SYNC,schmooloos,NOschmooloos,TIhifrqmin40ACTable,TIhifrqmax40ACTable,TIhifrqloose40ACTable,TIhifrqedge40ACTable,TIsearch40ACTable,TIsearchlevels40ACTable,TIchar40ACTable);
            t[tvH1LIF] := 14ns;      (* H1 low to IIOF (output) valid, max   *)
                                     (* when IIOF is configured as an output *)
STOP(TMS320C40TAL_pg3x_50MHz,ALLTEMPS,ALLTESTS,DONT_RUN_SYNC,RUN_SYNC,schmooloos,NOschmooloos,TIhifrqmin40ACTable,TIhifrqmax40ACTable,TIhifrqloose40ACTable,TIhifrqedge40ACTable,TIsearch40ACTable,TIsearchlevels40ACTable,TIchar40ACTable);
else                  
START(ALLTEMPS,ALLTESTS,ALLDEVICES-TMS320C40TAL_pg3x_50MHz,DONT_RUN_SYNC,RUN_SYNC,schmooloos,NOschmooloos,TIhifrqmin40ACTable,TIhifrqmax40ACTable,TIhifrqloose40ACTable,TIhifrqedge40ACTable,TIsearch40ACTable,TIsearchlevels40ACTable,TIchar40ACTable);
(*bb-book*) t[tvH1LIF] := 16ns;  (* H1 low to IIOF (output) valid, max   *)
                                 (* when IIOF is configured as an output *)
STOP(ALLTEMPS,ALLTESTS,ALLDEVICES-TMS320C40TAL_pg3x_50MHz,DONT_RUN_SYNC,RUN_SYNC,schmooloos,NOschmooloos,TIhifrqmin40ACTable,TIhifrqmax40ACTable,TIhifrqloose40ACTable,TIhifrqedge40ACTable,TIsearch40ACTable,TIsearchlevels40ACTable,TIchar40ACTable);

            t[tsuIF]   := 11ns;      (* IIOF (input) setup before H1 low, min*)
            t[thIF]    :=  0ns;      (* IIOF (input) hold after H1 low, min  *)
                                     (* when IIOF changes from output to inp *)

if (TIDeviceType = TMS320C40TAL_pg3x_50MHz) then  
START(TMS320C40TAL_pg3x_50MHz,ALLTEMPS,ALLTESTS,DONT_RUN_SYNC,RUN_SYNC,schmooloos,NOschmooloos,TIhifrqmin40ACTable,TIhifrqmax40ACTable,TIhifrqloose40ACTable,TIhifrqedge40ACTable,TIsearch40ACTable,TIsearchlevels40ACTable,TIchar40ACTable);
            t[tdH1LIF] := 14ns;      (* H1 low to IIOF (output) valid, max   *)
                                    (* when IIOF changes from input  to out *)
STOP(TMS320C40TAL_pg3x_50MHz,ALLTEMPS,ALLTESTS,DONT_RUN_SYNC,RUN_SYNC,schmooloos,NOschmooloos,TIhifrqmin40ACTable,TIhifrqmax40ACTable,TIhifrqloose40ACTable,TIhifrqedge40ACTable,TIsearch40ACTable,TIsearchlevels40ACTable,TIchar40ACTable);
else
START(ALLTEMPS,ALLTESTS,ALLDEVICES-TMS320C40TAL_pg3x_50MHz,DONT_RUN_SYNC,RUN_SYNC,schmooloos,NOschmooloos,TIhifrqmin40ACTable,TIhifrqmax40ACTable,TIhifrqloose40ACTable,TIhifrqedge40ACTable,TIsearch40ACTable,TIsearchlevels40ACTable,TIchar40ACTable);
(*bb-book*) t[tdH1LIF] := 16ns;      (* H1 low to IIOF (output) valid, max   *)
                                     (* when IIOF changes from input  to out *)
STOP(ALLTEMPS,ALLTESTS,ALLDEVICES-TMS320C40TAL_pg3x_50MHz,DONT_RUN_SYNC,RUN_SYNC,schmooloos,NOschmooloos,TIhifrqmin40ACTable,TIhifrqmax40ACTable,TIhifrqloose40ACTable,TIhifrqedge40ACTable,TIsearch40ACTable,TIsearchlevels40ACTable,TIchar40ACTable);

            t[thH1LIFOI] := 0ns;     (* H1 low to IIOF (output) disable, min *)
                                     (* when IIOF changes form Output to inp *)
                                     (* to disable strobe when invalid       *)

   (**************************************************************************)
   (* Timing Parameters for Reset                                            *)
   (**************************************************************************)

            t[tsuRESET]     := 11ns; (* RS_ low  setup before CLKIN low, min *)
            t[tsuRESETH]    := 13ns; (* RS_ high setup before H1 low, min    *)

            t[tdisH1HD]     := 13ns; (* H1 high to DATA three state, max     *)
            t[tdisH3HA]     :=  9ns; (* H3 high to ADDR three state, max     *)
            t[tdH3HCTRLH]   :=  9ns; (* H3 high to control signals high, max *)

            t[tdisRESETLAS] := 21ns; (* RS_ low to asynchronous reset signals*)
                                     (* three state, max                     *)

            t[tRESETLOC]    :=  0ns; (* RESETLOC1,0 start time               *)

   (**************************************************************************)
   (* Timing Parameters for IIOF(3-0) When Configured as Interrupt Pins      *)
   (**************************************************************************)

            t[tsuINT] := 11ns;       (* IIOF (int) setup before H1 low, min  *)

            t[tsuINTIDLE] := 18ns;   (* IIOF (int) setup before H1 low, min  *)
                                     (* to wake clocks from IDLE2 in correct phase. *)

            t[twINT]  := t[tcH];     (* IIOF (int) pulse width, min          *)
                                     (* to guarantee an interrupt is seen    *)

   (**************************************************************************)
   (* Timing Parameters for IACK_                                            *)
   (**************************************************************************)

            t[tdH1LIACK] := 9ns;     (* H1 low to IACK_, max                 *)

   (**************************************************************************)
   (* Timing Parameters for Communication Ports (Fifos)                      *)
   (**************************************************************************)

   (*                                                                        *)
   (* Communication Port Drive Timings / Timings for Pins Configured as Input*)
   (*                                                                        *)

            t[tsuCREQ]  := 10ns;                 (* CREQ drive wrt    H1 low *)
            t[tsuCACK]  := 10ns;                 (* CACK drive before H1 low *)

            t[tCRDYLO]  := t[tref]+t[tcCI];              (* after H3 rising  *)
            t[tCRDYHI]  := t[tref]+t[tcH];               (* after H1 rising  *)

            t[tCSTRBLO] := t[tref]+t[tCSTRBfhi];         (* after H1 rising  *)
            t[tCSTRBHI] := t[tref]+t[tCSTRBfhi]+t[tcCI]; (* after H3 rising  *)

   (*                                                                        *)
   (* Communication Port Byte-Transfer Cycle Timing                          *)
   (*                                                                        *)

(* bb *)    t[tdRHSLw]   :=  12ns;    (* CRDY high to CSTRB low (write), max  *)

(* bb *)    t[tdRLSHw]   :=  12ns;    (* CRDY low to CSTRB high (write), max  *)

            t[tsuCDw]    :=  2ns;    (* CD valid before CSTRB (write), min   *)

if (TIDeviceType = TMS320C40TAL_pg3x_50MHz) then  
START(TMS320C40TAL_pg3x_50MHz,ALLTEMPS,ALLTESTS,DONT_RUN_SYNC,RUN_SYNC,schmooloos,NOschmooloos,TIhifrqmin40ACTable,TIhifrqmax40ACTable,TIhifrqloose40ACTable,TIhifrqedge40ACTable,TIsearch40ACTable,TIsearchlevels40ACTable,TIchar40ACTable);
(* bb *)    t[thCDw]     :=  2ns;    (* CD hold after CRDY low (write), min  *)
STOP(TMS320C40TAL_pg3x_50MHz,ALLTEMPS,ALLTESTS,DONT_RUN_SYNC,RUN_SYNC,schmooloos,NOschmooloos,TIhifrqmin40ACTable,TIhifrqmax40ACTable,TIhifrqloose40ACTable,TIhifrqedge40ACTable,TIsearch40ACTable,TIsearchlevels40ACTable,TIchar40ACTable);
else
START(ALLTEMPS,ALLTESTS,ALLDEVICES-TMS320C40TAL_pg3x_50MHz,DONT_RUN_SYNC,RUN_SYNC,schmooloos,NOschmooloos,TIhifrqmin40ACTable,TIhifrqmax40ACTable,TIhifrqloose40ACTable,TIhifrqedge40ACTable,TIsearch40ACTable,TIsearchlevels40ACTable,TIchar40ACTable);
(* bb *)    t[thCDw]     :=  1ns;    (* CD hold after CRDY low (write), min  *)
STOP(ALLTEMPS,ALLTESTS,ALLDEVICES-TMS320C40TAL_pg3x_50MHz,DONT_RUN_SYNC,RUN_SYNC,schmooloos,NOschmooloos,TIhifrqmin40ACTable,TIhifrqmax40ACTable,TIhifrqloose40ACTable,TIhifrqedge40ACTable,TIsearch40ACTable,TIsearchlevels40ACTable,TIchar40ACTable);


(* bb *)    t[tdSLRLr]   :=  10ns;    (* CSTRB low to CRDY low (read), max    *)

(* bb *)    t[tdSHRHr]   :=  10ns;    (* CSTRB high to CRDY high (read), max  *)

            t[tsuCDr]    :=  0ns;    (* CD valid before CSTRB (read), min    *)

            t[thCDr]     :=  2ns;    (* CD held valid after CRDY low (read)  *)

   (*                                                                        *)
   (* Communication Port Token Transfer Sequence                             *)
   (*                                                                        *)

            t[tdH1HRQLt] := 28ns;    (* H1 high to CREQ low, max             *)
                                     (* for token request                    *)

            t[tdALRQHt]  := 22ns;    (* CACK low to CREQ high, max           *)
                                     (* for token request acknowledge        *)

            t[tdRQHRQLt] :=  8ns;    (* CREQ high to CREQ low, max           *)
                                     (* for the next token request           *)

            t[tdRQHRQOt] := 22ns;    (* CREQ high to CREQ, max               *)
                                     (* change from input to output hi-level *)

            t[tdRQLALt]  := 22ns;    (* CREQ low to CACK low, min            *)
                                     (* for token request acknowledge        *)

   (**************************************************************************)
   (* Timing Parameters for Timer Pins                                       *)
   (**************************************************************************)

            t[tsuTCLK] := 10ns;      (* TCLK setup before H1 low, min        *)
            t[thTCLK]  :=  0ns;      (* TCLK hold after H1 low, min          *)
            t[tdTCLK]  := 13ns;      (* TCLK valid after H1 high, max        *)

   (**************************************************************************)
   (* Timing Parameters for ROMEN                                            *)
   (**************************************************************************)

            t[tROMEN] := 0ns;        (* ROMEN start time                     *)

   (**************************************************************************)
   (* Timing Parameters for NMI_                                             *)
   (**************************************************************************)

            t[tNMI] := 0ns;          (* NMI_ start time                      *)

   (**************************************************************************)
   (* Timing Parameters for Jtag/Emulation                                   *)
   (**************************************************************************)

            t[tsuTDITMS] := 10ns;    (* TDI/TMS setup to TCK high, min       *)
            t[thTDITMS]  :=  5ns;    (* TDI/TMS hold from TCK high, min      *)
            t[tdTDO]     := 15ns;    (* TCK low to TDO valid, max            *)
            t[tJTAG]     :=  7ns;    (* TRS start time                       *)

            t[tdEMU]     := 20ns;    (* TCK low to EMU valid, max            *)
            t[tEMU]      :=  0ns;    (* EMU0/EMU1 start time                 *)


STOP(ALLENUMS,TIhifrqmin40ACTable,TIhifrqmax40ACTable,TIhifrqloose40ACTable,TIhifrqedge40ACTable,TIsearch40ACTable,TIsearchlevels40ACTable,TIchar40ACTable);
          end;

(**************************************************************************)
(******* Set Timing Spec limits for 60Mhz AC waveforms      ***************) 
(**************************************************************************)
        TIhifrqmin33ACTable,
        TIhifrqmax33ACTable,
        TIspecsetupmin33ACTable,
        TIspecholdmin33ACTable,
        TIspecsetupmax33ACTable,
        TIspecholdmax33ACTable,
        TIsearchlevels33ACTable,
        TIsearch33ACTable,
        TIchar33ACTable:
          begin
START(ALLENUMS,TIhifrqmin33ACTable,TIhifrqmax33ACTable,TIspecsetupmin33ACTable,TIspecholdmin33ACTable,TIspecsetupmax33ACTable,TIspecholdmax33ACTable,TIsearchlevels33ACTable,TIsearch33ACTable,TIchar33ACTable);
            t[tfH]       := 3ns;         (* H1/H3 fall time, def             *)
            t[tfHmax]    := 3ns;         (* H1/H3 fall time, max             *)
            t[twHLmin]   := t[tcCI]-6ns; (* H1/H3 low pulse duration, min    *)
            t[twHL]      := t[tcCI];     (* H1/H3 low pulse duration, def    *)
            t[twHLmax]   := t[tcCI]+6ns; (* H1/H3 low pulse duration, max    *)
            t[twHHmin]   := t[tcCI]-6ns; (* H1/H3 high pulse duration, min   *)
            t[twHH]      := t[tcCI];     (* H1/H3 high pulse duration, def   *)
            t[twHHmax]   := t[tcCI]+6ns; (* H1/H3 high pulse duration, max   *)
            t[trH]       := 4ns;         (* H1/H3 rise time, def             *)
            t[trHmax]    := 4ns;         (* H1/H3 rise time, max             *)

            t[tdHLHHmin] :=-1ns;     (* H1(H3) low to H3(H1) high delay, min *)
            t[tdHLHH]    := 4ns;     (* H1(H3) low to H3(H1) high delay, def *)
            t[tdHLHHmax] := 4ns;     (* H1(H3) low to H3(H1) high delay, max *)

            t[tdCLKINHH1min] :=  2ns;    (* CLKIN high to H1, min            *)
            t[tdCLKINHH1max] := 10ns;    (* CLKIN high to H1, max            *)
            t[tdCLKINHH3min] :=  2ns;    (* CLKIN high to H3, min            *)
            t[tdCLKINHH3max] := 10ns;    (* CLKIN high to H3, max            *)

   (**************************************************************************)
   (* Timing Parameters for Global and Local External Memory Ports           *)
   (**************************************************************************)

(*bb-book*) t[tdH1LS]    :=  8ns;    (* H1 low to STRB_ delay, max           *)
            t[tdH1HRW]   :=  8ns;    (* H1 high to RW_ delay, max            *)
(*bb-book*) t[tdH1LA]    :=  9ns;    (* H1 low to ADDRESS/PAGE valid, max    *)
            t[tdH1LAV]   := 22ns;    (* H1 low to ADDRESS valid, max         *)
                                     (* after reset, coming out of tristate  *)
(*bb-1/19*) t[tsuDR]     :=  9ns;    (* DATA valid before H1 low (read), min *)
            t[thDR]      :=  0ns;    (* DATA hold time after H1 low (read)   *)
            t[tsuRDY]    := 18ns;    (* RDY valid before H1 low, min         *)
            t[thRDY]     :=  0ns;    (* RDY hold time after H1 low, min      *)
(*bb-1/19*) t[tdH1LSTAT] :=  8.0ns;    (* H1 low to STAT valid, max            *)

            t[tvDW]      := 13ns;    (* DATA valid after H1 low (write), max *)
            t[thDW]      :=  0ns;    (* DATA hold time after H1 high (write) *)

(*bb-book*) t[tdH1HA]    :=  8ns;    (* H1 high to ADDRESS valid, max        *)
                                     (* on back-to-back write cycles (write) *)

(*bb-1/19*) t[tdH1LLOCK] :=  8ns;    (* H1 low to LOCK_, max                 *)
                                     (* when executing an interlocked instr  *)

            t[tENB]      :=  0ns;    (* DE_/AE_/CE_ start time               *)
            t[tdENBZ]    := 15ns;    (* DE_/AE_/CE_ to D/A/RW_/STRB_/PAGE hiz*)
            t[tdENBDV]   := 16ns;    (* DE_ to DATA valid                    *)
(* bb *)    t[tdENBAV]   := 16ns;    (* AE_ to ADDR valid                    *)
            t[tdENBCV]   := 16ns;    (* CE_ to CTRL valid                    *)

   (**************************************************************************)
   (* Timing Parameters for IIOF(3-0) When Configured as General Purpose I/O *)
   (**************************************************************************)
                        
(*EGM-book*) t[tvH1LIF] := 14ns;     (* H1 low to IIOF (output) valid, max   *)
                                     (* when IIOF is configured as an output *)

            t[tsuIF]   := 11ns;      (* IIOF (input) setup before H1 low, min*)
            t[thIF]    :=  0ns;      (* IIOF (input) hold after H1 low, min  *)
                                     (* when IIOF changes from output to inp *)

            t[tdH1LIF] := 14ns;      (* H1 low to IIOF (output) valid, max   *)
                                     (* when IIOF changes from input  to out *)

            t[thH1LIFOI] := 0ns;     (* H1 low to IIOF (output) disable, min *)
                                     (* when IIOF changes form Output to inp *)
                                     (* to disable strobe when invalid       *)

   (**************************************************************************)
   (* Timing Parameters for Reset                                            *)
   (**************************************************************************)

            t[tsuRESET]     := 11ns; (* RS_ low  setup before CLKIN low, min *)
            t[tsuRESETH]    := 13ns; (* RS_ high setup before H1 low, min    *)

            t[tdisH1HD]     := 13ns; (* H1 high to DATA three state, max     *)
            t[tdisH3HA]     :=  9ns; (* H3 high to ADDR three state, max     *)
            t[tdH3HCTRLH]   :=  9ns; (* H3 high to control signals high, max *)

            t[tdisRESETLAS] := 21ns; (* RS_ low to asynchronous reset signals*)
                                     (* three state, max                     *)

            t[tRESETLOC]    :=  0ns; (* RESETLOC1,0 start time               *)

   (**************************************************************************)
   (* Timing Parameters for IIOF(3-0) When Configured as Interrupt Pins      *)
   (**************************************************************************)

            t[tsuINT] := 11ns;       (* IIOF (int) setup before H1 low, min  *)

            t[tsuINTIDLE] := 15ns;   (* IIOF (int) setup before H1 low, min  *)
                                     (* to wake clocks from IDLE2 in correct phase. *)

            t[twINT]  := t[tcH];     (* IIOF (int) pulse width, min          *)
                                     (* to guarantee an interrupt is seen    *)

   (**************************************************************************)
   (* Timing Parameters for IACK_                                            *)
   (**************************************************************************)

            t[tdH1LIACK] := 7ns;     (* H1 low to IACK_, max                 *)

   (**************************************************************************)
   (* Timing Parameters for Communication Ports (Fifos)                      *)
   (**************************************************************************)

   (*                                                                        *)
   (* Communication Port Drive Timings / Timings for Pins Configured as Input*)
   (*                                                                        *)

            t[tsuCREQ]  := 10ns;                 (* CREQ drive wrt    H1 low *)
            t[tsuCACK]  := 10ns;                 (* CACK drive before H1 low *)

            t[tCRDYLO]  := t[tref]+t[tcCI];              (* after H3 rising  *)
            t[tCRDYHI]  := t[tref]+t[tcH];               (* after H1 rising  *)

            t[tCSTRBLO] := t[tref]+t[tCSTRBfhi];         (* after H1 rising  *)
            t[tCSTRBHI] := t[tref]+t[tCSTRBfhi]+t[tcCI]; (* after H3 rising  *)

   (*                                                                        *)
   (* Communication Port Byte-Transfer Cycle Timing                          *)
   (*                                                                        *)

(* bb *)    t[tdRHSLw]   :=  12ns;    (* CRDY high to CSTRB low (write), max  *)

(* bb *)    t[tdRLSHw]   :=  12ns;    (* CRDY low to CSTRB high (write), max  *)

            t[tsuCDw]    :=  2ns;    (* CD valid before CSTRB (write), min   *)

(* bb *)    t[thCDw]     :=  2ns;    (* CD hold after CRDY low (write), min  *)

(* bb *)    t[tdSLRLr]   :=  10ns;    (* CSTRB low to CRDY low (read), max    *)

(* bb *)    t[tdSHRHr]   :=  10ns;    (* CSTRB high to CRDY high (read), max  *)

            t[tsuCDr]    :=  0ns;    (* CD valid before CSTRB (read), min    *)

            t[thCDr]     :=  2ns;    (* CD held valid after CRDY low (read)  *)

   (*                                                                        *)
   (* Communication Port Token Transfer Sequence                             *)
   (*                                                                        *)

            t[tdH1HRQLt] := 28ns;    (* H1 high to CREQ low, max             *)
                                     (* for token request                    *)

            t[tdALRQHt]  := 22ns;    (* CACK low to CREQ high, max           *)
                                     (* for token request acknowledge        *)

            t[tdRQHRQLt] :=  8ns;    (* CREQ high to CREQ low, max           *)
                                     (* for the next token request           *)

            t[tdRQHRQOt] := 22ns;    (* CREQ high to CREQ, max               *)
                                     (* change from input to output hi-level *)

            t[tdRQLALt]  := 22ns;    (* CREQ low to CACK low, min            *)
                                     (* for token request acknowledge        *)

   (**************************************************************************)
   (* Timing Parameters for Timer Pins                                       *)
   (**************************************************************************)

            t[tsuTCLK] := 10ns;      (* TCLK setup before H1 low, min        *)
            t[thTCLK]  :=  0ns;      (* TCLK hold after H1 low, min          *)
            t[tdTCLK]  := 13ns;      (* TCLK valid after H1 high, max        *)

   (**************************************************************************)
   (* Timing Parameters for ROMEN                                            *)
   (**************************************************************************)

            t[tROMEN] := 0ns;        (* ROMEN start time                     *)

   (**************************************************************************)
   (* Timing Parameters for NMI_                                             *)
   (**************************************************************************)

            t[tNMI] := 0ns;          (* NMI_ start time                      *)

   (**************************************************************************)
   (* Timing Parameters for Jtag/Emulation                                   *)
   (**************************************************************************)

            t[tsuTDITMS] := 10ns;    (* TDI/TMS setup to TCK high, min       *)
            t[thTDITMS]  :=  5ns;    (* TDI/TMS hold from TCK high, min      *)
            t[tdTDO]     := 12ns;    (* TCK low to TDO valid, max            *)
            t[tJTAG]     :=  7ns;    (* TRS start time                       *)

            t[tdEMU]     := 20ns;    (* TCK low to EMU valid, max            *)
            t[tEMU]      :=  0ns;    (* EMU0/EMU1 start time                 *)
STOP(ALLENUMS,TIhifrqmin33ACTable,TIhifrqmax33ACTable,TIspecsetupmin33ACTable,TIspecholdmin33ACTable,TIspecsetupmax33ACTable,TIspecholdmax33ACTable,TIsearchlevels33ACTable,TIsearch33ACTable,TIchar33ACTable);

          end;


        TIspecsetupmin25ACTable,
        TIspecholdmin25ACTable,
        TIspecsetupmax25ACTable,
        TIspecholdmax25ACTable,
        TIsearch25ACTable,
        TIchar25ACTable:
          begin
START(ALLENUMS,TIspecsetupmin25ACTable,TIspecholdmin25ACTable,TIspecsetupmax25ACTable,TIspecholdmax25ACTable,TIsearch25ACTable,TIchar25ACTable);
            t[tfH]       := 3ns;         (* H1/H3 fall time, def             *)
            t[tfHmax]    := 3ns;         (* H1/H3 fall time, max             *)
            t[twHLmin]   := t[tcCI]-6ns; (* H1/H3 low pulse duration, min    *)
            t[twHL]      := t[tcCI];     (* H1/H3 low pulse duration, def    *)
            t[twHLmax]   := t[tcCI]+6ns; (* H1/H3 low pulse duration, max    *)
            t[twHHmin]   := t[tcCI]-6ns; (* H1/H3 high pulse duration, min   *)
            t[twHH]      := t[tcCI];     (* H1/H3 high pulse duration, def   *)
            t[twHHmax]   := t[tcCI]+6ns; (* H1/H3 high pulse duration, max   *)
            t[trH]       := 4ns;         (* H1/H3 rise time, def             *)
            t[trHmax]    := 4ns;         (* H1/H3 rise time, max             *)

            t[tdHLHHmin] :=-1ns;     (* H1(H3) low to H3(H1) high delay, min *)
            t[tdHLHH]    := 4ns;     (* H1(H3) low to H3(H1) high delay, def *)
            t[tdHLHHmax] := 4ns;     (* H1(H3) low to H3(H1) high delay, max *)

            t[tdCLKINHH1min] :=  2ns;    (* CLKIN high to H1, min            *)
            t[tdCLKINHH1max] := 10ns;    (* CLKIN high to H1, max            *)
            t[tdCLKINHH3min] :=  2ns;    (* CLKIN high to H3, min            *)
            t[tdCLKINHH3max] := 10ns;    (* CLKIN high to H3, max            *)

   (**************************************************************************)
   (* Timing Parameters for Global and Local External Memory Ports           *)
   (**************************************************************************)

(*bb-book*) t[tdH1LS]    :=  8ns;    (* H1 low to STRB_ delay, max           *)
            t[tdH1HRW]   :=  8ns;    (* H1 high to RW_ delay, max            *)
(*bb-book*) t[tdH1LA]    :=  8ns;    (* H1 low to ADDRESS/PAGE valid, max    *)
            t[tdH1LAV]   := 22ns;    (* H1 low to ADDRESS valid, max         *)
                                     (* after reset, coming out of tristate  *)
(*bb-1/19*) t[tsuDR]     :=  9ns;    (* DATA valid before H1 low (read), min *)
            t[thDR]      :=  0ns;    (* DATA hold time after H1 low (read)   *)
            t[tsuRDY]    := 18ns;    (* RDY valid before H1 low, min         *)
            t[thRDY]     :=  0ns;    (* RDY hold time after H1 low, min      *)
(*bb-1/19*) t[tdH1LSTAT] :=  8ns;    (* H1 low to STAT valid, max            *)

            t[tvDW]      := 13ns;    (* DATA valid after H1 low (write), max *)
            t[thDW]      :=  0ns;    (* DATA hold time after H1 high (write) *)

(*bb-book*) t[tdH1HA]    :=  8ns;    (* H1 high to ADDRESS valid, max        *)
                                     (* on back-to-back write cycles (write) *)

(*bb-1/19*) t[tdH1LLOCK] :=  8ns;    (* H1 low to LOCK_, max                 *)
                                     (* when executing an interlocked instr  *)

            t[tENB]      :=  0ns;    (* DE_/AE_/CE_ start time               *)
            t[tdENBZ]    := 15ns;    (* DE_/AE_/CE_ to D/A/RW_/STRB_/PAGE hiz*)
            t[tdENBDV]   := 16ns;    (* DE_ to DATA valid                    *)
(* bb *)    t[tdENBAV]   := 16ns;    (* AE_ to ADDR valid                    *)
            t[tdENBCV]   := 16ns;    (* CE_ to CTRL valid                    *)

   (**************************************************************************)
   (* Timing Parameters for IIOF(3-0) When Configured as General Purpose I/O *)
   (**************************************************************************)
                       (*25ns,>60Mhz,orig:18ns*)
(*bb-book*) t[tvH1LIF] := 18ns;      (* H1 low to IIOF (output) valid, max   *)
                                     (* when IIOF is configured as an output *)

            t[tsuIF]   := 11ns;      (* IIOF (input) setup before H1 low, min*)
            t[thIF]    :=  0ns;      (* IIOF (input) hold after H1 low, min  *)
                                     (* when IIOF changes from output to inp *)

            t[tdH1LIF] := 14ns;      (* H1 low to IIOF (output) valid, max   *)
                                     (* when IIOF changes from input  to out *)

            t[thH1LIFOI] := 0ns;     (* H1 low to IIOF (output) disable, min *)
                                     (* when IIOF changes form Output to inp *)
                                     (* to disable strobe when invalid       *)

   (**************************************************************************)
   (* Timing Parameters for Reset                                            *)
   (**************************************************************************)

            t[tsuRESET]     := 11ns; (* RS_ low  setup before CLKIN low, min *)
            t[tsuRESETH]    := 13ns; (* RS_ high setup before H1 low, min    *)

            t[tdisH1HD]     := 13ns; (* H1 high to DATA three state, max     *)
            t[tdisH3HA]     :=  9ns; (* H3 high to ADDR three state, max     *)
            t[tdH3HCTRLH]   :=  9ns; (* H3 high to control signals high, max *)

            t[tdisRESETLAS] := 21ns; (* RS_ low to asynchronous reset signals*)
                                     (* three state, max                     *)

            t[tRESETLOC]    :=  0ns; (* RESETLOC1,0 start time               *)

   (**************************************************************************)
   (* Timing Parameters for IIOF(3-0) When Configured as Interrupt Pins      *)
   (**************************************************************************)

            t[tsuINT] := 11ns;       (* IIOF (int) setup before H1 low, min  *)

            t[tsuINTIDLE] := 15ns;   (* IIOF (int) setup before H1 low, min  *)
                                     (* to wake clocks from IDLE2 in correct phase. *)

            t[twINT]  := t[tcH];     (* IIOF (int) pulse width, min          *)
                                     (* to guarantee an interrupt is seen    *)

   (**************************************************************************)
   (* Timing Parameters for IACK_                                            *)
   (**************************************************************************)

            t[tdH1LIACK] := 7ns;     (* H1 low to IACK_, max                 *)

   (**************************************************************************)
   (* Timing Parameters for Communication Ports (Fifos)                      *)
   (**************************************************************************)

   (*                                                                        *)
   (* Communication Port Drive Timings / Timings for Pins Configured as Input*)
   (*                                                                        *)

            t[tsuCREQ]  := 10ns;                 (* CREQ drive wrt    H1 low *)
            t[tsuCACK]  := 10ns;                 (* CACK drive before H1 low *)

            t[tCRDYLO]  := t[tref]+t[tcCI];              (* after H3 rising  *)
            t[tCRDYHI]  := t[tref]+t[tcH];               (* after H1 rising  *)

            t[tCSTRBLO] := t[tref]+t[tCSTRBfhi];         (* after H1 rising  *)
            t[tCSTRBHI] := t[tref]+t[tCSTRBfhi]+t[tcCI]; (* after H3 rising  *)

   (*                                                                        *)
   (* Communication Port Byte-Transfer Cycle Timing                          *)
   (*                                                                        *)

(* bb *)    t[tdRHSLw]   :=  12ns;    (* CRDY high to CSTRB low (write), max  *)

(* bb *)    t[tdRLSHw]   :=  12ns;    (* CRDY low to CSTRB high (write), max  *)

            t[tsuCDw]    :=  2ns;    (* CD valid before CSTRB (write), min   *)

(* bb *)    t[thCDw]     :=  2ns;    (* CD hold after CRDY low (write), min  *)

(* bb *)    t[tdSLRLr]   :=  10ns;    (* CSTRB low to CRDY low (read), max    *)

(* bb *)    t[tdSHRHr]   :=  10ns;    (* CSTRB high to CRDY high (read), max  *)

            t[tsuCDr]    :=  0ns;    (* CD valid before CSTRB (read), min    *)

            t[thCDr]     :=  2ns;    (* CD held valid after CRDY low (read)  *)

   (*                                                                        *)
   (* Communication Port Token Transfer Sequence                             *)
   (*                                                                        *)

            t[tdH1HRQLt] := 28ns;    (* H1 high to CREQ low, max             *)
                                     (* for token request                    *)

            t[tdALRQHt]  := 22ns;    (* CACK low to CREQ high, max           *)
                                     (* for token request acknowledge        *)

            t[tdRQHRQLt] :=  8ns;    (* CREQ high to CREQ low, max           *)
                                     (* for the next token request           *)

            t[tdRQHRQOt] := 22ns;    (* CREQ high to CREQ, max               *)
                                     (* change from input to output hi-level *)

            t[tdRQLALt]  := 22ns;    (* CREQ low to CACK low, min            *)
                                     (* for token request acknowledge        *)

   (**************************************************************************)
   (* Timing Parameters for Timer Pins                                       *)
   (**************************************************************************)

            t[tsuTCLK] := 10ns;      (* TCLK setup before H1 low, min        *)
            t[thTCLK]  :=  0ns;      (* TCLK hold after H1 low, min          *)
            t[tdTCLK]  := 13ns;      (* TCLK valid after H1 high, max        *)

   (**************************************************************************)
   (* Timing Parameters for ROMEN                                            *)
   (**************************************************************************)

            t[tROMEN] := 0ns;        (* ROMEN start time                     *)

   (**************************************************************************)
   (* Timing Parameters for NMI_                                             *)
   (**************************************************************************)

            t[tNMI] := 0ns;          (* NMI_ start time                      *)

   (**************************************************************************)
   (* Timing Parameters for Jtag/Emulation                                   *)
   (**************************************************************************)

            t[tsuTDITMS] := 10ns;    (* TDI/TMS setup to TCK high, min       *)
            t[thTDITMS]  :=  5ns;    (* TDI/TMS hold from TCK high, min      *)
            t[tdTDO]     := 15ns;    (* TCK low to TDO valid, max            *)
            t[tJTAG]     :=  7ns;    (* TRS start time                       *)

            t[tdEMU]     := 20ns;    (* TCK low to EMU valid, max            *)
            t[tEMU]      :=  0ns;    (* EMU0/EMU1 start time                 *)
STOP(ALLENUMS,TIspecsetupmin25ACTable,TIspecholdmin25ACTable,TIspecsetupmax25ACTable,TIspecholdmax25ACTable,TIsearch25ACTable,TIchar25ACTable);

          end;



        others:
          begin
          end;
      end; (* case *)

    end; (* with *)
STOP(ALLENUMS,ALLTABLES);

 end; (* TITimingSet *)


	(***********************************************************)
	(***                   ACDataSheetSet                    ***)
	(***********************************************************)
	(***                                                     ***)
	(*** This is the beginning of procedure ACDataSheetSet   ***)
	(***                                                     ***)
	(***********************************************************)

begin (*ACDataSheetSet*)

  case TITestType of
    Probe:
      begin             (* Device specific guardbands for probe    *)
        lfgb :=  0ns;   (* PROBE G/B AT LOW FREQUENCY              *)
        hfgb :=  0ns;   (* PROBE G/B AT HIGH FREQUENCY             *)
      end;
    Final:
      begin             (* Device specific guardbands for final    *)
        lfgb := 15ns;   (* FINAL G/B AT LOW FREQUENCY              *)
        hfgb :=  0ns;   (* FINAL G/B AT HIGH FREQUENCY             *)
      end;
    QA:
      begin             (* Device specific guardbands for qa       *)
        lfgb :=  0ns;   (* QA G/B AT LOW FREQUENCY                 *)
        hfgb :=  0ns;   (* QA G/B AT HIGH FREQUENCY                *)
      end;
    others:
      begin             (* Device specific guardbands for others   *)
        lfgb :=  0ns;   (* OTHERS G/B AT LOW FREQUENCY             *)
        hfgb :=  0ns;   (* OTHERS G/B AT HIGH FREQUENCY            *)
      end;
  end; (*case*)

    (*                                                                       *)
    (* Set-up timings for parametric tests                                   *)
    (*                                                                       *)

 if (actable in [TIallACTable, TIparametricACTable]) then
  begin
   duty   := 50;
   period := PeriodLower(485ns, StdSpeed);
   TITimingSet( TIparametricACTable );
  end;(*if*)

    (*                                                                       *)
    (* Set-up timings for crystal test                                       *)
    (*                                                                       *)

 if (actable in [TIallACTable, TIcrystalACTable]) then
  begin
   duty   := 50;
   period := PeriodLower(200ns, StdSpeed);
   TITimingSet( TIcrystalACTable );
  end;(*if*)

    (*                                                                       *)
    (* Set-up loose timings for nom frequency w/nominal duty cycle on clkin  *)
    (*                                                                       *)

 if (actable in [TIallACTable, TInomlooseACTable]) then
  begin
   duty   := 50;
   period := PeriodLower(100ns, StdSpeed);
   TITimingSet( TInomlooseACTable );
  end;(*if*)

    (*                                                                       *)
    (* Set-up loose timings for low frequency w/nominal duty cycle on clkin  *)
    (*                                                                       *)

 if (actable in [TIallACTable, TIstressminACTable]) then
  begin
   duty   := 50;
   period := PeriodLower(485ns, StdSpeed);
   TITimingSet( TIstressminACTable );
  end;(*if*)

    (*                                                                       *)
    (* Set-up loose timings for nom frequency w/nominal duty cycle on clkin  *)
    (*                                                                       *)

 if (actable in [TIallACTable, TIstressmaxACTable]) then
  begin
   duty   := 50;
   period := PeriodLower(100ns, StdSpeed);
   TITimingSet( TIstressmaxACTable );
  end;(*if*)

    (*                                                                       *)
    (* Set-up spec timings for low frequency w/minimum duty cycle on clkin   *)
    (*                                                                       *)

 if (actable in [TIallACTable, TIlofrqminACTable]) then
  begin
   duty   := 33;
   period := PeriodLower(485ns+lfgb, StdSpeed);
   TITimingSet( TIlofrqminACTable );
  end;(*if*)

    (*                                                                       *)
    (* Set-up spec timings for low frequency w/maximum duty cycle on clkin   *)
    (*                                                                       *)

 if (actable in [TIallACTable, TIlofrqmaxACTable]) then
  begin
   duty   := 67;
   period := PeriodLower(485ns+lfgb, StdSpeed);
   TITimingSet( TIlofrqmaxACTable );
  end;(*if*)

    (*                                                                       *)
    (* Set-up loose timings for low frequency w/nominal duty cycle on clkin  *)
    (*                                                                       *)

 if (actable in [TIallACTable, TIlofrqlooseACTable]) then
  begin
   duty   := 50;
   period := PeriodLower(485ns+lfgb, StdSpeed);
   TITimingSet( TIlofrqlooseACTable );
  end;(*if*)

    (*                                                                       *)
    (* Set-up timings using edge strobes for low frequency                   *)
    (*                      ----                                             *)

 if (actable in [TIallACTable, TIlofrqedgeACTable]) then
  begin
   duty   := 50;
   period := PeriodLower(485ns+lfgb, StdSpeed);
   TITimingSet( TIlofrqedgeACTable );
  end;(*if*)

    (*                                                                       *)
    (* Set-up spec timings for low frequency w/minimum duty cycle on clkin   *)
    (*                                                                       *)

 if (actable in [TIallACTable, TIlofrqmin60ACTable]) then
  begin
   duty   := 33;
   period := PeriodLower(485ns+lfgb, StdSpeed);
   TITimingSet( TIlofrqmin60ACTable );
  end;(*if*)

    (*                                                                       *)
    (* Set-up spec timings for low frequency w/maximum duty cycle on clkin   *)
    (*                                                                       *)

 if (actable in [TIallACTable, TIlofrqmax60ACTable]) then
  begin
   duty   := 67;
   period := PeriodLower(485ns+lfgb, StdSpeed);
   TITimingSet( TIlofrqmax60ACTable );
  end;(*if*)

    (*                                                                       *)
    (* Set-up loose timings for low frequency w/nominal duty cycle on clkin  *)
    (*                                                                       *)

 if (actable in [TIallACTable, TIlofrqloose60ACTable]) then
  begin
   duty   := 50;
   period := PeriodLower(485ns+lfgb, StdSpeed);
   TITimingSet( TIlofrqloose60ACTable );
  end;(*if*)

    (*                                                                       *)
    (* Set-up timings using edge strobes for low frequency                   *)
    (*                      ----                                             *)

 if (actable in [TIallACTable, TIlofrqedge60ACTable]) then
  begin
   duty   := 50;
   period := PeriodLower(485ns+lfgb, StdSpeed);
   TITimingSet( TIlofrqedge60ACTable );
  end;(*if*)

    (*                                                                       		*)
    (* Set-up spec timings for setup timings at 25ns w/minimum duty cycle on clkin	*)
    (*                                                                       		*)

 if (actable in [TIallACTable, TIspecsetupmin25ACTable]) then
  begin
   duty   := 33;
   period := PeriodLower(25ns-hfgb, StdSpeed);
   TITimingSet( TIspecsetupmin25ACTable );
  end;(*if*)

    (*                                                                       		*)
    (* Set-up spec timings for spec hold timings at 25ns w/minimum duty cycle on clkin	*)
    (*                                                                       		*)

 if (actable in [TIallACTable, TIspecholdmin25ACTable]) then
  begin
   duty   := 33;
   period := PeriodLower(25ns-hfgb, StdSpeed);
   TITimingSet( TIspecholdmin25ACTable );
  end;(*if*)

    (*                                                                       		*)
    (* Set-up spec timings for setup timings at 25ns w/maximum duty cycle on clkin	*)
    (*                                                                       		*)

 if (actable in [TIallACTable, TIspecsetupmax25ACTable]) then
  begin
   duty   := 67;
   period := PeriodLower(25ns-hfgb, StdSpeed);
   TITimingSet( TIspecsetupmax25ACTable );
  end;(*if*)

    (*                                                                       		*)
    (* Set-up spec timings for spec hold timings at 25ns w/maximum duty cycle on clkin	*)
    (*                                                                       		*)

 if (actable in [TIallACTable, TIspecholdmax25ACTable]) then
  begin
   duty   := 33;
   period := PeriodLower(25ns-hfgb, StdSpeed);
   TITimingSet( TIspecholdmax25ACTable );
  end;(*if*)

    (*                                                                       		*)
    (* Set-up spec timings for setup timings at 33ns w/minimum duty cycle on clkin	*)
    (*                                                                       		*)

 if (actable in [TIallACTable, TIspecsetupmin33ACTable]) then
  begin
   duty   := 33;
   period := PeriodLower(33ns-hfgb, StdSpeed);
   TITimingSet( TIspecsetupmin33ACTable );
  end;(*if*)

    (*                                                                       		*)
    (* Set-up spec timings for spec hold timings at 33ns w/minimum duty cycle on clkin	*)
    (*                                                                       		*)

 if (actable in [TIallACTable, TIspecholdmin33ACTable]) then
  begin
   duty   := 33;
   period := PeriodLower(33ns-hfgb, StdSpeed);
   TITimingSet( TIspecholdmin33ACTable );
  end;(*if*)

    (*                                                                       		*)
    (* Set-up spec timings for setup timings at 33ns w/maximum duty cycle on clkin	*)
    (*                                                                       		*)

 if (actable in [TIallACTable, TIspecsetupmax33ACTable]) then
  begin
   duty   := 67;
   period := PeriodLower(33ns-hfgb, StdSpeed);
   TITimingSet( TIspecsetupmax33ACTable );
  end;(*if*)

    (*                                                                       		*)
    (* Set-up spec timings for spec hold timings at 33ns w/maximum duty cycle on clkin	*)
    (*                                                                       		*)

 if (actable in [TIallACTable, TIspecholdmax33ACTable]) then
  begin
   duty   := 67;
   period := PeriodLower(33ns-hfgb, StdSpeed);
   TITimingSet( TIspecholdmax33ACTable );
  end;(*if*)

    (*                                                                       		*)
    (* Set-up spec timings for high freq  33ns w/minimum duty cycle on clkin	*)
    (*                                                                       		*)

 if (actable in [TIallACTable, TIhifrqmin33ACTable]) then
  begin
   duty   := 33;
   period := PeriodLower(33ns-hfgb, StdSpeed);
   TITimingSet( TIhifrqmin33ACTable );
  end;(*if*)

    (*                                                                       		*)
    (* Set-up spec timings for high freq  33ns w/maximum duty cycle on clkin	*)
    (*                                                                       		*)

 if (actable in [TIallACTable, TIhifrqmax33ACTable]) then
  begin
   duty   := 67;
   period := PeriodLower(33ns-hfgb, StdSpeed);
   TITimingSet( TIhifrqmax33ACTable );
  end;(*if*)

    (*                                                                       *)
    (* Set-up spec timings for high freq 40ns w/minimum duty cycle on clkin  *)
    (*                                                                       *)

 if (actable in [TIallACTable, TIhifrqmin40ACTable]) then
  begin
   duty   := 33;
   period := PeriodLower(40ns-hfgb, StdSpeed);
   TITimingSet( TIhifrqmin40ACTable );
  end;(*if*)

    (*                                                                       *)
    (* Set-up spec timings for high freq 40ns w/maximum duty cycle on clkin  *)
    (*                                                                       *)

 if (actable in [TIallACTable, TIhifrqmax40ACTable]) then
  begin
   duty   := 67;
   period := PeriodLower(40ns-hfgb, StdSpeed);
   TITimingSet( TIhifrqmax40ACTable );
  end;(*if*)

    (*                                                                       *)
    (* Set-up loose timings for high freq 40ns w/nominal duty cycle on clkin *)
    (*                                                                       *)

 if (actable in [TIallACTable, TIhifrqloose40ACTable]) then
  begin
   duty   := 50;
   if (pg2patt) and (TITestType = Pre_Burnin) then
      period := PeriodLower(42ns-hfgb, StdSpeed)     (* Frequency for 90C test to be equal to 55c, 40ns screen *)
   else						     (* Changed from 45ns to 42ns.  See delta data  phq 8/5/93 *)
      period := PeriodLower(40ns-hfgb, StdSpeed);
   TITimingSet( TIhifrqloose40ACTable );
  end;(*if*)

    (*                                                                       *)
    (* Set-up timings using edge strobes for high freq 40ns                  *)
    (*                      ----                                             *)

 if (actable in [TIallACTable, TIhifrqedge40ACTable]) then
  begin
   duty   := 50;
   period := PeriodLower(40ns-hfgb, StdSpeed);
   TITimingSet( TIhifrqedge40ACTable );
  end;(*if*)

    (*                                                                       *)
    (* Set-up spec timings for high freq 50ns w/minimum duty cycle on clkin  *)
    (*                                                                       *)

 if (actable in [TIallACTable, TIhifrqmin50ACTable]) then
  begin
   duty   := 33;
   period := PeriodLower(50ns-hfgb, StdSpeed);
   TITimingSet( TIhifrqmin50ACTable );
  end;(*if*)

    (*                                                                       *)
    (* Set-up spec timings for high freq 50ns w/maximum duty cycle on clkin  *)
    (*                                                                       *)

 if (actable in [TIallACTable, TIhifrqmax50ACTable]) then
  begin
   duty   := 67;
   period := PeriodLower(50ns-hfgb, StdSpeed);
   TITimingSet( TIhifrqmax50ACTable );
  end;(*if*)

    (*                                                                       *)
    (* Set-up loose timings for high freq 50ns w/nominal duty cycle on clkin *)
    (*                                                                       *)

 if (actable in [TIallACTable, TIhifrqloose50ACTable]) then
  begin
   duty   := 50;
   period := PeriodLower(50ns-hfgb, StdSpeed);
   TITimingSet( TIhifrqloose50ACTable );
  end;(*if*)

    (*                                                                       *)
    (* Set-up timings using edge strobes for high freq 50ns                  *)
    (*                      ----                                             *)

 if (actable in [TIallACTable, TIhifrqedge50ACTable]) then
  begin
   duty   := 50;
   period := PeriodLower(50ns-hfgb, StdSpeed);
   TITimingSet( TIhifrqedge50ACTable );
  end;(*if*)

    (*                                                                       *)
    (* Set-up spec timings for high freq 60ns w/minimum duty cycle on clkin  *)
    (*                                                                       *)

 if (actable in [TIallACTable, TIhifrqmin60ACTable]) then
  begin
   duty   := 33;
   period := PeriodLower(50ns-hfgb, StdSpeed);
   TITimingSet( TIhifrqmin60ACTable );
  end;(*if*)

    (*                                                                       *)
    (* Set-up spec timings for high freq 60ns w/maximum duty cycle on clkin  *)
    (*                                                                       *)

 if (actable in [TIallACTable, TIhifrqmax60ACTable]) then
  begin
   duty   := 67;
   period := PeriodLower(50ns-hfgb, StdSpeed);
   TITimingSet( TIhifrqmax60ACTable );
  end;(*if*)

    (*                                                                       *)
    (* Set-up loose timings for high freq 60ns w/nominal duty cycle on clkin *)
    (*                                                                       *)

 if (actable in [TIallACTable, TIhifrqloose60ACTable]) then
  begin
   duty   := 50;
   period := PeriodLower(50ns-hfgb, StdSpeed);
   TITimingSet( TIhifrqloose60ACTable );
  end;(*if*)

    (*                                                                       *)
    (* Set-up timings using edge strobes for high freq 60ns                  *)
    (*                      ----                                             *)

 if (actable in [TIallACTable, TIhifrqedge60ACTable]) then
  begin
   duty   := 50;
   period := PeriodLower(50ns-hfgb, StdSpeed);
   TITimingSet( TIhifrqedge60ACTable );
  end;(*if*)

    (*                                                                       *)
    (* Set-up timings for schmoo routine (other than 40ns range)             *)
    (*                                                                       *)

 if (actable in [TIsearchACTable]) then
  begin
   period := PeriodLower(ACDataSheets[actable].t[tcH], StdSpeed);
   TITimingSet( TIsearchACTable );
  end;(*if*)

    (*                                                                       *)
    (* Set-up timings for schmoo routine (40ns range)                        *)
    (*                                                                       *)

 if (actable in [TIsearch40ACTable]) then
  begin
   period := PeriodLower(ACDataSheets[actable].t[tcH], StdSpeed);
   TITimingSet( TIsearch40ACTable );
  end;(*if*)


    (*                                                                       *)
    (* Set-up timings for schmoo routine (33ns range)                        *)
    (*                                                                       *)

 if (actable in [TIsearch33ACTable]) then
  begin
   period := PeriodLower(ACDataSheets[actable].t[tcH], StdSpeed);
   TITimingSet( TIsearch33ACTable );
  end;(*if*)


    (*                                                                       *)
    (* Set-up timings for schmoo routine (other than 40ns range) - spec lvls *)
    (*                                                                       *)

 if (actable in [TIsearchlevelsACTable]) then
  begin
   period := PeriodLower(ACDataSheets[actable].t[tcH], StdSpeed);
   TITimingSet( TIsearchlevelsACTable );
  end;(*if*)

    (*                                                                       *)
    (* Set-up timings for schmoo routine (40ns range) - spec lvls            *)
    (*                                                                       *)

 if (actable in [TIsearchlevels40ACTable]) then
  begin
   period := PeriodLower(ACDataSheets[actable].t[tcH], StdSpeed);
   TITimingSet( TIsearchlevels40ACTable );
  end;(*if*)


    (*                                                                       *)
    (* Set-up timings for schmoo routine (33ns range) - spec lvls            *)
    (*                                                                       *)

 if (actable in [TIsearchlevels33ACTable]) then
  begin
   period := PeriodLower(ACDataSheets[actable].t[tcH], StdSpeed);
   TITimingSet( TIsearchlevels33ACTable );
  end;(*if*)



    (*                                                                       *)
    (* Set-up timings for characterization routine (other than 40ns char)    *)
    (*                                                                       *)

 if (actable in [TIcharACTable]) then
  begin
   duty := 50;
   period := PeriodLower(ACDataSheets[actable].t[tcH], StdSpeed);
   TITimingSet( TIcharACTable );
  end;(*if*)

    (*                                                                       *)
    (* Set-up timings for characterization routine (33ns char)               *)
    (*                                                                       *)

 if (actable in [TIchar33ACTable]) then
  begin
   duty := 50;
   period := PeriodLower(ACDataSheets[actable].t[tcH], StdSpeed);
   TITimingSet( TIchar33ACTable );
  end;(*if*)


    (*                                                                       *)
    (* Set-up timings for characterization routine (40ns char)               *)
    (*                                                                       *)

 if (actable in [TIchar40ACTable]) then
  begin
   duty := 50;
   period := PeriodLower(ACDataSheets[actable].t[tcH], StdSpeed);
   TITimingSet( TIchar40ACTable );
  end;(*if*)

end; (*ACDataSheetSet*)

