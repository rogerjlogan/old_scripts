__FIND_LIST__ = ['AIC_CID_INM','AIC_CID_INP','AIC_HD_INM','AIC_HD_INP','AIC_HN_INM','AIC_HN_INP','AIC_LN_INM','AIC_LN_INP','AIC_MIC_INM','AIC_MIC_INP','LAN_RXM','LAN_RXP','LAN_TXM','LAN_TXP','PC_RXM','PC_RXP','PC_TXM','PC_TXP','VDDS_W16','VDD_L9','VR_VBASE1','VR_VBASE2','VR_VBASE3']
__REPL_STRING__ = ""

import sys
import re
import pprint
import os
#import string
from string import *
import time
import gzip

__PROGRAM_NAME__ = "Delete lines if contains word in list"
__AUTHOR__ = "AUTHOR: Roger Logan, Anora, Test Engineer, Dallas, TX"
__DATEMODIFIED__ = "LAST MODIFIED: November 12, 2013"
__VERSION__ = " v1.0"
__PROGFILE__ = "deleteline.py"
__INPUTFILE__ = "<inputfile.txt>"
__OUTPUTFILE__ = "output.txt"

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

    files=content.split('\n')
    for thisfile in  files:
        if not len(thisfile): continue
        if thisfile[-3:] == '.gz':
            f = gzip.open(thisfile, 'rb')
        else:
            f = open(thisfile, 'r')
        file_content = f.read()
        f.close()
        
        newcontent = ""
        lines = file_content.split('\n')
        for line in lines:
            delete=False
            for word in __FIND_LIST__:
                if '('+word+')' in line:
                    delete=True
            if not delete:
                newcontent += line+'\n'
        if thisfile[-3:] == '.gz':
            f = gzip.open(thisfile, 'wb')
        else:
            f = open(thisfile, 'w')
        f.write(newcontent)
        f.close()
    #End for
            
    print '\n\n'
    print __PROGRAM_NAME__+" "+__VERSION__
    print __AUTHOR__
    print __DATEMODIFIED__
    print "SUCCESS!!!\n\n"


#End main()
#-----------------------------------------------------------------------
#     BEGIN MAIN
#-----------------------------------------------------------------------
if __name__ == '__main__':
    main()
