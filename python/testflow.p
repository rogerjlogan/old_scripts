BoardCheckEnable              :true
BootCodeEnable                :true
IddqEnable                    :true
IddqLowerVddEnable            :false
IddqLowerVddScreenEnable      :false
IddqScreenEnable              :true
Idle3Enable                   :false
Idle3LowerVddEnable           :false
Idle3LowerVddScreenEnable     :false
Idle3ScreenEnable             :false
IdleEnable                    :false
IdleScreenEnable              :false
InleakEnable                  :false
LevelTestEnable               :true
LogIddqEnable                 :false
LogMaxVddEnable               :false
LogRamFailEnable              :false
LowFreqEnable                 :true
OscillatorTestEnable          :false
PllEnable                     :true
PMUInleakEnable               :false
PMUTrileakEnable              :false
PowerEnable                   :false
PowerScreenEnable             :false
PreStressFuncEnable           :true
PreStressIddqEnable           :false
PreStressIdle3Enable          :false
PreStressInLeakEnable         :false
PreStressPTULeakEnable        :false
PTULeakEnable                 :true
RamRetentionTestEnable        :false
RamSequenceTestEnable         :true
RamWalkTestEnable             :true
RomProtectEnable              :false
RomTestEnable                 :true
ScanTestEnable                :false
SDAlog_Enable                 :false
SecondPassEnable              :true
SpeedSortEnable               :true
StressEnable                  :false
StressScreenEnable            :false
TrileakEnable                 :false
VeryHighVddHighFreqTestEnable :false
VeryHighVddProbeTestEnable    :false
VeryHighVddTestEnable         :false
VeryLowVddQGTestEnable        :false
VeryLowVddScanTestEnable      :false
VeryLowVddTestEnable          :false

procedure TestFlow;
label 5, 10, 11, 12, 13, 100, 200;
var
    IgnoreFail            :   boolean;
    FailStress            :   boolean;
    incr,i                :   integer;
    PatName               :   String;
    idleactable           :   ACTable;
    initial_iddq_current  :   NanoAmps;
    FirstCycle            :   integer;
    LastCycle             :   integer;
    CurrentLine           :   integer;
    iddqmeasure           :   boolean;
    ctipdllog             :   boolean;
    hardbinnumber,
    softbinnumber         :   integer;
    TempSoftBin           :   SoftBin;
    TempHardBin           :   HardBin;
    pattern               :   TestName;
    highestvcount,
    execcount,pass        :   integer;
    failstress            :   boolean;
    appliedvoltage        :   MicroVolts;
    Temp_IOH              :   NanoAmps;
    Temp_IOL              :   NanoAmps;
    numberofpass          :   integer;
    save_iddqlimit        :   NanoAmps;
    receive_string        :   String;
    send_string           :   String;
    errorbit              :   integer;
    wafer_id              :   array [1..20] of char;
    waferID_gpib          :   integer;
    save_dosync           :   boolean;
    dopll                 :   boolean;
    found_GEC             :   boolean;
    LooseFuncFail         :   boolean;
    LooseSyncFail         :   boolean;
    LooseRamFail          :   boolean;
    LooseRomFail          :   boolean;
    stress_first_pass     :   boolean;
    logmaxvdd             :   boolean;
    dlog_file             :   text;
    vddmin_fail           :   boolean;
    stress_time           :   integer;
    LooseFuncCheck        :   boolean;
    totalunits                      : integer;
    TimeofDay, TodaysDate           : alfa;
    test_time_01                    : integer;
    test_time_02                    : integer;
    timer                           : boolean;
    powerconsumption_cvdd_max       : MicroAmps;
    powerconsumption_dvdd_max       : MicroAmps;
    powerconsumption_cvdd_typ       : MicroAmps;
    powerconsumption_dvdd_typ       : MicroAmps;
    dummy_TIMeasure                 : boolean;
    timenow                         : MicroSeconds;
    timelast                        : MicroSeconds;
    always_fail                     : boolean;
procedure SetSoftBin;
 begin
writeln(execFile,'PROC:SetSoftBin');
  case vdd of
   Vddmin :
      case testactable of
          TIveryhifrqACTable,TIveryhifrqACTable1,TIveryhifrqACTable2,TIveryhifrqlooseACTable :
             begin
              if failsync or failsclksync then softbin:=LoVddVeryHiFrqSyncFail;
              if failspecsync then softbin:=LoVddVeryHiFrqSpecSyncFail;
              if failtiming then softbin:=LoVddVeryHiFrqTimingFail;
              if failramsequence then softbin:=LoVddVeryHiFrqRamSequenceFail;
              if failramwalk then softbin:=LoVddVeryHiFrqRamWalkFail;
              if failtiming2 then softbin:=LoVddVeryHiFrqTiming2Fail;
              if failtaa then softbin:=LoVddVeryHiFrqTaAFail;
              if failrom then softbin:=LoVddVeryHiFrqRomFail;
              if failpll then softbin:=LoVddVeryHiFrqPllFail;
              if failloospll then softbin:=LoVddVeryHiFrqPllLoosFail;
             end;
          TIhifrqACTable,TIhifrqACTable1,TIhifrqACTable2,TIhifrqlooseACTable :
             begin
              if failsync or failsclksync then softbin:=LoVddHiFrqSyncFail;
              if failspecsync then softbin:=LoVddHiFrqSpecSyncFail;
              if failtiming then softbin:=LoVddHiFrqTimingFail;
              if failramsequence then softbin:=LoVddHiFrqRamSequenceFail;
              if failramwalk then softbin:=LoVddHiFrqRamWalkFail;
              if failtiming2 then softbin:=LoVddHiFrqTiming2Fail;
              if failtaa then softbin:=LoVddHiFrqTaAFail;
              if failrom then softbin:=LoVddHiFrqRomFail;
              if failpll then softbin:=LoVddHiFrqPllFail;
              if failloospll then softbin:=LoVddHiFrqPllLoosFail;
             end;
          TIlofrqACTable,TIlofrqACTable1,TIlofrqACTable2,TIlofrqlooseACTable,TIlofrqpllACTable:
             begin
              if failsync or failsclksync then softbin:=LoVddLoFrqSyncFail;
              if failspecsync then softbin:=LoVddLoFrqSpecSyncFail;
              if failtiming then softbin:=LoVddLoFrqTimingFail;
              if failrom then softbin:=LoVddLoFrqRomFail;
              if failpll then softbin:=LoVddLoFrqPllFail;
              if failloospll then softbin:=LoVddLoFrqPllLoosFail;
             end;
          others: begin end;
      end;
   Vddmax :
      case testactable of
          TIveryhifrqACTable,TIveryhifrqACTable1,TIveryhifrqACTable2,TIveryhifrqlooseACTable :
             begin
              if failsync or failsclksync then softbin:=HiVddVeryHiFrqSyncFail;
              if failspecsync then softbin:=HiVddVeryHiFrqSpecSyncFail;
              if failtiming then softbin:=HiVddVeryHiFrqTimingFail;
              if failramsequence then softbin:=HiVddVeryHiFrqRamSequenceFail;
              if failramwalk then softbin:=HiVddVeryHiFrqRamWalkFail;
              if failtiming2 then softbin:=HiVddVeryHiFrqTiming2Fail;
              if failtaa then softbin:=HiVddVeryHiFrqTaAFail;
              if failrom then softbin:=HiVddVeryHiFrqRomFail;
              if failpll then softbin:=HiVddVeryHiFrqPllFail;
              if failloospll then softbin:=HiVddVeryHiFrqPllLoosFail;
            end;
          TIhifrqACTable,TIhifrqACTable1,TIhifrqACTable2,TIhifrqlooseACTable :
             begin
              if failsync or failsclksync then softbin:=HiVddHiFrqSyncFail;
              if failspecsync then softbin:=HiVddHiFrqSpecSyncFail;
              if failtiming then softbin:=HiVddHiFrqTimingFail;
              if failramsequence then softbin:=HiVddHiFrqRamSequenceFail;
              if failramwalk then softbin:=HiVddHiFrqRamWalkFail;
              if failtiming2 then softbin:=HiVddHiFrqTiming2Fail;
              if failtaa then softbin:=HiVddHiFrqTaAFail;
              if failrom then softbin:=HiVddHiFrqRomFail;
              if failpll then softbin:=HiVddHiFrqPllFail;
              if failloospll then softbin:=HiVddHiFrqPllLoosFail;
             end;
          TIlofrqACTable,TIlofrqACTable1,TIlofrqACTable2,TIlofrqlooseACTable,TIlofrqpllACTable:
             begin
              if failsync or failsclksync then softbin:=HiVddLoFrqSyncFail;
              if failspecsync then softbin:=HiVddLoFrqSpecSyncFail;
              if failtiming then softbin:=HiVddLoFrqTimingFail;
              if failrom then softbin:=HiVddLoFrqRomFail;
              if failpll then softbin:=HiVddLoFrqPllFail;
              if failloospll then softbin:=HiVddLoFrqPllLoosFail;
             end;
          others: begin end;
      end;
   VddMin :
      case testactable of
          TIveryhifrqACTable,TIveryhifrqACTable1,TIveryhifrqACTable2,TIveryhifrqlooseACTable :
             begin
              if failsync or failsclksync then softbin:=LoVddVeryHiFrqSyncFail;
              if failspecsync then softbin:=LoVddVeryHiFrqSpecSyncFail;
              if failtiming then softbin:=LoVddVeryHiFrqTimingFail;
              if failramsequence then softbin:=LoVddVeryHiFrqRamSequenceFail;
              if failramwalk then softbin:=LoVddVeryHiFrqRamWalkFail;
              if failtiming2 then softbin:=LoVddVeryHiFrqTiming2Fail;
              if failtaa then softbin:=LoVddVeryHiFrqTaAFail;
              if failrom then softbin:=LoVddVeryHiFrqRomFail;
              if failpll then softbin:=LoVddVeryHiFrqPllFail;
              if failloospll then softbin:=LoVddVeryHiFrqPllLoosFail;
             end;
          others:
            begin
              if failquickgen then softbin:=VddMin_OtherFuncFail;
            end;
      end;
   Vddnom : begin end;
   others : begin end;
 end;
writeln(execFile,'PROCEND:SetSoftBin');
end;
 procedure SetSyncSoftbin;
     begin
writeln(execFile,'PROC:SetSyncSoftbin');
        case softbin of
            SyncFail           :  begin
                                    if failNRD then
                                       softbin:=SyncFail_NRD
                                    else if failsclksync then
                                       softbin:=SyncFail_CLKX
                                    else if failtclksync then
                                       softbin:=SyncFail_TCLKX;
                                  end;
           VddMin_SyncFail     :  begin
                                    if failNRD then
                                       softbin:=VddMin_SyncFail_NRD
                                    else if failsclksync then
                                       softbin:=VddMin_SyncFail_CLKX
                                    else if failtclksync then
                                       softbin:=VddMin_SyncFail_TCLKX;
                                  end;
           VddMax_SyncFail     :  begin
                                    if failNRD then
                                       softbin:=VddMax_SyncFail_NRD
                                    else if failsclksync then
                                       softbin:=VddMax_SyncFail_CLKX
                                    else if failtclksync then
                                       softbin:=VddMax_SyncFail_TCLKX;
                                  end;
           PreStress_SyncFail  :  begin
                                    if failNRD then
                                       softbin:=PreStress_SyncFail_NRD
                                    else if failsclksync then
                                       softbin:=PreStress_SyncFail_CLKX
                                    else if failtclksync then
                                       softbin:=PreStress_SyncFail_TCLKX;
                                  end;
           Stress_SyncFail     :  begin
                                    if failNRD then
                                       softbin:=Stress_SyncFail_NRD
                                    else if failsclksync then
                                       softbin:=Stress_SyncFail_CLKX
                                    else if failtclksync then
                                       softbin:=Stress_SyncFail_TCLKX;
                                  end;
           others               : begin
                                  end;
         end ;
writeln(execFile,'PROCEND:SetSyncSoftbin');
end;
procedure RestoreLoads;
begin
writeln(execFile,'PROC:RestoreLoads');
  ISet(NRD,      IOH,     Temp_IOH);
  ISet(CLKOUT,   IOH,     Temp_IOH);
  ISet(LOOSEOUTS,IOH,     Temp_IOH);
  ISet(ALLIOS,   IOH,     Temp_IOH);
  ISet(NRD,      IOL,     Temp_IOL);
  ISet(CLKOUT,   IOL,     Temp_IOL);
  ISet(LOOSEOUTS,IOL,     Temp_IOL);
  ISet(ALLIOS,   IOL,     Temp_IOL);
writeln(execFile,'PROCEND:RestoreLoads');
end;
procedure LoosFunc;
 label 5;
    begin
writeln(execFile,'PROC:LoosFunc');
       save_dosync:=dosync;
       dosync:=true;
       vdd:=Vddnom;powerup(DCDataSheets[TIdataDCTable].v[vdd]);
       Sync(TIlofrqlooseACTable,TIlooseDCTable,force_clkin);
       if failsync or failsclksync or failtclksync then
          begin
            if not LooseFuncCheck then
               softbin:=PreStress_SyncFail
            else
               softbin:=SyncFail;
            SetSyncSoftbin;
            if (TIScreenPrint) then writeln(' SYNC FAILED 5v');
            if not TIIgnoreFail then
              begin
                LooseFuncFail:=true;
                goto 5;
              end;
          end;
       if not patterntest(cycletable,TIlofrqlooseACTable,TIlooseDCTable,FirstPatternName,LastPatternName) then
            begin
                if ( myTestFunc(saram) and myTestFunc(ramb0) and myTestFunc(ramb1) and myTestFunc(ramb2) ) then
                    begin
                      if not LooseFuncCheck then
                        softbin:=PreStress_FuncFail
                      else
                        softbin:=FuncFail;
                        if (TIScreenPrint) then writeln(' >> 5V FUNCTIONAL FAILED');
                    end else
                    begin
                      if not LooseFuncCheck then
                        softbin:=PreStress_RamFail
                      else
                        softbin:=RamFail;
                        if LogRamFailEnable then LogAllMemoryFails;
                        if (TIScreenPrint) then writeln(' >> 5V SARAM FAILED');
                    end;
                 if not TIIgnoreFail then
                    begin
                      LooseFuncFail:=true;goto 5;
                   end;
            end;
       if not myTestFunc(ext_dma_all) then
            begin
              if not LooseFuncCheck then
                softbin:=PreStress_RamFail
              else
                softbin:=RamFail;
                if LogRamFailEnable then LogAllMemoryFails;
                if (TIScreenPrint) then writeln(' >> EXT_DMA_ALL FAILED 5V');
                if not TIIgnoreFail then
                   begin
                     LooseFuncFail:=true;goto 5;
                   end;
            end;
       if not myTestFunc(romdump) or not myTestFunc(rom_coupling) or not myTestFunc(extrom) then
            begin
              if not LooseFuncCheck then
                softbin:=PreStress_RomFail
              else
                softbin:=RomFail;
                if LogRamFailEnable then LogAllMemoryFails;
                if (TIScreenPrint) then writeln(' >> ROM FAILED 5V');
                if not TIIgnoreFail then
                   begin
                     LooseFuncFail:=true;goto 5;
                   end;
            end;
      if (TIScreenPrint and not TIIgnoreFail) then writeln(' PASSED 5V TESTS');
  5:
      dosync:=save_dosync;
writeln(execFile,'PROCEND:LoosFunc');
end;
procedure opens_test;
begin
writeln(execFile,'PROC:opens_test');
  pd;
  opens_fail:=false;
  if not OPENS(TIopensTest) then begin
    if (TIScreenPrint) then writeln('>> FAILED OPENS test');
    softbin:= OpensFail;
    if not TIIgnoreFail then opens_fail:=true;
  end;
writeln(execFile,'PROCEND:opens_test');
end;
procedure shorts_test;
begin
writeln(execFile,'PROC:shorts_test');
  shorts_fail:=false;
  if not SHORTS(TIshortsTest) then begin
    if (TIScreenPrint) then writeln('>> FAILED SHORTS test');
    softbin:= ShortsFail;
    if not TIIgnoreFail then shorts_fail:=true;
  end;
writeln(execFile,'PROCEND:shorts_test');
end;
procedure ProgramTimer( s : String );
  begin
writeln(execFile,'PROC:ProgramTimer');
    timenow := TimerRead;
    writeln(s:40,timenow/1e6:10:3,'s',
            (timenow - timelast)/1e6:11:3,'s');
    timelast := timenow;
writeln(execFile,'PROCEND:ProgramTimer');
end;
begin
writeln(execFile,'PROC:TestFlow');
  logmaxvdd:=false;
  FirstScanPatternName:=scan_cntrl;
  LastScanPatternName:=rom5_scan;
  if UseLongPattern then
    begin
      FirstPatternName:=generic_long;
      LastPatternName:=specific_long;
    end else
    begin
      FirstPatternName:=alu1;
      LastPatternName:=mpassing_base;
    end;
  if not tipi_site then ModeSet(TesterLockBegin);
  if TIScreenPrint then writeln;
  ctipdllog:=CTIPDLLog;
  if ctipdllog then CTIPDLDataLogNewUnit(0);
  if TimeProgram then
    begin
      timenow  := 0us;
      timelast := 0us;
      writeln('Test Flow Timer Started = ',TimerStart);
      writeln('                                         CUMULATIVE  INDIVIDUAL');
      writeln('TEST                                        TIME        TIME   ');
      writeln('---------------------------------------------------------------');
    end;
  if PreStressInLeakEnable then
     begin
       vdd:=Vddparam;powerup(DCDataSheets[TIdataDCTable].v[vdd]);
       if not INLEAK(TIinleakTest) then begin
         if (TIScreenPrint) then writeln('>> Failed INPUT LEAKAGE test');
         softbin:= InleakFail;
         if not TIIgnoreFail then goto 100;
       end;
    end;
if TimeProgram then
             ProgramTimer('PreStressInLeak ');
  if PreStressPTULeakEnable then
    begin
       vdd:=Vddparam;powerup(DCDataSheets[TIdataDCTable].v[vdd]);
       if not PTULeak then begin
         if (TIScreenPrint) then writeln('>> Failed PTULeakage tests');
         softbin:= PTULeakFail;
         if not TIIgnoreFail then goto 100;
       end else if (TIScreenPrint) then writeln('Passed PTULeakage tests');
    end;
case TITestType of
Probe:
begin
 WaferNumber := CTIWaferMapData.proberwafernum;
 Xcoord      := CTIWaferMapData.proberXcoord;
 Ycoord      := CTIWaferMapData.proberYcoord;
 if TIScreenPrint then
    writeln ( 'Wafer = ', WaferNumber:3, '  X = ', Xcoord:2,'  Y = ', Ycoord:2 );
 if (WaferNumber <> LastWaferNumber) then
  begin
    new_wafer:=true;
    found_GEC:=false;
    LastWaferNumber:=WaferNumber;
  end
 else
    new_wafer:=false;
 if (new_wafer or (die_count>=50)) then
   begin
     dosync:=true;
     dopll:=true;
     die_count:=0;
   end;
 if new_wafer then ramfail_count:=0;
 if not (TIFELot=last_TIFELot) then
   begin
     IntDlogFile:=false;
     SDAIntDone:=false;
     new_lot:=true;
   end else
   begin
     new_lot:=false;
     if new_wafer then begin
       IntDlogFile:=true;
       SDAIntDone:=false;
     end;
   end;
 last_TIFELot:=TIFELot;
 if (new_lot) then wafer_cnt:=0;
 if new_wafer then wafer_cnt:=wafer_cnt+1;
 if ( ((WaferNumber in [5,10,15,20]) and SDAlog_Enable ) or SDA_debug_mode ) then
   do_ram_SDA:=true
 else
   do_ram_SDA:=false;
 if ((LogRamFailEnable or LogIddqEnable) and ((not IntDlogFile) or (new_wafer))) then
    Initialize_Datalog_File;
 softbin:=VeryGoodUnit;
 LooseFuncCheck := false;
vddmin_fail    :=false;
10:
if VeryLowVddTestEnable then
  begin
  vdd:=VddMin;powerup(DCDataSheets[TIdataDCTable].v[vdd]);
  Sync(TIhifrqlooseACTable,TIlooseDCTable,force_clkin);
  if failsync or failsclksync then
      begin
        opens_test;if (opens_fail) then goto 100;
        shorts_test;if (shorts_fail) then goto 100;
        if (TIScreenPrint) then writeln(' >> FAILED SYNC');
        if not accept_bin01_only then
           softbin:=GoodUnit_LoVddVeryHiFrqSyncFail
        else
           softbin:=Do_not_ship_LoVddVeryHiFrqSyncFail;
        vddmin_fail:=true;
        if not TIIgnoreFail then goto 11;
      end;
if TimeProgram then
             ProgramTimer('sync TIhifrqlooseACTable');
  if not patterntest(cycletable,TIhifrqlooseACTable,TIlooseDCTable,FirstPatternName,LastPatternName) then
      begin
        opens_test;if (opens_fail) then goto 100;
        shorts_test;if (shorts_fail) then goto 100;
        if not dosync then
          begin
            dosync:=true;goto 10;
          end;
        if (TIScreenPrint) then writeln(' >> FAILED FUNC ');
        if not accept_bin01_only then
           softbin:=GoodUnit_LoVddVeryHiFrqTimingFail
        else
           softbin:=Do_not_ship_LoVddVeryHiFrqTimingFail;
          vddmin_fail:=true;
        if not TIIgnoreFail then goto 11;
      end;
if TimeProgram then
             ProgramTimer('LoVddVeryHiFrq ');
  if not myTestFunc(ext_dma_all) then
      begin
        opens_test;if (opens_fail) then goto 100;
        shorts_test;if (shorts_fail) then goto 100;
        if not dosync then begin
           dosync:=true;goto 10;
        end;
        if (TIScreenPrint) then writeln(' >> FAILED EXT_DMA_ALL ');
        if not accept_bin01_only then
           softbin:=GoodUnit_LoVddVeryHiFrqRamSequenceFail
        else
           softbin:=Do_not_ship_LoVddVeryHiFrqRamSequenceFail;
        vddmin_fail:=true;
        if not TIIgnoreFail then goto 11;
      end;
if TimeProgram then
             ProgramTimer('LoVddVeryHiFrqRam ');
  if not myTestFunc(romdump) or not myTestFunc(rom_coupling) or not myTestFunc(extrom) then
      begin
        opens_test;if (opens_fail) then goto 100;
        shorts_test;if (shorts_fail) then goto 100;
        if not dosync then begin
           dosync:=true;goto 10;
        end;
        if (TIScreenPrint) then writeln(' >> FAILED ROMDUMP ');
        softbin:=GoodUnit_LoVddVeryHiFrqRomFail;
        vddmin_fail:=true;
        if not TIIgnoreFail then goto 11;
      end;
  goto 12;
11:
vddmin_fail    :=false;
if TimeProgram then
             ProgramTimer('LoVddVeryHiFrqRom ');
  vdd:=Vddmin;powerup(DCDataSheets[TIdataDCTable].v[vdd]);
  Sync(TIhifrqlooseACTable,TIlooseDCTable,force_clkin);
  if failsync or failsclksync then
      begin
        opens_test;if (opens_fail) then goto 100;
        shorts_test;if (shorts_fail) then goto 100;
        if (TIScreenPrint) then writeln(' >> FAILED SYNC');
        softbin:=VddMin_SyncFail;
        vddmin_fail:=true;
        if not TIIgnoreFail then goto 12;
      end;
if TimeProgram then
             ProgramTimer('sync hifrqlooseACT Min_Vdd ');
  if not patterntest(cycletable,TIhifrqlooseACTable,TIlooseDCTable,FirstPatternName,LastPatternName) then
      begin
        opens_test;if (opens_fail) then goto 100;
        shorts_test;if (shorts_fail) then goto 100;
        if not dosync then
          begin
            dosync:=true;goto 11;
          end;
        if (TIScreenPrint) then writeln(' >> FAILED FUNC ');
          softbin:=VddMin_FuncFail;
          vddmin_fail:=true;
        if not TIIgnoreFail then goto 12;
      end;
if TimeProgram then
             ProgramTimer('VddMin_Func test ');
  if not myTestFunc(ext_dma_all) then
      begin
        opens_test;if (opens_fail) then goto 100;
        shorts_test;if (shorts_fail) then goto 100;
        if not dosync then begin
           dosync:=true;goto 11;
        end;
        if (TIScreenPrint) then writeln(' >> FAILED EXT_DMA_ALL ');
        softbin:=VddMin_RamFail;
        vddmin_fail:=true;
        if not TIIgnoreFail then goto 12;
      end;
if TimeProgram then
             ProgramTimer('VddMin_Ram ');
  if not myTestFunc(romdump) or not myTestFunc(rom_coupling) or not myTestFunc(extrom) then
      begin
        opens_test;if (opens_fail) then goto 100;
        shorts_test;if (shorts_fail) then goto 100;
        if not dosync then begin
           dosync:=true;goto 11;
        end;
        if (TIScreenPrint) then writeln(' >> FAILED ROMDUMP ');
        softbin:=VddMin_RomFail;
        vddmin_fail:=true;
        if not TIIgnoreFail then goto 12;
      end;
if TimeProgram then
             ProgramTimer('VddMin_Rom ');
12:
  if vddmin_fail then
      begin
        LoosFunc;
        if not TIIgnoreFail then goto 100;
      end else if (TIScreenPrint and not TIIgnoreFail) then writeln(' PASSED VERY LOW VDD TESTS');
end;
if VeryLowVddQGTestEnable then
  begin
    if ( (romcode='37362') or (romcode='37368') or  ( romcode='373c3') ) then begin
        if quickgentest( ((ACDataSheets[TIveryhifrqlooseACTable].t[tper] + 500ps) div 1ns),
                           DCDataSheets[TIdataDCTable].v[VddMin], force_clkin2, quickgen1,quickgen6) then else;
      end;
    if (Device=c51sx) then begin
      if quickgentest( ((ACDataSheets[TIhifrqlooseACTable].t[tper] + 500ps) div 1ns),
                         DCDataSheets[TIdataDCTable].v[VddMin], force_clkin2, quickgen1,quickgen6) then else;
      end;
    if failquickgen then
      begin
        if TIScreenPrint then writeln(' >> FAILED QUICKGEN ');
        softbin:=VddMin_OtherFuncFail;
        if not TIIgnoreFail then goto 100;
      end else if TIScreenPrint then writeln(' PASSED QUICKGEN');
  end;
if TimeProgram then
             ProgramTimer('VeryLowVddQGTest ');
if VeryHighVddTestEnable then
  begin
    vdd:=VddMax;powerup(DCDataSheets[TIdataDCTable].v[vdd]);
    mySetupSet(cycletable,TIlofrqlooseACTable,TIlooseDCTable);
 IGet(NRD,      IOH,    Temp_IOH);
 IGet(NRD,      IOL,    Temp_IOL);
 ISet(NRD,      IOH,     DCDataSheets[TIdataDCTable].i[iohstress]);
 ISet(CLKOUT,   IOH,     DCDataSheets[TIdataDCTable].i[iohstress]);
 ISet(LOOSEOUTS,IOH,     DCDataSheets[TIdataDCTable].i[iohstress]);
 ISet(ALLIOS,   IOH,     DCDataSheets[TIdataDCTable].i[iohstress]);
 ISet(NRD,      IOL,     DCDataSheets[TIdataDCTable].i[iolstress]);
 ISet(CLKOUT,   IOL,     DCDataSheets[TIdataDCTable].i[iolstress]);
 ISet(LOOSEOUTS,IOL,     DCDataSheets[TIdataDCTable].i[iolstress]);
 ISet(ALLIOS,   IOL,     DCDataSheets[TIdataDCTable].i[iolstress]);
    Sync(TIlofrqlooseACTable,TIlooseDCTable,force_clkin);
    if failsync or failsclksync or failtclksync then
       begin
         softbin:=VddMax_SyncFail;
         SetSyncSoftbin;
         if (TIScreenPrint) then writeln(' >> SYNC FAILED VDDMAX');
         RestoreLoads;dosync:=save_dosync;if not TIIgnoreFail then goto 100;
       end;
if TimeProgram then
             ProgramTimer('VddMax_Sync ');
    if not patterntest(cycletable,TIlofrqlooseACTable,TIlooseDCTable,FirstPatternName,LastPatternName) then
       begin
         if ( myTestFunc(saram) and myTestFunc(ramb0) and myTestFunc(ramb1) and myTestFunc(ramb2) ) then
           begin
             softbin:=VddMax_FuncFail;
             if (TIScreenPrint) then writeln(' >> VDDMAX FUNCTIONAL FAIL');
           end else
           begin
             softbin:=VddMax_RamFail;
             if (TIScreenPrint) then writeln(' >> VDDMAX RAM FAIL');
           end;
         RestoreLoads;dosync:=save_dosync;if not TIIgnoreFail then goto 100;
       end;
if TimeProgram then
             ProgramTimer('VddMax_Ram ');
    if not myTestFunc(romdump) or not myTestFunc(rom_coupling) or not myTestFunc(extrom) then
       begin
         softbin:=VddMax_RomFail;
         if (TIScreenPrint) then writeln(' >> VDDMAX ROM FAIL');
         RestoreLoads;dosync:=save_dosync;if not TIIgnoreFail then goto 100;
       end;
    if TIScreenPrint then writeln(' PASSED VDDMAX FUNCTIONAL TEST');
  end;
if TimeProgram then
             ProgramTimer('VddMax_Rom ');
if StressEnable then
begin
if PreStressIddqEnable then
 begin
        IddQTest(DCDataSheets[TIdataDCTable].v[CVddIddq2],DCDataSheets[TIdataDCTable].v[DVddIddq2],
                   DCDataSheets[TIdataDCTable].i[IddqFailLeak],1,1);
        if failiddq and IddqScreenEnable then
           begin
             softbin:= PreStress_IddqPowerFail;
             if not TIIgnoreFail then goto 100;
           end;
 end;
if TimeProgram then
             ProgramTimer('PreStress_IddqPower test ');
if PreStressIdle3Enable then
 begin
        Idle3Test(DCDataSheets[TIdataDCTable].v[CVddIdle32],DCDataSheets[TIdataDCTable].v[DVddIdle32],
                     DCDataSheets[TIdataDCTable].i[Idle3FailLeak],1);
        if myTestFunc(sync) then else;
        if failidle3 and Idle3ScreenEnable then
           begin
             softbin:= PreStress_Idle3PowerFail;
             if not TIIgnoreFail then goto 100;
           end;
 end;
if TimeProgram then
             ProgramTimer('PreStress_Idle3Power test ');
 save_dosync:=dosync;
 dosync:=true;
 failstress:=false;
 ModeSet(TesterLockBegin);
 vdd:=VddStress; powerup(DCDataSheets[TIdataDCTable].v[vdd]);
 if TimerStart then else;
 stress_done:=false;
 mySetupSet(cycletable,TIlofrqlooseACTable,TIlooseDCTable);
 IGet(NRD,      IOH,    Temp_IOH);
 IGet(NRD,      IOL,    Temp_IOL);
 ISet(NRD,      IOH,     DCDataSheets[TIdataDCTable].i[iohstress]);
 ISet(CLKOUT,   IOH,     DCDataSheets[TIdataDCTable].i[iohstress]);
 ISet(LOOSEOUTS,IOH,     DCDataSheets[TIdataDCTable].i[iohstress]);
 ISet(ALLIOS,   IOH,     DCDataSheets[TIdataDCTable].i[iohstress]);
 ISet(NRD,      IOL,     DCDataSheets[TIdataDCTable].i[iolstress]);
 ISet(CLKOUT,   IOL,     DCDataSheets[TIdataDCTable].i[iolstress]);
 ISet(LOOSEOUTS,IOL,     DCDataSheets[TIdataDCTable].i[iolstress]);
 ISet(ALLIOS,   IOL,     DCDataSheets[TIdataDCTable].i[iolstress]);
 while (not stress_done) do
  begin
  Sync(TIlofrqlooseACTable,TIlooseDCTable,force_clkin);
  if failsync or failsclksync or failtclksync then
      begin
        if StressScreenEnable then
        begin
          softbin:=Stress_SyncFail;
          SetSyncSoftbin;
        end;
        if (TIScreenPrint) then writeln(' >> SYNC FAILED STRESS');
        failstress:=true;
        stress_done:=true;
      end;
if TimeProgram then
             ProgramTimer('Stress_Sync ');
  if not StressScreenEnable then TestControlAll(NoAbortFail);
     if not patterntest(cycletable,TIlofrqlooseACTable,TIlooseDCTable,FirstPatternName,LastPatternName) then
        begin
          if myTestFunc(saram) then
             begin
               if StressScreenEnable then softbin:=Stress_OtherFuncFail;
               if (TIScreenPrint) then writeln(' >> SPECIFIC FAILED STRESS');
             end else
             begin
               if StressScreenEnable then softbin:=Stress_RamFail;
                if (TIScreenPrint) then writeln(' >> SARAM FAILED STRESS');
             end;
          failstress:=true;
          if StressScreenEnable then stress_done:=true;
         end;
if TimeProgram then
             ProgramTimer('Stress_Func test');
if not myTestFunc(romdump) or not myTestFunc(rom_coupling) or not myTestFunc(extrom) then
        begin
           if StressScreenEnable then softbin:=Stress_RomFail;
           if (TIScreenPrint) then writeln(' >> ROM FAILED STRESS');
           failstress:=true;
           if StressScreenEnable then stress_done:=true;
        end;
     if Process in[G50C18_1,G50C18_2] then
     begin
          stress_time:=TimerStop;
          stress_done:=true;
     end;
       if (TimerRead/1000000 > 0.9) then
          begin
            stress_time:=TimerStop;
            stress_done:=true;
          end;
       if Process in [ G50C21_1,G50C21_2,G50C18_1,G50C18_2] then
          begin
            stress_time:=TimerStop;
            stress_done:=true;
          end;
 end;
if TimeProgram then
             ProgramTimer('Stress_Func test');
 if TIScreenPrint then
   writeln(' STRESS TIME=',stress_time/1000000:2:2,'s');
 TestControlResetAll;
 if TimerStart then else;
 if ( failstress and not TIIgnoreFail ) then
    goto 100
 else
 if (TIScreenPrint and (not failstress)) then writeln(' PASSED STRESS TESTS');
 dosync:=save_dosync;
 RestoreLoads;
end;
if (IddqEnable and StressEnable) then
 begin
                IddQTest(DCDataSheets[TIdataDCTable].v[CVddIddq2],DCDataSheets[TIdataDCTable].v[DVddIddq2],
                           DCDataSheets[TIdataDCTable].i[IddqFailLeak],1,1);
        if LogIddqEnable then LogIddq;
        if failiddq and IddqScreenEnable then
           begin
             if PreStressIddqEnable then
                softbin:= PostStress_IddqPowerFail
             else if lmos_site then
                 begin
                   if (CVdd_iddq_current > DCDataSheets[TIdataDCTable].i[Iddq30uA])
                     then softbin := IddqPowerFail
                   else if (CVdd_iddq_current > DCDataSheets[TIdataDCTable].i[Iddq20uA])
                     then softbin := IddqPowerFail20uA_30uA
                   else if (CVdd_iddq_current > DCDataSheets[TIdataDCTable].i[Iddq12uA])
                     then softbin := IddqPowerFail12uA_20uA
                   else if (CVdd_iddq_current > DCDataSheets[TIdataDCTable].i[Iddq7uA])
                     then softbin := IddqPowerFail7uA_12uA
                   else softbin := IddqPowerFail5uA_7uA;
                       end
              else softbin:= IddqPowerFail;
             if not TIIgnoreFail then goto 100;
           end;
 end;
if TimeProgram then
             ProgramTimer('PostStress_IddqPower ');
   if (Process in [G33C15,G33C19]) then
    begin
      LooseFuncCheck:=true;
      LoosFunc;
      if not TIIgnoreFail then goto 100;
      if (TIScreenPrint and not TIIgnoreFail) then writeln(' PASSED LOOSE FUNCTIONAL AFTER STRESS ');
    end;
 if ( ScanTestEnable and (not RomProtectEnable) ) then
 begin
  vdd:=Vddscan;powerup(DCDataSheets[TIdataDCTable].v[vdd]);
  Sync(TIscanACTable,TIlooseDCTable,force_none);
  if not myPATTERNTEST(cycletable,TIscanACTable,TIlooseDCTable,FirstScanPatternName,LastScanPatternName) then
      begin
        if TIScreenPrint then writeln(' >> FAILED SCAN FLUSH ');
        softbin:= ScanFail;
        if not TIIgnoreFail then goto 100;
      end else
        if TIScreenPrint then writeln(' PASSED SCAN FLUSH ');
  if not myPATTERNTEST(cycletable,TIscanACTable,TIlooseDCTable,jtag_bypass,boundary_scan) then
      begin
        if TIScreenPrint then writeln(' >> FAILED JTAG BOUNDARY_SCAN ' );
        softbin:= BoundaryFail;
        if not TIIgnoreFail then goto 100;
      end else
        if TIScreenPrint then writeln(' PASSED JTAG BOUNDARY_SCAN ' );
 end;
if TimeProgram then
             ProgramTimer('Scan Flush test ');
  if (PllEnable and (romcode='173a5')) then
         powerup(2.67v);
  if (PllEnable and (romcode='17337')) then
         powerup(2.75v);
  if (PllEnable and ((romcode='173a5') or (romcode='17337'))) then
     begin
         Pll(SpecJitter,SpecTP,TIveryhifrqlooseACTable,TIlooseDCTable);
         if failpll then
            begin
              if not accept_bin01_only then
                 softbin:= GoodUnit_PllSpecFail
              else
                 softbin:= Do_not_ship_PllSpecFail;
              Pll(LooseJitter,LooseTP,TIveryhifrqlooseACTable,TIlooseDCTable);
              if failpll then
                 begin
                   failloospll:=true;
                   if TIScreenPrint then write(' >> FAILED LOOSE PLL TEST ');
                   if not accept_bin01_only then
                      softbin:= GoodUnit_PllLoosFail
                   else
                      softbin:= Do_not_ship_PllLoosFail;
                   if not TIIgnoreFail then goto 100;
                 end else if TIScreenPrint then write(' >> FAILED SPEC PLL TEST ');
            end else
              if TIScreenPrint then write(' PASSED PLL weedout TEST ');
         if TIScreenPrint then writeln(PllString:12,' at ',ACDataSheets[TIveryhifrqlooseACTable].t[tper]/1000:7:2,'ns');
      end
  else
   if PllEnable and dopll then
      begin
        vdd:=Vddscan;powerup(DCDataSheets[TIdataDCTable].v[vdd]);
        Pll(LooseJitter,LooseTP,TIhifrqlooseACTable,TIlooseDCTable);
          if failpll then
             begin
               softbin:= ProbePllFail;
               if TIScreenPrint then writeln(' >> FAILED Loose TEST PLL ');
               if not TIIgnoreFail then goto 100;
             end else
               if TIScreenPrint then writeln(' PASSED TEST PLL ',PllString:12,' at ',ACDataSheets[TIhifrqlooseACTable].t[tper]/1000:7:2,'ns');
        end;
if TimeProgram then
             ProgramTimer('PLL  test ');
if ( VeryLowVddScanTestEnable and (not RomProtectEnable) ) then
 begin
  vdd:=VddMin;powerup(DCDataSheets[TIdataDCTable].v[vdd]);
  Sync(TIscanACTable,TIlooseDCTable,force_none);
  if not myPATTERNTEST(cycletable,TIscanACTable,TIlooseDCTable,FirstScanPatternName,LastScanPatternName) then
      begin
        if TIScreenPrint then writeln(' >> FAILED SCAN FLUSH ');
        softbin:= VddMinScanFail;
        if not TIIgnoreFail then goto 100;
      end else
        if TIScreenPrint then writeln(' PASSED SCAN FLUSH ');
 end;
if TimeProgram then
             ProgramTimer('VeryLowVddScanTest ');
if (Idle3Enable and StressEnable) then
 begin
        Idle3Test(DCDataSheets[TIdataDCTable].v[CVddIdle32],DCDataSheets[TIdataDCTable].v[DVddIdle32],
                 DCDataSheets[TIdataDCTable].i[Idle3FailLeak],1);
        if myTestFunc(sync) then else;
        if failidle3 and Idle3ScreenEnable then
           begin
             if PreStressIdle3Enable then
                softbin:= PostStress_Idle3PowerFail
             else if lmos_site then
                 begin
                   if (CVdd_idle3_current > DCDataSheets[TIdataDCTable].i[Iddq30uA])
                     then softbin := Idle3PowerFail
                   else if (CVdd_idle3_current > DCDataSheets[TIdataDCTable].i[Iddq20uA])
                     then softbin := Idle3PowerFail20uA_30uA
                   else if (CVdd_idle3_current > DCDataSheets[TIdataDCTable].i[Iddq12uA])
                     then softbin := Idle3PowerFail12uA_20uA
                   else if (CVdd_idle3_current > DCDataSheets[TIdataDCTable].i[Iddq7uA])
                     then softbin := Idle3PowerFail7uA_12uA
                   else softbin := Idle3PowerFail4uA_7uA;
                  end
             else softbin:= Idle3PowerFail;
             if not TIIgnoreFail then goto 100;
           end;
 end;
if TimeProgram then
             ProgramTimer('POST STRESS IDLE3 ');
  vdd:=Vddparam;powerup(DCDataSheets[TIdataDCTable].v[vdd]);
if InleakEnable then
  if not INLEAK(TIinleakTest) then begin
    if (TIScreenPrint) then writeln('>> Failed INPUT LEAKAGE test');
    softbin:= InleakFail;
    if not TIIgnoreFail then goto 100;
  end;
if TimeProgram then
             ProgramTimer('TIinleakTest ');
if TrileakEnable then
  if not TRILKG(TItrilkgTest, TriStatePattern) then begin
    if (TIScreenPrint) then writeln('>> Failed TRISTATE LEAKAGE test');
    softbin:= TrileakFail;
    if not TIIgnoreFail then goto 100;
    end;
if TimeProgram then
             ProgramTimer('TItrilkgTest ');
  if PMUInleakEnable then
    begin
      if not PMUINLEAK(TIinleakTest,INUPSpmuinleakhiTest,TRSTpmuinleakhiTest) then begin
         if (TIScreenPrint) then writeln('>> Failed PMU INPUT LEAKAGE test');
         softbin:= PmuInleakFail;
         if not TIIgnoreFail then goto 100;
       end else
         if (TIScreenPrint) then writeln('Passed PMU INPUT LEAKAGE test');
    end;
if TimeProgram then
             ProgramTimer('PMUINLEAK ');
  if PMUTrileakEnable then
    begin
      if not PMUTRILKG(TItrilkgTest,IOUPSpmutrilkgloTest,IOUPSpmutrilkghiTest,TriStatePattern) then begin
         if (TIScreenPrint) then writeln('>> Failed PMU TRISTATE LEAKAGE test');
         softbin:= PmuTrileakFail;
         if not TIIgnoreFail then goto 100;
       end else
         if (TIScreenPrint) then writeln('Passed PMU TRISTATE LEAKAGE test');
    end;
if TimeProgram then
             ProgramTimer('PMUTRILKG ');
  if PTULeakEnable then
    begin
      if not PTULeak then begin
        if (TIScreenPrint) then writeln('>> Failed PTULeakage tests');
        softbin:= PTULeakFail;
        if not TIIgnoreFail then goto 100;
      end else if (TIScreenPrint) then writeln('Passed PTULeakage tests');
    end;
if TimeProgram then
             ProgramTimer('PTULeak ');
 if RamRetentionTestEnable then
   begin
     vdd:=Vddretention;
     RamRetention(DCDataSheets[TIdataDCTable].v[vdd],DCDataSheets[TIdataDCTable].v[vdd],delayretention);
      if  failramretention then begin
         if TIScreenPrint then writeln(' >> FAILED RAM RETENTION TEST AT ',
                                 (DCDataSheets[TIdataDCTable].v[vdd])/1000000:4:2,' v delay=',delayretention);
         softbin:= RamRetentionFail;
         if not TIIgnoreFail then goto 100;
       end else if TIScreenPrint then writeln(' PASSED RAM RETENTION TEST AT ',
                                        (DCDataSheets[TIdataDCTable].v[vdd])/1000000:4:2,' v delay=',delayretention);
  end;
if TimeProgram then
             ProgramTimer('ram retention test ');
if VeryHighVddHighFreqTestEnable then
  begin
  vdd:=VddMaxHighFreq;powerup(DCDataSheets[TIdataDCTable].v[vdd]);
  Sync(TIveryhifrqlooseACTable,TIlooseDCTable,force_clkin);
  if failsync or failsclksync then
      begin
        softbin:=VddMaxHighFreq_SyncFail;
        if (TIScreenPrint) then writeln(' >> SYNC FAILED VERY HIGH VDD HIGH FREQ');
        if not TIIgnoreFail then goto 100;
      end;
if TimeProgram then
             ProgramTimer('VddMaxHighFreq_Sync ');
  if UseLongPattern then begin
       if not myTestFunc(generic_long) then
            begin
                softbin:=VddMaxHighFreq_FuncFail;
                if (TIScreenPrint) then writeln(' >> GENERIC FAILED VERY HIGH VDD HIGH FREQ');
                if not TIIgnoreFail then goto 100;
            end;
       end else
       if not patterntest(cycletable,TIveryhifrqlooseACTable,TIlooseDCTable,FirstPatternName,LastPatternName) then
            begin
                softbin:=VddMaxHighFreq_FuncFail;
                if (TIScreenPrint) then writeln(' >> FUNC FAILED VERY HIGH VDD HIGH FREQ');
                if not TIIgnoreFail then goto 100;
            end;
if TimeProgram then
             ProgramTimer('VddMaxHighFreq_Func ');
  if not myTestFunc(romdump) or not myTestFunc(rom_coupling) or not myTestFunc(extrom) then
            begin
                softbin:=VddMaxHighFreq_RomFail;
                if (TIScreenPrint) then writeln(' >> ROM FAILED VERY HIGH VDD HIGH FREQ');
                if not TIIgnoreFail then goto 100;
            end;
if TimeProgram then
             ProgramTimer('VddMaxHighFreq_Rom ');
  if UseLongPattern then begin
       if not patterntest(cycletable,TIveryhifrqlooseACTable,TIlooseDCTable,specific_long,specific_long) then
            begin
                if myTestFunc(saram) then
                    begin
                        softbin:=VddMaxHighFreq_OtherFuncFail;
                        if (TIScreenPrint) then writeln(' >> SPECIFIC FAILED VERY HIGH VDD HIGH FREQ');
                    end else
                    begin
                        softbin:=VddMaxHighFreq_RamFail;
                        if (TIScreenPrint) then writeln(' >> SARAM FAILED VERY HIGH AND NOMINAL VDD');
                    end;
                 if not TIIgnoreFail then goto 100;
            end;
       end;
       if (TIScreenPrint and not TIIgnoreFail) then writeln(' PASSED VERY HIGH VDD HIGH FREQ TESTS');
 end;
if TimeProgram then
             ProgramTimer('VddMaxHighFreq_Ram ');
if LevelTestEnable then
  for vdd:=Vddmin to Vddmax do begin
    powerup(DCDataSheets[TIdataDCTable].v[vdd]);
    if RomProtectEnable or (Device in [c52..c52_4,c53sx,c53sx_4,c511..c511a]) then
       begin
          Sync(TIlofrqlooseACTable,levelsdctable,force_clkin);
          if not myTestFunc(ints) or not myTestFunc(hold_selfc5x) or not myTestFunc(ready_selfc5x) or
             not myTestFunc(sport4) or not myTestFunc(tsport4) then
             begin
                if TIScreenPrint then writeln(' >> FAILED SPEC OUTPUT LEVELS ' );
                softbin:= LevelFail;
                if not TIIgnoreFail then goto 100;
          end else
             if TIScreenPrint then writeln(' PASSED SPEC OUTPUT LEVELS ' );
       end
    else
       begin
          Sync(TIscanACTable,levelsdctable,force_none);
          if not myTestFunc(boundary_scan) then
             begin
                if TIScreenPrint then writeln(' >> FAILED SPEC OUTPUT LEVELS ' );
                softbin:= LevelFail;
                if not TIIgnoreFail then goto 100;
          end else
             if TIScreenPrint then writeln(' PASSED SPEC OUTPUT LEVELS ' );
    end;
  end;
if TimeProgram then
             ProgramTimer('Spec levels test ');
 if OscillatorTestEnable then
   begin
     vdd:=Vddnom;powerup(DCDataSheets[TIdataDCTable].v[vdd]);
     mySetupSet(cycletable,TIlofrqlooseACTable,TIlevelsHVDCTable);
     OriginSet(orgclkin,0ns);
     mySetupSet(cycletable,TIlofrqlooseACTable,TIlevelsHVDCTable);
     VSet(CLKMOD1,VIL,DCDataSheets[TIdataDCTable].v[vdd]-50mv);
     VSet(CLKMOD1,VIH,DCDataSheets[TIdataDCTable].v[vdd]-50mv);
     VSet(CLKMOD2,VIL,DCDataSheets[TIdataDCTable].v[vdd]-50mv);
     VSet(CLKMOD2,VIH,DCDataSheets[TIdataDCTable].v[vdd]-50mv);
     PinStrobeMaskReset;
     if not myTestFunc(int_osc) then
       begin
         if TIScreenPrint then writeln(' >> FAILED INTERNAL OSCILLATOR TEST');
         softbin:= OscillatorFail;
         if not TIIgnoreFail then goto 100;
       end else if TIScreenPrint then writeln(' PASSED INTERNAL OSCILLATOR TEST');
  end;
if TimeProgram then
             ProgramTimer('OscillatorTest ');
if PowerEnable then
 begin
 if miho_site then
   begin
    dummy_TIMeasure:=TIMeasure;
    TIMeasure:=true;
    vdd:=Vddnom;powerup(DCDataSheets[TIdataDCTable].v[vdd]);
    if ( (abs( (50*1000) - ACDataSheets[TIsearchlooseACTable].t[tper]) ) >= 1ns )
      then ss(50);
   end
 else
   begin
    vdd:=Vddmax;powerup(DCDataSheets[TIdataDCTable].v[vdd]);
    if ((abs(ACDataSheets[TIhifrqlooseACTable].t[tper]-ACDataSheets[TIsearchlooseACTable].t[tper])) >= 1ns )
      then ss( (ACDataSheets[TIhifrqlooseACTable].t[tper] + 500ps ) div 1ns );
   end;
   Sync(TIsearchlooseACTable,TIpowerDCTable,force_clkin);
   if TIDebug and TIScreenPrint then
       if not myTestFunc(powermax) then writeln('Fail powermax pattern ');
   if TIScreenPrint then write(' PowerMax ');
   if not (POWER(TIpowerTest,PowerMaxTest,supplylimitslist1)) and PowerScreenEnable then
           begin
             softbin:= PowerMaxFail;
             if not TIIgnoreFail then
               begin
                 if miho_site then TIMeasure:=dummy_TIMeasure;
                 goto 100;
               end;
           end;
   SupplyResult1:=TestResultPOWERGet(CVdd);
   SupplyResult2:=TestResultPOWERGet(DVdd);
if miho_site then
  begin
   powerconsumption_cvdd_max:=SupplyResult1;
   powerconsumption_dvdd_max:=SupplyResult2;
  end;
   if TIScreenPrint and TIMeasure then
       writeln('PowerMax Measure is      :    ',SupplyResult1/1000:7:2,' ma','   ',SupplyResult2/1000:7:2,' ma');
   if ctipdllog then
        begin
          CTIstring := 'CPWM';
          CTIPDLDataLogVariable(CTIstring,mA,SupplyResult1);
          CTIstring := 'DPWM';
          CTIPDLDataLogVariable(CTIstring,mA,SupplyResult2);
        end;
   if TIDebug and TIScreenPrint then
       if not myTestFunc(powertyp) then writeln('Fail powertyp pattern ');
   if TIScreenPrint then write(' PowerTyp ');
   if not (POWER(TIpowerTest,PowerTypTest,supplylimitslist2)) and PowerScreenEnable then
           begin
             softbin:= PowerTypFail;
             if not TIIgnoreFail then
               begin
                 if miho_site then TIMeasure:=dummy_TIMeasure;
                 goto 100;
               end;
           end;
   SupplyResult1:=TestResultPOWERGet(CVdd);
   SupplyResult2:=TestResultPOWERGet(DVdd);
if miho_site then
  begin
    powerconsumption_cvdd_typ:=SupplyResult1;
    powerconsumption_dvdd_typ:=SupplyResult2;
  end;
   if TIScreenPrint and TIMeasure then
       writeln('PowerTyp Measure is      :    ',SupplyResult1/1000:7:2,' ma','   ',SupplyResult2/1000:7:2,' ma');
   if ctipdllog then
        begin
          CTIstring := 'CPWT';
          CTIPDLDataLogVariable(CTIstring,mA,SupplyResult1);
          CTIstring := 'DPWT';
          CTIPDLDataLogVariable(CTIstring,mA,SupplyResult2);
        end;
   if miho_site then TIMeasure:=dummy_TIMeasure;
 end;
if TimeProgram then
             ProgramTimer('Power consumption test ');
if IdleEnable then
 begin
        idleactable:=TIveryhifrqlooseACTable;
        vdd:=Vddmax;powerup(DCDataSheets[TIdataDCTable].v[vdd]);
        DCBusDisconnectPinList(PMU1Bus);
        DCBusDisconnectPMU(PMU1Bus);
        DCBusDisconnectSupply(PMU1Bus);
        Idle(IdlePattern,idleactable);
        if failidle and TIScreenPrint then writeln(' >> FAILED Idle1');
        if failidle and IdleScreenEnable then
           begin
             softbin:= IdlePowerFail;
             if not TIIgnoreFail then goto 100;
           end;
        Idle(Idle2PllPattern,idleactable);
        if failidle and TIScreenPrint then writeln(' >> FAILED Idle2Pll');
        if failidle and IdleScreenEnable then
           begin
             softbin:= IdlePowerFail;
             if not TIIgnoreFail then goto 100;
           end;
        Idle(Idle2Pattern,idleactable);
        if failidle and TIScreenPrint then writeln(' >> FAILED Idle2');
        if failidle and IdleScreenEnable then
           begin
             softbin:= IdlePowerFail;
             if not TIIgnoreFail then goto 100;
           end;
  end;
if TimeProgram then
             ProgramTimer('Idle Power test ');
if IddqEnable then
  begin
        if (not StressEnable) then
          IddQTest(DCDataSheets[TIdataDCTable].v[CVddIddq2],DCDataSheets[TIdataDCTable].v[DVddIddq2],
                     DCDataSheets[TIdataDCTable].i[IddqFailLeak],1,1);
        if failiddq and IddqScreenEnable then
           begin
             softbin:= IddqPowerFail;
             if not TIIgnoreFail then goto 100;
           end;
       if lmos_site then
          begin
            if (CVdd_iddq_current > DCDataSheets[TIdataDCTable].i[Iddq30uA] ) then
              case softbin of
              VeryGoodUnit : softbin := VeryGoodUnit_30uA_40uA_iddq;
              others : begin end;
              end
            else if (CVdd_iddq_current > DCDataSheets[TIdataDCTable].i[Iddq23uA]) then
              case softbin of
              VeryGoodUnit : softbin := VeryGoodUnit_23uA_30uA_iddq;
              others : begin end;
              end
            else if (CVdd_iddq_current > DCDataSheets[TIdataDCTable].i[Iddq18uA]) then
              case softbin of
              VeryGoodUnit : softbin := VeryGoodUnit_18uA_23uA_iddq;
              others : begin end;
              end
            else if (CVdd_iddq_current > DCDataSheets[TIdataDCTable].i[Iddq13uA]) then
              case softbin of
              VeryGoodUnit : softbin := VeryGoodUnit_13uA_18uA_iddq;
              others : begin end;
              end
            else if (CVdd_iddq_current > DCDataSheets[TIdataDCTable].i[Iddq9uA]) then
              case softbin of
              VeryGoodUnit : softbin := VeryGoodUnit_9uA_13uA_iddq;
              others : begin end;
              end
            else if (CVdd_iddq_current > DCDataSheets[TIdataDCTable].i[Iddq6uA]) then
              case softbin of
              VeryGoodUnit : softbin := VeryGoodUnit_6uA_9uA_iddq;
              others : begin end;
              end
            else if (CVdd_iddq_current > DCDataSheets[TIdataDCTable].i[Iddq4uA]) then
              case softbin of
              VeryGoodUnit : softbin := VeryGoodUnit_4uA_6uA_iddq;
              others : begin end;
              end
            else if (CVdd_iddq_current > DCDataSheets[TIdataDCTable].i[Iddq2uA]) then
              case softbin of
              VeryGoodUnit : softbin := VeryGoodUnit_2uA_4uA_iddq;
              others : begin end;
              end
            else if (CVdd_iddq_current > DCDataSheets[TIdataDCTable].i[Iddq1uA]) then
              case softbin of
              VeryGoodUnit : softbin := VeryGoodUnit_1uA_2uA_iddq;
              others : begin end;
              end
            else if (CVdd_iddq_current > DCDataSheets[TIdataDCTable].i[Iddq500nA]) then
              case softbin of
              VeryGoodUnit : softbin := VeryGoodUnit_500nA_1uA_iddq;
              others : begin end;
              end;
          end
       else
        begin
         if not (CVdd_iddq_current < DCDataSheets[TIdataDCTable].i[IddqLeaky]) then
          begin
            if CVdd_iddq_current < DCDataSheets[TIdataDCTable].i[IddqVeryLeaky] then
              case softbin of
              VeryGoodUnit : softbin:=VeryGoodUnit_Leaky;
              GoodUnit_VeryHiFrqRomFail : if not accept_bin01_only then
                                             softbin:=GoodUnit_VeryHiFrqRomFail_Leaky
                                          else
                                             softbin:=Do_not_ship_VeryHiFrqRomFail_Leaky;
              GoodUnit_VeryHiFrqFuncFail : if not accept_bin01_only then
                                              softbin:=GoodUnit_VeryHiFrqFuncFail_Leaky
                                           else
                                              softbin:=Do_not_ship_VeryHiFrqFuncFail_Leaky;
              others : begin end;
              end
            else begin
              if CVdd_iddq_current < DCDataSheets[TIdataDCTable].i[IddqFailLeak] then
                case softbin of
                VeryGoodUnit : softbin:=VeryGoodUnit_VeryLeaky;
                GoodUnit_VeryHiFrqRomFail  : if not accept_bin01_only then
                                                softbin:=GoodUnit_VeryHiFrqRomFail_VeryLeaky
                                             else
                                                softbin:=Do_not_ship_VeryHiFrqRomFail_VeryLeaky;
                GoodUnit_VeryHiFrqFuncFail : if not accept_bin01_only then
                                                softbin:=GoodUnit_VeryHiFrqFuncFail_VeryLeaky
                                             else
                                                softbin:=Do_not_ship_VeryHiFrqFuncFail_VeryLeaky;
                others : begin end;
                end
              else
                begin
                case softbin of
                VeryGoodUnit : softbin:=VeryGoodUnit_FailLeak;
                GoodUnit_VeryHiFrqRomFail  : if not accept_bin01_only then
                                                softbin:=GoodUnit_VeryHiFrqRomFail_FailLeak
                                             else
                                                softbin:=Do_not_ship_VeryHiFrqRomFail_FailLeak;
                GoodUnit_VeryHiFrqFuncFail : if not accept_bin01_only then
                                                softbin:=GoodUnit_VeryHiFrqFuncFail_FailLeak
                                             else
                                                softbin:=Do_not_ship_VeryHiFrqFuncFail_FailLeak;
                others : begin end;
                end;
                if not TIIgnoreFail then goto 100;
                end;
            end;
          end;
        end;
  end;
if TimeProgram then
             ProgramTimer('iddq test ');
if Idle3Enable then
  begin
        if (not StressEnable) then
          Idle3Test(DCDataSheets[TIdataDCTable].v[CVddIdle32],DCDataSheets[TIdataDCTable].v[DVddIdle32],
                      DCDataSheets[TIdataDCTable].i[Idle3FailLeak],1);
        if failidle3 and Idle3ScreenEnable then
           begin
             softbin:= Idle3PowerFail;
             if not TIIgnoreFail then goto 100;
           end;
       if lmos_site then
          begin
            if (CVdd_idle3_current > DCDataSheets[TIdataDCTable].i[Iddq2uA]) then
              case softbin of
              VeryGoodUnit : softbin := VeryGoodUnit_2uA_4uA_iddq;
              others : begin end;
              end
            else if (CVdd_idle3_current > DCDataSheets[TIdataDCTable].i[Iddq1uA]) then
              case softbin of
              VeryGoodUnit : softbin := VeryGoodUnit_1uA_2uA_iddq;
              others : begin end;
              end
            else if (CVdd_idle3_current > DCDataSheets[TIdataDCTable].i[Iddq500nA]) then
              case softbin of
              VeryGoodUnit : softbin := VeryGoodUnit_500nA_1uA_iddq;
              others : begin end;
              end;
          end
       else
        begin
        if not (CVdd_idle3_current < DCDataSheets[TIdataDCTable].i[Idle3Leaky]) then
          begin
            if CVdd_idle3_current < DCDataSheets[TIdataDCTable].i[Idle3VeryLeaky] then
              case softbin of
              VeryGoodUnit               : softbin:=VeryGoodUnit_Leaky;
              GoodUnit_VeryHiFrqRomFail  : if not accept_bin01_only then
                                              softbin:=GoodUnit_VeryHiFrqRomFail_Leaky
                                           else
                                              softbin:=Do_not_ship_VeryHiFrqRomFail_Leaky;
              GoodUnit_VeryHiFrqFuncFail : if not accept_bin01_only then
                                              softbin:=GoodUnit_VeryHiFrqFuncFail_Leaky
                                           else
                                              softbin:=Do_not_ship_VeryHiFrqFuncFail_Leaky;
              others : begin end;
              end
            else begin
              if CVdd_idle3_current < DCDataSheets[TIdataDCTable].i[Idle3FailLeak] then
                case softbin of
                VeryGoodUnit : softbin:=VeryGoodUnit_VeryLeaky;
                GoodUnit_VeryHiFrqRomFail  : if not accept_bin01_only then
                                                softbin:=GoodUnit_VeryHiFrqRomFail_VeryLeaky
                                             else
                                                softbin:=Do_not_ship_VeryHiFrqRomFail_VeryLeaky;
                GoodUnit_VeryHiFrqFuncFail : if not accept_bin01_only then
                                                softbin:=GoodUnit_VeryHiFrqFuncFail_VeryLeaky
                                             else
                                                softbin:=Do_not_ship_VeryHiFrqFuncFail_VeryLeaky;
                others : begin end;
                end
              else
                begin
                case softbin of
                VeryGoodUnit : softbin:=VeryGoodUnit_FailLeak;
                GoodUnit_VeryHiFrqRomFail  : if not accept_bin01_only then
                                                softbin:=GoodUnit_VeryHiFrqRomFail_FailLeak
                                             else
                                                softbin:=Do_not_ship_VeryHiFrqRomFail_FailLeak;
                GoodUnit_VeryHiFrqFuncFail : if not accept_bin01_only then
                                                softbin:=GoodUnit_VeryHiFrqFuncFail_FailLeak
                                             else
                                                softbin:=Do_not_ship_VeryHiFrqFuncFail_FailLeak;
                others : begin end;
                end;
                if not TIIgnoreFail then goto 100;
                end;
            end;
          end;
       end;
  end;
if IddqLowerVddEnable then
 begin
        IddQTest(DCDataSheets[TIdataDCTable].v[CVddIddq1],DCDataSheets[TIdataDCTable].v[DVddIddq1],
                   DCDataSheets[TIdataDCTable].i[IddqLowerVddFailLeak],0,0);
        if failiddq and IddqLowerVddScreenEnable then
           begin
             softbin:= IddqLowerVddPowerFail;
             if not TIIgnoreFail then goto 100;
           end;
 end;
if Idle3LowerVddEnable then
 begin
        Idle3Test(DCDataSheets[TIdataDCTable].v[CVddIdle31],DCDataSheets[TIdataDCTable].v[DVddIdle31],
                     DCDataSheets[TIdataDCTable].i[Idle3LowerVddFailLeak],0);
        if failidle3 and Idle3LowerVddScreenEnable then
           begin
             softbin:= Idle3LowerVddPowerFail;
             if not TIIgnoreFail then goto 100;
           end;
 end;
if failstress then
  begin
    case softbin of
           GoodUnit_VeryHiFrqRomFail,
           GoodUnit_VeryHiFrqRomFail_Leaky,
           GoodUnit_VeryHiFrqFuncFail,
           GoodUnit_VeryHiFrqFuncFail_Leaky,
           GoodUnit_VeryHiFrqRomFail_VeryLeaky,
           GoodUnit_VeryHiFrqFuncFail_VeryLeaky,
           GoodUnit_VeryHiFrqRomFail_FailLeak,
           GoodUnit_VeryHiFrqFuncFail_FailLeak  : if not accept_bin01_only then
                                                     softbin:=GoodUnit_Stress_FuncFail
                                                  else
                                                     softbin:=Do_not_ship_Stress_FuncFail;
           VeryGoodUnit,
           VeryGoodUnit_Leaky,
           VeryGoodUnit_VeryLeaky,
           VeryGoodUnit_FailLeak                : softbin:=VeryGoodUnit_Stress_FuncFail;
           others                               : begin end;
     end;
  end;
end;
Final,QA,Engineering:
 begin
  if not OPENS(TIopensTest) then begin
    if (TIScreenPrint) then writeln('>> FAILED OPENS test');
    softbin:= OpensFail;
    if not TIIgnoreFail then goto 100;
  end;
if TimeProgram then
             ProgramTimer('OPENS ');
  if ( PinListLength(NCPINS)<>0 ) then
    if not PMUINLEAK(TIinleakTest,NCopensTest,NCopensTest) then begin
       if (TIScreenPrint) then writeln('>> Failed Opens test, ');
       if (TIScreenPrint) then writeln('>> Following pins should be Not Connected :');
       if (TIScreenPrint) then PinListPrint(NCPINS);
       softbin:= OpensFail;
       if not TIIgnoreFail then goto 100;
    end;
if TimeProgram then
             ProgramTimer('PMUINLEAK ');
  if not SHORTS(TIshortsTest) then begin
    if (TIScreenPrint) then writeln('>> FAILED SHORTS test');
    softbin:= ShortsFail;
    if not TIIgnoreFail then goto 100;
  end;
if TimeProgram then
             ProgramTimer('Shorts ');
 if SpeedSortEnable then testactable:=TIveryhifrqACTable else testactable:=TIhifrqACTable;
 vdd:=Vddmin; powerup(DCDataSheets[TIdataDCTable].v[vdd]);
 if c5x_PATTERNTEST(testactable,timingsdctable,FirstPatternName,LastPatternName) then
    begin
      if SpeedSortEnable then
         softbin:=VeryGoodUnit
      else
         if not accept_bin01_only then
            softbin:=GoodUnit
         else
            softbin:=Do_not_ship_unit;
 if not c5x_PATTERNTEST(testactable,timingsdctable,meminout,meminout) then
             begin
                if TIScreenPrint then writeln(' >> FAILED MEMINOUT RAM CORRUPTION TEST ' );
                softbin:= MeminoutFail;
                if not TIIgnoreFail then goto 100;
             end else
             if TIScreenPrint then writeln(' PASSED MEMINOUT RAM CORRUPTION TEST ' );
    end
 else
    begin
      SetSoftBin;
      vdd:=Vddmin;powerup(DCDataSheets[TIdataDCTable].v[vdd]);
      if (testactable=TIveryhifrqACTable) then
        begin
          testactable:=TIhifrqACTable;
          if c5x_PATTERNTEST(testactable,timingsdctable,FirstPatternName,LastPatternName) then
            begin
              if softbin=LoVddVeryHiFrqSyncFail then begin
                 if not accept_bin01_only then
                    softbin:=GoodUnit_LoVddVeryHiFrqSyncFail
                 else
                    softbin:=Do_not_ship_LoVddVeryHiFrqSyncFail;
              end;
              if softbin=LoVddVeryHiFrqSpecSyncFail then begin
                 if not accept_bin01_only then
                    softbin:=GoodUnit_LoVddVeryHiFrqSpecSyncFail
                 else
                    softbin:=Do_not_ship_LoVddVeryHiFrqSpecSyncFail;
              end;
              if softbin=LoVddVeryHiFrqTimingFail then begin
                 if not accept_bin01_only then
                    softbin:=GoodUnit_LoVddVeryHiFrqTimingFail
                 else
                    softbin:=Do_not_ship_LoVddVeryHiFrqTimingFail;
              end;
              if softbin=LoVddVeryHiFrqRamSequenceFail then begin
                 if not accept_bin01_only then
                    softbin:=GoodUnit_LoVddVeryHiFrqRamSequenceFail
                 else
                    softbin:=Do_not_ship_LoVddVeryHiFrqRamSequenceFail;
              end;
              if softbin=LoVddVeryHiFrqRamWalkFail then begin
                 if not accept_bin01_only then
                    softbin:=GoodUnit_LoVddVeryHiFrqRamWalkFail
                 else
                    softbin:=Do_not_ship_LoVddVeryHiFrqRamWalkFail;
              end;
              if softbin=LoVddVeryHiFrqTaAFail then begin
                 if not accept_bin01_only then
                    softbin:=GoodUnit_LoVddVeryHiFrqTaAFail
                 else
                    softbin:=Do_not_ship_LoVddVeryHiFrqTaAFail;
              end;
              if softbin=LoVddVeryHiFrqTiming2Fail then begin
                 if not accept_bin01_only then
                    softbin:=GoodUnit_LoVddVeryHiFrqTiming2Fail
                 else
                    softbin:=Do_not_ship_LoVddVeryHiFrqTiming2Fail;
              end;
              if softbin=LoVddVeryHiFrqRomFail then begin
                 if not accept_bin01_only then
                    softbin:=GoodUnit_LoVddVeryHiFrqRomFail
                 else
                    softbin:=Do_not_ship_LoVddVeryHiFrqRomFail;
              end;
              if softbin=LoVddVeryHiFrqPllFail then begin
                 if not accept_bin01_only then
                    softbin:=GoodUnit_LoVddVeryHiFrqPllFail
                 else
                    softbin:=Do_not_ship_LoVddVeryHiFrqPllFail;
              end;
              if softbin=LoVddVeryHiFrqPllLoosFail then begin
                 if not accept_bin01_only then
                    softbin:=GoodUnit_LoVddVeryHiFrqPllLoosFail
                 else
                    softbin:=Do_not_ship_LoVddVeryHiFrqPllLoosFail;
              end;
            end
          else
            begin
              SetSoftBin;
              testactable:=TIlofrqlooseACTable;
              if TIScreenPrint then writeln(testactable,ACDataSheets[testactable].t[tper]/1000:7:2,'ns');
              Sync(testactable,TIlooseDCTable,force_clkin);
              if failsync or failsclksync then
                begin
                  softbin:=SyncFail;
                  if (TIScreenPrint) then writeln(' >> SYNC FAILED AT LOOSE CONDITION');
                  if not TIIgnoreFail then goto 100;
                end;
              if not patterntest(cycletable,TIlofrqlooseACTable,TIlooseDCTable,FirstPatternName,LastPatternName) then
                begin
                  softbin:=FuncFail;
                  if (TIScreenPrint) then writeln(' >> FUNC FAILED AT LOOSE CONDITION');
                  if not TIIgnoreFail then goto 100;
                end;
              if not myTestFunc(romdump) or not myTestFunc(rom_coupling) or not myTestFunc(extrom) then
                begin
                  softbin:=RomFail;
                  if (TIScreenPrint) then writeln(' >> ROM FAILED AT LOOSE CONDITION code ',romcode);
                  if not TIIgnoreFail then goto 100;
                end;
              if not TIIgnoreFail then goto 100;
            end;
        end
      else
        begin
          testactable:=TIlofrqlooseACTable;
          if TIScreenPrint then writeln(testactable,ACDataSheets[testactable].t[tper]/1000:7:2,'ns');
          Sync(testactable,TIlooseDCTable,force_clkin);
          if failsync or failsclksync then
            begin
              softbin:=SyncFail;
              if (TIScreenPrint) then writeln(' >> SYNC FAILED AT LOOSE CONDITION');
              if not TIIgnoreFail then goto 100;
            end;
          if not patterntest(cycletable,TIlofrqlooseACTable,TIlooseDCTable,FirstPatternName,LastPatternName) then
            begin
              softbin:=FuncFail;
              if (TIScreenPrint) then writeln(' >> FUNC FAILED AT LOOSE CONDITION');
              if not TIIgnoreFail then goto 100;
            end;
          if not myTestFunc(romdump) or not myTestFunc(rom_coupling) or not myTestFunc(extrom) then
            begin
              softbin:=RomFail;
              if (TIScreenPrint) then writeln(' >> ROM FAILED AT LOOSE CONDITION code ',romcode);
              if not TIIgnoreFail then goto 100;
            end;
        if not TIIgnoreFail then goto 100;
        end;
  end;
if TimeProgram then
             ProgramTimer('SPEC BOX HIGH FREQ/LOW VOLTAGE ');
if LevelTestEnable then
  begin
    vdd:=Vddmin;
    powerup(DCDataSheets[TIdataDCTable].v[vdd]);
    if RomProtectEnable or (Device in [c52..c52_4,c53sx,c53sx_4,c511..c511a]) then
       begin
          Sync(TIlofrqlooseACTable,levelsdctable,force_clkin);
          if not myTestFunc(ints) or not myTestFunc(hold_selfc5x) or not myTestFunc(ready_selfc5x) or
             not myTestFunc(sport4) or not myTestFunc(tsport4) then
             begin
                if TIScreenPrint then writeln(' >> FAILED SPEC OUTPUT LEVELS ' );
                softbin:= LevelFail;
                if not TIIgnoreFail then goto 100;
             end else
             if TIScreenPrint then writeln(' PASSED SPEC OUTPUT LEVELS ' );
       end
    else
       begin
          Sync(TIscanACTable,levelsdctable,force_none);
          if not myTestFunc(boundary_scan) then
             begin
                if TIScreenPrint then writeln(' >> FAILED SPEC OUTPUT LEVELS ' );
                softbin:= LevelFail;
                if not TIIgnoreFail then goto 100;
          end else
             if TIScreenPrint then writeln(' PASSED SPEC OUTPUT LEVELS ' );
    end;
  end;
if TimeProgram then
             ProgramTimer('Spec Levels ');
if StressEnable then
begin
if PreStressIddqEnable then
  begin
        IddQTest(DCDataSheets[TIdataDCTable].v[CVddIddq2],DCDataSheets[TIdataDCTable].v[DVddIddq2],
                   DCDataSheets[TIdataDCTable].i[IddqFailLeak],1,1);
        if failiddq and IddqScreenEnable then
           begin
             softbin:= PreStress_IddqPowerFail;
             if not TIIgnoreFail then goto 100;
           end;
   end;
if TimeProgram then
             ProgramTimer('PreStress_IddqPower ');
if PreStressIdle3Enable then
 begin
        Idle3QTest(DCDataSheets[TIdataDCTable].v[CVddIdle32],DCDataSheets[TIdataDCTable].v[DVddIdle32],
                 DCDataSheets[TIdataDCTable].i[Idle3FailLeak],1,1);
        if failidle3 and Idle3ScreenEnable then
           begin
             softbin:= PreStress_Idle3PowerFail;
             if not TIIgnoreFail then goto 100;
           end;
 end;
if TimeProgram then
             ProgramTimer('PreStress_Idle3Power ');
 save_dosync:=dosync;
 dosync:=true;
 failstress:=false;
 ModeSet(TesterLockBegin);
 vdd:=VddStress; powerup(DCDataSheets[TIdataDCTable].v[vdd]);
 if TimerStart then else;
 stress_done:=false;
 mySetupSet(cycletable,TIlofrqlooseACTable,TIlooseDCTable);
 IGet(NRD,      IOH,    Temp_IOH);
 IGet(NRD,      IOL,    Temp_IOL);
 ISet(NRD,      IOH,     DCDataSheets[TIdataDCTable].i[iohstress]);
 ISet(CLKOUT,   IOH,     DCDataSheets[TIdataDCTable].i[iohstress]);
 ISet(LOOSEOUTS,IOH,     DCDataSheets[TIdataDCTable].i[iohstress]);
 ISet(ALLIOS,   IOH,     DCDataSheets[TIdataDCTable].i[iohstress]);
 while (not stress_done) do
  begin
  Sync(TIlofrqlooseACTable,TIlooseDCTable,force_clkin);
  if failsync or failsclksync or failtclksync then
      begin
        if StressScreenEnable then
        begin
          softbin:=Stress_SyncFail;
          SetSyncSoftbin;
        end;
        if (TIScreenPrint) then writeln(' >> SYNC FAILED STRESS');
        if StressScreenEnable and (not TIIgnoreFail) then begin RestoreLoads;goto 100;end;
      end;
  if not StressScreenEnable then TestControlAll(NoAbortFail);
       if UseLongPattern then
          begin
          if not myTestFunc(generic_long) then
               begin
                   if (TIScreenPrint) then writeln(' >> GENERIC FAILED STRESS');
                   if StressScreenEnable then softbin:=Stress_FuncFail;
                   failstress:=true;
                   TestControlAll(NoAbortFail);
               end;
          if not patterntest(cycletable,TIlofrqlooseACTable,TIlooseDCTable,specific_long,specific_long) then
               begin
                   if myTestFunc(saram) then
                       begin
                           if StressScreenEnable then softbin:=Stress_OtherFuncFail;
                           if (TIScreenPrint) then writeln(' >> SPECIFIC FAILED STRESS');
                       end else
                       begin
                           if StressScreenEnable then softbin:=Stress_RamFail;
                           if (TIScreenPrint) then writeln(' >> SARAM FAILED STRESS');
                       end;
                   failstress:=true;
                   TestControlAll(NoAbortFail);
               end;
       end else
       if not patterntest(cycletable,TIlofrqlooseACTable,TIlooseDCTable,FirstPatternName,LastPatternName) then
            begin
                if (TIScreenPrint) then writeln(' >> FUNC FAILED STRESS');
                if StressScreenEnable then softbin:=Stress_FuncFail;
                failstress:=true;
                TestControlAll(NoAbortFail);
            end;
       if not myTestFunc(romdump) or not myTestFunc(rom_coupling) or not myTestFunc(extrom) then
            begin
                if StressScreenEnable then softbin:=Stress_RomFail;
                if (TIScreenPrint) then writeln(' >> ROM FAILED STRESS');
                failstress:=true;
                TestControlAll(NoAbortFail);
            end;
     if Process in [G50C18_1,G50C18_2] then
     begin
          stress_time:=TimerStop;
          stress_done:=true;
     end;
      if (TimerRead/1000000 > 0.9) then
         stress_done:=true;
      if ((TIScreenPrint and (not TIIgnoreFail)) or TIPrintTimings) and stress_done  then
          begin
             writeln(' STRESS TIME=',TimerStop/1000000:2:2,'s');
          end;
    TestControlResetAll;
 end;
 if (failstress and not TIIgnoreFail and StressScreenEnable) then
    goto 100
 else
 if (TIScreenPrint and not TIIgnoreFail and not StressScreenEnable and not failstress) then writeln(' PASSED STRESS TESTS');
 dosync:=save_dosync;
 RestoreLoads;
if TimeProgram then
             ProgramTimer('Stress test ');
 if failstress then
    begin
       vdd:=Vddnom;powerup(DCDataSheets[TIdataDCTable].v[vdd]);
       Sync(TIlofrqlooseACTable,TIlooseDCTable,force_clkin);
       if failsync or failsclksync or failtclksync then
          begin
            if (TIScreenPrint) then writeln(' SYNC FAILED 5v AFTER FAILING STRESS');
            if not TIIgnoreFail then goto 100;
          end;
       if not patterntest(cycletable,TIlofrqlooseACTable,TIlooseDCTable,FirstPatternName,LastPatternName) then
            begin
                if (TIScreenPrint) then writeln(' >> FUNC FAILED 5V AFTER FAILING STRESS');
                if not TIIgnoreFail then goto 100;
            end;
       if not myTestFunc(romdump) or not myTestFunc(rom_coupling) or not myTestFunc(extrom) then
            begin
                if (TIScreenPrint) then writeln(' >> ROM FAILED 5V');
                if not TIIgnoreFail then goto 100;
            end;
       if not accept_bin01_only then
          softbin:=GoodUnit_StressVddFail
       else
          softbin:=Do_not_ship_StressVddFail;
       if (TIScreenPrint and not TIIgnoreFail) then writeln(' PASSED 5V TESTS AFTER FAILING STRESS');
    end;
if TimeProgram then
             ProgramTimer('POST-STRESS LOOSE FUNCTIONAL TEST ');
if IddqEnable then
 begin
        IddQTest(DCDataSheets[TIdataDCTable].v[CVddIddq2],DCDataSheets[TIdataDCTable].v[DVddIddq2],
                   DCDataSheets[TIdataDCTable].i[IddqFailLeak],1,1);
        if LogIddqEnable then LogIddq;
        if failiddq and IddqScreenEnable then
           begin
             if PreStressIddqEnable then
                softbin:= PostStress_IddqPowerFail
             else softbin:= IddqPowerFail;
             if not TIIgnoreFail then goto 100;
           end;
 end;
if TimeProgram then
             ProgramTimer('POST STRESS IDDQ TEST ');
if Idle3Enable then
 begin
        Idle3QTest(DCDataSheets[TIdataDCTable].v[CVddIdle32],DCDataSheets[TIdataDCTable].v[DVddIdle32],
                 DCDataSheets[TIdataDCTable].i[Idle3FailLeak],1,1);
        if failidle3 and Idle3ScreenEnable then
           begin
             if PreStressIdle3Enable then
                softbin:= PostStress_Idle3PowerFail
             else softbin:= Idle3PowerFail;
             if not TIIgnoreFail then goto 100;
           end;
 end;
end;
if TimeProgram then
             ProgramTimer('POST STRESS IDLE3 TEST ');
13:
if VeryLowVddTestEnable then
  begin
  vdd:=VddMin;powerup(DCDataSheets[TIdataDCTable].v[vdd]);
  Sync(TIveryhifrqlooseACTable,TIlooseDCTable,force_clkin);
  if failsync or failsclksync then
      begin
        if (TIScreenPrint) then writeln(' >> FAILED SYNC');
        softbin:=VddMin_SyncFail;
        if not TIIgnoreFail then goto 100;
      end;
  if not patterntest(cycletable,TIhifrqlooseACTable,TIlooseDCTable,FirstPatternName,LastPatternName) then
      begin
        if not dosync then
          begin
            dosync:=true;
            goto 13;
          end;
        if (TIScreenPrint) then writeln(' >> FAILED FUNC ');
          softbin:=VddMin_FuncFail;
          if not TIIgnoreFail then goto 100;
      end;
  if not myTestFunc(ext_dma_all) then
      begin
        if not dosync then begin
           dosync:=true;
           goto 13;
        end;
        if (TIScreenPrint) then writeln(' >> FAILED EXT_DMA_ALL ');
        softbin:=VddMin_RamFail;
        if not TIIgnoreFail then goto 100;
      end;
  if not myTestFunc(romdump) or not myTestFunc(rom_coupling) or not myTestFunc(extrom) then
      begin
        if not dosync then begin
           dosync:=true;
           goto 13;
        end;
        if (TIScreenPrint) then writeln(' >> FAILED ROMDUMP ');
        softbin:=VddMin_RomFail;
        if not TIIgnoreFail then goto 100;
      end else if (TIScreenPrint and not TIIgnoreFail) then writeln(' PASSED VERY LOW VDD TESTS');
end;
if TimeProgram then
             ProgramTimer('VERY LOW VDD VERYHIGH FREQ test ');
if VeryLowVddQGTestEnable then
  begin
    if ( (romcode='37362') or (romcode='37368') or  ( romcode='373c3') ) then begin
        if quickgentest( ((ACDataSheets[TIveryhifrqlooseACTable].t[tper] + 500ps) div 1ns),
                           DCDataSheets[TIdataDCTable].v[VddMin], force_clkin2, quickgen1,quickgen6) then else;
      end;
    if (Device=c51sx) then begin
      if quickgentest( ((ACDataSheets[TIhifrqlooseACTable].t[tper] + 500ps) div 1ns),
                         DCDataSheets[TIdataDCTable].v[VddMin], force_clkin2, quickgen1,quickgen6) then else;
      end;
    if failquickgen then
      begin
        if TIScreenPrint then writeln(' >> FAILED QUICKGEN ');
        softbin:=VddMin_OtherFuncFail;
        if not TIIgnoreFail then goto 100;
      end else if TIScreenPrint then writeln(' PASSED QUICKGEN');
  end;
if TimeProgram then
             ProgramTimer('VERY LOW VDD VERYHIGH FREQ QUICK GEN TEST ');
 if OscillatorTestEnable then
   begin
     vdd:=Vddnom;powerup(DCDataSheets[TIdataDCTable].v[vdd]);
     mySetupSet(cycletable,TIlofrqlooseACTable,TIlevelsHVDCTable);
     OriginSet(orgclkin,0ns);
     mySetupSet(cycletable,TIlofrqlooseACTable,TIlevelsHVDCTable);
     VSet(CLKMOD1,VIL,DCDataSheets[TIdataDCTable].v[vdd]-50mv);
     VSet(CLKMOD1,VIH,DCDataSheets[TIdataDCTable].v[vdd]-50mv);
     VSet(CLKMOD2,VIL,DCDataSheets[TIdataDCTable].v[vdd]-50mv);
     VSet(CLKMOD2,VIH,DCDataSheets[TIdataDCTable].v[vdd]-50mv);
     PinStrobeMaskReset;
     if not myTestFunc(int_osc) then
       begin
         if TIScreenPrint then writeln(' >> FAILED INTERNAL OSCILLATOR TEST');
         softbin:= OscillatorFail;
         if not TIIgnoreFail then goto 100;
       end else if TIScreenPrint then writeln(' PASSED INTERNAL OSCILLATOR TEST');
  end;
if TimeProgram then
             ProgramTimer('Internal oscillator ');
 if RamRetentionTestEnable then
   begin
     vdd:=Vddretention;
     RamRetention(DCDataSheets[TIdataDCTable].v[vdd],DCDataSheets[TIdataDCTable].v[vdd],delayretention);
     if failramretention then
       begin
         if TIScreenPrint then writeln(' >> FAILED RAM RETENTION TEST AT ',
                                 (DCDataSheets[TIdataDCTable].v[vdd])/1000000:4:2,' v delay=',delayretention);
         softbin:= RamRetentionFail;
         if not TIIgnoreFail then goto 100;
       end else if TIScreenPrint then writeln(' PASSED RAM RETENTION TEST AT ',
                                        (DCDataSheets[TIdataDCTable].v[vdd])/1000000:4:2,' v delay=',delayretention);
  end;
if TimeProgram then
             ProgramTimer('ram retention test ');
if PowerEnable then
 begin
if miho_site then
  begin
    dummy_TIMeasure:=TIMeasure;
    TIMeasure:=true;
    vdd:=Vddnom;powerup(DCDataSheets[TIdataDCTable].v[vdd]);
    if ( (abs( (50*1000) - ACDataSheets[TIsearchlooseACTable].t[tper] ) ) > 1ns ) then ss(50);
  end else
  begin
    vdd:=Vddmax;powerup(DCDataSheets[TIdataDCTable].v[vdd]);
    if ((abs( ACDataSheets[TIhifrqlooseACTable].t[tper]-ACDataSheets[TIsearchlooseACTable].t[tper])) >= 1ns)
      then ss( (ACDataSheets[TIhifrqlooseACTable].t[tper] + 500 ) div 1ns );
  end;
   Sync(TIsearchlooseACTable,TIpowerDCTable,force_clkin);
   if TIDebug and TIScreenPrint then
       if not myTestFunc(powermax) then writeln('Fail powermax pattern ');
   if TIScreenPrint then write(' PowerMax ');
   if not (POWER(TIpowerTest,PowerMaxTest,supplylimitslist1)) and PowerScreenEnable then
           begin
             softbin:= PowerMaxFail;
             if not TIIgnoreFail then
               begin
                 if miho_site then TIMeasure:=dummy_TIMeasure;
                 goto 100;
               end;
           end;
   SupplyResult1:=TestResultPOWERGet(CVdd);
   SupplyResult2:=TestResultPOWERGet(DVdd);
if miho_site then
  begin
   powerconsumption_cvdd_max:=SupplyResult1;
   powerconsumption_dvdd_max:=SupplyResult2;
  end;
   if TIScreenPrint and TIMeasure then
       writeln('PowerMax Measure is      :    ',SupplyResult1/1000:7:2,' ma','   ',SupplyResult2/1000:7:2,' ma');
   if ctipdllog then
        begin
          CTIstring := 'CPWM';
          CTIPDLDataLogVariable(CTIstring,mA,SupplyResult1);
          CTIstring := 'DPWM';
          CTIPDLDataLogVariable(CTIstring,mA,SupplyResult2);
        end;
   if TIDebug and TIScreenPrint then
       if not myTestFunc(powertyp) then writeln('Fail powertyp pattern ');
   if TIScreenPrint then write(' PowerTyp ');
   if not (POWER(TIpowerTest,PowerTypTest,supplylimitslist2)) and PowerScreenEnable then
           begin
             softbin:= PowerTypFail;
             if not TIIgnoreFail then
               begin
                 if miho_site then TIMeasure:=dummy_TIMeasure;
                 goto 100;
               end;
           end;
   SupplyResult1:=TestResultPOWERGet(CVdd);
   SupplyResult2:=TestResultPOWERGet(DVdd);
if miho_site then
  begin
    powerconsumption_cvdd_typ:=SupplyResult1;
    powerconsumption_dvdd_typ:=SupplyResult2;
  end;
   if TIScreenPrint and TIMeasure then
       writeln('PowerTyp Measure is      :    ',SupplyResult1/1000:7:2,' ma','   ',SupplyResult2/1000:7:2,' ma');
   if ctipdllog then
        begin
          CTIstring := 'CPWT';
          CTIPDLDataLogVariable(CTIstring,mA,SupplyResult1);
          CTIstring := 'DPWT';
          CTIPDLDataLogVariable(CTIstring,mA,SupplyResult2);
        end;
   if miho_site then TIMeasure:=dummy_TIMeasure;
 end;
if TimeProgram then
             ProgramTimer('POWER CONSUMPTION TEST');
if ( ScanTestEnable and (not RomProtectEnable) ) then
 begin
  vdd:=Vddscan;powerup(DCDataSheets[TIdataDCTable].v[vdd]);
  Sync(TIscanACTable,TIlooseDCTable,force_none);
  if not myPATTERNTEST(cycletable,TIscanACTable,TIlooseDCTable,FirstScanPatternName,LastScanPatternName) then
      begin
        if TIScreenPrint then writeln(' >> FAILED SCAN FLUSH ');
        softbin:= ScanFail;
        if not TIIgnoreFail then goto 100;
      end else
        if TIScreenPrint then writeln(' PASSED SCAN FLUSH ');
  if not myPATTERNTEST(cycletable,TIscanACTable,TIlooseDCTable,jtag_bypass,boundary_scan) then
      begin
        if TIScreenPrint then writeln(' >> FAILED JTAG BOUNDARY_SCAN ' );
        softbin:= BoundaryFail;
        if not TIIgnoreFail then goto 100;
      end else
        if TIScreenPrint then writeln(' PASSED JTAG BOUNDARY_SCAN ' );
 end;
if ( VeryLowVddScanTestEnable and (not RomProtectEnable) ) then
 begin
  vdd:=VddMin;powerup(DCDataSheets[TIdataDCTable].v[vdd]);
  Sync(TIscanACTable,TIlooseDCTable,force_none);
  if not myPATTERNTEST(cycletable,TIscanACTable,TIlooseDCTable,FirstScanPatternName,LastScanPatternName) then
      begin
        if TIScreenPrint then writeln(' >> FAILED SCAN FLUSH ');
        softbin:= VddMinScanFail;
        if not TIIgnoreFail then goto 100;
      end else
        if TIScreenPrint then writeln(' PASSED SCAN FLUSH ');
 end;
if TimeProgram then
             ProgramTimer('SCAN / JTAG BOUNDARY SCAN ');
if SpeedSortEnable and (softbin=VeryGoodUnit) then testactable:=TIveryhifrqACTable else testactable:=TIhifrqACTable;
vdd:=Vddmax;powerup(DCDataSheets[TIdataDCTable].v[vdd]);
if not c5x_PATTERNTEST(testactable,timingsdctable,meminout,meminout) then
     begin
       if TIScreenPrint then writeln(' >> FAILED MEMINOUT RAM CORRUPTION TEST Hi Vdd ' );
       softbin:= MeminoutFail;
       if not TIIgnoreFail then goto 100;
     end else
      if TIScreenPrint then writeln(' PASSED MEMINOUT RAM CORRUPTION TEST ' );
if not c5x_PATTERNTEST(testactable,timingsdctable,FirstPatternName,LastPatternName) then
  begin
    if (softbin in [VeryGoodUnit, GoodUnit, Do_not_ship_unit]) then
      begin
        SetSoftBin;
        if (testactable=TIveryhifrqACTable) then
          begin
            testactable:=TIhifrqACTable;
            if c5x_PATTERNTEST(testactable,timingsdctable,FirstPatternName,LastPatternName) then
              begin
                if softbin=HiVddVeryHiFrqSyncFail then begin
                   if not accept_bin01_only then
                      softbin:=GoodUnit_HiVddVeryHiFrqSyncFail
                   else
                      softbin:=Do_not_ship_HiVddVeryHiFrqSyncFail;
                end;
                if softbin=HiVddVeryHiFrqSpecSyncFail then begin
                   if not accept_bin01_only then
                      softbin:=GoodUnit_HiVddVeryHiFrqSpecSyncFail
                   else
                      softbin:=Do_not_ship_HiVddVeryHiFrqSpecSyncFail;
                end;
                if softbin=HiVddVeryHiFrqTimingFail then begin
                   if not accept_bin01_only then
                      softbin:=GoodUnit_HiVddVeryHiFrqTimingFail
                   else
                      softbin:=Do_not_ship_HiVddVeryHiFrqTimingFail;
                end;
                if softbin=HiVddVeryHiFrqRamSequenceFail then begin
                   if not accept_bin01_only then
                      softbin:=GoodUnit_HiVddVeryHiFrqRamSequenceFail
                   else
                      softbin:=Do_not_ship_HiVddVeryHiFrqRamSequenceFail;
                end;
                if softbin=HiVddVeryHiFrqRamWalkFail then begin
                   if not accept_bin01_only then
                      softbin:=GoodUnit_HiVddVeryHiFrqRamWalkFail
                   else
                      softbin:=Do_not_ship_HiVddVeryHiFrqRamWalkFail;
                end;
                if softbin=HiVddVeryHiFrqTaAFail then begin
                   if not accept_bin01_only then
                      softbin:=GoodUnit_HiVddVeryHiFrqTaAFail
                   else
                      softbin:=Do_not_ship_HiVddVeryHiFrqTaAFail;
                end;
                if softbin=HiVddVeryHiFrqTiming2Fail then begin
                   if not accept_bin01_only then
                      softbin:=GoodUnit_HiVddVeryHiFrqTiming2Fail
                   else
                      softbin:=Do_not_ship_HiVddVeryHiFrqTiming2Fail;
                end;
                if softbin=HiVddVeryHiFrqRomFail then begin
                   if not accept_bin01_only then
                      softbin:=GoodUnit_HiVddVeryHiFrqRomFail
                   else
                      softbin:=Do_not_ship_HiVddVeryHiFrqRomFail;
                end;
                if softbin=HiVddVeryHiFrqPllFail then begin
                   if not accept_bin01_only then
                      softbin:=GoodUnit_HiVddVeryHiFrqPllFail
                   else
                      softbin:=Do_not_ship_HiVddVeryHiFrqPllFail;
                end;
                if softbin=HiVddVeryHiFrqPllLoosFail then begin
                   if not accept_bin01_only then
                      softbin:=GoodUnit_HiVddVeryHiFrqPllLoosFail
                   else
                      softbin:=Do_not_ship_HiVddVeryHiFrqPllLoosFail;
                end;
              end
            else
              begin
                SetSoftBin;
                if not TIIgnoreFail then goto 100;
              end;
          end
        else
          if not TIIgnoreFail then goto 100;
      end
    else
      begin
        if not (TempSoftBin in [LoVddHiFrqSyncFail..LoVddHiFrqRamWalkFail]) then SetSoftBin;
        if not TIIgnoreFail then goto 100;
      end;
  end;
if TimeProgram then
             ProgramTimer('SPEC BOX HIGH FREQ/HIGH VOLTAGE ');
if LevelTestEnable then
  begin
    vdd:=Vddmax;
    powerup(DCDataSheets[TIdataDCTable].v[vdd]);
    if RomProtectEnable or (Device in [c52..c52_4,c53sx,c53sx_4,c511..c511a]) then
       begin
          Sync(TIlofrqlooseACTable,levelsdctable,force_clkin);
          if not myTestFunc(ints) or not myTestFunc(hold_selfc5x) or not myTestFunc(ready_selfc5x) or
             not myTestFunc(sport4) or not myTestFunc(tsport4) then
             begin
                if TIScreenPrint then writeln(' >> FAILED SPEC OUTPUT LEVELS ' );
                softbin:= LevelFail;
                if not TIIgnoreFail then goto 100;
             end else
             if TIScreenPrint then writeln(' PASSED SPEC OUTPUT LEVELS ' );
       end
    else
       begin
          Sync(TIscanACTable,levelsdctable,force_none);
          if not myTestFunc(boundary_scan) then
             begin
                if TIScreenPrint then writeln(' >> FAILED SPEC OUTPUT LEVELS ' );
                softbin:= LevelFail;
                if not TIIgnoreFail then goto 100;
          end else
             if TIScreenPrint then writeln(' PASSED SPEC OUTPUT LEVELS ' );
    end;
  end;
if TimeProgram then
             ProgramTimer('Output Levels ');
if LowFreqEnable then begin
  testactable:=TIlofrqACTable;
  vdd:=Vddmax;
  if ( ( Process=G1ZSE ) and
       ( (DCDataSheets[TIdataDCTable].v[Vddnom])<>(DCDataSheets[TIdataDCTable].v[VddnomHV]) ) )
     then vdd:=Vddmin;
  powerup(DCDataSheets[TIdataDCTable].v[vdd]);
  if not c5x_PATTERNTEST(testactable,timingsdctable,FirstPatternName,LastPatternName) then
      begin
        SetSoftBin;
        if (not VeryHighVddTestEnable) and (not VeryLowVddTestEnable) and (not StressEnable) then
          begin
            Sync(TIlofrqlooseACTable,TIlooseDCTable,force_clkin);
            if failsync or failsclksync then
               begin
                 softbin:=SyncFail;
                 if (TIScreenPrint) then writeln(' >> SYNC FAILED AT LOOSE CONDITION');
                 if not TIIgnoreFail then goto 100;
               end;
            if not patterntest(cycletable,TIlofrqlooseACTable,TIlooseDCTable,FirstPatternName,LastPatternName) then
               begin
                 softbin:=FuncFail;
                 if (TIScreenPrint) then writeln(' >> FUNC FAILED AT LOOSE CONDITION');
                 if not TIIgnoreFail then goto 100;
               end;
            if not myTestFunc(romdump) or not myTestFunc(rom_coupling) or not myTestFunc(extrom) then
               begin
                 softbin:=RomFail;
                 if (TIScreenPrint) then writeln(' >> ROM FAILED AT LOOSE CONDITION code ',romcode);
                 if not TIIgnoreFail then goto 100;
               end;
          end;
       if not TIIgnoreFail then goto 100;
     end;
end;
if TimeProgram then
             ProgramTimer('SPEC BOX LOW FREQ ');
  if InleakEnable or TrileakEnable or PMUInleakEnable or PMUTrileakEnable or PTULeakEnable then begin
    vdd:=Vddparam;powerup(DCDataSheets[TIdataDCTable].v[vdd]);
  end;
  if InleakEnable then
    begin
    if not INLEAK(TIinleakTest) then begin
      if (TIScreenPrint) then writeln('>> Failed INPUT LEAKAGE test');
      softbin:= InleakFail;
      if not TIIgnoreFail then goto 100;
    end;
  end;
if TimeProgram then
             ProgramTimer('INLEAK test ');
  if TrileakEnable then
    begin
    if not TRILKG(TItrilkgTest, TriStatePattern) then begin
      if (TIScreenPrint) then writeln('>> Failed TRISTATE LEAKAGE test');
      softbin:= TrileakFail;
      if not TIIgnoreFail then goto 100;
    end;
  end;
if TimeProgram then
             ProgramTimer('TRILKG test ');
  if PMUInleakEnable then
    begin
      if not PMUINLEAK(TIinleakTest,INUPSpmuinleakhiTest,TRSTpmuinleakhiTest) then begin
         if (TIScreenPrint) then writeln('>> Failed PMU INPUT LEAKAGE test');
         softbin:= PmuInleakFail;
         if not TIIgnoreFail then goto 100;
       end else
         if (TIScreenPrint) then writeln('Passed PMU INPUT LEAKAGE test');
    end;
if TimeProgram then
             ProgramTimer('PMUINLEAK test ');
  if PMUTrileakEnable then
    begin
      if not PMUTRILKG(TItrilkgTest,IOUPSpmutrilkgloTest,IOUPSpmutrilkghiTest,TriStatePattern) then begin
         if (TIScreenPrint) then writeln('>> Failed PMU TRISTATE LEAKAGE test');
         softbin:= PmuTrileakFail;
         if not TIIgnoreFail then goto 100;
       end else
         if (TIScreenPrint) then writeln('Passed PMU TRISTATE LEAKAGE test');
    end;
if TimeProgram then
             ProgramTimer('PMUTRILKG test ');
  if PTULeakEnable then
    begin
      if not PTULeak then begin
        if (TIScreenPrint) then writeln('>> Failed PTULeakage tests');
        softbin:= PTULeakFail;
        if not TIIgnoreFail then goto 100;
      end else if (TIScreenPrint) then writeln('Passed PTULeakage tests');
    end;
if TimeProgram then
             ProgramTimer('PTULeak test ');
if IddqEnable then
 begin
        if (not StressEnable) then
          if (TITestType = QA)
          then IddQTest(DCDataSheets[TIdataDCTable].v[CVddIddq2],DCDataSheets[TIdataDCTable].v[DVddIddq2],
                          DCDataSheets[TIdataDCTable].i[IddqFailLeak],2,1)
          else IddQTest(DCDataSheets[TIdataDCTable].v[CVddIddq2],DCDataSheets[TIdataDCTable].v[DVddIddq2],
                          DCDataSheets[TIdataDCTable].i[IddqFailLeak],1,1);
        if failiddq and IddqScreenEnable then
           begin
             softbin:= IddqPowerFail;
             if not TIIgnoreFail then goto 100;
           end;
        if not (CVdd_iddq_current < DCDataSheets[TIdataDCTable].i[IddqLeaky]) then
          begin
            if CVdd_iddq_current < DCDataSheets[TIdataDCTable].i[IddqVeryLeaky] then
              case softbin of
              VeryGoodUnit : softbin:=VeryGoodUnit_Leaky;
              GoodUnit_VeryHiFrqRomFail  : if not accept_bin01_only then
                                              softbin:=GoodUnit_VeryHiFrqRomFail_Leaky
                                           else
                                              softbin:=Do_not_ship_VeryHiFrqRomFail_Leaky;
              GoodUnit_VeryHiFrqFuncFail : if not accept_bin01_only then
                                              softbin:=GoodUnit_VeryHiFrqFuncFail_Leaky
                                           else
                                              softbin:=Do_not_ship_VeryHiFrqFuncFail_Leaky;
              others : begin end;
              end
            else begin
              if CVdd_iddq_current < DCDataSheets[TIdataDCTable].i[IddqFailLeak] then
                case softbin of
                VeryGoodUnit : softbin:=VeryGoodUnit_VeryLeaky;
                GoodUnit_VeryHiFrqRomFail  : if not accept_bin01_only then
                                                softbin:=GoodUnit_VeryHiFrqRomFail_VeryLeaky
                                             else
                                                softbin:=Do_not_ship_VeryHiFrqRomFail_VeryLeaky;
                GoodUnit_VeryHiFrqFuncFail : if not accept_bin01_only then
                                                softbin:=GoodUnit_VeryHiFrqFuncFail_VeryLeaky
                                             else
                                                softbin:=Do_not_ship_VeryHiFrqFuncFail_VeryLeaky;
                others : begin end;
                end
              else
                begin
                case softbin of
                VeryGoodUnit : softbin:=VeryGoodUnit_FailLeak;
                GoodUnit_VeryHiFrqRomFail  : if not accept_bin01_only then
                                                softbin:=GoodUnit_VeryHiFrqRomFail_FailLeak
                                             else
                                                softbin:=Do_not_ship_VeryHiFrqRomFail_FailLeak;
                GoodUnit_VeryHiFrqFuncFail : if not accept_bin01_only then
                                                softbin:=GoodUnit_VeryHiFrqFuncFail_FailLeak
                                             else
                                                softbin:=Do_not_ship_VeryHiFrqFuncFail_FailLeak;
                others : begin end;
                end;
                if not TIIgnoreFail then goto 100;
                end;
            end;
          end;
 end;
if TimeProgram then
             ProgramTimer('STANDBY CURRENT TEST ');
if Idle3Enable then
 begin
        if (not StressEnable) then
          if (TITestType = QA)
          then Idle3QTest(DCDataSheets[TIdataDCTable].v[CVddIdle32],DCDataSheets[TIdataDCTable].v[DVddIdle32],
                      DCDataSheets[TIdataDCTable].i[Idle3FailLeak],2,1)
          else Idle3QTest(DCDataSheets[TIdataDCTable].v[CVddIdle32],DCDataSheets[TIdataDCTable].v[DVddIdle32],
                      DCDataSheets[TIdataDCTable].i[Idle3FailLeak],1,1);
        if failidle3 and Idle3ScreenEnable then
           begin
             softbin:= Idle3PowerFail;
             if not TIIgnoreFail then goto 100;
           end;
        if not (CVdd_idle3_current < DCDataSheets[TIdataDCTable].i[Idle3Leaky]) then
          begin
            if CVdd_idle3_current < DCDataSheets[TIdataDCTable].i[Idle3VeryLeaky] then
              case softbin of
              VeryGoodUnit : softbin:=VeryGoodUnit_Leaky;
              GoodUnit_VeryHiFrqRomFail  : if not accept_bin01_only then
                                                softbin:=GoodUnit_VeryHiFrqRomFail_Leaky
                                             else
                                                softbin:=Do_not_ship_VeryHiFrqRomFail_Leaky;
              GoodUnit_VeryHiFrqFuncFail : if not accept_bin01_only then
                                                softbin:=GoodUnit_VeryHiFrqFuncFail_Leaky
                                             else
                                                softbin:=Do_not_ship_VeryHiFrqFuncFail_Leaky;
              others : begin end;
              end
            else begin
              if CVdd_idle3_current < DCDataSheets[TIdataDCTable].i[Idle3FailLeak] then
                case softbin of
                VeryGoodUnit : softbin:=VeryGoodUnit_VeryLeaky;
                GoodUnit_VeryHiFrqRomFail  : if not accept_bin01_only then
                                                softbin:=GoodUnit_VeryHiFrqRomFail_VeryLeaky
                                             else
                                                softbin:=Do_not_ship_VeryHiFrqRomFail_VeryLeaky;
                GoodUnit_VeryHiFrqFuncFail : if not accept_bin01_only then
                                                softbin:=GoodUnit_VeryHiFrqFuncFail_VeryLeaky
                                             else
                                                softbin:=Do_not_ship_VeryHiFrqFuncFail_VeryLeaky;
                others : begin end;
                end
              else
                begin
                case softbin of
                VeryGoodUnit : softbin:=VeryGoodUnit_FailLeak;
                GoodUnit_VeryHiFrqRomFail  : if not accept_bin01_only then
                                                softbin:=GoodUnit_VeryHiFrqRomFail_FailLeak
                                             else
                                                softbin:=Do_not_ship_VeryHiFrqRomFail_FailLeak;
                GoodUnit_VeryHiFrqFuncFail : if not accept_bin01_only then
                                                softbin:=GoodUnit_VeryHiFrqFuncFail_FailLeak
                                             else
                                                softbin:=Do_not_ship_VeryHiFrqFuncFail_FailLeak;
                others : begin end;
                end;
                if not TIIgnoreFail then goto 100;
                end;
            end;
          end;
   end;
if IddqLowerVddEnable then
 begin
        IddQTest(DCDataSheets[TIdataDCTable].v[CVddIddq1],DCDataSheets[TIdataDCTable].v[DVddIddq1],
                   DCDataSheets[TIdataDCTable].i[IddqLowerVddFailLeak],0,0);
        if failiddq and IddqLowerVddScreenEnable then
           begin
             softbin:= IddqLowerVddPowerFail;
             if not TIIgnoreFail then goto 100;
           end;
 end;
if Idle3LowerVddEnable then
 begin
        Idle3QTest(DCDataSheets[TIdataDCTable].v[CVddIdle31],DCDataSheets[TIdataDCTable].v[DVddIdle31],
                     DCDataSheets[TIdataDCTable].i[Idle3LowerVddFailLeak],0,0);
        if failidle3 and Idle3LowerVddScreenEnable then
           begin
             softbin:= Idle3LowerVddPowerFail;
             if not TIIgnoreFail then goto 100;
           end;
 end;
 end;
end;
if TimeProgram then
             ProgramTimer('Idle Power test ');
100:
 if ((TITestType=Probe) and (NominalVdd=Vdd_v50) and dosync and
    (softbin in [VeryGoodUnit..GoodUnit_HiVddVeryHiFrqRamWalkFail])) then
    dosync:=false;
 if ((TITestType=Probe) and dopll and (softbin in [VeryGoodUnit..GoodUnit_HiVddVeryHiFrqRamWalkFail])) then
    dopll:=false;
 if (TITestType=Probe) then
    die_count:=die_count+1;
 if ( softbin in [Stress_SyncFail,Stress_FuncFail,Stress_RomFail,Stress_RamFail,Stress_OtherFuncFail])
    and ( (TIScreenPrint and (not TIIgnoreFail)) or TIPrintTimings ) then
     begin writeln('STRESS TIME=',TimerStop/1000000:2:2,'s');end;
 if EngineeringEval then
    begin
    powerup(DCDataSheets[TIdataDCTable].v[CVddIddq2]);
    IddqMeasure:=false;
    DCBusDisconnectPinList(PMU1Bus);
    DCBusDisconnectPMU(PMU1Bus);
    DCBusDisconnectSupply(PMU1Bus);
    TestControlAll(NoAbortFail);
    for pattern:= alu1 to mpassing_base do
        begin
                    writeln(pattern);
                    Sync(TIlofrqlooseACTable,TIidleDCTable,force_clkin);
                    if not myTestFunc(pattern) then writeln('failed test');
                    PinListDisconnect(IDDQDISCONNECT);
                    if Bug_Supply and (not SingleDUTSupply) then SupplyDisconnect(DVdd);
                    Iddq(CVdd,4ma);
                    if (iddq_current>500na) then writeln(iddq_current:8,'  na');
                    if Bug_Supply and (not SingleDUTSupply) then SupplyConnect(DVdd);
                    PinListConnect(IDDQDISCONNECT);
                    if not EngineeringEval then pattern:=mpassing_base;
        end;
    for pattern:= alu1 to mpassing_base do
        begin
            writeln(pattern);
            if VectorGetHighest(pattern,highestvcount) then else;
            for execcount:= 153 to highestvcount do
              begin
                    Sync(TIlofrqlooseACTable,TIidleDCTable,force_clkin);
                    VectorIntervalSet(pattern,1,execcount);if not myTestFunc(pattern) then writeln('failed test');
                    PinListDisconnect(IDDQDISCONNECT);
                    if Bug_Supply and (not SingleDUTSupply) then SupplyDisconnect(DVdd);
                    Iddq(CVdd,4ma);
                    if (iddq_current>1000na) then writeln(iddq_current:8,'  na');
                    if (iddq_current>1000na) then writeln(pattern:15,execcount);
                    if (iddq_current>1000na) then VectorPrint(pattern,TIVM,execcount,execcount);
                    if Bug_Supply and (not SingleDUTSupply) then SupplyConnect(DVdd);
                    PinListConnect(IDDQDISCONNECT);
                    VectorIntervalResetAll;
                    if not EngineeringEval then execcount:=highestvcount;
              end;
        if not EngineeringEval then pattern:=mpassing_base;
        end;
    TestControlResetAll;
    end;
 if not TIIgnoreFail then TestFlagSet(softbin);
 if ctipdllog then
    begin
      i:=0;
      for TempSoftBin:=FirstSoftBin to LastSoftBin do
          begin
            i:=i+1;
            if TempSoftBin=softbin then softbinnumber:=i;
          end;
      CTIstring := 'SBIN';
      CTIPDLDataLogVariable(CTIstring,Z,softbinnumber);
    end;
 if (( iddqdatalog_one_over_number <> 0 ) and DiskLogEnable) then
    begin
      if ( ( softbin in [GoodUnit_LoVddVeryHiFrqSyncFail..GoodUnit_StressVddFail] ) and
         (iddqnumberofunit>=iddqdatalog_one_over_number) ) then
        begin
          iddqnumberofunit:=1;
          if (TIDeviceType in [C5X_Probe..C5X_Probe512CS]) then dlog_probe_iddq else dlog_ft_iddq;
        end else iddqnumberofunit:=iddqnumberofunit+1;
    end;
 if (( speeddatalog_one_over_number <> 0 ) and DiskLogEnable) then
    begin
      if ( ( softbin in [VeryGoodUnit,VeryGoodUnit_Leaky,VeryGoodUnit_VeryLeaky] ) and
         (speednumberofunit>=speeddatalog_one_over_number) ) then
        begin
          speednumberofunit:=1;
          if (TIDeviceType in [C5X_Probe..C5X_Probe512CS]) then else dlog_ft_speed;
        end else speednumberofunit:=speednumberofunit+1;
    end;
if ( (TILotType=ProductionLot) and (TITestType=Final) and
     ( (romcode='37357') or (romcode='37360') or (romcode='37362') or (romcode='37368') or  ( romcode='373c3') ) and
     ( softbin in [VeryGoodUnit,VeryGoodUnit_Leaky,VeryGoodUnit_VeryLeaky] )
   ) then dlog_eci;
PowerDown;
ModeSet(TesterLockEnd);
  if SDAlog_Enable and do_ram_SDA then
    begin
      if not SDAIntDone then
        begin
          InitializeSDA;
          SDAIntDone:=true;
        end;
      RamSDATest;
      if do_ram_SDA then
         do_ram_SDA:=false;
    end;
  if Datalog_Enable then
  begin
    if Access(DatalogFile,'a') then append(Log_Data, DatalogFile)
    else begin
      message ('  ' );
      message ('Error opening file ', DatalogFile );
      goto 200;
    end;
    File_Open := true;
    if handlernumber in [1,2] then
      HandlerGetTotalTested(handlernumber, totalunits );
    if ( Datalog_Enable and (totalunits = 0))  then
      writeln ( Log_Data, '@@@@@ Start of new segment @@@@@' );
    time ( TimeofDay );
    date ( TodaysDate );
    write ( Log_Data, TIDeviceType, '_ ' );
    write ( Log_Data, TIFELot:7, '_ ',TISMS370Lot:7, '_ ' );
    write ( Log_Data, WaferNumber:2,'_ ', Xcoord:2, '_ ', Ycoord:2, '_ ' );
    write ( Log_Data, TodaysDate:9, '_ ', TimeofDay:9, '_ ' );
    if IddqEnable or PreStressIddqEnable then
    begin
      case softbin of
        PreStress_SyncFail,
        PreStress_FuncFail,
        PreStress_RomFail,
        PreStress_RamFail,
        PreStress_OtherFuncFail,
        Stress_SyncFail,
        Stress_FuncFail,
        Stress_RomFail,
        Stress_RamFail,
        Stress_OtherFuncFail,
        OpensFail,
        ShortsFail :
          write ( Log_Data, ' 0_ 0_ 0_ 0_ 0_ 0_ ');
        InleakFail :
            if PreStressInLeakEnable then write ( Log_Data, ' 0_ 0_ 0_ 0_ 0_ 0_ ')
            else begin
              write ( Log_Data, CVdd_iddq_current/1000:8:2,'_ ' );
              write ( Log_Data, DVdd_iddq_current/1000:8:2,'_ ' );
              write ( Log_Data, ' 0_ 0_ 0_ 0_ ');
            end;
        others :
          begin
            write ( Log_Data, CVdd_iddq_current/1000:8:2,'_ ' );
            write ( Log_Data, DVdd_iddq_current/1000:8:2,'_ ' );
            write ( Log_Data, powerconsumption_cvdd_max/1000:7:2,'_ ' );
            write ( Log_Data, powerconsumption_dvdd_max/1000:7:2,'_ ' );
            write ( Log_Data, powerconsumption_cvdd_typ/1000:7:2,'_ ' );
            write ( Log_Data, powerconsumption_dvdd_typ/1000:7:2,'_ ' );
          end;
      end;
    end else
        write ( Log_Data, ' 0_ 0_ 0_ 0_ 0_ 0_ ');
    write ( Log_Data, test_time_01/1e6:6:2,'_ ');
    write ( Log_Data, test_time_02/1e6:6:2,'_ ');
    write ( Log_Data, softbin,'_ ' );
    if TIHardBinMapEnable then hardbin:= TestFlagHardBinGet;
    write ( Log_Data, hardbin,' ' );
200:
    writeln(Log_Data);
    CloseFile(Log_Data);
    File_Open := false;
  end;
if TimeProgram then
             ProgramTimer('Total Test Time ');
writeln(execFile,'PROCEND:TestFlow');
end;
