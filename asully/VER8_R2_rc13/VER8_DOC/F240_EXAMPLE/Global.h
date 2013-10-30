(***********************************************************************)
(***								     ***)
(***                     320X240 TEST PROGRAM 	                     ***)
(***			 --------------------   		     ***)
(***								     ***)
(***	 		File Name:  Global.h			     ***)
(***								     ***)
(***   								     ***)
(***   Revision History:					     ***)
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


type
        (*                                                                *)
        (*              Declaration of ordinal values                     *)
        (*                                                                *)

        (*                                                                *)
        (*           Declaration of Voltage Supply Names                  *)
        (* Supply Names are first referenced in the DeviceTableSet        *)
        (* procedure.                                                     *)
        (*                                                                *)

        (*                                                                *)
        (*           Declaration of Supply Names                          *)
        (* All Supply Names will be assigned minimum and maximum          *)
        (* allowable values in the DeviceTableSet procedure.              *)
        (*                                                                *)
        (*                  Naming Convention                             *)
        (*  Use power supply names from data book or specification        *)
        (*                                                                *)

  SupplyName         = (CVdd, DVdd, Vcca, Vccp,
                        CVss, DVss, Vssa, VREFLO, TPAD);
        (*                                                                *)
        (*           Declaration of Voltage Parameters                    *)
        (* All Voltage Parameters should be assigned values in  the*)
        (* DCDataSheetSet procedure.                                      *)
        (*                                                                *)
        (*                  Naming Convention                             *)
        (* 1. Power supplies. Use supply name with addition of            *)
        (*    min, max, and nom.                                          *)
        (* 2. I/O levels. Use type of level (ie. vil, voh, etc.)          *)
        (*    followed by test requirement in caps (ie. TTL,              *)
        (*    1090MOS, etc.).                                             *)
        (* 3. PTU force voltages. Use v, followed by test type            *)
        (*    (ie. opens, shortslo, etc.)                                 *)
        (*                                                                *)

  VoltageParameter =    (
                        Vddmin,
                        Vddmax,
                        Vddnom,
                        VddnomLV,
                        VddminLV,
                        VddmaxLV,
                        VddnomHV,
                        VddminHV,
                        VddmaxHV,
                        Vddparam,
                        VddMin,
                        VddMax,
                        VddpMax,
                        CVddIddq1,
                        DVddIddq1,
                        AVddIddq1,
                        PVddIddq1,
                        CVddIddq2,
                        DVddIddq2,
                        AVddIddq2,
                        PVddIddq2,
                        VddStress,
                        Vddretention,

                        vilTTL,
                        vilLV,
                        vilX2,
                        vilX2LV,
                        vilSCLK,
                        vilSCLKLV,
                        villoos,
                        vilpower,
                        vilpowerX2,

                        vihTTL,
                        vihLV,
                        vihX2,
                        vihX2LV,
                        vihSCLK,
                        vihSCLKLV,
                        vihloos,
                        vihloosX2,
                        vihpower,
                        vihpowerX2,
                        vihmax,
                        vihparm,
                        vihiddq,
                        
                        volTTL,
                        volLV,
                        vol1090TTL,
                        vol1090LV,
                        volrelax,
                        volrelaxLV,
                        volloos,
                        volpower,

                        vohTTL,
                        vohLV,
                        voh1090TTL,
                        voh1090LV,
                        vohloos,
                        vohpower,
                        
                        vloadTTL,
                        vloadLV,
                        vloadmatch,
                        vloadmatch2,
                        vloadmatchLV,
                        vloadmatch2LV,
                        vloadloos,
                        vloadpower,
                        vloadpullup,
                        vloadPMT,
                        vohPMTloose,
                        volPMTloose,
                        vihloose,
                        villoose,
                        vitlTTL,
                        vithTTL,
                        vopens,
                        vshortslo,
                        vshortshi,
                        vinleaklo,
                        vinleakhi,
                        vINDOWNSleaklo,
                        vINUPSleakhi,
                        vtrilkglo,
                        vtrilkghi,

                        vitlX2LV,
                        vithX2LV,
                        vitlLV,
                        vithLV,
                        vitlX2,
                        vithX2,
                        vitl,
                        vith
                        );

        (*                                                                *)
        (*           Declaration of Current Parameters                    *)
        (* All Current Parameters should be assigned values in  the*)
        (* DCDataSheetSet procedure.                                      *)
        (*                                                                *)
        (*                  Naming Convention                             *)
        (* 1. Power supplies. Use supply current name followed by         *)
        (*    min, max, or nom.                                           *)
        (* 2. I/O levels. Use type of level (ie. iol, ioh, etc.)          *)
        (*    followed by test requirement in caps (ie. TTL, MOS,         *)
        (*    CLK, etc).                                                  *)
        (*                                                                *)

  CurrentParameter =    ( 
                        CIddmin,
                        DIddmin,
                        AIddmin,
                        PIddmin,
                        CIddclamp,
                        DIddclamp,
                        AIddclamp,
                        PIddclamp,
                        CIddmax,
                        DIddmax,
                        AIddmax,
                        PIddmax,
                        CIddtyp,
                        DIddtyp,
                        AIddtyp,
                        PIddtyp,

                        IddIdlemax,
                        IddIdle2max,
                        IddIdle2Pllmax,

                        CIddqFailLeak2,
                        DIddqFailLeak2,
                        AIddqFailLeak2,
                        PIddqFailLeak2,
                        CIddqFailLeak1,
                        DIddqFailLeak1,
                        AIddqFailLeak1,
                        PIddqFailLeak1,
                        IddqLeaky,
                        IddqVeryLeaky,
                        IddqLimit1,
                        IddqLimit2,
                        IddqDelta,

                        iolTTL,
                        iolLV,
                        iolmatch,
                        iolmatchLV,
                        iolloos,
                        iolpower,
                        iolpullup,
                        iolstress,
                        ivccpmax,

                        iohTTL,
                        iohLV,
                        iohmatch,
                        iohmatch2,
                        iohmatchLV,
                        iohmatch2LV,
                        iohloos,
                        iohpower,
                        iohpullup,
                        iohstress,

                        iolloose,
                        iohloose,

                        iopens,
                        ishortslo,
                        ishortshi,
                        iinleaklo,
                        iinleakhi,
                        ipturangeINS,
                        iREFHIleaklo,
                        iREFHIleakhi,
                        ipturangeREF,
                        iINUPSleaklo,
                        iINUPSleakhi,
                        ipturangeINUPS,
                        iINDOWNSleaklo,
                        iINDOWNSleakhi,
                        ipturangeINDOWNS,
                        itrilkglo,
                        itrilkghi,
                        ipturangeIOS,
                        iADClkglo,
                        iADClkghi,
                        ipturangeADC,
                        iIOUPSlkglo,
                        iIOUPSlkghi,
                        ipturangeIOUPS
                        );

        (*                                                                *)
        (*           Declaration of DC Table names                        *)
        (* All DC Table names are first referenced in the                 *)
        (* DCDataSheetSet and DCTableSet procedure. Both the              *)
        (* DCDataSheets and DCTables are tables of type DCTable           *)
        (*                                                                *)
        (*                  Naming Convention                             *)
        (* Start with TI, followed by a descriptor describing what        *)
        (* type of table it is (ie. data, opens, inleak1), followed       *)
        (* by DCTable.                                                    *)
        (*                                                                *)

  DCTable        = ( TIdataDCTable,                        (*DCDataSheet *)
                     TIopensDCTable,                       (*DCTable     *)
                     TIshorts1DCTable, TIshorts2DCTable,   (*DCTable     *)
                     TIinleak1DCTable, TIinleak2DCTable,   (*DCTable     *)

               TIPTUIOddHi1DCTable, TIPTUIOddLo1DCTable,   (*DCTable     *)
               TIPTUIOddHi2DCTable, TIPTUIOddLo2DCTable,   (*DCTable     *)
               TIPTUIOddHi3DCTable, TIPTUIOddLo3DCTable,   (*DCTable     *)
                     TIlatchupDCTable,                     (*DCTable     *)

                     TItrilkg1DCTable, TItrilkg2DCTable,   (*DCtable     *)

                     TIpowerDCTable,                       (*DCTable     *)
                     TIidleDCTable,                        (*DCTable     *)

                     TIlooseDCTable,                       (*DCTable     *)

                     TIlevelsHVDCTable,                    (*DCTable     *)
                     TIlevelsLVDCTable,                    (*DCTable     *)

                     TItimingsHVDCTable,                   (*DCTable     *)
                     TItimingsLVDCTable,                   (*DCTable     *)

                     TIPMTminDCTable,
                     TIPMTDCTable,
                     TIPMTmaxDCTable,

                     TIallDCTable);                        (*DCTable     *)


        (*                                                                *)
        (*           Declaration of Time Parameters                       *)
        (* All Time Parameters should be assigned values in the           *)
        (* ACDataSheetSet procedure.                                      *)
        (*                                                                *)
        (*                  Naming Convention                             *)
        (* Start with t, followed by data book description of             *)
        (* the parameter (ie. wCL, rC, etc.).                             *)
        (*                                                                *)


  TimeParameter  = ( 
                        tref,tper,tH,tQ,tjitter,tloosjitter,
		        tdABUSRD,thzABUSRD,tdABUSWR,thzABUSWR,
		        tdACTRLLRD,thzACTRLLRD,tdACTRLHRD,thzACTRLHRD,
		        tdACTRLLWR,thzACTRLLWR,tdACTRLHWR,thzACTRLHWR,
		        tsuBION,thdBION,
		        tdBRNLRD,thzBRNLRD,tdBRNHRD,thzBRNHRD,
		        tdBRNLWR,thzBRNLWR,tdBRNHWR,thzBRNHWR,
		        tsuCAP,thdCAP,
		        tsuDBUSRD,thdDBUSRD,tdDBUSWR,thzDBUSWR,
		        tsuGPIOF,thdGPIOF,tdGPIOF,thzGPIOF,
		        tsuGPIOS,thdGPIOS,tdGPIOS,thzGPIOS,
		        tsuINTN,thdINTN,
		        tsuMPMCN,thdMPMCN,
		        tsuNMIN,thdNMIN,
		        tsuPDPINT,thdPDPINT,
		        tdPWM,thzPWM,
		        tdRDNL,thzRDNL,tdRDNH,thzRDNH,
		        tsuREADY,thdREADY,
		        tdRNWL,thzRNWL,tdRNWH,thzRNWH,
		        tsuRSN,thdRSN,tdRSN,thzRSN,
		        tsuSCIRXD,thdSCIRXD,tdSCITXD,thzSCITXD,
		        tsuSPICLK,thdSPICLK,tdSPICLK,thzSPICLK,
		        tsuSPISIMO,thdSPISIMO,tdSPISIMO,thzSPISIMO,
		        tsuSPISOMI,thdSPISOMI,tdSPISOMI,thzSPISOMI,
		        tsuSPISTE,thdSPISTE,
		        tdSTRBNL,thzSTRBNL,tdSTRBNH,thzSTRBNH,
		        tsuTMRCLK,thdTMRCLK,
		        tsuTMRDIR,thdTMRDIR,
		        tdWENL,thzWENL,tdWENH,thzWENH,
		        tdXF,thzXF,
		        twCIL,tdCIHCmin,tdCIHCmax,twCOLmin,
                        twCOLmax,twCOHmin,twCOHmax,
                        tdCIHCpllmin,tdCIHCpllmax,twCOpllmin,twCOpllmax,
                        tsuARD,thARD,
                        tdCOAmax,thACOr,tdCORDmin,tdCORDmax,
                        tdCOSmax,twRDLmin,twRDLmax,twRDHmin,
                        twRDHmax,tdRDW,taA,tsuDRD,thDRD,tsuDCOr,thDCOr,
                        taRD,tsuAW,thAW,tsuACO,thACOw,twWLmin,
                        twWLmax,twWHmin,twWHmax,tdCOWmin,tdCOWmax,
                        tdWRD,tsuDWmin,thDWmin,tsuDCOwmin,thDCOwmin,
                        tenDW,tsuRCO,thCOR,tsuRRD,thRRD,tvRW,thRW,
                        tvRAr,tvRAw,tdXFmin,tdXFmax,tdTOUTmin,
                        tdTOUTmax,twTOUT,tsuRSCI,tsuRSCO,tsuINCO,
                        thINCO,tdIACKCOmin,tdIACKCOmax,thDA,
                        tdDX,thDX,tdFSX,tdFSi,tsuDR,tsuFS,thFS,
                        tdPmtTDBUS,tsPmtTDBUS,tsNonFlash,
                        tnwef,tnwel,tnwer,tnweh
                   );

  ACTable        = (

                        TIlofrqACTable,
                        TIlofrqpllACTable,
                        TIhifrqACTable,         
                        TIveryhifrqACTable,         
                        TIsearchACTable,

                        TIlofrqlooseACTable,
                        TIhifrqlooseACTable,         
                        TIveryhifrqlooseACTable,         
                        TIsearchlooseACTable,

                        TIsearchlooseACTable2, (* for char *)
                    
                        TIscanACTable,
                    {   TIserialscanACTable,}
                        
                        TIPMT100ACTable,

                        TIallACTable

                   );         

        (*                                                                *)
        (*           Declaration of Test Names                            *)
        (* The TestNames are names assigned to certain test setup         *)
        (* in your program. Every pass/fail test (MegaPascal Test         *)
        (* statement) requires a TestName to be defined in the            *)
        (* TestSets procedure.                                            *)
        (*                                                                *)
        (*                  Naming Convention                             *)
        (* Start with TI, followed by a descriptor describing what        *)
        (* test the TestName invokes, followed by the word Test           *)
        (*                                                                *)


TestName      =(TIopensTest,
                TIshortsTest,
                TIPTUIOddLo1Test,
                TIPTUIOddHi1Test,
                TIPTUIOddHi2Test,
                TIPTUIOddLo2Test,
                TIPTUIOddHi3Test,
                TIPTUIOddLo3Test,
                TIinleakTest,
                TIpowerTest,
                TIFlashpowerTest,
                TIlatchupTest,
                TIqpowerTest,
                TIiddqTest,
                TItrilkgTest,

                NCopensTest,

                IOUPSpmutrilkgloTest,
                IOUPSpmutrilkghiTest,
                INUPSpmuinleakhiTest,
                INUPSpmuinleakloTest,
                INDOWNSpmuinleakloTest,
                INDOWNSpmuinleakhiTest,

        (*individual patterns always needed for sync, etc. *)

                PowerTypTest,
                powertyp,
                PowerMaxTest,
                powermax,
                PowerLifeTest,
                latchuppat,

                sync,
                basic,
{               SGclk_out,    } (* obsolete, needed for PG1.x material *)
                IddqPattern,
                IddQPattern,
                alloff,
                TriStatePattern,
                lifef240,

        (* CHAR TESTS (normal [std] functional mode) *)

        (* ADC TESTS (3) *)
{               AC2char,      } (* obsolete, convert Vcca & Vssa on ADCIN2 & ADCIN10
                                 with RPT #10 around writes for debug of ADCTest *)
                AC2char1_scan,  (* convert Vcca & Vssa on ADCIN2 & ADCIN10 *)
                AC2char8_scan,  (* convert Vcca & Vssa on ADCIN0 & ADCIN8 *)
                AC2extsoc,      (* checks PG2.0 ECN edge trigger vs level trigger *)
                AC2noise_bsl,   (* convert Vcca & Vssa on ADCIN0-ADCIN15 *)

        (* search_a2d pats *)
                ramptest1,      (* converts all values on ADCIN2 (edited version of AC2char1) *)
                ramptest2,      (* convert all values on ADCIN10 (edited version of AC2char1) *)
                ramptest3,      (* convert all values on ADCIN0 (edited version of AC2char8)  *)
                ramptest4,      (* convert all values on ADCIN8 (edited version of AC2char8)  *)
                ramptest_clean, (* converts all values on ADCIN2/10 in parallel (edited AC2char1) *)
                ramptest_dirty, (* converts all values on ADCIN0/8 in parallel (edited AC2char8) *)

(* the pats between BIOtest_bsl and FRreset_bsl inclusive are tested by chfails and charflow *)

        (* search_cpu pats *)
                BIOtest_bsl,
                lifef240_bsl,

        (* search_ev pats *)
                cap_bsl,           (* partial EVcapture2 *)
                pwm_bsl,           (* partial EVTest04 *)
                T1pwm_bsl,         (* partial EVTimer1_1 *)
                T2pwm_bsl,         (* partial EVTimer2_5 *)
                T3pwm_bsl,         (* partial EVTimer3_2a_r *)
                EVTim1_scan,

        (* search_exmif pats *)
                EXMIFchar0_scan,
                EXMIFchar1_scan,
                EXMIFchar5_scan,
                BRNchar0_bsl,
{               lifef240_bsl,   }  (* already listed above w/ cpu char pats *)

        (* search_gpio pats *)
        (* GPIO signals are prism clock based [opposite edge of clkout] *)

        (* the order of these patterns is critical for search_gpio *)
                PORTxchar_bsl,     (* slow & fast GPIO searches *)
                SMgpio_bsl,        (* slow & fast GPIO searches *)
                AMgpio_bsl,        (* slow GPIO searches *)
                XINT2io_bsl,       (* slow GPIO searches *)
                XINT3io_bsl,       (* slow GPIO searches *)

        (* search_power pats *)

           (* already listed above with std-func char pats *)
{               AC2noise,     }  (* convert Vcca & Vssa on ADCIN0-ADCIN15 *)
                pwr_cvdd,

        (* search_sci pats *)
                SCIchar_bsl,

        (* search_spi pats *)
                SPImcfewd_bsl,
                SPImcfewod_bsl,
                SPImcrewd_bsl,
                SPImcrewod_bsl,
                SPIscfewd_bsl,
                SPIscfewod_bsl,
                SPIscrewd_bsl,
                SPIscrewod_bsl,

        (* search_sys pats *)

{               pwm_bsl,       }  (* already listed above with search_ev pats *)
                iddqs0_bsl,

        (* the order of these 3 patterns is critical for search_sys *)
                XINT1_bsl,
                XINT2_bsl,
                XINT3_bsl,

                FRreset_bsl,
                SDswrst_bsl,

        (* CHAR TESTS [special, can't just TestFunc() these] *)

        (* PLL TESTS (9) pll_fb# + Hand generated char vectors *)

                pll_mult1,
                pll_mult2,
                pll_mult3,
                pll_mult4,
                pll_mult5,
                pll_mult9,
                pll_mult15,
                pll_mult25,
                pll_mult45,

                pll_test,   (* dummy test case for PLL schmoos *)
                
        (* CORE TESTS (57) *)
 
                alu1_lp,
                alu1a_lp,
                alu1b_lp,
                alu2_lp,
                alu2a_lp,
                alu3_lp,
                alu4_lp,
                alu6_lp,
                ar1_lp,
                ar1a_lp,
                ar2_lp,
                ar2a_lp,
                ar2b_lp,
                ar3_lp,
                ar4_lp,
                ar5_lp,
                block_lp,
                br_lp,
                branch2_lp,
                condb_lp,
                fast_alu_lp,
                fast_alu_lpa,
                fast_alu_lpb,
                fast_alu_lpc,
                fast_arau_lp,
                fast_mult_lp,
                intr_lp,
                ints_lp,
                mult1_lp,
                mult1a_lp,
                mult2_lp,
                mult3_lp,
                mult3a_lp,
                mult4_lp,
                newinst_lp,
                pcpf_lp,
                pipe_ar_lp,
                pipe_norm_lp,
                pipe_st0_lp,
                pipe_st1_lp,
                push_lp,
                ralu1_lp,
                ralu2_lp,
                ramb1b2_lp,
                ramb1b2a_lp,
                reset_lp,
                rpt1_lp,
                rpt1a_lp,
                rpt2_lp,
                rpt2a_lp,
                rpt3_lp,
                sfr_lp,
                st_lp,
                statp_lp,
                statpa_lp,
                tblrw_lp,
                tblrwa_lp,

        (* ADDITIONAL CORE TESTS REQUIRED FOR LPB FUNCTIONALITY(10) *)

		logint1_lp,
		logint2_lp,
		logint3_lp,
		ready_lp,
		rb0256_0cb_lp,
		rb0256_0da_lp,
		rb0256_1cb_lp,
		rb0256_1da_lp,
		rb0256_da0_lp,
		rb0256_da1_lp,

        (* SUB SET of Event Manager Tests (29 of 29) *)
                (* SUB SET to RUN *)
                
                EVCapture1,
                EVCapture1a,
                EVcapture12,
                EVcapture6Tg,
                EVQep1,
                EVQep2,
                EVSpace1, 
                EVTest04,
                EVTest05,
                EVTest06,
                EVTest07,
                EVTest110,
                EVTest30,
                EVTest61,
                EVTest70,
                EVTest71,
                EVTest87, 
                EVTest94,
                EVTest_IFRA, 
                EVTimer1_1,
                EVTimer1_3c_r,
                EVTimer2_5,
                EVTimer3_2a_r, 
                EVTimers_3a,
                EVtest_updb,
                EVtest_updndb,
                INTER_1,
                SVM_bound2,
                SVM_bound5,

    (* Additional Event Manager Tests (beyond sub-set) (1/2 of 239) *)
                             (* partial EVcapture2 run w/ char pats *)
                EVQep3,
                EVQep3_r,
                EVQep4,
                EVQep4_r,
                EVSComp3,
                EVSpace2,
                EVTest04a,
                EVTest04b,
                EVTest04c,
                EVTest04d,
                EVTest04e,
                EVTest04f,
                EVTest04g,
                EVTest05_3,
                EVTest05_a,
                EVTest05_b,
                EVTest05_c,
                EVTest05_d,
                EVTest05_e,
                EVTest08_t1,
                EVTest09,
                EVTest109,
                EVTest11,
                EVTest111,
                EVTest112,
                EVTest113,
                EVTest114,
                EVTest115,
                EVTest116,
                EVTest117,
                EVTest118,
                EVTest119,
                EVTest12,
                EVTest120,
                EVTest121,
                EVTest122,
                EVTest123,
                EVTest124,
                EVTest125,
                EVTest12a,
                EVTest12b,
                EVTest13,
                EVTest15,
                EVTest16,
                EVTest19,
                EVTest20,
                EVTest21,
                EVTest22,
                EVTest23,
                EVTest25,
                EVTest26,
                EVTest27,
                EVTest28,
                EVTest29,
                EVTest31,
                EVTest32,
                EVTest33,
                EVTest34,
                EVTest35,
                EVTest36,
                EVTest37,
                EVTest38,
                EVTest39,
                EVTest42,
                EVTest62,
                EVTest63,
                EVTest64,
                EVTest65,
                EVTest66,
                EVTest67_a,
                EVTest68,
                EVTest69,
                EVTest73,
                EVTest74,
                EVTest75,
                EVTest76,
                EVTest79,
                EVTest80,
                EVTest81,
                EVTest83,
                EVTest85,
                EVTest86,
                EVTest88,
                EVTest92,
                EVTest94a,
                EVTest94b,
                EVTest94c,
                EVTest94r,
                EVTest94s,
                EVTest94t,
                EVTest_cmpr,
                EVTi_sus_ud,
                EVTimer123b,
                EVTimer123c,
                EVTimer123c_r,
                EVTimer123e,
                EVTimer123e_r,
                EVTimer123f,
                EVTimer123f_r,
                EVTimer1_1a,
                EVTimer1_1a_r,
                EVTimer1_1b,
                EVTimer1_1b_r,
                EVTimer1_1d,
                EVTimer1_2a,
                EVTimer1_2a_r,
                EVTimer1_2d,
                EVTimer1_3a,
                EVTimer1_3b,
                EVTimer1_3c,
                EVTimer1_3d,
                EVTimer1_4,
                EVTimer1_4a,
                EVTimer1_4a_r,
                EVTimer1_4b,
                EVTimer1_4c,
                EVTimer1_4d,
                EVTimer1_4e,
                EVTimer1_5b,
                EVTimer23_2,
                EVTimer23_3_r,
                EVTimer23_4,
                EVTimer23_4_r,
                EVTimer23_5,
                EVTimer23_5_r,
                EVTimer2_1a,
                EVTimer2_1a_r,
                EVTimer2_1b,
                EVTimer2_1c,
                EVTimer2_2,
                EVTimer2_2a,
                EVTimer2_2a_r,
                EVTimer2_2b,
                EVTimer2_2b_r,
                EVTimer2_2c,
                EVTimer2_2d,
                EVTimer2_3a,
                EVTimer2_3a_r,
                EVTimer2_3b,
                EVTimer2_3b_r,
                EVTimer2_3c,
                EVTimer2_3d,
                EVTimer2_4a,
                EVTimer2_4a_r,
                EVTimer2_4b,
                EVTimer2_4d,
                EVTimer2_4e,
                EVTimer2_5a_r,
                EVTimer2_5b,
                EVTimer3_1a,
                EVTimer3_1a_r,
                EVTimer3_1b,
                EVTimer3_1c,
                EVTimer3_2a,
                EVTimer3_2d,
                EVTimer3_3a,
                EVTimer3_3a_r,
                EVTimer3_3b,
                EVTimer3_3c,
                EVTimer3_3d,
                EVTimer3_3d_r,
                EVTimer3_4a,
                EVTimer3_4a_r,
                EVTimer3_4b,
                EVTimer3_4b_r,
                EVTimer3_4c,
                EVTimer3_4d,
                EVTimer3_4e,
                EVTimer3_5a_r,
                EVTimer3_5b,
                EVTimer_sus,
                EVTimers_1a,
                EVTimers_2a,
                EVTimers_3b,
                EVTimers_4a,
                EVTimers_5a,
                EVcapture10,
                EVcapture2,
                EVcapture3,
                EVcapture4,
                EVcapture4b,
                EVcapture5,
                EVcapture6,
                EVcapture7,
                EVcapture8,
                EVcapture9,
                EVtest01,
                EVtest02a,
                EVtest02b,
                EVtest02c,
                EVtest03,
                EVtest100,
                EVtest101,
                EVtest102,
                EVtest103,
                EVtest104,
                EVtest105,
                EVtest106,
                EVtest107,
                EVtest108,
                EVtest126,
                EVtest127,
                EVtest128,
                EVtest17a,
                EVtest17b,
                EVtest17c,
                EVtest17d,
                EVtest40,
                EVtest41,
                EVtest43,
                EVtest46,
                EVtest49,
                EVtest52,
                EVtest55,
                EVtest58,
                EVtest75,
                EVtest77,
                EVtest78,
                EVtest82,
                EVtest84,
                EVtest89,
                EVtest90,
                EVtest91,
                EVtest93,
                EVtest95,
                EVtest96,
                EVtest97,
                EVtest98,
                EVtest99,
                GPTimer1_22,
                GPTimer1_36,
                GPTimer2_1,
                GPTimer2_2,
                GPTimer2_2b,
                GPTimer2_2c,
                GPTimer2_2d,
                GPTimer2_reset,
                SVM_boun1,
                SVM_bound10,

(* EV tests failing in simulation (25) *)

                EVTest04f_isr,
                EVTest94d,
                EVTest94e,
                EVTest94f,
                EVTest94g,
                EVTest94h,
                EVTest94i,
                EVTest94j,
                EVTest94k,
                EVTest94l,
                EVTest94m,
                EVTest94n,
                EVTest94o,
                EVTest94p,
                EVTest94q,
                EVTimer123b_r,
                EVTimer1_1c,
                EVTimer2_4c,
                INTER_2,
                INTER_3,
                SVM_bound3,
                SVM_bound4,
                SVM_bound6,
                SVM_bound7,
                SVM_bound9,

        (* INTERCONNECT TESTS (47) *)

{               AC2extsoc,	 }  (* listed w/ AC2noise since A2D conversions req. loose dctables *)
                AC2presc,
                AMdigio,
                AMregs,
                AMsusp,
                AMvecrd,
                BIOtest,
                DDapdat2_lp,
                DDapdir2_lp,
                DDbpdat2_lp,
                DDbpdir2_lp,
                DDcpdat2_lp,
                DDcpdir2_lp,
                DDpfchk2_lp,
                EVCapture2,
                EVTest08_adc,
                EVTest67,
                EVTimer1_3a_r,
                EVTimer1_5a_r,
                SDila_ds,
                SDpiomux02,
                SDpiomux12,
                SDpiomux32,
                SDregs,
                SGapdat2_lp,
                SGapdir2_lp,
                SGbpdat2_lp,
                SGbpdir2_lp,
                SGcpdat2_lp,
                SGcpdir2_lp,
                SGeint0A2_lp,
                SGeint1A2_lp,
                SGeint4C2_lp,
                SGeint4C2a_lp,
                SGeint5C2_lp,
                SGeint5C2a_lp,
                SGesr0a2_lp,
                SGscr12_lp,
                SGxint1,
                SMregs,
                SMspi,
                SMvecrd,
                WDregs,
                WDvecrd,
                ex_mif3,
                ex_mif3_aw,
                off,

        (* LOW POWER TESTS (3) *)

                SGeint0A2a_lp,
                SGlpmod2_lp,
                SDlow_power3,
                SGosclpmod2_lp,

        (* IDDQ TESTS (2) *)

                iddqm_lp,
                iddqs_lp,

        (* AI TESTS *)

                AIclkfreq,
                AIclkswitch,
                AIpllratio,
                AIpllratio2,

        (* RSN AS OUTPUT TESTS (2) *)
		SDreset_bsl,
		SDreset2_bsl,

        (* CORE FAULT GRADE TESTS (23) *)

                areup1_lpfg,
                c16bc1_lpfg,
                castop,
                intrp1_lpfg,
                macc1_lpfg,
                memadrp1_lpfg,
                mpass_base2_lp,
                mpassing2_lp,
                mpassing2a_lp,
                nopsa1_lpfg,
                pcp1_lpfg,
                reset1_lpfg,
                reset2_lpfg,
                reset3_lpfg,
                rptcp1_lpfg,
                scan_chain,
                wrdscmb1_lpfg,
                wrdscmb2_lpfg,
                wrdscmb3_lpfg,
                xicorep1_lpfg,
                xicorep2_lpfg,
                xifr_c1_lpfg,
                xifr_c2_lpfg,

        (* MODULE FUNCTIONAL FG TESTS (3) *)

		AIfg0_lp,  (* REQUIRED FOR AC2 FG *)
		XIfg0_bsl,  (* REQUIRED FOR EXMIF FG *)
		WDsuspend,  (* REQUIRED FOR WD FG *)

        (* MODULE ATPG TESTS (10) *)

		AC2control,
		AIcontrol,
		AMcontrol,
		EV1top1,
		EV1top2,
		EV1top3,
		EV1top4,
		SDc240,    (* NO TDL YET *)
		SMcontrol,
		WDtop,
		
               {SCiteves, } (* REPLACED WITH AMcontrol *)
               {SPiteves, } (* REPLACED WITH SMcontrol *)

        (* FLASH TESTS (19) *)
        (* require flash erased before running <all 1's> *)

                fl_clear0_d20,
                fl_progrhi0_d20,
                fl_progrlo0_d20,
                fl_readone0_d20,
                fl_readxor0_d20,
                fl_readxor0_d20_scld,
                fl_rsegxor0_d20,
                fl_verone0_d20,
                fl_regtest0_d20,
                fl_wrtprot0_d20,
                fl_memdec_p_d20,
                fl_readprt0_d20,
                fl_ersprot0_d20,
                fl_ersprtsp_d20,
                fl_iverase0_d20,
                fl_rdv1xor0_d20,
                fl_readall0_d20,    (* Not needed for F240. (no bootcode) *)

        (* require flash cleared before running <all 0's> *)

                fl_erase0_d20, 
                fl_eraseall_d20,
                fl_erseg0_d20,      (* Not needed for F240, since have fl_ersegall_d20 *)
                fl_ersegall_d20,
                fl_readzer0_d20,
                fl_verzero0_d20,

        (* require flash programmed checkerboard before running *)

                fl_speed0_d20,
                fl_speedrv0_d20,

        (* require flash erased before running *)

                fl_ld_boot1,
                fl_ld_boot2,
                fl_wcode0,
                flash_exe,

        (* independent of state of flash *)

                fl_readdrow_d20,
                fl_wrtdrow_d20,
		fl_we0_idd,

        (* PMT FLASH TESTS (22) *)

                PMT_m01_wzero,
                PMT_m01_wchkb,
                PMT_m01_wichkb,
                PMT_m01_wstrp,
                PMT_m01_wspeed,
                PMT_m01_wispeed,

                PMT_m0_clr_1mhz,
                PMT_m0_clr_5mhz,
                PMT_m0_clr_10mhz,

                PMT_m0_rver1,
                PMT_m0_rver0,
                PMT_m0_read1,
                PMT_m0_read0,
                PMT_m0_rstrp,
                PMT_m0_rchkb,
                PMT_m0_richkb,
                PMT_m0_erase,

                PMT_m0_erase_datarow,
                PMT_m0_pgm,
                PMT_m0_ierase,
                PMT_m0_flwrite,
                PMT_m0_datarow_wFFFE,
                PMT_m0_datarow_rFFFE,
                PMT_m0_datarow_wFFF0,
                PMT_m0_datarow_rFFF0,
                PMT_m0_datarow_r0x01,
                PMT_m0_datarow_r0x04,
                PMT_m0_datarow_r0x07,
                PMT_m0_datarow_r0x08,
                PMT_m0_datarow_r0x00,
                PMT_m0_datarow_w0x00,
                PMT_m0_readvt0,

        (* ROM TESTS - C240 (2) *)
		rom_lp,
		c240romc,

        (* LONG (concatenated) TESTS (3) *)

                core_long,
                ev_long,
                intc_long,
                char_long,
                fg_long,
		atpg_long,
		core_long1,
		core_long2,
		intc_long1,
		intc_long2,
	        debug_long,

                Debug1, Debug2, Debug3, Debug4, Debug5, Debug6, Debug7, Debug8, Debug9, Debug10

                );


        (*                                                                *)
        (*           Declaration of CycleTable names                      *)
        (* Normally, there will be only one CycleTable name. At           *)
        (* a maximum, two are allowed. The first reference of             *)
        (* the CycleTable name will be in the CycleTableSet               *)
        (* procedure.                                                     *)
        (*                                                                *)
        (*                  Naming Convention                             *)
        (* Start with TI, followed by a descriptor describing what        *)
        (* type of table it is (ie. all), followed by CycleTable.         *)
        (*                                                                *)
 
  CycleTable     = ( TIP50CycleTable,TIP100CycleTable); 

        (*                                                                *)
        (* 14-Feb-97 begin change to WSATables for ADCTest                *)
        (*                                                                *)

        (*                                                                *)
        (*           Declaration of WSATable names for ADC Tests          *)
        (*                                                                *)
        (*                  Naming Convention                             *)
        (* Start with TI, followed by a descriptor describing what        *)
        (* type of table it is (ie. all), followed by WSATable            *)
        (*                                                                *)
        (*                                                                *)


 WSATable = (     TIA2DWSATable,
                  TIA2DnomWSATable,
                  TIA2DminWSATable,
                  TIA2DmaxWSATable,
                  TIdataWSATable,  
                  TIallWSATable,   
                  TIspare1WSATable,
                  TIspare2WSATable,
                  TIspare3WSATable,
                  TIspare4WSATable,
                  NoWSATable );    

  SamplerWindow = (noSamplerWindow);

  SamplerTable  = (noSamplerTable );

        (*                                                                *)
        (* 14-Feb-97 end   change to WSATables for ADCTest                *)
        (*                                                                *)


        (*                                                                *)
        (*           Declaration of Waveform names                        *)
        (* All Waveform names should be assigned values in the            *)
        (* ACTableSet procedure.                                          *)
        (*                                                                *)
        (*                                                                *)
 
  Wave              =   ( 
                        ABUSRDstrobeWF,
                        ABUSWRstrobeWF,            
                        xABUSRDstrobeWF,
                        xABUSWRstrobeWF,            
                        ABUSdriveWF,
                        ACTRLstrobeWF,            
                        xACTRLFRDstrobeWF,            
                        xACTRLFWRstrobeWF,            
                        xACTRLLRDstrobeWF,            
                        xACTRLLWRstrobeWF,            
                        xACTRLRRDstrobeWF,            
                        xACTRLRWRstrobeWF,            
                        AllOff,
                        BIONdriveWF,
                        BIONstrobeWF,
                        BOOTNdriveWF,
                        BRNstrobeWF,
                        xBRNFRDstrobeWF,
                        xBRNFWRstrobeWF,
                        xBRNLRDstrobeWF,
                        xBRNLWRstrobeWF,
                        xBRNRRDstrobeWF,
                        xBRNRWRstrobeWF,
                        CAPdriveWF,
                        CLKINdrive2WF,
                        CLKINdriveWF,              
                        CLKINresumeWF,   
                        CLKINscan_drvWF,
                        CLKMODdriveWF,             
                        CLKMODresumeWF,  
                        CLKOUT1_scan_strbWF,
                        CLKOUT1strobe2WF,
                        CLKOUT1strobeWF,           
                        SYSCLKstrobeWF,           
                        WDCLKstrobeWF,           
                        CLKRdriveWF,
                        CLKXdriveWF,
                        CLKXstrobeWF,
                        ContinueWF,
                        Continue_drive,
                        DBUS_driveoff,  
                        DBUSdriveWF,               
                        xDBUSRDdriveWF,               
                        xDBUSWRdriveWF,               
                        DBUSstrobeWF,              
                        xDBUSWRstrobeWF,
                        DIVdriveWF,
                        DIVstrobeWF,
                        DRdriveWF,
                        DXstrobeWF,
                        EMU0resumeWF,    
                        EMU1resumeWF,    
                        EMUdriveWF,      
                        EMUstrobeWF,              
                        F240clockWF,
                        F240driveWF,
                        F240strobeWF,
                        FSRdriveWF,
                        FSXdriveWF,
                        FSXstrobeWF,
                        GPIOFdriveWF,
                        GPIOFstrobeWF,
                        GPIOSdriveWF,
                        GPIOSstrobeWF,
                        HOLDANstrobeWF,
                        INSresumeWF,     
                        INTNdriveWF,
                        INUPSresumeWF,
                        IOSdriveL,     
                        IOSresumeWF,     
                        IOdriveWF,
                        IOstrobeWF,
                        LVDdriveWF,
                        LVDdriveLWF,
                        LVDdriveHWF,
                        LVDresumeWF,
                        MPMCNdriveWF,              
                        MPMC_drive,
                        NMINdriveWF,
                        NRdrive,
                        NonFlashdriveWF,
                        NonFlashstrobeWF,
                        OFFdriveH,     
                        OFFdriveL,     
                        OUTSresumeWF,    
                        PDPINTdriveWF,
                        PLL_CAP1strobeWF,
                        PLL_CLKOUT1strobeWF,
                        PLLdriveWF,
                        PWMstrobeWF,
                        PmtEMU0driveWF,
                        PmtEMU0strobeWF,
                        PmtEMU1driveWF,
                        PmtEMU1strobeWF,
                        PmtTABUSdriveWF,
                        PmtTCEdriveWF,
                        PmtTDBUSdriveWF,
                        PmtTDBUSstrobeWF,
                        PmtTERASEdriveWF,
                        PmtTESTdriveWF,
                        PmtTEXEdriveWF,
                        PmtTFOENABdriveWF,
                        PmtTLPdriveWF,
                        PmtTMSdriveWF,
                        PmtTPMTdriveWF,
                        PmtTRESETdriveWF,
                        PmtTRST_GdriveWF,
                        PmtTRSTdriveWF,
                        PmtTSPdriveWF,
                        PmtTTCRdriveWF,
                        PmtTVER0driveWF,
                        PmtTVER1driveWF,
                        PmtTWRITEdriveWF,
                        RDNLstrobeWF,               
                        RDNHstrobeWF,               
                        xRDNFstrobeWF,               
                        xRDNFstrobe2WF,               
                        xRDNLstrobeWF,               
                        xRDNRstrobeWF,
                        READYdriveWF,
                        RNWLstrobeWF,               
                        RNWHstrobeWF,               
                        xRNWFstrobeWF,               
                        xRNWLstrobeWF,               
                        xRNWRstrobeWF,               
                        RSNdriveLWF,
                        RSNdriveHWF,
                        RSNstrobeWF,
                        RSNresumeWF,     
                        RSdriveHWF,                
                        RSdriveLWF,                
                        RSdriveWF,                 
                        SCIRXDdriveWF,             
                        SCITXDstrobeWF,             
                        SPICLKdriveWF,             
                        SPICLKstrobeWF,             
                        SPISIMOdriveWF,             
                        SPISIMOstrobeWF,             
                        SPISOMIdriveWF,             
                        SPISOMIstrobeWF,             
                        SPISTEdriveWF,             
                        STRBNLstrobeWF,
                        STRBNHstrobeWF,
                        xSTRBNFstrobeWF,
                        xSTRBNLstrobeWF,
                        xSTRBNRstrobeWF,
                        SYNCresumeWF,
                        TCK_PSA1driveWF,
                        TCK_PSA2driveWF,
                        TCKdriveWF,
                        TDIdriveWF,                
                        TDOstrobeWF,
                        TMRCLKdriveWF,               
                        TMRDIRdriveWF,
                        TMSdriveWF,              
                        TRSTdriveWF,               
                        TRSTresumeWF,    
                        WENLstrobeWF,               
                        WENHstrobeWF,               
                        xWENFstrobeWF,               
                        xWENLstrobeWF,               
                        xWENRstrobeWF,
                        XFstrobeWF,                
                        XTAL2resumeWF,      
                        XTAL2strobeWF );
                        
        (*                                                                *)
        (*           Declaration of Cycle names                           *)
        (* Declaration of Global Cycle Type names. Up to 64 are           *)
        (* allowed. Use one for each timing set required. Global          *)
        (* Cycle Types are initialized in the CycleTableSet               *)
        (* procedure.                                                     *)
        (*                                                                *)
 
  Cycle             =   ( 
                        ALLOFF__,
                        CONTINUE,
                        HACK____,
                        IDLE____,
                        OFF_____,
                        PLL_____,
                        PMT0____,
                        GCT0____,
                        GCT1____,
                        GCT2____,
                        GCT3____,
                        GCT4____,
                        GCT5____,
                        GCT6____,
                        GCT7____,
                        GCT8____,
                        GCT9____,
                        GCT10___,
                        GCT11___,
                        GCT12___,
                        GCT13___,
                        GCT14___,
                        GCT15___,
                        GCT16___,
                        GCT17___,
                        GCT18___,
                        GCT19___,
                        GCT20___,
                        GCT21___,
                        GCT22___,
                        GCT23___,
                        GCT24___,
                        GCT25___,
                        GCT26___,
			SCANGCT0
                        );

        (*                                                                *)
        (*           Declaration of Vector Map names                      *)
        (* Normally, there will be only one Vector Map name. The          *)
        (* Vector Map tells the tester how your patterns are              *)
        (* formatted. Each VectorMap is created during the creation*)
        (* of a CycleTable, in the CycleTableSet procedure.               *)
        (*                                                                *)
        (*                  Naming Convention                             *)
        (* Start with TI, followed by a descriptor describing what        *)
        (* tests the Vector Map applies to (ie. all), followed by         *)
        (* VectorMap.                                                     *)
        (*                                                                *)
 
  VectorMap    = ( TIVMAP,  ScanInOrderVM, ScanOutOrderVM );              
  
        (*                                                                *)
        (*           Declaration of Test Types                            *)
        (*                                                                *)
        (* Normally, there will be three test types, Probe, Final,        *)
        (* and QA. The test type is used to select from multiple          *)
        (* sets of test parameters for different tests. Test Flow         *)
        (* can also be selected, but in the standard program, all         *)
        (* test flows are assumed to be the same. A common addition*)
        (* to the Test Types may be temperature (i.e. Final0Deg)          *)
        (*                                                                *)

  TITypeOfTest   = (Probe, Final, FT2, FT3, Q100_FT1, Q100_FT2, Q100_FT3, QA, Engineering );

  SoftBin        = ( 
                     NoResult, 
                     OpensFail,                 (* Parametric fail counter*)
                     ShortsFail,                                            
                     InleakFail,                                            
                     PmuInleakFail,                                           
                     TrileakFail,                                           
                     PmuTrileakFail,
                     PowerTypFail,
                     PowerMaxFail, 
                     PTULeakFail,
                     LevelFail,
                     LoVddLevelFail,
                     HiVddLevelFail,

                     VeryGoodUnit,

                     HiFrqATPGFail,
                     HiFrqA2DFail,
                     HiFrqCoreFail,
                     HiFrqCharFail,
                     HiFrqFGFail,
                     HiFrqEVFail,
                     HiFrqIntcFail,
                     HiFrqPllFail,
                     HiFrqRomFail,
                     HiFrqSyncFail,

                     HiFrqSpecATPGFail,
                     HiFrqSpecA2DFail,
                     HiFrqSpecCoreFail,
                     HiFrqSpecCharFail,
                     HiFrqSpecFGFail,
                     HiFrqSpecEVFail,
                     HiFrqSpecIntcFail,
                     HiFrqSpecPllFail,
                     HiFrqSpecRomFail,
                     HiFrqSpecSyncFail,

                     HiVddHiFrqATPGFail,
                     HiVddHiFrqA2DFail,
                     HiVddHiFrqCoreFail,
                     HiVddHiFrqCharFail,
                     HiVddHiFrqFGFail,
                     HiVddHiFrqEVFail,
                     HiVddHiFrqIntcFail,
                     HiVddHiFrqPllFail,                                         
                     HiVddHiFrqRomFail,
                     HiVddHiFrqSyncFail,

                     HiVddHiFrqSpecATPGFail,
                     HiVddHiFrqSpecA2DFail,
                     HiVddHiFrqSpecCoreFail,
                     HiVddHiFrqSpecCharFail,
                     HiVddHiFrqSpecFGFail,
                     HiVddHiFrqSpecEVFail,
                     HiVddHiFrqSpecIntcFail,
                     HiVddHiFrqSpecPllFail,                                         
                     HiVddHiFrqSpecRomFail,
                     HiVddHiFrqSpecSyncFail,

                     HiVddLoFrqATPGFail,
                     HiVddLoFrqA2DFail,
                     HiVddLoFrqCoreFail,
                     HiVddLoFrqCharFail,
                     HiVddLoFrqFGFail,
                     HiVddLoFrqEVFail,
                     HiVddLoFrqIntcFail,
                     HiVddLoFrqPllFail,                                         
                     HiVddLoFrqRomFail,
                     HiVddLoFrqSyncFail,

                     HiVddLoFrqSpecATPGFail,
                     HiVddLoFrqSpecA2DFail,
                     HiVddLoFrqSpecCoreFail,
                     HiVddLoFrqSpecCharFail,
                     HiVddLoFrqSpecFGFail,
                     HiVddLoFrqSpecEVFail,
                     HiVddLoFrqSpecIntcFail,
                     HiVddLoFrqSpecPllFail,                                         
                     HiVddLoFrqSpecRomFail,
                     HiVddLoFrqSpecSyncFail,

                     HiVddVeryHiFrqATPGFail,
                     HiVddVeryHiFrqA2DFail,
                     HiVddVeryHiFrqCoreFail,
                     HiVddVeryHiFrqCharFail,
                     HiVddVeryHiFrqFGFail,
                     HiVddVeryHiFrqEVFail,
                     HiVddVeryHiFrqIntcFail,
                     HiVddVeryHiFrqPllFail,                                         
                     HiVddVeryHiFrqRomFail,
                     HiVddVeryHiFrqSyncFail,

                     HiVddVeryHiFrqSpecATPGFail,
                     HiVddVeryHiFrqSpecA2DFail,
                     HiVddVeryHiFrqSpecCoreFail,
                     HiVddVeryHiFrqSpecCharFail,
                     HiVddVeryHiFrqSpecFGFail,
                     HiVddVeryHiFrqSpecEVFail,
                     HiVddVeryHiFrqSpecIntcFail,
                     HiVddVeryHiFrqSpecPllFail,
                     HiVddVeryHiFrqSpecRomFail,
                     HiVddVeryHiFrqSpecSyncFail,

                     LoFrqATPGFail,
                     LoFrqA2DFail,
                     LoFrqCoreFail,
                     LoFrqCharFail,
                     LoFrqFGFail,
                     LoFrqEVFail,
                     LoFrqIntcFail,
                     LoFrqPllFail,
                     LoFrqRomFail,
                     LoFrqSyncFail,

                     LoFrqSpecATPGFail,
                     LoFrqSpecA2DFail,
                     LoFrqSpecCoreFail,
                     LoFrqSpecCharFail,
                     LoFrqSpecFGFail,
                     LoFrqSpecEVFail,
                     LoFrqSpecIntcFail,
                     LoFrqSpecPllFail,
                     LoFrqSpecRomFail,
                     LoFrqSpecSyncFail,

                     LoVddHiFrqATPGFail,
                     LoVddHiFrqA2DFail,
                     LoVddHiFrqCoreFail,
                     LoVddHiFrqCharFail,
                     LoVddHiFrqFGFail,
                     LoVddHiFrqEVFail,
                     LoVddHiFrqIntcFail,
                     LoVddHiFrqPllFail,                                         
                     LoVddHiFrqRomFail,
                     LoVddHiFrqSyncFail,

                     LoVddHiFrqSpecATPGFail,
                     LoVddHiFrqSpecA2DFail,
                     LoVddHiFrqSpecCoreFail,
                     LoVddHiFrqSpecCharFail,
                     LoVddHiFrqSpecFGFail,
                     LoVddHiFrqSpecEVFail,
                     LoVddHiFrqSpecIntcFail,
                     LoVddHiFrqSpecSyncFail,
                     LoVddHiFrqSpecRomFail,
                     LoVddHiFrqSpecPllFail,                                         

                     LoVddLoFrqATPGFail,
                     LoVddLoFrqA2DFail,
                     LoVddLoFrqCoreFail,
                     LoVddLoFrqCharFail,
                     LoVddLoFrqFGFail,
                     LoVddLoFrqEVFail,
                     LoVddLoFrqIntcFail,
                     LoVddLoFrqPllFail,                                         
                     LoVddLoFrqRomFail,
                     LoVddLoFrqSyncFail,

                     LoVddLoFrqSpecATPGFail,
                     LoVddLoFrqSpecA2DFail,
                     LoVddLoFrqSpecCoreFail,
                     LoVddLoFrqSpecCharFail,
                     LoVddLoFrqSpecFGFail,
                     LoVddLoFrqSpecEVFail,
                     LoVddLoFrqSpecIntcFail,
                     LoVddLoFrqSpecSyncFail,
                     LoVddLoFrqSpecRomFail,
                     LoVddLoFrqSpecPllFail,                                         

                     LoVddVeryHiFrqATPGFail,
                     LoVddVeryHiFrqA2DFail,
                     LoVddVeryHiFrqCoreFail,
                     LoVddVeryHiFrqCharFail,
                     LoVddVeryHiFrqFGFail,
                     LoVddVeryHiFrqEVFail,
                     LoVddVeryHiFrqIntcFail,
                     LoVddVeryHiFrqPllFail,                                         
                     LoVddVeryHiFrqRomFail,
                     LoVddVeryHiFrqSyncFail,

                     LoVddVeryHiFrqSpecATPGFail,
                     LoVddVeryHiFrqSpecA2DFail,
                     LoVddVeryHiFrqSpecCoreFail,
                     LoVddVeryHiFrqSpecCharFail,
                     LoVddVeryHiFrqSpecFGFail,
                     LoVddVeryHiFrqSpecEVFail,
                     LoVddVeryHiFrqSpecIntcFail,
                     LoVddVeryHiFrqSpecPllFail,                                         
                     LoVddVeryHiFrqSpecRomFail,
                     LoVddVeryHiFrqSpecSyncFail,

                     VeryHiFrqATPGFail,
                     VeryHiFrqA2DFail,
                     VeryHiFrqCoreFail,
                     VeryHiFrqCharFail,
                     VeryHiFrqFGFail,
                     VeryHiFrqEVFail,
                     VeryHiFrqIntcFail,
                     VeryHiFrqPllFail,
                     VeryHiFrqRomFail,
                     VeryHiFrqSyncFail,

                     VeryHiFrqSpecATPGFail,
                     VeryHiFrqSpecA2DFail,
                     VeryHiFrqSpecCoreFail,
                     VeryHiFrqSpecCharFail,
                     VeryHiFrqSpecFGFail,
                     VeryHiFrqSpecEVFail,
                     VeryHiFrqSpecIntcFail,
                     VeryHiFrqSpecPllFail,
                     VeryHiFrqSpecRomFail,
                     VeryHiFrqSpecSyncFail,

                     GoodUnit,

                     Good_HiVddVeryHiFrqATPGFail,
                     Good_HiVddVeryHiFrqA2DFail,
                     Good_HiVddVeryHiFrqCoreFail,
                     Good_HiVddVeryHiFrqCharFail,
                     Good_HiVddVeryHiFrqFGFail,
                     Good_HiVddVeryHiFrqEVFail,
                     Good_HiVddVeryHiFrqIntcFail,
                     Good_HiVddVeryHiFrqPllFail,                            
                     Good_HiVddVeryHiFrqRomFail,
                     Good_HiVddVeryHiFrqSyncFail,

                     Good_HiVddVeryHiFrqSpecATPGFail,
                     Good_HiVddVeryHiFrqSpecA2DFail,
                     Good_HiVddVeryHiFrqSpecCoreFail,
                     Good_HiVddVeryHiFrqSpecCharFail,
                     Good_HiVddVeryHiFrqSpecFGFail,
                     Good_HiVddVeryHiFrqSpecEVFail,
                     Good_HiVddVeryHiFrqSpecIntcFail,
                     Good_HiVddVeryHiFrqSpecPllFail,                            
                     Good_HiVddVeryHiFrqSpecRomFail,
                     Good_HiVddVeryHiFrqSpecSyncFail,

                     Good_LoVddVeryHiFrqATPGFail,
                     Good_LoVddVeryHiFrqA2DFail,
                     Good_LoVddVeryHiFrqCoreFail,
                     Good_LoVddVeryHiFrqCharFail,
                     Good_LoVddVeryHiFrqFGFail,
                     Good_LoVddVeryHiFrqEVFail,
                     Good_LoVddVeryHiFrqIntcFail,
                     Good_LoVddVeryHiFrqPllFail,                       
                     Good_LoVddVeryHiFrqRomFail,
                     Good_LoVddVeryHiFrqSyncFail,

                     Good_LoVddVeryHiFrqSpecATPGFail,
                     Good_LoVddVeryHiFrqSpecA2DFail,
                     Good_LoVddVeryHiFrqSpecCoreFail,
                     Good_LoVddVeryHiFrqSpecCharFail,
                     Good_LoVddVeryHiFrqSpecFGFail,
                     Good_LoVddVeryHiFrqSpecEVFail,
                     Good_LoVddVeryHiFrqSpecIntcFail,
                     Good_LoVddVeryHiFrqSpecSyncFail,
                     Good_LoVddVeryHiFrqSpecRomFail,
                     Good_LoVddVeryHiFrqSpecPllFail,                       

                     Good_VeryHiFrqATPGFail,
                     Good_VeryHiFrqA2DFail,
                     Good_VeryHiFrqCoreFail,
                     Good_VeryHiFrqCharFail,
                     Good_VeryHiFrqFGFail,
                     Good_VeryHiFrqEVFail,
                     Good_VeryHiFrqIntcFail,
                     Good_VeryHiFrqPllFail,
                     Good_VeryHiFrqRomFail,
                     Good_VeryHiFrqSyncFail,

                     Good_VeryHiFrqSpecATPGFail,
                     Good_VeryHiFrqSpecA2DFail,
                     Good_VeryHiFrqSpecCoreFail,
                     Good_VeryHiFrqSpecCharFail,
                     Good_VeryHiFrqSpecFGFail,
                     Good_VeryHiFrqSpecEVFail,
                     Good_VeryHiFrqSpecIntcFail,
                     Good_VeryHiFrqSpecPllFail,
                     Good_VeryHiFrqSpecRomFail,
                     Good_VeryHiFrqSpecSyncFail,

                     LoVddIddqFail,
                     HiVddIddqFail,
                     PreStressHiVddIddqFail,
                     PostStressHiVddIddqFail,
                     PreStressLoVddIddqFail,
                     PostStressLoVddIddqFail,

                     (* Flash Softbins *) 

                     FlashFlowCheckFail,
                     FlashMP2FlowCheckFail,
                     FlashDataRetentionFail,
                     FlashDataGainFail,
                     FlashEraseVer1Fail,       
                     FlashErsegVer1Fail,       
                     FlashInvEraseFail,        
                     FlashRead1LoVddFail,
                     FlashRead1HiVddFail,   
                     FlashXORRead1LoVddFail,      
                     FlashRead0LoVddFail,      
                     FlashRead0HiVddFail,      
                     FlashReadStripesLoVddFail,
                     FlashReadChkbLoVddFail,
                     FlashVddminSearchFail,   
                     FlashPgmZerosFail,
                     FlashPgmStripesFail,   
                     FlashPgmChkbFail,
                     FlashPgmInvChkbFail,
                     FlashPgmSpeedCodeFail,    
                     FlashPgmInvSpeedCodeFail, 
                     FlashPgmFlowCheckFail,
                     FlashSpeedTestFail,
                     FlashWrapperTestFail,       
                     FlashCPUProgramFail,
                     FlashCPUPgmBootFail,
                     FlashCPUExecuteBootFail,

                     (* End Flash Softbins *)

                     RamRetentionFail,

                     CharSyncFail,
                     CharFuncFail,

                     StressSyncFail,
                     StressFuncFail,

                     LoVddLooseFuncFail,
                
                     LoVddHiFrqTimingFail,                                         
                     LoVddHiFrqIntTimingFail,
                     LoVddHiFrqExtTimingFail,                                         
                     HiVddHiFrqTimingFail,                                         
                     HiVddHiFrqIntTimingFail,                                         
                     HiVddHiFrqExtTimingFail,                                         
                     LoVddLoFrqTimingFail,
                     LoVddLoFrqIntTimingFail,
                     LoVddLoFrqExtTimingFail,
                     LoVddLoFrqPMTTimingFail,
                     HiVddLoFrqTimingFail,                                         
                     HiVddLoFrqIntTimingFail,                                         
                     HiVddLoFrqExtTimingFail,                                         
                     HiVddLoFrqPMTTimingFail,                                         

                     LoVddHiFrqIntLevelsFail,                                         
                     LoVddHiFrqExtLevelsFail,                                         

                     LooseSyncFail,
                     LoVddLooseSyncFail,
                     HiVddLooseSyncFail, 
                     LooseFuncFail,
                     LoVddHiFrqLooseSyncFail,
                     LoVddHiFrqLooseFuncFail,
                     LooseATPGFail,
                         
                     LooseCoreFail,
                     LooseCharFail,
                     LooseFGFail,
                     LoVddLooseCoreFail,
                     LoVddLooseCharFail,
                     LoVddLooseFGFail,
                     HiVddLooseATPGFail,
                     LooseRomFail,
                     HiVddLooseCoreFail,
                     HiVddLooseCharFail,
                     HiVddLooseFGFail,

                     LooseEVFail,
                     LoVddLooseEVFail,
                     HiVddLooseRomFail,
                     HiVddLooseEVFail,
                     LooseIntcFail,
                     LoVddLooseIntcFail,
                     HiVddLooseIntcFail,

                     SpareSoftBin
                   );

  HardBin        = (DummyBIN00,                 (* This one can't be used *)
                    BIN01, BIN02, BIN03, BIN04, (* DeltaFlex use will only*)
                    BIN05, BIN06, BIN07, BIN08, (* include 1-6, but 32 can*)
                    BIN09, BIN10, BIN11, BIN12, (* be used with some      *)
                    BIN13, BIN14, BIN15, BIN16, (* handlers mainly probers*)
                    BIN17, BIN18, BIN19, BIN20,
                    BIN21, BIN22, BIN23, BIN24,
                    BIN25, BIN26, BIN27, BIN28, 
                    BIN29, BIN30, BIN31);

  HandlerType    = ( noHandlerType );
  HandlerResult  = ( noHandlerResult );
  ParallelDevice = ( noParallelDevice );

        (*  Test Engineering inserts for Vega tester compatability        *)

  LECSetup               = (noLECSetup);

  WaveGroup              = (noWaveGroup);

        (*                                                                *)
        (*           Declaration of Device Types                          *)
        (* Declare the device types to be selected among in the           *)
        (* OperatorSetup menu. This will normally be used to              *)
        (* control test flow.                                             *)
        (*                                                                *)

  DeviceType     = (
                    F240_Probe,
                    F240_132QFP,
                    C240_Probe,
                    C240_132QFP
                   );


        (*                                                                *)
        (*           Declaration of Temperature Types                     *)
        (* Declare the temperature types to be selected among in          *)
        (* the OperatorSetup menu. This will normally be used to          *)
        (* control selection of supply limits.                            *)
        (*                                                                *)

  TempType       = (
                    Temp_N40_Degrees_C,
                    Temp_0_Degrees_C,
                    Temp_5_Degrees_C,        (* +5 DC spec Final *)
                    Temp_25_Degrees_C,
                    Temp_70_Degrees_C,      (* T= 70c ambient spec QA  *)     
                    Temp_90_Degrees_C,      (* T= 70c ambient spec FT1 *)
                    Temp_85_Degrees_C,      (* T= 85c ambient spec QA  *)     
                    Temp_105_Degrees_C,     (* T= 85c ambient spec FT1 *)
                    Temp_125_Degrees_C,     (* T=125c ambient spec QA  *)
                    Temp_135_Degrees_C      (* T=125c ambient spec F1T *)
                    );


        (*                                                         *)
        (*           Declaration of Origins                        *)
        (*                                                         *)

  Origin         = (
                        orgclkin,orgclkin2,orgclkout,orgpll,org_scan_clkin,
                        orgclkoutll,orgclkoutlf,orgclkouteh,orgclkouter,
                        orgclkoutlh,orgclkoutlr,orgclkoutel,orgclkoutef,
                        orgwenll,orgabusron,orgabusroff,
                        orgabuswon,orgabuswoff,orgdbusdon,orgdbusdoff,
                        orgdbusson,orgdbussoff,orgreadyon,orgreadyoff,

                        orgnrdll,orgnrdeh,orgnrdel,orgnrdlh,
                        orgclkr,orgiclkx,orgitclkx,orgxclkx,orgxtclkx,
                        orgxtclkx_tdm,orgtclkr_tdm,orgscan
                    );

  Clock          = (force_clkin,force_tck,force_pll,force_none);

  JitterType     = (LooseJitter,
                    SpecJitter,
                    CharJitter);

  TPType         = (LooseTP,
                    SpecTP,
                    CharTP);

        (*                                                                *)
        (*           Call to MegaTest provided procedures                 *)
        (* This call to the MegaTest procedures follows the               *)
        (* type declarations required by MegaTest, but precedes           *)
        (* type declarations which utilize some of the MegaTest           *)
        (* declared types. This call must precede the type                *)
        (* declarations below.                                            *)
        (*                                                                *)

insert 'MegaOne.Standard';
#include "constant.h"

type
                              
  TestTable = record
                     cycletablefield                : CycleTable;
                        actablefield                       : ACTable;
                        pinlistfield                       : PinList;
                        case WhatTestTable                 : TestName of
                          TIopensTest,
                          TIqpowerTest,
                          TIpowerTest                      : (dctablefield  : DCTable);
                          TIshortsTest,
                          TIinleakTest,
                          TItrilkgTest                     : (dctablefield1  : DCTable;
                                                              dctablefield2  : DCTable)
                     end;(*record definition*)


  TestTableArray = array [TIopensTest..TItrilkgTest] of TestTable;

  PeriodNumber   = 0..10;

  Period         = array [ PeriodNumber ] of integer;

  VddNumber      = 0..10;

  Vdd            = array [ VddNumber ] of MicroVolts;

  SearchBooleanArray   = array [FirstTempType..LastTempType,
                                0..10,          (* charperiod[1]..charperiod[10] *)
                                0..10           (* charvdd[1]..charvdd[10]]      *)
                                ] of boolean;


        (*                                                                *)
        (* The following three type declarations may be deleted if        *)
        (* no Sync routine is to be used. If a Sync routine               *)
        (* is used, the second field in each should include all of        *)
        (* the VoltageParameters assigned to a single supply. If          *)
        (* the device uses more than one supply, then the number of       *)
        (* dimensions of the arrays must be increased. One                *)
        (* should be added for each supply used.                          *)
        (*                                                                *)

#include "TIMSOPlusglobal.h"
#include "/u/TI_apps/stdprogram/TIexterns.h"
#include "externs.h"

var

      supplylimitslist1,
      supplylimitslist2,
      qsupplylimitslist,
      iddqsupplylimitslist                  : SupplyLimitsArray;

      FirstPatternName                      : TestName;
      LastPatternName                       : TestName;

      FirstScanPatternName                  : TestName;
      LastScanPatternName                   : TestName;

      pll_start,pll_end,
      pll_pmt_start,pll_pmt_end             : TestName;

      pattern                               : TestName;

      tgdb,

      clkoutll,clkoutlf,clkouteh,clkouter,
      clkoutlh,clkoutlr,clkoutel,clkoutef,

      nrdll,nrdlh,wenll,wenlh,
      abusron,abusroff,abuswon,
      jitterrise,jitterfall,
      abus,dbus,
      iclkx,itclkx,xclkx,xtclkx,
      clkin,clkin2,
      loostaa                               : PicoSeconds;

      jitterfall1                           : array [1..9] of PicoSeconds;
      jitterrise1                           : array [1..9] of PicoSeconds;
      clkin1                                : array [1..9] of PicoSeconds;
      pll_tpcycles                          : array [1..9] of integer;

      iddq_gb,lkg_gb,prb_gb                 : integer;
      stresspassnumber                      : integer;
      tpcycles,chartpcycles                 : integer;
      pass,fail                             : integer;

      vddtempgb                             : MicroVolts;
      logvmax                               : MicroVolts;

      idle_current                          : NanoAmps;
      iddq_current                          : NanoAmps;
      CVdd_iddq_current                     : NanoAmps;
      DVdd_iddq_current                     : NanoAmps;
      Vcca_iddq_current                     : NanoAmps;
      Vccp_iddq_current                     : NanoAmps;

      datalogiarray                         : NanoAmpsArray;
      datalogvarray                         : MicroVoltsArray;

      vdd                                   : VoltageParameter;
      clocksource                           : Clock;
      SupplyResult1, SupplyResult2          : MicroAmps;
      SupplyResult3, SupplyResult4          : MicroAmps;

      charinit                              : boolean;
      lastperiodnumber                      : PeriodNumber;
      lastvddnumber                         : VddNumber;
      charperiodnumber                      : PeriodNumber;
      charvddnumber                         : VddNumber;
      charperiod                            : Period;
      charvdd                               : Vdd;
      chardctable                           : DCTable;
      charactable                           : ACTable;
      charflowabort                         : boolean;
      skip_search                           : boolean;
      search_a2d,
      search_cpu,
      search_ev,
      search_exmif,
      search_flash,
      search_freqcase,
      search_gpio,
      search_iddq,
      search_levels,
      search_parametric,
      search_pll,
      search_power,
      search_spi,
      search_sci,
      search_sys,
      search_vddcase                        : boolean;
      search                                : SearchBooleanArray;
      chartemp                              : TempType;

      unitnumber,total_units_tested         : integer;
      numberofunit                          : integer;
      filenumber,lotnumber                  : integer;
      pcapvarcount                          : integer;

      cycletable                     : CycleTable;
      cycletablespeed               : CycleTableSpeed;

      testactable                           : ACTable;
      timingsdctable                        : DCTable;
      levelsdctable                         : DCTable;
      loosedctable                          : DCTable;
      stressdctable                         : DCTable;

      DataLogName                           : String;
      RomPatternName                        : String;
      pulled_romcode                	    : String;
      PllString,stdstring,SysClass          : String;

      CTIPDLLog                             : boolean;
      CTIstring                             : String;

      numberofunits                         : integer;
      savenumberofunits                     : integer;

      warning                               : boolean;
      continue                              : boolean;
      print                                 : integer;
      stopramsp0                            : integer;
      stopramsp1                            : integer;
      abort                                 : boolean;  
      schmooabort                           : boolean;
      handler                               : boolean;

      data_log                              : boolean;
      difflotold                            : String;
      summaryfile                           : String;
      summary                               : text;   
      delayretention                        : MicroSeconds;   
      delaysoak                             : MicroSeconds;   

      failatpg                              : boolean;
      faila2d                               : boolean;
      failcore                              : boolean;
      failchar                              : boolean;
      failev                                : boolean;
      failfg                                : boolean;
      failflash                             : boolean;
      failidle                              : boolean;
      failiddq                              : boolean;
      failintc                              : boolean;
      failjitter                            : boolean;
      failloospll                           : boolean;
      failpll                               : boolean;
      failpmt                               : boolean;
      failramretention                      : boolean;
      failrom                               : boolean;
      failsclksync                          : boolean;
      failspecsync                          : boolean;
      failstress                            : boolean;
      failsync                              : boolean;
      failtaa                               : boolean;
      failtiming                            : boolean;
      failtiming2                           : boolean;
      failtp                                : boolean;

      Bug_Supply                            : boolean;  
      DynamicLevelsWaveForms                : boolean;
      EngineeringEval                       : boolean;  
      Fast_Iddq                             : boolean;  
      IddqBoolean                           : boolean;  
      IddqEnable                            : boolean;
      LoVddIddqEnable                       : boolean;
      LoVddIddqScreenEnable                 : boolean;
      ADCMeasure                            : boolean;
      PwrMeasure                            : boolean;
      IddqMeasure                           : boolean;
      IddqScreenEnable                      : boolean;
      IdleEnable                            : boolean;
      IdleScreenEnable                      : boolean;
      IgnoreFail                            : boolean; 

      FlashEnable                           : boolean;
      FlashPMTEnable                        : boolean;
      InleakEnable                          : boolean;
      JitterMeasure                         : boolean;
      LevelTestEnable                       : boolean;
      LoadAIPats                            : boolean;
      LoadATPGPats                          : boolean;
      LoadCHARPats                          : boolean;
      LoadCOREPats                          : boolean;
      LoadEVPats                            : boolean;
      LoadEV2Pats                           : boolean;
      LoadFGPats                            : boolean;
      LoadFLPats                            : boolean;
      LoadFLFTPats                          : boolean;
      LoadFLFT1Pats                         : boolean;
      LoadFLMP2Pats                         : boolean;
      LoadINTCPats                          : boolean;
      LoadLongPats                          : boolean;
      LoadLPPats                            : boolean;
      LoadPLLPats                           : boolean;
      LoadPMTPats                           : boolean;
      LoadQ100Pats                          : boolean;
      LoadPats                              : boolean;
      LoadROMPats                           : boolean;
      LogIddqEnable                         : boolean;
      LogMaxVddEnable                       : boolean;
      LogRamFailEnable                      : boolean;
      LoFreqEnable                          : boolean;
      OscillatorTestEnable                  : boolean;
      PMUInleakEnable                       : boolean;
      PMUTrileakEnable                      : boolean;
      PTULeakEnable                         : boolean;
      PllEnable                             : boolean;
      PllPMTEnable                          : boolean;
      PowerEnable                           : boolean;
      PowerScreenEnable                     : boolean;
      PostStressFuncTestEnable              : boolean;
      PreStressIddqEnable                   : boolean;
      PreStressLoVddIddqEnable              : boolean;
      PreStressInLeakEnable                 : boolean;
      PreStressPTULeakEnable                : boolean;
      RamRetentionTestEnable                : boolean;
      RamSequenceTestEnable                 : boolean;
      RamWalkTestEnable                     : boolean;
      RomProtectEnable                      : boolean;
      RomTestEnable                         : boolean;
      ScanTestEnable                        : boolean;
      ScreenBIN2                            : boolean;
      SingleDUTSupply                       : boolean;  
      SpecPll                               : boolean;
      SpecTimings                           : boolean;
      SpecVdd                               : boolean;
      SecondPassEnable                      : boolean;
      SpeedSortEnable                       : boolean;
      StressEnable                          : boolean;
      StressScreenEnable                    : boolean;
      TIPrintTimings                        : boolean;
      TrileakEnable                         : boolean;
      UseLongPattern                        : boolean;     
      VeryHighVddHighFreqTestEnable         : boolean;
      VeryHighVddProbeTestEnable            : boolean;
      VeryHighVddTestEnable                 : boolean;
      VeryLowVddQGTestEnable                : boolean;
      VeryLowVddScanTestEnable              : boolean;
      VeryLowVddTestEnable                  : boolean;

(* Single Pins *)

  WEN,RNW,BRN,STRBN,D0,D1,D2,D3,D4,D5,D6,D7,D8,D9,D10,D11,D12,D13,D14,D15,
  TCK,TDI,TRSTN,TMS,TDO,RSN,READY,MPMCN,EMU0,EMU1,NMIN,LVDOVRD,PMTMODE,
  SCIRXD,SCITXD,SPISIMO,SPISOMI,SPICLK,SPISTE,PDPINT,XINT1,XINT2,XINT3,
  OSCBYPN,XTAL2,CLKIN,ADCSOC,CLKOUT1,XF,BION,CAP1,CAP2,CAP3,CAP4,ADCIN0,
  ADCIN1,ADCIN2,ADCIN3,ADCIN4,ADCIN5,ADCIN6,ADCIN7,ADCIN15,ADCIN14,ADCIN13,
  ADCIN12,VREFHI,ADCIN11,ADCIN10,ADCIN9,ADCIN8,
  PWM1,PWM2,PWM3,PWM4,PWM5,PWM6,PWM7,PWM8,PWM9,T1PWM,T2PWM,T3PWM,TMRDIR,TMRCLK,
  A0,A1,A2,A3,A4,A5,A6,A7,A8,A9,A10,A11,A12,A13,A14,A15,DSN,ISN,PSN,RDN,

(* FLASH Group Pins *)

         TABUS,TTCR,TSP,TWRITE,TERASE,TVER1,TVER0,TRESET,TFOENAB,TCE,TLP,TEXE,
           TDBUS,TPMT,
           NonFlashINS,NonFlashOUT,NonFlashIOS, 

(* Pattern Field Group Pins *)

         FIELD12, FIELD11, FIELD10, FIELD9, FIELD8, FIELD7, FIELD6, 
         FIELD5, FIELD4, FIELD3, FIELD2, FIELD1,

(* Busses and other Functional Group Pins *)
        
         ABUS,DBUS,
         ABTIME,
         ACTRL,
         ADCINS,
         ADCIOS,
         ALLOUTS,
         ALLIOS,IOPINS,
         MUXPINS,
       
(* Parametric  Group Pins *)

         ALLINS,
         ALLINLEAKIOS,
         ALLINLEAKOUTS,
         ALLPINS,
         ALLTRISTATE,
         EVENADCINS,
         EVENADCIOS,
         EVENINLEAKINS,
         EVENINS,
         EVENPINS,
         EVENTRISTATE,
         IDDQDISCONNECT,
         INDOWNS,
         INPUTS,
         INUPS,
         IOUPS,
         LOOSEIOS,
         LOOSEOUTS,
         MASKED,
         NCPINS,
         NOINLEAKTESTINS,
         NOTRILKGTESTIOS,
         NOPTUITESTPINS,
         ODDADCINS,
         ODDADCIOS,
         ODDINLEAKINS,
         ODDINS,
         ODDPINS,
         ODDTRISTATE,
         OPENSPINS,
         PTULEAK1,
         PTULEAK2,
         PTULEAK3,
         SAVEMASKED,
         SHORTSPINS,
         TESTINS,
         TIMINGIOS,
         TIMINGOUTS,

         (* 19-Dec-96 begin add adc test *)
         AWGTRIGGER_CLK, 
         AWGTRIGGER_START, 
         DIOTRIGGER,
         LECPINS,
         ADCINPUTP,
         ADCINPUTN,
         (* 19-Dec-96 end add adc test *)

         noPinList               : PinList;


      CharFileName,CharFileName1            : String;
      CharFile,CharFile1                    : text;
      CFFlag                                : boolean;
      timesearch                            : boolean;
      actablename                           : ACTable;
      dctablename                           : DCTable;
      wsatablename                          : WSATable;
      cycletablename                        : CycleTable;
      lotn, tempn, tester                   : String;
      totalunits, devicen                   : integer;
      charabort,charsetup,first_done        : boolean;
      env, envresult                        : String;
      hmos_site                             : boolean;
      dmos_site                             : boolean;
      miho_site                             : boolean;
      lmos_site                             : boolean;
      tipi_site                             : boolean;
      adc_dual_test                         : boolean;
      mso_tester                            : boolean;
      delta_rev                             : boolean;
      (*For Flash*)
      code                                  : array [1..16384,1..2] of integer;

(* MP2 Data Log Variables *)
      m0_Vcc0_MP1,m0_Vcc0_MP2               : MicroVolts;
      m0_Vcc0				    : MicroVolts;
      m0_loss				    : real;


      M0_Erase                              : integer;
      M0_Erseg                              : integer;

