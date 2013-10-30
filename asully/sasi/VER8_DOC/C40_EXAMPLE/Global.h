procedure SccsIdentificationGlobal;
  var
    SccsId	:   String;
  begin
    SccsId:= '@(#) Global.h 1.25 4/27/95 12:50:24 c TI';
  end;

(******************************************************************************
			SCCS	INFO

	MODULE		: Global.h
	VERSION NO.	: 1.25
	FILE CREATED	: 4/27/95 12:50:24
	PREVIOUS DELTA  : 4/27/95 12:50:22
	SCCS FILE	: /tmp_mnt/net/starbase4/ops19/dsp2/bburgess/elf/c40/pgm/SCCS/s.Global.h 
	Copyright	: Texas Instruments, Inc.
        320C40N00:      Previous commercial file rev copied for N00.    
                 RA     12/12/95                                    
        320C40N01:      Added vihCLKhifreq and vihTTLcmprt DC level parameters 
        RA  02/07/96    and COMPORT_CNTLpinlist.
        320C40N02:      Declared motherboard variable for daughter/mother board 
        rr  04/29/96    test option if program loaded using option 3
                        (engineering option).
                        Changed DeviceType names in first to last call. 
        320C40N05:      Added TMS320C40_pg5x_60MHz device option.
        RA  11/14/96 
        320C40N08:      Modified test temperature options to fit MPD temperatures.
        RR  11/18/97    Added the MPM TWB device to device list. 
       320C40N14:      Modified Temp to complie with new std format.
        TJL  12/16/04     

******************************************************************************)
        (***********************************************************)
	(***                Global Declarations                  ***)
	(***********************************************************)
	(***                                                     ***)
	(*** Pascal ordinal types and variables that will be used***)
	(*** in the test program should be declared here. It is  ***)
	(*** possible to use local variables in the various test ***)
	(*** procedures, but those local variables are not       ***)
	(*** available to the user interactively through the use ***)
	(*** of interactive Pascal. In addition, this file makes ***)
	(*** a handy reference for all names used in the program.***)
	(*** Naming conventions are described here in order to   ***)
	(*** improve the useability of this file as a reference. ***)
	(***                                                     ***)
	(***********************************************************)

type

	(*                                                         *)
	(*       Declaration of ordinal values                     *)
	(*                                                         *)

	(*                                                         *)
	(*       Declaration of voltage Supply Names               *)
	(* Supply Names are first referenced in the DeviceTableSet *)
	(* procedure.                                              *)
	(*                                                         *)

	(*                                                         *)
	(*       Declaration of Supply Names                       *)
	(* All Supply Names will be assigned minimum and maximum   *)
	(* allowable values in the DeviceTableSet procedure.       *)
	(*                                                         *)
	(*       Naming Convention                                 *)
	(* Use power supply names from data book or specification  *)
	(*                                                         *)

  SupplyName = (VDD, DVDD, VSUB, VSS);

	(*                                                         *)
	(*       Declaration of Voltage Parameters                 *)
	(* All Voltage Parameters should be assigned values in the *)
	(* DCDataSheetSet procedure.                               *)
	(*                                                         *)
	(*       Naming Convention                                 *)
	(* 1. Power supplies. Use supply name with addition of     *)
	(*    min, max, and nom.                                   *)
	(* 2. I/O levels. Use type of level (ie. vil, voh, etc.),  *)
	(*    followed by test requirement in caps (ie. TTL,       *)
	(*    1090MOS, etc.)                                       *)
	(* 3. PTU force voltages. Use v, followed by test type     *)
	(*    (ie. opens, shortslo, etc.)                          *)
	(*                                                         *)

  VoltageParameter = (VDDmin, VDD10min, VDDmax, VDD10max, VDDnom, VDDiddqlow,
                      VDDlow,VDDhighpg2x,VDDhigh,VDDabsmax, VSUBmin, VSUBnom,
                      vihCLK, vihTTL, vilTTL, vihloosTTL, villoosTTL,
		      vihCLKhifreq, vihTTLcmprt,
                      vohTTL, volTTL, volPOLTTL, voh2080TTL, vol2080TTL,
                      vohstllTTL, volstllTTL, vohloosTTL, volloosTTL,
                      vih_crdy_t, vih_crdy_l,
                      vilstressmin,vihstressmin,vihstrclkmin,volstressmin,
                      vohstressmin,vitlstressmin,vithstressmin,
                      vilstressmax,vihstressmax,volstressmax,vohstressmax,
                      vitlstressmax,vithstressmax, 
                      vihtiming, vihtimingcmprt, vihtimingCRDY_, viltiming,
                      votl, voth,
                      vloadTTL,
                      vopens,
                      vshortslo, vshortshi,
                      vinleaklo, vinleakhi,
                      vtrilkglo, vtrilkghi,
                      vloadpower,
                      vitl, vith);
           

	(*                                                         *)
	(*       Declaration of Current Parameters                 *)
	(* All Current Parameters should be assigned values in the *)
	(* DCDataSheetSet procedure.                               *)
	(*                                                         *)
	(*       Naming Convention                                 *)
	(* 1. Power supplies. Use supply current name followed by  *)
	(*    min, max, or nom.                                    *)
	(* 2. I/O levels. Use type of level (ie. iol, ioh, etc.),  *)
	(*    followed by test requirement in caps (ie. TTL, MOS,  *)
	(*    CLK, etc)                                            *)
	(*                                                         *)

  CurrentParameter = (IDDmin, IDDmax, DIDDmax, IDDmax_cum,
                      IDD60max,DIDD60max, IDD60max_cum,
                      ISUBmin, ISUBmax,
                      iohTTL, iolTTL,
                      iopens,
                      ishortslo, ishortshi,
                      iinleaklo, iinleakhi,
                      iinleakclo, iinleakchi,
                      PMUinleakpulo, PMUinleakpuhi,
                      PMUinleakpdlo, PMUinleakpdhi,
                      itrilkglo, itrilkghi,
                      itrilkglo2, itrilkghi2,
                      IDDQmax, DIDDQmax,
                      IDDQmin, DIDDQmin, 
                      iohpower, iolpower);

	(*                                                         *)
	(*       Declaration of DC Table names                     *)
	(* All DC Table names are first referenced in the          *)
	(* DCDataSheetSet and DCTableSet procedure. Both the       *)
	(* DCDataSheets and DCTables are tables of type DCTable.   *)
	(*                                                         *)
	(*       Naming Convention                                 *)
	(* Start with TI, followed by a descriptor describing what *)
	(* type of table it is (ie. data, opens, inleak1) followed *)

	(*                                                         *)

  DCTable = (TIdataDCTable,                      (* DCDataSheet*)
             TIopensDCTable,                     (* DCTable    *)
             TIshorts1DCTable, TIshorts2DCTable, (* DCTable    *)
             TIinleak1DCTable, TIinleak2DCTable, (* DCTable    *)
             TItrilkg1DCTable, TItrilkg2DCTable, (* DCTable    *)
             TIpowerDCTable, TIiddqlowDCTable,   (* DCTable    *)
             TIlooseDCTable,                     (* DCTable    *)
             TItimingDCTable,                    (* DCTable    *)
             TIlevelsDCTable,                    (* DCTable    *)
             TIstressminDCTable,                 (* DCTable    *)
             TIstressmaxDCTable,                 (* DCTable    *)
             TIallDCTable);                      (* DCTable    *)

	(*                                                         *)
	(*       Declaration of Time Parameters                    *)
	(* All Time Parameters should be assigned values in the    *)
	(* ACDataSheetSet procedure.                               *)
	(*                                                         *)
	(*       Naming Convention                                 *)
	(* Start with t, followed by data book description of      *)
	(* the parameter (ie. wCL, rC, etc.)                       *)
	(*                                                         *)

  TimeParameter = (restrict,loosclock,loossetup,looshold,loosdelay,
                   loosdelay4,loosdelay5,loosdelay6,loosdelay7,
                   loosabus,looscd,true_toffset,true_tH1flo,true_tH3flo,
                   true_tH3rhi,true_tCSTRBfhi,true_tCRDYflo,tref,tgb,
                   tclockdelay,tsyncdelay,tcCI,twCIH,twCIL,tcH,tper,
                   toffset,tH1flo,tH3flo,tH3rhi,tH1rlo,tH1fhi,tH3fhi,
                   tH3rlo,tCSTRBfhi,tCRDYflo,tfH,tfHmax,twHLmin,twHL,
                   twHLmax,twHHmin,twHH,twHHmax,trH,trHmax,tdHLHHmin,
                   tdHLHH,tdHLHHmax,tdCLKINHH1min,tdCLKINHH1max,
                   tdCLKINHH3min,tdCLKINHH3max,tdH1LS,tdH1HRW,tdH1LA,
                   tdH1LAV,tsuDR,thDR,tsuRDY,thRDY,tdH1LSTAT,tvDW,thDW,
                   tdH1HA,tdH1LLOCK,tENB,tdENBZ,tdENBDV,tdENBAV,tdENBCV,
                   tvH1LIF,thH1LIFOI,tsuIF,thIF,tdH1LIF,tsuRESET,tsuRESETH,tdisH1HD,
                   tdisH3HA,tdH3HCTRLH,tdisRESETLAS,tRESETLOC,tsuINT,twINT,
                   tdH1LIACK,tsuCREQ,tsuCACK,tCRDYHI,tCRDYLO,tCSTRBLO,
                   tCSTRBHI,tdRHSLw,tdRLSHw,tsuCDw,thCDw,tdSLRLr,tdSHRHr,
                   tsuCDr,thCDr,tdH1HRQLt,tdALRQHt,tdRQHRQLt,tdRQHRQOt,
                   tdRQLALt,tsuTCLK,thTCLK,tdTCLK,tROMEN,tNMI,tsuTDITMS,
                   thTDITMS,tdTDO,tdEMU,tJTAG,tsuDR2,tEMU,tsuINTIDLE);

	(*                                                         *)
	(*       Declaration of Waveform names                     *)
	(* All Waveform names should be assigned values in the     *)
	(* ACTableSet procedure.                                   *)
	(*                                                         *)
	(*       Naming Convention                                 *)
	(* Start with PinList name, followed by the function of the*)
	(* waveform (ie. drive, compare, nocompare, etc.), followed*)
	(* by WF.                                                  *)
	(*                                                         *)

  Wave = (CLKINdriveWF, RESETdriveWF, H1strobeWF, H1HIGHstrobeWF,
          H1LOWstrobeWF, H3strobeWF, H3LOWstrobeWF, H3HIGHstrobeWF,
          STRBstrobeWF, RWstrobeWF, ABUSVstrobeWF, ABUSstrobeWF,
          ABUSWWstrobeWF,ABUSWWTstrobeWF, STATstrobeWF, LOCKstrobeWF, DBUSdriveWF,
          DBUSstrobeWF, DBUSstrobeoffWF, DBUSWWstrobeWF, RDYdriveWF,
          ENBdriveWF, DBUSHIZstrobeWF, ABUSHIZstrobeWF, CTRLHIZstrobeWF,
          DBUSVALstrobeWF, ABUSVALstrobeWF, CTRLVALstrobeWF, IIOFdriveWF,
          IIOFstrobeWF, IIOFstrobeoffWF, IIOFWWstrobeWF, INTdriveWF,
          IACKstrobeWF, CREQdriveWF, CREQstrobeWF, CREQ2strobeWF,
          CACKdriveWF, CACKstrobeWF, CRDYdriveWF, CSTRB_SYNCstrobeWF,
          CSTRBstrobeWF, CDstrobeWF, CSTRBdriveWF, CRDY_SYNCstrobeWF,
          CRDYstrobeWF, CDdriveWF, TCLKdriveWF, TCLKstrobeWF,
          TCKCLKdriveWF, TCKdriveWF, TDITMSdriveWF, JTAGdriveWF,
          TDOstrobeWF, JTAGH1strobeWF, JTAGVARYstrobeWF, 
          JTAGABUSstrobeWF,JTAGstrobeWF,
          EMUdriveWF, EMUstrobeWF, RESETLOCdriveWF, ROMENdriveWF,
          NMIdriveWF, ContinueWF, DBUSWW2strobeWF, DBUSHOLDstrobeWF, 
          H1IDLEstrobeWF,H3IDLEstrobeWF,INTIDLEdriveWF,ALLoffWF);

    (*                                                         *)
    (*       Declaration of Origin names                       *)
    (* Origins are used to offset timings after a Sync-up.     *)
    (*                                                         *)
    (*       Naming Convention                                 *)
    (* Start with a TimeParameter name which indicates the     *)
    (* offset, and drop the leading t. Concatenate multiple    *)
    (* TimeParameters for those to be calculated by expression.*)
    (*                                                         *)

  Origin = (orgtoffset, orgtH1flo, orgtH3flo, orgtH3rhi, orgtH1high,
            orgtH1low, orgtH3high, orgtH3low, orgtCSTRBfhi, orgtCRDYflo);

	(*                                                         *)
	(*       Declaration of AC Table names                     *)
	(* All AC Table names are first referenced in the          *)
	(* ACDataSheetSet and ACTableSet procedure. Both the       *)
	(* ACDataSheets and ACTables are tables of type ACTable.   *)
	(*                                                         *)
	(*       Naming Convention                                 *)
	(* Start with TI, followed by a descriptor describing what *)
	(* type of table it is (use the period in the description, *)
	(* ie. 1000, 200loose, etc.) followed by ACTable.          *)
	(*                                                         *)

        (* NOTE : TIxxxxxxxx60ACTables are actually 50ns with      *)
	(*	  slower IO timings.  Since 60ns test is obsoleted *)
	(* 	  the name is used for convenient.	           *)
	(*					phq   7/31/1993    *)

  ACTable = (TIparametricACTable,            (* ACTableSet     *)
             TIcrystalACTable,               (* ACTableSet     *)
             TInomlooseACTable,              (* ACTableSet     *)
             TIlofrqminACTable,              (* ACTableSet     *)
             TIlofrqmaxACTable,              (* ACTableSet     *)
             TIlofrqlooseACTable,            (* ACTableSet     *)
             TIlofrqedgeACTable,             (* ACTableSet     *)
             TIhifrqmin33ACTable,            (* ACTableSet     *)  
             TIhifrqmax33ACTable,            (* ACTableSet     *)
             TIhifrqmin40ACTable,            (* ACTableSet     *)
             TIhifrqmax40ACTable,            (* ACTableSet     *)
             TIhifrqloose40ACTable,          (* ACTableSet     *)
             TIhifrqedge40ACTable,           (* ACTableSet     *)
             TIhifrqmin50ACTable,            (* ACTableSet     *)
             TIhifrqmax50ACTable,            (* ACTableSet     *)
             TIhifrqloose50ACTable,          (* ACTableSet     *)
             TIhifrqedge50ACTable,           (* ACTableSet     *)
             TIhifrqmin60ACTable,            (* ACTableSet     *)
             TIhifrqmax60ACTable,            (* ACTableSet     *)
             TIhifrqloose60ACTable,          (* ACTableSet     *)
             TIhifrqedge60ACTable,           (* ACTableSet     *)
             TIlofrqmin60ACTable,            (* ACTableSet     *)
             TIlofrqmax60ACTable,            (* ACTableSet     *)
             TIlofrqloose60ACTable,          (* ACTableSet     *)
             TIlofrqedge60ACTable,           (* ACTableSet     *)
             TIstressminACTable,             (* ACTableSet     *)
             TIstressmaxACTable,             (* ACTableSet     *)
             TIsearchACTable,                (* ACTableSet     *)
             TIsearchlevelsACTable,          (* ACTableSet     *)
             TIcharACTable,                  (* ACTableSet     *)
             TIsearch40ACTable,              (* ACTableSet     *)
             TIsearchlevels40ACTable,        (* ACTableSet     *)
             TIchar40ACTable,                (* ACTableSet     *)
	     TIspecsetupmin25ACTable,        (* ACTableSet     *)
 	     TIspecholdmin25ACTable,         (* ACTableSet     *)
	     TIspecsetupmax25ACTable,        (* ACTableSet     *)
 	     TIspecholdmax25ACTable,         (* ACTableSet     *)
	     TIspecsetupmin33ACTable,        (* ACTableSet     *)
 	     TIspecholdmin33ACTable,         (* ACTableSet     *)
	     TIspecsetupmax33ACTable,        (* ACTableSet     *)
 	     TIspecholdmax33ACTable,         (* ACTableSet     *)
             TIsearchlevels33ACTable,        (* ACTableSet     *)
  	     TIsearch33ACTable,              (* ACTableSet     *)
	     TIsearch25ACTable,              (* ACTableSet     *)
             TIchar33ACTable,                (* ACTableSet     *)
             TIchar25ACTable,                (* ACTableSet     *)
             TIallACTable);                  (* Set all tables *)

	(*                                                         *)
	(*       Declaration of CycleTable names                   *)
	(* Normally, there will be only one CycleTable name. At    *)
	(* a maximum, two are allowed. The first reference of      *)
	(* the CycleTable name will be in the CycleTableSet        *)
	(* procedure.                                              *)
	(*                                                         *)
	(*       Naming Convention                                 *)
	(* Start with TI, followed by a descriptor describing what *)
	(* type of table it is (ie. all), followed by CycleTable.  *)
	(*                                                         *)

  CycleTable = (TIallCycleTable, TIextportCycleTable,
                TIcomportCycleTable, TIcomport41CycleTable,
                TIfaultCycleTable);

	(*                                                         *)
	(*       Declaration of Cycle names                        *)
	(* Declaration of Global Cycle Type names. Up to 63 are    *)
	(* allowed. Use one for each timing set required. Global   *)
	(* Cycle Types are initialized in the CycleTableSet        *)
	(* procedure.                                              *)
	(*                                                         *)

  Cycle = (ALLOFFCycle, 
           SYNCFIFOCycle, SYNCVER1Cycle, SYNCVER2Cycle, RESETCMPCycle,
           LRDDGRDDCycle, LWRBGRDDCycle, LWRCGRDDCycle, LWEAGRDDCycle,
           LWREGRDDCycle, LWWBGRDDCycle, LRDDGWRBCycle, LRDDGWRCCycle,
           LRDDGWEACycle, LRDDGWRECycle, LRDDGWWBCycle, LWREGWRCCycle,
           LWRBGWRCCycle, LWRCGWEACycle, LWRCGWRBCycle, LWRCGWRCCycle,
           LWEAGWEACycle, LWEAGWRCCycle, LWRBGWEACycle, LWEAGWRBCycle,
           LWRCGWWBCycle, LWWBGWRCCycle, LWRBGWWBCycle, LWRCGWRECycle,
           LWREGWRBCycle, LWRBGWRBCycle, LWEAGWWBCycle, LWRBGWRECycle,
           LC1ZGRDDCycle, LC1VGRDDCycle, LC0ZGRDDCycle, LC0VGRDDCycle,
           LABZGRDDCycle, LABVGRDDCycle, LDBVGRDDCycle, LWRCGHIZCycle,
           LWEAGHIZCycle, LRDDGHIZCycle, LRDDGVALCycle, LWRBGVALCycle,
           LRDDGC1ZCycle, LRDDGC1VCycle, LRDDGC0ZCycle, LRDDGC0VCycle,
           LRDDGABZCycle, LRDDGABVCycle, LRDDGDBVCycle, LHIZGWRCCycle,
           LHIZGWEACycle, LHIZGRDDCycle, LVALGRDDCycle, LVALGWRBCycle,
           LRDDFF0RCycle, LRDDFF3RCycle, LWRBFF3RCycle, LWWBFF3RCycle,
           LWEAFF3RCycle, LRDDFF1RCycle, LRDDFF4RCycle, LWRBFF4RCycle,
           LWWBFF4RCycle, LWEAFF4RCycle, LRDDFF2RCycle, LRDDFF5RCycle,
           LWRBFF5RCycle, LWWBFF5RCycle, LWEAFF5RCycle, GWRBFF5RCycle,
           GWRBFF1RCycle, GWRCFF4RCycle, GWRCFF5RCycle, GWEAFF1RCycle,
           GWRBFF2RCycle, GWRBFF3RCycle, GWRCFF2RCycle, GWRCFF3RCycle,
           GWWBFF2RCycle, GWWBFF3RCycle, GWEAFF2RCycle, GWEAFF3RCycle,
           GWEAFF0RCycle, GRDDIINTCycle, GWRBIINTCycle, GWRCIINTCycle,
           GWWBIINTCycle, GWEAIINTCycle, GWREIINTCycle, GRDDIWRBCycle,
           GWRBIWRCCycle, GWRCIWRECycle, GWRCIWRCCycle, GWWBIWRCCycle,
           GWEAIWRCCycle, GRDDIWRCCycle, GRDDIWRECycle, IDDQTESTCycle,
           IDLETESTCycle, JTAGEXTECycle, ContinueCycle, LRDDGWEATCycle);

	(*                                                         *)
	(*       Declaration of Vector Map names                   *)
	(* Normally, there will be only one Vector Map name. The   *)
	(* Vector Map tells the tester how your patterns are       *)
	(* formatted. Each VectorMap is created during the creation*)
	(* of a CycleTable, in the CycleTableSet procedure.        *)
	(*                                                         *)
	(*       Naming Convention                                 *)
	(* Start with TI, followed by a descriptor describing what *)
	(* tests the Vector Map applies to (ie. all) followed by   *)
	(* VectorMap.                                              *)
	(*                                                         *)

  VectorMap = (TIallVectorMap);

	(*                                                         *)
	(*       Declaration of Test Names                         *)
	(*                                                         *)

  TestName = (TIopensTest,          (* Name of std opens  test *)
              TIshortsTest,         (* Name of std shorts test *)
              TIinleakTest,         (* Name of std inleak test *)
              TIPMUleakpuloTest,    (* Name of PMU inleak test *)
              TIPMUleakpuhiTest,    (* Name of PMU inleak test *)
              TIPMUleakpdloTest,    (* Name of PMU inleak test *)
              TIPMUleakpdhiTest,    (* Name of PMU inleak test *)
              TIpower25Test,        (* Name of 25ns power test *)
              TIpower33Test,        (* Name of 33ns power test *)
              TIpower40Test,        (* Name of 40ns power test *)
              TIpower50Test,        (* Name of 50ns power test *)
              TIpower60Test,        (* Name of 60ns power test *)
              TItrilkgTest,         (* Name of std trilkg test *)
              TriStatePattern,      (* Tri-state test pattern  *)
              IDDQPattern,          (* IDDQ Test Pattern - pg5 *)
              Reten0WritPattern,    (* Retention Test pattern  *)
              Reten0ReadPattern,    (* Retention Test pattern  *)
              Reten1WritPattern,    (* Retention Test pattern  *)
              Reten1ReadPattern,    (* Retention Test pattern  *)
              IDDPattern,           (* Norm-mode power pattern *)
              PowerPattern,         (* New power Pattern       *)
              CRYSTALPattern,       (* Crystal test pattern    *)
              SYNCPattern,          (* Sync-up test pattern    *)
              SYNCVERPattern,       (* Sync-up verify pattern  *)
              WAITPattern,          (* Ram retention pattern   *)
              RAMRETPGMPattern,     (* Ram retention pattern   *)
              RAMRETVERPattern,     (* Ram retention pattern   *)
              EXPORTRDYPattern,     (* Functional pattern      *)
              POWERDOWNPattern,     (* Functional pattern - PG5 *)
              ADDRGLPattern,        (* Functional pattern      *)
              ADDRMODEPattern,      (* Functional pattern      *)
              ALUBYTEPattern,       (* Functional pattern      *)
              ALUCMPPattern,        (* Functional pattern      *)
              ALUDAT1Pattern,       (* Functional pattern      *)
              ALUDAT2Pattern,       (* Functional pattern      *)
              ALUDAT3Pattern,       (* Functional pattern      *)
              ALUDAT4Pattern,       (* Functional pattern      *)
              ALUDAT5Pattern,       (* Functional pattern      *)
              ALUDAT6Pattern,       (* Functional pattern      *)
              ALUDAT7Pattern,       (* Functional pattern      *)
              ALUDAT8Pattern,       (* Functional pattern      *)
              ALUFP1_1Pattern,      (* Functional pattern      *)
              ALUFP2_1Pattern,      (* Functional pattern      *)
              ALUFP2_2Pattern,      (* Functional pattern      *)
              ALUFP2_3Pattern,      (* Functional pattern      *)
              ALUFP3_1Pattern,      (* Functional pattern      *)
              ALUFP3_2Pattern,      (* Functional pattern      *)
              ALUFP3_3Pattern,      (* Functional pattern      *)
              ALUFP3_4Pattern,      (* Functional pattern      *)
              ALUFP3_5Pattern,      (* Functional pattern      *)
              ALUINSTPattern,       (* Functional pattern      *)
              ANALYSIS1Pattern,     (* Functional pattern      *)
              ANALYSIS2Pattern,     (* Functional pattern      *)
              ANALYSIS3Pattern,     (* Functional pattern      *)
              BASIC_MPPattern,      (* Functional pattern      *)
              CACHEPattern,         (* Functional pattern      *)
              CIRCPattern,          (* Functional pattern      *)
              CONDBRPattern,        (* Functional pattern      *)
              CONDCODEPattern,      (* Functional pattern      *)
              DMA_AUTOPattern,      (* Functional pattern      *)
              DMA_CTL1Pattern,      (* Functional pattern      *)
              DMA_CTL2Pattern,      (* Functional pattern      *)
              DMA_MULTI1Pattern,    (* Functional pattern      *)
              DMA_MULTI2Pattern,    (* Functional pattern      *)
              DMA_MULTI3Pattern,    (* Functional pattern      *)
              DMA_SPLAUTOPattern,   (* Functional pattern      *)
              DMA_SPLITPattern,     (* Functional pattern      *)
              DMAPIPEPattern,       (* Functional pattern      *)
              DPPTRPattern,         (* Functional pattern      *)
              ELFPIPEPattern,       (* Functional pattern      *)
              EXPORTPattern,        (* Functional pattern      *)
              FIFOPattern,          (* Functional pattern      *)
              FIX_PG1Pattern,       (* Functional pattern      *)
              IEEEPattern,          (* Functional pattern      *)
              INTEGER1Pattern,      (* Functional pattern      *)
              INTEGER2Pattern,      (* Functional pattern      *)
              INTEGER3Pattern,      (* Functional pattern      *)
              INTEGER4Pattern,      (* Functional pattern      *)
              INTRPTDMPattern,      (* Functional pattern      *)
              INTRPTPDPattern,      (* Functional pattern      *)
              INTRPTRGPattern,      (* Functional pattern      *)
              LOGICALPattern,       (* Functional pattern      *)
              MEMPRI2Pattern,       (* Functional pattern      *)
              MPASS_CMDPattern,     (* Functional pattern      *)
              MPASS_DATPattern,     (* Functional pattern      *)
              MULT1Pattern,         (* Functional pattern      *)
              MULT2Pattern,         (* Functional pattern      *)
              MULT3Pattern,         (* Functional pattern      *)
              MULT4Pattern,         (* Functional pattern      *)
              NEWINSTPattern,       (* Functional pattern      *)
              PROGFLO1Pattern,      (* Functional pattern      *)
              PROGFLO2Pattern,      (* Functional pattern      *)
              RAM0SPattern,         (* Functional pattern      *)
              RAM1SPattern,         (* Functional pattern      *)
              RAMCKPattern,         (* Functional pattern      *)
              RECP2Pattern,         (* Functional pattern      *)
              REG1Pattern,          (* Functional pattern      *)
              REGRDYPattern,        (* Functional pattern      *)
              RETI1Pattern,         (* Functional pattern      *)
              RETIDPattern,         (* Funcitonal pattern      *)
              SCANANAPattern,       (* Functional pattern      *)
              SCANCPUPattern,       (* Functional pattern      *)
              SCANSYSPattern,       (* Functional pattern      *)
              SQRT2Pattern,         (* Functional pattern      *)
              STACKPattern,         (* Functional pattern      *)
              TIMER1Pattern,        (* Functional pattern      *)
              TIMER2Pattern,        (* Functional pattern      *)
              TRAPPattern,          (* Functional pattern      *)
              ROMDUMPPattern,       (* Functional pattern      *)
              IBMPattern,           (* Functional pattern - PG3 and later  *)
              GLENAYREPattern,      (* Functional pattern - PG5 *)
              GLENDMAREGPattern,      (* Functional pattern - PG5 *)
              GLENDMA012Pattern,      (* Functional pattern      *)
              GLENDMA345Pattern,      (* Functional pattern      *)
              GLENCPU1Pattern,      (* Functional pattern      *)
	      GLENCPU2Pattern,      (* Functional pattern      *)
              NMIPattern,           (* Functional pattern - PG5 *)
              LONGPattern,          (* Concatonated functional *)
              JTE008Pattern,        (* mem_rw_jte.008          *)
              JTE009Pattern,        (* mem_rw_jte.009          *)
              JTEBYPASSPattern,     (* mem_rw_jte_bypass       *)
              JTEEMUAS1_E1Pattern,  (* jte_emuas1_jte_emuas1   *)
              JTEEMUAS1_E9Pattern,  (* jte_emuas1_jte_emuas9   *)
              JTEEMUAS2_E2Pattern,  (* jte_emuas2_jte_emuas2   *)
              JTEEMUAS3_E3Pattern,  (* jte_emuas3_jte_emuas3   *)
              JTEEMUAS4_E4Pattern,  (* jte_emuas4_jte_emuas4   *)
              JTEEMUAS4_S4Pattern,  (* jte_emuas4_jte_sima4    *)
              JTEEMUASG_E5Pattern,  (* jte_emuas_gen_jte_emuas5*)
              JTEEMUASG_E6Pattern,  (* jte_emuas_gen_jte_emuas6*)
              JTEEMUASG_E7Pattern,  (* jte_emuas_gen_jte_emuas7*)
              JTEEMUASG_E8Pattern,  (* jte_emuas_gen_jte_emuas8*)
              JTEEMUASG_S5Pattern,  (* jte_emuas_gen_jte_sima5 *)
              JTEEMUASG_S6Pattern,  (* jte_emuas_gen_jte_sima6 *)
              JTEEMUASG_S7Pattern,  (* jte_emuas_gen_jte_sima7 *)
              JTEEMUASG_S8Pattern,  (* jte_emuas_gen_jte_sima8 *)
              JTEEMUERPattern,      (* jte_emuer_jte_emuer     *)
              JTEEMUES1Pattern,     (* jte_emues1_jte_emues1   *)
              JTEEMUES2Pattern,     (* jte_emues2_jte_emues2   *)
              JTEEMUES3Pattern,     (* jte_emues3_jte_emues3   *)
              JTEHANGMEPattern,     (* jte_hangme_jte_hangme   *)
              JTEMISC_MPattern,     (* jte_misc_jte_misc       *)
              JTEMISC_M2Pattern,    (* jte_misc_jte_misc2      *)
              JTEMPXFERPattern,     (* jte_mpxfer_jte_mpxfer   *)
              JTESIMPattern,        (* jte_sim_jte_sim         *)
              JTESIM2Pattern,       (* jte_sim2_jte_sim2       *)
              JTESIMAPattern,       (* jte_sima_jte_sima       *)
              JTESIMA1Pattern,      (* jte_sima1_jte_sima1     *)
              JTESIMA2Pattern,      (* jte_sima2_jte_sima2     *)
              JTESIME1Pattern,      (* jte_sime1_jte_sime1     *)
              JTESIME2Pattern,      (* jte_sime2_jte_sime2     *)
              JTESIME3Pattern,      (* jte_sime3_jte_sime3     *)
              JTESIMTOGPattern,     (* mem_rw_jte_simtog       *)
              BRYEXTESTPattern,     (* mem_rw_bry_extest       *)
              BRYINTESTPattern,     (* mem_rw_bry_intest       *)
              LONGJTAGPattern,      (* Concatonated JTAG       *)
              ALU_FAULT1Pattern,    (* Functional fault pattern*)
              ALU_FAULT2Pattern,    (* Functional fault pattern*)
              ALU_FAULT3Pattern,    (* Functional fault pattern*)
              ALU_FAULT4Pattern,    (* Functional fault pattern*)
              ALU_FAULT5Pattern,    (* Functional fault pattern*)
              ANA_FAULT1Pattern,    (* Functional fault pattern*)
              ANA_FAULT2Pattern,    (* Functional fault pattern*)
              ANA_FAULT3Pattern,    (* Functional fault pattern*)
              ANA_FAULT4Pattern,    (* Functional fault pattern*)
              ANA_FAULT5Pattern,    (* Functional fault pattern*)
              ANA_FAULT6Pattern,    (* Functional fault pattern*)
              ANA_FAULT7Pattern,    (* Functional fault pattern*)
              ANA_FAULT8Pattern,    (* Functional fault pattern*)
              AUX_FAULTPattern,     (* Functional fault pattern*)
              CACHE_FAULTPattern,   (* Functional fault pattern*) 
              DMA_FAULT2Pattern,    (* Functional fault pattern*)
              DMA_FAULT3Pattern,    (* Functional fault pattern*)
              CTRL_FAULT1Pattern,   (* Functional fault pattern*)
              CTRL_FAULT2Pattern,   (* Functional fault pattern*)
              CTRL_FAULT3Pattern,   (* Functional fault pattern*)
              CTRL_FAULT4Pattern,   (* Functional fault pattern*)
              DMA_FAULT1Pattern,    (* Functional fault pattern*)
              DMA_FAULT4Pattern,    (* Functional fault pattern*)
              DMA_FAULT5Pattern,    (* Functional fault pattern*)
              FIFO_FAULT1Pattern,   (* Functional fault pattern*)
              FIFO_FAULT2Pattern,   (* Functional fault pattern*)
              MULT_FAULTPattern,    (* Functional fault pattern*)
              REG_FAULT1Pattern,    (* Functional fault pattern*)
              REG_FAULT2Pattern,    (* Functional fault pattern*)
              TIMER0_FAULTPattern,  (* Functional fault pattern*)
              TIMER1_FAULTPattern); (* Functional fault pattern*)


	(*                                                         *)
	(*       Declaration of Test Types                         *)
	(* Normally, there will be three test types, Probe, Final, *)
	(* and QA. The test type is used to select from multiple   *)
	(* sets of test parameters for different tests. Test Flow  *)
	(* can also be selected, but in the standard program, all  *)
	(* test flows are assumed to be the same. A common addition*)
	(* to the Test Types may be temperature (i.e. Final0Deg)   *)
	(*                                                         *)

  TITypeOfTest = (Probe, Pre_Burnin , Final, QA, Final_QA, IDSEngr);

  SoftBin = (noresult,                 (* Counter for no results *)
             opens, shorts,            (* Parametric fail counter*)
             sublkg, inleak,           (* Parametric fail counter*)
             PMUinleakpu, PMUinleakpd, (* Parametric fail counter*)
             trilkg,idd,iddq, funcidd, (* Parametric fail counter*)
             crystal, sync, funcsync,  (* Parametric fail counter*)
             loosefunc, ramret,        (* User defined functional*)
             loosejtag, loosefault, QA_Fail,
             stress,lowstress,highstress,
      	     stlvhf25, sllvhf25,       (* fail counters          *)
             sthvhf25, slhvhf25,
             lllvhf25, llhvhf25,
      	     stlvhf33, sllvhf33, 
             sthvhf33, slhvhf33,
             lllvhf33, llhvhf33,
      	     stlvhf40, sllvhf40, 
             sthvhf40, slhvhf40,
             lllvhf40, llhvhf40,
             stlvhf50, sllvhf50,
             sthvhf50, slhvhf50,
             lllvhf50, llhvhf50,
             stlvhf60, sllvhf60,
             sthvhf60, slhvhf60,
             lllvhf60, llhvhf60,
             stlvlf, sllvlf,
             sthvlf, slhvlf,
             lllvlf, llhvlf,
	     good_40MHz, good_50MHz, good_60MHz,
             goodfunc, good25ns, good33ns, good40ns, good60ns, 
	     good50ns, good50ns_SlowIO, goodbin1,
             EXPORTRDY, ADDRGL, ADDRMODE, ALUBYTE,
             ALUCMP, ALUDAT1, ALUDAT2, ALUDAT3,
             ALUDAT4, ALUDAT5, ALUDAT6, ALUDAT7,
             ALUDAT8, ALUFP1_1, ALUFP2_1, ALUFP2_2,
             ALUFP2_3, ALUFP3_1, ALUFP3_2, ALUFP3_3,
             ALUFP3_4, ALUFP3_5, ALUINST, ANALYSIS1,
             ANALYSIS2, ANALYSIS3, BASIC_MP, CACHE,
             CIRC, CONDBR, CONDCODE, DMA_AUTO, DMA_CTL1,
             DMA_CTL2, DMA_MULTI1, DMA_MULTI2, DMA_MULTI3,
             DMA_SPLAUTO, DMA_SPLIT, DMAPIPE, DPPTR,
             ELFPIPE, EXPORT, FIFO, FIX_PG1, IEEE,
             INTEGER1, INTEGER2, INTEGER3, INTEGER4,
             INTRPTDM, INTRPTPD, INTRPTRG, LOGICAL,
             MEMPRI2, MPASS_CMD, MPASS_DAT, MULT1, MULT2,
             MULT3, MULT4, NEWINST, PROGFLO1, PROGFLO2,
             RAM0S, RAM1S, RAMCK, RECP2, REG1, REGRDY, RETI1 ,RETID,
             ROMDUMP, SCANANA, SCANCPU, SCANSYS, SQRT2,
             STACK, TIMER1, TIMER2, TRAP, LONG, RAMRETPGM,
             RAMRETVER);

  HardBin = (BIN00,                      (* This one can't be used. *)
             BIN01, BIN02, BIN03, BIN04, (* Normal use will only    *)
             BIN05, BIN06, BIN07, BIN08, (* include 1-8, but 16 can *)
             BIN09, BIN10, BIN11, BIN12, (* be used with some       *)
             BIN13, BIN14, BIN15, BIN16, (* handlers.  There are    *)
             BIN17, BIN18, BIN19, BIN20, (* a total of 32 for tipc  *)
             BIN21, BIN22, BIN23, BIN24, (* probe interface.        *)
             BIN25, BIN26, BIN27, BIN28, (*                         *)
             BIN29, BIN30, BIN31);       (*                         *)

  HandlerType   = (noHandlerType);
  HandlerResult = (noHandlerResult);

  ParallelDevice = (noParallelDevice);

  SamplerWindow          = (noSamplerWindow);

  SamplerTable           = (noSamplerTable );

        (*                                                         *)
        (*           Declaration of new Vega types                 *)
        (* Declare the new types required for Vega programs        *)
        (*                                                         *)
        (*                                                         *)

  LECSetup               = (noLECSetup);
  WaveGroup              = (noWaveGroup);

(*** Added below 5 lines to support Mixed Signal Test Capability  ***)
(*** on Polaris 						  ***)

  AnalogVoltageParameter = (noAnalogVoltageParameter);
  AnalogTimeParameter    = (noAnalogTimeParameter);
  AnalogIntegerParameter = (noAnalogIntegerParameter);
  AnalogLimitParameter   = (noAnalogLimitParameter);
  AnalogTable		 = (noAnalogTable);


	(*                                                         *)
	(*       Declaration of Device Types                       *)
	(* Declare the device types to be selected among in the    *)
	(* OperatorSetup menu. This will normally be used to       *)
	(* control test flow.                                      *)
	(*                                                         *)

  DeviceType = (SMJ320C40GFM_pg3x_40MHz, SMJ320C40GFM_pg5x_40MHz, 
                SMJ320C40GFM_pg5x_50MHz, SMJ320C40GFM_pg5x_60MHz,
                SMJ320C40HFHM_pg3x_40MHz, SMJ320C40HFHM_pg5x_40MHz,
	        SMJ320C40HFHM_pg5x_50MHz, SMJ320C40HFHM_pg5x_60MHz,
		SM320C40TAB_pg3x_40MHz, SM320C40TAB_pg5x_40MHz,
                SM320C40TAB_pg5x_50MHz, SM320C40TAB_pg5x_60MHz,
                TMS320C40TAL_pg3x_50MHz, TMS320C40TAL_pg5x_60MHz,
                TMS320C41QFP,MPM11856KGDC);
		          
	(*                                                         *)
	(*       Declaration of Temperature Types                  *)
	(* Declare the temperature types to be selected among in   *)
	(* the OperatorSetup menu. This will normally be used to   *)
	(* control selection of supply limits.                     *)
	(*                                                         *)

  TempType = (TEMP_N55_DEG, TEMP_N40_DEG,
              TEMP_N25_DEG, TEMP_25_DEG,
              TEMP_70_DEG,  TEMP_85_DEG,
              TEMP_100_DEG, TEMP_125_DEG);

	(*                                                         *)
	(*       Call to MegaTest provided procedures              *)
	(* This call to the MegaTest procedures follows the        *)
	(* type declarations required by MegaTest, but precedes    *)
	(* type declarations which utilize some of the MegaTest    *)
	(* declared types. This call must precede the type         *)
	(* declarations below.                                     *)
	(*                                                         *)

insert 'MegaOne.Standard';

#include "constant.h"


type

  TestTable = record
               cycletablefield : CycleTable;
               actablefield    : ACTable;
               pinlistfield    : PinList;
               case WhatTestTable : TestName of
                TIopensTest,
                TIpower40Test,
                TIpower50Test,
                TIpower60Test  : (dctablefield  : DCTable);
                TIshortsTest,
                TIinleakTest,
                TItrilkgTest   : (dctablefield1 : DCTable;
                                  dctablefield2 : DCTable)
              end; (* record definition *)

  TestTableArray = array [TIopensTest..TItrilkgTest] of TestTable;

  SyncSupplyArray = array [SupplyVType] of VoltageParameter;
  SyncTimeArray = array [ACTable,VoltageParameter,TimeParameter] of PicoSeconds;
  SyncDoneArray = array [ACTable,VoltageParameter] of boolean;

  SoftBinArrayFlag = array [SoftBin] of boolean;







#include "/u/TI_apps/stdprogram/TIglobal.h"
#include "/u/TI_apps/stdprogram/TIexterns.h"
#include "externs.h"


var

  SyncSupply                                 : SyncSupplyArray;
  SyncTime                                   : SyncTimeArray;
  SyncDone                                   : SyncDoneArray;
  supplylimitslist1, supplylimitslist2       : SupplyLimitsArray;
  FirstPatternName,    LastPatternName       : TestName;
  FirstExtPatternName, LastExtPatternName    : TestName;
  FirstComPatternName, LastComPatternName    : TestName;
  FirstJTAGPatternName, LastJTAGPatternName  : TestName;
  FirstFaultPatternName,LastFaultPatternName : TestName;
  cycletablename                             : CycleTable;
  actablename, actable                       : ACTable;
  dctablename                                : DCTable;
  motherboard                                : boolean;
  TIPatternPrint, TICornerPrint              : boolean;
  failsync, truesyncfail, schmoosync         : boolean;
  edgeon                                     : boolean;
  CRYSTAL, failcrystal                       : boolean;
  characterize, charsetup, charmenu          : boolean;
  initfile                                   : boolean;
  loosefunconly, loosefunctest               : boolean;
  ftqa					     : boolean;
  tmx, burnin, burn_in_flag                  : boolean;
  schmooloos, schmooabort, schmoo            : boolean;
  ramonlymap, romonlymap, ramrommap, newrom  : boolean;
  engrpgm,pg2patt, pg3patt, pg5patt, jtagtest: boolean;
  faulttest,lowvddtest,highvddtest,sublktest : boolean;
  iddqtest                                   : boolean;
  datalog_on, datalog_flag                   : boolean;
  vsub_result, vdd_result, dvdd_result       : boolean;
  vsub_leak, vdd_leak, dvdd_leak             : NanoAmps;
  vsub_leak_max, vdd_leak_max, dvdd_leak_max : NanoAmps;
  vsub_leak_min                              : NanoAmps;
  dummyvoltage,tempvhi, tempvlo              : MicroVolts;
  tempt0, tempt1, tempt2, tempt3             : MicroVolts;
  iddcurrent, diddcurrent, iddcurrent_total  : MicroAmps;
  iddcurrent_max,iddcurrent60_max,iddspectot : MicroAmps;
  VDDvalue                                   : VoltageParameter;
  filenumber, pnumber                        : integer;
  lotnumber, unitnumber, temperature         : integer;
  duty, i, j, k, l, n                        : integer;
  s                                          : String;

  softbn : array [1..125, 1..50] of char;
  fa1    : array [0..63, 1..16,1..4] of boolean; (* rom map array *)
  fa2    : array [0..135,1..16,1..4] of integer; (* ram map array *)


 (* added for boolean segment summaries *)

  SliceArray                  : array[1..max_no_die,1..max_softbin] of char;
  SoftBinArray                : SoftBinArrayFlag;
  dummy_softbin               : SoftBin;
  ftqa_softbin		      : SoftBin;
  ftqa_hardbin		      : HardBin;
  summary, reference          : text;
  summaryfile                 : String;
  prbslice                    : String;
  pinlistname2                : String;
  slice, die                  : integer;

 (* spare variables *)

  ss                          : String;
  si1,si2,si3,si4,si5,si6,si7 : integer;
  sr                          : real;
  sb                          : boolean;
  sm                          : MicroVolts;
  sp                          : PicoSeconds;
  st                          : TestName;


  X2CLKIN,X1,H1,H3                         : PinList; (* Single Pin PinLists *)
  LD31,LD30,LD29,LD28,LD27,LD26,LD25,LD24  : PinList; (* Single Pin PinLists *)
  LD23,LD22,LD21,LD20,LD19,LD18,LD17,LD16  : PinList; (* Single Pin PinLists *)
  LD15,LD14,LD13,LD12,LD11,LD10,LD9, LD8   : PinList; (* Single Pin PinLists *)
  LD7, LD6, LD5, LD4, LD3, LD2, LD1, LD0   : PinList; (* Single Pin PinLists *)
  LA30,LA29,LA28,LA27,LA26,LA25,LA24       : PinList; (* Single Pin PinLists *)
  LA23,LA22,LA21,LA20,LA19,LA18,LA17,LA16  : PinList; (* Single Pin PinLists *)
  LA15,LA14,LA13,LA12,LA11,LA10,LA9, LA8   : PinList; (* Single Pin PinLists *)
  LA7, LA6, LA5, LA4, LA3, LA2, LA1, LA0   : PinList; (* Single Pin PinLists *)
  LRW1_,LRW0_,LSTRB1_,LSTRB0_              : PinList; (* Single Pin PinLists *)
  LRDY1_,LRDY0_,LPAGE1,LPAGE0              : PinList; (* Single Pin PinLists *)
  LSTAT3,LSTAT2,LSTAT1,LSTAT0              : PinList; (* Single Pin PinLists *)
  LLOCK_                                   : PinList; (* Single Pin PinLists *)
  LAE_,LDE_,LCE1_,LCE0_                    : PinList; (* Single Pin PinLists *)
  GD31,GD30,GD29,GD28,GD27,GD26,GD25,GD24  : PinList; (* Single Pin PinLists *)
  GD23,GD22,GD21,GD20,GD19,GD18,GD17,GD16  : PinList; (* Single Pin PinLists *)
  GD15,GD14,GD13,GD12,GD11,GD10,GD9, GD8   : PinList; (* Single Pin PinLists *)
  GD7, GD6, GD5, GD4, GD3, GD2, GD1, GD0   : PinList; (* Single Pin PinLists *)
  GA30,GA29,GA28,GA27,GA26,GA25,GA24       : PinList; (* Single Pin PinLists *)
  GA23,GA22,GA21,GA20,GA19,GA18,GA17,GA16  : PinList; (* Single Pin PinLists *)
  GA15,GA14,GA13,GA12,GA11,GA10,GA9, GA8   : PinList; (* Single Pin PinLists *)
  GA7, GA6, GA5, GA4, GA3, GA2, GA1, GA0   : PinList; (* Single Pin PinLists *)
  GRW1_,GRW0_,GSTRB1_,GSTRB0_              : PinList; (* Single Pin PinLists *)
  GRDY1_,GRDY0_,GPAGE1,GPAGE0              : PinList; (* Single Pin PinLists *)
  GSTAT3,GSTAT2,GSTAT1,GSTAT0              : PinList; (* Single Pin PinLists *)
  GLOCK_                                   : PinList; (* Single Pin PinLists *)
  GAE_,GDE_,GCE1_,GCE0_                    : PinList; (* Single Pin PinLists *)
  IACK_,NMI_,IIOF3,IIOF2,IIOF1,IIOF0       : PinList; (* Single Pin PinLists *)
  ROMEN,RESET_,RESETLOC1,RESETLOC0         : PinList; (* Single Pin PinLists *)
  TCLK0,TCLK1,EMU0,EMU1                    : PinList; (* Single Pin PinLists *)
  TCK,TDI,TDO,TMS,TRS                      : PinList; (* Single Pin PinLists *)
  C0D7,C0D6,C0D5,C0D4,C0D3,C0D2,C0D1,C0D0  : PinList; (* Single Pin PinLists *)
  CRDY0_,CSTRB0_,CREQ0_,CACK0_             : PinList; (* Single Pin PinLists *)
  C1D7,C1D6,C1D5,C1D4,C1D3,C1D2,C1D1,C1D0  : PinList; (* Single Pin PinLists *)
  CRDY1_,CSTRB1_,CREQ1_,CACK1_             : PinList; (* Single Pin PinLists *)
  C2D7,C2D6,C2D5,C2D4,C2D3,C2D2,C2D1,C2D0  : PinList; (* Single Pin PinLists *)
  CRDY2_,CSTRB2_,CREQ2_,CACK2_             : PinList; (* Single Pin PinLists *)
  C3D7,C3D6,C3D5,C3D4,C3D3,C3D2,C3D1,C3D0  : PinList; (* Single Pin PinLists *)
  CRDY3_,CSTRB3_,CREQ3_,CACK3_             : PinList; (* Single Pin PinLists *)
  C4D7,C4D6,C4D5,C4D4,C4D3,C4D2,C4D1,C4D0  : PinList; (* Single Pin PinLists *)
  CRDY4_,CSTRB4_,CREQ4_,CACK4_             : PinList; (* Single Pin PinLists *)
  C5D7,C5D6,C5D5,C5D4,C5D3,C5D2,C5D1,C5D0  : PinList; (* Single Pin PinLists *)
  CRDY5_,CSTRB5_,CREQ5_,CACK5_             : PinList; (* Single Pin PinLists *)

  CLKOUTS                                  : PinList; (* Device specific     *)
  LDBUS,LABUS,LCTL,GDBUS,GABUS,GCTL        : PinList; (* pin group PinLists  *)
  STAT,LOCK_,RDY_,ENB_                     : PinList;
  CONTROL,IIOF,RESETLOC                    : PinList;
  TIMERS,EMU,JTAG,JTINPUTS                 : PinList;
  COMPORT0,COMPORT1,COMPORT2               : PinList;
  COMPORT3,COMPORT4,COMPORT5               : PinList;
  CD,CRDY_,CSTRB_,CREQ_,CACK_              : PinList;
  COMPORT_CNTL				   : PinList;

  IOPINS_NO_LDBUS                          : PinList; (* All IO's except LDBUS *)
  IOPINS_NO_CD                             : PinList; (* All IO's except Comport Data Pins*)
  OUTPUTS_NO_X1                            : PinList; (* All outputs except X1 *)
  IDDQDISCONNECT                           : PinList; (* IDDQ pinlist          *)  

  FIELD1,FIELD2,FIELD3,FIELD4              : PinList; (* Patternfield pinlist*)
  FIELD5,FIELD6,FIELD7,FIELD8              : PinList; (* Patternfield pinlist*)
  FIELD9,FIELD10,FIELD11,FIELD12           : PinList; (* Patternfield pinlist*)
  FIELD13,FIELD14,FIELD15,FIELD16          : PinList; (* Patternfield pinlist*)

  INPUTS,OUTPUTS,IOPINS                    : PinList;
  EVENPINS,ODDPINS,ALLPINS                 : PinList; (* PinLists defined by *)
  EVENINS,ODDINS,PMUINS                    : PinList; (* test engineering for*)
  TESTINS,NOTESTINS                        : PinList; (* use with standard   *)
  ALLOUTS,ALLIOS                           : PinList; (* parametric and      *)
  EVENTRISTATE,ODDTRISTATE                 : PinList; (* functional tests    *)
  ALLTRISTATE                              : PinList; (* functional tests    *)
  NOTRISTATEOUTS,NOTRISTATEIOS             : PinList;
  MUXPINS                                  : PinList; (* All MuxPins         *)
  noPinList                                : PinList; (* empty pin list      *)
