"""
    Requirements:
         - Python2.3 or higher
    Function:
        Used to convert A5-80 patterns to Fusion Patterns
"""
__progfile__ = "v580pat.py"
__version__ = "v2.0"
__author__ = "AUTHOR: Roger Logan, Anora, Test Engineer, Dallas, TX"
__date__ = "LAST MODIFIED: August 20, 2013"

__delims__ = ['(*','*)','{','}','/*','*/','\"',';'] #delimiters for occasional removal

__a580chars__ = "LHXMV-01"#all possible characters for A5-80
__fusion_chars__ = "01XFV-LH"#translated characters for fusion
__dummy_char__ = 'X'#character to fill dummy vector at end of pattern
__default_tset__ = "TSET_default"
__cycleEvo__ = "cycletbl.evo"

__D_D_dict__ = {'LL':'c','HH':'C','HL':'k','LH':'K','XX':'X','--':'-'}#double drive dictionary

import sys
import re
import pprint
import os
import gzip
from string import *
from string import whitespace as ws
import time
import inspect

__EVHDR__ = "enVision:\"bl8:R11.1.0.WW1111:S3.5\"; /* 5.7 */\n\n"
__RD_ERROR__ = "Make sure you have permissions to READ files in this directory."
__WR_ERROR__ = "Make sure you have permissions to WRITE files in this directory."

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
    pinsPat = re.compile("\s*\d+\s*\"(\w+?)\"(?:.*?)hsd50_\w+:\d+,")
    __pinlist__ = pinsPat.findall(content)
    if not len(__pinlist__):
        exit("\n\n ERROR!!! No pins found in progfile.tl !!!\nLine: "+str(lineno())+"\n\n")
    donePat = re.compile("\"\s*(?P<pingroup>\w+)\s*\"\s*field\s*")
    found,done=False,False
    string=''
    __pingroups__ = Ddict( dict )
    for line in content.split('\n'):
        beg = line.rfind('(')+1
        end = line.find(')')
        if beg > 0:
            done=False
            found = True
            string=''
        if found:
            end = len(line)
            for i in range(beg,end):
                if line[i] == ')':
                    end = i
                    done=True
                    break
            string+=line[beg:end]
        if done:
            doneObj=donePat.search(line[end:].strip())
            if doneObj:
                pins = map(lambda p: p.strip(), string.split(',')) #strip ws from each element
                __pingroups__[doneObj.group('pingroup')] = pins
#End getAllPinsAllGroups()

def buildPinlistHdr(sighdr):
    maxlen=len(max(sighdr,key=len))
    padpins=[]
    for pin in sighdr:
        padpins.append(pin.ljust(maxlen))
    hdr = []
    for c in range(1,maxlen+1):
        row = "\" "
        for p in padpins:
            row += p[c-1]
        row += " \""
        hdr.append(row)
    return join(hdr,"\n")
#End buildPinlistHdr()

def translate(vectorStr):
    """
    requirement:from string import maketrans
    This will switch out characters from A5-80 convention to TI fusion convention
    A5-80 convention:
     'L' => cmp:low                             ,drv:hiz   ,loads:on    
     'H' => cmp:high                            ,drv:hiz   ,loads:on    
     'X' => cmp:mask                            ,drv:hiz   ,loads:on    
     'M' => cmp:expect midband (invalid level)  ,drv:hiz   ,loads:on    
     'V' => cmp:expect valid level (not midband),drv:hiz   ,loads:on    
     '-' => cmp:runtime repeat                  ,drv:repeat,loads:repeat
     '0' => cmp:mask                            ,drv:low   ,loads:off   
     '1' => cmp:mask                            ,drv:high  ,loads:off   
    """
    intab = __a580chars__
    outtab = __fusion_chars__
    trantab = maketrans(intab,outtab)
    vectorStr = vectorStr.translate(trantab,ws);#translate characters and remove ws
    return vectorStr
#End translate()

def myOpen(fileN, mode="r"):
    if fileN.endswith('.gz'):
        return gzip.open(fileN,mode)
    return open(fileN,mode)
#End myOpen()
def getVectHdr(rawvectHdr):
    rawvectHdr = rawvectHdr.replace('(','')
    rawvectHdr = rawvectHdr.replace(')','')
    pins = map(lambda p: p.strip(), rawvectHdr.split(',')) #make list and remove ws
    vectHdr = Ddict( dict )
    i = -1
    for pin in pins:
        i+=1
        colon = pin.find(':')
        if colon != -1:
            modifier = pin[colon+1:]
            pin = pin[:colon]
        else:modifier = ''
        if len(modifier) and modifier != 'D_D':
            err="\n\n ERROR !!! Unsupported modifier found: "+modifier
            err+="\n Currrently, only D_D is supported !"
            exit(err)
        vectHdr[i]["modifier"] = modifier
        if pin not in __pinlist__:
            if pin not in __pingroups__:
                exit("\n\n ERROR!!! Unknown pin element: "+pin+"\nLine: "+str(lineno())+"\n\n")
            else:#this must be a pingroup
                vectHdr[i]["pinLst"]=__pingroups__[pin]
        else:#this must be a pin
            vectHdr[i]["pinLst"]=pin.split(',')#make a single element list
        vectHdr[i]["name"]=pin
    return vectHdr
#End getVectHdr()

comm1Pat = re.compile("\/\*(.*?)\*\/",re.DOTALL)
comm2Pat = re.compile("\{(.*?)\}",re.DOTALL)
tsetPat = re.compile("(TSET\s+(?P<tset>\d+)\s*)")
globlabelPat = re.compile("(\s*GLOBAL\s+(?P<globlabel>\w+)\s*:\s*)")
labelPat = re.compile("(\s*(?P<label>\w+)\s*:\s*)")
callPat = re.compile("((?P<call>\s*CALL\s+\w+)\s*)")
def getNonData(string):
    globflag=False
    string = re.sub('\n','',string).strip()
    comments = ''.join(comm1Pat.findall(string)) + ''.join(comm2Pat.findall(string))
    for s in __delims__:
        comments = comments.replace(s,' ')
    the_rest = re.sub(comm1Pat,'',string).strip()
    the_rest = re.sub(comm2Pat,'',the_rest).strip()
    tsetObj = tsetPat.search(the_rest)
    try:tset = tsetObj.group('tset')
    except:tset = ''
    the_rest = re.sub(tsetPat,'',the_rest).strip()
    globlabelObj = globlabelPat.search(the_rest)
    label = ''
    if globlabelObj:
        globflag=True
        label = globlabelObj.group('globlabel')
    labelObj = labelPat.search(the_rest)
    if labelObj and not globflag:
        label = labelObj.group('label')
    the_rest = re.sub(globlabelPat,'',the_rest).strip()
    the_rest = re.sub(labelPat,'',the_rest).strip()
    callObj = callPat.search(the_rest)
    try:call=callObj.group('call')
    except:call=''
    micro = re.sub(callPat,'',the_rest).strip()
    return comments,call,label,micro,tset
#End getNonData()

def formatVector(comments,call,label,data,tset,micro):
    if len(comments):
        comments = ' \"'+comments+'\"'
    comments+='\n'
    if len(call):
        call = '\n#############\n'+call+'\n#############\n\n'
    if len(label):
        label = '$'+label+'\n'
    if not len(data):
        exit("\n\n ERROR !!! No Data is Being Formatted !\nLine: "+str(lineno())+"\n\n")
    else:
        data = '* '+data+' *'
    if len(tset):
        tset = ' TSET_'+tset
    if len(micro):
        micro = ' <'+micro+'>'
    return comments+call+label+data+tset+';'+micro
#End formatVector()

__sighdr__,__sighdrStrs__ = [],[]
def getSigHdr(vectHdr):
    global __sighdr__,__sighdrStrs__
    notused,pinlist = [],[]
    sighdrStr = ''
    for i in range(0,len(vectHdr)):
        pinlist += vectHdr[i]['pinLst']
        sighdrStr += '\n        %'+' '.join(vectHdr[i]['pinLst'])
    notused = [p for p in __pinlist__ if p not in pinlist]
    sighdrStr += '\n        %'+' '.join(notused)
    sighdr = pinlist+notused
    if sighdr not in __sighdr__:
        __sighdr__.append(sighdr)
        __sighdrStrs__.append(sighdrStr.strip())
    return __sighdr__.index(sighdr)
#End getVectHdr()

def reOrgData(vectHdr,data,sighdrNum):
    data = translate(data)
    try:sighdr = __sighdr__[sighdrNum]
    except:exit("\n\n ERROR !!! Signal order out of range !\nLine: "+str(lineno())+"\n\n")
    vector=''
    end=0
    for i in range(0,len(vectHdr)):
        offset = len(vectHdr[i]['pinLst'])
        beg=end
        end+=offset
        if vectHdr[i]['modifier']=='D_D':
            dd_data = ''
            for ii in range(beg,beg+offset):
                vector += __D_D_dict__[data[ii]+data[ii+offset]]
            beg+=offset
            end+=offset
        else:
            vector+=data[beg:end]
    vector+='X'*(len(sighdr)-len(vector)) #pad vector with 'X'
    return vector
#End reOrgData

def getVectData(patname,rawvectData,vectHdr):
    #build regex pattern from vectHdr
    data=''
    for i in range(0,len(vectHdr)):
        data+='['+re.escape(__a580chars__)+']{'+str(len(vectHdr[i]["pinLst"]))+'}\s*'
        if vectHdr[i]["modifier"] == "D_D":
            data+='['+re.escape(__a580chars__)+']{'+str(len(vectHdr[i]["pinLst"]))+'}\s*'
    data += "$"
    data = data.strip()
    vectPat = re.compile("(?P<front>.*?)\s*(?P<data>"+data+")\s*",re.DOTALL)
    vectors = rawvectData.split(';')
    tset=''
    vectData=''
    sighdrNum = getSigHdr(vectHdr)
    for i,v in enumerate(vectors):
        dataObj = vectPat.search(v)
        try:
            front = dataObj.group('front')
            data = dataObj.group('data')
        except:
            front = ''
            data = ''
            continue
        comments,call,label,micro,temptset = getNonData(front)
        data = reOrgData(vectHdr,data,sighdrNum)
        if len(temptset):#keep a running track of tset
            tset = temptset
        vector = formatVector(comments,call,label,data,tset,micro)
        if len(vector):
            vectData+=vector
    beg_label = '\n$'+patname+'_begin\n'
    end_label = '\n$'+patname+'_end\n'
    dummyvect = '* '+__dummy_char__*len(__sighdr__[sighdrNum])+' *;'
    vectData = beg_label+vectData+end_label+dummyvect
    return vectData,sighdrNum
#End getVectData()

def build_ostr(hdrcomm,patname,sighdrNum,pinlistHdr,vectData):
    ostr=__EVHDR__
    ostr+=hdrcomm
    ostr+="Pattern "+patname+' {\n'
    ostr+="Type Cpm;\n"
    ostr+=__CREATION_MSG__
    ostr+="\"############################################################################################\"\n"
    ostr+="\"#WARNINGS....                                                                              #\"\n"
    ostr+="\"#           -You must manually convert micro-instructions between < and > below            #\"\n"
    ostr+="\"#           -The last vector is denoted by <HALT>                                          #\"\n"
    ostr+="\"#            Vectors below <HALT> are subroutines and must be placed where there is a CALL #\"\n"
    ostr+="\"############################################################################################\"\n\n"
    ostr+="Default WaveformTable "+__default_tset__+";\n"
    ostr+="Default SignalHeader SH"+str(sighdrNum)+";\n"
    ostr+=pinlistHdr+'\n'
    ostr+=vectData+'\n}'
    return ostr
#End build_ostr()

__pats_created__=[]
def createPatEvo(tp_path,patname,ostr):
    global __pats_created__
    evo_path = tp_path+"EvosRaw"
    if not os.path.exists(evo_path):
        try:
            os.makedirs(evo_path)    
        except:exit("Directory WRITE/CREATE Error !!!: "+evo_path+"\n"+__WR_ERROR__+"\nLine: "+str(lineno())+"\n\n")
    try:
        pathfn = os.path.join(evo_path,patname+'.evo')
        patfile = open(pathfn, "w")
        patfile.write(ostr)
        patfile.close()
    except:exit("Directory WRITE/CREATE Error !!!: "+patname+".evo\n"+__WR_ERROR__+"\nLine: "+str(lineno())+"\n\n")
    __pats_created__.append(pathfn)
#End createPatEvo()

def processPat(pathfn):
    global __vectHdrs__
    tp_path, fn = os.path.split(pathfn)
    patname = os.path.splitext(fn)[0]
    print "Processing",fn,"..."
    vectPat = re.compile("(?P<hdrcomm>.*?)filetype\s*=\s*hsd50\s*;\s*vector\s*\((?P<pins>.*)\)\s*\{(?P<data>.*)\}\s*;",re.DOTALL)
    fp = myOpen(pathfn)
    vectObj = vectPat.search(fp.read())
    try:
        hdrcomm = vectObj.group('hdrcomm')
        rawvectHdr = vectObj.group('pins')
        rawvectData = vectObj.group('data').replace('\n','')
        fp.close()
    except:
        exit("\n\n ERROR !!! VECTOR DATA NOT FOUND !!!\nLine: "+str(lineno())+"\n\n")
        fp.close()
    for s in __delims__:
        hdrcomm=hdrcomm.replace(s,' ')
    hdrcomm = hdrcomm.strip()
    if len(hdrcomm):
        hdrcomm = '/*'+hdrcomm+'*/\n\n'
    vectHdr = getVectHdr(rawvectHdr)
    vectData,sighdrNum = getVectData(patname,rawvectData,vectHdr)
    pinlistHdr = buildPinlistHdr(__sighdr__[sighdrNum])
    ostr = build_ostr(hdrcomm,patname,sighdrNum,pinlistHdr,vectData)
    createPatEvo(tp_path,patname,ostr)
#End processPat()

def createCycEvo():
    sigHdrStr = ""
    cycStr =__EVHDR__
    cycStr+="WaveformTable A580PatGrp A580PatGrp {\n"
    cycStr+="    Cell \"A580PatGrp.Pins\" S   ScanOut              { Data 6 Serial; Color 6;  }\n"
    cycStr+="    Cell \"A580PatGrp.Pins\" D   ScanIn               { Data 6 Serial; Color 6;  }\n"
    cycStr+="    Cell \"A580PatGrp.Pins\" d   CPMDPM               { Data 3 Other;  Color 3;  }\n"
    cycStr+="    Cell \"A580PatGrp.Pins\" F   FloatStrobe_F        { Data 0;        Color 3/6;}\n"
    cycStr+="    Cell \"A580PatGrp.Pins\" V   ExpectValid          { Data 0;        Color 3/6;}\n"
    cycStr+="    Cell \"A580PatGrp.Pins\" l/h Drive_lh             { Data 6/7;      Color 3/6;}\n"
    cycStr+="    Cell \"A580PatGrp.Pins\" L/H Drive_LH             { Data 6/7;      Color 3/6;}\n"
    cycStr+="    Cell \"A580PatGrp.Pins\" 0/1 Strobe_01            { Data 0/1;      Color 3/6;}\n"
    cycStr+="    Cell \"A580PatGrp.Pins\" x/X StrobeMask           { Data 2/3;      Color 3/6;}\n"
    cycStr+="    Cell \"A580PatGrp.Pins\" c   DoubleClock00        { Data 6;        Color 3;  }\n"
    cycStr+="    Cell \"A580PatGrp.Pins\" C   DoubleClock11        { Data 7;        Color 6;  }\n"
    cycStr+="    Cell \"A580PatGrp.Pins\" k   DoubleClock10        { Data 6;        Color 3;  }\n"
    cycStr+="    Cell \"A580PatGrp.Pins\" K   DoubleClock01        { Data 7;        Color 6;  }\n"
    cycStr+="    Cell \"A580PatGrp.Pins\" -   Continue             { Data 6;        Color 6;  }\n"
    cycStr+="}\n"
    cycStr+="\n"
    cycStr+="PatternGroup A580PatGrp {\n"
    cycStr+="    SignalHeader"
    for i,sighdr in enumerate(__sighdrStrs__):
        cycStr+=" SH"+str(i)+""
        sigHdrStr+="SignalHeader SH"+str(i)+" {\n"
        sigHdrStr+="    Signals {\n"
        sigHdrStr+="        "+__sighdrStrs__[i]+"\n"
        sigHdrStr+="    }\n"
        sigHdrStr+="}\n"
    cycStr+=";\n}\n\n"
    ostr = cycStr+sigHdrStr
    try:
        cycfile = open(__cycleEvo__, "w")
        cycfile.write(ostr)
        cycfile.close()
    except:exit("Directory WRITE/CREATE Error !!!: "+__cycleEvo__+"\n"+__WR_ERROR__+"\nLine: "+str(lineno())+"\n\n")
#End createCycEvo()

#-----------------------------------------------------------------------
#   main
#-----------------------------------------------------------------------
def main():
    global __CREATION_MSG__
#    __PATTERN__=args[0][0:len(args[0])-3]
    
    # Get the arguments from the command line, except the first one.
    args = sys.argv[1:]
    if not (len(args)>1 and args[0][-3:]==".tl" and (args[1][-3:]==".tp" or args[1][-6:]==".tp.gz")):
        err="\nusage: python "+__progfile__+" progfile.tl *.tp"
        exit(err)
    try:
        infile = file(args[0], 'r')
        content = infile.read()
        infile.close()
    except:
        exit("File READ Error !!!: "+args[0]+"\n"+__RD_ERROR__+"\nLine: "+str(lineno())+"\n\n")
    localtime = time.asctime(time.localtime(time.time()))
    __CREATION_MSG__ = "\"Pattern generated by: "+__progfile__+" "+__version__+"\"\n\""+__author__+"\"\n\"PATTERN CREATION DATE: "+str(localtime)+"\"\n\n"
    
    getAllPinsAllGroups(content)
    
    for pathfn in args[1:]:
        processPat(pathfn)
    
    createCycEvo()

    print "\nSUCCESS !!! Files created:"+"\n\n"+__cycleEvo__+"\n\n"+'\n'.join(__pats_created__)+"\n\n"
    print "WARNING !!! \"EvosRaw\" need lots of hand edits due the following:"
    print "     - Micro-instructions were preserved between \'<\' and \'>\' but not converted."
    print "     - Subroutines may exist as vectors below <HALT> micro-instruction, but must be placed where CALL exits."
    print "     - Patterns over 4k vectors will need to be modified as Cpm calling Dpm. pushCPMintoDPM.py may be an option.\n\n"
    
    print __progfile__+" "+__version__
    print __author__
    print __date__+"\n\n"

#End main()
#-----------------------------------------------------------------------
#     BEGIN MAIN
#-----------------------------------------------------------------------
if __name__ == '__main__':
    main()
