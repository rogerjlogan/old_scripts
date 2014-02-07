import sys
import re
import pprint
import os
import inspect
import string
from datetime import datetime

__PROGRAM_NAME__ = "ACTABLE PARSER"
__AUTHOR__ = "AUTHOR: Roger Logan, LTXCredence Apps Engineer, Houston, TX"
__DATEMODIFIED__ = "LAST MODIFIED: December 5, 2008"
__VERSION__ = "v1.0"
__PROGFILE__ = "vectorgen.py"
__INPUTFILE__ = "<execution_mod.log>" #modify to deliminate vectors, add signal header, and last vector from init file

__DEBUG__ = True
__VERBOSE__ = False

#from Global.h
__ACTableLIST__     ,__CycleTableLIST__ ,__CycleLIST__  ,__VectorMapLIST__  ,__TestNameLIST__ = [],[],[],[],[]
__TITypeOfTestLIST__,__SoftBinLIST__    ,__HardBinLIST__,__DeviceTypeLIST__ ,__TempTypeLIST__ = [],[],[],[],[]

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

def getGlobals(glblcont):

    global __ACTableLIST__,__CycleTableLIST__,__CycleLIST__,__VectorMapLIST__,__TestNameLIST__
    global __TITypeOfTestLIST__,__SoftBinLIST__,__HardBinLIST__,__DeviceTypeLIST__,__TempTypeLIST__

    p = re.compile("(?:\s*)ACTable(?:\s*)=(?:\s*)\((?P<data>.*?)\)",re.DOTALL)
    actables=p.search(glblcont)
    actables = actables.group('data').split(',')
    for v in actables:__ACTableLIST__.append(v.strip())
    
    p = re.compile("(?:\s*)CycleTable(?:\s*)=(?:\s*)\((?P<data>.*?)\)",re.DOTALL)
    cycetables=p.search(glblcont)
    cycetables = cycetables.group('data').split(',')
    for v in cycetables:__CycleTableLIST__.append(v.strip())
    
    p = re.compile("(?:\s*)Cycle(?:\s*)=(?:\s*)\((?P<data>.*?)\)",re.DOTALL)
    cycles=p.search(glblcont)
    cycles = cycles.group('data').split(',')
    for v in cycles:__CycleLIST__.append(v.strip())
    
    p = re.compile("(?:\s*)VectorMap(?:\s*)=(?:\s*)\((?P<data>.*?)\)",re.DOTALL)
    vmaps=p.search(glblcont)
    vmaps = vmaps.group('data').split(',')
    for v in vmaps:__VectorMapLIST__.append(v.strip())
    
    p = re.compile("(?:\s*)TestName(?:\s*)=(?:\s*)\((?P<data>.*?)\)",re.DOTALL)
    testnames=p.search(glblcont)
    testnames = testnames.group('data').split(',')
    for v in testnames:__TestNameLIST__.append(v.strip())
    
    p = re.compile("(?:\s*)TITypeOfTest(?:\s*)=(?:\s*)\((?P<data>.*?)\)",re.DOTALL)
    typeoftests=p.search(glblcont)
    typeoftests = typeoftests.group('data').split(',')
    for v in typeoftests:__TITypeOfTestLIST__.append(v.strip())
    
    p = re.compile("(?:\s*)SoftBin(?:\s*)=(?:\s*)\((?P<data>.*?)\)",re.DOTALL)
    softbins=p.search(glblcont)
    softbins = softbins.group('data').split(',')
    for v in softbins:__SoftBinLIST__.append(v.strip())
    
    p = re.compile("(?:\s*)HardBin(?:\s*)=(?:\s*)\((?P<data>.*?)\)",re.DOTALL)
    hardbins=p.search(glblcont)
    hardbins = hardbins.group('data').split(',')
    for v in hardbins:__HardBinLIST__.append(v.strip())
    
    p = re.compile("(?:\s*)DeviceType(?:\s*)=(?:\s*)\((?P<data>.*?)\)",re.DOTALL)
    devtypes=p.search(glblcont)
    devtypes = devtypes.group('data').split(',')
    for v in devtypes:__DeviceTypeLIST__.append(v.strip())
    
    p = re.compile("(?:\s*)TempType(?:\s*)=(?:\s*)\((?P<data>.*?)\)",re.DOTALL)
    temptypes=p.search(glblcont)
    temptypes = temptypes.group('data').split(',')
    for v in temptypes:__TempTypeLIST__.append(v.strip())

#End getGlobals()

def parse(content):
    """
        Groups code into sections based on their control statements
    """
    #remove spaces next to symbols
    symbls=[',',':',';','\+','-','\*','/','=']
    for s in symbls:
        patrn=re.compile("(?:\s*)"+s+"(?:\s*)",re.DOTALL)
        content=re.sub(patrn,s,content)
    content=content.replace('\+','+')
    content=content.replace('\*','*')
    content=content.replace('\n',' ')
    content=content.replace(';',';\n')
    patrn=re.compile("begin(?:\s*)")
    content=re.sub(patrn,"\nbegin\n",content)
    patrn=re.compile("then(?:\s*)")
    content=re.sub(patrn,"then\n",content)
    patrn=re.compile("else(?:\s*)")
    content=re.sub(patrn,"else\n",content)
    
    patrn=re.compile("(?P<specaddon>.*)ACTableOpen(?P<actable>.*)",re.DOTALL)
    actcontObj=patrn.search(content)
    actcont='ACTableOpen'+actcontObj.group('actable')
    specaddon=actcontObj.group('specaddon')
    
    print actcont
    
    
#End parse()

def makeEnumsFile():

    enums_ofile = open(__ENUMS_OFILE__, "w")
    enums_ostr=__EVHDR__+'\n\n'
    if __TempTypeLIST__:
        enums_ostr+='enum TITestTemp\n{\n'
        for temp in __TempTypeLIST__:
            enums_ostr+='\t'+temp+',\n'
        enums_ostr=enums_ostr[:-2]+'\n};\n'
    if __DeviceTypeLIST__:
        enums_ostr+='enum TIDeviceType\n{\n'
        for dev in __DeviceTypeLIST__:
            enums_ostr+='\t'+dev+',\n'
        enums_ostr=enums_ostr[:-2]+'\n};\n'
    if __TITypeOfTestLIST__:
        enums_ostr+='enum TITestType\n{\n'
        for testtype in __TITypeOfTestLIST__:
            enums_ostr+='\t'+testtype+',\n'
        enums_ostr=enums_ostr[:-2]+'\n};\n'
    enums_ofile.write(enums_ostr)
    enums_ofile.close()
#End makeEnumFile()

def makeACTableFile():
    act_ofile = open(__ACTABLEFILE__, "w")
    act_ostr=''
    act_ofile.write(act_ostr)
    act_ofile.close()
#End makeACTableFile()

def makeAnlysFile(anlys_ostr):
    anlys_ofile = open(__ANLYS_OFILE__, "w")
    anlys_ofile.write(anlys_ostr)
    anlys_ofile.close()

#End makeAnlysFile()

#End CodeRetriever()
#-----------------------------------------------------------------------
#   main
#-----------------------------------------------------------------------
def main():
    global __ACTABLEFILE__
    
    # Get the arguments from the command line, except the first one.
    args = sys.argv[1:]
    if len(args) != 2:
        print "usage: "+__PROGFILE__+" "+__ACTABLEFILE__+" "+__GLOBALS_IFILE__
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
    actblcont = infile.read()
    infile = file(args[1], 'r')
    glblcont = infile.read()
    __ACTABLEFILE__=args[0]+'.new'

    #all spaces WITHOUT newlines
    ws_patrn = re.compile("([ \t\r\f\v]*)")
    #all spaces WITH newlines
    wsn_patrn = re.compile("(\s*)")
    wsn2_patrn = re.compile("(?P<ws>\s)(\s*)")
    if __STRIP_COMMENTS__:
        actblcont=strip(actblcont,'(*','*)')
        actblcont=strip(actblcont,'{','}')
        glblcont=strip(glblcont,'(*','*)')
        glblcont=strip(glblcont,'{','}')
    actblcont=wsn2_patrn.sub('\g<ws>',actblcont)
    glblcont=wsn2_patrn.sub('\g<ws>',glblcont)
    getGlobals(glblcont)

    parse(actblcont)




    makeEnumsFile()
    pstr = "SUCCESS!!! NEW FILES CREATED:\n"+__ACTABLEFILE__+"\n"+__ENUMS_OFILE__
    if __DEBUG__:
        pstr += "\n"+__ANLYS_OFILE__
        makeAnlysFile(actblcont)
#End main()
#-----------------------------------------------------------------------
#     BEGIN MAIN
#-----------------------------------------------------------------------
if __name__ == '__main__':
    main()
