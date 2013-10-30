import sys
import re
import pprint
import os
#import string
from string import *
import time

# This program generates vectors starting with the last vector of a pattern.
# It requires a signal header, the last vector of the pattern to appended, and a 
# modified execution log from Polaris (simulation output that shows drives and strobes)
# or created by hand from deliberate drive/strobe instructions.
# Each vector must be delimited by 3 asterisks (***)

__PROGRAM_NAME__ = "VECTOR GENERATOR"
__AUTHOR__ = "AUTHOR: Roger Logan, Anora, Test Engineer, Dallas, TX"
#Created: March 14, 2011"
__DATEMODIFIED__ = "LAST MODIFIED: Jan 18, 2013"
__VERSION__ = " v2.1"
__PROGFILE__ = "vectorgen.py"
__INPUTFILE__ = "<execution_mod.log>" #modify to deliminate vectors with 3 asterisks (***), must contain a valid envision signal header
__OUTPUTFILE__ = "new_vectors.txt"  #copy these into your pattern.evo

__EVO_HEADER__ = "enVision:\"bl8:R10.3.2.WW0104:S3.0\"; /* 5.7 */\n\n"
__CREATION_MSG__ = ""#written in main time.time()

__WFT__ = "WFT3"             #Default Waveform Table
__SGH__ = "Sig_Header_Dev"   #Default Signal Header
__MINVECTORLENGTH__ = 32
__DEBUG__ = 0
__CLEARSTROBES__ = 1 # USE THIS TO MASK STROBES DURING DRIVE VECTORS

__pins__ = [] #all pins from signal header
__pinhdr__ = "" #all pins from signal header to be dislayed vertically
__startvctr__ = [] #last vector of init pattern
__addvectors__ = [] #these are the vectors to be added to init pattern
__strobetype__ = 0 #gathered from user to determine whether to strobe 0's, 1's, or char from input
__control__ = 0 #0=Control:APPLY, 1=Control:REMOVE

class TextException(Exception): pass

def replace_all(oldlist, oldstr, newstr):
    newlist=[]
    for elem in oldlist:
        if elem == oldstr:
            elem = newstr
        newlist.append(elem)
        #End if
    #End for
    return newlist
#End replace_all()

def str2list(string):
    mylist = []
    for ch in string:
        mylist.append(ch)
    return mylist
#End string2list()

def buildPinlistHeader():
    global __pinhdr__
    offset=3
    maxlen=len(max(__pins__,key=len))
    padpins=[]
    for pin in __pins__:
        padpins.append(pin.ljust(maxlen))
    hdr = []
    for c in range(1,maxlen):
        row = "\" "
        for p in padpins:
            row += p[c-1]
        row += " \""
        hdr.append(row)
    __pinhdr__ = join(hdr,"\n")
#End buildPinlistHeader

def getPins(content):
    global __pins__
    p=re.compile("SIGNALHEADER:(?P<signalhdr>.*)")
    signalhdr=p.search(content)
    signalhdr=signalhdr.group('signalhdr')
    __pins__ = split(signalhdr,",")
    buildPinlistHeader()
#End getPins()

def getStartVector(content):
    global __startvctr__
    p=re.compile("VECTOR:(?P<startvctr>.*)")
    startvctr=p.search(content)
    __startvctr__=strip(startvctr.group('startvctr'))
    
#End getStartVector()

def makeOutputFile(ostr):
    global __OUTPUTFILE__
    patnamePat=re.compile("(?P<patname>.*?)\.")
    patnameObj=patnamePat.search(__OUTPUTFILE__)
    patname=strip(patnameObj.group('patname'))
    __OUTPUTFILE__=patname+".evo"

    header=__EVO_HEADER__
    header=header+"Pattern "+patname+" {\n"
    header=header+"Type Dpm;\n"
    header=header+"Default WaveformTable "+__WFT__+";\n"
    header=header+"Default SignalHeader  "+__SGH__+";\n"
    header=header+__CREATION_MSG__
    header=header+__pinhdr__+"\n"
    header=header+"$"+patname+"_begin\n"
    
    footer="$"+patname+"_end\n}"

    vectorsList=split(ostr,'\n')
    n=0;newvectorList=[]
    for vector in vectorsList:
        n=n+1
        vector="* "+vector+" *;\"vector add:"+str(n)+"\""
        newvectorList.append(vector)
    #End for
    new_ostr=join(newvectorList,'\n')+'\n'
    outfile = open(__OUTPUTFILE__, "w")
    outfile.write(header+new_ostr+footer)
    outfile.close()
#End makeOutputFile()

def buildVectors(content):
    raw_vectors=split(content,'***')
    index=0
    __addvectors__.append(__startvctr__)
    forcount=0
    preVecWasStrb=0
    strobe_flag=0#initialize
    for raw_vector in raw_vectors:
        forcount=forcount+1
        preVecWasStrb=strobe_flag
        drive_flag=0
        strobe_flag=0
        if __DEBUG__:
            print"\n\nloopcount:"+str(forcount)
            print"index:"+str(index)
            print"# of vectors:"+str(len(__addvectors__))

        #initialize next vector from previous vector (or from start vector)
        if index>0:
            if __control__ :
                if preVecWasStrb and index-2>=0:
                    __addvectors__.append(__addvectors__[index-2])
                else:
                    __addvectors__.append(__addvectors__[index-1])
            else:

                __addvectors__.append(__startvctr__)



        #since strings are immutable, we need to convert to a list
        #in order to modify
        thisvector=str2list(__addvectors__[index])
        if __DEBUG__: print "vector before:"+join(thisvector,"")
        for line in split(raw_vector,'\n'):
            drvpinsPat=re.compile("DRV:(?P<drvpins>.*?):")
            drvpinsObj=drvpinsPat.search(line)
            
            drvlevelPat=re.compile(":(?:.*?):(?P<drvlevel>.*)")
            drvlevelObj=drvlevelPat.search(line)
            
            strbpinsPat=re.compile("STRB:(?P<strbpins>.*?):")
            strbpinsObj=strbpinsPat.search(line)
            
            strblevelPat=re.compile(":(?:.*?):(?P<strblevel>.*)")
            strblevelObj=strblevelPat.search(line)
            
            #only process if drives or strobes are found
          
            if drvpinsObj and drvlevelObj:
                drive_flag=1
                drvpins = split(drvpinsObj.group('drvpins'),',')
                drvlevel = drvlevelObj.group('drvlevel')
                if __DEBUG__: 
                    print "drives found:"+drvpinsObj.group('drvpins')
                    print "drive level:"+drvlevel
                if __CLEARSTROBES__:
                    #we need to mask strobes since we are just driving this vector
                    thisvector=replace_all(thisvector,'0','x')
                    thisvector=replace_all(thisvector,'1','x')
                for pin in drvpins:
                    if drvlevel=='0':
                        thisvector[__pins__.index(pin)]='L'
                    elif drvlevel=='1':
                        thisvector[__pins__.index(pin)]='H'
                    elif drvlevel=='Z':
                        thisvector[__pins__.index(pin)]='Z'
                    else:
                        print "ERROR!!!  Unknown drive found!"
                        sys.exit(-1)
                    #End if
                #End for
            elif strbpinsObj and strblevelObj:
                strobe_flag=1
                strbpins = split(strbpinsObj.group('strbpins'),',')
                strblevel = strblevelObj.group('strblevel')
                if __DEBUG__: 
                    print "strobes found:"+strbpinsObj.group('strbpins')
                    print "strobe level:"+strblevel
                for pin in strbpins:
                    if __strobetype__ == 0:#force low
                        thisvector[__pins__.index(pin)]='0'
                    elif __strobetype__ == 1:#force high
                        thisvector[__pins__.index(pin)]='1'
                    elif __strobetype__ == 2:#keep value from input file
                        if strblevel=='0':
                            thisvector[__pins__.index(pin)]='0'
                        elif strblevel=='1':
                            thisvector[__pins__.index(pin)]='1'
                        else:
                            print "ERROR!!!  Unknown strobe found!"
                            sys.exit(-1)
                    #End if
                #End for
            #End if
        #End for

        if drive_flag or strobe_flag:
            if __DEBUG__: print "keeping vector"
            #make changes permanent
            __addvectors__[index]=join(thisvector,"")
            if __DEBUG__: 
                print "vector after: "+join(thisvector,"")
                print "__addvectors__["+str(index)+"]="+str(__addvectors__[index])
            index=index+1
        else:
            if __DEBUG__: print "discarding vector"
            #no changes
            __addvectors__.pop()
            if index==0:
                #back at 1st vector
                __addvectors__.append(__startvctr__)
            #End if
        #End if
    #End for
    if len(__addvectors__) < __MINVECTORLENGTH__:
        print len(__addvectors__)
        for i in range(1,__MINVECTORLENGTH__ - len(__addvectors__) + 1):
            __addvectors__.append(__startvctr__)    
#End buildVectors()
#-----------------------------------------------------------------------
#   promptUser()
#-----------------------------------------------------------------------
def promptUser(query,errmsg,choices):
    exit=False
    while 1:
      try:
        ans = raw_input(query)
        if ans.lower()=='x':
          exit=True
          break
        elif ans.lower() not in choices:
          raise TextException()
        else:
          break
      except Exception:
        print errmsg
    #End while
    if exit:sys.exit(-1)
    else: return ans
#End promptUser()
#-----------------------------------------------------------------------
#   getUserInput
#-----------------------------------------------------------------------
def getUserInput():
    #global reference so these variables can be edited in this function
    global __strobetype__,__control__
    strobetype_errmsg = "\nERROR!!! You Must Choose 'a', 'b' or 'c' (or 'x' to abort)\n"
    control_errmsg = "\nERROR!!! You Must Choose 'a' or 'b' (or 'x' to abort)\n"
    strobetype_q = """Enter strobe type:\n\
        a) Strobe all 0's\n\
        b) Strobe all 1's\n\
        c) Keep same as input\n"""
    control_q = """Enter control (does not affect strobes which are automatically removed):\n\
        a) Control:APPLY  (applies the drive data and preserves it vector to vector until new data changes it)\n\
        b) Control:REMOVE (applies the drive data and then replaces with character from start vector)\n"""
    strobetype_choices = ('a','b','c')
    control_choices = ('a','b')
    strobetype = promptUser(strobetype_q,strobetype_errmsg,strobetype_choices)
#    control = promptUser(control_q,control_errmsg,control_choices)
    control = 'b'
    if strobetype.lower()=='a':
        __strobetype__ = 0 #0's
    elif strobetype.lower()=='b':
        __strobetype__ = 1 #1's
    elif strobetype.lower()=='c':
        __strobetype__ = 2 #same as input
    if control.lower()=='a':
        __control__ = 1 #Control:APPLY
    elif control.lower()=='b':
        __control__ = 0 #Control:REMOVE
#End getUserInput()

#-----------------------------------------------------------------------
#   main
#-----------------------------------------------------------------------
def main():
    global __OUTPUTFILE__,__CREATION_MSG__
    
    # Get the arguments from the command line, except the first one.
    args = sys.argv[1:]
    if len(args) != 1:
        print "usage: "+__PROGFILE__+" "+__INPUTFILE__
        sys.exit(-1)
    
    localtime = time.asctime(time.localtime(time.time()))
    
    __CREATION_MSG__ = "\"Pattern generated by: "+__PROGFILE__+__VERSION__+" from an input text file\"\n\""+__AUTHOR__+"\"\n\"PATTERN CREATION DATE: "+str(localtime)+"\"\n\n"
    
    os.system('clear')
    print '\n\n'

    getUserInput()
    print '\n'

    infile = open(args[0], 'r')
    __OUTPUTFILE__=args[0]+'.vectors'
    content = infile.read()
    infile.close()

    #populate __pins__
    getPins(content)
    #populate __startvctr__
    getStartVector(content)
    
    if len(__startvctr__)!= len(__pins__):
    	print "ERROR!!!  Vector length doesn't match signal header length"
    	print "# of chars in start vector:"+str(len(__startvctr__))
    	print "VECTOR:"+str(__startvctr__)
    	print "# of pins in signal header:"+str(len(__pins__))
    	print "SIGNALHEADER:"+str(__pins__)
    	sys.exit(-1)
    #End if
    
    #populate __addvectors__
    buildVectors(content)
    
    ostr=join(__addvectors__,'\n')

    makeOutputFile(ostr)

    print '\n\n'
    print __PROGRAM_NAME__+" "+__VERSION__
    print __AUTHOR__
    print __DATEMODIFIED__
    print "SUCCESS!!! NEW FILE CREATED: "+__OUTPUTFILE__+"\n\n"


#End main()
#-----------------------------------------------------------------------
#     BEGIN MAIN
#-----------------------------------------------------------------------
if __name__ == '__main__':
    main()
