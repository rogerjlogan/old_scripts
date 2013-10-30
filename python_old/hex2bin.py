import sys
import re
import pprint
import os
#import string
from string import *
import math

# This program converts hex numbers to binary

__PROGRAM_NAME__ = "hex2bin converter"
__AUTHOR__ = "AUTHOR: Roger Logan, Anora Solutions, Test Engineer, Houston, TX"
__DATEMODIFIED__ = "LAST MODIFIED: April 6, 2011"
__VERSION__ = "v1.1"
__PROGFILE__ = "hex2bin.py"
__INPUTFILE__ = "<hex_values.txt>"
__OUTPUTFILE__ = "bin_values.txt"

__DEBUG__ = 0

def makeOutputFile(ostr):
    outfile = open(__OUTPUTFILE__, "w")
    outfile.write(ostr)
    outfile.close()
#End makeOutputFile()

#-----------------------------------------------------------------------
#   main
#-----------------------------------------------------------------------
def main():
    
    # Get the arguments from the command line, except the first one.
    args = sys.argv[1:]
    if len(args) != 1:
        print "usage: "+__PROGFILE__+" "+__INPUTFILE__
        sys.exit(-1)
    
    os.system('clear')
    print '\n\n'
    
    infile = open(args[0], 'r')
    content = infile.read()
    infile.close()
    
    HFtoEXTmap = [(0,368),(1,369),(2,370),(3,371),(4,372)]
    
    for hf,ex in HFtoEXTmap:
        print "hf: "+str(hf)+"\n"
        print "ex: "+str(ex)+"\n"
    
    sys.exit(-1)
    
    hex2binMap = {'0':'0000','1':'0001','2':'0010','3':'0011',\
                  '4':'0100','5':'0101','6':'0110','7':'0111',\
                  '8':'1000','9':'1001','A':'1010','B':'1011',\
                  'C':'1100','D':'1101','E':'1110','F':'1111',}

    #populate __addvectors__
    lines=split(content,'\n')
    hexvalues=[]
    for line in lines:
        if len(line)>1:
            hexvalues.append(line)
    binvalues=[]
    for hexv in hexvalues:
        binvalues.append(hexv+' ')
        for char in hexv:
            binvalues.append(hex2binMap[char])
        binvalues.append('\n')

    print 
    ostr=join(binvalues,'')

    print '\n\n'
    print __PROGRAM_NAME__+" "+__VERSION__
    print __AUTHOR__
    print __DATEMODIFIED__
    print "SUCCESS!!! NEW FILE CREATED: "+__OUTPUTFILE__+"\n\n"

    makeOutputFile(ostr)

#End main()
#-----------------------------------------------------------------------
#     BEGIN MAIN
#-----------------------------------------------------------------------
if __name__ == '__main__':
    main()
