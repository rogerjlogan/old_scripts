import sys
import re
import pprint

#from global_defs import *

__CYCLETABLE_IFILE__ = "<cycletbl.p>"
__DEVICE_IFILE__ = "<device.p>"
__PINLIST_OFILE__ = "pinlist.txt"
__PINGROUP_OFILE__ = "pinlists.evo"
#Error Messages
__PERMISSIONS_ERR__ = "If file was input, check to see if it exists and that read permissions are allowed for you.\n"
__PERMISSIONS_ERR__ += "Also, check that write permissions are allowed for this directory, as this scripts creates certain files."

class TextException(Exception): pass

class Ddict(dict):
    def __init__(self, default=None):
        self.default = default
    def __getitem__(self, key):
        if not self.has_key(key):
            self[key] = self.default()
        return dict.__getitem__(self, key)
#End Ddict()

class PinGroupConverter(object):
    def getPins(self,item):
        pinlist=[]
        for v in self._extract(item):
            pinlist.append(v)
        #End for
        return pinlist
    #End getPins
    def _extract(self,item2chk):
        if item2chk.strip() not in __allpingroups__:
            yield item2chk
        else:
            for item in __allpingroups__[item2chk.strip()]:
                for v in self._extract(item):
                    yield v
                #End for
            #End for
    #End extract()
    def getGroups(self,item,srtd_grps):
        plst=item.split(',')
        for g in srtd_grps:
            if g in __xgrps__:continue
            intsct=filter(lambda x:x in plst,__allpingroups__[g])
            diff=filter(lambda x:x not in __allpingroups__[g],plst)
            if intsct and len(intsct)==len(__allpingroups__[g]):
                diff.append(g)
                item=(',').join(diff)
                plst=diff
        #End for
        return item
    #End getGroups()
#End PinGroupConverter()

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
            try:
                print apex['groups'];
                print "made it EXITING!!!!"
                sys.exit(-1)
                for p in conv.getPins(pin,apex['groups']):
                    if p not in lst:
                        lst.append(p)
            except:
                print apex['groups'];
                print "EXITING!!!!"
                sys.exit(-1)
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

#-----------------------------------------------------------------------
#   main
#-----------------------------------------------------------------------
def main():
    global __CYCLETABLE_IFILE__,__DEVICE_IFILE__,__ACTABLE_IFILE__,__GLOBALS_IFILE__
    
    # Get the arguments from the command line, except the first one.
    args = sys.argv[1:]
    if len(args) != 2:
        err="\nusage: python "+__progfile__+" "+__CYCLETABLE_IFILE__+" "+__DEVICE_IFILE__+"\n"
        sys.exit(err)

    __CYCLETABLE_IFILE__=args[0]
    __DEVICE_IFILE__=args[1]

    if __VERBOSE__:
        print '\n\n'
        print __progfile__,__version__
        print __author__
        print __date__
    print '\n'

    apex=getPinsAndGroups(__CYCLETABLE_IFILE__,__DEVICE_IFILE__)
#    mkPinGroupEVOFile(apex)
    mkPinlistFile(apex['pins'])
    
    ostr="SUCCESS!!! NEW FILES CREATED:\n"
    ostr+=__PINLIST_OFILE__+"\n"
    ostr+=__PINGROUP_OFILE__+"\n"
    print ostr

#End main()
#-----------------------------------------------------------------------
#     BEGIN MAIN
#-----------------------------------------------------------------------
if __name__ == '__main__':
    main()
