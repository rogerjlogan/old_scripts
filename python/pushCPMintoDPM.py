import sys
import re
import pprint
import os
#import string
from string import *
import time


__PROGRAM_NAME__ = "PUSH CPM VECTORS INTO DPM"
__AUTHOR__ = "AUTHOR: Roger Logan, Anora Solutions, Test Engineer, Houston, TX"
__DATEMODIFIED__ = "LAST MODIFIED: September 27, 2011"
__VERSION__ = " v1.0"
__PROGFILE__ = "pushCPMintoDPM.py"
__INPUTFILE__  = "<cpm_pat.evo>" #CPM pattern modified with CPMcallDPM label
__OUTPUTFILE__ = "<cpm_pat.evo>.new"  #new cpm calling dpm pattern

__EVO_HEADER__ = "enVision:\"bl8:R10.3.2.WW0104:S3.0\"; /* 5.7 */\n\n"
__CREATION_MSG__ = ""#written in main time.time()

#dpm
__DPM_BEG__ = "DPM_AD_ACCU_scld_begin"  #place dpm begin label here
__CYC_CNT__ = 16210                 #place your cycle count here(NOTE: this is usually accurate in comments of last vector line Example:VNIR2=16210)
#cpm
__CPMcallDPM_LOC__ = "XXX_INSERT_VECTORS_HERE"     #copy this into your cpm pattern where you want your cpm calling dpm vectors to go

#-----------------------------------------------------------------------
#   main
#-----------------------------------------------------------------------
def main():
    global __OUTPUTFILE__
    global __CREATION_MSG__
    
    # Get the arguments from the command line, except the first one.
    args = sys.argv[1:]
    if len(args) != 1:
        print "usage: "+__PROGFILE__+" "+__INPUTFILE__
        sys.exit(-1)
    
    localtime = time.asctime(time.localtime(time.time()))
    
    __CREATION_MSG__ = "\"Pattern generated by: "+__PROGFILE__+__VERSION__+"\"\n\""+__AUTHOR__+"\"\n\"PATTERN CREATION DATE: "+str(localtime)+"\"\n\n"
    
    os.system('clear')
    print '\n\n'

    infile = open(args[0], 'r')
    __OUTPUTFILE__=args[0]+'.new'
    content = infile.read()
    infile.close()

    p = re.compile("\*(?P<firstvector>.*?)\*")
    firstvectorObj=p.search(content)
    if not firstvectorObj:
        print "Error! No vectors found!"
        sys.exit(-1)
    firstvectorStr=firstvectorObj.group("firstvector")
    numv=0
    for i in range(len(firstvectorStr)):
        if not strip(firstvectorStr[i]):continue
        numv+=1

    continues = "*"
    sdpvectstr  = "*"
    for i in range(numv):
        continues += ">"
        sdpvectstr  += "d"
    continues += "* DEF_WFT SH0; "
    sdpvectstr += "* DEF_WFT SH0; <RPT "+str(__CYC_CNT__)+",SDP>\n"
    vector1 = continues+"<LDA "+__DPM_BEG__+">\n"
    vector2 = continues+"<RPT DpmPipeline,SWCDPM>\n"
    vector3 = sdpvectstr
    vector4 = continues+"<SWCCPM>\n"
    addvectors = vector1 + vector2 + vector3 + vector4
    
    newcontent = content.replace(__CPMcallDPM_LOC__,addvectors)
    
    try:
        newcpmfile = open(__OUTPUTFILE__, "w")
    except:
        err="File Error: Unable to create new file.  Check permissions in this directory.\n"
        sys.exit(-1)
    newcpmfile.write(newcontent)
    newcpmfile.close()
    
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
