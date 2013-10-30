"""
    Requirements:
         - Python2.3 or higher
    Function:
        Used to generate the following files:
            - actable.proc          - Required by GCT_GEN_MOD6 (or later version)
            - pinlist.txt           - Required by GCT_GEN_MOD6 (or later version)
            - enums.evo             - Required by GCT_GEN_MOD6 (or later version) and Required by fusion program
            - pinlists.evo           - Required by fusion program
            - globalvars.proc       - Required by GCTGENMODpost.py
            - specAddonREADME.evo   - User needs to take data from here and manually place in ACSpec (acdata.evo)
"""
__progfile__ = "GCTGENMODsetup.py"
__version__ = "v1.0"
__author__ = "AUTHOR: Roger Logan, LTXCredence Apps Engineer, Houston, TX"
__date__ = "LAST MODIFIED: December 18, 2008"

import sys
import re
import pprint

from global_defs import *

__CYCLETABLE_IFILE__ = "<cycletbl.p>"
__DEVICE_IFILE__ = "<device.p>"
__ACTABLE_IFILE__ = "<actable.p>"
__GLOBALS_IFILE__ = "<Global.h>"
__PINLIST_OFILE__ = "pinlist.txt"
__ENUMS_OFILE__ = "enums.evo"
__PINGROUP_OFILE__ = "pinlists.evo"
__GLOBALVARS_OFILE__ = "globalvars.proc"
__ACTABLEMOD_OFILE__ = "actable.proc"
__SPECADDON_OFILE__ = "specAddonREADME.evo"
__SPECADDON_COMMENTS__ = "THE CONTENTS OF THIS FILE WERE EXTRACTED FROM "+__ACTABLE_IFILE__+", SPECIFICALLY, THE SECTION LOCATED ABOVE 'ACTableOpen'\n"
__SPECADDON_COMMENTS__ += "YOU MUST GO THROUGH THE CONTENTS OF THIS FILE AND ADD DATA TO YOUR acdata.evo WHERE APPROPRIATE.\n"
__SPECADDON_COMMENTS__ += "THIS WAS DECLARED AN 'EVO' FILE TO SIMPLY REMIND THE USER TO LOOK IN THIS VERY IMPORTANT FILE."
__EVHDR__ = "enVision:\"bl8:R11.1.0.WW1111:S3.5\"; /* 5.7 */\n\n"
__VERBOSE__ = True

#Error Messages
__PERMISSIONS_ERR__ = "If file was input, check to see if it exists and that read permissions are allowed for you.\n"
__PERMISSIONS_ERR__ += "Also, check that write permissions are allowed for this directory, as this scripts creates certain files."
__ACTABLECONTENT_ERR__ = "'ACTableOpen' not found in "+__ACTABLE_IFILE__

def getPinsAndGroups(ctblfile,devfile):
    """
        Gathers pins, groups, and excluded groups from
        <cycletbl.p> and <device.p> and places
        in apex dictionary variable for later use
    """

    infile = file(ctblfile, 'r')
    ctblcont = infile.read()
    infile.close()
    infile = file(devfile, 'r')
    devcont = infile.read()
    infile.close()

    #all spaces WITH newlines
    wsn_patrn = re.compile("(\s*)")

    apex = Ddict( dict )
    
    #GET PINGROUPS
    pinlistset_patrn = re.compile("PinListSet(?:\s*)\((.*?),(.*?)\)",re.DOTALL)
    rawgroups=pinlistset_patrn.findall(devcont)
    for pingroup,pins in rawgroups:
        #strip leading and trailing spaces
        pingroup=pingroup.strip();
        pins=re.sub(wsn_patrn,'',pins)
        pins=pins.split(',')
        apex['groups'][pingroup]=pins
    #End for
    #CREATE LIST OF SORTED PIN GROUPS
    lengths=[]
    allpingroups_pins=Ddict(dict)
    conv=PinGroupConverter()
    for g in apex['groups']:
        lst=[]
        for pin in apex['groups'][g]:
            for p in conv.getPins(pin,apex['groups']):
                if p not in lst:
                    lst.append(p)
            allpingroups_pins[g]=lst
        #End for
        if len(allpingroups_pins[g]) not in lengths:
            lengths.append(len(allpingroups_pins[g]))
    #End for
    lengths.sort()
    lengths.reverse()
    apg_pins_srtd=[]
    for l in lengths:
        for g in allpingroups_pins:
            if l==len(allpingroups_pins[g]):
                apg_pins_srtd.append(g)
        #End for
    #End for
    apex['orig_grps']=apex['groups']
    #let's modify apex['groups'] so that no subgroups are used
    apex['groups']=allpingroups_pins
    apex['srtdgrps']=apg_pins_srtd

    #GET EXCLUDED GROUPS
    xgrps_patrn = re.compile("EXCLUDE_THESE_GROUPS(?:\s*)\((.*?)\)",re.DOTALL)
    rawxgrps=xgrps_patrn.findall(devcont)
    xgroups=[]
    for xgrps in rawxgrps:
        #strip leading and trailing spaces
        xgrps=xgrps.strip();
        xgrps=re.sub(wsn_patrn,'',xgrps)
        xgrps=xgrps.split(',')
        for xgrp in xgrps:
            if xgrp not in xgroups:
                xgroups.append(xgrp)
        #End for
    #End for
    apex['xgrps']=xgroups
    
    #GET MUXPINS
    muxpin_patrn = re.compile("PinSetMux(?:[MP]P)?(?:\s*)\((.*?),(?:.*?)\)",re.DOTALL)
    apex['muxpins']=unique(muxpin_patrn.findall(devcont))

    #GET APEX PINLIST (list of ALL device pins IN ORDER)
    vmapset_patrn = re.compile("VectorMapSet(?:\s*)\((.*?),(.*?),(.*?),(.*?)\)",re.DOTALL)
    vmapset=vmapset_patrn.findall(ctblcont)
    conv=PinGroupConverter()
    apex['pins']=[]
    for vmaptpl in vmapset:
        for pin in conv.getPins(vmaptpl[2],apex['groups']):
            apex['pins'].append(pin)
        #End for
    #End for
    return apex
#End getPinsAndGroups()

def getGlobals(glblfile):
    """
        Gathers all info (mostly all) from <Global.h>
        which will be used to create enums.evo
    """
    try:
        infile = file(glblfile, 'r')
        glblcont = infile.read()
        infile.close()
    except:
        err="File Error: "+glblfile+"\n"
        err+=__PERMISSIONS_ERR__
        sys.exit(stop(err))

    wsn2_patrn = re.compile("(?P<ws>\s)(\s*)")
    glblcont=stripcom(glblcont,'(*','*)')
    glblcont=stripcom(glblcont,'{','}')
    glblcont=wsn2_patrn.sub('\g<ws>',glblcont)
    
    globalvars=dict()

    # REQUIRED FOR ENUMS FILE
    globalvars['TempTypeLIST']=[]
    p = re.compile("(?:\s*)TempType(?:\s*)=(?:\s*)\((?P<data>.*?)\)",re.DOTALL)
    temptypesObj=p.search(glblcont)
    try:
        temptypes = temptypesObj.group('data').split(',')
        for v in temptypes:globalvars['TempTypeLIST'].append(v.strip())
    except Exception:
        err="TempType not found in "+__GLOBALS_IFILE__
        sys.exit(stop(err))

    # REQUIRED FOR ENUMS FILE
    globalvars['DeviceTypeLIST']=[]
    p = re.compile("(?:\s*)DeviceType(?:\s*)=(?:\s*)\((?P<data>.*?)\)",re.DOTALL)
    devtypesObj=p.search(glblcont)
    try:
        devtypes = devtypesObj.group('data').split(',')
        for v in devtypes:globalvars['DeviceTypeLIST'].append(v.strip())
    except Exception:
        err="DeviceType not found in "+__GLOBALS_IFILE__
        sys.exit(stop(err))

    # REQUIRED FOR ENUMS FILE
    globalvars['TITypeOfTestLIST']=[]
    p = re.compile("(?:\s*)TITypeOfTest(?:\s*)=(?:\s*)\((?P<data>.*?)\)",re.DOTALL)
    typeoftestsObj=p.search(glblcont)
    try:
        typeoftests = typeoftestsObj.group('data').split(',')
        for v in typeoftests:globalvars['TITypeOfTestLIST'].append(v.strip())
    except Exception:
        err="TITypeOfTest not found in "+__GLOBALS_IFILE__
        sys.exit(stop(err))

    globalvars['ACTableLIST']=[]
    p = re.compile("(?:\s*)ACTable(?:\s*)=(?:\s*)\((?P<data>.*?)\)",re.DOTALL)
    actablesObj=p.search(glblcont)
    if actablesObj:
        actables = actablesObj.group('data').split(',')
        for v in actables:globalvars['ACTableLIST'].append(v.strip())
    
    globalvars['CycleTableLIST']=[]
    p = re.compile("(?:\s*)CycleTable(?:\s*)=(?:\s*)\((?P<data>.*?)\)",re.DOTALL)
    cycetablesObj=p.search(glblcont)
    if cycetablesObj:
        cycetables = cycetablesObj.group('data').split(',')
        for v in cycetables:globalvars['CycleTableLIST'].append(v.strip())
    
    globalvars['CycleLIST']=[]
    p = re.compile("(?:\s*)Cycle(?:\s*)=(?:\s*)\((?P<data>.*?)\)",re.DOTALL)
    cyclesObj=p.search(glblcont)
    if cyclesObj:
        cycles = cyclesObj.group('data').split(',')
        for v in cycles:globalvars['CycleLIST'].append(v.strip())
    
    globalvars['VectorMapLIST']=[]
    p = re.compile("(?:\s*)VectorMap(?:\s*)=(?:\s*)\((?P<data>.*?)\)",re.DOTALL)
    vmapsObj=p.search(glblcont)
    if vmapsObj:
        vmaps = vmapsObj.group('data').split(',')
        for v in vmaps:globalvars['VectorMapLIST'].append(v.strip())
    
    globalvars['TestNameLIST']=[]
    p = re.compile("(?:\s*)TestName(?:\s*)=(?:\s*)\((?P<data>.*?)\)",re.DOTALL)
    testnamesObj=p.search(glblcont)
    if testnamesObj:
        testnames = testnamesObj.group('data').split(',')
        for v in testnames:globalvars['TestNameLIST'].append(v.strip())
    
    globalvars['SoftBinLIST']=[]
    p = re.compile("(?:\s*)SoftBin(?:\s*)=(?:\s*)\((?P<data>.*?)\)",re.DOTALL)
    softbinsObj=p.search(glblcont)
    if softbinsObj:
        softbins = softbinsObj.group('data').split(',')
        for v in softbins:globalvars['SoftBinLIST'].append(v.strip())
    
    globalvars['HardBinLIST']=[]
    p = re.compile("(?:\s*)HardBin(?:\s*)=(?:\s*)\((?P<data>.*?)\)",re.DOTALL)
    hardbinsObj=p.search(glblcont)
    if hardbinsObj:
        hardbins = hardbinsObj.group('data').split(',')
        for v in hardbins:globalvars['HardBinLIST'].append(v.strip())
    
    return globalvars
#End getGlobals()

def getACTABLEcontents(actblfile):
    """
        Get ACTable and structures it for easy parsing
        Grabs actblcont located above keyword 'ACTableOpen' and 
        places in specAddonREADME.evo
    """
    try:
        infile = file(actblfile, 'r')
        actblallcont = infile.read()
        infile.close()
    except:
        err="File Error: "+actblfile+"\n"
        err+=__PERMISSIONS_ERR__
        sys.exit(stop(err))
    patrn=re.compile("(?P<specaddon>.*)ACTableOpen(?P<actable>.*)",re.DOTALL)
    if "ACTableOpen" not in actblallcont:
        sys.exit(stop(__ACTABLECONTENT_ERR__))
    actblcontObj=patrn.search(actblallcont)
    actblcont='ACTableOpen'+actblcontObj.group('actable')
    specaddon=actblcontObj.group('specaddon')

    actblcont=stripcom(actblcont,'(*','*)')
    actblcont=stripcom(actblcont,'{','}')

    #remove spaces next to symbols
    symbls=[',',':',';','\+','-','\*','/','=']
    for s in symbls:
        patrn=re.compile("(?:\s*)"+s+"(?:\s*)",re.DOTALL)
        actblcont=re.sub(patrn,s,actblcont)
    actblcont=actblcont.replace('\+','+')
    actblcont=actblcont.replace('\*','*')
    actblcont=actblcont.replace('\n',' ')
    actblcont=actblcont.replace(';',';\n')
    patrn=re.compile("begin(?:\s*)")
    actblcont=re.sub(patrn,"\nbegin\n",actblcont)
    patrn=re.compile("then(?:\s*)")
    actblcont=re.sub(patrn,"then\n",actblcont)
    patrn=re.compile("else(?:\s*)")
    actblcont=re.sub(patrn,"else\n",actblcont)
    
    return actblcont,specaddon
#End parseACTable()

def mkEnumsEVOFile(globalvars):
    try:
        enums_ofile = open(__ENUMS_OFILE__, "w")
    except:
        err="File Error: "+__ENUMS_OFILE__+"\n"
        err+=__PERMISSIONS_ERR__
        sys.exit(stop(err))
    enums_ostr=__EVHDR__+mkHeader(__progfile__,__version__,__author__,'//')+'\n\n'
    if globalvars['TempTypeLIST']:
        enums_ostr+='enum TITestTemp\n{\n'
        for temp in globalvars['TempTypeLIST']:
            enums_ostr+='\t'+temp+',\n'
        enums_ostr=enums_ostr[:-2]+'\n};\n'
    if globalvars['DeviceTypeLIST']:
        enums_ostr+='enum TIDeviceType\n{\n'
        for dev in globalvars['DeviceTypeLIST']:
            enums_ostr+='\t'+dev+',\n'
        enums_ostr=enums_ostr[:-2]+'\n};\n'
    if globalvars['TITypeOfTestLIST']:
        enums_ostr+='enum TITestType\n{\n'
        for testtype in globalvars['TITypeOfTestLIST']:
            enums_ostr+='\t'+testtype+',\n'
        enums_ostr=enums_ostr[:-2]+'\n};\n'
    enums_ofile.write(enums_ostr)
    enums_ofile.close()
#End mkEnumFile()

def mkPinGroupEVOFile(apex):
    try:
        pingrp_ofile = open(__PINGROUP_OFILE__, "w")
    except:
        err="File Error: "+__PINGROUP_OFILE__+"\n"
        err+=__PERMISSIONS_ERR__
        sys.exit(stop(err))
    pingrp_ostr=__EVHDR__+mkHeader(__progfile__,__version__,__author__,'//')+'\n\n'

    grpkeys=sortDictkeys(apex['orig_grps'])

    for key in grpkeys:
        pinsonlygrps='+'.join(apex['groups'][key])
        orig_groups='+'.join(apex['orig_grps'][key])
        if pinsonlygrps!=orig_groups:
            pingrp_ostr+="//  PinGroup "+key+"{ Group = Expr { String = \""+pinsonlygrps+"\"; } }\n"
        pingrp_ostr+="\tPinGroup "+key+"{ Group = Expr { String = \""+orig_groups+"\"; } }\n\n"
        
    
    #REPLACE ALL INSTANCES OF 'MUXPIN' WITH 'MUXPIN','MUXPINm'
    for muxpin in apex['muxpins']:
        pingrp_ostr=pingrp_ostr.replace(muxpin,muxpin+"+"+muxpin+"m")
    
    pingrp_ofile.write(pingrp_ostr)
    pingrp_ofile.close()
#End mkPinGroupEVOFile()

def mkPinlistFile(apexpins):
    try:
        ofile = open(__PINLIST_OFILE__, "w")
    except:
        err="File Error: "+__PINLIST_OFILE__+"\n"
        err+=__PERMISSIONS_ERR__
        sys.exit(stop(err))
    #create pinlist.txt
    apexpins_str='\n'.join(apexpins)
    ofile.write(mkHeader(__progfile__,__version__,__author__))
    ofile.write(apexpins_str+'\n')
    ofile.close()
#End mkPinlistFile()

def mkACTableModFile(actcont):
    try:
        ofile = open(__ACTABLEMOD_OFILE__, "w")
    except:
        err="File Error: "+__ACTABLEMOD_OFILE__+"\n"
        err+=__PERMISSIONS_ERR__
        sys.exit(stop(err))
    ofile.write(mkHeader(__progfile__,__version__,__author__))
    ofile.write(actcont)
    ofile.close()
#End mkACTableModFile()

def mkSpecAddonEVOFile(specaddon):
    try:
        ofile = open(__SPECADDON_OFILE__, "w")
    except:
        err="File Error: "+__SPECADDON_OFILE__+"\n"
        err+=__PERMISSIONS_ERR__
        sys.exit(stop(err))
    ofile.write(mkHeader(__progfile__,__version__,__author__))
    ofile.write("##########################################################################################################\n")
    ofile.write(__SPECADDON_COMMENTS__)
    ofile.write("\n##########################################################################################################\n\n\n")
    ofile.write(specaddon)
    ofile.close()
#End mkSpecAddonEVOFile()

def mkGlobalVarsFile(apex):
    try:
        ofile = open(__GLOBALVARS_OFILE__, "w")
    except:
        err="File Error: "+__GLOBALVARS_OFILE__+"\n"
        err+=__PERMISSIONS_ERR__
        sys.exit(stop(err))
    ofile.write(mkHeader(__progfile__,__version__,__author__))
    ofile.write('PINS:'+str(apex['pins'])+'\n')
    ofile.write('MUXPINS:'+str(apex['muxpins'])+'\n')
    ofile.write('GROUPS:'+str(apex['groups'])+'\n')
    ofile.write('ORIG_GRPS:'+str(apex['orig_grps'])+'\n')
    ofile.write('XGROUPS:'+str(apex['xgrps'])+'\n')
    ofile.write('SRTDGRPS:'+str(apex['srtdgrps'])+'\n')
    ofile.close()
#End mkGlobalVarsFile()


#-----------------------------------------------------------------------
#   main
#-----------------------------------------------------------------------
def main():
    global __CYCLETABLE_IFILE__,__DEVICE_IFILE__,__ACTABLE_IFILE__,__GLOBALS_IFILE__
    
    # Get the arguments from the command line, except the first one.
    args = sys.argv[1:]
    if len(args) != 4:
        err="\nusage: python "+__progfile__+" "+__CYCLETABLE_IFILE__+" "+__DEVICE_IFILE__+" "+__ACTABLE_IFILE__+" "+__GLOBALS_IFILE__+"\n"
        sys.exit(err)

    __CYCLETABLE_IFILE__=args[0]
    __DEVICE_IFILE__=args[1]
    __ACTABLE_IFILE__=args[2]
    __GLOBALS_IFILE__=args[3]

    if __VERBOSE__:
        print '\n\n'
        print __progfile__,__version__
        print __author__
        print __date__
    print '\n'

    apex=getPinsAndGroups(__CYCLETABLE_IFILE__,__DEVICE_IFILE__)
    actcont,specaddon=getACTABLEcontents(__ACTABLE_IFILE__)
    globalvars=getGlobals(__GLOBALS_IFILE__)
    mkACTableModFile(actcont)
    mkSpecAddonEVOFile(specaddon)
    mkEnumsEVOFile(globalvars)
    mkPinGroupEVOFile(apex)
    mkPinlistFile(apex['pins'])
    mkGlobalVarsFile(apex)
    
    ostr="SUCCESS!!! NEW FILES CREATED:\n"
    ostr+=__ACTABLEMOD_OFILE__+"\n"
    ostr+=__GLOBALVARS_OFILE__+"\n"
    ostr+=__PINLIST_OFILE__+"\n"
    ostr+=__ENUMS_OFILE__+"\n"
    ostr+=__PINGROUP_OFILE__+"\n"
    ostr+=__SPECADDON_OFILE__+"\n"
    print ostr

#End main()
#-----------------------------------------------------------------------
#     BEGIN MAIN
#-----------------------------------------------------------------------
if __name__ == '__main__':
    main()
