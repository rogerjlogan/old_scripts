"""
    Requirements:
         - Python2.3 or higher
    Function:
        Used to get marker information for each vseries pin
        this info includes levels, formats, and timing.
"""
import sys
import re
import pprint
import os
from string import *
from string import whitespace as ws
import time
import inspect
import pyparsing

__progfile__ = "markers.py"
__author__ = "AUTHOR: Roger Logan, Anora, Test Engineer, Dallas, TX"
__date__ = "LAST MODIFIED: August 20, 2013"
__strip_nested__ = False # Set this to 'True' if you think you might have nested comments. It will take longer, but will do a better job

__delims__ = ['(*','*)','{','}','/*','*/','\"',';'] #delimiters for occasional removal

dupe_err  = "You may have multiple conditions (TIDeviceType, etc.)\n"
dupe_err += "Create a file for input that only has one set of conditions.\n"
__localtime__ = time.asctime(time.localtime(time.time()))

__EVHDR__ = "enVision:\"bl8:R11.1.0.WW1111:S3.5\"; /* 5.7 */\n\n"
__RD_ERROR__ = "Make sure you have permissions to READ files in this directory."
__WR_ERROR__ = "Make sure you have permissions to WRITE files in this directory."
__PINGROUP_OFILE__ = "pinlists.evo"

def removeComments(string):
    """Remove all comments from string"""
    if __strip_nested__:
        print "Removing nested comments...\nIf you are sure that you don't have nested comments, set \"__strip_nested__ = False\"\nIt will be faster."
        print "Warning: You can still have problems if you have unmatched comment delimiters inside literal strings.\n\n"
        comment1 = pyparsing.nestedExpr("(*", "*)").suppress()
        comment2 = pyparsing.nestedExpr("{", "}").suppress()
        string = comment1.transformString(string)         
        string = comment2.transformString(string)         
    else:
        print "Warning! Removing simple comments...\nIf you have nested comments set \"__strip_nested__ = True\" and re-run."
        string = re.sub(re.compile("\(\*.*?\*\)",re.DOTALL ) ,"" ,string)
        string = re.sub(re.compile("\{.*?\}",re.DOTALL ) ,"" ,string)
    return string
#End removeComments()

def stripLst(string):
    """String whitesspace from each element in a string of comma separated elements."""
    return map(lambda p: p.strip(), string.split(',')) #strip ws from each element
#End stripLst()

class Ddict(dict):
    def __init__(self, default=None):
        self.default = default
    def __getitem__(self, key):
        if not self.has_key(key):
            self[key] = self.default()
        return dict.__getitem__(self, key)
#End Ddict()

def lineno():
    """Returns the current line number in our program."""
    return inspect.currentframe().f_back.f_lineno
#End lineno()

def getAllPinsAllGroups(content):
    global __pinlist__,__pingroups__
    pintablePat = re.compile("PINTABLEOPEN(.*?)PINTABLECLOSE",re.DOTALL)
    pintable = pintablePat.findall(content)
    if not pintable:
        exit("\n\nERROR !!!  No PinTableOpen to PinTableClose found !\nLine: "+str(lineno())+"\n\n")
    elif len(pintable)>1:
        err  = "\n\nERROR !!!  More than one PinTableOpen to PinTableClose found !\n"
        exit(err+dupe_err+"Line: "+str(lineno())+"\n\n")
    else:
        content = pintable[0]
    pinsetPat = re.compile("PINSET\s*\(\s*(?P<pinset>.*?)\s*,(?:.*?),(?:.*?),(?:.*?),(?:.*?),(?:.*?),(?:.*?)\)\s*;",re.DOTALL)
    pinsetLst = pinsetPat.findall(content)
    if not pinsetLst:
        exit("\n\nERROR !!!  No PinSet statements found !\nLine: "+str(lineno())+"\n\n")
    elif len(set(pinsetLst)) != len(pinsetLst):
        err  = "\n\nERROR !!!  Duplicate PinSet statements found !\n"
        exit(err+dupe_err+"Line: "+str(lineno())+"\n\n")
    else:
        __pinlist__ = pinsetLst
    pinlistsetPat = re.compile("PINLISTSET\s*\(\s*(.*?)\s*\)\s*;",re.DOTALL)
    pinlistset = pinlistsetPat.findall(content)
    __pingroups__ = Ddict( dict )
    if not pinlistset:
        exit("\n\nERROR !!!  No PinListSet statements found !\nLine: "+str(lineno())+"\n\n")
    else:
        dupe_pinlistset  = "WARNING !!!  Duplicate PinListSet statements found !"
        for i,pinlist in enumerate(pinlistset):
            rawpinlist = stripLst(pinlist)
            group = rawpinlist[0]
            pinlist = rawpinlist[1:]
            if group in __pingroups__:
                print dupe_pinlistset+" Updating "+group
                __pingroups__[group] += pinlist
            else:
                __pingroups__[group] = pinlist
        #End for
    #sanity check
    for grp in __pingroups__:
        for pin in __pingroups__[grp]:
            if pin not in __pingroups__.keys() and pin not in __pinlist__:
                exit("\n\nERROR !!!  Unknown pin or pingroup: "+pin+"\nLine: "+str(lineno())+"\n\n")
    __pingroups__['ALLPINS_SUPERSET'] = __pinlist__
    for grp in __pingroups__:
        __pingroups__[grp] = flattenPinGroup(__pingroups__[grp])
#End getAllPinsAllGroups()

def flattenPinGroup(inLst):
    """This function will take a list of pins/pingroups and return a list of pins with no pingroups."""
    pinlist=[]
    for item in inLst:
        for v in extract(item):
            pinlist.append(v)
    return pinlist
def extract(item2chk):
    """This recursive function will keep calling itself until all pins have been found and returned as a list of pins."""
    if item2chk in __pinlist__:
        yield item2chk
    elif item2chk in __pingroups__.keys():
        for item in __pingroups__[item2chk]:
            for v in extract(item):
                yield v
    else:
        exit("\n\nError !!! Unknown pin element: "+item2chk++"\nLine: "+str(lineno())+"\n\n")
#End extract()

def mkPinGroupEVOFile(pingroups,fn):
    try:
        pingrp_ofile = open(fn, "w")
    except:
        err="File Error: "+fn+"\n"
        err+=__WR_ERROR__
        exit(err+"\nLine: "+str(lineno())+"\n\n")
    pingrp_ostr=__EVHDR__+mkHeader(__progfile__,__author__)+'\n\n'

    #build max length of parameters
    maxlen=0
    for grp in pingroups:
        if len(grp) > maxlen:
            maxlen=len(grp)
        #End if
    #End for

    for grp in pingroups:
        spaces = ' '
        for i in range(maxlen-len(grp)):
            spaces+=' '
        grpStr =  '+'.join(pingroups[grp])
        pingrp_ostr+="PinGroup "+grp+spaces+"{ Group = Expr { String = \""+grpStr+"\"; } }\n"
    #End for    

    pingrp_ofile.write(pingrp_ostr)
    pingrp_ofile.close()
    
    ostr="SUCCESS!!! NEW FILES CREATED:\n"
    ostr+=fn+"\n"
    print ostr
#End mkPinGroupEVOFile()

def mkHeader (prog,auth):
    localtime = time.asctime(time.localtime(time.time()))
    header  = "// This file was generated by: "+prog+"\n"
    header += "// "+auth+"\n"
    header += "// CREATION DATE: "+str(localtime)+"\n\n"
    return header
#End mkHeader()

def getCycleTables(content):
    ctablePat = re.compile("CYCLETABLEOPEN(.*?)CYCLETABLECLOSE",re.DOTALL)
    tablePat = re.compile("\((?P<table>.*?)\)",re.DOTALL)
    csetPat = re.compile("CYCLESET\s*\((?P<cycle>.*?),(?P<acg>.*?),(?P<pins>.*?)\)",re.DOTALL)
    ctables = ctablePat.findall(content)
    __cycletables__ = Ddict( dict )
    for ctable in ctables:
        tableElemsLst = ctable.split(';')
        tableObj = tablePat.search(tableElemsLst[0])
        try:
            table = tableObj.group('table').strip()
            __cycletables__[table] = Ddict( dict )
        except:
            exit("\n\nError !!! CycleTable name not found !\nLine: "+str(lineno())+"\n\n")
        for elem in tableElemsLst[1:]:
            csetObj = csetPat.search(elem)
            if csetObj:
                cycle = csetObj.group('cycle').strip()
                acg = csetObj.group('acg').strip()
                pins = csetObj.group('pins').strip()
                __cycletables__[table][cycle]['acg'] = acg
                __cycletables__[table][cycle]['pins'] = pins
    if not len(__cycletables__):
        exit("\n\nError !!! No valid CycleTable found !\nLine: "+str(lineno())+"\n\n")
#End getCycleTables()

def getFormatTables(content):
    """This is just a wrapper procedure to populate __defaultformats__ and __formats__ in order."""
    getFTables(content,True)
    getFTables(content)
#End getFormatTables()
def getFTables(content,default=False):
    global __defaultformats__,__formats__
    if default:
        ftablePat = re.compile("FORMATTABLEOPEN(.*?)FORMATTABLECLOSE",re.DOTALL)
        namePat = re.compile("\((?P<name>.*?)\)",re.DOTALL)
    else:
        ftablePat = re.compile("FORMATSETUPOPEN(.*?)FORMATSETUPCLOSE",re.DOTALL)
        namePat = re.compile("\((?P<name>.*?),(?P<defname>.*?)\)",re.DOTALL)
    setinPat = re.compile("FORMATSETIN\s*\((?P<dset0>.*?),(?P<dset1>.*?),(?P<pins>.*?)\)",re.DOTALL)
    setoutPat = re.compile("FORMATSETOUT\s*\((?P<rcv>.*?),(?P<pins>.*?)\)",re.DOTALL)
    setinoutPat = re.compile("FORMATSETINOUT\s*\((?P<dset0>.*?),(?P<dset1>.*?),(?P<rcv>.*?),(?P<pins>.*?)\)",re.DOTALL)
    ftable = ftablePat.findall(content)
    if not ftable:
        if default:
            exit("\n\nERROR !!!  No FormatTableOpen to FormatTableClose found !\nLine: "+str(lineno())+"\n\n")
        else:
            exit("\n\nERROR !!!  No FormatSetupOpen to FormatSetupClose found !\nLine: "+str(lineno())+"\n\n")
    formats = Ddict( dict )
    for table in ftable:
        tableElemsLst = table.split(';')
        nameObj = namePat.search(tableElemsLst[0])
        try:
            name = nameObj.group('name').strip()
            formats[name] = Ddict( dict )
        except:
            exit("\n\nError !!! FormatTable name not found !\nLine: "+str(lineno())+"\n\n")
        tableElemsLst = tableElemsLst[1:]
        if not default:
            #Let's inherit the correct default table values
            defname = nameObj.group('defname').strip()
            if len(__defaultformats__[defname]):
                formats[name] = __defaultformats__[defname]
            else:
                exit("\n\nError !!! Default table referenced has not been defined: "+defname+" (case insensitive)\nLine: "+str(lineno())+"\n\n")
        for elem in tableElemsLst:
            setinObj = setinPat.search(elem)
            setoutObj = setoutPat.search(elem)
            setinoutObj = setinoutPat.search(elem)
            if setinObj:
                pins = setinObj.group('pins').strip()
                if pins in __pinlist__:
                    formats[name][pins]['dset0'] = setinObj.group('dset0').strip()
                    formats[name][pins]['dset1'] = setinObj.group('dset1').strip()
                    formats[name][pins]['rcv'] = None
                elif pins in __pingroups__.keys():
                    for p in __pingroups__[pins]:
                        formats[name][p]['dset0'] = setinObj.group('dset0').strip()
                        formats[name][p]['dset1'] = setinObj.group('dset1').strip()
                        formats[name][p]['rcv'] = None
                else:
                    exit("\n\nError !!! Unknown pin element in "+name+" !\nLine: "+str(lineno())+"\n\n")
            elif setoutObj:
                pins = setoutObj.group('pins').strip()
                if pins in __pinlist__:
                    formats[name][pins]['dset0'] = None
                    formats[name][pins]['dset1'] = None
                    formats[name][pins]['rcv'] = setoutObj.group('rcv').strip()
                elif pins in __pingroups__.keys():
                    for p in __pingroups__[pins]:
                        formats[name][p]['dset0'] = None
                        formats[name][p]['dset1'] = None
                        formats[name][p]['rcv'] = setoutObj.group('rcv').strip()
                else:
                    exit("\n\nError !!! Unknown pin element in "+name+" !\nLine: "+str(lineno())+"\n\n")
            elif setinoutObj:
                pins = setinoutObj.group('pins').strip()
                if pins in __pinlist__:
                    formats[name][pins]['dset0'] = setinoutObj.group('dset0').strip()
                    formats[name][pins]['dset1'] = setinoutObj.group('dset1').strip()
                    formats[name][pins]['rcv'] = setinoutObj.group('rcv').strip()
                elif pins in __pingroups__.keys():
                    for p in __pingroups__[pins]:
                        formats[name][p]['dset0'] = setinoutObj.group('dset0').strip()
                        formats[name][p]['dset1'] = setinoutObj.group('dset1').strip()
                        formats[name][p]['rcv'] = setinoutObj.group('rcv').strip()
                else:
                    exit("\n\nError !!! Unknown pin element in "+name++"\nLine: "+str(lineno())+"\n\n")
            #End if
        #End for
    #End for
    if default:
        __defaultformats__ = formats
    else:
        __formats__ = formats
#End getFTables()

def getACTables(content):
    """This is just a wrapper procedure to populate __defaultACTs__ and __ACTs__ in order."""
    getacTables(content,True)
    getacTables(content)
#End getACTables()
def getacTables(content,default=False):
    global __defaultACTs__,__ACTs__
    if default:
        actablePat = re.compile("ACTABLEOPEN(.*?)ACTABLECLOSE",re.DOTALL)
        namePat = re.compile("\((?P<name>.*?)\)",re.DOTALL)
    else:
        actablePat = re.compile("ACSETUPOPEN(.*?)ACSETUPCLOSE",re.DOTALL)
        namePat = re.compile("\((?P<name>.*?),(?P<act>.*?),(?P<cyt>.*?),(?P<prt>.*?),(?P<base_per>.*?),(?P<dct>.*?),(?P<fmtsu>.*?)\)",re.DOTALL)
    csetPat = re.compile("CYCLESET\s*\((?P<cycle>.*?),(?P<acg>.*?),(?P<pins>.*?)\)",re.DOTALL)
    acsetinPat = re.compile("ACSETIN\s*\((?P<t3>.*?),(?P<t1>.*?),(?P<t2>.*?)\)",re.DOTALL)
    acsetoutPat = re.compile("ACSETOUT\s*\((?P<t4>.*?),(?P<t5>.*?)\)",re.DOTALL)
    acsetinoutPat = re.compile("ACSETINOUT\s*\((?P<t3>.*?),(?P<t1>.*?),(?P<t2>.*?),(?P<t4>.*?),(?P<t5>.*?)\)",re.DOTALL)
    actables = actablePat.findall(content)
    if not actables:
        if default:
            exit("\n\nERROR !!!  No ACTableOpen to ACTableClose found !\nLine: "+str(lineno())+"\n\n")
        else:
            exit("\n\nERROR !!!  No ACSetupOpen to ACSetupClose found !\nLine: "+str(lineno())+"\n\n")
    acts = Ddict( dict )
    for actable in actables:
        tableElemsLst = actable.split(';')
        nameObj = namePat.search(tableElemsLst[0])
        try:
            name = nameObj.group('name').strip()
            acts[name] = Ddict( dict )
        except:
            exit("\n\nError !!! ACTable name not found !\nLine: "+str(lineno())+"\n\n")
        tableElemsLst = tableElemsLst[1:]
        if not default:
            #Let's inherit the correct default table values
            act = nameObj.group('act').strip()
            cyt = nameObj.group('cyt').strip()
            prt = nameObj.group('prt').strip()
            base_per = nameObj.group('base_per').strip()
            dct = nameObj.group('dct').strip()
            fmtsu = nameObj.group('fmtsu').strip()
            if len(__defaultACTs__[defname]):
                acts[name] = __defaultACTs__[defname]
            else:
                exit("\n\nError !!! Default table referenced has not been defined: "+defname+" (case insensitive)\nLine: "+str(lineno())+"\n\n")
        continue
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        for elem in tableElemsLst:
            
            acsetinObj = setinPat.search(elem)
            acsetoutObj = setoutPat.search(elem)
            acsetinoutObj = setinoutPat.search(elem)
            if setinObj:
                pins = setinObj.group('pins').strip()
                if pins in __pinlist__:
                    acts[name][pins]['dset0'] = setinObj.group('dset0').strip()
                    acts[name][pins]['dset1'] = setinObj.group('dset1').strip()
                    acts[name][pins]['rcv'] = None
                elif pins in __pingroups__.keys():
                    for p in __pingroups__[pins]:
                        acts[name][p]['dset0'] = setinObj.group('dset0').strip()
                        acts[name][p]['dset1'] = setinObj.group('dset1').strip()
                        acts[name][p]['rcv'] = None
                else:
                    exit("\n\nError !!! Unknown pin element in "+name++"\nLine: "+str(lineno())+"\n\n")
            elif setoutObj:
                pins = setoutObj.group('pins').strip()
                if pins in __pinlist__:
                    acts[name][pins]['dset0'] = None
                    acts[name][pins]['dset1'] = None
                    acts[name][pins]['rcv'] = setoutObj.group('rcv').strip()
                elif pins in __pingroups__.keys():
                    for p in __pingroups__[pins]:
                        acts[name][p]['dset0'] = None
                        acts[name][p]['dset1'] = None
                        acts[name][p]['rcv'] = setoutObj.group('rcv').strip()
                else:
                    exit("\n\nError !!! Unknown pin element in "+name++"\nLine: "+str(lineno())+"\n\n")
            elif setinoutObj:
                pins = setinoutObj.group('pins').strip()
                if pins in __pinlist__:
                    acts[name][pins]['dset0'] = setinoutObj.group('dset0').strip()
                    acts[name][pins]['dset1'] = setinoutObj.group('dset1').strip()
                    acts[name][pins]['rcv'] = setinoutObj.group('rcv').strip()
                elif pins in __pingroups__.keys():
                    for p in __pingroups__[pins]:
                        acts[name][p]['dset0'] = setinoutObj.group('dset0').strip()
                        acts[name][p]['dset1'] = setinoutObj.group('dset1').strip()
                        acts[name][p]['rcv'] = setinoutObj.group('rcv').strip()
                else:
                    exit("\n\nError !!! Unknown pin element in "+name++"\nLine: "+str(lineno())+"\n\n")
            #End if
        #End for
    #End for
    if default:
        __defaultACTs__ = acts
    else:
        __ACTs__ = acts
#End getacTables()





#-----------------------------------------------------------------------
#   main
#-----------------------------------------------------------------------
def main():

    # Get the arguments from the command line, except the first one.
    args = sys.argv[1:]
    if len(args)>1:
        err="\nusage: python "+__progfile__+" progfile.itp"
        exit(err+"\nLine: "+str(lineno())+"\n\n")
    try:
        infile = file(args[0], 'r')
        content = infile.read()
        infile.close()
    except:
        exit("File READ Error !!!: "+args[0]+"\n"+__RD_ERROR__+"\nLine: "+str(lineno())+"\nLine: "+str(lineno())+"\n\n")
    
    content = removeComments(content).upper()
    getAllPinsAllGroups(content)
    mkPinGroupEVOFile(__pingroups__,__PINGROUP_OFILE__)
    getFormatTables(content)
    getCycleTables(content)
#    getACTables(content)

    pprint.pprint(__defaultformats__,width=100)

#    getDCTables(content)

    
    print __progfile__
    print __author__
    print __date__+"\n\n"

#End main()
#-----------------------------------------------------------------------
#     BEGIN MAIN
#-----------------------------------------------------------------------
if __name__ == '__main__':
    main()
