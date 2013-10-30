import sys
import re
import pprint
import os
import inspect
import string
import datetime

__PROGRAM_NAME__ = "CYCLETABLE OPTIMIZER"
__AUTHOR__ = "AUTHOR: Roger Logan, LTXCredence Apps Engineer, Houston, TX"
__DATEMODIFIED__ = "LAST MODIFIED: November 26, 2008"
__VERSION__ = "v1.0"
__FILENAME__ = "cycletblopt.py"
__INPUT1_FILENAME__ = "<cycletbl_mod.p>"
__INPUT2_FILENAME__ = "<device_mod.p>"
__OUTPUT1_FILENAME__ = "<cycletbl_mod.p>.new"
__OUTPUT2_FILENAME__ = "pinlist.txt"
__OUTPUT3_FILENAME__ = "analysis.txt"

__DEBUG__ = True
__USE_GROUPS__ = True
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

def getGroups(item,srtd_grps):
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

def formatZippers(envCycTbls):

#{0: {'dependencies': ['LWRBGWRBCycle,LRDDFF0RCycle,GWE
#     'pins': {'IACKstrobeWF,ALLoffWF': 'IACK_'}},
# 1: {'dependencies': ['LWRBGWRBCycle,LRDDFF0RCycle,GWE
#     'pins': {'H1strobeWF,ALLoffWF': 'H1'}},
# 2: {'dependencies': ['LWRBGWRBCycle,LRDDFF0RCycle,GWE
#     'pins': {'ALLoffWF,ROMENdriveWF': 'ROMEN'}},
# 3: {'dependencies': ['LWRBGWRBCycle,LRDDFF0RCycle,GWE
#     'pins': {'TCKCLKdriveWF,TCKdriveWF': 'TCK'}},
# 4: {'dependencies': ['JTAGEXTECycle',
#                      'JTAGEXTECycle',
#                      'JTAGEXTECycle',
#
#
#
#    pprint.pprint(envCycTbls)
#    sys.exit(-1)
    
    polCycTbls=Ddict(dict)
    i=0
    for ect in envCycTbls:
        for cts in envCycTbls[ect]['dependencies']:
            tbls=cts.split(',')
            for t in tbls:
                if t not in polCycTbls:
                    polCycTbls[t]=[]
                if ect not in polCycTbls[t]:
                    polCycTbls[t].append(ect)
                #else:it's already listed
            #End for
        #End for
    #End for


#    polCycTbls=Ddict(dict)
#    for ect in envCycTbls:
#        for cts in envCycTbls[ect]['dependencies']:
#            if cts not in polCycTbls.keys():
#                polCycTbls[cts]=[]
#            if ect not in polCycTbls[cts]:
#                polCycTbls[cts].append(ect)
#            #else:it's already listed
#        #End for
#    #End for
    
    ostr=''
#    ostr='\n\n\tZipper = Zipper {'
#    for t in polCycTbls:
#        ostr+='\n\t\tRow { TDLStdPatGrp, %-15s = { ' % t
#        for i in polCycTbls[t]:
#            ostr+='WFT_'+str(i)+','
#        ostr=ostr[:-1]+' }'
#    ostr+='\n\t}'
    
    astr='\n%-15s' % 'WFT_##'
    for ect in envCycTbls:
        astr+='%3s' % str(ect)
    astr+='\n'
    for pct in polCycTbls:
        astr+='\n%-15s' % pct
        for ect in envCycTbls:
            if ect in polCycTbls[pct]:
                astr+='%3s' % '*'
            else:
                astr+='%3s' % ' '
    return ostr,astr

#End formatZippers()

def formatCycSets(envCycTbls):
    ostr='\n\n'
    for t in envCycTbls:
        for cell in envCycTbls[t]['pins']:
            d0d1=cell.split(',')
            d0,d1=d0d1[0],d0d1[1]
            pins=envCycTbls[t]['pins'][cell].replace(',','+')
            row = {'cycletbl':'WFT_'+str(t)+',','d0':d0+',','d1': d1+',','pins':pins}
            ostr+='\tCycleSetMD( %(cycletbl)-12s %(d0)-20s %(d1)-20s %(pins)s );\n' % row
    return ostr
#End formatCycSets()

#-----------------------------------------------------------------------
#   main
#-----------------------------------------------------------------------
def main():
    global __OUTPUT1_FILENAME__
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
    
    __OUTPUT1_FILENAME__=args[0]+'.new'
    out1file = open(__OUTPUT1_FILENAME__, "w")
    out2file = open(__OUTPUT2_FILENAME__, "w")
    if __DEBUG__:
        out3file = open(__OUTPUT3_FILENAME__, "w")

    #all spaces WITHOUT newlines
    ws_patrn = re.compile("([ \t\r\f\v]*)")
    #all spaces WITH newlines
    wsn_patrn = re.compile("(\s*)")

###############################
#
#      GATHER DATA FROM INPUT FILES
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

#    #GET APEX PINLIST (list of ALL device pins IN ORDER)
#    vectormapset_patrn = re.compile("VectorMapSet(?:\s*)\((?:.*?),(?:.*?),(.*?),(?:.*?)\)",re.DOTALL)
#    apexgroups=vectormapset_patrn.findall(ctblcont)
#    for item in apexgroups:
#        for pin in getPins(item):
#            __apexpins__.append(pin)
            
            
            
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

    #GET CYCLE TABLES
    cyclesetmd_patrn = re.compile("CycleSetMD(?:\s*)\((.*),(.*),(.*),(.*)\)")
    allcells=cyclesetmd_patrn.findall(ctblcont)
    formats=Ddict(dict)
    i=-1
    for tbl,dset0,dset1,pin in allcells:
        i+=1
        tbl=re.sub(wsn_patrn,'',tbl)
        dset0=re.sub(wsn_patrn,'',dset0)
        dset1=re.sub(wsn_patrn,'',dset1)
        pin=re.sub(wsn_patrn,'',pin)
        pinlist=getPins(pin)
        pinlist_str=','.join(pinlist)
        f=dset0+','+dset1
        if tbl not in __allcytbls__:
            __allcytbls__.append(tbl)
        if pinlist_str not in formats[f]:
            formats[f][pinlist_str]=tbl
        else:
            newtbl=formats[f][pinlist_str]+','+tbl
            formats[f][pinlist_str]=newtbl
    #End for

#################
#
#    CONSOLIDATE PINS FOR EACH FORMAT (dset0,dset1)
#    AND ELIMINATE MORE THAN ONE REFERENCE FOR ANY
#    GIVEN CYCLE TABLE PER FORMAT
#    (to see the difference this section makes,
#     uncomment the following lines)
#
#    pprint.pprint(formats,out1file)
#    sys.exit(-1)
#
#################

    #reverse keys(pins) with values(cycletables) so we can reduce number of cycletable references
    fmts=Ddict(dict)
    for f in formats:
        for p_str in formats[f]:
            v=formats[f][p_str]
            if formats[f][p_str] not in fmts[f]:
                fmts[f][v]=p_str
            else:
                newpstr=fmts[f][v]+','+p_str
                fmts[f][v]=newpstr
        #End for
    #End for
    
    for f in fmts:
        xtbls=[]
        for t in fmts[f]:
            tbls=t.split(',')
            cyctbls=Ddict(dict)
            for v in tbls:
                if v not in cyctbls.keys():
                    cyctbls[v]=fmts[f][t]
            #End for
            xtbls.append(cyctbls)
        #End for
        
        tmptbls=Ddict(dict)
        for row in xtbls:
            for t in row:
                if t not in tmptbls.keys():
                    tmptbls[t]=row[t]
                else:
                    val1=filter(lambda x:x not in tmptbls[t].split(','),row[t].split(','))
                    val2=filter(lambda x:x not in row[t].split(','),tmptbls[t].split(','))
                    disctinct_list=val1+val2
                    tmptbls[t]=','.join(disctinct_list)
            #End for
        #End for
        
        #reverse and reduce again
        tmp2tbls=Ddict(dict)
        for t in tmptbls:
            p=tmptbls[t]
            if p not in tmp2tbls.keys():
                tmp2tbls[p]=t
            else:
                tmp2tbls[p]=tmp2tbls[p]+','+t
        #End for
        
        #reverse back
        newtbls=Ddict(dict)
        for p in tmp2tbls:
            t=tmp2tbls[p]
            if t not in newtbls.keys():
                newtbls[t]=p
        #End for
        
        fmts[f]=newtbls
#        fmts[f]=tmp2tbls
    #End for

#################
#
#    PRINT ANALYSIS
#
#################
    if __DEBUG__:
        pprint.pprint(fmts,out3file)

########################################################################################################
#
#    ORGANIZE DATA FOR SIMPLER COMPREHENSION
#
#       (THE INFO BELOW IS FOR DEBUGGING PURPOSES ONLY)
#
#   BEFORE:
#           f = 'ABUSVALstrobeWF,ALLoffWF'                   - format
#           t = 'LABVGRDDCycle,LVALGWRBCycle,LVALGRDDCycle'  - cycletable
#  fmts[f][t] = 'LA30,LA29,LA28'                             - pins
#  {'ABUSVALstrobeWF,ALLoffWF': {'LABVGRDDCycle,LVALGWRBCycle,LVALGRDDCycle': 'LA30,LA29,LA28',
#                                'LRDDGABVCycle,LWRBGVALCycle,LRDDGVALCycle': 'GA30,GA29,GA28',}
#   AFTER:
#            i = 0                                           - WFT_##
#  pinsDict[i] = 0: {'LA30' : 'ABUSVALstrobeWF,ALLoffWF+LABVGRDDCycle,LVALGWRBCycle,LVALGRDDCycle'     - pin : format + cycletable dependencies
#  pinsDict[i] = 0: {'LA29' : 'ABUSVALstrobeWF,ALLoffWF+LABVGRDDCycle,LVALGWRBCycle,LVALGRDDCycle'     - pin : format + cycletable dependencies
#  .... .... .... .... .... .... .... .... .... .... ....
#  pinsDict[i] = 0: {'GA28' : 'ABUSVALstrobeWF,ALLoffWF+LRDDGABVCycle,LWRBGVALCycle,LRDDGVALCycle'     - pin : format + cycletable dependencies
#
########################################################################################################

#    pinsDict=Ddict(dict)
#    i=0
#    for f in fmts:
#        for tbls in fmts[f]:
#            pins=fmts[f][tbls].split(',')
#            for pin in pins:
#                if pin in pinsDict[i].keys():
#                    i+=1
#                pinsDict[i][pin]=f+'+'+tbls
#            #End for
#        #End for
#    #End for
    
    pinsDict=Ddict(dict)
    depsDict=Ddict(dict)
    i=-1
#    depsDict[i]=[]
    for f in fmts:

        i+=1
        depsDict[i]=[]
        


        for t in fmts[f]:
            pins=fmts[f][t].split(',')
            for pin in pins:

#                if pin in pinsDict[i].keys() or t in  pinsDict[i]:
#                    i+=1
#                    depsDict[i]=[]
                    
                pinsDict[i][pin]=f
                depsDict[i].append(t)


#                if pin not in pinsDict[i].keys() and t not in pinsDict[i]:
#                    pinsDict[i][pin]=f
#                    depsDict[i].append(t)
#                else:
#                    i+=1
#                    depsDict[i]=[]
#                    pinsDict[i][pin]=f
#                    depsDict[i].append(t)


            #End for
        #End for
    #End for


#########################################################
#
#    ORGANIZE DATA FOR SIMPLER COMPREHENSION ( CONTINUED FROM ABOVE)
#
#   AFTER:
#            i = 0                                                                                            - WFT_##
#  pinsDict[i] = 0 : {'ABUSVALstrobeWF,ALLoffWF': 'LA30,LA29,LA28,LA30,LA29,LA28'}                            - format : pins
#  depsDict[i] = 0 : ['LABVGRDDCycle,LVALGWRBCycle,LVALGRDDCycle,LRDDGABVCycle,LWRBGVALCycle,LRDDGVALCycle']  - cycletable dependencies
#
#########################################################

#    depsDict=Ddict(dict)
#    for i in pinsDict:
#        depsDict[i]=[]
#        for p in pinsDict[i]:
#            fandt=pinsDict[i][p].split('+')
#            cyctblslst=fandt[1:]                            #just grab the tables, not the format
#            pinsDict[i][p]=string.join( fandt[:1], '' )     #place the format back in place with the tables
#            
#            for tbl in cyctblslst:
#                ct=tbl.split(',')
#                
#                for t in ct:
#                    if t not in depsDict[i]:
#                        depsDict[i].append(t)
#                
##                val1=filter(lambda x:x not in ct,depsDict[i])
##                val2=filter(lambda x:x not in depsDict[i],ct)
##                depsDict[i]=val1+val2
                    
    newcell=Ddict(dict)
    for t in pinsDict:
        for p in pinsDict[t]:
            f=pinsDict[t][p]
            if f not in newcell[t]:
                newcell[t][f]=p
            else:
                newcell[t][f]=newcell[t][f]+','+p
        #End for
    #End for
    pinsDict=newcell
    
#################
#
#    CONVERT PINS TO AS FEW GROUPS AS POSSIBLE
#
#################
    if __USE_GROUPS__:
        srtd_grps=getSrtdGrps_andUPDATEallpingroups()
        for t in pinsDict:
            for f in pinsDict[t]:
                pinsDict[t][f]=getGroups(pinsDict[t][f],srtd_grps)
            #End for
        #End for

#################
#
#    ORGANIZE DATA FOR EASIER OUTPUT
#
#################
    envCycTbls=Ddict(dict)
    for i in pinsDict:
        envCycTbls[i]={'pins':pinsDict[i],'dependencies':depsDict[i]}
    if __DEBUG__:
        pprint.pprint(pinsDict,out3file)
        pprint.pprint(depsDict,out3file)
        pprint.pprint(envCycTbls,out3file)


    pprint.pprint(envCycTbls)
    sys.exit(-1)


#################
#
#    PRINT FILES AND EXIT
#
#################
    ostr,astr=formatZippers(envCycTbls)
    ostr+=formatCycSets(envCycTbls)
    
    printstr = "SUCCESS!!! NEW FILES CREATED:\n"+__OUTPUT1_FILENAME__+"\n"+__OUTPUT2_FILENAME__
    if __DEBUG__:
        printstr += "\n"+__OUTPUT3_FILENAME__
    print printstr
    out1file.write(astr)
    out1file.write(ostr)
    out1file.close()

    #create pinlist.txt
    apexpins_str='\n'.join(__apexpins__)
    out2file.write(apexpins_str+'\n')
    out2file.close()

    if __DEBUG__:
        out3file.close()


#End main()
#-----------------------------------------------------------------------
#     BEGIN MAIN
#-----------------------------------------------------------------------
if __name__ == '__main__':
    main()
