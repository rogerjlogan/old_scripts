(***********************************************************************)
(***                                                                 ***)
(***                       320VC33 TEST PROGRAM                      ***)
(***                       --------------------                      ***)
(***                                                                 ***)
(***                        File Name:  cycletbl.p                   ***)
(***                        Revision :  00 20021011                  ***)
(***                                                                 ***)
(***     Revision History:                                           ***)
(***     00 SC 08/04/99  Program generation.                         ***)
(***********************************************************************)
(***********************************************************************)
(***                                                                 ***)
(*** VC33PGE00  20021011  Major  Curtis Woods                        ***)
(***  - Initial revision. Program generated from the commercial pro- ***)
(***    gram 320VC33B3.                                              ***)
(***                                                                 ***)
(***********************************************************************)



	(***********************************************************)
	(***		   Cycle Table Definition		 ***)
	(***********************************************************)
	(***							 ***)
	(*** The Cycle Table binds the waveforms defined in the  ***)
	(*** AC Table to particular pins. In order to make use	 ***)
	(*** of the Mask control and Drive control fields in the ***)
	(*** patterns, the CycleSetMD statement must be used.	 ***)
	(*** This is the section in which multiple timing sets	 ***)
	(*** will be declared, if necessary. Each timing set	 ***)
	(*** must have a unique Global Cycle Type. The Global	 ***)
	(*** Cycle Type will be the first parameter of each line ***)
	(*** of patterns. Normally, a single Cycle Table with	 ***)
	(*** multiple Global Cycle Types (GCTs) will be 	 ***)
	(*** sufficient. Only two are allowed as a maximum.	 ***)
	(***							 ***)
	(*** NOTE THAT ALL GLOBAL CYCLE TYPES MUST BE DECLARED	 ***)
	(*** IN THE Cycle LIST IN Global.h.			 ***)
	(***							 ***)
	(*** Vector Maps are also declared within the Cycle	 ***)
	(*** Table. The Vector Map allows the user to create	 ***)
	(*** readable patterns by breaking them into fields	 ***)
	(*** defined by the user. The Vector Map is used to map  ***)
	(*** pattern bits to the correct pins. Normally, a single***)
	(*** Vector Map will be sufficient. In that case, use	 ***)
	(*** the VectorMapSetCycleAll statement to assign the	 ***)
	(*** Vector Map to all Global Cycle Types in the Cycle	 ***)
	(*** Table.						 ***)
	(***							 ***)
	(*** NOTE THAT THE NAME OF THE VECTOR MAP MUST BE	 ***)
	(*** DECLARED IN THE VectorMap LIST IN Global.h 	 ***)
	(***							 ***)
	(***********************************************************)

procedure CycleTableSet; (*cycletable : CycleTable*)

var
  sccsidgctmain, sccsidgctserpt, sccsidgctscan : String;
	(***********************************************************)
	(***							 ***)
	(*** The Internal procedure TICycleTableSet added to	 ***)
	(*** set up multiple cycle tables.			 ***)
	(***							 ***)
	(***********************************************************)

procedure TICycleTableSet( cycletable : CycleTable );

begin
  CycleTableOpen( cycletable );

  case cycletable of
    TIspecCycleTable: 
      begin
    CycleTableSpeedSet  (FastSpeed);
    CycleTableMDModeSet (ExtMDMode);
#include "gctmain.h" (* include must be at beginning of line *)
      end; 

    TIsportCycleTable: 
      begin
    CycleTableSpeedSet  (FastSpeed);
    CycleTableMDModeSet (ExtMDMode);
#include "gctserpt.h" (* include must be at beginning of line *)
      end; 
  end; (* case *)

    (*									    *)
    (*	    Definition of Vector Map of Pattern Fields to Pin Lists	    *)
    (*									    *)
    (*		    Name of	    Pattern	  PinList	     Data   *)
    (*		   VectorMap	      Field			     Type   *)
    (*									    *)

      VectorMapSet (TIallVectorMap,	  1,	      FIELD1,	     Hex    );
      VectorMapSet (TIallVectorMap,	  2,	      FIELD2,	     Hex    );
      VectorMapSet (TIallVectorMap,	  3,	      FIELD3,	     Binary );
      VectorMapSet (TIallVectorMap,	  4,	      FIELD4,	     Binary );
      VectorMapSet (TIallVectorMap,	  5,	      FIELD5,	     Binary );
      VectorMapSet (TIallVectorMap,	  6,	      FIELD6,	     Binary );
      VectorMapSet (TIallVectorMap,	  7,	      FIELD7,	     Binary );
      VectorMapSet (TIallVectorMap,	  8,	      FIELD8,	     Binary );
      VectorMapSet (TIallVectorMap,	  9,	      FIELD9,	     Hex    );
      VectorMapSet (TIallVectorMap,	 10,	      FIELD10,	     Binary );
      VectorMapSet (TIallVectorMap,      11,          FIELD11,       Binary ); 
      VectorMapSet (TIallVectorMap,      12,          FIELD12,       Binary ); 
      VectorMapSet (TIallVectorMap,      13,          FIELD13,       Binary ); 
      VectorMapSet (TIallVectorMap,      14,          FIELD14,       Binary );
      VectorMapSetCycleAll(TIallVectorMap);

{  case cycletable of 
  TIspecCycleTable:
   begin  
      VectorMapSetCycle (TIallVectorMap,DRDCycle);
      VectorMapSetCycle (TIallVectorMap,SDRDCycle);
      VectorMapSetCycle (TIallVectorMap,SyncDRDCycle);
      VectorMapSetCycle (TIallVectorMap,ALLOFFcycle);
      VectorMapSetCycle (TIallVectorMap,DW2Cycle);
      VectorMapSetCycle (TIallVectorMap,DW2ACycle);
      VectorMapSetCycle (TIallVectorMap,DW1Cycle);
      VectorMapSetCycle (TIallVectorMap,DWRCycle);
      VectorMapSetCycle (TIallVectorMap,DWRXFCycle);
      VectorMapSetCycle (TIallVectorMap,DWWCycle);
      VectorMapSetCycle (TIallVectorMap,DRDthCycle);
      VectorMapSetCycle (TIallVectorMap,DW2thCycle);
      VectorMapSetCycle (TIallVectorMap,DW1thCycle);
      VectorMapSetCycle (TIallVectorMap,DWRthCycle);
      VectorMapSetCycle (TIallVectorMap,DWWthCycle);
      VectorMapSetCycle (TIallVectorMap,DRDH7Cycle);
      VectorMapSetCycle (TIallVectorMap,DRDH9Cycle);
      VectorMapSetCycle (TIallVectorMap,DRDSIGICycle);
      VectorMapSetCycle (TIallVectorMap,DW1SIGICycle);
      VectorMapSetCycle (TIallVectorMap,DW2SIGICycle);
      VectorMapSetCycle (TIallVectorMap,DWRSIGICycle);
      VectorMapSetCycle (TIallVectorMap,DRDLDIICycle);
      VectorMapSetCycle (TIallVectorMap,DRDSTIICycle);
      VectorMapSetCycle (TIallVectorMap,HOLDTRCycle);
      VectorMapSetCycle (TIallVectorMap,MCSCycle);
      VectorMapSetCycle (TIallVectorMap,XF1OICycle);
      VectorMapSetCycle (TIallVectorMap,XF0OICycle);
      VectorMapSetCycle (TIallVectorMap,XFIOCycle);
      VectorMapSetCycle (TIallVectorMap,DRDCICycle);
      VectorMapSetCycle (TIallVectorMap,TIMGPIOCycle);
      VectorMapSetCycle (TIallVectorMap,DRDaCycle);
      VectorMapSetCycle (TIallVectorMap,DRDbCycle);
      VectorMapSetCycle (TIallVectorMap,DRDESCKCycle);
      VectorMapSetCycle (TIallVectorMap,DW1ESCKCycle);
      VectorMapSetCycle (TIallVectorMap,DW2ESCKCycle);
      VectorMapSetCycle (TIallVectorMap,DWRESCKCycle);
      VectorMapSetCycle (TIallVectorMap,DRDStopCycle);
      VectorMapSetCycle (TIallVectorMap,IDDQCycle);
      VectorMapSetCycle (TIallVectorMap,NullCY);
   end; (* case 1 TIspecCycleTable *)

   TIsportCycleTable:
   begin
      VectorMapSetCycle (TIallVectorMap,DRDSP1Cycle);
      VectorMapSetCycle (TIallVectorMap,ALLOFFcycle);
      VectorMapSetCycle (TIallVectorMap,DW1SP1Cycle);
      VectorMapSetCycle (TIallVectorMap,DW2SP1Cycle);
      VectorMapSetCycle (TIallVectorMap,DRDSP1ACycle);
      VectorMapSetCycle (TIallVectorMap,DRDSP1AaCycle);
      VectorMapSetCycle (TIallVectorMap,DWRSP1Cycle);
      VectorMapSetCycle (TIallVectorMap,DWWSP1Cycle);
      VectorMapSetCycle (TIallVectorMap,DWWSP1ACycle);
      VectorMapSetCycle (TIallVectorMap,DWWSP1AaCycle);
      VectorMapSetCycle (TIallVectorMap,DRDSP2Cycle);
      VectorMapSetCycle (TIallVectorMap,DW1SP2Cycle);
      VectorMapSetCycle (TIallVectorMap,DW2SP2Cycle);
      VectorMapSetCycle (TIallVectorMap,DWRSP2Cycle);
      VectorMapSetCycle (TIallVectorMap,DWWSP2Cycle);
      VectorMapSetCycle (TIallVectorMap,DRDSP4Cycle);
      VectorMapSetCycle (TIallVectorMap,DW1SP4Cycle);
      VectorMapSetCycle (TIallVectorMap,DW2SP4Cycle);
      VectorMapSetCycle (TIallVectorMap,TDDXZCycle);
      VectorMapSetCycle (TIallVectorMap,DWRSP4Cycle);
      VectorMapSetCycle (TIallVectorMap,DWWSP4Cycle);
      VectorMapSetCycle (TIallVectorMap,DRDSP5Cycle);
      VectorMapSetCycle (TIallVectorMap,DW1SP5Cycle);
      VectorMapSetCycle (TIallVectorMap,DW2SP5Cycle);
      VectorMapSetCycle (TIallVectorMap,DWRSP5Cycle);
      VectorMapSetCycle (TIallVectorMap,DWWSP5Cycle);
      VectorMapSetCycle (TIallVectorMap,DRDCycle);
      VectorMapSetCycle (TIallVectorMap,DW1Cycle);
      VectorMapSetCycle (TIallVectorMap,DW2Cycle);
      VectorMapSetCycle (TIallVectorMap,DW2ACycle);
      VectorMapSetCycle (TIallVectorMap,DWRCycle);
      VectorMapSetCycle (TIallVectorMap,DWWCycle);
      VectorMapSetCycle (TIallVectorMap,NullCY);
   end; (* case 2 TIsportCycleTable *)

  end; (* case *) }
 CycleTableClose;

 end; (* TICycleTableSet *)

begin (* CycleTableSet *)

 if (cycletable in [TIallCycleTable, TIspecCycleTable]) then
   TICycleTableSet( TIspecCycleTable );
 if (cycletable in [TIallCycleTable, TIsportCycleTable]) then
   TICycleTableSet( TIsportCycleTable );

end;(* CycleTableSet *)
