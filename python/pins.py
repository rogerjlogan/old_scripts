import sys
import re
import pprint
import os
import inspect
import string
import datetime

__PROGRAM_NAME__ = "Polaris Pin Group Analyzer"
__AUTHOR__ = "AUTHOR: Roger Logan, Anora Engineer, Dallas, TX"
__DATEMODIFIED__ = "LAST MODIFIED: Feb 15, 2012"
__VERSION__ = "v1.0"
__FILENAME__ = "pin.py"
__INPUT1_FILENAME__ = "<cycletbl_mod.p>"
__INPUT2_FILENAME__ = "<device_mod.p>"
__OUTPUT1_FILENAME__ = "pinlistset.p"
__OUTPUT2_FILENAME__ = "pinlist.txt"

__DEBUG__ = True
__USE_GROUPS__ = False
__VERBOSE__ = False

__allpingroups__ = []
__xgrps__ = []
__apexpins__ = []
__allcytbls__ = []

def lineno():
    """Returns the current line number in our program."""
    return inspect.currentframe().f_back.f_lineno

class TextException(Exception): pass

class Ddict(dict):
    def __init__(self, default=None):
        self.default = default
    def __getitem__(self, key):
        if not self.has_key(key):
            self[key] = self.default()
        return dict.__getitem__(self, key)
#End Ddict()


def getPins(item):
    pinlist=[]
    for v in extract(item):
        pinlist.append(v)
    #End for
    return pinlist
#End getPins
def extract(item2chk):
    if item2chk.strip() not in __allpingroups__:
        yield item2chk
    else:
        for item in __allpingroups__[item2chk.strip()]:
            for v in extract(item):
                yield v
            #End for
        #End for
#End extract()

def getGroups(item,srtd_grps,group=''):
    plst=item.split(',')
    for g in srtd_grps:
        if g in __xgrps__ or g==group:continue
        intsct=filter(lambda x:x in plst,__allpingroups__[g])
        diff=filter(lambda x:x not in __allpingroups__[g],plst)
        if intsct and len(intsct)==len(__allpingroups__[g]):
            diff.append(g)
            item=(',').join(diff)
            plst=diff
    #End for
    return item
#End getGroups()

def getSrtdGrps_andUPDATEallpingroups():
    """
        create a sorted list of __allpingroups__ by length of each group
        update __allpingroups__ so that each group contains only pins (no groups within groups)
    """
    global __allpingroups__
    def numeric_compare(x,y):
       if x>y:    return 1
       elif x==y: return 0
       else:      return -1 # x<y
    lengths=[]
    allpingroups_pins=Ddict(dict)
    for g in __allpingroups__:
        lst=[]
        for pin in __allpingroups__[g]:
            for p in getPins(pin):
                if p not in lst:
                    lst.append(p)
            allpingroups_pins[g]=lst
        #End for
        if len(allpingroups_pins[g]) not in lengths:
            lengths.append(len(allpingroups_pins[g]))
    #End for
    lengths.sort(numeric_compare)
    lengths.reverse()
    apg_pins_srtd=[]
    for l in lengths:
        for g in allpingroups_pins:
            if l==len(allpingroups_pins[g]):
                apg_pins_srtd.append(g)
        #End for
    #End for
    #let's modify __allpingroups__ so that no subgroups are used
    __allpingroups__=allpingroups_pins
    return apg_pins_srtd
#End getSrtdGrps_andUPDATEallpingroups()

#-----------------------------------------------------------------------
#   main
#-----------------------------------------------------------------------
def main():
    global __allpingroups__
    global __xgrps__
    global __apexpins__
    global __allcytbls__
    # Get the arguments from the command line, except the first one.
    args = sys.argv[1:]
    if len(args) != 2:
        print "usage: "+__FILENAME__+" "+__INPUT1_FILENAME__+" "+__INPUT2_FILENAME__
        sys.exit(-1)
    
    os.system('clear')
    if __VERBOSE__:
        print '\n\n'
        print __PROGRAM_NAME__
        print __AUTHOR__
        print __DATEMODIFIED__
        print __VERSION__
    print '\n\n'
    
    infile = file(args[0], 'r')
    ctblcont = infile.read()
    infile.close()
    infile = file(args[1], 'r')
    devcont = infile.read()
    infile.close()
    
    out1file = open(__OUTPUT1_FILENAME__, "w")
    out2file = open(__OUTPUT2_FILENAME__, "w")

    #all spaces WITHOUT newlines
    ws_patrn = re.compile("([ \t\r\f\v]*)")
    #all spaces WITH newlines
    wsn_patrn = re.compile("(\s*)")

###############################
#
#      GATHER PINGROUPS AND PINS FROM INPUT FILES
#
###############################

    #GET PINGROUPS
    pinlistset_patrn = re.compile("PinListSet(?:\s*)\((.*?),(.*?)\)",re.DOTALL)
    rawgroups=pinlistset_patrn.findall(devcont)
    __allpingroups__ = Ddict( dict )
    for pingroup,pins in rawgroups:
        #strip leading and trailing spaces
        pingroup=pingroup.strip();
        pins=re.sub(wsn_patrn,'',pins)
        pins=pins.split(',')
        __allpingroups__[pingroup]=pins
    #End for

    #GET NULL PINGROUPS
    pinlistsetnull_patrn = re.compile("PinListSetNull(?:\s*)\((.*?)\)",re.DOTALL)
    nullgroups=pinlistsetnull_patrn.findall(devcont)
    for ngroup in nullgroups:
        #strip leading and trailing spaces
        ngroup=ngroup.strip();
        __allpingroups__[ngroup]=''
    #End for

    #FILTER OUT UNSET PINS/PINGROUPS
    pinlistunset_patrn = re.compile("PinListUnSet(?:\s*)\((.*?),(.*?)\)",re.DOTALL)
    unsetrawgroups=pinlistunset_patrn.findall(devcont)
    for g in __allpingroups__:
        for ugrp,upins in unsetrawgroups:
            if g==ugrp:
                diff=filter(lambda x:x not in getPins(upins),getPins(g))
                __allpingroups__[g]=diff
            #End if
        #End for
    #End for

    #GET EXCLUDED GROUPS
    xgrps_patrn = re.compile("EXCLUDE_THESE_GROUPS(?:\s*)\((.*?)\)",re.DOTALL)
    rawxgrps=xgrps_patrn.findall(devcont)
    for xgrps in rawxgrps:
        #strip leading and trailing spaces
        xgrps=xgrps.strip();
        xgrps=re.sub(wsn_patrn,'',xgrps)
        xgrps=xgrps.split(',')
        for xgrp in xgrps:
            if xgrp not in __xgrps__:
                __xgrps__.append(xgrp)
    #End for

    #GET APEX PINLIST (list of ALL device pins IN ORDER)
    vmapset_patrn = re.compile("VectorMapSet(?:\s*)\((.*?),(.*?),(.*?),(.*?)\)",re.DOTALL)
    vmapset=vmapset_patrn.findall(ctblcont)
    for vmaptpl in vmapset:
        for pin in getPins(vmaptpl[2]):
            __apexpins__.append(pin)
#        vmap     = vmaptpl[0]
#        vfield   = vmaptpl[1]
#        vpinlist = vmaptpl[2]
#        vbase    = vmaptpl[3]


#################
#
#    BUILD NEW PinListSet's for output file
#
#################

    srtd_grps=getSrtdGrps_andUPDATEallpingroups()
#    pprint.pprint(getGroups('D14,D15,D10,D11,D12,D13,D8,D9,D6,D7,D4,D5,D2,D3,D0,D1',srtd_grps))
#    pprint.pprint(__allpingroups__)

    PinListSets = []
    for group in __allpingroups__:
        if not len(__allpingroups__[group]):
            PinListSets.append("PinListSetNull("+group+");")
            continue
        pinstr = ','.join(__allpingroups__[group])
        comment = '' 
        if __USE_GROUPS__:
            PinListSets.append("{PinListSet("+group+","+pinstr+");}")
            pinstr = getGroups(pinstr,srtd_grps,group)
        PinListSets.append("PinListSet("+group+","+pinstr+");")
    #End for

#    pprint.pprint(PinListSets)

    printstr = "SUCCESS!!! NEW FILES CREATED:\n"+__OUTPUT1_FILENAME__+"\n"+__OUTPUT2_FILENAME__

    print printstr
    pinlistset_str='\n'.join(PinListSets)
    out1file.write(pinlistset_str+'\n')
    out1file.close()

    #create pinlist.txt
    apexpins_str='\n'.join(__apexpins__)
    out2file.write(apexpins_str+'\n')
    out2file.close()

#End main()
#-----------------------------------------------------------------------
#     BEGIN MAIN
#-----------------------------------------------------------------------
if __name__ == '__main__':
    main()
