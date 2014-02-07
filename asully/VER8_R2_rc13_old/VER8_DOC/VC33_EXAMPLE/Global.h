(***********************************************************************)
(***                                                                 ***)
(***                     SM320VC33 TEST PROGRAM                      ***)
(***                     ----------------------                      ***)
(***                                                                 ***)
(***                      File Name:  Global.h                       ***)
(***                      Revision :  01 20030320                    ***)
(***                                                                 ***)
(***     Revision History:                                           ***)
(***     00 SC 08/18/99  Program generation.                         ***)
(***     01 SC 08/18/99  Defined EXTCLKdriveWF                       ***)
(***     02 SC 08/18/99  Defined CLKMDSELdriveWF for CLKMODE0/1 pin  ***)
(***     03 SC 08/18/99  Defined EDGEMDdriveWF for EDGMODE pin       ***)
(***     04 SC 08/18/99  Defined RSVdriveWF for RSV0/1 pin           ***)
(***     05 SC 08/18/99  Defined TCKdriveWF for TCK pin              ***)
(***     06 SC 08/20/99  Defined TIhifrqloose13ACTable               ***)
(***     07 SC 08/26/99  Defined TIhifrqloose16ACTable               ***)
(***     08 SC 09/01/99  Defined TIpower13Test                       ***)
(***     10 SC 09/01/99  Defined IDD13max and DIDD13max for Brody    ***) 
(***     11 SC 09/01/99  Defined TIlopower33Test for Brody           ***)
(***     12 SC 09/01/99  Defined IDDlopwr13max and IDDlopwr13max     ***)
(***     13 SC 09/01/99  Defined TIidle2power13Test                  ***)
(***     14 SC 09/29/99  Defined TIpower16Test                       ***)
(***     15 SC 09/29/99  Defined IDD16max and DIDD16max for Brody    ***) 
(***     16 SC 09/30/99  Defined TIlopower13Test                     ***)
(***     17 SC 09/30/99  Defined IDDlopwr16max and IDDlopwr16max     ***)
(***                     TIidle2power16Test,IDDidle2_13max,          ***)
(***                     DIDDidle2_13max                             ***)
(***     18 SC 10/05/99  Defined dieid0-dieid48 pattern and variables. *)
(***     19 SC 11/18/99  Defined JTAG1-5 and First and               ***)
(***                     LastJTAGPatternName variables.              ***)
(***     20 SC 02/23/00  Defined VDDboxlo, DVDDboxlo, VDDboxhi and   ***)
(***                     DVDDboxhi for VBOX test.                    ***)
(***     21 SC 04/05/00  Defined Vboxlo and Vboxhi setup vars        ***)
(***     22 SC 04/27/00  Added FT_stress                             ***)
(***     23 TD 07/05/00  Added TIIDDQDCTable                         ***)
(***     24 SC 07/20/00  Added Temp_92_Degrees_C                     ***)
(***     25 TD 07/20/00  Added sofbins (low_sp_me,mem_fail_10/60/75mhz**)
(***                     at probe.                                   ***)
(***     27 SC 07/21/00  Added TIhifrqspec13ACTable,TIhifrqspec16ACTable*)
(***                     and TIhifrqloose10ACTable                   ***)
(***     28 TD 08/29/00  Added long patterns at  final tests         ***)
(***     29 TD 09/05/00  Cleaned up unused parameter from C31 device ***)
(***     30 SC 10/19/00  Changed Good_100Mhz to Good_90Mhz           ***)
(***     31 SC 10/19/00  Renamed TIhifrqloose10ACTable to            ***)
(***                     TIhifrqloose11ACTable to reflect 90Mhz test ***)
(***     32 SC 10/19/00  Changed TMS320VC33PGE100 to TMS320VC33PGE90 ***)
(***     33 SC 10/20/00  Added orgH1H to origin definition           ***)
(***     34 SC 11/09/00  Added mem_fail_90mhz flag                   ***)
(***     35 SC 11/10/00  Added spfixPattern for PG1.2 serial port fix  *)
(***     36 SC 11/29/00  Added PG1dot1 and PG1dot2 boolean           ***)
(***     37 SC 02/16/01  Changed TMS320VC33PGE90 to TMS320VC33PGE100 ***)
(***     38 SC 02/16/01  Changed Good11ns to Good10ns and Good_90Mhz ***)
(***                     to Good_100Mhz                              ***)
(***     39 SC 03/31/01  Added 60Mhz for softbin as per TIPI request ***)
(***     40 SC 04/11/01  Added RamDatalogFile and Ram_Log_Data var   ***)
(***                     ram test datalog.                           ***)
(***     41 SC 04/11/01  Added datalog_memory as a boolean flag      ***)
(***     42 SC 04/11/01  Added ck_4k* and ck_1k* patterns            ***)
(***     43 SC 04/17/01  Added march13Pattern                        ***)
(***     44 SC 05/18/01  Defined LONG_M13Pattern & LONG_CKPattern    ***)
(***     45 SC 05/18/01  Added SRAM_M13,SRAM_CK & SRAM_M13CK to      ***)
(***                     softtbin                                    ***)
(***     46 SC 02/28/02  Added SRAM_CK1 and SRAM_CK4 to softbin for  ***)
(***                     bin seperation of 1k & 4k SRAM failures     ***)
(***     47 SC 03/27/02  Seperation of LONGCK pattern into LONGCK1 and *)
(***                     LONGCK4 for SRAM visibilty.                 ***)
(***********************************************************************)
(***********************************************************************)
(***                                                                 ***)
(*** VC33PGE00  20021011  Major  Curtis Woods                        ***)
(***  - Initial revision. Program generated from the commercial pro- ***)
(***    gram 320VC33B3.                                              ***)
(***  - Added SMVC33PGEA12EP device & 100C temp.                     ***)
(***                                                                 ***)
(*** VC33PGE01  20030320  Major  Curtis Woods                        ***)
(***  - Added DTX patterns to Global definition.                     ***)
(***  - Added PG1.3 margin patterns.                                 ***)
(***  - Added margin_test boolean for flow control.                  ***)
(***                                                                 ***)
(***********************************************************************)

(*** To be erased if above is correct and complete.                  ***)
(***     48 CW 10/11/02  Start of Military PGM                       ***)
(***     49 CW 10/11/02  Added SMVC33PGEA12EP device & 100C temp     ***)
(***     50 CW 06/13/02  Added DTX Patterns to Global definition.    ***)
(***     51 CW 10/02/02  Added PG1.3 margin patterns.                ***)
(***     52 CW 10/02/02  Added margin_test boolean for flow control  ***)
(***********************************************************************)




{ const SccsId_Global = '@(#) Global.h 1.1 9/28/89 11:57:02 c TI'; }



	(***********************************************************)
	(***		  Global Declarations			 ***)
	(***********************************************************)
	(***							 ***)
	(*** Pascal ordinal types and variables that will be used***)
	(*** in the test program should be declared here. It is  ***)
	(*** possible to use local variables in the various test ***)
	(*** procedures, but those local variables are not	 ***)
	(*** available to the user interactively through the use ***)
	(*** of interactive Pascal. In addition, this file makes ***)
	(*** a handy reference for all names used in the program.***)
	(*** Naming conventions are described here in order to	 ***)
	(*** improve the usability of this file as a reference.  ***)
	(***							 ***)
	(***********************************************************)

type
	(*							   *)
	(*		Declaration of ordinal values		   *)
	(*							   *)

	(*							   *)
	(*	     Declaration of voltage Supply Names	   *)
	(* Supply Names are first referenced in the DeviceTableSet *)
	(* procedure.						   *)
	(*							   *)

	(*							   *)
	(*	     Declaration of Supply Names		   *)
	(* All Supply Names will be assigned minimum and maximum   *)
	(* allowable values in the DeviceTableSet procedure.	   *)
	(*							   *)
	(*		    Naming Convention			   *)
	(*  Use power supply names from data book or specification *)
	(*							   *)

  SupplyName	   = (VDD, DVDD, PLLVDD, Vss);
	(*							   *)
	(*	     Declaration of Voltage Parameters		   *)
	(* All Voltage Parameters should be assigned values in	the*)
	(* DCDataSheetSet procedure.				   *)
	(*							   *)
	(*		    Naming Convention			   *)
	(* 1. Power supplies. Use supply name with addition of	   *)
	(*    min, max, and nom.				   *)
	(* 2. I/O levels. Use type of level (ie. vil, voh, etc.),  *)
	(*    followed by test requirement in caps (ie. TTL,	   *)
	(*    1090MOS, etc.).					   *)
	(* 3. PTU force voltages. Use v, followed by test type	   *)
	(*    (ie. opens, shortslo, etc.)			   *)
	(*							   *)

  VoltageParameter = ( VDDmin, VDDmax, VDDnom,
		       DVDDmin, DVDDmax, DVDDnom,
                       VDDboxlo, DVDDboxlo,
                       VDDboxhi, DVDDboxhi,
		       VDD10min,   VDD10max,VDDabsmax,
		       VDDreten,
		       VDDstressmax,VDDstressmin,  (*High/low      *)
		       DVDDstressmax, DVDDstressmin, 
		       vilstressmin,vilstressmax,  (*voltage	   *)
		       vihstressmin,vihstressmax,  (*functional	   *)
		       volstressmin,volstressmax,  (*test          *)
		       vohstressmin,vohstressmax,  (*voltage       *)
		       vitlstressmin,vitlstressmax,(*parameters	   *)
		       vithstressmin,vithstressmax,(*              *)
		       vihstrclkmin,	           (*              *)
                       VSUBSmin, VSUBSmax, VSUBSnom,
		       vil,	   vih,     vol,	   voh,
		       vil1090, vih1090, vol2080, voh2080,
		       villoos, vihloos, volloos, vohloos,
                       vboxlo_vol, vboxlo_voh, vboxlo_vcomm,
                       vboxhi_vol, vboxhi_voh, vboxhi_vcomm,
		       vload, vloadmatch,
		       vilCLK,	  vihCLK,    volCLK,	vohCLK,
		       vil1090CLK,vih1090CLK,vol2080CLK,voh2080CLK,
		       villoosCLK,vihloosCLK,volloosCLK,vohloosCLK,
		       vloadCLK,
                     (* parametric test parameters *)
		       vopens,
		       vshortslo,  vshortshi,
		       vinleaklo,  vinleakhi,
		       vtrilkglo,  vtrilkghi,
		       vloadpower,
                       vitlclk, vithclk,
		       vitl,	   vith);
	(*							   *)
	(*	     Declaration of Current Parameters		   *)
	(* All Current Parameters should be assigned values in	the*)
	(* DCDataSheetSet procedure.				   *)
	(*							   *)
	(*		    Naming Convention			   *)
	(* 1. Power supplies. Use supply current name followed by  *)
	(*    min, max, or nom. 				   *)
	(* 2. I/O levels. Use type of level (ie. iol, ioh, etc.),  *)
	(*    followed by test requirement in caps (ie. TTL, MOS,  *)
	(*    CLK, etc).					   *)
	(*							   *)
  CurrentParameter = ( IDDmin,	   DIDDmin,
		       IDDmax,     DIDDmax,
                       IDD13max,   DIDD13max,
                       IDD16max,   DIDD16max, 
                       IDDlopwr16max,  DIDDlopwr16max, 
                       IDDlopwr13max,  DIDDlopwr13max,
                       IDDidle2_16max, DIDDidle2_16max,
                       IDDidle2_13max, DIDDidle2_13max,
                       IDDQmin,    DIDDQmin,
                       IDDQmax,    DIDDQmax,
                       IDDQ3min,    DIDDQ3min,
                       IDDQ3max,    DIDDQ3max,
                       ISUBSmin,   ISUBSmax,
		       iol,	     ioh,
                       ioliddq,      iohiddq,
		       iolCLK,	     iohCLK,
		       iolmatch,     iohmatch,
                       iolstressmin, iohstressmin,
                       iolstressmax, iohstressmax,
		       iolpower,     iohpower,
		       iopens,
		       ishortslo,  ishortshi,
		       iinleaklo,  iinleakhi,
{		       PMUinleaklo1, PMUinleakhi1,   }
		       iinleakpulluplo1,iinleakpulluphi1,
  		       iinleakpulldownlo2,iinleakpulldownhi2,
		       iinleakolo, iinleakohi,
		       itrilkglo,  itrilkghi);

	(*							   *)
	(*	     Declaration of DC Table names		   *)
	(* All DC Table names are first referenced in the	   *)
	(* DCDataSheetSet and DCTableSet procedure. Both the	   *)
	(* DCDataSheets and DCTables are tables of type DCTable    *)
	(*							   *)
	(*		    Naming Convention			   *)
	(* Start with TI, followed by a descriptor describing what *)
	(* type of table it is (ie. data, opens, inleak1), followed*)
	(* by DCTable.						   *)
	(*							   *)

  DCTable	   = ( TIdataDCTable,			     (*DCDataSheet *)
		       TIopensDCTable,			     (*DCTable	   *)
		       TIshorts1DCTable, TIshorts2DCTable,   (*DCTable	   *)
		       TIinleak1DCTable, TIinleak2DCTable,   (*DCTable	   *)
		       TItrilkg1DCTable, TItrilkg2DCTable,   (*DCTable	   *)
		       TIpowerDCTable,			     (*DCTable	   *)
		       TIlooseDCTable,			     (*DCTable	   *)
                       TIvboxloDCTable,                      (*DCTable     *) 
                       TIvboxhiDCTable,                      (*DCTable     *)
		       TIpbtimingDCTable, 		     (*DCTable	   *)
		       TIhifrqminDCTable, 		     (*DCTable	   *)
		       TIhifrqmaxDCTable, 		     (*DCTable	   *)
                       TIlofrqminDCTable,                    (*DCTable     *)
                       TIlofrqmaxDCTable,                    (*DCTable     *)
		       TIlevelsDCTable, 		     (*DCTable	   *)
		       TIstressmaxDCTable,                   (*DCTable	   *)(*For high/low    *)
		       TIstressminDCTable, 		     (*DCTable	   *)(*functional tests*)
                       TIIDDQDCTable,                        (*DCTable	   *)
		       TIallDCTable);			     (*DCTable	   *)
		       

	(*							   *)
	(*	     Declaration of Time Parameters		   *)
	(* All Time Parameters should be assigned values in the    *)
	(* ACDataSheetSet procedure.				   *)
	(*							   *)
	(*		    Naming Convention			   *)
	(* Start with t, followed by data book description of	   *)
	(* the parameter (ie. wCL, rC, etc.).			   *)
	(*							   *)

  TimeParameter    = (tper,tref,twCIL,twCILcf,twCIH,twCIHcf,tcCI,tfH,twHL,twHH,trH,tdH1LH3H,
		      tdH3LH1H,tcH,tdH1LSL,tdH1LMSL,tdH1LSH,tdH1LMSH,
		      tdH1HRWLmax,tdH1LA,
		      tsuDRmin,thDRmin,tsuRDYmin,
		      thRDYmin,
		      tdH1HRWHmax,tsuHOLD_min,
		      tvDWmax,thDWmin,thD,
		      loos,tdloos,
		      tMCMP,tfHmax,tdH1LMSHmax,tdH1LSHmin,
		      tdH1LSHmax,twHHmin,twHHmax,
		      trHmax,tdH1LAmin,
		      tdHLHLmax,twHLmin,
		      tdH1HRWLmin,tdH1LSLmin,tdH1LAmax,tdH1HAWmax,
		      twHLmax,tdHLHHmax,tSCANIN,
		      toffset,tdCLKINH1,tdCLKINH3,tTEST,tdSCANOUT,tdH1LSLmax,
		      tdHLHHmin,tsuINT,tsuINTCLKSTP,tc1r,tscanper,tscanadj,tH1rlo,
		      twH1h,tH1flo,tclockdelay,
                      tH3flo,tH3fhi,tH3rlo,tH3rhi,
                      tsuDRSP,thDRSP,tsuDX, thDX,tsuFSR,thFSR,
     		      tdCLKXHDX,tdCLKXHFSXH,tsuFSRCLKRL,
		      tsuDRCLKRL,thDRCLKRL,thFSRCLKRL,tdCLKXHFSXL,
		      tsuEFSXCLKXHmin,tsuEFSXCLKXHmax,thEFSXCLKXL,tsuDRECLKRL,
		      tdECLKXHFSXH,tcSCKmin,tcESCKmin,
		      tdECLKXHDX,tdDXZ,
                      tsuFSRECLKRL,thFSRECLKRL,tdECLKXHFSXL,
		      tsuEFSXHECLKXHmin,tsuEFSXHECLKXHmax,thEFSXECLKXL,
		      tdH1HCLKXH,tdH1HCLKXL,tdH1HCLKX,tdH1HCLKR,
                      tdH1HCLKRH,tdH1HCLKRL,thCLKRDR,tdH1LIOAImin,tdH1LIOAImax,
                      tsuRESET_,tdCLKINHH1Hmax,tdCLKINHH1L,tdCLKINHH3L,tdCLKINHH3H,
		      tsuRESETHH1L,tdH1HIACKL,tdH1HIACKH,tdCLKINHH3Lmax,
		      trSCK,tfSCK,thDRECLKRL,tdECHDXV,tdCHDXV,tdFSXDXV,
		      tvHOLDA_,tdH1LSHH,tdisH1LS,tenH1LS,tdisH1LRW,
                      tenH1LRW,tdisH1LA,tenH1LA,tdisH1HD,EXTCLKR,EXTCLKX,
		      tdH1HCLKXrlo,tdH1HCLKXfhi,tdH1HCLKRrlo,tdH1HCLKRfhi,
                      twSCKmax,twSCKmin,
		      trSCKX,trSCKR,tfSCKX,tfSCKR,tvH3HXF,tdH3HXFOI,tdH3HXFIO,
		      tsuXF,thXF,tsuXF1SIGI,thXF1SIGI,tsuXF1LDII,thXF1LDII,
                      tdH3HXF0L,tdH3HXF0H,tdCLKINH2L,tdSPGPIO,tsuSPGPIO,
		      thSPGPIO,twSCKXL,twSCKXH,twSCKRL,twSCKRH,
                      twTCLKL,twTCLKH,twTCLKmin,twTCLKmax,
                      trTCLK,tfTCLK,tdTCLKrh,tdTCLKrl,tdTCLKfh,tdTCLKfl,
		      tsuTCLK,thTCLK,tdTCLK,tsuTCLKGPIO,thTCLKGPIO,tdTCLKGPIO,
                      thH3H,
		      tECLKXLduty, tECLKXHduty, tECLKRLduty, tECLKRHduty,
		      tdisH1HXD, tdisH3HXA, tdH3HCONTROLH, tdisRESETLASYNCH,
		      twINT, twHOLD_, twHOLDA_,tdCLKINHH1Hmin,tdCLKINHH3Lmin,
                      tdCLKINHH1Lmax,tdCLKINHH1Lmin,
                      tdCLKINHH3Hmax,tsuTDITMS,thTDITMS,tdTDO,tJTAG,
                      tdCLKINHH3Hmin);

	(*							   *)
	(*	     Declaration of Waveform names		   *)
	(* All Waveform names should be assigned values in the	   *)
	(* ACTableSet procedure.				   *)
	(*							   *)
	(*		    Naming Convention			   *)
	(* Start with PinList name, followed by the function of the*)
	(* waveform (ie. drive, compare, nocompare, etc.), followed*)
	(* by WF.						   *)
	(*							   *)

  Wave             = ( CLKINdriveWF,     H1strobeWF,
                       H3strobeWF,       CRYSDUTstrobeWF,
                       SH1strobeWF,       SH3strobeWF,
                       SyncH1HstrobeWF,   SyncH1LstrobeWF,
                       SyncH3HstrobeWF,   SyncH3LstrobeWF,
                       STCLKstrobeWF,
                       SCLKXstrobeWF,     SCLKRstrobeWF,
                       SyncCLKXHstrobeWF, SyncCLKXLstrobeWF, 
                       SyncCLKRHstrobeWF, SyncCLKRLstrobeWF, 
		       ABUSstrobeWF,	  ABUSbstrobeWF,
		       DBUSstrobeWF,      DBUSdriveWF,
                       RDY_driveWF,	  RDY_driveNRWF,
		       DBUSNRdriveWF,	 
		       RW_strobeWF,	 STRB_strobeWF,  STRB_astrobeWF,
		       STRB_bstrobeWF,
		       HOLD_driveWF,	 HOLDA_strobeWF, HOLD_BdriveWF,
		       HOLDSTRB_strobeWF,HOLDSTRB_HstrobeWF,
		       HOLDABUSstrobeWF, HOLDRW_strobeWF,
		       ABUSHIZstrobeWF,  DBUSHIZstrobeWF,
		       RW_HIZstrobeWF,	 STRB_HIZstrobeWF,
		       RESET_driveWF,	 INT_driveWF, INT_BdriveWF,
                       INT_CLKSTPdriveWF,
		       IACK_strobeWF,	 MCBLdriveWF,
		       RESETHIGH_driveWF,
		       XFdriveWF,	 XFstrobeWF,
		       CLKXdriveWF,	 ECLKXdriveWF,   CLKXstrobeWF,
		       CLKRdriveWF,	 ECLKRdriveWF,   CLKRstrobeWF,
		       FSXstrobeWF,	 FSXdriveWF,
		       FSRstrobeWF,	 FSRdriveWF,
                       FSXadriveWF,      DXastrobeWF,
		       DXstrobeWF,	 DXdriveWF,
		       DRstrobeWF,	 DRdriveWF,
                       DRthdriveWF,
		       TCLKdriveWF,	 TCLKstrobeWF,
                       TCLKNRdriveWF,    XFNRdriveWF,
		       SCANOUTstrobeWF,  CdriveWF,
		       ETdriveWF,	 ETstrobeWF,
		       TESTdriveWF,	 TEST1driveWF,   TESTstrobeWF,
		       ContinueWF,	 ALLoffWF,
		       RESET_HIZstrobeWF,SHZ_driveWF,
                       SHZ_ABUSstrobeWF,
		       PRFINTstrobeWF,	 PRFINTdriveWF,
                       ABUSwrtendstrobeWF,
		       ABUSwrtbgnstrobeWF,
		       DBUSendstrobeWF, 
                       DRECLKRdriveWF,
		       DXECLKXstrobeWF,
                       FSRECLKRdriveWF,
		       FSXMINECLKXdriveWF,FSXECLKXstrobeWF,
		       FSXMAXECLKXdriveWF,FSXMINCLKXdriveWF,
		       FSXMAXCLKXdriveWF,SCANclkWF,
		       CLKX1driveWF,CLKX2driveWF,
		       CLKR1driveWF,CLKR2driveWF,
                       EXFSXdrive1WF, EXFSXdrive2WF,
                       EXSPCLKXdrive1WF, EXSPCLKXdrive2WF,
                       EXSPCLKXdrive3WF, EXSPCLKXdrive4WF,
		       EXSPCLKXdrive5WF, EXFSRFdrive2WF,
                       EXSPCLKRdrive1WF, EXSPCLKRdrive2WF,
                       EXSPCLKRdrive3WF, EXSPCLKRdrive4WF,
		       EXSPCLKRdrive5WF, 
                       SPCLKXdrive1WF, SPCLKXdrive2WF,
                       SPCLKXdrive3WF, SPCLKXdrive4WF,
		       SPCLKXdrive5WF, EXFSRdrive1WF,
                       SPCLKRdrive1WF, SPCLKRdrive2WF,
                       SPCLKRdrive3WF, SPCLKRdrive4WF,
		       SPCLKRdrive5WF, EXFSXdrive5WF,
		       EXDXstrobe1WF, EXDXAstrobe1WF, EXDRdrive2WF,
                       EXFSRVdrive2WF, EXDRdrive5WF,
                       EXDXAastrobe1WF, EXFSXadrive1WF,
                       EXDXstrobe4WF, DUMPclkWF,
                       EXTDXdriveWF,   EXTDXstrobe1WF,
                       EXTDXAstrobe1WF,EXTDXAastrobe1WF,
                       EXTDRdrive2WF,  EXFSRdrive2WF,
                       EXTDRdrive5WF,  EXTDXstrobe4WF,
                       FSRdrive1WF,    FSRdrive4WF,
                       FSXdrive1WF,    FSXdrive4WF,
		       DRGPIOstrobeWF, DRGPIOdriveWF,
		       DXGPIOstrobeWF, DXGPIOdriveWF,
		       FSRGPIOstrobeWF, FSRGPIOdriveWF,
		       FSXGPIOstrobeWF, FSXGPIOdriveWF,
		       CLKRGPIOstrobeWF, CLKRGPIOdriveWF,
		       CLKXGPIOstrobeWF, CLKXGPIOdriveWF,
		       XF0SIGIstrobeWF, XF1SIGIdriveWF,
		       XF0LDIIstrobeWF, XF1LDIIdriveWF,
		       XF0STIIstrobeWF, HOLDTRstrobeWF,
		       XFOIstrobeWF, XFIOstrobeWF,
		       TIMGPIOstrobeWF, TIMGPIOdriveWF,
                       TDDXZstrobeWF,TCKdriveWF,
                       EXTCLKdriveWF, CLKMDSELdriveWF,
                       EDGEMDdriveWF, RSVdriveWF,
                       TDITMSdriveWF,JTAGdriveWF,
                       TDOstrobeWF,
                       FSXbdriveWF);

        (*                                                         *)
        (*           Declaration of Origin names                   *)
        (* Origin are used to offset timings after a Sync-up.      *)
        (* ACTableSet procedure.                                   *)
        (*                                                         *)
        (*                  Naming Convention                      *)
        (* Start with a TimeParameter name which indicates the     *)
        (* offset, and drop the leading t. Concatenate multiple    *)
        (* TimeParameters for those to be calculated by expression.*)
        (*                                                         *)
 
  Origin          = ( orgH1L, orgH1H, orgtoffset, orgtoffset_im,orgtdH1HCLKXH, orgtdH1HCLKXL, orgtdH1HCLKRL);

  (* The following added for Test Engineering changes *)
  ParallelDevice  =       ( noParallelDevice); 
  AnalogVoltageParameter = (noAnalogVoltageParameter);
  AnalogTimeParameter    = (noAnalogTimeParameter);
  AnalogIntegerParameter = (noAnalogIntegerParameter);
  AnalogLimitParameter   = (noAnalogLimitParameter);
  AnalogTable            = (noAnalogTable);
  SamplerWindow          = (noSamplerWindow);
  SamplerTable           = (noSamplerTable );
        (*                                                         *)
        (*           Declaration of new Vega types                 *)
        (* Declare the new types required for Vega programs        *)
        (*                                                         *)
        (*                                                         *)
  LECSetup               = (noLECSetup);
  WaveGroup              = (noWaveGroup);

	(*							   *)
	(*	     Declaration of AC Table names		   *)
	(* All AC Table names are first referenced in the	   *)
	(* ACDataSheetSet and ACTableSet procedure. Both the	   *)
	(* ACDataSheets and ACTables are tables of type ACTable    *)
	(*							   *)
	(*		    Naming Convention			   *)
	(* Start with TI, followed by a descriptor describing what *)
	(* type of table it is (use the period in the description, *)
	(* ie. 1000, 200loose, etc.), followed by ACTable.	   *)
	(*							   *)

  ACTable	   = ( TIparametricACTable, 
		       TIhifrqloose13ACTable,
                       TIhifrqloose13DIV2ACTable,
                       TIhifrqloose16ACTable,
                       TIhifrqloose16DIV2ACTable,
                       TIhifrqloose10ACTable,
                       TIhifrqloose11ACTable,
                       TIhifrqspec13ACTable,
                       TIhifrqspec16ACTable,
		       TIhifrqminACTable,	
		       TIhifrqmaxACTable,	
		       TIhifrqlooseACTable,	
                       TIlofrqmaxACTable,
                       TIlofrqminACTable,
                       TIlofrqlooseACTable,
		       TInomlooseACTable,
                       TIvboxloACTable,
                       TIvboxhiACTable,
		       TIstressACTable,			   (*high/low voltage functional tests*)
                       TIIDDQACTable,                      (*IDDQ actable  *)
		       TIallACTable );			   (*Set all tables*)

	(*							   *)
	(*	     Declaration of CycleTable names		   *)
	(* Normally, there will be only one CycleTable name. At    *)
	(* a maximum, two are allowed. The first reference of	   *)
	(* the CycleTable name will be in the CycleTableSet	   *)
	(* procedure.						   *)
	(*							   *)
	(*		    Naming Convention			   *)
	(* Start with TI, followed by a descriptor describing what *)
	(* type of table it is (ie. all), followed by CycleTable.  *)
	(*							   *)

  CycleTable	   = (TIallCycleTable, TIspecCycleTable,TIsportCycleTable);

	(*							   *)
	(*	     Declaration of Cycle names 		   *)
	(* Declaration of Global Cycle Type names. Up to 64 are    *)
	(* allowed. Use one for each timing set required. Global   *)
	(* Cycle Types are initialized in the CycleTableSet	   *)
	(* procedure.						   *)
	(*							   *)

  Cycle   =
      ( NullCY,
        SyncDRDCycle,
        SDRDCycle,
        DRDCycle,    DW1Cycle,    DW2Cycle,    DWRCycle,    DWWCycle,     DW2ACycle,
        DRDthCycle,  DW1thCycle,  DW2thCycle,  DWRthCycle,  DWWthCycle,
        DRDESCKCycle,DW1ESCKCycle,DW2ESCKCycle,DWRESCKCycle,
                                               DWRXFCycle,
        DRDSP1Cycle, DW1SP1Cycle, DW2SP1Cycle, DWRSP1Cycle, DWWSP1Cycle,
        DRDSP1ACycle,                                       DWWSP1ACycle,
        DRDSP1AaCycle,                                      DWWSP1AaCycle,
        DRDSP2Cycle, DW1SP2Cycle, DW2SP2Cycle, DWRSP2Cycle, DWWSP2Cycle,
        DRDSP4Cycle, DW1SP4Cycle, DW2SP4Cycle, DWRSP4Cycle, DWWSP4Cycle,
        DRDSP5Cycle, DW1SP5Cycle, DW2SP5Cycle, DWRSP5Cycle, DWWSP5Cycle,
        DW2SP5AaCycle,
        DRDSIGICycle,DW1SIGICycle,DW2SIGICycle,DWRSIGICycle,
        DRDLDIICycle,
        DRDSTIICycle,
        DRDCICycle,  
        DRDaCycle,
        DRDbCycle,
        DRDH7Cycle,
        DRDH9Cycle,
        DRDStopCycle,
        IDDQCycle,
        XF1OICycle,  XF0OICycle,  XFIOCycle,
        ALLOFFcycle,
        HOLDTRCycle, SHZ_Cycle,    TDDXZCycle,  TIMGPIOCycle, IDLECycle); 


	(*							   *)
	(*	     Declaration of Vector Map names		   *)
	(* Normally, there will be only one Vector Map name. The   *)
	(* Vector Map tells the tester how your patterns are	   *)
	(* formatted. Each VectorMap is created during the creation*)
	(* of a CycleTable, in the CycleTableSet procedure.	   *)
	(*							   *)
	(*		    Naming Convention			   *)
	(* Start with TI, followed by a descriptor describing what *)
	(* tests the Vector Map applies to (ie. all), followed by  *)
	(* VectorMap.						   *)
	(*							   *)

  VectorMap	   = ( TIallVectorMap);

	(*							   *)
	(*	     Declaration of Test Names			   *)
	(* Normally, there will be only one Vector Map name. The   *)
	(* Vector Map tells the tester how your patterns are	   *)
	(* formatted. Each VectorMap is created during the creation*)
	(* Of a CycleTable, in the CycleTableSet procedure.	   *)
	(*							   *)
        (***********************************************************)
        (** TestNames with a comment 'comp' are patterns that     **)
        (** changed for the C31 compaction.                       **)
        (***********************************************************)

  TestName	   = (TIopensTest,		 (* Name of std opens  test*)
		      TIshortsTest,		 (* Name of std shorts test*)
		      TIinleakTest,		 (* Name of std inleak test*)
		      TIpuleak1Test,
		      TIpdleak2Test,
		      TIpullupleaklo1Test,
		      TIpulldownleakhi2Test,
		      TItrilkgTest,		 (* Name of std trilkg test*)
                      TIPMUtrilkgloTest1,        (* Name of PMU trilkg test*) 
                      TIPMUtrilkghiTest1,        (* Name of PMU trilkg test*)
                      TIpower13Test,             (* Name of 13ns power test *)
                      TIpower16Test,             (* Name of 16ns power test *)
                      TIlopower13Test,           (* divede by 16 power test *)
                      TIlopower16Test,           (* divede by 16 power test *) 
                      TIidle2power13Test,        (* IDLE2 mode power test   *) 
                      TIidle2power16Test,        (* IDLE2 mode power test   *)

                      TIQPower3Test,
                      TIiddqTest,                (* Clock Stop power test   *)

                      CRYSTALTest,               (* Name of Crystal test   *)
		      shz_portPattern,           (* C33 tristate pattern   *)
		      IDDPattern,		 (* Norm-mode power pattern*)
                      IDD1Pattern,               (* continuous loop IDD     *)
                                                 (* pattern for MAXSPEED.   *)
                      IDD2Pattern,               (* continuous loop IDD     *)
                                                 (* pattern for LOPOWER test*)
                      IDDIdlePattern,            (* IDLE2 IDD pattern       *)
                      IDDQPattern,               (* IDDQ Pattern           *)
                      IDDQ1Pattern,              (* IDDQ Pattern case1     *)
                      IDDQ2Pattern,              (* IDDQ Pattern case2     *)
		      CRYSTALPattern,		 (* Crystal test pattern   *)
		      TEMPWAITPattern,		 (* TemperatureWait pattern*)
(* *********************************************************************** *)
(* *****                Start of Functional Patterns                 ***** *)
(* *********************************************************************** *)
                      addrmodePattern,
                      alu_faultPattern,
                      aludat1Pattern,
                      aludat2Pattern,
                      aludat3Pattern,
                      aludat4Pattern,
                      aludat5Pattern,
                      aludat6Pattern,
                      aludat7Pattern,
                      aludat8Pattern,
                      alufp1_1Pattern,
                      alufp2_1Pattern,
                      alufp2_2Pattern,
                      alufp2_3Pattern,
                      alufp3_1Pattern,
                      alufp3_2Pattern,
                      alufp3_3Pattern,
                      alufp3_4Pattern,
                      alufp3_5Pattern,
                      aluinstPattern,
                      aux_faultPattern,
                      cache1Pattern,
                      cache2Pattern,
                      cache3Pattern,
                      circPattern,
                      condbrPattern,
                      condcodePattern,
                      ctrl_fault_vc33Pattern,
                      dmaPattern,
                      dma_faultPattern,
                      edgeintrpPattern,
                      exintrptPattern,
                      extholdPattern,
                      extmorePattern,
                      extportPattern,
                      extwaitPattern,
                      fix_pg1Pattern,
                      integer1Pattern,
                      integer2Pattern,
                      integer3Pattern,
                      integer4Pattern,
                      integer5Pattern,
                      intrpt1Pattern,
                      iofregPattern,
                      logicalPattern,
		      memtest4Pattern,
                      mempri_vc33Pattern,
                      mult1Pattern,
                      mult2Pattern,
                      mult3Pattern,
                      mult_faultPattern,
                      page_portPattern,
                      parPattern,
                      pbifPattern,
                      pbifmorePattern,
                      pipe2Pattern,
                      pipenewPattern,
                      portcextPattern,
                      power_downPattern,
                      progflo1Pattern,
                      progflo2Pattern,
                      ram1Pattern,
                      ram16k_funcPattern,
                      ram2aPattern,
                      ram2bPattern,
                      reg1Pattern,
                      reg2Pattern,
                      regfiles_vc33Pattern,
                      regrdyPattern,
                      romcodePattern,
                      romexe16bitPattern,
                      romexe32bitPattern,
                      romexe8bitPattern,
                      romexeserPattern,
                      speedextPattern,
                      speedpthPattern,
                      stackPattern,
                      timer0_faultPattern,
                      timer1Pattern,
                      timer1_faultPattern,
                      timer2Pattern,
                      trapPattern,
                      trap2Pattern,
                      serport1Pattern,
                      serport2Pattern,
                      serport3aPattern,
                      serport4Pattern,
                      serport5Pattern,
                      serport6Pattern,
                      serport7Pattern,
                      spfixPattern,
                      power_avgPattern,  
                      reten_0r,
                      reten_0w,
                      reten_1r,
                      reten_1w,
                      iddq_0,
                      iddq_1,
		      reten0rw_master,
		      reten1rw_master,
		      aluinst_div2Pattern,
		      aluinst_pllPattern, 
                      power_down_div2Pattern,
                      power_down_pllPattern,
		      emuscanPattern,
		      rsv_portPattern,
                      resetPattern,
                      ram2kwalk01Pattern,
                      ram32kwalk01Pattern,
                      ram2kckbPattern,
                      ram32kckbPattern,
                      ram_800k,
                      ram_804k,
                      lifetestPattern,
                      levelsPattern,
                      lilkillPattern,
                      lilkill1Pattern,
                      lilkill2Pattern,
                      ck_4ka_Pattern,
                      ck_4kb_Pattern,
                      ck_4kc_Pattern,
                      ck_4kd_Pattern,
                      ck_4ke_Pattern,
                      ck_4kf_Pattern,
                      ck_4kg_Pattern,
                      ck_4kh_Pattern,
                      ck_1ka_Pattern,
                      ck_1kb_Pattern,
                      march13_1kPattern,
                      march13_4kPattern,
                      dtxn_r0_Pattern,
                      dtxn_r1_Pattern,
                      dtxn_ram2_0Pattern,
                      dtxn_ram2_1Pattern,
                      dtxn_ram2_2Pattern,
                      dtxn_ram2_3Pattern,
                      dtxn_ram3_0Pattern,
                      dtxn_ram3_1Pattern,
                      dtxn_ram3_2Pattern,
                      dtxn_ram3_3Pattern,
                      char_levelsPattern,
                      char_resetPattern,
                      char_resetPattern2,
                      reset_0613Pattern,
                      char_iofregPattern,
                      char_aludat5Pattern,
                      char_serport1Pattern,
                      extholdxPattern,
                      char_shz_portPattern,
                      pllPattern,
                      LONG1Pattern,
                      LONGRamPattern,
                      LONG_M13Pattern,
                      LONG_CKPattern,
                      LONG_CK1Pattern, 
                      LONG_CK4Pattern, 
                      VBoxloPattern,
                      VBoxhiPattern,
                      Div2Pattern,
                      LONGSPORT,
                      LONG_CCPatterns,
  

(**************************)
(* PG 1.3 Margin Patterns *)
(**************************)
                      cc_ck_4ka_Pattern,
                      cc_ck_4kb_Pattern,
                      cc_ck_4kc_Pattern,
                      cc_ck_4kd_Pattern,
                      cc_ck_4ke_Pattern,
                      cc_ck_4kf_Pattern,
                      cc_ck_4kg_Pattern,
                      cc_ck_4kh_Pattern,
                      cc_ck_1ka_Pattern,
                      cc_ck_1kb_Pattern,

                      cc_dtxn_ram2_0Pattern,
                      cc_dtxn_ram2_1Pattern,
                      cc_dtxn_ram2_2Pattern,
                      cc_dtxn_ram2_3Pattern,
                      cc_dtxn_ram3_0Pattern,
                      cc_dtxn_ram3_1Pattern,
                      cc_dtxn_ram3_2Pattern,
                      cc_dtxn_ram3_3Pattern,
                      cc_dtxn_ram2Pattern,

                      cc_march13_1kPattern,
                      cc_march13_4kPattern,

                      cc_mempri_vc33Pattern,

                      cc_ram1Pattern,
                      cc_ram16k_funcPattern,
                      cc_ram2aPattern,
                      cc_ram2bPattern,

                      cc_ram2kwalk01Pattern,
                      cc_ram32kwalk01Pattern,
                      cc_ram2kckbPattern,
                      cc_ram32kckbPattern,
                      cc_ram_800k,
                      cc_ram_804k,

(* *********************************************************************** *)
(* *****                End of Functional Patterns                   ***** *)
(* *********************************************************************** *)
                      OUTNOISEPattern,
                      SCANALLCTLPattern,         (* Control Scan test      *)
                      SCANDUMPPattern,           (* SCAN dump test         *)
                      SCANIN0,
                      SCANIN1,
                      SCANC31CTLPattern,
                      SCANINSTIPattern,
                      SCANINLDIPattern,
                      SCANIN2ndPattern,
                      SCANOUTPattern,
		      SYNCPattern,
                      serport_sync, 
                      SYNC_DIV2, 
                      SYNC_PLL, 
		      SYNCaPattern,
                      RESETALLPattern,
                      RESETALL1Pattern,
                      RESETIACKPattern,
                      MCSPattern,
                      SERPORT7charPattern,
		      FLUSHcharPattern,
                      SERPORTZPattern,
                      HOLDTRIS1Pattern,
                      HOLDWIDTHPattern,
                      HOLDTRISPattern,
                      DummyTestName,
		      dieid0,
                      dieid1 ,dieid2 ,dieid3 ,dieid4 ,dieid5 ,dieid6 ,dieid7 ,dieid8 ,dieid9 ,dieid10,
                      dieid11,dieid12,dieid13,dieid14,dieid15,dieid16,dieid17,dieid18,dieid19,dieid20,
                      dieid21,dieid22,dieid23,dieid24,dieid25,dieid26,dieid27,dieid28,dieid29,dieid30,
                      dieid31,dieid32,dieid33,dieid34,dieid35,dieid36,dieid37,dieid38,dieid39,dieid40,
                      dieid41,dieid42,dieid43,dieid44,dieid45,dieid46,dieid47,dieid48,
		      JTAG_80000x,
                      JTAG_80400x,
                      JTAG_80980x,
                      JTAG_809c0x,
                      emu01_shz,
                      pll,
                      Debug1,
                      Debug2,
                      Debug3,
                      Debug4,
                      Debug5);         (* The dummy test name was   *)
                                              (* added to allow indexing   *)
                                              (* past the end of the test  *)
                                              (* names.                    *)


	(*							   *)
	(*	     Declaration of Test Types			   *)
	(* Normally, there will be three test types, Probe, Final, *)
	(* and QA. The test type is used to select from multiple   *)
	(* sets of test parameters for different tests. Test Flow  *)
	(* can also be selected, but in the standard program, all  *)
	(* test flows are assumed to be the same. A common addition*)
	(* to the Test Types may be temperature (i.e. Final0Deg)   *)
	(*							   *)

  TITypeOfTest	   = (Probe,PRE_Burnin_Handler,PRE_Burnin_Handtest,
                      Final_Handler,Final_Handtest,QA_Handler,QA_Handtest);

  SoftBin	   = (noresult,	      (* Counter for no results *)
                      opens, shorts,          (* Parametric soft bins   *)
                      jtag,
                      STLL, LTSL,
                      Good_100Mhz,Good_90Mhz, Good_75Mhz, Good_60Mhz,_60Mhz,
                      OthlrIddq,OtlrVbxH,OtlrVbxL,Otlr_oth,FuncGros,
                      Funcscan,FuncSlow,low_sp_mem,mem_fail_10mhz,mem_fail_60mhz,
                      mem_fail_75mhz,mem_fail_90mhz,SRAM,SRAM_M13,SRAM_CK,SRAM_CK1,SRAM_CK4,SRAM_M13CK,DRAM,Flash,ROM,FuncFast,
                      cc_mem_fail_10mhz, cc_mem_fail_60mhz, cc_mem_fail_75mhz,cc_mem_fail_90mhz, cc_SRAM, cc_SRAM_M13,cc_SRAM_CK,cc_SRAM_CK1,
		      cc_SRAM_CK4,cc_SRAM_M13CK,
                      Para_AC,Para_DC,avgpwr,maxpwr,analog,FT_stress,                      
                      sublkg,
                      inleak,inleakpu,inleakpd,
		      hifunc,lofunc,	  (* High/low voltage functional bins *)
                      trileak,PMUtrilkg, idd, 
                      iddlopwr,iddIdle,iddq,iddq_pre,iddq_post,iddq_delta,v_out,
		      scanall,                (* Functional soft bins    *)
		      scanflsh,               
		      retention,veryloose,
                      ram,regfile,    
                      faultpat,stress,
                      lthflv,  lthfhv,  ltlflv,  ltlfhv,
                      sthflv,  sthfhv,  stlflv,  stlfhv,
                      slhflv,  slhfhv,  sllflv,  sllfhv,
                      scanhflv, scanhfhv,
                      scanlflv, clocks,
                      loosehfnv, looselfnv,
                      sync,                    (* Sync-up soft bins       *)
                      H1H3, tclk,
                      syncLFT,
                      specsync, spclks,
                      GoodCat3,
                      Good16ns,Good13ns,Good10ns,
                      lastsoftbin);


  HardBin = (BIN00,			 (* This one can't be used.*)
	     BIN01, BIN02, BIN03, BIN04, (* Normal use will only   *)
	     BIN05, BIN06, BIN07, BIN08, (* include 1-8, but 16 can*)
	     BIN09, BIN10, BIN11, BIN12, (* be used with some	   *)
	     BIN13, BIN14, BIN15, BIN16, (* handlers.	There are  *)
	     BIN17, BIN18, BIN19, BIN20, (* a total of 32 for tipc *)
	     BIN21, BIN22, BIN23, BIN24, (* probe interface.	   *)
	     BIN25, BIN26, BIN27, BIN28, (*			   *)
	     BIN29, BIN30, BIN31);	 (*			   *)

  HandlerType	   = (noHandlerType);
  HandlerResult    = (noHandlerResult);

	(*							   *)
	(*	     Declaration of Device Types		   *)
	(* Declare the device types to be selected among in the    *)
	(* OperatorSetup menu. This will normally be used to	   *)
	(* control test flow.					   *)
	(*							   *)

  DeviceType = (TMS320VC33PGE100,
                TMS320VC33PGE,
                TMS320VC33PGE75,
                TMS320VC33PGE60, 
                TMS320VC33_Probe,
		TMS320VC33_SWR,
                SMVC33PGEA12EP);

	(*							   *)
	(*	     Declaration of Temperature Types		   *)
	(* Declare the temperature types to be selected among in   *)
	(* the OperatorSetup menu. This will normally be used to   *)
	(* control selection of supply limits.			   *)
	(*							   *)

  TempType   = (Temp_N40_Degrees_C,Temp_0_Degrees_C,   
                Temp_25_Degrees_C,Temp_90_Degrees_C,
                Temp_92_Degrees_C,Temp_105_Degrees_C);

	(*							   *)
	(*	     Call to MegaTest provided procedures	   *)
	(* This call to the MegaTest procedures follows the	   *)
	(* type declarations required by MegaTest, but precedes    *)
	(* type declarations which utilize some of the MegaTest    *)
	(* declared types. This call must precede the type	   *)
	(* declarations below.					   *)
	(*							   *)

(* Mega Test Spare variables are declared in /usr/mega/MegaOne.Standard *)
insert 'MegaOne.Standard';

#include "constant.h"

type
  BinLimitTable = record
                    device             : SoftBin;
                    hifrqminACTable    : ACTable;
                    hifrqmaxACTable    : ACTable;
                    hifrqlooseACTable  : ACTable;
                    lofrqminACTable    : ACTable;
                    lofrqmaxACTable    : ACTable;
                    lofrqlooseACTable  : ACTable;
                    powerTest          : TestName;
                    IDDmax             : CurrentParameter;
                    DIDDmax            : CurrentParameter;
                    lopowerTest        : TestName;
                    IDDlopwrmax        : CurrentParameter;
                    DIDDlopwrmax       : CurrentParameter;
                    idle2powerTest     : TestName;
                    IDDidle2max        : CurrentParameter;
                    DIDDidle2max       : CurrentParameter;
                  end;

  TestTable	   = record
			cycletablefield 		   : CycleTable;
			actablefield			   : ACTable;
			pinlistfield			   : PinList;
			case WhatTestTable : TestName of
                          TIopensTest   :  (dctablefield   : DCTable);
			  TIshortsTest,
			  TIinleakTest,
			  TItrilkgTest	 : (dctablefield1  : DCTable;
					    dctablefield2  : DCTable)
		     end;(*record definition*)

  TestTableArray   = array [TIopensTest..TIiddqTest] of TestTable;
  DieIdArray = array [0..50] of integer;
  ABUSArray = array [0..32] of integer;
  filename	   = array [1..25] of char;  (* for search routine *)
  SoftBinArrayFlag = array[SoftBin] of boolean;
  SyncSupplyVddArray  = array[SupplyVType] of VoltageParameter;
  SyncTimeArray = array[ACTable,VoltageParameter,Origin] of PicoSeconds;
  SyncDoneArray = array[ACTable,VoltageParameter] of boolean;

#include "/u/TI_apps/stdprogram/TIglobal.h"
#include "/u/TI_apps/stdprogram/TIexterns.h"
#include "externs.h"
var

 (* Die ID Variables *)

        die_id_x,
        die_id_y,
        die_id_wafer_nb,
        die_id_lot_nb,
        die_id_fab,
        die_id_ram_repair                   : integer;
        DieId                               : DieIdArray;
        ABUS_bit                            : ABUSArray;
	FirstPatternName		    : TestName;
	LastPatternName 		    : TestName;
	FirstJTAGPatternName		    : TestName;
	LastJTAGPatternName                 : TestName;
	FirstRAMPattern 		    : TestName;
        LastRAMPattern                      : TestName;    
        FirstLoosePatName  		    : TestName;
        FirstFaultPattern                   : TestName;
        LastFaultPattern                    : TestName;
        FirstSportPattern                   : TestName;
        LastSportPattern                    : TestName;
        testx,testy      		    : TestName;
        CurrentBINTable                     : BinLimitTable;
        BIN01Table                          : BinLimitTable;
        BIN02Table                          : BinLimitTable;
        BIN03Table                          : BinLimitTable; 
        SyncVcc                             : VoltageParameter;
	supplylimitslist		    : SupplyLimitsArray;
        supplylimitslist1                   : SupplyLimitsArray;
        SliceArray                          : array[1..120,1..max_softbin] 
                                                of char;
	cycletablename			    : CycleTable;
	actablename, actable   		    : ACTable;
	dctablename			    : DCTable;
        individual_pats                     : boolean;
	TIPatternPrint			    : boolean;
	failsync			    : boolean;
	failH1H3			    : boolean;
	failtclk			    : boolean;
	failspclks			    : boolean;
	failspecsync			    : boolean;
        TISyncAllCorners                    : boolean;
	CRYSTAL 			    : boolean;
	failcrystal			    : boolean;
        failidle                            : boolean;
	characterize			    : boolean;
	fastsearch			    : boolean;
	timesearch			    : boolean;
	schmooloos			    : boolean;
	schmooabort			    : boolean;
	schmoo				    : boolean;
        handler                             : boolean;
        continue_                           : boolean;
	ramonlymap			    : boolean;
	romonlymap			    : boolean;
	ramrommap			    : boolean;
	engrpgm 			    : boolean;
        PG1dot1                             : boolean;
        PG1dot2                             : boolean;
        stressed_to_the_max                 : boolean;
        F731839A                            : boolean;
        F731839B                            : boolean;
	charsetup			    : boolean;
	datalog_on			    : boolean;
        margin_test			    : boolean;
	resetorigins			    : boolean;
        reference_slice                     : boolean;
        datalog_flag                        : boolean;
        datalog_memory                      : boolean;
        refpresent                          : boolean;
        TICornerPrint                       : boolean;  
	supplycapcheck			    : boolean;
	DIEID				    : boolean;
        VDDgb                               : MicroVolts;
        idle_current                        : NanoAmps;
        B1speed                             : PicoSeconds;
        TWCIL,TWCIH                         : PicoSeconds;
        TWCILcf,TWCIHcf                     : PicoSeconds;
        tgbclk,tgbhold,tgbother             : PicoSeconds;
        schmooperiod                        : PicoSeconds;
	CharPicoSeconds1		    : PicoSeconds;
	CharPicoSeconds2		    : PicoSeconds;
	CharPicoSeconds3		    : PicoSeconds;
	CharPicoSeconds4		    : PicoSeconds;
	looseclock			    : PicoSeconds;
	loosetclk			    : PicoSeconds;
	loosestbdly			    : PicoSeconds;
	looseoffdly			    : PicoSeconds;
	looseRW_			    : PicoSeconds;
	loosewrtbgnAdly			    : PicoSeconds;
	looseDBUSMdly			    : PicoSeconds;
        sp                                  : PicoSeconds;
	schmo				    : real;
	filenumber			    : integer;
        Set_Temp_Time			    : boolean;
        Wait_Time			    : MicroSeconds;
        char_by_pin                         : boolean;
        lvlsrch				    : boolean;
        timesrch			    : boolean;
	iddsrch 			    : boolean;
        lotnumber			    : integer;
        unitnumber			    : integer;
        datalogiarray                       : NanoAmpsArray;
	SyncSupplyVdd 			    : SyncSupplyVddArray;
	SyncTime			    : SyncTimeArray;
	SyncDone			    : SyncDoneArray;
        refnum, refcount                    : integer;
        IddqDatalogFile                     : String;
        RamDatalogFile                      : String;
        Iddq_Log_Data                       : text;
        Ram_Log_Data                        : text;
        dummystring, tempstring             : String;
        WaferNumber, Xcoord, Ycoord         : integer;
	SysClass          		    : String;

	failcount		       : integer;(*counter for crystal test*)
	tempfile		       : text;	  (* files to write binary *)
	holdfile		       : filename;(* search results to	   *)

	failcnt 		       : integer;(* stop_pattern var *)
	SerialLength		       : integer;
        difflotold                     : String;
	failpinlist		       : PinList;

        wafer,
        die_count                      : integer;

(* characterization variables *)
        pnumber,temperature            : integer;
        VDDvalue                       : VoltageParameter;
        duty, i, j, k, l, n            : integer;
        s                              : String;

        (* added for boolean segment summaries *)
        summaryfile,referencefile      : String;
        summary, reference,summary2    : text;
        SoftBinArray                   : SoftBinArrayFlag;
        dummy_softbin  		       : SoftBin;
	prbmenu			       : boolean;
	prbtext			       : boolean;
        unittext 		       : boolean;
	levelsheader		       : boolean;

	D31,D30,D29,D28,D27,D26,D25,D24: PinList;    (* Single Pin PinLists*)
	D23,D22,D21,D20,D19,D18,D17,D16: PinList;    (* Single Pin PinLists*)
	D15,D14,D13,D12,D11,D10,D9,D8  : PinList;    (* Single Pin PinLists*)
	D7, D6, D5, D4, D3, D2, D1, D0 : PinList;    (* Single Pin PinLists*)
	A23,A22,A21,A20,A19,A18,A17,A16: PinList;    (* Single Pin PinLists*)
	A15,A14,A13,A12,A11,A10,A9,A8  : PinList;    (* Single Pin PinLists*)
	A7, A6, A5, A4, A3, A2, A1, A0 : PinList;    (* Single Pin PinLists*)
	INT0_,INT1_,INT2_,INT3_,IACK_  : PinList;    (* Single Pin PinLists*)
	RW_,STRB_,RDY_,HOLD_,HOLDA_    : PinList;    (* Single Pin PinLists*)
	RESET_,MCBL,XF0,XF1,X2CLKIN    : PinList;    (* Single Pin PinLists*)
	CLKX0,CLKR0,DX0,DR0,FSX0,FSR0  : PinList;    (* Single Pin PinLists*)
	TCLK0,TCLK1,H1,H3,X1           : PinList;    (* Single Pin PinLists*)
        PAGE0_,PAGE1_,PAGE2_,PAGE3_    : PinList;    (* Single Pin PinLists*)
        EMU0,EMU1,TCK,TDO,TDI,TMS      : PinList;    (* Single Pin PinLists*)
        TRST_,CLKMODE0,CLKMODE1,SHZ_   : PinList;    (* Single Pin PinLists*)
        EXTCLK,RSV0,RSV1,EDGEMODE      : PinList;    (* Single Pin PinLists*)


	DBUS,ABUS                      : PinList;    (*Device specific	   *)
	EXTINT,EXTMEMCONTROL           : PinList;    (*pin group PinLists  *)
	CONTROL,CLKOUTS                : PinList;
	SPPINS,TPINS,ETPINS,INPUTS     : PinList;
	OUTPUTS,SCANPINS               : PinList;
{	PMUINS1 		       : PinList; }   (*Inputs with pull-ups*)
        INPU_1			       : PinList;    (*Inputs with pull-ups  *)
        INPD_1			       : PinList;    (*Inputs with pull-down *)
	PMUTRIS 		       : PinList;    (*I/O    with pull-ups  *)
	OPENPINS		       : PinList;
{        SCANHOLDPINS,SCANOFFPINS       : PinList;}
        IOPINS                         : PinList;
        ICCQDisconnectPinList          : PinList;

	FIELD1,FIELD2,FIELD3,FIELD4    : PinList;    (*Patternfield pinlist*)
	FIELD5,FIELD6,FIELD7,FIELD8    : PinList;    (*Patternfield pinlist*)
	FIELD9,FIELD10,FIELD11,FIELD12 : PinList;    (*Patternfield pinlist*)
	FIELD13,FIELD14,FIELD15        : PinList;    (*Patternfield pinlist*)
     	FIELD16,FIELD17,FIELD18        : PinList;    (*Patternfield pinlist*)
	FIELD19,FIELD20,FIELD21        : PinList;    (*Patternfield pinlist*)
	FIELD22,FIELD23 	       : PinList;    (*Patternfield pinlist*)

	SCANINFIELD,SCANOUTFIELD       : PinList;    (*Scan Patternfield list*)

	EVENPINS, ODDPINS, ALLPINS     : PinList;    (*PinLists defined by *)
	EVENINS, ODDINS, ALLINS	       : PinList;    (*test engineering for*)
	TESTINS, NOTESTINS	       : PinList;    (*use with standard   *)
	ALLOUTS, ALLIOS 	       : PinList;    (*parametric and	   *)
	EVENTRISTATE, ODDTRISTATE      : PinList;    (*functional tests    *)
	ALLTRISTATE,TRSTHIPINS	       : PinList;
	NOTRISTATEOUTS,NOTRISTATEIO    : PinList;
	MUXPINS 		       : PinList;    (* All MuxPins	   *)
	noPinList		       : PinList;    (* empty pin list	   *)

	TimeProgram                    : boolean;
	LogVmin                        : boolean;
